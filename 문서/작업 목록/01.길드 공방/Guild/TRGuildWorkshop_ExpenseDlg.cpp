/* ---------------------------------------------------------------
 *
 * Copyright 2019 by Rhaon Ent.
 *
 * TRGuildWorkshop_ExpenseDlg.cpp
 *
 * 2019. 12. Han Younho
 *
 * ---------------------------------------------------------------
 */

#include "stdafx.h"
#include "TRGuildWorkshop_ExpenseDlg.h"

#include "language/LanguageHeader.h"

#include "NetClientManager.h"

CTRGuildWorkshop_ExpenseDlg::CTRGuildWorkshop_ExpenseDlg()
	: m_dlgID(CGUIControlID::INVALID_ID), m_listDlgID(CGUIControlID::INVALID_ID)
	, m_eCurCondition(eRewardCondition_GUILD_POINT)
	, m_iCurPage(1), m_iMaxPage(1), m_iSelMonth(-1)
{
	m_vecListPiece.reserve(6);
	m_vecExpenseList.reserve(48);
}

CTRGuildWorkshop_ExpenseDlg::~CTRGuildWorkshop_ExpenseDlg()
{
	closeDialog();
}

bool CTRGuildWorkshop_ExpenseDlg::isVisible() const
{
	CGUIControl* pDlg = m_dlgID.findControl();
	return pDlg ? pDlg->isVisible() : false;
}

bool CTRGuildWorkshop_ExpenseDlg::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
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

	if (startswith(name, "month"))
	{
		int month = atoi(name.substr(5).c_str());
		if (1 > month || 12 < month)
		{
			return false;
		}

		_setButtonChecked(name, true);
		
		// ��(month)�� �´� ������ ����Ʈ ��û
		CNetClientManager::getInstance().requestGetGuildPlantExpenseList(m_eCurCondition, month);

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
	else if ("PointBtn" == name)
	{
		_setButtonChecked(name, true);
		_setButtonChecked("ManagementBtn", false);

		// ��� ����Ʈ ����� ����Ʈ ����
		_setInvestorListCondition(eRewardCondition_GUILD_POINT);

		_setStaticText(m_dlgID, "RemainPoint", _STR(GUILD_PLANT_REMAIN_GUILD_POINT));

		return true;
	}
	else if ("ManagementBtn" == name)
	{
		_setButtonChecked("PointBtn", false);
		_setButtonChecked(name, true);

		// � TR ����� ����Ʈ ����
		_setInvestorListCondition(eRewardCondition_GUILD_MANAGER_TR);

		_setStaticText(m_dlgID, "RemainPoint", _STR(GUILD_PLANT_REMAIN_MANAGE_TR));

		return true;
	}
	else if ("Close" == name)
	{
		closeDialog();
		return true;
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRGuildWorkshop_ExpenseDlg::showDialog()
{
	closeDialog();

	std::string errmsg;

	CGUIDialog* pDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_ExpenseBase.gui", errmsg);
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

	_setStaticText(m_dlgID, "RemainPoint", _STR(GUILD_PLANT_REMAIN_GUILD_POINT));

	_setListDialog();
	_setListPieceDialog();

	_setButtonChecked("PointBtn", true);

	time_type time = CCurrentTime::current();

	// ���� �ð��� ���� ���ڿ��� ��ȯ("yyyy/mm/dd hh:mm:ss.ms")
	std::string curTime;
	CCurrentTime::format(time, curTime);

	// 'mm' �κи� ���� ������ ��ȯ
	int month = atoi(curTime.substr(5, 6).c_str());

	_setButtonChecked(format("month%d", month), true);

	// ���� ��(month)�� �´� ���� ����Ʈ ��û
	CNetClientManager::getInstance().requestGetGuildPlantExpenseList(m_eCurCondition, month);
}

void CTRGuildWorkshop_ExpenseDlg::closeDialog()
{
	m_iCurPage = 1;
	m_iMaxPage = 1;
	m_iSelMonth = -1;

	m_eCurCondition = eRewardCondition_GUILD_POINT;

	for (auto& ctrlID : m_vecListPiece)
	{
		CGUIControl* pListPiece = ctrlID.findControl();
		if (pListPiece)
		{
			pListPiece->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		}
	}

	m_vecListPiece.clear();
	m_vecExpenseList.clear();

	CGUIControl* pListDlg = m_listDlgID.findControl();
	if (pListDlg)
	{
		pListDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_listDlgID = CGUIControlID::INVALID_ID;
	}

	CGUIControl* pDlg = m_dlgID.findControl();
	if (pDlg)
	{
		pDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_dlgID = CGUIControlID::INVALID_ID;
	}
}

void CTRGuildWorkshop_ExpenseDlg::onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList)
{
	m_vecExpenseList.clear();

	// �ش� �޿� ���� ������ �ϳ��� ���� �� �ֱ� ������, �Լ��� ���������� �ʰ� ��� ����
	if (false == useList.empty())
	{
		// ���� ������ ���� �ͺ��� ���̱� ������, �ֽ� ������ �����̳ʿ� ��������
		// ������ �ݺ��ڸ� ���� ���� ���� ���߿� �������� �ʾƵ� �ż� ����
		auto& riter = useList.rbegin();
		for (; riter != useList.rend(); ++riter)
		{
			m_vecExpenseList.push_back(*riter);
		}
	}
	
	m_iSelMonth = iMonth;

	// ������ ���� �� �������� �´� ����Ʈ ����
	_setPage(true);
	_setInvestorListByPage(m_iCurPage);
}

void CTRGuildWorkshop_ExpenseDlg::_setListDialog()
{
	std::string errmsg;

	CGUIDialog* pListDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_ExpenseDlg.gui", errmsg);
	if (nullptr == pListDlg)
	{
		return;
	}

	m_listDlgID = pListDlg->getControlID();

	_setClientPos(m_dlgID, m_listDlgID, "ExpenseDlg");
	pListDlg->setDialogListener(getCommandTargetID());
	pListDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));

	_setStaticText(m_listDlgID, "PageNum", format("%d / %d", m_iCurPage, m_iMaxPage));
}

void CTRGuildWorkshop_ExpenseDlg::_setListPieceDialog()
{
	std::string errmsg;

	for (int i = 0; i < 6; ++i)
	{
		CGUIDialog* pListPiece = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_ExpensePiece.gui", errmsg);
		if (pListPiece)
		{
			CGUIControlID ctrlID = pListPiece->getControlID();

			_setClientPos(m_listDlgID, ctrlID, format("ExpensePiece_0%d", i + 1));
			pListPiece->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f));

// 			_setStaticText(ctrlID, "Day", "");
// 			_setStaticText(ctrlID, "Expense", "");
// 			_setStaticText(ctrlID, "Content", "");
// 			_setStaticText(ctrlID, "Point", "");
// 			_setStaticText(ctrlID, "GuildMember", "");

			m_vecListPiece.push_back(ctrlID);
		}
	}
}

void CTRGuildWorkshop_ExpenseDlg::_setInvestorListByPage(int page)
{
	if (1 > page || m_iMaxPage < page)
	{
		return;
	}

	if (m_vecExpenseList.empty())
	{
		for (auto& ctrlID : m_vecListPiece)
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

	// i�� ������ ����Ʈ ���̾�α��� �ε���(0 ~ m_vecListPiece.size())
	// index�� ������ ���� �����̳��� �ε���(0 ~ m_vecExpenseList.size())
	while (m_vecListPiece.size() > i && m_vecExpenseList.size() > index)
	{
		CGUIDialog* pListPiece = static_cast<CGUIDialog*>(m_vecListPiece[i].findControl());
		if (pListPiece)
		{
			pListPiece->setVisible(true);

			GuildPlantPointUseInfo pointUseInfo(m_vecExpenseList[index]);

			_setStaticText(m_vecListPiece[i], "Expense", format("%d", pointUseInfo.m_iUsePoint));
			_setStaticText(m_vecListPiece[i], "Content", pointUseInfo.m_strMemo);
			_setStaticText(m_vecListPiece[i], "GuildMember", pointUseInfo.m_strNickName);

			// time_type ������ ���� ��¥ ���ڿ��� �޾ƿ���(yyyy/mm/dd hh:mm:ss.ms)
			std::string day, point;
			CCurrentTime::format(pointUseInfo.m_tDateTime, day);

			_setStaticText(m_vecListPiece[i], "Day", day.substr(0, 10));

			if (eRewardCondition_GUILD_POINT == m_eCurCondition)
			{
				point = format("%d ", pointUseInfo.m_iRemainPoint) + _STR(MONEY_GP);
			}
			else if (eRewardCondition_GUILD_MANAGER_TR == m_eCurCondition)
			{
				point = format("%d ", pointUseInfo.m_iRemainPoint) + _STR(MONEY_TR);
			}

			_setStaticText(m_vecListPiece[i], "Point", point);
		}

		++index;
		++i;
	}

	// ���� ������ ���� ������ ����Ʈ ���̾�αװ� ����� ��� ������ �ʰ� ó��
	if (0 <= i && m_vecListPiece.size() > i)
	{
		for (size_t j = i; j < m_vecListPiece.size(); ++j)
		{
			CGUIDialog* pListPiece = static_cast<CGUIDialog*>(m_vecListPiece[j].findControl());
			if (pListPiece)
			{
				pListPiece->setVisible(false);
			}
		}
	}

	m_iCurPage = page;

	_setPage();
}

void CTRGuildWorkshop_ExpenseDlg::_setInvestorListCondition(eRewardCondition eCondition)
{
	if (eRewardCondition_GUILD_POINT > eCondition || eRewardCondition_GUILD_MANAGER_TR < eCondition)
	{
		return;
	}

	m_eCurCondition = eCondition;

	CNetClientManager::getInstance().requestGetGuildPlantExpenseList(m_eCurCondition, m_iSelMonth);
}

void CTRGuildWorkshop_ExpenseDlg::_setPage(bool bInit)
{
	if (bInit)
	{
		m_iCurPage = 1;

		int maxPage = 1;

		// ȭ�鿡 �°� ���� ����Ʈ�� �����ֱ� ���� �۾�
		// �ڼ��� ���� TRGuildWorkshop_ManagementDlg.h�� _setPage(eItemCategory, eRewardCondition) �Լ� ����
		if (m_vecExpenseList.size())
		{
			if (m_vecExpenseList.size() / 6)
			{
				if (0 == m_vecExpenseList.size() % 6)
				{
					maxPage = m_vecExpenseList.size() / 6;
				}
				else
				{
					maxPage = (m_vecExpenseList.size() / 6) + 1;
				}
			}
		}

		m_iMaxPage = maxPage;
	}

	_setStaticText(m_listDlgID, "PageNum", format("%d / %d", m_iCurPage, m_iMaxPage));
}

void CTRGuildWorkshop_ExpenseDlg::_setButtonChecked(const std::string& name, bool b)
{
	CGUIControl* pDlg = m_dlgID.findControl();
	if (nullptr == pDlg)
	{
		return;
	}

	int month = 0;

	if (startswith(name, "month"))
	{
		month = atoi(name.substr(5).c_str());

		for (int i = 0; i < 12; ++i)
		{
			CGUIButton* pButton = static_cast<CGUIButton*>(pDlg->findControl(format("month%d", i + 1)));
			if (pButton)
			{
				if (i + 1 != month)
				{
					pButton->setChecked(false);
				}
				else
				{
					pButton->setChecked(true);
				}
			}
		}
	}
	else
	{
		CGUIImageButton* pButton = static_cast<CGUIImageButton*>(pDlg->findControl(name));
		if (pButton)
		{
			pButton->setChecked(b);
		}
	}
}

void CTRGuildWorkshop_ExpenseDlg::_setStaticText(CGUIControlID ctrlID, const std::string& name, const std::string& message)
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

void CTRGuildWorkshop_ExpenseDlg::_setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string& name)
{
	CGUIControl* pParentDialog = parentID.findControl();
	CGUIControl* pChildDialog = childID.findControl();
	if (nullptr == pParentDialog || nullptr == pChildDialog)
	{
		return;
	}

	CGUIControl* pFrame = pParentDialog->findControl(name);
	if (pFrame)
	{
		pChildDialog->setClientPos(pFrame->getScreenRect());
	}
}