#include <iostream>
#include <conio.h>
#include "Calendar.h"
#include "MemberList.h"

using namespace std;

int main()
{
	Calendar *calendar = new Calendar();
	MemberList *memberList = new MemberList();
	bool status = true;

	do
	{
		char selectmenu;

		cout << "메인메뉴 및 입력 프롬프트\n";
		cout << "1. 근무표 관리\n";
		cout << "2. 명단 관리\n";
		cout << "ESC. 저장 및 종료\n";

		selectmenu = _getch();

		switch (selectmenu)
		{
		case 49: // 1
			cout << "근무표\n";
			//캘린더 메뉴 함수
			break;
		case 50: // 2
			cout << "명단관리\n";
			//명단 메뉴 함수
			break;
		case 27: // ESC 키
			cout << "종료\n";
			status = false;
			break;
		default:
			cout << selectmenu << " 입력.\n";
			cout << "메뉴에 존재하는 한 자리 숫자만을 입력하십시오.\n";
			break;
		}

		cout << "\n";
	} while (status);

	/*
	while (true)
	{
		//Test 부분
		{

			string ID;

			cout << "기존 명부 확인\n";
			memberList->PrintList();

			cout << "신규 인원 입력\n";
			memberList->Insert();

			cout << "제거할 아이디 입력 : \n";
			cin >> ID;
			memberList->Delete(ID);

			cout << "기존 명부 확인\n";
			memberList->PrintList();
		}
	}
	*/
	memberList->~MemberList();
	calendar->~Calendar();

	return 0;
}
