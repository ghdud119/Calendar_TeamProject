#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <sstream>
#include "Calendar.h"
#include "MemberList.h"

using namespace std;

#define WFILE "Workingcheck.txt"
#define WEEKFILE "weekendCheck.txt"

Calendar* calendar = new Calendar();
MemberList* memberList = new MemberList();
int isWorking = -1;
string deletedID = "-1";

struct Team
{
	string TeamName = "ERROR";
	UserInformation userinfo[3];
};


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
string team[DAYMAX];
vector<Team> teamList;
vector<pair<UserInformation, int>> validlist;

int STATE[DAYMAX];

/// 추가변수
int teamindex;
int dayworker = 0;
bool teambuild = true;
vector<pair<string, bool>> pre_Shift;
vector<pair<string, bool>> cur_Shift;
// 추가변수

vector<int> fileStatingMonth;
vector<string> fileID;
vector<string> fileChoiceDate;

void mainMenu();
void calendarMenu();
void listMenu();
void ChoiceDay();
void showSchedule();

bool checkID(string str);
int dateChanger(string str);
bool checkDayint(string str);
bool checkDay(int date, int day);
bool checkDate(string str);

bool CalenderFileInput(int month, string* team, vector<Team>* teamList, int* _STATE);
void CalenderFileOutput(int month, string* team, vector<Team>* teamList, int* STATE);

int Search(vector<pair<UserInformation, int>>* validlist, string id);

int Search(vector<pair<UserInformation, int>> *validlist, string id);
vector<pair<string, int>> wfileinput();
void wfileout(vector<pair<UserInformation, int>> validlist, vector<pair<string, int>> workingcheck, int info);

vector<pair<string, bool>> weekendInput();
void weekendOutput(vector<pair<string, bool>> shift);

int main()
{
	mainMenu();
	memberList->FileOutput(isWorking);
	memberList->~MemberList();
	calendar->~Calendar();
	return 0;
}

void mainMenu()
{
	isWorking = stoi(memberList->GetWorkingCalender());
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

		char escapeDetect = 0;
		string temp;
		switch (selectmenu)
		{
		case 49: // 1
			memberList->PrintList();
			break;
		case 50:				 // 2
			if (isWorking != -1) // 작성 중인 근무표 있는지 변수
			{
				cout << "작성 중인 근무표가 완성되기 전까지 명단 등록을 할 수 없습니다." << endl;
				return;
			}
			memberList->Insert();
			break;
		case 51: // 3
			cout << "삭제할 근무자의 아이디를 입력하십시오. 입력 : ";
			escapeDetect = _getch();
			if (escapeDetect == 27)
				break;
			else
			{
				getline(cin, temp);
				temp.insert(temp.length(), 0, escapeDetect);
				escapeDetect = 0;
			}
			if (memberList->Search(temp) == -1)
			{
				cout << "아이디가 유효하지 않습니다.";
			}
			else if (Search(&validlist, temp) != -1)
			{
				cout << "현재 근무표에 등록되어 있는 근무자입니다.";
				return;
			}
			else
			{
				deletedID = memberList->Delete();
			}

			break;
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
	int date = isWorking;
	int Month;
	int lastday;

	/***** 작성 중인 근무표가 있는지 확인 *****/
	if (date == -1)
	{
		for (int i = 0; i < DAYMAX; i++)
		{
			ID[i] = "";
			STATE[i] = vacant;
		}

		cout << "근무표 작성을 시작합니다. 근무표를 작성할 연월을 입력하십시오. 입력 : ";

		char escapeDetect = _getch();
		if (escapeDetect == 27)
		{
			cout << endl;
			return;
		}
		else
		{
			cout << escapeDetect;
			getline(cin, temp);
			temp.insert(0, 1, escapeDetect);
		}

		/***** 규칙 - 오류(p.19) 근무일 선택이 불가능한 경우 *****/
		if (!checkDate(temp))
		{
			cout << "날짜를 형식에 맞게 입력하십시오." << endl;
			return;
		}
		date = dateChanger(temp); // 형식 변환 string to int
		Month = date;
		// 파일 중에 동년 동월의 근무표가 있는지 확인하기
		temp[4] = '-';
		string t = temp + ".txt";
		const char* filename = t.c_str();
		FILE* f;
		if (f = fopen(filename, "r"))
		{
			fclose(f);
			cout << "동년 동월의 근무표가 존재합니다." << endl;
			return;
		}
		int con_check = 0;
		Calendar cal;
		for (int i = 0; i < cal.Lastday(date / 100, date % 100); i++) {
			if (STATE[i] == 2)
				con_check++;
		}
		if (con_check == cal.Lastday(date / 100, date % 100)) {
			cout << "동년 동월의 근무표가 존재합니다." << endl;
			return;
		}
		lastday = cal.Lastday(date / 100, date % 100);
		isWorking = date;
		CalenderFileInput(date, team, &teamList, STATE);

		//주말근무여부 초기화
		for (auto i = validlist.begin(); i < validlist.end(); i++)
			cur_Shift.push_back(make_pair(i->first.ID, false));

		/***** 주말 근무 여부 체크해서 true로 바꿔주기 *****/
		for (int i = 1; i < DAYMAX; i++) {
			Calendar cal;
			if (STATE[i] == occupied) {	//만약, 점유중인 날짜가 있다면
				for (auto j = pre_Shift.begin(); j < pre_Shift.end(); j++) {	//cur_Shift에서 ID와 날짜 체크해서 true만들기
					if (j->first.compare(ID[i]) == 0 && cal.weekDay(date / 100, date % 100, i) > 5) {
						//해당 날짜 근무자의 ID와 cur_Shift의 ID가 같고, 날짜가 주말이면
						j->second = true;
					}
				}
			}
		}
	}
	else
	{
		date = stoi(memberList->GetWorkingCalender());
		isWorking = date;
		CalenderFileInput(date, team, &teamList, STATE);
		Calendar cal;
		lastday = cal.Lastday(date / 100, date % 100);
	}

	// 추가변수
	int totalworkers;

	// 1. 몇 명이 조를 맺을지 입력 받는 부분
	if (dayworker == 0)
	{
		cout << "일일근무인원을 입력하십시오. 입력 : " << endl;
		char escapeDetect = _getch();
		if (escapeDetect == 27)
		{
			cout << endl;
			return;
		}
		else
		{
			cout << escapeDetect;
			getline(cin, temp);
			temp.insert(0, 1, escapeDetect);
		}

		dayworker = stoi(temp);

		if (dayworker > 3 || dayworker < 1)
		{
			cout << "1 ~ 3 사이의 정수값을 입력해주십시오." << endl;
			return;
		}
	}


	/***** 명단에서 근무 투입이 가능한 인원만 새로운 배열에 저장 *****/
	vector<UserInformation>* tmpv = memberList->GetMemberList();
	
	vector<pair<string, int>> workingcheck = wfileinput();
	
	int index = 0;
	for (auto iter = tmpv->begin(); iter != tmpv->end(); iter++, index++)
	{
		if (iter->startingMonth < date)
			validlist.push_back(make_pair(*iter, 0));
	}

	/***** 규칙 - 오류(p.19) 근무 투입이 가능한 사람이 1명 이하인 경우 *****/
	if (validlist.size() <= 1) // 기획서 수정!!!!!
	{
		cout << "유효근무자가 1명 이하이므로 근무표 작성이 불가합니다." << endl;
		isWorking = -1;
		return;
	}


	// team 배열에서 읽어온 값으로 ID 배열에 최선임 넣기
	for (int i = 1; i < DAYMAX; i++)
		if (team[i].size() != 0)
			for (int j = 0; j < teamList.size(); j++)
				if (teamList[j].TeamName == team[i])
					ID[i] = teamList[j].userinfo[0].ID;

	// 파일을 불러온 경우 근무 횟수 변경함
	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i] != vacant)
		{
			// 조장 근무 횟수 변경
			validlist[Search(&validlist, ID[i])].second += 1;

			// 같은 조인 근무자들 근무 횟수 변경
			for (int j = 0; j < teamList.size(); j++)
				if (ID[i] == teamList[j].userinfo[0].ID)
					for (int k = 1; k < dayworker; k++)
						validlist[Search(&validlist, teamList[j].userinfo[k].ID)].second += 1;
		}
	}

	// 2. 입력 받는 값으로 조를 짜는 부분
	if (teambuild)
	{
		totalworkers = validlist.size();
		int remainder = totalworkers % dayworker;

		if (remainder == 0)
		{
			int remtemp = remainder;
			for (int i = 0; i < totalworkers / dayworker; i++)
			{
				int tempidx = 0;
				Team ttemp;
				ttemp.TeamName = to_string(i + 1) + "조";
				teamList.push_back(ttemp); // 고쳐야함

				for (remtemp; remtemp < dayworker + remainder; remtemp++)
				{
					teamList[i].userinfo[tempidx].ID = validlist[remtemp].first.ID;
					teamList[i].userinfo[tempidx].startingMonth = validlist[remtemp].first.startingMonth;
					tempidx++;
				}
				remainder += remtemp;
			}
		}
		else
		{
			int remtemp = remainder;
			for (int i = 0; i < totalworkers / dayworker; i++)
			{
				int tempidx = 0;
				Team ttemp;
				ttemp.TeamName = to_string(i + 1) + "조";
				teamList.push_back(ttemp); 

				for (remtemp; remtemp < dayworker + remainder; remtemp++)
				{
					teamList[i].userinfo[tempidx].ID = validlist[remtemp].first.ID;
					teamList[i].userinfo[tempidx].startingMonth = validlist[remtemp].first.startingMonth;
					tempidx++;
				}
				remainder += remtemp;
			}
		}
		teambuild = false;
	}

	// 3. 조 출력하는 부분
	switch (dayworker)
	{
	case 1:
		for (int i = 0; i < teamList.size(); i++)
			cout << teamList[i].TeamName << " : " << teamList[i].userinfo[0].ID << endl;
		break;
	case 2:
		for (int i = 0; i < teamList.size(); i++)
			cout << teamList[i].TeamName << " : " << teamList[i].userinfo[0].ID << " " << teamList[i].userinfo[1].ID << endl;
		break;
	case 3:
		for (int i = 0; i < teamList.size(); i++)
			cout << teamList[i].TeamName << " : " << teamList[i].userinfo[0].ID << " " << teamList[i].userinfo[1].ID << " " << teamList[i].userinfo[2].ID << endl;
		break;
	default:
		cout << "error" << endl;
		break;
	}
	

	/***** 근무표 출력 *****/
	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i])
			calendar->InsertInfo(i, team[i]);
	}

	calendar->PrintCalendar(date / 100, date % 100);


	/***** 아이디 입력 받기 *****/
	cout << "아이디를 입력하십시오. 입력 : ";
	// getline(cin, id);
	char escapeDetect = _getch();
	if (escapeDetect == 27)
	{
		cout << endl;
		return;
	}
	else
	{
		cout << escapeDetect;
		getline(cin, id);
		id.insert(0, 1, escapeDetect);
	}

	/***** 규칙 - 오류(p.19) 근무일 선택이 불가능한 경우 *****/
	if (memberList->Search(id) != -1 && Search(&validlist, id) == -1)
	{
		cout << id << "근무자는 근무자 요건을 만족하지 않습니다." << endl;
		return;
	}
	/***** 입력 - 오류(p.18) 명단에 없는 아이디를 입력한 경우 *****/
	else if (Search(&validlist, id) == -1)
	{
		cout << "아이디가 유효하지 않습니다." << endl;
		return;
	}
	// 이하 Search는 반드시 성공한다.


	/***** 해당 인원의 주말 근무 여부를 체크 후 주말 근무라면 return *****/
	int weekendCheck = 0;
	for (auto i = pre_Shift.begin(); i < pre_Shift.end(); i++) {
		if (id == i->first && i->second)
			weekendCheck = 1;
	}
	if (weekendCheck) {
		cout << "주말 근무로 인해 이번 근무 선택에서 제외됩니다." << endl;
		return;
	}

	/***** 입력받은 근무자가 수정하는 것인지 확인 *****/
	bool rechoice;
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
	if (min == 0 && max == 0)
	{
		rechoice = false;
	}
	else if (min == max)
	{
		rechoice = false;
	}
	else if (validlist[Search(&validlist, id)].second == min)
	{
		rechoice = false;
	}
	else if (validlist[Search(&validlist, id)].second > min)
	{
		rechoice = true;
	}
	/***** 규칙 - 경고(p.20) 수정인 경우 확인 메시지 *****/
	if (rechoice)
	{
		cout << "아직 다른 인원들이 근무일을 선택하지 않았습니다. 근무일을 수정하시겠습니까?"; //6-2-2
		char ans = _getch();
		cin.clear();

		if (ans == 'Y') {
			cout << "아이디를 입력하십시오. 입력 : ";
			//getline(cin, id);
			escapeDetect = _getch();
			if (escapeDetect == 27)
			{
				cout << endl;
				return;
			}
			else
			{
				cout << escapeDetect;
				getline(cin, id);
				id.insert(0, 1, escapeDetect);
			}
			/***** 규칙 - 오류(p.19) 근무일 선택이 불가능한 경우 *****/
			if (memberList->Search(id) != -1 && Search(&validlist, id) == -1)
			{
				cout << id << "근무자는 근무자 요건을 만족하지 않습니다." << endl;
				return;
			}
			/***** 입력 - 오류(p.18) 명단에 없는 아이디를 입력한 경우 *****/
			else if (Search(&validlist, id) == -1)
			{
				cout << "아이디가 유효하지 않습니다." << endl;
				return;
			}
		}
		else if (ans == 'N') {
			return;
		}
		else {
			cout << "Y 또는 N만을 입력하십시오." << endl;
			return;
		}
		// Y or N 입력받기, 유효성 검사하기, N이면 return하기
	}

	/***** 날짜 입력받기(PASS 가능) *****/
	cout << "희망 근무일을 입력하십시오. 입력 : ";
	//getline(cin, input);

	escapeDetect = _getch();
	if (escapeDetect == 27)
	{
		cout << endl;
		return;
	}
	else
	{
		cout << escapeDetect;
		getline(cin, input);
		input.insert(0, 1, escapeDetect);
	}
	/***** PASS를 입력한 경우 패스 테스트 *****/
	if (input == "PASS")
	{
		int vcount = 0;
		int tcount = 0;
		for (int i = 1; i <= lastday; i++)
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
			if (target.first.startingMonth < validlist[i].first.startingMonth && target.second >= validlist[i].second)
			{
				tcount++;
			}
		}
		/***** 패스 조건을 불만족한 경우 *****/
		if (tcount < vcount)
		{
			cout << "패스 조건을 만족하지 않습니다." << endl;
			return;
		}
		/***** 패스 조건을 만족했으며 수정하는 경우 *****/
		if (rechoice)
		{
			for (int i = 0; i <= lastday; i++)
			{
				if (ID[i] == id && STATE[i] == occupied)
				{
					ID[i] = "";
					STATE[i] = vacant;
				}
			}

			cout << "패스가 완료되었습니다." << endl;
			int postnum = validlist[Search(&validlist, id)].second;
			validlist[Search(&validlist, id)].second = PASS;

			/***** 이전에 패스한 근무자들의 조건을 다시 검사함 *****/
			for (int i = 0; i < workingcheck.size(); i++)
			{
				if (workingcheck[i].second == PASS)
				{
					tcount = 0;
					vcount = 0;
					target = validlist[Search(&validlist, workingcheck[i].first)];

					cout << target.first.ID << "의 조건 다시 검색" << endl;

					for (int k = 1; k <= lastday; k++)
					{
						if (STATE[k] == vacant)
						{
							vcount++;
						}
					}
					for (int j = 0; j < validlist.size(); j++)
					{
						if (target.first.startingMonth < validlist[j].first.startingMonth && target.second >= validlist[j].second)
						{
							tcount++;
						}
					}
					if (tcount < vcount)
					{
						cout << target.first.ID << "근무자는 근무일을 다시 선택해야 합니다. - 패스 조건 불만족" << endl;
						workingcheck.erase(workingcheck.begin() + i);						
					}
				}
			}

			// team 배열에 ID 배열에 있는 근무자에 해당하는 조 이름 넣기
			for (int i = 0; i < DAYMAX; i++)
				if (ID[i].size() != 0)
					for (int j = 0; j < teamList.size(); j++)
						if (teamList[j].userinfo[0].ID == ID[i])
							team[i] = teamList[j].TeamName;

			memberList->FileOutput(isWorking);
			wfileout(validlist, workingcheck, 1);
			CalenderFileOutput(date, team, &teamList, STATE);
			return;
		}
		/***** 패스 조건을 만족한 경우 *****/
		else
		{
			validlist[Search(&validlist, id)].second = PASS;
			cout << "패스가 완료되었습니다." << endl;

			// team 배열에 ID 배열에 있는 근무자에 해당하는 조 이름 넣기
			for (int i = 0; i < DAYMAX; i++)
				if (ID[i].size() != 0)
					for (int j = 0; j < teamList.size(); j++)
						if (teamList[j].userinfo[0].ID == ID[i])
							team[i] = teamList[j].TeamName;

			memberList->FileOutput(isWorking);
			wfileout(validlist, workingcheck, 1);
			CalenderFileOutput(date, team, &teamList, STATE);
			return;
		}
	}
	cin.clear();

	/***** 날짜를 입력하는 경우 *****/
	if (!checkDayint(input)) //숫자가 아닌 애들 거르기
	{
		cout << "날짜를 형식에 맞게 입력하십시오." << endl;
		return;
	}
	int hopeday = stoi(input);

	if (!checkDay(date, hopeday))
	{
		cout << "날짜를 형식에 맞게 입력하십시오." << endl;
		return;
	}
	/***** 규칙 - 오류(p.20) 확정된 날짜인 경우 *****/
	if (STATE[hopeday] == confirmed)
	{
		cout << "해당 근무일은 이미 확정되었습니다." << endl;
		return;
	}
	/***** 강탈을 시도하는 경우 우선순위를 비교 *****/
	if (STATE[hopeday] == occupied)
	{
		string postID = ID[hopeday];
		if (validlist[Search(&validlist, postID)].first.startingMonth < validlist[Search(&validlist, id)].first.startingMonth)
		{
			cout << "우선 순위가 낮아서 강탈할 수 없습니다." << endl;
			return;
		}
		else
		{
			cout << "해당 근무일은" << postID << "근무자가 점유 중입니다.해당 근무일을 선택하시겠습니까?\n";
			char ans = _getch();

			if (ans == 'Y') {
			}
			else if (ans == 'N') {
				return;
			}
			else {
				cout << "Y 또는 N만을 입력하십시오." << endl;
				return;
			}
			validlist[Search(&validlist, postID)].second -= 1; // 강탈, 점유자 근무횟수 감소
			cout << postID << "근무자는 근무일을 다시 선택해야 합니다. - 근무일 강탈";
		}
	}

	/***** 이하 모든 조건을 통과했으며 선택한 근무일이 반영됨 *****/

	/***** 수정인 경우 이전에 점유 중이던 날짜를 비움 *****/
	if (rechoice)
	{
		for (int i = 0; i <= lastday; i++)
		{
			if (ID[i] == id && STATE[i] == occupied)
			{
				STATE[i] = vacant;
			}
		}
		/***** 선택한 날짜 반영 *****/
		cout << "근무일 수정이 완료되었습니다." << endl;

		// 4. 근무일을 선택했을 때, 같은 조끼리는 공유하는 부분
		teamindex = -1;

		for (int i = 0; i < teamList.size(); i++)
		{
			for(int j = 0; j < dayworker; j++)
				if (id == teamList[i].userinfo[j].ID)
				{
					teamindex = i;
				}		
		}

		if (teamindex == -1)
		{
			cout << "없는 근무자입니다.\n" << endl;
			return;
		}
		for (int i = 0; i < dayworker; i++)
			validlist[Search(&validlist, teamList[teamindex].userinfo[i].ID)].second += 1;
		
		ID[hopeday] = teamList[teamindex].userinfo[0].ID;
		STATE[hopeday] = occupied;

		/***** 점유할 날짜 주말근무여부 체크해서 수정 *****/
		Calendar weekCal;
		if (weekCal.weekDay(date / 100, date % 100, hopeday) > 5) {	//만약, hopeday가 주말이면
			for (int j = 0; j < dayworker; j++)	//하루 근무자 수 만큼 반복
				for (auto i = cur_Shift.begin(); i < cur_Shift.end(); i++)	//cur_Shift의 처음부터 끝까지
					if (i->first == teamList[teamindex].userinfo[j].ID)	//ID를 search해서 맞으면
						i->second = true;
		}
		else {
			for (int j = 0; j < dayworker; j++)	//하루 근무자 수 만큼 반복
				for (auto i = cur_Shift.begin(); i < cur_Shift.end(); i++)	//cur_Shift의 처음부터 끝까지
					if (i->first == teamList[teamindex].userinfo[j].ID)	//ID를 search해서 맞으면
						i->second = false;
		}
	}
	/***** 수정이 아닌 경우 선택한 날짜를 바로 반영함 *****/
	else
	{
		teamindex = -1;

		for (int i = 0; i < teamList.size(); i++)
		{
			for (int j = 0; j < dayworker; j++)
				if (id == teamList[i].userinfo[j].ID)
				{
					teamindex = i;
				}
		}

		if (teamindex == -1)
		{
			cout << "없는 근무자입니다.\n" << endl;
			return;
		}
		for (int i = 0; i < dayworker; i++)
			validlist[Search(&validlist, teamList[teamindex].userinfo[i].ID)].second += 1;

		ID[hopeday] = teamList[teamindex].userinfo[0].ID;
		STATE[hopeday] = occupied;

		/***** 점유할 날짜 주말근무여부 확인해서 수정 *****/
		Calendar weekCal;
		if (weekCal.weekDay(date / 100, date % 100, hopeday) > 5) {	//만약, hopeday가 주말이면
			for (int j = 0; j < dayworker; j++)	//하루 근무자 수 만큼 반복
				for (auto i = cur_Shift.begin(); i < cur_Shift.end(); i++)	//cur_Shift의 처음부터 끝까지
					if (i->first == teamList[teamindex].userinfo[j].ID)	//ID를 search해서 맞으면
						i->second = true;
		}
		else {
			for (int j = 0; j < dayworker; j++)	//하루 근무자 수 만큼 반복
				for (auto i = cur_Shift.begin(); i < cur_Shift.end(); i++)	//cur_Shift의 처음부터 끝까지
					if (i->first == teamList[teamindex].userinfo[j].ID)	//ID를 search해서 맞으면
						i->second = false;
		}

		cout << "근무일 수정이 완료되었습니다.";

		// team 배열에 ID 배열에 있는 근무자에 해당하는 조 이름 넣기
		for (int i = 0; i < DAYMAX; i++)
			if (ID[i].size() != 0)
				for (int j = 0; j < teamList.size(); j++)
					if (teamList[j].userinfo[0].ID == ID[i])
						team[i] = teamList[j].TeamName;

		wfileout(validlist, workingcheck, 1);
		CalenderFileOutput(date, team, &teamList, STATE);
	}

	/***** 완성되면 확정으로 변경 *****/
	int complete = 1;
	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i] == vacant)
		{
			complete = 0;
		}
	}
	if (complete == 1)
	{
		for (int i = 0; i <= lastday; i++) // 근무표가 완성되면 확정으로 변경
		{
			STATE[i] = confirmed;
		}
		isWorking = -1;
	}

	/***** 근무자들의 선택횟수를 비교하여 확정함 *****/
	int cof = 1;
	int cmp = validlist[0].second;
	for (int i = 0; i < validlist.size(); i++)
	{
		if (cmp != validlist[i].second)
		{
			cof = 0;
		}
	}
	if (cof == 1)
	{
		for (int i = 0; i <= lastday; i++) // 모든 근무자의 근무횟수가 같으면 확정으로 변경
		{
			if (STATE[i] == occupied)
			{
				STATE[i] = confirmed;
			}
		}
		/***** 주말근무횟수 정보 최신화 해주고, 근무횟수 +1 해준다 *****/
		pre_Shift = cur_Shift;
		string temp;
		for (auto i = cur_Shift.begin(); i < cur_Shift.end(); i++) {
			if (i->second)
				temp = i->first;
			validlist[Search(&validlist, temp)].second += 1;
		}
	}

	// team 배열에 ID 배열에 있는 근무자에 해당하는 조 이름 넣기
	for (int i = 0; i < DAYMAX; i++)
		if (ID[i].size() != 0)
			for (int j = 0; j < teamList.size(); j++)
				if (teamList[j].userinfo[0].ID == ID[i])
					team[i] = teamList[j].TeamName;

	// 파일 쓰기 ID, STATE 저장
	memberList->FileOutput(isWorking);
	wfileout(validlist, workingcheck, 0);
	CalenderFileOutput(date, team, &teamList, STATE);
}

vector<pair<string, int>> wfileinput()
{
	ifstream inFile;
	inFile.open(WFILE);

	string inputLine = "";
	string tempStr = "";
	string idstr = "";
	vector<pair<string, int>> workingcheck;

	int count = 0;
	int linecount = 0;

	if (inFile.is_open())
	{
		while (getline(inFile, inputLine))
		{
			count = 0;
			inputLine += " ";
			for (int i = 0; i < inputLine.length(); i++)
			{
				if (inputLine[i] != ' ')
				{
					tempStr += inputLine[i];
				}
				else
				{
					switch (count)
					{
					case 0:
					{
						idstr = tempStr;
						tempStr = "";
						break;
					}
					case 1:
					{
						int tempInt = stoi(tempStr);
						tempStr = "";
						workingcheck.push_back(make_pair(idstr, tempInt));
						break;
					}
					default:
						printf("파일 읽기 오류, 저장파일의 문법이 잘못되었습니다.\n");
						exit(1);
					}
					count++;
					if (count > 1)
						break;
				}
			}
		}

	}
	else
	{
		ofstream NewSaveFile(WFILE);
		printf("Workingcheck 저장 파일을 생성하였습니다.\n");
		NewSaveFile.close();
	}
	inFile.close();
	return workingcheck;
}

void wfileout(vector<pair<UserInformation, int>> validlist, vector<pair<string, int>> workingcheck, int info) {

	ofstream outworking;
	outworking.open(WFILE);

	if (info != 0) {
		if (outworking.is_open())
		{
			for (auto iter = workingcheck.begin(); iter != workingcheck.end(); iter++)
			{
				outworking << iter->first << " " << iter->second << endl;
			}

			for (auto iter = validlist.begin(); iter != validlist.end(); iter++)
			{
				if (iter->second == PASS) {
					outworking << iter->first.ID << " " << iter->second << endl;
				}
			}
		}
	}

	outworking.close();
}

void showSchedule()
{
	string temp;
	int date;
	cout << "열람할 근무표의 연월을 입력하십시오 : " << endl;

	//getline(cin, temp);

	char escapeDetect = _getch();
	if (escapeDetect == 27)
	{
		cout << endl;
		return;
	}
	else
	{
		cout << escapeDetect;
		getline(cin, temp);
		temp.insert(0, 1, escapeDetect);
		cout << temp;
	}

	if (!checkDate(temp))
	{
		cout << "날짜를 형식에 맞게 입력하십시오." << endl;
		return;
	}
	date = dateChanger(temp); // 형식 변환 string to int


	// 파일 읽어서 출력하기
	string IDarr[DAYMAX];
	int junk[DAYMAX];
	CalenderFileInput(date, IDarr, &teamList, STATE);

	for (int i = 1; i < DAYMAX; i++)
	{
		if (junk[i])
			calendar->InsertInfo(i, IDarr[i]);
	}

	calendar->PrintCalendar(date / 100, date % 100);
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

bool checkDayint(string str) {
	//이게 불렸다는 건 PASS가 아닌 숫자여야만 함.
	if (str.length() != 1 && str.length() != 2)
	{ //전체 문자열 길이 체크
		return false;
	}

	for (int i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]) == 0)
		{ //숫자가 아님
			return false;
		}
	}
	return true;
}

bool checkDay(int date, int day)
{
	int checkyear = date / 100;
	int checkmon = date % 100;

	int m[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (checkyear % 4 == 0 && checkyear % 100 != checkyear % 400 == 0) {
		m[1] = 29;
	}
	else {
		m[1] = 28;
	}

	if (day > 0 && day <= m[checkmon - 1]) {
		return true;
	}
	else {
		return false;
	}
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

	//의미 규칙 
	int returndate = stoi(str);
	int checkyear = stoi(str.substr(0, 4));

	if (checkyear > 2000) {
		if (abs(2000 - checkyear) > 99 || abs(2000 - checkyear) < 1) return false;
	}
	else {
		if (abs(2000 - checkyear) > 100 || abs(2000 - checkyear) < 0) return false;
	}

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
		if (str[6] == '0' || str[6] == '1' || str[6] == '2')
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

int Search(vector<pair<UserInformation, int>>* validlist, string id) // 탐색 대상 아이디의 인덱스를 반환함.
{
	int index = 0;
	for (auto iter = validlist->begin(); iter != validlist->end(); iter++, index++)
	{
		if (iter->first.ID.compare(id) == 0)
			return index;
	}
	return -1;
}

//input(불러올 달, 달의 근무일정 배열, 팀 리스트 배열, State 배열) output(파일 존재시 true, 새로 생성시 false 출력) *주의 실행시 팀리스트 배열은 초기화되며, 해당 달의 팀으로 재작성됨.
bool CalenderFileInput(int month, string* team, vector<Team>* teamList, int* _STATE)
{
	//해당 달 이름의 파일 열기
	string inputFileName = to_string(month);
	inputFileName.insert(4, "-");
	inputFileName += ".txt";
	ifstream inputFile;
	inputFile.open(inputFileName);

	Calendar cal;
	int lastday = cal.Lastday(month / 100, month % 100);

	string inputLine = "";
	string tempStr = "";
	int count = 0;

	if (inputFile.is_open())
	{
		teamList->clear();
		int count = 0;
		vector<string> tempStr;
		string strBuffer;
		Team tempTeam;
		//TeamList 추출
		while (getline(inputFile, inputLine))
		{
			if (inputLine.compare("-"))
			{
				istringstream iss(inputLine);
				while (getline(iss, strBuffer, ' '))
				{
					tempStr.push_back(strBuffer);
				}
				for (auto iter = tempStr.begin(); iter != tempStr.end(); iter++, count++)
				{
					switch (count)
					{
					case 0:
						tempTeam.TeamName.assign(*iter);
						break;
					case 1:
						tempTeam.userinfo[0].ID.assign(*iter);
						break;
					case 2:
						tempTeam.userinfo[0].startingMonth = stoi(*iter);
						break;
					case 3:
						tempTeam.userinfo[1].ID.assign(*iter);
						break;
					case 4:
						tempTeam.userinfo[1].startingMonth = stoi(*iter);
						break;
					case 5:
						tempTeam.userinfo[2].ID.assign(*iter);
						break;
					case 6:
						tempTeam.userinfo[2].startingMonth = stoi(*iter);
						break;

					default:
						break;
					}
				}
				teamList->push_back(tempTeam);
				count = 0;
				tempStr.clear();
			}
			else
			{
				break;
			}
		}

		//근무일정 추출
		count = 1;
		while (getline(inputFile, inputLine))
		{
			istringstream iss(inputLine);
			while (getline(iss, strBuffer, ' '))
			{
				tempStr.push_back(strBuffer);
			}
			team[count] = tempStr[1];
			_STATE[count] = stoi(tempStr[2]);
			tempStr.clear();
			count++;
		}
	}
	else
	{
		ofstream NewSaveFile(inputFileName);
		printf("새 저장 파일을 생성하였습니다.\n");
		NewSaveFile.close();
		return false;
	}

	inputFile.close();

	return true;
}

void CalenderFileOutput(int month, string* team, vector<Team>* teamList, int* STATE)
{
	string outPutFileName = to_string(month);
	outPutFileName.insert(4, "-");
	outPutFileName += ".txt";
	ofstream outputFile;
	outputFile.open(outPutFileName);

	Calendar cal;
	int lastday = cal.Lastday(month / 100, month % 100);

	if (outputFile.is_open())
	{
		for (auto iter = teamList->begin(); iter != teamList->end(); iter++)
		{
			outputFile << iter->TeamName << " " << iter->userinfo[0].ID << " " << iter->userinfo[0].startingMonth << " " << iter->userinfo[1].ID << " " << iter->userinfo[1].startingMonth << " " << iter->userinfo[2].ID << " " << iter->userinfo[2].startingMonth << endl;
		}
		outputFile << "-" << endl;
		for (int i = 1; i < DAYMAX; i++)
		{
			outputFile << i << " " << team[i] << " " << STATE[i] << endl;
		}
	}
	outputFile.close();
}

vector<pair<string, bool>> weekendInput() {
	ifstream file;
	file.open(WEEKFILE);

	string inLine = "";
	string temp = "";
	string id = "";

	vector<pair<string, bool>> Shift;

	int num = 0;
	int lineNum = 0;

	if (file.is_open()) {	//case : File exist and successfully open
		while (getline(file, inLine)) {
			num = 0;
			inLine += " ";	//파일 데이터를 받아옴. 맨 뒤에 num > 1 경우 만들기! 그래야 break 가능
			for (int i = 0; i < inLine.length(); i++) {
				if (inLine[i] != ' ') {
					temp += inLine[i];
				}
				else {
					switch (num) {
					case 0: {	//id string의 끝
						id = temp;
						temp = "";
						break;	//switch문 종료
					}
					case 1: {	//shift value
						bool shift = stoi(temp);
						temp = "";
						Shift.push_back(make_pair(id, shift));
						break;
					}
					default:
						printf("파일 읽기 오류, 저장 파일의 문법이 잘못되었습니다.\n");
						_exit(1);
					}
					num++;
					if (num > 1) break;	//한 줄 다 읽음
				}
			}
		}
	}
	else {	//case : File is not exist
		ofstream newF;
		newF.open(WEEKFILE);
		printf("weekendCheck.txt 저장 파일을 생성하였습니다.\n");
		newF.close();
	}

	file.close();
	return Shift;
}

void weekendOutput(vector<pair<string, bool>> shift) {
	ofstream file;
	file.open(WEEKFILE);

	if (file.is_open()) {
		for (auto i = shift.begin(); i < shift.end(); i++) {
			file << i->first << " " << i->second << endl;
		}
	}

	file.close();
}
