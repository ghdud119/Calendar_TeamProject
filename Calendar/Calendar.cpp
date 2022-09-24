#include<iomanip>
#include"Calendar.h"

#define WIDTH 6


Calendar::Calendar()
{
}

Calendar::~Calendar()
{
}

void Calendar::PrintCalendar(int year, int month)
{
	for (int i = 0; i < (WIDTH + 1) * 7; i++)	printf("_"); printf("\n");
	printf("                                     %d년  %d월\n", year, month);
	for (int i = 0; i < (WIDTH + 1) * 7; i++)	printf("_"); printf("\n");
	printf("    일    월     화     수     목     금     토\n");
	for (int i = 0; i < (WIDTH + 1) * 7; i++)	printf("_"); printf("\n");

	for (int i = 0; i < weekDay(year, month, 1); i++)
	{
		printf("       ");
	}

	for (int i = 1; i < Lastday(year, month) + 1; i++)
	{
		cout << setw(WIDTH) << i << " ";
		if (weekDay(year, month, i) == 6 && Lastday(year, month) != i)
		{
			printf("\n\n\n");
		}
	}
	printf("\n");
	for(int i = 0; i< (WIDTH+1)*7;i++)	printf("_");
	printf("\n");
}

int Calendar::Lastday(int year, int month)
{
	int m[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };	
	m[1] = IsLeapYear(year) ? 29 : 28;
	return m[month - 1];
}

int Calendar::totalDay(int year, int month, int day)
{
	int total = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
	for (int i = 1; i < month; i++)
	{
		total += Lastday(year, i);
	}
	return total + day;
}

int Calendar::weekDay(int year, int month, int day)
{
	return totalDay(year, month, day) % 7;
}
