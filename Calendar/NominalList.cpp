#include "NominalList.h"

NominalList::NominalList()
{
	FileInput();
}

NominalList::~NominalList()
{
	FileOutput();
}

void NominalList::Insert()
{
	UserInfomation NewUser;
	cout << "이름을 입력해 주세요 : "; cin >> NewUser.name;
	cout << "계급을 입력해 주세요 : "; cin >> NewUser.rank;

	while (true)
	{
		cout << "아이디를 입력해 주세요 : "; cin >> NewUser.ID;
		if (Search(NewUser.ID) == -1)
			break;
		else
			cout << "이미 존재하는 아이디입니다.\n";
	}
	this->nominalList.push_back(make_pair(NewUser, NewUser.ID));
}

void NominalList::Delete(std::string targetID)
{
	int index = Search(targetID);
	if (index == -1)
		cout << "존재하지 않는 아이디입니다.\n";
	else
	{
		nominalList.erase(nominalList.begin() + index);
		cout << "해당 아이디 및 정보가 삭제되었습니다.\n";
	}
}

int NominalList::Search(string targetID)
{
	int index = 0;
	for (auto iter = this->nominalList.begin(); iter != this->nominalList.end(); iter++, index++)
	{
		if (iter->second.compare(targetID) == 0)
			return index;
	}
	return -1;
}

void NominalList::PrintList()
{
	if (nominalList.empty())
	{
		cout << "저장된 인원 정보가 없습니다.\n";
	}
	else
	{
		for (auto iter = this->nominalList.begin(); iter != this->nominalList.end(); iter++)
		{
			cout << "계급 : " << iter->first.rank << " 이름 : " << iter->first.name << " ID : " << iter->second << "\n";
		}
	}
}

void NominalList::FileInput()
{
	ifstream inputFile;
	inputFile.open("ListSave.txt");

	string inputLine = "";
	string tempStr = "";

	int count = 0;

	UserInfomation InsertInfo;

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
						InsertInfo.ID = tempStr;
						tempStr = "";
						break;
					case 1:
						InsertInfo.rank = tempStr;
						tempStr = "";
						break;
					case 2:
						InsertInfo.name = tempStr;
						nominalList.push_back(make_pair(InsertInfo, InsertInfo.ID));
						tempStr = "";
						break;
					default:
						printf("File Info Isert Error\n");
						break;
					}
					count++;
				}
			}
		}
	}
	else
	{
		cout << "There is No File.\n";
	}
	inputFile.close();
}

void NominalList::FileOutput()
{
	ofstream outputFile;
	outputFile.open("ListSave.txt");
	
	if (outputFile.is_open())
	{
		for (auto iter = nominalList.begin(); iter != nominalList.end(); iter++)
		{
			outputFile << iter->first.ID << " " << iter->first.rank << " " << iter->first.name << endl;
		}
	}

	outputFile.close();
}

void One_Line_Str_Input(vector<string>* inputVec)
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




