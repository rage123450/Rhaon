#include "stdafx.h"
#include "Test0001.h"
//
#include "gui/GUIMacro.h"

CTest0001::CTest0001()
{
}

CTest0001::~CTest0001()
{
	closeDialog();
}

void CTest0001::showDialog()
{
	m_pDlg.m_pMain = static_cast<unique_ptr<CGUIDialog>>(CTRUserInterface::loadGUI("gui/shop/Renewal_shop_test.gui", string("")));
	m_pDlg.m_pMain->centerPosition();
	m_pDlg.m_pMain->setModalDialog(true);
	CTRUserInterface::getInstance().setGUIAnimatorPopupShow(m_pDlg.m_pMain.get());

	BIND_BUTTON_FUNC(m_pDlg.m_pMain, "CloseBtn", CTest0001::OnCloseBtn);

	InitRectInfo();

	//CGUIFrameImage* pTemp = (CGUIFrameImage *)m_pDlg.m_pMain->findControl("DlgBase", GUI_SUB_CONTROL_FRAME);
	//pTemp->setClientPos(500, 500);

	// MoveRectInfo(m_pDlg.m_pMain, SHOP_NAME[EShopType::SHOPTYPE_MAIN],500,500);
	// MoveRectInfo(m_pDlg.m_pMain, SHOP_NAME[EShopType::SHOPTYPE_MILEAGE], 500, 500);
	// MoveRectInfo(m_pDlg.m_pMain, SHOP_NAME[EShopType::SHOPTYPE_VIP], 500, 500);

	// SwapRectInfo("Shop_CoupleSale_90000", "Shop_SaleBtn_20000");

	SortRectInfo(m_pDlg.m_pMain,
		{
			"Event1",
			"Shop_MileageBtn_30000",
			"Shop_VIPBtn_40000",
			"Shop_CoupleSale_90000",
			"Shop_NormalBtn_10000",
			"Shop_SaleBtn_20000",
			"Shop_SelelcBtn_100000",
			"Shop_MainBtn_80000"
		});
}

void CTest0001::closeDialog()
{
	for_each(begin(m_pDlg.m_arrDlg), end(m_pDlg.m_arrDlg), [](unique_ptr<CGUIDialog>& _pDlg)
	{
		if(_pDlg)
		{
			CTRUserInterface::getInstance().setGUIAnimatorPopupHide(_pDlg.get());
		}
	});
}

void CTest0001::InitRectInfo()
{
	for(size_t i = 0; i < MAX_SHOP; i++)
	{
		InitRectInfo(m_pDlg.m_pMain, SHOP_NAME[i]);
	}
}

void CTest0001::InitRectInfo(const unique_ptr<CGUIDialog>& _pDlg, string _strCtrlName)
{
	if(_strCtrlName == "Event1")
	{
		get<ORIGIN>(m_mapPos[_strCtrlName]) = make_tuple(35, 571, 238, 98);
		get<MODIFY>(m_mapPos[_strCtrlName]) = make_tuple(35, 571, 238, 98);
	}
	else if(_strCtrlName == "Event2")
	{
		get<ORIGIN>(m_mapPos[_strCtrlName]) = make_tuple(35, 679, 238, 59);
		get<MODIFY>(m_mapPos[_strCtrlName]) = make_tuple(35, 679, 238, 59);
	}
	else
	{
		CRectInfo info = CRectInfo(0, 0, 0, 0);
		GET_CONTROL_RECT(_pDlg, _strCtrlName, info);
		get<ORIGIN>(m_mapPos[_strCtrlName]) = make_tuple(info.left, info.top, info.width(), info.height());
		get<MODIFY>(m_mapPos[_strCtrlName]) = make_tuple(info.left, info.top, info.width(), info.height());

		if(_strCtrlName == "Shop_MileageBtn_30000")
		{
			get<INSIDE>(m_mapPos[_strCtrlName]).push_back(GetInsideData(_pDlg, "MileagePointGuide", info));
			get<INSIDE>(m_mapPos[_strCtrlName]).push_back(GetInsideData(_pDlg, "MileagePointGuideEf", info));
			get<INSIDE>(m_mapPos[_strCtrlName]).push_back(GetInsideData(_pDlg, "MyMileage", info));
		}
		else if(_strCtrlName == "Shop_VIPBtn_40000")
		{
			get<INSIDE>(m_mapPos[_strCtrlName]).push_back(GetInsideData(_pDlg, "VipGuide", info));
			for(size_t i = 1; i <= 10; i++)
			{
				get<INSIDE>(m_mapPos[_strCtrlName]).push_back(GetInsideData(_pDlg, "Vip" + to_string(i), info));
			}
			get<INSIDE>(m_mapPos[_strCtrlName]).push_back(GetInsideData(_pDlg, "Gauge", info));
			get<INSIDE>(m_mapPos[_strCtrlName]).push_back(GetInsideData(_pDlg, "GaugeBase", info));
		}
	}
}

void CTest0001::SwapRectInfo(const string& _strA,const string& _strB)
{
	int nAx, nAy, nAw, nAh;
	tie(nAx, nAy, nAw, nAh) = get<MODIFY>(m_mapPos[_strA]);

	int nBx, nBy, nBw, nBh;
	tie(nBx, nBy, nBw, nBh) = get<MODIFY>(m_mapPos[_strB]);

	if(nAw != nBw && nAh != nBh)
	{
		return;
	}

	tuple<x, y, w, h> tupleTemp = get<MODIFY>(m_mapPos[_strA]);
	get<MODIFY>(m_mapPos[_strA]) = get<MODIFY>(m_mapPos[_strB]);
	get<MODIFY>(m_mapPos[_strB]) = tupleTemp;

	int nX, nY;
	tie(nX, nY, ignore, ignore) = get<MODIFY>(m_mapPos[_strA]);
	SET_CONTROL_RECT(m_pDlg.m_pMain, _strA, nX, nY);
	tie(nX, nY, ignore, ignore) = get<MODIFY>(m_mapPos[_strB]);
	SET_CONTROL_RECT(m_pDlg.m_pMain, _strB, nX, nY);
}

void CTest0001::SortRectInfo(const unique_ptr<CGUIDialog>& _pDlg, const string(&_strName)[MAX_SHOP])
{
	int nPosY = get<Y>(get<ORIGIN>(m_mapPos[SHOP_NAME[0]]));
	for(size_t i = 0; i < MAX_SHOP; i++)
	{
		nPosY = SetRectInfo(_pDlg, _strName[i], SHOP_NAME[i], nPosY, GAP[i]);
	}
}

void CTest0001::MoveRectInfo(const unique_ptr<CGUIDialog>& _pDlg, const string & _strCtrlName, const int _nX, const int _nY)
{
	if(_strCtrlName == "Event1")
	{
		SET_CONTROL_RECT(_pDlg, "DlgBase", _nX, _nY);
	}
	else if(_strCtrlName == "Event2")
	{
		SET_CONTROL_RECT(_pDlg, "DlgBase2", _nX, _nY);
	}
	else
	{
		SET_CONTROL_RECT(_pDlg, _strCtrlName, _nX, _nY);
	}

	if(_strCtrlName == "Shop_MileageBtn_30000" || _strCtrlName == "Shop_VIPBtn_40000")
	{
		for(auto& i : get<INSIDE>(m_mapPos[_strCtrlName]))
		{
			SET_CONTROL_RECT(_pDlg, i.strName, _nX + i.pairPos.first, _nY + i.pairPos.second);
		}
	}
}

int CTest0001::SetRectInfo(const unique_ptr<CGUIDialog>& _pDlg, string _strMove, string _strOrigin, int _nPosY, const int _nGap)
{
	int nPosX = get<X>(get<MODIFY>(m_mapPos[_strMove]));
	int nPosH = get<H>(get<MODIFY>(m_mapPos[_strMove]));

	MoveRectInfo(_pDlg, _strMove, nPosX, _nPosY);

	return _nPosY + nPosH + _nGap;
}

bool CTest0001::OnCloseBtn(CGUIControl * sender)
{
	closeDialog();
	return true;
}

CTest0001::INSIDE_DATA CTest0001::GetInsideData(const unique_ptr<CGUIDialog>& _pDlg, const string & _strCtrlName, const CRectInfo& _info)
{
	INSIDE_DATA temp;
	CRectInfo insideInfo = CRectInfo(0, 0, 0, 0);
	int nX, nY;

	temp.strName = _strCtrlName;
	GET_CONTROL_RECT(_pDlg, temp.strName, insideInfo);
	nX = insideInfo.left - _info.left;
	nY = insideInfo.top - _info.top;
	temp.pairPos = make_pair(nX, nY);
	get<INSIDE>(m_mapPos[_strCtrlName]).push_back(temp);

	return temp;
}
