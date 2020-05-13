/* ---------------------------------------------------------------
 *
 * Copyright 2019 by Rhaon Ent.
 *
 * TRGuildWorkshop_Popup.cpp
 *
 * 2019. 12. Han Younho
 *
 * ---------------------------------------------------------------
 */

#include "stdafx.h"
#include "TRGuildWorkshop_Popup.h"

#include "language/LanguageHeader.h"

#include "gameui/TRShortTimeMessage.h"

#include "NetClientManager.h"
#include "TRWorkshopController.h"

CTRGuildWorkshop_Popup::CTRGuildWorkshop_Popup()
	: m_pController(nullptr)
	, m_dlgID(CGUIControlID::INVALID_ID)
	, m_bIsPermission(false)
{
	
}

CTRGuildWorkshop_Popup::~CTRGuildWorkshop_Popup()
{
	SAFE_DELETE(m_pController);

	closeDialog();
}

bool CTRGuildWorkshop_Popup::isVisible() const
{
	CGUIControl* pDlg = m_dlgID.findControl();
	return pDlg ? pDlg->isVisible() : false;
}

bool CTRGuildWorkshop_Popup::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	if (false == isVisible())
	{
		return false;
	}

	CGUIControl* pCtrl = ctrlID.findControl();
	if (pCtrl)
	{
		auto& tuple = m_pController->Init(pCtrl->getName());

		switch (std::get<0>(tuple))
		{
		case CTRWorkshopController::EWorkshop::CLOSE:
			closeDialog();
			return true;

		case CTRWorkshopController::EWorkshop::ETC:
			return true;

		case CTRWorkshopController::EWorkshop::MANAGEMENT:
			// 서브 마스터 이상만 공방 관리를 열 수 있음
			if (m_bIsPermission)
			{
				m_pController->showDialog(std::get<1>(tuple));
			}
			else
			{
				CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_GUILD_INVALID_PERMISSION));
			}

			return true;

		default:
			m_pController->showDialog(std::get<1>(tuple));
			return true;
		}
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRGuildWorkshop_Popup::showDialog()
{
	closeDialog();

	std::string errmsg;

	CGUIDialog* pDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_Popup.gui", errmsg);
	if (nullptr == pDlg)
	{
		return;
	}

	m_dlgID = pDlg->getControlID();

	pDlg->centerPosition();
	pDlg->setModalDialog(true);
	pDlg->setDialogListener(getCommandTargetID());
	CGUIManager::getInstance().setFocus(m_dlgID);
	CTRUserInterface::getInstance().setGUIAnimatorPopupShow(pDlg, true);

	if (nullptr == m_pController)
	{
		m_pController = new CTRWorkshopController;
	}

	GuildUserInfo myGuildUserInfo = CNetClientManager::getInstance().getMyGuildUserInfo();

	// 서브 마스터 이상만 공방 관리 열람 권한 획득
	if (eGuildMemberGrade_SUBMASTER == myGuildUserInfo.m_eGrade || eGuildMemberGrade_MASTER == myGuildUserInfo.m_eGrade)
	{
		m_bIsPermission = true;
	}

	// CTRGuildWorkshop_ManagementDlg에서 제작 대기 중인 것, 판매 중인 것을 제외하고
	// 아이템 리스트를 띄워야 하기 때문에, 미리 한 번 요청해서 저장해놓기 위한 요청 함수
	CNetClientManager::getInstance().requestGetGuildPlantSellItemList();		// 제작공방 아이템 리스트 요청
	CNetClientManager::getInstance().requestGetGuildPlantMakeStandbyItemList();	// 제작대기 아이템 리스트 요청

	// GuildPoint Dialog의 각 요소들을 초기화 하기 위한 요청들
	int iGuildNum = CNetClientManager::getInstance().getMyGuildNum();
	CNetClientManager::getInstance().requestGuild_getGuildPoint(iGuildNum);				// 길드 포인트 요청
	CNetClientManager::getInstance().requestGuild_getGuildContributionPoint(iGuildNum);	// 마이 길드 포인트 요청
	CNetClientManager::getInstance().requestGetGuildPlantManagerTR(iGuildNum);			// 길드 운영 TR 요청
}

void CTRGuildWorkshop_Popup::closeDialog()
{
	m_bIsPermission = false;

	if (m_pController)
	{
		m_pController->closeDialog();
	}

	CGUIControl* pDlg = m_dlgID.findControl();
	if (pDlg)
	{
		CTRUserInterface::getInstance().setGUIAnimatorPopupHide(pDlg);
		m_dlgID = CGUIControlID::INVALID_ID;
	}
}

void CTRGuildWorkshop_Popup::onRecvCurrentGuildPoint(__int64 iGuildPt)
{
	if (m_pController)
	{
		m_pController->onRecvCurrentGuildPoint(iGuildPt);
	}
}

void CTRGuildWorkshop_Popup::onRecvCurrentMyGuildPoint(int iMyGuildPt)
{
	if (m_pController)
	{
		m_pController->onRecvCurrentMyGuildPoint(iMyGuildPt);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantGetGuildManagerTR(iGuildManagerTR);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetGuildManagerTRFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantInvestGuildManagerTR(iGuildManagerTR);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantInvestGuildManagerTRFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantGetStorageExtendOK(iExtendCount, iExtendValue, iUserInvestCount, iUserInvestValue);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetStorageExtendFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantRegisterItemOK(iGuildManagerTR);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantRegisterItemFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantGetInvestorManagerTRListOK(userList);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetInvestorManagerTRFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantGetExpenseListOK(pointType, iMonth, useList);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetExpenseListFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantGetMakeProgressItemOK(guildplantMakeInfo, iMyContributionPoint, distributeKind);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetMakeProgressItemFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantGetMakeStandByItemListOK(guildplant);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetMakeStandByItemFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantGetPlantItemListOK(useList);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetPlantItemListFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantChangeMyConstributionPointItemOK(iItemIndexNum);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantChangeMyConstributionPointItemFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantGetGivePossibleUserListOK(userList);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetGivePossibleUserListFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGiveGiftOK(int iItemIndexNum)
{

}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGiveGiftFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList)
{
	if (m_pController)
	{
		m_pController->onRecvGuildPlantGetItemContributeRankLIstOK(userList);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantGetItemContributeRankLIstFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount)
{
	if(m_pController)
	{
		m_pController->onRecvGuildPlantBuyItemOK(iSellNum, iItemNum, iBuyCount);
	}
}

void CTRGuildWorkshop_Popup::onRecvGuildPlantBuyItemFailed(eGuildPlantFailReason iFailedReason)
{
	_showErrorMessage(iFailedReason);
}

void CTRGuildWorkshop_Popup::_showErrorMessage(eGuildPlantFailReason iFailedReason)
{
	std::string errmsg;

	switch (iFailedReason)
	{
	case eGuildPlantFailReason_UNKNOWN:	// 알 수 없는 오류
		errmsg = _STR(HS_ERR_UNKNOWN);
		break;

	case eGuildPlantFailReason_NOT_PERMISSION:	// 권한 부족
		errmsg = _STR(FAILED_GUILD_INVALID_PERMISSION);
		break;

	case eGuildPlantFailReason_OVER_MANAGERTR:	// 하루 투자금액 초과
		errmsg = _STR(GUILD_PLANT_FAILED_INVEST_AMOUNT_EXCEEDED);
		break;

	case eGuildPlantFailReason_OVER_INVEST_COUNT:	// 하루 투자횟수 초과
		errmsg = _STR(GUILD_PLANT_FAILED_OVER_INVEST_COUNT);
		break;

	case eGuildPlantFailReason_NOT_ENOUGH_TR:	// TR 보유 금액 부족
		errmsg = _STR(FAILED_CREATE_FAMILY_NOT_ENOUGH_MONEY);
		break;

	case eGuildPlantFailReason_NOT_ENOUGH_GUILDPOINT:	// 길드포인트 보유금액 부족
		errmsg = _STR(FAILED_GUILDSKILL_CHECK_AVAILABILITY_TYPE_GUILD_POINT_SHORTAGE);
		break;

	case eGuildPlantFailReason_NOT_ENOUGH_MANAGETR:	// 길드 운영 TR 보유금액 부족
		errmsg = _STR(GUILD_PLANT_FAILED_NOT_ENOUGH_GUILD_MANAGE_TR);
		break;

	case eGuildPlantFailReason_NOT_ITEMINDEX:	// 잘못된 아이템 인덱스 번호
		errmsg = _STR(INVALID_ITEM);
		break;

	case eGuildPlantFailReason_ALREADY_MAKE_ITEMINDEX:	// 이미 제작중인 아이템 인덱스 번호
		errmsg = _STR(GUILD_PLANT_FAILED_ALEADY_MAKE_ITEMINDEX);
		break;

	case eGuildPlantFailReason_NOT_MAKE_ITEMINDEX:	// 제작 진행중인 인덱스 번호가 아님
		errmsg = _STR(GUILD_PLANT_FAILED_NOT_MAKE_ITEMINDEX);
		break;

	case eGuildPlantFailReason_ALREADY_FINISH:	// 이미 제작이 완료됨
		errmsg = _STR(GUILD_PLANT_FAILED_ALREADY_FINISH_ITEMINDEX);
		break;

	case eGuildPlantFailReason_ALREADY_CONTRIBUTION_ITEMINDEX:	// 이미 제작에 기여중
		errmsg = _STR(GUILD_PLANT_FAILED_ALREADY_CONTRIBUTION_ITEMINDEX);
		break;

	case eGuildPlantFailReason_ALREADY_BUY_ITEM:	// 이미 구매한 아이템
		errmsg = _STR(ITEM_BUY_NO_ITEM);
		break;

	case eGuildPlantFailReason_FINISH_SELL_ITEM:	// 판매가 종료되었다
		errmsg = _STR(FAILED_SOLDOUT_ITEM);
		break;

	case eGuildPlantFailReason_NOT_GIVE_ITEM:	// 아이템 지급에 실패
		errmsg = _STR(FAILED_GIVEITEM_FAILED);
		break;

	case eGuildPlantFailReason_OVER_GIFT_COUNT:	// 선물지급 인원수 초과
		errmsg = _STR(GUILD_PLANT_FAILED_GUILD_PLANT_OVER_GIFT_COUNT);
		break;

	case eGuildPlantFailReason_NOT_GUILD_NUM:	// 잘못된 길드 번호
		errmsg = _STR(MSG_INVALID_GUILD_NUMBER);
		break;

	case eGuildPlantFailReason_NOT_ENOUGH_MYGUILDPOINT:	// 마이 길드 포인트 부족
		errmsg = format(_STR(DICEBOARD_HUMONG_RESET_NEED_ITEM), _STR(MONEY_MY_GUILD_POINT));
		break;
	}

	CTRShortTimeMessage::getInstance().showMessage(errmsg);
}