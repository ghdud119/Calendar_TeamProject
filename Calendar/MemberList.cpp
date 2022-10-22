#include "MemberList.h"

MemberList::MemberList()
{
	FileInput();
}

MemberList::~MemberList()
{
	FileOutput();
}

void MemberList::Insert()
{
	UserInfomation NewUser;

	while (true)
	{
		cout << "���̵� �Է��� �ּ��� : ";
		cin >> NewUser.ID;
		if (Search(NewUser.ID) == -1)
			break;
		else
		{
			cout << "�̹� �����ϴ� ���̵��Դϴ�.\n";
			return;
		}
	}

	cout << "���۴��� �Է��� �ּ��� : ";
	cin >> NewUser.startingMonth;

	this->memberList.push_back(NewUser);
	Sort();
}

void MemberList::Delete()
{
	std::string id;
	cout << "�̸��� �Է��� �ּ��� : ";
	cin >> id;
	int index = Search(id);
	if (index == -1)
		cout << "�������� �ʴ� ���̵��Դϴ�.\n";
	else
	{
		memberList.erase(memberList.begin() + index);
		cout << "�ش� ���̵� �� ������ �����Ǿ����ϴ�.\n";
	}
}

int MemberList::Search(string targetID)
{
	int index = 0;
	for (auto iter = this->memberList.begin(); iter != this->memberList.end(); iter++, index++)
	{
		if (iter->ID.compare(targetID) == 0)
			return index;
	}
	return -1;
}

void MemberList::Sort()
{
	sort(this->memberList.begin(), this->memberList.end(), Compare);
	return;
}

void MemberList::PrintList()
{
	if (memberList.empty())
	{
		cout << "����� �ο� ������ �����ϴ�.\n";
	}
	else
	{
		for (auto iter = this->memberList.begin(); iter != this->memberList.end(); iter++)
		{
			cout << "���� �� : " << iter->startingMonth << " ID : " << iter->ID << "\n";
		}
	}
}

bool MemberList::FileInput()
{
	ifstream inputFile;
	inputFile.open("MemberListSaveFile.txt");

	string inputLine = "";
	string tempStr = "";

	int count = 0;
	bool workingMonthCheck = false;

	UserInfomation InsertInfo;

	if (inputFile.is_open())
	{
		while (getline(inputFile, inputLine))
		{
			if (workingMonthCheck)
			{
				WorkingCalender = inputLine;
				if (WorkingCalender != "-1" || WorkingCalender.length() != 6)
				{
					printf("���� ������ ���� �� �����ϴ�.");
					return false;
				}
				workingMonthCheck = true;
				continue;
			}

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
						if (tempStr.length() != 6)
						{
							printf("���� ������ ���� �� �����ϴ�.");
							return false;
						}
						InsertInfo.startingMonth = tempStr;
						tempStr = "";
						break;

					case 1:
						InsertInfo.name = tempStr;
						tempStr = "";
						break;

					case 2:
						InsertInfo.ID = tempStr;
						memberList.push_back(make_pair(InsertInfo, InsertInfo.ID));
						tempStr = "";
						break;

					default:
						printf("���� ������ ���� �� �����ϴ�.");
						return false;
					}
					count++;
				}
			}
		}
	}
	else
	{
		ofstream NewSaveFile("MemberListSaveFile.txt");
		NewSaveFile.close();
	}
	inputFile.close();
	Sort();

	return true;
}

void MemberList::FileOutput()
{
	ofstream outputFile;
	outputFile.open("MemberListSaveFile.txt");

	if (outputFile.is_open())
	{
		outputFile << WorkingCalender << endl;
		for (auto iter = memberList.begin(); iter != memberList.end(); iter++)
		{
			outputFile << iter->first.startingMonth << " " << iter->first.name << " " << iter->first.ID << endl;
		}
	}

	outputFile.close();
}

void One_Line_Str_Input(vector<string> *inputVec)
{
	string inputStr;
	string tempStr = "";
	getline(cin, inputStr);

	inputStr += " ";

	for (int i = 0; i < inputStr.length(); i++)
	{
		if (inputStr[i] != ' ')
		{
			tempStr += inputStr[i];
		}
		else
		{
			inputVec->push_back(tempStr);
			tempStr = "";
		}
	}
	return;
}
