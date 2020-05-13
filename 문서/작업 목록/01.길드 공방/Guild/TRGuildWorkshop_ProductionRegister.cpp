/* ---------------------------------------------------------------
 *
 * Copyright 2019 by Rhaon Ent.
 *
 * TRGuildWorkshop_ProductionRegister.cpp
 *
 * 2019. 12. Han Younho
 *
 * ---------------------------------------------------------------
 */

#include "stdafx.h"
#include "TRGuildWorkshop_ProductionRegister.h"

#include "language/LanguageHeader.h"

#include "gameui/TRShortTimeMessage.h"
#include "gameui/ClientItemInfoLoader.h"

#include "gui/GUIItemImageCtrl.h"

#include "NetClientManager.h"
#include "TRGuildWorkshop_ManagementDlg.h"

CTRGuildWorkshop_ProductionRegister::CTRGuildWorkshop_ProductionRegister(CTRGuildWorkshop_ManagementDlg* pOwner)
	: m_pOwner(pOwner), m_pItemInfo(nullptr)
	, m_dlgID(CGUIControlID::INVALID_ID), m_itemDlgID(CGUIControlID::INVALID_ID)
{

}

CTRGuildWorkshop_ProductionRegister::~CTRGuildWorkshop_ProductionRegister()
{
	m_pOwner = nullptr;
	m_pItemInfo = nullptr;

	closeDialog();
}

bool CTRGuildWorkshop_ProductionRegister::isVisible() const
{
	CGUIControl* pDlg = m_dlgID.findControl();
	return pDlg ? pDlg->isVisible() : false;
}

bool CTRGuildWorkshop_ProductionRegister::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	if (false == isVisible())
	{
		return false;
	}	

	CGUIControl* pCtrl = ctrlID.findControl();
	if (nullptr == pCtrl)
	{
		return false;
	}

	std::string name = pCtrl->getName();

	if ("yes" == name)
	{
		_registerItemToGuildPlant();
		closeDialog();
		return true;
	}
	else if ("no" == name)
	{
		closeDialog();
		return true;
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRGuildWorkshop_ProductionRegister::showDialog(GuildPlantItemInfo* pItemInfo)
{
	// 아이템 정보가 제대로 들어왔는지 검사 후 다이얼로그 초기화
	if (nullptr == pItemInfo)
	{
		CTRShortTimeMessage::getInstance().showMessage(_STR(AUCTION_SYSTEM_NOT_SELECT_ITEM));
		return;
	}
	
	if (nullptr == m_pOwner)
	{
		DBG_DEMO_OUTPUT("%s - Reason[%s]", __FUNCTION__, _STR(MSG_BILLING_ERROR_USER_INFO_NO_EXIST));
		return;
	}

	// 존재하는 아이템인지 확인
	if (false == m_pOwner->isValidIndexItemNum(pItemInfo->iIndex))
	{
		CTRShortTimeMessage::getInstance().showMessage(_STR(AUCTION_SYSTEM_NOT_SELECT_ITEM));
		return;
	}

	closeDialog();

	std::string errmsg;

	CGUIDialog* pDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_Production_Register.gui", errmsg);
	if (nullptr == pDlg)
	{
		return;
	}

	m_dlgID = pDlg->getControlID();

	pDlg->centerPosition();
	pDlg->setModalDialog(true);
	pDlg->setDialogListener(getCommandTargetID());
	pDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
	CGUIManager::getInstance().setFocus(m_dlgID);

	if (m_pItemInfo)
	{
		m_pItemInfo = nullptr;
	}

	m_pItemInfo = pItemInfo;

	CGUIStaticText* pText = static_cast<CGUIStaticText*>(pDlg->findControl("MyGuildPoint"));
	if (pText)
	{
		if (eGuildPlantDistributeKind_GIFT_MASTER == m_pOwner->getCurItemDistributeKindEnum())
		{
			pText->setText("-");
		}
		else
		{
			if (eRewardCondition_TRMONEY == m_pItemInfo->iSellPointKind)
			{
				pText->setText(format("%d %s", m_pItemInfo->iSellPointValue, _STR(MONEY_TR)));
			}
			else if (eRewardCondition_PERSONAL_GUILD_POINT == m_pItemInfo->iSellPointKind)
			{
				pText->setText(format("%d %s", m_pItemInfo->iSellPointValue, _STR(MONEY_MY_GUILD_POINT)));
			}
		}
	}

	pText = static_cast<CGUIStaticText*>(pDlg->findControl("Message"));
	if (pText)
	{
		pText->setText(_STR(GUILD_PLANT_REGIST_ITEM_PRODUCTION));
	}

	_setItemDialog();
}

void CTRGuildWorkshop_ProductionRegister::closeDialog()
{
	CGUIControl* pItemDlg = m_itemDlgID.findControl();
	if (pItemDlg)
	{
		pItemDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_itemDlgID = CGUIControlID::INVALID_ID;
	}

	CGUIControl* pDlg = m_dlgID.findControl();
	if (pDlg)
	{
		pDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_dlgID = CGUIControlID::INVALID_ID;
	}
}

void CTRGuildWorkshop_ProductionRegister::_setItemDialog()
{
	if (nullptr == m_pOwner)
	{
		DBG_DEMO_OUTPUT("%s - Reason[%s]", __FUNCTION__, _STR(MSG_BILLING_ERROR_USER_INFO_NO_EXIST));
		return;
	}

	std::string errmsg;

	CGUIDialog* pItemDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_SelectItemDlg.gui", errmsg);
	if (nullptr == pItemDlg)
	{
		return;
	}

	m_itemDlgID = pItemDlg->getControlID();

	CGUIControl* pDlg = m_dlgID.findControl();
	if (pDlg)
	{
		CGUIControl* pFrame = pDlg->findControl("Workshop_SelectItemDlg");
		if (pFrame)
		{
			pItemDlg->setClientPos(pFrame->getScreenRect());
		}
	}

	pItemDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));

	CGUIStaticText* pText = static_cast<CGUIStaticText*>(pItemDlg->findControl("TypeMent"));
	if (pText)
	{
		pText->setText(m_pOwner->getCurItemDistributeKindString());
	}

	const CItemInfoNode* pItemInfoNode = CClientItemList::getInstance().getRealItemInfo(m_pItemInfo->iItemNum);
	if (pItemInfoNode)
	{
		pText = static_cast<CGUIStaticText*>(pItemDlg->findControl("GoodsName"));
		if (pText)
		{
			pText->setText(pItemInfoNode->m_name);
		}

		CGUIItemImageCtrl* pItemImage = static_cast<CGUIItemImageCtrl*>(pItemDlg->findControl("Image"));
		if (pItemImage)
		{
			pItemImage->setRealItemImage(pItemInfoNode);
		}
	}

	pText = static_cast<CGUIStaticText*>(pItemDlg->findControl("Day"));
	if (pText)
	{
		pText->setText(format("%s: %d%s", _STR(PRODUCTION_PERIOD), m_pItemInfo->iDurationDay, _STR(ITEM_TIME_DAY)));
	}
}

void CTRGuildWorkshop_ProductionRegister::_registerItemToGuildPlant()
{
	if (nullptr == m_pItemInfo)
	{
		CTRShortTimeMessage::getInstance().showMessage(_STR(AUCTION_SYSTEM_NOT_SELECT_ITEM));
		return;
	}

	if (nullptr == m_pOwner)
	{
		DBG_DEMO_OUTPUT("%s - Reason[%d]", __FUNCTION__, m_pItemInfo->iItemNum);
		return;
	}

	if (false == m_pOwner->isValidIndexItemNum(m_pItemInfo->iIndex))
	{
		CTRShortTimeMessage::getInstance().showMessage(_STR(AUCTION_SYSTEM_NOT_SELECT_ITEM));
		return;
	}

	eGuildPlantDistributeKind eDistributeKind = m_pOwner->getCurItemDistributeKindEnum();
	int iLimitBuyCount = m_pOwner->getCurItemLimitBuyCount();

	// 길드공방 제작 등록 요청
	CNetClientManager::getInstance().requestRegisterGuildPlantItemMake(m_pItemInfo->iIndex, eDistributeKind, iLimitBuyCount);
	DBG_DEMO_OUTPUT("requestRegisterGuildPlantItemMake - index[%d], eDistributeKind[%d], iLimitBuyCount[%d]", m_pItemInfo->iIndex, eDistributeKind, iLimitBuyCount);
}