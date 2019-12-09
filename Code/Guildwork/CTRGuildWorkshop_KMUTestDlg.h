#pragma once
#include "gameui/TRUserInterface.h"
#include "TRWorldshop_GUI.h"
//
#include <bitset>
class CTRGuildWorkshop_KMUTestDlg :
	public CTRCommandTarget
	public CTRWorldshop_GUI
{
public:
	const int MAX_TEST_DATANUM = 100;

public:
	enum EButton
	{
		BUTTON_CLOSE,
		BUTTON_OPTION1,
		BUTTON_OPTION2,
		BUTTON_OPTION3,
		BUTTON_OPTION4,
		BUTTON_OPTION5,
		BUTTON_END,
	};

	enum EListBox
	{
		LB_LISTBOX1,
		LB_END
	};

	enum EBitListBox
	{
		BLB_00 = 0x00,
		BLB_01 = 0x01,
		BLB_02 = 0x02,
		BLB_03 = 0x03,
		BLB_04 = 0x04,
		BLB_05 = 0x05,
		BLB_END
	};

	enum
	{
		eMAX_BIT_LISTCONDITION = 6
	};

public:
	struct SButton
	{
		string strName;
		CGUIButton* pGUI;
		function<void(void)> funcEvent;
	};

	struct SListBox
	{
		string strName;
		CGUIListBox* pGUI;
		vector<pair<int, bitset<EBitListBox::BLB_END>>> vecResult;
	};

private:
	CGUIDialog* m_pDlg = nullptr;

private:
	array<SButton, EButton::BUTTON_END> m_arrayButton;
	array<SListBox, EListBox::LB_END> m_arrayListBox;

public:
	CTRGuildWorkshop_KMUTestDlg();
	virtual ~CTRGuildWorkshop_KMUTestDlg();

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

public:
	void showDialog();
	void closeDialog();

private:
	bool Init();
	bool InitButton();
	bool InitListBox();

	void UpdateListBox(SButton& _sButton, SListBox& _sListBox, EBitListBox _eBit, function<bool(int)> _funcObj);
};

