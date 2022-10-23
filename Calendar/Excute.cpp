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

void mainMenu();
void calendarMenu();
void listMenu();
void ChoiceDay();
void showSchedule();

bool checkID(string str);
int dateChanger(string str);
bool checkDay(int date);
bool checkDate(string str);

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
			if (isWorking == -1) // �ۼ� ���� �ٹ�ǥ �ִ��� ����
			{
				cout << "�ۼ� ���� �ٹ�ǥ�� �ϼ��Ǳ� ������ ��� ����� �� �� �����ϴ�." << endl;
				// return;
			}
			memberList->Insert();
			break;
		case 51: // 3
			memberList->Delete();
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
	int date = -1;
	int Month;
	STATE[0] = confirmed;
	for (int i = 1; i < DAYMAX; i++)
	{
		STATE[i] = vacant;
	}

	// ���� �б�, date ���� �����ϱ�
	ifstream inputFile;
	inputFile.open("MemberListSaveFile.txt");

	string inputLine = "";
	string tempStr = "";

	char check;
	inputFile.get(check);
	date = (int)check;

	if (date != -1) // condition 1. �ۼ� �� ����
	{
		for (int i = 0; i < DAYMAX; i++)
		{
			ID[i] = "";
			STATE[i] = vacant;
		}

		cout << "�ٹ�ǥ �ۼ��� �����մϴ�. �ٹ�ǥ�� �ۼ��� ������ �Է��Ͻʽÿ�. �Է� : ";
		getline(cin, temp); //���� �Է� �����ؾ���.

		if (!checkDate(temp))
		{
			cout << "��¥�� ���Ŀ� �°� �Է��Ͻʽÿ�." << endl;
			return;
		}
		date = dateChanger(temp); // ���� ��ȯ string to int
		Month = date;
		// ���� �߿� ���� ������ �ٹ�ǥ�� �ִ��� Ȯ���ϱ�
	}
	else
	{
		// ID, STATE �о� ����!!!
		while (!inputFile.eof()) {	//��� �� �д� �۾�
			getline(inputFile, inputLine);
			char lineid = inputLine[1];	//�ش� ���� ID ����
			for (int i = 2; i < inputLine.length(); i++) {	//�ٹ� ������ tempStr�� ����
				tempStr += inputLine[i] + " ";
			}

			vector<string> dates;	//������ ��¥�� �ִ� vector
			stringstream sstream(tempStr);	//tempStr�� �ɰ��� ���� vector
			string choice_date;	//sstream�� ������ �������� choice_date�� �ɰ��� ����
			while (getline(sstream, choice_date, ' ')) {
				dates.push_back(choice_date);
			}

			for (int i = 0; i < dates.size(); i++) {	//dates���� ������ ��¥���� ������
				int index = stoi(dates[i]);	//������ ��¥�� int�� index�� ��ȯ
				ID[index] = lineid;	//������ ��¥�� id ǥ��
				STATE[index] = confirmed;	//������ ��¥�� confirmed�� �ٲٱ�
			}
		}
		inputFile.close();
		date = 0; // date ���� ������ ���⼭!!
	}

	// �ٹ� ������ ������ �ο��� �߷���.
	vector<pair<UserInformation, int>> validlist;
	vector<UserInformation> *tmpv = memberList->GetMemberList();

	int index = 0;
	for (auto iter = tmpv->begin(); iter != tmpv->end(); iter++, index++)
	{
		if (iter->startingMonth < date)
			validlist.push_back(make_pair(*iter, 0));
	}

	if (validlist.size() <= 1) // ��ȹ�� ����!!!!!
	{
		cout << "�ٹ�ǥ�� �ۼ��ϱ⿡ �ο��� ������� �ʽ��ϴ�." << endl;
		return;
	}

	cout << "���̵� �Է��Ͻʽÿ�. �Է� : ";
	cin >> id;
	if (memberList->Search(id) != -1 && Search(&validlist, id) == -1)
	{
		cout << "%s �ٹ��ڴ� �ٹ��� ����� �������� �ʽ��ϴ�." << endl;
		return;
	}
	else if (Search(&validlist, id) == -1) // condition 2. ��ȿ�� ���̵�
	{
		cout << "���̵� ��ȿ���� �ʽ��ϴ�." << endl;
		return;
	}

	bool rechoice; // condition 3. ���� ����
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
	if (min == max)
	{
		rechoice = true;
	}
	else if (validlist[Search(&validlist, id)].second == min)
	{
		rechoice = false;
	}
	else if (validlist[Search(&validlist, id)].second > min)
	{
		rechoice = true;
	}

	if (rechoice)
	{
		cout << "���� �ٸ� �ο����� �ٹ����� �������� �ʾҽ��ϴ�. �ٹ����� �����Ͻðڽ��ϱ�?";
		// Y or N �Է¹ޱ�, ��ȿ�� �˻��ϱ�, N�̸� return�ϱ�
	}

	cout << "��� �ٹ����� �Է��Ͻʽÿ�. �Է� : ";
	cin >> input;
	if (input == "PASS") // condition 4. �н� �׽�Ʈ
	{
		int vcount = 0;
		int tcount = 0;
		for (int i = 0; i < DAYMAX; i++)
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
			if (target.first.startingMonth > validlist[i].first.startingMonth && target.second <= validlist[i].second)
			{
				tcount++;
			}
		}
		if (tcount < vcount)
		{
			cout << "�н� ������ �������� �ʽ��ϴ�." << endl;
			return;
		}

		if (rechoice)
		{
			cout << "�н��� �Ϸ�Ǿ����ϴ�." << endl;
			int temp = validlist[Search(&validlist, id)].second;
			validlist[Search(&validlist, id)].second = PASS;

			for (int i = 0; i < validlist.size(); i++)
			{
				if (validlist[i].second == PASS)
				{
					tcount = 0;
					for (int i = 0; i < validlist.size(); i++) // �ߺ� �ڵ�
					{
						if (validlist[i].first.ID.compare(id) == 0)
						{
							target = validlist[i];
							break;
						}
					}
					for (int i = 0; i < validlist.size(); i++)
					{
						if (target.first.startingMonth > validlist[i].first.startingMonth)
						{
							tcount++;
						}
					}
					if (tcount < vcount)
					{
						cout << validlist[i].first.ID << "%s �ٹ��ڴ� �ٹ����� �ٽ� �����ؾ� �մϴ�. - �н� ���� �Ҹ���" << endl;
						validlist[Search(&validlist, id)].second = temp;
					}
				}
			}
			return;
		}
		else
		{
			validlist[Search(&validlist, id)].second = PASS;
			cout << "�н��� �Ϸ�Ǿ����ϴ�." << endl;
		}
	}

	int hopeday = stoi(input);
	if (!checkDay(hopeday)) // condition 5. �Է��� ��ȿ��
	{
		cout << "��ȿ���� ���� �Է��Դϴ�." << endl;
		return;
	}

	if (STATE[hopeday] == confirmed) // condition 5. ��Ȯ�� ��¥
	{
		cout << "�ش� �ٹ����� �̹� Ȯ���Ǿ����ϴ�." << endl;
		return;
	}

	if (STATE[hopeday] == occupied) // condition 6. �켱���� ��
	{
		string postID = ID[hopeday];
		if (validlist[Search(&validlist, postID)].first.startingMonth >= validlist[Search(&validlist, id)].first.startingMonth)
		{
			cout << "�켱 ������ ���Ƽ� ��Ż�� �� �����ϴ�." << endl;
			return;
		}
		else
		{
			cout << "�ش� �ٹ����� %s �ٹ��ڰ� ���� ���Դϴ�. �ش� �ٹ����� �����Ͻðڽ��ϱ�?";
			// Y or N �Է¹ޱ�, ��ȿ�� �˻��ϱ�, N�̸� return�ϱ�
			validlist[Search(&validlist, postID)].second -= 1; // ��Ż, ������ �ٹ�Ƚ�� ����
			cout << "%s �ٹ��ڴ� �ٹ����� �ٽ� �����ؾ� �մϴ�. - �ٹ��� ��Ż";
		}
	}

	if (rechoice)
	{
		// ���� ���� ����
		for (int i = 0; i < DAYMAX; i++)
		{
			if (ID[i] == id && STATE[i] == occupied)
			{
				STATE[i] = vacant;
			}
		}
		cout << "���� �Ϸ�" << endl;
		STATE[hopeday] = occupied;
		ID[hopeday] = id;
	}
	else
	{
		STATE[hopeday] = occupied;
		ID[hopeday] = id;
		cout << "��� �Ϸ�";
		validlist[Search(&validlist, id)].second += 1; // ����� �ٹ�Ƚ�� �߰�

	}

	// Ȯ�� ����
	int cmp = validlist[0].second;
	for (int i = 0; i < validlist.size(); i++)
	{
		if (cmp != validlist[i].second)
		{
			return;
		}
	}
	for (int i = 0; i < DAYMAX; i++) // ��� �ٹ����� �ٹ�Ƚ���� ������ Ȯ������ ����
	{
		if (STATE[i] == occupied)
		{
			STATE[i] = confirmed;
		}
	}

	// ���� ���� ID, STATE ����
}

void showSchedule()
{
	string temp;
	int date;
	cout << "������ �ٹ�ǥ�� ������ �Է��Ͻʽÿ� : " << endl;
	getline(cin, temp);

	if (checkDate(temp))
	{
		cout << "��¥�� ���Ŀ� �°� �Է��Ͻʽÿ�." << endl;
		return;
	}
	date = dateChanger(temp); // ���� ��ȯ string to int

	// ���� �о ����ϱ�
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

bool checkDay(int date)
{
	if (date < 10 && date > 0)
	{
		return true;
	}
	else if (date <= 31) // ���� �ʿ�
	{
		return true;
	}

	return false;
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