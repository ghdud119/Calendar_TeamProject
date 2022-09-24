#pragma once
#include<iostream>

using namespace std;

class Calendar
{
public:
	Calendar();
	~Calendar();
	void PrintCalendar(int year, int month);

private:
	bool IsLeapYear(int year) { return year % 4 == 0 && year % 100 != year % 400 == 0; }
	int	Lastday(int year, int month);
	int totalDay(int year, int month, int day);
	int weekDay(int year, int month, int day);

};