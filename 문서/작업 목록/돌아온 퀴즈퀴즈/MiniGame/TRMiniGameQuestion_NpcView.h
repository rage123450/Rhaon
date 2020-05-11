#pragma once
#include "TRMiniGameQuestion.h"
#include "gameui/TRObjectView.h"

class CTRMiniGameQuestion_NpcView :
	public CTRMiniGameQuestion
{
private:
	std::map<std::tuple<int, int, int>, std::string> m_mapMent;

	CGUIUserControl* m_pDiceViewCtrl = nullptr;
	CTRObjectView m_diceObjView;

public:
	CTRMiniGameQuestion_NpcView() = default;
	virtual ~CTRMiniGameQuestion_NpcView() = default;

public:
	bool LoadMent(const std::string& strFileName);

	void InitNpcView(CGUIDialog* _pDlg, std::string _strCtrlName, std::string _strModelName, std::string _strAnimationName, std::tuple<float, float> _tupleRadius = { 0.0f,0.0f }, float _fFovy = CONST_PI / 10);
	void UpdateNpcView(float fElapsed);
	
	void ChangeNpcView(string _strPartGroupName, string _strAnimationName);

public:
	std::reference_wrapper<std::map<std::tuple<int, int, int>, std::string>> GetMent() { return ref(m_mapMent); }
	__declspec(property(get = GetMent)) std::reference_wrapper<std::map<std::tuple<int, int, int>, std::string>> __mapMent;
};

