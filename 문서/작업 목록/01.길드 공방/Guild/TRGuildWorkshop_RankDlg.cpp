#include "stdafx.h"
#include "TRGuildWorkshop_RankDlg.h"
//
#include "NetClientManager.h"
#include "gui/GUIItemImageCtrl.h"
#include "gameui/ClientItemInfoLoader.h"
#include "gameui/TRShortTimeMessage.h"
#include "language/LanguageHeader.h"

CTRGuildWorkshop_RankDlg::CTRGuildWorkshop_RankDlg()
{
}

CTRGuildWorkshop_RankDlg::~CTRGuildWorkshop_RankDlg()
{
	closeDialog();
}

void CTRGuildWorkshop_RankDlg::showDialog()
{
	__super::showDialog();

	m_bStart = true;

	CNetClientManager::getInstance().requestGetGuildPlantItemContributeRankList(m_sGuildPlantMakeInfo.m_iItemIndexNum);

	InitListPiece();

	InitPage();

	InitSelectDlg();
}

void CTRGuildWorkshop_RankDlg::closeDialog()
{
	m_bStart = false;

	for(int i = 0; i < ERank::END; ++i)
	{
		if(m_arrDlg[i])
		{
			m_arrDlg[i]->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
			m_arrDlg[i] = nullptr;
		}
	}
}

void CTRGuildWorkshop_RankDlg::onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList)
{
	if(userList.size() > 0)
	{
		for(auto& i : userList)
		{
			m_userList.emplace_back(i);
		}
		sort(m_userList.begin(), m_userList.end(),
			[&](tuple<int, string> _a, tuple<int, string> _b)
		{
			return get<0>(_a) > get<0>(_b);
		});
		m_nTotalNickName = m_userList.size();
	}

	if(m_bStart)
	{
// 		UpdatePage();
// 		UpdateListPiece();
		InitPage();
	}
}

bool CTRGuildWorkshop_RankDlg::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	string name;

	CGUIControl* pCtrl = ctrlID.findControl();
	if(pCtrl)
	{
		name = pCtrl->getName();
		for each (SButtonEvent var in m_arrayButtonEvent)
		{
			if(var.strName == name)
			{
				var.funcEvent();
			}
		}
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRGuildWorkshop_RankDlg::InitName()
{
	InitGUIName({
		make_tuple<EGUIName, string>(EGUIName::GN_RANKPOPUP, "gui/Guild/Workshop/Workshop_RankPopup.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_RANK_LIST, "gui/Guild/Workshop/Workshop_Rank_List.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_RANK_LISTPIECE, "gui/Guild/Workshop/Workshop_Rank_ListPiece.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_SELECTITEMDLG, "gui/Guild/Workshop/Workshop_SelectItemDlg.gui"),
		});

	InitControlName(EControl::CONTROL_BUTTON,
		{
			// RankPopup
			"Close",
			// Rank_List
			"PrevBtn","NextBtn"
		});

	InitControlName(EControl::CONTROL_STATICTEXT,
		{
			// Rank_List
			"PageNum",
			// Rank_ListPiece
			"Name","Point","RankNum",
			// SelectItemDlg
			"GoodsName","Day","TypeMent"
		});

	InitControlName(EControl::CONTROL_FRAME,
		{
			// RankPopup
			"Workshop_Rank_List",
			"Workshop_SelectItemDlg"
		});

	InitControlName(EControl::CONTROL_IMAGECONTROL,
		{
			// SelectItemDlg
			"Image"
		});
}

void CTRGuildWorkshop_RankDlg::InitGUI()
{
	string errmsg;

	for(int i = 0; i < ERank::END; ++i)
	{
		switch(i)
		{
		case CTRGuildWorkshop_RankDlg::RANK_BASE:
			m_arrDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_RANKPOPUP], errmsg);
			if(m_arrDlg[i])
			{
				m_arrDlg[i]->centerPosition();
				m_arrDlg[i]->setModalDialog(true);
				m_arrDlg[i]->setDialogListener(getCommandTargetID());
				CGUIManager::getInstance().setFocus(m_arrDlg[i]->getControlID());
				m_arrDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
			break;

		case CTRGuildWorkshop_RankDlg::RANK_LIST:
			m_arrDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_RANK_LIST], errmsg);
			if(m_arrDlg[i])
			{
				m_arrDlg[i]->setClientPos(m_arrDlg[ERank::RANK_BASE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_WORKSHOP_RANK_LIST], GUI_SUB_CONTROL_FRAME)->getScreenRect());
				m_arrDlg[i]->setDialogListener(getCommandTargetID());
				m_arrDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
			break;

		case CTRGuildWorkshop_RankDlg::RANK_LISTPIECE01:
		case CTRGuildWorkshop_RankDlg::RANK_LISTPIECE02:
		case CTRGuildWorkshop_RankDlg::RANK_LISTPIECE03:
		case CTRGuildWorkshop_RankDlg::RANK_LISTPIECE04:
		case CTRGuildWorkshop_RankDlg::RANK_LISTPIECE05:
		case CTRGuildWorkshop_RankDlg::RANK_LISTPIECE06:
		{
			int j = (RANK_LISTPIECE06 - (RANK_LISTPIECE06 - i)) - RANK_LISTPIECE01;
			m_arrDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_RANK_LISTPIECE], errmsg);
			if(m_arrDlg[i])
			{
				m_arrDlg[i]->setClientPos(m_arrDlg[ERank::RANK_LIST]->findControl("Rank_ListPiece" + to_string(++j), GUI_SUB_CONTROL_FRAME)->getScreenRect());
				m_arrDlg[i]->setDialogListener(getCommandTargetID());
				m_arrDlg[i]->setVisible(false);
				m_arrDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
		}
		break;

		case CTRGuildWorkshop_RankDlg::RANK_SELECTITEM:
			m_arrDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_SELECTITEMDLG], errmsg);
			if(m_arrDlg[i])
			{
				m_arrDlg[i]->setClientPos(m_arrDlg[ERank::RANK_BASE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_WORKSHOP_SELECTITEMDLG], GUI_SUB_CONTROL_FRAME)->getScreenRect());
				m_arrDlg[i]->setDialogListener(getCommandTargetID());
				m_arrDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
			break;
		}
	}
}

void CTRGuildWorkshop_RankDlg::InitButton()
{
	for(int i = 0; i < m_arrayButtonEvent.size(); i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_RankDlg::BN_CLOSE:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_CLOSE];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				closeDialog();
			};
			break;

		case CTRGuildWorkshop_RankDlg::BN_PREV:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_PREV];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				if(m_nCurPage > 0)
				{
					m_nCurPage--;
					UpdateListPiece();
				}
			};
			break;

		case CTRGuildWorkshop_RankDlg::BN_NEXT:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_NEXT];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				if(m_nTotalPage > 0 && m_nCurPage < m_nTotalPage)
				{
					m_nCurPage++;
					UpdateListPiece();
				}
			};
			break;
		}
	}
}

void CTRGuildWorkshop_RankDlg::InitStaticText()
{
	for(int i = 0; i < EStaticTextName::SN_END; i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_RankDlg::SN_PAGENUM:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrDlg[ERank::RANK_LIST]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_PAGENUM], GUI_SUB_CONTROL_STATIC_TEXT));
			break;
		case CTRGuildWorkshop_RankDlg::SN_SELECTITEM_GOODSNAME:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrDlg[ERank::RANK_SELECTITEM]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_SELECTITEM_GOODSNAME], GUI_SUB_CONTROL_STATIC_TEXT));
			m_arrayStaticText[i]->setVisible(false);
			break;
		case CTRGuildWorkshop_RankDlg::SN_SELECTITEM_DAY:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrDlg[ERank::RANK_SELECTITEM]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_SELECTITEM_DAY], GUI_SUB_CONTROL_STATIC_TEXT));
			m_arrayStaticText[i]->setVisible(false);
			break;
		case CTRGuildWorkshop_RankDlg::SN_SELECTITEM_TYPEMENT:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrDlg[ERank::RANK_SELECTITEM]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_SELECTITEM_TYPEMENT], GUI_SUB_CONTROL_STATIC_TEXT));
			break;
		}
	}
}

void CTRGuildWorkshop_RankDlg::InitImageControl()
{
	m_pSelectItemImageCtrl = static_cast<CGUIItemImageCtrl*>(m_arrDlg[ERank::RANK_SELECTITEM]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::IC_SELECTITEM_IMAGE], GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
}

void CTRGuildWorkshop_RankDlg::InitListPiece()
{
	for(int i = 0; i < MAX_LISTPIECE; i++)
	{
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_NAME] = static_cast<CGUIStaticText*>(m_arrDlg[ERank::RANK_LISTPIECE01 + i]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_LISTPIECE_NAME], GUI_SUB_CONTROL_STATIC_TEXT));
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_NAME]->setVisible(false);

		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_POINT] = static_cast<CGUIStaticText*>(m_arrDlg[ERank::RANK_LISTPIECE01 + i]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_LISTPIECE_POINT], GUI_SUB_CONTROL_STATIC_TEXT));
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_POINT]->setVisible(false);

		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_RANKNUM] = static_cast<CGUIStaticText*>(m_arrDlg[ERank::RANK_LISTPIECE01 + i]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_LISTPIECE_RANKNUM], GUI_SUB_CONTROL_STATIC_TEXT));
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_RANKNUM]->setVisible(false);
	}
}

void CTRGuildWorkshop_RankDlg::UpdateListPiece()
{
	UpdatePage();

	InitListPiece();

	if(m_nTotalNickName == 0)
	{
		return;
	}
	
	for(int i = 0; i < m_nCurNickName; i++)
	{
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_NAME]->setText(get<1>(m_userList[i + (MAX_LISTPIECE * m_nCurPage)]));
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_NAME]->setVisible(true);

		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_RANKNUM]->setText(to_string(1 + i + (MAX_LISTPIECE * m_nCurPage)));
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_RANKNUM]->setVisible(true);

		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_POINT]->setText(to_string(get<0>(m_userList[i + (MAX_LISTPIECE * m_nCurPage)])) + _STR(MONEY_GP));
		m_arrayListPiece[i].arrayStaticText[SListPiece::SN_POINT]->setVisible(true);
	}
}

void CTRGuildWorkshop_RankDlg::InitPage()
{
	m_nTotalPage = m_nTotalNickName / MAX_LISTPIECE == 0 ? 0 : (m_nTotalNickName / MAX_LISTPIECE);
	m_nTotalPage = m_nTotalNickName % MAX_LISTPIECE == 0 ? m_nTotalPage - 1 : m_nTotalPage;
	m_nTotalPage = m_nTotalPage == -1 ? 0 : m_nTotalPage;
	m_nCurPage = 0;

	UpdatePage();

	UpdateListPiece();
}

void CTRGuildWorkshop_RankDlg::UpdatePage()
{
	if(m_nTotalPage > 0)
	{
		if(m_nCurPage < m_nTotalPage)
		{
			m_nCurNickName = MAX_LISTPIECE;
		}
		else
		{
			m_nCurNickName = m_nTotalNickName % MAX_LISTPIECE;
		}
	}
	else
	{
		m_nCurNickName = m_nTotalNickName % MAX_LISTPIECE == 0 ? MAX_LISTPIECE : m_nTotalNickName % MAX_LISTPIECE;
	}

	m_arrayStaticText[EStaticTextName::SN_PAGENUM]->setText(to_string(m_nCurPage + 1) + m_strPageNumSign + to_string(m_nTotalPage + 1));
}

void CTRGuildWorkshop_RankDlg::InitSelectDlg()
{
	if(m_sGuildPlantMakeInfo.m_iItemDescNum != 0)
	{
		UpdateSelectDlg();
	}
}

void CTRGuildWorkshop_RankDlg::UpdateSelectDlg()
{
	if(m_arrDlg[ERank::RANK_SELECTITEM])
	{
		const CItemInfoNode* pItemInfo = CClientItemList::getInstance().getRealItemInfo(m_sGuildPlantMakeInfo.m_iItemDescNum);

		m_pSelectItemImageCtrl->setItemImage(m_sGuildPlantMakeInfo.m_iItemDescNum);

		m_arrayStaticText[EStaticTextName::SN_SELECTITEM_GOODSNAME]->setText(pItemInfo->m_name);
		m_arrayStaticText[EStaticTextName::SN_SELECTITEM_GOODSNAME]->setVisible(true);

		m_arrayStaticText[EStaticTextName::SN_SELECTITEM_DAY]->setText(GetSelectDay(m_nFinishDate));
		m_arrayStaticText[EStaticTextName::SN_SELECTITEM_DAY]->setVisible(true);
	}
}

void CTRGuildWorkshop_RankDlg::DummyInitData()
{
	vector<string> vecName = { "aaa","bbb", "ccc", "ddd", "eee", "fff", "ggg", "hhh", "iii", "jjj", "kkk", "lll", "mmm","nnn" };

	for(int i = 0; i < vecName.size(); i++)
	{
		m_userList.emplace_back(i, vecName[i]);
	}
}
