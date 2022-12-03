#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <sstream>
#include "Calendar.h"
#include "MemberList.h"

using namespace std;

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

int STATE[DAYMAX];

/// ì¶”ê°€ ë³€ìˆ˜
int teamindex;
// ì¶”ê°€ ë³€ìˆ˜

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

bool ChalenderFileInput(int month, string* team, vector<Team>* teamList, int* _STATE);
void ChalenderFileOutput(int month, vector<Team>* teamList, string* team, int* STATE);

int Search(vector<pair<UserInformation, int>>* validlist, string id);

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

		cout << "1. ±Ù¹«Ç¥ °ü¸®\n";
		cout << "2. ¸í´Ü °ü¸®\n";
		cout << "ESC. ÀúÀå ¹× Á¾·á\n";

		selectmenu = _getch();

		switch (selectmenu)
		{
		case 49: // 1
			calendarMenu();
			break;
		case 50: // 2
			listMenu();
			break;
		case 27: // ESC Å°
			status = false;
			break;
		default:
			cout << selectmenu << " ÀÔ·Â.\n";
			cout << "¸Ş´º¿¡ Á¸ÀçÇÏ´Â ÇÑ ÀÚ¸® ¼ıÀÚ¸¸À» ÀÔ·ÂÇÏ½Ê½Ã¿À.\n";
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

		cout << "1. ±Ù¹«Ç¥ È®ÀÎ\n";
		cout << "2. ±Ù¹«ÀÏ ¼±ÅÃ\n";
		cout << "ESC. ÀúÀå ¹× Á¾·á\n";

		selectmenu = _getch();

		switch (selectmenu)
		{
		case 49: // 1
			showSchedule();
			break;
		case 50: // 2
			ChoiceDay();
			break;
		case 27: // ESC Å°
			status = false;
			break;
		default:
			cout << selectmenu << " ÀÔ·Â.\n";
			cout << "¸Ş´º¿¡ Á¸ÀçÇÏ´Â ÇÑ ÀÚ¸® ¼ıÀÚ¸¸À» ÀÔ·ÂÇÏ½Ê½Ã¿À.\n";
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

		cout << "¸ŞÀÎ¸Ş´º ¹× ÀÔ·Â ÇÁ·ÒÇÁÆ®\n";
		cout << "1. ¸í´Ü º¸±â\n";
		cout << "2. ¸í´Ü µî·Ï\n";
		cout << "3. ¸í´Ü »èÁ¦\n";
		cout << "ESC. ÀúÀå ¹× Á¾·á\n";

		selectmenu = _getch();

		switch (selectmenu)
		{
		case 49: // 1
			memberList->PrintList();
			break;
		case 50:				 // 2
			if (isWorking != -1) // ÀÛ¼º ÁßÀÎ ±Ù¹«Ç¥ ÀÖ´ÂÁö º¯¼ö
			{
				cout << "ÀÛ¼º ÁßÀÎ ±Ù¹«Ç¥°¡ ¿Ï¼ºµÇ±â Àü±îÁö ¸í´Ü µî·ÏÀ» ÇÒ ¼ö ¾ø½À´Ï´Ù." << endl;
				return;
			}
			memberList->Insert();
			break;
		case 51: // 3
			deletedID = memberList->Delete();

			if (deletedID == "-1")
				cout << "¾ÆÀÌµğ°¡ À¯È¿ÇÏÁö ¾Ê½À´Ï´Ù.\n"; // »èÁ¦½ÇÆĞ
			else
			{
				cout << "ÇöÀç ±Ù¹«Ç¥¿¡ µî·ÏµÇ¾î ÀÖ´Â ±Ù¹«ÀÚÀÔ´Ï´Ù. »èÁ¦ÇÏ½Ã°Ú½À´Ï±î?";
				char answer;
				answer = _getch();
				switch (answer)
				{
				case 'Y':
					for (int i = 1; i < DAYMAX; i++) // ¸í´Ü¿¡¼­ »èÁ¦µÈ ID ±Ù¹«Ç¥¿¡¼­µµ »èÁ¦
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
		case 27: // ESC Å°
			status = false;
			break;
		default:
			cout << selectmenu << " ÀÔ·Â.\n";
			cout << "¸Ş´º¿¡ Á¸ÀçÇÏ´Â ÇÑ ÀÚ¸® ¼ıÀÚ¸¸À» ÀÔ·ÂÇÏ½Ê½Ã¿À.\n";
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

	/***** ÀÛ¼º ÁßÀÎ ±Ù¹«Ç¥°¡ ÀÖ´ÂÁö È®ÀÎ *****/
	if (date == -1)
	{
		for (int i = 0; i < DAYMAX; i++)
		{
			ID[i] = "";
			STATE[i] = vacant;
		}

		cout << "±Ù¹«Ç¥ ÀÛ¼ºÀ» ½ÃÀÛÇÕ´Ï´Ù. ±Ù¹«Ç¥¸¦ ÀÛ¼ºÇÒ ¿¬¿ùÀ» ÀÔ·ÂÇÏ½Ê½Ã¿À. ÀÔ·Â : ";

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

		/***** ±ÔÄ¢ - ¿À·ù(p.19) ±Ù¹«ÀÏ ¼±ÅÃÀÌ ºÒ°¡´ÉÇÑ °æ¿ì *****/
		if (!checkDate(temp))
		{
			cout << "³¯Â¥¸¦ Çü½Ä¿¡ ¸Â°Ô ÀÔ·ÂÇÏ½Ê½Ã¿À." << endl;
			return;
		}
		date = dateChanger(temp); // Çü½Ä º¯È¯ string to int
		Month = date;
		//ChalenderFileInput(date, ID, STATE);
		// ÆÄÀÏ Áß¿¡ µ¿³â µ¿¿ùÀÇ ±Ù¹«Ç¥°¡ ÀÖ´ÂÁö È®ÀÎÇÏ±â
		int con_check = 0;
		Calendar cal;
		for (int i = 0; i < cal.Lastday(date / 100, date % 100); i++) {
			if (STATE[i] == 2)
				con_check++;
		}
		if (con_check == cal.Lastday(date / 100, date % 100)) {
			cout << "µ¿³â µ¿¿ùÀÇ ±Ù¹«Ç¥°¡ Á¸ÀçÇÕ´Ï´Ù." << endl;
			return;
		}
		lastday = cal.Lastday(date / 100, date % 100);
		isWorking = date;
	}
	else
	{
		date = stoi(memberList->GetWorkingCalender());
		isWorking = date;
		//ChalenderFileInput(date, ID, STATE);
		Calendar cal;
		lastday = cal.Lastday(date / 100, date % 100);
	}

	// ì¶”ê°€ë³€ìˆ˜
	int dayworker;
	int totalworkers;

<<<<<<< Updated upstream
	/***** ±Ù¹«Ç¥ Ãâ·Â *****/
=======
	// 1. ëª‡ ëª…ì´ ì¡°ë¥¼ ë§ºì„ì§€ ì…ë ¥ ë°›ëŠ” ë¶€ë¶„
	cout << "ì¼ì¼ê·¼ë¬´ì¸ì›ì„ ì…ë ¥í•˜ì‹­ì‹œì˜¤. ì…ë ¥ : " << endl;
	cin >> dayworker;
>>>>>>> Stashed changes

	if (dayworker > 3 || dayworker < 1)
	{
		cout << "1ë¶€í„° 3 ì‚¬ì´ì˜ ì •ìˆ˜ ê°’ì„ ì…ë ¥í•´ì£¼ì‹­ì‹œì˜¤." << endl;
		return;
	}

<<<<<<< Updated upstream
	calendar->PrintCalendar(date / 100, date % 100);

	/***** ¸í´Ü¿¡¼­ ±Ù¹« ÅõÀÔÀÌ °¡´ÉÇÑ ÀÎ¿ø¸¸ »õ·Î¿î ¹è¿­¿¡ ÀúÀå *****/
=======
	/***** ëª…ë‹¨ì—ì„œ ê·¼ë¬´ íˆ¬ì…ì´ ê°€ëŠ¥í•œ ì¸ì›ë§Œ ìƒˆë¡œìš´ ë°°ì—´ì— ì €ì¥ *****/
>>>>>>> Stashed changes
	vector<pair<UserInformation, int>> validlist;
	vector<UserInformation>* tmpv = memberList->GetMemberList();
	int index = 0;
	for (auto iter = tmpv->begin(); iter != tmpv->end(); iter++, index++)
	{
		if (iter->startingMonth < date)
			validlist.push_back(make_pair(*iter, 0));
	}

	/***** ±ÔÄ¢ - ¿À·ù(p.19) ±Ù¹« ÅõÀÔÀÌ °¡´ÉÇÑ »ç¶÷ÀÌ 1¸í ÀÌÇÏÀÎ °æ¿ì *****/
	if (validlist.size() <= 1) // ±âÈ¹¼­ ¼öÁ¤!!!!!
	{
		cout << "À¯È¿±Ù¹«ÀÚ°¡ 1¸í ÀÌÇÏÀÌ¹Ç·Î ±Ù¹«Ç¥ ÀÛ¼ºÀÌ ºÒ°¡ÇÕ´Ï´Ù." << endl;
		isWorking = -1;
		return;
	}

	// ÆÄÀÏÀ» ºÒ·¯¿Â °æ¿ì ±Ù¹« È½¼ö º¯°æÇÔ
	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i] != vacant)
		{
			validlist[Search(&validlist, ID[i])].second += 1;
		}
	}

<<<<<<< Updated upstream
	/***** ¾ÆÀÌµğ ÀÔ·Â ¹Ş±â *****/
	cout << "¾ÆÀÌµğ¸¦ ÀÔ·ÂÇÏ½Ê½Ã¿À. ÀÔ·Â : ";
=======
	// 2. ì…ë ¥ ë°›ì€ ê°’ìœ¼ë¡œ ì¡°ë¥¼ ì§œëŠ” ë¶€ë¶„
	totalworkers = validlist.size();
	int remainder = totalworkers % dayworker;
	
	if (remainder == 0)
	{
		for (int i = 0; i < totalworkers / dayworker; i++)
		{
			teamList[i].TeamName = "1ì¡°"; // ê³ ì³ì•¼í•¨
			
			for (remainder; remainder < (dayworker + remainder); remainder++)
				teamList[i].userinfo[0] = validlist[remainder].first;
		}
	}
	else
	{ 
		for (int i = 0; i < totalworkers / dayworker; i++)
		{
			teamList[i].TeamName = "1ì¡°"; // ê³ ì³ì•¼í•¨

			for (remainder; remainder < (dayworker + remainder); remainder++)
				teamList[i].userinfo[0] = validlist[remainder].first;
		}
	}

	// 3. ì¡° ì¶œë ¥í•˜ëŠ” ë¶€ë¶„
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
	

	/***** ê·¼ë¬´í‘œ ì¶œë ¥ *****/
	for (int i = 1; i <= lastday; i++)
	{
		if (STATE[i])
			calendar->InsertInfo(i, ID[i]);
	}

	calendar->PrintCalendar(date / 100, date % 100);



	/***** ì•„ì´ë”” ì…ë ¥ ë°›ê¸° *****/
	cout << "ì•„ì´ë””ë¥¼ ì…ë ¥í•˜ì‹­ì‹œì˜¤. ì…ë ¥ : ";
>>>>>>> Stashed changes
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

	/***** ±ÔÄ¢ - ¿À·ù(p.19) ±Ù¹«ÀÏ ¼±ÅÃÀÌ ºÒ°¡´ÉÇÑ °æ¿ì *****/
	if (memberList->Search(id) != -1 && Search(&validlist, id) == -1)
	{
		cout << id << "±Ù¹«ÀÚ´Â ±Ù¹«ÀÚ ¿ä°ÇÀ» ¸¸Á·ÇÏÁö ¾Ê½À´Ï´Ù." << endl;
		return;
	}
	/***** ÀÔ·Â - ¿À·ù(p.18) ¸í´Ü¿¡ ¾ø´Â ¾ÆÀÌµğ¸¦ ÀÔ·ÂÇÑ °æ¿ì *****/
	else if (Search(&validlist, id) == -1)
	{
		cout << "¾ÆÀÌµğ°¡ À¯È¿ÇÏÁö ¾Ê½À´Ï´Ù." << endl;
		return;
	}
	// ÀÌÇÏ Search´Â ¹İµå½Ã ¼º°øÇÑ´Ù.


	/***** ÀÔ·Â¹ŞÀº ±Ù¹«ÀÚ°¡ ¼öÁ¤ÇÏ´Â °ÍÀÎÁö È®ÀÎ *****/
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
	/***** ±ÔÄ¢ - °æ°í(p.20) ¼öÁ¤ÀÎ °æ¿ì È®ÀÎ ¸Ş½ÃÁö *****/
	if (rechoice)
	{
		cout << "¾ÆÁ÷ ´Ù¸¥ ÀÎ¿øµéÀÌ ±Ù¹«ÀÏÀ» ¼±ÅÃÇÏÁö ¾Ê¾Ò½À´Ï´Ù. ±Ù¹«ÀÏÀ» ¼öÁ¤ÇÏ½Ã°Ú½À´Ï±î?"; //6-2-2
		char ans = _getch();
		cin.clear();

		if (ans == 'Y') {
			cout << "¾ÆÀÌµğ¸¦ ÀÔ·ÂÇÏ½Ê½Ã¿À. ÀÔ·Â : ";
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
			/***** ±ÔÄ¢ - ¿À·ù(p.19) ±Ù¹«ÀÏ ¼±ÅÃÀÌ ºÒ°¡´ÉÇÑ °æ¿ì *****/
			if (memberList->Search(id) != -1 && Search(&validlist, id) == -1)
			{
				cout << id << "±Ù¹«ÀÚ´Â ±Ù¹«ÀÚ ¿ä°ÇÀ» ¸¸Á·ÇÏÁö ¾Ê½À´Ï´Ù." << endl;
				return;
			}
			/***** ÀÔ·Â - ¿À·ù(p.18) ¸í´Ü¿¡ ¾ø´Â ¾ÆÀÌµğ¸¦ ÀÔ·ÂÇÑ °æ¿ì *****/
			else if (Search(&validlist, id) == -1)
			{
				cout << "¾ÆÀÌµğ°¡ À¯È¿ÇÏÁö ¾Ê½À´Ï´Ù." << endl;
				return;
			}
		}
		else if (ans == 'N') {
			return;
		}
		else {
			cout << "Y ¶Ç´Â N¸¸À» ÀÔ·ÂÇÏ½Ê½Ã¿À." << endl;
			return;
		}
		// Y or N ÀÔ·Â¹Ş±â, À¯È¿¼º °Ë»çÇÏ±â, NÀÌ¸é returnÇÏ±â
	}

	/***** ³¯Â¥ ÀÔ·Â¹Ş±â(PASS °¡´É) *****/
	cout << "Èñ¸Á ±Ù¹«ÀÏÀ» ÀÔ·ÂÇÏ½Ê½Ã¿À. ÀÔ·Â : ";
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
	/***** PASS¸¦ ÀÔ·ÂÇÑ °æ¿ì ÆĞ½º Å×½ºÆ® *****/
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
		/***** ÆĞ½º Á¶°ÇÀ» ºÒ¸¸Á·ÇÑ °æ¿ì *****/
		if (tcount < vcount)
		{
			cout << "ÆĞ½º Á¶°ÇÀ» ¸¸Á·ÇÏÁö ¾Ê½À´Ï´Ù." << endl;
			return;
		}
		/***** ÆĞ½º Á¶°ÇÀ» ¸¸Á·ÇßÀ¸¸ç ¼öÁ¤ÇÏ´Â °æ¿ì *****/
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

			cout << "ÆĞ½º°¡ ¿Ï·áµÇ¾ú½À´Ï´Ù." << endl;
			int postnum = validlist[Search(&validlist, id)].second;
			validlist[Search(&validlist, id)].second = PASS;

			/***** ÀÌÀü¿¡ ÆĞ½ºÇÑ ±Ù¹«ÀÚµéÀÇ Á¶°ÇÀ» ´Ù½Ã °Ë»çÇÔ *****/
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
						cout << validlist[i].first.ID << "±Ù¹«ÀÚ´Â ±Ù¹«ÀÏÀ» ´Ù½Ã ¼±ÅÃÇØ¾ß ÇÕ´Ï´Ù. - ÆĞ½º Á¶°Ç ºÒ¸¸Á·" << endl;
						validlist[Search(&validlist, id)].second = postnum; // ±Ù¹«ÅõÀÔÈ½¼ö¸¦ ÁÙÀÎ´Ù.
					}
				}
			}
			memberList->FileOutput(isWorking);
			//ChalenderFileOutput(date, ID, STATE);
			return;
		}
		/***** ÆĞ½º Á¶°ÇÀ» ¸¸Á·ÇÑ °æ¿ì *****/
		else
		{
			validlist[Search(&validlist, id)].second = PASS;
			cout << "ÆĞ½º°¡ ¿Ï·áµÇ¾ú½À´Ï´Ù." << endl;
			memberList->FileOutput(isWorking);
			//ChalenderFileOutput(date, ID, STATE);
			return;
		}
	}
	cin.clear();

	/***** ³¯Â¥¸¦ ÀÔ·ÂÇÏ´Â °æ¿ì *****/
	if (!checkDayint(input)) //¼ıÀÚ°¡ ¾Æ´Ñ ¾Öµé °Å¸£±â
	{
		cout << "³¯Â¥¸¦ Çü½Ä¿¡ ¸Â°Ô ÀÔ·ÂÇÏ½Ê½Ã¿À." << endl;
		return;
	}
	int hopeday = stoi(input);

	if (!checkDay(date, hopeday))
	{
		cout << "³¯Â¥¸¦ Çü½Ä¿¡ ¸Â°Ô ÀÔ·ÂÇÏ½Ê½Ã¿À." << endl;
		return;
	}
	/***** ±ÔÄ¢ - ¿À·ù(p.20) È®Á¤µÈ ³¯Â¥ÀÎ °æ¿ì *****/
	if (STATE[hopeday] == confirmed)
	{
		cout << "ÇØ´ç ±Ù¹«ÀÏÀº ÀÌ¹Ì È®Á¤µÇ¾ú½À´Ï´Ù." << endl;
		return;
	}
	/***** °­Å»À» ½ÃµµÇÏ´Â °æ¿ì ¿ì¼±¼øÀ§¸¦ ºñ±³ *****/
	if (STATE[hopeday] == occupied)
	{
		string postID = ID[hopeday];
		if (validlist[Search(&validlist, postID)].first.startingMonth < validlist[Search(&validlist, id)].first.startingMonth)
		{
			cout << "¿ì¼± ¼øÀ§°¡ ³·¾Æ¼­ °­Å»ÇÒ ¼ö ¾ø½À´Ï´Ù." << endl;
			return;
		}
		else
		{
			cout << "ÇØ´ç ±Ù¹«ÀÏÀº" << postID << "±Ù¹«ÀÚ°¡ Á¡À¯ ÁßÀÔ´Ï´Ù.ÇØ´ç ±Ù¹«ÀÏÀ» ¼±ÅÃÇÏ½Ã°Ú½À´Ï±î?\n";
			char ans = _getch();

			if (ans == 'Y') {
			}
			else if (ans == 'N') {
				return;
			}
			else {
				cout << "Y ¶Ç´Â N¸¸À» ÀÔ·ÂÇÏ½Ê½Ã¿À." << endl;
				return;
			}
			validlist[Search(&validlist, postID)].second -= 1; // °­Å», Á¡À¯ÀÚ ±Ù¹«È½¼ö °¨¼Ò
			cout << postID << "±Ù¹«ÀÚ´Â ±Ù¹«ÀÏÀ» ´Ù½Ã ¼±ÅÃÇØ¾ß ÇÕ´Ï´Ù. - ±Ù¹«ÀÏ °­Å»";
		}
	}

	/***** ÀÌÇÏ ¸ğµç Á¶°ÇÀ» Åë°úÇßÀ¸¸ç ¼±ÅÃÇÑ ±Ù¹«ÀÏÀÌ ¹İ¿µµÊ *****/

	/***** ¼öÁ¤ÀÎ °æ¿ì ÀÌÀü¿¡ Á¡À¯ ÁßÀÌ´ø ³¯Â¥¸¦ ºñ¿ò *****/
	if (rechoice)
	{
		for (int i = 0; i <= lastday; i++)
		{
			if (ID[i] == id && STATE[i] == occupied)
			{
				STATE[i] = vacant;
			}
		}
<<<<<<< Updated upstream
		/***** ¼±ÅÃÇÑ ³¯Â¥ ¹İ¿µ *****/
		cout << "±Ù¹«ÀÏ ¼öÁ¤ÀÌ ¿Ï·áµÇ¾ú½À´Ï´Ù." << endl;
=======
		/***** ì„ íƒí•œ ë‚ ì§œ ë°˜ì˜ *****/
		cout << "ê·¼ë¬´ì¼ ìˆ˜ì •ì´ ì™„ë£Œë˜ì—ˆìŠµë‹ˆë‹¤." << endl;

		// 4. ê·¼ë¬´ì¼ì„ ì„ íƒí–ˆì„ ë•Œ, ê°™ì€ ì¡°ë¼ë¦¬ëŠ” ê³µìœ í•˜ëŠ” ë¶€ë¶„
		teamindex = -1;

		for (int i = 0; i < teamList.size(); i++)
		{
			for(int j=0; j<dayworker; j++)
				if (id == teamList[i].userinfo[j].ID)
				{
					teamindex = i;
				}		
		}

		if (teamindex == -1)
		{
			cout << "ì—†ëŠ” ê·¼ë¬´ìì…ë‹ˆë‹¤\n" << endl;
			return;
		}
		for (int i = 0; i < dayworker; i++)
			validlist[Search(&validlist, teamList[teamindex].userinfo[i].ID)].second += 1;
		
		ID[hopeday] = teamList[teamindex].userinfo[0].ID;
>>>>>>> Stashed changes
		STATE[hopeday] = occupied;
	}
	/***** ¼öÁ¤ÀÌ ¾Æ´Ñ °æ¿ì ¼±ÅÃÇÑ ³¯Â¥¸¦ ¹Ù·Î ¹İ¿µÇÔ *****/
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
			cout << "ì—†ëŠ” ê·¼ë¬´ìì…ë‹ˆë‹¤\n" << endl;
			return;
		}
		for (int i = 0; i < dayworker; i++)
			validlist[Search(&validlist, teamList[teamindex].userinfo[i].ID)].second += 1;

		ID[hopeday] = teamList[teamindex].userinfo[0].ID;
		STATE[hopeday] = occupied;
<<<<<<< Updated upstream
		ID[hopeday] = id;
		cout << "±Ù¹«ÀÏ ¼öÁ¤ÀÌ ¿Ï·áµÇ¾ú½À´Ï´Ù.";
		validlist[Search(&validlist, id)].second += 1; // »ç¿ëÀÚ ±Ù¹«È½¼ö Ãß°¡
=======

		cout << "ê·¼ë¬´ì¼ ìˆ˜ì •ì´ ì™„ë£Œë˜ì—ˆìŠµë‹ˆë‹¤."; // ì‚¬ìš©ì ê·¼ë¬´íšŸìˆ˜ ì¶”ê°€
>>>>>>> Stashed changes
		//ChalenderFileOutput(date, ID, STATE);
	}

	/***** ¿Ï¼ºµÇ¸é È®Á¤À¸·Î º¯°æ *****/
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
		for (int i = 0; i <= lastday; i++) // ±Ù¹«Ç¥°¡ ¿Ï¼ºµÇ¸é È®Á¤À¸·Î º¯°æ
		{
			STATE[i] = confirmed;
		}
		isWorking = -1;
	}

	/***** ±Ù¹«ÀÚµéÀÇ ¼±ÅÃÈ½¼ö¸¦ ºñ±³ÇÏ¿© È®Á¤ÇÔ *****/
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
		for (int i = 0; i <= lastday; i++) // ¸ğµç ±Ù¹«ÀÚÀÇ ±Ù¹«È½¼ö°¡ °°À¸¸é È®Á¤À¸·Î º¯°æ
		{
			if (STATE[i] == occupied)
			{
				STATE[i] = confirmed;
			}
		}
	}

	// ÆÄÀÏ ¾²±â ID, STATE ÀúÀå
	memberList->FileOutput(isWorking);
	//ChalenderFileOutput(date, ID, STATE);
}

void showSchedule()
{
	string temp;
	int date;
	cout << "¿­¶÷ÇÒ ±Ù¹«Ç¥ÀÇ ¿¬¿ùÀ» ÀÔ·ÂÇÏ½Ê½Ã¿À : " << endl;

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
		cout << "³¯Â¥¸¦ Çü½Ä¿¡ ¸Â°Ô ÀÔ·ÂÇÏ½Ê½Ã¿À." << endl;
		return;
	}
	date = dateChanger(temp); // Çü½Ä º¯È¯ string to int


	// ÆÄÀÏ ÀĞ¾î¼­ Ãâ·ÂÇÏ±â
	string IDarr[DAYMAX];
	int junk[DAYMAX];
	//ChalenderFileInput(date, IDarr, junk);

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
	//ÀÌ°Ô ºÒ·È´Ù´Â °Ç PASS°¡ ¾Æ´Ñ ¼ıÀÚ¿©¾ß¸¸ ÇÔ.
	if (str.length() != 1 && str.length() != 2)
	{ //ÀüÃ¼ ¹®ÀÚ¿­ ±æÀÌ Ã¼Å©
		return false;
	}

	for (int i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]) == 0)
		{ //¼ıÀÚ°¡ ¾Æ´Ô
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
	{ //ÀüÃ¼ ¹®ÀÚ¿­ ±æÀÌ Ã¼Å©
		return false;
	}

	for (int i = 0; i < str.length(); i++)
	{ //¼ıÀÚ(0~9)¿Í ±¸ºĞÀÚ Ã¼Å©
		if (isdigit(str[i]) == 0)
		{ //¼ıÀÚ°¡ ¾Æ´Ô
			if (i != 4)
			{ //±¸ºĞÀÚ ÀÚ¸®°¡ ¾Æ´Ñ °÷¿¡ ¼ıÀÚ°¡ ¾Æ´Ñ °Ô ÀÖÀ» °æ¿ì
				return false;
			}
		}
		else
		{
			if (i == 4)
			{ //±¸ºĞÀÚ ÀÚ¸®¿¡ ¼ıÀÚ°¡ ÀÖ´Â °æ¿ì
				return false;
			}
		}
	}

	//ÀÇ¹Ì ±ÔÄ¢ - ´Ş¸¸ Ã¼Å©ÇÏ¸é µÊ. 5 -> 0ÀÌ¸é µÚ¿¡ 0¸¸ ¾Æ´Ï¸é µÊ / 5->1ÀÌ¸é µÚ¿¡°¡ 1¾Æ´Ï¸é 2¿©¾ß¸¸.
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

int Search(vector<pair<UserInformation, int>>* validlist, string id) // Å½»ö ´ë»ó ¾ÆÀÌµğÀÇ ÀÎµ¦½º¸¦ ¹İÈ¯ÇÔ.
{
	int index = 0;
	for (auto iter = validlist->begin(); iter != validlist->end(); iter++, index++)
	{
		if (iter->first.ID.compare(id) == 0)
			return index;
	}
	return -1;
}

//input(ºÒ·¯¿Ã ´Ş, ´ŞÀÇ ±Ù¹«ÀÏÁ¤ ¹è¿­, ÆÀ ¸®½ºÆ® ¹è¿­, State ¹è¿­) output(ÆÄÀÏ Á¸Àç½Ã true, »õ·Î »ı¼º½Ã false Ãâ·Â) *ÁÖÀÇ ½ÇÇà½Ã ÆÀ¸®½ºÆ® ¹è¿­Àº ÃÊ±âÈ­µÇ¸ç, ÇØ´ç ´ŞÀÇ ÆÀÀ¸·Î ÀçÀÛ¼ºµÊ.
bool CalenderFileInput(int month, string* team, vector<Team>* teamList, int* _STATE)
{
	//ÇØ´ç ´Ş ÀÌ¸§ÀÇ ÆÄÀÏ ¿­±â
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
		//TeamList ÃßÃâ
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

		//±Ù¹«ÀÏÁ¤ ÃßÃâ
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
		printf("»õ ÀúÀå ÆÄÀÏÀ» »ı¼ºÇÏ¿´½À´Ï´Ù.\n");
		NewSaveFile.close();
		return false;
	}

	inputFile.close();

	return true;
}

void CalenderFileOutput(int month, vector<Team>* teamList, string* team, int* STATE)
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
			outputFile << iter->TeamName << " " << iter->userinfo[0].ID << " " << iter->userinfo[0].startingMonth << " " << iter->userinfo[1].ID << iter->userinfo[1].startingMonth << " " << iter->userinfo[2].ID << " " << iter->userinfo[2].startingMonth;
		}
		outputFile << "-";
		for (int i = 1; i < DAYMAX; i++)
		{
			outputFile << i << " " << team[i] << " " << STATE[i];
		}
	}
	outputFile.close();
}