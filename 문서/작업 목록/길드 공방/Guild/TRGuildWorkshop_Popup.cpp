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
			// ���� ������ �̻� ���� ������ �� �� ����
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

	// ���� ������ �̻� ���� ���� ���� ���� ȹ��
	if (eGuildMemberGrade_SUBMASTER == myGuildUserInfo.m_eGrade || eGuildMemberGrade_MASTER == myGuildUserInfo.m_eGrade)
	{
		m_bIsPermission = true;
	}

	// CTRGuildWorkshop_ManagementDlg���� ���� ��� ���� ��, �Ǹ� ���� ���� �����ϰ�
	// ������ ����Ʈ�� ����� �ϱ� ������, �̸� �� �� ��û�ؼ� �����س��� ���� ��û �Լ�
	CNetClientManager::getInstance().requestGetGuildPlantSellItemList();		// ���۰��� ������ ����Ʈ ��û
	CNetClientManager::getInstance().requestGetGuildPlantMakeStandbyItemList();	// ���۴�� ������ ����Ʈ ��û

	// GuildPoint Dialog�� �� ��ҵ��� �ʱ�ȭ �ϱ� ���� ��û��
	int iGuildNum = CNetClientManager::getInstance().getMyGuildNum();
	CNetClientManager::getInstance().requestGuild_getGuildPoint(iGuildNum);				// ��� ����Ʈ ��û
	CNetClientManager::getInstance().requestGuild_getGuildContributionPoint(iGuildNum);	// ���� ��� ����Ʈ ��û
	CNetClientManager::getInstance().requestGetGuildPlantManagerTR(iGuildNum);			// ��� � TR ��û
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
	case eGuildPlantFailReason_UNKNOWN:	// �� �� ���� ����
		errmsg = _STR(HS_ERR_UNKNOWN);
		break;

	case eGuildPlantFailReason_NOT_PERMISSION:	// ���� ����
		errmsg = _STR(FAILED_GUILD_INVALID_PERMISSION);
		break;

	case eGuildPlantFailReason_OVER_MANAGERTR:	// �Ϸ� ���ڱݾ� �ʰ�
		errmsg = _STR(GUILD_PLANT_FAILED_INVEST_AMOUNT_EXCEEDED);
		break;

	case eGuildPlantFailReason_OVER_INVEST_COUNT:	// �Ϸ� ����Ƚ�� �ʰ�
		errmsg = _STR(GUILD_PLANT_FAILED_OVER_INVEST_COUNT);
		break;

	case eGuildPlantFailReason_NOT_ENOUGH_TR:	// TR ���� �ݾ� ����
		errmsg = _STR(FAILED_CREATE_FAMILY_NOT_ENOUGH_MONEY);
		break;

	case eGuildPlantFailReason_NOT_ENOUGH_GUILDPOINT:	// �������Ʈ �����ݾ� ����
		errmsg = _STR(FAILED_GUILDSKILL_CHECK_AVAILABILITY_TYPE_GUILD_POINT_SHORTAGE);
		break;

	case eGuildPlantFailReason_NOT_ENOUGH_MANAGETR:	// ��� � TR �����ݾ� ����
		errmsg = _STR(GUILD_PLANT_FAILED_NOT_ENOUGH_GUILD_MANAGE_TR);
		break;

	case eGuildPlantFailReason_NOT_ITEMINDEX:	// �߸��� ������ �ε��� ��ȣ
		errmsg = _STR(INVALID_ITEM);
		break;

	case eGuildPlantFailReason_ALREADY_MAKE_ITEMINDEX:	// �̹� �������� ������ �ε��� ��ȣ
		errmsg = _STR(GUILD_PLANT_FAILED_ALEADY_MAKE_ITEMINDEX);
		break;

	case eGuildPlantFailReason_NOT_MAKE_ITEMINDEX:	// ���� �������� �ε��� ��ȣ�� �ƴ�
		errmsg = _STR(GUILD_PLANT_FAILED_NOT_MAKE_ITEMINDEX);
		break;

	case eGuildPlantFailReason_ALREADY_FINISH:	// �̹� ������ �Ϸ��
		errmsg = _STR(GUILD_PLANT_FAILED_ALREADY_FINISH_ITEMINDEX);
		break;

	case eGuildPlantFailReason_ALREADY_CONTRIBUTION_ITEMINDEX:	// �̹� ���ۿ� �⿩��
		errmsg = _STR(GUILD_PLANT_FAILED_ALREADY_CONTRIBUTION_ITEMINDEX);
		break;

	case eGuildPlantFailReason_ALREADY_BUY_ITEM:	// �̹� ������ ������
		errmsg = _STR(ITEM_BUY_NO_ITEM);
		break;

	case eGuildPlantFailReason_FINISH_SELL_ITEM:	// �ǸŰ� ����Ǿ���
		errmsg = _STR(FAILED_SOLDOUT_ITEM);
		break;

	case eGuildPlantFailReason_NOT_GIVE_ITEM:	// ������ ���޿� ����
		errmsg = _STR(FAILED_GIVEITEM_FAILED);
		break;

	case eGuildPlantFailReason_OVER_GIFT_COUNT:	// �������� �ο��� �ʰ�
		errmsg = _STR(GUILD_PLANT_FAILED_GUILD_PLANT_OVER_GIFT_COUNT);
		break;

	case eGuildPlantFailReason_NOT_GUILD_NUM:	// �߸��� ��� ��ȣ
		errmsg = _STR(MSG_INVALID_GUILD_NUMBER);
		break;

	case eGuildPlantFailReason_NOT_ENOUGH_MYGUILDPOINT:	// ���� ��� ����Ʈ ����
		errmsg = format(_STR(DICEBOARD_HUMONG_RESET_NEED_ITEM), _STR(MONEY_MY_GUILD_POINT));
		break;
	}

	CTRShortTimeMessage::getInstance().showMessage(errmsg);
}