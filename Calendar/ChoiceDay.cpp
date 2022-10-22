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
        return true; // ���� �� ����
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
    if (str.length() != 7) { //��ü ���ڿ� ���� üũ
        return false;
    }

    for (int i = 0; i < str.length(); i++) { //����(0~9)�� ������ üũ
        if (isdigit(str[i]) == 0) { //���ڰ� �ƴ�
            if (i != 4) { //������ �ڸ��� �ƴ� ���� ���ڰ� �ƴ� �� ���� ���
                return false;
            }
        }
        else {
            if (i == 4) { //������ �ڸ��� ���ڰ� �ִ� ���
                return false;
            }
        }
    }

    //�ǹ� ��Ģ - �޸� üũ�ϸ� ��. 5 -> 0�̸� �ڿ� 0�� �ƴϸ� �� / 5->1�̸� �ڿ��� 1�ƴϸ� 2���߸�.
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