#include <iostream>
#include "Calendar.h"
#include "MemberList.h"
using namespace std;

void mainMenu()
{
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
            calendarMenu();
            break;
        case 50: // 2
            listMenu();
            break;
        case 27: // ESC 키
            status = false;
            break;
        default:
            cout << selectmenu << " 입력.\n";
            cout << "메뉴에 존재하는 한 자리 숫자만을 입력하십시오.\n";
            break;
        }

        cout << "\n";
    } while (status);
}

void calendarMenu()
{
    bool status = true;
    do
    {
        char selectmenu;

        cout << "메인메뉴 및 입력 프롬프트\n";
        cout << "1. 근무표 열람\n";
        cout << "2. 근무일 선택\n";
        cout << "ESC. 저장 및 종료\n";

        selectmenu = _getch();

        switch (selectmenu)
        {
        case 49: // 1
            showSchedule();
            break;
        case 50: // 2
            ChoiceDay();
            break;
        case 27: // ESC 키
            status = false;
            break;
        default:
            cout << selectmenu << " 입력.\n";
            cout << "메뉴에 존재하는 한 자리 숫자만을 입력하십시오.\n";
            break;
        }

        cout << "\n";
    } while (status);

    return;
}

void listMenu()
{
    bool status = true;
    do
    {
        char selectmenu;

        cout << "메인메뉴 및 입력 프롬프트\n";
        cout << "1. 명단 보기\n";
        cout << "2. 명단 등록\n";
        cout << "3. 명단 삭제\n";
        cout << "ESC. 저장 및 종료\n";

        selectmenu = _getch();

        switch (selectmenu)
        {
        case 49: // 1
            memberList->PrintList();
            break;
        case 50: // 2
            if (workingSchedule)
            {
                cout << "작성 중인 근무표가 완성되기 전까지 명단 등록을 할 수 없습니다." << endl;
            }
            memberList->Insert();
            break;
        case 51: // 3
            memberList->Delete();
            break;
        case 27: // ESC 키
            status = false;
            break;
        default:
            cout << selectmenu << " 입력.\n";
            cout << "메뉴에 존재하는 한 자리 숫자만을 입력하십시오.\n";
            break;
        }

        cout << "\n";
    } while (status);
}
