#include "stdafx.h"
#include "TRScissorsRockPaper_GaugeDlg.h"
//
#include "TRScissorsRockPaper_MainBaseDlg.h"

CTRScissorsRockPaper_GaugeDlg::CTRScissorsRockPaper_GaugeDlg()
{
}

CTRScissorsRockPaper_GaugeDlg::~CTRScissorsRockPaper_GaugeDlg()
{
}

void CTRScissorsRockPaper_GaugeDlg::InitName()
{
	InitGUIName({
		make_tuple<EGUIName, string>(EGUIName::GN_GAUGEDLG, "gui/park/RockPaperScissor/RockPaperScissor_GaugeDlg.gui"),
		});
}

void CTRScissorsRockPaper_GaugeDlg::InitGUI()
{
	string errmsg;
	m_pDlg = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_GAUGEDLG], errmsg);
	m_pDlg->setZOrder(-1.0f);
	
}

void CTRScissorsRockPaper_GaugeDlg::showDialog()
{
	__super::showDialog();
}

void CTRScissorsRockPaper_GaugeDlg::closeDialog()
{
	if(m_pDlg)
	{
		m_pDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_pDlg = nullptr;
	}
}

void CTRScissorsRockPaper_GaugeDlg::SettingClientPos(int _nIndex)
{
	if(m_pDlg)
	{
		m_pDlg->setClientPos(m_pMainDlg->GetFrameGauge(_nIndex));
	}
}
