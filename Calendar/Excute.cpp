#include <iostream>
#include <conio.h>
#include "Calendar.h"
#include "MemberList.h"

using namespace std;

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
