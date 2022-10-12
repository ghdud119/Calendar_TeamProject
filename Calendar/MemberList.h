#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct UserInfomation
{
	string name = "ERROR";
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
	vector<pair<UserInfomation, string>> *GetMemberList() { return &memberList; }

	bool FileInput();
	void FileOutput();

private:
	void Sort();
	static bool Compare(pair<UserInfomation, string> member1, pair<UserInfomation, string> member2) { return stoi(member1.first.startingMonth) < stoi(member2.first.startingMonth); }

private:
	vector<pair<UserInfomation, string>> memberList;
	string WorkingCalender = "-1";
};
