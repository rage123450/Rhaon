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
	// 길드공방 제작 대기 아이템 리스트 요청 관련
	virtual void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant)override;
	
	// 아이템 지급 가능 길드원 리스트 요청 관련
	virtual void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList)override;

	// 길드공방 아이템 기여도 순위 리스트 요청 관련
	virtual void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList)override;

	// 길드공방 제작 진행 아이템 정보 요청 관련
	virtual void onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind)override;

	// 길드공방 제작 기여 아이템 변경 관련
	virtual void onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum)override;

	// 길드공방 아이템 지급 요청 성공
	virtual void onRecvGuildPlantGiveGiftOK(int iItemIndexNum)override;

	// ========================================================================================================================================================

	// 길드 운영 TR 요청 성공
	virtual void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR) override;

	// 길드 운영 TR 투자에 성공
	virtual void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR) override;

	// 길드 운영 TR 창고 확장 정보를 요청 성공
	virtual void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue) override;

	// 길드 운영 TR 투자자 리스트 요청 성공
	virtual void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList) override;

	// 길드 재화 지출 리스트 요청 성공
	virtual void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList) override;

public:
	void LoadGuideList(CTRGuildPlanInfoLoader* pLoader);
};

