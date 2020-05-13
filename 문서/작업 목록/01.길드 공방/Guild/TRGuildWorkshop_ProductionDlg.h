#pragma once
#include "gameui/TRUserInterface.h"
#include "TRGuildWorkshop_GUI.h"
//
#include "TRWorkshopBase.h"
#include "gameui/YesNoDialog.h"

class CTRGuildWorkshop_RankDlg;
class CTRGuildWorkshop_GiveDlg;
class CTRGuildWorkshop_WarehouseDlg;
class CTRGuildWorkshop_ExpenseDlg;
class CTRGuildWorkshop_GuideDlg;

class CTRGuildWorkshop_ProductionDlg :
	public CTRCommandTarget,
	public CTRGuildWorkshop_GUI
{
private:
	constexpr static int MAX_LISTPIECE = 8;

public:
	enum EGUIName
	{
		GN_PROGRESSBASE,
		GN_PROGRESSLISTDLG,
		GN_SELECTITEMDLG,
		GN_PROGRESSLISTPIECE,
		GN_PROGRESSLISTPIECE02,
		GN_PROGRESSLISTPIECE03,
		GN_PROGRESSLISTPIECE04,
		GN_PROGRESSLISTPIECE05,
		GN_PROGRESSLISTPIECE06,
		GN_PROGRESSLISTPIECE07,
		GN_PROGRESSLISTPIECE08,
		GN_END
	};

	enum EButtonName
	{
		// ProgressBase 
		BN_CLOSE,
		BN_GIVE,
		BN_RESETL,
		BN_RANKPOPUP,

		// ProgressListDlg
		BN_PREV,
		BN_NEXT,

		// ProgressListPiece
		BN_GOODS,
		BN_END
	};

	enum EStaticTextName
	{
		// ProgressBase 
		STN_NEEDGUILDPOINT,
		STN_DAY,
		STN_TITLE,
		STN_MYPOINT,
		STN_NEEDGUILDPOINTPERCENT,

		// ProgressListDlg
		STN_PAGENUM,

		// ProgressListPiece
		STN_LISTPIECE_GOODSNAME,
		STN_LISTPIECE_DAY,

		// SelectItemDlg
		STN_SELECTITEM_GOODSNAME,
		STN_SELECTITEM_DAY,
		STN_SELECTITEM_TYPEMENT,
		STN_END
	};

	enum EFrameName
	{
		// ProgressBase 
		FN_WORKSHOP_PROGRESSLISTDLG,
		FN_WORKSHOP_SELECTITEMDLG,
		FN_WORKSHOP_GAUGE,

		// ProgressListDlg
		FN_GOODSITEM,
		FN_END
	};

	enum EImageControlName
	{
		// ProgressBase
		ICN_GAUGEIMG,
		ICN_INBASE,

		// ProgressListPiece
		ICN_LISTPIECE_IMAGE,

		// SelectItemDlg
		ICN_SELECTDLG_IMAGE,
		ICN_END
	};

private:
	struct SButtonEvent
	{
		string strName;
		function<void(void)> funcEvent;
		function<void(int, GuildPlantMakeInfo&)> funcEvent2;
	};

	struct SListPiece
	{
		enum EStaticTextName
		{
			SN_GOODSNAME,
			SN_DAY,
			SN_END
		};

		enum EItemImageCtrlName
		{
			IN_IMAGE,
			IN_END
		};

		array<CGUIStaticText*, SListPiece::SN_END> arrayStaticText = { nullptr, };
		array<CGUIItemImageCtrl*, SListPiece::IN_END> arrayItemImageCtrl = { nullptr, };
		CGUIButton* pButton = nullptr;
		SButtonEvent sButtonEvent;
	};

private:
	shared_ptr<CTRGuildWorkshop_RankDlg> m_pRankDlg = nullptr;
	shared_ptr<CTRGuildWorkshop_GiveDlg> m_pGiveDlg = nullptr;
	CYesNoDialogEx<CTRGuildWorkshop_ProductionDlg> m_yesNoChangeDlg;

private:
	array<CGUIDialog*, EGUIName::GN_END> m_arrayDlg = { nullptr, };
	array<CGUIStaticText*, EStaticTextName::STN_END> m_arrayStaticText = { nullptr, };
	array<CGUIImageCtrl*, EImageControlName::ICN_END> m_arrayImageControl = { nullptr, };
	array<CGUIFrameImage*, EFrameName::FN_END> m_arrayFrame = { nullptr, };

	array<SButtonEvent, EButtonName::BN_END> m_arrayButtonEvent;
	array<SListPiece, MAX_LISTPIECE> m_arrayListPiece;

	vector<tuple<int, GuildPlantMakeInfo>> m_guildplant;

	CGUIItemImageCtrl* m_pSelectItemImageCtrl = nullptr;
	CGUIButton* m_pGiveBtn = nullptr;
	
	bool m_bStart = false;

	int m_nTotalItem = 0;
	int m_nCurItem = 0;
	int m_nTotalPage = 0;
	int m_nCurPage = 0;

	int m_nItemDescNum = -1;
	time_type m_iFinishDate = 0;
	GuildPlantMakeInfo m_sGuildPlantMakeInfo;

	tuple<GuildPlantMakeInfo, int, eGuildPlantDistributeKind> m_tupleMakeProgressItem;
	tuple<int, int> m_tupleChecked;			// CurPage, CheckedIndex

	int m_nChangeItemIndexNum = 0;

	string m_strPageNumSign = " / ";

public:
	CTRGuildWorkshop_ProductionDlg();
	virtual ~CTRGuildWorkshop_ProductionDlg();

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

	// CTRGuildWorkshop_GUI��(��) ���� ��ӵ�
	virtual void InitName();
	virtual void InitGUI();
	virtual void InitButton();
	virtual void InitImageControl();
	virtual void InitStaticText();
	virtual void InitFrame();

public:
	void showDialog();
	void closeDialog();

public:
	// ������ ���� ��� ������ ����Ʈ ��û ����
	void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant);

	// ������ ���� ���� ���� ����Ʈ ��û ����
	void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList);

	// ������ ������ �⿩�� ���� ����Ʈ ��û ����
	void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList);

	// ������ ���� ���� ������ ���� ��û ����
	void onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind);

	// ������ ������ ���޸� ��û ����
	void onRecvGuildPlantGiveGiftOK(int iItemIndexNum);

	// ������ ���� �⿩ ������ ���� ����
	void onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum);

	// ========================================================================================================================================================

	// ��� � TR ��û ����
	void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR);

	// ��� � TR ���ڿ� ����
	void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR);

	// ��� � TR â�� Ȯ�� ������ ��û ����
	void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue);

	// ��� � TR ������ ����Ʈ ��û ����
	void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList);

	// ��� ��ȭ ���� ����Ʈ ��û ����
	void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList);

private:
	void InitPage();
	void InitListPiece();
	void InitSelectDlg(int _nIndex = 0);
	void InitNeedGuildPoint(int _nCurNeedGuildPoint, int _nMaxNeedGuildPoint);
	void InitNeedGuildPointPercent(int _nCurNeedGuildPoint, int _nMaxNeedGuildPoint);
	void InitSelectDay(time_type _nDurationDay, bool _bComplete = false);
	void InitMyPoint(int _nMyPoint);
	void InitCheckedButton();

	void UpdateListPiece();
	void UpdatePage();
	void UpdateSelectDlg(GuildPlantMakeInfo& temp, int _nIndex = 0);
	void UpdateCheckedButton(tuple<int, int> _tupleChecked);

	void ClearSelectDlg();
	void showChangeYes();
	void SettingGaugeImg(int _nPercent);

	bool IsMyGuildGradeMaster();
	bool IsSelectCompleteMakeItem();

	void SetPage(int _nPageNum);
	
public:
	void LoadGuideList(CTRGuildPlanInfoLoader* pLoader);

private:	// Dummy : Test
	void DummyInitData(int _nNum);

private:	// CTRGuildWorkshop_ManagementDlg
	CGUIControlID m_guildPointDlgID = CGUIControlID::INVALID_ID;	// ����Ʈ ��� ���̾�α�
	CTRGuildWorkshop_WarehouseDlg* m_pWarehouseDlg = nullptr;		// � TR â��
	CTRGuildWorkshop_ExpenseDlg* m_pExpenseDlg = nullptr;			// ��ȭ ���� ��Ȳ
	shared_ptr<CTRGuildWorkshop_GuideDlg> m_pGuideDlg = nullptr;	// ���̵�

	__int64	m_iGuildPoint;		// ��� ����Ʈ
	__int64	m_iGuildManagerTR;	// ��� � TR
	int	m_iMyGuildPoint;		// ���� ��� ����Ʈ

	void _setGuildPointDialog();
	void _updateGuildPointDialog();

	void _setStaticText(CGUIControlID ctrlID, const std::string& name, const std::string& message);	// CGUIStaticText�� �ؽ�Ʈ ����
	void _setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string& name);		// parent�� name ��Ʈ�� ��ġ�� child�� ��ġ��Ų��
};

