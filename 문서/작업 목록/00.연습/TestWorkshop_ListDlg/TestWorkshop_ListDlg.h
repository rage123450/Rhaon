#pragma once
class CTestWorkshop_ListDlg
{
private:
	static constexpr size_t MAX_LISTPIECE = 8;
	static constexpr size_t MAX_PAGE = 9;
	static constexpr size_t MAX_ITEMNUM = 13;

private:
	typedef struct tagItemInfo
	{
		int nName;
		int nDay;
		int nMoney;
		tagItemInfo() : nName(0), nDay(0), nMoney(0) {}
		tagItemInfo(int _nName, int _nDay, int _nMoney) : nName(_nName), nDay(_nDay), nMoney(_nMoney) {}
	}ITEM_INFO;

private:
	unique_ptr<CGUIDialog> m_pDlgListBase = nullptr;
	unique_ptr<CGUIDialog> m_pDlgListDlg = nullptr;
	array<unique_ptr<CGUIDialog>, MAX_LISTPIECE> m_arrDlgListPiece;
	array<ITEM_INFO, MAX_ITEMNUM> m_arrItemInfo;

	int m_nCurPage = 1;
	int m_nMaxPage = 0;

public:
	CTestWorkshop_ListDlg();
	virtual ~CTestWorkshop_ListDlg();

public:
	void showDialog();
	void closeDialog();

private:
	void InitItemInfo();
	void UpdateListPiece();
	void UpdateListPiece(unique_ptr<CGUIDialog>& _pDlg, const ITEM_INFO& _tagItem);

	int GetCalMaxPage();

	bool OnClose(CGUIControl* _pCtrl);
	bool OnPrevBtn(CGUIControl* _pCtrl);
	bool OnNextBtn(CGUIControl* _pCtrl);
	bool OnBuyBtn(CGUIControl* _pCtrl);
};