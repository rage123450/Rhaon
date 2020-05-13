#pragma once
#include "gameui/TRUserInterface.h"
#include "TRGuildWorkshop_GUI.h"
//
#include "TRWorkshopBase.h"
#include "gameui/YesNoDialog.h"

class CTRGuildWorkshop_WarehouseDlg;
class CTRGuildWorkshop_ExpenseDlg;
class CTRGuildWorkshop_GuideDlg;

class CTRWorkshop_ListDlg :
	public CTRCommandTarget,
	public CTRGuildWorkshop_GUI
{
private:
	constexpr static int MAX_LISTPIECE = 8;

public:
	enum EGUIName
	{
		GN_LISTBASE,
		GN_LISTDLG,
		GN_LISTPIECE,
		GN_LISTPIECE02,
		GN_LISTPIECE03,
		GN_LISTPIECE04,
		GN_LISTPIECE05,
		GN_LISTPIECE06,
		GN_LISTPIECE07,
		GN_LISTPIECE08,
		GN_END
	};

	enum EButtonName
	{
		// ListBase
		BN_CLOSE,

		// ListDlg
		BN_PREVBTN,
		BN_NEXTBTN,
		
		// ListPiece
		BN_BUYBTN,
		BN_END
	};

	enum EFrameName
	{
		// ListBase
		FN_WORKSHOP_LISTDLG,
		FN_END
	};

	enum EStaticTextName
	{
		// ListDlg
		SN_PAGENUM,

		// ListPiece
		SN_GOODSNAME,
		SN_LIMITEDTIME,
		SN_PRICE,
		SN_END
	};

	enum EImageControlName
	{
		// ListPiece
		IN_IMAGE,
		IN_TRIMG,
		IN_CASHIMG,
		IN_IMAGECTRL,
		IN_END
	};

public:
	struct SListPiece
	{
		enum EButtonName
		{
			BN_BUYBTN,
			BN_END
		};

		enum EStaticTextName
		{
			SN_GOODSNAME,
			SN_LIMITEDTIME,
			SN_PRICE,
			SN_END
		};

		enum EImageControlName
		{
			IN_TRIMG,
			IN_CASHIMG,
			IN_IMAGECTRL,
			IN_END
		};

		array<tuple<string, function<void(int)>>, SListPiece::BN_END> arrayButton;
		array<CGUIStaticText*, SListPiece::SN_END> arrayStaticText = { nullptr, };
		array<CGUIImageCtrl*, SListPiece::IN_END> arrayImageCtrl = { nullptr, };
		CGUIButton* pButton = nullptr;
		CGUIItemImageCtrl* pItemImageCtrl = nullptr;
	};

private:
	array<CGUIDialog*, EGUIName::GN_END> m_arrayDlg = { nullptr, };
	array<tuple<string, function<void(void)>>, EButtonName::BN_END> m_arrayButton;
	array<CGUIStaticText*, EStaticTextName::SN_END> m_arrayStaticText = { nullptr, };
	array<CGUIImageCtrl*, EImageControlName::IN_END> m_arrayImageCtrl = { nullptr, };
	array<SListPiece, MAX_LISTPIECE> m_arrayListPiece;

	int m_nTotalItem = 0;
	int m_nCurItem = 0;
	int m_nTotalPage = 0;
	int m_nCurPage = 0;

	CYesNoDialogEx<CTRWorkshop_ListDlg> m_pYesNoDlg;

	vector<tuple<time_type, GuildPlantSellInfo>> m_useList;
	int m_nItemDescNum = -1;
	int m_nSellNum = 0;
	int m_nSellItemIndex = 0;
	time_type m_tFinishDate = 0;

	bool m_bStart = false;

public:
	CTRWorkshop_ListDlg();
	virtual ~CTRWorkshop_ListDlg();

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

	virtual void InitName();
	virtual void InitGUI();

	virtual void InitButton();
	virtual void InitStaticText();
	virtual void InitImageControl() {}

	virtual void showDialog();
	virtual void closeDialog();
	
	// 길드공방 아이템 리스트 요청 관련
	void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList);

	// 길드공방 아이템 구매를 요청 성공
	void onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount);

	// ========================================================================================================================================================

	// 길드 운영 TR 요청 성공
	void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR);

	// 길드 운영 TR 투자에 성공
	void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR);

	// 길드 운영 TR 창고 확장 정보를 요청 성공
	void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue);

	// 길드 운영 TR 투자자 리스트 요청 성공
	void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList);

	// 길드 재화 지출 리스트 요청 성공
	void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList);

private:
	void InitPage();
	void InitListPiece();
	
	void UpdatePage();
	void UpdateListPiece();

	void showGiveYes();

private:	// CTRGuildWorkshop_ManagementDlg
	CGUIControlID m_guildPointDlgID = CGUIControlID::INVALID_ID;	// 포인트 목록 다이얼로그
	CTRGuildWorkshop_WarehouseDlg* m_pWarehouseDlg = nullptr;		// 운영 TR 창고
	CTRGuildWorkshop_ExpenseDlg* m_pExpenseDlg = nullptr;			// 재화 지출 현황
	shared_ptr<CTRGuildWorkshop_GuideDlg> m_pGuideDlg = nullptr;	// 가이드

	__int64	m_iGuildPoint;		// 길드 포인트
	__int64	m_iGuildManagerTR;	// 길드 운영 TR
	int	m_iMyGuildPoint;		// 마이 길드 포인트

	void _setGuildPointDialog();
	void _updateGuildPointDialog();

	void _setStaticText(CGUIControlID ctrlID, const std::string& name, const std::string& message);	// CGUIStaticText의 텍스트 변경
	void _setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string& name);		// parent의 name 컨트롤 위치에 child를 위치시킨다

public:
	void LoadGuideList(CTRGuildPlanInfoLoader* pLoader);
};

