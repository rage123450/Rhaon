#include "stdafx.h"
#include "TestWorkshop_ListDlg.h"
#include "gui/GUIMacro.h"
#include "gameui/TRShortTimeMessage.h"

CTestWorkshop_ListDlg::CTestWorkshop_ListDlg()
{
}

CTestWorkshop_ListDlg::~CTestWorkshop_ListDlg()
{
	closeDialog();
}

void CTestWorkshop_ListDlg::showDialog()
{
	closeDialog();

	std::string errmsg;
	m_pDlgListBase = unique_ptr<CGUIDialog>(CTRUserInterface::loadGUI("gui/Guild/Workshop/Workshop_ListBase.gui", errmsg));
	m_pDlgListBase->centerPosition();
	m_pDlgListBase->setModalDialog(true);
	CTRUserInterface::getInstance().setGUIAnimatorPopupShow(m_pDlgListBase.get());
	CGUIManager::getInstance().setFocus(m_pDlgListBase->getControlID());
	BIND_BUTTON_FUNC(m_pDlgListBase, "Close", CTestWorkshop_ListDlg::OnClose);

	m_pDlgListDlg = unique_ptr<CGUIDialog>(CTRUserInterface::loadGUI(m_pDlgListBase->getControlID(), "gui/Guild/Workshop/Workshop_ListDlg.gui", errmsg));
	m_pDlgListDlg->setClientPos(m_pDlgListBase->findControl("Workshop_ListDlg", GUI_SUB_CONTROL_FRAME)->getClientRect());
	CTRUserInterface::getInstance().setGUIAnimatorPopupShow(m_pDlgListDlg.get());
	BIND_BUTTON_FUNC(m_pDlgListDlg, "PrevBtn", CTestWorkshop_ListDlg::OnPrevBtn);
	BIND_BUTTON_FUNC(m_pDlgListDlg, "NextBtn", CTestWorkshop_ListDlg::OnNextBtn);

	for(size_t i = 0; i < m_arrDlgListPiece.size(); i++)
	{
		m_arrDlgListPiece[i] = unique_ptr<CGUIDialog>(CTRUserInterface::loadGUI(m_pDlgListDlg->getControlID(), "gui/Guild/Workshop/Workshop_ListPiece.gui", errmsg));
		m_arrDlgListPiece[i]->setClientPos(m_pDlgListDlg->findControl("GoodsItem" + to_string(i + 1), GUI_SUB_CONTROL_FRAME)->getClientRect());
		BIND_BUTTON_FUNC(m_arrDlgListPiece[i], "BuyBtn", CTestWorkshop_ListDlg::OnBuyBtn);
	}

	m_nMaxPage = GetCalMaxPage();
	SET_CONTROL_TEXT(m_pDlgListDlg.get(), "PageNum", format("%02d/%02d", m_nCurPage, m_nMaxPage));

	InitItemInfo();
	UpdateListPiece();
}

void CTestWorkshop_ListDlg::closeDialog()
{
	CTRUserInterface::getInstance().setGUIAnimatorPopupHide(m_pDlgListBase.get());
	CTRUserInterface::getInstance().setGUIAnimatorPopupHide(m_pDlgListDlg.get());
}

void CTestWorkshop_ListDlg::InitItemInfo()
{
	for(size_t i = 0; i < MAX_ITEMNUM; i++)
	{
		ITEM_INFO tagItemInfo;
		tagItemInfo.nName = CRandomGen::instance.iRandom(100, 999);
		tagItemInfo.nMoney = CRandomGen::instance.iRandom(1000, 9999);
		tagItemInfo.nDay = CRandomGen::instance.iRandom(10, 99);
		m_arrItemInfo[i] = tagItemInfo;
	}
}

void CTestWorkshop_ListDlg::UpdateListPiece()
{
	for(size_t i = 0; i < m_arrDlgListPiece.size(); i++)
	{
		int nCurItemIndx = i + ((m_nCurPage - 1) * MAX_LISTPIECE);
		if(nCurItemIndx < MAX_ITEMNUM)
		{
			m_arrDlgListPiece[i]->setVisible(true);
			UpdateListPiece(m_arrDlgListPiece[i], m_arrItemInfo[nCurItemIndx]);
		}
		else
		{
			m_arrDlgListPiece[i]->setVisible(false);
			UpdateListPiece(m_arrDlgListPiece[i], ITEM_INFO());
		}
	}
}

void CTestWorkshop_ListDlg::UpdateListPiece(unique_ptr<CGUIDialog>& _pDlg, const ITEM_INFO& _tagItem)
{
	SET_CONTROL_TEXT(_pDlg.get(), "GoodsName", format("%d", _tagItem.nName));
	SET_CONTROL_TEXT(_pDlg.get(), "limitedTime", format("%d일 남음", _tagItem.nDay));
	SET_CONTROL_TEXT(_pDlg.get(), "Price", format("%d원", _tagItem.nMoney));
}

int CTestWorkshop_ListDlg::GetCalMaxPage()
{
	int nShare = MAX_ITEMNUM / MAX_LISTPIECE;
	int nRest = MAX_ITEMNUM % MAX_LISTPIECE;

	return nShare += nRest == 0 ? 0 : 1;
}

bool CTestWorkshop_ListDlg::OnClose(CGUIControl * _pCtrl)
{
	closeDialog();
	return true;
}

bool CTestWorkshop_ListDlg::OnPrevBtn(CGUIControl * _pCtrl)
{
	SET_CONTROL_TEXT(m_pDlgListDlg.get(), "PageNum", format("%02d/%02d", m_nCurPage -= m_nCurPage <= 1 ? 0 : 1, m_nMaxPage));
	UpdateListPiece();
	return true;
}

bool CTestWorkshop_ListDlg::OnNextBtn(CGUIControl * _pCtrl)
{
	SET_CONTROL_TEXT(m_pDlgListDlg.get(), "PageNum", format("%02d/%02d", m_nCurPage += m_nCurPage >= m_nMaxPage ? 0 : 1, m_nMaxPage));
	UpdateListPiece();
	return true;
}

bool CTestWorkshop_ListDlg::OnBuyBtn(CGUIControl * _pCtrl)
{
	CTRShortTimeMessage::getInstance().showMessage("구매 성공!");
	return true;
}
