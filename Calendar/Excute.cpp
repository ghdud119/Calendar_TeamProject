#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <sstream>
#include "Calendar.h"
#include "MemberList.h"

using namespace std;

Calendar *calendar = new Calendar();
MemberList *memberList = new MemberList();
int isWorking = -1;

const int DAYMAX = 32;
const int IDMAX = 16;
const int DATEMAX = 7;
const int PASS = 999;

enum state
{
	vacant = 0,
	occupied,
	confirmed
};

string ID[DAYMAX];
int STATE[DAYMAX];

void mainMenu();
void calendarMenu();
void listMenu();
void ChoiceDay();
void showSchedule();

bool checkID(string str);
int dateChanger(string str);
bool checkDay(int date);
bool checkDate(string str);

int Search(vector<pair<UserInformation, int>> *validlist, string id);

int main()
{
	mainMenu();

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

		cout << "1. 근무표 확인\n";
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
		case 50:				 // 2
			if (isWorking == -1) // 작성 중인 근무표 있는지 변수
			{
				cout << "작성 중인 근무표가 완성되기 전까지 명단 등록을 할 수 없습니다." << endl;
				// return;
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

void ChoiceDay()
{
	string temp;
	string id;
	string input;
	int date = -1;
	int Month;
	STATE[0] = confirmed;
	for (int i = 1; i < DAYMAX; i++)
	{
		STATE[i] = vacant;
	}

	// 파일 읽기, date 변수 수정하기
	ifstream inputFile;
	inputFile.open("MemberListSaveFile.txt");

	string inputLine = "";
	string tempStr = "";

	char check;
	inputFile.get(check);
	date = (int)check;

	if (date != -1) // condition 1. 작성 중 여부
	{
		for (int i = 0; i < DAYMAX; i++)
		{
			ID[i] = "";
			STATE[i] = vacant;
		}

		cout << "근무표 작성을 시작합니다. 근무표를 작성할 연월을 입력하십시오. 입력 : ";
		getline(cin, temp); //공백 입력 가능해야함.

		if (!checkDate(temp))
		{
			cout << "날짜를 형식에 맞게 입력하십시오." << endl;
			return;
		}
		date = dateChanger(temp); // 형식 변환 string to int
		Month = date;
		// 파일 중에 동년 동월의 근무표가 있는지 확인하기
	}
	else
	{
		// ID, STATE 읽어 오기!!!
		while (!inputFile.eof()) {	//모든 줄 읽는 작업
			getline(inputFile, inputLine);
			char lineid = inputLine[1];	//해당 줄의 ID 저장
			for (int i = 2; i < inputLine.length(); i++) {	//근무 선택일 tempStr에 저장
				tempStr += inputLine[i] + " ";
			}

			vector<string> dates;	//선택한 날짜를 넣는 vector
			stringstream sstream(tempStr);	//tempStr을 쪼개기 위한 vector
			string choice_date;	//sstream을 공백을 기준으로 choice_date에 쪼개서 저장
			while (getline(sstream, choice_date, ' ')) {
				dates.push_back(choice_date);
			}

			for (int i = 0; i < dates.size(); i++) {	//dates에는 선택한 날짜들이 들어가있음
				int index = stoi(dates[i]);	//선택한 날짜를 int인 index로 변환
				ID[index] = lineid;	//선택한 날짜에 id 표시
				STATE[index] = confirmed;	//선택한 날짜에 confirmed로 바꾸기
			}
		}
		inputFile.close();
		date = 0; // date 변수 수정은 여기서!!
	}

	// 근무 투입이 가능한 인원만 추려냄.
	vector<pair<UserInformation, int>> validlist;
	vector<UserInformation> *tmpv = memberList->GetMemberList();

	int index = 0;
	for (auto iter = tmpv->begin(); iter != tmpv->end(); iter++, index++)
	{
		if (iter->startingMonth < date)
			validlist.push_back(make_pair(*iter, 0));
	}

	if (validlist.size() <= 1) // 기획서 수정!!!!!
	{
		cout << "근무표를 작성하기에 인원이 충분하지 않습니다." << endl;
		return;
	}

	cout << "아이디를 입력하십시오. 입력 : ";
	cin >> id;
	if (memberList->Search(id) != -1 && Search(&validlist, id) == -1)
	{
		cout << "%s 근무자는 근무자 요건을 만족하지 않습니다." << endl;
		return;
	}
	else if (Search(&validlist, id) == -1) // condition 2. 유효한 아이디
	{
		cout << "아이디가 유효하지 않습니다." << endl;
		return;
	}

	bool rechoice; // condition 3. 수정 여부
	int min = 100;
	int max = 0;
	for (auto iter = validlist.begin(); iter != validlist.end(); iter++)
	{
		if (iter->second < min)
		{
			min = iter->second;
		}
		if (iter->second > max)
		{
			max = iter->second;
		}
	}
	if (min == max)
	{
		rechoice = true;
	}
	else if (validlist[Search(&validlist, id)].second == min)
	{
		rechoice = false;
	}
	else if (validlist[Search(&validlist, id)].second > min)
	{
		rechoice = true;
	}

	if (rechoice)
	{
		cout << "아직 다른 인원들이 근무일을 선택하지 않았습니다. 근무일을 수정하시겠습니까?";
		// Y or N 입력받기, 유효성 검사하기, N이면 return하기
	}

	cout << "희망 근무일을 입력하십시오. 입력 : ";
	cin >> input;
	if (input == "PASS") // condition 4. 패스 테스트
	{
		int vcount = 0;
		int tcount = 0;
		for (int i = 0; i < DAYMAX; i++)
		{
			if (STATE[i] == vacant)
			{
				vcount++;
			}
		}
		pair<UserInformation, int> target;
		for (int i = 0; i < validlist.size(); i++)
		{
			if (validlist[i].first.ID.compare(id) == 0)
			{
				target = validlist[i];
				break;
			}
		}
		for (int i = 0; i < validlist.size(); i++)
		{
			if (target.first.startingMonth > validlist[i].first.startingMonth && target.second <= validlist[i].second)
			{
				tcount++;
			}
		}
		if (tcount < vcount)
		{
			cout << "패스 조건을 만족하지 않습니다." << endl;
			return;
		}

		if (rechoice)
		{
			cout << "패스가 완료되었습니다." << endl;
			int temp = validlist[Search(&validlist, id)].second;
			validlist[Search(&validlist, id)].second = PASS;

			for (int i = 0; i < validlist.size(); i++)
			{
				if (validlist[i].second == PASS)
				{
					tcount = 0;
					for (int i = 0; i < validlist.size(); i++) // 중복 코드
					{
						if (validlist[i].first.ID.compare(id) == 0)
						{
							target = validlist[i];
							break;
						}
					}
					for (int i = 0; i < validlist.size(); i++)
					{
						if (target.first.startingMonth > validlist[i].first.startingMonth)
						{
							tcount++;
						}
					}
					if (tcount < vcount)
					{
						cout << validlist[i].first.ID << "%s 근무자는 근무일을 다시 선택해야 합니다. - 패스 조건 불만족" << endl;
						validlist[Search(&validlist, id)].second = temp;
					}
				}
			}
			return;
		}
		else
		{
			validlist[Search(&validlist, id)].second = PASS;
			cout << "패스가 완료되었습니다." << endl;
		}
	}

	int hopeday = stoi(input);
	if (!checkDay(hopeday)) // condition 5. 입력의 유효성
	{
		cout << "유효하지 않은 입력입니다." << endl;
		return;
	}

	if (STATE[hopeday] == confirmed) // condition 5. 미확정 날짜
	{
		cout << "해당 근무일은 이미 확정되었습니다." << endl;
		return;
	}

	if (STATE[hopeday] == occupied) // condition 6. 우선순위 비교
	{
		string postID = ID[hopeday];
		if (validlist[Search(&validlist, postID)].first.startingMonth >= validlist[Search(&validlist, id)].first.startingMonth)
		{
			cout << "우선 순위가 낮아서 강탈할 수 없습니다." << endl;
			return;
		}
		else
		{
			cout << "해당 근무일은 %s 근무자가 점유 중입니다. 해당 근무일을 선택하시겠습니까?";
			// Y or N 입력받기, 유효성 검사하기, N이면 return하기
			validlist[Search(&validlist, postID)].second -= 1; // 강탈, 점유자 근무횟수 감소
			cout << "%s 근무자는 근무일을 다시 선택해야 합니다. - 근무일 강탈";
		}
	}

	if (rechoice)
	{
		// 이전 선택 삭제
		for (int i = 0; i < DAYMAX; i++)
		{
			if (ID[i] == id && STATE[i] == occupied)
			{
				STATE[i] = vacant;
			}
		}
		cout << "수정 완료" << endl;
		STATE[hopeday] = occupied;
		ID[hopeday] = id;
	}
	else
	{
		STATE[hopeday] = occupied;
		ID[hopeday] = id;
		cout << "등록 완료";
		validlist[Search(&validlist, id)].second += 1; // 사용자 근무횟수 추가

	}

	// 확정 갱신
	int cmp = validlist[0].second;
	for (int i = 0; i < validlist.size(); i++)
	{
		if (cmp != validlist[i].second)
		{
			return;
		}
	}
	for (int i = 0; i < DAYMAX; i++) // 모든 근무자의 근무횟수가 같으면 확정으로 변경
	{
		if (STATE[i] == occupied)
		{
			STATE[i] = confirmed;
		}
	}

	// 파일 쓰기 ID, STATE 저장
}

void showSchedule()
{
	string temp;
	int date;
	cout << "열람할 근무표의 연월을 입력하십시오 : " << endl;
	getline(cin, temp);

	if (checkDate(temp))
	{
		cout << "날짜를 형식에 맞게 입력하십시오." << endl;
		return;
	}
	date = dateChanger(temp); // 형식 변환 string to int

	// 파일 읽어서 출력하기
}

bool checkID(string str)
{
	char id[IDMAX];
	strcpy_s(id, str.c_str());
	for (int i = 0; i < IDMAX; i++)
	{
		if (!(id[i] > 'a' && id[i] < 'z') || !(id[i] > 'A' && id[i] < 'Z') || !(id[i] > '0' && id[i] < '9'))
		{
			// invalid id
			return false;
		}
	}

	return true;
}

int dateChanger(string str)
{
	string temp = str.erase(4, 1);

	return stoi(temp);
}

bool checkDay(int date)
{
	if (date < 10 && date > 0)
	{
		return true;
	}
	else if (date <= 31) // 수정 필요
	{
		return true;
	}

	return false;
}

bool checkDate(string str)
{
	if (str.length() != 7)
	{ //전체 문자열 길이 체크
		return false;
	}

	for (int i = 0; i < str.length(); i++)
	{ //숫자(0~9)와 구분자 체크
		if (isdigit(str[i]) == 0)
		{ //숫자가 아님
			if (i != 4)
			{ //구분자 자리가 아닌 곳에 숫자가 아닌 게 있을 경우
				return false;
			}
		}
		else
		{
			if (i == 4)
			{ //구분자 자리에 숫자가 있는 경우
				return false;
			}
		}
	}

	//의미 규칙 - 달만 체크하면 됨. 5 -> 0이면 뒤에 0만 아니면 됨 / 5->1이면 뒤에가 1아니면 2여야만.
	int returndate = stoi(str);
	if (str[5] == '0')
	{
		if (str[6] == '0')
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (str[5] == '1')
	{
		if (str[6] == '1' || str[6] == '2')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	// return false;
}

int Search(vector<pair<UserInformation, int>> *validlist, string id) // 탐색 대상 아이디의 인덱스를 반환함.
{
	int index = 0;
	for (auto iter = validlist->begin(); iter != validlist->end(); iter++, index++)
	{
		if (iter->first.ID.compare(id) == 0)
			return index;
	}
	return -1;
}