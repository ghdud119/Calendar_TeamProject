#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

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
	void Delete();
	int Search(string targetID);

	void PrintList();

	void SetWorkingCalender(string yearMonth) { this->workingMonth = yearMonth; }
	string GetWorkingCalender() { return this->workingMonth; }

	//벡터 포인터 리턴 vector->first = startingMonth, vector->second = ID
	vector<UserInformation> *GetMemberList() { return &memberList; }

	bool FileInput();
	void FileOutput();

private:
	void Sort();
	static bool Compare(UserInformation member1, UserInformation member2) { return member1.ID < member2.ID; }

private:
	vector<UserInformation> memberList;
	string workingMonth = "-1";
};
