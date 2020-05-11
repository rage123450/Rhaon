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
// 길드 공방 팝업 다이얼로그
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
	void onRecvCurrentGuildPoint(__int64 iGuildPt);	// 길드 포인트 요청 성공
	void onRecvCurrentMyGuildPoint(int iMyGuildPt);	// 마이 길드 포인트 요청 성공

public:	// 길드 운영 TR 요청 관련
	void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR);
	void onRecvGuildPlantGetGuildManagerTRFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드 운영 TR 투자 관련
	void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR);
	void onRecvGuildPlantInvestGuildManagerTRFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드 운영 TR 창고 확장 관련
	void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue);
	void onRecvGuildPlantGetStorageExtendFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드공방 아이템 제작 등록 관련
	void onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR);
	void onRecvGuildPlantRegisterItemFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드 운영 TR 투자자 리스트 요청 관련
	void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList);
	void onRecvGuildPlantGetInvestorManagerTRFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드 재화 지출 리스트 요청 관련
	void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList);
	void onRecvGuildPlantGetExpenseListFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드공방 제작 진행 아이템 요청 관련
	void onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind);
	void onRecvGuildPlantGetMakeProgressItemFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드공방 제작 대기 아이템 요청 관련
	void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant);
	void onRecvGuildPlantGetMakeStandByItemFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드공방 아이템 리스트 요청 관련
	void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList);
	void onRecvGuildPlantGetPlantItemListFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드공방 제작기여 아이템 변경 관련
	void onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum);
	void onRecvGuildPlantChangeMyConstributionPointItemFailed(eGuildPlantFailReason iFailedReason);

public:	// 아이템 지급 가능 길드원 리스트 요청 관련
	void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList);
	void onRecvGuildPlantGetGivePossibleUserListFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드공방 아이템 지급 요청 관련
	void onRecvGuildPlantGiveGiftOK(int iItemIndexNum);
	void onRecvGuildPlantGiveGiftFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드공방 아이템 기여도 순위 리스트 요청 관련
	void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList);
	void onRecvGuildPlantGetItemContributeRankLIstFailed(eGuildPlantFailReason iFailedReason);

public:	// 길드공방 아이템 구매 요청 관련
	void onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount);
	void onRecvGuildPlantBuyItemFailed(eGuildPlantFailReason iFailedReason);

private:
	void _showErrorMessage(eGuildPlantFailReason iFailedReason);

private:
	CTRWorkshopController*	m_pController;

	CGUIControlID	m_dlgID;	// 메인 다이얼로그

	bool	m_bIsPermission;	// 공방 관리 권한 여부 (서브 마스터 이상만 열람 가능)
};