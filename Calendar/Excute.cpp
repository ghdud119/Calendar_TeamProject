#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "Calendar.h"
#include "MemberList.h"

using namespace std;

Calendar* calendar = new Calendar();
MemberList* memberList = new MemberList();
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

void mainMenu();
void calendarMenu();
void listMenu();
void ChoiceDay(MemberList list);
void showSchedule();

bool checkID(string str);
int dateChanger(string str);
bool checkDay(int date);
bool checkDate(string str);

vector<pair<UserInformation, int>> listPickout(MemberList list, int date);
int Search(vector<pair<UserInformation, int>> validlist, string id);
bool isfirst(vector<pair<UserInformation, int>> validlist, string id);
bool passTest(vector<pair<UserInformation, int>> validlist, string id, int vcount);
bool priorityCompare(vector<pair<UserInformation, int>> validlist, string pid, string id);


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
            if (memberList->GetMemberList())
                ChoiceDay(*memberList);
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
        case 50:                 // 2
            if (isWorking == -1) // 작성 중인 근무표 있는지 변수
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

void ChoiceDay(MemberList list)
{
    bool isNew = false;
    string temp = 0;
    string ID = nullptr;
    string input = 0;
    string id[DAYMAX];
    int state[DAYMAX];
    int date;

    state[0] = confirmed;
    for (int i = 1; i < DAYMAX; i++)
    {
        state[i] = vacant;
    }

    // 파일 읽기, isNew 변수 수정하기, date 변수 수정하기

    if (isNew) // condition 1. 작성 중 여부
    {
        cout << "연월을 입력하십시오 : ";
        getline(cin, temp); //공백 입력 가능해야함.


        if (checkDate(temp))
        {
            cout << "날짜를 형식에 맞게 입력하십시오." << endl;
            return;
        }
        date = dateChanger(temp); // 형식 변환 string to int
    }
    else
    {
        date = 0; // date 변수 수정은 여기서!!
    }

    vector<pair<UserInformation, int>> validlist = listPickout(list, date); // 기획서 수정!!!!!

    if (validlist.size() <= 1)
    {
        cout << "근무표를 작성하기에 인원이 충분하지 않습니다." << endl;
    }

    cout << "아이디를 입력하십시오 : ";
    cin >> ID;
    if (Search(validlist, ID) == -1) // condition 2. 유효한 아이디
    {
        cout << "아이디가 유효하지 않습니다." << endl;
        return;
    }

    bool rechoice = isfirst(validlist, ID); // condition 3. 수정 여부

    cout << "희망 근무일을 입력하십시오 : ";
    cin >> input;
    if (input == "PASS") // condition 4. 패스 테스트
    {
        int vcount = 0;
        for (int i = 0; i < DAYMAX; i++)
        {
            if (state[i] == vacant)
            {
                vcount++;
            }
        }
        if (!passTest(validlist, ID, vcount))
        {
            cout << "패스 조건을 만족하지 않습니다." << endl;
            return;
        }

        if (rechoice)
        {
            cout << "패스가 완료되었습니다." << endl;
            int temp = validlist[Search(validlist, ID)].second;
            validlist[Search(validlist, ID)].second = PASS;

            for (int i = 0; i < validlist.size(); i++)
            {
                if (validlist[i].second == PASS)
                {
                    if (!passTest(validlist, validlist[i].first.ID, vcount))
                    {
                        cout << validlist[i].first.ID << "님이 근무일을 재선택해야합니다. (패스 조건 불만족)" << endl;
                        validlist[Search(validlist, ID)].second = temp;
                    }
                }
            }
            return;
        }
        else
        {
            validlist[Search(validlist, ID)].second = PASS;
            cout << "패스가 완료되었습니다." << endl;
        }
    }

    int hopeday = stoi(input);
    if (!checkDay(hopeday)) // condition 5. 입력의 유효성
    {
        cout << "유효하지 않은 입력입니다." << endl;
        return;
    }

    if (state[hopeday] == confirmed) // condition 5. 미확정 날짜
    {
        cout << "확정된 날짜입니다." << endl;
        return;
    }

    if (state[hopeday] == occupied) // condition 6. 우선순위 비교
    {
        string postID = id[hopeday];
        if (!priorityCompare(validlist, postID, ID))
        {
            cout << "우선 순위가 낮아서 강탈할 수 없습니다." << endl;
            return;
        }
        else
        {
            validlist[Search(validlist, postID)].second -= 1; // 점유자 근무횟수 감소
        }
    }

    if (rechoice)
    {
        // 이전 선택 삭제
        for (int i = 0; i < DAYMAX; i++)
        {
            if (id[i] == ID && state[i] == occupied)
            {
                state[i] = vacant;
            }
        }
        cout << "수정 완료" << endl;
        state[hopeday] = occupied;
        id[hopeday] = ID;
        return;
    }

    state[hopeday] = occupied;
    id[hopeday] = ID;
    cout << "등록 완료";
    validlist[Search(validlist, ID)].second += 1; // 사용자 근무횟수 추가

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
        if (state[i] == occupied)
        {
            state[i] = confirmed;
        }
    }

    // 파일 쓰기
}

void showSchedule()
{
    string temp;
    int date;
    cout << "연월을 입력하십시오 : " << endl;
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
    if (str.length() != 7) { //전체 문자열 길이 체크
        return false;
    }

    for (int i = 0; i < str.length(); i++) { //숫자(0~9)와 구분자 체크
        if (isdigit(str[i]) == 0) { //숫자가 아님
            if (i != 4) { //구분자 자리가 아닌 곳에 숫자가 아닌 게 있을 경우
                return false;
            }
        }
        else {
            if (i == 4) { //구분자 자리에 숫자가 있는 경우
                return false;
            }
        }
    }

    //의미 규칙 - 달만 체크하면 됨. 5 -> 0이면 뒤에 0만 아니면 됨 / 5->1이면 뒤에가 1아니면 2여야만.
    int returndate = stoi(str);
    if (str[5] == '0') {
        if (str[6] == '0') {
            return false;
        }
        else {
            return true;

        }
    }
    else if (str[5] == '1') {
        if (str[6] == '1' || str[6] == '2') {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

    //return false;
}

vector<pair<UserInformation, int>> listPickout(MemberList list, int date) // 근무 투입이 가능한 인원만 추려냄.
{
    vector<pair<UserInformation, int>> validlist;
    vector<UserInformation>* temp = list.GetMemberList();
    for (auto iter = temp->begin(); iter != temp->end(); iter++)
    {
        if (stoi(iter->startingMonth) < date)
        {
            validlist.push_back(make_pair(*iter, 0));
        }
    }

    return validlist;
}

int Search(vector<pair<UserInformation, int>> validlist, string id) // 탐색 대상 아이디의 인덱스를 반환함.
{
    int index = 0;
    for (int i = 0; i < validlist.size(); i++, index++)
    {
        if (validlist[i].first.ID.compare(id) == 0)
            return index;
    }
    return -1;
}

bool isfirst(vector<pair<UserInformation, int>> validlist, string id) // 근무자가 근무를 수정하는 것인지, 처음 입력하는 것인지 확인함.
{
    int min = 100;
    int max = 0;
    for (int i = 0; i < validlist.size(); i++)
    {
        if (validlist[i].second < min)
        {
            min = validlist[i].second;
        }
        if (validlist[i].second > max)
        {
            max = validlist[i].second;
        }
    }

    if (min == max)
    {
        return true;
    }
    else if (validlist[Search(validlist, id)].second == min)
    {
        return false;
    }
    else if (validlist[Search(validlist, id)].second > min)
    {
        return true;
    }
}

bool passTest(vector<pair<UserInformation, int>> validlist, string id, int vcount) // 근무자가 패스 조건을 만족하는지 확인함.
{
    pair<UserInformation, int> target;
    int tcount = 0;
    for (int i = 0; i < validlist.size(); i++)
    {
        if (validlist[i].first.ID == id)
        {
            target = validlist[i];
        }
    }
    for (int i = 0; i < validlist.size(); i++)
    {
        if (target.first.startingMonth > validlist[i].first.startingMonth)
        {
            tcount++;
        }
    }
    if (tcount >= vcount)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool priorityCompare(vector<pair<UserInformation, int>> validlist, string pid, string id) // 강탈이 가능한지 확인함.
{
    if (validlist[Search(validlist, pid)].first.startingMonth >=
        validlist[Search(validlist, id)].first.startingMonth)
    {
        return false;
    }
    else
    {
        return true; // 뺏을 수 있음
    }
}