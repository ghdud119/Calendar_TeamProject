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
string deletedID = "-1";



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

bool ChalenderFileInput(int month, string* ID, int* STATE);
void ChalenderFileOutput(int month, string* ID, int* STATE);

int Search(vector<pair<UserInformation, int>> *validlist, string id);

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
			deletedID = memberList->Delete();

			if (deletedID == "-1")
				cout << "아이디가 유효하지 않습니다.\n"; // 삭제실패
			else
			{
				cout << "현재 근무표에 등록되어 있는 근무자입니다. 삭제하시겠습니까?";
				char answer;
				answer = _getch();
				switch (answer)
				{
				case 'Y':
					for (int i = 1; i < DAYMAX; i++) // 명단에서 삭제된 ID 근무표에서도 삭제
					{
						if (ID[i] == deletedID)
						{
							ID[i] = "";
							STATE[i] = vacant;
						}
					}
					break;
				case 'N':
					return;

				default:
					break;
				}

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
		ChalenderFileInput(date, ID, STATE);
		// 파일 중에 동년 동월의 근무표가 있는지 확인하기
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
	}
	else
	{
		date = stoi(memberList->GetWorkingCalender());
		isWorking = date;
		ChalenderFileInput(date, ID, STATE);
		Calendar cal;
		lastday = cal.Lastday(date / 100, date % 100);
	}


	/***** 근무표 출력 *****/

	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i])
			calendar->InsertInfo(i, ID[i]);
	}

	calendar->PrintCalendar(date / 100, date % 100);

	/***** 명단에서 근무 투입이 가능한 인원만 새로운 배열에 저장 *****/
	vector<pair<UserInformation, int>> validlist;
	vector<UserInformation>* tmpv = memberList->GetMemberList();
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

	// 파일을 불러온 경우 근무 횟수 변경함
	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i] != vacant)
		{
			validlist[Search(&validlist, ID[i])].second += 1;
		}
	}

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
			for (int i = 0; i < validlist.size(); i++)
			{
				if (validlist[i].second == PASS)
				{
					tcount = 0;
					vcount = 0;
					target = validlist[i];

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
						cout << validlist[i].first.ID << "근무자는 근무일을 다시 선택해야 합니다. - 패스 조건 불만족" << endl;
						validlist[Search(&validlist, id)].second = postnum; // 근무투입횟수를 줄인다.
					}
				}
			}
			memberList->FileOutput(isWorking);
			ChalenderFileOutput(date, ID, STATE);
			return;
		}
		/***** 패스 조건을 만족한 경우 *****/
		else
		{
			validlist[Search(&validlist, id)].second = PASS;
			cout << "패스가 완료되었습니다." << endl;
			memberList->FileOutput(isWorking);
			ChalenderFileOutput(date, ID, STATE);
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
		STATE[hopeday] = occupied;
		ID[hopeday] = id;
	}
	/***** 수정이 아닌 경우 선택한 날짜를 바로 반영함 *****/
	else
	{
		STATE[hopeday] = occupied;
		ID[hopeday] = id;
		cout << "근무일 수정이 완료되었습니다.";
		validlist[Search(&validlist, id)].second += 1; // 사용자 근무횟수 추가
		ChalenderFileOutput(date, ID, STATE);
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
	}
	
	// 파일 쓰기 ID, STATE 저장
	memberList->FileOutput(isWorking);
	ChalenderFileOutput(date, ID, STATE);
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
	ChalenderFileInput(date, IDarr, junk);

	for (int i = 1; i < DAYMAX; i++)
	{
		if(junk[i])
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

bool ChalenderFileInput(int month, string* _ID, int* _STATE)
{
	string inputFileName = to_string(month);
	inputFileName.insert(4, "-");
	inputFileName += ".txt";
	ifstream inputFile;
	inputFile.open(inputFileName);

	Calendar cal;
	int lastday = cal.Lastday(month / 100, month % 100);

	string tempID[DAYMAX] = { "" };
	int tempState[DAYMAX] = { 0 };


	string inputLine = "";
	string tempStr = "";

	int dayCount = 0;
	int count = 0;

	if (inputFile.is_open())
	{
		while (getline(inputFile, inputLine))
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
						dayCount = stoi(tempStr);
						if (dayCount > 32)
						{
							printf("파일 읽기 오류, 저장파일의 문법이 잘못되었습니다.\n");
							return false;
						}
						tempStr = "";
					}
					case 1:
					{
						tempID[dayCount] = tempStr;
						tempStr = "";
						break;
					}
					case 2:
					{
						if (stoi(tempStr) > 2 || stoi(tempStr) < 0)
						{
							printf("파일 읽기 오류, 저장파일의 문법이 잘못되었습니다.\n");
							return false;
						}
						tempState[dayCount] = stoi(tempStr);
						tempStr = "";
						break;
					}
					default:
						printf("파일 읽기 오류, 저장파일의 문법이 잘못되었습니다.\n");
						return false;
					}
					count++;
					if (count > 2)
						break;
				}
			}
		}
		for (int i = 1; i <= lastday; i++)
		{
			_ID[i] = tempID[i];
			_STATE[i] = tempState[i];
		}
	}
	else
	{
		ofstream NewSaveFile(inputFileName);
		printf("새 저장 파일을 생성하였습니다.\n");
		NewSaveFile.close();
	}
	inputFile.close();

	return month;
}

void ChalenderFileOutput(int month, string* ID, int* STATE)
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
		for (int i = 1; i <= lastday; i++)
		{
			outputFile << i << " " << ID[i] << " " << STATE[i] << endl;
		}
	}
	outputFile.close();
}