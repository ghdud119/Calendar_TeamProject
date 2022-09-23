#include "NominalList.h"

#include<vector>
#include<iostream>


using namespace std;

NominalList::NominalList()
{
}

NominalList::~NominalList()
{
}

void NominalList::Insert()
{
	UserInfomation NewUser;
	cout << "성명을 입력해주세요 : ";
	cin >> NewUser.name;
	cout << "계급을 입력해 주세요 : ";
	cin >> NewUser.rank;
	do 
	{
		
	} while (!equal<string, string>(Search(NewUser.ID)->ID, -1);
}

void NominalList::Delete(std::string ID)
{
}

UserInfomation* NominalList::Search(std::string ID)
{
	return nullptr;
}

