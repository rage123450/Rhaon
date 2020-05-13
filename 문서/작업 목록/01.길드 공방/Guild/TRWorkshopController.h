#pragma once

class CTRWorkshopBase;
class CTRGuildPlanInfoLoader;

class CTRWorkshopController
{
public:
	enum EWorkshop
	{
		NONE,
		CLOSE,		// ����
		MANAGEMENT,	// ���� ����
		PRODUCTION,	// ���� ���� ��Ȳ
		LIST,		// ���� ����Ʈ
		ETC,		// ��Ȯ��
		END
	};

private:
	CTRWorkshopBase*		m_arrBase[EWorkshop::END] = { nullptr, };
	CTRGuildPlanInfoLoader*	m_pLoader = nullptr;

	std::string	m_arrControlName[EWorkshop::END];

public:
	CTRWorkshopController();
	virtual ~CTRWorkshopController();

public:
	void onRecvCurrentGuildPoint(__int64 iGuildPt);													// ��� ����Ʈ ��û ����
	void onRecvCurrentMyGuildPoint(int iMyGuildPt);													// ���� ��� ����Ʈ ��û ����
	void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR);								// ��� � TR ��û ����
	void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR);							// ��� � TR ���� ����
	void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue);	// ��� � TR â�� Ȯ�� ���� ��û ����
	void onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR);									// ������ ������ ���� ��� ����
	void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList);		// ��� � TR ������ ����Ʈ ��û ����
	void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList);	// ��� ��ȭ ���� ����Ʈ ��û ����
	void onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind);	// ������ ���� ���� ������ ��û ����
	void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant);	// ������ ���� ��� ������ ��û ����
	void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList);	// ������ ������ ����Ʈ ��û ����
	void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList);				// ������ ���� ���� ���� ����Ʈ ��û ����
	void onRecvGuildPlantGiveGiftOK(int iItemIndexNum);												// ������ ������ ���� ��û ����
	void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList);		// ������ ������ �⿩�� ���� ����Ʈ ��û ����
	void onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum);						// ������ ���� �⿩ ������ ���� ����
	void onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount);						// ������ ������ ���� ��û ����

public:
	std::tuple<EWorkshop, int> Init(std::string _strControlName);

public:
	void showDialog(int _nIndex);
	void closeDialog();
};