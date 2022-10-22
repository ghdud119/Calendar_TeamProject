#include <iostream>
#include <string>
#include <vector>
#include "Calendar.h"
#include "MemberList.h"

using namespace std;

const int DAYMAX = 32;
const int IDMAX = 16;
const int DATEMAX = 7;

enum state
{
    vacant = 0,
    occupied,
    confirmed
};

int Search(vector<pair<UserInformation, int>> validlist, string id)
{
    validlist[1].first.ID;
    int index = 0;
    for (int i = 0; i < validlist.size(); i++, index++)
    {
        if (validlist[i].first.ID.compare(id) == 0)
            return index;
    }
    return -1;
}

vector<pair<UserInformation, int>> listPickout(MemberList list, int date)
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

bool isfirst(vector<pair<UserInformation, int>> validlist, string id)
{
    int min = 100;
    for (int i = 0; i < validlist.size(); i++)
    {
        if (validlist[i].second < min)
        {
            min = validlist[i].second;
        }
    }

    if (validlist[Search(validlist, id)].second == min)
    {
        return false;
    }
    else if (validlist[Search(validlist, id)].second > min)
    {
        return true;
    }
}

bool passTest(vector<pair<UserInformation, int>> validlist, string id, int vcount)
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

bool priorityCompare(vector<pair<UserInformation, int>> validlist, string pid, string id)
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
    else if (date <= 31) // from calendar
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

    // 파일 읽기, isNew = ?
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
        date = 0; // from file read
    }

    vector<pair<UserInformation, int>> validlist = listPickout(list, date); // 유효한 사람만 가져옴
    cout << "아이디를 입력하십시오 : ";
    cin >> ID;
    if (Search(validlist, ID) == -1) // condition 2. 유효한 아이디
    {
        cout << "invalid ID" << endl;
        return;
    }

    bool rechoice = isfirst(validlist, ID); // condition 3. 수정 여부

    cout << "희망 근무일을 입력하십시오 : ";
    cin >> input;
    int vcount = 0;
    if (input == "PASS") // condition 4. 패스 테스트
    {
        for (int i = 0; i < DAYMAX; i++)
        {
            if (state[i] == vacant)
            {
                vcount++;
            }
        }
        if (!passTest(validlist, ID, vcount))
        {
            cout << "패스 조건 불만족" << endl;
            return;
        }
        if (rechoice)
        {
            // Retest all post passer
            cout << "패스 완료" << endl;
            validlist[Search(validlist, ID)].second = 999;
            return;
        }
        else
        {
            validlist[Search(validlist, ID)].second = 999;
            cout << "패스 완료" << endl;
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
    validlist[Search(validlist, ID)].second += 1;

    // 확정 갱신
    int cmp = validlist[0].second;
    for (int i = 0; i < validlist.size(); i++)
    {
        if (cmp != validlist[i].second)
        {
            return;
        }
    }
    for (int i = 0; i < DAYMAX; i++)
    {
        if (state[i] == occupied)
        {
            state[i] = confirmed;
        }
    }
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
    // file
}