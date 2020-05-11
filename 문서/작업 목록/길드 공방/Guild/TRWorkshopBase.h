#pragma once

struct GuildPlantItemInfo
{
	int iIndex;				// 공방아이템 인덱스 번호
	int iCategory;			// 공방관리 카테고리(1: 소모품, 2: 장비, 3: 스페셜(미솔로지 등))
	int iRegisterPointKind;	// eRewardCondition(900: 길드포인트, 901: 길드운영TR)
	int iOrder;				// 정렬순서
	int iItemNum;			// 아이템 번호(UniqueNum)
	int iDurationDay;		// 제작 기간
	int iSellPointKind;		// 판매포인트 타입(200: TR, 1000: 개인 길드포인트)
	int iSellPointValue;	// 판매비용

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
	int iIndex;				// 공방아이템 인덱스 번호
	int iDistributeKind;	// -1 : 마스터 선택 / 7, 15, 30 : 공방 등록 날짜
	int iLimitBuyCount;		// 구매 가능 갯수 / -1 : 무제한
	int iRegisterTR;		// 등록 비용 : 길드 운영TR
	int iRegisterGP;		// 등록 비용 : 길드 포인트

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
	virtual void onRecvCurrentGuildPoint(__int64 iGuildPt) {}													// 길드 포인트 요청 성공
	virtual void onRecvCurrentMyGuildPoint(int iMyGuildPt) {}													// 마이 길드 포인트 요청 성공
	virtual void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR) {}									// 길드 운영 TR 요청 성공
	virtual void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR) {}								// 길드 운영 TR 투자 성공
	virtual void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue) {}	// 길드 운영 TR 창고 확장 정보 요청 성공
	virtual void onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR) {}									// 길드공방 아이템 제작 등록 성공
	virtual void onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind) {}	// 길드공방 제작 진행 아이템 정보 요청 성공
	virtual void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant) {}		// 길드공방 제작 대기 아이템 리스트 요청 성공
	virtual void onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum) {}							// 길드공방 제작 기여 아이템 변경 성공
	virtual void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList) {}		// 길드 운영 TR 투자자 리스트 요청 성공
	virtual void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList) {}	// 길드 재화 지출 리스트 요청 성공
	virtual void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList) {}		// 길드공방 아이템 기여도 순위 리스트 요청 성공
	virtual void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList) {}				// 아이템 지급 가능 길드원 리스트 요청 성공
	virtual void onRecvGuildPlantGiveGiftOK(int iItemIndexNum) {}												// 길드공방 아이템 지급 요청 성공
	virtual void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList) {}	// 길드공방 아이템 리스트 요청 성공
	virtual void onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount) {}						// 길드공방 아이템 구매 요청 성공

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