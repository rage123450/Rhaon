/* ---------------------------------------------------------------
 *
 * Copyright 2019 by Rhaon Ent.
 *
 * TRGuildWorkshop_ManagementDlg.h
 *
 * 2019. 12. Han Younho
 *
 * ---------------------------------------------------------------
 */

#pragma once

#include "gameui/TRUserInterface.h"

#include "TRWorkshopBase.h"

////////////////////////////////////////////////////////////////////////////////////

class CTRGuildWorkshop_WarehouseDlg;
class CTRGuildWorkshop_ExpenseDlg;
class CTRGuildWorkshop_ProductionRegister;
class CTRGuildWorkshop_GuideDlg;

////////////////////////////////////////////////////////////////////////////////////
// 공방 관리 다이얼로그
class CTRGuildWorkshop_ManagementDlg : public CTRCommandTarget, public CGUIButtonEventNotify, public CTRWorkshopBase
{
public:
	typedef std::map<int, std::vector<GuildPlantItemInfo>>	MAP_ITEMLIST_BASE;
	typedef std::map<int, MAP_ITEMLIST_BASE>				MAP_ITEMLIST;
	typedef std::map<int, int>								MAP_ITEM;

public:
	// 길드 공방 아이템 카테고리
	enum eItemCategory
	{
		eItemCategory_None		= 0,	// None
		eItemCategory_Supplies	= 1,	// 소모품
		eItemCategory_Equipment	= 2,	// 장비 아이템
		eItemCategory_Special	= 3,	// 스페셜
		eItemCategory_End				// eItemCategory Count
	};

public:
	CTRGuildWorkshop_ManagementDlg();
	virtual ~CTRGuildWorkshop_ManagementDlg();

public:
	std::string getCurItemDistributeKindString();
	eGuildPlantDistributeKind getCurItemDistributeKindEnum();
	int getCurItemLimitBuyCount();

public:
	bool isVisible() const;

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;
	virtual void onButtonEventNotify(CGUIButton* pButton, GUI_MOUSE_EVENT event) override;

public:
	virtual void showDialog() override;
	virtual void closeDialog() override;

public:
	// 길드 포인트 요청 성공
	virtual void onRecvCurrentGuildPoint(__int64 iGuildPt) override;
	// 마이 길드 포인트 요청 성공
	virtual void onRecvCurrentMyGuildPoint(int iMyGuildPt) override;
	// 길드 운영 TR 요청 성공
	virtual void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR) override;
	// 길드 운영 TR 투자에 성공
	virtual void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR) override;
	// 길드 운영 TR 창고 확장 정보를 요청 성공
	virtual void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue) override;
	// 길드공방 아이템 제작 등록을 성공
	virtual void onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR) override;
	// 길드 운영 TR 투자자 리스트 요청 성공
	virtual void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList) override;
	// 길드 재화 지출 리스트 요청 성공
	virtual void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList) override;
	// 길드공방 아이템 지급 요청 성공
	virtual void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList) override;
	// 길드공방 제작대기 아이템 리스트 요청 성공
	virtual void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant) override;

public:
	void loadItemList(CTRGuildPlanInfoLoader* pLoader);
	void updateItemList();

public:
	void removeItem(int iItemCategory, int iConsumptionCategory, int iItemIndex);
	bool isValidIndexItemNum(int iIndexItemnum);

private:
	void _setItem(int index);

private:
	void _setSubDialog();
	void _setGuildPointDialog();
	void _setListDialog();
	void _setListPieceDialog();
	void _setItemDialog();
	void _setProductionDialog();

private:
	void _updateDistubeKindList(int iSelect = 0);				// 공방 등록 분류 드롭 리스트 갱신
	void _updateLimitBuyCountList(int iDistubeKind = 0);		// 구매 제한 개수 드롭 리스트 갱신
	void _updateCurrentItem();									// 현재 아이템에 따른 다이얼로그들 갱신
	int _getSelectDistributeKind();								// 드롭 리스트에서 현재 선택된 공방 등록 분류 반환
	int _getSelectLimitBuyCount();								// 드롭 리스트에서 현재 선택된 구매 제한 개수 반환
	int _getRegisterNeedPoint();								// 선택된 아이템에 맞는 등록 포인트 반환
	std::string _getDistributeKindString(int iDistributeKind);	// 원하는 공방 등록 분류 문자열 반환

private:
	void _setPage();																	// 페이지 번호 세팅 (단순히 번호 갱신하는 용도)
	void _setPage(eItemCategory eItemCategory, eRewardCondition eConsumptionCategory);	// 선택한 분류에 따른 페이지 정보 갱신

private:
	void _setItemListByCategory(eRewardCondition eConsumptionCategory);				// 소비 재화 분류에 따른 정보 갱신
	void _setItemListByCategory(eRewardCondition eConsumptionCategory, int page);	// + 페이지에 따른 정보 갱신

private:
	void _setButtonChecked(CGUIControlID ctrlID, const std::string& name, bool b);
	void _setItemButtonChecked(int index);
	void _setStaticText(CGUIControlID ctrlID, const std::string& name, const std::string& message);	// CGUIStaticText의 텍스트 변경
	void _setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string& name);		// parent의 name 컨트롤 위치에 child를 위치시킨다

private:
	void _checkForProductionRegistItem(int needPoint);	// 등록할 수 있는 아이템인지 포인트 비교 후 버튼 활성화

private:
	int _findStandByItemList(int itemIndex);	// 제작 대기 중인 아이템 찾기 (없으면 -1 반환)
	int _findPlantItemList(int itemIndex);		// 제작공방 등록 아이템 찾기 (없으면 -1 반환)

private:
	CGUIControlID	m_dlgID;			// 주 다이얼로그
	CGUIControlID	m_subDlgID;			// 서브 다이얼로그
	CGUIControlID	m_guildPointDlgID;	// 포인트 목록 다이얼로그
	CGUIControlID	m_listDlgID;		// 아이템 리스트 다이얼로그
	CGUIControlID	m_itemDlgID;		// 선택된 아이템 다이얼로그
	CGUIControlID	m_productionDlgID;	// 제작 관련 다이얼로그

	CTRGuildPlanInfoLoader*					m_pLoader;					// 길드공방 아이템 정보 로더 클래스
	CTRGuildWorkshop_WarehouseDlg*			m_pWarehouseDlg;			// 운영 TR 창고
	CTRGuildWorkshop_ExpenseDlg*			m_pExpenseDlg;				// 재화 지출 현황
	CTRGuildWorkshop_ProductionRegister*	m_pProductionRegisterDlg;	// 아이템 제작 등록
	CTRGuildWorkshop_GuideDlg*				m_pGuideDlg;				// 가이드 다이얼로그

	MAP_ITEMLIST	m_mapItemList;			// 제작 등록이 가능한 아이템 리스트
	MAP_ITEM		m_mapStandByItemList;	// 제작 대기중 아이템
	MAP_ITEM		m_mapPlantItemList;		// 제작공방 등록 아이템

	std::vector<CGUIControlID>	m_vecListPiece;	// 아이템 정보를 보여주는 다이얼로그 컨테이너

	GuildPlantItemInfo	m_tCurItem;			// 현재 선택한 아이템 정보

	eItemCategory		m_eCurItemCategory;			// 현재 선택한 아이템 분류
	eItemCategory		m_eSelItemCategory;			// m_pItemtDlg에 띄운 아이템의 아이템 분류
	eRewardCondition	m_eCurConsumptionCategory;	// 현재 선택한 소비 재화 분류
	eRewardCondition	m_eSelConsumptionCategory;	// m_pItemtDlg에 띄운 아이템의 소비 재화 분류

	__int64	m_iGuildPoint;		// 길드 포인트
	__int64	m_iGuildManagerTR;	// 길드 운영 TR

	int	m_iCurPage;			// 현재 페이지
	int	m_iSelPage;			// m_pItemtDlg에 띄운 아이템이 선택된 페이지
	int	m_iMaxPage;			// 최대 페이지
	int	m_iSelIndex;		// m_pItemtDlg에 띄운 아이템이 선택된 m_vecListPiece 컨테이너의 인덱스
	int	m_iMyGuildPoint;	// 마이 길드 포인트

	bool	m_bClickWorkshopList;	// m_pProductionDlg의 Workshop_List 드롭박스를 클릭했는가
	bool	m_bClickLimitList;		// m_pProductionDlg의 LimitList 드롭박스를 클릭했는가
};