#pragma once

class CTRWorkshopBase;
class CTRGuildPlanInfoLoader;

class CTRWorkshopController
{
public:
	enum EWorkshop
	{
		NONE,
		CLOSE,		// 종료
		MANAGEMENT,	// 공방 관리
		PRODUCTION,	// 공방 제작 현황
		LIST,		// 공방 리스트
		ETC,		// 미확정
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
	void onRecvCurrentGuildPoint(__int64 iGuildPt);													// 길드 포인트 요청 성공
	void onRecvCurrentMyGuildPoint(int iMyGuildPt);													// 마이 길드 포인트 요청 성공
	void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR);								// 길드 운영 TR 요청 성공
	void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR);							// 길드 운영 TR 투자 성공
	void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue);	// 길드 운영 TR 창고 확장 정보 요청 성공
	void onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR);									// 길드공방 아이템 제작 등록 성공
	void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList);		// 길드 운영 TR 투자자 리스트 요청 성공
	void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList);	// 길드 재화 지출 리스트 요청 성공
	void onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind);	// 길드공방 제작 진행 아이템 요청 성공
	void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant);	// 길드공방 제작 대기 아이템 요청 성공
	void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList);	// 길드공방 아이템 리스트 요청 성공
	void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList);				// 아이템 지급 가능 길드원 리스트 요청 성공
	void onRecvGuildPlantGiveGiftOK(int iItemIndexNum);												// 길드공방 아이템 지급 요청 성공
	void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList);		// 길드공방 아이템 기여도 순위 리스트 요청 성공
	void onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum);						// 길드공방 제작 기여 아이템 변경 성공
	void onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount);						// 길드공방 아이템 구매 요청 성공

public:
	std::tuple<EWorkshop, int> Init(std::string _strControlName);

public:
	void showDialog(int _nIndex);
	void closeDialog();
};