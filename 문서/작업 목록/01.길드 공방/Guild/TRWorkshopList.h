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

public:	// ������ ������ ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList)override;

	// ������ ������ ���Ÿ� ��û ����
	void onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount);

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

