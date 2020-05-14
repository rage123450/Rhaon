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

// ���� Ŭ����
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

	//!< Ŀ�÷��� ���ذ�(�ְ���) �������ð����� üũ��
	int iCoupleLevelMax = atoi(CNetClientManager::getInstance().getServerSetting("CoupleMaxLevel", "20").c_str());

	m_mapRingDayGradeTable[backRequirementLevel] = iCoupleLevelMax+1;   // ������ ��� Ŀ�ø����� ���� �ܰ谡 �����Ƿ� ū���� �ִ´�.

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
	if(m_bCurProposeRecv)  // ���� Ŀ�� ��û ���̶��(��û�� ����)
	{
		m_yesNoDlg.showDialog(format(_STR(COUPLESYS_PROPOSE_ASK_COUPLE_OK),m_fromNickname.c_str(), m_coupleName.c_str()) , this, &CTRCoupleSystem::onYesCoupleConsent, &CTRCoupleSystem::onNoCoupleConsent, "park\\Couple_Agree.gui", -3.f, false);
	}
	else
	{
		// onResetCoupleInfo �� ��Ȳ���� �ʱ�ȭ ������ ����  if/else ����
		if(m_bCurProposeSend)
		{
			// Ŀ���� ����Ǿ��ٰ� ����.
			showCoupleProposeResponse(m_bProposeResponse, m_eReason);	
		}
		else if(m_bCoupleBreak)
		{
			// Ŀ���� �������ٰ� ����.
			m_OKDlg.showDialog(format(_STR(COUPLESYS_CUT_MSG_CUT_COUPLE_BY_MY_COUPLE), m_fromNickname.c_str()));		
		}
		else if(m_bCoupleRingChangeRecv)
		{
			// Ŀ���� ��ü�Ǿ��ٰ� ����.
			m_coupleRingChangeResultDlg.showDialog(m_iOrgCoupleRingNum,m_iCoupleRingNum);
		}
		else if(m_bCoupleNameChangeRecv)
		{
			// Ŀ�� �̸��� ����
			m_coupleNameChangeSuccDlg.showDialog(m_coupleName);			
		}
		else if(m_bCoupleDescChangeRecv)
		{
			// Ŀ�� ������ ����
			string msg = _STR(MSG_MODIFY_COUPLE_DESC);
			m_OKDlg.showDialog("<normal>" + msg + "</normal>");
		}
		else if(m_bCoupleDivinationRecv)
		{
			// ���� Ŀ���� Ŀ�� ���� �ô�
			m_resultCard.showDialog(m_coupleDivination, m_appliedExtraAbility, "gui\\park\\FortuneShop_Result_Couple.gui");
		}

		onResetCoupleInfo();  // �����߿� ���� Ŀ�������� �ʱ�ȭ
	}	
}

bool CTRCoupleSystem::checkNextJewelBox(int &jewelBoxItemNum)
{
	vector<int> destList;

	destList = CClientItemList::getInstance().getItemInfo(eCharacterKind_NONE, eFuncItemPosition_JEWEL_BOX);

	int nowCoupleLevel = getMyCoupleLevel();

	for(vector<int>::iterator iter = destList.begin() ; iter < destList.end() ; ++iter)
	{
		// �����ϰ� �ִ� �����Ե��� ������ �޾ƿ´�.
		int requirementLevel = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(*iter).m_attr[eItemAttr_Couple_Level]);

		// �������� ������ ���� ��ü�ؾ��� ������ ���ٸ�
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
		// �����ϰ� �ִ� �����Ե��� ������ �޾ƿ´�.
		int requirementLevel = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum((*iter).m_iItemDescNum).m_attr[eItemAttr_Couple_Level]);

		// �������� ������ ���� ��ü�ؾ��� ������ ���ٸ�
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
		// ���õ� ����ġ ������ ����ġ�� �ð����� ȯ��

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
	// �α��� ���� �� Ŀ�� �� ��ü�ñ����� �˸�.
	checkCoupleChangeNotify();

	// �˸� �޼��� ó��

}

int CTRCoupleSystem::getMyCoupleDay()
{
	int myCoupleDay = 0;

	if(CNetClientManager::getInstance().getMyCoupleInfo().iCoupleNum > 0)
	{
		// Ŀ�� �ϼ� üũ
		time_type currentTime = CServerTime::getInstance().getCurrentTime();
		time_type coupleCreateTime = CNetClientManager::getInstance().getMyCoupleInfo().tCoupleCreateTime;

		int dayCountConstant = 1000 * 60 * 60 * 24;

		time_type day = currentTime/dayCountConstant - coupleCreateTime/dayCountConstant;		

		myCoupleDay = (int)(day + 1);      // ��¥ ����		
	}

	return myCoupleDay;
}

// ���� Ŀ��Level�� ��´�.(Ŀ���� �ƴ϶�� 0�� ��´�.)
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
	// Ŀ�� ������ �ʱ�ȭ�� �Ѵ�.
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
			//������ �����߽��ϴ�.
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_MSG_REFUSAL_CANCEL));
			break;
		case eCoupleProposeReject_LOGOUT:
			//������ �α׾ƿ��߽��ϴ�. �ڵ� �����Դϴ�.
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
		// ���ýý��� ����ؼ� �������� �� ��� �ϰ�� 
		m_proposeDlg.showDialog(iBuyItemNum, true);
	}
}

void CTRCoupleSystem::onChangeCoupleRingYesNo(int coupleLevel)
{
	int jewelBoxItemNum;

	if(checkNextJewelBox(jewelBoxItemNum))
	{
		const CItemInfoNode *nextJewelBox = CClientItemList::getInstance().getItemInfo(jewelBoxItemNum);
		// ��ü�� ������ ���� ������ �������ڰ� �ƴ� ���
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
		// ���� �ϰ� �ִ� ������ ���׷��̵尡 �������� ������
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
			m_iCoupleRingNum =  myCoupleInfo.coupleRingInfo.iCoupleRingNum;	//< ���� �� ��û �� ���� Ŀ�ø� ��ȣ�� ����صд�.
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

// �������� Ŀ�ÿ��� �����Ѵ�.
void CTRCoupleSystem::showGiftDialogSendGiftItem()
{
	// ��Ʈ�����̺��� �����۹�ȣ�� �о� �´�.
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
	// �������ڰ� ���ٸ� ����â�� ����.
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
			if(requirementLevel > myCoupleLevel)   // ���� ���� Ŀ�ø� �������� Ŀ����
			{
				buyitemList.push_back(pItemInfo);
			}
		}		
	}

	// �켱 �����ؾ��� ���������� �Ӽ� ��¥�� ���� ������������ ����
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

// ������� �ʾ� �ּ� ó�� ��
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

	if(iGameState == GAME_STATE_NO_GAME                   // �������� �ƴϿ�����
		&& !m_bRecvLimit)                                 // ���ѽ����� �ƴϿ�����
		return true;

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CTRCoupleSystem::onRecvCoupleCreateCoupleInfo(eServerResult eResult, const int iCoupleNum, const int iCoupleRingNum)
{	
	// ������ Ŀ�� ������ ����� �޾Ҵ�.
	if(eResult == eServerResult_OK_ACK)
	{
		CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_JEWEL_BOX);
		m_bCoupleRingnumDirty = true;

		// ������ Ŀ�� ���� ����
		CNetClientManager::getInstance().requestCoupleUpdateCoupleInfo();

		// �����̶�� ��뿡�� Ŀ�ø��ڰ� ������.
		CNetClientManager::getInstance().community_responsePropose(m_fromNickname, true, eCoupleProposeReject_NONE, iCoupleNum, iCoupleRingNum);

		CAudioManager::getInstance().playAudioEffectByFileName("sound\\redshoes.wav");

		m_coupleSuccDlg.showDialog(m_iJewelBoxNum, iCoupleRingNum);

		// Ŀ�� ��û ���̿��ٸ� �ݴ´�.
		m_proposeDlg.closeDialog();
	}
	else
	{
		switch(eResult)
		{
		case eServerResult_COUPLE_DUPLICATE_COUPLE_NAME_ACK:			
			// �̹� �����ϴ� Ŀ�ø��̴�.
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_DUPLICATE_COUPLE_NAME));
			_ASSERTE(false);
			break;
		case eServerResult_COUPLE_HE_IS_MY_FAMILY_ACK:
			m_OKDlg.showDialog(_STR(COUPLESYS_PROPOSE_ERR_IN_MY_FAMILY));
			break;
		case eServerResult_COUPLE_DBFAILED_ACK:			
			// DB ����.
			DBG_OUTPUT("CTRCoupleSystem::onRecvCoupleCreateCoupleInfo result = DB ERROR");
			break;
		}
	}

	onResetCoupleInfo();
}

/// �������� ������ üũ�Ѵ�.
void CTRCoupleSystem::onRecvCoupleCheckProposeInfo(eServerResult eResult, const bool bMeetingDependency)
{
	m_proposeDlg.onRecvCoupleCheckProposeInfo(eResult, bMeetingDependency);
}

void CTRCoupleSystem::onRecvCoupleInitRecvProposeInfoOK()
{
	// ���� ����
	CNetClientManager::getInstance().community_responsePropose(m_fromNickname, false, eCoupleProposeReject_DISAGREE, -1, 0);
	onResetCoupleInfo();
}

void CTRCoupleSystem::onRecvCoupleChangeCoupleRingOK(const CoupleInfo & OrgCoupleInfo ,const CoupleInfo & ChangeCoupleInfo)
{
	CNetClientManager & rNetClientMgr = CNetClientManager::getInstance();
	int iNewCoupleRingNum = ChangeCoupleInfo.coupleRingInfo.iCoupleRingNum;
	rNetClientMgr.requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_JEWEL_BOX);

	// ������ Ŀ�� ���� ����
	rNetClientMgr.requestCoupleUpdateCoupleInfo();

	string myCoupleMateName = rNetClientMgr.getMyCoupleInfo().strMateNickname;

	// �� ������ ����
	rNetClientMgr.requestMyCharacter();
	m_bChangeMyAvatar     = true;
	m_bCoupleRingnumDirty = true;

	// ��ü�Ǿ����� �˸���.
	m_coupleRingChangeResultDlg.showDialog(OrgCoupleInfo.coupleRingInfo.iCoupleRingNum,ChangeCoupleInfo.coupleRingInfo.iCoupleRingNum);

	// Ŀ�ø� ��ü �����̼� üũ
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

	// ��뿡�� �������ٰ� �˸���.
	rNetClientMgr.community_sendCoupleSayGoodbye(strMateName);

	rNetClientMgr.requestCharacterAvatarItemByItemNum(rNetClientMgr.getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
	
	updateRingItem(rNetClientMgr.getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);

	// ������ Ŀ�� ���� ����
	rNetClientMgr.requestCoupleUpdateCoupleInfo();

	// ������ �йи� ���� ����
	rNetClientMgr.requestFamilyInfo(rNetClientMgr.getMyNickname(), false);

	m_bCoupleRingnumDirty = true;

	// �� ������ ����
	rNetClientMgr.requestMyCharacter();
	m_bChangeMyAvatar = true;
	
	m_OKDlg.showDialog(_STR(COUPLESYS_CUT_MSG_CUT_COUPLE));	
}

//! ���� Ŀ�� ������ ���� �޾Ҵ�.
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
		if(CNetClientManager::getInstance().requestSaveCharacterSetting(advancedAvatarInfo))  // �����鿡 �� �ƺ�Ÿ ������ �˸���.
		{
			if(CTRGameParkUI::getInstance().isActive())
			{
				/// �������̶�� �� ������ ����		
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
	// ���ӷ�ȿ��� Ŀ���� ���������� �ƹ�Ÿ ������ �����Ѵ�.
	if(m_bChangeMyAvatar)
	{
		cpk_type character = CTRNetPlayManager::getInstance().getRealCharacter();
		CNetClientManager::getInstance().requestSaveDefaultCharacter(character);

		m_bChangeMyAvatar = false;   // �ƹ�Ÿ ������ ���� �Ϸ�
	}	
}

/// Ŀ���̸� ���� ó���� �����ߴ�.
void CTRCoupleSystem::onRecvCoupleModifyCoupleNameResult(eServerResult eResult, std::string strCoupleName)
{
	// ������ Ŀ�� ������ ����� �޾Ҵ�.
	if(eResult == eServerResult_OK_ACK)
	{
		// ���� �����̶�� ���Ŀ�ÿ��� ����� Ŀ���̸��� ������.
		CNetClientManager::getInstance().community_sendCoupleNameChange(CNetClientManager::getInstance().getMyCoupleInfo().strMateNickname, strCoupleName);

		// �Է�â�� �ݴ´�.
		m_coupleNameChangeDlg.closeDialog();

		// Ŀ�ø� ����Ǿ��ٰ� �˸�â�� ����.
		m_coupleNameChangeSuccDlg.showDialog(strCoupleName);

		// ��������� ����Ʈ�� �ٽ� ��û�Ѵ�.
		CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_CHANGE_COUPLE_NAME_ITEM);
	}
	else
	{
		m_coupleNameChangeDlg.onRecvCoupleModifyCoupleNameResultFailed(eResult);		
	}
}

/// �� Ŀ�ÿ� ���� ������ �޾Ҵ�.
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

/// ������� ���� ���ο��θ� �޾Ҵ�.
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

	// ���� �̹� Ŀ���̶�� �ڵ����� �����Ѵ�.
	if(isHaveCouple())
	{
		onNoCoupleConsent();
		return;
	}

	// ���� ���� Ŀ�� ������ �޴´�.
	m_coupleName = strCoupleName;
	m_coupleDes = strCoupleDesc;
	m_fromNickname = strFromNickname;
	m_iJewelBoxNum = iJewelBoxNum;
	m_bMeetingDependency = bMeetingDependency;

	if(checkCoupleRecvNoLimit())
	{
		m_yesNoDlg.showDialog(format(_STR(COUPLESYS_PROPOSE_ASK_COUPLE_OK), strFromNickname.c_str(), strCoupleName.c_str()) , this, &CTRCoupleSystem::onYesCoupleConsent, &CTRCoupleSystem::onNoCoupleConsent, "park\\Couple_Agree.gui", -3.f, false);
	}

	m_bCurProposeRecv = true; // ���� Ŀ�� ��û�� ���� ���������� ����
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

	// �� ������ ����
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

/// ���κ��� Ŀ�ø��� �����ߴ� ������ �޾Ҵ�.
void CTRCoupleSystem::community_onRecvCoupleRingChanged(const std::string & strFromNickname, const int iCoupleRingNum)
{
	CNetClientManager & rNetClientMgr = CNetClientManager::getInstance();
	m_iCoupleRingNum = rNetClientMgr.getMyCoupleInfo().coupleRingInfo.iCoupleRingNum;
	

	m_bCoupleRingnumDirty = true;

	rNetClientMgr.requestCharacterAvatarItemByItemNum(m_iCoupleRingNum);
	// ������ Ŀ�� ���� ����
	rNetClientMgr.requestCoupleUpdateCoupleInfo();

	// �� ������ ����
	rNetClientMgr.requestMyCharacter();
	m_bChangeMyAvatar = true;

	// Ŀ�ø� ��ü �����̼� üũ
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

/// ���κ��� Ŀ�ø��� �����ߴ� ������ �޾Ҵ�.
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

/// ���κ��� Ŀ�üҰ��� �����ߴ� ������ �޾Ҵ�.
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