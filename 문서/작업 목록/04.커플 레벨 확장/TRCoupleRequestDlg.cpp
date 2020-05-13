/* ---------------------------------------------------------------
*
* Copyright 2008 by Rhaon Ent.
*
* TRCoupleRequestDlg.cpp
*
* 2008. 1. Im Cheolsu.
* 
* ---------------------------------------------------------------
*/


#include "stdafx.h"
#include "TRCoupleRequestDlg.h"
#include "NetClientManager.h"
#include "gameui/TRGoodsImageManager.h"
#include "gameui/ClientItemInfoLoader.h"
#include "gui/GUIItemImageCtrl.h"
#include "language/LanguageHeader.h"
#include "netcommon/ItemAttrTable.h"
#include "park/TRCoupleSystem.h"

CTRCoupleRequestDlg::CTRCoupleRequestDlg()
{
	m_pDlg = NULL;
	m_pUserList = NULL;
	m_pCoupleNameCtrl = NULL;
	m_pCoupleIntroCtrl = NULL;

	m_jewelBoxItemNum = 0;
	m_bMeetingDependency  = false;
	
}

CTRCoupleRequestDlg::~CTRCoupleRequestDlg()
{

}

void CTRCoupleRequestDlg::showDialog(int jewelBoxItemNum, const bool bMeetingSystem /*= false*/)
{
	closeDialog();

	string errmsg;
	m_pDlg = CTRUserInterface::loadGUI("gui\\park\\Couple_Made.gui", errmsg);

	if (NULL == m_pDlg)
	{
		_ASSERTE(false);
		return;
	}

	m_pDlg->setZOrder(-0.1f);
	m_pDlg->centerPosition();
	m_pDlg->setModalDialog(true);
	m_pDlg->setDialogListener(getCommandTargetID());
	CGUIManager::getInstance().setFocus(m_pDlg->getControlID());
	CTRUserInterface::getInstance().setGUIAnimatorPopupShow(m_pDlg);

	m_pUserList			    = (CGUIComboBoxDropList*)	m_pDlg->findControl("UserComboList");
	m_pCoupleNameCtrl		= (CGUIEditCtrl*)	m_pDlg->findControl("CoupleName");
	m_pCoupleIntroCtrl		= (CGUIEditCtrl*)	m_pDlg->findControl("CoupleInfo");

	
	if( m_pUserList ) 
	{
		vector< FriendInfo > FriendList = CNetClientManager::getInstance().getFriendList();

		for( unsigned int i = 0 ; i < FriendList.size() ; ++i)
		{
			if(FriendList[i].m_eState == eUserState_OnLine && !FriendList[i].m_bDeleted && !CNetClientManager::getInstance().getMyFamilyInfo().isFamilyMember(FriendList[i].m_strNickname))
			{
				m_pUserList->addString(FriendList[i].m_strNickname);
			}
		}	

		m_pUserList->unDropListBox();
	}

	m_jewelBoxItemNum = jewelBoxItemNum;
	m_bMeetingDependency  = bMeetingSystem;
}

void CTRCoupleRequestDlg::closeDialog()
{	
	if(m_pDlg)
	{
		CTRUserInterface::getInstance().setGUIAnimatorPopupHide(m_pDlg);
		m_pDlg = NULL;
	}

	m_toNickName = "";
	m_coupleName = "";
	m_coupleDesc = "";

	m_jewelBoxItemNum = 0;
	m_bMeetingDependency  = false;
}

void CTRCoupleRequestDlg::closeOKDialog()
{
	m_OKDlg.closeDialog();
}

bool CTRCoupleRequestDlg::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	string name;

	CGUIControl* pCtrl = ctrlID.findControl();
	if(pCtrl)
	{
		name = pCtrl->getName();
	}

	if(name == "Ok")
	{
		sendCoupleRequest();
		return true;
	}
	else if(name == "Cancle")
	{
		closeDialog();
		return true;
	}

	return false;
}

bool CTRCoupleRequestDlg::onKeyDown(WPARAM wParam)
{
	if(!isVisible()) return false;

	switch(wParam)
	{
	case VK_RETURN:
		sendCoupleRequest();
		return true;
	case VK_ESCAPE:
		closeDialog();
		return true;
	}

	return __super::onKeyDown(wParam);
}

bool CTRCoupleRequestDlg::isVisible()
{
	if( m_pDlg ) return m_pDlg->isVisible();

	return false;
}

void CTRCoupleRequestDlg::sendCoupleRequest()
{
	/// 신청할 사람 이름 체크
	if(m_pUserList)
	{
		m_pUserList->getText(m_toNickName);
	}

	if (m_toNickName.empty() )
	{
		m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_MSG_CHOICE_COUPLE));
		_ASSERTE(false);
		return;
	}

	/// 커플이름
	if(m_pCoupleNameCtrl)
	{
		m_pCoupleNameCtrl->getText(m_coupleName);
	}

	if (m_coupleName.empty() )
	{
		m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_MSG_INPUT_COUPLENAME));
		_ASSERTE(false);
		return;
	}

	if(CTRChattingManager::getInstance().isAbuseString(m_coupleName.c_str()))
	{
		m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_INVALID_TEXT_IN_COUPLE_NAME));
		_ASSERTE(false);
		return;
	}

	/// 커플 소개
	if(m_pCoupleIntroCtrl)
	{
		m_pCoupleIntroCtrl->getText(m_coupleDesc);
	}

	if(CTRChattingManager::getInstance().isAbuseString(m_coupleDesc.c_str()))
	{
		m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_INVALID_TEXT_IN_COUPLE_DESC));		
		_ASSERTE(false);
		return;
	}

	const FriendInfo * pFrendeInfo = CNetClientManager::getInstance().getFriendInfo(m_toNickName);

	if(pFrendeInfo && pFrendeInfo->m_eState != eUserState_OnLine)
	{
		m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_DISCONNETOR_USER));
		_ASSERTE(false);
		return;
	}

	CNetClientManager::getInstance().requestCoupleCheckPropose(m_coupleName, m_toNickName, m_bMeetingDependency, m_jewelBoxItemNum);
}

void CTRCoupleRequestDlg::onRecvCoupleCheckProposeInfo(eServerResult eResult, const bool bMeetingDependency)
{
	if(!isVisible()) return;

	if(eServerResult_OK_ACK == eResult) // 커플 요청이 성공이라면
	{		
		CTRCoupleSystem::getInstacne().community_requestPropose(m_toNickName, m_coupleName, m_coupleDesc, m_jewelBoxItemNum, bMeetingDependency);
		m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_COMPLETE));
		closeDialog();
	}
	else
	{
		switch(eResult)
		{
		case eServerResult_COUPLE_DUPLICATE_COUPLE_NAME_ACK:			
            // 이미 존재하는 커플명이다.
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_DUPLICATE_COUPLE_NAME));
			_ASSERTE(false);
			break;
		case eServerResult_COUPLE_INVALID_COUPLE_NAME_ACK:			
			// 사용할 수 없는 커플명이다.			
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_NOT_USE_COUPLENAME));
			_ASSERTE(false);
			break;
		case eServerResult_COUPLE_UNKOWN_USER_NAME_ACK:			
			// 내 친구 리스트에 없거나 존재하지 않는 유저다.
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_NOT_EXIST_USER));			
			break;
		case eServerResult_COUPLE_ALREADY_I_HAVE_MATE_ACK:			
			// 나는 이미 커플이다.			
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_HAVE_ALREADY_COUPLE));
			_ASSERTE(false);
			break;
		case eServerResult_COUPLE_ALREADY_HE_HAS_MATE_ACK:			
			// 대상은 이미 커플이다.		
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_DUPLICATE_USER_COUPLE));
			_ASSERTE(false);
			break;
		case eServerResult_COUPLE_ALREADY_HAS_WISHLIST_ACK:		
			// 나는 이미 커플신청 중에 있다.			
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_PROPOSE_DUPLICATE));
			_ASSERTE(false);
			break;
		case eServerResult_COUPLE_HE_HAS_WISHLIST_ACK:
			//!< 대상은 이미 커플신청 중에 있다.
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_PROPOSING_MY_FRIEND));
			break;
		case eServerResult_COUPLE_HE_IS_MY_FAMILY_ACK:
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_IN_MY_FAMILY));
			break;
		case eServerResult_COUPLE_DBFAILED_ACK:			
			// DB 실패.
			DBG_OUTPUT("DB ERROR");
			break;
		}
	}
}

/////////////////////////////////////////////////////////////

CTRCoupleSuccessDlg::CTRCoupleSuccessDlg()
{

}
CTRCoupleSuccessDlg::~CTRCoupleSuccessDlg()
{

}

void CTRCoupleSuccessDlg::showDialog(int boxItem, int ringItem)
{
	m_guiFilename = "gui\\park\\Couple_Success.gui";

	__super::showDialog("");

	CGUIDialog * pDlg = (CGUIDialog *)m_dlgID.findControl();

	if(pDlg)
	{
		CGUIItemImageCtrlSimple * pImgCtrl = NULL;

		const CItemInfoNode * pBoxIteminfo = CClientItemList::getInstance().getItemInfo(boxItem);
		if(pBoxIteminfo)
		{
			pImgCtrl = (CGUIItemImageCtrlSimple *)pDlg->findControl("ItemImg1", GUI_SUB_CONTROL_ITEM_IMAGE_CTRL);
			if(pImgCtrl)
			{
				pImgCtrl->setAttrBits(GUI_ATTR_BIT_RECEIVE_MOUSE_EVENT, false);
				pImgCtrl->setItemImage(*pBoxIteminfo);
			}
		}

		const CItemInfoNode * pRingIteminfo = CClientItemList::getInstance().getItemInfo(ringItem);

		if(pRingIteminfo)
		{
			pImgCtrl = (CGUIItemImageCtrlSimple *)pDlg->findControl("ItemImg2", GUI_SUB_CONTROL_ITEM_IMAGE_CTRL);
			if(pImgCtrl)
			{
				pImgCtrl->setAttrBits(GUI_ATTR_BIT_RECEIVE_MOUSE_EVENT, false);
				pImgCtrl->setItemImage(*pRingIteminfo);
			}		

			pImgCtrl = (CGUIItemImageCtrlSimple *)pDlg->findControl("ItemImg3", GUI_SUB_CONTROL_ITEM_IMAGE_CTRL);
			if(pImgCtrl)
			{
				pImgCtrl->setAttrBits(GUI_ATTR_BIT_RECEIVE_MOUSE_EVENT, false);
				pImgCtrl->setItemImage(*pRingIteminfo);
			}	
		}
	}

	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(boxItem);
}

////////////////////////////////////////////////////////////////////////

CTRCoupleNameChangeDlg::CTRCoupleNameChangeDlg()
{
	m_guiFilename = "gui\\park\\Couple_ChangeName.gui";
}

void CTRCoupleNameChangeDlg::onShowDialog()
{
	CGUIControl * pDlg = m_dlgID.findControl();

	if(pDlg == NULL) return;

	resetInput();	
}

void CTRCoupleNameChangeDlg::onCloseDialog()
{
	m_OKDlg.closeDialog();
}

bool CTRCoupleNameChangeDlg::checkChangeCoupleName(string coupleName)
{
	if (coupleName.empty() )
	{
		m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_MSG_INPUT_COUPLENAME));
		_ASSERTE(false);
		return false;
	}

	if(CTRChattingManager::getInstance().isAbuseString(coupleName.c_str()))
	{
		const string msgInputAgain = _STR(MSG_INPUT_AGAIN);
		const string msg = _STR(COUPLESYS_PROPOSE_ERR_NOT_USE_COUPLENAME);

		m_OKDlg.showDialog(msg + "<br>" + msgInputAgain);
		_ASSERTE(false);
		return false;
	}

	return true;
}

void CTRCoupleNameChangeDlg::resetInput()
{
	CGUIControl * pDlg = m_dlgID.findControl();

	if(pDlg == NULL) return;

	CGUIControl *pCtrl = pDlg->findControl("ChangeName");
	if(pCtrl)
	{
		pCtrl->setText("");

		CGUIManager::getInstance().setFocus(pCtrl->getControlID());
	}
}

void CTRCoupleNameChangeDlg::onRecvCoupleModifyCoupleNameResultFailed(eServerResult eResult)
{
	string msg;
	const string msgInputAgain = _STR(MSG_INPUT_AGAIN);

	switch(eResult)
	{
	case eServerResult_COUPLE_INVALID_COUPLE_NAME_ACK:
		// 사용할 수 없는 커플명이다.
		msg = _STR(COUPLESYS_PROPOSE_ERR_NOT_USE_COUPLENAME);
		m_OKDlg.showDialog(msg + "<br>" + msgInputAgain);
		_ASSERTE(false);
		break;
	case eServerResult_COUPLE_DUPLICATE_COUPLE_NAME_ACK:			
		// 이미 존재하는 커플명이다.
		msg = _STR(COUPLESYS_PROPOSE_ERR_DUPLICATE_COUPLE_NAME);
		m_OKDlg.showDialog(msg + "<br>" + msgInputAgain);
		_ASSERTE(false);
		break;
	case eServerResult_COUPLE_DBFAILED_ACK:			
		// DB 실패.
		DBG_OUTPUT("CTRCoupleSystem::onRecvCoupleCreateCoupleInfo result = DB ERROR");
		break;
	}

	resetInput();
}


void CTRCoupleNameChangeDlg::onYes()
{	
	CGUIControl * pDlg = m_dlgID.findControl();

	if(pDlg == NULL) return;

	CGUIControl *pCtrl = pDlg->findControl("ChangeName");
	if(pCtrl)
	{
		string coupleName;

		pCtrl->getText(coupleName);
		if( !coupleName.empty() )
		{				
			if(!checkChangeCoupleName(coupleName))    // 커플 이름 유효한지 체크
			{					
				resetInput();
				return ;
			}

			CNetClientManager::getInstance().requestCoupleModifyCoupleName(coupleName);
		}
	}			

//	closeDialog();
}


void CTRCoupleNameChangeDlg::onNo()
{
	closeDialog();
}

/////////////////////////////////////////////

CTRCoupleNameChangeSuccessDlg::CTRCoupleNameChangeSuccessDlg()
{

}
CTRCoupleNameChangeSuccessDlg::~CTRCoupleNameChangeSuccessDlg()
{

}

void CTRCoupleNameChangeSuccessDlg::showDialog(string message)
{
	m_guiFilename = "gui\\park\\Couple_NewName.gui";

	__super::showDialog("");

	CGUIControl * pDlg = m_dlgID.findControl();
	if(pDlg == NULL) return;


	CGUIControl *pCtrl = pDlg->findControl("CoupleName");

	if(pCtrl)
		pCtrl->setText(message);
}

/////////////////////////////////////////////

void CTRCoupleRingChangeResultDlg::showDialog(int OrgRingItemNum,int ChangeRingItemNum)
{
	// 바꿀 아이템의 반지 레벨을 가져온다. 반지의 최고레벨은 netcommondefine 에 정의 되어있다.
	int ringLevel = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(ChangeRingItemNum).m_attr[eItemAttr_Couple_Level]);

	//!< 커플레벨 기준값(10레벨) 서버세팅값으로 체크함
	int iCoupleLevel10 = atoi(CNetClientManager::getInstance().getServerSetting("CoupleLevelConditionCheck", "10").c_str());

	if(ringLevel == iCoupleLevel10)
	{
		_showAddItemChangeRingDialog(OrgRingItemNum,ChangeRingItemNum);		
	}
	else
	{
		if(ringLevel > iCoupleLevel10)
		{
			_updateRingItem(OrgRingItemNum);
			_updateRingItem(ChangeRingItemNum);
		}
		_showChangeRingDialog(ChangeRingItemNum);       
	}
}

void CTRCoupleRingChangeResultDlg::_showChangeRingDialog(int ringItemNum)
{
	m_guiFilename = "gui\\park\\Couple_ChangeRing.gui";

	__super::showDialog("");

	CGUIDialog * pDlg = (CGUIDialog *)m_dlgID.findControl();

	if(pDlg)
	{
		CGUIItemImageCtrl *pItemImgCtrl = static_cast<CGUIItemImageCtrl *>(pDlg->findControl("ItemImgBase", GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
		if(pItemImgCtrl) pItemImgCtrl->setItemImage(ringItemNum);

		CGUIControl *pCtrl = pDlg->findControl("ItemName");
		if(pCtrl)
		{
			const CItemInfoNode * pIteminfo = CClientItemList::getInstance().getItemInfo(ringItemNum);

			if(pIteminfo)
				pCtrl->setText(pIteminfo->m_name);
		}
	}
}

void CTRCoupleRingChangeResultDlg::_showAddItemChangeRingDialog(int OrgRingItemNum,int ChangeRingItemNum)
{
	const CItemInfoNode * pCurRingIteminfo = CClientItemList::getInstance().getItemInfo(OrgRingItemNum);

	const CItemInfoNode * pChangeRingIteminfo = CClientItemList::getInstance().getItemInfo(ChangeRingItemNum);
	
	const int iSpecialItemNum = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(ChangeRingItemNum).m_attr[eltemAttr_JewelBox_AdditionItemDescNum]);
	const CItemInfoNode * pSpecialIteminfo = CClientItemList::getInstance().getItemInfo(iSpecialItemNum);

	const int iOrgSpecialItemNum = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(OrgRingItemNum).m_attr[eltemAttr_JewelBox_AdditionItemDescNum]);
	const CItemInfoNode * pOrgSpecialIteminfo = CClientItemList::getInstance().getItemInfo(iOrgSpecialItemNum);

	string msg = "";

	if(pChangeRingIteminfo == NULL || pCurRingIteminfo == NULL || pSpecialIteminfo == NULL)
	{
		DBG_OUTPUT("CTRCoupleRingChangeResultDlg::_showAddItemChangeRingDialog pChangeRingIteminfo(%d), pCurRingIteminfo(%d), pSpecialIteminfo(%d)", pChangeRingIteminfo, pCurRingIteminfo, pSpecialIteminfo);
		return;
	}
	if (pSpecialIteminfo != NULL)
	{
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(pSpecialIteminfo->m_iUniqueNumber);
	}
	if (pOrgSpecialIteminfo != NULL)
	{
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(pOrgSpecialIteminfo->m_iUniqueNumber);
	}
	
	msg = format(_STR(COUPLESYS_CHANGE_MSG_365DAY_COUPLE_RING), pCurRingIteminfo->m_name.c_str(), pChangeRingIteminfo->m_name.c_str());
	m_guiFilename = "gui\\park\\Couple_SpecialChange.gui";	

	__super::showDialog(msg, FALSE);

	CGUIDialog * pDlg = (CGUIDialog *)m_dlgID.findControl();

	if(pDlg)
	{
		// 교체된 반지 이미지 설정
		CGUIItemImageCtrl *pCtrl = static_cast<CGUIItemImageCtrl *>(pDlg->findControl("ItemImg2", GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
		if(pCtrl)
		{
			pCtrl->setAttrBits(GUI_ATTR_BIT_RECEIVE_MOUSE_EVENT, false);
			pCtrl->setItemImage(ChangeRingItemNum);
		}

		// 내가 가지고 있는 반지 이미지 설정
		pCtrl = static_cast<CGUIItemImageCtrl *>(pDlg->findControl("ItemImg1", GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
		if(pCtrl) pCtrl->setItemImage(OrgRingItemNum);

		// 특별 추가 되는 아이템 이미지 설정
		pCtrl = static_cast<CGUIItemImageCtrl *>(pDlg->findControl("ItemImg3", GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
		if(pCtrl) pCtrl->setItemImage(pSpecialIteminfo->m_iUniqueNumber);
	}
}

void CTRCoupleRingChangeResultDlg::_updateRingItem(int ringItemNum)
{
	const int nSpecialItemNum = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(ringItemNum).m_attr[eltemAttr_JewelBox_AdditionItemDescNum]);
	const CItemInfoNode * pCurSpecialIteminfo = CClientItemList::getInstance().getItemInfo(nSpecialItemNum);
	if(pCurSpecialIteminfo)
	{
		if(pCurSpecialIteminfo->isSetItem())
		{
			std::vector<int> itemList;
			itemList.reserve(16);

			for(auto& i : pCurSpecialIteminfo->m_vecHaveSetItem)
			{
				const CItemInfoNode * pParent = CClientItemList::getInstance().getItemInfo(i->m_iUniqueNumber);
				itemList.push_back(pParent->m_iUniqueNumber);
			}

			if(!itemList.empty())
			{
				CNetClientManager::getInstance().requestCharacterAvatarItemByItemNumList(itemList);
			}
		}
		else
		{
			CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(pCurSpecialIteminfo->m_iUniqueNumber);
		}
	}
}
