#include "stdafx.h"
#include "TRScissorsRockPaper_BaseInfoDlg.h"
//
#include "TRScissorsRockPaper_MainBaseDlg.h"

CTRScissorsRockPaper_BaseInfoDlg::CTRScissorsRockPaper_BaseInfoDlg()
{
}

CTRScissorsRockPaper_BaseInfoDlg::~CTRScissorsRockPaper_BaseInfoDlg()
{
}

void CTRScissorsRockPaper_BaseInfoDlg::InitName()
{
	InitGUIName({
		make_tuple<EGUIName, string>(EGUIName::GN_BASEINFO, "gui/park/RockPaperScissor/RockPaperScissor_BaseInfo.gui"),
		});
}

void CTRScissorsRockPaper_BaseInfoDlg::InitGUI()
{
	string errmsg;
	m_pDlg = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_BASEINFO], errmsg);
	m_pDlg->setZOrder(-1.0f);
	m_pDlg->setClientPos(m_pMainDlg->GetFrameBaseInfo());
}

void CTRScissorsRockPaper_BaseInfoDlg::showDialog()
{
	__super::showDialog();
}

void CTRScissorsRockPaper_BaseInfoDlg::closeDialog()
{
	if(m_pDlg)
	{
		m_pDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));

		CGUIManager::getInstance().removeControl(m_pDlg);
		m_pDlg = nullptr;
	}
}
