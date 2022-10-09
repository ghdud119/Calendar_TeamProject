#include <iostream>
#include <string>
#include <vector>
#include "Calendar.h"
#include "MemberList.h"
#include "Valid.cpp"

void ChoiceDay(MemberList list)
{
    Calendar *calendar = new Calendar();
    bool isNew = false;
    string temp = 0;
    string ID = nullptr;
    string input = 0;
    string name[31];
    string state[31];
    int date;

    // 파일 읽기, isNew = ?
    if (isNew) // condition 1. 작성 중 여부
    {
        cout << "연월을 입력하십시오 : ";
        cin >> temp;
        date = dateChanger(temp); // 형식 변환 string to int
        if (!checkDate(date))
        {
            cout << "날짜 입력 형식 오류";
            return;
        }
    }
    else
    {
        date = // from file read
    }

    vector<pair<UserInfomation, int>> validlist = listPickout(list, date); // 유효한 사람만 가져옴
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
    if (input == "PASS") // condition 4. 패스 테스트
    {
        if (!passTest(validlist, ID))
        {
            cout << "패스 조건 불만족";
            return;
        }
        if (rechoice)
        {
            // Retest all post passer
            cout << "패스 완료";
            validlist[Search(validlist, ID)].second = 999;
            return;
        }
        else
        {
            cout << "패스 완료";
        }
    }

    int hopeday = stoi(input);
    if (!checkDay(hopeday)) // condition 5. 입력의 유효성
    {
        return;
    }

    if (state[hopeday] == "확정") // condition 5. 미확정 날짜
    {
        cout << "확정된 날짜입니다." << endl;
        return;
    }

    if (state[hopeday] == "점유") // condition 6. 우선순위 비교
    {
        string postID = name[hopeday];
        if (!priorityCompare(validlist, postID, ID))
        {
            cout << "우선 순위 낮음";
            return;
        }
    }

    state[hopeday] = "점유";
    name[hopeday] = ID;
    if (rechoice)
    {
        // 이전 선택 삭제
        cout << "수정 완료";
        return;
    }
    cout << "등록 완료";
}