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

		// 아이템 분류를 선택했을 때, 소비 재화 분류를 길드 포인트를 선택한 상태를 기본으로 한다
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

		// -1을 하는 이유는 버튼 이름 뒤의 번호가 1부터 시작하기 때문
		int index = atoi(name.substr(9).c_str()) - 1;
		if (0 > index || 8 <= index)
		{
			return true;
		}

		// 이전과 같은 버튼을 클릭한 경우 무시
		if ((m_eCurItemCategory == m_eSelItemCategory)					&&
			(m_eCurConsumptionCategory == m_eSelConsumptionCategory)	&&
			(m_iCurPage == m_iSelPage)									&&
			(index == m_iSelIndex))
		{
			return true;
		}

		// 선택한 아이템(+버튼) 세팅
		_setItem(index + ((m_iCurPage - 1) * 8));
		_setItemButtonChecked(index);

		m_eSelItemCategory = m_eCurItemCategory;
		m_eSelConsumptionCategory = m_eCurConsumptionCategory;

		m_iSelPage = m_iCurPage;
		m_iSelIndex = index;

		// 선택된 아이템에 맞게 다이얼로그 갱신
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
			// 선택된 아이템이 없거나 잘못된 정보일 경우 무시
			if (false == isValidIndexItemNum(m_tCurItem.iIndex))
			{
				m_bClickWorkshopList = false;
				return true;
			}

			// 공방 등록 분류(마스터 선택 지급, 30일, 15일, 7일, 무제한) 선택 확인
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
			// 선택된 아이템이 없거나 잘못된 정보일 경우 무시
			if (false == isValidIndexItemNum(m_tCurItem.iIndex))
			{
				m_bClickWorkshopList = false;
				return true;
			}

			// 최대 판매 개수 확인
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
		// 제작 등록 버튼은 선택한 아이템의 판매 가격보다 보유한 재화가 많을 때만 활성화
		// 활성화가 되지 않으면 애초에 함수에 들어오지 않지만 혹시 몰라 예외처리
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
		// 이 버튼이 눌렸다는 것은 드롭 박스를 열었다는 뜻
		// 이 상태에서 드롭 박스 버튼 이벤트가 위(onButtonClick 함수)에서 발생하면 정보가 갱신되었을 수도 있음
		// 실시간 정보 갱신을 위한 bool 변수 활용
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

	// 일단 첫 화면은 소비품, 길드 포인트 첫 페이지로 초기화
	_setButtonChecked(m_dlgID, "SuppliesBtn", true);
	_setButtonChecked(m_subDlgID, "GuildPointBtn", true);

	_setItemListByCategory(m_eCurConsumptionCategory);

	// 아이템 버튼은 선택하지 않은 상태로 초기화
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

	// 소모한 포인트 갱신 요청
	if (eRewardCondition_GUILD_POINT == m_tCurItem.iRegisterPointKind)
	{
		CNetClientManager::getInstance().requestGuild_getGuildPoint(iGuildNum);
	}
	else if (eRewardCondition_GUILD_MANAGER_TR == m_tCurItem.iRegisterPointKind)
	{
		CNetClientManager::getInstance().requestGetGuildPlantManagerTR(iGuildNum);
	}

	// 아이템 제작 등록에 성공하면, 등록된 아이템을 컨테이너에서 지워준다
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

		// 길드공방에 등록된 아이템이면 생략
		if (-1 != _findPlantItemList(itemInfo.iIndex))
		{
			continue;
		}

		// 제작 대기중인 아이템이라면 생략 (제작중인 아이템 포함)
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
		// 드롭 리스트 초기화
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

		// 현재 선택된 소비 재화 버튼에 따라 재화 표기 초기화
		if (eRewardCondition_GUILD_POINT == m_eCurConsumptionCategory)
		{
			_setStaticText(m_productionDlgID, "GuildPoint", format("%d %s", 0, _STR(MONEY_GP)));
		}
		else if (eRewardCondition_GUILD_MANAGER_TR == m_eCurConsumptionCategory)
		{
			_setStaticText(m_productionDlgID, "GuildPoint", format("%d %s", 0, _STR(MONEY_TR)));
		}

		// 제작등록 버튼 숨기기
		CGUIButton* pButton = static_cast<CGUIButton*>(pCtrl->findControl("productionBtn"));
		if (pButton)
		{
			pButton->setVisible(false);
		}
	}

	// 선택 아이템 다이얼로그 초기화
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

	// 이전에 갖고 있던 아이템 정보 삭제 및 초기화
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

	// TRGuildWorkshop_PopupDlg를 열 때 요청하여 한 번 초기화하지만
	// TRGuildWorkshop_ManagementDlg를 열기 전에 포인트 변동이 있을 수 있으므로 한 번 더 요청해서 갱신
	int iGuildNum = CNetClientManager::getInstance().getMyGuildNum();
	CNetClientManager::getInstance().requestGuild_getGuildPoint(iGuildNum);				// 길드 포인트 요청
	CNetClientManager::getInstance().requestGuild_getGuildContributionPoint(iGuildNum);	// 마이 길드 포인트 요청
	CNetClientManager::getInstance().requestGetGuildPlantManagerTR(iGuildNum);			// 길드 운영 TR 요청
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

			// 버튼 각각이 하나의 다이얼로그이므로 전부 이름이 같다. 그래서 순번을 뒤에 붙여준다
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

		// 드롭 박스를 여는 버튼을 따로 이벤트 등록. 이름이 없기 때문에 임의로 지어준다
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

	// 제작 등록 버튼은 일단 비활성화 (아이템 미선택을 가정)
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

		// 아이템 개수에 맞게, 펼쳐졌을 때의 드롭 리스트 높이 조절
		// +1의 이유는 EditControl 부분까지 포함하기 위해
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

		// 아이템 개수에 맞게, 펼쳐졌을 때의 드롭 리스트 높이 조절
		// +1의 이유는 EditControl 부분까지 포함하기 위해
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

 		// 공방 아이템 인덱스와 공방 등록 분류를 통해 제작에 필요한 포인트를 저장한 구조체를 받아온다
		int needPoint = _getRegisterNeedPoint();

		// 소비 재화 분류에 따라 텍스트 설정
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

		// 재화 검사 후, 제작이 가능할 경우(보유 포인트가 등록 포인트보다 많거나 같은 경우) 버튼이 보이게 한다
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
		// 한 화면에 여덞 개의 아이템이 들어가므로 페이지 수를 세기 위해 나눈다
		// 이 정보가 0이라는 뜻은 아이템 개수가 8개 미만이라는 뜻 (1page만 존재)
		if (m_mapItemList[eItemCategory][eConsumptionCategory].size() / 8)
		{
			// 한 페이지 이상 존재하는데 나머지가 0이라는 것은 아이템이 8의 배수(1page 단위)만큼 존재한다는 것
			if (0 == m_mapItemList[eItemCategory][eConsumptionCategory].size() % 8)
			{
				maxPage = m_mapItemList[eItemCategory][eConsumptionCategory].size() / 8;
			}
			// 그렇지 않다면 나눈 페이지를 넘어간다
			// 예로, 몫이 1(page == 아이템 8개 이상)인 상황에서 나머지가 나왔을 경우에는 아이템이 (8, 16]개라는 뜻
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
		// 현재 페이지에 아이템이 없는 경우, 아이템 버튼 전부 비활성화
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

	// i는 아이템 버튼 리스트 인덱스(0 ~ m_vecListPiece.size())
	// index는 아이템 컨테이너의 인덱스(0 ~ m_mapItemList[m_eCurItemCategory][m_eCurConsumptionCategory].size())
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

	// 현재 페이지 내의 아이템 버튼 정보가 없는 것이 있을 경우, 그 아이템 버튼들을 비활성화
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

	// 선택한 아이템이 존재하는 페이지인지 확인하고, 맞는 경우 선택한 아이템을 체크 상태로 만든다
	if ((m_eCurItemCategory == m_eSelItemCategory)					&&
		(m_eCurConsumptionCategory == m_eSelConsumptionCategory)	&&
		(m_iCurPage == m_iSelPage))
	{
		_setItemButtonChecked(m_iSelIndex);
		return;
	}

	// 선택한 아이템이 현재 페이지에 없을 경우 전부 체크 상태를 해제한다
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
	// 버튼 인덱스(0 ~ 7) + ALL_BUTTON(8; 전체 버튼 초기화)
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