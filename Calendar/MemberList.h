#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct UserInfomation
{
	string startingMonth = "ERROR";
	string ID = "ERROR";
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

	void SetWorkingCalender(string yearMonth) { this->WorkingCalender = yearMonth; }
	string GetWorkingCalender() { return this->WorkingCalender; }

	//벡터 포인터 리턴 vector->first = struct(name, startingMonth), vector->second = ID
	vector<UserInfomation> *GetMemberList() { return &memberList; }

	bool FileInput();
	void FileOutput();

private:
	void Sort();
	static bool Compare(UserInfomation member1, UserInfomation member2) { return stoi(member1.startingMonth) < stoi(member2.startingMonth); }

private:
	vector<UserInfomation> memberList;
	string WorkingCalender = "-1";
};
