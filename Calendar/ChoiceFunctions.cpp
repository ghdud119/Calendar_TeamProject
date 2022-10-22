#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Calendar.h"
#include "MemberList.h"


const int IDMAX = 16;
const int DATEMAX = 7;

using namespace std;

int Search(vector<pair<UserInformation, int>> validlist, string id)
{
    validlist[1].first.ID;
    int index = 0;
    for (int i = 0; i < validlist.size(); i++, index++)
    {
        if (validlist[i].first.ID.compare(id) == 0)
            return index;
    }
    return -1;
}

vector<pair<UserInformation, int>> listPickout(MemberList list, int date)
{
    vector<pair<UserInformation, int>> validlist;
    vector<UserInformation>* temp = list.GetMemberList();
    for (auto iter = temp->begin(); iter != temp->end(); iter++)
    {
        if (stoi(iter->startingMonth) < date)
        {
            validlist.push_back(make_pair(*iter, 0));
        }
    }

    return validlist;
}

bool isfirst(vector<pair<UserInformation, int>> validlist, string id)
{
    int min = 100;
    for (int i = 0; i < validlist.size(); i++)
    {
        if (validlist[i].second < min)
        {
            min = validlist[i].second;
        }
    }

    if (validlist[Search(validlist, id)].second == min)
    {
        return false;
    }
    else if (validlist[Search(validlist, id)].second > min)
    {
        return true;
    }
}

bool passTest(vector<pair<UserInformation, int>> validlist, string id, int vcount)
{
    pair<UserInformation, int> target;
    int tcount = 0;
    for (int i = 0; i < validlist.size(); i++)
    {
        if (validlist[i].first.ID == id)
        {
            target = validlist[i];
        }
    }
    for (int i = 0; i < validlist.size(); i++)
    {
        if (target.first.startingMonth > validlist[i].first.startingMonth)
        {
            tcount++;
        }
    }
    if (tcount >= vcount)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool priorityCompare(vector<pair<UserInformation, int>> validlist, string pid, string id)
{
    if (validlist[Search(validlist, pid)].first.startingMonth >=
        validlist[Search(validlist, id)].first.startingMonth)
    {
        return false;
    }
    else
    {
        return true; // 뺏을 수 있음
    }
}

bool checkID(string str)
{
    char id[IDMAX];
    strcpy_s(id, str.c_str());
    for (int i = 0; i < IDMAX; i++)
    {
        if (!(id[i] > 'a' && id[i] < 'z') || !(id[i] > 'A' && id[i] < 'Z') || !(id[i] > '0' && id[i] < '9'))
        {
            // invalid id
            return false;
        }
    }

    return true;
}

int dateChanger(string str)
{
    string temp = str.erase(4, 1);

    return stoi(temp);
}

bool checkDay(int date)
{
    if (date < 10 && date > 0)
    {
        return true;
    }
    else if (date <= 31) // from calendar
    {
        return true;
    }

    return false;
}

bool checkDate(string str)
{
    if (str.length() != 7) { //전체 문자열 길이 체크
        return false;
    }

    for (int i = 0; i < str.length(); i++) { //숫자(0~9)와 구분자 체크
        if (isdigit(str[i]) == 0) { //숫자가 아님
            if (i != 4) { //구분자 자리가 아닌 곳에 숫자가 아닌 게 있을 경우
                return false;
            }
        }
        else {
            if (i == 4) { //구분자 자리에 숫자가 있는 경우
                return false;
            }
        }
    }

    //의미 규칙 - 달만 체크하면 됨. 5 -> 0이면 뒤에 0만 아니면 됨 / 5->1이면 뒤에가 1아니면 2여야만.
    int returndate = stoi(str);
    if (str[5] == '0') {
        if (str[6] == '0') {
            return false;
        }
        else {
            return true;

        }
    }
    else if (str[5] == '1') {
        if (str[6] == '1' || str[6] == '2') {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

    //return false;
}