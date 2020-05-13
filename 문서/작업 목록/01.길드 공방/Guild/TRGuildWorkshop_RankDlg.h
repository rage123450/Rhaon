#pragma once
#include "gameui/TRUserInterface.h"
#include "TRGuildWorkshop_GUI.h"

class CTRGuildWorkshop_RankDlg :
	public CTRCommandTarget,
	public CTRGuildWorkshop_GUI
{
private:
	constexpr static int MAX_LISTPIECE = 6;

public:
	enum ERank
	{
		RANK_BASE,
		RANK_LIST,
		RANK_LISTPIECE01,
		RANK_LISTPIECE02,
		RANK_LISTPIECE03,
		RANK_LISTPIECE04,
		RANK_LISTPIECE05,
		RANK_LISTPIECE06,

		// Workshop_SelectItemDlg
		RANK_SELECTITEM,
		END
	};

public:
	enum EGUIName
	{
		GN_RANKPOPUP,
		GN_RANK_LIST,
		GN_RANK_LISTPIECE,

		// Workshop_SelectItemDlg
		GN_SELECTITEMDLG,
		GN_END
	};

	enum EButtonName
	{
		// Rank_Popup
		BN_CLOSE,

		// Rank_List
		BN_PREV,
		BN_NEXT,
		BN_END
	};

	enum EStaticTextName
	{
		// Rank_List
		SN_PAGENUM,

		// Rank_ListPiece
		SN_LISTPIECE_NAME,
		SN_LISTPIECE_POINT,
		SN_LISTPIECE_RANKNUM,

		// SelectItemDlg
		SN_SELECTITEM_GOODSNAME,
		SN_SELECTITEM_DAY,
		SN_SELECTITEM_TYPEMENT,
		SN_END
	};

	enum EImageControlName
	{
		// SelectItemDlg
		IC_SELECTITEM_IMAGE,
		IC_END
	};

	enum EFrameName
	{
		// RankPopup
		FN_WORKSHOP_RANK_LIST,
		FN_WORKSHOP_SELECTITEMDLG,
		FN_END
	};

private:
	struct SButtonEvent
	{
		string strName;
		function<void(void)> funcEvent;
	};

	struct SListPiece
	{
		enum EstaticTextName
		{
			SN_NAME,
			SN_POINT,
			SN_RANKNUM,
			SN_END
		};

		array<CGUIStaticText*, SListPiece::SN_END> arrayStaticText = { nullptr, };
	};

private:
	CGUIDialog* m_arrDlg[ERank::END] = { nullptr, };
	
	array<SButtonEvent, EButtonName::BN_END> m_arrayButtonEvent;
	array<CGUIStaticText*, EStaticTextName::SN_END> m_arrayStaticText = { nullptr, };
	array<CGUIImageCtrl*, EImageControlName::IC_END> m_arrayImageCtrl = { nullptr, };
	array<SListPiece, MAX_LISTPIECE> m_arrayListPiece;

	CGUIItemImageCtrl* m_pSelectItemImageCtrl = nullptr;

	int m_nTotalNickName = 0;
	int m_nCurNickName = 0;
	int m_nTotalPage = 0;
	int m_nCurPage = 0;

	vector<tuple<int, string>> m_userList;
	tuple<GuildPlantMakeInfo, int, eGuildPlantDistributeKind> m_tupleMakeProgressItem;
	GuildPlantMakeInfo m_sGuildPlantMakeInfo;
	time_type m_nFinishDate = 0;

	bool m_bStart = false;

	string m_strPageNumSign = " / ";

public:
	CTRGuildWorkshop_RankDlg();
	virtual ~CTRGuildWorkshop_RankDlg();

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

public:
	void showDialog();
	void closeDialog();

public:
	virtual void InitName();
	virtual void InitGUI();

	virtual void InitButton();
	virtual void InitStaticText();
	virtual void InitImageControl();

	// 길드공방 아이템 기여도 순위 리스트 요청 관련
	void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList);

private:
	void InitPage();
	void InitListPiece();

	void UpdateListPiece();
	void UpdatePage();

	void InitSelectDlg();
	void UpdateSelectDlg();

public:
	void SetFinishDate(time_type _nFinishDate) { m_nFinishDate = _nFinishDate; }
	void SetMakeProgressItem(tuple<GuildPlantMakeInfo, int, eGuildPlantDistributeKind> _tupleMakeProgressItem) { m_tupleMakeProgressItem = _tupleMakeProgressItem; }
	void SetGuildPlantMakeInfo(GuildPlantMakeInfo _sGuildPlantMakeInfo) { m_sGuildPlantMakeInfo = _sGuildPlantMakeInfo; }

private:	//Dummy
	void DummyInitData();
};

