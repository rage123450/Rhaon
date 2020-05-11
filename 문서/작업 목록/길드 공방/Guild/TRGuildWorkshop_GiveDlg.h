#pragma once
#include "gameui/TRUserInterface.h"
//
#include "gameui/YesNoDialog.h"
#include "TRGuildWorkshop_GUI.h"

class CTRGuildWorkshop_GiveDlg :
	public CTRCommandTarget,
	public CTRGuildWorkshop_GUI
{
public:
	enum EDialog
	{
		DLG_GIVEPOPUP,
		DLG_SELECTITEMDLG,
		DLG_END
	};

	enum EListBoxCondition
	{
		LBC_01,
		LBC_02,
		LBC_03,
		LBC_04,
		LBC_END
	};

public:
	enum EGUIName
	{
		GN_GIVEPOPUP,
		GN_SELECTITEMDLG,
		GN_END
	};

	enum EButtonName
	{
		// GivePopup
		BUTTON_CLOSE,
		BUTTON_GIVE,
		BUTTON_OPTION1,
		BUTTON_OPTION2,
		BUTTON_OPTION3,
		BUTTON_OPTION4,
		BUTTON_IN,
		BUTTON_OUT,
		BUTTON_END
	};

	enum EStaticTextName
	{
		// GivePopup
		ST_TITLE,
		ST_OPTION1,
		ST_OPTION2,
		ST_OPTION3,
		ST_OPTION4,

		// SelectItemDlg
		ST_SELECTITEM_GOODSNAME,
		ST_SELECTITEM_DAY,
		ST_SELECTITEM_TYPEMENT,
		ST_END
	};

	enum EImageControlName
	{
		// GivePopup
		IC_BASE,

		// SelectItemDlg
		IC_SELECTITEM_IMAGE,
		IC_SELECTITEM_BASE,
		IC_END
	};

	enum EFrameName
	{
		// GivePopup
		FN_WORKSHOP_SELECTITEMDLG,
		FN_END
	};

	enum EListBoxName
	{
		// GivePopup
		LB_POSSIBLEMEMBER,
		LB_RECEIVEMEMBER,
		LB_END
	};

private:
	struct SButtonEvent
	{
		string strName;
		function<void(void)> funcEvent;
	};

	struct SListBox
	{
		CGUIListBox* pListBox = nullptr;
		vector<string> vecName;
	};

private:
	CYesNoDialogEx<CTRGuildWorkshop_GiveDlg> m_yesNoDlg;

private:
	array<CGUIDialog*, EDialog::DLG_END> m_arrayDlg = { nullptr, };
	array<CGUIButton*, EButtonName::BUTTON_END> m_arrayButton = { nullptr, };
	array<CGUIStaticText*, EStaticTextName::ST_END> m_arrayStaticText = { nullptr, };
	array<CGUIImageCtrl*, EImageControlName::IC_END> m_arrayImageControl = { nullptr, };

	array<SButtonEvent, EButtonName::BUTTON_END> m_arrayButtonEvent;
	array<SListBox, EListBoxName::LB_END> m_arrayListBox;
	array<function<bool(string, bool)>, EListBoxCondition::LBC_END> m_arrayListBoxCondition;

	CGUIItemImageCtrl* m_pSelectItemImageCtrl = nullptr;

	vector<string> m_userList;
	int m_nItemIndexNum = 0;
	time_type m_iFinishDate = 0;
	GuildPlantMakeInfo m_sGuildPlantMakeInfo;

	bool m_bStart = false;

public:
	CTRGuildWorkshop_GiveDlg();
	virtual ~CTRGuildWorkshop_GiveDlg();

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

	// CTRGuildWorkshop_GUI을(를) 통해 상속됨
	virtual void InitName();
	virtual void InitGUI();
	virtual void InitButton();
	virtual void InitStaticText();
	virtual void InitImageControl();
	virtual void InitListBox();

public:
	void showDialog();
	void closeDialog();

	// 아이템 지급 가능 길드원 리스트 요청 관련
	void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList);

	void showGiveYes();

private:
	void InitListBoxCondition();
	void InitSelectDlg();

	void UpdateListBox(SListBox& _sListBox);
	void ChangeListBox(SListBox& _sFromListBox, SListBox& _sToListBox);
	void ClearListBox(SListBox& _sListBox);
	map<eGuildPlantGiveCondition, bool> GetConditionCheck();

public:
	void SetSelectItemIndex(int _nSelectItemIndexNum) { m_nItemIndexNum = _nSelectItemIndexNum; }
	void SetFinishDate(time_type _iFinishDate) { m_iFinishDate = _iFinishDate; }
	void SetGuildPlantMakeInfo(GuildPlantMakeInfo _sGuildPlantMakeInfo) { m_sGuildPlantMakeInfo = _sGuildPlantMakeInfo; }
};

