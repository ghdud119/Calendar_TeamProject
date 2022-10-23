#include <iomanip>
#include <vector>
#include <algorithm>
#include "Calendar.h"

#define WIDTH 6

Calendar::Calendar()
{
}

Calendar::~Calendar()
{
}

void Calendar::PrintCalendar(int year, int month)
{
	printf("\n");

	for (int i = 0; i < (WIDTH + 1) * 7; i++)	printf("_"); // --------
	printf("\n");

	printf("                                     %d��  %d��\n", year, month); // ��, ��

	for (int i = 0; i < (WIDTH + 1) * 7; i++)	printf("_"); // --------
	printf("\n");

	printf("    ��    ��     ȭ     ��     ��     ��     ��\n"); // ����

	for (int i = 0; i < (WIDTH + 1) * 7; i++)	printf("_"); // --------
	printf("\n");

	for (int i = 0; i < weekDay(year, month, 1); i++) // ��ĭó��
	{
		printf("       ");
	}

	/// /////////////////

	int cnt = 0;

	/// ////////////////////////
	int isFull = 0;
	for (int i = 1; i < Lastday(year, month) + 1; i++)
	{

		cout << setw(WIDTH) << i << " ";
		if (weekDay(year, month, i) == 6 && Lastday(year, month) != i)
		{
			printf("\n");
			if (cnt == 0)
				for (int k = 0; k < weekDay(year, month, 1); k++) // ��ĭó��
				{
					printf("       ");
				}

			for (int j = 1; j < i - cnt + 1; j++) // 1 ~ 8
			{
				isFull = 0;
				for (int t = 0; t < ChoicedInfo.size(); t++)
				{
					if (j + cnt == ChoicedInfo[t].first) // 5 ~ 12
					{
						if (ChoicedInfo[t].second.size() > 6)
							ChoicedInfo[t].second = ChoicedInfo[t].second.substr(0, 6);
						cout << setw(WIDTH) << ChoicedInfo[t].second << " ";
						isFull = 1;
					}
				}
				if (!isFull) printf("       ");
			}

			cnt = i;

			printf("\n\n");
		}
	}
	printf("\n");
	for (int i = 0; i < (WIDTH + 1) * 7; i++)	printf("_"); // --------
	printf("\n");
}

void Calendar::InsertInfo(int date, string name)
{
	ChoicedInfo.push_back(make_pair(date, name));
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
