#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <sstream>
#include "Calendar.h"
#include "MemberList.h"

using namespace std;

Calendar *calendar = new Calendar();
MemberList *memberList = new MemberList();
int isWorking = -1;
string deletedID = "-1";



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
int STATE[DAYMAX];
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

bool ChalenderFileInput(int month, string* ID, int* STATE);
void ChalenderFileOutput(int month, string* ID, int* STATE);

int Search(vector<pair<UserInformation, int>> *validlist, string id);

int main()
{
	mainMenu();
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
				// return;
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
		ChalenderFileInput(date, ID, STATE);
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

	}
	else
	{
		date = stoi(memberList->GetWorkingCalender());
		ChalenderFileInput(date, ID, STATE);
		Calendar cal;
		lastday = cal.Lastday(date / 100, date % 100);
	}


	/***** �ٹ�ǥ ��� *****/

	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i])
			calendar->InsertInfo(i, ID[i]);
	}

	calendar->PrintCalendar(date / 100, date % 100);

	/***** ��ܿ��� �ٹ� ������ ������ �ο��� ���ο� �迭�� ���� *****/
	vector<pair<UserInformation, int>> validlist;
	vector<UserInformation>* tmpv = memberList->GetMemberList();
	int index = 0;
	for (auto iter = tmpv->begin(); iter != tmpv->end(); iter++, index++)
	{
		if (iter->startingMonth < date)
			validlist.push_back(make_pair(*iter, 0));
	}

	/***** ��Ģ - ����(p.19) �ٹ� ������ ������ ����� 1�� ������ ��� *****/
	if (validlist.size() <= 1) // ��ȹ�� ����!!!!!
	{
		cout << "�ش� ������ ���Ե� �� �ִ� �ٹ��ڰ� 1�� �����̹Ƿ� �ٹ�ǥ �ۼ��� �Ұ��մϴ�." << endl;
		return;
	}

	// ������ �ҷ��� ��� �ٹ� Ƚ�� ������
	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i] != vacant)
		{
			validlist[Search(&validlist, ID[i])].second += 1;
		}
	}

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
			cout << "�н��� �Ϸ�Ǿ����ϴ�." << endl;
			int temp = validlist[Search(&validlist, id)].second;
			validlist[Search(&validlist, id)].second = PASS;

			/***** ������ �н��� �ٹ��ڵ��� ������ �ٽ� �˻��� *****/
			for (int i = 0; i < validlist.size(); i++)
			{
				if (validlist[i].second == PASS)
				{
					tcount = 0;
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
					if (tcount < vcount)
					{
						cout << validlist[i].first.ID << "�ٹ��ڴ� �ٹ����� �ٽ� �����ؾ� �մϴ�. - �н� ���� �Ҹ���" << endl;
						validlist[Search(&validlist, id)].second = temp; // �ٹ�����Ƚ���� ���δ�.
					}
				}
			}
			return;
		}
		/***** �н� ������ ������ ��� *****/
		else
		{
			validlist[Search(&validlist, id)].second = PASS;
			cout << "�н��� �Ϸ�Ǿ����ϴ�." << endl;
		}
	}

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
		if (validlist[Search(&validlist, postID)].first.startingMonth >= validlist[Search(&validlist, id)].first.startingMonth)
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
		cout << "���� �Ϸ�" << endl;
		STATE[hopeday] = occupied;
		ID[hopeday] = id;
	}
	/***** ������ �ƴ� ��� ������ ��¥�� �ٷ� �ݿ��� *****/
	else
	{
		STATE[hopeday] = occupied;
		ID[hopeday] = id;
		cout << "��� �Ϸ�";
		validlist[Search(&validlist, id)].second += 1; // ����� �ٹ�Ƚ�� �߰�
		ChalenderFileOutput(date, ID, STATE);
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
	ChalenderFileOutput(date, ID, STATE);
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
	ChalenderFileInput(date, IDarr, junk);

	for (int i = 1; i < DAYMAX; i++)
	{
		if(junk[i])
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

	//�ǹ� ��Ģ - �޸� üũ�ϸ� ��. 5 -> 0�̸� �ڿ� 0�� �ƴϸ� �� / 5->1�̸� �ڿ��� 1�ƴϸ� 2���߸�.
	int returndate = stoi(str);
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

int Search(vector<pair<UserInformation, int>> *validlist, string id) // Ž�� ��� ���̵��� �ε����� ��ȯ��.
{
	int index = 0;
	for (auto iter = validlist->begin(); iter != validlist->end(); iter++, index++)
	{
		if (iter->first.ID.compare(id) == 0)
			return index;
	}
	return -1;
}

bool ChalenderFileInput(int month, string* _ID, int* _STATE)
{
	string inputFileName = to_string(month);
	inputFileName.insert(4, "-");
	inputFileName += ".txt";
	ifstream inputFile;
	inputFile.open(inputFileName);

	Calendar cal;
	int lastday = cal.Lastday(month / 100, month % 100);

	string tempID[DAYMAX] = { "" };
	int tempState[DAYMAX] = { 0 };


	string inputLine = "";
	string tempStr = "";

	int dayCount = 0;
	int count = 0;

	if (inputFile.is_open())
	{
		while (getline(inputFile, inputLine))
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
						dayCount = stoi(tempStr);
						if (dayCount > 32)
						{
							printf("���� �б� ����, ���������� ������ �߸��Ǿ����ϴ�.\n");
							return false;
						}
						tempStr = "";
					}
					case 1:
					{
						tempID[dayCount] = tempStr;
						tempStr = "";
						break;
					}
					case 2:
					{
						if (stoi(tempStr) > 2 || stoi(tempStr) < 0)
						{
							printf("���� �б� ����, ���������� ������ �߸��Ǿ����ϴ�.\n");
							return false;
						}
						tempState[dayCount] = stoi(tempStr);
						tempStr = "";
						break;
					}
					default:
						printf("���� �б� ����, ���������� ������ �߸��Ǿ����ϴ�.\n");
						return false;
					}
					count++;
					if (count > 2)
						break;
				}
			}
		}
		for (int i = 1; i <= lastday; i++)
		{
			_ID[i] = tempID[i];
			_STATE[i] = tempState[i];
		}
	}
	else
	{
		ofstream NewSaveFile(inputFileName);
		printf("�� ���� ������ �����Ͽ����ϴ�.\n");
		NewSaveFile.close();
	}
	inputFile.close();

	return month;
}

void ChalenderFileOutput(int month, string* ID, int* STATE)
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
		for (int i = 1; i <= lastday; i++)
		{
			outputFile << i << " " << ID[i] << " " << STATE[i] << endl;
		}
	}
	outputFile.close();
}