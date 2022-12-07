#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <sstream>
#include "Calendar.h"
#include "MemberList.h"

using namespace std;

#define WFILE "Workingcheck.txt"

Calendar* calendar = new Calendar();
MemberList* memberList = new MemberList();
int isWorking = -1;
string deletedID = "-1";

struct Team
{
	string TeamName = "ERROR";
	UserInformation userinfo[3];
};


const int DAYMAX = 32;
const int IDMAX = 16;
const int DATEMAX = 7;
const int PASS = 999;

enum state
{
	vacant = 0,
	occupied,
	confirmed
};

string ID[DAYMAX];
string team[DAYMAX];
vector<Team> teamList;

int STATE[DAYMAX];

/// �߰�����
int teamindex;
int dayworker = 0;
bool teambuild = true;
// �߰�����

vector<int> fileStatingMonth;
vector<string> fileID;
vector<string> fileChoiceDate;

void mainMenu();
void calendarMenu();
void listMenu();
void ChoiceDay();
void showSchedule();

bool checkID(string str);
int dateChanger(string str);
bool checkDayint(string str);
bool checkDay(int date, int day);
bool checkDate(string str);

bool CalenderFileInput(int month, string* team, vector<Team>* teamList, int* _STATE);
void CalenderFileOutput(int month, string* team, vector<Team>* teamList, int* STATE);

int Search(vector<pair<UserInformation, int>>* validlist, string id);

int Search(vector<pair<UserInformation, int>> *validlist, string id);
vector<pair<string, int>> wfileinput();
void wfileout(vector<pair<UserInformation, int>> validlist, vector<pair<string, int>> workingcheck, int info);

int main()
{
	mainMenu();
	memberList->FileOutput(isWorking);
	memberList->~MemberList();
	calendar->~Calendar();
	return 0;
}

void mainMenu()
{
	isWorking = stoi(memberList->GetWorkingCalender());
	bool status = true;
	do
	{
		char selectmenu;

		cout << "1. �ٹ�ǥ ����\n";
		cout << "2. ��� ����\n";
		cout << "ESC. ���� �� ����\n";

		selectmenu = _getch();

		switch (selectmenu)
		{
		case 49: // 1
			calendarMenu();
			break;
		case 50: // 2
			listMenu();
			break;
		case 27: // ESC Ű
			status = false;
			break;
		default:
			cout << selectmenu << " �Է�.\n";
			cout << "�޴��� �����ϴ� �� �ڸ� ���ڸ��� �Է��Ͻʽÿ�.\n";
			break;
		}

		cout << "\n";
	} while (status);
}

void calendarMenu()
{

	bool status = true;
	do
	{
		char selectmenu;

		cout << "1. �ٹ�ǥ Ȯ��\n";
		cout << "2. �ٹ��� ����\n";
		cout << "ESC. ���� �� ����\n";

		selectmenu = _getch();

		switch (selectmenu)
		{
		case 49: // 1
			showSchedule();
			break;
		case 50: // 2
			ChoiceDay();
			break;
		case 27: // ESC Ű
			status = false;
			break;
		default:
			cout << selectmenu << " �Է�.\n";
			cout << "�޴��� �����ϴ� �� �ڸ� ���ڸ��� �Է��Ͻʽÿ�.\n";
			break;
		}

		cout << "\n";
	} while (status);
}

void listMenu()
{
	bool status = true;
	do
	{
		char selectmenu;

		cout << "���θ޴� �� �Է� ������Ʈ\n";
		cout << "1. ��� ����\n";
		cout << "2. ��� ���\n";
		cout << "3. ��� ����\n";
		cout << "ESC. ���� �� ����\n";

		selectmenu = _getch();

		switch (selectmenu)
		{
		case 49: // 1
			memberList->PrintList();
			break;
		case 50:				 // 2
			if (isWorking != -1) // �ۼ� ���� �ٹ�ǥ �ִ��� ����
			{
				cout << "�ۼ� ���� �ٹ�ǥ�� �ϼ��Ǳ� ������ ��� ����� �� �� �����ϴ�." << endl;
				return;
			}
			memberList->Insert();
			break;
		case 51: // 3
			deletedID = memberList->Delete();

			if (deletedID == "-1")
				cout << "���̵� ��ȿ���� �ʽ��ϴ�.\n"; // ��������
			else
			{
				cout << "���� �ٹ�ǥ�� ��ϵǾ� �ִ� �ٹ����Դϴ�. �����Ͻðڽ��ϱ�?";
				char answer;
				answer = _getch();
				switch (answer)
				{
				case 'Y':
					for (int i = 1; i < DAYMAX; i++) // ��ܿ��� ������ ID �ٹ�ǥ������ ����
					{
						if (ID[i] == deletedID)
						{
							ID[i] = "";
							STATE[i] = vacant;
						}
					}
					break;
				case 'N':
					return;

				default:
					break;
				}

			}
			break;
			break;
		case 27: // ESC Ű
			status = false;
			break;
		default:
			cout << selectmenu << " �Է�.\n";
			cout << "�޴��� �����ϴ� �� �ڸ� ���ڸ��� �Է��Ͻʽÿ�.\n";
			break;
		}

		cout << "\n";
	} while (status);
}

void ChoiceDay()
{
	string temp;
	string id;
	string input;
	int date = isWorking;
	int Month;
	int lastday;

	/***** �ۼ� ���� �ٹ�ǥ�� �ִ��� Ȯ�� *****/
	if (date == -1)
	{
		for (int i = 0; i < DAYMAX; i++)
		{
			ID[i] = "";
			STATE[i] = vacant;
		}

		cout << "�ٹ�ǥ �ۼ��� �����մϴ�. �ٹ�ǥ�� �ۼ��� ������ �Է��Ͻʽÿ�. �Է� : ";

		char escapeDetect = _getch();
		if (escapeDetect == 27)
		{
			cout << endl;
			return;
		}
		else
		{
			cout << escapeDetect;
			getline(cin, temp);
			temp.insert(0, 1, escapeDetect);
		}

		/***** ��Ģ - ����(p.19) �ٹ��� ������ �Ұ����� ��� *****/
		if (!checkDate(temp))
		{
			cout << "��¥�� ���Ŀ� �°� �Է��Ͻʽÿ�." << endl;
			return;
		}
		date = dateChanger(temp); // ���� ��ȯ string to int
		Month = date;
		CalenderFileInput(date, ID, &teamList, STATE);
		// ���� �߿� ���� ������ �ٹ�ǥ�� �ִ��� Ȯ���ϱ�
		int con_check = 0;
		Calendar cal;
		for (int i = 0; i < cal.Lastday(date / 100, date % 100); i++) {
			if (STATE[i] == 2)
				con_check++;
		}
		if (con_check == cal.Lastday(date / 100, date % 100)) {
			cout << "���� ������ �ٹ�ǥ�� �����մϴ�." << endl;
			return;
		}
		lastday = cal.Lastday(date / 100, date % 100);
		isWorking = date;
	}
	else
	{
		date = stoi(memberList->GetWorkingCalender());
		isWorking = date;
		CalenderFileInput(date, ID, &teamList, STATE);
		Calendar cal;
		lastday = cal.Lastday(date / 100, date % 100);
	}

	// �߰�����
	int totalworkers;

	// 1. �� ���� ���� ������ �Է� �޴� �κ�
	if (dayworker == 0)
	{
		cout << "���ϱٹ��ο��� �Է��Ͻʽÿ�. �Է� : " << endl;
		char escapeDetect = _getch();
		if (escapeDetect == 27)
		{
			cout << endl;
			return;
		}
		else
		{
			cout << escapeDetect;
			getline(cin, temp);
			temp.insert(0, 1, escapeDetect);
		}

		dayworker = stoi(temp);

		if (dayworker > 3 || dayworker < 1)
		{
			cout << "1 ~ 3 ������ �������� �Է����ֽʽÿ�." << endl;
			return;
		}
	}


	/***** ��ܿ��� �ٹ� ������ ������ �ο��� ���ο� �迭�� ���� *****/
	vector<pair<UserInformation, int>> validlist;
	vector<UserInformation>* tmpv = memberList->GetMemberList();
	
	vector<pair<string, int>> workingcheck = wfileinput();
	
	int index = 0;
	for (auto iter = tmpv->begin(); iter != tmpv->end(); iter++, index++)
	{
		if (iter->startingMonth < date)
			validlist.push_back(make_pair(*iter, 0));
	}

	/***** ��Ģ - ����(p.19) �ٹ� ������ ������ ����� 1�� ������ ��� *****/
	if (validlist.size() <= 1) // ��ȹ�� ����!!!!!
	{
		cout << "��ȿ�ٹ��ڰ� 1�� �����̹Ƿ� �ٹ�ǥ �ۼ��� �Ұ��մϴ�." << endl;
		isWorking = -1;
		return;
	}

	// ������ �ҷ��� ��� �ٹ� Ƚ�� ������
	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i] != vacant)
		{
			// ���� �ٹ� Ƚ�� ����
			validlist[Search(&validlist, ID[i])].second += 1;

			// ���� ���� �ٹ��ڵ� �ٹ� Ƚ�� ����
			for (int j = 0; j < teamList.size(); j++)
				if (ID[i] == teamList[j].userinfo[0].ID)
					for (int k = 1; k < dayworker; k++)
						validlist[Search(&validlist, teamList[j].userinfo[k].ID)].second += 1;
		}
	}

	// 2. �Է� �޴� ������ ���� ¥�� �κ�
	if (teambuild)
	{
		totalworkers = validlist.size();
		int remainder = totalworkers % dayworker;

		if (remainder == 0)
		{
			int remtemp = remainder;
			for (int i = 0; i < totalworkers / dayworker; i++)
			{
				int tempidx = 0;
				Team ttemp;
				ttemp.TeamName = to_string(i+1) + "��";
				teamList.push_back(ttemp); // ���ľ���

				for (remtemp; remtemp < dayworker + remainder; remtemp++)
				{
					teamList[i].userinfo[tempidx].ID = validlist[remtemp].first.ID;
					teamList[i].userinfo[tempidx].startingMonth = validlist[remtemp].first.startingMonth;
					tempidx++;
				}
				remainder += remtemp;
			}
		}
		else
		{
			int remtemp = remainder;
			for (int i = 0; i < totalworkers / dayworker; i++)
			{
				int tempidx = 0;
				Team ttemp;
				ttemp.TeamName = "1��";
				teamList.push_back(ttemp); // ���ľ���

				for (remtemp; remtemp < dayworker + remainder; remtemp++)
				{
					teamList[i].userinfo[tempidx].ID = validlist[remtemp].first.ID;
					teamList[i].userinfo[tempidx].startingMonth = validlist[remtemp].first.startingMonth;
					tempidx++;
				}
				remainder += remtemp;
			}
		}
		teambuild = false;
	}

	// 3. �� ����ϴ� �κ�
	switch (dayworker)
	{
	case 1:
		for (int i = 0; i < teamList.size(); i++)
			cout << teamList[i].TeamName << " : " << teamList[i].userinfo[0].ID << endl;
		break;
	case 2:
		for (int i = 0; i < teamList.size(); i++)
			cout << teamList[i].TeamName << " : " << teamList[i].userinfo[0].ID << " " << teamList[i].userinfo[1].ID << endl;
		break;
	case 3:
		for (int i = 0; i < teamList.size(); i++)
			cout << teamList[i].TeamName << " : " << teamList[i].userinfo[0].ID << " " << teamList[i].userinfo[1].ID << " " << teamList[i].userinfo[2].ID << endl;
		break;
	default:
		cout << "error" << endl;
		break;
	}
	

	/***** �ٹ�ǥ ��� *****/
	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i])
			calendar->InsertInfo(i, ID[i]);
	}

	calendar->PrintCalendar(date / 100, date % 100);


	/***** ���̵� �Է� �ޱ� *****/
	cout << "���̵� �Է��Ͻʽÿ�. �Է� : ";
	// getline(cin, id);
	char escapeDetect = _getch();
	if (escapeDetect == 27)
	{
		cout << endl;
		return;
	}
	else
	{
		cout << escapeDetect;
		getline(cin, id);
		id.insert(0, 1, escapeDetect);
	}

	/***** ��Ģ - ����(p.19) �ٹ��� ������ �Ұ����� ��� *****/
	if (memberList->Search(id) != -1 && Search(&validlist, id) == -1)
	{
		cout << id << "�ٹ��ڴ� �ٹ��� ����� �������� �ʽ��ϴ�." << endl;
		return;
	}
	/***** �Է� - ����(p.18) ��ܿ� ���� ���̵� �Է��� ��� *****/
	else if (Search(&validlist, id) == -1)
	{
		cout << "���̵� ��ȿ���� �ʽ��ϴ�." << endl;
		return;
	}
	// ���� Search�� �ݵ�� �����Ѵ�.


	/***** �Է¹��� �ٹ��ڰ� �����ϴ� ������ Ȯ�� *****/
	bool rechoice;
	int min = 100;
	int max = 0;
	for (auto iter = validlist.begin(); iter != validlist.end(); iter++)
	{
		if (iter->second < min)
		{
			min = iter->second;
		}
		if (iter->second > max)
		{
			max = iter->second;
		}
	}
	if (min == 0 && max == 0)
	{
		rechoice = false;
	}
	else if (min == max)
	{
		rechoice = false;
	}
	else if (validlist[Search(&validlist, id)].second == min)
	{
		rechoice = false;
	}
	else if (validlist[Search(&validlist, id)].second > min)
	{
		rechoice = true;
	}
	/***** ��Ģ - ���(p.20) ������ ��� Ȯ�� �޽��� *****/
	if (rechoice)
	{
		cout << "���� �ٸ� �ο����� �ٹ����� �������� �ʾҽ��ϴ�. �ٹ����� �����Ͻðڽ��ϱ�?"; //6-2-2
		char ans = _getch();
		cin.clear();

		if (ans == 'Y') {
			cout << "���̵� �Է��Ͻʽÿ�. �Է� : ";
			//getline(cin, id);
			escapeDetect = _getch();
			if (escapeDetect == 27)
			{
				cout << endl;
				return;
			}
			else
			{
				cout << escapeDetect;
				getline(cin, id);
				id.insert(0, 1, escapeDetect);
			}
			/***** ��Ģ - ����(p.19) �ٹ��� ������ �Ұ����� ��� *****/
			if (memberList->Search(id) != -1 && Search(&validlist, id) == -1)
			{
				cout << id << "�ٹ��ڴ� �ٹ��� ����� �������� �ʽ��ϴ�." << endl;
				return;
			}
			/***** �Է� - ����(p.18) ��ܿ� ���� ���̵� �Է��� ��� *****/
			else if (Search(&validlist, id) == -1)
			{
				cout << "���̵� ��ȿ���� �ʽ��ϴ�." << endl;
				return;
			}
		}
		else if (ans == 'N') {
			return;
		}
		else {
			cout << "Y �Ǵ� N���� �Է��Ͻʽÿ�." << endl;
			return;
		}
		// Y or N �Է¹ޱ�, ��ȿ�� �˻��ϱ�, N�̸� return�ϱ�
	}

	/***** ��¥ �Է¹ޱ�(PASS ����) *****/
	cout << "��� �ٹ����� �Է��Ͻʽÿ�. �Է� : ";
	//getline(cin, input);

	escapeDetect = _getch();
	if (escapeDetect == 27)
	{
		cout << endl;
		return;
	}
	else
	{
		cout << escapeDetect;
		getline(cin, input);
		input.insert(0, 1, escapeDetect);
	}
	/***** PASS�� �Է��� ��� �н� �׽�Ʈ *****/
	if (input == "PASS")
	{
		int vcount = 0;
		int tcount = 0;
		for (int i = 1; i <= lastday; i++)
		{
			if (STATE[i] == vacant)
			{
				vcount++;
			}
		}
		pair<UserInformation, int> target;
		for (int i = 0; i < validlist.size(); i++)
		{
			if (validlist[i].first.ID.compare(id) == 0)
			{
				target = validlist[i];
				break;
			}
		}
		for (int i = 0; i < validlist.size(); i++)
		{
			if (target.first.startingMonth < validlist[i].first.startingMonth && target.second >= validlist[i].second)
			{
				tcount++;
			}
		}
		/***** �н� ������ �Ҹ����� ��� *****/
		if (tcount < vcount)
		{
			cout << "�н� ������ �������� �ʽ��ϴ�." << endl;
			return;
		}
		/***** �н� ������ ���������� �����ϴ� ��� *****/
		if (rechoice)
		{
			for (int i = 0; i <= lastday; i++)
			{
				if (ID[i] == id && STATE[i] == occupied)
				{
					ID[i] = "";
					STATE[i] = vacant;
				}
			}

			cout << "�н��� �Ϸ�Ǿ����ϴ�." << endl;
			int postnum = validlist[Search(&validlist, id)].second;
			validlist[Search(&validlist, id)].second = PASS;

			/***** ������ �н��� �ٹ��ڵ��� ������ �ٽ� �˻��� *****/
			for (int i = 0; i < workingcheck.size(); i++)
			{
				if (workingcheck[i].second == PASS)
				{
					tcount = 0;
					vcount = 0;
					target = validlist[Search(&validlist, workingcheck[i].first)];

					cout << target.first.ID << "�� ���� �ٽ� �˻�" << endl;

					for (int k = 1; k <= lastday; k++)
					{
						if (STATE[k] == vacant)
						{
							vcount++;
						}
					}
					for (int j = 0; j < validlist.size(); j++)
					{
						if (target.first.startingMonth < validlist[j].first.startingMonth && target.second >= validlist[j].second)
						{
							tcount++;
						}
					}
					if (tcount < vcount)
					{
						cout << target.first.ID << "�ٹ��ڴ� �ٹ����� �ٽ� �����ؾ� �մϴ�. - �н� ���� �Ҹ���" << endl;
						workingcheck.erase(workingcheck.begin() + i);						
					}
				}
			}
			memberList->FileOutput(isWorking);
			wfileout(validlist, workingcheck, 1);
			CalenderFileOutput(date, ID, &teamList, STATE);
			return;
		}
		/***** �н� ������ ������ ��� *****/
		else
		{
			validlist[Search(&validlist, id)].second = PASS;
			cout << "�н��� �Ϸ�Ǿ����ϴ�." << endl;
			memberList->FileOutput(isWorking);
			wfileout(validlist, workingcheck, 1);
			CalenderFileOutput(date, ID, &teamList, STATE);
			return;
		}
	}
	cin.clear();

	/***** ��¥�� �Է��ϴ� ��� *****/
	if (!checkDayint(input)) //���ڰ� �ƴ� �ֵ� �Ÿ���
	{
		cout << "��¥�� ���Ŀ� �°� �Է��Ͻʽÿ�." << endl;
		return;
	}
	int hopeday = stoi(input);

	if (!checkDay(date, hopeday))
	{
		cout << "��¥�� ���Ŀ� �°� �Է��Ͻʽÿ�." << endl;
		return;
	}
	/***** ��Ģ - ����(p.20) Ȯ���� ��¥�� ��� *****/
	if (STATE[hopeday] == confirmed)
	{
		cout << "�ش� �ٹ����� �̹� Ȯ���Ǿ����ϴ�." << endl;
		return;
	}
	/***** ��Ż�� �õ��ϴ� ��� �켱������ �� *****/
	if (STATE[hopeday] == occupied)
	{
		string postID = ID[hopeday];
		if (validlist[Search(&validlist, postID)].first.startingMonth < validlist[Search(&validlist, id)].first.startingMonth)
		{
			cout << "�켱 ������ ���Ƽ� ��Ż�� �� �����ϴ�." << endl;
			return;
		}
		else
		{
			cout << "�ش� �ٹ�����" << postID << "�ٹ��ڰ� ���� ���Դϴ�.�ش� �ٹ����� �����Ͻðڽ��ϱ�?\n";
			char ans = _getch();

			if (ans == 'Y') {
			}
			else if (ans == 'N') {
				return;
			}
			else {
				cout << "Y �Ǵ� N���� �Է��Ͻʽÿ�." << endl;
				return;
			}
			validlist[Search(&validlist, postID)].second -= 1; // ��Ż, ������ �ٹ�Ƚ�� ����
			cout << postID << "�ٹ��ڴ� �ٹ����� �ٽ� �����ؾ� �մϴ�. - �ٹ��� ��Ż";
		}
	}

	/***** ���� ��� ������ ��������� ������ �ٹ����� �ݿ��� *****/

	/***** ������ ��� ������ ���� ���̴� ��¥�� ��� *****/
	if (rechoice)
	{
		for (int i = 0; i <= lastday; i++)
		{
			if (ID[i] == id && STATE[i] == occupied)
			{
				STATE[i] = vacant;
			}
		}
		/***** ������ ��¥ �ݿ� *****/
		cout << "�ٹ��� ������ �Ϸ�Ǿ����ϴ�." << endl;

		// 4. �ٹ����� �������� ��, ���� �������� �����ϴ� �κ�
		teamindex = -1;

		for (int i = 0; i < teamList.size(); i++)
		{
			for(int j=0; j<dayworker; j++)
				if (id == teamList[i].userinfo[j].ID)
				{
					teamindex = i;
				}		
		}

		if (teamindex == -1)
		{
			cout << "���� �ٹ����Դϴ�.\n" << endl;
			return;
		}
		for (int i = 0; i < dayworker; i++)
			validlist[Search(&validlist, teamList[teamindex].userinfo[i].ID)].second += 1;
		
		ID[hopeday] = teamList[teamindex].userinfo[0].ID;
		STATE[hopeday] = occupied;
	}
	/***** ������ �ƴ� ��� ������ ��¥�� �ٷ� �ݿ��� *****/
	else
	{
		teamindex = -1;

		for (int i = 0; i < teamList.size(); i++)
		{
			for (int j = 0; j < dayworker; j++)
				if (id == teamList[i].userinfo[j].ID)
				{
					teamindex = i;
				}
		}

		if (teamindex == -1)
		{
			cout << "���� �ٹ����Դϴ�.\n" << endl;
			return;
		}
		for (int i = 0; i < dayworker; i++)
			validlist[Search(&validlist, teamList[teamindex].userinfo[i].ID)].second += 1;

		ID[hopeday] = teamList[teamindex].userinfo[0].ID;
		STATE[hopeday] = occupied;

		cout << "�ٹ��� ������ �Ϸ�Ǿ����ϴ�.";
		wfileout(validlist, workingcheck, 1);
		CalenderFileOutput(date, ID, &teamList, STATE);
	}

	/***** �ϼ��Ǹ� Ȯ������ ���� *****/
	int complete = 1;
	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i] == vacant)
		{
			complete = 0;
		}
	}
	if (complete == 1)
	{
		for (int i = 0; i <= lastday; i++) // �ٹ�ǥ�� �ϼ��Ǹ� Ȯ������ ����
		{
			STATE[i] = confirmed;
		}
		isWorking = -1;
	}

	/***** �ٹ��ڵ��� ����Ƚ���� ���Ͽ� Ȯ���� *****/
	int cof = 1;
	int cmp = validlist[0].second;
	for (int i = 0; i < validlist.size(); i++)
	{
		if (cmp != validlist[i].second)
		{
			cof = 0;
		}
	}
	if (cof == 1)
	{
		for (int i = 0; i <= lastday; i++) // ��� �ٹ����� �ٹ�Ƚ���� ������ Ȯ������ ����
		{
			if (STATE[i] == occupied)
			{
				STATE[i] = confirmed;
			}
		}
	}

	// ���� ���� ID, STATE ����
	memberList->FileOutput(isWorking);
	wfileout(validlist, workingcheck, 0);
	CalenderFileOutput(date, ID, &teamList, STATE);
}
vector<pair<string, int>> wfileinput()
{
	ifstream inFile;
	inFile.open(WFILE);

	string inputLine = "";
	string tempStr = "";
	string idstr = "";
	vector<pair<string, int>> workingcheck;

	int count = 0;
	int linecount = 0;

	if (inFile.is_open())
	{
		while (getline(inFile, inputLine))
		{
			count = 0;
			inputLine += " ";
			for (int i = 0; i < inputLine.length(); i++)
			{
				if (inputLine[i] != ' ')
				{
					tempStr += inputLine[i];
				}
				else
				{
					switch (count)
					{
					case 0:
					{
						idstr = tempStr;
						tempStr = "";
						break;
					}
					case 1:
					{
						int tempInt = stoi(tempStr);
						tempStr = "";
						workingcheck.push_back(make_pair(idstr, tempInt));
						break;
					}
					default:
						printf("���� �б� ����, ���������� ������ �߸��Ǿ����ϴ�.\n");
						exit(1);
					}
					count++;
					if (count > 1)
						break;
				}
			}
		}

	}
	else
	{
		ofstream NewSaveFile(WFILE);
		printf("Workingcheck ���� ������ �����Ͽ����ϴ�.\n");
		NewSaveFile.close();
	}
	inFile.close();
	return workingcheck;
}

void wfileout(vector<pair<UserInformation, int>> validlist, vector<pair<string, int>> workingcheck, int info) {

	ofstream outworking;
	outworking.open(WFILE);

	if (info != 0) {
		if (outworking.is_open())
		{
			for (auto iter = workingcheck.begin(); iter != workingcheck.end(); iter++)
			{
				outworking << iter->first << " " << iter->second << endl;
			}

			for (auto iter = validlist.begin(); iter != validlist.end(); iter++)
			{
				if (iter->second == PASS) {
					outworking << iter->first.ID << " " << iter->second << endl;
				}
			}
		}
	}

	outworking.close();
}

void showSchedule()
{
	string temp;
	int date;
	cout << "������ �ٹ�ǥ�� ������ �Է��Ͻʽÿ� : " << endl;

	//getline(cin, temp);

	char escapeDetect = _getch();
	if (escapeDetect == 27)
	{
		cout << endl;
		return;
	}
	else
	{
		cout << escapeDetect;
		getline(cin, temp);
		temp.insert(0, 1, escapeDetect);
		cout << temp;
	}

	if (!checkDate(temp))
	{
		cout << "��¥�� ���Ŀ� �°� �Է��Ͻʽÿ�." << endl;
		return;
	}
	date = dateChanger(temp); // ���� ��ȯ string to int


	// ���� �о ����ϱ�
	string IDarr[DAYMAX];
	int junk[DAYMAX];
	CalenderFileInput(date, ID, &teamList, STATE);

	for (int i = 1; i < DAYMAX; i++)
	{
		if (junk[i])
			calendar->InsertInfo(i, IDarr[i]);
	}

	calendar->PrintCalendar(date / 100, date % 100);
}

bool checkID(string str)
{
	char id[IDMAX];
	strcpy_s(id, str.c_str());
	for (int i = 0; i < IDMAX; i++)
	{
		if (!(id[i] > 'a' && id[i] < 'z') || !(id[i] > 'A' && id[i] < 'Z') || !(id[i] > '0' && id[i] < '9'))
		{
			// invalid id
			return false;
		}
	}

	return true;
}

int dateChanger(string str)
{
	string temp = str.erase(4, 1);

	return stoi(temp);
}

bool checkDayint(string str) {
	//�̰� �ҷȴٴ� �� PASS�� �ƴ� ���ڿ��߸� ��.
	if (str.length() != 1 && str.length() != 2)
	{ //��ü ���ڿ� ���� üũ
		return false;
	}

	for (int i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]) == 0)
		{ //���ڰ� �ƴ�
			return false;
		}
	}
	return true;
}

bool checkDay(int date, int day)
{
	int checkyear = date / 100;
	int checkmon = date % 100;

	int m[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (checkyear % 4 == 0 && checkyear % 100 != checkyear % 400 == 0) {
		m[1] = 29;
	}
	else {
		m[1] = 28;
	}

	if (day > 0 && day <= m[checkmon - 1]) {
		return true;
	}
	else {
		return false;
	}
}

bool checkDate(string str)
{
	if (str.length() != 7)
	{ //��ü ���ڿ� ���� üũ
		return false;
	}

	for (int i = 0; i < str.length(); i++)
	{ //����(0~9)�� ������ üũ
		if (isdigit(str[i]) == 0)
		{ //���ڰ� �ƴ�
			if (i != 4)
			{ //������ �ڸ��� �ƴ� ���� ���ڰ� �ƴ� �� ���� ���
				return false;
			}
		}
		else
		{
			if (i == 4)
			{ //������ �ڸ��� ���ڰ� �ִ� ���
				return false;
			}
		}
	}

	//�ǹ� ��Ģ 
	int returndate = stoi(str);
	int checkyear = stoi(str.substr(0, 4));

	if (checkyear > 2000) {
		if (abs(2000 - checkyear) > 99 || abs(2000 - checkyear) < 1) return false;
	}
	else {
		if (abs(2000 - checkyear) > 100 || abs(2000 - checkyear) < 0) return false;
	}

	if (str[5] == '0')
	{
		if (str[6] == '0')
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (str[5] == '1')
	{
		if (str[6] == '1' || str[6] == '2')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	// return false;
}

int Search(vector<pair<UserInformation, int>>* validlist, string id) // Ž�� ��� ���̵��� �ε����� ��ȯ��.
{
	int index = 0;
	for (auto iter = validlist->begin(); iter != validlist->end(); iter++, index++)
	{
		if (iter->first.ID.compare(id) == 0)
			return index;
	}
	return -1;
}

//input(�ҷ��� ��, ���� �ٹ����� �迭, �� ����Ʈ �迭, State �迭) output(���� ����� true, ���� ������ false ���) *���� ����� ������Ʈ �迭�� �ʱ�ȭ�Ǹ�, �ش� ���� ������ ���ۼ���.
bool CalenderFileInput(int month, string* team, vector<Team>* teamList, int* _STATE)
{
	//�ش� �� �̸��� ���� ����
	string inputFileName = to_string(month);
	inputFileName.insert(4, "-");
	inputFileName += ".txt";
	ifstream inputFile;
	inputFile.open(inputFileName);

	Calendar cal;
	int lastday = cal.Lastday(month / 100, month % 100);

	string inputLine = "";
	string tempStr = "";
	int count = 0;

	if (inputFile.is_open())
	{
		teamList->clear();
		int count = 0;
		vector<string> tempStr;
		string strBuffer;
		Team tempTeam;
		//TeamList ����
		while (getline(inputFile, inputLine))
		{
			if (inputLine.compare("-"))
			{
				istringstream iss(inputLine);
				while (getline(iss, strBuffer, ' '))
				{
					tempStr.push_back(strBuffer);
				}
				for (auto iter = tempStr.begin(); iter != tempStr.end(); iter++, count++)
				{
					switch (count)
					{
					case 0:
						tempTeam.TeamName.assign(*iter);
						break;
					case 1:
						tempTeam.userinfo[0].ID.assign(*iter);
						break;
					case 2:
						tempTeam.userinfo[0].startingMonth = stoi(*iter);
						break;
					case 3:
						tempTeam.userinfo[1].ID.assign(*iter);
						break;
					case 4:
						tempTeam.userinfo[1].startingMonth = stoi(*iter);
						break;
					case 5:
						tempTeam.userinfo[2].ID.assign(*iter);
						break;
					case 6:
						tempTeam.userinfo[2].startingMonth = stoi(*iter);
						break;

					default:
						break;
					}
				}
				teamList->push_back(tempTeam);
				count = 0;
				tempStr.clear();
			}
			else
			{
				break;
			}
		}

		//�ٹ����� ����
		count = 1;
		while (getline(inputFile, inputLine))
		{
			istringstream iss(inputLine);
			while (getline(iss, strBuffer, ' '))
			{
				tempStr.push_back(strBuffer);
			}
			team[count] = tempStr[1];
			_STATE[count] = stoi(tempStr[2]);
			tempStr.clear();
			count++;
		}
	}
	else
	{
		ofstream NewSaveFile(inputFileName);
		printf("�� ���� ������ �����Ͽ����ϴ�.\n");
		NewSaveFile.close();
		return false;
	}

	inputFile.close();

	return true;
}

void CalenderFileOutput(int month, string* team, vector<Team>* teamList, int* STATE)
{
	string outPutFileName = to_string(month);
	outPutFileName.insert(4, "-");
	outPutFileName += ".txt";
	ofstream outputFile;
	outputFile.open(outPutFileName);

	Calendar cal;
	int lastday = cal.Lastday(month / 100, month % 100);

	if (outputFile.is_open())
	{
		for (auto iter = teamList->begin(); iter != teamList->end(); iter++)
		{
			outputFile << iter->TeamName << " " << iter->userinfo[0].ID << " " << iter->userinfo[0].startingMonth << " " << iter->userinfo[1].ID << " " << iter->userinfo[1].startingMonth << " " << iter->userinfo[2].ID << " " << iter->userinfo[2].startingMonth << endl;
		}
		outputFile << "-" << endl;
		for (int i = 1; i < DAYMAX; i++)
		{
			outputFile << i << " " << team[i] << " " << STATE[i] << endl;
		}
	}
	outputFile.close();
}