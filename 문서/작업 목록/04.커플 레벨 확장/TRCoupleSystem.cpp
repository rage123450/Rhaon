/* ---------------------------------------------------------------
*
* Copyright 2008 by Rhaon Ent.
*
* TRCoupleSystem.cpp
*
* 2008. 2. Im Cheolsu.
* 
* ---------------------------------------------------------------
*/


#include "stdafx.h"
#include "TRCoupleSystem.h"
#include "game/TRNetPlayManager.h"
#include "gameui/TRMyKeepGoodsList.h"
#include "gameui/TRShopDlg.h"
#include "gameui/ServerTime.h"
#include "gameui/TRChallengeSubjectManager.h"
#include "gameui/TRShopGiftDialog.h"
#include "gameui/TRShortTimeMessage.h"
#include "language/LanguageHeader.h"
#include "netcommon/ItemAttrTable.h"
#include "park/TRGameParkUI.h"

#ifdef _SHOP_RENEWAL_
#include "gameui/Shop/TRShopManager.h"
#endif

// 정렬 클래스
class CSortItemInfoRequireDay
{
public:
	bool operator()(const int s1, const int s2 ) const
	{
		int requirementDay1 = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(s1).m_attr[eltemAttr_Requirement_Couple_Days]);
		int requirementDay2 = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(s2).m_attr[eltemAttr_Requirement_Couple_Days]);
		return requirementDay1 >= requirementDay2;
	}
};


////////////////////////////////
class CSortItemNodeRequireLevel
{
public:
	bool operator()(const CItemInfoNode *s1, const CItemInfoNode * s2 ) const
	{
		int requirementLevel1 = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(s1->m_iUniqueNumber).m_attr[eItemAttr_Couple_Level]);
		int requirementLevel2 = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(s2->m_iUniqueNumber).m_attr[eItemAttr_Couple_Level]);
		return requirementLevel1 <= requirementLevel2;
	}
};

class CSortItemInfoCoupleLevel
{
public:
	bool operator()(const int s1, const int s2 ) const
	{
		int coupleLevel1 = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(s1).m_attr[eItemAttr_Couple_Level]);
		int coupleLevel2 = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(s2).m_attr[eItemAttr_Couple_Level]);
		return coupleLevel1 <= coupleLevel2;
	}
};



CTRCoupleSystem::CTRCoupleSystem()
{
	m_fromNickname = "";

	m_bCurProposeSend = false;
	m_bCurProposeRecv = false;
	m_bCoupleBreak = false;
	m_bCoupleRingChangeRecv = false;
	m_bCoupleNameChangeRecv = false;

	m_bProposeResponse = false;
	m_eReason = eCoupleProposeReject_NONE;

	m_bBuyJewelBoxByCoupleSystem = false;
	m_iCoupleRingNum = 0;
	m_iJewelBoxNum = 0;
	m_iOrgCoupleRingNum = 0;
	m_bChangeCoupleRing = true;

	m_bChangeMyAvatar = false;

	m_bRecvLimit = false;
	m_bCoupleRingnumDirty = false;

	vector<int> jewelBoxList = CClientItemList::getInstance().getItemInfo(eCharacterKind_NONE, eFuncItemPosition_JEWEL_BOX);
	sort(jewelBoxList.begin(), jewelBoxList.end(), CSortItemInfoCoupleLevel());

	int backRequirementLevel = 0;
	for(size_t i = 0 ; i < jewelBoxList.size() ; i++)
	{
		int requirementLevel = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(jewelBoxList[i]).m_attr[eItemAttr_Couple_Level]);

		if(i == 0)
		{
			backRequirementLevel = requirementLevel;
			continue;
		}

		m_mapRingDayGradeTable[backRequirementLevel] = requirementLevel;
		backRequirementLevel = requirementLevel;
	}

	//!< 커플레벨 기준값(최고레벨) 서버세팅값으로 체크함
	int iCoupleLevelMax = atoi(CNetClientManager::getInstance().getServerSetting("CoupleMaxLevel", "20").c_str());

	m_mapRingDayGradeTable[backRequirementLevel] = iCoupleLevelMax+1;   // 마지막 등급 커플링일은 다음 단계가 없으므로 큰값을 넣는다.

	m_bCurWedding = false;
}

CTRCoupleSystem::~CTRCoupleSystem()
{

}

CTRCoupleSystem & CTRCoupleSystem::getInstacne()
{
	static CTRCoupleSystem inst;

	return inst;
}

void CTRCoupleSystem::showProposeDlg()
{

}

void CTRCoupleSystem::closeCoupleSysUI()
{
	m_proposeDlg.closeDialog();
	m_coupleRingChangeResultDlg.closeDialog();
	m_coupleNameChangeDlg.closeDialog();
	m_coupleNameChangeSuccDlg.closeDialog();
	m_yesNoDlg.closeDialog();	
	m_coupleSuccDlg.closeDialog();
	m_OKDlg.closeDialog();
	m_resultCard.closeDialog();
}

void CTRCoupleSystem::closeCoupleSysParkUI()
{
	m_proposeDlg.closeDialog();
}

void CTRCoupleSystem::onResetCoupleInfo()
{
	m_coupleName = "";
	m_coupleDes = "";
	m_fromNickname = "";	
	m_coupleDivination = "";

	m_bCurProposeRecv = false;
	m_bCurProposeSend = false;
	m_bCoupleBreak = false;
	m_bCoupleRingChangeRecv = false;
	m_bCoupleNameChangeRecv = false;
	m_bCoupleDescChangeRecv = false;
	m_bCoupleDivinationRecv = false;

	m_bProposeResponse = false;
	m_eReason = eCoupleProposeReject_NONE;

	m_iCoupleRingNum = 0;
	m_iJewelBoxNum = 0;
	m_iOrgCoupleRingNum = 0;
	m_bChangeCoupleRing = true;
	m_bRecvLimit = false;
}

void CTRCoupleSystem::checkCoupleMsg()
{
	if(m_bCurProposeRecv)  // 현재 커플 신청 중이라면(신청을 받음)
	{
		m_yesNoDlg.showDialog(format(_STR(COUPLESYS_PROPOSE_ASK_COUPLE_OK),m_fromNickname.c_str(), m_coupleName.c_str()) , this, &CTRCoupleSystem::onYesCoupleConsent, &CTRCoupleSystem::onNoCoupleConsent, "park\\Couple_Agree.gui", -3.f, false);
	}
	else
	{
		// onResetCoupleInfo 각 상황마다 초기화 시점에 따라  if/else 나눔
		if(m_bCurProposeSend)
		{
			// 커플이 성사되었다고 받음.
			showCoupleProposeResponse(m_bProposeResponse, m_eReason);	
		}
		else if(m_bCoupleBreak)
		{
			// 커플이 끊어졌다고 받음.
			m_OKDlg.showDialog(format(_STR(COUPLESYS_CUT_MSG_CUT_COUPLE_BY_MY_COUPLE), m_fromNickname.c_str()));		
		}
		else if(m_bCoupleRingChangeRecv)
		{
			// 커플이 교체되었다고 받음.
			m_coupleRingChangeResultDlg.showDialog(m_iOrgCoupleRingNum,m_iCoupleRingNum);
		}
		else if(m_bCoupleNameChangeRecv)
		{
			// 커플 이름이 변경
			m_coupleNameChangeSuccDlg.showDialog(m_coupleName);			
		}
		else if(m_bCoupleDescChangeRecv)
		{
			// 커플 설명이 변경
			string msg = _STR(MSG_MODIFY_COUPLE_DESC);
			m_OKDlg.showDialog("<normal>" + msg + "</normal>");
		}
		else if(m_bCoupleDivinationRecv)
		{
			// 나의 커플이 커플 점을 봤다
			m_resultCard.showDialog(m_coupleDivination, m_appliedExtraAbility, "gui\\park\\FortuneShop_Result_Couple.gui");
		}

		onResetCoupleInfo();  // 게임중에 받은 커플정보를 초기화
	}	
}

bool CTRCoupleSystem::checkNextJewelBox(int &jewelBoxItemNum)
{
	vector<int> destList;

	destList = CClientItemList::getInstance().getItemInfo(eCharacterKind_NONE, eFuncItemPosition_JEWEL_BOX);

	int nowCoupleLevel = getMyCoupleLevel();

	for(vector<int>::iterator iter = destList.begin() ; iter < destList.end() ; ++iter)
	{
		// 소유하고 있는 보석함들의 레벨을 받아온다.
		int requirementLevel = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(*iter).m_attr[eItemAttr_Couple_Level]);

		// 보석함의 레벨이 다음 교체해야할 레벨과 같다면
		if(requirementLevel == m_mapRingDayGradeTable[nowCoupleLevel])
		{
			jewelBoxItemNum = *iter;
			return true;
		}
	}
	return false;
}

bool CTRCoupleSystem::checkKeepNextJewelBox(int &jewelBoxItemNum)
{
	vector<NetItemInfo> destList;

	CKeepItemList::getInstance().getItemList(eCharacterKind_NONE, eFuncItemPosition_JEWEL_BOX, destList);

	int nowCoupleLevel = getMyCoupleLevel();

	for(vector<NetItemInfo>::iterator iter = destList.begin() ; iter < destList.end() ; ++iter)
	{
		// 소유하고 있는 보석함들의 레벨을 받아온다.
		int requirementLevel = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum((*iter).m_iItemDescNum).m_attr[eItemAttr_Couple_Level]);

		// 보석함의 레벨이 다음 교체해야할 레벨과 같다면
		if(requirementLevel == m_mapRingDayGradeTable[nowCoupleLevel])
		{
			jewelBoxItemNum = (*iter).m_iItemDescNum;
			return true;
		}
	}
	return false;
}



bool CTRCoupleSystem::checkRingRequirementDay(CoupleInfo coupleInfo, int &nextLevel)
{
	nextLevel = getNextChangeCoupleLevel(coupleInfo.coupleRingInfo.coupleRingLevel);

	time_type requireRing = coupleInfo.coupleRingInfo.iRequireCoupleDays * 24 * 60;
	time_type myExpRingMinuteTime = checkMyExpRingMinuteTime(coupleInfo);

	return myExpRingMinuteTime >= requireRing;
}

bool CTRCoupleSystem::checkRingRequirementDay(CoupleInfo coupleInfo)
{
	time_type requireRing = coupleInfo.coupleRingInfo.iRequireCoupleDays * 24 * 60;
	time_type myExpRingMinuteTime = checkMyExpRingMinuteTime(coupleInfo);

	return myExpRingMinuteTime >= requireRing + 1;
}

time_type CTRCoupleSystem::checkMyExpRingMinuteTime(CoupleInfo coupleInfo)
{
	time_type ExpminuteTime = 0;
	if(coupleInfo.iCoupleNum > 0)
	{
		time_type currentTime = CServerTime::getInstance().getCurrentTime();
		time_type ringChangedTime = coupleInfo.tRingChangedTime;

		int minuteCountConstant = 1000 * 60;
		// 셋팅된 경험치 비율로 경험치를 시간으로 환산

		float TimeDecreaseExp = (float)atoi(CNetClientManager::getInstance().getServerSetting("coupleLevelUpTimeDecreaseExp", "100").c_str());

		double coupleExp = ((double)coupleInfo.iAccumulateExp / TimeDecreaseExp) * 60.f;

		ExpminuteTime = currentTime/minuteCountConstant - ringChangedTime/minuteCountConstant + (__int64)coupleExp;
	}

	return ExpminuteTime;
}

bool CTRCoupleSystem::checkCoupleChangeNotify()
{
	CoupleInfo myCoupleInfo = CNetClientManager::getInstance().getMyCoupleInfo();
	int coupleNum = myCoupleInfo.iCoupleNum;

	if(coupleNum > 0)
	{
		int myCoupleDay = getMyCoupleDay();
		int myRingDay = myCoupleInfo.coupleRingInfo.iRequireCoupleDays;

		if(checkRingRequirementDay(myCoupleInfo))
		{
			int iCoupleLevelMax = atoi(CNetClientManager::getInstance().getServerSetting("CoupleMaxLevel", "15").c_str());
			if (myCoupleInfo.coupleRingInfo.coupleRingLevel < iCoupleLevelMax)
			{
				m_OKDlg.showDialog(_STR(COUPLESYS_CHANGE_MSG_CAN_CHANGE_RING_UPGRADE));
				return true;
			}
		}
	}
	return false;
}

bool CTRCoupleSystem::checkAbleChangeCoupleRing(int changeCoupleLevel)
{
	int nowCoupleRingLevel = CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.coupleRingLevel;

	map<int, int>::iterator itor = m_mapRingDayGradeTable.find(nowCoupleRingLevel);

	if(m_mapRingDayGradeTable.end() != itor)
		return m_mapRingDayGradeTable[nowCoupleRingLevel] == changeCoupleLevel;

	return false;
}

int CTRCoupleSystem::getNextChangeCoupleLevel(int nowcoupleRingLevel)
{
	map<int, int>::iterator itor = m_mapRingDayGradeTable.find(nowcoupleRingLevel);

	if(m_mapRingDayGradeTable.end() != itor)
		return m_mapRingDayGradeTable[nowcoupleRingLevel];

	return 0;
}

void CTRCoupleSystem::checkNeedUpdate()
{
	if (m_bNeedUpdate)
	{
		m_bNeedUpdate = false;
		CNetClientManager::getInstance().requestCoupleUpdateCoupleInfo();
	}
}

void CTRCoupleSystem::updateRingItem(int ringItemNum)
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

void CTRCoupleSystem::onLoginProcess()
{
	// 로그인 했을 때 커플 링 교체시기임을 알림.
	checkCoupleChangeNotify();

	// 알림 메세지 처리

}

int CTRCoupleSystem::getMyCoupleDay()
{
	int myCoupleDay = 0;

	if(CNetClientManager::getInstance().getMyCoupleInfo().iCoupleNum > 0)
	{
		// 커플 일수 체크
		time_type currentTime = CServerTime::getInstance().getCurrentTime();
		time_type coupleCreateTime = CNetClientManager::getInstance().getMyCoupleInfo().tCoupleCreateTime;

		int dayCountConstant = 1000 * 60 * 60 * 24;

		time_type day = currentTime/dayCountConstant - coupleCreateTime/dayCountConstant;		

		myCoupleDay = (int)(day + 1);      // 날짜 생성		
	}

	return myCoupleDay;
}

// 나의 커플Level를 얻는다.(커플이 아니라면 0을 얻는다.)
int CTRCoupleSystem::getMyCoupleLevel()
{
	int myCoupleLevel = 0;

	if(isHaveCouple())
	{
		myCoupleLevel = CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.coupleRingLevel;
	}

	return myCoupleLevel;
}


void CTRCoupleSystem::onYesCoupleConsent()
{	
	CNetClientManager::getInstance().requestCoupleCreateCouple(m_coupleName, m_fromNickname, m_coupleDes, m_iJewelBoxNum, m_bMeetingDependency);
}

void CTRCoupleSystem::onNoCoupleConsent()
{
	// 커플 정보를 초기화를 한다.
	CNetClientManager::getInstance().requestCoupleInitRecvProposeInfo(m_fromNickname);	
}

void CTRCoupleSystem::showCoupleProposeResponse(bool bOK, eCoupleProposeReject eReason)
{
	m_proposeDlg.closeOKDialog();

	if(bOK)
	{
		m_coupleSuccDlg.showDialog(m_iJewelBoxNum, m_iCoupleRingNum);
		CAudioManager::getInstance().playAudioEffectByFileName("sound\\redshoes.wav");
	}
	else
	{
		switch(eReason)
		{
		case eCoupleProposeReject_DISAGREE:
			//상대방이 거절했습니다.
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_MSG_REFUSAL_CANCEL));
			break;
		case eCoupleProposeReject_LOGOUT:
			//상대방이 로그아웃했습니다. 자동 거절입니다.
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_MSG_LOGOUT_CANCEL));
			break;
		case eCoupleProposeReject_PROPOSE_STATE:
			break;
		}
		_ASSERTE(false);		
	}
}

void CTRCoupleSystem::onProcessMeLogOff()
{
	if(m_bCurProposeRecv && CNetClientManager::getInstance().isConnectedToServerTCP() == true)
	{
		CNetClientManager::getInstance().community_responsePropose(m_fromNickname, false, eCoupleProposeReject_LOGOUT, -1, 0);
		onResetCoupleInfo();
	}
}

bool CTRCoupleSystem::_checkCouplePropose(int & iBuyItemNum)
{
	eCoupleType eType = CNetClientManager::getInstance().getMyCoupleInfo().coupleType;

	if(eType != eCoupleType_None)
	{
		m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_HAVE_ALREADY_COUPLE));
		return false;
	}

	vector<NetItemInfo> destList;

	CKeepItemList::getInstance().getItemList(eCharacterKind_NONE, eFuncItemPosition_JEWEL_BOX, destList);

	int requirementDay = 10000;
	iBuyItemNum = 0;

	for(size_t i = 0 ; i < destList.size() ; i++)
	{
		int day = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum((int)destList[i].m_iItemDescNum).m_attr[eltemAttr_Requirement_Couple_Days]);
		if(requirementDay > day)
		{
			requirementDay = day;
			iBuyItemNum = (int)destList[i].m_iItemDescNum;
		}
	}	

	if(destList.size() == 0 || requirementDay > 0)
	{
		m_bChangeCoupleRing = false;
		m_yesNoDlg.showDialog(_STR(COUPLESYS_PROPOSE_BUY_JEWELBOX), this, &CTRCoupleSystem::showBuyDialogJewelBoxItem, NULL);
		return false;
	}

	return true;
}

void CTRCoupleSystem::onReadyCouplePropose()
{
	int iBuyItemNum = 0;
	if(_checkCouplePropose(iBuyItemNum))
	{
		m_proposeDlg.showDialog(iBuyItemNum);
	}
}

void CTRCoupleSystem::onReadyCouplePropose_Meeting()
{
	int iBuyItemNum = 0;
	if(_checkCouplePropose(iBuyItemNum))
	{
		// 미팅시스템 사용해서 프로포즈 할 경우 일경우 
		m_proposeDlg.showDialog(iBuyItemNum, true);
	}
}

void CTRCoupleSystem::onChangeCoupleRingYesNo(int coupleLevel)
{
	int jewelBoxItemNum;

	if(checkNextJewelBox(jewelBoxItemNum))
	{
		const CItemInfoNode *nextJewelBox = CClientItemList::getInstance().getItemInfo(jewelBoxItemNum);
		// 교체할 반지가 다음 차례의 보석상자가 아닐 경우
		m_yesNoDlg.showDialog(format(_STR(COUPLESYS_CHANGE_MENT_NEED_JEWELBOX), nextJewelBox->m_name.c_str()), this, &CTRCoupleSystem::onChangeCoupleRing, NULL);
	}
	else
		m_OKDlg.showDialog(_STR(COUPLESYS_ERR_NOT_FIND_APPLY_JEWELBOX));
}

void CTRCoupleSystem::onChangeCoupleRing()
{
	int nextLevel = 0;

	CoupleInfo myCoupleInfo = CNetClientManager::getInstance().getMyCoupleInfo();

	if(!(myCoupleInfo.iCoupleNum > 0)) return;

	if(!CTRCoupleSystem::getInstacne().checkRingRequirementDay(myCoupleInfo, nextLevel))
	{
		// 착용 하고 있는 반지가 업그레이드가 가능하지 않을때
		m_OKDlg.showDialog(_STR(COUPLESYS_NOT_LEVELUP_STATE));
	}
	else
	{
		int KeepNextJewelBoxItemNum;

		if(getMyCoupleLevel() <= 0)
		{
			return;
		}
		else if(checkKeepNextJewelBox(KeepNextJewelBoxItemNum))
		{
			m_iCoupleRingNum =  myCoupleInfo.coupleRingInfo.iCoupleRingNum;	//< 레벨 업 요청 전 현재 커플링 번호를 기억해둔다.
			CNetClientManager::getInstance().requestCoupleChangeCoupleRing(KeepNextJewelBoxItemNum);
		}
		else
		{
			m_bChangeCoupleRing = true;
			m_yesNoDlg.showDialog(_STR(COUPLESYS_CHANGE_MENT_BUY_JEWELBOX), this, &CTRCoupleSystem::showBuyDialogJewelBoxItem, NULL);
		}
	}
}

void CTRCoupleSystem::showChangeCoupleNameDlg()
{
	if(isHaveCouple())
		m_coupleNameChangeDlg.showDialog("");
	else
		m_OKDlg.showDialog(_STR(COUPLESYS_NAME_CHANGE_ERR_USE_ITEM));
}

bool CTRCoupleSystem::isHaveCouple()
{
	if(CNetClientManager::getInstance().getMyCoupleInfo().iCoupleNum > 0)
		return true;

	return false;
}

void CTRCoupleSystem::onChangeCoupleName()
{
	vector<NetItemInfo> destList;

	CKeepItemList::getInstance().getItemList(eCharacterKind_NONE, eFuncItemPosition_CHANGE_COUPLE_NAME_ITEM, destList);

	if(destList.size() == 0)
	{
		m_yesNoDlg.showDialog(_STR(COUPLESYS_NAME_CHANGE_ASK_BUY_ITEM), this, &CTRCoupleSystem::showBuyDialogCoupleNameChangeItem, NULL);		
	}
	else
	{
		showChangeCoupleNameDlg();
	}        
}

void CTRCoupleSystem::onRemoveCoupleRing()
{
	m_yesNoDlg.showDialog(_STR(COUPLESYS_CUT_ASK_CUT_COUPLE), this, &CTRCoupleSystem::requestCoupleRemoveCouple, NULL);	
}

void CTRCoupleSystem::onGiftToMyCouple()
{
	m_yesNoDlg.showDialog(_STR(COUPLESYS_GIFT_ASK_SEND_TO_MY_COUPLE), this, &CTRCoupleSystem::showGiftDialogSendGiftItem, NULL);
}

void CTRCoupleSystem::requestCoupleRemoveCouple()
{
	CNetClientManager::getInstance().requestCoupleRemoveCouple();
}

void CTRCoupleSystem::showBuyDialogCoupleNameChangeItem()
{
	vector<int> coupleNameChangeItemList = CClientItemList::getInstance().getItemInfo(eCharacterKind_NONE, eFuncItemPosition_CHANGE_COUPLE_NAME_ITEM);

	if(coupleNameChangeItemList.size() == 0)
		return;
	
	vector<const CItemInfoNode*> buyitemList;

	buyitemList.push_back(CClientItemList::getInstance().getItemInfo(coupleNameChangeItemList[0]));
#ifdef _SHOP_RENEWAL_
	if ("true" == CNetClientManager::getInstance().getServerSetting("UseShopRenewal", "true"))
	{
		CTRShopManager::getInstance().CreateBuyUI(buyitemList);
	}
	else
#endif
	{
		CTRShopDlg::getInstance().showBuyAllDialog(buyitemList);
		CTRShopDlg::getInstance().setVisibleMoneyFillingBtn(false);
	}
}

// 공원에서 커플에게 선물한다.
void CTRCoupleSystem::showGiftDialogSendGiftItem()
{
	// 스트링테이블에서 아이템번호를 읽어 온다.
	string strGiftItemNum = _STR(COUPLESYS_GIFT_EVENT_ITEM);

	const int iGiftItemNum = atoi(strGiftItemNum.c_str());
	const CItemInfoNode * pIteminfo = CClientItemList::getInstance().getItemInfo(iGiftItemNum);	

	if(pIteminfo)
	{
		string myCoupleMateName = CNetClientManager::getInstance().getMyCoupleInfo().strMateNickname;

		CTRShopGiftDialog::getInstance().showDialog(pIteminfo, myCoupleMateName);
	}
}

void CTRCoupleSystem::showBuyDialogJewelBoxItem()
{
	// 보석상자가 없다면 구매창을 띄운다.
	vector<int> jewelBoxList = CClientItemList::getInstance().getItemInfo(eCharacterKind_NONE, eFuncItemPosition_JEWEL_BOX);
	int myCoupleLevel = getMyCoupleLevel();

	vector<const CItemInfoNode*> buyitemList;

	vector<int>::reverse_iterator iter;
	for(iter = jewelBoxList.rbegin() ; iter < jewelBoxList.rend() ; iter++)
	{
		int requirementLevel = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(*iter).m_attr[eItemAttr_Couple_Level]);

		const CItemInfoNode * pItemInfo = CClientItemList::getInstance().getItemInfo(*iter);

		if(pItemInfo)
		{
			if(requirementLevel > myCoupleLevel)   // 내가 가진 커플링 레벨보다 커야함
			{
				buyitemList.push_back(pItemInfo);
			}
		}		
	}

	// 우선 구입해야할 보석상자의 속성 날짜에 대한 오름차순으로 정렬
	sort(buyitemList.begin(), buyitemList.end(), CSortItemNodeRequireLevel());

	if(buyitemList.size())
	{
		m_bBuyJewelBoxByCoupleSystem = true;
#ifdef _SHOP_RENEWAL_
		if ("true" == CNetClientManager::getInstance().getServerSetting("UseShopRenewal", "true"))
		{
			CTRShopManager::getInstance().CreateBuyUI(buyitemList);
		}
		else
#endif
		{
			CTRShopDlg::getInstance().showBuyAllDialog(buyitemList);
			CTRShopDlg::getInstance().setVisibleMoneyFillingBtn(false);
		}
		m_bBuyJewelBoxByCoupleSystem = false;
	}
}

// 사용하지 않아 주석 처리 됨
void CTRCoupleSystem::checkChallengeSubjeck(int ringNum)
{
	int day = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(ringNum).m_attr[eltemAttr_Requirement_Couple_Days]);

	DBG_OUTPUT("CTRCoupleSystem::checkChallengeSubjeck day = %d ", day);

	int coupleGrade = 1;

	for( map<int, int>::iterator itor = m_mapRingDayGradeTable.begin();itor != m_mapRingDayGradeTable.end() ; ++itor,++coupleGrade)
	{
		if(day == itor->second)
		{
			int iChallengeSubjectAchievePoint = 0;
			switch(coupleGrade)
			{
			case COUPLE_RING_GRADE_SECOND :
			case COUPLE_RING_GRADE_THIRD :
			case COUPLE_RING_GRADE_FOURTH :
			case COUPLE_RING_GRADE_FIFTH :
			case COUPLE_RING_GRADE_SIXTH :
			case COUPLE_RING_GRADE_SEVEN :
		//	CTRChallengeSubjectManager::getInstance().updateMyChallengeInfo(CHALLENGE_COUPLE_DAY,coupleGrade - 1);
				break;
			default:
				return;
			}
		}
	}	
}

bool CTRCoupleSystem::checkCoupleRecvNoLimit()
{
	GAME_STATE iGameState = CTRNetPlayManager::getInstance().getGameState();

	if(iGameState == GAME_STATE_NO_GAME                   // 게임중이 아니여야함
		&& !m_bRecvLimit)                                 // 제한시점이 아니여야함
		return true;

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CTRCoupleSystem::onRecvCoupleCreateCoupleInfo(eServerResult eResult, const int iCoupleNum, const int iCoupleRingNum)
{	
	// 서버로 커플 생성의 결과를 받았다.
	if(eResult == eServerResult_OK_ACK)
	{
		CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_JEWEL_BOX);
		m_bCoupleRingnumDirty = true;

		// 서버에 커플 정보 갱신
		CNetClientManager::getInstance().requestCoupleUpdateCoupleInfo();

		// 성공이라면 상대에서 커플맺자고 보낸다.
		CNetClientManager::getInstance().community_responsePropose(m_fromNickname, true, eCoupleProposeReject_NONE, iCoupleNum, iCoupleRingNum);

		CAudioManager::getInstance().playAudioEffectByFileName("sound\\redshoes.wav");

		m_coupleSuccDlg.showDialog(m_iJewelBoxNum, iCoupleRingNum);

		// 커플 신청 중이였다면 닫는다.
		m_proposeDlg.closeDialog();
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
		case eServerResult_COUPLE_HE_IS_MY_FAMILY_ACK:
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_IN_MY_FAMILY));
			break;
		case eServerResult_COUPLE_DBFAILED_ACK:			
			// DB 실패.
			DBG_OUTPUT("CTRCoupleSystem::onRecvCoupleCreateCoupleInfo result = DB ERROR");
			break;
		}
	}

	onResetCoupleInfo();
}

/// 프로포즈 정보를 체크한다.
void CTRCoupleSystem::onRecvCoupleCheckProposeInfo(eServerResult eResult, const bool bMeetingDependency)
{
	m_proposeDlg.onRecvCoupleCheckProposeInfo(eResult, bMeetingDependency);
}

void CTRCoupleSystem::onRecvCoupleInitRecvProposeInfoOK()
{
	// 거절 성공
	CNetClientManager::getInstance().community_responsePropose(m_fromNickname, false, eCoupleProposeReject_DISAGREE, -1, 0);
	onResetCoupleInfo();
}

void CTRCoupleSystem::onRecvCoupleChangeCoupleRingOK(const CoupleInfo & OrgCoupleInfo ,const CoupleInfo & ChangeCoupleInfo)
{
	CNetClientManager & rNetClientMgr = CNetClientManager::getInstance();
	int iNewCoupleRingNum = ChangeCoupleInfo.coupleRingInfo.iCoupleRingNum;
	rNetClientMgr.requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_JEWEL_BOX);

	// 서버에 커플 정보 갱신
	rNetClientMgr.requestCoupleUpdateCoupleInfo();

	string myCoupleMateName = rNetClientMgr.getMyCoupleInfo().strMateNickname;

	// 내 복장을 갱신
	rNetClientMgr.requestMyCharacter();
	m_bChangeMyAvatar     = true;
	m_bCoupleRingnumDirty = true;

	// 교체되었음을 알린다.
	m_coupleRingChangeResultDlg.showDialog(OrgCoupleInfo.coupleRingInfo.iCoupleRingNum,ChangeCoupleInfo.coupleRingInfo.iCoupleRingNum);

	// 커플링 교체 도전미션 체크
	//checkChallengeSubjeck(iCoupleRingNum);

	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(OrgCoupleInfo.coupleRingInfo.iCoupleRingNum);
	rNetClientMgr.community_sendCoupleRingChange(myCoupleMateName, iNewCoupleRingNum);
}

void CTRCoupleSystem::onRecvCoupleChangeCoupleRingFailed(eCoupleChangeCoupleRing failedReason)
{
	string message;
	switch(failedReason)
	{
	case eCoupleChangeCoupleRing_INCORRENT_CLIENT_TIME:
		message = _STR(FAILED_RETRY_AFTER_MINUTE);
		break;
	default:
		return;
	}
	
	CTRShortTimeMessage::getInstance().showMessage(message);
}

void CTRCoupleSystem::onRecvCoupleRemoveCoupleInfo(std::string strMateName)
{
	CNetClientManager & rNetClientMgr = CNetClientManager::getInstance();

	// 상대에게 끊어졌다고 알린다.
	rNetClientMgr.community_sendCoupleSayGoodbye(strMateName);

	rNetClientMgr.requestCharacterAvatarItemByItemNum(rNetClientMgr.getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
	
	updateRingItem(rNetClientMgr.getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);

	// 서버에 커플 정보 갱신
	rNetClientMgr.requestCoupleUpdateCoupleInfo();

	// 서버에 패밀리 정보 갱신
	rNetClientMgr.requestFamilyInfo(rNetClientMgr.getMyNickname(), false);

	m_bCoupleRingnumDirty = true;

	// 내 복장을 갱신
	rNetClientMgr.requestMyCharacter();
	m_bChangeMyAvatar = true;
	
	m_OKDlg.showDialog(_STR(COUPLESYS_CUT_MSG_CUT_COUPLE));	
}

//! 나의 커플 정보를 갱신 받았다.
void CTRCoupleSystem::onRecvCoupleUpdateCoupleInfo(const CoupleInfo & conpleInfo)
{
	if(m_bCoupleRingnumDirty)
	{
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(conpleInfo.coupleRingInfo.iCoupleRingNum);
		m_bCoupleRingnumDirty = false;
	}
}

void CTRCoupleSystem::onRecvAvatarInfo(const AdvancedAvatarInfo & advancedAvatarInfo)
{
	if(m_bChangeMyAvatar)
	{
		if(CNetClientManager::getInstance().requestSaveCharacterSetting(advancedAvatarInfo))  // 방사람들에 내 아비타 정보를 알린다.
		{
			if(CTRGameParkUI::getInstance().isActive())
			{
				/// 공원안이라면 내 정보를 갱신		
				CTRGameParkUI::getInstance().av_setAdvancedAvatarInfo(advancedAvatarInfo);
			}
		}
		else
		{
			CNetClientManager::getInstance().requestSaveDefaultCharacter(CTRNetPlayManager::getInstance().getRealCharacter());
			m_bChangeMyAvatar = false;
		}
	}
}

void CTRCoupleSystem::onRecvMyRoomSetCharacterSetting()
{
	// 게임룸안에서 커플이 끊어졌을때 아바타 정보를 갱신한다.
	if(m_bChangeMyAvatar)
	{
		cpk_type character = CTRNetPlayManager::getInstance().getRealCharacter();
		CNetClientManager::getInstance().requestSaveDefaultCharacter(character);

		m_bChangeMyAvatar = false;   // 아바타 정보를 갱신 완료
	}	
}

/// 커플이름 변경 처리가 성공했다.
void CTRCoupleSystem::onRecvCoupleModifyCoupleNameResult(eServerResult eResult, std::string strCoupleName)
{
	// 서버로 커플 생성의 결과를 받았다.
	if(eResult == eServerResult_OK_ACK)
	{
		// 변경 성공이라면 상대커플에게 변경된 커플이름을 보낸다.
		CNetClientManager::getInstance().community_sendCoupleNameChange(CNetClientManager::getInstance().getMyCoupleInfo().strMateNickname, strCoupleName);

		// 입력창을 닫는다.
		m_coupleNameChangeDlg.closeDialog();

		// 커플명 변경되었다고 알림창을 띄운다.
		m_coupleNameChangeSuccDlg.showDialog(strCoupleName);

		// 공통아이템 리스트를 다시 요청한다.
		CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_CHANGE_COUPLE_NAME_ITEM);
	}
	else
	{
		m_coupleNameChangeDlg.onRecvCoupleModifyCoupleNameResultFailed(eResult);		
	}
}

/// 내 커플에 의해 버프를 받았다.
void CTRCoupleSystem::onRecvDivinationCoupleExAbilitiesResult(const ExtraAbilityInfo & appliedExtraAbilities, std::string strDivinationDesc)
{
	if(checkCoupleRecvNoLimit())
	{
		m_resultCard.showDialog(strDivinationDesc, appliedExtraAbilities, "gui\\park\\FortuneShop_Result_Couple.gui");
	}
	else
	{
		m_bCoupleDivinationRecv = true;
		m_coupleDivination = strDivinationDesc;
		m_appliedExtraAbility = appliedExtraAbilities;
	}
}

void CTRCoupleSystem::community_requestPropose(const std::string & strToNickname, const std::string & strCoupleName, const std::string & strCoupleDesc, const int iJewelBoxNum, const bool bMeetingDependency)
{
	CNetClientManager::getInstance().community_requestPropose(strToNickname, strCoupleName, strCoupleDesc, iJewelBoxNum, bMeetingDependency);

	m_iJewelBoxNum = iJewelBoxNum;
}

/// 프로포즈에 대한 승인여부를 받았다.
void CTRCoupleSystem::community_onRecvCoupleProposeResponse(const std::string & strFromNickname, const bool bOK, const eCoupleProposeReject eReason, const int iCoupleNum, const int iCoupleRingNum)
{
	DBG_OUTPUT("CTRCoupleSystem::community_onRecvCoupleProposeResponse strFromNickname = %s bOK = %s eReason = %d", strFromNickname.c_str(), bOK ? "true" : "false", eReason);

	if(bOK == true)
	{
		m_bCoupleRingnumDirty = true;
		CNetClientManager::getInstance().requestCoupleUpdateCoupleInfo();
	}
	m_iCoupleRingNum = iCoupleRingNum;

	if(checkCoupleRecvNoLimit())
	{
		showCoupleProposeResponse(bOK, eReason);
	}
	else
	{
		m_bCurProposeSend = true;
		m_bProposeResponse = bOK;
		m_eReason = eReason;
	}
}

void CTRCoupleSystem::community_onRecvCoupleProposeRequest(const std::string & strFromNickname, const std::string & strCoupleName, const std::string & strCoupleDesc, const int iJewelBoxNum, const bool bMeetingDependency)
{
	DBG_OUTPUT("CTRCoupleSystem::community_onRecvCoupleProposeRequest strFromNickname = %s strCoupleName = %s strCoupleDesc = %s  iJewelBoxNum = %d, bMeetingDependency = %s", strFromNickname.c_str(), strCoupleName.c_str(), strCoupleDesc.c_str(),iJewelBoxNum, bMeetingDependency ? "TRUE" : "FALSE");

	// 내가 이미 커플이라면 자동으로 거절한다.
	if(isHaveCouple())
	{
		onNoCoupleConsent();
		return;
	}

	// 상대로 부터 커플 응답을 받는다.
	m_coupleName = strCoupleName;
	m_coupleDes = strCoupleDesc;
	m_fromNickname = strFromNickname;
	m_iJewelBoxNum = iJewelBoxNum;
	m_bMeetingDependency = bMeetingDependency;

	if(checkCoupleRecvNoLimit())
	{
		m_yesNoDlg.showDialog(format(_STR(COUPLESYS_PROPOSE_ASK_COUPLE_OK), strFromNickname.c_str(), strCoupleName.c_str()) , this, &CTRCoupleSystem::onYesCoupleConsent, &CTRCoupleSystem::onNoCoupleConsent, "park\\Couple_Agree.gui", -3.f, false);
	}

	m_bCurProposeRecv = true; // 현재 커플 신청을 받은 상태인지를 설정
	m_coupleName = strCoupleName;
	m_fromNickname = strFromNickname;
}

void CTRCoupleSystem::community_onRecvCoupleSayGoodBye(const std::string & strFromNickname)
{
	CNetClientManager & rNetClientMgr = CNetClientManager::getInstance();

	rNetClientMgr.requestCharacterAvatarItemByItemNum(rNetClientMgr.getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
	rNetClientMgr.requestCoupleUpdateCoupleInfo();
	rNetClientMgr.requestFamilyInfo(rNetClientMgr.getMyNickname(), false);
	updateRingItem(rNetClientMgr.getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);

	// 내 복장을 갱신
	rNetClientMgr.requestMyCharacter();
	m_bChangeMyAvatar = true;

	m_fromNickname = strFromNickname;

	if(checkCoupleRecvNoLimit())
	{
		m_OKDlg.showDialog(format(_STR(COUPLESYS_CUT_MSG_CUT_COUPLE_BY_MY_COUPLE), strFromNickname.c_str()));
		CTRGameParkUI::getInstance().onCoupleInfoChange();
	}
	else
	{
		m_bCoupleBreak = true;
	}
}

/// 상대로부터 커플링을 변경했다 통지를 받았다.
void CTRCoupleSystem::community_onRecvCoupleRingChanged(const std::string & strFromNickname, const int iCoupleRingNum)
{
	CNetClientManager & rNetClientMgr = CNetClientManager::getInstance();
	m_iCoupleRingNum = rNetClientMgr.getMyCoupleInfo().coupleRingInfo.iCoupleRingNum;
	

	m_bCoupleRingnumDirty = true;

	rNetClientMgr.requestCharacterAvatarItemByItemNum(m_iCoupleRingNum);
	// 서버에 커플 정보 갱신
	rNetClientMgr.requestCoupleUpdateCoupleInfo();

	// 내 복장을 갱신
	rNetClientMgr.requestMyCharacter();
	m_bChangeMyAvatar = true;

	// 커플링 교체 도전미션 체크
	//checkChallengeSubjeck(iCoupleRingNum);

	m_fromNickname   = strFromNickname;

	if(checkCoupleRecvNoLimit())
	{
		m_coupleRingChangeResultDlg.showDialog(m_iCoupleRingNum,iCoupleRingNum);
	}
	else
	{
		m_bCoupleRingChangeRecv = true;
	}

	m_iOrgCoupleRingNum = m_iCoupleRingNum;
	m_iCoupleRingNum    = iCoupleRingNum;
}

/// 상대로부터 커플명을 변경했다 통지를 받았다.
void CTRCoupleSystem::community_onRecvCoupleNameChanged(const std::string & strFromNickname, const std::string & strCoupleName)
{
	if(checkCoupleRecvNoLimit())
	{
		m_coupleNameChangeSuccDlg.showDialog(strCoupleName);
	}
	else
	{
		m_coupleName = strCoupleName;
		m_bCoupleNameChangeRecv = true;
	}
}

/// 상대로부터 커플소개가 변경했다 통지를 받았다.
void CTRCoupleSystem::community_onRecvCoupleDescModify(const std::string & strFromNickname)
{
	if(checkCoupleRecvNoLimit())
	{
		string msg = _STR(MSG_MODIFY_COUPLE_DESC);
		m_OKDlg.showDialog("<normal>" + msg + "</normal>");
		
	}
	else
	{
		m_bCoupleDescChangeRecv = true;        
	}
}