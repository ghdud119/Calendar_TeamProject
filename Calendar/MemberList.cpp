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
		cout << "아이디를 입력해 주세요 : ";
		cin >> NewUser.ID;
		if (Search(NewUser.ID) == -1)
			break;
		else
		{
			cout << "이미 존재하는 아이디입니다.\n";
			return;
		}
	}

	cout << "시작달을 입력해 주세요 : ";
	cin >> NewUser.startingMonth;

	this->memberList.push_back(NewUser);
	Sort();
}

void MemberList::Delete()
{
	std::string id;
	cout << "이름을 입력해 주세요 : ";
	cin >> id;
	int index = Search(id);
	if (index == -1)
		cout << "존재하지 않는 아이디입니다.\n";
	else
	{
		memberList.erase(memberList.begin() + index);
		cout << "해당 아이디 및 정보가 삭제되었습니다.\n";
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
		cout << "저장된 인원 정보가 없습니다.\n";
	}
	else
	{
		for (auto iter = this->memberList.begin(); iter != this->memberList.end(); iter++)
		{
			cout << "시작 달 : " << iter->startingMonth << " ID : " << iter->ID << "\n";
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
					printf("저장 파일을 읽을 수 없습니다.");
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
							printf("저장 파일을 읽을 수 없습니다.");
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
						printf("저장 파일을 읽을 수 없습니다.");
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
