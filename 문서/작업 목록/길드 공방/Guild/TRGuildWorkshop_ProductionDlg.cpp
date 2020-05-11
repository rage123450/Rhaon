#include "stdafx.h"
#include "TRGuildWorkshop_ProductionDlg.h"
//
#include "TRGuildWorkshop_RankDlg.h"
#include "TRGuildWorkshop_GiveDlg.h"
#include "TRGuildWorkshop_WarehouseDlg.h"
#include "TRGuildWorkshop_ExpenseDlg.h"
#include "TRGuildWorkshop_GuideDlg.h"

#include "NetClientManager.h"
#include "gui/GUIItemImageCtrl.h"
#include "gameui/ClientItemInfoLoader.h"
#include "gameui/TRShortTimeMessage.h"
#include "language/LanguageHeader.h"

CTRGuildWorkshop_ProductionDlg::CTRGuildWorkshop_ProductionDlg()
{
}

CTRGuildWorkshop_ProductionDlg::~CTRGuildWorkshop_ProductionDlg()
{
	closeDialog();
}

bool CTRGuildWorkshop_ProductionDlg::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	CGUIControl* pCtrl = ctrlID.findControl();
	if(pCtrl)
	{
		string name = pCtrl->getName();

		for_each(m_arrayButtonEvent.begin(), m_arrayButtonEvent.end(), [&](SButtonEvent var) {if(var.strName == name) var.funcEvent(); });

		for(int i = 0; i < m_arrayListPiece.size(); i++)
		{
			if(m_arrayListPiece[i].sButtonEvent.strName == name)
			{
				m_arrayListPiece[i].sButtonEvent.funcEvent2(i, get<1>(m_guildplant[i + (m_nCurPage * MAX_LISTPIECE)]));
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

void CTRGuildWorkshop_ProductionDlg::InitName()
{
	InitGUIName({
		make_tuple<EGUIName, string>(EGUIName::GN_PROGRESSBASE, "gui/Guild/Workshop/Workshop_ProgressBase.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_PROGRESSLISTDLG, "gui/Guild/Workshop/Workshop_ProgressListDlg.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_SELECTITEMDLG, "gui/Guild/Workshop/Workshop_SelectItemDlg.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_PROGRESSLISTPIECE, "gui/Guild/Workshop/Workshop_ProgressListPiece.gui"),
		});

	InitControlName(EControl::CONTROL_BUTTON,
		{
			// ProgressBase
			"Close", "GiveBtn", "ResetlBtn", "RankPopupBtn",
			// ProgressListDlg
			"PrevBtn", "NextBtn",
			// ProgressListPiece
			"GoodsBtn"
		});

	InitControlName(EControl::CONTROL_STATICTEXT,
		{
			// ProgressBase
			"NeedGuildPoint","Day", "Title", "MyPoint","NeedGuildPointPercent",
			// ProgressListDlg
			"PageNum",
			// ProgressListPiece
			"GoodsName","Day",
			// SelectItemDlg
			"GoodsName","Day","TypeMent"
		});

	InitControlName(EControl::CONTROL_FRAME,
		{
			// ProgressBase
			"Workshop_ProgressListDlg","Workshop_SelectItemDlg","Gauge",
			// ProgressListPiece
			"GoodsItem"
		});

	InitControlName(EControl::CONTROL_IMAGECONTROL,
		{
			// ProgressBase
			"GaugeImg","InBase",
			// ProgressListPiece
			"Image",
			// SelectItemDlg
			"Image"
		});
}

void CTRGuildWorkshop_ProductionDlg::InitGUI()
{
	string errmsg;

	for(int i = 0; i < EGUIName::GN_END; ++i)
	{
		switch(i)
		{
		case CTRGuildWorkshop_ProductionDlg::GN_PROGRESSBASE:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_PROGRESSBASE], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->centerPosition();
				m_arrayDlg[i]->setModalDialog(true);
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
				CGUIManager::getInstance().setFocus(m_arrayDlg[i]->getControlID());
				m_arrayDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
			break;

		case CTRGuildWorkshop_ProductionDlg::GN_PROGRESSLISTDLG:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_PROGRESSLISTDLG], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->setClientPos(m_arrayDlg[EGUIName::GN_PROGRESSBASE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_WORKSHOP_PROGRESSLISTDLG], GUI_SUB_CONTROL_FRAME)->getScreenRect());
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
			}
			break;

		case CTRGuildWorkshop_ProductionDlg::GN_SELECTITEMDLG:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_SELECTITEMDLG], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->setClientPos(m_arrayDlg[EGUIName::GN_PROGRESSBASE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_WORKSHOP_SELECTITEMDLG], GUI_SUB_CONTROL_FRAME)->getScreenRect());
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
				m_arrayDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
			break;

		case CTRGuildWorkshop_ProductionDlg::GN_PROGRESSLISTPIECE:
		case CTRGuildWorkshop_ProductionDlg::GN_PROGRESSLISTPIECE02:
		case CTRGuildWorkshop_ProductionDlg::GN_PROGRESSLISTPIECE03:
		case CTRGuildWorkshop_ProductionDlg::GN_PROGRESSLISTPIECE04:
		case CTRGuildWorkshop_ProductionDlg::GN_PROGRESSLISTPIECE05:
		case CTRGuildWorkshop_ProductionDlg::GN_PROGRESSLISTPIECE06:
		case CTRGuildWorkshop_ProductionDlg::GN_PROGRESSLISTPIECE07:
		case CTRGuildWorkshop_ProductionDlg::GN_PROGRESSLISTPIECE08:
			int j = (GN_PROGRESSLISTPIECE08 - (GN_PROGRESSLISTPIECE08 - i)) - GN_PROGRESSLISTPIECE;
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_PROGRESSLISTPIECE], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->setClientPos(m_arrayDlg[EGUIName::GN_PROGRESSLISTDLG]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_GOODSITEM] + to_string(++j), GUI_SUB_CONTROL_FRAME)->getScreenRect());
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
				m_arrayDlg[i]->setVisible(false);
			}
			break;
		}
	}

	m_pGiveDlg = m_pGiveDlg == nullptr ? make_shared<CTRGuildWorkshop_GiveDlg>() :
		[&]()
	{
		m_pGiveDlg = nullptr;
		return make_shared<CTRGuildWorkshop_GiveDlg>();
	}();

	m_pGiveBtn = static_cast<CGUIButton*>(m_arrayDlg[EGUIName::GN_PROGRESSBASE]->findControl(m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_GIVE], GUI_SUB_CONTROL_IMAGE_BUTTON));
	m_pGiveBtn->setVisible(false);
}

void CTRGuildWorkshop_ProductionDlg::InitButton()
{
	for(int i = 0; i < m_arrayButtonEvent.size(); i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_ProductionDlg::BN_CLOSE:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_CLOSE];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				closeDialog();
			};
			break;

		case CTRGuildWorkshop_ProductionDlg::BN_GIVE:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_GIVE];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				if(m_pGiveDlg && m_nItemDescNum != -1)
				{
					m_pGiveDlg->SetFinishDate(m_iFinishDate);
					m_pGiveDlg->SetGuildPlantMakeInfo(m_sGuildPlantMakeInfo);
					m_pGiveDlg->showDialog();
				}
			};
			break;

		case CTRGuildWorkshop_ProductionDlg::BN_RESETL:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_RESETL];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{ 
				if(m_guildplant.size() > 0)
				{
					CNetClientManager::getInstance().requestGetGuildPlantMakeStandbyItemList();
					CNetClientManager::getInstance().requestGetGuildPlantProgressItem();
					SetPage(0);
				}
			};
			break;
			
		case CTRGuildWorkshop_ProductionDlg::BN_RANKPOPUP:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_RANKPOPUP];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				if(m_nTotalItem == 0)
				{
					CTRShortTimeMessage::getInstance().showMessage(_STR(AUCTION_SYSTEM_NOT_SELECT_ITEM));
					return;
				}

				m_pRankDlg = m_pRankDlg == nullptr ? make_shared<CTRGuildWorkshop_RankDlg>() :
					[&]()
				{
					m_pRankDlg = nullptr;
					return make_shared<CTRGuildWorkshop_RankDlg>();
				}();
				m_pRankDlg->SetFinishDate(m_iFinishDate);
				m_pRankDlg->SetMakeProgressItem(m_tupleMakeProgressItem);
				m_pRankDlg->SetGuildPlantMakeInfo(m_sGuildPlantMakeInfo);
				m_pRankDlg->showDialog();
			};
			break;

		case CTRGuildWorkshop_ProductionDlg::BN_PREV:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_PREV];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				if(m_nCurPage > 0)
				{
					m_nCurPage--;

					UpdatePage();
					UpdateListPiece();
					UpdateCheckedButton(m_tupleChecked);
				}
			};
			break;

		case CTRGuildWorkshop_ProductionDlg::BN_NEXT:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_NEXT];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				if(m_nTotalPage > 0 && m_nCurPage < m_nTotalPage)
				{
					m_nCurPage++;

					UpdatePage();
					UpdateListPiece();
					UpdateCheckedButton(m_tupleChecked);
				}
			};
			break;
		}
	}
}

void CTRGuildWorkshop_ProductionDlg::InitImageControl()
{
	m_arrayImageControl[EImageControlName::ICN_GAUGEIMG] = static_cast<CGUIImageCtrl*>(m_arrayDlg[EGUIName::GN_PROGRESSBASE]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::ICN_GAUGEIMG], GUI_SUB_CONTROL_IMAGE_CTRL));
	m_arrayImageControl[EImageControlName::ICN_INBASE] = static_cast<CGUIImageCtrl*>(m_arrayDlg[EGUIName::GN_PROGRESSBASE]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::ICN_INBASE], GUI_SUB_CONTROL_IMAGE_CTRL));

	m_pSelectItemImageCtrl = static_cast<CGUIItemImageCtrl*>(m_arrayDlg[EGUIName::GN_SELECTITEMDLG]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::ICN_SELECTDLG_IMAGE], GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
}

void CTRGuildWorkshop_ProductionDlg::InitStaticText()
{
	// ProgressBase
	m_arrayStaticText[EStaticTextName::STN_NEEDGUILDPOINT] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_PROGRESSBASE]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::STN_NEEDGUILDPOINT], GUI_SUB_CONTROL_STATIC_TEXT));
	m_arrayStaticText[EStaticTextName::STN_DAY] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_PROGRESSBASE]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::STN_DAY], GUI_SUB_CONTROL_STATIC_TEXT));
	m_arrayStaticText[EStaticTextName::STN_MYPOINT] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_PROGRESSBASE]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::STN_MYPOINT], GUI_SUB_CONTROL_STATIC_TEXT));
	m_arrayStaticText[EStaticTextName::STN_NEEDGUILDPOINTPERCENT] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_PROGRESSBASE]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::STN_NEEDGUILDPOINTPERCENT], GUI_SUB_CONTROL_STATIC_TEXT));

	// ProgressListDlg
	m_arrayStaticText[EStaticTextName::STN_PAGENUM] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_PROGRESSLISTDLG]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::STN_PAGENUM], GUI_SUB_CONTROL_STATIC_TEXT));

	// SelectItemDlg
	m_arrayStaticText[EStaticTextName::STN_SELECTITEM_GOODSNAME] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_SELECTITEMDLG]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::STN_SELECTITEM_GOODSNAME], GUI_SUB_CONTROL_STATIC_TEXT));
	m_arrayStaticText[EStaticTextName::STN_SELECTITEM_GOODSNAME]->setVisible(false);

	m_arrayStaticText[EStaticTextName::STN_SELECTITEM_DAY] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_SELECTITEMDLG]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::STN_SELECTITEM_DAY], GUI_SUB_CONTROL_STATIC_TEXT));
	m_arrayStaticText[EStaticTextName::STN_SELECTITEM_DAY]->setVisible(false);

	m_arrayStaticText[EStaticTextName::STN_SELECTITEM_TYPEMENT] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_SELECTITEMDLG]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::STN_SELECTITEM_TYPEMENT], GUI_SUB_CONTROL_STATIC_TEXT));
	m_arrayStaticText[EStaticTextName::STN_SELECTITEM_TYPEMENT]->setVisible(false);
}

void CTRGuildWorkshop_ProductionDlg::InitFrame()
{
	for(int i = 0; i < m_arrayFrame.size(); i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_ProductionDlg::FN_WORKSHOP_PROGRESSLISTDLG:
			m_arrayFrame[i] = static_cast<CGUIFrameImage*>(m_arrayDlg[EGUIName::GN_PROGRESSBASE]
				->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_WORKSHOP_PROGRESSLISTDLG], GUI_SUB_CONTROL_FRAME));
			break;

		case CTRGuildWorkshop_ProductionDlg::FN_WORKSHOP_SELECTITEMDLG:
			m_arrayFrame[i] = static_cast<CGUIFrameImage*>(m_arrayDlg[EGUIName::GN_PROGRESSBASE]
				->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_WORKSHOP_SELECTITEMDLG], GUI_SUB_CONTROL_FRAME));
			break;

		case CTRGuildWorkshop_ProductionDlg::FN_WORKSHOP_GAUGE:
			m_arrayFrame[i] = static_cast<CGUIFrameImage*>(m_arrayDlg[EGUIName::GN_PROGRESSBASE]
				->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_WORKSHOP_GAUGE], GUI_SUB_CONTROL_FRAME));
			break;
		}
	}
}

void CTRGuildWorkshop_ProductionDlg::showDialog()
{
	__super::showDialog();

	m_bStart = true;

	CNetClientManager::getInstance().requestGetGuildPlantMakeStandbyItemList();
	CNetClientManager::getInstance().requestGetGuildPlantProgressItem();

	InitListPiece();

	InitPage();

	UpdatePage();

	UpdateListPiece();
	
	InitSelectDlg();

	InitCheckedButton();

	_setGuildPointDialog();
}

void CTRGuildWorkshop_ProductionDlg::closeDialog()
{
	m_bStart = false;

	m_yesNoChangeDlg.closeDialog();

	if(m_pRankDlg)
	{
		m_pRankDlg->closeDialog();
	}

	if(m_pGiveDlg)
	{
		m_pGiveDlg->closeDialog();
	}

	for(int i = 0; i < m_arrayListPiece.size(); i++)
	{
		for(int j = 0; i < m_arrayListPiece[i].arrayItemImageCtrl.size(); i++)
		{
			m_arrayListPiece[i].arrayItemImageCtrl[j] = nullptr;
		}

		for(int j = 0; i < m_arrayListPiece[i].arrayStaticText.size(); i++)
		{
			m_arrayListPiece[i].arrayStaticText[j] = nullptr;
		}
		m_arrayListPiece[i].pButton = nullptr;
	}

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

void CTRGuildWorkshop_ProductionDlg::onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant)
{
	m_guildplant.clear();

	if (m_guildplant.size() > 0)
	{
		auto plant = m_guildplant.begin();
		while (plant != m_guildplant.end())
		{
			plant = m_guildplant.erase(plant);
		}
	}

	if(guildplant.size() > 0)
	{
		for(auto& iter : guildplant)
		{
			m_guildplant.emplace_back(make_tuple(iter.first, iter.second));
		}
	}

	m_nTotalItem = m_guildplant.size();

	if(m_bStart)
	{
		InitPage();
		UpdatePage();
		UpdateListPiece();
	}
}

void CTRGuildWorkshop_ProductionDlg::onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList)
{
	if(m_pGiveDlg)
	{
		m_pGiveDlg->onRecvGuildPlantGetGivePossibleUserListOK(userList);
	}
}

void CTRGuildWorkshop_ProductionDlg::onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList)
{
	if(m_pRankDlg)
	{
		m_pRankDlg->onRecvGuildPlantGetItemContributeRankLIstOK(userList);
	}
}

void CTRGuildWorkshop_ProductionDlg::onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind)
{
	if(!m_bStart)
	{
		return;
	}

	if(guildplantMakeInfo.m_iItemIndexNum == 0)
	{
		guildplantMakeInfo.m_iAccumulatePoint = 0;
		guildplantMakeInfo.m_iNeedPoint = 0;
		iMyContributionPoint = 0;
	}

	m_tupleMakeProgressItem = make_tuple(guildplantMakeInfo, iMyContributionPoint, distributeKind);

	int nCurPageNum = 0;
	int nCurItemNum = 0;
	int nCheckItem = 0;
	for(int i = 0; i < m_guildplant.size(); i++)
	{
		if(get<1>(m_guildplant[i]).m_iItemIndexNum == guildplantMakeInfo.m_iItemIndexNum)
		{
			nCurPageNum = i / MAX_LISTPIECE;
			nCurItemNum = i % MAX_LISTPIECE;
			nCheckItem = i;
			break;
		}
	}

	m_tupleChecked = make_tuple(nCurPageNum, nCurItemNum);

	UpdateSelectDlg(get<1>(m_guildplant[nCheckItem]), nCheckItem);
	InitMyPoint(get<1>(m_tupleMakeProgressItem));
	InitCheckedButton();
}

void CTRGuildWorkshop_ProductionDlg::onRecvGuildPlantGiveGiftOK(int iItemIndexNum)
{
	ClearSelectDlg();
}

void CTRGuildWorkshop_ProductionDlg::onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum)
{
	m_tupleChecked = make_tuple(iItemIndexNum / MAX_LISTPIECE, iItemIndexNum % MAX_LISTPIECE);
}

void CTRGuildWorkshop_ProductionDlg::onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR)
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

void CTRGuildWorkshop_ProductionDlg::onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR)
{
	if(m_pWarehouseDlg && m_pWarehouseDlg->isVisible())
	{
		m_pWarehouseDlg->onRecvGuildPlantInvestGuildManagerTR(iGuildManagerTR);
	}
}

void CTRGuildWorkshop_ProductionDlg::onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue)
{
	if(m_pWarehouseDlg)
	{
		m_pWarehouseDlg->onRecvGuildPlantGetStorageExtendOK(iExtendCount, iExtendValue, iUserInvestCount, iUserInvestValue);
	}
}

void CTRGuildWorkshop_ProductionDlg::onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList)
{
	if(m_pWarehouseDlg)
	{
		m_pWarehouseDlg->onRecvGuildPlantGetInvestorManagerTRListOK(userList);
	}
}

void CTRGuildWorkshop_ProductionDlg::onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList)
{
	if(m_pExpenseDlg && m_pExpenseDlg->isVisible())
	{
		m_pExpenseDlg->onRecvGuildPlantGetExpenseListOK(pointType, iMonth, useList);
	}
}

void CTRGuildWorkshop_ProductionDlg::InitListPiece()
{
	for(int i = 0; i < MAX_LISTPIECE; i++)
	{
		// StaticText
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_GOODSNAME] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_PROGRESSLISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::STN_LISTPIECE_GOODSNAME], GUI_SUB_CONTROL_STATIC_TEXT));
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_DAY] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_PROGRESSLISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::STN_LISTPIECE_DAY], GUI_SUB_CONTROL_STATIC_TEXT));

		// ImageControl
		m_arrayListPiece[i].arrayItemImageCtrl[SListPiece::IN_IMAGE] = static_cast<CGUIItemImageCtrl*>(m_arrayDlg[EGUIName::GN_PROGRESSLISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::ICN_LISTPIECE_IMAGE], GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));

		// Button
		m_arrayListPiece[i].pButton = static_cast<CGUIButton*>(m_arrayDlg[EGUIName::GN_PROGRESSLISTPIECE + i]->findControl(m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_GOODS], GUI_SUB_CONTROL_IMAGE_BUTTON));

		// ButtonEvent
		m_arrayListPiece[i].sButtonEvent.strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_GOODS];
		m_arrayListPiece[i].sButtonEvent.funcEvent2 = [&](int index, GuildPlantMakeInfo& temp)
		{
			if(m_arrayListPiece[index].pButton->isMouseOver())
			{
				int nCurItemIndexNum = get<0>(m_tupleChecked)*MAX_LISTPIECE + get<1>(m_tupleChecked);
				m_nChangeItemIndexNum = index + (m_nCurPage*MAX_LISTPIECE);

				if(nCurItemIndexNum != m_nChangeItemIndexNum)
				{
					m_yesNoChangeDlg.showDialog(_STR(GUILD_PLANT_MAKEITEM_CHANGE), this, &CTRGuildWorkshop_ProductionDlg::showChangeYes, nullptr);
				}
			}
		};
	}
}

void CTRGuildWorkshop_ProductionDlg::InitSelectDlg(int _nIndex)
{
	InitNeedGuildPoint(0, 0);
	InitMyPoint(0);
	InitSelectDay(0);
}

void CTRGuildWorkshop_ProductionDlg::InitNeedGuildPoint(int _nCurNeedGuildPoint, int _nMaxNeedGuildPoint)
{
	if(m_arrayStaticText[EStaticTextName::STN_NEEDGUILDPOINT])
	{
		m_arrayStaticText[EStaticTextName::STN_NEEDGUILDPOINT]->setText(to_string(_nCurNeedGuildPoint) + m_strPageNumSign + to_string(_nMaxNeedGuildPoint) + _STR(MONEY_GP));
	}

	InitNeedGuildPointPercent(_nCurNeedGuildPoint, _nMaxNeedGuildPoint);
}

void CTRGuildWorkshop_ProductionDlg::InitNeedGuildPointPercent(int _nCurNeedGuildPoint, int _nMaxNeedGuildPoint)
{
	if(m_arrayStaticText[EStaticTextName::STN_NEEDGUILDPOINTPERCENT])
	{
		int nPercent = _nMaxNeedGuildPoint != 0 ? (_nCurNeedGuildPoint * 100) / _nMaxNeedGuildPoint : 0;
		nPercent = nPercent > 100 ? 100 : nPercent;
		m_arrayStaticText[EStaticTextName::STN_NEEDGUILDPOINTPERCENT]->setText(to_string(nPercent) + "%");

		SettingGaugeImg(nPercent);
	}
}

void CTRGuildWorkshop_ProductionDlg::InitSelectDay(time_type _nDurationDay, bool _bComplete)
{
	if(m_arrayStaticText[EStaticTextName::STN_DAY])
	{
		m_arrayStaticText[EStaticTextName::STN_DAY]->setVisible(true);
		m_arrayStaticText[EStaticTextName::STN_DAY]->setText(format("%s : %s", _STR(PRODUCTION_PERIOD), GetSelectDay(_bComplete ? 0 : _nDurationDay).c_str()));
	}
}

void CTRGuildWorkshop_ProductionDlg::InitMyPoint(int _nMyPoint)
{
	if(m_arrayStaticText[EStaticTextName::STN_MYPOINT])
	{
		m_arrayStaticText[EStaticTextName::STN_MYPOINT]->setText(to_string(_nMyPoint) +_STR(MONEY_GP));
	}
}

void CTRGuildWorkshop_ProductionDlg::InitPage()
{
	m_nTotalPage = m_nTotalItem / MAX_LISTPIECE == 0 ? 0 : (m_nTotalItem / MAX_LISTPIECE);
	m_nTotalPage = m_nTotalItem % MAX_LISTPIECE == 0 ? m_nTotalPage - 1 : m_nTotalPage;
	m_nTotalPage = m_nTotalPage == -1 ? 0 : m_nTotalPage;
	m_nCurPage = 0;
}

void CTRGuildWorkshop_ProductionDlg::InitCheckedButton()
{
	for(int i = 0; i < m_arrayListPiece.size(); i++)
	{
		if(m_arrayListPiece[i].pButton)
		{
			m_arrayListPiece[i].pButton->setChecked(false);
		}
	}

	if(m_arrayListPiece[get<1>(m_tupleChecked)].pButton && get<0>(m_tupleChecked) == m_nCurPage)
	{
		m_arrayListPiece[get<1>(m_tupleChecked)].pButton->setChecked(true);
	}
}

void CTRGuildWorkshop_ProductionDlg::UpdateSelectDlg(GuildPlantMakeInfo& temp, int _nIndex)
{
	if(m_nTotalItem == 0)
	{
		ClearSelectDlg();
		return;
	}

	if(m_arrayDlg[EGUIName::GN_SELECTITEMDLG])
	{
		m_sGuildPlantMakeInfo = get<1>(m_guildplant[_nIndex]);

		int nItemDescNum = m_nItemDescNum = get<0>(m_guildplant[_nIndex]);
		const CItemInfoNode* pItemInfo = CClientItemList::getInstance().getRealItemInfo(nItemDescNum);

		m_pSelectItemImageCtrl->setItemImage(nItemDescNum);

		m_arrayStaticText[EStaticTextName::STN_SELECTITEM_GOODSNAME]->setText(pItemInfo->m_name);
		m_arrayStaticText[EStaticTextName::STN_SELECTITEM_GOODSNAME]->setVisible(true);

		time_type tFinishDate = m_iFinishDate = get<1>(m_guildplant[_nIndex]).m_tFinishDate;
		bool bFinish = temp.m_iAccumulatePoint >= temp.m_iNeedPoint ? true : false;

		m_arrayStaticText[EStaticTextName::STN_SELECTITEM_DAY]->setText(GetSelectDay(bFinish ? 0 : tFinishDate));
		m_arrayStaticText[EStaticTextName::STN_SELECTITEM_DAY]->setVisible(true);

		switch(m_sGuildPlantMakeInfo.m_guildPlantDistributeKind)
		{
		case eGuildPlantDistributeKind_NONE:
			break;
		case eGuildPlantDistributeKind_GIFT_MASTER:
			m_arrayStaticText[EStaticTextName::STN_SELECTITEM_TYPEMENT]->setText(_STR(GUILD_PLANT_DISTRIBUTE_KIND_4));
			break;
		case eGuildPlantDistributeKind_SELL_DAY7:
			m_arrayStaticText[EStaticTextName::STN_SELECTITEM_TYPEMENT]->setText(_STR(GUILD_PLANT_DISTRIBUTE_KIND_3));
			break;
		case eGuildPlantDistributeKind_SELL_DAY15:
			m_arrayStaticText[EStaticTextName::STN_SELECTITEM_TYPEMENT]->setText(_STR(GUILD_PLANT_DISTRIBUTE_KIND_2));
			break;
		case eGuildPlantDistributeKind_SELL_DAY30:
			m_arrayStaticText[EStaticTextName::STN_SELECTITEM_TYPEMENT]->setText(_STR(GUILD_PLANT_DISTRIBUTE_KIND_1));
			break;
		case eGuildPlantDistributeKind_SELL_FOREVER:
			m_arrayStaticText[EStaticTextName::STN_SELECTITEM_TYPEMENT]->setText(_STR(GUILD_PLANT_DISTRIBUTE_KIND_5));
			break;
		}
		m_arrayStaticText[EStaticTextName::STN_SELECTITEM_TYPEMENT]->setVisible(true);

		if(m_pGiveBtn)
		{
			m_pGiveBtn->setVisible(IsMyGuildGradeMaster() && IsSelectCompleteMakeItem() ? true : false);
		}
	}

	InitNeedGuildPoint(temp.m_iAccumulatePoint, temp.m_iNeedPoint);

	bool m_bComplete = temp.m_iAccumulatePoint >= temp.m_iNeedPoint ? true : false;

	InitSelectDay(temp.m_tFinishDate, m_bComplete);
}

void CTRGuildWorkshop_ProductionDlg::UpdateListPiece()
{
	for(int i = 0; i < MAX_LISTPIECE; ++i)
	{
		if(m_arrayDlg[EGUIName::GN_PROGRESSLISTPIECE + i])
		{
			m_arrayDlg[EGUIName::GN_PROGRESSLISTPIECE + i]->setVisible(false);
		}
	}

	if(m_nTotalItem == 0)
	{
		return;
	}

	int j = 0;
	for(int i = 0; i < m_nCurItem; ++i)
	{
		if(m_arrayDlg[EGUIName::GN_PROGRESSLISTPIECE + i])
		{
			m_arrayDlg[EGUIName::GN_PROGRESSLISTPIECE + i]->setClientPos(m_arrayDlg[EGUIName::GN_PROGRESSLISTDLG]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_GOODSITEM] + to_string(++j), GUI_SUB_CONTROL_FRAME)->getScreenRect());
			m_arrayDlg[EGUIName::GN_PROGRESSLISTPIECE + i]->setDialogListener(getCommandTargetID());
			m_arrayDlg[EGUIName::GN_PROGRESSLISTPIECE + i]->setVisible(true);
		}

		int nItemDescNum = m_nItemDescNum = get<0>(m_guildplant[i + (m_nCurPage*MAX_LISTPIECE)]);
		time_type tFinishDate = m_iFinishDate = get<1>(m_guildplant[i + (m_nCurPage*MAX_LISTPIECE)]).m_tFinishDate;
		int iAccumulatePoint = get<1>(m_guildplant[i + (m_nCurPage*MAX_LISTPIECE)]).m_iAccumulatePoint;
		int iNeedPoint = get<1>(m_guildplant[i + (m_nCurPage*MAX_LISTPIECE)]).m_iNeedPoint;

		const CItemInfoNode* pItemInfo = CClientItemList::getInstance().getItemInfo(nItemDescNum);

		if(m_arrayListPiece[i].arrayItemImageCtrl[SListPiece::IN_IMAGE])
		{
			m_arrayListPiece[i].arrayItemImageCtrl[SListPiece::IN_IMAGE]->setItemImage(pItemInfo->m_iUniqueNumber);
		}

		if(m_arrayListPiece[i].arrayStaticText[SListPiece::SN_GOODSNAME])
		{
			m_arrayListPiece[i].arrayStaticText[SListPiece::SN_GOODSNAME]->setText(pItemInfo->m_name);
		}

		if(m_arrayListPiece[i].arrayStaticText[SListPiece::SN_DAY])
		{
			bool bFinish = iAccumulatePoint >= iNeedPoint ? true : false;

			m_arrayListPiece[i].arrayStaticText[SListPiece::SN_DAY]->setText(GetSelectDay(bFinish ? 0 : tFinishDate));
		}
	}
}

void CTRGuildWorkshop_ProductionDlg::UpdatePage()
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

	m_arrayStaticText[EStaticTextName::STN_PAGENUM]->setText(to_string(m_nCurPage + 1) + m_strPageNumSign + to_string(m_nTotalPage + 1));
}

void CTRGuildWorkshop_ProductionDlg::UpdateCheckedButton(tuple<int, int> _tupleChecked)
{
	if(get<0>(_tupleChecked) == m_nCurPage)
	{
		m_arrayListPiece[get<1>(m_tupleChecked)].pButton->setChecked(false);
		m_arrayListPiece[get<1>(_tupleChecked)].pButton->setChecked(true);
		m_tupleChecked = _tupleChecked;
	}
	else
	{
		for(int i = 0; i < m_nCurItem; i++)
		{
			m_arrayListPiece[i].pButton->setChecked(false);
		}
	}
}

void CTRGuildWorkshop_ProductionDlg::ClearSelectDlg()
{
	InitNeedGuildPoint(0, 0);
	InitMyPoint(0);
	InitSelectDay(0);

	if(m_arrayDlg[EGUIName::GN_SELECTITEMDLG])
	{
		m_pSelectItemImageCtrl->setItemImage(NULL);

		m_arrayStaticText[EStaticTextName::STN_SELECTITEM_GOODSNAME]->setText("");
		m_arrayStaticText[EStaticTextName::STN_SELECTITEM_GOODSNAME]->setVisible(true);

		m_arrayStaticText[EStaticTextName::STN_SELECTITEM_DAY]->setText("");
		m_arrayStaticText[EStaticTextName::STN_SELECTITEM_DAY]->setVisible(false);

		m_arrayStaticText[EStaticTextName::STN_SELECTITEM_TYPEMENT]->setText("");
		m_arrayStaticText[EStaticTextName::STN_SELECTITEM_TYPEMENT]->setVisible(false);

		if(m_pGiveBtn)
		{
			m_pGiveBtn->setVisible(IsMyGuildGradeMaster() && IsSelectCompleteMakeItem() ? true : false);
		}
	}
}

void CTRGuildWorkshop_ProductionDlg::showChangeYes()
{
	if(m_guildplant.size() > 0)
	{
		CNetClientManager::getInstance().requestChangeGuildPlantMyContributionPointMakeItem(get<1>(m_guildplant[m_nChangeItemIndexNum]).m_iItemIndexNum);
		CNetClientManager::getInstance().requestGetGuildPlantProgressItem();
	}
}

void CTRGuildWorkshop_ProductionDlg::SettingGaugeImg(int _nPercent)
{
	if(m_arrayImageControl[EImageControlName::ICN_GAUGEIMG])
	{
		CRectInfo rt = m_arrayFrame[EFrameName::FN_WORKSHOP_GAUGE]->getClientRect();
		m_arrayImageControl[EImageControlName::ICN_GAUGEIMG]->setClientPos(CRectInfo(rt.left, rt.top, rt.left + (rt.width() * _nPercent / 100), rt.bottom));
	}
}

void CTRGuildWorkshop_ProductionDlg::SetPage(int _nPageNum)
{
	if(_nPageNum >= 0 && _nPageNum <= m_nTotalPage)
	{
		m_nCurPage = _nPageNum;
		UpdatePage();
		UpdateListPiece();
	}
}

void CTRGuildWorkshop_ProductionDlg::LoadGuideList(CTRGuildPlanInfoLoader * pLoader)
{
	if(nullptr == m_pGuideDlg)
	{
		m_pGuideDlg = make_shared<CTRGuildWorkshop_GuideDlg>();
	}

	m_pGuideDlg->LoadGuideList(pLoader);
}

bool CTRGuildWorkshop_ProductionDlg::IsMyGuildGradeMaster()
{
	GuildUserInfo myGuildUserInfo = CNetClientManager::getInstance().getMyGuildUserInfo();

	if(eGuildMemberGrade_MASTER != myGuildUserInfo.m_eGrade && eGuildMemberGrade_SUBMASTER != myGuildUserInfo.m_eGrade)
	{
		return false;
	}

	return true;
}

bool CTRGuildWorkshop_ProductionDlg::IsSelectCompleteMakeItem()
{
	return 	m_sGuildPlantMakeInfo.m_iAccumulatePoint >= m_sGuildPlantMakeInfo.m_iNeedPoint ? true : false;
}

void CTRGuildWorkshop_ProductionDlg::DummyInitData(int _nNum)
{
	m_guildplant.clear();

	for(int i = 0; i < _nNum; i++)
	{
		GuildPlantMakeInfo temp;
		temp.m_iItemIndexNum = 2;
		temp.m_iItemDescNum = 85098;
		temp.m_iNeedPoint = 3000;
		temp.m_iAccumulatePoint = i;
		temp.m_tFinishDate = 0;

		m_guildplant.emplace_back(make_tuple(temp.m_iItemDescNum, temp));
	}
}

void CTRGuildWorkshop_ProductionDlg::_setGuildPointDialog()
{
	std::string errmsg;

	CGUIDialog* pGuildPointDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_GuildPointDlg.gui", errmsg);
	if(nullptr == pGuildPointDlg)
	{
		return;
	}

	m_guildPointDlgID = pGuildPointDlg->getControlID();
	
	_setClientPos(m_arrayDlg[EGUIName::GN_PROGRESSBASE]->getControlID(), m_guildPointDlgID, "Workshop_GuildPointDlg");
	pGuildPointDlg->setDialogListener(getCommandTargetID());
	pGuildPointDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
	_updateGuildPointDialog();
}

void CTRGuildWorkshop_ProductionDlg::_updateGuildPointDialog()
{
	m_iGuildPoint = CNetClientManager::getInstance().getGuildInfo().m_iPoint;						// 길드 포인트
	m_iMyGuildPoint = CNetClientManager::getInstance().getMyGuildUserInfo().m_iContributionPoint;	// 마이 길드 포인트

	// 길드 운영 TR 요청
	CNetClientManager::getInstance().requestGetGuildPlantManagerTR(CNetClientManager::getInstance().getMyGuildNum());

	_setStaticText(m_guildPointDlgID, "Guild_Point", format("%d", m_iGuildPoint));
	_setStaticText(m_guildPointDlgID, "MyGuild_Point", format("%d", m_iMyGuildPoint));
}

void CTRGuildWorkshop_ProductionDlg::_setStaticText(CGUIControlID ctrlID, const std::string & name, const std::string & message)
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

void CTRGuildWorkshop_ProductionDlg::_setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string & name)
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
