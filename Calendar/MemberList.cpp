#include "MemberList.h"

#define SAVEFILE "MemberListSaveFile.txt"

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
	UserInformation input;
	string temp = "";

	while (true)
	{
		cout << "시작달을 입력해 주세요 : ";
		getline(cin, input.startingMonth);

		if (input.startingMonth[0] == 27)
			return;

		if (input.startingMonth.length() == 6 || input.startingMonth.length() == 7)
		{
			for (int i = 0; i < input.startingMonth.length(); i++)
			{
				cout << input.startingMonth << " " << temp << endl;

				if (isdigit(input.startingMonth[i]) != 0)
					temp += input.startingMonth[i];
				else if (input.startingMonth.length() == 6)
					temp += "0";
			}
			if (temp.length() != 6 || !temp.compare("000000"))
			{
				printf("잘못된 형식의 시작달 입력입니다.\n네글자의 연도+구분자+월의 형태로 입력해주세요\n");
			}
			else
			{
				input.startingMonth = temp;
				temp = "";
				break;
			}
		}
		else
		{
			printf("잘못된 형식의 시작달 입력입니다.\n네글자의 연도+구분자+월의 형태로 입력해주세요\n");
		}
	}

	while (true)
	{
		cout << "아이디를 입력해 주세요 : ";
		getline(cin, input.ID);
		if (input.ID[0] == 27)
			return;
		else if (Search(input.ID) == -1)
			break;
		else
			cout << "이미 존재하는 아이디입니다.\n";
	}
	this->memberList.push_back(input);
	Sort();
}

void MemberList::Delete()
{
	std::string ID;
	cout << "아이디을 입력해 주세요 : ";
	getline(cin, ID);
	int index = Search(ID);
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
	inputFile.open(SAVEFILE);

	string inputLine = "";
	string tempStr = "";

	int count = 0;
	bool workingMonthCheck = true;

	UserInformation insert;

	if (inputFile.is_open())
	{
		while (getline(inputFile, inputLine))
		{
			if (workingMonthCheck)
			{
				workingMonth = inputLine;
				if (!workingMonth.compare("-1 ") && workingMonth.length() != 6)
				{
					printf("파일 읽기 오류, 저장파일의 작업날짜 문법이 잘못되었습니다.\n");
					return false;
				}
				workingMonthCheck = false;
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
							printf("파일 읽기 오류, 저장파일의 날짜 문법이 잘못되었습니다.\n");
							return false;
						}
						insert.startingMonth = tempStr;
						tempStr = "";
						break;

					case 1:
						insert.ID = tempStr;
						memberList.push_back(insert);
						tempStr = "";
						break;

					default:
						printf("파일 읽기 오류, 저장파일의 문법이 잘못되었습니다.\n");
						return false;
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
		ofstream NewSaveFile(SAVEFILE);
		printf("새 저장 파일을 생성하였습니다.\n");
		NewSaveFile.close();
	}
	inputFile.close();
	Sort();

	return true;
}

void MemberList::FileOutput()
{
	ofstream outputFile;
	outputFile.open(SAVEFILE);

	if (outputFile.is_open())
	{
		outputFile << workingMonth << endl;
		for (auto iter = memberList.begin(); iter != memberList.end(); iter++)
		{
			outputFile << iter->startingMonth << " " << iter->ID << endl;
		}
	}

	outputFile.close();
}
