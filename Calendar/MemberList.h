#pragma once

#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

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
	vector<pair<string, string>> *GetMemberList() { return &memberList; }

	bool FileInput();
	void FileOutput();

private:
	void Sort();
	static bool Compare(pair<string, string> member1, pair<string, string> member2) { return stoi(member1.first) < stoi(member2.first); }

private:
	vector<pair<string, string>> memberList;
	string workingMonth = "-1";
};
