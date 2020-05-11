/* ---------------------------------------------------------------
 *
 * Copyright 2019 by Rhaon Ent.
 *
 * TRGuildWorkshop_WarehouseDlg.cpp
 *
 * 2019. 12. Han Younho
 *
 * ---------------------------------------------------------------
 */

#include "stdafx.h"
#include "TRGuildWorkshop_WarehouseDlg.h"

#include "language/LanguageHeader.h"

#include "gameui/TRShortTimeMessage.h"
#include "gameui/ClientItemInfoLoader.h"

#include "gameui/shop/TRShopManager.h"
#include "gameui/shop/TRShopRenewalDialogPopularityItemList.h"

#include "NetClientManager.h"

namespace
{
	enum { EXTEND_MAX_COUNT = 5 };
	enum { DAILY_MAX_INVEST_MONEY = 1000000 };
}

CTRGuildWorkshop_WarehouseDlg::CTRGuildWorkshop_WarehouseDlg()
	: m_dlgID(CGUIControlID::INVALID_ID), m_manageID(CGUIControlID::INVALID_ID), m_investorListID(CGUIControlID::INVALID_ID)
	, m_iCurGuildManageTR(0), m_iMaxGuildManageTR(0)
	, m_iCurPage(1), m_iMaxPage(1)
	, m_bCheckInvest(false)
{
	m_vecInvestorListPiece.reserve(6);
	m_vecInvestorList.reserve(16);
}

CTRGuildWorkshop_WarehouseDlg::~CTRGuildWorkshop_WarehouseDlg()
{
	closeDialog();
}

bool CTRGuildWorkshop_WarehouseDlg::isVisible() const
{
	CGUIControl* pDlg = m_dlgID.findControl();
	return pDlg ? pDlg->isVisible() : false;
}

bool CTRGuildWorkshop_WarehouseDlg::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
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
	
	if ("InvestorTRBtn" == name)
	{
		if (false == pCtrl->isVisible())
		{
			return true;
		}

		// 정말 투자할 것인지 팝업창 띄움
		_yesnoDialogPopup();

		return true;
	}
	else if ("InvestorBtn" == name)
	{
		GuildUserInfo myGuildUserInfo = CNetClientManager::getInstance().getMyGuildUserInfo();

		// 서브 마스터 이상만 열 수 있게 한다
		if (eGuildMemberGrade_SUBMASTER != myGuildUserInfo.m_eGrade && eGuildMemberGrade_MASTER != myGuildUserInfo.m_eGrade)
		{
			CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_GUILD_INVALID_PERMISSION));
			return true;
		}

		// 투자자 리스트 창을 열면서 투자 창은 비활성화
		CGUIControl* pManage = m_manageID.findControl();
		if (pManage)
		{
			pManage->setVisible(false);
		}

		_setInvestorListVisible(true);

		_setButtonChecked("ManageBtn", false);
		_setButtonChecked(name, true);

		// 첫 페이지 리스트들을 갱신
		_setPage(true);
		_setInvestorListByPage(m_iCurPage);

		return true;
	}
	// 운영 TR 창고 확장 버튼은 현재 없어졌음 (추후 패치 때 추가 예정)
// 	else if ("MaxUpBtn" == name)
// 	{
// 		CNetClientManager::getInstance().requestGetGuildPlantStorageExtend();
// 		return true;
// 	}
	else if ("ManageBtn" == name)
	{
		CGUIControl* pManage = m_manageID.findControl();
		if (pManage)
		{
			pManage->setVisible(true);
		}

		_setInvestorListVisible(false);

		_setButtonChecked(name, true);
		_setButtonChecked("InvestorBtn", false);

// 		// 길드 운영 TR 창고 정보 요청
// 		// 이곳에서 요청을 한 번 더 하는 이유는, 창을 바꿀 때 하루가 지날 수 있기 때문에 갱신하는 목적
// 		CNetClientManager::getInstance().requestGetGuildPlantStorageExtend();
// 
// 		m_bCheckInvest = true;

		return true;
	}
	else if ("NextBtn" == name)
	{
		++m_iCurPage;

		if (m_iMaxPage < m_iCurPage)
		{
			m_iCurPage = m_iMaxPage;
			return true;
		}

		_setInvestorListByPage(m_iCurPage);

		return true;
	}
	else if ("PrevBtn" == name)
	{
		--m_iCurPage;

		if (1 > m_iCurPage)
		{
			m_iCurPage = 1;
			return true;
		}

		_setInvestorListByPage(m_iCurPage);

		return true;
	}
	else if ("Close" == name)
	{
		closeDialog();
		return true;
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRGuildWorkshop_WarehouseDlg::showDialog()
{
	closeDialog();

	std::string errmsg;

	CGUIDialog* pDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_TR_Warehouse.gui", errmsg);
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

	_setManage();
	_setInvestorList();
	_setInvestorListPiece();

	_setButtonChecked("ManageBtn", true);

	// 길드 운영 TR 요청
	CNetClientManager::getInstance().requestGetGuildPlantManagerTR(CNetClientManager::getInstance().getMyGuildNum());

	GuildUserInfo myGuildUserInfo = CNetClientManager::getInstance().getMyGuildUserInfo();

	// 서브 마스터 이상만 투자 리스트 갱신
	if (eGuildMemberGrade_SUBMASTER == myGuildUserInfo.m_eGrade || eGuildMemberGrade_MASTER == myGuildUserInfo.m_eGrade)
	{
		CNetClientManager::getInstance().requestGetGuildPlantInvestorManagerTRList();
	}

	// 가입 7일 미만일 경우 투자 버튼 비활성화 (에딧 컨트롤도 비활성화)
	if (_cheackJoinWithin7Days(myGuildUserInfo.m_tJoin))
	{
		_hideInvestButton();
	}

	// 길드 운영 TR 창고 정보 요청
	CNetClientManager::getInstance().requestGetGuildPlantStorageExtend();

	m_bCheckInvest = true;
}

void CTRGuildWorkshop_WarehouseDlg::closeDialog()
{
	m_bCheckInvest = false;

	m_iCurPage = 1;
	m_iMaxPage = 1;

	m_iCurGuildManageTR = 0;
	m_iMaxGuildManageTR = 0;

	m_vecInvestorList.clear();

	for (auto& ctrlID : m_vecInvestorListPiece)
	{
		CGUIControl* pInvestorListPiece = ctrlID.findControl();
		if (pInvestorListPiece)
		{
			CGUIManager::getInstance().removeControl(pInvestorListPiece);
		}
	}

	m_vecInvestorListPiece.clear();

	if (m_yesnoDialog.isVisible())
	{
		m_yesnoDialog.closeDialog();
	}

	CGUIControl* pManage = m_manageID.findControl();
	if (pManage)
	{
		pManage->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_manageID = CGUIControlID::INVALID_ID;
	}

	CGUIControl* pInvestorList = m_investorListID.findControl();
	if (pInvestorList)
	{
		pInvestorList->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_investorListID = CGUIControlID::INVALID_ID;
	}

	CGUIControl* pDlg = m_dlgID.findControl();
	if (pDlg)
	{
		pDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_dlgID = CGUIControlID::INVALID_ID;
	}
}

void CTRGuildWorkshop_WarehouseDlg::onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR)
{
	// format("%d %s", iGuildManagerTR, _STR(MONEY_TR)) -> 이걸로 할 경우 _STR(MONEY_TR)이 (null) 반환됨
	// 따로 사용하면 괜찮기 때문에 이렇게 적용
	std::string str = format("%d ", iGuildManagerTR) + _STR(MONEY_TR);
	_setStaticText(m_manageID, "ManageTR", str);

	m_iCurGuildManageTR = iGuildManagerTR;
}

void CTRGuildWorkshop_WarehouseDlg::onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR)
{
	int iGuildNum = CNetClientManager::getInstance().getMyGuildNum();

	CNetClientManager::getInstance().requestCurrentTR();						// 개인 TR 갱신
	CNetClientManager::getInstance().requestGetGuildPlantManagerTR(iGuildNum);	// 길드 운영 TR 갱신

	GuildUserInfo myGuildUserInfo = CNetClientManager::getInstance().getMyGuildUserInfo();

	// 서브 마스터 이상만 투자 리스트 갱신
	if (eGuildMemberGrade_SUBMASTER == myGuildUserInfo.m_eGrade || eGuildMemberGrade_MASTER == myGuildUserInfo.m_eGrade)
	{
		CNetClientManager::getInstance().requestGetGuildPlantInvestorManagerTRList();
	}

	// 투자에 성공했으면, 하루에 한 번만 투자가 가능하므로 투자 버튼과 에딧 컨트롤을 비활성화
	_hideInvestButton();

	CTRShortTimeMessage::getInstance().showMessage(_STR(GUILD_PLANT_INVEST_OK));
}

void CTRGuildWorkshop_WarehouseDlg::onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue)
{
	// 오늘 투자했는지 확인
	if (m_bCheckInvest)
	{
		// 투자 횟수가 존재할 경우 오늘 이미 투자를 한 것이므로 투자 버튼 비활성화
		if (iUserInvestCount)
		{
			_hideInvestButton();
		}

		m_bCheckInvest = false;

		_setStaticText(m_manageID, "MaxTR", format("%d%s", iExtendValue, _STR(MONEY_TR)));

		m_iMaxGuildManageTR = iExtendValue;

		return;
	}
	
	// 창고 확장 최대 개수(EXTEND_MAX_COUNT)를 넘어섰을 경우 나간다
	if (EXTEND_MAX_COUNT < iExtendCount)
	{
		CTRShortTimeMessage::getInstance().showMessage(_STR(GUILD_PLANT_FAILED_STORAGE_EXTEND_OVER_COUNT));
		return;
	}
	// 확장 가능한 경우 아이템 구매 창을 열어준다
	else
	{
		std::vector<const CItemInfoNode*> vecItem;

		// 운영 TR 창고 확장권을 받아온다
		std::vector<int> itemNumList = CClientItemList::getInstance().getItemInfo(eCharacterKind_NONE, eFarmItemPosition_GUILDPLANT_UPGRADE_MANAGETR);
		if (false == itemNumList.empty())
		{
			const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(itemNumList[0]);
			if (pItem)
			{
				vecItem.push_back(pItem);
			}
		}

		if (false == vecItem.empty())
		{
			CTRShopManager::getInstance().CreateBuyUI(vecItem);	// 아이템 구매 UI 생성
		}
		else
		{
			CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_INVALID_ITEMNUM));	// 아이템이 존재하지 않는다
		}
	}

	m_iMaxGuildManageTR = iExtendValue;

	_setStaticText(m_manageID, "MaxTR", format("%d%s", iExtendValue, _STR(MONEY_TR)));
}

void CTRGuildWorkshop_WarehouseDlg::onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList)
{
	m_vecInvestorList.clear();

	auto& iter = userList.begin();
	if (userList.end() == iter)
	{
		return;
	}

	for (; iter != userList.end(); ++iter)
	{
		m_vecInvestorList.push_back(std::make_pair(iter->first, iter->second));
	}

	// 투자 금액에 따라 내림차순 정렬
	std::sort(m_vecInvestorList.begin(), m_vecInvestorList.end(), [](auto& lhs, auto& rhs)
	{
		return lhs.first > rhs.first;
	});
}

void CTRGuildWorkshop_WarehouseDlg::_setManage()
{
	std::string errmsg;

	CGUIDialog* pManage = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_TR_Warehouse_Manage.gui", errmsg);
	if (nullptr == pManage)
	{
		return;
	}

	m_manageID = pManage->getControlID();

	_setClientPos(m_dlgID, m_manageID, "SubInfo");
	pManage->setDialogListener(getCommandTargetID());
	pManage->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));

	_setStaticText(m_manageID, "Disment", _STR(GUILD_PLANT_WAREHOUSE_MAX_INVEST_MENT));
	_setStaticText(m_manageID, "InvestorTRGuide", _STR(GUILD_PLANT_WAREHOUSE_INVEST_MENT));

	CGUIEditCtrl* pEdit = static_cast<CGUIEditCtrl*>(pManage->findControl("InvestorTR"));
	if (pEdit)
	{
		// 숫자만 입력 가능하게 셋팅
		pEdit->setNumeralMode(true);
		// 최소값 최대값 설정
		pEdit->setNumeralMaxMin(0, DAILY_MAX_INVEST_MONEY);
	}
}

void CTRGuildWorkshop_WarehouseDlg::_setInvestorList()
{
	std::string errmsg;

	CGUIDialog* pInvestorList = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_TR_Warehouse_List.gui", errmsg);
	if (nullptr == pInvestorList)
	{
		return;
	}

	m_investorListID = pInvestorList->getControlID();

	_setClientPos(m_dlgID, m_investorListID, "SubInfo");
	pInvestorList->setDialogListener(getCommandTargetID());
	pInvestorList->setVisible(false);	// 운영 투자 창이 먼저 뜨므로 일단 보이지 않게 처리

	_setStaticText(m_investorListID, "PageNum", format("%d / %d", m_iCurPage, m_iMaxPage));
}

void CTRGuildWorkshop_WarehouseDlg::_setInvestorListPiece()
{
	std::string errmsg;

	for (int i = 0; i < 6; ++i)
	{
		CGUIDialog* pInvestorListPiece = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_TR_Warehouse_ListPiece.gui", errmsg);
		if (pInvestorListPiece)
		{
			CGUIControlID ctrlID = pInvestorListPiece->getControlID();

			_setClientPos(m_investorListID, ctrlID, format("ListPiece%d", i + 1));
			pInvestorListPiece->setVisible(false);	// 운영 투자 창이 먼저 뜨므로 일단 보이지 않게 처리

			m_vecInvestorListPiece.push_back(ctrlID);
		}
	}
}

void CTRGuildWorkshop_WarehouseDlg::_setPage(bool bInit)
{
	if (bInit)
	{
		m_iCurPage = 1;

		int maxPage = 1;

		// 투자자 리스트를 불러와 전체 페이지를 구한다
		// 자세한 사항은 TRGuildWorkshop_ManagementDlg.h의 _setPage(eItemCategory, eRewardCondition) 함수 참조
		if (m_vecInvestorList.size())
		{
			if (m_vecInvestorList.size() / 6)
			{
				if (0 == m_vecInvestorList.size() % 6)
				{
					maxPage = m_vecInvestorList.size() / 6;
				}
				else
				{
					maxPage = (m_vecInvestorList.size() / 6) + 1;
				}
			}
		}

		m_iMaxPage = maxPage;
	}

	_setStaticText(m_investorListID, "PageNum", format("%d / %d", m_iCurPage, m_iMaxPage));
}

void CTRGuildWorkshop_WarehouseDlg::_setInvestorListVisible(bool b)
{
	CGUIControl* pInvestList = m_investorListID.findControl();
	if (pInvestList)
	{
		pInvestList->setVisible(b);
	}

	for (auto& ctrlID : m_vecInvestorListPiece)
	{
		CGUIControl* pInvestorListPiece = ctrlID.findControl();
		if (pInvestorListPiece)
		{
			pInvestorListPiece->setVisible(b);
		}
	}
}

void CTRGuildWorkshop_WarehouseDlg::_setInvestorListByPage(int page)
{
	if (1 > page || m_iMaxPage < page)
	{
		return;
	}

	if (m_vecInvestorListPiece.empty())
	{
		for (auto& ctrlID : m_vecInvestorListPiece)
		{
			CGUIControl* pListPiece = ctrlID.findControl();
			if (pListPiece)
			{
				pListPiece->setVisible(false);
			}
		}

		return;
	}

	size_t i = 0;
	size_t index = (page - 1) * 6;

	// i는 투자자 리스트 다이얼로그의 인덱스(0 ~ m_vecInvestorListPiece.size())
	// index는 투자자 정보 리스트의 인덱스(0 ~ m_vecInvestorList.size())
	while (m_vecInvestorListPiece.size() > i && m_vecInvestorList.size() > index)
	{
		CGUIDialog* pListPiece = static_cast<CGUIDialog*>(m_vecInvestorListPiece[i].findControl());
		if (pListPiece)
		{
			pListPiece->setVisible(true);

			auto& pair = m_vecInvestorList[index];

			_setStaticText(m_vecInvestorListPiece[i], "Name", pair.second);
			_setStaticText(m_vecInvestorListPiece[i], "TR", format("%d %s", pair.first, _STR(MONEY_TR)));
		}

		++index;
		++i;
	}

	// 현재 페이지에 투자자 리스트가 비는 것이 있는 경우, 그 리스트들은 비활성화
	if (0 <= i && m_vecInvestorListPiece.size() > i)
	{
		for (size_t j = i; j < m_vecInvestorListPiece.size(); ++j)
		{
			CGUIControl* pListPiece = m_vecInvestorListPiece[j].findControl();
			if (pListPiece)
			{
				pListPiece->setVisible(false);
			}
		}
	}

	m_iCurPage = page;

	_setPage();
}

bool CTRGuildWorkshop_WarehouseDlg::_cheackJoinWithin7Days(time_type joinDate)
{
	time_type diff = CCurrentTime::current() - joinDate;

	std::string date;
	CCurrentTime::format(diff, date);

	std::vector<std::string> splitDiffTime;

	// 'yyyy/mm/ss'까지만 따로 떼서 문자열을 분리시킨다
	stringutil::splitString(date.substr(0, 10), '/', splitDiffTime);

	/*
	 * C 표준함수들은 1970년 1월 1일을 기준으로 시간을 처리
	 * 그 기준 시간을 없애기 위해 각각 요소에서 빼준다
	 */

	int year = atoi(splitDiffTime[0].c_str()) - 1970;
	if (year)
	{
		return false;
	}

	int month = atoi(splitDiffTime[1].c_str()) - 1;
	if (month)
	{
		return false;
	}

	int day = atoi(splitDiffTime[2].c_str()) - 1;
	if (7 < day)
	{
		return false;
	}

	return true;
}

void CTRGuildWorkshop_WarehouseDlg::_hideInvestButton()
{
	CGUIControl* pManage = m_manageID.findControl();
	if (pManage)
	{
		CGUIButton* pButton = static_cast<CGUIButton*>(pManage->findControl("InvestorTRBtn"));
		if (pButton)
		{
			pButton->setVisible(false);
		}

		CGUIEditCtrl* pEdit = static_cast<CGUIEditCtrl*>(pManage->findControl("InvestorTR"));
		if (pEdit)
		{
			pEdit->setVisible(false);
		}
	}
}

void CTRGuildWorkshop_WarehouseDlg::_yesnoDialogPopup()
{
	CGUIControl* pManage = m_manageID.findControl();
	if (nullptr == pManage)
	{
		return;
	}

	CGUIEditCtrl* pEdit = static_cast<CGUIEditCtrl*>(pManage->findControl("InvestorTR"));
	if (pEdit)
	{
		std::string point;
		pEdit->getText(point);

		if (0 >= atoi(point.c_str()))
		{
			CTRShortTimeMessage::getInstance().showMessage(_STR(MSG_QUIZ_HOTTIME_EMPTY_DATA));

			pEdit->setText("");

			return;
		}
	}

	// yes를 클릭한 경우 함수(_operationalTRInvestment()) 호출
	m_yesnoDialog.showDialog(_STR(GUILD_PLANT_INVEST_MESSAGE), this,
							 &CTRGuildWorkshop_WarehouseDlg::_operationalTRInvestment, nullptr);
}

void CTRGuildWorkshop_WarehouseDlg::_operationalTRInvestment()
{
	CGUIControl* pManage = m_manageID.findControl();
	if (nullptr == pManage)
	{
		return;
	}

	CGUIEditCtrl* pEdit = static_cast<CGUIEditCtrl*>(pManage->findControl("InvestorTR"));
	if (pEdit)
	{
		std::string point;
		pEdit->getText(point);

		int myTR = CNetClientManager::getInstance().getGameMoney();
		int trCost = atoi(point.c_str());

		// 하루 최대 충전 금액(100만) 보다 큰지
		if (DAILY_MAX_INVEST_MONEY < trCost)
		{
			CTRShortTimeMessage::getInstance().showMessage(_STR(GUILD_PLANT_FAILED_INVEST_AMOUNT_EXCEEDED));

			pEdit->setText("");

			return;
		}

		// 현재 내가 보유한 TR 보다 많은지
		if (myTR < trCost)
		{
			CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_CREATE_FAMILY_NOT_ENOUGH_MONEY));

			pEdit->setText("");

			return;
		}

		// 투자했을 때, 길드 운영 TR 창고의 현재 최대 금액을 넘어서는지
		if (m_iMaxGuildManageTR < m_iCurGuildManageTR + trCost)
		{
			CTRShortTimeMessage::getInstance().showMessage(format(_STR(GUILD_PLANT_FAILED_OVER_INVEST_STORAGE)));

			pEdit->setText("");

			return;
		}

		// 투자 요청
		CNetClientManager::getInstance().requestInvestGuildPlantManagerTR(trCost);
		
		pEdit->setText("");
	}
}

void CTRGuildWorkshop_WarehouseDlg::_setButtonChecked(const std::string& name, bool b)
{
	CGUIControl* pDlg = m_dlgID.findControl();
	if (nullptr == pDlg)
	{
		return;
	}

	CGUIImageButton* pButton = static_cast<CGUIImageButton*>(pDlg->findControl(name));
	if (pButton)
	{
		pButton->setChecked(b);
	}
}

void CTRGuildWorkshop_WarehouseDlg::_setStaticText(CGUIControlID ctrlID, const std::string& name, const std::string& message)
{
	CGUIControl* pCtrl = ctrlID.findControl();
	if (nullptr == pCtrl)
	{
		return;
	}

	CGUIStaticText* pText = static_cast<CGUIStaticText*>(pCtrl->findControl(name));
	if (pText)
	{
		pText->setText(message);
	}
}

void CTRGuildWorkshop_WarehouseDlg::_setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string& name)
{
	CGUIControl* pParentDlg = parentID.findControl();
	CGUIControl* pChildDlg = childID.findControl();
	if (nullptr == pParentDlg || nullptr == pChildDlg)
	{
		return;
	}

	CGUIControl* pFrame = pParentDlg->findControl(name);
	if (pFrame)
	{
		pChildDlg->setClientPos(pFrame->getScreenRect());
	}
}