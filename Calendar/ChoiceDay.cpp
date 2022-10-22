#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Calendar.h"
#include "MemberList.h"
#include "ChoiceFunctions.cpp"

const int DAYMAX = 32;

enum state
{
    vacant = 0,
    occupied,
    confirmed
};

void ChoiceDay(MemberList list)
{
    Calendar* calendar = new Calendar();
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