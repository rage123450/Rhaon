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

		// ���� ������ ������ �˾�â ���
		_yesnoDialogPopup();

		return true;
	}
	else if ("InvestorBtn" == name)
	{
		GuildUserInfo myGuildUserInfo = CNetClientManager::getInstance().getMyGuildUserInfo();

		// ���� ������ �̻� �� �� �ְ� �Ѵ�
		if (eGuildMemberGrade_SUBMASTER != myGuildUserInfo.m_eGrade && eGuildMemberGrade_MASTER != myGuildUserInfo.m_eGrade)
		{
			CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_GUILD_INVALID_PERMISSION));
			return true;
		}

		// ������ ����Ʈ â�� ���鼭 ���� â�� ��Ȱ��ȭ
		CGUIControl* pManage = m_manageID.findControl();
		if (pManage)
		{
			pManage->setVisible(false);
		}

		_setInvestorListVisible(true);

		_setButtonChecked("ManageBtn", false);
		_setButtonChecked(name, true);

		// ù ������ ����Ʈ���� ����
		_setPage(true);
		_setInvestorListByPage(m_iCurPage);

		return true;
	}
	// � TR â�� Ȯ�� ��ư�� ���� �������� (���� ��ġ �� �߰� ����)
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

// 		// ��� � TR â�� ���� ��û
// 		// �̰����� ��û�� �� �� �� �ϴ� ������, â�� �ٲ� �� �Ϸ簡 ���� �� �ֱ� ������ �����ϴ� ����
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

	// ��� � TR ��û
	CNetClientManager::getInstance().requestGetGuildPlantManagerTR(CNetClientManager::getInstance().getMyGuildNum());

	GuildUserInfo myGuildUserInfo = CNetClientManager::getInstance().getMyGuildUserInfo();

	// ���� ������ �̻� ���� ����Ʈ ����
	if (eGuildMemberGrade_SUBMASTER == myGuildUserInfo.m_eGrade || eGuildMemberGrade_MASTER == myGuildUserInfo.m_eGrade)
	{
		CNetClientManager::getInstance().requestGetGuildPlantInvestorManagerTRList();
	}

	// ���� 7�� �̸��� ��� ���� ��ư ��Ȱ��ȭ (���� ��Ʈ�ѵ� ��Ȱ��ȭ)
	if (_cheackJoinWithin7Days(myGuildUserInfo.m_tJoin))
	{
		_hideInvestButton();
	}

	// ��� � TR â�� ���� ��û
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
	// format("%d %s", iGuildManagerTR, _STR(MONEY_TR)) -> �̰ɷ� �� ��� _STR(MONEY_TR)�� (null) ��ȯ��
	// ���� ����ϸ� ������ ������ �̷��� ����
	std::string str = format("%d ", iGuildManagerTR) + _STR(MONEY_TR);
	_setStaticText(m_manageID, "ManageTR", str);

	m_iCurGuildManageTR = iGuildManagerTR;
}

void CTRGuildWorkshop_WarehouseDlg::onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR)
{
	int iGuildNum = CNetClientManager::getInstance().getMyGuildNum();

	CNetClientManager::getInstance().requestCurrentTR();						// ���� TR ����
	CNetClientManager::getInstance().requestGetGuildPlantManagerTR(iGuildNum);	// ��� � TR ����

	GuildUserInfo myGuildUserInfo = CNetClientManager::getInstance().getMyGuildUserInfo();

	// ���� ������ �̻� ���� ����Ʈ ����
	if (eGuildMemberGrade_SUBMASTER == myGuildUserInfo.m_eGrade || eGuildMemberGrade_MASTER == myGuildUserInfo.m_eGrade)
	{
		CNetClientManager::getInstance().requestGetGuildPlantInvestorManagerTRList();
	}

	// ���ڿ� ����������, �Ϸ翡 �� ���� ���ڰ� �����ϹǷ� ���� ��ư�� ���� ��Ʈ���� ��Ȱ��ȭ
	_hideInvestButton();

	CTRShortTimeMessage::getInstance().showMessage(_STR(GUILD_PLANT_INVEST_OK));
}

void CTRGuildWorkshop_WarehouseDlg::onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue)
{
	// ���� �����ߴ��� Ȯ��
	if (m_bCheckInvest)
	{
		// ���� Ƚ���� ������ ��� ���� �̹� ���ڸ� �� ���̹Ƿ� ���� ��ư ��Ȱ��ȭ
		if (iUserInvestCount)
		{
			_hideInvestButton();
		}

		m_bCheckInvest = false;

		_setStaticText(m_manageID, "MaxTR", format("%d%s", iExtendValue, _STR(MONEY_TR)));

		m_iMaxGuildManageTR = iExtendValue;

		return;
	}
	
	// â�� Ȯ�� �ִ� ����(EXTEND_MAX_COUNT)�� �Ѿ�� ��� ������
	if (EXTEND_MAX_COUNT < iExtendCount)
	{
		CTRShortTimeMessage::getInstance().showMessage(_STR(GUILD_PLANT_FAILED_STORAGE_EXTEND_OVER_COUNT));
		return;
	}
	// Ȯ�� ������ ��� ������ ���� â�� �����ش�
	else
	{
		std::vector<const CItemInfoNode*> vecItem;

		// � TR â�� Ȯ����� �޾ƿ´�
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
			CTRShopManager::getInstance().CreateBuyUI(vecItem);	// ������ ���� UI ����
		}
		else
		{
			CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_INVALID_ITEMNUM));	// �������� �������� �ʴ´�
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

	// ���� �ݾ׿� ���� �������� ����
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
		// ���ڸ� �Է� �����ϰ� ����
		pEdit->setNumeralMode(true);
		// �ּҰ� �ִ밪 ����
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
	pInvestorList->setVisible(false);	// � ���� â�� ���� �߹Ƿ� �ϴ� ������ �ʰ� ó��

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
			pInvestorListPiece->setVisible(false);	// � ���� â�� ���� �߹Ƿ� �ϴ� ������ �ʰ� ó��

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

		// ������ ����Ʈ�� �ҷ��� ��ü �������� ���Ѵ�
		// �ڼ��� ������ TRGuildWorkshop_ManagementDlg.h�� _setPage(eItemCategory, eRewardCondition) �Լ� ����
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

	// i�� ������ ����Ʈ ���̾�α��� �ε���(0 ~ m_vecInvestorListPiece.size())
	// index�� ������ ���� ����Ʈ�� �ε���(0 ~ m_vecInvestorList.size())
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

	// ���� �������� ������ ����Ʈ�� ��� ���� �ִ� ���, �� ����Ʈ���� ��Ȱ��ȭ
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

	// 'yyyy/mm/ss'������ ���� ���� ���ڿ��� �и���Ų��
	stringutil::splitString(date.substr(0, 10), '/', splitDiffTime);

	/*
	 * C ǥ���Լ����� 1970�� 1�� 1���� �������� �ð��� ó��
	 * �� ���� �ð��� ���ֱ� ���� ���� ��ҿ��� ���ش�
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

	// yes�� Ŭ���� ��� �Լ�(_operationalTRInvestment()) ȣ��
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

		// �Ϸ� �ִ� ���� �ݾ�(100��) ���� ū��
		if (DAILY_MAX_INVEST_MONEY < trCost)
		{
			CTRShortTimeMessage::getInstance().showMessage(_STR(GUILD_PLANT_FAILED_INVEST_AMOUNT_EXCEEDED));

			pEdit->setText("");

			return;
		}

		// ���� ���� ������ TR ���� ������
		if (myTR < trCost)
		{
			CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_CREATE_FAMILY_NOT_ENOUGH_MONEY));

			pEdit->setText("");

			return;
		}

		// �������� ��, ��� � TR â���� ���� �ִ� �ݾ��� �Ѿ����
		if (m_iMaxGuildManageTR < m_iCurGuildManageTR + trCost)
		{
			CTRShortTimeMessage::getInstance().showMessage(format(_STR(GUILD_PLANT_FAILED_OVER_INVEST_STORAGE)));

			pEdit->setText("");

			return;
		}

		// ���� ��û
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