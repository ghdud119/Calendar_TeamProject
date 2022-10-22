#include <iostream>
#include <string>
#include "Calendar.h"
#include "MemberList.h"
#include "Menu.h"

const int IDMAX = 16;
const int DATEMAX = 7;

using namespace std;

int Search(vector<pair<UserInfomation, int>> validlist, string id)
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

vector<pair<UserInfomation, int>> listPickout(MemberList list, int date)
{
    vector<pair<UserInfomation, int>> validlist;
    // for (int i = 0; i < list.memberList.size(); i++)
    // {
    //     if (list.memberList[i].startingmonth > date)
    //     {
    //         validlist.push_back(list.memberList[i]);
    //     }
    // }

    return validlist;
}

bool isfirst(vector<pair<UserInfomation, int>> validlist, string id)
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

bool passTest(vector<pair<UserInfomation, int>> validlist, string id, int vcount)
{
    pair<UserInfomation, int> target;
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

bool priorityCompare(vector<pair<UserInfomation, int>> validlist, string pid, string id)
{
    if (validlist[Search(validlist, pid)].first.startingMonth >=
        validlist[Search(validlist, id)].first.startingMonth)
    {
        return false;
    }
    else
    {
        return true; // »¯À» ¼ö ÀÖÀ½
    }
}

bool checkID(string str)
{
    char id[IDMAX];
    strcpy(id, str.c_str());
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
    char date[DATEMAX];
    strcpy(date, str.c_str());
    int retval = 0;
    for (int i = 0; i < DATEMAX; i++)
    {
        if (date[i] > '0' && date[i] < '9')
        {
            date[i] = (int)date[i];
        }
        else
        {
            return -1;
        }
    }

    retval = date[0] * 100000 + date[1] * 10000 + date[2] * 1000 + date[3] * 100 + date[5] * 10 + date[6];
    return retval;
}

bool checkDay(int date)
{
    if (date < 10 && date > 0)
    {
        return true;
    }
    else if (date < Lastday) // from calendar
    {
        return true;
    }

    return false;
}

bool checkDate(int num)
{
    int m1 = num / 10000;
    int m2 = num / 100000;
    if (m1 > 1)
        return false;
    else if (m1 == 0 && m2 == 0)
        return false;
    else if (m1 == 1 && m2 > 2)
        return false;

    return true;
}