#include <iostream>
#include <conio.h>
#include "Calendar.h"
#include "MemberList.h"
#include "ChoiceDay.cpp"

using namespace std;

Calendar* calendar = new Calendar();
MemberList* memberList = new MemberList();
int isWorking = -1;

int main()
{
	bool status = true;

	do
	{
		char selectmenu;

		cout << "���θ޴� �� �Է� ������Ʈ\n";
		cout << "1. �ٹ�ǥ ����\n";
		cout << "2. ��� ����\n";
		cout << "ESC. ���� �� ����\n";

		selectmenu = _getch();

		switch (selectmenu)
		{
		case 49: // 1
			cout << "�ٹ�ǥ\n";
			//Ķ���� �޴� �Լ�
			break;
		case 50: // 2
			cout << "��ܰ���\n";
			//��� �޴� �Լ�
			break;
		case 27: // ESC Ű
			cout << "����\n";
			status = false;
			break;
		default:
			cout << selectmenu << " �Է�.\n";
			cout << "�޴��� �����ϴ� �� �ڸ� ���ڸ��� �Է��Ͻʽÿ�.\n";
			break;
		}

		cout << "\n";
	} while (status);

	/*
	while (true)
	{
		//Test �κ�
		{

			string ID;

			cout << "���� ��� Ȯ��\n";
			memberList->PrintList();

			cout << "�ű� �ο� �Է�\n";
			memberList->Insert();

			cout << "������ ���̵� �Է� : \n";
			cin >> ID;
			memberList->Delete(ID);

			cout << "���� ��� Ȯ��\n";
			memberList->PrintList();
		}
	}
	*/
	memberList->~MemberList();
	calendar->~Calendar();

	return 0;
}

void mainMenu()
{
    bool status = true;
    do
    {
        char selectmenu;

        cout << "���θ޴� �� �Է� ������Ʈ\n";
        cout << "1. �ٹ�ǥ ����\n";
        cout << "2. ��� ����\n";
        cout << "ESC. ���� �� ����\n";

        selectmenu = _getch();

        switch (selectmenu)
        {
        case 49: // 1
            calendarMenu();
            break;
        case 50: // 2
            listMenu();
            break;
        case 27: // ESC Ű
            status = false;
            break;
        default:
            cout << selectmenu << " �Է�.\n";
            cout << "�޴��� �����ϴ� �� �ڸ� ���ڸ��� �Է��Ͻʽÿ�.\n";
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

        cout << "���θ޴� �� �Է� ������Ʈ\n";
        cout << "1. �ٹ�ǥ ����\n";
        cout << "2. �ٹ��� ����\n";
        cout << "ESC. ���� �� ����\n";

        selectmenu = _getch();

        switch (selectmenu)
        {
        case 49: // 1
            showSchedule();
            break;
        case 50: // 2
            if (memberList->GetMemberList())
                ChoiceDay(*memberList);
            break;
        case 27: // ESC Ű
            status = false;
            break;
        default:
            cout << selectmenu << " �Է�.\n";
            cout << "�޴��� �����ϴ� �� �ڸ� ���ڸ��� �Է��Ͻʽÿ�.\n";
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

        cout << "���θ޴� �� �Է� ������Ʈ\n";
        cout << "1. ��� ����\n";
        cout << "2. ��� ���\n";
        cout << "3. ��� ����\n";
        cout << "ESC. ���� �� ����\n";

        selectmenu = _getch();

        switch (selectmenu)
        {
        case 49: // 1
            memberList->PrintList();
            break;
        case 50:                 // 2
            if (isWorking == -1) // �ۼ� ���� �ٹ�ǥ �ִ��� ����
            {
                cout << "�ۼ� ���� �ٹ�ǥ�� �ϼ��Ǳ� ������ ��� ����� �� �� �����ϴ�." << endl;
            }
            memberList->Insert();
            break;
        case 51: // 3
            memberList->Delete();
            break;
        case 27: // ESC Ű
            status = false;
            break;
        default:
            cout << selectmenu << " �Է�.\n";
            cout << "�޴��� �����ϴ� �� �ڸ� ���ڸ��� �Է��Ͻʽÿ�.\n";
            break;
        }

        cout << "\n";
    } while (status);
}
