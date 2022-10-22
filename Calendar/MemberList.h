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
	string startingMonth = "ERROR";
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
	// vector<UserInformation> *GetMemberList() { return &memberList; }
	vector<UserInformation>* GetMemberList()
	{
		UserInformation temp;
		for (auto iter = memberList.begin(); iter < memberList.end(); iter++)
		{
			UserInformation temp;
			temp.startingMonth = stoi(iter->startingMonth);
			temp.ID = iter->ID;
			mList.push_back(temp);
		}
		return &mList;
	}

	bool FileInput();
	void FileOutput();

private:
	void Sort();
	static bool Compare(UserInformation member1, UserInformation member2) { return stoi(member1.ID) < stoi(member2.ID); }

private:
	vector<UserInformation> memberList;
	vector<UserInformation> mList;
	string workingMonth = "-1";
};
