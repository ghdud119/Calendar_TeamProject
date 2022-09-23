#include<iostream>

#include"Calendar.h"

using namespace std;

int main()
{
	int year = 0, month = 0;
	while (year != -1)
	{
		cin >> year;
		cin >> month;
		Calendar *calendar = new Calendar();
		calendar->PrintCalendar(year,month);

	}
}