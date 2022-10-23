#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



class Calendar
{
public:
    Calendar();
    ~Calendar();
    void PrintCalendar(int year, int month);
    void InsertInfo(int date, string name);
    int Lastday(int year, int month);

private:
    bool IsLeapYear(int year) { return year % 4 == 0 && year % 100 != year % 400 == 0; }
    int totalDay(int year, int month, int day);
    int weekDay(int year, int month, int day);

private:
    vector <pair<int, string>> ChoicedInfo;
};