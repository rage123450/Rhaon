#include "stdafx.h"
#include "TRGuildWorkshop_GUI.h"

#include "language/LanguageHeader.h"

CTRGuildWorkshop_GUI::CTRGuildWorkshop_GUI()
{
}

CTRGuildWorkshop_GUI::~CTRGuildWorkshop_GUI()
{
}

void CTRGuildWorkshop_GUI::Init()
{
	InitName();
	
	InitGUI();

	InitButton();
	InitStaticText();
	InitEdit();
	InitListBox();
	InitDropListCombo();
	InitSlider();
	InitFrame();
	InitImageControl();
	InitScrollBar();
	InitFormatedText();
}

void CTRGuildWorkshop_GUI::InitGUIName(vector<tuple<int, string>> _vecTemp)
{
	for(auto& i : _vecTemp)
	{
		m_mapGUIName.insert(make_pair(get<0>(i), get<1>(i)));
	}
}

void CTRGuildWorkshop_GUI::InitControlName(EControl _eControl, vector<string> _vecName)
{
	m_arrayControlName[_eControl].assign(_vecName.begin(), _vecName.end());
}

void CTRGuildWorkshop_GUI::showDialog()
{
	closeDialog();

	Init();
}

string CTRGuildWorkshop_GUI::GetSelectDay(int _nDurationDay)
{
	if(_nDurationDay <= 0)
	{
		return _STR(MSG_COMPLETION);
	}

	int nMin = 0, nHour = 0, nDay = 0;

	nHour = _nDurationDay / 60;
	nDay = nHour / 24;

	nMin = _nDurationDay % 60;
	nHour = nHour % 24;

	string strDay, strHour, strMin;

	strDay = nDay == 0 ? "" : to_string(nDay) + _STR(ITEM_TIME_DAY);
	strHour = nHour == 0 ? "" : to_string(nHour) + _STR(ITEM_TIME_HOUR);
	strMin = nMin == 0 ? "" : to_string(nMin) + _STR(ITEM_TIME_MINUTE);

	return (strDay + strHour + strMin) == "" ? "-" : strDay + strHour + strMin;
}

string CTRGuildWorkshop_GUI::GetSelectDay(time_type _nDurationDay)
{
	if(_nDurationDay <= 0)
	{
		return GetSelectDay(0);
	}

	// 9999년 12월 31일 : 무제한
	if(_nDurationDay >= UNLIMITED)
	{
		return _STR(ITEM_MSG_UNLIMITED);
	}

	time_type curTime = CCurrentTime::current();
	time_type temp = _nDurationDay - CCurrentTime::current();
	string strTemp;
	CCurrentTime::format(temp, strTemp);

	vector<string> vecTemp;
	stringutil::splitString(strTemp.substr(0, 10), '/', vecTemp);
	int month = stoi(vecTemp[1]);
	int day = stoi(vecTemp[2]);

	vector<string> vecTemp2;
	stringutil::splitString(strTemp.substr(11, strTemp.size()), ':', vecTemp2);
	int hour = stoi(vecTemp2[0]);
	int min = stoi(vecTemp2[1]);

	int nMonthToMin = month * (MONTH * DAY * HOUR);
	int nDayToMin = day * (DAY * HOUR);
	int nHourToMin = (hour * HOUR) + min;

	int result = nMonthToMin + nDayToMin + nHourToMin;

	result -= (MONTH*DAY*HOUR) + (DAY*HOUR) + (9 * HOUR);

	return GetSelectDay(result);
}
