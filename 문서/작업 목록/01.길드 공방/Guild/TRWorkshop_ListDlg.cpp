#include "stdafx.h"
#include "TRWorkshop_ListDlg.h"
//
#include "language/LanguageHeader.h"
#include "NetClientManager.h"
#include "gameui/ClientItemInfoLoader.h"
#include "gameui/TRShortTimeMessage.h"
#include "game/TRRewardManager.h"
#include "gui/GUIItemImageCtrl.h"
#include "TRGuildWorkshop_WarehouseDlg.h"
#include "TRGuildWorkshop_ExpenseDlg.h"
#include "TRGuildWorkshop_GuideDlg.h"

CTRWorkshop_ListDlg::CTRWorkshop_ListDlg()
{
}

CTRWorkshop_ListDlg::~CTRWorkshop_ListDlg()
{
	closeDialog();
}

void CTRWorkshop_ListDlg::showDialog()
{
	__super::showDialog();

	m_bStart = true;

	CNetClientManager::getInstance().requestGetGuildPlantSellItemList();

	InitListPiece();

	InitPage();

	UpdateListPiece();

	_setGuildPointDialog();
}

void CTRWorkshop_ListDlg::closeDialog()
{
	m_bStart = false;

	for(int i = 0; i < m_arrayDlg.size(); i++)
	{
		if(m_arrayDlg[i])
		{
			m_arrayDlg[i]->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
			m_arrayDlg[i] = nullptr;
		}
	}

	SAFE_DELETE(m_pWarehouseDlg);
	SAFE_DELETE(m_pExpenseDlg);

	CGUIControl* pGuildPointDlg = m_guildPointDlgID.findControl();
	if(pGuildPointDlg)
	{
		pGuildPointDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_guildPointDlgID = CGUIControlID::INVALID_ID;
	}
}

bool CTRWorkshop_ListDlg::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	CGUIControl* pCtrl = ctrlID.findControl();

	if(pCtrl)
	{
		string name = pCtrl->getName();
		for_each(m_arrayButton.begin(), m_arrayButton.end(), [&](auto var) {if(get<0>(var) == name) get<1>(var)(); });

		for(int i = 0; i < MAX_LISTPIECE; ++i)
		{
			for(int j = 0; j < m_arrayListPiece[i].arrayButton.size(); j++)
			{
				if(get<0>(m_arrayListPiece[i].arrayButton[j]) == name)
				{
					get<1>(m_arrayListPiece[i].arrayButton[j])(i);
				}
			}
		}

		if("ManageBtn" == name)
		{
			if(nullptr == m_pWarehouseDlg)
			{
				m_pWarehouseDlg = new CTRGuildWorkshop_WarehouseDlg;
			}

			m_pWarehouseDlg->showDialog();
		}
		else if("ExpenseBtn" == name)
		{
			if(nullptr == m_pExpenseDlg)
			{
				m_pExpenseDlg = new CTRGuildWorkshop_ExpenseDlg;
			}

			m_pExpenseDlg->showDialog();
		}
		else if("GuideBtn" == name)
		{
			if(nullptr == m_pGuideDlg)
			{
				m_pGuideDlg = make_shared<CTRGuildWorkshop_GuideDlg>();
			}
			m_pGuideDlg->showDialog();
		}
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRWorkshop_ListDlg::onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList)
{
	m_useList.clear();

	if(m_useList.size() > 0)
	{
		auto plant = m_useList.begin();
		while(plant != m_useList.end())
		{
			plant = m_useList.erase(plant);
		}
	}

	if(useList.size() > 0)
	{
		for(auto& i : useList)
		{
			m_useList.emplace_back(i);
		}
	}

	m_nTotalItem = m_useList.size();

	if(m_bStart)
	{
		InitPage();
		UpdatePage();
		UpdateListPiece();
	}
}

void CTRWorkshop_ListDlg::onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount)
{
	CNetClientManager::getInstance().requestGuild_getGuildContributionPoint(CNetClientManager::getInstance().getMyGuildNum());
	CNetClientManager::getInstance().requestCurrentTR();
	CTRRewardManager::getInstance().getReward(eRewardCondition_ITEM, iItemNum, 1, true);
	COkDialogEx::getInstance().showDialog(format("<NORMAL>%s</NORMAL>", _STR(ITEM_BUY_OK)));

	get<1>(m_useList[m_nSellItemIndex + (MAX_LISTPIECE * m_nCurPage)]).m_iBuyCount = iBuyCount;

	_updateGuildPointDialog();
}

void CTRWorkshop_ListDlg::onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR)
{
	if(0 > iGuildManagerTR)
	{
		iGuildManagerTR = 0;
	}

	m_iGuildManagerTR = iGuildManagerTR;

	_setStaticText(m_guildPointDlgID, "GuildManage_Point", format("%d", m_iGuildManagerTR));

	if(m_pWarehouseDlg && m_pWarehouseDlg->isVisible())
	{
		m_pWarehouseDlg->onRecvGuildPlantGetGuildManagerTR(iGuildManagerTR);
	}
}

void CTRWorkshop_ListDlg::onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR)
{
	if(m_pWarehouseDlg && m_pWarehouseDlg->isVisible())
	{
		m_pWarehouseDlg->onRecvGuildPlantInvestGuildManagerTR(iGuildManagerTR);
	}
}

void CTRWorkshop_ListDlg::onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue)
{
	if(m_pWarehouseDlg)
	{
		m_pWarehouseDlg->onRecvGuildPlantGetStorageExtendOK(iExtendCount, iExtendValue, iUserInvestCount, iUserInvestValue);
	}
}

void CTRWorkshop_ListDlg::onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList)
{
	if(m_pWarehouseDlg)
	{
		m_pWarehouseDlg->onRecvGuildPlantGetInvestorManagerTRListOK(userList);
	}
}

void CTRWorkshop_ListDlg::onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList)
{
	if(m_pExpenseDlg && m_pExpenseDlg->isVisible())
	{
		m_pExpenseDlg->onRecvGuildPlantGetExpenseListOK(pointType, iMonth, useList);
	}
}

void CTRWorkshop_ListDlg::InitName()
{
	InitGUIName({
		make_tuple<EGUIName, string>(EGUIName::GN_LISTBASE, "gui/Guild/Workshop/Workshop_ListBase.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_LISTDLG, "gui/Guild/Workshop/Workshop_ListDlg.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_LISTPIECE, "gui/Guild/Workshop/Workshop_ListPiece.gui"),
		});

	InitControlName(EControl::CONTROL_BUTTON,
		{
			// ListBase
			"Close",
			// ListDlg
			"PrevBtn","NextBtn",
			// ListPiece
			"BuyBtn"
		});

	InitControlName(EControl::CONTROL_FRAME,
		{
			// ListBase
			"Workshop_ListDlg"
		});

	InitControlName(EControl::CONTROL_STATICTEXT,
		{
			// ListDlg
			"PageNum",
			// ListPiece
			"GoodsName","limitedTime","Price"
		});

	InitControlName(EControl::CONTROL_IMAGECONTROL,
		{
			// ListPiece
			"Image","TrImg", "CashImg", "ImageCtrl"
		});
}

void CTRWorkshop_ListDlg::InitGUI()
{
	for(int i = 0; i < EGUIName::GN_END; i++)
	{
		switch(i)
		{
		case CTRWorkshop_ListDlg::GN_LISTBASE:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_LISTBASE], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->centerPosition();
				m_arrayDlg[i]->setModalDialog(true);
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
				CGUIManager::getInstance().setFocus(m_arrayDlg[i]->getControlID());
				m_arrayDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
			break;

		case CTRWorkshop_ListDlg::GN_LISTDLG:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_LISTDLG], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->setClientPos(m_arrayDlg[EGUIName::GN_LISTBASE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_WORKSHOP_LISTDLG], GUI_SUB_CONTROL_FRAME)->getScreenRect());
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
			}
			break;

		case CTRWorkshop_ListDlg::GN_LISTPIECE:
		case CTRWorkshop_ListDlg::GN_LISTPIECE02:
		case CTRWorkshop_ListDlg::GN_LISTPIECE03:
		case CTRWorkshop_ListDlg::GN_LISTPIECE04:
		case CTRWorkshop_ListDlg::GN_LISTPIECE05:
		case CTRWorkshop_ListDlg::GN_LISTPIECE06:
		case CTRWorkshop_ListDlg::GN_LISTPIECE07:
		case CTRWorkshop_ListDlg::GN_LISTPIECE08:
			int j = (GN_LISTPIECE08 - (GN_LISTPIECE08 - i)) - GN_LISTPIECE;
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_LISTPIECE], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->setClientPos(m_arrayDlg[EGUIName::GN_LISTDLG]->findControl("GoodsItem" + to_string(++j), GUI_SUB_CONTROL_FRAME)->getScreenRect());
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
				m_arrayDlg[i]->setVisible(true);
			}
			break;
		}
	}
}

void CTRWorkshop_ListDlg::InitButton()
{
	for(int i = 0; i < EButtonName::BN_END; i++)
	{
		switch(i)
		{
		case CTRWorkshop_ListDlg::BN_CLOSE:
			get<0>(m_arrayButton[i]) = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_CLOSE];
			get<1>(m_arrayButton[i]) = [&]()
			{
				closeDialog();
			};
			break;

		case CTRWorkshop_ListDlg::BN_PREVBTN:
			get<0>(m_arrayButton[i]) = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_PREVBTN];
			get<1>(m_arrayButton[i]) = [&]()
			{
				m_nCurPage = m_nCurPage > 0 ?
					[&]() {m_nCurPage--; UpdateListPiece(); return m_nCurPage; }() : m_nCurPage;
			};
			break;

		case CTRWorkshop_ListDlg::BN_NEXTBTN:
			get<0>(m_arrayButton[i]) = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_NEXTBTN];
			get<1>(m_arrayButton[i]) = [&]()
			{
				m_nCurPage = (m_nTotalPage > 0 && m_nCurPage < m_nTotalPage) ?
					[&]() {m_nCurPage++; UpdateListPiece(); return m_nCurPage; }() : m_nCurPage;
			};
			break;
		}
	}
}

void CTRWorkshop_ListDlg::InitStaticText()
{
	for(int i = 0; i <= EStaticTextName::SN_END; i++)
	{
		m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_LISTDLG]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][i], GUI_SUB_CONTROL_STATIC_TEXT));
	}
}

void CTRWorkshop_ListDlg::InitPage()
{
	m_nTotalPage = m_nTotalItem / MAX_LISTPIECE == 0 ? 0 : (m_nTotalItem / MAX_LISTPIECE);
	m_nTotalPage = m_nTotalItem % MAX_LISTPIECE == 0 ? m_nTotalPage - 1 : m_nTotalPage;
	m_nTotalPage = m_nTotalPage == -1 ? 0 : m_nTotalPage;
	m_nCurPage = 0;
}

void CTRWorkshop_ListDlg::InitListPiece()
{
	for(int i = 0; i < MAX_LISTPIECE; ++i)
	{
		// Button
		m_arrayListPiece[i].pButton = static_cast<CGUIButton*>(m_arrayDlg[EGUIName::GN_LISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_BUYBTN], GUI_SUB_CONTROL_IMAGE_BUTTON));
		m_arrayListPiece[i].pButton->setVisible(false);

		// ButtonEvent
		get<0>(m_arrayListPiece[i].arrayButton[SListPiece::BN_BUYBTN]) = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_BUYBTN];
		get<1>(m_arrayListPiece[i].arrayButton[SListPiece::BN_BUYBTN]) = [&](int index)
		{
			if(m_arrayListPiece[index].pButton->isMouseOver())
			{
				m_nSellNum = get<1>(m_useList[index + (MAX_LISTPIECE * m_nCurPage)]).m_iSellNum;
				m_nSellItemIndex = index;
				m_pYesNoDlg.showDialog(_STR(DICEBOARD_HUMONG_BUY_CONSUME), this, &CTRWorkshop_ListDlg::showGiveYes, nullptr);
			}
		};

		// StaticText
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_GOODSNAME] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_LISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_GOODSNAME], GUI_SUB_CONTROL_STATIC_TEXT));
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_GOODSNAME]->setVisible(false);

		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_PRICE] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_LISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_PRICE], GUI_SUB_CONTROL_STATIC_TEXT));
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_PRICE]->setVisible(false);

		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_LIMITEDTIME] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_LISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_LIMITEDTIME], GUI_SUB_CONTROL_STATIC_TEXT));
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_LIMITEDTIME]->setVisible(false);

		// ImageControl
		m_arrayListPiece[i].pItemImageCtrl = static_cast<CGUIItemImageCtrl*>(m_arrayDlg[EGUIName::GN_LISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::IN_IMAGE], GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
		m_arrayListPiece[i].pItemImageCtrl->setVisible(false);

		m_arrayListPiece[i].arrayImageCtrl[SListPiece::IN_TRIMG] = static_cast<CGUIImageCtrl*>(m_arrayDlg[EGUIName::GN_LISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::IN_TRIMG], GUI_SUB_CONTROL_IMAGE_CTRL));
		m_arrayListPiece[i].arrayImageCtrl[SListPiece::IN_TRIMG]->setVisible(false);

		m_arrayListPiece[i].arrayImageCtrl[SListPiece::IN_CASHIMG] = static_cast<CGUIImageCtrl*>(m_arrayDlg[EGUIName::GN_LISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::IN_CASHIMG], GUI_SUB_CONTROL_IMAGE_CTRL));
		m_arrayListPiece[i].arrayImageCtrl[SListPiece::IN_CASHIMG]->setVisible(false);

		m_arrayListPiece[i].arrayImageCtrl[SListPiece::IN_IMAGECTRL] = static_cast<CGUIImageCtrl*>(m_arrayDlg[EGUIName::GN_LISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::IN_IMAGECTRL], GUI_SUB_CONTROL_IMAGE_CTRL));
		m_arrayListPiece[i].arrayImageCtrl[SListPiece::IN_IMAGECTRL]->setVisible(false);
	}
}

void CTRWorkshop_ListDlg::UpdatePage()
{
	if(m_nTotalPage > 0)
	{
		if(m_nCurPage < m_nTotalPage)
		{
			m_nCurItem = MAX_LISTPIECE;
		}
		else
		{
			m_nCurItem = m_nTotalItem % MAX_LISTPIECE == 0 ? MAX_LISTPIECE : m_nTotalItem % MAX_LISTPIECE;
		}
	}
	else
	{
		m_nCurItem = m_nTotalItem % MAX_LISTPIECE == 0 ? MAX_LISTPIECE : m_nTotalItem % MAX_LISTPIECE;
	}

	if(m_arrayStaticText[EStaticTextName::SN_PAGENUM])
	{
		m_arrayStaticText[EStaticTextName::SN_PAGENUM]->setText(to_string(m_nCurPage + 1) + " / " + to_string(m_nTotalPage + 1));
	}
}

void CTRWorkshop_ListDlg::UpdateListPiece()
{
	UpdatePage();

	for(int i = 0; i < MAX_LISTPIECE; ++i)
	{
		if(m_arrayDlg[EGUIName::GN_LISTPIECE + i])
		{
			m_arrayDlg[EGUIName::GN_LISTPIECE + i]->setVisible(false);
		}
	}

	if(m_nTotalItem == 0)
	{
		return;
	}

	int j = 0;
	for(int i = 0; i < m_nCurItem; i++)
	{
		if(m_arrayDlg[EGUIName::GN_LISTPIECE + i])
		{
			m_arrayDlg[EGUIName::GN_LISTPIECE + i]->setClientPos(m_arrayDlg[EGUIName::GN_LISTDLG]->findControl("GoodsItem" + to_string(++j), GUI_SUB_CONTROL_FRAME)->getScreenRect());
			m_arrayDlg[EGUIName::GN_LISTPIECE + i]->setDialogListener(getCommandTargetID());
			m_arrayDlg[EGUIName::GN_LISTPIECE + i]->setVisible(true);
		}
		
		int iItemDescNum = m_nItemDescNum = get<1>(m_useList[i + (MAX_LISTPIECE * m_nCurPage)]).m_iItemDescNum;
		time_type tFinishDate = m_tFinishDate = get<1>(m_useList[i + (MAX_LISTPIECE * m_nCurPage)]).m_tFinishDate;
		const CItemInfoNode* pItemInfo = CClientItemList::getInstance().getRealItemInfo(iItemDescNum);

		// StaticText
		if(m_arrayListPiece[i].arrayStaticText[SListPiece::SN_GOODSNAME])
		{
			m_arrayListPiece[i].arrayStaticText[SListPiece::SN_GOODSNAME]->setText(pItemInfo->m_name);
			m_arrayListPiece[i].arrayStaticText[SListPiece::SN_GOODSNAME]->setVisible(true);
		}
		if(m_arrayListPiece[i].arrayStaticText[SListPiece::SN_PRICE])
		{
			switch(get<1>(m_useList[i + (MAX_LISTPIECE * m_nCurPage)]).m_pointType)
			{
			case eRewardCondition::eRewardCondition_PERSONAL_GUILD_POINT:
				m_arrayListPiece[i].arrayStaticText[SListPiece::SN_PRICE]->setText(to_string(get<1>(m_useList[i + (MAX_LISTPIECE * m_nCurPage)]).m_iPointValue) + " " + _STR(MONEY_MY_GP));
				break;

			case eRewardCondition::eRewardCondition_TRMONEY:
				m_arrayListPiece[i].arrayStaticText[SListPiece::SN_PRICE]->setText(to_string(get<1>(m_useList[i + (MAX_LISTPIECE * m_nCurPage)]).m_iPointValue) + " " + _STR(MONEY_TR));
				break;
			}
			m_arrayListPiece[i].arrayStaticText[SListPiece::SN_PRICE]->setVisible(true);
		}
		if(m_arrayListPiece[i].arrayStaticText[SListPiece::SN_LIMITEDTIME])
		{
			m_arrayListPiece[i].arrayStaticText[SListPiece::SN_LIMITEDTIME]->setText(GetSelectDay(get<0>(m_useList[i + (MAX_LISTPIECE * m_nCurPage)])));
			m_arrayListPiece[i].arrayStaticText[SListPiece::SN_LIMITEDTIME]->setVisible(true);
		}

		// ItemImage
		if(m_arrayListPiece[i].pItemImageCtrl)
		{
			m_arrayListPiece[i].pItemImageCtrl->setItemImage(iItemDescNum);
			m_arrayListPiece[i].pItemImageCtrl->setVisible(true);
		}

		m_arrayListPiece[i].pButton->setVisible(true);
	}
}

void CTRWorkshop_ListDlg::showGiveYes()
{
	int nMaxCount = get<1>(m_useList[m_nSellItemIndex + (MAX_LISTPIECE * m_nCurPage)]).m_iMaxCount;
	int iBuyCount = get<1>(m_useList[m_nSellItemIndex + (MAX_LISTPIECE * m_nCurPage)]).m_iBuyCount;
	if (nMaxCount != -1 && nMaxCount <= iBuyCount)
	{
		CTRShortTimeMessage::showMessage(_STR(COMBINATION_SHOP_OVER_LIMIT_USER_COUNT));
		return;
	}

	CNetClientManager::getInstance().requestBuyGuildPlantItem(m_nSellNum);
}

void CTRWorkshop_ListDlg::_setGuildPointDialog()
{
	std::string errmsg;

	CGUIDialog* pGuildPointDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_GuildPointDlg.gui", errmsg);
	if(nullptr == pGuildPointDlg)
	{
		return;
	}

	m_guildPointDlgID = pGuildPointDlg->getControlID();

	_setClientPos(m_arrayDlg[EGUIName::GN_LISTBASE]->getControlID(), m_guildPointDlgID, "Workshop_GuildPointDlg");
	pGuildPointDlg->setDialogListener(getCommandTargetID());
	pGuildPointDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
	_updateGuildPointDialog();
}

void CTRWorkshop_ListDlg::_updateGuildPointDialog()
{
	m_iGuildPoint = CNetClientManager::getInstance().getGuildInfo().m_iPoint;						// 길드 포인트
	m_iMyGuildPoint = CNetClientManager::getInstance().getMyGuildUserInfo().m_iContributionPoint;	// 마이 길드 포인트

	// 길드 운영 TR 요청
	CNetClientManager::getInstance().requestGetGuildPlantManagerTR(CNetClientManager::getInstance().getMyGuildNum());

	_setStaticText(m_guildPointDlgID, "Guild_Point", format("%d", m_iGuildPoint));
	_setStaticText(m_guildPointDlgID, "MyGuild_Point", format("%d", m_iMyGuildPoint));
}

void CTRWorkshop_ListDlg::_setStaticText(CGUIControlID ctrlID, const std::string & name, const std::string & message)
{
	CGUIControl* pCtrl = ctrlID.findControl();
	if(nullptr == pCtrl)
	{
		return;
	}

	CGUIStaticText* pText = static_cast<CGUIStaticText*>(pCtrl->findControl(name));
	if(pText)
	{
		pText->setText(message);
	}
}

void CTRWorkshop_ListDlg::_setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string & name)
{
	CGUIControl* pParentDialog = parentID.findControl();
	CGUIControl* pChildDialog = childID.findControl();
	if(nullptr == pParentDialog || nullptr == pChildDialog)
	{
		return;
	}

	CGUIControl* pFrame = pParentDialog->findControl(name);
	if(pFrame)
	{
		pChildDialog->setClientPos(pFrame->getScreenRect());
	}
}

void CTRWorkshop_ListDlg::LoadGuideList(CTRGuildPlanInfoLoader * pLoader)
{
	if(nullptr == m_pGuideDlg)
	{
		m_pGuideDlg = make_shared<CTRGuildWorkshop_GuideDlg>();
	}

	m_pGuideDlg->LoadGuideList(pLoader);
}
