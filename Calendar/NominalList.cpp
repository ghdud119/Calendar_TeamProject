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
	cout << "������ �Է����ּ��� : ";
	cin >> NewUser.name;
	cout << "����� �Է��� �ּ��� : ";
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

