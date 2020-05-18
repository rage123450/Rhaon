#pragma once
#include "TRMiniGameAnswer.h"
class CTRMiniGameAnswer_ChoiceSRP :
	public CTRMiniGameAnswer
{
public:
	enum ESelectSRP
	{
		SS_SCISSORS,
		SS_ROCK,
		SS_PAPER,
		SS_END
	};

private:
	ESelectSRP m_eCurSelectSRP;
	std::vector<std::string> m_vecBtnName;
	std::vector<std::string> m_vecBtnDisName;

public:
	CTRMiniGameAnswer_ChoiceSRP();
	virtual ~CTRMiniGameAnswer_ChoiceSRP();

public:
	// CTRMiniGameAnswer을(를) 통해 상속됨
	virtual void Init() override;

public:
	void InitSelectSRP(CGUIDialog * _pDlg, std::vector<std::tuple<std::string, std::function<bool(CGUIControl*)>, std::string, int>> _vecData);
	void InitDisSRP(CGUIDialog * _pDlg, std::vector<std::tuple<std::string, std::function<bool(CGUIControl*)>, std::string, int>> _vecData);

	bool UpdateSelectSRP(int _nSRP);

	void ToggleSelectSRP(bool _bOn);
	void ToggleCheckedButton(ESelectSRP _eSelectSRP);

public:
	inline ESelectSRP GetESelectSRPToInt(int _nNum)
	{
		switch(_nNum)
		{
		case 0: return ESelectSRP::SS_SCISSORS;
		case 1: return ESelectSRP::SS_ROCK;
		case 2: return ESelectSRP::SS_PAPER;
		}
	}

public:
	ESelectSRP GetCurSelectSRP()const { return m_eCurSelectSRP; }
};

