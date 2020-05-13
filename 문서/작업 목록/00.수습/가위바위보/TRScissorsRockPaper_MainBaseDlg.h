#pragma once
#include "TRScissorsRockPaper_GUI.h"

class CTRScissorsRockPaper_BaseInfoDlg;
class CTRScissorsRockPaper_GaugeDlg;

class CTRScissorsRockPaper_MainBaseDlg :
	public CTRScissorsRockPaper_GUI
{
private:
	constexpr static int MAX_GAUGE = 3;

public:
	enum EGUIName
	{
		GN_BASE,
		GN_BASEINFO,
		GN_GAUGEDLG,
		GN_ROUNDDLG,
		GN_END
	};

	enum EButtonName
	{
		BN_SCISSORBTN1,
		BN_ROCKBTN2,
		BN_PAPERBTN3,
		BN_CLOSEBTN,
		BN_STARTBTN,
		BN_SCISSORBTNDIS1,
		BN_ROCKBTNDIS2,
		BN_PAPERBTNDIS3,
		BN_END
	};

	enum EFormatedTextName
	{
		FTN_NPCMENT,
		FTN_END
	};

	enum EFrameName
	{
		FN_BASEFRAME,
		FN_ITEMDLG,
		FN_BASEINFODLG,
		FN_ROUNDDLG,
		FN_GAGEDLG1,
		FN_GAGEDLG2,
		FN_GAGEDLG3,
		FN_BASE_BK,
		FN_END
	};

	enum EImageCtrlName
	{
		IN_WIN,
		IN_LOSE,
		IN_DRAW,
		IN_TIME,
		IN_END
	};

private:
	std::unique_ptr<CTRScissorsRockPaper_BaseInfoDlg> m_pBaseInfo = nullptr;
	std::array<unique_ptr<CTRScissorsRockPaper_GaugeDlg>, MAX_GAUGE> m_arrayGaugeDlg;

private:
	CGUIDialog* m_pDlg = nullptr;

	std::array<CGUIImageButton*, EButtonName::BN_END> m_arrayButton = { nullptr, };
	std::array<CFormatedStaticText*, EFormatedTextName::FTN_END> m_arrayFormatedText = { nullptr, };
	std::array<CGUIFrameImage*, EFrameName::FN_END> m_arrayFrame = { nullptr, };
	std::array<CGUIImageCtrl*, EImageCtrlName::IN_END> m_arrayImageCtrl = { nullptr, };

public:
	CTRScissorsRockPaper_MainBaseDlg();
	virtual ~CTRScissorsRockPaper_MainBaseDlg();

public:
	// CTRScissorsRockPaper_GUI을(를) 통해 상속됨
	virtual void InitName() override;
	virtual void InitGUI() override;
	
	virtual void showDialog() override;
	virtual void closeDialog() override;

	virtual void InitButton() override;
	virtual void InitFrame() override;
	virtual void InitImageControl() override;
	virtual void InitFormatedText() override;

public:
	inline const CRectInfo& GetFrameBaseInfo()const
	{
		if(m_pDlg)
		{
			return m_pDlg->findControl(m_arrayName[EControlType::CT_FRAME][EFrameName::FN_BASEINFODLG], GUI_SUB_CONTROL_FRAME)->getScreenRect();
		}
	}

	inline const CRectInfo& GetFrameGauge(int _nIndex)const
	{
		if(m_pDlg)
		{
			return m_pDlg->findControl(m_arrayName[EControlType::CT_FRAME][EFrameName::FN_GAGEDLG1 + _nIndex], GUI_SUB_CONTROL_FRAME)->getScreenRect();
		}
	}
};
