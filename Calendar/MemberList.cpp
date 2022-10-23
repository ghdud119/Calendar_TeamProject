#include "MemberList.h"

#define SAVEFILE "MemberListSaveFile.txt"

MemberList::MemberList()
{
	if (!FileInput())
	{
		cout << "\n�������� ������ ���α׷��� �����մϴ�.\n";
		cout << SAVEFILE << " �� ���� Ȥ�� �������ּ���.\n";
		exit(0);
	}
}

MemberList::~MemberList()
{
	FileOutput();
}

void MemberList::Insert()
{
	UserInformation input;
	string temp = "";
	string mtemp = "";

	int tempInt = 0;

	while (true)
	{
		cout << "���۴� �Է� : ";
		getline(cin, mtemp);

		if (mtemp[0] == 27)
			return;

		if (mtemp.length() == 6 || mtemp.length() == 7)
		{
			for (int i = 0; i < mtemp.length(); i++)
			{
				if (isdigit(mtemp[i]) != 0)
					temp += mtemp[i];
				else if (mtemp.length() == 6)
					temp += "0";
			}
			if (temp.length() != 6 || !temp.compare("000000"))
			{
				printf("��¥�� ���Ŀ� �°� �Է����ֽʽÿ�.\n");
				temp = "";
			}
			else
			{
				tempInt = stoi(temp);
				if (tempInt % 100 > 12 || tempInt % 100 <= 0 || tempInt == 0)
				{
					printf("��¥�� ���Ŀ� �°� �Է����ֽʽÿ�.\n");
					temp = "";
				}
				else
				{
					input.startingMonth = stoi(temp);
					temp = "";
					break;
				}
			}
		}
		else
		{
			printf("��¥�� ���Ŀ� �°� �Է����ֽʽÿ�.\n");
		}
	}

	bool IDCheck;
	while (true)
	{
		cout << "���̵� �Է� : ";
		getline(cin, input.ID);
		IDCheck = false;

		if (input.ID[0] == 27)
			return;
		else if (input.ID.length() < 3 || input.ID.length() > 15)
			IDCheck = true;

		for (int i = 0; i < input.ID.length(); i++)
		{
			if (!(58 > input.ID[i] && input.ID[i] > 46) && !(123 > input.ID[i] && input.ID[i] > 64))
			{
				IDCheck = true;
			}
		}
		if (IDCheck)
		{
			cout << "���̵�� �θ��ڿ� ���ڸ����� �����Ǿ�� �ϸ�, 3�� �̻� 15�� ���Ͽ��� �մϴ�.\n";
			continue;
		}
		else if (Search(input.ID) == -1)
			break;
		else
			cout << "�̹� �����ϴ� ���̵��Դϴ�.\n";
	}
	cout << "��� ����� �Ϸ�Ǿ����ϴ�." << endl;
	this->memberList.push_back(input);
	Sort();
}

void MemberList::Delete()
{
	std::string ID;
	cout << "������ �ٹ����� ���̵� �Է��Ͻʽÿ�. �Է� : ";
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
					{
						if (tempStr.length() != 6)
						{
							printf("���� �б� ����, ���������� ���۴� ������ �߸��Ǿ����ϴ�.\n");
							return false;
						}

						int tempInt = stoi(tempStr);
						if (tempInt % 100 > 12 || tempInt % 100 <= 0 || tempInt == 0)
						{
							printf("���� �б� ����, ���������� ���۴� ������ �߸��Ǿ����ϴ�.\n");
							return false;
						}
						else
						{
							insert.startingMonth = tempInt;
							tempStr = "";
						}
						break;
					}
					case 1:
					{
						insert.ID = tempStr;
						memberList.push_back(insert);
						tempStr = "";
						break;
					}
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
