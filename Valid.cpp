#include <iostream>
#include <string>
#include "Calendar.h"
#include "MemberList.h"

const int IDMAX = 16;
const int DATEMAX = 7;

using namespace std;

int dateChanger(string str)
{
}

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
}

bool isfirst(vector<pair<UserInfomation, int>> validlist, string id)
{
}

bool passTest(vector<pair<UserInfomation, int>> validlist, string id)
{
}

bool priorityCompare(vector<pair<UserInfomation, int>> validlist, string pid, string id)
{
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

bool checkDay(int date)
{
    if (date < 10 && date > 0)
    {
        return true;
    }
    else if (date < lastday) // from calendar
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