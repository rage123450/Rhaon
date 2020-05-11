#pragma once
#include "TRWorkshopBase.h"
class CTRWorkshop_ListDlg;
class CTRWorkshopList :
	public CTRWorkshopBase
{
private:
	shared_ptr<CTRWorkshop_ListDlg> m_pDlg = nullptr;

public:
	CTRWorkshopList();
	virtual ~CTRWorkshopList();

public:
	virtual void showDialog();
	virtual void closeDialog();

public:	// 길드공방 아이템 리스트 요청 관련
	virtual void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList)override;

	// 길드공방 아이템 구매를 요청 성공
	void onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount);

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

