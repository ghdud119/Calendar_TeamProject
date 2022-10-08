#include<iostream>

#include"Calendar.h"
#include"MemberList.h"

using namespace std;



int main()
{
	Calendar* calendar = new Calendar();
	MemberList* memberList = new MemberList();

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
			
			break;
		}
	}

	memberList->~MemberList();
	calendar->~Calendar();
}