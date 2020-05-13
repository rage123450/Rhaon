#pragma once
#include "TRMiniGameAnswer.h"
class CTRMiniGameAnswer_Choice :
	public CTRMiniGameAnswer
{
private:
	std::unordered_map<std::string, CGUIControl*> m_umapBtn;
	std::vector<std::string> m_vecBtnActName;
	std::vector<std::string> m_vecBtnDisName;

public:
	CTRMiniGameAnswer_Choice() = default;
	virtual ~CTRMiniGameAnswer_Choice() = default;

public:
	void InitBtnAct(CGUIDialog * _pDlg, std::vector<std::tuple<std::string, std::function<bool(CGUIControl*)>, std::string, int>> _vecData);
	void InitBtnDis(CGUIDialog * _pDlg, std::vector<std::tuple<std::string, std::function<bool(CGUIControl*)>, std::string, int>> _vecData);
	
	void ToggleBtn(bool _bOn);
	void ToggleBtnCheck(int _nNum);
	void ResetBtnCheck();

	void SetBtnText(std::vector<string> _vecText);

private:
	void InitButton(std::vector<std::string>& _vecBtnName, CGUIDialog * _pDlg, std::vector<std::tuple<std::string, std::function<bool(CGUIControl*)>, std::string, int>> _vecData);
	void bindBtn(CGUIDialog* _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func);
	void BindBtnAndData(CGUIDialog* _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func, std::string key, int data);
	void setCtrlUserData(std::string ctrlName, std::string key, int data);
};

