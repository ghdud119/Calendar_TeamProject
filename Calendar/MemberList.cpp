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
		cout << "���۴��� �Է��� �ּ��� : ";
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
				printf("�߸��� ������ ���۴� �Է��Դϴ�.\n�ױ����� ����+������+���� ���·� �Է����ּ���\n");
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
			printf("�߸��� ������ ���۴� �Է��Դϴ�.\n�ױ����� ����+������+���� ���·� �Է����ּ���\n");
		}
	}

	while (true)
	{
		cout << "���̵� �Է��� �ּ��� : ";
		getline(cin, input.ID);
		if (input.ID[0] == 27)
			return;
		else if (Search(input.ID) == -1)
			break;
		else
			cout << "�̹� �����ϴ� ���̵��Դϴ�.\n";
	}
	this->memberList.push_back(input);
	Sort();
}

void MemberList::Delete()
{
	std::string ID;
	cout << "���̵��� �Է��� �ּ��� : ";
	getline(cin, ID);
	int index = Search(ID);
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
					printf("���� �б� ����, ���������� �۾���¥ ������ �߸��Ǿ����ϴ�.\n");
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
							printf("���� �б� ����, ���������� ��¥ ������ �߸��Ǿ����ϴ�.\n");
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
						printf("���� �б� ����, ���������� ������ �߸��Ǿ����ϴ�.\n");
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
		printf("�� ���� ������ �����Ͽ����ϴ�.\n");
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
