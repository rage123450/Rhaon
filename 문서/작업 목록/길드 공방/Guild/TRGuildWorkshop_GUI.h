#pragma once
class CTRGuildWorkshop_GUI
{
private:
	constexpr static int MONTH = 31;
	constexpr static int DAY = 24;
	constexpr static int HOUR = 60;
	constexpr static long long UNLIMITED = 253402182000000;

public:
	enum EControl
	{
		CONTROL_BUTTON,
		CONTROL_STATICTEXT,
		CONTROL_EDIT,
		CONTROL_LISTBOX,
		CONTROL_DROPLISTCOMBO,
		CONTROL_SLIDER,
		CONTROL_FRAME,
		CONTROL_IMAGECONTROL,
		CONTROL_SCROLLBAR,
		CONTROL_FORMATEDTEXT,
		CONTROL_END
	};

protected:
	map<int, string> m_mapGUIName;
	array<vector<string>, EControl::CONTROL_END> m_arrayControlName = { {}, };
	string errmsg;

public:
	CTRGuildWorkshop_GUI();
	virtual ~CTRGuildWorkshop_GUI();

public:
	virtual void InitName()abstract;
	virtual void InitGUI()abstract;
	
	virtual void InitButton() {}
	virtual void InitStaticText() {}
	virtual void InitEdit() {}
	virtual void InitListBox() {}
	virtual void InitDropListCombo() {}
	virtual void InitSlider() {}
	virtual void InitFrame() {}
	virtual void InitImageControl() {}
	virtual void InitScrollBar() {}
	virtual void InitFormatedText() {}

	virtual void showDialog();
	virtual void closeDialog()abstract;

public:
	void Init();
	void InitGUIName(vector<tuple<int, string>> _vecTemp);
	void InitControlName(EControl _eControl, vector<string> _vecName);

protected:
	string GetSelectDay(int _nDurationDay);
	string GetSelectDay(time_type _nDurationDay);
};
