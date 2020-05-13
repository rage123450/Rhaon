#pragma once
#include "gameui/TRUserInterface.h"

class CTRMiniGameAnswer
{
public:
	enum AnswerType
	{
		Answer_NONE,
		Answer_STRING,
		Answer_CHOICENUM,
		Answer_CHOICEOX,
		Answer_SRP,
	};

private:
	AnswerType m_eType;

protected:
	std::unordered_map<std::string, CGUIControl*> m_umapBtn;

public:
	CTRMiniGameAnswer(AnswerType eType);
	virtual ~CTRMiniGameAnswer();

public:
	virtual void Init() abstract;

public:
	void bindBtn(CGUIDialog* _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func);
	void setCtrlUserData(CGUIDialog* _pDlg, std::string ctrlName, std::string key, std::string data);
	void setCtrlUserData(CGUIDialog* _pDlg, std::string ctrlName, std::string key, int data);
	std::string GetUserDataString(std::string btnName, std::string key);
	int GetUserDataInt(std::string btnName, std::string key);

	CGUIControl* GetButtonControl(std::string btnName);

	void BindBtnAndData(CGUIDialog* _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func, std::string key, std::string data);
	void BindBtnAndData(CGUIDialog* _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func, std::string key, int data);

private:
	void setCtrlUserData(std::string ctrlName, std::string key, std::string data);
	void setCtrlUserData(std::string ctrlName, std::string key, int data);

public:
	AnswerType getType()const { return m_eType; }
};

