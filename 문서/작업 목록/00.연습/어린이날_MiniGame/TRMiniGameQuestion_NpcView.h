#pragma once
#include "TRMiniGameQuestion.h"
//
#include "gameui/TRObjectView.h"

class CTRMiniGameQuestion_NpcView :
	public CTRMiniGameQuestion,
	public IntTask
{
private:
	CGUIUserControl* m_pDiceViewCtrl = nullptr;
	CTRObjectView m_diceObjView;

	std::map<std::tuple<int, int, int>, std::string> m_mapMent;

public:
	CTRMiniGameQuestion_NpcView();
	virtual ~CTRMiniGameQuestion_NpcView();

public:
	virtual void Update(float fElapsed);

public:
	void Init(CGUIDialog* _pDlg, std::string _strCtrlName, std::string _strModelName, std::string _strAnimationName, std::tuple<float, float> _tupleRadius = { 0.0f,0.0f }, float _fFovy = CONST_PI / 10);
	void ChangeUserView(string _strPartGroupName, string _strAnimationName);
	bool LoadMent(const std::string& strFileName);

public:
	const std::map<std::tuple<int, int, int>, std::string>& GetMent() { return m_mapMent; }
};