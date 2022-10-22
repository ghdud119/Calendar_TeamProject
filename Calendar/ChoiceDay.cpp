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

    // ���� �б�, isNew = ?
    if (isNew) // condition 1. �ۼ� �� ����
    {
        cout << "������ �Է��Ͻʽÿ� : ";
        getline(cin, temp); //���� �Է� �����ؾ���.


        if (checkDate(temp))
        {
            cout << "��¥�� ���Ŀ� �°� �Է��Ͻʽÿ�." << endl;
            return;
        }
        date = dateChanger(temp); // ���� ��ȯ string to int
    }
    else
    {
        date = 0; // from file read
    }

    vector<pair<UserInformation, int>> validlist = listPickout(list, date); // ��ȿ�� ����� ������
    cout << "���̵� �Է��Ͻʽÿ� : ";
    cin >> ID;
    if (Search(validlist, ID) == -1) // condition 2. ��ȿ�� ���̵�
    {
        cout << "invalid ID" << endl;
        return;
    }

    bool rechoice = isfirst(validlist, ID); // condition 3. ���� ����

    cout << "��� �ٹ����� �Է��Ͻʽÿ� : ";
    cin >> input;
    int vcount = 0;
    if (input == "PASS") // condition 4. �н� �׽�Ʈ
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
            cout << "�н� ���� �Ҹ���" << endl;
            return;
        }
        if (rechoice)
        {
            // Retest all post passer
            cout << "�н� �Ϸ�" << endl;
            validlist[Search(validlist, ID)].second = 999;
            return;
        }
        else
        {
            validlist[Search(validlist, ID)].second = 999;
            cout << "�н� �Ϸ�" << endl;
        }
    }

    int hopeday = stoi(input);
    if (!checkDay(hopeday)) // condition 5. �Է��� ��ȿ��
    {
        cout << "��ȿ���� ���� �Է��Դϴ�." << endl;
        return;
    }

    if (state[hopeday] == confirmed) // condition 5. ��Ȯ�� ��¥
    {
        cout << "Ȯ���� ��¥�Դϴ�." << endl;
        return;
    }

    if (state[hopeday] == occupied) // condition 6. �켱���� ��
    {
        string postID = id[hopeday];
        if (!priorityCompare(validlist, postID, ID))
        {
            cout << "�켱 ������ ���Ƽ� ��Ż�� �� �����ϴ�." << endl;
            return;
        }
    }

    if (rechoice)
    {
        // ���� ���� ����
        for (int i = 0; i < DAYMAX; i++)
        {
            if (id[i] == ID && state[i] == occupied)
            {
                state[i] = vacant;
            }
        }
        cout << "���� �Ϸ�" << endl;
        state[hopeday] = occupied;
        id[hopeday] = ID;
        return;
    }
    state[hopeday] = occupied;
    id[hopeday] = ID;
    cout << "��� �Ϸ�";
    validlist[Search(validlist, ID)].second += 1;

    // Ȯ�� ����
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
    cout << "������ �Է��Ͻʽÿ� : " << endl;
    getline(cin, temp);


    if (checkDate(temp))
    {
        cout << "��¥�� ���Ŀ� �°� �Է��Ͻʽÿ�." << endl;
        return;
    }
    date = dateChanger(temp); // ���� ��ȯ string to int
    // file
}