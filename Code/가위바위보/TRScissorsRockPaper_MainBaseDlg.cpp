#include "stdafx.h"
#include "TRScissorsRockPaper_MainBaseDlg.h"
//
#include "TRScissorsRockPaper_BaseInfoDlg.h"
#include "TRScissorsRockPaper_GaugeDlg.h"

CTRScissorsRockPaper_MainBaseDlg::CTRScissorsRockPaper_MainBaseDlg()
{
}

CTRScissorsRockPaper_MainBaseDlg::~CTRScissorsRockPaper_MainBaseDlg()
{
	closeDialog();
}

void CTRScissorsRockPaper_MainBaseDlg::InitName()
{
	InitGUIName({
		make_tuple<EGUIName, string>(EGUIName::GN_BASE, "gui/park/RockPaperScissor/RockPaperScissor_Base.gui"),
		});

	InitControlName(EControlType::CT_BUTTON,
		{
			"ScissorBtn1","RockBtn2","PaperBtn3","CloseBtn","StartBtn","ScissorBtnDis1","RockBtnDis2","PaperBtnDis3",
		});

	InitControlName(EControlType::CT_FORMATEDTEXT,
		{
			"NpcMent",
		});

	InitControlName(EControlType::CT_FRAME,
		{
			"BaseFrame","ItemDlg","BaseInfoDlg","RoundDlg","GageDlg1","GageDlg2","GageDlg3","Base_Bk",
		});

	InitControlName(EControlType::CT_IMAGECONTROL,
		{
			"Win","Lose","Draw","Time",
		});
}

void CTRScissorsRockPaper_MainBaseDlg::InitGUI()
{
	string errmsg;
	m_pDlg = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_BASE], errmsg);
	m_pDlg->setZOrder(-1.0f);
	m_pDlg->centerPosition();
	m_pDlg->setModalDialog(true);
	CGUIManager::getInstance().setFocus(m_pDlg->getControlID());
	m_pDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
}

void CTRScissorsRockPaper_MainBaseDlg::showDialog()
{
	__super::showDialog();

	m_pBaseInfo = make_unique<CTRScissorsRockPaper_BaseInfoDlg>();
	m_pBaseInfo->SetMainDlg(this);
	m_pBaseInfo->showDialog();

	for(int i = 0; i < MAX_GAUGE; i++)
	{
		m_arrayGaugeDlg[i] = make_unique<CTRScissorsRockPaper_GaugeDlg>();
		m_arrayGaugeDlg[i]->SetMainDlg(this);
		m_arrayGaugeDlg[i]->showDialog();
		m_arrayGaugeDlg[i]->SettingClientPos(i);
	}
}

void CTRScissorsRockPaper_MainBaseDlg::closeDialog()
{
	if(m_pDlg)
	{
		m_pDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_pDlg = nullptr;
	}

	if(m_pBaseInfo)
	{
		m_pBaseInfo->closeDialog();
	}

	for(auto& i : m_arrayGaugeDlg)
	{
		if(i)
		{
			i->closeDialog();
		}
	}
}

void CTRScissorsRockPaper_MainBaseDlg::InitButton()
{
	for(int i = 0; i < EButtonName::BN_END; i++)
	{
		switch(i)
		{
		case CTRScissorsRockPaper_MainBaseDlg::BN_SCISSORBTN1:
			break;
		
		case CTRScissorsRockPaper_MainBaseDlg::BN_ROCKBTN2:
			break;
		
		case CTRScissorsRockPaper_MainBaseDlg::BN_PAPERBTN3:
			break;
		
		case CTRScissorsRockPaper_MainBaseDlg::BN_CLOSEBTN:
			m_arrayButton[i] = static_cast<CGUIImageButton*>(m_pDlg
				->findControl(m_arrayName[EControlType::CT_BUTTON][i], GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i]->bindButtonClickCmdFunc([&](CGUIControl* pCtrl)->bool
			{
				closeDialog();
				return true;
			});
			break;

		case CTRScissorsRockPaper_MainBaseDlg::BN_STARTBTN:
			break;
	
		case CTRScissorsRockPaper_MainBaseDlg::BN_SCISSORBTNDIS1:
			break;
		
		case CTRScissorsRockPaper_MainBaseDlg::BN_ROCKBTNDIS2:
			break;
		
		case CTRScissorsRockPaper_MainBaseDlg::BN_PAPERBTNDIS3:
			break;
		}
	}
}

void CTRScissorsRockPaper_MainBaseDlg::InitFrame()
{
}

void CTRScissorsRockPaper_MainBaseDlg::InitImageControl()
{
}

void CTRScissorsRockPaper_MainBaseDlg::InitFormatedText()
{
}
