#pragma once

struct GuildPlantItemInfo
{
	int iIndex;				// ��������� �ε��� ��ȣ
	int iCategory;			// ������� ī�װ�(1: �Ҹ�ǰ, 2: ���, 3: �����(�ַ̼��� ��))
	int iRegisterPointKind;	// eRewardCondition(900: �������Ʈ, 901: ���TR)
	int iOrder;				// ���ļ���
	int iItemNum;			// ������ ��ȣ(UniqueNum)
	int iDurationDay;		// ���� �Ⱓ
	int iSellPointKind;		// �Ǹ�����Ʈ Ÿ��(200: TR, 1000: ���� �������Ʈ)
	int iSellPointValue;	// �Ǹź��

	GuildPlantItemInfo()
		: iIndex(0), iCategory(0), iRegisterPointKind(0), iOrder(0), iItemNum(0), iDurationDay(0)
		, iSellPointKind(0), iSellPointValue(0) {}

	void clear()
	{
		iIndex = 0;
		iCategory = 0;
		iRegisterPointKind = 0;
		iOrder = 0;
		iItemNum = 0;
		iDurationDay = 0;
		iSellPointKind = 0;
		iSellPointValue = 0;
	}
};

struct GuildPlantGuideInfo
{
	std::string	title;
	std::string	body;

	int	iIndex;
	int	iSubIndex;

	GuildPlantGuideInfo()
		: iIndex(0), iSubIndex(0) {}

	void clear()
	{
		title.clear();
		body.clear();

		iIndex = 0;
		iSubIndex = 0;
	}
};

struct stGuildPlantNeedPointInfo
{
	int iIndex;				// ��������� �ε��� ��ȣ
	int iDistributeKind;	// -1 : ������ ���� / 7, 15, 30 : ���� ��� ��¥
	int iLimitBuyCount;		// ���� ���� ���� / -1 : ������
	int iRegisterTR;		// ��� ��� : ��� �TR
	int iRegisterGP;		// ��� ��� : ��� ����Ʈ

	stGuildPlantNeedPointInfo()
		: iIndex(0), iDistributeKind(0), iLimitBuyCount(0), iRegisterTR(0), iRegisterGP(0) {}

	void clear()
	{
		iIndex = 0;
		iDistributeKind = 0;
		iLimitBuyCount = 0;
		iRegisterTR = 0;
		iRegisterGP = 0;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////

class CTRWorkshopBase
{
public:
	CTRWorkshopBase() = default;
	virtual ~CTRWorkshopBase() = default;

public:
	virtual void onRecvCurrentGuildPoint(__int64 iGuildPt) {}													// ��� ����Ʈ ��û ����
	virtual void onRecvCurrentMyGuildPoint(int iMyGuildPt) {}													// ���� ��� ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR) {}									// ��� � TR ��û ����
	virtual void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR) {}								// ��� � TR ���� ����
	virtual void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue) {}	// ��� � TR â�� Ȯ�� ���� ��û ����
	virtual void onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR) {}									// ������ ������ ���� ��� ����
	virtual void onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind) {}	// ������ ���� ���� ������ ���� ��û ����
	virtual void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant) {}		// ������ ���� ��� ������ ����Ʈ ��û ����
	virtual void onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum) {}							// ������ ���� �⿩ ������ ���� ����
	virtual void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList) {}		// ��� � TR ������ ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList) {}	// ��� ��ȭ ���� ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList) {}		// ������ ������ �⿩�� ���� ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList) {}				// ������ ���� ���� ���� ����Ʈ ��û ����
	virtual void onRecvGuildPlantGiveGiftOK(int iItemIndexNum) {}												// ������ ������ ���� ��û ����
	virtual void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList) {}	// ������ ������ ����Ʈ ��û ����
	virtual void onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount) {}						// ������ ������ ���� ��û ����

public:
	virtual void showDialog() {}
	virtual void closeDialog() {}
};

////////////////////////////////////////////////////////////////////////////////////////////////

class CTRGuildPlanInfoLoader
{
public:
	typedef std::map<int, GuildPlantItemInfo*>						MAP_ITEMLIST;
	typedef std::map<int, std::vector<stGuildPlantNeedPointInfo*>>	MAP_NEEDPOINTLIST;
	typedef std::map<std::pair<int, int>, GuildPlantGuideInfo*>		MAP_GUIDELIST;

public:
	CTRGuildPlanInfoLoader();
	~CTRGuildPlanInfoLoader();

public:
	inline MAP_ITEMLIST& getPlantItemList()
	{
		return m_mapGuildPlantItemList;
	}
	
	inline MAP_NEEDPOINTLIST& getPlantNeedPointList()
	{
		return m_mapGuildPlantNeedPoint;
	}

	inline MAP_GUIDELIST& getPlantGuideList()
	{
		return m_mapGuildPlantGuideList;
	}

public:
	void Init();

public:
	bool loadGuildPlantItemInfo(const std::string& strFileName);
	bool loadGuildPlantNeedPointInfo(const std::string& strFileName);
	bool loadGuildPlantGuideInfo(const std::string& strFileName);

public:
	bool isValidIndexItemNum(int iIndexItemnum);

public:
	std::vector<int> getDistributeKind(int iIndex, int iRegisterPointKind);
	std::vector<int> getLimtBuyCount(int iIndex, int iDistributeKind, int iRegisterPointKind);
	int getNeedPoint(int iIndex, int iDistributeKind, int iLimitBuyCount, int iRegisterPointKind);

private:
	MAP_ITEMLIST		m_mapGuildPlantItemList;
	MAP_NEEDPOINTLIST	m_mapGuildPlantNeedPoint;
	MAP_GUIDELIST		m_mapGuildPlantGuideList;
};