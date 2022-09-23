#pragma once
class NominalList
{
public:
	struct UserInfomation
	{
		string name = "ERROR";
		string rank = "ERROR";
		string ID = "-1";
	};

public:
	NominalList();
	~NominalList();
	void Insert();
	void Delete(std::string ID);
	UserInfomation* Search(std::string ID);
	
private:

	vector<pair<UserInfomation, string>> nominalList;
};

