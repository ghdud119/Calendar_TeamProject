#pragma once

#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>

using namespace std;

struct UserInformation
{
	string ID = "ERROR";
	int startingMonth = -1;
};

class MemberList
{
public:
	MemberList();
	~MemberList();

public:
	void Insert();
	string Delete();
	int Search(string targetID);

	void PrintList();

	void SetWorkingCalender(string yearMonth) { this->workingMonth = yearMonth; }
	string GetWorkingCalender() { return this->workingMonth; }

	//벡터 포인터 리턴 vector->first = startingMonth, vector->second = ID
	vector<UserInformation> *GetMemberList() { return &memberList; }

	bool FileInput();
	void FileOutput(int isw);

private:
	void Sort();
	static bool Compare(UserInformation member1, UserInformation member2) { return member1.startingMonth < member2.startingMonth; }

private:
	vector<UserInformation> memberList;
	string workingMonth = "-1";
};
