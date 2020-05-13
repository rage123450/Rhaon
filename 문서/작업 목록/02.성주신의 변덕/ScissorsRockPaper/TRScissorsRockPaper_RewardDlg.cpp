#include "stdafx.h"
#include "TRScissorsRockPaper_RewardDlg.h"
//
#include "gui/GUIItemImageCtrl.h"
#include "gameui/ClientItemInfoLoader.h"
#include "TRScissorsRockPaper_GameAlone.h"
#include "TRScissorsRockPaper_GameGroup.h"

CTRScissorsRockPaper_RewardDlg::CTRScissorsRockPaper_RewardDlg()
{
}

CTRScissorsRockPaper_RewardDlg::~CTRScissorsRockPaper_RewardDlg()
{
	closeDialog();
}

bool CTRScissorsRockPaper_RewardDlg::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	CGUIControl* pCtrl = ctrlID.findControl();
	if(!pCtrl)
	{
		return false;
	}

	string name = pCtrl->getName();

	for(auto& x : m_arrayButton)
	{
		if(get<0>(x) == name)
		{
			get<1>(x)();
			break;
		}
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRScissorsRockPaper_RewardDlg::showDialog()
{
	__super::showDialog();

	UpdateRewardItem();
}

void CTRScissorsRockPaper_RewardDlg::closeDialog()
{
	for(auto& x : m_arrayDlg)
	{
		if(x)
		{
			x->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
			x = nullptr;
		}
	}
}

void CTRScissorsRockPaper_RewardDlg::InitName()
{
	InitGUIName({
		make_tuple<EGUIName, string>(EGUIName::GN_REWARD, "gui/park/RockPaperScissor/RockPaperScissor_Reward.gui"),
		});

	InitControlName(EControlType::CT_BUTTON,
		{
			// Reward
			"Ok",
		});

	InitControlName(EControlType::CT_STATICTEXT,
		{
			// Reward
			"Name",
		});

	InitControlName(EControlType::CT_FORMATEDTEXT,
		{
			// Reward
			"Desc",
		});

	InitControlName(EControlType::CT_IMAGECONTROL,
		{
			// Reward
			"ItemImg",
		});
}

void CTRScissorsRockPaper_RewardDlg::InitGUI()
{
	string errmsg;

	for(int i = 0; i < EGUIName::GN_END; i++)
	{
		switch(i)
		{
		case CTRScissorsRockPaper_RewardDlg::GN_REWARD:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[i], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->centerPosition();
				m_arrayDlg[i]->setModalDialog(true);
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
				CGUIManager::getInstance().setFocus(m_arrayDlg[i]->getControlID());
				m_arrayDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
			break;
		}
	}
}

void CTRScissorsRockPaper_RewardDlg::InitButton()
{
	for(int i = 0; i < EButtonName::BN_END; i++)
	{
		switch(i)
		{
		case CTRScissorsRockPaper_RewardDlg::BN_OK:
			get<0>(m_arrayButton[i]) = m_arrayName[EControlType::CT_BUTTON][i];
			get<1>(m_arrayButton[i]) = [&]()
			{
				if(m_pGameAlone)
				{
					m_pGameAlone->closeDialog();
				}
				else if(m_pGameGroup)
				{
					m_pGameGroup->closeDialog();
				}
			};
			break;
		}
	}
}

void CTRScissorsRockPaper_RewardDlg::InitStaticText()
{
	m_arrayStaticText[EStaticTextName::STN_NAME] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_REWARD]->findControl(m_arrayName[EControlType::CT_STATICTEXT][EStaticTextName::STN_NAME], GUI_SUB_CONTROL_STATIC_TEXT));
}

void CTRScissorsRockPaper_RewardDlg::InitFormatedText()
{
	m_arrayFormatedText[EFormatedTextName::FTN_DESC] = static_cast<CFormatedStaticText*>(m_arrayDlg[EGUIName::GN_REWARD]->findControl(m_arrayName[EControlType::CT_FORMATEDTEXT][EFormatedTextName::FTN_DESC], GUI_SUB_CONTROL_FORMATED_STATIC_TEXT));
}

void CTRScissorsRockPaper_RewardDlg::InitImageControl()
{
	m_pItemImageCtrl = static_cast<CGUIItemImageCtrl*>(m_arrayDlg[EGUIName::GN_REWARD]->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][EImageCtrlName::IC_ITEMIMG], GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
}

void CTRScissorsRockPaper_RewardDlg::UpdateRewardItem()
{
	if(!m_pGameAlone && !m_pGameGroup)
	{
		return;
	}

	int nGetItemNumIndex = 0;
	if(m_pGameAlone)
	{
		nGetItemNumIndex = m_pGameAlone->GetFinalItemIndex();
	}
	else if(m_pGameGroup)
	{
		nGetItemNumIndex = m_pGameGroup->GetFinalItemIndex();
	}
	
	const CItemInfoNode* pItemInfo = CClientItemList::getInstance().getRealItemInfo(nGetItemNumIndex);

	if(m_pItemImageCtrl)
	{
		m_pItemImageCtrl->setItemImage(nGetItemNumIndex);
	}

	if(m_arrayStaticText[EStaticTextName::STN_NAME])
	{
		m_arrayStaticText[EStaticTextName::STN_NAME]->setText(pItemInfo->m_name);
	}

	if(m_arrayFormatedText[EFormatedTextName::FTN_DESC])
	{
		m_arrayFormatedText[EFormatedTextName::FTN_DESC]->setText(pItemInfo->m_desc);
	}
}