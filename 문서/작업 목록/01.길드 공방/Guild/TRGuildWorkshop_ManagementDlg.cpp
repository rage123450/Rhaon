/* ---------------------------------------------------------------
 *
 * Copyright 2019 by Rhaon Ent.
 *
 * TRGuildWorkshop_ManagementDlg.cpp
 *
 * 2019. 12. Han Younho
 *
 * ---------------------------------------------------------------
 */

#include "stdafx.h"
#include "TRGuildWorkshop_ManagementDlg.h"

#include "language/LanguageHeader.h"

#include "gameui/YesNoDialog.h"
#include "gameui/ClientItemInfoLoader.h"
#include "gameui/TRShortTimeMessage.h"

#include "gui/GUIItemImageCtrl.h"

#include "NetClientManager.h"
#include "TRGuildWorkshop_WarehouseDlg.h"
#include "TRGuildWorkshop_ExpenseDlg.h"
#include "TRGuildWorkshop_ProductionRegister.h"
#include "TRGuildWorkshop_GuideDlg.h"

namespace
{
	enum { ALL_BUTTON = 8 };
}

CTRGuildWorkshop_ManagementDlg::CTRGuildWorkshop_ManagementDlg()
	: m_dlgID(CGUIControlID::INVALID_ID), m_subDlgID(CGUIControlID::INVALID_ID)
	, m_guildPointDlgID(CGUIControlID::INVALID_ID), m_listDlgID(CGUIControlID::INVALID_ID)
	, m_itemDlgID(CGUIControlID::INVALID_ID), m_productionDlgID(CGUIControlID::INVALID_ID)
	, m_pLoader(nullptr), m_pWarehouseDlg(nullptr), m_pExpenseDlg(nullptr), m_pProductionRegisterDlg(nullptr), m_pGuideDlg(nullptr)
	, m_eCurItemCategory(eItemCategory_Supplies), m_eSelItemCategory(eItemCategory_None)
	, m_eCurConsumptionCategory(eRewardCondition_GUILD_POINT), m_eSelConsumptionCategory(eRewardCondition_NONE)
	, m_iGuildPoint(0), m_iGuildManagerTR(0)
	, m_iCurPage(1), m_iSelPage(-1), m_iMaxPage(1), m_iSelIndex(-1), m_iMyGuildPoint(0)
	, m_bClickWorkshopList(false), m_bClickLimitList(false)
{
	m_mapItemList.clear();
	m_mapPlantItemList.clear();
	m_mapStandByItemList.clear();

	m_vecListPiece.reserve(8);

	m_tCurItem.clear();
}

CTRGuildWorkshop_ManagementDlg::~CTRGuildWorkshop_ManagementDlg()
{
	closeDialog();
}

std::string CTRGuildWorkshop_ManagementDlg::getCurItemDistributeKindString()
{
	return _getDistributeKindString(_getSelectDistributeKind());
}

eGuildPlantDistributeKind CTRGuildWorkshop_ManagementDlg::getCurItemDistributeKindEnum()
{
	return eGuildPlantDistributeKind(_getSelectDistributeKind());
}

int CTRGuildWorkshop_ManagementDlg::getCurItemLimitBuyCount()
{
	return _getSelectLimitBuyCount();
}

bool CTRGuildWorkshop_ManagementDlg::isVisible() const
{
	CGUIControl* pDlg = m_dlgID.findControl();
	return pDlg ? pDlg->isVisible() : false;
}

bool CTRGuildWorkshop_ManagementDlg::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
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

	if ("SuppliesBtn" == name)
	{
		m_eCurItemCategory = eItemCategory_Supplies;

		_setButtonChecked(m_dlgID, name, true);
		_setButtonChecked(m_dlgID, "EquipmentBtn", false);
		_setButtonChecked(m_dlgID, "SpecialBtn", false);

		// ������ �з��� �������� ��, �Һ� ��ȭ �з��� ��� ����Ʈ�� ������ ���¸� �⺻���� �Ѵ�
		_setButtonChecked(m_subDlgID, "GuildPointBtn", true);
		_setButtonChecked(m_subDlgID, "GuildManageBtn", false);

		_setItemListByCategory(eRewardCondition_GUILD_POINT);

		return true;
	}
	else if ("EquipmentBtn" == name)
	{
		m_eCurItemCategory = eItemCategory_Equipment;

		_setButtonChecked(m_dlgID, "SuppliesBtn", false);
		_setButtonChecked(m_dlgID, name, true);
		_setButtonChecked(m_dlgID, "SpecialBtn", false);

		_setButtonChecked(m_subDlgID, "GuildPointBtn", true);
		_setButtonChecked(m_subDlgID, "GuildManageBtn", false);

		_setItemListByCategory(eRewardCondition_GUILD_POINT);

		return true;
	}
	else if ("SpecialBtn" == name)
	{
		m_eCurItemCategory = eItemCategory_Special;

		_setButtonChecked(m_dlgID, "SuppliesBtn", false);
		_setButtonChecked(m_dlgID, "EquipmentBtn", false);
		_setButtonChecked(m_dlgID, name, true);

		_setButtonChecked(m_subDlgID, "GuildPointBtn", true);
		_setButtonChecked(m_subDlgID, "GuildManageBtn", false);

		_setItemListByCategory(eRewardCondition_GUILD_POINT);

		return true;
	}
	else if (startswith(name, "GoodsItem"))
	{
		if (false == pCtrl->isVisible())
		{
			return false;
		}

		// -1�� �ϴ� ������ ��ư �̸� ���� ��ȣ�� 1���� �����ϱ� ����
		int index = atoi(name.substr(9).c_str()) - 1;
		if (0 > index || 8 <= index)
		{
			return true;
		}

		// ������ ���� ��ư�� Ŭ���� ��� ����
		if ((m_eCurItemCategory == m_eSelItemCategory)					&&
			(m_eCurConsumptionCategory == m_eSelConsumptionCategory)	&&
			(m_iCurPage == m_iSelPage)									&&
			(index == m_iSelIndex))
		{
			return true;
		}

		// ������ ������(+��ư) ����
		_setItem(index + ((m_iCurPage - 1) * 8));
		_setItemButtonChecked(index);

		m_eSelItemCategory = m_eCurItemCategory;
		m_eSelConsumptionCategory = m_eCurConsumptionCategory;

		m_iSelPage = m_iCurPage;
		m_iSelIndex = index;

		// ���õ� �����ۿ� �°� ���̾�α� ����
		_updateDistubeKindList();
		_updateCurrentItem();

		return true;
	}
	else if ("GuildPointBtn" == name)
	{
		_setButtonChecked(m_subDlgID, name, true);
		_setButtonChecked(m_subDlgID, "GuildManageBtn", false);

		_setItemListByCategory(eRewardCondition_GUILD_POINT);

		return true;
	}
	else if ("GuildManageBtn" == name)
	{
		_setButtonChecked(m_subDlgID, "GuildPointBtn", false);
		_setButtonChecked(m_subDlgID, name, true);

		_setItemListByCategory(eRewardCondition_GUILD_MANAGER_TR);

		return true;
	}
	else if ("Workshop_List" == name)
	{
		if (m_bClickWorkshopList)
		{
			// ���õ� �������� ���ų� �߸��� ������ ��� ����
			if (false == isValidIndexItemNum(m_tCurItem.iIndex))
			{
				m_bClickWorkshopList = false;
				return true;
			}

			// ���� ��� �з�(������ ���� ����, 30��, 15��, 7��, ������) ���� Ȯ��
			int distributeKind = _getSelectDistributeKind();
			if (distributeKind == eGuildPlantDistributeKind_NONE)
			{
				m_bClickLimitList = false;
				return true;
			}

			_updateLimitBuyCountList(distributeKind);
			_updateCurrentItem();

			m_bClickWorkshopList = false;
		}

		return true;
	}
	else if ("LimitList" == name)
	{
		if (m_bClickLimitList)
		{
			// ���õ� �������� ���ų� �߸��� ������ ��� ����
			if (false == isValidIndexItemNum(m_tCurItem.iIndex))
			{
				m_bClickWorkshopList = false;
				return true;
			}

			// �ִ� �Ǹ� ���� Ȯ��
			int iLimitBuyCount = _getSelectLimitBuyCount();
			if (iLimitBuyCount == 0)
			{
				m_bClickLimitList = false;
				return true;
			}

			_updateCurrentItem();

			m_bClickLimitList = false;
		}

		return true;
	}
	else if ("ManageBtn" == name)
	{
		if (nullptr == m_pWarehouseDlg)
		{
			m_pWarehouseDlg = new CTRGuildWorkshop_WarehouseDlg;
		}

		m_pWarehouseDlg->showDialog();

		return true;
	}
	else if ("ExpenseBtn" == name)
	{
		if (nullptr == m_pExpenseDlg)
		{
			m_pExpenseDlg = new CTRGuildWorkshop_ExpenseDlg;
		}

		m_pExpenseDlg->showDialog();

		return true;
	}
	else if ("GuideBtn" == name)
	{
		if (nullptr == m_pGuideDlg)
		{
			m_pGuideDlg = new CTRGuildWorkshop_GuideDlg;
			m_pGuideDlg->LoadGuideList(m_pLoader);
		}

		m_pGuideDlg->showDialog();

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

		_setItemListByCategory(m_eCurConsumptionCategory, m_iCurPage);

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

		_setItemListByCategory(m_eCurConsumptionCategory, m_iCurPage);

		return true;
	}
	else if ("productionBtn" == name)
	{
		// ���� ��� ��ư�� ������ �������� �Ǹ� ���ݺ��� ������ ��ȭ�� ���� ���� Ȱ��ȭ
		// Ȱ��ȭ�� ���� ������ ���ʿ� �Լ��� ������ ������ Ȥ�� ���� ����ó��
		if (pCtrl->isVisible())
		{
			if (nullptr == m_pProductionRegisterDlg)
			{
				m_pProductionRegisterDlg = new CTRGuildWorkshop_ProductionRegister(this);
			}

			m_pProductionRegisterDlg->showDialog(&m_tCurItem);
		}

		return true;
	}
	else if ("Close" == name)
	{
		m_pLoader = nullptr;

		closeDialog();

		return true;
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRGuildWorkshop_ManagementDlg::onButtonEventNotify(CGUIButton* pButton, GUI_MOUSE_EVENT event)
{
	if (false == isVisible() || nullptr == pButton)
	{
		return;
	}

	std::string name = pButton->getName();

	switch (event)
	{
	case GUI_MOUSE_EVENT_LBUTTON_DOWN:
		// �� ��ư�� ���ȴٴ� ���� ��� �ڽ��� �����ٴ� ��
		// �� ���¿��� ��� �ڽ� ��ư �̺�Ʈ�� ��(onButtonClick �Լ�)���� �߻��ϸ� ������ ���ŵǾ��� ���� ����
		// �ǽð� ���� ������ ���� bool ���� Ȱ��
		if ("WorkshopListBtn" == name)
		{
			if (false == m_bClickWorkshopList)
			{
				m_bClickWorkshopList = true;
			}

			return;
		}
		else if ("LimitListBtn" == name)
		{
			if (false == m_bClickLimitList)
			{
				m_bClickLimitList = true;
			}

			return;
		}

		break;
	}
}

void CTRGuildWorkshop_ManagementDlg::showDialog()
{
	closeDialog();

	std::string errmsg;

	CGUIDialog* pDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_ManagementBase.gui", errmsg);
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

	_setSubDialog();
	_setGuildPointDialog();
	_setListDialog();
	_setListPieceDialog();
	_setItemDialog();
	_setProductionDialog();

	// �ϴ� ù ȭ���� �Һ�ǰ, ��� ����Ʈ ù �������� �ʱ�ȭ
	_setButtonChecked(m_dlgID, "SuppliesBtn", true);
	_setButtonChecked(m_subDlgID, "GuildPointBtn", true);

	_setItemListByCategory(m_eCurConsumptionCategory);

	// ������ ��ư�� �������� ���� ���·� �ʱ�ȭ
	_setItemButtonChecked(ALL_BUTTON);
}

void CTRGuildWorkshop_ManagementDlg::closeDialog()
{
	m_bClickWorkshopList = false;
	m_bClickLimitList = false;

	m_iCurPage = 1;
	m_iSelPage = -1;
	m_iMaxPage = 1;
	m_iSelIndex = -1;

	m_eCurItemCategory = eItemCategory_Supplies;
	m_eSelItemCategory = eItemCategory_None;
	m_eCurConsumptionCategory = eRewardCondition_GUILD_POINT;
	m_eSelConsumptionCategory = eRewardCondition_NONE;

	m_tCurItem.clear();

	for (auto& ctrlID : m_vecListPiece)
	{
		CGUIControl* pListPiece = ctrlID.findControl();
		if (pListPiece)
		{
			pListPiece->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		}
	}

	m_vecListPiece.clear();

	SAFE_DELETE(m_pWarehouseDlg);
	SAFE_DELETE(m_pExpenseDlg);
	SAFE_DELETE(m_pProductionRegisterDlg);
	SAFE_DELETE(m_pGuideDlg);

	CGUIControl* pListDlg = m_listDlgID.findControl();
	if (pListDlg)
	{
		pListDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_listDlgID = CGUIControlID::INVALID_ID;
	}

	CGUIControl* pItemtDlg = m_itemDlgID.findControl();
	if (pItemtDlg)
	{
		pItemtDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_itemDlgID = CGUIControlID::INVALID_ID;
	}

	CGUIControl* pProductionDlg = m_productionDlgID.findControl();
	if (pProductionDlg)
	{
		pProductionDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_productionDlgID = CGUIControlID::INVALID_ID;
	}

	CGUIControl* pGuildPointDlg = m_guildPointDlgID.findControl();
	if (pGuildPointDlg)
	{
		pGuildPointDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_guildPointDlgID = CGUIControlID::INVALID_ID;
	}

	CGUIControl* pSubDlg = m_subDlgID.findControl();
	if (pSubDlg)
	{
		pSubDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_subDlgID = CGUIControlID::INVALID_ID;
	}

	CGUIControl* pDlg = m_dlgID.findControl();
	if (pDlg)
	{
		pDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_dlgID = CGUIControlID::INVALID_ID;
	}
}

void CTRGuildWorkshop_ManagementDlg::onRecvCurrentGuildPoint(__int64 iGuildPt)
{
	if (0 > iGuildPt)
	{
		iGuildPt = 0;
	}

	m_iGuildPoint = iGuildPt;

	_setStaticText(m_guildPointDlgID, "Guild_Point", format("%d", iGuildPt));
}

void CTRGuildWorkshop_ManagementDlg::onRecvCurrentMyGuildPoint(int iMyGuildPt)
{
	if (0 > iMyGuildPt)
	{
		iMyGuildPt = 0;
	}

	m_iMyGuildPoint = iMyGuildPt;

	_setStaticText(m_guildPointDlgID, "MyGuild_Point", format("%d", m_iMyGuildPoint));
}

void CTRGuildWorkshop_ManagementDlg::onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR)
{
	if (0 > iGuildManagerTR)
	{
		iGuildManagerTR = 0;
	}

	m_iGuildManagerTR = iGuildManagerTR;

	_setStaticText(m_guildPointDlgID, "GuildManage_Point", format("%d", m_iGuildManagerTR));

	if (m_pWarehouseDlg && m_pWarehouseDlg->isVisible())
	{
		m_pWarehouseDlg->onRecvGuildPlantGetGuildManagerTR(iGuildManagerTR);
	}
}

void CTRGuildWorkshop_ManagementDlg::onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR)
{
	if (m_pWarehouseDlg && m_pWarehouseDlg->isVisible())
	{
		m_pWarehouseDlg->onRecvGuildPlantInvestGuildManagerTR(iGuildManagerTR);
	}
}

void CTRGuildWorkshop_ManagementDlg::onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue)
{
	if (m_pWarehouseDlg)
	{
		m_pWarehouseDlg->onRecvGuildPlantGetStorageExtendOK(iExtendCount, iExtendValue, iUserInvestCount, iUserInvestValue);
	}
}

void CTRGuildWorkshop_ManagementDlg::onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR)
{
	int iGuildNum = CNetClientManager::getInstance().getMyGuildNum();

	// �Ҹ��� ����Ʈ ���� ��û
	if (eRewardCondition_GUILD_POINT == m_tCurItem.iRegisterPointKind)
	{
		CNetClientManager::getInstance().requestGuild_getGuildPoint(iGuildNum);
	}
	else if (eRewardCondition_GUILD_MANAGER_TR == m_tCurItem.iRegisterPointKind)
	{
		CNetClientManager::getInstance().requestGetGuildPlantManagerTR(iGuildNum);
	}

	// ������ ���� ��Ͽ� �����ϸ�, ��ϵ� �������� �����̳ʿ��� �����ش�
	removeItem(m_tCurItem.iCategory, m_tCurItem.iRegisterPointKind, m_tCurItem.iIndex);

	CTRShortTimeMessage::getInstance().showMessage(_STR(GUILD_PLANT_ITEM_PRODUCTION_START));
}

void CTRGuildWorkshop_ManagementDlg::onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList)
{
	if (m_pWarehouseDlg)
	{
		m_pWarehouseDlg->onRecvGuildPlantGetInvestorManagerTRListOK(userList);
	}
}

void CTRGuildWorkshop_ManagementDlg::onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList)
{
	if (m_pExpenseDlg)
	{
		m_pExpenseDlg->onRecvGuildPlantGetExpenseListOK(pointType, iMonth, useList);
	}
}

void CTRGuildWorkshop_ManagementDlg::onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList)
{
	m_mapPlantItemList.clear();

	if (useList.empty())
	{
		return;
	}

	for (auto& pair : useList)
	{
		GuildPlantSellInfo itemInfo(pair.second);

		m_mapPlantItemList.insert(std::make_pair(itemInfo.m_iItemIndexNum, itemInfo.m_iItemIndexNum));
	}
}

void CTRGuildWorkshop_ManagementDlg::onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant)
{
	m_mapStandByItemList.clear();

	if (guildplant.empty())
	{
		return;
	}

	for (auto& pair : guildplant)
	{
		GuildPlantMakeInfo itemInfo(pair.second);

		m_mapStandByItemList.insert(std::make_pair(itemInfo.m_iItemIndexNum, itemInfo.m_iItemIndexNum));
	}
}

void CTRGuildWorkshop_ManagementDlg::loadItemList(CTRGuildPlanInfoLoader* pLoader)
{
	if (nullptr == pLoader)
	{
		return;
	}

	m_pLoader = pLoader;

	auto& mapItemList = m_pLoader->getPlantItemList();
	if (mapItemList.empty())
	{
		return;
	}

	m_mapItemList.clear();

	for (auto& pair : mapItemList)
	{
		GuildPlantItemInfo itemInfo(*pair.second);

		// �����濡 ��ϵ� �������̸� ����
		if (-1 != _findPlantItemList(itemInfo.iIndex))
		{
			continue;
		}

		// ���� ������� �������̶�� ���� (�������� ������ ����)
		if (-1 != _findStandByItemList(itemInfo.iIndex))
		{
			continue;
		}

		m_mapItemList[itemInfo.iCategory][itemInfo.iRegisterPointKind].push_back(itemInfo);
	}
}

void CTRGuildWorkshop_ManagementDlg::updateItemList()
{
	_setPage(m_eCurItemCategory, m_eCurConsumptionCategory);
	_setItemListByCategory(m_eCurConsumptionCategory, m_iCurPage);
}

void CTRGuildWorkshop_ManagementDlg::removeItem(int iItemCategory, int iConsumptionCategory, int iItemIndex)
{
	if ((eItemCategory_Supplies > iItemCategory || eItemCategory_End <= iItemCategory) ||
		(eRewardCondition_GUILD_POINT > iConsumptionCategory || eRewardCondition_GUILD_MANAGER_TR < iConsumptionCategory))
	{
		return;
	}

	auto& vecItemInfo = m_mapItemList[iItemCategory][iConsumptionCategory];

	for (size_t i = 0; i < vecItemInfo.size(); ++i)
	{
		if (vecItemInfo[i].iIndex == iItemIndex)
		{
			m_mapStandByItemList.insert(std::make_pair(vecItemInfo[i].iIndex, vecItemInfo[i].iIndex));

			vecItemInfo.erase(vecItemInfo.begin() + i);

			break;
		}
	}

	m_tCurItem.clear();

	m_eSelItemCategory = eItemCategory_None;
	m_eSelConsumptionCategory = eRewardCondition_NONE;

	m_iSelPage = -1;
	m_iSelIndex = -1;

	updateItemList();

	CGUIControl* pCtrl = m_productionDlgID.findControl();
	if (pCtrl)
	{
		// ��� ����Ʈ �ʱ�ȭ
		CGUIComboBoxDropList* pDropList = static_cast<CGUIComboBoxDropList*>(pCtrl->findControl("Workshop_List"));
		if (pDropList)
		{
			pDropList->deleteAllItem();
			pDropList->unDropListBox();
		}

		pDropList = static_cast<CGUIComboBoxDropList*>(pCtrl->findControl("LimitList"));
		if (pDropList)
		{
			pDropList->deleteAllItem();
			pDropList->unDropListBox();
		}

		// ���� ���õ� �Һ� ��ȭ ��ư�� ���� ��ȭ ǥ�� �ʱ�ȭ
		if (eRewardCondition_GUILD_POINT == m_eCurConsumptionCategory)
		{
			_setStaticText(m_productionDlgID, "GuildPoint", format("%d %s", 0, _STR(MONEY_GP)));
		}
		else if (eRewardCondition_GUILD_MANAGER_TR == m_eCurConsumptionCategory)
		{
			_setStaticText(m_productionDlgID, "GuildPoint", format("%d %s", 0, _STR(MONEY_TR)));
		}

		// ���۵�� ��ư �����
		CGUIButton* pButton = static_cast<CGUIButton*>(pCtrl->findControl("productionBtn"));
		if (pButton)
		{
			pButton->setVisible(false);
		}
	}

	// ���� ������ ���̾�α� �ʱ�ȭ
	pCtrl = m_itemDlgID.findControl();
	if (pCtrl)
	{
		_setStaticText(m_itemDlgID, "TypeMent", "");
		_setStaticText(m_itemDlgID, "GoodsName", "");
		_setStaticText(m_itemDlgID, "Day", "");

		CGUIItemImageCtrl* pImage = static_cast<CGUIItemImageCtrl*>(pCtrl->findControl("Image"));
		if (pImage)
		{
			pImage->setImage(nullptr);
		}
	}
}

bool CTRGuildWorkshop_ManagementDlg::isValidIndexItemNum(int iIndexItemnum)
{
	return m_pLoader ? m_pLoader->isValidIndexItemNum(iIndexItemnum) : false;
}

void CTRGuildWorkshop_ManagementDlg::_setItem(int index)
{
	if (0 > index || m_mapItemList[m_eCurItemCategory][m_eCurConsumptionCategory].size() <= static_cast<size_t>(index))
	{
		DBG_DEMO_OUTPUT("%s - Reason[%d]", __FUNCTION__, index);
		return;
	}

	// ������ ���� �ִ� ������ ���� ���� �� �ʱ�ȭ
	m_tCurItem.clear();
	m_tCurItem = m_mapItemList[m_eCurItemCategory][m_eCurConsumptionCategory][index];
}

void CTRGuildWorkshop_ManagementDlg::_setSubDialog()
{
	std::string errmsg;

	CGUIDialog* pSubDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_ManagementInBase.gui", errmsg);
	if (nullptr == pSubDlg)
	{
		return;
	}

	m_subDlgID = pSubDlg->getControlID();

	_setClientPos(m_dlgID, m_subDlgID, "Workshop_ManagementInBase");
	pSubDlg->setDialogListener(getCommandTargetID());
	pSubDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
}

void CTRGuildWorkshop_ManagementDlg::_setGuildPointDialog()
{
	std::string errmsg;

	CGUIDialog* pGuildPointDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_GuildPointDlg.gui", errmsg);
	if (nullptr == pGuildPointDlg)
	{
		return;
	}

	m_guildPointDlgID = pGuildPointDlg->getControlID();

	_setClientPos(m_dlgID, m_guildPointDlgID, "Workshop_GuildPointDlg");
	pGuildPointDlg->setDialogListener(getCommandTargetID());
	pGuildPointDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));

	// TRGuildWorkshop_PopupDlg�� �� �� ��û�Ͽ� �� �� �ʱ�ȭ������
	// TRGuildWorkshop_ManagementDlg�� ���� ���� ����Ʈ ������ ���� �� �����Ƿ� �� �� �� ��û�ؼ� ����
	int iGuildNum = CNetClientManager::getInstance().getMyGuildNum();
	CNetClientManager::getInstance().requestGuild_getGuildPoint(iGuildNum);				// ��� ����Ʈ ��û
	CNetClientManager::getInstance().requestGuild_getGuildContributionPoint(iGuildNum);	// ���� ��� ����Ʈ ��û
	CNetClientManager::getInstance().requestGetGuildPlantManagerTR(iGuildNum);			// ��� � TR ��û
}

void CTRGuildWorkshop_ManagementDlg::_setListDialog()
{
	std::string errmsg;

	CGUIDialog* pListDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_ManagementItemListDlg.gui", errmsg);
	if (nullptr == pListDlg)
	{
		return;
	}

	m_listDlgID = pListDlg->getControlID();

	_setClientPos(m_subDlgID, m_listDlgID, "Workshop_ManagementItemListDlg");
	pListDlg->setDialogListener(getCommandTargetID());
	pListDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));

	_setStaticText(m_listDlgID, "PageNum", format("%d / %d", m_iCurPage, m_iMaxPage));
}

void CTRGuildWorkshop_ManagementDlg::_setListPieceDialog()
{
	std::string errmsg;

	for (int i = 0; i < 8; ++i)
	{
		CGUIDialog* pListPiece = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_ManagementItemListPiece.gui", errmsg);
		if (pListPiece)
		{
			CGUIControlID ctrlID = pListPiece->getControlID();

			_setClientPos(m_listDlgID, ctrlID, format("GoodsItem%d", i + 1));
			pListPiece->setDialogListener(getCommandTargetID());
			pListPiece->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f));

			// ��ư ������ �ϳ��� ���̾�α��̹Ƿ� ���� �̸��� ����. �׷��� ������ �ڿ� �ٿ��ش�
			CGUIButton* pButton = static_cast<CGUIButton*>(pListPiece->findControl("GoodsBtn"));
			if (pButton)
			{
				pButton->setName(format("GoodsItem%d", i + 1));
			}

			m_vecListPiece.push_back(ctrlID);
		}
	}
}

void CTRGuildWorkshop_ManagementDlg::_setItemDialog()
{
	std::string errmsg;

	CGUIDialog* pItemDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_SelectItemDlg.gui", errmsg);
	if (nullptr == pItemDlg)
	{
		return;
	}

	m_itemDlgID = pItemDlg->getControlID();

	_setClientPos(m_subDlgID, m_itemDlgID, "Workshop_SelectItemDlg");
	pItemDlg->setDialogListener(getCommandTargetID());
	pItemDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));

	_setStaticText(m_itemDlgID, "TypeMent", "");
	_setStaticText(m_itemDlgID, "GoodsName", "");
	_setStaticText(m_itemDlgID, "Day", "");
}

void CTRGuildWorkshop_ManagementDlg::_setProductionDialog()
{
	std::string errmsg;

	CGUIDialog* pProductionDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_ManagementProductionDlg.gui", errmsg);
	if (nullptr == pProductionDlg)
	{
		return;
	}

	m_productionDlgID = pProductionDlg->getControlID();

	_setClientPos(m_subDlgID, m_productionDlgID, "Workshop_productionDlg");
	pProductionDlg->setDialogListener(getCommandTargetID());
	pProductionDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));

	CGUIComboBoxDropList* pDropList = static_cast<CGUIComboBoxDropList*>(pProductionDlg->findControl("Workshop_List"));
	if (pDropList)
	{
		pDropList->deleteAllItem();
		pDropList->unDropListBox();

		// ��� �ڽ��� ���� ��ư�� ���� �̺�Ʈ ���. �̸��� ���� ������ ���Ƿ� �����ش�
		CGUIButton* pButton = pDropList->getButton();
		if (pButton)
		{
			pButton->setName("WorkshopListBtn");
			pButton->setEventNotifyListener(this);
		}
	}

	pDropList = static_cast<CGUIComboBoxDropList*>(pProductionDlg->findControl("LimitList"));
	if (pDropList)
	{
		pDropList->deleteAllItem();
		pDropList->unDropListBox();

		CGUIButton* pButton = pDropList->getButton();
		if (pButton)
		{
			pButton->setName("LimitListBtn");
			pButton->setEventNotifyListener(this);
		}
	}

	_setStaticText(m_productionDlgID, "GuildPoint", format("0 %s", _STR(MONEY_GP)));

	// ���� ��� ��ư�� �ϴ� ��Ȱ��ȭ (������ �̼����� ����)
	CGUIButton* pButton = static_cast<CGUIButton*>(pProductionDlg->findControl("productionBtn"));
	if (pButton)
	{
		pButton->setVisible(false);
	}
}

void CTRGuildWorkshop_ManagementDlg::_updateDistubeKindList(int iSelect)
{
	if (m_productionDlgID == CGUIControlID::INVALID_ID)		return;
	CGUIDialog* pDlg = (CGUIDialog*)(m_productionDlgID.findControl());
	if (pDlg == NULL)	return;

	CGUIComboBoxDropList* pDropList = static_cast<CGUIComboBoxDropList*>(pDlg->findControl("Workshop_List", GUI_SUB_CONTROL_COMBO_BOX_DROPLIST));
	if (pDropList)
	{
		pDropList->deleteAllItem();

		if (m_pLoader)
		{
			std::vector<int> vecDistributeKind = m_pLoader->getDistributeKind(m_tCurItem.iIndex, m_tCurItem.iRegisterPointKind);
			if (!vecDistributeKind.empty())
			{
				for (auto& iKind : vecDistributeKind)
				{
					if (iKind == eGuildPlantDistributeKind_GIFT_MASTER)
						pDropList->addString(_STR(GUILD_PLANT_DISTRIBUTE_KIND_4));
					else if (iKind == eGuildPlantDistributeKind_SELL_DAY30)
						pDropList->addString(_STR(GUILD_PLANT_DISTRIBUTE_KIND_1));
					else if (iKind == eGuildPlantDistributeKind_SELL_DAY15)
						pDropList->addString(_STR(GUILD_PLANT_DISTRIBUTE_KIND_2));
					else if (iKind == eGuildPlantDistributeKind_SELL_DAY7)
						pDropList->addString(_STR(GUILD_PLANT_DISTRIBUTE_KIND_3));
					else if (iKind == eGuildPlantDistributeKind_SELL_FOREVER)
						pDropList->addString(_STR(GUILD_PLANT_DISTRIBUTE_KIND_5));
				}
			}
		}

		// ������ ������ �°�, �������� ���� ��� ����Ʈ ���� ����
		// +1�� ������ EditControl �κб��� �����ϱ� ����
		int height = pDropList->getListBox()->getItemHeight() * (pDropList->getNumItems() + 1);
		pDropList->setListBoxHeight(height);

		pDropList->setSelected(iSelect);
		pDropList->unDropListBox();
	}

	_updateLimitBuyCountList(_getSelectDistributeKind());
}

void CTRGuildWorkshop_ManagementDlg::_updateLimitBuyCountList(int iDistubeKind)
{
	if (m_productionDlgID == CGUIControlID::INVALID_ID)		return;
	CGUIDialog* pDlg = (CGUIDialog*)(m_productionDlgID.findControl());
	if (pDlg == NULL)	return;

	if (iDistubeKind == eGuildPlantDistributeKind_NONE)	return;

	CGUIComboBoxDropList* pDropList = static_cast<CGUIComboBoxDropList*>(pDlg->findControl("LimitList", GUI_SUB_CONTROL_COMBO_BOX_DROPLIST));
	if (pDropList)
	{
		pDropList->deleteAllItem();

		if (m_pLoader)
		{
			std::vector<int> vecLimitBuyCount = m_pLoader->getLimtBuyCount(m_tCurItem.iIndex, iDistubeKind, m_tCurItem.iRegisterPointKind);
			if (!vecLimitBuyCount.empty())
			{
				for (auto& iCount : vecLimitBuyCount)
				{
					if (iCount == -1)
						pDropList->addString(_STR(ITEM_MSG_UNLIMITED));
					else
						pDropList->addString(format("%d", iCount));
				}
			}
		}

		// ������ ������ �°�, �������� ���� ��� ����Ʈ ���� ����
		// +1�� ������ EditControl �κб��� �����ϱ� ����
		int height = pDropList->getListBox()->getItemHeight() * (pDropList->getNumItems() + 1);
		pDropList->setListBoxHeight(height);

		pDropList->setSelected(0);
		pDropList->unDropListBox();
	}

	_setStaticText(m_productionDlgID, "GuildPoint", format("0 %s", _STR(MONEY_GP)));
}

void CTRGuildWorkshop_ManagementDlg::_updateCurrentItem()
{
	CGUIDialog* pItemDlg = static_cast<CGUIDialog*>(m_itemDlgID.findControl());
	if (pItemDlg == NULL)		return;

	CGUIDialog* pProductionDlg = (CGUIDialog*)(m_productionDlgID.findControl());
	if (pProductionDlg == NULL)	return;

	const CItemInfoNode* pItem = CClientItemList::getInstance().getRealItemInfo(m_tCurItem.iItemNum);
	if (pItem)
	{
		int iDistributeKind = _getSelectDistributeKind();

		_setStaticText(m_itemDlgID, "GoodsName", pItem->m_name);
		_setStaticText(m_itemDlgID, "TypeMent", _getDistributeKindString(iDistributeKind));
		_setStaticText(m_itemDlgID, "Day", format("%s: %d%s", _STR(PRODUCTION_PERIOD), m_tCurItem.iDurationDay, _STR(ITEM_TIME_DAY)));

		CGUIItemImageCtrl* pImage = static_cast<CGUIItemImageCtrl*>(pItemDlg->findControl("Image"));
		if (pImage)
		{
			pImage->setRealItemImage(pItem);
		}

 		// ���� ������ �ε����� ���� ��� �з��� ���� ���ۿ� �ʿ��� ����Ʈ�� ������ ����ü�� �޾ƿ´�
		int needPoint = _getRegisterNeedPoint();

		// �Һ� ��ȭ �з��� ���� �ؽ�Ʈ ����
		if (eRewardCondition_GUILD_POINT == m_tCurItem.iRegisterPointKind)
		{
			_setStaticText(m_productionDlgID, "CustomPoint", _STR(GUILD_PLANT_COMSUME_GP));
			_setStaticText(m_productionDlgID, "GuildPoint", format("%d %s", needPoint, _STR(MONEY_GP)));
		}
		else if (eRewardCondition_GUILD_MANAGER_TR == m_tCurItem.iRegisterPointKind)
		{
			_setStaticText(m_productionDlgID, "CustomPoint", _STR(GUILD_PLANT_COMSUME_TR));
			_setStaticText(m_productionDlgID, "GuildPoint", format("%d %s", needPoint, _STR(MONEY_TR)));
		}

		// ��ȭ �˻� ��, ������ ������ ���(���� ����Ʈ�� ��� ����Ʈ���� ���ų� ���� ���) ��ư�� ���̰� �Ѵ�
		_checkForProductionRegistItem(needPoint);
	}
}

int CTRGuildWorkshop_ManagementDlg::_getSelectDistributeKind()
{
	if (m_productionDlgID == CGUIControlID::INVALID_ID)
		return eGuildPlantDistributeKind_NONE;

	CGUIDialog* pDlg = (CGUIDialog*)(m_productionDlgID.findControl());
	if (pDlg == NULL)
		return eGuildPlantDistributeKind_NONE;

	CGUIComboBoxDropList* pDropList = static_cast<CGUIComboBoxDropList*>(pDlg->findControl("Workshop_List", GUI_SUB_CONTROL_COMBO_BOX_DROPLIST));
	if (pDropList)
	{
		std::string strDistributeKind;
		pDropList->getSelectedItem(strDistributeKind);

		_setStaticText(m_itemDlgID, "TypeMent", strDistributeKind);

		if (_STR(GUILD_PLANT_DISTRIBUTE_KIND_4) == strDistributeKind)
		{
			return eGuildPlantDistributeKind_GIFT_MASTER;
		}
		else if (_STR(GUILD_PLANT_DISTRIBUTE_KIND_5) == strDistributeKind)
		{
			return eGuildPlantDistributeKind_SELL_FOREVER;
		}
		else if (_STR(GUILD_PLANT_DISTRIBUTE_KIND_1) == strDistributeKind)
		{
			return eGuildPlantDistributeKind_SELL_DAY30;
		}
		else if (_STR(GUILD_PLANT_DISTRIBUTE_KIND_2) == strDistributeKind)
		{
			return eGuildPlantDistributeKind_SELL_DAY15;
		}
		else if (_STR(GUILD_PLANT_DISTRIBUTE_KIND_3) == strDistributeKind)
		{
			return eGuildPlantDistributeKind_SELL_DAY7;
		}
	}

	return eGuildPlantDistributeKind_NONE;
}

int CTRGuildWorkshop_ManagementDlg::_getSelectLimitBuyCount()
{
	if (m_productionDlgID == CGUIControlID::INVALID_ID)
		return 0;

	CGUIDialog* pDlg = (CGUIDialog*)(m_productionDlgID.findControl());
	if (pDlg == NULL)
		return 0;

	CGUIComboBoxDropList* pDropList = static_cast<CGUIComboBoxDropList*>(pDlg->findControl("LimitList", GUI_SUB_CONTROL_COMBO_BOX_DROPLIST));
	if (pDropList)
	{
		std::string strLimitBuyCount;
		pDropList->getSelectedItem(strLimitBuyCount);

		if (_STR(ITEM_MSG_UNLIMITED) == strLimitBuyCount)
		{
			return -1;
		}
		else
		{
			return atoi(strLimitBuyCount.c_str());
		}
	}

	return 0;
}

int CTRGuildWorkshop_ManagementDlg::_getRegisterNeedPoint()
{
	int iNeedPoint = 0;
	if (m_pLoader)
		iNeedPoint = m_pLoader->getNeedPoint(m_tCurItem.iIndex, _getSelectDistributeKind(), _getSelectLimitBuyCount(), m_tCurItem.iRegisterPointKind);

	return iNeedPoint;
}

std::string CTRGuildWorkshop_ManagementDlg::_getDistributeKindString(int iDistributeKind)
{
	std::string strValue;
	switch (iDistributeKind)
	{
	case eGuildPlantDistributeKind_GIFT_MASTER:
		strValue = _STR(GUILD_PLANT_DISTRIBUTE_KIND_4);
		break;
	case eGuildPlantDistributeKind_SELL_DAY30:
		strValue = _STR(GUILD_PLANT_DISTRIBUTE_KIND_1);
		break;
	case eGuildPlantDistributeKind_SELL_DAY15:
		strValue = _STR(GUILD_PLANT_DISTRIBUTE_KIND_2);
		break;
	case eGuildPlantDistributeKind_SELL_DAY7:
		strValue = _STR(GUILD_PLANT_DISTRIBUTE_KIND_3);
		break;
	case eGuildPlantDistributeKind_SELL_FOREVER:
		strValue = _STR(GUILD_PLANT_DISTRIBUTE_KIND_5);
		break;
	default:
		break;
	}
	return strValue;
}

void CTRGuildWorkshop_ManagementDlg::_setPage()
{
	if (1 > m_iCurPage)
	{
		m_iCurPage = 1;
	}

	if (1 > m_iMaxPage)
	{
		m_iMaxPage = 1;
	}

	if (m_iMaxPage < m_iCurPage)
	{
		m_iCurPage = m_iMaxPage;
	}

	_setStaticText(m_listDlgID, "PageNum", format("%d / %d", m_iCurPage, m_iMaxPage));
}

void CTRGuildWorkshop_ManagementDlg::_setPage(eItemCategory eItemCategory, eRewardCondition eConsumptionCategory)
{
	if ((eRewardCondition_GUILD_POINT > eConsumptionCategory || eRewardCondition_GUILD_MANAGER_TR < eConsumptionCategory) ||
		(eItemCategory_Supplies > eItemCategory || eItemCategory_End <= eItemCategory))
	{
		return;
	}

	m_iCurPage = 1;

	int maxPage = 1;

	if (m_mapItemList[eItemCategory][eConsumptionCategory].size())
	{
		// �� ȭ�鿡 ���� ���� �������� ���Ƿ� ������ ���� ���� ���� ������
		// �� ������ 0�̶�� ���� ������ ������ 8�� �̸��̶�� �� (1page�� ����)
		if (m_mapItemList[eItemCategory][eConsumptionCategory].size() / 8)
		{
			// �� ������ �̻� �����ϴµ� �������� 0�̶�� ���� �������� 8�� ���(1page ����)��ŭ �����Ѵٴ� ��
			if (0 == m_mapItemList[eItemCategory][eConsumptionCategory].size() % 8)
			{
				maxPage = m_mapItemList[eItemCategory][eConsumptionCategory].size() / 8;
			}
			// �׷��� �ʴٸ� ���� �������� �Ѿ��
			// ����, ���� 1(page == ������ 8�� �̻�)�� ��Ȳ���� �������� ������ ��쿡�� �������� (8, 16]����� ��
			else
			{
				maxPage = (m_mapItemList[eItemCategory][eConsumptionCategory].size() / 8) + 1;
			}
		}
	}

	m_iMaxPage = maxPage;
}

void CTRGuildWorkshop_ManagementDlg::_setItemListByCategory(eRewardCondition eConsumptionCategory)
{
	_setPage(m_eCurItemCategory, eConsumptionCategory);
	_setItemListByCategory(eConsumptionCategory, m_iCurPage);
}

void CTRGuildWorkshop_ManagementDlg::_setItemListByCategory(eRewardCondition eConsumptionCategory, int page)
{
	if ((1 > page || m_iMaxPage < page) ||
		(eRewardCondition_GUILD_POINT > eConsumptionCategory || eRewardCondition_GUILD_MANAGER_TR < eConsumptionCategory))
	{
		return;
	}

	m_eCurConsumptionCategory = eConsumptionCategory;

	auto& vecItemInfo = m_mapItemList[m_eCurItemCategory][m_eCurConsumptionCategory];
	if (vecItemInfo.empty())
	{
		// ���� �������� �������� ���� ���, ������ ��ư ���� ��Ȱ��ȭ
		for (auto& ctrlID : m_vecListPiece)
		{
			CGUIControl* pListPiece = ctrlID.findControl();
			if (pListPiece && pListPiece->isVisible())
			{
				pListPiece->setVisible(false);
			}
		}

		_setPage();

		return;
	}

	size_t i = 0;
	size_t index = (page - 1) * 8;

	// i�� ������ ��ư ����Ʈ �ε���(0 ~ m_vecListPiece.size())
	// index�� ������ �����̳��� �ε���(0 ~ m_mapItemList[m_eCurItemCategory][m_eCurConsumptionCategory].size())
	while (m_vecListPiece.size() > i && vecItemInfo.size() > index)
	{
		CGUIControl* pListPiece = m_vecListPiece[i].findControl();
		if (pListPiece)
		{
			pListPiece->setVisible(true);

			const CItemInfoNode* pItemInfo = CClientItemList::getInstance().getRealItemInfo(vecItemInfo[index].iItemNum);
			if (pItemInfo)
			{
				CGUIItemImageCtrl* pItemImage = static_cast<CGUIItemImageCtrl*>(pListPiece->findControl("Image"));
				if (pItemImage)
				{
					pItemImage->setRealItemImage(pItemInfo);
				}

				_setStaticText(m_vecListPiece[i], "GoodsName", pItemInfo->m_name);
			}
		}

		++index;
		++i;
	}

	// ���� ������ ���� ������ ��ư ������ ���� ���� ���� ���, �� ������ ��ư���� ��Ȱ��ȭ
	if (0 <= i && m_vecListPiece.size() > i)
	{
		for (size_t j = i; j < m_vecListPiece.size(); ++j)
		{
			CGUIControl* pListPiece = m_vecListPiece[j].findControl();
			if (pListPiece && pListPiece->isVisible())
			{
				pListPiece->setVisible(false);
			}
		}
	}

	_setPage();

	// ������ �������� �����ϴ� ���������� Ȯ���ϰ�, �´� ��� ������ �������� üũ ���·� �����
	if ((m_eCurItemCategory == m_eSelItemCategory)					&&
		(m_eCurConsumptionCategory == m_eSelConsumptionCategory)	&&
		(m_iCurPage == m_iSelPage))
	{
		_setItemButtonChecked(m_iSelIndex);
		return;
	}

	// ������ �������� ���� �������� ���� ��� ���� üũ ���¸� �����Ѵ�
	_setItemButtonChecked(ALL_BUTTON);
}

void CTRGuildWorkshop_ManagementDlg::_setButtonChecked(CGUIControlID ctrlID, const std::string& name, bool b)
{
	CGUIControl* pCtrl = ctrlID.findControl();
	if (nullptr == pCtrl)
	{
		return;
	}

	CGUIButton* pButton = static_cast<CGUIButton*>(pCtrl->findControl(name));
	if (pButton)
	{
		pButton->setChecked(b);
	}
}

void CTRGuildWorkshop_ManagementDlg::_setItemButtonChecked(int index)
{
	// ��ư �ε���(0 ~ 7) + ALL_BUTTON(8; ��ü ��ư �ʱ�ȭ)
	if (m_vecListPiece.empty() || (0 > index || ALL_BUTTON < index))
	{
		return;
	}

	for (size_t i = 0; i < m_vecListPiece.size(); ++i)
	{
		CGUIControl* pListPiece = m_vecListPiece[i].findControl();
		if (pListPiece && pListPiece->isVisible())
		{
			if (ALL_BUTTON != index && index == i)
			{
				_setButtonChecked(m_vecListPiece[i], format("GoodsItem%d", i + 1), true);
			}
			else
			{
				_setButtonChecked(m_vecListPiece[i], format("GoodsItem%d", i + 1), false);
			}
		}
	}
}

void CTRGuildWorkshop_ManagementDlg::_setStaticText(CGUIControlID ctrlID, const std::string& name, const std::string& message)
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

void CTRGuildWorkshop_ManagementDlg::_setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string& name)
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

void CTRGuildWorkshop_ManagementDlg::_checkForProductionRegistItem(int needPoint)
{
	__int64 curPoint = (eRewardCondition_GUILD_POINT == m_tCurItem.iRegisterPointKind) ? m_iGuildPoint : m_iGuildManagerTR;

	CGUIControl* pProductionDlg = m_productionDlgID.findControl();
	if (pProductionDlg)
	{
		CGUIButton* pButton = static_cast<CGUIButton*>(pProductionDlg->findControl("productionBtn"));
		if (pButton)
		{
			if (curPoint >= static_cast<__int64>(needPoint))
			{
				pButton->setVisible(true);
			}
			else
			{
				pButton->setVisible(false);
			}
		}
	}
}

int CTRGuildWorkshop_ManagementDlg::_findStandByItemList(int itemIndex)
{
	auto& iter_find = m_mapStandByItemList.find(itemIndex);
	if (m_mapStandByItemList.end() == iter_find)
	{
		return -1;
	}

	return iter_find->second;
}

int CTRGuildWorkshop_ManagementDlg::_findPlantItemList(int itemIndex)
{
	auto& iter_find = m_mapPlantItemList.find(itemIndex);
	if (m_mapPlantItemList.end() == iter_find)
	{
		return -1;
	}

	return iter_find->second;
}