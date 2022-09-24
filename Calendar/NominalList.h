#pragma once

#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
#include<iostream>

using namespace std;

struct UserInfomation
{
	string name = "ERROR";
	string rank = "ERROR";
	string ID = "-1";
};

class NominalList
{
public:
	NominalList();
	~NominalList();

public:
	void Insert();
	void Delete(std::string targetID);
	int Search(string targetID);
	void PrintList();

public:
	void FileInput();
	void FileOutput();

private:
	vector<pair<UserInfomation, string>> nominalList;
};

