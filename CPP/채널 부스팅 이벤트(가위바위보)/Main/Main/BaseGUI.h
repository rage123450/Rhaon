#pragma once
class CBaseGUI
{
public:
	CBaseGUI();
	virtual ~CBaseGUI();

public:
	virtual bool onButtonClick() = 0;
	virtual void showDialog() = 0;
	virtual void closeDialog() = 0;
};

