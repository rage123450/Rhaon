#pragma once
#include "TRWorkshopBase.h"

class CTRGuildPlanInfoLoader;

class CTRWorkshopProduction :
	public CTRWorkshopBase
{
private:
	shared_ptr<class CTRGuildWorkshop_ProductionDlg> m_pDlg = nullptr;

public:
	CTRWorkshopProduction();
	virtual ~CTRWorkshopProduction();

public:
	virtual void showDialog();
	virtual void closeDialog();

public:	
	// ������ ���� ��� ������ ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant)override;
	
	// ������ ���� ���� ���� ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList)override;

	// ������ ������ �⿩�� ���� ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList)override;

	// ������ ���� ���� ������ ���� ��û ����
	virtual void onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind)override;

	// ������ ���� �⿩ ������ ���� ����
	virtual void onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum)override;

	// ������ ������ ���� ��û ����
	virtual void onRecvGuildPlantGiveGiftOK(int iItemIndexNum)override;

	// ========================================================================================================================================================

	// ��� � TR ��û ����
	virtual void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR) override;

	// ��� � TR ���ڿ� ����
	virtual void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR) override;

	// ��� � TR â�� Ȯ�� ������ ��û ����
	virtual void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue) override;

	// ��� � TR ������ ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList) override;

	// ��� ��ȭ ���� ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList) override;

public:
	void LoadGuideList(CTRGuildPlanInfoLoader* pLoader);
};

