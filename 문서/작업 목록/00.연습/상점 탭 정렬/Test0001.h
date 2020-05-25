#pragma once
class CTest0001 :
	public CTRCommandTarget
{
private:
	using x = int;
	using y = int;
	using w = int;
	using h = int;

private:
	static constexpr int MAX_DLG = 1;
	static constexpr int MAX_SHOP = 8;
	static constexpr int GAP[] = { 3,3,3,9,9,7,9 };
	static constexpr const char* SHOP_NAME[MAX_SHOP] =
	{
		"Shop_MainBtn_80000",
		"Shop_NormalBtn_10000",
		"Shop_MileageBtn_30000",
		"Shop_VIPBtn_40000",
		"Event1",
		"Shop_CoupleSale_90000",
		"Shop_SaleBtn_20000",
		"Shop_SelelcBtn_100000"
	};

private:
	enum EShopType
	{
		SHOPTYPE_MAIN,
		SHOPTYPE_NORMAL,
		SHOPTYPE_MILEAGE,
		SHOPTYPE_VIP,
		SHOPTYPE_EVENT1,
		SHOPTYPE_EVENT2,
		SHOPTYPE_SALE,
		SHOPTYPE_SELECT,
		SHOPTYPE_END
	};

private: // tuple
	enum ETuplePos { ORIGIN, MODIFY,INSIDE };
	enum ETupleXYWH { X, Y, W, H };

private:
	typedef struct tagDialog
	{
		union
		{
			struct
			{
				unique_ptr<CGUIDialog> m_pMain;
			};
			array<unique_ptr<CGUIDialog>, MAX_DLG> m_arrDlg;
		};
		tagDialog() :m_pMain(nullptr) {}
		~tagDialog() {}
	}DIALOG;

	typedef struct tagInsideData
	{
		string strName;
		pair<x, y> pairPos;
	}INSIDE_DATA;

private:
	DIALOG m_pDlg;
	unordered_map<string, tuple<tuple<x, y, w, h>, tuple<x, y, w, h>, vector<INSIDE_DATA>>> m_mapPos;

public:
	CTest0001();
	virtual ~CTest0001();

public:
	void showDialog();
	void closeDialog();

private:
	void InitRectInfo();
	void InitRectInfo(const unique_ptr<CGUIDialog>& _pDlg, string _strCtrlName);

	void SwapRectInfo(const string& _strA, const string& _strB);
	void SortRectInfo(const unique_ptr<CGUIDialog>& _pDlg, const string(&_strName)[MAX_SHOP]);
	void MoveRectInfo(const unique_ptr<CGUIDialog>& _pDlg, const string& _strCtrlName, const int _nX, const int _nY);

	int SetRectInfo(const unique_ptr<CGUIDialog>& _pDlg, string _strMove, string _strOrigin, int _nPosY, const int _nGap);

	bool OnCloseBtn(CGUIControl* sender);

	INSIDE_DATA GetInsideData(const unique_ptr<CGUIDialog>& _pDlg, const string& _strCtrlName, const CRectInfo& _info);
};

