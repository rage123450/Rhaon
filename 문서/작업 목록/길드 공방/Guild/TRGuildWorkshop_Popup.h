/* ---------------------------------------------------------------
 *
 * Copyright 2019 by Rhaon Ent.
 *
 * TRGuildWorkshop_Popup.h
 *
 * 2019. 12. Han Younho
 *
 * ---------------------------------------------------------------
 */

#pragma once

#include "gameui/TRUserInterface.h"

class CTRWorkshopController;

////////////////////////////////////////////////////////////////////////////////////
// ��� ���� �˾� ���̾�α�
class CTRGuildWorkshop_Popup : public CTRCommandTarget
{
public:
	CTRGuildWorkshop_Popup();
	virtual ~CTRGuildWorkshop_Popup();

public:
	bool isVisible() const;

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

public:
	void showDialog();
	void closeDialog();

public:
	void onRecvCurrentGuildPoint(__int64 iGuildPt);	// ��� ����Ʈ ��û ����
	void onRecvCurrentMyGuildPoint(int iMyGuildPt);	// ���� ��� ����Ʈ ��û ����

public:	// ��� � TR ��û ����
	void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR);
	void onRecvGuildPlantGetGuildManagerTRFailed(eGuildPlantFailReason iFailedReason);

public:	// ��� � TR ���� ����
	void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR);
	void onRecvGuildPlantInvestGuildManagerTRFailed(eGuildPlantFailReason iFailedReason);

public:	// ��� � TR â�� Ȯ�� ����
	void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue);
	void onRecvGuildPlantGetStorageExtendFailed(eGuildPlantFailReason iFailedReason);

public:	// ������ ������ ���� ��� ����
	void onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR);
	void onRecvGuildPlantRegisterItemFailed(eGuildPlantFailReason iFailedReason);

public:	// ��� � TR ������ ����Ʈ ��û ����
	void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList);
	void onRecvGuildPlantGetInvestorManagerTRFailed(eGuildPlantFailReason iFailedReason);

public:	// ��� ��ȭ ���� ����Ʈ ��û ����
	void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList);
	void onRecvGuildPlantGetExpenseListFailed(eGuildPlantFailReason iFailedReason);

public:	// ������ ���� ���� ������ ��û ����
	void onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind);
	void onRecvGuildPlantGetMakeProgressItemFailed(eGuildPlantFailReason iFailedReason);

public:	// ������ ���� ��� ������ ��û ����
	void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant);
	void onRecvGuildPlantGetMakeStandByItemFailed(eGuildPlantFailReason iFailedReason);

public:	// ������ ������ ����Ʈ ��û ����
	void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList);
	void onRecvGuildPlantGetPlantItemListFailed(eGuildPlantFailReason iFailedReason);

public:	// ������ ���۱⿩ ������ ���� ����
	void onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum);
	void onRecvGuildPlantChangeMyConstributionPointItemFailed(eGuildPlantFailReason iFailedReason);

public:	// ������ ���� ���� ���� ����Ʈ ��û ����
	void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList);
	void onRecvGuildPlantGetGivePossibleUserListFailed(eGuildPlantFailReason iFailedReason);

public:	// ������ ������ ���� ��û ����
	void onRecvGuildPlantGiveGiftOK(int iItemIndexNum);
	void onRecvGuildPlantGiveGiftFailed(eGuildPlantFailReason iFailedReason);

public:	// ������ ������ �⿩�� ���� ����Ʈ ��û ����
	void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList);
	void onRecvGuildPlantGetItemContributeRankLIstFailed(eGuildPlantFailReason iFailedReason);

public:	// ������ ������ ���� ��û ����
	void onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount);
	void onRecvGuildPlantBuyItemFailed(eGuildPlantFailReason iFailedReason);

private:
	void _showErrorMessage(eGuildPlantFailReason iFailedReason);

private:
	CTRWorkshopController*	m_pController;

	CGUIControlID	m_dlgID;	// ���� ���̾�α�

	bool	m_bIsPermission;	// ���� ���� ���� ���� (���� ������ �̻� ���� ����)
};