#include<iostream>

#include"Calendar.h"
#include"NominalList.h"

using namespace std;



int main()
{
	Calendar* calendar = new Calendar();
	NominalList* nominalList = new NominalList();

	while (true)
	{
		//Test 부분
		{
			int year = 0, month = 0;

			cout << "확인할 연월 입력 : ";
			cin >> year >> month;

			string ID;
			calendar->PrintCalendar(year, month);

			cout << "기존 명부 확인\n";
			nominalList->PrintList();

			cout << "신규 인원 입력\n";
			nominalList->Insert();

			cout << "제거할 아이디 입력 : \n";
			cin >> ID;
			nominalList->Delete(ID);

			cout << "기존 명부 확인\n";
			nominalList->PrintList();
			
			break;
		}
	}

	nominalList->~NominalList();
	calendar->~Calendar();
}