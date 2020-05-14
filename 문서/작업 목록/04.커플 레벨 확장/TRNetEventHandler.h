/* ---------------------------------------------------------------
*
* Copyright 2005 by Rhaon Ent.
*
* TRNetEventHandler.h
*
* 2006.6.30 Pyo, Taesu.
* 
* ---------------------------------------------------------------
*/

#pragma once

#include "NetClientManager.h"
#include "IntNetListener.h"

class CTRNetPlayManager;
class CTRGameRoomUIBase;


class CTRNetEventListener
{
public:
	/// ������ ���� ���� ���.
	virtual bool onRecvLoginAuth(eServerResult eResult, const std::string& strMyID)
	{
		return false;
	}

	virtual bool onRecvLoginFail(eServerResult eError , BYTE byDetail)
	{
		return false;
	}

	virtual bool onRecvSnDALoginNotEnoughInfoFailed(const eServerResult& failedReason, const std::string& addtionInfo)
	{
		return false;
	}
	virtual void onRecvP2PData(int iPlayerIndex, const char * dataPtr, size_t dataSize, bool bWithConfirm) {}
	virtual void onRecvMyRoomSetCharacterSetting() {}
	virtual void onRecvMyRoomSetDefaultCharacterOK() {}
	virtual void onRecvForwardToRoomUser(const size_t from,const CPacketChunk & data){};

	// TODO: onRecvForwardToAllRoomUser � �������̽���...
#ifdef _SHU_SYSTEM_
	//!< ���� �ȿ��� ĳ���� --> �� �±� �׼��� �����ߴ�..
	virtual void onRecvShuCharIngameTagAction_Start(const int nPlayerIndex,const int characterAvatarItemNum){};

	//!< ���� �ȿ��� �� --> ĳ���� �±� �׼��� �����Ͽ���.
	virtual void onRecvShuCharIngameTagAction_End(const int nPlayerIndex,const SHU_SYSTEM::eIN_GAME_SHU_TAG_END_TYPE end_type){};

	//!< ���� �ȾƼ� ���������� �� �±� �׼� ������ �����Ͽ���.
	virtual void onRecvThisPlayerShuCharIngameTagAction_Start_failed(){};

	//!< ���ӹ� �ȿ��� Ư�� ������ �� ĳ���� ������ ����Ǿ���.
	virtual void onRecvPlayerShuCharInfoModify(const int nPlayerIndex,const SHU_SYSTEM::CPlayerShuCharacterInfo & updateInfo){};
#endif //_SHU_SYSTEM_
};



class CTRNetEventHandler : public IntNetListener
{
public:
	CTRNetEventHandler();

	void setNetEventListener(CTRNetEventListener * pListener)
	{
		m_pNetEventListener = pListener;
	}

	void setGameRoomUI(CTRGameRoomUIBase * pGameRoomUI)
	{
		m_pGameRoomUI = pGameRoomUI;        
	}
	
public:

public:
	
	/// ������ ���� ���� ������ �����.
	virtual void onRecvServerSettingInfo();

	/// ������ ���� ������ �ٲ����.
	virtual void onRecvServerSettingInfoChanged();

	/// ������ ���� ���� ���.
	virtual void onRecvLoginAuth(eServerResult eResult, const std::string& strMyID);

	//////////////////////////////////////////////////////////////////////////
	/// �ε� ������ ���� ����.

	//! ���� ���θ� �˸���.
	virtual void LoadBalance_Connect(eLoadBalanceProtocolResult eResult);

	//! ������ ���� ������ �����.
	virtual void LoadBalance_Disconnect();

	//! ������ ���� �۰� ����ִ� ������ �ּҿ� ��Ʈ�� ��´�.
	virtual void LoadBalance_Login( const std::string & serverIP, const int & nPort, bool bHash);

	/// �ε� ������ ���� ���� ��.
	//////////////////////////////////////////////////////////////////////////


	/// ������ �޼����� ���������� �޾Ҵ�.
	virtual void onRecvGetItemMsgOK(std::vector<ItemMsgInfo>& vecItemMsgInfo);

	/// ���� ������ �޼����� ���������� �޾Ҵ�.
	virtual void onRecvGetGiftItemMsgOK(std::vector<ItemMsgInfo>& vecItemMsgInfo);

	/// �ӽú����� ������ �޼����� ���������� �޾Ҵ�.
	virtual void onRecvGetOutboxItemMsgOK(std::vector<ItemMsgInfo>& vecItemMsgInfo);

	/// ������ �޼����� �޴µ� �����Ͽ���.
	virtual void onRecvGetItemMsgFailed();

	//////////////////////////////////////////////////////////////////////////

	/// Ŭ���̾�Ʈ �ؽ����� �������� üũ�� ����� �����.
	virtual void onRecvClientHashCheck(eClientHashCheck eResult);

	/// ���̺�Ʈ�� �߻��ߴ�.
	virtual void onRecvRoomEvent(eRoomEvent eEventType, BYTE playerIndex, BYTE eventID );


	//////////////////////////////////////////////////////////////////////////
	/// �߰��� ��ŷ�� �ؽ����� �޾Ҵ�.
	virtual void onRecvAddHackingToolHack(const std::vector<std::string>& vecHackingToolHash, const std::vector<std::string>& vecAllowingHackingToolHash);

	/// ������ �޾Ҵ�.
	virtual void onRecvGetGuildName(const std::string& strGuildName, const std::string & strGuildMarkURL);

	/// �����������޾Ҵ�.
	virtual void onRecvGetLadderInfo(const int & iLadderPoint, const int & iLadderRank);

	/// PC�� ���� �������� �޾Ҵ�.
	virtual void onRecvGetPCRoomItem(const std::set<int> & setPCRoomItem);

	/// PC�� Ÿ���� ����Ǿ���.
	virtual void onRecvGetPCRoomRivalType();

	/// �Ϸ��ѹ� �����ؾ��Ѵ�.(�θƽý��ۿ�)
	virtual void onRecvGetResetNotify();

	/// ����� ���� �������� �޾Ҵ�.
	virtual void onRecvGetMembershipItem(const std::vector<int> & vecMembershipItem);

	/// ����� ���� �������� ������ ��û�� �޾Ҵ�.
	virtual void onRecvRemoveMembershipItem(const std::vector<int> & vecMembershipItem);

	/// ������ ON/OFF�ߴ�.
	virtual void onRecvItemOnOff(const eServerResult eResult, const int iItemDescNum,const bool bOnOff);

	/// �α��� ��⸦ �ض�.
	virtual void onRecvNoticeWaitForLogin(const size_t iRemainUserCount, const DWORD dwEstimatedRemainTime);

	/// ���� �α��� �����, ��⿹�� �ð� ������ �޾Ҵ�.
	virtual void onRecvNoticeRemainUserNumAndTimeInfo(const size_t iRemainUserCount, const DWORD dwEstimatedRemainTime);

	/// ������ �޾Ҵ�.
	virtual void onRecvGetGuildName(const std::string& strGuildName){}

	/// ������ ����ġ�� ���� ������ �޾Ҵ�
	virtual void onRecvLevelUPInfo(std::map<eLevelUPKind, LevelUPExp>& levelUPInfo);

	/// Shutdown ������ �޾Ҵ�.
	virtual void onRecvShutdownNotify(eShutdownNotification eNotification, const std::string& strServerMessage);

	/// �� ���׷��̵带 �����ߴ�.
	virtual void onRecvMyRoomPetUpgradeOK();

	/// �� ���׷��̵带 �����ߴ�.
	virtual void onRecvMyRoomPetUpgradeFailed(eMyRoomProtocol_PET_UPGRADE_FAILED_REASON failedReason);

	/// �������� ����µ� �����ߴ�.
	virtual void onRecvMyRoomDeleteItemOK(const int iDeleteItemItemDescNum);

	/// �������� ����µ� �����ߴ�.
	virtual void onRecvMyRoomDeleteItemFailed(eDeleteItemFailedReason failedReason);

	/// ���� ž�µ��� �ƹ�Ÿ�� �����µ� �����ߴ�.
	virtual void onRecvMyRoomGetAnimalAvatarOK(AnimalRacingAnimalAvatar & animalRacingAvatar);

	/// ���� ž�µ��� �ƹ�Ÿ�� �����µ� �����ߴ�.
	virtual void onRecvMyRoomGetAnimalAvatarFailed();

	/// ���̷뿡�� ž�µ��� �ƹ�Ÿ ������ �����ϴ� �� �����ߴ�.
	virtual void onRecvMyRoomSetAnimalRacingAvatarInfoSettingOK(AnimalRacingAnimalAvatar & animalRacingAvatar);

	/// ���̷뿡�� ž�µ��� �ƹ�Ÿ ������ �����ϴ� �� �����ߴ�.
	virtual void onRecvMyRoomSetAnimalRacingAvatarInfoSettingFailed(int nReason);

	/// ���̷뿡�� ž�µ��� �����ִµ� �����ߴ�.
	virtual void onRecvMyRoomAnimalRacingFeedAnimalOK(int nTargetAnimalDescNum, int nFeedItemDescNum);

	/// ���̷뿡�� ž�µ��� �����ִµ� �����ߴ�.
	virtual void onRecvMyRoomAnimalRacingFeedAnimalFailed(byte nReason);

	/// �� ���� �������� ����ġ�� �޾Ҵ�.
	virtual void onRecvRoomExpOfUsers(const std::map < BYTE, exp_type > indexToExp);

	/// ������ ������ ���ʽ��� �޾Ҵ�.
	virtual void onRecvEndGameBonus(eEndGameBonus eType, BYTE byBoardNum);

	/// ���� ī�� �� ������ ��ϵ��� �����.
	virtual void onRecvMyCardRecipeKeepList(const std::vector< CardRecipeKeepInfo > & keepList, bool bReplace = false);

	/// ���� ī�� �� ������ ��ϵ� ��µ� �����ߴ�.
	virtual void onRecvMyCardRecipeFailed();

	/// ���� �������� ���µ� �����ߴ�.
	virtual void onRecvMyRoomUseRepairItemOK(const int iTargetItemDescNum, const int iRepairItemdDescNum);

	/// ���� �������� ���µ� �����ߴ�.
	virtual void onRecvMyRoomUseRepairItemFailed(eMyRoomProtocol_USE_REPAIR_ITEM_FAILED_REASON failedReason,const int iTargetItemDescNum, const int iRepairItemDescNum);

	/// ģ�� Ȯ��� ������ ��븦 �����ߴ�.
	virtual void onRecvMyRoomUseAddFriendOK(const int iItemDescNum, const int iFriendAddCount);

	/// ģ�� Ȯ��� ������ ��븦 �����ߴ�.
	virtual void onRecvMyRoomUseAddFriendFailed(eMyRoomProtocol_ADDFRIEND_FAILED_REASON failedReason);
	
	/// �� ���� �������� ���µ� �����ߴ�.
	virtual void onRecvMyRoomUsePetFeedOK(const int iTargetPetDescNum, const int iFeedItemDescNum);

	/// �� ���� �������� ���µ� �����ߴ�.
	virtual void onRecvMyRoomUsePetFeedFailed(eMyRoomProtocol_USE_PET_FEED_FAILED_REASON failedReason);

	/// �� ��Ȱ �������� ���µ� �����ߴ�.
	virtual void onRecvMyRoomUsePetRebirthOK(const std::vector<int> petItemNumList, int iPetRebirthItemNum);

	/// �� ��Ȱ �������� ���µ� �����ߴ�.
	virtual void onRecvMyRoomUsePetRebirthFailed(const int iTargetPetItemDescNum,eMyRoomProtocol_USE_PET_REBIRH_FAILED_REASON failedReason);

	/// ������ �ð��� �޾Ҵ�.
	virtual void onRecvServerTime(const time_type & serverTime, bool bCheckTime);

	/// ���� ��ŷ �ǽ� ������.
	virtual void onRecvHackingTime(const time_type& hackingTime );

	/// �������� �α����� �����ߴ�.
	virtual void onRecvLoginFail(eServerResult eError , BYTE byDetail);

	/// ����� �̷��� �������� �α����� �����ߴ�.
	virtual void onRecvLoginFailByBlock(int iBlockReason, time_type tBlockStartTime, time_type tBlockEndTime);

	/// ���� �α��� ����. 
	virtual void onRecvSnDALoginOK(void); 

	/// ���� �α��� ���� �������� ����.. �߰���û �ʿ�. 
	virtual void onRecvSnDALoginNotEnoughInfoFailed(const eServerResult& failedReason, const std::string& addtionInfo); 

	/// 
	virtual void onRecvSnDALoginFailed(void); 

	/// ������ ������ ������ �̷����(TCP ���� �� UDP ��ȯ�� �̷������)
	virtual void onCompleteFullConnection();

	/// �г����� �Է��ض�.
	virtual void onRecvEnterNickname();

	/// �г����� �� �ԷµǾ���.
	virtual void onRecvEnterMyNicknameOK();

	/// ��밡���� �г��������� üũ�ϴ� ����� �Դ�.
	virtual void onRecvCheckNicknameResult(const std::string & strNickname, eServerResult result);

	/// ���� �� ���� �г����̾���.
	virtual void onRecvEnterMyNicknameFailed(const DWORD & dwResult);

	/// �г����� ����Ǿ���.
	virtual void onRecvChangeMyNicknameOK();

	/// �г��� ���濡 �����ߴ�.
	virtual void onRecvChangeMyNicknameFailed(const DWORD & dwResult);

	/// ���� �г����� �޾Ҵ�.
	virtual void onRecvMyNickname(const std::string & strNickname);

	/// Ư�� ������ �г����� �޾Ҵ�.
	virtual void onRecvGetUserNickname(const int iUserNum, const std::string &strNickname);

	/// Ư�� ������ �г����� �������⸦ �����ߴ�.
	virtual void onRecvGetUserNicknameFailed(const eServer_GET_USER_NICKNAME_FAILED_REASON eFailedReason);

	/// ����ġ�� ���� �޾Ҵ�.
	virtual void onRecvExp(eLevelUPKind levelKind, const exp_type iExp);

	/// ������ �ý��� �ð��� �޾Ҵ�.
	virtual void onRecvServerSystemTime(time_type tServerTime);

	/// XTrap ���� ��Ŷ�� �޾Ҵ�.
	virtual void onRecvXTrapCSPacket(char * data, size_t size);

	/// Xigncode ���� ��Ŷ�� �޾Ҵ�.
	virtual void onRecvXigncodeCSPacket(char * data, size_t size);

	/// AhnHackShield ���� �޼����� ������ ���� �޾Ҵ�.
	virtual void onRecvAhnHSAuthMSG(unsigned char * pbyRequest, unsigned long ulLength);

#ifdef _ITEM_ONOFF
	/// �ǽð� ���� ���� �ؾߵǴ� ������ ������ �޾Ҵ�.
	virtual void onRecvRealTimeItemInfo(RT_ITEM::CPacket_RealTimeItemInfo & data);
#endif//_ITEM_ONOFF

	/// ���� Ȱ��ȭ�� ��ɼ� �������� �޾Ҵ�.
	virtual void onRecvGetActiveFuncItem(const CActiveItems & activeItems);

	/// ���� Ȱ��ȭ�� ��ɼ� �������� �޴µ� �����ߴ�.
	virtual void onRecvGetActiveFuncItemFailed();

	/// ���� ������ �ɷ�ġ�� �޾Ҵ�.
	virtual void onRecvGetUserItemAttr(const CUserItemAttrManager& useritemAttr);

	/// ���� ������ �ɷ�ġ�� �޴µ� �����Ͽ���.
	virtual void onRecvGetUserItemAttrFailed();

	/// ���� �ɸ��� �ɷ�ġ�� �޾Ҵ�.
	virtual void onRecvGetUserCharAttr(const CUserItemAttrManager& useritemAttr);

	/// ���� �ɸ��� �ɷ�ġ�� �޴µ� �����Ͽ���.
	virtual void onRecvGetUserCharAttrFailed();

	/// ���� ��ȭ������ ������ �޾Ҵ�. 
	virtual void onRecvGetUserStrengthenItemInfo(); 

	/// ���� ��ȭ������ ������ �޴µ� �����Ͽ���. 
	virtual void onRecvGetUserStrengthenItemInfoFailed(); 

	/// ���ӷ�ȿ� �ִ� ������� Ȱ��ȭ�� ������ ������ �ٲ����.
	virtual void onRecvChangeUserActiveItems( BYTE playerIndex , const CActiveItems & activeItems);

	/// ���ӷ�ȿ� �ִ� ������� Ȱ��ȭ�� �ϳ��� ������ ������ �ٲ����.
	virtual void onRecvChangeUserActiveItemsOne( BYTE playerIndex , const CActiveItems & activeItems, const CUserItemAttrManager & useritemattr, const eChangeUserActiveItemFlag changeFlag);

	/// ���ӷ�ȿ� �ִ� ������� ������ �ɷ�ġ ������ �ٲ����.
	virtual void onRecvChangeUserItemAttr( BYTE playerIndex,const CUserItemAttrManager& useritemattr);

	/// ���ӷ�ȿ� �ִ� ������� ��ý�Ʈ ������ ������ �ٲ����.
	virtual void onRecvChangeUserAssistItems( std::vector< AssistItemBuyInfo > & assistItemBuyInfo );

	/// Ư�������� ���������� �ٲ����.
	virtual void  onRecvUserState(BYTE playerIndex , const int iState );

	/// ���� Ȱ��ȭ�� ��ɼ� �������� �ð��� ������.
	virtual void onRecvActiveFuncItemTimeOut(const int iItemDescNum);
	virtual void onRecvActiveFuncItemTimeOut();

	/// ���� ���� �������� �ð��� ������.
	virtual void onRecvBuffItemTimeOut(const int iItemDescNum);

	/// Ŭ���̾�Ʈ�� ���� �� �������� url �� �޾Ҵ�.
	virtual void onRecvClientWebPageURL(eWebPageReq reqKind, const std::string & strURL);

	/// ó�� �����̾ ĳ���� ����â�� ��� �����ض�.
	virtual void onRecvSelectStartCharacter();

	/// ĳ���� ������ �ߵǾ���. ����â�� �ݾƶ�.
	virtual void onRecvSelectStartChracterOK();

	/// ���� �ƹ�Ÿ�� �����ϴµ� DB Error �� ���� �ɰ��� ������.
	virtual void onRecvSelectStartCharacterFail();

	/// ���� �ƹ�Ÿ ������ �޾Ҵ�.
	virtual void onRecvAvatarInfo(const AdvancedAvatarInfo & advancedAvatarInfo);

	/// ���� �������̽� �ƹ�Ÿ ������ �޾Ҵ�.
	virtual void onRecvAnimalRacingAvatarInfo(const AnimalRacingAnimalAvatar& animalRacingAvatarInfo);

	/// �������̽� �ƹ�Ÿ�� �޴µ� �����ߴ�.
	void onRecvAnimalRacingAvatarFail();

	/// �������̽� �ƹ�Ÿ�� ����. Ʃ�丮�� �����ؾ��Ѵ�.
	void onRecvHaveNoAnimalRacingAvatar();

	/// �ƹ�Ÿ �������� DB Error �� ���Ͽ� ���� ���ߴ�. �ɰ��� ��Ȳ�̴�.
	virtual void onRecvGetAvatarFail() {}

	/// �̺�Ʈ�� �����ߴ�.
	virtual void onRecvEventFail();

	/// �̺�Ʈ ���� ������ ���.
	virtual void onRecvEventUserReset(const std::string & strUserID, bool bSuccess) {}

	/// ���������� �޾Ҵ�.
	virtual void onRecvNoticeMsg(const NOTICE& notice) override;

	/// ��ġ�� �������� ����ߴ�.
	virtual void onRecvUseShoutItem(eServerResult dwResult,const int iShoutItemDescNum, std::string& restrictEndTime);

	/// ��ġ�� �޼���
	virtual void onRecvShoutItemMsg(const UserShoutInfo& info);

	/// Ŀ�û��� ���� ��ġ�� �޼���
	virtual void onRecvShoutCoupleCreateCoupleMsg(const UserShoutInfo& info);

	/// �����α� ���� ��ġ�� �޼���
	virtual void onRecvShoutCoupleCreateFamilyMsg(const UserShoutInfo& info);

	/// ��ȥ ���� �޼���
	virtual void onRecvShoutWeddingMarchMsg(const UserShoutInfo& info);

	/// �߿��� �ø��� ���ؼ���� �޼���
	virtual void onRecvShoutInterruptObjectMsg(const UserShoutInfo& info);

	/// ��� ������ �޽���
	virtual void onRecvShoutGuildLevelUpMsg(const UserShoutInfo& info);

	/// Ŀ�ø� ��ü ���� ��ġ�� �޼���
	virtual void onRecvShoutCoupleChangeRingMsg(const UserShoutInfo& info);

	/// ���Ӵ� �������� ����ߴ�.
	virtual void onRecvUseChargeCommunityMoneyItem(eServerResult dwResult,const int iItemDescNum, std::string stdUserID);

	/// ���� ������ �Դ�.
	virtual void onRecvGetUserInfoOK(const UserInfo & userInfo, AvatarLock & avatarLock = AvatarLock());

	/// ���� ������ ��µ� �����Ͽ���.
	virtual void onRecvGetUserInfoFailed(const std::string & stdNickName);	

	/// ���� �ɼ� ������ �Դ�.
	virtual void onRecvSetUserOptionOK(const int iOption);

	/// ���� �ɼ� ������ ��µ� �����Ͽ���.
	virtual void onRecvUserOptionFailed();

#ifdef _ITEM_COLLECTION
	/// ���� ������ �÷¼� �����̴�.
	virtual void onRecvItemCollectionInfoOK(const std::string & strNickName, const exp_type iPoint, const int iRank);

	/// ���� ������ �÷¼� ������ �����̴�.
	virtual void onRecvItemCollectionListOK(const std::string & strNickName, const std::vector<int> & vItemList);

	/// ���� ������ �÷¼� ��ǥ ������ ��Ͽ� �����ߴ�.
	virtual void onRecvItemCollectionAddOK();

	///  ���� ������ �÷¼� �����Ͽ� �����Ͽ���.
	virtual void onRecvItemCollectionFailed(const eServerResult & dwResult);
#endif

	/// ��ŷ ������ �Դ�.
	virtual void onRecvRankInfo(const eRequestRankKind rankKind, const std::vector < CRankListData > & rankList, const std::vector<CoupleRankInfo>& coupleRankList);

	/// ��ŷ ������ �޴µ� �����ߴ�.
	virtual void onRecvRankInfoFailed(void);

	/// �� ��ŷ ������ �Դ�.
	virtual void onRecvMyRankInfo(const eRequestRankKind rankKind, const CRankListData & rankData, const CoupleRankInfo& coupleRankInfo);

	/// �� ��ŷ ������ �޴µ� �����ߴ�.
	virtual void onRecvMyRankInfoFailed(eRequestRankKind rankKind);

	/// ���ŷ �޽����� �޾Ҵٴ� ������ �Դ�.
	virtual void onRecvBlockingResult(eBlockReason reason);

	/// ���ǼҸ� �����϶�� �Դ�.
	virtual void onRecvCourtResult(const int judgementNum, const eCourtKind kind, const BYTE punishcount, const bool infinity);

	/// ���Ǽ��� ���� ���ٰ� �Դ�.
	virtual void onRecvCourtNoResult();

	/// �ҷ����� �Ű� ������ �Դ�.
	virtual void onRecvBadUserResult(const eCourtKind kind, const eServerResult dwResult);

	//////////////////////////////////////////////////////////////////////////
	// MiniGame ���� ����..

	//!< �̴ϰ��� �� ������ �޴� �� �����Ͽ���.
	virtual void onRecvMiniGameGetMapInfoOK(const int numMap,const int nMapPrice,const int nRewardPoint,const int nLife,const int nItemDescNum);

	//!< �̴ϰ��� �� ������ �޴� �� �����Ͽ���.
	virtual void onRecvMiniGameGetMapInfoFailed();

	//!< �̴ϰ����� �����ص� ����.
	virtual void onRecvMiniGameStartOK(const int numMap, const int iRandomSeed,const int iRemainGameMoney);

	//!< ���� �Ӵϰ� �����Ͽ� ������ ���� ���ߴ�.
	virtual void onRecvMiniGameStartFailedPayGameMoney(const int numMap, const int iRemainGameMoney);

	//!< ��ȿ���� �ʴ� ���� �����Ϸ��� �ߴ�.
	virtual void onRecvMiniGameStartFailedInvalidMapNum();

	//!< �̴ϰ��� ��ŷ ������ �����.
	virtual void onRecvMiniGameGetRankOK(const int numMap, const std::vector<MiniGameRankInfo>& rankInfo, const int nMyRank, const DWORD dwMyPoint);

	//!< �̴ϰ��� ��ŷ ������ ��µ� �˼� ���� ������ �����Ͽ���
	// TODO : �������.
	virtual void onRecvMiniGameGetRankFailed(){}

	//!< �̴ϰ��� ��ŷ ������ ��µ� �����Ͽ���(�ʹ�ȣ�� ��ȿ���� ����.)
	virtual void onRecvMiniGameGetRankFailedInvalidMapNum();

	//!< �̴ϰ��� �� ����.
	virtual void onRecvMiniGameOverOK(const int myBestPoint, const int myRank,const int nRewardItemDescNum , DWORD dwRewardPoint);

	//!< �̴ϰ��� �� ����.
	virtual void onRecvMiniGameOverFailed(eServerResult eResult);

	// MiniGame ���� ��..

	//! ���� �˸� ������ �����.
	virtual void onRecvUserAlarmInfo(std::vector<UserAlarmInfo> vAlarmInfoList);
	//////////////////////////////////////////////////////////////////////////
	// Ŀ�ýý��� ���� ����...

	//! �������� ������ üũ�Ѵ�.
	virtual void onRecvCoupleCheckProposeInfo(eServerResult eResult, bool bMeetingDependency);

	//! Ŀ�ø� ��ü�� �����ߴ�.
	virtual void onRecvCoupleChangeCoupleRingOK(const CoupleInfo & OrgCoupleInfo ,const CoupleInfo & ChangeCoupleInfo);

	//! Ŀ�ø� ��ü�� �����ߴ�.
	virtual void onRecvCoupleChangeCoupleRingFailed(eCoupleChangeCoupleRing failedReason);

	//! �������� ���� �ʱ�ȭ�� �����ߴ�.
	virtual void onRecvCoupleInitRecvProposeInfoOK();

	//! �������� ���� �ʱ�ȭ�� �����ߴ�.
	virtual void onRecvCoupleInitRecvProposeInfoFailed();

	//! Ŀ�� ������û�� ���� ������ �޾Ҵ�.
	virtual void onRecvCoupleCreateCoupleInfo(eServerResult eResult, const int iCoupleNum, const int iCoupleRingNum);

	//!< Ŀ������ ���� ó���� �����ߴ�.
	virtual void onRecvCoupleModifyCoupleInfoOK();

	//!< Ŀ������ ���� ó���� �����ߴ�.
	virtual void onRecvCoupleModifyCoupleInfoFailed();

	//!< Ŀ���̸� ���� ó���� �����ߴ�.
	virtual void onRecvCoupleModifyCoupleNameResult(eServerResult eResult, std::string strCoupleName);

	//! Ŀ�� ������û�� ���� ������ �޾Ҵ�.
	virtual void onRecvCoupleRemoveCoupleInfo(std::string strMateName);

	//! Ŀ�� ������û�� ���� ���������� �޾Ҵ�.
	virtual void onRecvCoupleRemoveCoupleInfoFailed();

	//! ������ Ŀ�� ������ �޾Ҵ�.
	virtual void onRecvCoupleGetCoupleInfo(std::string strCoupleName, std::string strCoupleDesc, CoupleInfo & info, std::map<std::string, AvatarInfo> & mapCoupleAvatarInfo, bool bForTalesBook);

	//! ������ Ŀ�� ������ �޴µ� �����޴�.
	virtual void onRecvCoupleGetCoupleInfoFailed();

	//! ���� Ŀ�� ������ ���� �޾Ҵ�.
	virtual void onRecvCoupleUpdateCoupleInfo(const CoupleInfo & conpleInfo);

	//! ���� Ŀ�� ������ ���� �޴µ� �����ߴ�.
	virtual void onRecvCoupleUpdateCoupleInfoFailed();


	// Ŀ�ýý��� ���� ��..
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// ���� �ý���

	//! ������ ������ �޴´�.
	virtual void onRecvFamilyGetFamilyInfo(const std::map<eFAMILY_UNIT_TYPE, const std::map<std::string, FamilyUnitInfo> > familyInfoList, std::string strNickName, int iParentsCoupleNum, int iMyCoupleNum, eCoupleType eMyCoupleType);

	//! ������ ������ �޴µ� �����ߴ�.
	virtual void onRecvFamilyGetFamilyInfoFailed(eServerResult failedReason);

	//! ���� �α� �������� üũ ��û�� ���� ���� �޽����� �޾Ҵ�.
	virtual void onRecvFamilyCheckProposeCondition(std::string strNickName, bool bParents);

	//! ���� �α� �������� üũ ��û�� ���� ���� �޽����� �޾Ҵ�.
	virtual void onRecvFamilyCheckProposeConditionFailed(eServerResult failedReason);

	//! ������ �α⿡ �����ߴ�.
	virtual void onRecvFamilyMakeFamily(std::string strTargetNickName, const std::map<eFAMILY_UNIT_TYPE, const std::map<std::string, FamilyUnitInfo> > familyInfoList, std::string strMyNickName, int iParentsCoupleNum, int iMyCoupleNum, bool bParents, eCoupleType eMyCoupleType);

	//! ������ �α⿡ �����ߴ�.
	virtual void onRecvFamilyMakeFamilyFailed(std::string strNickName, eServerResult failedReason);

	//! ������ ���⿡ �����ߴ�.
	virtual void onRecvFamilyDissolveFamily(std::string strTargetNickName, const std::map<eFAMILY_UNIT_TYPE, const std::map<std::string, FamilyUnitInfo> > familyInfoList, std::string strMyNickName, int iParentsCoupleNum, int iMyCoupleNum, bool bParents, eCoupleType eMyCoupleType);

	//! ������ ���⿡ �����ߴ�.
	virtual void onRecvFamilyDissolveFamilyFailed(eServerResult failedReason);

	//////////////////////////////////////////////////////////////////////////
	// ȥ�ڴ޸��� ���� ����...

	/// ������ �����϶�� ����� �޾Ҵ�.
	virtual void onRecvAloneRunStartGameOK(const int numMap);

	/// �׳� ������.
	virtual void onRecvAloneRunGoalInNormal(DWORD dwLapTime);

	/// �̻��� �� Ÿ���̴�. ���ǵ����� ��������...
	virtual void onRecvAloneRunGoalInFailedNotCorrectLapTime();

	/// ��ŷ�� ������ ��ϵǾ� �ִ�.
	virtual void onRecvAloneRunGoalInFailedHackingToolUser();

	// ���ο� �����Ͽ���
	virtual void onRecvAloneRunGameOver();
	// ȥ�ڴ޸��� ���� ��...
	//////////////////////////////////////////////////////////////////////////

	/// ���� ������������ ���� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvChallengeUserMissionInfo(std::map <int,UserChallengeInfo> mUserChallengeInfoList);
	/// ���� �������������� ���Ű���� �޾Ҵ�.(�׷� ����)
	virtual void onRecvChallengeUpdateGroupResult(const int iGroupNum, const int iSubNum, const bool bComplete, const int iAchieveNum, const eRewardCondition iRewardClass);

	/// ������������ ������ �����ߴ�.(�׷� ����)
	virtual void onRecvChallengeUpdateGroupResultDBFailed(const int iGroupNum);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// ���չ̼ǰ���..

	/// ��� �̼� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvMissionInfo(std::vector<MissionInfoForClient>& missionInfo);

	/// ������ �̼� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvMissionUserListOK(const MissionUserInfoMap& missionUserInfo);

	/// ������ �̼� ����Ʈ �ޱ⸦ �����ߴ�.
	virtual void onRecvMissionUserListFailed(const eMissionFailedReason failedReason);

	/// ������ �̼� ����Ʈ�� �̼� �߰��� �����ߴ�.
	virtual void onRecvMissionUserMissionAddOK(const MissionRequestInfo& requestInfo, const time_type& challengeExpireTime);

	/// ������ �̼� ����Ʈ�� �̼� �߰��� �����ߴ�.
	virtual void onRecvMissionUserMissionAddFailed(const MissionRequestInfo& requestInfo, const eMissionFailedReason failedReason);

	/// Ư�� �ð��� ������ ���� �̼� ���� ����Ʈ �߰� ����
	virtual void onRecvMissionUserMissionGroupAddOK(std::vector<MissionRequestDetailInfo>& requestInfo);

	/// Ư�� �ð��� ������ ���� �̼� ���� ����Ʈ �߰� ���� ����
	virtual void onRecvMissionUserMissionGroupAddFailed(const eMissionKind missionKind, const eMissionFailedReason failedReason);

	/// ������ �̼� ����Ʈ�� �̼� ���Ÿ� �����ߴ�.
	virtual void onRecvMissionUserMissionRemoveOK(const MissionRequestInfo& requestInfo);

	/// ������ �̼� ����Ʈ�� �̼� ���Ÿ� �����ߴ�.
	virtual void onRecvMissionUserMissionRemoveFailed(const MissionRequestInfo& requestInfo, const eMissionFailedReason failedReason);

	/// ������ �̼� ����Ʈ ������Ʈ�� �����ߴ�.
	virtual void onRecvMissionUserMissionUpdateOK(const MissionRequestInfo& requestInfo, const MissionConditionAchievedPoint& achievedPoint);

	/// ������ �̼� ����Ʈ ������Ʈ�� �����ߴ�.
	virtual void onRecvMissionUserMissionUpdateFailed(const MissionRequestInfo& requestInfo, const int conditionNum, const eMissionFailedReason failedReason);

	/// ������ �̼��� �Ϸ�Ǿ����� �˸���.
	virtual void onRecvMissionUserMissionCompleteCheckOK(const MissionRequestInfo& requestInfo, const eMissionCompleteType checkTyp);

#ifdef CONTENTS_OPTIONAL_MISSSION
	/// ��ɼ� �̼� ����
	virtual void onRecvMissionUserMissionCompleteCheckOK_For_OptionalMission(const MissionRequestInfo& requestInfo, const eMissionCompleteType completeType, const int completeCount);
#endif

	/// ������ �̼��� �Ϸ���� �ʾ����� �˸���.
	virtual void onRecvMissionUserMissionCompleteCheckFailed(const MissionRequestInfo& requestInfo, const int conditionNum, const eMissionFailedReason& failedReason);

	/// ������ �Ϸ��� �̼��� ���� �ޱ⸦ �����ߴ�.
	virtual void onRecvMissionGiveRewardOK(const std::vector<MissionRequestInfo> vecRequestInfo,const std::vector<RewardInfo>& rewardList);

	/// ������ �Ϸ��� �̼��� ���� �ޱ⸦ �����ߴ�.
	virtual void onRecvMissionGiveRewardFailed(const MissionRequestInfo& requestInfo, const eMissionFailedReason& faliedReason);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! ��� �̼�

	/// ������ ���ԵǾ��ִ� ����� ��� �̼� ����Ʈ�� ���Դ�.
	virtual void onRecvUserGuildMissionListOK(const std::vector<GuildMissionInfoForClient>& guildMisionInfo, std::vector<int>& nextMasterMissionNum);

	/// ������ ���ԵǾ��ִ� ����� ��� �̼� ����Ʈ �޾ƿ��⸦ �����ߴ�.
	virtual void onRecvUserGuildMissionListFailed(const eGuildMissionFailedReason& failedReason);

	/// ��� ������ �̼� ���� ����
	virtual void onRecvGuildMissionSetMasterMissionOK(std::vector<int>& nextMasterMissionList);

	/// ��� ������ �̼� ���� ����
	virtual void onRecvGuildMissionSetMasterMissionFailed(const eGuildMissionFailedReason& failedReason);

	/// Ư�� �ð��� ������ ��� �̼� ���� ����Ʈ ���� ����
	virtual void onRecvGuildMissionUserMissionDeleteNotify(const int notifyType);

	//////////////////////////////////////////////////////////////////////////
	// ���� �̼�

	/// ���� ���� �̼� ����Ʈ�� ���Դ�.
	virtual void onRecvUserOneDayMissionListOK(const std::map<eMissionKind, std::vector<OneDayMissionInfoForClient> >& oneDayMisionInfo, const std::map<eMissionKind, bool>& oneDayMissionBuff);

	/// ���� ���� �̼� ����Ʈ �޾ƿ��⸦ �����ߴ�.
	virtual void onRecvUserOneDayMissionListFailed(const eOneDayMissionFailedReason& failedReason);

	/// ���� ���� �̼� �Ϸ� Ƚ���� ���Դ�.
	virtual void onRecvUserOneDayMissionFinishCountOK(const std::map<eMissionKind, int>& oneDayMissionFinishCount);

	/// ���� ���� �̼� �Ϸ� Ƚ�� �޾ƿ��⸦ �����ߴ�.
	virtual void onRecvUserOneDayMissionFinishCountFailed(const eOneDayMissionFailedReason& failedReason);

	/// �̺�Ʈ �̼� ����.	
	virtual void onRecvOneDayMissionGetEventMissionStatusOK(CMissionEventInfo& missionEventInfo);

	/// �̺�Ʈ �̼� �Ⱓ�� �ƴϴ�
	virtual void onRecvOneDayMissionGetEventMissionStatusFailed(const eMissionFailedReason& failedReason);

	/// Ư�� �ð��� ������ ���� �̼� ���� ����Ʈ ���� ����
	virtual void onRecvOneDayMissionUserMissionDeleteNotify(std::vector<eMissionKind>& missionKindList, const int notifyType);

	//////////////////////////////////////////////////////////////////////////

#ifdef CONTENTS_OPTIONAL_MISSSION
	/// ������ ��ɼ� �̼ǿ� ���� ������ ���� 
	virtual void onRecvOptionalMissionUserInfoOK(std::map<int, OptionalMissionInfoForClient>& userOptionalMissionInfo);

	/// ������ ��ɼ� �̼ǿ� ���� ���� �ޱ⸦ ����
	virtual void onRecvOptionalMissionUserInfoFailed(eOptionalMissionResult result);

	/// ��ɼ� �̼��� �ʱ�ȭ�Ǿ���
#ifdef _EVENTPICKBOARD_
	virtual void onRecvOptionalMissionInit(std::vector<int> initMissionList);
#else
	virtual void onRecvOptionalMissionInit();
#endif

	/// ������ ���� ������ ���� ��û�� ���� ����� ����
	virtual void onRecvLotteryCouponChangeOK(std::vector<RewardInfo>& rewardList, const bool bExchangeMode);

	/// ������ ���� ������ ���� ��û�� ���� ����� ���� ����
	virtual void onRecvLotteryCouponChangeFailed();
#endif

#ifdef COLLECTION_SYSTEM
    /// ���� �ݷ��� �̼� ���� ����Ʈ�� �޾Ҵ�.
    virtual void onRecvUserCollectionMissionListOK(const eCollectionType collectionType, std::vector<CollectionMissionInfoForClient>& collectionUserInfoList);

    /// ���� �ݷ��� �̼� ���� ����Ʈ �ޱ⸦ ����
    virtual void onRecvUserCollectionMissionListFailed(const eMissionFailedReason failedReason);
#endif


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// ����

	/// ���� �̺�Ʈ ���� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvEmblemEventInfo(std::vector<EmblemEventInfo>& emblemEventInfoList);

	/// ���� ���� ���� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvEmblemUserInfoResultOK(std::vector<EmblemUserInfo>& emblemUserInfoList);

	/// ���� ���� ���� ����Ʈ�� �޾ƿ��⸦ �����ߴ�.
	virtual void onRecvEmblemUserInfoResultFailed(eEmblemFailedReason eReason);

	/// ���� ȹ�� ��û�� ���� ����� �޾Ҵ�.
	virtual void onRecvEmblemAquireResultOK(int iEmblemNum);

	/// ���� ȹ�� ��û�� �����ߴ�.
	virtual void onRecvEmblemAquireResultFailed(int iEmblemNum, eEmblemFailedReason eReason);

	/// ���� ������ ȹ�� �̺�Ʈ ����/���Ḧ �˸���.
	virtual void onRecvEmblemFirstComeFirstServerdEventEndNotify(int iEmblemNum, bool bEventStart);

	/// ���� ȹ���� �����Ѵ�.
	virtual void onRecvEmblemAcquisitionNotify(int iEmblemNum, int iRank, const std::string& strNickName);

	/// ȥ���� ���� ȹ�� ������ �г��Ӱ� ������ ��û�� ���� ����� �޾Ҵ�.
	virtual void onRecvChaosEmblemAcquisitionUserListOK(eEmblemType emblemType, std::vector<EmblemAcquisitonUserInfo>& emblemAcquisitionUserInfoList);

	/// ȥ���� ���� ȹ�� ������ �г��Ӱ� ������ ��û�� �����ߴ�.
	virtual void onRecvChaosEmblemAcquisitionUserListFailed(eEmblemFailedReason eReason, eEmblemType emblemType);

	///�̼��� üũ�ϱ����� ������ ����� �غ�Ǿ���.
	virtual void onRecvRoomResultForMissionCheckNotify();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	/// ��� �ý���
	/// ������������� ���´�.
	virtual void onRecvHugSystemGetUserInfoOK();

	/// ������������� �����µ� �����ߴ�.
	virtual void onRecvHugSystemGetUserInfoFailed();

	/// ��������� ��õ�ϱ⸦ �����ߴ�.
	virtual void onRecvHugSystemRecommendUserOK(const std::string & recommendNickName, int iRewardGroupID);

	/// ��������� ��õ�ϱ⸦ �����ߴ�.
	virtual void onRecvHugSystemRecommendUserFailed(std::string& recommenderNickName, eHugSystemFailed recommendUserFailed);

	/// ��� ������ �������� �����ߴ�.
	virtual void onRecvHugSystemLevelUpOK(int iRewardGroupID, short iHugLevel, eHugUserType eUserType);

	/// ��� ������ �������� �����ߴ�.
	virtual void onRecvHugSystemLevelUpFailed(eHugSystemFailed eHugLevelFailed);

	/// ��õ���� ������ �޾Ҵ�.
	virtual void onRecvHugSystemReceiveGiftOK(const std::string& strNickName, int iRewardGroupID);

	/// ��õ���� ������ �ޱ⸦ �����ߴ�.
	virtual void onRecvHugSystemReceiveGiftFailed(eHugSystemFailed failReason);

	/// ����õ�� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvHugSystemGetRecommendUserListOK(const std::vector<RecommendedUserInfo>& recommendedUserInfoList);

	/// ����õ�� ����Ʈ �ޱ⸦ �����ߴ�.
	virtual void onRecvHugSystemGetRecommendUserListFailed(eHugSystemFailed failReason);

	/// ����õ���� �����Ѵ�.
	virtual void onRecvHugSystemRemoveRecommendedUserOK(const std::string& strNickName);

	/// ����õ���� ���ſ� �����ߴ�.
	virtual void onRecvHugSystemRemoveRecommendedUserFailed(eHugSystemFailed failReason);

	/// Ư�� ������ �ű�, ��� ��õ������ ���ŵǾ���.
	virtual void onRecvHugSystemUpdateRecommend(unsigned int numPlayerIndex, bool bIsNotRecommendUser);

	/// ��õ���� ������ ����ũ ������ �� �������� �޾Ҵ�.
	virtual void onRecvHugSystemGetUniqueUserCountOK(short iUniqueUserCount);

	/// ��õ���� ������ ����ũ ������ �� �������� �޴µ� �����ߴ�.
	virtual void onRecvHugSystemGetUniqueUserCountFailed(eHugSystemFailed failReason);

	//////////////////////////////////////////////////////////////////////////

	/// ī���� ����/���� ���� ������ �˸���.
	virtual void onRecvChaosAngelDevilAlchemistOpenNotify();

	//////////////////////////////////////////////////////////////////////////

	/// ���� ���� �б⸦ ��û�� ���� ����� �޾Ҵ�.

	/// ���� ���� ���� �� ������ �˷��ش�.
	virtual void onRecvIndividualGameNodify(const stIndividualRecordGame& stRecordGame);

	/// ���� ���� ��Ÿ ������ �˷��ش�.
	virtual void onRecvIndividualMiscellaneousNodify(const stIndividualRecordMiscellaneous& recordMiscellaneous);

	//////////////////////////////////////////////////////////////////////////
	 
	 //////////////////////////////////////////////////////////////////////////
	 /// ĸ�� �̱��� ���� ��û�� ���� ����� �޾Ҵ�.
	 virtual void onRecvCapsuleMachineGetMachineInfo(CapsuleItemListMap mapMachineInfo, int iMachineNum, eCapsuleMachineKind iMachineKind, int iMachineGroupNum, int iMyPoint, int iUsePoint, int usedCountMax, int usedCount, int luckyCount, bool bIsWinnerParty, bool bIsTodayMachine, bool bIsOlympicGameTime);
#ifdef _VALENTINE
	 virtual void onRecvCapsuleMachineGetMachineInfo(CapsuleItemListMap mapMachineInfo, int iMachineNum, eCapsuleMachineKind iMachineKind, int iMachineGroupNum, int iMyPoint, int iUsingPoint, int usedCountMax, int usedCount, int luckyCount, const SENDER_NICK& sender_nick);
#endif
	 /// ĸ�� �̱��� ���� ��û�� ���� ������ ����� �޾Ҵ�.
	 virtual void onRecvCapsuleMachineGetMachineInfoFailed(int bMachineNum, int iMachineGroupNum,  byte bFailReason);

	 /// ĸ�� ���� ����� �޾Ҵ�.
	 virtual void onRecvCapsuleMachineSelect(int bMachineNum, int itemNum);

	 /// ĸ�� ���� ����� �������̴�.
	 virtual void onRecvCapsuleMachineSelectFailed(int bMachineNum,byte bFailedReason);

	 /// �ű� ���ĸ�� ���� ����� �޾Ҵ�.
	 virtual void onRecvCapsuleMachineSelectEx(int bMachineNum, int itemNum);

	 /// �ű� ���ĸ�� ���� ����� �������̴�.
	 virtual void onRecvCapsuleMachineSelectExFailed(int bMachineNum, eCapsuleMachine_FAILED_REASON eFail);

	 /// ĸ�� ���� �������� ���޿�û�� ���� ������ �޾Ҵ�.
	 virtual void onRecvCapsuleMachineGive(int itemNum);

	 /// ĸ�� ���� ������ ���� �����Ͽ���.
	 virtual void onRecvCapsuleMachineGiveFailed(byte failedReason);

	 /// ĸ�� ���� ����� �����Ѵ�.
	 virtual void onRecvCapsuleMachineNotify(byte type, int bMachineNum, int itemNum, std::string nickname, ePieroOlympicPartyType ePartyType);

#ifdef _AUCTION_SYSTEM_
	 /// ��� �ý��� ������ �޾Ҵ�
	 virtual void onRecvAuctionSchedule(int iAuctionNum, time_type tSDate, time_type tEDate, eAuctionState	auctionState);

	 /// ��� �ý��� �����Ӵ� �޾Ҵ�
	 virtual void onRecvAuctionCermony(int iItemNum, std::string & sBeforeNickName, std::string & sNextNickName, int iBeforeTR, int iNextTR);

	 /// ��� �ý��� ����Ʈ �޾Ҵ�.
	 virtual void onRecvAuctionListOK(eAuctionKind auctionKind, int iAuctionNum, time_type tSDate, time_type tEDate, std::map<int, AuctionLIst> & mapAuctionList, int iTotalCount);
	 virtual void onRecvAuctionListFailed(const DWORD & dwResult);

	 /// ��� �ý��� ��ǰ��� ����� �޾Ҵ�.
	 virtual void onRecvAuctionRegisterOK(const DWORD & dwResult, INT64 iStorageNum);
	 virtual void onRecvAuctionRegisterFailed(const DWORD & dwResult);

	 /// ��� �ý��� ��ǰ üũ ����� �޾Ҵ�.
	 virtual void onRecvAuctionRegisterItemCheckOK(int iPrice);
	 virtual void onRecvAuctionRegisterItemCheckFailed(const DWORD & dwResult);

	 /// ��� �ý��� ���� ��ǰ��� ���� �޾Ҵ�.
	 virtual void onRecvAuctionRegisterListOK(std::vector<std::pair<int,int> > & vecList);
	 virtual void onRecvAuctionRegisterListFailed(const DWORD & dwResult);

	 /// ��� �ý��� ���� ����� �޾Ҵ�..
	 virtual void onRecvAuctionTenderOK(const DWORD & dwResult);
	 virtual void onRecvAuctionTenderChangePrice(const DWORD & dwResult, int iPrice);
	 virtual void onRecvAuctionTenderFailed(const DWORD & dwResult);

	 /// ��� �ý��� ���� ���� ���� �޾Ҵ�.
	 virtual void onRecvAuctionMyTenderListOK(std::vector<std::pair<int,int> > & vecList);
	 virtual void onRecvAuctionMyTenderListFailed(const DWORD & dwResult);

	 /// ��� �ý��� ���� ���� ���� �޾Ҵ�.
	 virtual void onRecvAuctionHistoryInfoOK(std::vector<std::pair<int,std::string> > & vecList, std::string & sMaxTR_NickName, int iMaxTR, int iMaxCountTR, int iMaxCount);
	 virtual void onRecvAuctionHistoryInfoFailed(const DWORD & dwResult);

	 /// ��� �ý��� �ְ� �������� �޾Ҵ�.
	 virtual void onRecvAuctionTenderPriceOK(eAuctionKind auctionKind, int iAuctionNum, int iMaxPrice);
	 virtual void onRecvAuctionTenderPriceFailed(const DWORD & dwResult);

	 /// ��� �ý��� ���� ����Ƚ���� �޾Ҵ�.
	 virtual void onRecvAuctionTenderCountOK(int iAuctionNum, int iCount);
	 virtual void onRecvAuctionTenderCountFailed(const DWORD & dwResult);
#endif

#ifdef ENTRY_SYSTEM
	 //////////////////////////////////////////////////////////////////////////
	 /// ���� �ý��� ����Ⱓ ������ �޾Ҵ�.
	 virtual void onRecvEntrySystemPeriodSchedule(eEntrySystemShopType shopType, bool bOpen, time_type tOpenTime, time_type tCloseTime, int iScheduleNum);

	 /// ���� �ý��� ���� ������ �޾Ҵ�
	 virtual void onRecvEntrySystemShopSchedule(eEntrySystemShopType shopType, bool bReset, time_type tOpenTime);

	 /// ���� �ý��� ���� �޾Ҵ�
	 virtual void onRecvEntrySystemGetMachineInfo(int iScheduleNum, eEntrySystemShopType shopType, int iCategoryNum, EntrySystemListMap& mapSystemList);

	 /// ���� �ý��� ������ ������ ����� �޾Ҵ�.
	 virtual void onRecvEntrySystemGetMachineInfoFailed(eEntrySystemShopType shopType, int iCategoryNum, byte bFailReason);

	 /// ���� �ý��� ���� ����� �޾Ҵ�.
	 virtual void onRecvEntrySystemSelect(int iUniqueNum, bool bSucess, int itemNum);

	 /// ���� �ý��� ���� ����� �������̴�.
	 virtual void onRecvEntrySystemSelectFailed(int iUniqueNum, byte bFailedReason);

	 /// ���� ���� �������� ���޿�û�� ���� ������ �޾Ҵ�.
	 virtual void onRecvEntrySystemGive(int itemNum);

	 /// ���� ���� ������ ���� �����Ͽ���.
	 virtual void onRecvEntrySystemGiveFailed(byte failedReason);

	 /// ���� �ý��� ��÷ ��� ����Ʈ�� �޾Ҵ�.
	 virtual void onRecvEntrySystemResult(eEntrySystemShopType shopType, int iTotalCount, unsigned short numPage, std::vector<EntrySystemResultInfo>& vEntrySystemResult);

	 /// ���� �ý��� ��÷ ��� ����Ʈ�� �ޱ� �����ߴ�.
	 virtual void onRecvEntrySystemResultDBFailed();

	 /// ���� �ý��� ��÷ ����� �޾Ҵ�.
	 virtual void onRecvEntrySystemResultView(int iScheduleNum, int iSelectNum, int iUniqueNum, bool bSucess, bool bUse, int itemNum);

	 /// ���� �ý��� ��÷ ����� �������̴�.
	 virtual void onRecvEntrySystemResultViewFailed(byte bFailedReason);

#endif

	 //////////////////////////////////////////////////////////////////////////

	/// ����Ű ī�� �̺�Ʈ ���� ���� ����� �޾Ҵ�.
	virtual void onRecvApplyEventResult(const int iEventNum, const int iTotalCardAmount, const bool bSuccess);

	/// ����Ű ī�� �̺�Ʈ ���� ���� ����� �޾Ҵ�.(DB error)
	virtual void onRecvApplyEventResultDBFailed();
	
	/// ���� ����� �̺�Ʈ ���� ���� ����� �޾Ҵ�.(������ ���)
	virtual void onRecvApplyEventTicketResult(const int iEventNum, std::map<int, int> & mApplyInfoList, const bool bSuccess);

	/// ���� ����� �̺�Ʈ ���� ���� ����� �޾Ҵ�.(DB error)
	virtual void onRecvApplyEventTicketResultDBFailed();

	/// ������ - TR ��ȯ ��û�� ���� ����� �޾Ҵ�.
	virtual void onRecvExchangeItemToTRResult(const int iItemNum, const int iRewardTR, const int iCount);

	/// ������ - TR ��ȯ ��û�� ���� ����� �޾Ҵ�.(DB Error)
	virtual void onRecvExchangeItemToTRResultFailed();

	/// ���۹� ��Ȯ �������� �����û�� ���� ��� ����
	virtual void onRecvFarmHarvestItemExchangeReward(const int iItemNum, const int iCount, std::vector<RewardInfo>& rewardList);

	/// ���۹� ��Ȯ �������� �����û�� �����ߴ�
	virtual void onRecvFarmHarvestItemExchangeRewardFailed();

	/// ���ο� �� ����� �޾Ҵ�. 
	virtual void onRecvFarmList(eFarmListKind farmListKind, const std::vector < CFarmListData > & farmList, const std::vector < unsigned int > & notExistFarmRoomList, unsigned int thisPageIndex, unsigned int numFarmListPageCount ); 

	/// ���ο� �� ����� �޾Ҵ�.
	virtual void onRecvRoomList(eRoomKind roomKind, const std::vector < CRoomListData > & roomList, unsigned int numRoomListPage, unsigned int numRoomListPageCount);

	/// �� ����Ⱑ �����ߴ�.
	virtual void onRecvMakeRoomFail(eMakeRoomFail makeRoomFail, unsigned int hRoom);

	/// �� ������ �����ߴ�.
	virtual void onRecvEnterRoomFailed(eEnterRoomResult enterRoomResult, const eRoomKind roomKind, const int numMaxPlayer, const int restrictTime);

	/// ������ ����� �޾Ҵ�.
	virtual void onRecvGetAvatarItemList(const cpk_type character, const std::vector < NetItemInfo > & ItemList);

	/// ������ ����� �޾Ҵ�.
	virtual void onRecvGetAvatarItemList(const cpk_type character, const int iPosition, const std::vector < NetItemInfo > & ItemList);

	/// ������ ��� �ޱ� ����
	virtual void onRecvGetAvatarItemsFailed();

	/// Ư�� �������� ������ �޾Ҵ�.
	virtual void onRecvGetAvatarItemInfo(const NetItemInfo & ItemInfo);

	/// Ư�� �������� ������ �ޱ� �����ߴ�.
	virtual void onRecvGetAvatarItemInfoFailed();

	/// Ư�� �����۵��� ������ �޾Ҵ�.(ĳ���� �� ī�� �������� �����Ѵ�..)
	virtual void onRecvGetAvatarItemInfoList(const std::vector<NetItemInfo>& iteminfoList);

	/// �������� ������ �޾Ҵ�.
	virtual void onRecvGetRemainCountAvatarItem(const int itemDescNum, time_type expireTime, int remainCount);

	/// �������� ������ ���� ���ߴ�.
	virtual void onRecvGetRemainCountAvatarItemFailed(eServerResult eResult, const int itemDescNum);

	/// ���̷� �������� ����Ͽ���.
	virtual void onRecvMyRoomUseItem(eServerResult eResult, const int iItemNum, const int iItemRemainCount );

	/// ��Ÿ���� �ִ� �������� ����ߴ�.
	virtual void onRecvUseItemEx(eServerResult eResult, int iItemDescNum, int iItemRemainCount, time_type tNextUsableTime);

	/// Ư�� ������ Ư�� �������� ����ߴ�.
	virtual void onRecvRoomUseItemNotify(BYTE iUserGameIndex, BYTE iTargetGameIndex, int iItemDescNum);

	/// �˸��ٹ� ù ������ ������ ��û�� �޾Ҵ�.
	virtual void onRecvAlibabaOpenGate(DWORD dwGameTime){}

	/// �� �̺�Ʈ �߻� ������ �޾Ҵ�.
	virtual void onRecvMapEvent(eMapEventType byEventType, DWORD dwEventTime);

	/// ���� �ø��� ���������� �޾Ҵ�..
	virtual void onRecvNextOlympicGameInfo(const OlympicGameInfo & gameInfo);

	/// ���� �ø��� ���� ���� ������ �޾Ҵ�..
	virtual void onRecvNextOlympicGameNoticeInfo(const OlympicGameInfo & gameInfo);


	//////////////////////////////////////////////////////////////////////////
	// �߿��� �ø���

	/// ���� �߿��� �ø��� ��� ������ �޾Ҵ�.
	virtual void onRecvNextPieroOlympicGameNoticeInfo(const std::vector<OlympicGameInfo>& pieroOlympicGameInfoList);

	//!< ���� �߿��� �ø��� ���� ���� ���� ������ �޾Ҵ�.
	virtual void onRecvPieroOlympicNextGameStartScheduleNotice(const OlympicGameInfo & gameInfo);

	//!< ���� �߿��� �ø��� ���� ���� ���� ������ �޾Ҵ�.
	virtual void onRecvPieroOlympicThisGameFinishScheduleNotice(const OlympicGameInfo & gameInfo);

	//!< ���� �߿��� �ø��� ���� ���� ������ �޾Ҵ�. (�¸���)
	virtual void onRecvPieroOlympicThisGameFinisheNotice(ePieroOlympicPartyType winnerParty);

	//!< ���� �߿��� �ø��� ���� �̿밡���� �� ������ �޾Ҵ�.(�����̿밡�� ���� ��)
	virtual void onRecvPieroOlympicShopUsablePartyNotice(const std::vector<ePieroOlympicPartyType>& partyTypeList);

	//!< ���� �߿��� �ø��� ������ ��� ������ �����ϱ���� ���� �ð��� ���� �޾Ҵ�.
	virtual void onRecvPieroOlympicShopUsablePartyRemainTimeNotice(const time_type remainTime);

	//!< �߿��� ���� ������ EXP ���ʽ� ������ �޾Ҵ�.
	virtual void onRecvPieroOlympicPieroAlchemistItemEXPBonusNotice(const std::map<ePieroOlympicPartyType, int>& PieroOlympicEXPBonusMap);

	//!< New �߿��� �巡�� ���� EXP���ʽ� ������ �޾Ҵ�.
	virtual void onRecvPieroOlympicDragonEXPBonusNotice(int iEXPBonus);

	//!< �߿��ι� TR,EXP ���ʽ� ������ �޾Ҵ�.
	virtual void onRecvPieroOlympicPieroBonusNotice(std::map<ePieroOlympicPartyType, BuffBonusInfo> pieroOlympicPieroBonusMap);

	/// ���� �߿��� �ø��� ������ ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetMyPieroOlympicInfoOK(const PieroOlympicUserInfo& pieroOlympicUserInfo);

	/// ���� �߿��� �ø��� ������ ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetMyPieroOlympicInfoFailed(ePieroOlympicFailedReason failedReason);

	/// ���� �߿��� �ø��� �⿩����Ʈ ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetMyContributionPointOK(int iContributionPoint, int iAccumulationPoint);

	/// ���� �߿��� �ø��� �⿩����Ʈ ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetMyContributionPointFailed(ePieroOlympicFailedReason failedReason);

	/// ������ ��������Ʈ�� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetThisSeasonGrowthPointOK(const std::vector<PieroOlympicPartyInfo>& todaysGrowthPointList);

	/// ������ ��������Ʈ�� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetThisSeasonGrowthPointFailed(ePieroOlympicFailedReason failedReason);

	/// ��ü ��������Ʈ�� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetTotalGrowthPointOK(const std::vector<PieroOlympicPartyInfo>& totalGrowthPointList);

	/// ��ü ��������Ʈ�� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetTotalGrowthPointFailed(ePieroOlympicFailedReason failedReason);

	/// ���� ��������Ʈ�� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetInterruptGrowthPointOK(const std::vector<PieroOlympicInterruptGrowthInfo>& interruptGrowthPointList);

	/// ���� ��������Ʈ�� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetInterruptGrowthPointFailed(ePieroOlympicFailedReason failedReason);

	/// �߿��� ������ ������ ������ ���� �������� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGiveLevelUpRewardOK(int iRewardItemNum);

	/// �߿��� ������ ������ ������ ���� �������� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGiveLevelUpRewardFailed(ePieroOlympicFailedReason failedReason);

	/// �߿��� �ø��� �� ���� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicJoinPartyOK(ePieroOlympicPartyType ePartyType, int iRewardItemNum);

	/// �߿��� �ø��� �� ���� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicJoinPartyFailed(ePieroOlympicFailedReason eFailedReason);

	/// �߿��� �ø��� �� ���� ���� �����ߴ�.
	virtual void onRecvPieroOlympicJoinPartyPurposeInfoOK(ePieroOlympicPartyType ePartyType, int iRewardItemNum);

	/// �߿��� �ø��� �� ���� ���� �����ߴ�.
	virtual void onRecvPieroOlympicJoinPartyPurposeInfoFailed(ePieroOlympicFailedReason eFailedReason);

	/// �߿��� �������� ������ ���Ž� ���� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicShopBuyItemOK(const std::vector<PieroOlympicShopInfo>& shopInfo);

	/// �߿��� �������� ������ ���Ž� ���� ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicShopBuyItemFailed(ePieroOlympicShopFailedReason failedReason, int iItemNum);

	/// �߿��� �������� �Ǹ��ϴ� �����۸���Ʈ ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetShopInfoOK(const std::vector<PieroOlympicShopInfo>& itemList, const std::vector<ePieroOlympicPartyType>& partyList, const bool bActiveShop, const bool bShopUsableWinnerParty);

	/// �߿��� �������� �Ǹ��ϴ� �����۸���Ʈ ��û�� �����ߴ�.
	virtual void onRecvPieroOlympicGetShopInfoFailed();

	/// ���� �� ������ �޾Ҵ�.
	virtual void onRecvPieroOlympicGetCompetitionTeamInfo(eCompetitionRule rule, const std::vector<ePieroOlympicPartyType>& teamInfo);

	/// ���� ������ �޾Ҵ�.
	virtual void onRecvCompetitionInfoOK();

	///////////////////////////////////////////////////////////////////////////
	/// Ƽ�� ��Ż��

	///Ƽ�� ��Ż�� �������� �޾Ҵ�.
	virtual void onRecvTicketScrambleJoinPartyOK(ePieroOlympicPartyType ePartyType);

	///Ƽ�� ��Ż�� �����Կ� �����ߴ�.
	virtual void onRecvTicketScrambleJoinPartyFailed(ePieroOlympicFailedReason failedReason);

	///Ƽ�� ��Ż�� ������ �޾Ҵ�.
	virtual void onRecvTicketScrambleGetInfoOK(const TicketScrambleInfo& ticketScrambleInfo);

	///Ƽ�� ��Ż�� ���� ��û�� �����ߴ�.
	virtual void onRecvTicketScrambleGetInfoFailed();

	///Ƽ�� ������ �޾Ҵ�.
	virtual void onRecvTicketScrambleRechargeTicketOK(int iTicketCount);

	///Ƽ�� ������ �����ߴ�.
	virtual void onRecvTicketScrambleRechargeTicketFailed();

	///Ƽ�� ��Ż�� ��� ����������� �޾Ҵ�.
	virtual void onRecvTicketScrambleResultReward(const RewardInfo & rewardInfo);

	//Ƽ�� ��Ż�� ���� �ʱ�ȭ�� �޾Ҵ�.
	virtual void onRecvTicketScrambleInitInfo();

	///////////////////////////////////////////////////////////////////////////
	/// ���׸�2
#ifdef _RUNNING_MAN2

	/// ���� ���׸�2 ��� ������ �޾Ҵ�.
	virtual void onRecvNextRunningMan2GameNoticeInfo(const std::vector<OlympicGameInfo>& gameInfoList);

	///���׸�2 �������� �޾Ҵ�.
	virtual void onRecvRunningMan2JoinPartyOK(ePieroOlympicPartyType ePartyType);

	///���׸�2 �����Կ� �����ߴ�.
	virtual void onRecvRunningMan2JoinPartyFailed(ePieroOlympicFailedReason failedReason);

	///���׸�2 ������ �޾Ҵ�.
	virtual void onRecvRunningMan2GetInfoOK(const TicketScrambleInfo& ticketScrambleInfo);

	///���׸�2 ���� ��û�� �����ߴ�.
	virtual void onRecvRunningMan2GetInfoFailed();

	///���׸�2 Ƽ�� ������ �޾Ҵ�.
	virtual void onRecvRunningMan2RechargeTicketOK(const TicketScrambleInfo& ticketScrambleInfo);

	///���׸�2 Ƽ�� ������ �����ߴ�.
	virtual void onRecvRunningMan2RechargeTicketFailed();

	///���׸�2 ��� ����������� �޾Ҵ�.
	virtual void onRecvRunningMan2ResultReward(const RewardInfo & rewardInfo);

	///���׸�2 ���� �ʱ�ȭ�� �޾Ҵ�.
	virtual void onRecvRunningMan2InitInfo();

	/// ���׸�2 �������� ������ ���Ž� ���� ��û�� �����ߴ�.
	virtual void onRecvRunningMan2ShopBuyItemOK(int iItemNum, const std::vector<PieroOlympicShopInfo>& shopInfo);

	/// ���׸�2 �������� ������ ���Ž� ���� ��û�� �����ߴ�.
	virtual void onRecvRunningMan2ShopBuyItemFailed(ePieroOlympicShopFailedReason failedReason, int iItemNum);

	/// ���׸�2 ���� ���� ��û�� �����ߴ�.
	virtual void onRecvRunningMan2GetShopInfoOK(const std::vector<PieroOlympicShopInfo>& shoInfo);

	/// ���׸�2 ���� ���� ��û�� �����ߴ�.
	virtual void onRecvRunningMan2GetShopInfoFailed();

#endif	// _RUNNING_MAN2

	//////////////////////////////////////////////////////////////////////////
	// ���� �޸��� ��� ����

	/// ������ ������ Ŭ������ �ʷ� ������ �޾Ҵ�.
	virtual void onRecvCorunModeGetUserLastClearedMapRuleInfoOK();

	/// ������ ������ Ŭ������ �ʷ� ���� �ޱ⸦ �����ߴ�.
	virtual void onRecvCorunModeGetUserLastClearedMapRuleInfoFailed(eCorunModeFailedReason eFailedReason);

	/// ������ ������ Ŭ������ �ʷ� ������ ������Ʈ�Ǿ���.
	virtual void onRecvCorunModeUpdateUserLastClearedMapRuleInfo();

	/// ���� ���� �ְ� ����� �޾Ҵ�. (���� �޸��� ��忡�� ������ ���� �ε� ������ ��û�ϸ� �������� ������)
	virtual void onRecvCorunModeTopRecord(eCorunModeRank eRank, int iClearTime, std::vector<std::string> &vecUserNickname);

	/// �ð��� ��� ������ Ŭ���� ���� �ð��� �����ض�.
	virtual void onRecvCorunModeSetClearLimitTime(int iClearLimitTime);

	/// �� �̺�Ʈ�� �߻��ߴ�.
	virtual void onRecvCorunModeTriggerMapEvent(BYTE byEventNum, int iEventLapTime);

	/// ������Ʈ �̺�Ʈ�� �߻��ߴ�.
	virtual void onRecvCorunModeTriggerObjectEvent(int iObjectIndex, eCorunModeObjectEventType eEventType,unsigned int iValue);

	// ������Ʈ ���� üũ �� �̺�Ʈ�� �߻��Ѵ�.
	virtual void onRecvCorunModeTriggerCheckInObjectEvent(const BYTE numGameIndex, int iObjectIndex, int iLockIndex, eCorunModeObjectEventType eEventType,unsigned int iValue);

	/// ��ź ��ġ ��� �̺�Ʈ�� �߻��ߴ�.
	virtual void onRecvCorunModeTriggerBombMotionEvent(byte byEventNum, byte byManagerIndex, byte byGeneratorIndex, byte byObjectIndex);
	/// �ð��� �帣�� ������ ������ �����ߴ�.
	virtual void onRecvCorunModeEnterTimeSection(BYTE bySectionNum, int iClearLimitTime, int iBonusTime);

	/// �ð��� �帣�� ������ ������ ������ Ŭ�����ߴ�.
	virtual void onRecvCorunModeClearTimeSection(BYTE bySectionNum, int iClearTime, int iBonusTime);

	/// ���� �������� �����ߴ�.
	virtual void onRecvCorunModeSetBossEnergyOK(int iObjectIndex);

	/// ���� ������ ������ �����ߴ�.
	virtual void onRecvCorunModeSetBossEnergyFailed(eCorunModeFailedReason eFailedReason);

	/// ���� �������� �����ߴ�.
	virtual void onRecvCorunModeDecreaseBossEnergy(int iBossEnergy, int iObjectIndex);

	/// ������Ʈ ���� �������� �����ߴ�.
	virtual void onRecvCorunModeSetObjectBossEnergyOK(int iObjectType, int iObjectIndex, int iValue);

	/// ������Ʈ ���� ������ ������ �����ߴ�.
	virtual void onRecvCorunModeSetObjectBossEnergyFailed(int iObjectType, int iObjectIndex, int iValue, eCorunModeFailedReason eFailedReason);

	/// ������Ʈ ���� �������� �����ߴ�.
	virtual void onRecvCorunModeDecreaseObjectBossEnergy(int iObjectType, int iObjectIndex, int iValue, int iBossEnergy);

	/// ������Ʈ ���� �������� �������״�.
	virtual void onRecvCorunModeIncreaseObjectBossEnergy(int iObjectType, int iObjectIndex, int iValue, int iBossEnergy);

#ifdef _SHOP_RENEWAL_
	//////////////////////////////////////////////////////////////////////////
	// ���� ������

	/// ���� ī�װ��� �޾Ҵ�
	virtual void onRecvShopCategoryACK(std::vector < ShopCategory > & vecCategory, std::multimap<int, ShopCategoryPurchasing > & mapShopCategoryPurchasing);
	virtual void onRecvShopCategoryFailed(eServerResult dwResult);

	/// ���� ���� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvShopDisplayLIstACK(SHOP_DISPLAY_LIST & list);
	virtual void onRecvShopItemSellLIstACK(std::multimap<int, ShopItemSellList > & list);
	virtual void onRecvShopDisplayDateLIstACK(SHOP_DISPLAY_DATE_LIST & list);
	virtual void onRecvShopBuyLimitCountLIstACK(SHOP_BUY_LIMIT_COUNT_LIST & list);
	virtual void onRecvShopBuyAddBenefitLIstACK(SHOP_BUY_ADD_BENEFIT_LIST & list);
	virtual void onRecvShopBuyAddSellPriceLIstACK(SHOP_BUY_ADD_SELL_PRICE_LIST & list);
	virtual void onRecvShopDisplayLIstFailed(eServerResult dwResult);

	/// ���� ���� ����Ʈ ���ε� ������ �޾Ҵ�.
	virtual void onRecvShopDisplayReloadNotify();

	/// ������ VIP ���� ���� ������ �޾Ҵ�.
	virtual void onRecvShopVipLevelNotify(const int iVipLevel);

	/// ������ VIP ���� ���� ���� ������ �޾Ҵ�.
	virtual void onRecvShopVipLevelResetNotify();

	/// ���� ��ũ �ʱ�ȭ ������ �޾Ҵ�.
	virtual void onRecvShopRanklResetNotify();

	/// ���� ����Ƚ�� ���� ������ �޾Ҵ�.
	virtual void onRecvShopBuyCountResetNotify();

	/// ���� ����Ƚ�� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvShopUserBuyCountLIstACK(SHOP_BUY_LIMIT_COUNT_LIST & list, std::map<int, int> & sellList);
	virtual void onRecvShopUserBuyCountLIstFailed(eServerResult dwResult);

	/// ���� ����Ƚ�� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvShopBuyCountLIstACK(std::map<int, int> & sellList);
	virtual void onRecvShopBuyCountLIstFailed(eServerResult dwResult);

	// ���� ��ũ ����Ʈ�� �޾Ҵ�.
	virtual void onRecvShopRankACK(int iCategory1, int iCategory2, int iCategory3, std::map<int, int> & list);
	virtual void onRecvShopRankFailed(eServerResult dwResult);

	// ���� �� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvShopUserWishLIstACK(std::map<int, time_type> & list);
	virtual void onRecvShopUserWishLIstFailed(eServerResult dwResult);

	// ���� �� ����Ʈ�� ��� ����� �޾Ҵ�.
	virtual void onRecvShopSetUserWishLIstACK(eShopWishListType wishType, int iDisplayNum);
	virtual void onRecvShopSetUserWishLIstFailed(eServerResult dwResult) ;

#endif
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	/// ���� ���� ����

	/// ���� TR �� �޾Ҵ�.
	virtual void onRecvCurrentGameMoney(const int iGameMoney);

	//! ���ݼ��翡�� ������ ���ظ� �Ѵ�.
	virtual void onRecvAlchemistDisjoint(eServerResult eResult,const int iItemDescNum);

	//! ���ݼ��� ������ �����ϰڴ�.
	virtual void onRecvAlchemistMixBegin(eServerResult eResult);

	/// ���ݼ��� ������ �����ߴ�.
	virtual void onRecvAlchemistMixEndOK(const UserItemAttrInfo& itemInfo);

	/// ���ݼ��� ������ ����
	virtual void onRecvAlchemistMixEndFailed(eAlchemistMixFailedReason reason);

	/// ���� �������� ��� ��þƮ�� �����ߴ�.
	virtual void onRecvAlchemistEnchantGradeOK(const UserItemAttrInfo& itemInfo, bool bSuccess);

	/// ���� �������� ��� ��þƮ�� �����ߴ�.
	virtual void onRecvAlchemistEnchantGradeFailed(eAlchemistEnchantGradeFailedReason reason);

	/// ������ ���� ������ �ð� ��û�� �����ߴ�.
	virtual void onRecvItemManufactureCoolTimeOK(int iManufactureNum, time_type tAlchemistCoolTime);

	/// ������ ���� ������ �ð� ��û�� �����ߴ�.
	virtual void onRecvItemManufactureCoolTimeFailed(int iManufactureNum);

	/// ������ ���� ��û�� �����ߴ�.
	virtual void onRecvItemManufactureMakeOK(int iManufactureNum);

	/// ������ ���� ��û�� �����ߴ�.
	virtual void onRecvItemManufactureMakeFailed(int iManufactureNum, eItemManufactureFailedReason reason);

	/// ȥ���� �ϼ�ü ���ʽ� ������ �޾Ҵ�.
	virtual	void onRecvChaosCompletionUnitBonus(const BuffBonusInfo& bonusInfo);

	/// �߿��� ���� ���ʽ� ������ �޾Ҵ�.
	virtual	void onRecvPieroJoinBuffBonus(const BuffBonusInfo& bonusInfo);

	/// �� �濡 �ִ� ���� ��� ������ �ְ� ����ġ ������ ���� ������ �޾Ҵ�.
	virtual void onRecvSortedHeroClassGameIndices(const std::vector<BYTE>& heroClassGameIndices);

	/// ���� ��� ���ʽ� ���� ������ �޾Ҵ�.
	virtual void onRecvHeroClassBuffBonusNotify(const BuffBonusInfo& bonusInfo);

	/// ��� ���ʽ� ������ �޾Ҵ�.
	virtual	void onRecvGuildUnitNotice(const BuffBonusInfo& bonusInfo);

	/// �巡�� ��Ʈ ���ʽ� ������ �޾Ҵ�.
	virtual void onRecvDragonAlchemistUnitBouns(const DragonAlchemistItemBonus& bonusInfo);

	/// �����̾� ���� ���ʽ� ������ �޾Ҵ�.
	virtual	void onRecvSuperRoomMasterInfo(const SuperRoomMasterInfo& bonusInfo);

	/// ����� ���� ���� ������ �޾Ҵ�
	virtual void onRecvSpecialGameRewardNotify(JackPotReward& rewardInfo);

	/// ������ �����ִ�. ������ ���Ḧ ����ϰų�, ���� ���̴�.
	virtual void onRecvShopClosed();

	/// �������� ���� ��°��� �����ߴ�.
	//virtual void onRecvShopBuyProductItemDescNum(const int iItemDescNum, const int m_iGameMoney);

	/// �������� ���ǵ� ���� ���� ��°��� �����ߴ�.
	virtual void onRecvShopBuyProductsTogetherSuccess(const std::vector <BuyingItemInfo> & successItemList, const std::map<__int64,int>& mapItemID, const std::map<int, int> & soldOutItemDesc, const std::vector<int>& discountCouponList);

	/// �������� ���ǵ� ������� ��� ���� �����ߴ�.
	virtual void onRecvShopBuyProductsTogetherFailed(const eShopFailed_REASON failedReason, const std::vector < BuyingItemInfo > & successItemList, const std::vector < BuyingItemInfo > & failedItemList, const std::map<__int64,int>& mapItemID, const std::map<int, int> & soldOutItemDesc);		//!< �Ǽ��縮 ���� ����

	/// ���� ������ ������ �޾Ҵ�.
	virtual void onRecvBillingError(eBillingError billingError);

	//////////////////////////////////////////////////////////////////////////

	/// �г��� �˻� ����
	virtual void onRecvSearchNickNameOK(const std::string & strSearchNickname);
	
	/// ���� ������ ���� ����
	virtual void onRecvMessageSendOK(MessageSystemInfo & messageInfo);

	/// App���� ���� ������ ���� ����
	virtual void onRecvMessageAppSendOK(std::vector<MessageSystemInfo>& messageInfo);

	/// ������ üũ�϶�� �޾Ҵ�.
	virtual void onRecvCheckMessage(MessageSystemInfo & messageInfo);
	virtual void onRecvCheckMessage(const std::map <__int64, MessageSystemInfo >& newArrivalMessageList);

	/// ������ ����� �޾Ҵ�
	virtual void onRecvMessageBoxList(const eMessageBoxType & messageBoxType, const unsigned short numPage, const unsigned short totalCount, const std::map <__int64, MessageSystemInfo > & messageMap);
	
	/// ���� �б� ����.
	virtual void onRecvReadMessageOK(const __int64 iMessageNum);

	/// ���� �Ű� ����.
	virtual void onRecvAccuseMessageOK(const __int64 iMessageNum);

	/// ���� ���� ����.
	virtual void onRecvDeleteMessageOK(const eMessageBoxType & messageBoxType, const bool isAll, std::vector<__int64>& vecMessageNum);

	/// ���� ���� ����.
	virtual void onRecvKeepMessageOK(const __int64 iMessageNum);

	/// ģ�� �߰��� ���� Ƚ��
	virtual void onRecvGetFriendAddFriendOK();

	/// ���� ���� ����
	virtual void onRecvMessageFailed(const eMessageBoxFailed failedReason);

	/// ���� �ɼ� �б�.
	virtual void onRecvGetMessageOptionOK(const eMessageBoxOption & messageOption);

	//////////////////////////////////////////////////////////////////////////

	/// ���� ������ ���� ����
	virtual void onRecvGiftProductOK(const int iItemDescNum, const int iGameMoney);

	/// ���� ������ ���� ����
	virtual void onRecvGiftProductFailed(const eGiftItemFailed failedReason);

	/// ������ üũ�϶�� �޾Ҵ�.
	virtual void onRecvCheckGift(const std::vector<eNewGiftMessagType>& msgList);

	/// �������� �ޱ� ��� ���� ���� ����� �޾Ҵ�.
	virtual void onRecvAcceptWaitGiftList(const unsigned short numPage,const unsigned short ItemCountPerPage, const std::vector < AcceptWaitItem > & v,int iTotalCount);

	/// �������� �ޱ� ��� ���� ���� ����� �޴µ� ����
	virtual void onRecvAcceptWaitGiftListFailed();

	/// �������� ��� ���� ������ �޾���.
	virtual void onRecvAcceptGiftOK(std::vector<int> vecGiftNum);

	/// �������� ��� ���� ������ �޴µ� ����
	virtual void onRecvAcceptGiftFailed(const eGiftAcceptFailedReason failedReason);

	/// ���� ���� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvAcceptedGiftList(const std::vector < AcceptedGift > & v) {}

	/// ���� ���� ����Ʈ�� �޴µ� �����ߴ�.
	virtual void onRecvAcceptedGiftListFailed() {}

	/// �������� ĳ�ø� �޾Ҵ�.
	virtual void onRecvShopCash(int iCash);

	/// �������� ĳ�ø� �޴µ� �����ߴ�.
	virtual void onRecvShopCashFailed();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//!< �Ƹ��� ���� ���� �̺�Ʈ �ڵ鷯. 

	/// ��ȭ ������ ����� ���������� �޾Ҵ�. 
	virtual void onRecvStrengthenItemListOK(const std::vector<CStrengthenItemDesc> & strengthens); 

	/// ��ȭ ������ ����� �޴� ���� ���� �߻�.
	virtual void onRecvStrengthenItemListFailed(eStrengthenItemListFailedReason failedReason);

	/// ������ ��ȭ�� �����ߴ�. 
	virtual void onRecvReInforceItemOK(const eStrengthenReInforceResponse response, const int & reInforcedItemNum, const unsigned short & reInforcedSlotIndex, const int & remainGameMoney, const int & remainReInforceCnt);	

	/// ������ ��ȭ�� �����ߴ�. 
	virtual void onRecvReInforceItemFailed(const eStrengthenReInforceFailedReason & failedReason, const int & reInforceItemNum, const unsigned short & reInforceSlotIdx); 

	/// ������ ��ȭ�� �����ߴ�. 
	virtual void onRecvPurifyItemOK(const int & purifiedItemNum, const unsigned short & purifySlotIndex, const int & usedItemDescNum, const unsigned short & remainPurifyItemCount);

	/// ������ ��ȭ�� �����ߴ�. 
	virtual void onRecvPurifyItemFailed(const eStrengthenPurifyFailedReason & failedReason, const int & purifyItemNum, const unsigned short & purifySlotIdx); 

	/// �������� ��ȭ Ƚ�� ������ �����ߴ�. 
	virtual void onRecvReChargeReInforceChanceOK(const int & rechargedItemNum, const unsigned short & refreshChanceCnt, const int & usedItemNum); 

	/// �������� ��ȭ Ƚ�� ������ �����ߴ�. 
	virtual void onRecvReChargeReInforceChanceFailed(const eStrengthenRechargeReInforceChanceFailedReason & failedReason, const unsigned int & rechargeItemNum, const unsigned int & usingItemNum); 

	/// �������� ���� ���� ������ �����ߴ�. 
	virtual void onRecvIncreaseSlotCountOK(const int & increasedItemNum, const unsigned short & refreshedSlotCnt, const int & usedItemNum); 

	/// �������� ���� ���� ������ �����ߴ�. 
	virtual void onRecvIncreaseSlotCountFailed(const eStrengthenIncreaseSlotCountFailedReason & failedReason, const int & increaseItemNum, const int & usingItemNum); 

	/// �������� Ư�� ���� Ưȭ�迭 ���������� �����ߴ�. 
	virtual void onRecvChangeSlotSpecializedTypeOK(const int & changedItemNum, const unsigned short & changedSlotIdx, const unsigned short & refreshedType, const int & usedItemNum); 

	/// �������� Ư�� ���� Ưȭ�迭 ���������� �����ߴ�. 
	virtual void onRecvChangeSlotSpecializedTypeFailed(const eStrengthenChangeSlotSpecializedTypeFailedReason & failedReason, const unsigned int & targetItemNum, const int & usingItemNum); 

	/// ���� ��ġ ������ ��ų� ���� ��ġ�� ���´�.
	virtual void onRecvGetFreeHammer(const eItemStrengthenGetFreeHammerType & type, const byte & bAcquisitionCount, const byte & bRemainingCount, const byte & bPossessionCount, time_type & lastAcquisitionTime );

	/// ���� ��ġ ������ ��ų� ���� ��ġ�� ���� ���Ͽ���.
	virtual void onRecvGetFreeHammerFailed(const eItemStrengthenGetFreeHammerType & type, const eItemStrengthenGetFreeHammerFailedReason & failedReason );

	/// �Ƹ��� ���ݻ����� �Ǹ� ��ǰ�� �޾Ҵ�.
	virtual void onRecvPremiumArinShopItemListOK(const std::map<int, ArinShopItemInfo> & itemTable); 

	/// �Ƹ��� ���ݻ����� �Ǹ� ��ǰ�� ���� ���ߴ�. 
	virtual void onRecvPremiumArinShopItemListFailed(const ePremiumArinShopItemListFailedReason & failedReason);

	/// ������ ���� ��û�� �����ߴ�.
	virtual void onRecvTransformItemOK(cpk_type iCharacter, cpk_type iPosition, cpk_type iTransKind, int iTransItemNum);

	/// ������ ���� ��û�� �����ߴ�.
	virtual void onRecvTransformItemFailed(eItemTransformFailedReason eReason);

	//!< ��ȭ������ ���� �̺�Ʈ �ڵ鷯 ��. 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// ��� ��� ������Ʈ�� Ư�� ������ ���� ���� ������ �޾Ҵ�.
	virtual void onRecvAnniversaryObjectActionOK(const AnniversaryObjectAction & objectAction, AnniversaryAction action);

	/// ��� ��� ������Ʈ�� Ư�� ������ ���� ���� ������ �޾Ҵ�.
	virtual void onRecvAnniversaryObjectActionFailed(int iObjectNum);

	/// ��� ��� ������Ʈ�� ���� �޾Ҵ�.
	virtual void onRecvAnniversaryObjectValueOK(std::map<int,int> objectValueMap);
	virtual void onRecvAnniversaryObjectValueOK64(std::map<int,__int64> objectValueMap);

	/// ��� ��� ������Ʈ�� �� �ޱ⿡ �����ߴ�.
	virtual void onRecvAnniversaryObjectValueFailed(std::map<int,int> objectValueMap);
	virtual void onRecvAnniversaryObjectValueFailed64(std::map<int,__int64> objectValueMap);

	/// ��� ��� ������Ʈ�� ���� ������ �޾Ҵ�.
	virtual void onRecvAnniversaryGetUserInfo(int objectNum, int iRank, int value);

	/// ��� ��� ������Ʈ�� ���� �߰��Ǿ���.
	virtual void onRecvAnniversaryAddObjectValueOK(const AnniversaryObjectAction & objectAction, int iValue);
	virtual void onRecvAnniversaryAddObjectValueOK64(const AnniversaryObjectAction & objectAction, __int64 iValue);

	/// ��� ��� ������Ʈ�� ���� ���ҵǾ���.
	virtual void onRecvAnniversarySubstractObjectValueOK(const AnniversaryObjectAction & objectAction, int iValue);
	virtual void onRecvAnniversarySubstractObjectValueOK64(const AnniversaryObjectAction & objectAction, __int64 iValue);

	/// ��� ��� ������Ʈ�� ���� ���ҽ��еǾ���.
	virtual void onRecvAnniversarySubstractObjectValueFailed(ePieroOlympicFailedReason eReason);

	// ��� ��� ������Ʈ�� ���� ���� ���� �ܰ� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvAnniversaryGetReveivedRewardGradeList(int iObjectNum, __int64 iValue, std::vector<BYTE> grades);

	// ��� ��� ������Ʈ�� ���� �ش� ����� ������ �޾Ҵ�.
	virtual void onRecvAnniversaryReceiveReward(eAnniversaryActionResult result, const RewardInfo& reward);

#ifdef _DUCTILITY_SYSTEM_
	// �����ý��� ������Ʈ�� Ư�� ������ ���� ������ �޾Ҵ�.
	virtual void onRecvDuctilityObjectActionOK(const AnniversaryObjectAction & objectAction, DuctilityAction action);

	// ���� �ý��� ��� ������Ʈ�� ȸ���� ������ �޾Ҵ�.
	virtual void onRecvDuctilityObjectStepReward(eDuctilityResult result, int iObjectNum, int iStepNum, RewardInfo& rewardInfo);

	// ���� �ý��� ���� �� ���� ������ �޾Ҵ�.
	virtual void onRecvDuctilityConditionRewardList(eDuctilityResult result, int iConditionNum, std::vector<RewardInfo>& rewardList);
#endif

#ifdef _TREASURE_HUNT
	// ����ã�� �ý����� ���۵Ǿ���.
	virtual void onRecvTreasureHuntStart();

	// ����ã�� �ý����� ������.
	virtual void onRecvTreasureHuntEnd();

	// ����ã�� ���� ������ �޾Ҵ�.
	virtual void onRecvTreasureHuntStartInfo(time_type tStartTime, bool bStart, int iEndTime, int iFreePlayCount, int iTicketPlayCount);

	// �ֱ������� �����ִ� ����ã�� ������ �޾Ҵ�.
	virtual void onRecvTreasureHuntInfo(int iFullCount, int iCurrCount, eTreasure_Boost_Level eBoostLevel);

	// ����ã�� �ý��ۿ��� �ν�Ʈ�� �ߵ��Ǿ���.
	virtual void onRecvTreasureHuntBoost(int iFullCount, int iCurrCount, eTreasure_Boost_Level eBoostLevel);

	// �н����忡 ���� ������ �޾Ҵ�.
	virtual void onRecvTreasureHuntPasswordAck(eTreasure_BOXACT eBoxAct, Treasure_Box sTreasureBox, int iPassword);

	// ������ �����Ǿ���.
	virtual void onRecvTreasureHuntDelete(Treasure_Box sTreasureBox);

	// ������ ã�Ҵ�.
	virtual void onRecvTreasureHuntFindAck(eTreasure_BOXACT eBoxAct, Treasure_Box sTreasureBox, int itemNum);

	// ������ ã�� ���ߴ�.
	virtual void onRecvTreasureHuntFindFailed();

	// �������ڿ� ���� �����͸� �޾Ҵ�.
	virtual void onRecvTreasureHuntBoxData(std::vector<Treasure_Box> boxList);

	// ����ã�⿡ �����Ͽ���.
	virtual void onRecvTreasureHuntEnterAck(bool bUseTicket, bool b);

	// ����ã�� ������ �����ߴ�.
	virtual void onRecvTreasureHuntEnterFailed(eTreasure_Result JoinResult);

	// ����ã�⸦ �����ߴ�.
	virtual void onRecvTreasureHuntGiveUpAck();

	// ����ã�� ���⿡ �����ߴ�.
	virtual void onRecvTreasureHuntGiveUpFailed();
#endif

#ifdef _ONEDAY_BUFF_SYSTEM_
	// ���� ���� ������ ����� �޾Ҵ�.
	virtual void onRecvOneDayBuffLevelUP(const std::vector<RewardInfo>& rewardList, const OneDayBuffData& buffData, eOneDayBuff_Result result);

	// ���� ���� ���� ������ �޾Ҵ�.
	virtual void onRecvOneDayBuffStartNotify(const OneDayBuffData& buffData);

	// ���� ���� ���� ������ �޾Ҵ�.
	virtual void onRecvOneDayBuffFinishNotify(const OneDayBuffData& buffData);
#endif

	// ���� ������ �޾Ҵ�.
	virtual void onRecvInegratedRewardGiveRewardOK(std::vector<IntegratedReward> rewardList, const AnniversaryObjectAction & objectAction);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���� ��й�ȣ
	/// ��й�ȣ ���� ���ο� ���� ������ �޾���.
	virtual void onRecvIsExistConfirmationPasswordOK(bool bIsExistConfirmationPassword);

	/// ��й�ȣ ���� ���ο� ���� ������ �ޱ� ��������.
	virtual void onRecvIsExistConfirmationPasswordFailed(eServer_IS_EXIST_CONFIRMATION_PASSWORD_FAILED_REASON eFailedReason);

	/// ��й�ȣ ������ ��������.
	virtual void onRecvSetConfirmationPasswordOK();

	/// ��й�ȣ ������ ��������.
	virtual void onRecvSetConfirmationPasswordFailed(eServer_SET_CONFIRMATION_PASSWORD_FAILED_REASON eFailedReason);

	/// ��й�ȣ üũ�� ��������.
	virtual void onRecvCheckConfirmationPasswordOK();

	/// ��й�ȣ üũ�� ��������.
	virtual void onRecvCheckConfirmationPasswordFailed(eServer_CHECK_CONFIRMATION_PASSWORD_FAILED_REASON eFailedReason);

	//////////////////////////////////////////////////////////////////////////
	// �̺�Ʈ ������ ��ȯ
	/// �̺�Ʈ ���������� ��ȯ�� �� �ִ� ������ ����� �޾���.
	virtual void onRecvEventItemExchangeItemListOK(int iEventNum, const std::vector<RewardItemInfo> &vecRewardList);

	/// �̺�Ʈ ���������� ��ȯ�� �� �ִ� ������ ��Ϲޱ⸦ ��������.
	virtual void onRecvEventItemExchangeItemListFailed(int iEventNum, eServer_EVENT_ITEM_EXCHANGE_ITEM_LIST_FAILED_REASON eFailedReason);

	/// �̺�Ʈ ������ ��ȯ�� ��������.
	virtual void onRecvExchangeEventItemOK(int iEventNum, eRewardCondition eRewardType, int iReward);

	/// �̺�Ʈ ������ ��ȯ�� ��������.
	virtual void onRecvExchangeEventItemFailed(int iEventNum, eServer_EXCHANGE_EVENT_ITEM_FAILED_REASON eFailedReason);

	//////////////////////////////////////////////////////////////////////////
	
	// ��������
	/// ������ ����� �������� �Ұ��������� �޾Ҵ�.(bFree = TRUE : ����, FALSE : ����)
	virtual void onRecvDivinationCheckFree( bool bFree, eDivinationType requestType);

	/// ���� ���� ��ȸ�� �����ߴ�.
	virtual void onRecvDivinationCheckFreeFailed(eDivinationType requestType);

	/// ������ �޾Ҵ�.
	virtual void onRecvDivinationResult(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities, eDivinationType requestType);

	/// �����Ⱑ �����ߴ�.
	virtual void onRecvDivinationResultFailed(eDivinationFailReason failReason, eDivinationType requestType);

	/// �� Ŀ�ÿ� ���� ������ �޾Ҵ�.
	virtual void onRecvDivinationCoupleExAbilitiesResult(const ExtraAbilityInfo & appliedExtraAbilities, std::string strDivinationDesc);

	virtual void onRecvDivinationCoupleExAbilitiesResultFailed();

	//////////////////////////////////////////////////////////////////////////
	// Ư�� �ɷ�ġ(����)

	/// ��û�� Ư�� �ɷ��� ���(Ư���� �ɷ�ġ-����-�� ����Ǵ� ������ ���)�� �޾Ҵ�.
	virtual void onRecvExtraAbilities(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities);

	/// Ư�� ����ġ �ޱⰡ �����ߴ�.
	virtual void onRecvExtraAbilitiesFailed();

	/// Ư�� �ɷ�ġ(����)������ ����� �����ߴ�.
	virtual void onRecvUseExtraAbilityItem(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities,eDivinationType requestType, int iUseItemNum, int iRemainUseItemCount);

	/// Ư�� �ɷ�ġ(����)������ ����� �����ߴ�.
	virtual void onRecvUseExtraAbilityItemFailed(eUseExtraAbilityItemFailReason failReason, eDivinationType requestType);

	/// �̼� ���� Ư�� �ɷ�ġ(����)������ ����� �����ߴ�.
	virtual void onRecvUseMissionExtraAbilityItem(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities,eMissionKind missionKind);

	/// �̼� ���� Ư�� �ɷ�ġ(����)������ ����� �����ߴ�.
	virtual void onRecvUseMissionExtraAbilityItemFailed(eUseExtraAbilityItemFailReason failReason, eMissionKind missionKind);

	//////////////////////////////////////////////////////////////////////////

	///<! �������̽� ���� �̺�Ʈ �ڵ鷯
	// ���� ����̱⿡ �����ߴ�.
	virtual void onRecvAnimalRacingPetTrainingOK(__int64 nFarmItemID, int nFarmPetDescNum, int nRidingPetDescNum);

	// ���� ����̱⿡ �����ߴ�.
	virtual void onRecvAnimalRacingPetTrainingFailed(__int64 nFarmItemID, int nItemDescNum, int nReturnValue);

	// �⺻ ���� �ޱ� ����
	virtual void onRecvAnimalRacingGetDefaultAnimalOK();
	
	// �⺻ ���� �ޱ� ����
	virtual void onRecvAnimalRacingGetDefaultAnimalFailed(int nReason);

	// ����� ���� ����Ʈ �ޱ� ����
	virtual void onRecvAnimalRacingGetExpiredAnimalAvatarListOK(std::vector<int> & nAnimalKindList);

	// ����� ���� ����Ʈ �ޱ� ����
	virtual void onRecvAnimalRacingGetExpiredAnimalAvatarListFailed();

	//////////////////////////////////////////////////////////////////////////
	// ���� �������� �޾Ҵ�.
	virtual void onRecvUserProfile( const UserProfile & stUserProfile);

	// ���� �������� ����� ���� ���Ͽ���.
	virtual void onRecvUserProfileFailed();

	//���� �������� �����Ѵ�.
	virtual void onRecvSetUserProfile(const UserProfile & stUserProfile);

	// ���� �������� ����� �������� ���ߴ�.
	virtual void onRecvSetUserProfileFailed();

#ifdef _GAME_OPTION_
	// ���� ���ӿɼ� ���� �޾Ҵ�.
	virtual void onRecvUserGameOptionOK(std::string & sMacro, std::string & sShare, GameOptionInfo & gameOption);

	// ���� ���ӿɼ� ���� ���� ���Ͽ���.
	virtual void onRecvUserGameOptionFailed();

	//���� ���ӿɼ� ���� �����Ѵ�.
	virtual void onRecvSetUserGameOptionOK();

	// ���� ���ӿɼ� ���� �������� ���ߴ�.
	virtual void onRecvSetUserGameOptionFailed();
#endif

#ifdef _SECOND_PASSWORD_
	// 2�� ��й�ȣ ��û �Ѵ�.
	virtual void onRecvSecondPasswordInfo();

	// 2�� ��й�ȣ ���� ����.
	virtual void onRecvSetSecondPasswordOK();

	// 2�� ��й�ȣ ���� ����.
	virtual void onRecvSetSecondPasswordFailed();

	// 2�� ��й�ȣ Ȯ�� ����.
	virtual void onRecvCheckSecondPasswordOK(eCERTIFY_TYPE certifyType);

	// 2�� ��й�ȣ Ȯ�� ����.
	virtual void onRecvCheckSecondPasswordFailed(eSecondPassword_FAILED_REASON eFailedReason, int iFailedCount, time_type tFailedDate);

	// 2�� ��й�ȣ ���� ����.
	virtual void onRecvChangeSecondPasswordOK(eCERTIFY_TYPE certifyType);

	// 2�� ��й�ȣ ���� ����.
	virtual void onRecvChangeSecondPasswordFailed(eSecondPassword_FAILED_REASON eFailedReason, int iFailedCount, time_type tFailedDate);

	// 2�� ��й�ȣ �������� ����.
	virtual void onRecvCertifySecondPasswordOK();

	// 2�� ��й�ȣ �������� ����.
	virtual void onRecvCertifySecondPasswordFailed(eSecondPassword_FAILED_REASON eFailedReason);

	// 2�� ��й�ȣ ��� ���� ����.
	virtual void onRecvSecondPasswordUseCancelOK(eCERTIFY_TYPE certifyType);

	// 2�� ��й�ȣ ��� ���� ����.
	virtual void onRecvSecondPasswordUseCancelFailed(eSecondPassword_FAILED_REASON eFailedReason, eCERTIFY_TYPE certifyType, int iFailedCount, time_type tFailedDate);
#endif // _SECOND_PASSWORD_

	//////////////////////////////////////////////////////////////////////////
	/// �ʿ��� ���̴� ����� ����

	//! ���� �����ϴµ� �����Ͽ���.
	virtual void onRecvFarmCreateFarmOK(const FarmInfo& farmInfo);

	//<! �� �� ������Ʈ�� ���� ������ ������Ʈ�� ������ �����Ѵ�. 

	//! �߰��� �� ������Ʈ ������ ó��. 
	virtual void onRecvFarmModifyByInsertOK(const RecvFarmMapObjectInfo& mapObject); 

	//! ��ġ�� ������� ����� �� ������Ʈ ������ ó��. 
	virtual void onRecvFarmModifyByModifyOK(const RecvFarmMapObjectInfo& mapObject); 

	//! ������ �� ������Ʈ ������ ó��.
	virtual void onRecvFarmModifyByDeleteOK(const __int64& iFarmDescNum); 


	//! ���� �����ϴµ� �����Ͽ���.
	virtual void onRecvFarmCreateFarmFailed(const eFarm_CREATE_FARM_FAILED_REASON);

	//! �������� ��Ȯ�ϴµ� �����Ͽ���.
	virtual void onRecvFarmHarvestOK(const __int64 intiTargetItemID,const std::vector<FarmHarvestInfo>& vecResultItem);

	//! �������� ��Ȯ�ϴµ� �����Ͽ���.
	virtual void onRecvFarmHarvestFailed(const eServerResult& eResult, const __int64 intiTargetItemID);

	//! �� ��Ȯ������ ��Ȯ�� �����Ͽ���
	virtual void onRecvFarmHarvestCropHarvestOK(__int64& farmItemID, std::vector<RewardInfo>& rewardList);

	//! �� ��Ȯ������ ��Ȯ�� �����Ͽ���
	virtual void onRecvFarmHarvestCropHarvestFailed(__int64& farmItemID);

	//! �� ���� �ǹ����� ������ ������ �����Ͽ���
	virtual void onRecvFarmHarvestBuildingMakeItemAcOK(const __int64 buildingItemID, const int makeItemNum);

	//! �� ���� �ǹ����� ������ ������ �����Ͽ���
	virtual void onRecvFarmHarvestBuildingMakeItemFailed(const __int64 buildingItemID);

	//! ���� �� ����Ʈ�� �����ϴµ� ���� �Ͽ���.
	virtual void onRecvFarmGiveMeRandomFarmPointOK(const __int64 iFarmItemID, const int iRemainFarmPoint, const int iGiveFarmPoint);

	//! ���� �� ����Ʈ�� ��µ� �����Ͽ����ϴ�.
	virtual void onRecvFarmGetMyFarmPointOK(const int iFarmPoint);

	//! ���� �� ����Ʈ�� ��µ� �����Ͽ����ϴ�.
	virtual void onRecvFarmGetMyFarmPointFailed();

	//! ���� �� ����Ʈ�� �����ϴµ� �����Ͽ���.
	virtual void onRecvFarmGiveMeRandomFarmPointFailed(const __int64 iFarmItemID);

	//! ���� �����ϴµ� �����Ͽ���. 
	virtual void onRecvFarmDestroyFarmOK(const int iFarmUniqueNum); 

	//! ���� �����ϴµ� �����Ͽ���. 
	virtual void onRecvFarmDestroyFarmFailed(const int iFarmUniqueNum);

	//! �� ������Ʈ ���� ���� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvFarmObjectLockInfoList(std::map<FarmObjectIDIndex, BYTE> mapFarmObjectLockInfoList);

	//! �� ������Ʈ ���� ������ ����Ǿ���.
	virtual void onRecvFarmModifyObjectLockInfo(eServerResult eResult, FarmObjectIDIndex stOIDIndex, BYTE iGameIndex, bool bLock);

	//! �� �̸��� �����Ͽ���.
	virtual void onRecvFarmChangeFarmName( const int iFarmUniqueNum, const std::string strFamrName);

	//! �� �̸� ������ �����Ͽ���.
	virtual void onRecvFarmChangeFarmNameFailed( const eServerResult eResult, const eFarm_CHANGE_FARM_NAME_FAILED_REASON failedReason);

	//! �����̾��� Ÿ���� �����Ͽ���.
	virtual void onRecvFarmChangePremiumFarmType( const eServerResult eResult, const int iFarmUniqueNum, const ePremiumFarmType premiumFarmType);

	//! �� ����/�����(��й�ȣ) ������ �����Ͽ���. 
	virtual void onRecvFarmChangePublicModeOK( const int iFarmUniqueNum, const bool bPublic );

	//! �� ����/�����(��й�ȣ) ������ �����Ͽ���. 
	virtual void onRecvFarmChangePublicModeFailed( const eFarm_CHANGE_FARM_PASSWORD_FAILED_REASON byReason );

	//! �� Talking-Mode ������ �����Ͽ���. 
	virtual void onRecvFarmChangeTalkingMode( const eServerResult eResult, const bool bTalkOn, const FarmChattingInfo& farmChattingInfo, const ePremiumFarmType premiumFarmType);

	//! ���� �� ������ �����ϴ�. 
	virtual void onRecvFarmJoinOnRamdonOK( const int& farmUniqueNum );

	//! ���� �� ������ �����Ͽ���. 
	virtual void onRecvFarmJoinOnRandomFailed( const eFarm_JOIN_TALKFARM_ON_RANDOM_JOIN_FAILED_REASON& failedReason); 

	//! �г����� ���� �� �˻� ����. 
	virtual void onRecvFarmSearchByNickNameOK( const int iFarmUniqueNum, const bool isPublic); 
	
	//! �г����� ���� �� �˻� ����. 
	virtual void onRecvFarmSearchByNickNameFailed( const eFarm_SEARCH_FARM_FAILED_REASON& failedReason); 

	//! ������ȣ�� ���� �� �˻� ����. 
	virtual void onRecvFarmSearchByUserNumOK(const int iFarmUniqueNum, const bool isPublic);

	//! ������ȣ�� ���� �� �˻� ����. 
	virtual void onRecvFarmSearchByUserNumFailed(const eFarm_SEARCH_FARM_FAILED_REASON failedReason);

	//! �������� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetFarmInfoOK(const int iFarmUniqueNum,const FarmInfo& info);

	//! �������� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetFarmInfoFailed(const int iFarmUniqueNum);

	//! �ڽ��� �������� ��µ� �����Ͽ���. 
	virtual void onRecvFarmGetMyFarmInfoOK(const FarmInfo& info); 

	//! �ڽ��� �������� ��µ� �����Ͽ���. 
	virtual void onRecvFarmGetMyFarmInfoFailed(void);	

	//! ��� �������� ��µ� �����Ͽ���. 
	virtual void onRecvFarmGetGuildFarmInfoOK(const FarmInfo& info);

	//! ��� �������� ��µ� �����Ͽ���. 
	virtual void onRecvFarmGetGuildFarmInfoFailed(void);

	//! ����� �� Ÿ���� ����Ǿ���
	virtual void onRecvGuildFarmGetChangeMapType(const int iGuildNum, const int iFarmUniqueNum, const int iGuildFarmType);

	//! ����� �� Ÿ���� �����Ͽ���
	virtual void onRecvGuildFarmGetChangeMapTypeFailed( const eFarm_GET_GUILDFARM_INFO_FAILED_REASON & byReason );

	//! ����� ������Ʈ�� �ɷ�ġ�� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetGuildFarmObjectAttrListOK(const int iGuildNum, std::map<int, GuildFarmItemAttrInfo > & mapFamrItemAttr);

	//! ����� ������Ʈ�� �ɷ�ġ�� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetGuildFarmObjectAttrListFailed();	

	//! ����� �Ĺ� ��Ȯ�� �����Ͽ���.
	virtual void onRecvGuildFarmGetHarvestOK(const int iGuildNum, const __int64 iOID, const bool bDelete);

	//! ����� �Ĺ� ��Ȯ�� �����Ͽ���.
	virtual void onRecvGuildFarmGetHarvestFailed(const eServerResult& eResult,const __int64 intiTargetItemID);

	//!< ������� �ָ��� ������ �����Ͽ���.
	virtual void onRecvFarmModifyGuildFarmNoticeBoardInfo(const int iGuildNum, const std::string & strBoardInfo);

	//!< ������� �ָ��� ���� ���濡 �����Ͽ���.
	virtual void onRecvFarmModifyGuildFarmNoticeBoardInfoFailed(const int iGuildNum);

	//! �ʰ��� ������ ����Ʈ ������ �����Ѵ�. 
	virtual void onRecvFarmGetFarmItemListBegin(void); 

	//! �ʰ��� ������ ����Ʈ�� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetFarmItemListOK(const std::vector<FarmItemInfo>&	vecItems);

	//! �ʰ��� ������ ����Ʈ�� ��� �� �޾Ҵ�. 
	virtual void onRecvFarmGetFarmItemListAll(const size_t& totalCount);

	//! �ʰ��� ������ ����Ʈ�� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetFarmItemListFailed();

	//! �� ���� Ư�� ������ ����� �޾Ҵ�.
	virtual void onRecvFarmGetFarmItemListExOK(const std::vector<FarmItemInfo>&	vecItems);

	//! ����� ���� Ư�� ������ ����� �޾Ҵ�.
	virtual void onRecvFarmGetGuileFarmItemListExOK(const int iGuildNum, const std::vector<FarmItemInfo>&	vecItems);

	//! �ʰ��� �������� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetFarmMapInfoOK(const int iFarmUniqueNum, const int iFarmMapType, const std::vector<RecvFarmMapObjectInfo>& vecMapInfo, const std::vector<RecvFarmMapVoxelsInfo>& vecVoxelInfo);
	//! ���� �������� ���ε��ߴ�.
	virtual void onRecvFarmReloadFarmMapInfo(const int iFarmUniqueNum, const int iFarmTypeNum, const int iFarmSkyBoxNum, const int iFarmWeatherNum, const std::vector<RecvFarmMapObjectInfo>& vecMapInfo, const std::vector<RecvFarmMapVoxelsInfo>& vecVoxelInfo);

	//! �ʰ��� �������� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetFarmMapInfoFailed(const int iFarmUniqueNum);


	//! �������� �ʱ�ȭ�ϴµ� �����Ͽ���.
	virtual void onRecvFarmClearFarmMapInfoOK(const int iFarmUniqueNum);

	//! �������� �ʱ�ȭ�ϴµ� �����Ͽ���.
	virtual void onRecvFarmClearFarmMapInfoFailed(const int iFarmUniqueNum);

	//! �ʸ� ���� ���� �����κ��� ������ �޾Ҵ�
	virtual void onRecvFarmModifyFarmMapInfoOK(const int iFarmUniqueNum, mapObjectModifyResult& mapObjectResultList);

	//! ���� �� ���� ����Ʈ�� �дµ� �����Ͽ���.  
	virtual void onRecvFarmGetFarmSlotListOK(std::vector<FarmSlotInfo> & vecFarmSlotInfo);

	//! ���� �� ���� ����Ʈ�� �дµ� �����Ͽ���.  
	virtual void onRecvFarmGetFarmSlotListFailed(const eFarm_GET_FARM_SLOT_LIST_FAILED_REASON& failedReason);

	//! ���� �� ������ �����ϴµ� �����Ͽ���.  
	virtual void onRecvFarmSaveFarmSlotInfoOK(const int iFarmSlotNum, const FarmSlotInfo& eResult);

	//! ���� �� ������ �����ϴµ� �����Ͽ���.  
	virtual void onRecvFarmSaveFarmSlotInfoFailed(const eFarm_SAVE_FARM_SLOTINFO_FAILED_REASON& failedReason );

	//! ���� �� ������ �ʱ�ȭ�ϴµ� �����Ͽ���.  
	virtual void onRecvFarmClearFarmSlotInfoOK(const int iFarmSlotNum);

	//! ���� �� ������ �ʱ�ȭ�ϴµ� �����Ͽ���.  
	virtual void onRecvFarmClearFarmSlotInfoFailed(const eFarm_CLEAR_FARM_SLOTINFO_FAILED_REASON& failedReason);

	//! �ʰ��� ���� �������� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetFarmMapSlotInfoOK(const int iFarmUniqueNum, const int iFarmMapType, const int iFarmSkyBoxNum, const int iFarmWeatherNum, const std::vector<RecvFarmMapObjectInfo>& vecMapInfo, const std::vector<RecvFarmMapVoxelsInfo>& vecVoxelInfo);

	//! �ʰ��� ���� �������� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetFarmMapSlotInfoFailed(const int iFarmUniqueNum);

	//! ���� �� ������ �ҷ����� �ϴµ� �����Ͽ���.  
	virtual void onRecvFarmGetFarmSlotInfoOK(const int newFarmMapType, std::vector<ItemMsgInfo> & vecItemMsgInfo);

	//! ���� �� ������ �ҷ����� �ϴµ� �����Ͽ���.  
	virtual void onRecvFarmGetFarmSlotInfoFailed(const eFarm_GET_FARM_SLOTINFO_FAILED_REASON& failedReason);

	//! ���� �� ������ ���� �ϴµ� �����Ͽ���.  
	virtual void onRecvFarmPayFarmSlotResultOK(const int iFarmSlotNum);

	//! ���� �� ������ ���� �ϴµ� �����Ͽ���.  
	virtual void onRecvFarmPayFarmSlotResultFailed(const eFarm_PAY_FARM_SLOT_RESULT_FAILED_REASON& failedReason);

	//! ���� �� ��ȣ�� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetMyFarmUniqueNumOK(const int iFarmUniqueNum);

	//! ���� �� ������ ��µ� �����Ͽ���.
	virtual void onRecvFarmGetMyFarmUniqueNumFailed();

	//! Ư�� ���� �۹̼� ������ ��µ� �����Ͽ����ϴ�.
	virtual void onRecvFarmGetFarmPermisionInfoOK(const int iFarmUniqueNum, FarmPermisionInfo& rPermisionInfo);

	//! Ư�� ���� �۹̼� ������ ��µ� �����Ͽ����ϴ�.
	virtual void onRecvFarmGetFarmPermisionInfoFailed(const int iFarmUniqueNum);

	//! �� �������� �ɷ�ġ�� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetFarmItemAttrListOK(const int iFarmUniqueNum, std::map< __int64, std::map<int, FarmItemAttrInfo > >& mapFamrItemAttr, const bool bGetOnlySetUpObjectAttrInfo, const bool bDataReplace);

	//! �� �������� �ɷ�ġ�� ��µ� �����Ͽ���.
	virtual void onRecvFarmGetFarmItemAttrListFailed();

	//! Ư�� ���� �۹̼� ���� ����Ʈ�� ��µ� �����Ͽ����ϴ�.
	virtual void onRecvFarmGetFarmPermisionInfoListOK(const int iFarmUniqueNum, std::vector<UserFarmPermisionInfo>&		rVecFarmPermisionInfo );

	//! Ư�� ���� �۹̼� ������ ��µ� �����Ͽ����ϴ�.
	virtual void onRecvFarmGetFarmPermisionInfoListFailed(const int iFarmUniqueNum);

	//!< Ư�� ���� ���Ⱓ�� ����Ǿ����ϴ�. 
	virtual void onRecvFarmExpirationPeriodNotify(const int iFarmUniqueNum, const bool isExitFarmFlag); 

	//!< �ʿ� ��ġ�� �������� ���ŵǾ���.
	virtual void onRecvFarmDeleteMapItemNotify(const __int64 iOID);

	//!< �� ����Ʈ�� �̿��� ���� ���Ⱓ ���ſ�û�� ������ ��� ȣ��. (��û�� �������Ը� ���޵ȴ�.)
	virtual void onRecvFarmRenewalPeriodByFarmPointOK(const int refreshFarmPoint, const FarmInfo myFarmInfo); 

	//!< �� ����Ʈ�� �̿��� ���� ���Ⱓ ���ſ�û�� ������ ��� ȣ��. (��û�� �������Ը� ���޵ȴ�.)
	virtual void onRecvFarmRenewalPeriodByFarmPointFailed(const eFarm_RENEWAL_FARM_PERIOD_FAILED_REASON failedReason); 

	//!< �� �������� �̿��� ���� ���Ⱓ ���ſ�û�� ������ ��� ȣ��. (��û�� �������Ը� ���޵ȴ�.)
	virtual void onRecvFarmRenewalPeriodByItemOK(const int iRenewalItemDescNum, const FarmInfo myFarmInfo); 

	//!< �� �������� �̿��� ���� ���Ⱓ ���ſ�û�� ������ ��� ȣ��. (��û�� �������Ը� ���޵ȴ�.)
	virtual void onRecvFarmRenewalPeriodByItemFailed(const eFarm_RENEWAL_FARM_PERIOD_FAILED_REASON failedReason); 

	//!< �ʿ� ��ġ�� �����ۿ� Ư�� �������� ����� ��� �������� �� ȣ��. 
	virtual void onRecvFarmUseFarmItemToFarmObjectOK(/* ���� �������ϳ�.. */); 

	//!< �ʿ� ��ġ�� �����ۿ� Ư�� �������� ����� ��� �������� �� ȣ��. 
	virtual void onRecvFarmUseFarmItemToFarmObjectFailed(const eFarm_USED_FARMITEM_TO_FARMOBJECT_FAILED_REASON failedReason/*itemtype, ...*/); 

	//!< Ư�� ������ �� �Ⱓ�� ���ŵǾ��� ��� �������� ���޵Ǵ� ����. (���ŵ� �濡 �ִ� ������ ������ �����鿡�� ���۵ȴ�.)
	virtual void onRecvFarmRenewalPeriodNotify(const int farmUniqueNum, const FarmInfo userFarmInfo); 

	//!< �� ������Ʈ ����ġ ���� ��û�� ���� ����
	virtual void onRecvFarmObjectExpCharge( const int iPlayerIndex, const __int64 iObjectID, const int iObjectExp, const int iFarmPoint, const int iPremiumFarmPoint, const int iView, int iChargeItemNum);

	//!< �� ������Ʈ ����ġ ������ �˼� ���� ������ �����ߴ�.
	virtual void onRecvFarmObjectExpChargeFailed(eServerResult eFailedReason);

	//!< �� ������Ʈ�� ��Ȯ���� ���� ���� ��û�� �������� ��� ȣ��. 
	virtual void onRecvFarmObjectHarvestCountChargeOK( const __int64& appliedObjectID, const int& renewalCount, int iUsedItemDescNum); 

	//!< �� ������Ʈ�� ��Ȯ���� ���� ���� ��û�� �������� ��� ȣ��. 
	virtual void onRecvFarmObjectHarvestCountChargeFailed( const eFarm_OBJECT_HARVEST_COUNT_CHARGE_FAILED_REASON& failedReason);

	//!< �� ������ ������ 1�ܰ� Ű��� ��û�� �������� ��� ȣ��. 
	virtual void onRecvFarmIncreaseAnimalSizeOK(const __int64 appliedObjectID, const int view); 

	//!< �� ������ ������ 1�ܰ� Ű��� ��û�� �������� ��� ȣ��. 
	virtual void onRecvFarmIncreaseAnimalSizeFailed(const __int64 failedObjectID, const eFarm_INCREASE_ANIMAL_SIZE_FAILED_REASON failedReason); 

	//!< �� ������ �⺻ ������� ���� ��û�� �������� ��� ȣ��. 
	virtual void onRecvFarmRestoreAnimalDefaultSizeOK(const __int64 appliedObjectID, const int view); 

	//!< �� ������ �⺻ ������� ���� ��û�� �������� ��� ȣ��. 
	virtual void onRecvFarmRestoreAnimalDefaultSizeFailed(const __int64 failedObjectID, const eFarm_RESTORE_ANIMAL_DEFAULT_SIZE_FAILED_REASON failedReason); 

	//!< �ʴ뿡 ���� ����ó�� ����. 
	virtual void onRecvFarmGoTogetherFarmRoomFailed(const eFarm_GO_TOGETHER_FARM_ROOM_FAILED_REASON& failedReason);

	//!< �� �������� ������ ��� ��û�� �������� ��� ȣ��. 
	//!< ������ �ݵ��, �� �� ������ ���û�ؾ��Ѵ�. 
	virtual void onRecvFarmChangeMapTypeOK(const int& farmUniqueNum, const int& newFarmMapType); 

	//!< �� �������� ������ ��� ��û�� �������� ��� ȣ��. 
	virtual void onRecvFarmChangeMapTypeFailed( const eFarm_CHANGE_FARM_MAP_TYPE_FAILED_REASON& failedReason); 

	//!< �� �ָ��� ������ �޾Ҵ�.
	virtual void onRecvFarmNoticeBoardInfo(const __int64 iOID, const std::string & strBoardInfo); 

	//!< �� �ָ��� ������ �����Ͽ���.
	virtual void onRecvFarmModifyNoticeBoardInfo(const __int64 iOID); 

	//!< �� �ָ��� ���� ���濡 �����Ͽ���.
	virtual void onRecvFarmModifyNoticeBoardInfoFailed(const __int64 iOID);

	//!< �� ������Ʈ�� �Ӽ� �� ������ ����Ǿ���.
	virtual void onRecvFarmModifyObjectValueInfo(const __int64 iOID, const int iValue); 

	//!< �� ������Ʈ�� ������ ���濡 �����Ͽ���.
	virtual void onRecvFarmModifyObjectValueInfoFailed(const __int64 iOID); 

	//!< �� �������� ����� ��ī�̹ڽ� ������ �������� ��� ȣ��.
	virtual void onRecvFarmChangeSkyboxTypeOK(const int& farmUniqueNum, const int& newSkyBoxType); 

	//!< �� �������� ����� ��ī�̹ڽ� ������ �������� ��� ȣ��. 
	virtual void onRecvFarmChangeSkyboxTypeFailed( const eFarm_CHANGE_FARM_SKYBOX_TYPE_FAILED_REASON& failedReason ); 

	//!< �� �������� ����� ���� ������ �������� ��� ȣ��. 
	virtual void onRecvFarmChangeWeatherTypeOK(const int& farmUniqueNum, const int& newWeatherType); 

	//!< �� �������� ����� ���� ������ �������� ��� ȣ��. 
	virtual void onRecvFarmChangeWeatherTypeFailed( const eFarm_CHANGE_FARM_WEATHER_TYPE_FAILED_REASON& failedReason ); 

	//!< �� ����Ʈ�� �̿��� ������ ���Ÿ� �����ߴ�. 
	virtual void onRecvFarmBuyProductsUseFarmPointOK( const int& remainFarmPoint, std::vector<int> successItemList ); 

	//!< �� ����Ʈ�� �̿��� ������ ���Ÿ� �����ߴ�. 
	virtual void onRecvFarmBuyProductsUseFarmPointFailed(const eFarm_BUY_PRODUCTS_USE_FARMPOINT_FAILED_REASON& failedReason); 

	/// ���� ������ ��µ� �����Ͽ���. 
	virtual void onRecvFarmGetMasterUserInfoFailed(const eFarm_GET_MASTER_USER_INFO_FAILED_REASON& failedReason, const int& farmUniqueNum);

	/// Ư�� ���� ������ �Ӽ������� ���ŵǾ��ٴ� ������ ����. 
	virtual void onRecvUpdateFarmItemPropertyNotify( std::vector<RecvFarmMapObjectInfo>& farmItemList ); 

	/// �ʾ������� �Ⱓ ���� ���� üũ�� �����ߴ�.
	virtual void onRecvCheckFarmItemPeriodOK();

	/// �ʾ������� �Ⱓ ���� ���� üũ�� �����ߴ�.
	virtual void onRecvCheckFarmItemPeriodFailed(eServerResult eFailedReason);

	/// �� �������� �޽����� �޾Ҵ�.
	virtual void onRecvGetFarmItemMsgOK(const std::vector<ItemMsgInfo>& vecItemMsgInfo);

	/// �� �������� �޽����� �޴µ� �����ߴ�.
	virtual void onRecvGetFarmItemMsgFailed(eServerResult eFailedReason);

	/// �� ���ã�� ���� ������ �����ߴ�.
	virtual void onRecvSetFarmPortalInfo(const __int64 m_iObjectID, const int m_iFarmMasterUserNum, const std::string &m_strMemo);

	/// �� ���ã�� ���� ���� ������ �����ߴ�.
	virtual void onRecvSetFarmPortalInfoFailed(const eFarm_SET_FARM_PORTAL_INFO_FAILED_REASON eFailedReason);

	/// �� ���ã�� ���� ������ �޾Ҵ�.
	virtual void onRecvGetFarmPortalInfo(const __int64 iObjectID, const int iFarmMasterUserNum, const std::string &strFarmMasterNickname, const std::string &strMemo);

	/// �� ���ã�� ���� ���� �ޱ⸦ �����ߴ�.
	virtual void onRecvGetFarmPortalInfoFailed(const eFarm_GET_FARM_PORTAL_INFO_FAILED_REASON eFailedReason);

	//! ä���� �Ű��û�� ó���Ǿ���.
	virtual void onRecvAccuseChattingFarm(int iFarmUniqueNum, int iCautionCount);

	//! ä���� �Ű��û�� �����ߴ�.
	virtual void onRecvAccuseChattingFarmFailed(int iFarmUniqueNum);

	//!< �ð��� ��Ȯ �� �������� �ð� ���� ����� �޾Ҵ�
	//!< �ð��� ��Ȯ �� �������� �ð� ���� ����� �޾Ҵ�
	virtual void onRecvFarmObjectInfo(const int farmUniqueNum, const UINT iGameIndex, std::vector<FarmItemInfo>& farmItemList);

	//! �� ���� ������ ���� ���� �ο� ó��
	virtual void onRecvFarmNameTagSetting( const unsigned int iPlayerIndex, const unsigned int iItemKind, const std::string& strNameTag );

	//! ������ �ʿ����� ���� ��� �Ұ����� ���θ� ���´�.
	virtual void onRecvFarmNameTagCheck( const unsigned int iPlayerIndex, const std::string& strNameTag );

	//! �� ������ ����ϴ� �뿡 ���ο� ���� ���ӽ� ���� ���� ���� �������� �˷��ش�.
	virtual void onRecvFarmNameTagNewUser( std::map<unsigned int, NameTagInfo>& mapFarmNameTagList );

	//! �� ������ ����ϴ� �뿡 ������ �ʿ��� ������ �� ó��
	virtual void onRecvLeaveRoom(unsigned int iPlayerIndex);

	//! �� ������ ����Ҷ� ���� ó��
	virtual void onRecvFarmNameTagFliled( const eFarmNameTagResult& result );

	virtual void onRecvFarmNameTagRemove(const unsigned int iPlayerIndex);


	/// �ʿ��� ���̴� ����� ��
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	/// ���̷뿡�� ���̴� ����� ����

	virtual void onRecvMyRoomTransaction(const bool& bTransaction);

	/// ���̷뿡�� ���� ĳ���͵��� ����Ʈ�� �����.
	virtual void onRecvMyRoomMyCharacterList(const std::vector < cpk_type > & characterList);

	/// ���̷뿡�� ���� ĳ���͵��� ����Ʈ�� ��µ� �����ߴ�. ġ������ ������.
	virtual void onRecvMyRoomMyCharacterListFail();

	/// ���̷뿡�� Ư�� ĳ������ ������ �����.
	virtual void onRecvMyRoomGetMyCharacterSetting(const AvatarInfo & realAvatarInfo);

	/// ���̷뿡�� Ư�� ĳ������ ������ ��µ� �����ߴ�.
	virtual void onRecvMyRoomGetMyCharacterSettingFail();

	/// ���̷뿡�� Ư�� ĳ������ ������ �����ϴ� �� �����ߴ�.
	virtual void onRecvMyRoomSetCharacterSetting();

	/// ���̷뿡�� Ư�� ĳ������ ������ �����ϴ� �� �����ߴ�.
	virtual void onRecvMyRoomSetCharacterSettingFail();

	///���̷뿡�� TR ���� �������� �� �Ĵµ� ���� �ߴ�.
	virtual void onRecvSellTRItemOK(int iItemNum, int iSellPrice);
	///���̷뿡�� TR ���� �������� �� �Ĵµ� ���� �ߴ�.
	virtual void onRecvSellTRItemFailed(eSellTRItemFailedReason eFailedReason);
	/// �⺻ ĳ���� ������ �����ϴµ� �����ߴ�.
	virtual void onRecvMyRoomSetDefaultCharacterOK();

	/// �⺻ ĳ���� ������ �����ϴµ� �����ߴ�.
	virtual void onRecvMyRoomSetDefaultCharacterFail();

	/// �ɸ��� ���� ���� �����ߴ�.
	virtual void onRecvMyRoomCharacterStatResetOK(const int iStatNum, const UserItemAttrInfo & charAttr);

	/// �ɸ��� ���� ���� �����ߴ�.
	virtual void onRecvMyRoomCharacterStatResetFail(eMyRoomProtocol_STAT_RESET_FAILED_REASON failedReason);

	/// �ɸ��� ���� ���� ���� �����ߴ�.
	virtual void onRecvMyRoomCharacterStatConfirmOK(const UserItemAttrInfo& useritemAttr);

	/// �ɸ��� ���� ���� ���� �����ߴ�.
	virtual void onRecvMyRoomCharacterStatConfirmFail(eMyRoomProtocol_STAT_RESET_FAILED_REASON failedReason);

	/// ���� Ʈ���� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvMyRoomGetMyTrophyList(const std::vector < int > & trophyList);

	/// ���� Ʈ���� ����Ʈ�� �޴µ� �����ߴ�.
	virtual void onRecvMyRoomGetMyTrophyListFailed();

#ifdef _SELECTIVE_PACKAGE_
	///< ������ ���� ����ϴµ� �����ߴ�.
	void onRecvOpenSelectivePackageOK( int usedItemNum, const std::vector<RewardInfo> & rewardLis);

	///< ������ ���� ����ϴµ� �����ߴ�.
	void onRecvOpenSelectivePackageFailed(const eShopFailed_REASON failedReason, int requsetUseItemNum, eServerResult eResult);
#endif
	/// ���ָӴϸ� ����ϴµ� �����ߴ�.
	virtual void onRecvMyRoomUseLuckyBagOK( int usedItemNum, const std::map<int, BYTE/*count*/> & resultLottoItems, BYTE iCount);

	/// ���ָӴϸ� ����ϴµ� �����ߴ�.
	virtual void onRecvMyRoomUseLuckyBagFailed(int requsetUseItemNum, eServerResult eResult);

	/// �̱����� ������ �������� �����ߴ�.
	virtual void onRecvMyRoomGetLotteryStageInfoOK(const int lotteryNum, const std::vector <LotteryStateInfo> & myLotteryStageInfo);

	/// �̱����� ������ �������� �����ߴ�.
	virtual void onRecvMyRoomGetLotteryStageInfoFailed(const int lotteryNum, eServerResult eResult);

	/// �̱� �������� ����ϴµ� �����ߴ�.
	virtual void onRecvMyRoomUseLotteryOk(const int lotteryNum, eLotteryRewardType eRewardType, const int rewardValue);

	/// �̱� �������� ����ϴµ� �����ߴ�.
	virtual void onRecvMyRoomUseLotteryFailed(const int lotteryNum, eServerResult eResult);



	/// ���̷뿡�� ���̴� ����� ��
	//////////////////////////////////////////////////////////////////////////

	/// ���� �⺻ ������ �޾Ҵ�. 
	virtual void onRecvEnterFarmInfo(const FarmInfo& info, const FarmChattingInfo& farmChattingInfo);

	/// �濡 �����ߴ�.
	virtual void onRecvEnterRoom(const EnterRoomInfo & info, const std::vector<RecvFarmMapObjectInfo>& farmMapObjectInfoList, const std::vector<RecvFarmMapVoxelsInfo>& vecVoxels);

	/// ���ο� Ŭ���̾�Ʈ�� �濡 ���Դ�.
	virtual void addNewClient(int iPlayerIndex,const bool bReady,const BYTE followIndex,const int iState,const bool bIsNewEnterUser,const CNetPlayer * netPlayer);
	// ���� playerindex �� �޾Ҵ�.
	virtual void onRecvMyPlayerIndex(int iPlayerIndex);

	/// ���ο� �����̴�.
	virtual void onRecvSetMaster(unsigned int iPlayerIndex);

	/// ���� ���� ��� �����鿡�� ������ �޽����� �޾Ҵ�.
	virtual void onRecvForwardToAllRoomUser(const CPacketChunk & v);

	/// ���� ���� �츮 ������ ������ �޽����� �޾Ҵ�.
	virtual void onRecvForwardToMyTeamUser(const CPacketChunk & v);

	/// ���� ���� Ư�� ������ ������ ������ �޽����� �޾Ҵ�.
	virtual void onRecvForwardToRoomUser(const size_t from,const CPacketChunk & data);

	/// ä�� �޽����� �޾Ҵ�.
	virtual void onRecvChattingMsg(unsigned int nPlayerIndex, const char* data, size_t len);

	/// Ư�� ĳ������ ��ġ�� �޾Ҵ�.
	virtual void onRecvClientCharacterPosition(const BYTE numGameIndex, const ClientCharacterPosition & pos, const CPacketChunk & binData);

	/// on receive new follow index. if index indicate self, no follow move
	virtual void onRecvUpdateFollowIndex(const BYTE from, const BYTE to);

	/// ĳ���Ͱ� �ٲ����.
	virtual void onRecvChangeAvatar(unsigned int numPlayerIndex, const AdvancedAvatarInfo & advancedAvatarInfo);

	/// Ư�� ������ ���������� ���ŵǾ���.(���� ���ӷ뿡���� ȣ���.
	virtual void onRecvUpdateAvatar(unsigned int numPlayerIndex, const AdvancedAvatarInfo & advancedAvatarInfo);

	/// Ư�� ������ OnOff������ ������ ���ŵǾ���(���� ���ӷ뿡���� ȣ���).
	virtual void onRecvUpdateOnOffItem(unsigned int numGameIndex,const int iItemDescNum,const bool bOnOff);

	/// Ư�� ������ ž�� ���� ������ �ٲ����.
	virtual void onRecvChangeAnimalAvatar(unsigned int numPlayerIndex, const AnimalRacingAnimalAvatar & avatarInfo);

	/// Ư�� ������ ž�� ���� ������ �ٲ����.
	virtual void onRecvUpdateAnimalAvatar(unsigned int numPlayerIndex, const AnimalRacingAnimalAvatar & avatarInfo);

	/// �濡�� Ư�� ������ ������Ʈ�� ��� ������ �ߴ�.
	virtual void onRecvNotifyUserAction(BYTE byGameIndex, BYTE byAction, __int64 iOID);

	/// ���� ���¸� �޾Ҵ�.
	virtual void onRecvReadyStatus(unsigned int nPlayerIndex, bool bReady);

	/// ���� ����Ǿ���.
	virtual void onRecvMapChanged(const int numMap);

	/// ���� ����Ǿ���.
	virtual void onRecvRoomPlayerSelectTeam(BYTE byGameIndex, eTeam byTeamColor);

	/// �̹� ���� ���̾ �� ������ �����ߴ�.
	virtual void onRecvRoomPlayerSelectTeamFailedAlreadyReady();

	/// �̾�޸��⿡�� ���� ��ġ�� ����Ǿ���.
	virtual void onRecvRoomPlayerSelectRelayTeam(BYTE byGameIndex, eRelayTeamPosition byRelayTeamColor, eTeam eTeamColor);

	/// �̾�޸��⿡�� ���� ���°� ����Ǿ���.
	virtual void onRecvChangeSlotStateRelayTeam(eRelayTeam relayTeam, bool bClose);

	/// �̾�޸��⿡�� ���� ���°� ����Ǿ���.
	virtual void onRecvChangeSlotStateQuizTeam(eRelayTeamPosition relayTeam, bool bClose);

	/// �̾�޸��⿡�� ���� ���¸� �����ϴµ� �����ߴ�.
	virtual void onRecvChangeSlotStateRelayTeamFailed();

	/// �̾�޸��⿡�� ���� ���ڸ� �غ��Ѵ�.
	virtual void onRecvRelayPrepareNextRunner(BYTE numGameIndex);

	/// �̾�޸��⿡�� ���� ��ġ ������ ���Դ�.
	virtual void onRecvEnterBatonTouchArea(BYTE numGameIndex);

	/// �̾�޸��⿡�� ���� ��ġ ������ ����ߴ�.
	virtual void onRecvLeaveBatonTouchArea(BYTE numGameIndex);

	/// �̾�޸��⿡�� ���� ��ġ ����� �Դ�.
	virtual void onRecvBatonInput(BYTE numGameIndex, eBatonInput batonInput, int iParam);

	/// (�� �ȿ���)��� �̸��� ������Ʈ�Ǿ���.
	virtual void onRecvUpdateGuildInfo(BYTE numGameIndex, const std::string & strGuildName, int iGuildNum, eGuildMemberGrade eGrade, eGuildKind guildKind, const short guildLevel);

	/// (�� �ȿ���)Ŀ�� ������ ������Ʈ�Ǿ���.
	virtual void onRecvUpdateCoupleInfo(BYTE numGameIndex, const CoupleInfo & coupleInfo);

	/// ��ȥ�Ҽ� ������ �ʱ�ȭ �ϴµ� �����ߴ�.
	virtual void onRecvWeddingInitDivorceRequestInfoFailed();

	/// ��ȥ�Ҽ� ��û�� ���� ����� �Դ�.
	virtual void onRecvWeddingSuitForDivorceResult(const eServerResult eResult, const std::string & strMateNickname, eWeddingDivorceType eDivorceType);

	/// ��ȥ�Ҽ� ��û�� ���� ���� ����� �Դ�.
	virtual void onRecvWeddingSuitForDivorceResultFailed();

	/// ��ȥ ��û�� ���� ����� �Դ�.
	virtual void onRecvWeddingDivorceResult(const std::string & strMateNickname, eWeddingDivorceType eDivorceType, bool bEnforce);

	/// ��ȥ ��û�� ���� �����ߴ�.
	virtual void onRecvWeddingDivorceResultFailed();

	/// ���� ��ȯ���� ���� ������ �޾Ҵ�.
	virtual void onRecvGiftCouponRewardListInfo(int iCouponItemNum, std::map<eRewardCondition, std::vector<int> > & mapRewardInfoList);

	/// ���� ��ȯ���� ���� ������ �޴µ� �����ߴ�.
	virtual void onRecvGiftCouponRewardListInfoFailed();

	/// ���� ��ȯ�� ��뿡 ���� ����� �Դ�.
	virtual void onRecvGiftCouponReward(int iCouponItemNum, eRewardCondition eRewardType, int iReward);

	/// ���� ��ȯ�� ����� �����ߴ�.
	virtual void onRecvGiftCouponRewardFailed();

	/// ī�� ���� ���ۿ� ���� ó������� �Դ�.
	virtual void onRecvGiftCardSendResult(const eServerResult eResult, const std::string strRecvNickname);

	/// ���̼� �Ѹ������� Ű�� ���� ������ �Դ�.
	virtual void onRecvKeyInDoor(const OneInFour_KeyInDoor & info);

	/// ���� ���°� ����Ǿ���.
	virtual void onRecvRoomSlotChangeState(BYTE slotNum, bool bClosed);

	/// �� ������ �ٲ����.
	virtual void onRecvRoomTitleChange(const std::string & strTitle);

	/// �� ��ȣ�� �ٲ����.
	virtual void onRecvRoomPasswordChange(const std::string & strPassword);

	/// ���� ���� ��尡 �ٲ����.
	virtual void onRecvRoomSteppingModeChange(const bool bSteppingMode);

	/// ���� ������ ��尡 �ٲ����.
	virtual void onRecvRoomItemModeChange(const eItemMode itemMode);

	/// ���� �ɼ�(����,�н�����,������,�����۸��,���ǵ�������)�� �ٲ����.
	virtual void onRecvModifyRoomOption(const std::string strRoomTitle, const std::string strRoomPassword, 
										const bool bSteppingMode, const eItemMode itemMode
										);

	/// ����Ǿ���.
	virtual void onRecvRoomKicked(const BYTE numGameIndex);

	/// ���� ��� ������ �޾Ҵ�.
	virtual void onRecvRoomKickOutWarning(const KickOutWarning& beforeKickOutWarning, const KickOutWarning& kickOutWarning, bool bShowMessage);
	virtual void onRecvRoomKickOutWarningFailed();

	/// Ŀ�� ����ġ �߰� �������� ����ߴ�.
	virtual void onRecvMyRoomUseCoupleExpAdd(int iItemNum, bool bSelf);
	virtual void onRecvMyRoomUseCoupleExpAddFailed(eServerResult result);

	///���̷� ����
	//���̷� ���� : ������ ������ 
	void onRecvMyRoomSetSlotSettingFailed(eServerResult result);
	//���̷� ����: ������ �̸������� �ҷ����µ� ������
	void onRecvMyRoomGetUserSlotInfoFailed();
	//���̷� ����: ���� ������ ������ ������
	void onRecvMyRoomSetSlotItemSetting(int slotNum, AvatarInfo avatarInfo, std::string slotName);
	//���̷� ����: ���� ������ ������ �ҷ���
	void onRecvMyRoomGetUserSlotInfo(std::vector<MyRoomSlotInfo> vecSlotInfo);
	//���̷� ���� :���̷� ������ �����ϴµ� ������
	void onRecvMyRoomPayMyRoomSlotResultOK(int iMySlot);
	//���̷� ���� :���̷� ������ �����ϴµ� ������
	void onRecvMyRoomPayMyRoomSlotResultFailed(const eMyRoomProtocol_PAY_MYROOM_SLOT_RESULT_FAILED_REASON& failedreson);

	virtual void onRecvMyRoomFavoriteList(USER::eFavorite_LIST_RESULT result, const std::vector<int>& favorites);
	virtual void onRecvMyRoomFavoriteAddListAck(USER::eFavorite_ADD_RESULT result, int item);
	virtual void onRecvMyRoomFavoriteRemoveListAck(USER::eFavorite_REMOVE_RESULT result, int item);

	/// �ø��� �濡�� ������� ����� ���� ������ߴ�.
	virtual void onRecvOlympicRoomKicked();

	/// ���� ���� ī������ �ص� �ȴ�.
	virtual void onRecvStartCounting();

	/// ���� ���� ī������ �� �� ���� �����̴�.
	virtual void onRecvNotStartCounting(CStartCountFail::STATUS status);

	/// ���� ���� ī���� �� ��ҵǾ��ٴ� �޽���...
	virtual void onRecvStartCountingCancel();

	/// �ε��� �������ڴ� �޽����� �޾Ҵ�.
	virtual void onRecvStartLoading(const int numMap, const int iRandomSeed);

	/// �ε� ������ �����ߴٴ� �޽����� �޾Ҵ�.
	virtual void onRecvStartLoadingFail(eStartLoadingFail failNum);

	/// Mesh �ε��� �����ٴ� �޽����� �޾Ҵ�.
	virtual void onRecvEndMeshLoading(int iPlayerIndex);

	/// ��� �̵��� Mesh �ε��� �����ٰ� �޾Ҵ�.
	virtual void onRecvAllUserEndMeshLoading();

	/// �ε��� �����ٴ� �޽����� �޾Ҵ�.
	virtual void onRecvEndLoading(int iPlayerIndex);

	/// ��� �̵��� �ε��� �����ٰ� �޾Ҵ�.
	virtual void onRecvAllUserEndLoading();

	/// ���� ������ �����϶�� �޽����� �޾Ҵ�.
	virtual void onRecvStartGame(int iGameStartTick, int iNumberOfItem);

	/// ���� ���ʽ� EX�� �Ծ���
	virtual void onRecvBonusExEat(const int eatBonusIndex, std::vector<RewardInfo>& rewardList);

	/// ���� �� data �� �޾Ҵ�.
	virtual void onRecvData(int iPlayerIndex, const CPacketChunk & data);

	/// ���� �� event �� �޾Ҵ�.
	virtual void onRecvDataWithConfirm(int iPlayerIndex, int iEventType, const CPacketChunk & data);

	/// ������ tick �� �޴´�.
	virtual int getTick() const;

	/// �������κ����� tick �� �޾Ҵ�.
	/// iGameTick �� ������ �޽����� ���� ���� tick
	/// dwPingLoopTime �� ������ ������ ping �� ���� �� �ޱ������ �ð�. �� /2 �� �ϸ� ���µ� �ɸ� �ð��̴�.
	virtual void onRecvMasterTick(int iGameTick, DWORD dwPingLoopTime);

	/// �̹� ���� Random seed �� �޴´�.
	virtual void setRandomSeed(int);

	/// ������ �������� �Ծ���.
	virtual void onRecvEatItem(int iPlayerIndex, int iItemID, int iGameTick, int iItemKind, const int iMadeNextItemID, bool bMakeAndEat, int eatParam);

	/// ������ �Ա⸦ �����ߴ�.
	virtual void onRecvEatItemFailed(int iPlayerIndex, int iItemID, int iGameTick, int iMadeNextItemID, int iHaveItemID, int iHaveItemKind);

	/// ������ �ʿ��� ������ �������� �Ծ���.
	virtual void onRecvEatItemForRoomGenerate(int iPlayerIndex, const std::vector<MapEatItemInfo>& eat_item_list);

	/// ������ �ʿ��� ������ �������� ����߷ȴ�.
	virtual void onRecvDropItemForRoomGenerate(const std::vector<MapDropedItemInfo>& dropItemList, BYTE byUserIndex, int iSeed);

	/// ��Ÿ�� ������ make&eat�� �����ߴ�. LeftCoolTime = ������ ��Ŷ ���۽ÿ� ���� ��Ÿ�� �ð�. msec
	virtual void onRecvMakeEatItemCoolTimeFailed(int iItemKind, eRequestItem requestItemData, eGameItemMakeAndEat_Method gameItemMakeAndEat_Method, int argument, int leftCoolTime);

	/// ����� ������ �����Ѵ�. (�� ���� ������)
	virtual void onRecvDeleteDropedItemForRoomGenerate(const std::vector<int>& itemIDList, BYTE byUserIndex);

	/// ������ ������ ������ �����Ѵ�. (�� ���� ������)
	virtual void onRecvDeleteEquipedItemForRoomGenerate(const std::vector<int>& itemIDList, BYTE byUserIndex);

	/// ������ ������ ȹ��/������ ���� ������ �����Ǿ���.(�� ���� ������)
	virtual void onRecvPointNotifyForRoomGenerate(int user_index, const std::vector<int>& user_delta, const std::vector<int>& team_delta, const std::map<int/*user index*/, int/*point*/>& user_points, const std::map<eTeam, int>& team_points);

	/// ������ ����ũ �������� �Ծ���.
	virtual void onRecvGetUniqueItem(BYTE byPlayerIndex, int iItemID, int iGameTick, const int iMadeNextItemID);

	/// ������ ���� ���� �������� �Ծ���.
	virtual void onRecvGetBossAttackItem(BYTE byPlayerIndex, int iItemID, int iGameTick, const int iMadeNextItemID);

	/// ������ ������Ʈ ���ҽ� �������� �Ծ���.
	virtual void onRecvGetObjectResourceItem(BYTE byPlayerIndex, int iItemID, int iGameTick, const int iMadeNextItemID);

	/// ������ �������� ����ߴ�.
	virtual void onRecvUseItem(int iPlayerIndex, int iItemKind, int iGameTick, const CPacketChunk & useInfo);

	/// �������� ����ϴµ� �����Ͽ���.
	virtual void onRecvUseItemFailed();

	/// �������� ����� ó���� �Ѵ�.
	virtual void onRecvRemoveItem( int iPlayerIndex, bool isSuccess = true);

	/// ���м� ��ý�Ʈ �������� �޾Ҵ�.
	virtual void onRecvSpecialAssistItem(const std::vector < int > & assistItems);

	/// ��ý�Ʈ �������� ����ߴ�.
	virtual void onRecvUseAssistItem(int iPlayerIndex, int iItemID);

	/// ��ý�Ʈ �������� ����ϴµ� �����Ͽ���.
	virtual void onRecvUseAssistItemFailed(int iPlayerIndex, int iItemID);

	/// ������ �������� ������ �ߴ�.
	virtual void onRecvMakeItem(int iCanEatTick, int iItemKind, int iItemID, const CPacketChunk & data);

	/// �������� �ٽ� ������.
	virtual void onRecvRegenItem(GAME_ITEM iItemKind);

	/// ������ �ʿ��� �����Ǵ� �������� ������ �ߴ�.
	virtual void onRecvMakeItemForMapGenerate(int iCanEatGameTick, eMapGenerateItemType itemType, int iMadeNewItemID, const CPacketChunk & Data);

	/// ������ ���� ���� ���� �������� ��Ҵ�. ���� ���ڰ� ���� ���� �ε���, �ڰ� ���� ���� �ε���
	virtual void onRecvStepBirthdayCap(const BYTE numSteppedUserGameIndex, const BYTE numStepUserGameIndex);

	/// ������ �����.
	virtual void onRecvMakeFootBoard(const int iNumberOfFootBoard );

	/// ������ ������� ó���� �Ѵ�.
	virtual void onRecvStepFootBoard(const int iFootBoardIndex, const BYTE numPlayerIndex );

	/// ���� ����(?) �� ��� �� ó���� �Ѵ�.
	virtual void onRecvPassFootBoardArea();

	/// ���¡ ������ �ƴϴ�..
	virtual void onRecvAbusingUserListInfo(std::map<BYTE, AbusingInfo> & abusingInfoList);

	/// ������ �����̹� ��(����������)���� GameOver �ߴ�.
	virtual void onRecvGameOver(BYTE byPlayerIndex, eGameUserEventTypeResponse response);

	/// ������ �����̹� �ʿ��� ȥ�� ��Ƴ��Ҵ�.
	virtual void onRecvGameOverSurvive(std::vector<BYTE>& goalinList);

#ifdef _RANDOM_GAMEOVER

	/// Ż�� �����̹� ��忡�� üũ ����Ʈ�� ����ߴ�.
	virtual void onRecvServivalRandomGameoverCheckPoint(const BYTE channelCheckPoint, const BYTE byGameIndex, const std::vector<BYTE> & gameoverRankList);

	/// Ż�� �����̹� ��忡�� üũ ����Ʈ �Ÿ��� �޾Ҵ�.
	virtual void onRecvServivalRandomGameoverRaceLengthOK(const BYTE channelCheckPoint);
	virtual void onRecvServivalRandomGameoverRaceLengthFailed(const BYTE channelCheckPoint);

	/// Ż�� �����̹� ��忡�� Ż���������� �˷��ش�
	virtual void onRecvServivalRandomGameoverNotify(const BYTE channelCheckPoint, const bool isGameOver);

#endif

	/// �����̹� �ϻ�� �ʿ��� Ư�� üũ ����Ʈ�� ����ߴ�.
	virtual void onRecvPassSuvivalArithmeticCheckPoint(const DWORD dwLapTime, const int iTimeLimit, const int dwBonusTime, const bool bShow);

	/// �����̹� �ϻ�տ��� �� ������ ���ʷ� �� ������ ��Ҵ�.
	virtual void onRecvPassSteppedGoalBoard(BYTE byGameIndex, const int iRank);	

	/// �޸��� ������(�����) ���� ����Ʈ�� �޾ƿԴ�.
	virtual void onRecvRunQuizModeGetQuizList(RunQuizModeSelectData& runQuizInfo);

	/// �޸��� ������(�����) ���� ����Ʈ�� �ޱ� ���� ����.
	virtual void onRecvRunQuizModeGetQuizListFailed( eRunQuizModeResult reason );

	/// 1�� ������ ���� ������ ��Ƽ� Ÿ�Ӿƿ� ī��Ʈ ������ �Դ�.(���� ������ �ƴ�, 1�� ������ ������ �ο��鿡�Ը� �ѷ���.)
	virtual void onRecvTimeOutCount(const DWORD dwLapTime, const int iTimeLimit);

	/// ������ �����ߴ�.
	virtual void onRecvGoalInData(BYTE numPlayerIndex, DWORD dwLapTime, eGoalin flag);

	/// ȥ�μ��� �ܰ�� �Ѿ��.
	virtual void onRecvWeddingChangeAgreeState(eServerResult eResult);

	/// ȥ�� ���࿡ ���� �ߴ�.
	virtual void onRecvWeddingAgree(eServerResult eResult);

	/// ��ȥ�� �Ͽ� �κ��� ���谡 �Ǿ���.
	virtual void onRecvWeddingCreateCouple(eServerResult eResult, __int64 iCeremonyOfficerID);

	/// ���� �ð��� dwGametime ������ Ÿ�� ���� ī���͸� �����ض�.
	virtual void onRecvStartTimeOutCount(DWORD dwGametime, BYTE nTimeOutSeconds);

	/// ���� ��� ���� ������ ����� �޾Ҵ�.
	virtual void onRecvGameResultRewardInfo(std::vector<GameResultReward>& resultRewardList);

	/// ���� ����� �޾Ҵ�.
	virtual void onRecvGameResult(const GameResult& gameResult);

	/// ���� ����� �޾Ҵ�.
	virtual void onRecvGameResultItemEvent(std::vector<GameResultReward>& itemList);

	/// ���� �������� �ߴ�.
	virtual void onRecvLevelUpMe(eLevelUPKind levelKind, int iLevel);

	/// ���� ���� Ư�� ������ �������� �ߴ�.
	virtual void onRecvLevelUp(eLevelUPKind levelKind, BYTE byGameIndex, exp_type exp);

	/// ���ӹ濡�� �ٸ� ����� ������.
	virtual void onRecvOtherPlayerOut(size_t iPlayerIndex);

	/// ���ӹ濡�� �ڽ��� ������.
	virtual void onRecvThisPlayerOut(size_t iPlayerIndex);

	/// ���� �û� ȭ���� ������ ���ӷ����� ���ư���.
	virtual void onRecvMoveToGameRoom();

	///< ��ȸ ī������ �����.
	virtual void onRecvCancelSportsCount();

	///< ��ȸ ī������ �����ض�.
	virtual void onRecvStartSportsCount(const time_type tRemainTime);

	/// ��Ʈ���� ��������.... network error
	virtual void onDisconnectedFromServer();

	/// �޽��� �ڽ��� �����ֶ�� �޾Ҵ�.
	virtual void onRecvShowMsg(const std::string & strMsg);

	/// �ڵ����Ǵ� ������ ������ �޾Ҵ�.
	virtual void onRecvAutoUseItemInfo(const std::map<int,int>& useInfo );

	/// �� ������ �������� �ð��� ������.
	virtual void onRecvRoomUserFuncItemTimeOut(const BYTE numGameIndex, int iItemNum);
	virtual void onRecvRoomUserFuncItemTimeOut(const BYTE numGameIndex, const CActiveItems activeItems);

	/// �� ������ ������ �� �Ǿ���.
	virtual void onRecvRoomUserBuffItemTimeOut(const BYTE numGameIndex, int iItemNum);

	/// �������� ������ ��������.
	virtual void onRecvDisconnectFromServer(eServerResult eResult);

	/// �� ������ �Ƿε� �ð��� �޴´�.
	virtual void onRecvFatigue(const int iFatigueMinute);

	// ������ ���� ��ȿ�� ��� �̸����� üũ ����� �޾Ҵ�. bVaildGuildName == true �̸� ��ȿ�� ��� �̸�
	virtual void onRecvGuildCheckValidGuildNameResult(eGuildNameCheckResult byCheckResult);

	// ������ ���� ��带 ����µ� �����ߴٴ� ����� �޾Ҵ�.
	virtual void onRecvGuildMakeGuildSuccess();

	// ������ ���� ��带 ����µ� �����ߴٴ� ����� �޾Ҵ�.
	virtual void onRecvGuildMakeGuildFailed(eGuildMakeFailedReason byFailedReason);

	/// ��� ��ü ��û�� ó���ߴ�.
	virtual void onRecvGuildDeleteGuild();
	virtual void onRecvGuildDeleteGuildFailed(eGuildFailReason eReason);

	/// ��� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvGuildGetGuildList(const std::vector<GuildInfo>& guildList, int totalGuildListCount, const GuildSearchArg& arg);
	virtual void onRecvGuildGetGuildListFailed();

	/// ��� ���� ����� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvGuildGetJoinWaitMemberList(const std::vector<GuildWaiterInfo>& guildWaiterList);
	virtual void onRecvGuildGetJoinWaitMemberListFailed();

	/// ��� ���� ��û�� ����� �޾Ҵ�.
	virtual void onRecvGuildJoinRequest(eGuildJoinMethod eMethod, const std::string& strGuildName);
	virtual void onRecvGuildJoinRequestFailed(eGuildFailReason eReason, int iLimmitCount);

	/// ��� ���� ��û ��� ����� �޾Ҵ�.
	virtual void onRecvGuildCancelPropose(const std::string& strGuildName);
	virtual void onRecvGuildCancelProposeFailed(eGuildFailReason eReason);

	/// ��� ��� ���� �˶� �޽����� �޾Ҵ�.
	virtual void onRecvGuildNotify(const UserAlarmInfo& guildNotice);

	/// ��� ���� ��û�� ����/���� ó���� �ߴ�.
	virtual void onRecvGuildProcessJoinRequest(const std::string& strNickName, bool bAccept);
	virtual void onRecvGuildProcessJoinRequestFailed(eGuildFailReason eReason);

	/// ��忡�� ������ ��û�� ó���߽��ϴ�.(��Ż/�߹�)
	virtual void onRecvGuildProcessLeave(const std::string& strMemberNickName, bool bBySelf, const int guildLevel);
	virtual void onRecvGuildProcessLeaveFailed(eGuildFailReason eReason);

	// ��� ���� ���� ���� ���� ��û�� ó���߽��ϴ�.
	virtual void onRecvGuildModifyJoinLimmitLevel(short iLevel);
	virtual void onRecvGuildModifyJoinLimmitLevelFailed(eGuildFailReason eReason);

	// ��� ���� ���� ���� ��û�� ó���߽��ϴ�.
	virtual void onRecvGuildModifyJoinMethod(eGuildJoinMethod eMethod);
	virtual void onRecvGuildModifyJoinMethodFailed(eGuildFailReason eReason);

	// ��� ��ũ ���� ��û�� ó���߽��ϴ�.
	virtual void onRecvGuildModifyMark(int iMark);
	virtual void onRecvGuildModifyMarkFailed(eGuildFailReason eReason);

	// ������ ��� ���� ��û�� ó���߽��ϴ�.
	virtual void onRecvGuildModifyMemberGrade(const std::string& strMemberNickName, eGuildMemberGrade eGrade);
	virtual void onRecvGuildModifyMemberGradeFailed(eGuildFailReason eReason);

	// ����� �޽��� ���� ��û�� ó���߽��ϴ�.
	virtual void onRecvGuildModifyMessage(const std::string& strMessage);
	virtual void onRecvGuildModifyMessageFailed(eGuildFailReason eReason);

	// ����� �̸� ���� ��û�� ó���߽��ϴ�.
	virtual void onRecvGuildModifyName(const std::string& strBeforeName, const std::string& strName, int iItemNum, int iRemainItemCount);
	virtual void onRecvGuildModifyNameFailed(const std::string& strName, int iItemNum, eGuildFailReason eReason);

	// ��� ������ ��û�� ó���߽��ϴ�.
	virtual void onRecvGuildLevelUp(short iLevel);
	virtual void onRecvGuildLevelUpFailed(eGuildFailReason eReason);

	// ��� ���� ��û�� ó���߽��ϴ�.
	virtual void onRecvGuildGetGuildInfo(const GuildDetailInfo & info);
	virtual void onRecvGuildGetGuildInfoFailed(eGuildFailReason eReason);

	// ��� ������ ���� �̾��� ó���߽��ϴ�.
	virtual void onRecvGuildConveyanceMaster(const std::string& strNewMasterNickName, int iItemNum, int iRemainCount);
	virtual void onRecvGuildConveyanceMasterCandidates(std::vector<std::string> vecCandidate);
	virtual void onRecvGuildConveyanceMasterFailed(eGuildFailReason eReason);

	// ��� ����Ʈ �߰� �������� ����߽��ϴ�.
	virtual void onRecvGuildIncreaseGuildPoint(int iItemNum, int iRemainCount);
	virtual void onRecvGuildIncreaseGuildPointFailed(eGuildFailReason eReason);

	// ���� ���� ��û�� ��� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvGuildProposeListNotify();

	// ��� ��������Ʈ ��û�� ó���߽��ϴ�.
	virtual void onRecvGuildGetMyContributionPoint(const int iContributionPoint);
	virtual void onRecvGuildGetMyContributionPointFailed(eGuildFailReason eReason);

	// ��� ����Ʈ ��û�� ó���߽��ϴ�.
	virtual void onRecvGuildGetGuildPoint(const __int64 iGuildPoint);
	virtual void onRecvGuildGetGuildPointFailed(eGuildFailReason eReason);

	// ��� �������� ���� �������� ��뿡 ���� ����� �޾Ҵ�.
	virtual void onRecvGuildUseGiftBox(int iReceivedItemNum, int iGiftBoxItemNum, int iReaminItemCount);
	virtual void onRecvGuildUseGiftBoxFailed(eGuildFailReason eReason);

	// �ý��� ��� ������ �ߴ�
	virtual void onRecvGuildGraduationOK();
	virtual void onRecvGuildGraduationFailed();

	// ��ų ���� ��û�� ���� ����� �޾Ҵ�.
	virtual void onRecvGuildSkillAdd( GuildDetailInfo& guildInfo, std::map<int, int> &mapItemList );
	virtual void onRecvGuildSkillAddFailed( eGuildSkillCheckAvailabilityType result );

	virtual void onRecvGuildSkillReset( GuildDetailInfo& guildInfo );
	virtual void onRecvGuildSkillResetFailed( eGuildSkillCheckAvailabilityType result );

	/// ��� ���� ���� �˶� �޽����� �޾Ҵ�.
	virtual void onRecvGuildPlantNotify(const UserAlarmInfo& guildNotice);

	//!< ��� � TR  ��û ������ �޾Ҵ�.
	virtual void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR);
	virtual void onRecvGuildPlantGetGuildManagerTRFailed(eGuildPlantFailReason iFailedReason);

	//!< ��� � TR �� ���ڿ� �����ߴ�.
	virtual void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR);
	//!< ��� � TR �� ���ڿ� �����Ͽ���.
	virtual void onRecvGuildPlantInvestGuildManagerTRFailed(eGuildPlantFailReason iFailedReason);

	//!< ��� � TR â�� Ȯ�� ������ ��û �����ߴ�.
	virtual void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue);
	//!< ��� � TR â�� Ȯ�� ������ ��û �����Ͽ���.
	virtual void onRecvGuildPlantGetStorageExtendFailed(eGuildPlantFailReason iFailedReason);

	//!< ������ ������ ���� ����� �����ߴ�.
	virtual void onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR);
	//!< ������ ������ ���� ����� �����Ͽ���.
	virtual void onRecvGuildPlantRegisterItemFailed(eGuildPlantFailReason iFailedReason);

	//!< ������ ���� ���� ������ ������ ��û �����ߴ�
	virtual void onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind);
	//!< ������ ���� ���� ������ ������ ��û �����Ͽ���.
	virtual void onRecvGuildPlantGetMakeProgressItemFailed(eGuildPlantFailReason iFailedReason);

	//!< ������ ���� ��� ������ ����Ʈ�� ��û �����ߴ�
	virtual void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant);
	//!< ������ ���� ��� ������ ����Ʈ�� ��û �����Ͽ���.
	virtual void onRecvGuildPlantGetMakeStandByItemFailed(eGuildPlantFailReason iFailedReason);

	//!< ������ ���� �⿩ �������� ���� �����ߴ�.
	virtual void onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum);
	//!< ������ ���� �⿩ �������� ���� �����Ͽ���.
	virtual void onRecvGuildPlantChangeMyConstributionPointItemFailed(eGuildPlantFailReason iFailedReason);

	//!< ��� � TR ������ ����Ʈ�� ��û �����ߴ�
	virtual void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList);
	//!< ��� � TR ������ ����Ʈ�� ��û �����Ͽ���.
	virtual void onRecvGuildPlantGetInvestorManagerTRFailed(eGuildPlantFailReason iFailedReason);

	//!< ��� ��ȭ ���� ����Ʈ�� ��û �����ߴ�
	virtual void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList);
	//!< ��� ��ȭ ���� ����Ʈ�� ��û  �����Ͽ���.
	virtual void onRecvGuildPlantGetExpenseListFailed(eGuildPlantFailReason iFailedReason);

	//!< ������ ������ �⿩�� ���� ����Ʈ�� ��û �����ߴ�
	virtual void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList);
	//!< ������ ������ �⿩�� ���� ����Ʈ�� ��û �����Ͽ���.
	virtual void onRecvGuildPlantGetItemContributeRankLIstFailed(eGuildPlantFailReason iFailedReason);

	//!< ������ ���� ���� ���� ����Ʈ�� ��û �����ߴ�.
	virtual void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList);
	//!< ������ ���� ���� ���� ����Ʈ�� ��û �����Ͽ���.
	virtual void onRecvGuildPlantGetGivePossibleUserListFailed(eGuildPlantFailReason iFailedReason);

	//!< ������ ������ ���޸� ��û �����ߴ�.
	virtual void onRecvGuildPlantGiveGiftOK(int iItemIndexNum);
	//!< ������ ������ ���޸� ��û �����Ͽ���.
	virtual void onRecvGuildPlantGiveGiftFailed(eGuildPlantFailReason iFailedReason);

	//!< ������ ������ ����Ʈ�� ��û �����ߴ�
	virtual void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList);
	//!< ������ ������ ����Ʈ�� ��û �����Ͽ���.
	virtual void onRecvGuildPlantGetPlantItemListFailed(eGuildPlantFailReason iFailedReason);

	//!< ������ ������ ���Ÿ� ��û �����ߴ�
	virtual void onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount);
	//!< ������ ������ ���Ÿ� ��û �����Ͽ���.
	virtual void onRecvGuildPlantBuyItemFailed(eGuildPlantFailReason iFailedReason);

	/// ��Ÿ�� �̺�Ʈ ������ �޾Ҵ�.
	virtual void onRecvHotTimeEventInfoAck(const std::map<__int64, HotTimeEventInfo> & hotTimeEventInfo);

	/// ������ ��Ÿ�� ������ �޾Ҵ�.
	virtual void onRecvHotTimeEventSettingAck(const bool bUpdateSetting, const HotTimeEventInfo & hotTimeEventInfo);

	/// ��Ÿ�� �̺�Ʈ ���� ������ �����Ͽ���
	virtual void onRecvHotTimeEventSettingFaildAck(eHotTimeEventFailedReason failReason);

	/// ��Ÿ�� �̺�Ʈ ������ �����ߴ�.
	virtual void onRecvHotTimeEventDeleteAck(const __int64 iHotTimeEventID);

	/// ������ ��Ÿ�� �̺�Ʈ ���� �����ߴ�.
	virtual void onRecveHotTimeEventApplyAck(const __int64 iHotTimeEventID);

	/// ������ ��Ÿ�� �̺�Ʈ ���� �����ߴ�.
	virtual void onRecveHotTimeEventApplyFaildAck(const eHottimApplyFailedReason hotTimeResult, const __int64 iHotTimeEventID);

	/// Ʃ�丮�� �ڵ� (Agent ������ �����͸� DB�� �����ϵ��� ��û�� ���� ���� ����� �޾Ҵ�.)
	virtual void onRecvTutorialInsertMyData(std::string strValue, int iValue);

	/// Ʃ�丮�� �ڵ� (Agent ������ �����͸� DB�� �����ϵ��� ��û�� ���� ���� ����� �޾Ҵ�.)
	virtual void onRecvTutorialInsertMyDataFailed(eServerResult eResult);

	/// Ʃ�丮�� �ڵ� (Room ������ �����͸� DB�� ���ſ� ���� ���� ����� �޾Ҵ�.)
	virtual void onRecvTutorialUpdateMyDataFailed(std::string strValue, int iValue);

	/// Ʃ�丮�� �ڵ� (Room ������ �����͸� DB�� ���ſ� ���� ���� ����� �޾Ҵ�.)
	virtual void onRecvTutorialUpdateMyDataFailed(eServerResult eResult);

	////////////////////////////////////////////////////////////////////////////////
	/// ����� ����

	/// ������� ���� ����� ������ ����
	virtual void onRecvGuildMatchGetGuildInfo( const eOCCUPATION_AREA_TYPE eOccupationAreaType, std::vector<GuildMatchRankInfo> rankInfo);

	/// ������� ���� ��� ���� �ޱ� ����
	virtual void onRecvGuildMatchGetGuildInfoFailed(eGuildMatchType matchType, eGuildMatchFailedReason failedReason);

	/// ����� �ֱ� ������ ���� ������ ����
	virtual void onRecvGuildMatchGetLatestInfo(eGuildMatchType matchType, std::vector<GuildMatchLatest> matchLatest);

	/// ����� �ֱ� ������ ���� ���� �ޱ� ����
	virtual void onRecvGuildMatchGetLatestInfoFailed(eGuildMatchType matchType, eGuildMatchFailedReason failedReason);

	/// ����� ��ŷ ������ ����
	virtual void onRecvGuildMatchRankInfo(eServerResult result, eGuildMatchFailedReason failedReason, eRequestRankKind rankKind, std::vector<GuildMatchRankInfo>& rankList);

	/// ����� ���� ����� ��ŷ ������ ����
	virtual void onRecvGuildMatchMyGuildRankInfo(eRequestRankKind rankKind, GuildMatchRankInfo rankInfo);

	/// ����� ��ŷ ���� �ޱ⸦ ��������
	virtual void onRecvGuildMatchMyGuildRankInfoFailed(eRequestRankKind rankKind, eGuildMatchFailedReason failedReason);

	/// ���� ���� ����� ���� ������ �޾Ҵ�..
	virtual void onRecvGuildMatchNoticeNextOfficialGameInfo(OlympicGameInfo& gameInfo);

	/// ���� ���� ����� ���� ������ �޾Ҵ�..
	virtual void onRecvGuildMatchNextOfficialGameInfo(OlympicGameInfo& gameInfo);

	/// ���� ����� ������ ����
	virtual void onRecvGuildMatchOfficialEmpty();

	/// ��� �˻��� �Ϸ��Ͽ���
	virtual void onRecvGuildMatchSearchGuildPartyOK();

	/// ����� ��ġ ������ �����Ͽ���
	virtual void onRecvGuildMatchActionOK(eGuildMatchAction action);

	/// ����� ��ġ ������ �����Ͽ���
	virtual void onRecvGuildMatchActionFailed(eGuildMatchAction action, eGuildMatchFailedReason failedReason);

	/// ����� ����� ����
	virtual void onRecvGuildMatchRegistMatchOK(eGuildMatchType matchType, const bool bAllReady);

	/// ����� ��Ī ���ۿ� ���� ����
	virtual void onRecvGuildMatchActionNotify(eGuildMatchAction action, GuildMatchPartyInfo& partyInfo, bool bRequestParty, eRoomKind roomKind);

	/// ���� ��Ƽ ���� �ޱ⸦ ����
	virtual void onRecvGuildMatchMyPartyInfoOK(const bool success, GuildMatchPartyInfo& partyInfo);

	/// ���� ��Ƽ ���� �ޱ⸦ ����
	virtual void onRecvGuildMatchMyPartyInfoFailed();

	/// ����� ����� ��Ƽ�� ������ �����
	virtual void onRecvGuildMatchOtherPartyInfoOK(const bool success, GuildMatchPartyInfo& partyInfo);

	/// ���� ��Ƽ ID �Ҵ��� ����
	virtual void onRecvGuildMatchGetPartyIDOK(const __int64 partyID);

	/// ���� ��Ƽ ID �Ҵ��� ����
	virtual void onRecvGuildMatchGetPartyIDFailed(eGuildMatchFailedReason failedReason);
	
	/// ��Ƽ�� �����Ͱ� ����Ǿ���
	virtual void onRecvGuildMatchChangePartyMaster(const __int64 partyID, const UINT masterIndex);

	/// ������ ���������� Scene ��⸦ �Ѵ�
	virtual void onRecvGuildMatchRemakePartyWaitSceneChange(eRoomKind roomKind);

	/// ���� �����ض�
	virtual void onRecvGuildMatchChangeRoomKindNotify(const eRoomKind roomKind);

	/// ��Ƽ ����� ��ҵǾ���
	virtual void onRecvGuildMatchUnRegistPartyACK(const bool bSuccess);

	/// ��� ��ġ ������ ó���Ѵ� (���, ����, ���� ��Ȳ�϶� ���и� ����� �������� UI�ݱ� ó���� ���Ѱ�
	virtual void onRecvGuildMatchMatchActionACK(eGuildMatchAction action);

	/// ��Ī �˻��� �ٽ� �ض�
	virtual void onRecvGuildMatchSearchingPartyRetry();

	/// ��Ī ���� ��û�� �����Ͽ���
	virtual void onRecvGuildMatchSearchingPartyStartACK(eGuildMatchType matchType,const bool bSuccess);

	/// ��Ī �˻��� �Ϸ��� �ϴµ� �߸��Ǿ� �����ߴ� (���� ��Ȳ)
	virtual void onRecvGuildMatchSearchingPartyFailed(eGuildMatchFailedReason failedReason);

	/// ��Ī �˻��� �׸��д�, ��Ī�� �������� ���ߴ�
	virtual void onRecvGuildMatchSearchingMatchStop();

	/// ����� ��� �޽���
	virtual void onRecvGuildMatchGuildMsg(eGuildMatchType matchType, std::string& oppGuildName, bool bWinTeam, const int successiveWin);

	/// ��Ī�� ����Ͽ���
	virtual void onRecvGuildMatchSearchingPartyCancel();

	/// �������� ����� ��Ī�뿡 ���� ���⸦ �����ߴ�
	virtual void onRecvGuildMatchObserverEnterRoomReservationOK();

	/// �������� ����� ��Ī�뿡 ���� ���� ������ �����ߴ�
	virtual void onRecvGuildMatchObserverEnterRoomReservationFailed(eGuildMatchFailedReason failedReason);

	/// ������ �ʴ��ؾ� �� �������� �г����� �޾Ҵ�
	virtual void onRecvGuildMatchObserverEnterRoomData(std::string observerNickName);

	/// ����ġ �÷���Ƚ�� ���� �ִ°�� ��Ī ���� �ż���
	virtual void onRecvGuildMatchPlayStartLimitFailed(eGuildMatchFailedReason failedReason);

#ifdef _RAINBOW_LEAGUE
	///< ���κ��� ���� ���������� �޾Ҵ�
	virtual void onRecvRainbowGetUserInfoOK(RainbowLeagueUserInfo & userInfo);
	virtual void onRecvRainbowGetUserInfoFailed(eRainbowLeagueFailedReason failedReason);

	///< ��ġ ����� �޾Ҵ�
	virtual void onRecvRainbowGetDispositionResultOK(bool bIsResult, eRainbowLeagueType leagueType, int iTotalPoint);
	virtual void onRecvRainbowGetDispositionResultFailed(eRainbowLeagueFailedReason failedReason);

	///< ��, �������� ����
	virtual void onRecvRainbowDispositionRewardOK(eLevelUPKind rewardType, eRainbowLeagueKind leagueKind, int rewardLevel, std::vector<RewardInfo> & vecRewardInfo);
	virtual void onRecvRainbowDispositionRewardFailed(eRainbowLeagueFailedReason failedReason);

	///< ���κ��� ���� ��� ��� �� �޾Ҵ�
	virtual void onRecvRainbowGetLatestRecordOK(int iMapNum, RainbowLeagueLatestInfo & latestInfo, eRainbowLeagueKind matchKind, eRainbowLeagueType matchType, int iPoint);
	virtual void onRecvRainbowGetLatestRecordFailed(eRainbowLeagueFailedReason failedReason);

	///< ��Ī �̴ϰ��� ������ �޾Ҵ�
	virtual void onRecvRainbowMiniGameStartOK();
	virtual void onRecvRainbowMiniGameStartFailed(eRainbowLeagueFailedReason failedReason);

	///< ��Ī �̴ϰ��� ����� �޾Ҵ�
	virtual void onRecvRainbowMiniGamePointOK(exp_type iExp, int iGameMoney);
	virtual void onRecvRainbowMiniGamePointFailed(eRainbowLeagueFailedReason failedReason);

	/// ���� ���� ��ġ �ޱ� ����� �޾Ҵ�
	virtual void onRecvRainbowLeagueKindChangeAck(eRainbowLeagueKind leagueKind, eRainbowLeagueType leagueType, std::vector<RewardInfo> & vecConsumeList);
	virtual void onRecvRainbowLeagueKindChangeFailed(eRainbowLeagueFailedReason failedReason);

	///< �����ϱ� ��û�� �����Ͽ���
	virtual void onRecvRainbowLeagueSearchingDoingAck(int iEntryTime);

	///< �����ϱ� �ٽ� ��û�� �ض�
	virtual void onRecvRainbowLeagueSearchingRetry();

	///< ������ ��븦 ã�� ���ߴ�(������ Ŭ�󿡰� �׸��϶�� �˸���)
	virtual void onRecvRainbowLeagueSearchingMatchStop();

	///< ���� ��� ��ã���� �ƴ϶� ������ �߸��Ǿ� ����ó�� �� ��Ȳ
	virtual void onRecvRainbowLeagueSearchingFailed(eRainbowLeagueFailedReason failedReason);

	///< ���κ��� ��Ƽ ������ �˷��ش�
	virtual void onRecvRainbowLeagueMyPartyInfoNotify(RainbowLeaguePartyInfo & partyInfo);

	///< ���κ��� ��Ƽ �����Ϳ��� �˷��ش�. ���� ������
	virtual void onRecvRainbowLeagueActionNotify(eRainbowLeaguePartyState state, int iMatchingPointAVG);

	///< ���κ��� �� �ְ� ����� �޾Ҵ�
	virtual void onRecvRainbowLeagueTopRecordNotify(int iClearTime);

	///< �����ϱ� ������ ��ҿ� ���� �׸��д�
	virtual void onRecvRainbowLeagueSearchingCancel();

	///< ���κ��� �г�Ƽ ������ �޾Ҵ�
	virtual void onRecvRainbowLeaguePenaltyNotify(int restrictTime);

	///< ���κ��� �г�Ƽ ��������� �޾Ҵ�
	virtual void onRecvRainbowLeaguePenaltyResultNotify(eRainbowLeagueKind matchKind, eRainbowLeagueType matchType, eRainbowLeagueResult rainbowLeagueResult, int iResultPoint
#ifdef _CHAMPIONS_CUP
		, bool bIsAddPlayCount
#endif		
		);

	///< ���κ��� ��ŷ ��û
	virtual void onRecvRainbowLeagueRankInfo(eServerResult result, eRainbowLeagueFailedReason failedReason, eRequestRankKind rankKind, eRankDetailKind rankDetailKind, const std::vector<RainbowLeagueRankInfo> & rankInfo);

	///< ���� ���κ��� ��ŷ ���
	virtual void onRecvRainbowLeagueMyRankInfo(eRequestRankKind rankKind, eRankDetailKind rankDetailKind, RainbowLeagueRankInfo & rankInfo);
	virtual void onRecvRainbowLeagueMyRankInfoFailed(eRequestRankKind rankKind, eRankDetailKind rankDetailKind, eRainbowLeagueFailedReason failedReason);

#endif

	//////////////////////////////////////////////////////////////////////////
	/// ī���� ����

	// ī���� ���� ������ �޾Ҵ�. 
	virtual void onRecvCardPackOpenReward(const int cardPackNum, const short openType, std::vector<RewardInfo> & vRewardItem);

	// ī���� ���� ������ �ޱ� �����ߴ�.
	virtual void onRecvCardPackOpenFailed( eCardPackOpenRewardFailedReason failedreason );

	//////////////////////////////////////////////////////////////////////////

	// �ٸ� ������ �г����� �����ߴٰ� �޾Ҵ�.
	virtual void onRecvNickNameChangeNotify(const std::string& strNewNickName, const std::string& strOldNickName);

	// GM ��� �޽���
	virtual void onRecvGMWarningMsg(std::string& msg);

	/// ������ ����Ʈ ������ �޾���
	virtual void onRecvQuestUserInfo(eQuestServerResult result, const bool bComplete, QuestUserInfoMap& questUserInfoMap);

	/// ����Ʈ ������ ���� ���
	virtual void onRecvQuestAddAck(eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList);

	/// ����Ʈ ���⿡ ���� ���
	virtual void onRecvQuestRemoveAck(eQuestServerResult result, const int questNum);

	/// ����Ʈ �Ϸῡ ���� ���
	virtual void onRecvQuestRewardAck(eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList);

	/// �̺�Ʈ ����Ʈ ���� ����
	virtual void onRecvQuestEventNotify(bool bActive, std::set<int>& questNumList);


#ifdef NPC_EVENT
	/// ����Ʈ �����ϱ� ����
	virtual void onRecvQuestInterrogationInfoAck(eQuestServerResult result, const QuestInterrogationInfo questInterrogationInfo);

	/// ����Ʈ �����ϱ� �������
	virtual void onRecvQuestInterrogationConsumeAck(eQuestServerResult result, const int npcNum);

	/// ����Ʈ �����ϱ� �亯 ����
	virtual void onRecvQuestInterrogationQuestionAck(eQuestServerResult result, const int npcNum, std::vector<int>& nextNumList);

	/// ����Ʈ �����ϱ� �Ϸῡ ���� ��� (����)
	virtual void onRecvQuestInterrogationFinishAck(eQuestServerResult result, const int npcNum, const int iLevel, std::vector<IntegratedReward>& rewardList);

	/// NPC �����ϱ� ��� (����)
	virtual void onRecvQuestInterrogationRewardAck(eQuestServerResult result, const int npcNum, const int iLevel, std::vector<IntegratedReward>& rewardList);

	/// NPC �����ϱ� ������
	virtual void onRecvQuestInterrogationScheduleAck(std::map<int, QuestInterrogationScheduleInfo>& schedule);
#endif

#ifdef LOBBY_QUEST_CHANNEL_SYSTEM
	/// ������ ä������Ʈ ������ �޾���
	virtual void onRecvLobbyQuestUserInfo(eQuestServerResult result, const bool bComplete, QuestUserInfoMap& questUserInfoMap);

	/// ä������Ʈ ������ ���� ���
	virtual void onRecvLobbyQuestAddAck(eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList);

	/// ä������Ʈ ���⿡ ���� ���
	virtual void onRecvLobbyQuestRemoveAck(eQuestServerResult result, const int questNum);

	/// ä������Ʈ �Ϸῡ ���� ��� (����)
	virtual void onRecvLobbyQuestRewardAck(eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList);

	/// �̺�Ʈ ä������Ʈ ���� ����
	virtual void onRecvLobbyQuestEventNotify(bool bActive, std::set<int>& questNumList);
#endif

	/// ���� ���̵� ����� �� ���� ���������� �˷��ش�
	virtual void onRecvSimpleIDInvalidContentsNotify();

	/// Room Kind �� �Ӽ��� �޾���.
	virtual void onRecvRoomKindAttr(const RoomKindAttr& roomKindAttr, bool bValid);

	/// �ƴ��� ������ ������ �޾Ҵ�.
	virtual void onRecvAnubisExpeditionGetInfo(const AnubisExpeditionInfo & scheduleInfo, std::map<eRoomKind, int> & runInfo);

	/// �ƴ��� ������ ���� ������ �޾Ҵ�.
	virtual void onRecvAnubisExpeditionGetUserInfo(const int iPoint);
 
	/// �ƴ��� ������ ���� ���� ������ �޾Ҵ�.
	virtual void onRecvAnubisExpeditionEndGameNotify();

#ifdef SPORTS_PLAY_LIMIT_CHECK
	/// ��ȸ �Ϻ� ���۽ð��� �޾���
	virtual void onRecvSportsPlayLimit(const UserSportsPlayLimit& sportsPlayLimit, BOOL playable);
#endif

	//////////////////////////////////////////////////////////////////////////

#ifdef _EXCHANGE_SYSTEM
	/// ��ȯ �ý��� ��� ����
	virtual void onRecvExchangeSystemGetUseInfo(eExchangeSystem systemType, const eExchangeSystemResult result);

	/// ��ȯ �ý��� ��ȯ ����
	virtual void onRecvExchangeSystemExchangeOK(std::vector<RewardInfo>& resultList, int count);

	/// ��ȯ �ý��� ��ȯ ����
	virtual void onRecvExchangeSystemExchangeFailed(eExchangeSystemResult result);
#endif

#ifdef _COMBINATION_SHOP_
	/// ���� �ý��� ��� ����
	virtual void onRecvCombinationShopGetUseInfo(eCombinationShop systemType, const eCombinationShopResult result);

	/// ���� �ý��� ����,���� ����
	virtual void onRecvCombinationShopNotify(eCombinationShop systemType, const bool bIsVisible);

	/// ���� �ý��� ���� ���� ����Ʈ ����
	virtual void onRecvCombinationShopGetLimitInfoInfoOK(eCombinationShop systemType, std::map<int, int>& countList);

	/// ���� �ý��� ���� ���� ����Ʈ ����
	virtual void onRecvCombinationShopGetLimitInfoInfoFailed(eCombinationShop systemType, eCombinationShopResult result);

	/// ���� �ý��� �ǽð� ���� ������ ����Ʈ ����
	virtual void onRecvCombinationShopGetItemDetailInfoOK(std::map<int, CombinationShopItemDetailInfo>& itemList);

	/// ���� �ý��� ��ȯ ����
	virtual void onRecvCombinationShopExchangeOK(bool bSucess, std::vector<RewardInfo>& resultList);

	/// ���� �ý��� ��ȯ ����
	virtual void onRecvCombinationShopExchangeFailed(eCombinationShopResult result);
#endif

	/// ������ ��ȯ ���
	virtual void OnRecvItemConvertAck(const item_convert::CDoConvertResult& result);

	//!< DB ���� ��ũ��Ʈ ������Ʈ ���
	virtual void OnRecvEventStatusUpdateAck(const CEventStatusUpdateAck& ack);
	//!< DB ���� ��ũ��Ʈ ���� ���� ���
	virtual void OnRecvEventStatusExecAck(const CEventStatusExecAck& ack);
	//!< DB ���� ��ũ��Ʈ ���� ���
	virtual void OnRecvEventStatusQueryAck(const CEventStatusQueryAck& ack);


	//////////////////////////////////////////////////////////////////////////
	// Ŀ�´�Ƽ ���� ���� ����

	/// Ŀ�´�Ƽ ������ ���� ����
	virtual void community_onConnectFail(eCommunityConnectFail failReason);

	/// ģ�� �ƹ�Ÿ ������ �޾Ҵ�.
	virtual void community_onRecvFriendAvatarInfo(const std::string & strFriendNickname, const exp_type iExp
#ifdef _NUMBERS
		, const int iNumbers
#endif
		, const AvatarInfo & avatarInfo);


	/// �޽����� �޾Ҵ�.
	virtual void community_onRecvMsg(const std::string & strNickname, const std::string & strMsg);

	/// �޼����� ���� ������ �޾Ҵ�.
	virtual void community_onRecvMsgAck(const std::string& strNickName, const std::string& strMsg, eMessageResult messageResult);

	/// �޽����� ������ ���ϰ� �ٽ� ����
	virtual void community_onRecvForwardingMsgFailed(const std::string & strFromNickName, eForwardingFailed eResult);

	/// ä�� �Ӹ� �޼��� ��û�� �޾Ҵ�.
	virtual void community_onRecvWhisperMsgReq(const std::string & strNickname, const byte byUserAttr, const std::string & strMsg);

	/// ä�� �Ӹ� �޼��� ������ �޾Ҵ�.
	virtual void community_onRecvWhisperMsgAck(const std::string & strNickname, const byte byUserAttr, const std::string & strMsg, const eWhisperRequestResult whisperRequestResult);

	/// �Ϲ�, ����, ��� ä�� �޼����� �޾Ҵ�.
	virtual void community_onRecvChatting(const std::string & strNickname, const std::string & strMsg, eChattingType chattingType);

	/// �������� ���¸� �޾Ҵ�.
	virtual void community_onRecvState(const std::string & strNickname, const UserState & state);

	/// ģ�� �߰��� �����ߴ�.
	virtual void onRecvAddFriendOK(const std::string & strNickname);

	/// ģ���� ���� ���¸� �޾Ҵ�.
	virtual void community_onRecvGameState(const std::string & strFriendNickname, bool bPlayGame);

	/// ģ�� �߰��� �����ߴ�.
	virtual void onRecvAddFriendFailed(const std::string & strNickname, eAddFriendFailed addFriendFailed);

	/// ģ�� ������ �����ߴ�.
	virtual void community_onRecvAcceptFriendOK(const std::string & strNickname);

	/// ģ�� ������ �����ߴ�.
	virtual void community_onRecvAcceptFriendFailed(const std::string & strNickname, eCommunityAcceptFriendFailedReason reason);

	/// ģ�� ������ �����ߴ�.
	virtual void community_onRecvDeclineFriendOK(const std::string & strNickname);

	/// ģ�� ������ �����ߴ�.
	virtual void community_onRecvDeclineFriendFailed(const std::string & strNickname);

	/// ģ�� ����� �������ߴ�.
	virtual void community_onRecvDeclineFriend(const std::string & strNickname);

	/// ģ���� ���ϴµ� �����ߴ�.
	virtual void community_blockFriendOK(const std::string & strFriendNickname);

	/// ģ���� ���ϴµ� �����ߴ�.
	virtual void community_blockFriendFailed(const std::string & strFriendNickname, eRemoveFriendFailed eFailedReason);

	/// ģ�� ���� ����ϴµ� �����ߴ�.
	virtual void community_unblockFriendOK(const std::string & strFriendNickname);

	/// ģ�� ���� ����ϴµ� �����ߴ�.
	virtual void community_unblockFriendFailed(const std::string & strFriendNickname);

	/// ģ���� ���� ǥ���ϴµ� �����ߴ�.
	virtual void community_deleteFriendOK(const std::string & strFriendNickname);

	/// ģ���� ���� ǥ���ϴµ� �����ߴ�.
	virtual void community_deleteFriendFailed(const std::string & strFriendNickname, eRemoveFriendFailed eFailedReason);

	/// ģ���� ���� ǥ�� �����ϴµ� �����ߴ�.
	virtual void community_undeleteFriendOK(const std::string & strFriendNickname);

	/// ģ���� ���� ǥ�� �����ϴµ� �����ߴ�.
	virtual void community_undeleteFriendFailed(const std::string & strFriendNickname);

	/// ģ�� ��� ��� ���� ģ���� �����ϴµ� �����ߴ�.
	virtual void community_cancelAddFriendOK(const std::string & strNickname);

	/// ģ�� ��� ��� ���� ģ���� �����ϴµ� �����ߴ�.
	virtual void community_cancelAddFriendFailed(const std::string & strNickname);

	/// �׷� operation ���
	virtual void community_onRecvGroupOperate(eCommunityGroupOperationType type,vCommunityGroupInfo& vecGroupInfo);

	/// �׷� operation ����� �����Ͽ���
	virtual void community_onRecvGroupOperateFailed(eCommunityGroupOperationType type, eCommunityGroupResult result, short groupNum);

	/// �׷� ��� �̵� ���
	virtual void community_onRecvMoveGroupMember(eCommunityGroupResult result);

	/// ��ȭ�� ����
	virtual void community_onRecvOnlineIDSet(bool isSuccess, std::string strOnlineID);


	/// ���κ��� ģ�� ����Ʈ�κ��� �ڽ��� �������ϴ� ������ �޾Ҵ�.
	virtual void community_onRecvDeleteFriend(const std::string & strFromNickname);

	/// ģ���� �� ������ ����Ǿ��ٴ� ������ �޾Ҵ�. 
	virtual void community_onRecvFarmInfoToFriend(const std::string& strFromNickname, const FarmShortInfo& info); 

	/// ģ���� �� ���Ⱓ�� ����Ǿ��ٴ� ������ �޾Ҵ�. 
	virtual void community_onRecvFarmPeriodExpiredToFriend(const std::string& strFromNickname); 

	/// ģ���� �� ���Ⱓ�� �����ߴٴ� ������ �޾Ҵ�. 
	virtual void community_onRecvFarmPeriodRenewalToFriend(const std::string& strFromNickname, const FarmShortInfo& info); 

	/// ���� ģ���� ����� �� �ִ�.
	virtual void onRecvRequestToMeFriend(const std::string & strNickname,const std::string & strInviteMessage );

	//[mirime 2019-02-21] ģ�� ����� üũ�غ���.
	virtual void community_onRecvCheckFriendRequest(bool reqeustAdd, const std::string & nickname) override;

	/// ���� �ڱ� �濡 ������� �ߴ�.
	virtual void community_onRecvJoinMe(const std::string & strNickname, eRoomKind roomKind, int iRoomServerNum, unsigned int hRoom, const std::string & strPassword, const int iAttribute, const bool bRequireACK, const __int64 partyID = -1);

	/// �������� �ʴ��߾��µ� �� ���´ٰ� �Ѵ�.
	virtual void community_onRecvJoinMeFail(const std::string & strNickname, const bool bAutoReply,const int iAtrribute);

	/// ���������� �����Ͽ���.
	virtual void community_onRecvFindGoFailed(const std::string & strNickname );

	/// 1��1 ��ȭ�� ��û�Ѵ�.
	virtual void community_onRecvRequest1on1Chat( const std::string& strNickname );

	/// 1��1 ��ȭ�� �������¸� �����ش�.
	virtual void community_onRecvResponse1on1Chat(const std::string& strNickname, bool bOK);

	/// ģ���� �α��εǾ���.
	virtual void community_onRecvFriendOnline(const std::string & strFriendNickname);

	/// ������ �α��εǾ���.
	virtual void community_onRecvFamilyOnline(const std::string & strNickname);

	/// ������ �α��εǾ���.
	virtual void community_onRecvGuildOnline(const std::string & strNickname);

	/// ģ���� �α׿����Ǿ���.
	virtual void community_onRecvFriendOffline(const std::string & strFriendNickname);

	/// ������ �α׿����Ǿ���.
	virtual void community_onRecvFamilyOffline(const std::string & strNickname);

	/// ������ �α׿����Ǿ���.
	virtual void community_onRecvGuildOffline(const std::string & strNickname);

	/// ���κ��� �������� �޾Ҵ�.
	virtual void community_onRecvCoupleProposeRequest(const std::string & strFromNickname, const std::string & strCoupleName, const std::string & strCoupleDesc, const int iJewelBoxNum, const bool bMeetingDependency);

	/// ������� ���� ���ο��θ� �޾Ҵ�.
	virtual void community_onRecvCoupleProposeResponse(const std::string & strFromNickname, const bool bOK, const eCoupleProposeReject eReason, const int iCoupleNum, const int iCoupleRingNum);

	/// ���κ��� Ŀ���� ���ڴٴ� ������ �޾Ҵ�.
	virtual void community_onRecvCoupleSayGoodBye(const std::string & strFromNickname);

	/// ���κ��� Ŀ�ø��� �����ߴ� ������ �޾Ҵ�.
	virtual void community_onRecvCoupleRingChanged(const std::string & strFromNickname, const int iCoupleRingNum);

	/// ���κ��� Ŀ�ø��� �����ߴ� ������ �޾Ҵ�.
	virtual void community_onRecvCoupleNameChanged(const std::string & strFromNickname, const std::string & strCoupleName);

	/// ���κ��� Ŀ�üҰ��� �����ߴ� ������ �޾Ҵ�.
	virtual void community_onRecvCoupleDescModify(const std::string & strFromNickname);

	/// ���κ��� ��ȥ �Ҽ�(���Ǹ� ���ϱ� ����)�� �ߴٴ� ������ �޾Ҵ�.
	virtual void community_onRecvWeddingSuitForDivorce(const std::string & strFromNickname, const eWeddingDivorceType eDivorceType);

	/// ���κ��� ��ȥ�� �������� �ʴ´ٴ� ������ �޾Ҵ�.
	virtual void community_onRecvWeddingDisagreeForDivorce(const std::string & strFromNickname, eWeddingDisagreeDivorceType eDisagreeType);

	/// ���κ��� ��ȥ�ߴٴ� ������ �޾Ҵ�.
	virtual void community_onRecvWeddingDivorced(const std::string & strFromNickname, const eWeddingDivorceType eDivorceType, const bool bEnforce);

	/// ���濡�� Ŀ�� ���� �������� ���������� ���� �޾Ҵ�.
	virtual void community_onRecvBuyCoupleItem(const std::string & strFromNickname);

	/// ��뿡�� ���� �α� ��û�� �޾Ҵ�.
	virtual void community_onRecvFamilyPropose(const std::string& strFromNickname, bool bParents);

	/// ��뿡�� ���� �α� ��û�� ���� ���ο��� ������ �޾Ҵ�.
	virtual void community_onRecvFamilyProposeResponse(const std::string& strFromNickname, bool bSummit, eFamilyProposeReject eReason, bool bParents);

	/// ��뿡�� ���� �ξ����� �뺸 �޾Ҵ�.
	virtual void community_onRecvFamilyMakeNotify(const std::string& strFromNickName, bool bParents);

	/// ���� ���� ���� ���� �뺸�� �޾Ҵ�.
	virtual void community_onRecvFamilyBreakNotify(const std::string& strFromNickName);

	/// ��뿡�� �߿��� �ø��� �������� �������ڰ� ��û�� �޾Ҵ�.
	virtual void community_onRecvPieroOlympicJoinPartyPropose(const std::string& strFromNickname, const ePieroOlympicPartyType ePartyType);

	/// ���κ��� ���� TV�� ��û���̶�� ������ �޾Ҵ�.
	virtual void community_onRecvWatchingOpenTV();

	/// ���κ��� �α����� �ߴ��� Ȯ�� ��û�� �޾Ҵ�.
	virtual void community_onRecvRequestLogin(const std::string& strFromNickname);

	/// ���κ��� �α����� �ߴٴ� ������ �޾Ҵ�.
	virtual void community_onRecvResponseLogin(const std::string& strFromNickname, bool isBlocking);

	/// ��尡 ������ �Ǿ����� ��� �����ͷ� ���� ���� �޾Ҵ�.
	virtual void community_onRecvGuildLevelUp(short iGuildLevel);

	/// ��� �ɹ��� Ż�� �Ǿ����� ���� �޾Ҵ�.
	virtual void community_onRecvGuildMemberLeave(const std::string& strNickName);

	/// �������� �⿩�� ����Ʈ�� �޾Ҵ�. 
	virtual void community_guildMemberContributeRefresh();	

	/// ��� ���� ��õ�� �޾Ҵ�.
	virtual void community_onRecvGuildProposeRecommend(const std::string& strFromNickname, const GuildInfo& guildInfo, const bool & bInternJoin );

	/// ��� ������ �̾��� ��õ�޾Ҵ�.
	virtual void community_onRecvGuildConveyMasterPropose(const std::string& strFromNickname);

	///< �������� ��� �����͸� �̾������ �����.
	virtual void community_onRecvGuildConveyMasterProposeResult(const std::string& strFromNickname, bool bAccept);

	/// ģ�� ����Ʈ�� ������Ʈ �Ǿ���.
	virtual void onFriendListUpdate();

	/// ���� �ʴ���� �� �ִ� �����ΰ�.
	virtual bool canInvited() const;

	/// ���� 1��1 ��ȭ�� �Ҽ� �ִ� �����ΰ�?
	virtual e1on1ChatOption can1on1ChatInvited() const;

	/// Ʃ�丮�� �ڵ� (ģ������ �����͸� �޾Ҵ�.)
	virtual void community_onRecvTutorialSendMyDataToFriend(const std::string& strFromNickname, std::string strValue, int iValue);

	/// � ��������� ��õ������ ����Ѱ��� �˸���.
	virtual void community_onRecvHugSystemRecommendUser(const std::string & strFromNickname);

	/// ��õ���� �������� �ߴٰ� �˷��ش�.
	virtual void community_onRecvHugSystemLevelUp(const std::string & strFromNickname, short iHugLevel, eHugUserType eUserType);

	/// ����õ���� ��õ���� �����ߴٰ� �˷��ش�.
	virtual void community_onRecvHugSystemRemoveRecommendUser(const std::string & strFromNickname);	

#ifdef _PERSONAL_CONNECTIONS

	// �θƽý��� ��� ���� 
	virtual void community_onRecvPersonalConnectionsIsRegisterOK(const bool bRegister, const time_type infoEditDate, const __int64 authNum);
	virtual void community_onRecvPersonalConnectionsIsRegisterFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� ��� ��û 
	virtual void community_onRecvPersonalConnectionsRegisterOK(ePersonalConnectionsResult dwResult);

	// �θƽý��� �������� ���� 
	virtual void community_onRecvPersonalConnectionsSetInfoOK();
	virtual void community_onRecvPersonalConnectionsSetInfoFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� �������� ��û 
	virtual void community_onRecvPersonalConnectionsGetInfoOK(const PersonalConnectionsInfo & infoList);
	virtual void community_onRecvPersonalConnectionsGetInfoFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� �˻�Ƚ�� ��û 
	virtual void community_onRecvPersonalConnectionsCountInfoOK(const ePersonalConnectionsKind eKind, const int iCount);
	virtual void community_onRecvPersonalConnectionsCountInfoFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� ���� �˻� ��û 
	virtual void community_onRecvPersonalConnectionsBeforeSearchOK(const ePersonalConnectionsKind eKind, const std::map<std::string, PersonalConnectionsSearch> & resultList);
	virtual void community_onRecvPersonalConnectionsBeforeSearchFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� �˻� ��û 
	virtual void community_onRecvPersonalConnectionsSearchOK(const ePersonalConnectionsKind eKind, const std::map<std::string, PersonalConnectionsSearch> & resultList);
	virtual void community_onRecvPersonalConnectionsSearchFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� �̻��������� ����Ƚ��/���Ƚ�� ��û 
	virtual void community_onRecvPersonalConnectionsIdealTypeCountOK(const int iEntryCount, const int iWinCount);
	virtual void community_onRecvPersonalConnectionsIdealTypeCountFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� ������ ģ�� ���� 
	virtual void community_onRecvPersonalConnectionsTodayFriendOK(const bool bRegister);
	virtual void community_onRecvPersonalConnectionsTodayFriendFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� ����Ʈ, �̻��� ���� 
	virtual void community_onRecvPersonalConnectionsSelectUserOK(const ePersonalConnectionsKind eKind);
	virtual void community_onRecvPersonalConnectionsSelectUserFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� ����Ʈ ���� ���� 
	virtual void community_onRecvPersonalConnectionsOpenSlotOK(const ePersonalConnectionsKind eKind);
	virtual void community_onRecvPersonalConnectionsOpenSlotFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� ������ ��û 
	virtual void community_onRecvPersonalConnectionsProfileOK(const ePersonalConnectionsKind eKind, const PersonalConnectionsProfile & infoList);
	virtual void community_onRecvPersonalConnectionsProfileDetailOK(const PersonalConnectionsProfileDetail & infoList);
	virtual void community_onRecvPersonalConnectionsProfileFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� ȣ���ֱ� 
	virtual void community_onRecvPersonalConnectionsSetPointOK(const std::string & strTargetNickName, const std::string & strTargetAnotherName, const int iPoint);
	virtual void community_onRecvPersonalConnectionsSetPointFailed(ePersonalConnectionsResult dwResult);

	// �θƽý��� ���� �������� ��û ���� 
	virtual void community_onRecvPersonalConnectionsHistoryOK(const ePersonalConnectionsKind eKind, unsigned short numPage, unsigned short totalCount, const std::map <std::string, PersonalConnectionsSearch> & historyList);
	// �θƽý��� ���� �������� ��û ���� 
	virtual void community_onRecvPersonalConnectionsHistoryFailed(ePersonalConnectionsResult dwResult);

	/// �θƽý��� �������κ��� ȣ���� �޾Ҵ�.
	virtual void community_onRecvPersonalConnectionsSendPointNotify(const std::string& strFromNickName, const std::string& strAnotherName, const int iPoint);

	/// �θƽý��� ���� 1��1 ��ȭ�� ��û�Ѵ�.
	virtual void community_onRecvPersonalConnectionsRequest1on1Chat(const std::string& strNickName);

	/// �θƽý��� ���� 1��1 ��ȭ���¸� �˷��ش�.
	virtual void community_onRecvPersonalConnectionsResponse1on1Chat(const std::string& strNickName, bool bOK);

	/// �θƽý��� �������κ��� ���� ��ȭ �޼����� �޾Ҵ�.
	virtual void community_onRecvPersonalConnectionsMsg(const std::string & strFromNickName, const std::string & strFromAnotherName, const std::string & strMsg);

	/// �θƽý��� �޼����� ���� ������ �޾Ҵ�.
	virtual void community_onRecvPersonalConnectionsMsgAck(const std::string& strNickName, const std::string& strMsg, eMessageResult messageResult);

	/// �θƽý��� ��밡 ���� ������ ��û�ߴ�.
	virtual void community_onRecvPersonalConnections1on1nfoRequest(const std::string& strNickName);

	/// �θƽý��� ���� ������ �޾Ҵ�.
	virtual void community_onRecvPersonalConnections1on1nfoResponse(const std::string& strNickName, PersonalConnectionsSearch & info);
#endif


	virtual void community_onRecvFarmNameTagRequest(const std::string & strFromNickname, const std::string & strNameTag);

	virtual void community_onRecvFarmNameTagResponse(const std::string & strFromNickname, const std::string & strNameTag, const bool bOK, const eFarmNameTagResult eResult);


#ifdef _PARTY_SYSTEM
	/// ��Ƽ �ʴ뿡 ���� ����
	virtual void community_onRecvPartyInviteRefuse(const std::string& strNickName);
	
	/// ��Ƽ ������û�� ���� �˸�
	virtual void community_onRecvPartySupportBoardJoin(const std::string& strNickName);
#endif

	// Ŀ�´�Ƽ ���� ���� ��
	//////////////////////////////////////////////////////////////////////////

#ifdef COUNTERATTACK_OF_ANUBIS
	// �ƴ��� ����
	///��Ⱑ ���۵Ǽ� ���� ���̺� ������ �޾Ҵ�.
	virtual void onRecvAnubisStartGame(const AnubisWaveInfo& waveInfo);

	///�������� ���̺갡 ���� �Ǿ���.
	virtual void onRecvAnubisEndGame(eAnubisGameResult eResult);

	///���� ���� ���� ������ �޾Ҵ�.
	virtual void onRecvAnubisNextGameNotify(eAnubisWaveGrade eWaveGrade);

	///�� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvAnubisGetGateList(const std::vector<AnubisGateInfo>& roomList);

	///���� ����Ʈ ������ �޾Ҵ�.
	virtual void onRecvAnubisGetRemainGateCount(const int iRemainGateCount);

	///����Ʈ Ŭ���� ������ �޾Ҵ�.
	virtual void onRecvAnubisGateClearNotify(const eRoomKind roomKind, const int iGateNum);
#endif //COUNTERATTACK_OF_ANUBIS


#ifdef SMART_CHANNEL_SYSTEM
	virtual void onRecvSmartChannelScheduleInfo(std::map<time_type, time_type> & scheduleInfo);
	virtual void onRecvSmartChannelModeInfo(std::map<int/*modeNum*/, SmartChannel> & channelinfo);
	virtual void onRecvSmartChannelUserInfo(bool result, UserSmartChannel& userChannelInfo);

#endif

#ifdef _SCHOOL_BATTLE
	/// �б������� �������� ����
	virtual void onRecvSchoolBattleMyInfo(const SchoolBattleInfo& info, eSchoolBattleResult result);

	/// �б������� Top10 ��ŷ ����
	virtual void onRecvSchoolBattleTopRank(const std::vector<SchoolBattleInfo>& topTenRank, eSchoolBattleResult result);
#endif

	virtual void onRecvRoomKindPenaltyInfo(std::map<eRoomKind, int>& penaltyInfo);

	/// �������� ����ߴ�.
	virtual void onRecvAssaultModeUseItemOK(const int iItemDescNum, const int iItemCount);

	///NPC������ �����ϴµ� �����ߴ�.
	virtual void onRecvAssaultModeSetObjectInfoOK(const std::vector<AssaultModeObjectInfo>& objectInfo);

	///NPC������ �����ϴµ� �����ߴ�.
	virtual void onRecvAssaultModeSetObjectInfoFailed(const std::vector<int> & fail_list);

	///ĳ���� �������� �����ߴ�.
	virtual void onRecvAssaultModeSetCharacterEnergyInfo(const std::map<int/*playerIndex*/, int/*energy*/>& playerList);

	///ĳ������ �������� �����ƴ�.
	virtual void onRecvAssaultModeDecreaseCharacterEnergyOK(const int iPlayerIndex, const int iEnergy);

	///ĳ������ ������ ������ �����ߴ�.
	virtual void onRecvAssaultModeDecreaseCharacterEnergyFailed(const int iObjectNum, const int flag);

	///ĳ������ �������� ������ ���� / ����..
	virtual void onRecvAssaultModeChargeCharacterEnergyResult(const int nResultValue,const int nPlayerIndex,const int nEnergy);

	///NPC�� �������� �����ƴ�.
	virtual void onRecvAssaultModeDecreaseObjectEnergyOK(const int iPlayerIndex, const int iObjectNum, const int iEnergy, const int iDelta, int iAttacker);

	///NPC�� ������ ������ �����ߴ�.
	virtual void onRecvAssaultModeDecreaseObjectEnergyFailed(const int iObjectNum);

	///NPC ���� ������ �޾Ҵ�.
	virtual void onRecvAssaultModeGetObjectRewardInfo(const int iObjectNum, const std::vector<AssaultModeGotRewardInfo>& rewardInfo);

	virtual void onRecvAssaultModeChargeObjectEnergy(std::vector<std::pair<int,int>> & vecObjectChargeEnergyInfo);

	///NPC�� ������������ �����Ͽ���.
	virtual void onRecvAssaultModeChargeObjectEnergyFailed(std::vector<int> & list);

	///������ ȹ�� ����.
	virtual void onRecvAssaultModeEatItemOK(const AssaultModeGotRewardInfo& rewardInfo);


	///������ ȹ�� ����.
	virtual void onRecvAssaultModeEatItemFailed();

	///��Ȱ �������� ����ߴ�.
	virtual void onRecvAssaultModeRebirthOK(const int iPlayerIndex, const int iEnergy,const eAssaultModeRebirthType eFlag);

	///��Ȱ ������ ��뿡 �����ߴ�.
	virtual void onRecvAssaultModeRebirthFailed(eAssaultModeUseItemFailed eFailed,const eAssaultModeRebirthType eFlag);

	// ���ʽ� ������ ����� ����
	virtual void onRecvAssaultModeBonusItemMakeOK();

	// ���ʽ� ������ ����� ����
	virtual void onRecvAssaultModeBonusItemMakeFailed();

	// ���ʽ� ������ �Ա� ����
	virtual void onRecvAssaultModeBonusItemEatOK(const int index, RewardInfo& reward);

	// ���ʽ� ������ �Ա� ����
	virtual void onRecvAssaultModeBonusItemEatFailed();

	// �� ���� ��� ���
	virtual void onRecvMapBoardStepACK(const int boardIndex, eMapBoardType boardType, std::vector<BYTE>& userList);

	// ���� �ν��Ͻ� ���� �����Ǿ���.
	virtual void onRecvSelectRandomInstanceTeam(eTeam randomTeam, eInstanceTeam iInstanceTeam, eTeam otherTeam, eInstanceTeam iInstanceOtherTeam);

	// ���� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvTeamPoint(int teamPoint[eTeam_MAX]);

	//////////////////////////////////////////////////////////////////////////
#ifdef JOURNEY_TO_THE_WEST
	///������ ��� ������ �޾Ҵ�.
	virtual void onRecvJourneyToTheWestGetScheduleInfoOK(const time_type & tStartTime, const time_type & tCloseTime);

	///������ ���� ������ �޾Ҵ�.
	virtual void onRecvJourneyToTheWestGetUserInfoOK();

	///������ �� ������ �޾Ҵ�.
	virtual void onRecvJourneyToTheWestGetPartyInfoOK();

	///������ �� ���� ����� �޾Ҵ�.
	virtual void onRecvJourneyToTheWestJoinPartyOK();

	///������ �� ���Կ� �����ߴ�.
	virtual void onRecvJourneyToTheWestJoinPartyFailed(eJourneyToTheWestJoinPartyMsg eMsg);

	///������ ������ ���ŵǾ��ٰ� �޾Ҵ�. 
	virtual void onRecvJourneyToTheWestUpdateNotify(bool bSeasonOn);

	///������ ���� �� ������ ���µǾ���.
	virtual void onRecvJourneyToTheWestResetUserPartyNotify();
#endif
	//////////////////////////////////////////////////////////////////////////

	//////////////////////�ӽ� ������ ����////////////////////
	/// ���� ���� ��� ����� �޾Ҵ�.
	virtual void onRecvStandbyPurchaseDicisionGetListOk();
	/// ���� ���� ��� ����� �ޱ⸦ ���� �Ͽ���.
	virtual void onRecvStandbyPurchaseDicisionGetListFail(eServerResult eResult);
	/// ���� ���� ��� ��� �߰��Ǿ���.
	virtual void onRecvStandbyPurchaseDicisionAddListOk();
	/// ���� ���� ��� ��� �߰� �����Ͽ���.
	virtual void onRecvStandbyPurchaseDicisionAddListFail(eShopFailed_REASON eResult);
	/// ���� ���� ��� ��� ���ŵǾ���.
	virtual void onRecvStandbyPurchaseDicisionRemoveListOk(int iItemNum, bool bCancellation, int iShopItemNum);
	/// ���� ���� ��� ��� ���Ű� ���еǾ���.
	virtual void onRecvStandbyPurchaseDicisionRemoveListFail(eServerResult eResult);
	/// ���� ���� ��� ����� �Ⱓ ���� üũ ��� �˸�
	virtual void onRecvStandbyPurchaseDicisionExistExpireNontify();
	/// Nexon PC�� ���� ��� �޽���
	virtual void onRecvAlertMessageNontify(eAlertMessage iMessageType, int iRemainMinutes);
	/////////////////////////////////////////////////////////////

	/// �������� ������ ������ �ʿ����� ���θ� �޴´�.
	virtual void onRecvUserSystemInfo(const bool bSendUserInfo);


	/// �̺�Ʈ ���ʽ� ������ �޾Ҵ�
	virtual void onRecvEventBonusNofity(const int userIndex, const float bonusExpRatio, const float bonusTRRatio);
#ifdef _COMPETITION_EVENT
	virtual void onRecvEventAccumulateBonusNofity(const std::map<eEventPartyType, CompetitionEventBuffBonusInfo> & bonusInfo);
#endif

	/// �����̺�Ʈ ��ī�ε� �� �ο������� �޾Ҵ�
	virtual void OnRecvCompetitionEventRoomKindPlayerList(const std::map<int, RoomKind_UserMinMax>& RoomKindList);

	/// GM��ɾ�, ��ġ�� ���� �ɱ� ����
	virtual void onRecvGMCommandShoutRestrictOK(const bool bAddMode, const std::string& nickName, const std::string& startTime, const std::string& endTime);

	/// GM��ɾ�, ��ġ�� ���� �ɱ� ����
	virtual void onRecvGMCommandShoutRestrictFailed(const bool bAddMode, eServerResult result);

	//////////////////////////////////////////////////////////////////////////

#ifdef _CHAOS
	/// ī���� �������ӿ� ���� ������ ����
	virtual void onRecvChaosNoticeNextGameInfo(OlympicGameInfo& gameInfo);

	/// ī���� ���� ���ӿ� ���� ������ ����
	virtual void onRecvChaosNextGameInfo(OlympicGameInfo& gameInfo);

	/// ī���� ������ ����ִ�
	virtual void onRecvChaosGameEmpty();

	/// ī���� �¸����� ���� ����
	virtual void onRecvChaosNoticeWinnerParty(std::map<int, eEventPartyType>& territoryWinners, const bool chaosGroupSeasonOff);

	/// ī���� ���� ������ ���� ���� ����
	virtual void onRecvChaosTerritoryInfoOK(std::map<int, std::map<eEventPartyType, __int64> >& territoryInfo, std::map<int, std::pair<eEventPartyType, std::string> >& territoryWinners);

	/// ī���� ���� ������ ���� ���� �ޱ� ����
	virtual void onRecvChaosTerritoryInfoFailed(eChaosResult result, const int territoryNum);

	/// ī���� ���� ������ ���� ������ ���� ����
	virtual void onRecvChaosTerritoryUserInfoOK(std::map<int, __int64>& territoryUserInfo);

	/// ī���� ���� ������ ���� ������ ���� �ޱ� ����
	virtual void onRecvChaosTerritoryUserInfoFailed(eChaosResult result);

	/// ī���� ������ ���� ���� �����϶�� ����
	virtual void onRecvChaosTerritoryInfoRefresh();
#endif

	/// �̺�Ʈ ä�� ����Ʈ �� ���� �ޱ� ����
	virtual void onRecvEventPointRewardOK(short rewardLevel, std::vector<RewardInfo>& rewardList);

	/// �̺�Ʈ ä�� ���� ���� �� �ִ� �ð� ���� �ޱ� ����
	virtual void onRecvEventRewardLimitTimeOK(const time_type& startTime, const time_type& endTime);

	/// �̺�Ʈ ä�� ���� ����Ʈ�� ����
#ifdef _CHAOS_ZERO_
	virtual void onRecvEventChannelRewardListOK(const std::map<int, std::pair<eEventPartyType, bool> > rewardList, const std::map<int, bool > & JoinList);
#else
	virtual void onRecvEventChannelRewardListOK(const std::map<int, std::pair<eEventPartyType, bool> > rewardList);
#endif

	/// �̺�Ʈ ä�� ���� �޽���
	virtual void onRecvCompetitionEventFailed(eCompetitionEventResult result);

	/// �̺�Ʈ ä�� ���� ���� �¸����� ���� ������ ����
	virtual void onRecvEventChannelNoticeOnOff(const bool bStartNotice, const eEventPartyType winnerParty);	

	//////////////////////////////////////////////////////////////////////////

	/// ������ �̱� ���� ����
	virtual void onRecvPickBoardUserInfoACK(const int pickBoardNum, PickBoardUserInfo& pickBoardUserInfo);
	/// ������ �̱� ���� �ޱ⸦ ���� �ߴ�.
	virtual void onRecvGetPickBoardStateFailed(const int pickBoardNum, ePickBoardResult eResult);

	/// �̱⿡ ���� ���
	virtual void onRecvPickBoardUseOK(const int pickBoardNum, const int order, RewardInfo& reward);
	virtual void onRecvPickBoardUseFailed(const int pickBoardNum, ePickBoardResult result);

#ifdef _EVENTPICKBOARD_
	/// ������ �̺�Ʈ �̱� ���� ����
	virtual void onRecvEventPickBoardUserInfoACK(const EventPickBoardInfo & pickboardInfo, const BYTE nPickBoardStep, PickBoardUserInfo& pickBoardUserInfo);
	/// ������ �̺�Ʈ �̱� ���� �ޱ⸦ ���� �ߴ�.
	virtual void onRecvEventPickBoardUserInfoFailed(const int pickBoardNum, ePickBoardResult eResult);

	/// �̺�Ʈ �̱⿡ ���� ���
	virtual void onRecvEventPickBoardUseOK(const int pickBoardNum, const BYTE nPickBoardStep, const int order, RewardInfo& reward, const BYTE nNextStep, const bool bIsReset);
	virtual void onRecvEventPickBoardUseFailed(const int pickBoardNum, ePickBoardResult result);

	/// �̺�Ʈ �̱� �ޱ�/����
	virtual void onRecvEventPickBoardGiveOK(const bool bIsGift, RewardInfo& reward);
	virtual void onRecvEventPickBoardGiveFailed(ePickBoardResult result);

	/// �̺�Ʈ �̱� ����
	virtual void onRecvEventPickBoardResetNotify(const std::vector<int> & initPickBoard);
#endif

#ifdef _ASSAULT_RAID
	/// ������ ���̵� �������� �޾Ҵ�.
	virtual void onRecvAssaultRaidTodayScheduleNotify(const AssaultRaidScheduleList& scheduleList);

	/// ���̵� ���� ����, ���� ������ �޾Ҵ�.
	virtual void onRecvAssaultRaid_Start_End_Notify(const AssaultRaidState& state);

	/// ���� ���̵� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvAssaultRaidMyPoint(const UserChannelPoint& info);

	/// �⿩����Ʈ ������ �޾Ҵ�.
	virtual void onRecvAssaultRaidPointRewardOK(BYTE iRewardLevel, const std::vector<RewardInfo>& rewardList);
	virtual void onRecvAssaultRaidPointRewardFailed(BYTE iRewardLevel, eCompetitionEventResult result);
#endif

	/// ���� ���̵� ������ ������ �޾Ҵ�.
	virtual void onRecvDungeonRaidScheduleInfoNotify(const DungeonRaidInfo& scheduleInfo);

	/// ���� ���̵� ���� ����, ���� ������ �޾Ҵ�.
	virtual void onRecvDungeonRaid_Start_End_Notify(const eRaidChannelGateState dungeonRaidstate);

	/// ���� ���� ���̵� ����Ʈ�� �޾Ҵ�.
	virtual void onRecvtDungeonRaidMyPoint(const int dungeonRaidPoint);

	//////////////////////////////////////////////////////////////////////////

#ifdef _PARTY_SYSTEM

	/// ��Ƽ �ý���, ��Ƽ�� �����϶�� ��û
	virtual void onRecvPartyInviteRequest(PartyRequestInfo& requestInfo, const int masterServerNum, std::string& masterNickName);

	/// ��Ƽ �ý���, ��Ƽ �ʴ� ��û ����
	virtual void onRecvPartyInviteRequest_Failed(PartyRequestInfo& requestInfo, std::string& invitedNickName);

	/// ��Ƽ �ʴ뿡 ���� ���� ����
	virtual void onRecvPartyInviteAck_Failed(PartyRequestInfo& requestInfo, std::string& invitedNickName);

	/// ���� �ҼӵǾ��ִ� ��Ƽ�� ������ ����
	virtual void onRecvPartyInfo(PartyRequestInfo& requestInfo, InvitationPartyInfo& partyInfo);

	/// ���� �Ҽӵ� ��Ƽ�� ���ο� ����� ����
	virtual void onRecvParty_NewUserInfo(InvitationPartyUserInfo& newUserInfo);

	/// ���� �Ҽӵ� ��Ƽ�� ������ ����
	virtual void onRecvParty_LeaveUser(std::string& leaveUserNickName, ePartyLeaveType leaveType);

	/// ���� �Ҽӵ� ��Ƽ�� �����Ͱ� �����
	virtual void onRecvParty_SetMaster(std::string& masterNickName);

	/// ���� ��Ƽ���� ��������
	virtual void onRecvParty_LeaveAck(ePartyLeaveType leaveType);

	/// ��Ƽ �Խñ� ��� ���� ���п���
	virtual void onRecvPartyBoardAddRequest(const PartyRequestInfo& requestInfo);

	/// ��Ƽ �Խñ� ���� ���� ���� ����
	virtual void onRecvPartyBoardDelRequest(const PartyRequestInfo& requestInfo);

	/// ��Ƽ �Խñ� ��� ����
	virtual void onRecvPartyBoardList(const int iCurPageIndex, const int iMaxPageIndex, std::vector<PartyBoardInfo>& vecPartyBoardList);

	/// ��Ƽ �Խñ� ��� ����
	virtual void onRecvPartyBoardListFailed(const PartyRequestInfo& requestInfo);

	/// ��Ƽ �Խñ� ������û ����
	virtual void onRecvPartyBoardJoin(const PartyRequestInfo& requestInfo, std::string& strMasterNickName);

	/// ��Ƽ �Խñ� ������û ����
	virtual void onRecvPartyBoardJoinFailed(const PartyRequestInfo& requestInfo);

	/// ��Ƽ �Խñ� ������ ��Ϻ���( ��Ƽ�� �ۼ��� ������ ���� �� )
	virtual void onRecvPartyBoardRequestUserList( std::vector<InvitationPartyUserInfo>& vecPartyBoardUserList, const int iTotalPageIndex, const int iCurPageIndex );

	/// ��Ƽ �Խñ� ������ ��Ϻ��� ����
	virtual void onRecvPartyBoardRequestUserListFailed(const PartyRequestInfo& requestInfo);

	/// ��Ƽ ��û ��Ͽ��� ����
	virtual void onRecvPartyBoardJoinRefusalAck(const PartyRequestInfo& requestInfo, std::string& strTargetNickName);

	/// ��Ƽ �Խñ��� ������û â�� ���Ͽ� ��Ƽ ���Կ� ����(��Ƽ ���� ������ ��Ƽ ���� ����Ʈ �簻�� ���� ���)
	virtual void onRecvPartyBoardJoinOK(const PartyRequestInfo& requestInfo);

	/// ������ ������ ��Ƽ �Խñ��� ��Ƽ�� ��Ϻ���
	virtual void onRecvPartyBoardJoinList( std::vector<InvitationPartyUserInfo>& vecPartyJoinUserList, const std::string& strMasterNickName );

	/// ������ ������ ��Ƽ �Խñ��� ��Ƽ�� ��Ϻ��� ����
	virtual void onRecvPartyBoardJoinListFailed( const PartyRequestInfo& requestInfo );

	/// ��Ƽ���� ������ ������� �˸�
	virtual void onRecvPartyModifyUserInfo(InvitationPartyUserInfo& userInfo);

	/// ��Ƽ �ý��� TR,EXP ���ʽ� ������ �޾Ҵ�.
	virtual void onRecvPartyBuffBonusNotify(const BuffBonusInfo& buffBonus);
#endif

	//////////////////////////////////////////////////////////////////////////

	/// ���� �̺�Ʈ ���� �˸�
	virtual void onRecvCompetitionEventGameNotify(const bool bStartNotice, const int interval);

	/// ���� �̺�Ʈ ���� ���ӿ� ���� ������ ����
	virtual void onRecvCompetitionEventNextGameInfo(OlympicGameInfo& gameInfo);

	/// ���� �̺�Ʈ ��Ƽ�� ���� ������ ���� ����
	virtual void onRecvCompetitionEventPartyUserInfoOK(eEventPartyType partyType, const __int64& point, const __int64& accPoint);

	/// ���� �̺�Ʈ ��Ƽ�� ���� ���� ���� �ޱ� ����
	virtual void onRecvCompetitionEventPartyUserInfoFailed(eCompetitionEventResult result);

	/// ���� �̺�Ʈ ������ ���̻� ����
	virtual void onRecvCompetitionEventGameEmpty();

	/// ���� �̺�Ʈ ������ ����
	virtual void onRecvCompetitionEventTodayGameInfo(const std::vector<OlympicGameInfo>& competionEventGameList);

	/// ���� �̺�Ʈ ��Ƽ�� ���� ���
	virtual void onRecvCompetitionEventPartyJoinOK(eEventPartyType partyType, std::vector<RewardInfo>& rewardList);

	/// ���� �̺�Ʈ ��Ƽ ���� ����
	virtual void onRecvCompetitionEventPartyJoinFailed(eCompetitionEventResult result);

	/// ���� �̺�Ʈ ��Ƽ�� ���� ���� ����
	virtual void onRecvCompetitionEventPartyInfo(std::map<eEventPartyType, CompetitionPartyInfo>& partyInfo);

	/// ���� �̺�Ʈ �¸��� ������ ����
	virtual void onRecvCompetitionEventWinnerPartyRewardOK(std::vector<RewardInfo>& rewardList);

	/// ���� �̺�Ʈ �¸��� ���� �ޱ� ����
	virtual void onRecvCompetitionEventWinnerPartyRewardFailed(eCompetitionEventResult result);

	/// ���� �̺�Ʈ ������ �⿩ ���
	virtual void onRecvCompetitionEventPointAddUseItem(int iAddPoint);
	virtual void onRecvCompetitionEventPointAddUsePotionItem(int iAddPoint);
	virtual void onRecvCompetitionEventPointAddUseItemFailed(eCompetitionEvent_POINT_ADD_RESULT result);

	virtual void onRecvCompetitionEventPersonalPoint(int m_StepNum, int m_Point, bool isReward);
	virtual void onRecvCompetitionEventPersonalReward(int m_RefreshItemNum, bool isReward);

#ifdef _CHAOS_ZERO_
	/// ���� �̺�Ʈ ��������
	virtual void onRecvCompetitionEventTerritoryInfoOK(std::map<int, std::pair<eEventPartyType, int> > & territoryWinners, std::map<std::pair<int/*StageNum*/, eEventPartyType>, INT64 > & territoryTalesKnightsWinInfo);
	virtual void onRecvCompetitionEventTerritoryInfoFailed(eCompetitionEventResult result, int territoryNum);
#endif

#ifdef _OFFICIAL_COMPETITION_CHANNEL
	/// ä�� ������ �޾Ҵ�. ���� : room kind�� ��ġ�ϴ� �͸� ���� ������Ʈ!
	virtual void onRecvChannelInfo(const GAMECHANNEL::CHANNEL_INFO_MAP& info);

	/// ���� ����Ʈ ������ �޾Ҵ�. ���� : ���� �ε����� ��ġ�ϴ� �͸� ������Ʈ.
	virtual void onRecvUserPointInfo(eUserPointType pointType, const USER::UserPoint& pointInfo);
#endif


	/// Ư�����(ex)�ξⷳ��)���� ���� ī���� ���� ��û�� ���� ��� ����
	virtual void onRecvTimeCountStartAck(const bool result, const short playTime, const byte countIndex);

	/// Ư�����(ex)�ξⷳ��)���� ī������ �������� �˸�
	virtual void onRecvTimeCountEndAck(const byte countIndex, const short playTime, const bool checkAlivePlayer, std::vector<unsigned int>& alivePlayerList);

#ifdef PROMOTION_SALE
	/// ���� ���θ�� �������� ���� ����
	virtual void onRecvPromotionItemCount();
#endif

#ifdef _SHU_SYSTEM_

	//!<--------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------
	// �� ������ ���� 
	// --------------------------------------------------------------------------------------------


	//!< �� ������ ������ �����Ͽ���..
	virtual void onRecvUpdateShuItemInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CUserShuItemInfo> & update_Info);

	//!< Ư�� ��ĳ����(eCharacterShuKind)�� ���� ������ ������ �����Ͽ���.
	virtual void onRecvUpdateShuItemByCharacter(const eCharacterShuKind character,std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CUserShuItemInfo> & update_Info);

	//!< Ư�� �������� ��� ������ ������ �����Ͽ���.
	virtual void onRecvUpdateShuItemByPosition(const SHU_ITEM_POSITION position,std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CUserShuItemInfo> & update_Info);

	//!< �� ������ ���� ������ �����Ͽ���.
	virtual void onRecvUpdateShuItemState(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::eItem_curr_state> & update_Info);


	// --------------------------------------------------------------------------------------------
	// ��ĳ���� ����
	// --------------------------------------------------------------------------------------------


	//!< �� �˾������� ����Ͽ� ��ĳ���� ������ �����ϴµ� �����Ͽ���.
	virtual void onRecvCreateShuCharacterSucess(const SHU_SYSTEM::CTRShuItemID & eggItemID,const SHU_SYSTEM::CTRShuItemID & shuCharItemID);

	//!< ���� ���õ� ��ĳ���͸� �����Ͽ���.
	virtual void onRecvUpdateSelectCurrentShuCharacter(const SHU_SYSTEM::CTRShuItemID & itemID);

	//!< �� ĳ���� ���¸� �����Ͽ���.
	virtual void onRecvShuCharStatusInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::ShuStatusInfo> & update_info);

	//!<  ��ĳ���� ������ �����Ͽ���.
	virtual void onRecvUpdateShuCharacterInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CMyShuCharacterInfo> & update_Info);

	//!< �� ĳ���� �ƹ�Ÿ ������ �����Ͽ���
	virtual void onRecvUpdateShuAvatarInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::MyShuAvatarInfo> & update_Info);

	//!< �� ĳ���� �ƹ�Ÿ ������ �����Ͽ���.
	virtual void onRecvChangeShuAvatarInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::MyShuAvatarInfo>& update_Info);

	//!< �� ĳ���͸��� ���� �Ͽ���.
	virtual void onRecvChangeShuCharacterName(const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const std::string & name);

	//!< �� ���������͸� ����Ͽ� Ư�� �׼��� ���Ͽ���.
	virtual void onRecvShuCharManagerAction(const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const eShuManagerActionType action,
											const std::map<eShuStatusType, int> & apply_value,const int remainMP);

	//!< �� ĳ������ ����ġ�� ���ҽ��� ������ ������ �Ϸ��Ͽ���.
	virtual void onRecvSuccessShuCharGiftToThisPlayer(const SHU_SYSTEM::CTRShuItemID & from_ShuCharItemID,const int current_exp,const std::vector<RewardInfo> & reward_list);


	//!< �� ĳ���Ϳ��� Ư�� �������� ����Ͽ� ����� �޾Ҵ�.
	virtual void onRecvShuCharUseItemSuccess(const SHU_SYSTEM::CTRShuItemID & charItemID,const SHU_ITEM_POSITION useItemPosition,
		                                     const SHU_SYSTEM::CTRShuItemID & useItemID,const int useItemNumber,const int useCount);

	//!< �� ĳ���Ͱ� ���� ������ ���� �Ǿ���.
	virtual void onRcvShuCharLevelModify(const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const int preLevel,const int currLevel);

	// --------------------------------------------------------------------------------------------
	// ��ĳ���͸� �̿��� Ž������
	// --------------------------------------------------------------------------------------------

	//!< ���� ���� ���� Ž�� ���� ������ �����Ͽ���.
	virtual void onRecvShuCharExploreZoneInfo(std::vector<BYTE/*zoneNumber*/> & zone_list);

	//!< Ư�� Ž�� ������ Ž�縦 �����Ѵ�.
	virtual void onRecvShuCharExploreZone_Start(const BYTE zone_number,const SHU_SYSTEM::CTRShuItemID & shuCharItemID);

	//!< Ư�� Ž�� ������ Ž�縦 �����Ͽ���.
	virtual void onRecvShuCharExploreZone_Stop(const BYTE zone_number,const SHU_SYSTEM::CTRShuItemID & shuCharItemID);

	//!< Ư�� Ž�� ������ ������ �޾Ҵ�.(Ž�� �Ϸ�)
	virtual void onRecvShuCharExploreZone_Reward(const BYTE zone_number,const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const std::vector<RewardInfo> & reward_list);

	// --------------------------------------------------------------------------------------------
	// IN GAME SHU EVENT
	// --------------------------------------------------------------------------------------------

	//!< ���� �ȿ��� ĳ���� --> �� �±� �׼��� �����ߴ�..
	virtual void onRecvShuCharIngameTagAction_Start(const int nPlayerIndex,const int characterAvatarItemNum);

	//!< ���� �ȿ��� �� --> ĳ���� �±� �׼��� �����Ͽ���.
	virtual void onRecvShuCharIngameTagAction_End(const int nPlayerIndex,const SHU_SYSTEM::eIN_GAME_SHU_TAG_END_TYPE end_type);
	
	//!< ���� �ȾƼ� ���������� �� �±� �׼� ������ �����Ͽ���.
	virtual void onRecvThisPlayerShuCharIngameTagAction_Start_failed();

	//!< ���ӹ� �ȿ��� Ư�� ������ �� ĳ���� ������ ����Ǿ���.
	virtual void onRecvPlayerShuCharInfoModify(const int nPlayerIndex,const SHU_SYSTEM::CPlayerShuCharacterInfo & updateInfo);
	//!<--------------------------------------------------------------------------------------------

#endif // _SHU_SYSTEM_

	//////////////////////////////////////////////////////////////////////////
#ifdef _DRAWING_OF_THE_MONTH

	//!< �̴��� �̱� ������ �޾Ҵ�.
	virtual void onRecvMonthlyGotchaSystemInfo(eDOMResult result);

	//!< �̴��� �̱� ���� ������ �޾Ҵ�.
	virtual void onRecvMonthlyGotchaSystemUserInfo(eDOMResult result);

	//!< �̴��� �̱� ������ ����ߴ�.
	virtual void onRecvMonthlyGotchaSystemUseCoupon(eDOMResult result, int id, std::vector<DOM::DOM_ITEM>& resultItem);

	//!< �̴��� �̱� Ȯ�� ������ �޾Ҵ�.
	virtual void onRecvMonthlyGotchaSystemFixReward(eDOMResult result, int id, int resultItem);

#endif
	//////////////////////////////////////////////////////////////////////////
	/// â�� ó�� ����� �޾Ҵ�.
	virtual void onRecvStorageResult();

	/// �����Կ� ������ ���� ��û ����� �޾Ҵ�.
	virtual void onRecvStorage_SaveItem_Result(eStorage_Request_Result result);

	/// �����Կ� �ִ� ������ ���� ��û ����� �޾Ҵ�.
	virtual void onRecvStorage_Gift_Item_Result();

	/// â�� �ִ� ������ ���̷뿡 �ޱ� ��û ����� �޾Ҵ�.
	virtual void onRecvStorage_Get_Item_Result(std::vector<int> item);

	/// ���ױ� ��� �Ⱓ ���Ḧ �뺸 �޾Ҵ�.
	virtual void onRecvFreePass_Expire_Notify(const UserFreePassDesc& fDesc);
	virtual void onRecvFreePass_Expire_Notify();

	/// ���ױ� ��� ���� �뺸 �޾Ҵ�.
	virtual void onRecvFreePass_Inspire_Notify(const UserFreePassDesc& fDesc);

#ifdef _REGIST_REWARD_ITEM
	virtual void OnRecvMasterRegisteredRewardAck(ROOM_REWARD::eResult_MASTER_REGISTER_REWARD result, int item, __int64 storage_num);
	virtual void OnRecvNotifyRoomRewardRegistered(int item, int master_index, const ROOM_REWARD::SELECT_WINNER& select_winner);
	virtual void OnRecvNotifyRoomRewardClear();
	virtual void OnRecvNotifyRoomReward(int item, int player_index, const std::string& player_nick);
#endif

	virtual void OnGameRebirthAck(GAMELOGIC::CPacket_GameRebirthAck::RESULT result, unsigned int player_index, int option);

	virtual void OnRabbitTurtleMakeTeam(const std::vector<std::vector<unsigned int/*gameindex*/>>& team, const std::map<unsigned int, RABBIT_TURTLE::eCharacter>& idx2char);
	virtual void OnRabbitTurtleStatus(const RABBIT_TURTLE::RABBIT_TURTLE_INFO& info);
	virtual void OnRabbitTurtleTagAck(RABBIT_TURTLE::eTAG_CHANGE_RESULT r, int remain_sec);
	virtual void OnRabbitTurtleChangeLeader(unsigned int gameindex);
	virtual void OnRabbitTurtleChangeQueryed(unsigned int requester_gameindex);
	virtual void OnRabbitTurtleChangeAnswer(bool do_change, unsigned int requester_gameindex);

	virtual void OnSubjectKingQuestion(const std::vector<SUBJECTKING::QUESTION_ANSWER>& questions);
	virtual void OnSubjectKingAnswerValidation(int question, int answer, SUBJECTKING::eServer_SUBJECTKING_VALIDATE_ANSWER_ACK_TYPE ack);

	virtual void OnInGameSpecialAbilityAcquire(int boardindex, int param, int user_index, GAMELOGIC::eRoom_INGAME_SPECIAL_ABILITY_ACQUIRE_ACK_DETAIL detail, int skill_group, int groupType, const std::string& skill_group_name, const std::vector<INGAME_SPECIAL_ABILITY_DETAIL>& skills, rn::blob& clientinfo);
	virtual void OnInGameSpecialAbilityFire(int group, const INGAME_SPECIAL_ABILITY_DETAIL& skill, int user_index, GAMELOGIC::eRoom_INGAME_SPECIAL_ABILITY_FIRE_ACK_DETAIL detail, rn::blob& clientinfo);
	virtual void OnInGameSpecialAbilityRemove(int skill_group, int user_index, GAMELOGIC::eRoom_INGAME_SPECIAL_ABILITY_REMOVE_ACK_DETAIL detail);

	virtual void OnContinuousContributionPointStartAck(GAMELOGIC::eServer_ADD_CONTRIBUTION_POINT_START_ACK_DETAIL detail);
	virtual void OnContinuousContributionPointStopAck(GAMELOGIC::eServer_ADD_CONTRIBUTION_POINT_STOP_ACK_DETAIL detail);
	virtual void OnContinuousContributionPointNotify(const std::map<unsigned int, int>& current_point, unsigned int user, int user_delta);

	virtual void OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state);
	virtual void OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state);
	virtual void OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward);
	virtual void OnGlobalRSPStartNotify(int message_in_str_table, int game_schedule_left_time, int game_entrance_left_time);
	virtual void OnGlobalRSPEnterAck(eServer_GLOBAL_RSP_ENTER_ACK_TYPE ack, int base_reward, const std::vector<int>& round_rewards, int selection_limit, int time2round_start);
	virtual void OnGlobalRSPCurrentUserNotify(int delta_user, int user_in_playing);
	virtual void OnGlobalRSPGameStartNotify(int left_time_to_input, int current_state);
	virtual void OnGlobalRSPSelectionAck(eServer_GLOBAL_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION selection, int left_selection_count, int current_reward_state);
	virtual void OnGlobalRSPSelectionInfoNotify(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT]);
	virtual void OnGlobalRSPSelectionResultNotify(eRSP_SELECTION selection, eRSP_SELECTION_RESULT result, int current_reward_state, int current_state);
	virtual void OnUpdateRewardInfo(const std::vector<RewardInfo>& rewards);

	virtual void OnTypingRunQuestionAck(int index, int type, const std::string& question, GAMELOGIC::eQUESTION_ACK ack);
	virtual void OnTypingRunTypingDoneAck(int index, int rank, int total_user, int msec);
	virtual void OnUserSelection(int seq, const std::vector<int>& users);
	virtual void OnUserRankNotifyEnabled(eRACE_RANK_NOTIFY_METHOD method);

	virtual void OnTypingRunGoblinRacingQuestionAck(int index, const std::vector<GAMELOGIC::eGOBLIN_RACE_NOTE>& question, GAMELOGIC::eGOBLIN_RACE_QUESTION_ACK ack);
	virtual void OnTypingRunGoblinRacingTypingDoneAck(int index, int rank, int total_user, int point, int msec);

	virtual void OnIceFlowerQuestionAck(int index, const std::vector<GAMELOGIC::TIMING_MENT>& ment, float end_timing, bool gameover, GAMELOGIC::eICEFLOWER_QUESTION_ACK ack);

	virtual void OnGameRoundInformationNotify(std::vector<GAMELOGIC::GAME_ROUND>& round_info);
	virtual void OnGameRoundStartAck(GAMELOGIC::eROUND_START_ACK ack, int playtime_msec, int round, time_type server_now);
	virtual void OnGameRoundEndNotify(int round, int alive_report_msec, int rest_msec);
	virtual void OnGameRoundAliveAck(GAMELOGIC::eROUND_ALIVE_ACK ack, int round);
	virtual void OnGameRoundStatus(int round, int (&team_point)[eTeam_MAX], int(&delta_team_point)[eTeam_MAX], GAMELOGIC::ROUND_STATUS& myinfo);
	virtual void OnGameRoundStartEnabledNotify(int round, int playtime_msec);

	virtual void OnBombCountingStartAck(GAMELOGIC::eRoom_BOMB_COUTING_START_ACK_RESULT result);
	virtual void OnBombRaceTransferBombAck(int from_user, int to_user, int left_time, GAMELOGIC::eRoom_BOMB_RACE_TRANSFER_BOMB_ACK_RESULT result);
	virtual void OnBombRaceExpldingNotify(int user, int left_bomb_count);

#ifdef _PLAYGROUND_
	virtual void OnMultiMiniGame_UpdateResult(BYTE game_index, int total_point);
	virtual void OnMultiMiniGame_PointNotification(const MULTIMINIGAME::MINIGAME_POINT& points);
#endif
	virtual void OnRoundInfoAck(const GAMELOGIC::CGameRoundInfo_set_ack & result);
	virtual void OnRoundInfoNotify(const GAMELOGIC::CGameRoundInfo_set_notify & result);
	virtual void OnHammderMode_CaculationAck(HAMMERMODE::CHammerMode_CalculatePointAck::RESULT r, int iRedPoint, int iBluePoint, unsigned int iGameIndex);

	virtual void onRecvNumberForPreventAbusing(BYTE iNum);
	virtual void onRecvConfirmNumberForPreventAbusing_OK();
	virtual void onRecvConfirmNumberForPreventAbusing_Fail(int iNum, int iErrCnt);

#ifdef _CHALLENGE_MODE
	virtual void OnRecvSetRoomMedal(int mapnum);
	virtual void OnRecvGetUserInfoAck_ChallengeFullRecord(const std::string& target_nick, const CHALLENGEMODE::MAP2MEDAL& fullrecord, bool bFailed);
	virtual void OnRecvChallengeMapStartAck(CHALLENGEMODE::eRACE_START_RESULT result);
	virtual void OnRecvChallengeMapEndAck(CHALLENGEMODE::eRACE_END_RESULT result, const CHALLENGEMODE::CMedalInfo& best_info, const CHALLENGEMODE::CMedalInfo& current_info, int map_num);
	virtual void OnRecvChallengeMapSummary(const std::map<int, CHALLENGEMODE::SUCCESS_RATIO>& summary);
#endif

#ifdef _ENCHANT_SYSTEM_
	virtual void onRecvEnchantSystemGetMyItem(eENCHANT_SYSTEM_RESULT eResult);
	virtual void onRecvEnchantSystemMount(eENCHANT_SYSTEM_RESULT eResult, int iItemNum, BYTE iNewSeqNum);
	virtual void onRecvEnchantSystemMove(eENCHANT_SYSTEM_RESULT eResult, int iHammerNum, int iNewItemNum, BYTE iNewSeqNum);
	virtual void onRecvEnchantSystemRemove(eENCHANT_SYSTEM_RESULT eResult, bool bSuccess, int iStoneNum, int iHammerNum);
	virtual void onRecvEnchantSystemRemoveSeal(eENCHANT_SYSTEM_RESULT eResult, int iHammerNum);
	virtual void onRecvEnchantSystemStoneHardening(eENCHANT_SYSTEM_RESULT eResult, int iMaterialStoneNum, int iNewStoneNum);
#endif //_ENCHANT_SYSTEM_

	virtual void onRecvComeBackRewardUser(bool bNeedReward);
	virtual void onRecvRepairAllMyItemForComeBack(eServerResult result);

	virtual void onRecvRoomKindEntryCondition();

#ifdef _BONUS_STAGE_
	virtual void onRecvBonusStageRewardInfoList(const std::map<int, BonusStageRewardInfo>& mapRewardInfo);
	virtual void onRecvBonusStageRankInfoList(const std::map<int, std::string>& mapRankInfo);
	virtual void onRecvBonusStageLastChancePoint(const int iChancePoint);
#endif

#ifdef _NUMBERS
	virtual void OnNumbersRankUpdated(int current_rank, int prev_rank);
#endif

	virtual void OnRecvAvatarLockLoad(AvatarLock avatarLock);
#ifdef __NEW_AVATAR_LOCK__
	virtual void OnRecvAvatarLockSave(AvatarLock avatarLock, const std::vector<int>& lookItems);
#else
	virtual void OnRecvAvatarLockSave(AvatarLock avatarLock);
#endif

	virtual void OnRecvGuildBuffApplyGuildList(std::vector<int>& guildBufApplyGuildList);

	virtual void onRecvOpenPortalResponse(std::map<eTeam, bool>& PortalData);
	virtual void onRecvEnterPortalResponse(const size_t iPlayerIndex, const int iMoveIndex);

#ifdef _ITEM_TRADE
	virtual void OnItemTrade_Check(ITEM_TRADE::CCheckTradeAck* packet) const;
	virtual void OnItemTrade_Trade(ITEM_TRADE::CTradeAck* packet) const;
	virtual void OnItemTrade_ResultAction(ITEM_TRADE::CTradeResultActionAck* packet) const;
#endif

#ifdef _ITEM_CUBE
	virtual void OnRecvItemCube_check(int cube, int count, int gold_guage, int gold_guage_max, ITEM_CUBE::eCUBE_INFO_RESULT r);
	virtual void OnRecvItemCube_open(int cube, ITEM_CUBE::eCUBE_TYPE cube_type, ITEM_CUBE::eCUBE_OPEN_RESULT r, const std::vector<ITEM_CUBE::ITEM_OPEN_INFO>& open_result, const std::vector<ITEM_CUBE::ITEM_UNOPEN_INFO>& unopen_result, int max_acceptable);
	virtual void OnRecvItemCube_accept(int cube, ITEM_CUBE::eCUBE_ACCEPT_RESULT result);
#endif

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ��� ��ġ ������
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///< ��� ������ ��� ȹ�� ����Ʈ �� ���� ���� Ƚ�� ����
	virtual void onRecvGuildMatchArea_Point_Info( int iOneDayJoinCount, std::map<eOCCUPATION_AREA_TYPE, int>& mapGuildMatchAreaInfo ) ;
	///< ��� ������ ��� ȹ�� ����Ʈ �� ���� ���� Ƚ�� ���� ����
	virtual void onRecvGuildMatchArea_Point_Info_Failed( GuildMatchRequestInfo& requestInfo );
	///< ��� ������ ������ ��ŷ ���� ����
	virtual void onRecvGuildMatchOccupation_Area_Rank_Info( bool bRequestByGuild, std::map<eOCCUPATION_AREA_TYPE, std::map<int, GuildMatchOccupationRank_Info>>& list );
	///< ��� ������ ������ ��ŷ ���� ���� ����
	virtual void onRecvGuildMatchOccupation_Area_Rank_Info_Failed( GuildMatchRequestInfo& requestInfo );
	///< ��� ������ ���� ��ŷ ���� ����
	virtual void onRecvGuildMatchOccupation_Rank_Range( std::map<int, GuildMatchOccupationRank_Info>& list, const eGUILDMATCH_OCCUPATION_RANK_SEARCH_TYPE eSearchType );
	///< ��� ������ ���� ��ŷ ���� ���� ����
	virtual void onRecvGuildMatchOccupation_Rank_Range_Failed( GuildMatchRequestInfo& requestInfo );
	///< ��� ������ �������� ���� ���� �˷���
	virtual void onRecvGuildMatchOccupation_OpenSchedule();
	///< ��� ������ ���÷��̽� ���� ����
	virtual void onRecvGuildMatchOccupation_HotPlace_Info( std::map<eOCCUPATION_AREA_TYPE, std::map<byte, RewardInfo>>& list );
	///< ��� ������ ���÷��̽� ���� ���� ����
	virtual void onRecvGuildMatchOccupation_HotPlace_Info_Failed( GuildMatchRequestInfo& requestInfo );

	// ��������
	virtual void OnRecvTrainRun_team(const std::vector<int> (&team)[eTeam_MAX]);
	virtual void OnRecvTrainRun_game_timer(GAMELOGIC::eTrainRunTimerID timer);
	virtual void OnRecvTrainRun_KillLeaderAck(GAMELOGIC::eTRAINRUN_ACK ack);
	virtual void OnRecvTrainRun_Suicide();
	virtual void OnRecvTrainRun_ReviveAck(GAMELOGIC::eTRAINRUN_ACK ack, int iUserCount);

#ifdef _KNIGHT_FLOWERS_
	// ���� Į�̱�
	virtual void OnRecvKnightFlowers_StartNotify(const StepEventScheduleInfo& ScheduleData );
	virtual void OnRecvKnightFlowers_EndNotify(StepEventScheduleInfo& ScheduleData, const bool is_empty);
	virtual void OnRecvKnightFlowers_Schedule(const StepEventScheduleInfo& ScheduleData);
	virtual void OnRecvKnightFlowers_CheckPointList(const std::vector<eEventPartyType>& checkPointlist );
	virtual void OnRecvKnightFlowers_TeamPoint(const std::map<eEventPartyType, INT64>& TeamPointList);
	virtual void OnRecvKnightFlowers_WinList(const std::map<int, StepEventWinData>& WinList);
	virtual void OnRecvKnightFlowers_DrawCount(const int DrawCount, const int StepTotalDrawnCount, const int RewardItemNum, const bool bBoost, const bool bcanReceive);
	virtual void OnRecvKnightFlowers_AddPoint(const eKnightofFlowers_Result eResult);
	virtual void OnRecvKnightFlowers_DrawReward(const eKnightofFlowers_Result eResult);
	virtual void OnRecvKnightFlowers_TeamReward(const eKnightofFlowers_Result eResult, const int RewardItemNum);
	virtual void OnRecvKnightFlowers_AccReward(const eKnightofFlowers_Result eResult, const int RewardItemNum);
#endif
	virtual void onRecvIngameUserBonusInfo(eRewardCondition reward, int amount);

	virtual void OnRecvSiegeMode_change_base_ack(const std::string& base_id, eTeam server_team, SIEGE::eCHANGE_BASE_ACK ack, int useridx, int deltapoint);
	virtual void OnRecvSiegeMode_point_inc_ack(SIEGE::ePOINT_REQ_ACK r, SIEGE::ePOINT_TYPE type, int useridx, int deltapoint);
	virtual void OnRecvSiegeMode_teampoint_notify(const int (&team_point)[eTeam_MAX], const int (&delta_point)[eTeam_MAX], const std::map<int, int>& user_point, const std::map<int, int>& user_delta_point);

	virtual void OnRecvAreaWarMode_Occupation_Ack(const AreaWarOccupationData & data);
	virtual void OnRecvAreaWarMode_Occupation_Bonus_Notify(const eTeam occupationTeam, const eAreaWarOccupationBonus_TYPE bonusType);
	virtual void OnRecvAreaWarMode_Occupation_Data(size_t areaWarOccupationData);

	// ���� ���� �޼���
	virtual void OnRecvItemListRoomMasterBufMsg(std::vector<NetItemInfo> & info);
	virtual void OnRecvRoomMasterBufMsgNotify(RoomMasterBufMsgItem item);
	virtual void OnRecvGetMasterBuffMsgAck(eServerResult eResult, RoomMasterBufMsgItem item);
	virtual void OnRecvChangeMasterBuffMsgAck(eServerResult eResult, RoomMasterBufMsgItem item);

#ifdef _VALENTINE_2018_
	virtual void OnRecvValentineEvent_TalkInfo(int iCombineNum, int iNpcNum);
	virtual void OnRecvValentineEvent_TalkInfo_Failed();
	virtual void OnRecvValentineEvent_SetTalkResult(int iNpcNum, int iGoodFeelling, int iItemNum);
	virtual void OnRecvValentineEvent_SetTalkResult_Failed();
	virtual void OnRecvValentineEvent_GetRewardInfo(const std::map<int, ValentineDay_Talk_RewardInfo>& rewardList);
	virtual void OnRecvValentineEvent_GetRewardInfo_Failed();
	virtual void OnRecvValentineEvent_GiveReward(const std::vector<RewardInfo>& rewardList);
	virtual void OnRecvValentineEvent_GiveReward_Failed();
#endif

#ifdef _PIERO_ELECTION_
	virtual void OnRecvPieroLeaderAdvertiseAck(eServerResult eResult, int iMissionNum);
#endif

#ifdef _MOTION_KEY_
	virtual void OnRecvMotionQuickSlot_Info(const std::map<short,int>& SlotData);
#endif
	
	// �� ũ����Ʈ
	virtual void OnRecvFarmCraft_GetUserItemInfo( MAP_FARM_CRAFT_MASTER_ITEM_INFO& mapUserItemInfo );
	virtual void OnRecvFarmCraft_GetUserItemInfo_Failed( eFARM_CRAFT_Result eResult );
	virtual void OnRecvFarmCraft_UpdateUserItemInfo( FarmCraft_ItemInfo& info );
	virtual void OnRecvFarmCraft_UpdateUserItemInfo_Failed( eFARM_CRAFT_Result eResult );
	virtual void OnRecvFarmCraft_GetVoxelsData( RecvFarmMapVoxelsInfo& voxels, bool bUpdate, bool bEndCheck );
	virtual void OnRecvFarmCraft_GetVoxelsData_Failed( eFARM_CRAFT_Result eResult );
	virtual void OnRecvFarmCraft_SaveVoxelData();
	virtual void OnRecvFarmCraft_SaveVoxelData_Failed( eFARM_CRAFT_Result eResult );
	virtual void OnRecvFarmCraft_ReloadVoxelData_Failed( eFARM_CRAFT_Result eResult );
#ifdef _NEWBIE_RETURNER_
	virtual void OnRecvNewbieReturner_InitialReward_ACK(const NEWBIE_RETURNER::NEWBIE_RETURNER_STATUS& status, const NEWBIE_RETURNER::REWARDED_ITEM& items, const NEWBIE_RETURNER::eNEWBIE_RETURNER_ACK& ack);
	virtual void OnRecvNewbieReturner_Purchase_ACK(const NEWBIE_RETURNER::NEWBIE_RETURNER_STATUS& status, const NEWBIE_RETURNER::REWARDED_ITEM& items, const NEWBIE_RETURNER::eNEWBIE_RETURNER_ACK& ack, bool is_mawoo);
	virtual void OnRecvNewbieReturner_Status_ACK(const NEWBIE_RETURNER::NEWBIE_RETURNER_STATUS& status, const NEWBIE_RETURNER::eNEWBIE_RETURNER_ACK& ack);
#endif

#ifdef _PARK_DROP_BOX_EVENT_
	virtual void OnRecvDropBoxEvent_Failed( eDROP_BOX_EVENT_Result eResult );
	virtual void OnRecvDropBoxEvent_GetUserInfo( DropBoxEvent_UserInfo& userInfo );
	virtual void OnRecvDropBoxEvent_GetUserInfo_Failed( eDROP_BOX_EVENT_Result eResult );
	virtual void OnRecvDropBoxEvent_SettingBoxList( const std::map<int, DropBoxEvent_SettingInfo>& mapSettingList );
	virtual void OnRecvDropBoxEvent_SettingBoxList_Failed( eDROP_BOX_EVENT_Result eResult );
	virtual void OnRecvDropBoxEvent_EatItem( const DropBoxEvent_UserInfo& userinfo, int iItemIndex, int iRewardItemNum );
	virtual void OnRecvDropBoxEvent_EatItem_Failed( eDROP_BOX_EVENT_Result eResult, int iIndex );
	virtual void OnRecvDropBoxEvent_Schedule( std::vector<int>& vecPointInfo, time_type tOpenTime, time_type tCloseTime, time_type tFeverStartTime );
	virtual void OnRecvDropBoxEvent_Schedule_Failed( eDROP_BOX_EVENT_Result eResult );
	virtual void OnRecvDropBoxEvent_GetTotalPoint( int iTotalPoint );
	virtual void OnRecvDropBoxEvent_GetTotalPoint_Failed( eDROP_BOX_EVENT_Result eResult );
	virtual void OnRecvDropBoxEvent_GetToDaySchedule( std::vector<DropBoxEvent_ScheduleKind> vecSchedule, int iUseItemNum, int iUseItemCount, int iRewardGroupID );
	virtual void OnRecvDropBoxEvent_GetToDaySchedule_Failed( eDROP_BOX_EVENT_Result eResult );
	virtual void OnRecvDropBoxEvent_AddPointReward( const std::vector<RewardInfo>& rewardList, int iUseItemNum, int iUseItemCount );
	virtual void OnRecvDropBoxEvent_AddPointReward_Failed( eDROP_BOX_EVENT_Result eResult );
#endif

	virtual void onRecvItemDyeingDyedItemListAck(const std::map<int, TintBlendUserData>& list_man, const std::map<int, TintBlendUserData>& list_woman);
	virtual void onRecvItemDyeingDyeItemAck(int iItemNum, const TintBlendUserData& data, BYTE iGender);
	virtual void onRecvItemDyeingDecolorItemAck(int iItemNum, const TintBlendUserData& data, BYTE iGender);

	virtual void onRecvItemDyeingDyedItemListFailed(eServerResult result);
	virtual void onRecvItemDyeingDyeItemFailed(eServerResult result);
	virtual void onRecvItemDyeingDecolorItemFailed(eServerResult result);


#ifdef _USER_REPORT_SYSTEM
	virtual void OnRecvAgent_LEFT_ACCUSATION_COUNT_ACK(int left_free_accusationcount, int left_payed_accusationcount, int total_accusation_count, int accusation_point);
	virtual void OnRecvAgent_DO_ACCUSATION_ACK(const USER_REPORT_SYSTEM::PROSECUTION_TYPE& type, const std::string& target_nick, USER_REPORT_SYSTEM::eUSER_REPORT_ACK ack, int left_free_accusationcount, int left_payed_accusationcount, int total_accusation_count, int accusation_point);
	virtual void OnRecvAgent_DO_ACCUSATION_SET_COMMENT_ACK(USER_REPORT_SYSTEM::ACCUSATION_ID id, const std::string& comment, USER_REPORT_SYSTEM::eUSER_REPORT_ACK ack);
	virtual void OnRecvAgent_ACCUSATION_LIST_ACK(const std::list<USER_REPORT_SYSTEM::ACCUSATION_INFO>& info, int max_page, USER_REPORT_SYSTEM::eUSER_REPORT_ACK ack);
	virtual void OnRecvAgent_DEMERIT_INFO_ACK(const USER_REPORT_SYSTEM::USER_REPORT& user_report, const std::string& nickname);
//------------------------------------------------------------------------
	virtual void OnRecvAgent_JUDGMENT_NEED(const USER_REPORT_SYSTEM::USER_REPORT& ur);
	virtual void OnRecvAgent_JUDGMENT_ACK(USER_REPORT_SYSTEM::eUSER_REPORT_ACK ack, int judgment_id);
	virtual void OnRecvAgent_COURT_ROOM_INFO_ACK(int wait_count, int in_judge_count);
	virtual void OnRecvAgent_SET_PUNISHMENT(int period, USER_REPORT_SYSTEM::ePRISONER_TYPE prisoner_type);
	virtual void OnRecvAgent_USE_JAILITEM_ACK(int item, USER_REPORT_SYSTEM::eUSER_REPORT_ACK r);
	virtual void OnRecvRoom_COURT_INFORMATION(int defendant, const std::vector<int>& juror, const std::vector<int>& audience, int new_added_user, int removed_user);
	virtual void OnRecvRoom_COURT_DISCUSSION_START_NOTIFY(const int (&available_punishment)[USER_REPORT_SYSTEM::MAX_AVAILABLE_PUNISHMENT]);
	virtual void OnRecvRoom_COURT_EARLY_VERDICT_ACK(USER_REPORT_SYSTEM::eUSER_REPORT_ACK r);
	virtual void OnRecvRoom_COURT_EARLY_VERDICT_NOTIFY(const std::vector<int>& requested_user);
	virtual void OnRecvRoom_COURT_VERDICT_ACK(USER_REPORT_SYSTEM::eUSER_REPORT_ACK result);
	virtual void OnRecvRoom_COURT_VERDICT_INFO_NOTIFY(const USER_REPORT_SYSTEM::VERDICT_RESULT& result, const USER_REPORT_SYSTEM::VERDICT_COMMENT& comments, const USER_REPORT_SYSTEM::EVALUATION_RESULT& evaluation, bool is_final_punishment, int final_puniment, float final_evaluation, const bool (&user_exists)[USER_REPORT_SYSTEM::eCOURT_USER_TYPE_MAX]);
	virtual void OnRecvRoom_COURT_FORCED_VERDICT_NOTIFY(const int (&available_punishment)[USER_REPORT_SYSTEM::MAX_AVAILABLE_PUNISHMENT]);
	virtual void OnRecvRoom_COURT_TIME_STATE(const USER_REPORT_SYSTEM::TIME_INFO& time_info);	
#endif

#ifdef _TR_KNIGHTAGE_
	virtual void OnRecvTalesKnights_TakeUnitInfo(TalesKnights_UnitInfo &unitInfo, eTALES_KNIGHT_Result eResult);
	virtual void OnRecvTalesKnights_MyUnitInfo(std::vector<TalesKnights_UnitInfo> m_UnitList) ;
	virtual void OnrecvTalesKnights_MyGroupInfo(std::vector<TalesKnights_GroupInfo> m_GroupList);
	virtual void OnrecvTalesKnights_MyGroupInfoName(std::vector<TalesKnights_GroupInfo_Name> &vecGroupInfo);
	virtual void OnrecvTalesKnights_MyGroupNameUpdateAck(int iGroupNum, std::string &strGroupName);
	virtual void OnrecvTalesKnights_StageInfoAck(std::vector<TalesKnights_StageInfo> &vecStageInfo);
	virtual void OnrecvTalesKnights_EnterAdventureAck(eTALES_KNIGHT_Result eResult, TalesKnights_GroupInfo_Name &groupInfo);
	virtual void OnrecvTalesKnights_AdventureCancelAck(int iGroupNum);
	virtual void OnrecvTalesKnights_ResultReward(int iGroupNum, int iStageNum, std::vector<TalesKnightRewardInfo> &vecReward);
	virtual void OnrecvTalesKnights_ResultExp(int iGroupNum, int iStageNum, std::vector<TalesKnight_LevelUpInfo> &vecLevelUpInfo);
	virtual void OnrecvTalesKnights_ResultDeadUnit(int iGroupNum, int iStageNum, std::vector<int> &vecDeadUnitList);
	virtual void OnrecvTalesKnights_ResultWinList(std::map<int, eEventPartyType>& WinList) ;
	virtual	void OnRecvTalesKnights_ResultDamage(int iGroupNum , int Damage);
	virtual void OnrecvTalesKnights_PvERewardRecv(int iItemNum, eTALES_KNIGHT_Result eResult);
	virtual void OnrecvTalesKnights_PvPBattleAck(int iPlayerIndex, exp_type iExp, int iNumbers, bool bAccept, eTALES_KNIGHT_Result eResult, int iRemainTime);
	virtual void OnrecvTalesKnights_PvPReadyNotify(int iTargetIndex, int iTargetGroup, bool bReady);
	virtual void OnrecvTalesKnights_PVPCancle(int TargetIndex);
	virtual void OnrecvTalesKnights_PvPStartAck(std::string TargetGroupName, std::vector<TalesKnights_GroupInfo> &vecTargetGroupInfo, std::map<short, TalesKnight_PVPReusltInfo> &mapBattleResult, unsigned int iWinnerIndex, int iWinPoint, bool bLadderMatch);
	virtual void OnrecvTalesKnights_PvPCommunityNotify(int iPlayerIndex, std::string &msg);
	virtual void OnrecvTalesKnights_PvPNotifyDuel(int iPlayerIndex, bool bLadder);
	virtual void OnrecvTalesKnights_PvPLadderInfo(int WinCount, int LoseCount, int WinRate, int LadderPoint, int Rank);
	virtual void OnrecvTalesKnights_ReinForceUnitAck(int iUnitNum, int iMaxLevel,  bool bSuccess);
	virtual void OnrecvTalesKnights_UseExpItemAck(TalesKnight_LevelUpInfo &unitInfo, int RefreshItemNum);
#endif

#ifdef _FISHING_
	virtual void onRecvFishingMyPictureBookAck(const vector<Fish>& fishList);
	virtual void onRecvFishingMyKeepNetAck(const vector<Fish>& fishList);
	virtual void onRecvFishingProcFishingAck(bool bProc);
	virtual void onRecvFishingCatchFishNotify(const Fish& fish, int iDecoyNum);
	virtual void onRecvFishingCatchFishNotify(BYTE numGameIndex, int iFishNum, int iFishSize, bool bFarmMasterReward);
	virtual void onRecvFishingReceiveFromKeepNetAck(BYTE iRandomFist1, BYTE iRandomFist2);
	virtual void onRecvFishingReceiveFromKeepNetAck(const vector<Fish>& fishList);
	virtual void onRecvFishingMyRankingAck(const vector<FishingRanking>& fishingRankingList);
	virtual void onRecvFishingStartMiniGameNotify(const Fish& fish, int iDecoyNum, BYTE iRandomFish, eFishingMiniGameType type);
	virtual void onRecvFishingStartMiniGameNotify(BYTE numGameIndex, int iFishNum, int iFishSize);
	virtual void onRecvFishingMiniGameResultNotify(bool bSuccess, const Fish& fish, int iDecoyNum);
	virtual void onRecvFishingMiniGameResultNotify(BYTE numGameIndex, bool bSuccess, int iFishNum, int iFishSize, bool bFarmMasterReward);
	virtual void onRecvFishingFarmMasterRewardAck(const std::vector<Fishing_FarmMasterReward>& rewards);
	virtual void onRecvFishingFarmMasterRewardAck(const std::vector<int>& rewards);
	virtual void onRecvFishingRegistFarmMasterRewardAck(const std::vector<Fishing_FarmMasterReward>& rewards);
	virtual void onRecvFishingRemoveFarmMasterRewardAck(const std::vector<Fishing_FarmMasterReward>& rewards);
	virtual void onRecvFishingRegistFarmMasterRewardNotify(const std::vector<int>& rewards);
	virtual void onRecvFishingRemoveFarmMasterRewardNotify(const std::vector<int>& rewards);

	virtual void onRecvFishingMyPictureBookFailed(eServerResult result);
	virtual void onRecvFishingMyKeepNetFailed(eServerResult result);
	virtual void onRecvFishingProcFishingFailed(eServerResult result);
	virtual void onRecvFishingCatchFishFailed(eServerResult result);
	virtual void onRecvFishingReceiveFromKeepNetFailed(eServerResult result);
	virtual void onRecvFishingMyRankingFailed(eServerResult result);
	virtual void onRecvFishingStartMiniGameFailed(eServerResult result);
	virtual void onRecvFishingMiniGameResultFailed(eServerResult result);
	virtual void onRecvFishingFarmMasterRewardFailed(eServerResult result);
	virtual void onRecvFishingRegistFarmMasterRewardFailed(eServerResult result);
	virtual void onRecvFishingRemoveFarmMasterRewardFailed(eServerResult result);
#endif

#ifdef _FASHION_COORDI_KING_
	virtual void onRecvFashionCoordiKingMySeasonInfoAck(FK_SeasonInfo seasonInfo);
	virtual void onRecvFashionCoordiKingCoordiHistoryAck(std::vector<FK_History> historyList);
	virtual void onRecvFashionCoordiKingCoordiSubmitAck(int iEntrynum, int iCoordiModiCount);
	virtual void onRecvFashionCoordiKingEntryListAck(std::vector<FK_Screening> screeningList);
	virtual void onRecvFashionCoordiKingScreeningAck(int iWinner, int iRoundLevel, int iScreeningCount);
	virtual void onRecvFashionCoordiKingBookMarkAck(std::vector<FK_BookMark> bookmarklist);
	virtual void onRecvFashionCoordiKingAddBookMarkAck(FK_BookMark bookmark);
	virtual void onRecvFashionCoordiKingRemoveBookMarkAck(int iContestNum, int iEntryNum);
	virtual void onRecvFashionCoordiKingCoordiBookAck(std::vector<FK_CoordiBook> coordiBookList);
	virtual void onRecvFashionCoordiKingAddCoordiBookAck(FK_CoordiBook coordibook);
	virtual void onRecvFashionCoordiKingRemoveCoordiBookAck(int iContestNum);
	virtual void onRecvFashionCoordiKingModifyCoordiBookAck(FK_CoordiBook coordibook);
	virtual void onRecvFashionCoordiKingTop3RankAck(int iContestNum, std::vector<FK_Top3Ranker> rankerList);
	virtual void onRecvFashionCoordiKingRewardAck(std::vector<int> itemnums);
	virtual void onRecvFashionCoordiKingTop3RankNotify(std::vector<FK_Top3Ranker> rankerList);
	virtual void onRecvFashionCoordiKingScheduleNotify(std::vector<FK_Schedule> scheduleList);
	virtual void onRecvFashionCoordiKingFailed(eServerResult result);
#endif

#ifdef __EXTREME_COMBO__
	virtual void OnRecvExtremePointAck(ROOM_RESULT::eServer_EXTREME_POINT_ACK_DETAIL detail);
#endif

#ifdef _DEV_FESTIVAL_
	virtual void OnRecvDevFestival_GetUserInfo( DevFestival_info& user_info );
	virtual void OnRecvDevFestival_GetUserInfo_Failed( eDevFestival_Result eResult );
	
	virtual void OnRecvDevFestival_GiveRewardItem();
	virtual void OnRecvDevFestival_GiveRewardItem_Failed( eDevFestival_Result eResult );

	virtual void OnRecvDevFestival_GetStepRewardInfo( MAP_DEV_FESTIVAL_STEP_REWARD& rewardList );
	virtual void OnRecvDevFestival_GetStepRewardInfo_Failed( eDevFestival_Result eResult );

	virtual void OnRecvDevFestival_GiveStepRewardItem( BYTE iRewardLevel, int iRewardItemNum );
	virtual void OnRecvDevFestival_GiveStepRewardItem_Failed( eDevFestival_Result eResult );


	virtual void OnRecvDevFestival_GetEndingCreditInfo( bool bEndingCreditCheck );
	virtual void OnRecvDevFestival_GetEndingCreditInfo_Failed( eDevFestival_Result eResult );

	virtual void OnRecvDevFestival_GiveEndingCreditRewardItem( int iRewardItemNum );
	virtual void OnRecvDevFestival_GiveEndingCreditRewardItem_Failed( eDevFestival_Result eResult );
#endif

#ifdef _TALES_TALK_RUEGO
	virtual void OnRecvTalesTalkRuego_GetUserRuegoList( MAP_RUEGO_STATE_INFO& mapRuegoState, MAP_RUEGO_USER_NPC_INFO& mapRuegoUserNpcInfo );
	virtual void OnRecvTalesTalkRuego_Add( int iRuegoNum, eRuegoState eState );
	virtual void OnRecvTalesTalkRuego_CompleteCheck( int iRuegoNum, eRuegoState eState );
	virtual void OnRecvTalesTalkRuego_CompleteReward( int iRuegoNum, eRuegoState eState, int iNpcNum, INT64 iTotalFavorPoint, std::vector<RewardInfo>& vecRewardList );
	virtual void OnRecvTalesTalkRuego_CompetitionScheduleInfo( bool bScheduleOnOff, TalesTalk_RuegoCompetitionSchedule_Info& info );
	virtual void OnRecvTalesTalkRuego_CompetitionGameInfo(  bool bGetRewardCheck, VEC_RUEGO_COMPETITION_GAME_INFO& vecCompetitionGameInfo  );
	virtual void OnRecvTalesTalkRuego_CompetitionReward( std::vector<RewardInfo>& vecRewardList );
	virtual void OnRecvTalesTalkRuego_OneDayReset();
	virtual void OnRecvTalesTalkRuego_GetOneDayList( UserTalesTalk_RuegoOneDayInfo& userOneDayInfo );
	virtual void OnRecvTalesTalkRuego_Failed(eTalesTalk_RuegoResult eResult, const char* calledFunc, bool bShowFail);
#endif

#ifdef _HUMONG_PICKBOARD_
	virtual void OnRecvHumong_PickBoard_State_Ack(int iBoardNum, std::vector<HuMongPickBoard_Label>& labels);
	virtual void OnRecvHumong_PickBoard_State_Ack_Failed(eServerResult result);

	virtual void OnRecvHumong_PickBoard_Pick_Ack(int iPos, int iRank, int iAdditionalRewardItemNum);
	virtual void OnRecvHumong_PickBoard_Pick_Ack_Failed(eServerResult result);

	virtual void OnRecvHumong_PickBoard_Confirm_Ack(int iPos, int iRewardItemNum, int iAdditionalRewardItemNum);
	virtual void OnRecvHumong_PickBoard_Confirm_Ack_Failed(eServerResult result);

	virtual void OnRecvHumong_PickBoard_Init_Notify(int iBoardNum);
	virtual void OnRecvHumong_PICKBOARD_GET_MYINFO_ACK(std::map<int, int>& boards);
#endif

#ifdef _RUNLYMPIC
	virtual void Room_Runlympic_RACE_INFORMATION_NOTIFY(const RUNLYMPIC::room::RACE_INFORMATOIN& info);
	virtual void Room_Runlympic_RACE_START_ACK(RUNLYMPIC::room::eRACE_START_ACK ack);
	virtual void Room_Runlympic_RACE_END_ACK(RUNLYMPIC::room::eRACE_END_ACK ack);
	virtual void Room_Runlympic_RACE_NOTIFY(const RUNLYMPIC::room::RACE_NOTIFY& notify);
	virtual void Room_Runlympic_GAME_NOTIFY(std::vector<RUNLYMPIC::room::GAME_NOTIFY_RANK>& game_rank, eTeam winner_team, const std::map<eTeam, int>& team_point);
	virtual void Server_Runlympic_FRONT_INFO_ACK(const RUNLYMPIC::FRONT_INFO& front_info);
	virtual void Server_Runlympic_RANK_ACK(const RUNLYMPIC::RANK_INFO& rank_info);
	virtual void Server_Runympic_ACCEPT_REWARD_ACK(RUNLYMPIC::REWARD_DONE ack);
#endif 

#ifdef _GOODBYE_ACADEMY_
	virtual void OnRecvGraduated_Info_Ack (std::vector<int>& PieceVec, int AlbumNum);
	virtual void OnRecvGraduated_Update_Ack(int RefreshItemNum, int RefreshRewardNum, bool UpdateOkay, eGraduated_Result Result);
#endif

#ifdef _TUTORIAL_CHANNEL_
	virtual void OnRecvTutorial_Channel_UserInfo( TutorialChannel_UserInfo& userInfo );
	virtual void OnRecvTutorial_Channel_GiveRewardInfo( std::vector<RewardInfo>& vecRewardInfo );
	virtual void OnRecvTutorial_Channel_Failed(eTUTORIAL_CHANNEL_Result eResult);
#endif


#ifdef _TALES_MARBLE_
	virtual void OnRecvTalesMarble_GetUserInfo( TalesMarble_UserBoardInfo& userBoardInfo );
	virtual void OnRecvTalesMarble_PlayDice( TalesMarble_PlayData& playDiceData );
	virtual void OnRecvTalesMarble_OpenBoardInfo( std::set<int>& setTalesMarble_OpenBoard );
	virtual void OnRecvTalesMarble_GiftItem( eTalesMarble_GiftType giftType, int iBoardNum, int iItemDescNum );
	virtual void OnRecvTalesMarble_GaugeCharingUseItem( int iBoardNum, int iDiceGauge, int iUseItemNum );
	virtual void OnRecvTalesMarble_GetUserGaugeInfo( int iBoardNum, int iDiceGauge );
	virtual void OnRecvTalesMarble_Reset_BoardInfo_UseItem( TalesMarble_UserBoardInfo& userBoardInfo, int iUseItemDescNum );
	virtual void OnRecvTalesMarble_Failed( eTalesMarble_Result eResult, const char* calledFunc, bool bShowFail );
#endif

#ifdef _ARCHIVES_
	virtual void OnRecv_Archives_UserData(std::vector<UserData_Archives>& ArchiveList);
	virtual void OnRecv_Archives_RewardList(std::vector<RewardInfo>& RewardList);
	virtual void OnRecv_Archives_Exchange_RewardList(std::map<int,bool>& RewardList, int RefreshItem, eArchives_Result eResult);
#endif


	virtual void OnRecv_FronTier_SchduleInfo(std::vector<Competition_OpenMap_ScheduleInfo>& Schedulelist);
#ifdef _TALES_FRONTIER_
	virtual void OnRecv_FronTier_SummerBattleInfo(int remainCount);
	virtual void OnRecv_FronTier_TeamPointInfo(std::map<short, int>& PointList);
	virtual void OnRecv_FronTier_RewardInfo(bool CanReceive);
	virtual void OnRecv_FronTier_Reward(std::vector<RewardInfo>& RewardList, bool isWIn);
#endif

#ifdef  _TOWER_OF_ORDEAL_
	virtual void OnRecv_Tower_Of_Ordeal_Event_Notify(eTowerNotify NotiResult);
	virtual void OnRecv_Tower_Of_Ordeal_Event_OpenInfo(TowerGameInfo GameData, bool bEventOpen, time_type NextTime = 0);
	virtual void OnRecv_Tower_Of_Ordeal_Event_MyInfo(int TodayFreeCount, int TodayCashCount, int PlayedTime);
	virtual void OnRecv_Tower_Of_Ordeal_Event_Enter(eTowerResult eEnterResult, int FreeCount, int CashCount, int PlayableTime, bool isFree);
	virtual void OnRecv_Tower_Of_Ordeal_Event_GetItem(int iBoxGrade, int iRefreshNum, int iBoxIndex, eTowerResult Result);
	virtual void OnRecv_Tower_Of_Ordeal_Event_GiveUp();
	virtual void OnRecv_Tower_Of_Ordeal_EventBoxList(std::map<int, Tower_BoxData>& BoxList);
	virtual void OnRecv_Tower_Of_Ordeal_Event_GetBoxCount(std::map<int, int>& BoxCountList);
#endif

#ifdef _THANK_OFFERING_
	virtual void OnRecvThankOffering_Failed( eThankOffering_Result eResult, const char* calledFunc, bool bShowFail );
	virtual void OnRecvThankOffering_Receive_Reward(std::vector<RewardInfo> vecRewardList, eRoomKind roomkind );
	virtual void OnRecvThankOffering_UserPointInfo( int iNormal_LadderPoint, int iHardCore_LadderPoint );
	virtual void OnRecvThankOffering_CurSchedule( time_type tOpenDate, time_type tCloseDate );
	virtual void OnRecvThankOffering_LadderPoint(eRoomKind roomKind, int iLadderPoint);
	virtual void OnRecvThankOffering_GetRankInfo(ThankOffering_MapRankList& topRankList, ThankOffering_MapRankList& userRankList);
	virtual void OnRecvThankOffering_ScheduleOpenCloseNotify(bool bOpenClose);
#endif

#if defined(_WINTER_CHANNEL_2019_) || defined(_SPRING_CHANNEL_2020_)

	virtual void OnRecv_Winter_Channel_2019_UserWinInfo(std::map<int, std::vector<bool>>& List, int& RewardCount, int& TotalPoint);
	virtual void OnRecv_Winter_Channel_2019_RewardAck(std::vector<RewardInfo>& List, eWinter2019_Result eResult);
	virtual void OnRecv_Winter_Channel_2019_TeamLeagueAck(std::vector<TeamLeagueRankInfo>& List,
														  std::map<eEventPartyType, int>& RankCountList,
														  TeamLeagueRankInfo& MyRank,
														  INT64& CurPoint,
														  bool& CanReward,
														  eWinter2019_Result& Result);

	virtual void OnRecv_Winter_Channel_2019_TeamLeague_NextSchedule_Ack(Competition_OpenMap_ScheduleInfo& NextData);
	virtual void OnRecv_Winter_Channel_2019_TeamLeague_Rank_Reward_Ack(std::vector<RewardInfo>& List, eWinter2019_Result&	Result);
#endif

#ifdef _TELEPATHY_
	virtual void OnRecv_TelepathyMatchingOK(bool bJoin, const AdvancedAvatarInfo& avatarInfo, const std::string& strNickName);
	virtual void OnRecv_TelepathyMatchingFailed(eServerResult result);
	virtual void OnRecv_TelepathyChoiceACK(eServerResult result, short iOtherChoice);
	virtual void OnRecv_TelepathyGameResultNotify(eServerResult result, BYTE iSuccessCnt, int iRewardItemNum, bool bWin);
	virtual void OnRecv_TelepathyForceFinishNotify();
	virtual void OnRecv_TelepathyNextQuestionNotify(short iQuestionNum, short iAnswer1, short iAnswer2);
	virtual void OnRecv_TelepathyScheduleNotice();
	virtual void OnRecv_TelepathyScheduleNotify(bool bOn);
	virtual void OnRecv_TelepathyEventPeriodNotify(time_type tStart, time_type tEnd);
#endif

#ifdef _QUIZ_QUIZ_
	virtual void OnRecv_QuizQuizTodayPlayCountAck(int iPlayCount);
	virtual void OnRecv_QuizQuizStartAck(int iUseItemNum, int iPlayCount);
	virtual void OnRecv_QuizQuizQuestionAck(int iIndexNum, int iQuestionNum);
	virtual void OnRecv_QuizQuizAnswerAck(eServerResult eResult);
	virtual void OnRecv_QuizQuizIncorrectAnswerAck(const std::string &strCorrectAnswer);
	virtual void OnRecv_QuizQuizRewardAck(int iRewardItemNum);
	virtual void OnRecv_QuizQuizFailedAck(eServerResult eResult);
#endif

private:
	void _processQuestServerResultFailed(eQuestServerResult result);

private:
	vector<float> m_fMasterTickDiffs;

	bool m_bRecvLevelUPAck;

public:
	CTRNetPlayManager * m_pNetPlay;
	CTRNetEventListener * m_pNetEventListener;
	CTRGameRoomUIBase * m_pGameRoomUI;
};


