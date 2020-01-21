#pragma once
#include "TRScissorsRockPaper_GUI.h"

class CTRScissorsRockPaper_MainBaseDlg;

class CTRScissorsRockPaper_GaugeDlg :
	public CTRScissorsRockPaper_GUI
{
private:
	enum EGUIName
	{
		GN_BASE,
		GN_BASEINFO,
		GN_GAUGEDLG,
		GN_ROUNDDLG,
		GN_END
	};

private:	// Link
	CTRScissorsRockPaper_MainBaseDlg* m_pMainDlg = nullptr;

private:
	CGUIDialog* m_pDlg = nullptr;

public:
	CTRScissorsRockPaper_GaugeDlg();
	virtual ~CTRScissorsRockPaper_GaugeDlg();

public:
	// CTRScissorsRockPaper_GUI을(를) 통해 상속됨
	virtual void InitName() override;
	virtual void InitGUI() override;

	virtual void showDialog() override;
	virtual void closeDialog() override;

public:
	void SettingClientPos(int _nIndex);

public:	// Accessor
	inline void SetMainDlg(CTRScissorsRockPaper_MainBaseDlg* _pMainDlg) { m_pMainDlg = _pMainDlg; }
	
};
