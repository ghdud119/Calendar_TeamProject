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

        cout << "���θ޴� �� �Է� ������Ʈ\n";
        cout << "1. �ٹ�ǥ ����\n";
        cout << "2. ��� ����\n";
        cout << "ESC. ���� �� ����\n";

        selectmenu = _getch();

        switch (selectmenu)
        {
        case 49: // 1
            calendarMenu();
            break;
        case 50: // 2
            listMenu();
            break;
        case 27: // ESC Ű
            status = false;
            break;
        default:
            cout << selectmenu << " �Է�.\n";
            cout << "�޴��� �����ϴ� �� �ڸ� ���ڸ��� �Է��Ͻʽÿ�.\n";
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

        cout << "���θ޴� �� �Է� ������Ʈ\n";
        cout << "1. �ٹ�ǥ ����\n";
        cout << "2. �ٹ��� ����\n";
        cout << "ESC. ���� �� ����\n";

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
        case 27: // ESC Ű
            status = false;
            break;
        default:
            cout << selectmenu << " �Է�.\n";
            cout << "�޴��� �����ϴ� �� �ڸ� ���ڸ��� �Է��Ͻʽÿ�.\n";
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

        cout << "���θ޴� �� �Է� ������Ʈ\n";
        cout << "1. ��� ����\n";
        cout << "2. ��� ���\n";
        cout << "3. ��� ����\n";
        cout << "ESC. ���� �� ����\n";

        selectmenu = _getch();

        switch (selectmenu)
        {
        case 49: // 1
            memberList->PrintList();
            break;
        case 50:                 // 2
            if (isWorking == -1) // �ۼ� ���� �ٹ�ǥ �ִ��� ����
            {
                cout << "�ۼ� ���� �ٹ�ǥ�� �ϼ��Ǳ� ������ ��� ����� �� �� �����ϴ�." << endl;
            }
            memberList->Insert();
            break;
        case 51: // 3
            memberList->Delete();
            break;
        case 27: // ESC Ű
            status = false;
            break;
        default:
            cout << selectmenu << " �Է�.\n";
            cout << "�޴��� �����ϴ� �� �ڸ� ���ڸ��� �Է��Ͻʽÿ�.\n";
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

    // ���� �б�, isNew ���� �����ϱ�, date ���� �����ϱ�

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
        date = 0; // date ���� ������ ���⼭!!
    }

    vector<pair<UserInformation, int>> validlist = listPickout(list, date); // ��ȹ�� ����!!!!!

    if (validlist.size() <= 1)
    {
        cout << "�ٹ�ǥ�� �ۼ��ϱ⿡ �ο��� ������� �ʽ��ϴ�." << endl;
    }

    cout << "���̵� �Է��Ͻʽÿ� : ";
    cin >> ID;
    if (Search(validlist, ID) == -1) // condition 2. ��ȿ�� ���̵�
    {
        cout << "���̵� ��ȿ���� �ʽ��ϴ�." << endl;
        return;
    }

    bool rechoice = isfirst(validlist, ID); // condition 3. ���� ����

    cout << "��� �ٹ����� �Է��Ͻʽÿ� : ";
    cin >> input;
    if (input == "PASS") // condition 4. �н� �׽�Ʈ
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
            cout << "�н� ������ �������� �ʽ��ϴ�." << endl;
            return;
        }

        if (rechoice)
        {
            cout << "�н��� �Ϸ�Ǿ����ϴ�." << endl;
            int temp = validlist[Search(validlist, ID)].second;
            validlist[Search(validlist, ID)].second = PASS;

            for (int i = 0; i < validlist.size(); i++)
            {
                if (validlist[i].second == PASS)
                {
                    if (!passTest(validlist, validlist[i].first.ID, vcount))
                    {
                        cout << validlist[i].first.ID << "���� �ٹ����� �缱���ؾ��մϴ�. (�н� ���� �Ҹ���)" << endl;
                        validlist[Search(validlist, ID)].second = temp;
                    }
                }
            }
            return;
        }
        else
        {
            validlist[Search(validlist, ID)].second = PASS;
            cout << "�н��� �Ϸ�Ǿ����ϴ�." << endl;
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
        else
        {
            validlist[Search(validlist, postID)].second -= 1; // ������ �ٹ�Ƚ�� ����
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
    validlist[Search(validlist, ID)].second += 1; // ����� �ٹ�Ƚ�� �߰�

    // Ȯ�� ����
    int cmp = validlist[0].second;
    for (int i = 0; i < validlist.size(); i++)
    {
        if (cmp != validlist[i].second)
        {
            return;
        }
    }
    for (int i = 0; i < DAYMAX; i++) // ��� �ٹ����� �ٹ�Ƚ���� ������ Ȯ������ ����
    {
        if (state[i] == occupied)
        {
            state[i] = confirmed;
        }
    }

    // ���� ����
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

    // ���� �о ����ϱ�
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
    else if (date <= 31) // ���� �ʿ�
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

vector<pair<UserInformation, int>> listPickout(MemberList list, int date) // �ٹ� ������ ������ �ο��� �߷���.
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

int Search(vector<pair<UserInformation, int>> validlist, string id) // Ž�� ��� ���̵��� �ε����� ��ȯ��.
{
    int index = 0;
    for (int i = 0; i < validlist.size(); i++, index++)
    {
        if (validlist[i].first.ID.compare(id) == 0)
            return index;
    }
    return -1;
}

bool isfirst(vector<pair<UserInformation, int>> validlist, string id) // �ٹ��ڰ� �ٹ��� �����ϴ� ������, ó�� �Է��ϴ� ������ Ȯ����.
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

bool passTest(vector<pair<UserInformation, int>> validlist, string id, int vcount) // �ٹ��ڰ� �н� ������ �����ϴ��� Ȯ����.
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

bool priorityCompare(vector<pair<UserInformation, int>> validlist, string pid, string id) // ��Ż�� �������� Ȯ����.
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