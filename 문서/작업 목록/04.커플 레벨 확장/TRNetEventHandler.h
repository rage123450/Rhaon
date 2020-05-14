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
	/// 서버로 부터 인증 결과.
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

	// TODO: onRecvForwardToAllRoomUser 등도 인터페이스로...
#ifdef _SHU_SYSTEM_
	//!< 게임 안에서 캐릭터 --> 슈 태그 액션을 시작했다..
	virtual void onRecvShuCharIngameTagAction_Start(const int nPlayerIndex,const int characterAvatarItemNum){};

	//!< 게임 안에서 슈 --> 캐릭터 태그 액션을 종료하였다.
	virtual void onRecvShuCharIngameTagAction_End(const int nPlayerIndex,const SHU_SYSTEM::eIN_GAME_SHU_TAG_END_TYPE end_type){};

	//!< 게임 안아세 로컬유저의 슈 태그 액션 시작을 실패하였다.
	virtual void onRecvThisPlayerShuCharIngameTagAction_Start_failed(){};

	//!< 게임방 안에서 특정 유저의 슈 캐릭터 정보가 변경되었다.
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
	
	/// 서버로 부터 설정 정보를 얻었다.
	virtual void onRecvServerSettingInfo();

	/// 서버의 설정 정보가 바뀌었다.
	virtual void onRecvServerSettingInfoChanged();

	/// 서버로 부터 인증 결과.
	virtual void onRecvLoginAuth(eServerResult eResult, const std::string& strMyID);

	//////////////////////////////////////////////////////////////////////////
	/// 로드 벨런스 서버 관련.

	//! 접속 여부를 알린다.
	virtual void LoadBalance_Connect(eLoadBalanceProtocolResult eResult);

	//! 서버로 부터 접속이 끊겼다.
	virtual void LoadBalance_Disconnect();

	//! 유저가 가장 작게 들어있는 서버의 주소와 포트를 얻는다.
	virtual void LoadBalance_Login( const std::string & serverIP, const int & nPort, bool bHash);

	/// 로드 벨런스 서버 관련 끝.
	//////////////////////////////////////////////////////////////////////////


	/// 아이템 메세지를 성공적으로 받았다.
	virtual void onRecvGetItemMsgOK(std::vector<ItemMsgInfo>& vecItemMsgInfo);

	/// 선물 아이템 메세지를 성공적으로 받았다.
	virtual void onRecvGetGiftItemMsgOK(std::vector<ItemMsgInfo>& vecItemMsgInfo);

	/// 임시보관함 아이템 메세지를 성공적으로 받았다.
	virtual void onRecvGetOutboxItemMsgOK(std::vector<ItemMsgInfo>& vecItemMsgInfo);

	/// 아이템 메세지를 받는데 실패하였다.
	virtual void onRecvGetItemMsgFailed();

	//////////////////////////////////////////////////////////////////////////

	/// 클라이언트 해쉬값이 동일한지 체크한 결과를 얻었다.
	virtual void onRecvClientHashCheck(eClientHashCheck eResult);

	/// 룸이벤트가 발생했다.
	virtual void onRecvRoomEvent(eRoomEvent eEventType, BYTE playerIndex, BYTE eventID );


	//////////////////////////////////////////////////////////////////////////
	/// 추가된 해킹툴 해쉬값을 받았다.
	virtual void onRecvAddHackingToolHack(const std::vector<std::string>& vecHackingToolHash, const std::vector<std::string>& vecAllowingHackingToolHash);

	/// 길드명을 받았다.
	virtual void onRecvGetGuildName(const std::string& strGuildName, const std::string & strGuildMarkURL);

	/// 레더정보를받았다.
	virtual void onRecvGetLadderInfo(const int & iLadderPoint, const int & iLadderRank);

	/// PC방 관련 아이템을 받았다.
	virtual void onRecvGetPCRoomItem(const std::set<int> & setPCRoomItem);

	/// PC방 타입이 변경되었다.
	virtual void onRecvGetPCRoomRivalType();

	/// 하루한번 리셋해야한다.(인맥시스템외)
	virtual void onRecvGetResetNotify();

	/// 멤버십 관련 아이템을 받았다.
	virtual void onRecvGetMembershipItem(const std::vector<int> & vecMembershipItem);

	/// 멤버십 관련 아이템을 지우라는 요청을 받았다.
	virtual void onRecvRemoveMembershipItem(const std::vector<int> & vecMembershipItem);

	/// 아이템 ON/OFF했다.
	virtual void onRecvItemOnOff(const eServerResult eResult, const int iItemDescNum,const bool bOnOff);

	/// 로그인 대기를 해라.
	virtual void onRecvNoticeWaitForLogin(const size_t iRemainUserCount, const DWORD dwEstimatedRemainTime);

	/// 남은 로그인 대기자, 대기예상 시간 정보를 받았다.
	virtual void onRecvNoticeRemainUserNumAndTimeInfo(const size_t iRemainUserCount, const DWORD dwEstimatedRemainTime);

	/// 길드명을 받았다.
	virtual void onRecvGetGuildName(const std::string& strGuildName){}

	/// 레벨업 경험치에 대한 정보를 받았다
	virtual void onRecvLevelUPInfo(std::map<eLevelUPKind, LevelUPExp>& levelUPInfo);

	/// Shutdown 공지를 받았다.
	virtual void onRecvShutdownNotify(eShutdownNotification eNotification, const std::string& strServerMessage);

	/// 펫 업그레이드를 성공했다.
	virtual void onRecvMyRoomPetUpgradeOK();

	/// 펫 업그레이드를 실패했다.
	virtual void onRecvMyRoomPetUpgradeFailed(eMyRoomProtocol_PET_UPGRADE_FAILED_REASON failedReason);

	/// 아이템을 지우는데 성공했다.
	virtual void onRecvMyRoomDeleteItemOK(const int iDeleteItemItemDescNum);

	/// 아이템을 지우는데 실패했다.
	virtual void onRecvMyRoomDeleteItemFailed(eDeleteItemFailedReason failedReason);

	/// 나의 탑승동물 아바타를 얻어오는데 성공했다.
	virtual void onRecvMyRoomGetAnimalAvatarOK(AnimalRacingAnimalAvatar & animalRacingAvatar);

	/// 나의 탑승동물 아바타를 얻어오는데 실패했다.
	virtual void onRecvMyRoomGetAnimalAvatarFailed();

	/// 마이룸에서 탑승동물 아바타 설정을 저장하는 데 성공했다.
	virtual void onRecvMyRoomSetAnimalRacingAvatarInfoSettingOK(AnimalRacingAnimalAvatar & animalRacingAvatar);

	/// 마이룸에서 탑승동물 아바타 설정을 저장하는 데 실패했다.
	virtual void onRecvMyRoomSetAnimalRacingAvatarInfoSettingFailed(int nReason);

	/// 마이룸에서 탑승동물 먹이주는데 성공했다.
	virtual void onRecvMyRoomAnimalRacingFeedAnimalOK(int nTargetAnimalDescNum, int nFeedItemDescNum);

	/// 마이룸에서 탑승동물 먹이주는데 실패했다.
	virtual void onRecvMyRoomAnimalRacingFeedAnimalFailed(byte nReason);

	/// 이 방의 유저들의 경험치를 받았다.
	virtual void onRecvRoomExpOfUsers(const std::map < BYTE, exp_type > indexToExp);

	/// 게임이 끝나고 보너스를 받았다.
	virtual void onRecvEndGameBonus(eEndGameBonus eType, BYTE byBoardNum);

	/// 나의 카드 및 레시피 목록들을 얻었다.
	virtual void onRecvMyCardRecipeKeepList(const std::vector< CardRecipeKeepInfo > & keepList, bool bReplace = false);

	/// 나의 카드 및 레시피 목록들 얻는데 실패했다.
	virtual void onRecvMyCardRecipeFailed();

	/// 수리 아이템을 쓰는데 성공했다.
	virtual void onRecvMyRoomUseRepairItemOK(const int iTargetItemDescNum, const int iRepairItemdDescNum);

	/// 수리 아이템을 쓰는데 실패했다.
	virtual void onRecvMyRoomUseRepairItemFailed(eMyRoomProtocol_USE_REPAIR_ITEM_FAILED_REASON failedReason,const int iTargetItemDescNum, const int iRepairItemDescNum);

	/// 친구 확장권 아이템 사용를 성공했다.
	virtual void onRecvMyRoomUseAddFriendOK(const int iItemDescNum, const int iFriendAddCount);

	/// 친구 확장권 아이템 사용를 실패했다.
	virtual void onRecvMyRoomUseAddFriendFailed(eMyRoomProtocol_ADDFRIEND_FAILED_REASON failedReason);
	
	/// 펫 먹이 아이템을 쓰는데 성공했다.
	virtual void onRecvMyRoomUsePetFeedOK(const int iTargetPetDescNum, const int iFeedItemDescNum);

	/// 펫 먹이 아이템을 쓰는데 실패했다.
	virtual void onRecvMyRoomUsePetFeedFailed(eMyRoomProtocol_USE_PET_FEED_FAILED_REASON failedReason);

	/// 펫 부활 아이템을 쓰는데 성공했다.
	virtual void onRecvMyRoomUsePetRebirthOK(const std::vector<int> petItemNumList, int iPetRebirthItemNum);

	/// 펫 부활 아이템을 쓰는데 실패했다.
	virtual void onRecvMyRoomUsePetRebirthFailed(const int iTargetPetItemDescNum,eMyRoomProtocol_USE_PET_REBIRH_FAILED_REASON failedReason);

	/// 서버의 시간을 받았다.
	virtual void onRecvServerTime(const time_type & serverTime, bool bCheckTime);

	/// 나는 해킹 의심 유저다.
	virtual void onRecvHackingTime(const time_type& hackingTime );

	/// 서버와의 로그인을 실패했다.
	virtual void onRecvLoginFail(eServerResult eError , BYTE byDetail);

	/// 블록의 이류로 서버와의 로그인을 실패했다.
	virtual void onRecvLoginFailByBlock(int iBlockReason, time_type tBlockStartTime, time_type tBlockEndTime);

	/// 샨다 로그인 성공. 
	virtual void onRecvSnDALoginOK(void); 

	/// 샨다 로그인 정보 부족으로 실패.. 추가요청 필요. 
	virtual void onRecvSnDALoginNotEnoughInfoFailed(const eServerResult& failedReason, const std::string& addtionInfo); 

	/// 
	virtual void onRecvSnDALoginFailed(void); 

	/// 서버와 완전한 연결을 이루었다(TCP 연결 및 UDP 교환도 이루어졌다)
	virtual void onCompleteFullConnection();

	/// 닉네임을 입력해라.
	virtual void onRecvEnterNickname();

	/// 닉네임이 잘 입력되었다.
	virtual void onRecvEnterMyNicknameOK();

	/// 사용가능한 닉네임인지를 체크하는 결과가 왔다.
	virtual void onRecvCheckNicknameResult(const std::string & strNickname, eServerResult result);

	/// 넣을 수 없는 닉네임이었다.
	virtual void onRecvEnterMyNicknameFailed(const DWORD & dwResult);

	/// 닉네임이 변경되었다.
	virtual void onRecvChangeMyNicknameOK();

	/// 닉네임 변경에 실패했다.
	virtual void onRecvChangeMyNicknameFailed(const DWORD & dwResult);

	/// 나의 닉네임을 받았다.
	virtual void onRecvMyNickname(const std::string & strNickname);

	/// 특정 유저의 닉네임을 받았다.
	virtual void onRecvGetUserNickname(const int iUserNum, const std::string &strNickname);

	/// 특정 유저의 닉네임을 가져오기를 실패했다.
	virtual void onRecvGetUserNicknameFailed(const eServer_GET_USER_NICKNAME_FAILED_REASON eFailedReason);

	/// 경험치를 새로 받았다.
	virtual void onRecvExp(eLevelUPKind levelKind, const exp_type iExp);

	/// 서버의 시스템 시간을 받았다.
	virtual void onRecvServerSystemTime(time_type tServerTime);

	/// XTrap 인증 패킷을 받았다.
	virtual void onRecvXTrapCSPacket(char * data, size_t size);

	/// Xigncode 보안 패킷을 받았다.
	virtual void onRecvXigncodeCSPacket(char * data, size_t size);

	/// AhnHackShield 인증 메세지를 서버로 부터 받았다.
	virtual void onRecvAhnHSAuthMSG(unsigned char * pbyRequest, unsigned long ulLength);

#ifdef _ITEM_ONOFF
	/// 실시간 으로 변경 해야되는 아이템 정보를 받았다.
	virtual void onRecvRealTimeItemInfo(RT_ITEM::CPacket_RealTimeItemInfo & data);
#endif//_ITEM_ONOFF

	/// 나의 활성화된 기능성 아이템을 받았다.
	virtual void onRecvGetActiveFuncItem(const CActiveItems & activeItems);

	/// 나의 활성화된 기능성 아이템을 받는데 실패했다.
	virtual void onRecvGetActiveFuncItemFailed();

	/// 나의 아이템 능력치를 받았다.
	virtual void onRecvGetUserItemAttr(const CUserItemAttrManager& useritemAttr);

	/// 나의 아이템 능력치를 받는데 실패하였다.
	virtual void onRecvGetUserItemAttrFailed();

	/// 나의 케릭터 능력치를 받았다.
	virtual void onRecvGetUserCharAttr(const CUserItemAttrManager& useritemAttr);

	/// 나의 케릭터 능력치를 받는데 실패하였다.
	virtual void onRecvGetUserCharAttrFailed();

	/// 나의 강화아이템 정보를 받았다. 
	virtual void onRecvGetUserStrengthenItemInfo(); 

	/// 나의 강화아이템 정보를 받는데 실패하엿다. 
	virtual void onRecvGetUserStrengthenItemInfoFailed(); 

	/// 게임룸안에 있는 사용자의 활성화된 아이템 정보가 바뀌었다.
	virtual void onRecvChangeUserActiveItems( BYTE playerIndex , const CActiveItems & activeItems);

	/// 게임룸안에 있는 사용자의 활성화된 하나의 아이템 정보가 바뀌었다.
	virtual void onRecvChangeUserActiveItemsOne( BYTE playerIndex , const CActiveItems & activeItems, const CUserItemAttrManager & useritemattr, const eChangeUserActiveItemFlag changeFlag);

	/// 게임룸안에 있는 사용자의 아이템 능력치 정보가 바뀌었다.
	virtual void onRecvChangeUserItemAttr( BYTE playerIndex,const CUserItemAttrManager& useritemattr);

	/// 게임룸안에 있는 사용자의 어시스트 아이템 정보가 바뀌었다.
	virtual void onRecvChangeUserAssistItems( std::vector< AssistItemBuyInfo > & assistItemBuyInfo );

	/// 특정유저의 상태정보가 바뀌었다.
	virtual void  onRecvUserState(BYTE playerIndex , const int iState );

	/// 나의 활성화된 기능성 아이템이 시간이 지났다.
	virtual void onRecvActiveFuncItemTimeOut(const int iItemDescNum);
	virtual void onRecvActiveFuncItemTimeOut();

	/// 나의 버프 아이템이 시간이 지났다.
	virtual void onRecvBuffItemTimeOut(const int iItemDescNum);

	/// 클라이언트가 쓰일 웹 페이지의 url 을 받았다.
	virtual void onRecvClientWebPageURL(eWebPageReq reqKind, const std::string & strURL);

	/// 처음 접속이어서 캐릭터 선택창을 열어서 선택해라.
	virtual void onRecvSelectStartCharacter();

	/// 캐릭터 선택이 잘되었다. 선택창을 닫아라.
	virtual void onRecvSelectStartChracterOK();

	/// 시작 아바타를 선택하는데 DB Error 로 인한 심각한 에러다.
	virtual void onRecvSelectStartCharacterFail();

	/// 나의 아바타 정보를 받았다.
	virtual void onRecvAvatarInfo(const AdvancedAvatarInfo & advancedAvatarInfo);

	/// 나의 동물레이싱 아바타 정보를 받았다.
	virtual void onRecvAnimalRacingAvatarInfo(const AnimalRacingAnimalAvatar& animalRacingAvatarInfo);

	/// 동물레이싱 아바타를 받는데 실패했다.
	void onRecvAnimalRacingAvatarFail();

	/// 동물레이싱 아바타가 없다. 튜토리얼에 참여해야한다.
	void onRecvHaveNoAnimalRacingAvatar();

	/// 아바타 정보에서 DB Error 로 인하여 받지 못했다. 심각한 상황이다.
	virtual void onRecvGetAvatarFail() {}

	/// 이벤트에 실패했다.
	virtual void onRecvEventFail();

	/// 이벤트 유저 리셋의 결과.
	virtual void onRecvEventUserReset(const std::string & strUserID, bool bSuccess) {}

	/// 공지사항을 받았다.
	virtual void onRecvNoticeMsg(const NOTICE& notice) override;

	/// 외치기 아이템을 사용했다.
	virtual void onRecvUseShoutItem(eServerResult dwResult,const int iShoutItemDescNum, std::string& restrictEndTime);

	/// 외치기 메세지
	virtual void onRecvShoutItemMsg(const UserShoutInfo& info);

	/// 커플생성 축하 외치기 메세지
	virtual void onRecvShoutCoupleCreateCoupleMsg(const UserShoutInfo& info);

	/// 가족맺기 축하 외치기 메세지
	virtual void onRecvShoutCoupleCreateFamilyMsg(const UserShoutInfo& info);

	/// 결혼 축하 메세지
	virtual void onRecvShoutWeddingMarchMsg(const UserShoutInfo& info);

	/// 삐에로 올림픽 방해성장수 메세지
	virtual void onRecvShoutInterruptObjectMsg(const UserShoutInfo& info);

	/// 길드 레벨업 메시지
	virtual void onRecvShoutGuildLevelUpMsg(const UserShoutInfo& info);

	/// 커플링 교체 축하 외치기 메세지
	virtual void onRecvShoutCoupleChangeRingMsg(const UserShoutInfo& info);

	/// 골드머니 아이템을 사용했다.
	virtual void onRecvUseChargeCommunityMoneyItem(eServerResult dwResult,const int iItemDescNum, std::string stdUserID);

	/// 유저 정보가 왔다.
	virtual void onRecvGetUserInfoOK(const UserInfo & userInfo, AvatarLock & avatarLock = AvatarLock());

	/// 유저 정보를 얻는데 실패하였다.
	virtual void onRecvGetUserInfoFailed(const std::string & stdNickName);	

	/// 유저 옵션 정보가 왔다.
	virtual void onRecvSetUserOptionOK(const int iOption);

	/// 유저 옵션 정보를 얻는데 실패하였다.
	virtual void onRecvUserOptionFailed();

#ifdef _ITEM_COLLECTION
	/// 유저 아이템 컬력션 정보이다.
	virtual void onRecvItemCollectionInfoOK(const std::string & strNickName, const exp_type iPoint, const int iRank);

	/// 유저 아이템 컬력션 아이템 정보이다.
	virtual void onRecvItemCollectionListOK(const std::string & strNickName, const std::vector<int> & vItemList);

	/// 유저 아이템 컬력션 대표 아이템 등록에 성공했다.
	virtual void onRecvItemCollectionAddOK();

	///  유저 아이템 컬력션 관련하여 실패하였다.
	virtual void onRecvItemCollectionFailed(const eServerResult & dwResult);
#endif

	/// 랭킹 정보가 왔다.
	virtual void onRecvRankInfo(const eRequestRankKind rankKind, const std::vector < CRankListData > & rankList, const std::vector<CoupleRankInfo>& coupleRankList);

	/// 랭킹 정보를 받는데 실패했다.
	virtual void onRecvRankInfoFailed(void);

	/// 내 랭킹 정보가 왔다.
	virtual void onRecvMyRankInfo(const eRequestRankKind rankKind, const CRankListData & rankData, const CoupleRankInfo& coupleRankInfo);

	/// 내 랭킹 정보를 받는데 실패했다.
	virtual void onRecvMyRankInfoFailed(eRequestRankKind rankKind);

	/// 블로킹 메시지를 받았다는 응답이 왔다.
	virtual void onRecvBlockingResult(eBlockReason reason);

	/// 재판소를 진행하라고 왔다.
	virtual void onRecvCourtResult(const int judgementNum, const eCourtKind kind, const BYTE punishcount, const bool infinity);

	/// 재판소할 것이 없다고 왔다.
	virtual void onRecvCourtNoResult();

	/// 불량유저 신고 응답이 왔다.
	virtual void onRecvBadUserResult(const eCourtKind kind, const eServerResult dwResult);

	//////////////////////////////////////////////////////////////////////////
	// MiniGame 관련 시작..

	//!< 미니게임 맵 정보를 받는 데 성공하였다.
	virtual void onRecvMiniGameGetMapInfoOK(const int numMap,const int nMapPrice,const int nRewardPoint,const int nLife,const int nItemDescNum);

	//!< 미니게임 맵 정보를 받는 데 실패하였다.
	virtual void onRecvMiniGameGetMapInfoFailed();

	//!< 미니게임을 시작해도 좋다.
	virtual void onRecvMiniGameStartOK(const int numMap, const int iRandomSeed,const int iRemainGameMoney);

	//!< 게임 머니가 부족하여 시작을 하지 못했다.
	virtual void onRecvMiniGameStartFailedPayGameMoney(const int numMap, const int iRemainGameMoney);

	//!< 유효하지 않는 맵을 시작하려고 했다.
	virtual void onRecvMiniGameStartFailedInvalidMapNum();

	//!< 미니게임 랭킹 정보를 얻었다.
	virtual void onRecvMiniGameGetRankOK(const int numMap, const std::vector<MiniGameRankInfo>& rankInfo, const int nMyRank, const DWORD dwMyPoint);

	//!< 미니게임 랭킹 정보를 얻는데 알수 없는 이유로 실패하였다
	// TODO : 구현요망.
	virtual void onRecvMiniGameGetRankFailed(){}

	//!< 미니게임 랭킹 정보를 얻는데 실패하였다(맵번호가 유효하지 않음.)
	virtual void onRecvMiniGameGetRankFailedInvalidMapNum();

	//!< 미니게임 끝 성공.
	virtual void onRecvMiniGameOverOK(const int myBestPoint, const int myRank,const int nRewardItemDescNum , DWORD dwRewardPoint);

	//!< 미니게임 끝 실패.
	virtual void onRecvMiniGameOverFailed(eServerResult eResult);

	// MiniGame 관련 끝..

	//! 나의 알림 정보를 얻었다.
	virtual void onRecvUserAlarmInfo(std::vector<UserAlarmInfo> vAlarmInfoList);
	//////////////////////////////////////////////////////////////////////////
	// 커플시스템 관련 시작...

	//! 프로포즈 정보를 체크한다.
	virtual void onRecvCoupleCheckProposeInfo(eServerResult eResult, bool bMeetingDependency);

	//! 커플링 교체에 성공했다.
	virtual void onRecvCoupleChangeCoupleRingOK(const CoupleInfo & OrgCoupleInfo ,const CoupleInfo & ChangeCoupleInfo);

	//! 커플링 교체에 실패했다.
	virtual void onRecvCoupleChangeCoupleRingFailed(eCoupleChangeCoupleRing failedReason);

	//! 프로포즈 정보 초기화에 성공했다.
	virtual void onRecvCoupleInitRecvProposeInfoOK();

	//! 프로포즈 정보 초기화에 실패했다.
	virtual void onRecvCoupleInitRecvProposeInfoFailed();

	//! 커플 생성요청에 대한 응답을 받았다.
	virtual void onRecvCoupleCreateCoupleInfo(eServerResult eResult, const int iCoupleNum, const int iCoupleRingNum);

	//!< 커플정보 변경 처리가 성공했다.
	virtual void onRecvCoupleModifyCoupleInfoOK();

	//!< 커플정보 변경 처리가 실패했다.
	virtual void onRecvCoupleModifyCoupleInfoFailed();

	//!< 커플이름 변경 처리가 성공했다.
	virtual void onRecvCoupleModifyCoupleNameResult(eServerResult eResult, std::string strCoupleName);

	//! 커플 삭제요청에 대한 응답을 받았다.
	virtual void onRecvCoupleRemoveCoupleInfo(std::string strMateName);

	//! 커플 삭제요청에 대한 실패응답을 받았다.
	virtual void onRecvCoupleRemoveCoupleInfoFailed();

	//! 상대방의 커플 정보를 받았다.
	virtual void onRecvCoupleGetCoupleInfo(std::string strCoupleName, std::string strCoupleDesc, CoupleInfo & info, std::map<std::string, AvatarInfo> & mapCoupleAvatarInfo, bool bForTalesBook);

	//! 상대방의 커플 정보를 받는데 실패햇다.
	virtual void onRecvCoupleGetCoupleInfoFailed();

	//! 나의 커플 정보를 갱신 받았다.
	virtual void onRecvCoupleUpdateCoupleInfo(const CoupleInfo & conpleInfo);

	//! 나의 커플 정보를 갱신 받는데 실패했다.
	virtual void onRecvCoupleUpdateCoupleInfoFailed();


	// 커플시스템 관련 끝..
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// 가족 시스템

	//! 가족의 정보를 받는다.
	virtual void onRecvFamilyGetFamilyInfo(const std::map<eFAMILY_UNIT_TYPE, const std::map<std::string, FamilyUnitInfo> > familyInfoList, std::string strNickName, int iParentsCoupleNum, int iMyCoupleNum, eCoupleType eMyCoupleType);

	//! 가족의 정보를 받는데 실패했다.
	virtual void onRecvFamilyGetFamilyInfoFailed(eServerResult failedReason);

	//! 가족 맺기 가능한지 체크 요청에 대한 성공 메시지를 받았다.
	virtual void onRecvFamilyCheckProposeCondition(std::string strNickName, bool bParents);

	//! 가족 맺기 가능한지 체크 요청에 대한 실패 메시지를 받았다.
	virtual void onRecvFamilyCheckProposeConditionFailed(eServerResult failedReason);

	//! 가족의 맺기에 성공했다.
	virtual void onRecvFamilyMakeFamily(std::string strTargetNickName, const std::map<eFAMILY_UNIT_TYPE, const std::map<std::string, FamilyUnitInfo> > familyInfoList, std::string strMyNickName, int iParentsCoupleNum, int iMyCoupleNum, bool bParents, eCoupleType eMyCoupleType);

	//! 가족의 맺기에 실패했다.
	virtual void onRecvFamilyMakeFamilyFailed(std::string strNickName, eServerResult failedReason);

	//! 가족의 끊기에 성공했다.
	virtual void onRecvFamilyDissolveFamily(std::string strTargetNickName, const std::map<eFAMILY_UNIT_TYPE, const std::map<std::string, FamilyUnitInfo> > familyInfoList, std::string strMyNickName, int iParentsCoupleNum, int iMyCoupleNum, bool bParents, eCoupleType eMyCoupleType);

	//! 가족의 끊기에 실패했다.
	virtual void onRecvFamilyDissolveFamilyFailed(eServerResult failedReason);

	//////////////////////////////////////////////////////////////////////////
	// 혼자달리기 관련 시작...

	/// 게임을 시작하라는 허락을 받았다.
	virtual void onRecvAloneRunStartGameOK(const int numMap);

	/// 그냥 끝났다.
	virtual void onRecvAloneRunGoalInNormal(DWORD dwLapTime);

	/// 이상한 랩 타임이다. 스피드핵을 썼을지도...
	virtual void onRecvAloneRunGoalInFailedNotCorrectLapTime();

	/// 해킹툴 유저로 등록되어 있다.
	virtual void onRecvAloneRunGoalInFailedHackingToolUser();

	// 골인에 실패하였다
	virtual void onRecvAloneRunGameOver();
	// 혼자달리기 관련 끝...
	//////////////////////////////////////////////////////////////////////////

	/// 나의 도전과제진행 정보 리스트를 받았다.
	virtual void onRecvChallengeUserMissionInfo(std::map <int,UserChallengeInfo> mUserChallengeInfoList);
	/// 나의 도전과제정보의 갱신결과를 받았다.(그룹 단위)
	virtual void onRecvChallengeUpdateGroupResult(const int iGroupNum, const int iSubNum, const bool bComplete, const int iAchieveNum, const eRewardCondition iRewardClass);

	/// 도전과제정보 갱신이 실패했다.(그룹 단위)
	virtual void onRecvChallengeUpdateGroupResultDBFailed(const int iGroupNum);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 통합미션관련..

	/// 모든 미션 리스트를 받았다.
	virtual void onRecvMissionInfo(std::vector<MissionInfoForClient>& missionInfo);

	/// 유저의 미션 리스트를 받았다.
	virtual void onRecvMissionUserListOK(const MissionUserInfoMap& missionUserInfo);

	/// 유저의 미션 리스트 받기를 실패했다.
	virtual void onRecvMissionUserListFailed(const eMissionFailedReason failedReason);

	/// 유저의 미션 리스트에 미션 추가를 성공했다.
	virtual void onRecvMissionUserMissionAddOK(const MissionRequestInfo& requestInfo, const time_type& challengeExpireTime);

	/// 유저의 미션 리스트에 미션 추가를 실패했다.
	virtual void onRecvMissionUserMissionAddFailed(const MissionRequestInfo& requestInfo, const eMissionFailedReason failedReason);

	/// 특정 시간에 유저의 일일 미션 도전 리스트 추가 통지
	virtual void onRecvMissionUserMissionGroupAddOK(std::vector<MissionRequestDetailInfo>& requestInfo);

	/// 특정 시간에 유저의 일일 미션 도전 리스트 추가 실패 통지
	virtual void onRecvMissionUserMissionGroupAddFailed(const eMissionKind missionKind, const eMissionFailedReason failedReason);

	/// 유저의 미션 리스트의 미션 제거를 성공했다.
	virtual void onRecvMissionUserMissionRemoveOK(const MissionRequestInfo& requestInfo);

	/// 유저의 미션 리스트의 미션 제거를 실패했다.
	virtual void onRecvMissionUserMissionRemoveFailed(const MissionRequestInfo& requestInfo, const eMissionFailedReason failedReason);

	/// 유저의 미션 리스트 업데이트를 성공했다.
	virtual void onRecvMissionUserMissionUpdateOK(const MissionRequestInfo& requestInfo, const MissionConditionAchievedPoint& achievedPoint);

	/// 유저의 미션 리스트 업데이트를 실패했다.
	virtual void onRecvMissionUserMissionUpdateFailed(const MissionRequestInfo& requestInfo, const int conditionNum, const eMissionFailedReason failedReason);

	/// 유저의 미션이 완료되었음을 알린다.
	virtual void onRecvMissionUserMissionCompleteCheckOK(const MissionRequestInfo& requestInfo, const eMissionCompleteType checkTyp);

#ifdef CONTENTS_OPTIONAL_MISSSION
	/// 기능성 미션 전용
	virtual void onRecvMissionUserMissionCompleteCheckOK_For_OptionalMission(const MissionRequestInfo& requestInfo, const eMissionCompleteType completeType, const int completeCount);
#endif

	/// 유저의 미션이 완료되지 않았음을 알린다.
	virtual void onRecvMissionUserMissionCompleteCheckFailed(const MissionRequestInfo& requestInfo, const int conditionNum, const eMissionFailedReason& failedReason);

	/// 유저가 완료한 미션의 보상 받기를 성공했다.
	virtual void onRecvMissionGiveRewardOK(const std::vector<MissionRequestInfo> vecRequestInfo,const std::vector<RewardInfo>& rewardList);

	/// 유저가 완료한 미션의 보상 받기를 실패했다.
	virtual void onRecvMissionGiveRewardFailed(const MissionRequestInfo& requestInfo, const eMissionFailedReason& faliedReason);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! 길드 미션

	/// 유저가 가입되어있는 길드의 길드 미션 리스트를 얻어왔다.
	virtual void onRecvUserGuildMissionListOK(const std::vector<GuildMissionInfoForClient>& guildMisionInfo, std::vector<int>& nextMasterMissionNum);

	/// 유저가 가입되어있는 길드의 길드 미션 리스트 받아오기를 실패했다.
	virtual void onRecvUserGuildMissionListFailed(const eGuildMissionFailedReason& failedReason);

	/// 길드 마스터 미션 설정 성공
	virtual void onRecvGuildMissionSetMasterMissionOK(std::vector<int>& nextMasterMissionList);

	/// 길드 마스터 미션 설정 실패
	virtual void onRecvGuildMissionSetMasterMissionFailed(const eGuildMissionFailedReason& failedReason);

	/// 특정 시간에 유저의 길드 미션 도전 리스트 제거 통지
	virtual void onRecvGuildMissionUserMissionDeleteNotify(const int notifyType);

	//////////////////////////////////////////////////////////////////////////
	// 일일 미션

	/// 유저 일일 미션 리스트를 얻어왔다.
	virtual void onRecvUserOneDayMissionListOK(const std::map<eMissionKind, std::vector<OneDayMissionInfoForClient> >& oneDayMisionInfo, const std::map<eMissionKind, bool>& oneDayMissionBuff);

	/// 유저 일일 미션 리스트 받아오기를 실패했다.
	virtual void onRecvUserOneDayMissionListFailed(const eOneDayMissionFailedReason& failedReason);

	/// 유저 일일 미션 완료 횟수를 얻어왔다.
	virtual void onRecvUserOneDayMissionFinishCountOK(const std::map<eMissionKind, int>& oneDayMissionFinishCount);

	/// 유저 일일 미션 완료 횟수 받아오기를 실패했다.
	virtual void onRecvUserOneDayMissionFinishCountFailed(const eOneDayMissionFailedReason& failedReason);

	/// 이벤트 미션 여부.	
	virtual void onRecvOneDayMissionGetEventMissionStatusOK(CMissionEventInfo& missionEventInfo);

	/// 이벤트 미션 기간이 아니다
	virtual void onRecvOneDayMissionGetEventMissionStatusFailed(const eMissionFailedReason& failedReason);

	/// 특정 시간에 유저의 일일 미션 도전 리스트 제거 통지
	virtual void onRecvOneDayMissionUserMissionDeleteNotify(std::vector<eMissionKind>& missionKindList, const int notifyType);

	//////////////////////////////////////////////////////////////////////////

#ifdef CONTENTS_OPTIONAL_MISSSION
	/// 유저의 기능성 미션에 대한 정보를 받음 
	virtual void onRecvOptionalMissionUserInfoOK(std::map<int, OptionalMissionInfoForClient>& userOptionalMissionInfo);

	/// 유저의 기능성 미션에 대한 정보 받기를 실패
	virtual void onRecvOptionalMissionUserInfoFailed(eOptionalMissionResult result);

	/// 기능성 미션이 초기화되었다
#ifdef _EVENTPICKBOARD_
	virtual void onRecvOptionalMissionInit(std::vector<int> initMissionList);
#else
	virtual void onRecvOptionalMissionInit();
#endif

	/// 웹에서 뽑은 아이템 내역 요청에 대한 결과를 받음
	virtual void onRecvLotteryCouponChangeOK(std::vector<RewardInfo>& rewardList, const bool bExchangeMode);

	/// 웹에서 뽑은 아이템 내역 요청에 대한 결과를 받지 못함
	virtual void onRecvLotteryCouponChangeFailed();
#endif

#ifdef COLLECTION_SYSTEM
    /// 나의 콜렉션 미션 정보 리스트를 받았다.
    virtual void onRecvUserCollectionMissionListOK(const eCollectionType collectionType, std::vector<CollectionMissionInfoForClient>& collectionUserInfoList);

    /// 나의 콜렉션 미션 정보 리스트 받기를 실패
    virtual void onRecvUserCollectionMissionListFailed(const eMissionFailedReason failedReason);
#endif


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/// 엠블럼

	/// 엠블럼 이벤트 정보 리스트를 받았다.
	virtual void onRecvEmblemEventInfo(std::vector<EmblemEventInfo>& emblemEventInfoList);

	/// 나의 엠블럼 정보 리스트를 받았다.
	virtual void onRecvEmblemUserInfoResultOK(std::vector<EmblemUserInfo>& emblemUserInfoList);

	/// 나의 엠블럼 정보 리스트를 받아오기를 실패했다.
	virtual void onRecvEmblemUserInfoResultFailed(eEmblemFailedReason eReason);

	/// 엠블럼 획득 요청에 대한 결과를 받았다.
	virtual void onRecvEmblemAquireResultOK(int iEmblemNum);

	/// 엠블럼 획득 요청을 실패했다.
	virtual void onRecvEmblemAquireResultFailed(int iEmblemNum, eEmblemFailedReason eReason);

	/// 엠블럼 선착순 획득 이벤트 시작/종료를 알린다.
	virtual void onRecvEmblemFirstComeFirstServerdEventEndNotify(int iEmblemNum, bool bEventStart);

	/// 엠블럼 획득을 공지한다.
	virtual void onRecvEmblemAcquisitionNotify(int iEmblemNum, int iRank, const std::string& strNickName);

	/// 혼돈의 엠블럼 획득 유저의 닉네임과 순위를 요청에 대한 결과를 받았다.
	virtual void onRecvChaosEmblemAcquisitionUserListOK(eEmblemType emblemType, std::vector<EmblemAcquisitonUserInfo>& emblemAcquisitionUserInfoList);

	/// 혼돈의 엠블럼 획득 유저의 닉네임과 순위를 요청에 실패했다.
	virtual void onRecvChaosEmblemAcquisitionUserListFailed(eEmblemFailedReason eReason, eEmblemType emblemType);

	///미션을 체크하기위한 게임의 결과가 준비되었다.
	virtual void onRecvRoomResultForMissionCheckNotify();
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	/// 허그 시스템
	/// 허그유저정보를 얻어온다.
	virtual void onRecvHugSystemGetUserInfoOK();

	/// 허그유저정보를 얻어오는데 실패했다.
	virtual void onRecvHugSystemGetUserInfoFailed();

	/// 허그유저가 추천하기를 성공했다.
	virtual void onRecvHugSystemRecommendUserOK(const std::string & recommendNickName, int iRewardGroupID);

	/// 허그유저가 추천하기를 실패했다.
	virtual void onRecvHugSystemRecommendUserFailed(std::string& recommenderNickName, eHugSystemFailed recommendUserFailed);

	/// 허그 유저가 레벨업에 성공했다.
	virtual void onRecvHugSystemLevelUpOK(int iRewardGroupID, short iHugLevel, eHugUserType eUserType);

	/// 허그 유저가 레벨업에 실패했다.
	virtual void onRecvHugSystemLevelUpFailed(eHugSystemFailed eHugLevelFailed);

	/// 추천인이 선물을 받았다.
	virtual void onRecvHugSystemReceiveGiftOK(const std::string& strNickName, int iRewardGroupID);

	/// 추천인이 선물을 받기를 실패했다.
	virtual void onRecvHugSystemReceiveGiftFailed(eHugSystemFailed failReason);

	/// 피추천인 리스트를 받았다.
	virtual void onRecvHugSystemGetRecommendUserListOK(const std::vector<RecommendedUserInfo>& recommendedUserInfoList);

	/// 피추천인 리스트 받기를 실패했다.
	virtual void onRecvHugSystemGetRecommendUserListFailed(eHugSystemFailed failReason);

	/// 피추천인을 제거한다.
	virtual void onRecvHugSystemRemoveRecommendedUserOK(const std::string& strNickName);

	/// 피추천인을 제거에 실패했다.
	virtual void onRecvHugSystemRemoveRecommendedUserFailed(eHugSystemFailed failReason);

	/// 특정 유저의 신규, 허그 추천정보가 갱신되었다.
	virtual void onRecvHugSystemUpdateRecommend(unsigned int numPlayerIndex, bool bIsNotRecommendUser);

	/// 추천해준 유저중 유니크 유저가 된 유저수를 받았다.
	virtual void onRecvHugSystemGetUniqueUserCountOK(short iUniqueUserCount);

	/// 추천해준 유저중 유니크 유저가 된 유저수를 받는데 실패했다.
	virtual void onRecvHugSystemGetUniqueUserCountFailed(eHugSystemFailed failReason);

	//////////////////////////////////////////////////////////////////////////

	/// 카오스 엔젤/데빌 연금 가능함 알린다.
	virtual void onRecvChaosAngelDevilAlchemistOpenNotify();

	//////////////////////////////////////////////////////////////////////////

	/// 개인 정보 읽기를 요청에 대한 결과를 받았다.

	/// 개인 정보 게임 상세 정보를 알려준다.
	virtual void onRecvIndividualGameNodify(const stIndividualRecordGame& stRecordGame);

	/// 개인 정보 기타 정보를 알려준다.
	virtual void onRecvIndividualMiscellaneousNodify(const stIndividualRecordMiscellaneous& recordMiscellaneous);

	//////////////////////////////////////////////////////////////////////////
	 
	 //////////////////////////////////////////////////////////////////////////
	 /// 캡슐 뽑기기계 정보 요청에 대한 결과를 받았다.
	 virtual void onRecvCapsuleMachineGetMachineInfo(CapsuleItemListMap mapMachineInfo, int iMachineNum, eCapsuleMachineKind iMachineKind, int iMachineGroupNum, int iMyPoint, int iUsePoint, int usedCountMax, int usedCount, int luckyCount, bool bIsWinnerParty, bool bIsTodayMachine, bool bIsOlympicGameTime);
#ifdef _VALENTINE
	 virtual void onRecvCapsuleMachineGetMachineInfo(CapsuleItemListMap mapMachineInfo, int iMachineNum, eCapsuleMachineKind iMachineKind, int iMachineGroupNum, int iMyPoint, int iUsingPoint, int usedCountMax, int usedCount, int luckyCount, const SENDER_NICK& sender_nick);
#endif
	 /// 캡슐 뽑기기계 정보 요청에 대한 비정상 결과를 받았다.
	 virtual void onRecvCapsuleMachineGetMachineInfoFailed(int bMachineNum, int iMachineGroupNum,  byte bFailReason);

	 /// 캡슐 뽑은 결과를 받았다.
	 virtual void onRecvCapsuleMachineSelect(int bMachineNum, int itemNum);

	 /// 캡슐 뽑은 결과가 비정상이다.
	 virtual void onRecvCapsuleMachineSelectFailed(int bMachineNum,byte bFailedReason);

	 /// 신규 행운캡슐 뽑은 결과를 받았다.
	 virtual void onRecvCapsuleMachineSelectEx(int bMachineNum, int itemNum);

	 /// 신규 행운캡슐 뽑은 결과가 비정상이다.
	 virtual void onRecvCapsuleMachineSelectExFailed(int bMachineNum, eCapsuleMachine_FAILED_REASON eFail);

	 /// 캡슐 뽑은 아이템을 지급요청에 대한 응답을 받았다.
	 virtual void onRecvCapsuleMachineGive(int itemNum);

	 /// 캡슐 뽑은 아이템 지급 실패하였다.
	 virtual void onRecvCapsuleMachineGiveFailed(byte failedReason);

	 /// 캡슐 뽑은 결과를 공지한다.
	 virtual void onRecvCapsuleMachineNotify(byte type, int bMachineNum, int itemNum, std::string nickname, ePieroOlympicPartyType ePartyType);

#ifdef _AUCTION_SYSTEM_
	 /// 경매 시스템 스케쥴 받았다
	 virtual void onRecvAuctionSchedule(int iAuctionNum, time_type tSDate, time_type tEDate, eAuctionState	auctionState);

	 /// 경매 시스템 세레머니 받았다
	 virtual void onRecvAuctionCermony(int iItemNum, std::string & sBeforeNickName, std::string & sNextNickName, int iBeforeTR, int iNextTR);

	 /// 경매 시스템 리스트 받았다.
	 virtual void onRecvAuctionListOK(eAuctionKind auctionKind, int iAuctionNum, time_type tSDate, time_type tEDate, std::map<int, AuctionLIst> & mapAuctionList, int iTotalCount);
	 virtual void onRecvAuctionListFailed(const DWORD & dwResult);

	 /// 경매 시스템 물품등록 결과를 받았다.
	 virtual void onRecvAuctionRegisterOK(const DWORD & dwResult, INT64 iStorageNum);
	 virtual void onRecvAuctionRegisterFailed(const DWORD & dwResult);

	 /// 경매 시스템 물품 체크 결과를 받았다.
	 virtual void onRecvAuctionRegisterItemCheckOK(int iPrice);
	 virtual void onRecvAuctionRegisterItemCheckFailed(const DWORD & dwResult);

	 /// 경매 시스템 나의 물품등록 정보 받았다.
	 virtual void onRecvAuctionRegisterListOK(std::vector<std::pair<int,int> > & vecList);
	 virtual void onRecvAuctionRegisterListFailed(const DWORD & dwResult);

	 /// 경매 시스템 입찰 결과를 받았다..
	 virtual void onRecvAuctionTenderOK(const DWORD & dwResult);
	 virtual void onRecvAuctionTenderChangePrice(const DWORD & dwResult, int iPrice);
	 virtual void onRecvAuctionTenderFailed(const DWORD & dwResult);

	 /// 경매 시스템 나의 입찰 정보 받았다.
	 virtual void onRecvAuctionMyTenderListOK(std::vector<std::pair<int,int> > & vecList);
	 virtual void onRecvAuctionMyTenderListFailed(const DWORD & dwResult);

	 /// 경매 시스템 지난 낙찰 내역 받았다.
	 virtual void onRecvAuctionHistoryInfoOK(std::vector<std::pair<int,std::string> > & vecList, std::string & sMaxTR_NickName, int iMaxTR, int iMaxCountTR, int iMaxCount);
	 virtual void onRecvAuctionHistoryInfoFailed(const DWORD & dwResult);

	 /// 경매 시스템 최고 입찰가를 받았다.
	 virtual void onRecvAuctionTenderPriceOK(eAuctionKind auctionKind, int iAuctionNum, int iMaxPrice);
	 virtual void onRecvAuctionTenderPriceFailed(const DWORD & dwResult);

	 /// 경매 시스템 최저 입찰횟수를 받았다.
	 virtual void onRecvAuctionTenderCountOK(int iAuctionNum, int iCount);
	 virtual void onRecvAuctionTenderCountFailed(const DWORD & dwResult);
#endif

#ifdef ENTRY_SYSTEM
	 //////////////////////////////////////////////////////////////////////////
	 /// 응모 시스템 응모기간 스케쥴 받았다.
	 virtual void onRecvEntrySystemPeriodSchedule(eEntrySystemShopType shopType, bool bOpen, time_type tOpenTime, time_type tCloseTime, int iScheduleNum);

	 /// 응모 시스템 상점 스케쥴 받았다
	 virtual void onRecvEntrySystemShopSchedule(eEntrySystemShopType shopType, bool bReset, time_type tOpenTime);

	 /// 응모 시스템 정보 받았다
	 virtual void onRecvEntrySystemGetMachineInfo(int iScheduleNum, eEntrySystemShopType shopType, int iCategoryNum, EntrySystemListMap& mapSystemList);

	 /// 응모 시스템 정보한 비정상 결과를 받았다.
	 virtual void onRecvEntrySystemGetMachineInfoFailed(eEntrySystemShopType shopType, int iCategoryNum, byte bFailReason);

	 /// 응모 시스템 뽑은 결과를 받았다.
	 virtual void onRecvEntrySystemSelect(int iUniqueNum, bool bSucess, int itemNum);

	 /// 응모 시스템 뽑은 결과가 비정상이다.
	 virtual void onRecvEntrySystemSelectFailed(int iUniqueNum, byte bFailedReason);

	 /// 응모 뽑은 아이템을 지급요청에 대한 응답을 받았다.
	 virtual void onRecvEntrySystemGive(int itemNum);

	 /// 응모 뽑은 아이템 지급 실패하였다.
	 virtual void onRecvEntrySystemGiveFailed(byte failedReason);

	 /// 응모 시스템 당첨 결과 리스트를 받았다.
	 virtual void onRecvEntrySystemResult(eEntrySystemShopType shopType, int iTotalCount, unsigned short numPage, std::vector<EntrySystemResultInfo>& vEntrySystemResult);

	 /// 응모 시스템 당첨 결과 리스트를 받기 실패했다.
	 virtual void onRecvEntrySystemResultDBFailed();

	 /// 응모 시스템 당첨 결과를 받았다.
	 virtual void onRecvEntrySystemResultView(int iScheduleNum, int iSelectNum, int iUniqueNum, bool bSucess, bool bUse, int itemNum);

	 /// 응모 시스템 당첨 결과가 비정상이다.
	 virtual void onRecvEntrySystemResultViewFailed(byte bFailedReason);

#endif

	 //////////////////////////////////////////////////////////////////////////

	/// 나이키 카드 이벤트 응모에 대한 결과를 받았다.
	virtual void onRecvApplyEventResult(const int iEventNum, const int iTotalCardAmount, const bool bSuccess);

	/// 나이키 카드 이벤트 응모에 대한 결과를 받았다.(DB error)
	virtual void onRecvApplyEventResultDBFailed();
	
	/// 연금 응모권 이벤트 응모에 대한 결과를 받았다.(정상적 결과)
	virtual void onRecvApplyEventTicketResult(const int iEventNum, std::map<int, int> & mApplyInfoList, const bool bSuccess);

	/// 연금 응모권 이벤트 응모에 대한 결과를 받았다.(DB error)
	virtual void onRecvApplyEventTicketResultDBFailed();

	/// 아이템 - TR 교환 요청에 대한 결과를 받았다.
	virtual void onRecvExchangeItemToTRResult(const int iItemNum, const int iRewardTR, const int iCount);

	/// 아이템 - TR 교환 요청에 대한 결과를 받았다.(DB Error)
	virtual void onRecvExchangeItemToTRResultFailed();

	/// 농작물 수확 아이템의 보상요청에 대한 결과 받음
	virtual void onRecvFarmHarvestItemExchangeReward(const int iItemNum, const int iCount, std::vector<RewardInfo>& rewardList);

	/// 농작물 수확 아이템의 보상요청이 실패했다
	virtual void onRecvFarmHarvestItemExchangeRewardFailed();

	/// 새로운 팜 목록을 받았다. 
	virtual void onRecvFarmList(eFarmListKind farmListKind, const std::vector < CFarmListData > & farmList, const std::vector < unsigned int > & notExistFarmRoomList, unsigned int thisPageIndex, unsigned int numFarmListPageCount ); 

	/// 새로운 방 목록을 받았다.
	virtual void onRecvRoomList(eRoomKind roomKind, const std::vector < CRoomListData > & roomList, unsigned int numRoomListPage, unsigned int numRoomListPageCount);

	/// 방 만들기가 실패했다.
	virtual void onRecvMakeRoomFail(eMakeRoomFail makeRoomFail, unsigned int hRoom);

	/// 방 입장이 실패했다.
	virtual void onRecvEnterRoomFailed(eEnterRoomResult enterRoomResult, const eRoomKind roomKind, const int numMaxPlayer, const int restrictTime);

	/// 아이템 목록을 받았다.
	virtual void onRecvGetAvatarItemList(const cpk_type character, const std::vector < NetItemInfo > & ItemList);

	/// 아이템 목록을 받았다.
	virtual void onRecvGetAvatarItemList(const cpk_type character, const int iPosition, const std::vector < NetItemInfo > & ItemList);

	/// 아이템 목록 받기 실패
	virtual void onRecvGetAvatarItemsFailed();

	/// 특정 아이템의 정보를 받았다.
	virtual void onRecvGetAvatarItemInfo(const NetItemInfo & ItemInfo);

	/// 특정 아이템의 정보를 받기 실패했다.
	virtual void onRecvGetAvatarItemInfoFailed();

	/// 특정 아이템들의 정보를 받았다.(캐릭터 및 카드 아이템은 제외한다..)
	virtual void onRecvGetAvatarItemInfoList(const std::vector<NetItemInfo>& iteminfoList);

	/// 아이템의 수량을 받았다.
	virtual void onRecvGetRemainCountAvatarItem(const int itemDescNum, time_type expireTime, int remainCount);

	/// 아이템의 수량을 받지 못했다.
	virtual void onRecvGetRemainCountAvatarItemFailed(eServerResult eResult, const int itemDescNum);

	/// 마이룸 아이템을 사용하였다.
	virtual void onRecvMyRoomUseItem(eServerResult eResult, const int iItemNum, const int iItemRemainCount );

	/// 쿨타임이 있는 아이템을 사용했다.
	virtual void onRecvUseItemEx(eServerResult eResult, int iItemDescNum, int iItemRemainCount, time_type tNextUsableTime);

	/// 특정 유저가 특정 아이템을 사용했다.
	virtual void onRecvRoomUseItemNotify(BYTE iUserGameIndex, BYTE iTargetGameIndex, int iItemDescNum);

	/// 알리바바 첫 관문을 열어라는 요청을 받았다.
	virtual void onRecvAlibabaOpenGate(DWORD dwGameTime){}

	/// 맵 이벤트 발생 통지를 받았다.
	virtual void onRecvMapEvent(eMapEventType byEventType, DWORD dwEventTime);

	/// 다음 올림픽 게임정보를 받았다..
	virtual void onRecvNextOlympicGameInfo(const OlympicGameInfo & gameInfo);

	/// 다음 올림픽 게임 공지 정보를 받았다..
	virtual void onRecvNextOlympicGameNoticeInfo(const OlympicGameInfo & gameInfo);


	//////////////////////////////////////////////////////////////////////////
	// 삐에로 올림픽

	/// 다음 삐에로 올림픽 경기 일정을 받았다.
	virtual void onRecvNextPieroOlympicGameNoticeInfo(const std::vector<OlympicGameInfo>& pieroOlympicGameInfoList);

	//!< 다음 삐에로 올림픽 게임 시작 예정 공지를 받았다.
	virtual void onRecvPieroOlympicNextGameStartScheduleNotice(const OlympicGameInfo & gameInfo);

	//!< 현재 삐에로 올림픽 게임 종료 예정 공지를 받았다.
	virtual void onRecvPieroOlympicThisGameFinishScheduleNotice(const OlympicGameInfo & gameInfo);

	//!< 현재 삐에로 올림픽 게임 종료 공지를 받았다. (승리팀)
	virtual void onRecvPieroOlympicThisGameFinisheNotice(ePieroOlympicPartyType winnerParty);

	//!< 현재 삐에로 올림픽 상점 이용가능한 팀 공지를 받았다.(상점이용가능 복수 팀)
	virtual void onRecvPieroOlympicShopUsablePartyNotice(const std::vector<ePieroOlympicPartyType>& partyTypeList);

	//!< 현재 삐에로 올림픽 상점이 모든 팀에게 개방하기까지 남은 시간을 공지 받았다.
	virtual void onRecvPieroOlympicShopUsablePartyRemainTimeNotice(const time_type remainTime);

	//!< 삐에로 연금 아이템 EXP 보너스 공지를 받았다.
	virtual void onRecvPieroOlympicPieroAlchemistItemEXPBonusNotice(const std::map<ePieroOlympicPartyType, int>& PieroOlympicEXPBonusMap);

	//!< New 삐에로 드래곤 착용 EXP보너스 공지를 받았다.
	virtual void onRecvPieroOlympicDragonEXPBonusNotice(int iEXPBonus);

	//!< 삐에로방 TR,EXP 보너스 공지를 받았다.
	virtual void onRecvPieroOlympicPieroBonusNotice(std::map<ePieroOlympicPartyType, BuffBonusInfo> pieroOlympicPieroBonusMap);

	/// 나의 삐에로 올림픽 정보를 요청을 성공했다.
	virtual void onRecvPieroOlympicGetMyPieroOlympicInfoOK(const PieroOlympicUserInfo& pieroOlympicUserInfo);

	/// 나의 삐에로 올림픽 정보를 요청을 실패했다.
	virtual void onRecvPieroOlympicGetMyPieroOlympicInfoFailed(ePieroOlympicFailedReason failedReason);

	/// 나의 삐에로 올림픽 기여포인트 요청을 성공했다.
	virtual void onRecvPieroOlympicGetMyContributionPointOK(int iContributionPoint, int iAccumulationPoint);

	/// 나의 삐에로 올림픽 기여포인트 요청을 실패했다.
	virtual void onRecvPieroOlympicGetMyContributionPointFailed(ePieroOlympicFailedReason failedReason);

	/// 오늘의 성장포인트를 요청을 성공했다.
	virtual void onRecvPieroOlympicGetThisSeasonGrowthPointOK(const std::vector<PieroOlympicPartyInfo>& todaysGrowthPointList);

	/// 오늘의 성장포인트를 요청을 실패했다.
	virtual void onRecvPieroOlympicGetThisSeasonGrowthPointFailed(ePieroOlympicFailedReason failedReason);

	/// 전체 성장포인트를 요청을 성공했다.
	virtual void onRecvPieroOlympicGetTotalGrowthPointOK(const std::vector<PieroOlympicPartyInfo>& totalGrowthPointList);

	/// 전체 성장포인트를 요청을 실패했다.
	virtual void onRecvPieroOlympicGetTotalGrowthPointFailed(ePieroOlympicFailedReason failedReason);

	/// 방해 성장포인트를 요청을 성공했다.
	virtual void onRecvPieroOlympicGetInterruptGrowthPointOK(const std::vector<PieroOlympicInterruptGrowthInfo>& interruptGrowthPointList);

	/// 방해 성장포인트를 요청을 실패했다.
	virtual void onRecvPieroOlympicGetInterruptGrowthPointFailed(ePieroOlympicFailedReason failedReason);

	/// 삐에로 나무가 레벨업 했을때 보상 아이템을 요청에 성공했다.
	virtual void onRecvPieroOlympicGiveLevelUpRewardOK(int iRewardItemNum);

	/// 삐에로 나무가 레벨업 했을때 보상 아이템을 요청에 실패했다.
	virtual void onRecvPieroOlympicGiveLevelUpRewardFailed(ePieroOlympicFailedReason failedReason);

	/// 삐에로 올림픽 팀 가입 요청을 성공했다.
	virtual void onRecvPieroOlympicJoinPartyOK(ePieroOlympicPartyType ePartyType, int iRewardItemNum);

	/// 삐에로 올림픽 팀 가입 요청을 실패했다.
	virtual void onRecvPieroOlympicJoinPartyFailed(ePieroOlympicFailedReason eFailedReason);

	/// 삐에로 올림픽 팀 같이 가입 성공했다.
	virtual void onRecvPieroOlympicJoinPartyPurposeInfoOK(ePieroOlympicPartyType ePartyType, int iRewardItemNum);

	/// 삐에로 올림픽 팀 같이 가입 실패했다.
	virtual void onRecvPieroOlympicJoinPartyPurposeInfoFailed(ePieroOlympicFailedReason eFailedReason);

	/// 삐에로 상점에서 아이템 구매시 구매 요청에 성공했다.
	virtual void onRecvPieroOlympicShopBuyItemOK(const std::vector<PieroOlympicShopInfo>& shopInfo);

	/// 삐에로 상점에서 아이템 구매시 구매 요청에 실패했다.
	virtual void onRecvPieroOlympicShopBuyItemFailed(ePieroOlympicShopFailedReason failedReason, int iItemNum);

	/// 삐에로 상점에서 판매하는 아이템리스트 요청에 성공했다.
	virtual void onRecvPieroOlympicGetShopInfoOK(const std::vector<PieroOlympicShopInfo>& itemList, const std::vector<ePieroOlympicPartyType>& partyList, const bool bActiveShop, const bool bShopUsableWinnerParty);

	/// 삐에로 상점에서 판매하는 아이템리스트 요청에 실패했다.
	virtual void onRecvPieroOlympicGetShopInfoFailed();

	/// 대전 팀 정보를 받았다.
	virtual void onRecvPieroOlympicGetCompetitionTeamInfo(eCompetitionRule rule, const std::vector<ePieroOlympicPartyType>& teamInfo);

	/// 대전 정보를 받았다.
	virtual void onRecvCompetitionInfoOK();

	///////////////////////////////////////////////////////////////////////////
	/// 티켓 쟁탈전

	///티켓 쟁탈전 팀가입을 받았다.
	virtual void onRecvTicketScrambleJoinPartyOK(ePieroOlympicPartyType ePartyType);

	///티켓 쟁탈전 팀가입에 실패했다.
	virtual void onRecvTicketScrambleJoinPartyFailed(ePieroOlympicFailedReason failedReason);

	///티켓 쟁탈전 정보를 받았다.
	virtual void onRecvTicketScrambleGetInfoOK(const TicketScrambleInfo& ticketScrambleInfo);

	///티켓 쟁탈전 정보 요청에 실패했다.
	virtual void onRecvTicketScrambleGetInfoFailed();

	///티켓 충전을 받았다.
	virtual void onRecvTicketScrambleRechargeTicketOK(int iTicketCount);

	///티켓 충전을 실패했다.
	virtual void onRecvTicketScrambleRechargeTicketFailed();

	///티켓 쟁탈전 결과 보상아이템을 받았다.
	virtual void onRecvTicketScrambleResultReward(const RewardInfo & rewardInfo);

	//티켓 쟁탈전 정보 초기화를 받았다.
	virtual void onRecvTicketScrambleInitInfo();

	///////////////////////////////////////////////////////////////////////////
	/// 런닝맨2
#ifdef _RUNNING_MAN2

	/// 다음 런닝맨2 경기 일정을 받았다.
	virtual void onRecvNextRunningMan2GameNoticeInfo(const std::vector<OlympicGameInfo>& gameInfoList);

	///런닝맨2 팀가입을 받았다.
	virtual void onRecvRunningMan2JoinPartyOK(ePieroOlympicPartyType ePartyType);

	///런닝맨2 팀가입에 실패했다.
	virtual void onRecvRunningMan2JoinPartyFailed(ePieroOlympicFailedReason failedReason);

	///런닝맨2 정보를 받았다.
	virtual void onRecvRunningMan2GetInfoOK(const TicketScrambleInfo& ticketScrambleInfo);

	///런닝맨2 정보 요청에 실패했다.
	virtual void onRecvRunningMan2GetInfoFailed();

	///런닝맨2 티켓 충전을 받았다.
	virtual void onRecvRunningMan2RechargeTicketOK(const TicketScrambleInfo& ticketScrambleInfo);

	///런닝맨2 티켓 충전을 실패했다.
	virtual void onRecvRunningMan2RechargeTicketFailed();

	///런닝맨2 결과 보상아이템을 받았다.
	virtual void onRecvRunningMan2ResultReward(const RewardInfo & rewardInfo);

	///런닝맨2 정보 초기화를 받았다.
	virtual void onRecvRunningMan2InitInfo();

	/// 런닝맨2 상점에서 아이템 구매시 구매 요청에 성공했다.
	virtual void onRecvRunningMan2ShopBuyItemOK(int iItemNum, const std::vector<PieroOlympicShopInfo>& shopInfo);

	/// 런닝맨2 상점에서 아이템 구매시 구매 요청에 실패했다.
	virtual void onRecvRunningMan2ShopBuyItemFailed(ePieroOlympicShopFailedReason failedReason, int iItemNum);

	/// 런닝맨2 상점 정보 요청에 성공했다.
	virtual void onRecvRunningMan2GetShopInfoOK(const std::vector<PieroOlympicShopInfo>& shoInfo);

	/// 런닝맨2 상점 정보 요청에 실패했다.
	virtual void onRecvRunningMan2GetShopInfoFailed();

#endif	// _RUNNING_MAN2

	//////////////////////////////////////////////////////////////////////////
	// 협동 달리기 모드 시작

	/// 유저의 마지막 클리어한 맵룰 정보를 받았다.
	virtual void onRecvCorunModeGetUserLastClearedMapRuleInfoOK();

	/// 유저의 마지막 클리어한 맵룰 정보 받기를 실패했다.
	virtual void onRecvCorunModeGetUserLastClearedMapRuleInfoFailed(eCorunModeFailedReason eFailedReason);

	/// 유저의 마지막 클리어한 맵룰 정보가 업데이트되었다.
	virtual void onRecvCorunModeUpdateUserLastClearedMapRuleInfo();

	/// 현재 맵의 최고 기록을 받았다. (협동 달리기 모드에서 방장이 게임 로딩 시작을 요청하면 서버에서 보내줌)
	virtual void onRecvCorunModeTopRecord(eCorunModeRank eRank, int iClearTime, std::vector<std::string> &vecUserNickname);

	/// 시간이 흐는 구간의 클리어 제한 시간을 설정해라.
	virtual void onRecvCorunModeSetClearLimitTime(int iClearLimitTime);

	/// 맵 이벤트가 발생했다.
	virtual void onRecvCorunModeTriggerMapEvent(BYTE byEventNum, int iEventLapTime);

	/// 오브젝트 이벤트가 발생했다.
	virtual void onRecvCorunModeTriggerObjectEvent(int iObjectIndex, eCorunModeObjectEventType eEventType,unsigned int iValue);

	// 오브젝트 점유 체크 후 이벤트가 발생한다.
	virtual void onRecvCorunModeTriggerCheckInObjectEvent(const BYTE numGameIndex, int iObjectIndex, int iLockIndex, eCorunModeObjectEventType eEventType,unsigned int iValue);

	/// 폭탄 설치 모션 이벤트가 발생했다.
	virtual void onRecvCorunModeTriggerBombMotionEvent(byte byEventNum, byte byManagerIndex, byte byGeneratorIndex, byte byObjectIndex);
	/// 시간이 흐르는 구간에 누군가 입장했다.
	virtual void onRecvCorunModeEnterTimeSection(BYTE bySectionNum, int iClearLimitTime, int iBonusTime);

	/// 시간이 흐르는 구간을 마지막 유저가 클리어했다.
	virtual void onRecvCorunModeClearTimeSection(BYTE bySectionNum, int iClearTime, int iBonusTime);

	/// 보스 에너지를 설정했다.
	virtual void onRecvCorunModeSetBossEnergyOK(int iObjectIndex);

	/// 보스 에너지 설정을 실패했다.
	virtual void onRecvCorunModeSetBossEnergyFailed(eCorunModeFailedReason eFailedReason);

	/// 보스 에너지를 차감했다.
	virtual void onRecvCorunModeDecreaseBossEnergy(int iBossEnergy, int iObjectIndex);

	/// 오브젝트 보스 에너지를 설정했다.
	virtual void onRecvCorunModeSetObjectBossEnergyOK(int iObjectType, int iObjectIndex, int iValue);

	/// 오브젝트 보스 에너지 설정을 실패했다.
	virtual void onRecvCorunModeSetObjectBossEnergyFailed(int iObjectType, int iObjectIndex, int iValue, eCorunModeFailedReason eFailedReason);

	/// 오브젝트 보스 에너지를 차감했다.
	virtual void onRecvCorunModeDecreaseObjectBossEnergy(int iObjectType, int iObjectIndex, int iValue, int iBossEnergy);

	/// 오브젝트 보스 에너지를 증가시켰다.
	virtual void onRecvCorunModeIncreaseObjectBossEnergy(int iObjectType, int iObjectIndex, int iValue, int iBossEnergy);

#ifdef _SHOP_RENEWAL_
	//////////////////////////////////////////////////////////////////////////
	// 상점 리뉴얼

	/// 상점 카테고리를 받았다
	virtual void onRecvShopCategoryACK(std::vector < ShopCategory > & vecCategory, std::multimap<int, ShopCategoryPurchasing > & mapShopCategoryPurchasing);
	virtual void onRecvShopCategoryFailed(eServerResult dwResult);

	/// 상점 전시 리스트를 받았다.
	virtual void onRecvShopDisplayLIstACK(SHOP_DISPLAY_LIST & list);
	virtual void onRecvShopItemSellLIstACK(std::multimap<int, ShopItemSellList > & list);
	virtual void onRecvShopDisplayDateLIstACK(SHOP_DISPLAY_DATE_LIST & list);
	virtual void onRecvShopBuyLimitCountLIstACK(SHOP_BUY_LIMIT_COUNT_LIST & list);
	virtual void onRecvShopBuyAddBenefitLIstACK(SHOP_BUY_ADD_BENEFIT_LIST & list);
	virtual void onRecvShopBuyAddSellPriceLIstACK(SHOP_BUY_ADD_SELL_PRICE_LIST & list);
	virtual void onRecvShopDisplayLIstFailed(eServerResult dwResult);

	/// 상점 전시 리스트 리로드 공지를 받았다.
	virtual void onRecvShopDisplayReloadNotify();

	/// 유저의 VIP 상점 레벨 공지를 받았다.
	virtual void onRecvShopVipLevelNotify(const int iVipLevel);

	/// 유저의 VIP 상점 레벨 리셋 공지를 받았다.
	virtual void onRecvShopVipLevelResetNotify();

	/// 상점 랭크 초기화 공지를 받았다.
	virtual void onRecvShopRanklResetNotify();

	/// 상점 구매횟수 리셋 공지를 받았다.
	virtual void onRecvShopBuyCountResetNotify();

	/// 상점 구매횟수 리스트를 받았다.
	virtual void onRecvShopUserBuyCountLIstACK(SHOP_BUY_LIMIT_COUNT_LIST & list, std::map<int, int> & sellList);
	virtual void onRecvShopUserBuyCountLIstFailed(eServerResult dwResult);

	/// 상점 구매횟수 리스트를 받았다.
	virtual void onRecvShopBuyCountLIstACK(std::map<int, int> & sellList);
	virtual void onRecvShopBuyCountLIstFailed(eServerResult dwResult);

	// 상점 랭크 리스트를 받았다.
	virtual void onRecvShopRankACK(int iCategory1, int iCategory2, int iCategory3, std::map<int, int> & list);
	virtual void onRecvShopRankFailed(eServerResult dwResult);

	// 상점 찜 리스트를 받았다.
	virtual void onRecvShopUserWishLIstACK(std::map<int, time_type> & list);
	virtual void onRecvShopUserWishLIstFailed(eServerResult dwResult);

	// 상점 찜 리스트에 등록 결과를 받았다.
	virtual void onRecvShopSetUserWishLIstACK(eShopWishListType wishType, int iDisplayNum);
	virtual void onRecvShopSetUserWishLIstFailed(eServerResult dwResult) ;

#endif
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	/// 상점 관련 시작

	/// 현재 TR 을 받았다.
	virtual void onRecvCurrentGameMoney(const int iGameMoney);

	//! 연금술사에서 아이템 분해를 한다.
	virtual void onRecvAlchemistDisjoint(eServerResult eResult,const int iItemDescNum);

	//! 연금술사 조합을 시작하겠다.
	virtual void onRecvAlchemistMixBegin(eServerResult eResult);

	/// 연금술사 조합이 성공했다.
	virtual void onRecvAlchemistMixEndOK(const UserItemAttrInfo& itemInfo);

	/// 연금술사 조합이 실패
	virtual void onRecvAlchemistMixEndFailed(eAlchemistMixFailedReason reason);

	/// 연금 아이템의 등급 인첸트에 성공했다.
	virtual void onRecvAlchemistEnchantGradeOK(const UserItemAttrInfo& itemInfo, bool bSuccess);

	/// 연금 아이템의 등급 인첸트에 실패했다.
	virtual void onRecvAlchemistEnchantGradeFailed(eAlchemistEnchantGradeFailedReason reason);

	/// 아이템 제작 가능한 시간 요청에 성공했다.
	virtual void onRecvItemManufactureCoolTimeOK(int iManufactureNum, time_type tAlchemistCoolTime);

	/// 아이템 제작 가능한 시간 요청에 실패했다.
	virtual void onRecvItemManufactureCoolTimeFailed(int iManufactureNum);

	/// 아이템 제작 요청에 성공했다.
	virtual void onRecvItemManufactureMakeOK(int iManufactureNum);

	/// 아이템 제작 요청에 실패했다.
	virtual void onRecvItemManufactureMakeFailed(int iManufactureNum, eItemManufactureFailedReason reason);

	/// 혼돈의 완성체 보너스 정보를 받았다.
	virtual	void onRecvChaosCompletionUnitBonus(const BuffBonusInfo& bonusInfo);

	/// 삐에로 참여 보너스 정보를 받았다.
	virtual	void onRecvPieroJoinBuffBonus(const BuffBonusInfo& bonusInfo);

	/// 이 방에 있는 영웅 등급 유저중 최고 경험치 유저의 상태 변경을 받았다.
	virtual void onRecvSortedHeroClassGameIndices(const std::vector<BYTE>& heroClassGameIndices);

	/// 영웅 등급 보너스 버프 정보를 받았다.
	virtual void onRecvHeroClassBuffBonusNotify(const BuffBonusInfo& bonusInfo);

	/// 길드 보너스 정보를 받았다.
	virtual	void onRecvGuildUnitNotice(const BuffBonusInfo& bonusInfo);

	/// 드래곤 세트 보너스 정보를 받았다.
	virtual void onRecvDragonAlchemistUnitBouns(const DragonAlchemistItemBonus& bonusInfo);

	/// 프리미엄 방장 보너스 정보를 받았다.
	virtual	void onRecvSuperRoomMasterInfo(const SuperRoomMasterInfo& bonusInfo);

	/// 스페셜 게임 보상 통지를 받았다
	virtual void onRecvSpecialGameRewardNotify(JackPotReward& rewardInfo);

	/// 상점이 닫혀있다. 서버가 종료를 대기하거나, 시작 중이다.
	virtual void onRecvShopClosed();

	/// 상점에서 물건 사는것이 성공했다.
	//virtual void onRecvShopBuyProductItemDescNum(const int iItemDescNum, const int m_iGameMoney);

	/// 상점에서 물건들 여러 개를 사는것이 성공했다.
	virtual void onRecvShopBuyProductsTogetherSuccess(const std::vector <BuyingItemInfo> & successItemList, const std::map<__int64,int>& mapItemID, const std::map<int, int> & soldOutItemDesc, const std::vector<int>& discountCouponList);

	/// 상점에서 물건들 어려개를 사는 것이 실패했다.
	virtual void onRecvShopBuyProductsTogetherFailed(const eShopFailed_REASON failedReason, const std::vector < BuyingItemInfo > & successItemList, const std::vector < BuyingItemInfo > & failedItemList, const std::map<__int64,int>& mapItemID, const std::map<int, int> & soldOutItemDesc);		//!< 악세사리 종류 갯수

	/// 빌링 서버의 에러를 받았다.
	virtual void onRecvBillingError(eBillingError billingError);

	//////////////////////////////////////////////////////////////////////////

	/// 닉네임 검색 성공
	virtual void onRecvSearchNickNameOK(const std::string & strSearchNickname);
	
	/// 쪽지 보내는 것을 성공
	virtual void onRecvMessageSendOK(MessageSystemInfo & messageInfo);

	/// App에서 쪽지 보내는 것을 성공
	virtual void onRecvMessageAppSendOK(std::vector<MessageSystemInfo>& messageInfo);

	/// 쪽지를 체크하라고 받았다.
	virtual void onRecvCheckMessage(MessageSystemInfo & messageInfo);
	virtual void onRecvCheckMessage(const std::map <__int64, MessageSystemInfo >& newArrivalMessageList);

	/// 쪽지함 목록을 받았다
	virtual void onRecvMessageBoxList(const eMessageBoxType & messageBoxType, const unsigned short numPage, const unsigned short totalCount, const std::map <__int64, MessageSystemInfo > & messageMap);
	
	/// 쪽지 읽기 성공.
	virtual void onRecvReadMessageOK(const __int64 iMessageNum);

	/// 쪽지 신고 성공.
	virtual void onRecvAccuseMessageOK(const __int64 iMessageNum);

	/// 쪽지 삭제 성공.
	virtual void onRecvDeleteMessageOK(const eMessageBoxType & messageBoxType, const bool isAll, std::vector<__int64>& vecMessageNum);

	/// 쪽지 보관 성공.
	virtual void onRecvKeepMessageOK(const __int64 iMessageNum);

	/// 친구 추가권 가능 횟수
	virtual void onRecvGetFriendAddFriendOK();

	/// 쪽지 관련 실패
	virtual void onRecvMessageFailed(const eMessageBoxFailed failedReason);

	/// 쪽지 옵션 읽기.
	virtual void onRecvGetMessageOptionOK(const eMessageBoxOption & messageOption);

	//////////////////////////////////////////////////////////////////////////

	/// 선물 보내는 것을 성공
	virtual void onRecvGiftProductOK(const int iItemDescNum, const int iGameMoney);

	/// 선물 보내는 것을 실패
	virtual void onRecvGiftProductFailed(const eGiftItemFailed failedReason);

	/// 선물을 체크하라고 받았다.
	virtual void onRecvCheckGift(const std::vector<eNewGiftMessagType>& msgList);

	/// 상점에서 받기 대기 중인 선물 목록을 받았다.
	virtual void onRecvAcceptWaitGiftList(const unsigned short numPage,const unsigned short ItemCountPerPage, const std::vector < AcceptWaitItem > & v,int iTotalCount);

	/// 상점에서 받기 대기 중인 선물 목록을 받는데 실패
	virtual void onRecvAcceptWaitGiftListFailed();

	/// 상점에서 대기 중인 선물을 받았음.
	virtual void onRecvAcceptGiftOK(std::vector<int> vecGiftNum);

	/// 상점에서 대기 중인 선물을 받는데 실패
	virtual void onRecvAcceptGiftFailed(const eGiftAcceptFailedReason failedReason);

	/// 받은 선물 리스트를 받았다.
	virtual void onRecvAcceptedGiftList(const std::vector < AcceptedGift > & v) {}

	/// 받은 선물 리스트를 받는데 실패했다.
	virtual void onRecvAcceptedGiftListFailed() {}

	/// 상점에서 캐시를 받았다.
	virtual void onRecvShopCash(int iCash);

	/// 상점에서 캐시를 받는데 실패했다.
	virtual void onRecvShopCashFailed();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//!< 아린의 연금 관련 이벤트 핸들러. 

	/// 강화 아이템 목록을 정상적으로 받았다. 
	virtual void onRecvStrengthenItemListOK(const std::vector<CStrengthenItemDesc> & strengthens); 

	/// 강화 아이템 목록을 받던 도중 문제 발생.
	virtual void onRecvStrengthenItemListFailed(eStrengthenItemListFailedReason failedReason);

	/// 아이템 강화를 성공했다. 
	virtual void onRecvReInforceItemOK(const eStrengthenReInforceResponse response, const int & reInforcedItemNum, const unsigned short & reInforcedSlotIndex, const int & remainGameMoney, const int & remainReInforceCnt);	

	/// 아이템 강화를 실패했다. 
	virtual void onRecvReInforceItemFailed(const eStrengthenReInforceFailedReason & failedReason, const int & reInforceItemNum, const unsigned short & reInforceSlotIdx); 

	/// 아이템 정화를 성공했다. 
	virtual void onRecvPurifyItemOK(const int & purifiedItemNum, const unsigned short & purifySlotIndex, const int & usedItemDescNum, const unsigned short & remainPurifyItemCount);

	/// 아이템 정화를 실패했다. 
	virtual void onRecvPurifyItemFailed(const eStrengthenPurifyFailedReason & failedReason, const int & purifyItemNum, const unsigned short & purifySlotIdx); 

	/// 아이템의 강화 횟수 충전을 성공했다. 
	virtual void onRecvReChargeReInforceChanceOK(const int & rechargedItemNum, const unsigned short & refreshChanceCnt, const int & usedItemNum); 

	/// 아이템의 강화 횟수 충전을 실패했다. 
	virtual void onRecvReChargeReInforceChanceFailed(const eStrengthenRechargeReInforceChanceFailedReason & failedReason, const unsigned int & rechargeItemNum, const unsigned int & usingItemNum); 

	/// 아이템의 슬롯 개수 증가를 성공했다. 
	virtual void onRecvIncreaseSlotCountOK(const int & increasedItemNum, const unsigned short & refreshedSlotCnt, const int & usedItemNum); 

	/// 아이템의 슬롯 개수 증가를 실패했다. 
	virtual void onRecvIncreaseSlotCountFailed(const eStrengthenIncreaseSlotCountFailedReason & failedReason, const int & increaseItemNum, const int & usingItemNum); 

	/// 아이템의 특정 슬롯 특화계열 정보변경을 성공했다. 
	virtual void onRecvChangeSlotSpecializedTypeOK(const int & changedItemNum, const unsigned short & changedSlotIdx, const unsigned short & refreshedType, const int & usedItemNum); 

	/// 아이템의 특정 슬롯 특화계열 정보변경을 실패했다. 
	virtual void onRecvChangeSlotSpecializedTypeFailed(const eStrengthenChangeSlotSpecializedTypeFailedReason & failedReason, const unsigned int & targetItemNum, const int & usingItemNum); 

	/// 무료 망치 정보를 얻거나 무료 망치를 갖는다.
	virtual void onRecvGetFreeHammer(const eItemStrengthenGetFreeHammerType & type, const byte & bAcquisitionCount, const byte & bRemainingCount, const byte & bPossessionCount, time_type & lastAcquisitionTime );

	/// 무료 망치 정보를 얻거나 무료 망치를 갖지 못하였다.
	virtual void onRecvGetFreeHammerFailed(const eItemStrengthenGetFreeHammerType & type, const eItemStrengthenGetFreeHammerFailedReason & failedReason );

	/// 아린의 연금상점의 판매 물품을 받았다.
	virtual void onRecvPremiumArinShopItemListOK(const std::map<int, ArinShopItemInfo> & itemTable); 

	/// 아린의 연금상점의 판매 물품을 받지 못했다. 
	virtual void onRecvPremiumArinShopItemListFailed(const ePremiumArinShopItemListFailedReason & failedReason);

	/// 아이템 변형 요청에 성공했다.
	virtual void onRecvTransformItemOK(cpk_type iCharacter, cpk_type iPosition, cpk_type iTransKind, int iTransItemNum);

	/// 아이템 변형 요청에 실패했다.
	virtual void onRecvTransformItemFailed(eItemTransformFailedReason eReason);

	//!< 강화아이템 관련 이벤트 핸들러 끝. 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 기념 대상 오브젝트에 특정 행위에 대한 성공 응답을 받았다.
	virtual void onRecvAnniversaryObjectActionOK(const AnniversaryObjectAction & objectAction, AnniversaryAction action);

	/// 기념 대상 오브젝트에 특정 행위에 대한 실패 응답을 받았다.
	virtual void onRecvAnniversaryObjectActionFailed(int iObjectNum);

	/// 기념 대상 오브젝트의 값을 받았다.
	virtual void onRecvAnniversaryObjectValueOK(std::map<int,int> objectValueMap);
	virtual void onRecvAnniversaryObjectValueOK64(std::map<int,__int64> objectValueMap);

	/// 기념 대상 오브젝트의 값 받기에 실패했다.
	virtual void onRecvAnniversaryObjectValueFailed(std::map<int,int> objectValueMap);
	virtual void onRecvAnniversaryObjectValueFailed64(std::map<int,__int64> objectValueMap);

	/// 기념 대상 오브젝트의 유저 정보를 받았다.
	virtual void onRecvAnniversaryGetUserInfo(int objectNum, int iRank, int value);

	/// 기념 대상 오브젝트에 값이 추가되었다.
	virtual void onRecvAnniversaryAddObjectValueOK(const AnniversaryObjectAction & objectAction, int iValue);
	virtual void onRecvAnniversaryAddObjectValueOK64(const AnniversaryObjectAction & objectAction, __int64 iValue);

	/// 기념 대상 오브젝트에 값이 감소되었다.
	virtual void onRecvAnniversarySubstractObjectValueOK(const AnniversaryObjectAction & objectAction, int iValue);
	virtual void onRecvAnniversarySubstractObjectValueOK64(const AnniversaryObjectAction & objectAction, __int64 iValue);

	/// 기념 대상 오브젝트에 값이 감소실패되었다.
	virtual void onRecvAnniversarySubstractObjectValueFailed(ePieroOlympicFailedReason eReason);

	// 기념 대상 오브젝트로 부터 받은 보상 단계 리스트를 받았다.
	virtual void onRecvAnniversaryGetReveivedRewardGradeList(int iObjectNum, __int64 iValue, std::vector<BYTE> grades);

	// 기념 대상 오브젝트로 부터 해당 등급의 보상을 받았다.
	virtual void onRecvAnniversaryReceiveReward(eAnniversaryActionResult result, const RewardInfo& reward);

#ifdef _DUCTILITY_SYSTEM_
	// 연성시스템 오브젝트에 특정 행위에 대한 응답을 받았다.
	virtual void onRecvDuctilityObjectActionOK(const AnniversaryObjectAction & objectAction, DuctilityAction action);

	// 연성 시스템 대상 오브젝트의 회차별 보상을 받았다.
	virtual void onRecvDuctilityObjectStepReward(eDuctilityResult result, int iObjectNum, int iStepNum, RewardInfo& rewardInfo);

	// 연성 시스템 연성 후 조건 보상을 받았다.
	virtual void onRecvDuctilityConditionRewardList(eDuctilityResult result, int iConditionNum, std::vector<RewardInfo>& rewardList);
#endif

#ifdef _TREASURE_HUNT
	// 보물찾기 시스템이 시작되엇다.
	virtual void onRecvTreasureHuntStart();

	// 보물찾기 시스템이 끝났다.
	virtual void onRecvTreasureHuntEnd();

	// 보물찾기 시작 정보를 받았다.
	virtual void onRecvTreasureHuntStartInfo(time_type tStartTime, bool bStart, int iEndTime, int iFreePlayCount, int iTicketPlayCount);

	// 주기적으로 보내주는 보물찾기 정보를 받았다.
	virtual void onRecvTreasureHuntInfo(int iFullCount, int iCurrCount, eTreasure_Boost_Level eBoostLevel);

	// 보물찾기 시스템에서 부스트가 발동되었다.
	virtual void onRecvTreasureHuntBoost(int iFullCount, int iCurrCount, eTreasure_Boost_Level eBoostLevel);

	// 패스워드에 대한 응답을 받았다.
	virtual void onRecvTreasureHuntPasswordAck(eTreasure_BOXACT eBoxAct, Treasure_Box sTreasureBox, int iPassword);

	// 보물이 삭제되었다.
	virtual void onRecvTreasureHuntDelete(Treasure_Box sTreasureBox);

	// 보물을 찾았다.
	virtual void onRecvTreasureHuntFindAck(eTreasure_BOXACT eBoxAct, Treasure_Box sTreasureBox, int itemNum);

	// 보물을 찾지 못했다.
	virtual void onRecvTreasureHuntFindFailed();

	// 보물상자에 대한 데이터를 받았다.
	virtual void onRecvTreasureHuntBoxData(std::vector<Treasure_Box> boxList);

	// 보물찾기에 참가하였다.
	virtual void onRecvTreasureHuntEnterAck(bool bUseTicket, bool b);

	// 보물찾기 참가에 실패했다.
	virtual void onRecvTreasureHuntEnterFailed(eTreasure_Result JoinResult);

	// 보물찾기를 포기했다.
	virtual void onRecvTreasureHuntGiveUpAck();

	// 보물찾기 포기에 실패했다.
	virtual void onRecvTreasureHuntGiveUpFailed();
#endif

#ifdef _ONEDAY_BUFF_SYSTEM_
	// 요일 버프 레벨업 결과를 받았다.
	virtual void onRecvOneDayBuffLevelUP(const std::vector<RewardInfo>& rewardList, const OneDayBuffData& buffData, eOneDayBuff_Result result);

	// 요일 버프 시작 공지를 받았다.
	virtual void onRecvOneDayBuffStartNotify(const OneDayBuffData& buffData);

	// 요일 버프 종료 공지를 받았다.
	virtual void onRecvOneDayBuffFinishNotify(const OneDayBuffData& buffData);
#endif

	// 통합 보상을 받았다.
	virtual void onRecvInegratedRewardGiveRewardOK(std::vector<IntegratedReward> rewardList, const AnniversaryObjectAction & objectAction);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 결제 비밀번호
	/// 비밀번호 존재 여부에 대한 정보를 받았음.
	virtual void onRecvIsExistConfirmationPasswordOK(bool bIsExistConfirmationPassword);

	/// 비밀번호 존재 여부에 대한 정보를 받기 실패했음.
	virtual void onRecvIsExistConfirmationPasswordFailed(eServer_IS_EXIST_CONFIRMATION_PASSWORD_FAILED_REASON eFailedReason);

	/// 비밀번호 셋팅을 성공했음.
	virtual void onRecvSetConfirmationPasswordOK();

	/// 비밀번호 셋팅을 실패했음.
	virtual void onRecvSetConfirmationPasswordFailed(eServer_SET_CONFIRMATION_PASSWORD_FAILED_REASON eFailedReason);

	/// 비밀번호 체크를 성공했음.
	virtual void onRecvCheckConfirmationPasswordOK();

	/// 비밀번호 체크를 실패했음.
	virtual void onRecvCheckConfirmationPasswordFailed(eServer_CHECK_CONFIRMATION_PASSWORD_FAILED_REASON eFailedReason);

	//////////////////////////////////////////////////////////////////////////
	// 이벤트 아이템 교환
	/// 이벤트 아이템으로 교환할 수 있는 아이템 목록을 받았음.
	virtual void onRecvEventItemExchangeItemListOK(int iEventNum, const std::vector<RewardItemInfo> &vecRewardList);

	/// 이벤트 아이템으로 교환할 수 있는 아이템 목록받기를 실패했음.
	virtual void onRecvEventItemExchangeItemListFailed(int iEventNum, eServer_EVENT_ITEM_EXCHANGE_ITEM_LIST_FAILED_REASON eFailedReason);

	/// 이벤트 아이템 교환을 성공했음.
	virtual void onRecvExchangeEventItemOK(int iEventNum, eRewardCondition eRewardType, int iReward);

	/// 이벤트 아이템 교환을 실패했음.
	virtual void onRecvExchangeEventItemFailed(int iEventNum, eServer_EXCHANGE_EVENT_ITEM_FAILED_REASON eFailedReason);

	//////////////////////////////////////////////////////////////////////////
	
	// 점술상점
	/// 점술이 무료로 가능한지 불가능한지를 받았다.(bFree = TRUE : 무료, FALSE : 유료)
	virtual void onRecvDivinationCheckFree( bool bFree, eDivinationType requestType);

	/// 점술 무료 조회가 실패했다.
	virtual void onRecvDivinationCheckFreeFailed(eDivinationType requestType);

	/// 점괘를 받았다.
	virtual void onRecvDivinationResult(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities, eDivinationType requestType);

	/// 점보기가 실패했다.
	virtual void onRecvDivinationResultFailed(eDivinationFailReason failReason, eDivinationType requestType);

	/// 내 커플에 의해 버프를 받았다.
	virtual void onRecvDivinationCoupleExAbilitiesResult(const ExtraAbilityInfo & appliedExtraAbilities, std::string strDivinationDesc);

	virtual void onRecvDivinationCoupleExAbilitiesResultFailed();

	//////////////////////////////////////////////////////////////////////////
	// 특별 능력치(버프)

	/// 요청한 특별 능력의 목록(특별한 능력치-버프-가 적용되는 아이템 목록)을 받았다.
	virtual void onRecvExtraAbilities(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities);

	/// 특별 늑력치 받기가 실패했다.
	virtual void onRecvExtraAbilitiesFailed();

	/// 특별 능력치(버프)아이템 사용을 성공했다.
	virtual void onRecvUseExtraAbilityItem(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities,eDivinationType requestType, int iUseItemNum, int iRemainUseItemCount);

	/// 특별 능력치(버프)아이템 사용을 실패했다.
	virtual void onRecvUseExtraAbilityItemFailed(eUseExtraAbilityItemFailReason failReason, eDivinationType requestType);

	/// 미션 보상 특별 능력치(버프)아이템 사용을 성공했다.
	virtual void onRecvUseMissionExtraAbilityItem(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities,eMissionKind missionKind);

	/// 미션 보상 특별 능력치(버프)아이템 사용을 실패했다.
	virtual void onRecvUseMissionExtraAbilityItemFailed(eUseExtraAbilityItemFailReason failReason, eMissionKind missionKind);

	//////////////////////////////////////////////////////////////////////////

	///<! 동물레이싱 관련 이벤트 핸들러
	// 동물 길들이기에 성공했다.
	virtual void onRecvAnimalRacingPetTrainingOK(__int64 nFarmItemID, int nFarmPetDescNum, int nRidingPetDescNum);

	// 동물 길들이기에 실패했다.
	virtual void onRecvAnimalRacingPetTrainingFailed(__int64 nFarmItemID, int nItemDescNum, int nReturnValue);

	// 기본 동물 받기 성공
	virtual void onRecvAnimalRacingGetDefaultAnimalOK();
	
	// 기본 동물 받기 실패
	virtual void onRecvAnimalRacingGetDefaultAnimalFailed(int nReason);

	// 만료된 동물 리스트 받기 성공
	virtual void onRecvAnimalRacingGetExpiredAnimalAvatarListOK(std::vector<int> & nAnimalKindList);

	// 만료된 동물 리스트 받기 실패
	virtual void onRecvAnimalRacingGetExpiredAnimalAvatarListFailed();

	//////////////////////////////////////////////////////////////////////////
	// 유저 프로필을 받았다.
	virtual void onRecvUserProfile( const UserProfile & stUserProfile);

	// 유저 프로필을 제대로 받지 못하였다.
	virtual void onRecvUserProfileFailed();

	//유저 프로필을 설정한다.
	virtual void onRecvSetUserProfile(const UserProfile & stUserProfile);

	// 유저 프로필을 제대로 설정하지 못했다.
	virtual void onRecvSetUserProfileFailed();

#ifdef _GAME_OPTION_
	// 유저 게임옵션 정보 받았다.
	virtual void onRecvUserGameOptionOK(std::string & sMacro, std::string & sShare, GameOptionInfo & gameOption);

	// 유저 게임옵션 정보 받지 못하였다.
	virtual void onRecvUserGameOptionFailed();

	//유저 게임옵션 정보 설정한다.
	virtual void onRecvSetUserGameOptionOK();

	// 유저 게임옵션 정보 설정하지 못했다.
	virtual void onRecvSetUserGameOptionFailed();
#endif

#ifdef _SECOND_PASSWORD_
	// 2차 비밀번호 요청 한다.
	virtual void onRecvSecondPasswordInfo();

	// 2차 비밀번호 설정 성공.
	virtual void onRecvSetSecondPasswordOK();

	// 2차 비밀번호 설정 실패.
	virtual void onRecvSetSecondPasswordFailed();

	// 2차 비밀번호 확인 성공.
	virtual void onRecvCheckSecondPasswordOK(eCERTIFY_TYPE certifyType);

	// 2차 비밀번호 확인 실패.
	virtual void onRecvCheckSecondPasswordFailed(eSecondPassword_FAILED_REASON eFailedReason, int iFailedCount, time_type tFailedDate);

	// 2차 비밀번호 변경 성공.
	virtual void onRecvChangeSecondPasswordOK(eCERTIFY_TYPE certifyType);

	// 2차 비밀번호 변경 실패.
	virtual void onRecvChangeSecondPasswordFailed(eSecondPassword_FAILED_REASON eFailedReason, int iFailedCount, time_type tFailedDate);

	// 2차 비밀번호 인증변경 성공.
	virtual void onRecvCertifySecondPasswordOK();

	// 2차 비밀번호 인증변경 실패.
	virtual void onRecvCertifySecondPasswordFailed(eSecondPassword_FAILED_REASON eFailedReason);

	// 2차 비밀번호 사용 해제 성공.
	virtual void onRecvSecondPasswordUseCancelOK(eCERTIFY_TYPE certifyType);

	// 2차 비밀번호 사용 해제 실패.
	virtual void onRecvSecondPasswordUseCancelFailed(eSecondPassword_FAILED_REASON eFailedReason, eCERTIFY_TYPE certifyType, int iFailedCount, time_type tFailedDate);
#endif // _SECOND_PASSWORD_

	//////////////////////////////////////////////////////////////////////////
	/// 팜에서 쓰이는 응답들 시작

	//! 팜을 생성하는데 성공하였다.
	virtual void onRecvFarmCreateFarmOK(const FarmInfo& farmInfo);

	//<! 팜 맵 오브젝트의 변경 성공한 오브젝트의 정보를 수신한다. 

	//! 추가된 맵 오브젝트 아이템 처리. 
	virtual void onRecvFarmModifyByInsertOK(const RecvFarmMapObjectInfo& mapObject); 

	//! 위치나 방향등이 변경된 맵 오브젝트 아이템 처리. 
	virtual void onRecvFarmModifyByModifyOK(const RecvFarmMapObjectInfo& mapObject); 

	//! 삭제된 맵 오브젝트 아이템 처리.
	virtual void onRecvFarmModifyByDeleteOK(const __int64& iFarmDescNum); 


	//! 팜을 새성하는데 실패하였다.
	virtual void onRecvFarmCreateFarmFailed(const eFarm_CREATE_FARM_FAILED_REASON);

	//! 동물한테 수확하는데 성공하였다.
	virtual void onRecvFarmHarvestOK(const __int64 intiTargetItemID,const std::vector<FarmHarvestInfo>& vecResultItem);

	//! 동물한테 수확하는데 실패하였다.
	virtual void onRecvFarmHarvestFailed(const eServerResult& eResult, const __int64 intiTargetItemID);

	//! 팜 수확물에서 수확을 성공하였다
	virtual void onRecvFarmHarvestCropHarvestOK(__int64& farmItemID, std::vector<RewardInfo>& rewardList);

	//! 팜 수확물에서 수확을 실패하였다
	virtual void onRecvFarmHarvestCropHarvestFailed(__int64& farmItemID);

	//! 팜 생산 건물에서 아이템 생성을 성공하였다
	virtual void onRecvFarmHarvestBuildingMakeItemAcOK(const __int64 buildingItemID, const int makeItemNum);

	//! 팜 생산 건물에서 아이템 생성을 실패하였다
	virtual void onRecvFarmHarvestBuildingMakeItemFailed(const __int64 buildingItemID);

	//! 랜덤 팜 포인트를 지급하는데 성공 하였다.
	virtual void onRecvFarmGiveMeRandomFarmPointOK(const __int64 iFarmItemID, const int iRemainFarmPoint, const int iGiveFarmPoint);

	//! 나의 팜 포인트를 얻는데 성공하였습니다.
	virtual void onRecvFarmGetMyFarmPointOK(const int iFarmPoint);

	//! 나의 팜 포인트를 얻는데 실패하였습니다.
	virtual void onRecvFarmGetMyFarmPointFailed();

	//! 랜덤 팜 포인트를 지급하는데 실패하였다.
	virtual void onRecvFarmGiveMeRandomFarmPointFailed(const __int64 iFarmItemID);

	//! 팜을 삭제하는데 성공하였다. 
	virtual void onRecvFarmDestroyFarmOK(const int iFarmUniqueNum); 

	//! 팜을 삭제하는데 실패하였다. 
	virtual void onRecvFarmDestroyFarmFailed(const int iFarmUniqueNum);

	//! 팜 오브젝트 점유 정보 리스트를 받았다.
	virtual void onRecvFarmObjectLockInfoList(std::map<FarmObjectIDIndex, BYTE> mapFarmObjectLockInfoList);

	//! 팜 오브젝트 점유 정보가 변경되었다.
	virtual void onRecvFarmModifyObjectLockInfo(eServerResult eResult, FarmObjectIDIndex stOIDIndex, BYTE iGameIndex, bool bLock);

	//! 팜 이름을 변경하였다.
	virtual void onRecvFarmChangeFarmName( const int iFarmUniqueNum, const std::string strFamrName);

	//! 팜 이름 변경을 실패하였다.
	virtual void onRecvFarmChangeFarmNameFailed( const eServerResult eResult, const eFarm_CHANGE_FARM_NAME_FAILED_REASON failedReason);

	//! 프리미엄팜 타입을 변경하였다.
	virtual void onRecvFarmChangePremiumFarmType( const eServerResult eResult, const int iFarmUniqueNum, const ePremiumFarmType premiumFarmType);

	//! 팜 공개/비공개(비밀번호) 변경을 성공하였다. 
	virtual void onRecvFarmChangePublicModeOK( const int iFarmUniqueNum, const bool bPublic );

	//! 팜 공개/비공개(비밀번호) 변경을 실패하였다. 
	virtual void onRecvFarmChangePublicModeFailed( const eFarm_CHANGE_FARM_PASSWORD_FAILED_REASON byReason );

	//! 팜 Talking-Mode 설정을 변경하였다. 
	virtual void onRecvFarmChangeTalkingMode( const eServerResult eResult, const bool bTalkOn, const FarmChattingInfo& farmChattingInfo, const ePremiumFarmType premiumFarmType);

	//! 랜덤 팜 입장이 가능하다. 
	virtual void onRecvFarmJoinOnRamdonOK( const int& farmUniqueNum );

	//! 랜덤 팜 입장을 실패하였다. 
	virtual void onRecvFarmJoinOnRandomFailed( const eFarm_JOIN_TALKFARM_ON_RANDOM_JOIN_FAILED_REASON& failedReason); 

	//! 닉네임을 통한 팜 검색 성공. 
	virtual void onRecvFarmSearchByNickNameOK( const int iFarmUniqueNum, const bool isPublic); 
	
	//! 닉네임을 통한 팜 검색 실패. 
	virtual void onRecvFarmSearchByNickNameFailed( const eFarm_SEARCH_FARM_FAILED_REASON& failedReason); 

	//! 유저번호를 통한 팜 검색 성공. 
	virtual void onRecvFarmSearchByUserNumOK(const int iFarmUniqueNum, const bool isPublic);

	//! 유저번호를 통한 팜 검색 실패. 
	virtual void onRecvFarmSearchByUserNumFailed(const eFarm_SEARCH_FARM_FAILED_REASON failedReason);

	//! 팜정보를 얻는데 성공하였다.
	virtual void onRecvFarmGetFarmInfoOK(const int iFarmUniqueNum,const FarmInfo& info);

	//! 팜정보를 얻는데 실패하였다.
	virtual void onRecvFarmGetFarmInfoFailed(const int iFarmUniqueNum);

	//! 자신의 팜정보를 얻는데 성공하였다. 
	virtual void onRecvFarmGetMyFarmInfoOK(const FarmInfo& info); 

	//! 자신의 팜정보를 얻는데 실패하였다. 
	virtual void onRecvFarmGetMyFarmInfoFailed(void);	

	//! 길드 팜정보를 얻는데 성공하였다. 
	virtual void onRecvFarmGetGuildFarmInfoOK(const FarmInfo& info);

	//! 길드 팜정보를 얻는데 실패하였다. 
	virtual void onRecvFarmGetGuildFarmInfoFailed(void);

	//! 길드팜 맵 타입이 변경되었다
	virtual void onRecvGuildFarmGetChangeMapType(const int iGuildNum, const int iFarmUniqueNum, const int iGuildFarmType);

	//! 길드팜 맵 타입이 실패하였다
	virtual void onRecvGuildFarmGetChangeMapTypeFailed( const eFarm_GET_GUILDFARM_INFO_FAILED_REASON & byReason );

	//! 길드팜 오브젝트의 능력치를 얻는데 성공하였다.
	virtual void onRecvFarmGetGuildFarmObjectAttrListOK(const int iGuildNum, std::map<int, GuildFarmItemAttrInfo > & mapFamrItemAttr);

	//! 길드팜 오브젝트의 능력치를 얻는데 실패하였다.
	virtual void onRecvFarmGetGuildFarmObjectAttrListFailed();	

	//! 길드팜 식물 수확에 성공하였다.
	virtual void onRecvGuildFarmGetHarvestOK(const int iGuildNum, const __int64 iOID, const bool bDelete);

	//! 길드팜 식물 수확에 실패하였다.
	virtual void onRecvGuildFarmGetHarvestFailed(const eServerResult& eResult,const __int64 intiTargetItemID);

	//!< 길드집사 팻말의 내용을 변경하였다.
	virtual void onRecvFarmModifyGuildFarmNoticeBoardInfo(const int iGuildNum, const std::string & strBoardInfo);

	//!< 길드집사 팻말의 내용 변경에 실패하였다.
	virtual void onRecvFarmModifyGuildFarmNoticeBoardInfoFailed(const int iGuildNum);

	//! 팜관련 아이템 리스트 갱신을 시작한다. 
	virtual void onRecvFarmGetFarmItemListBegin(void); 

	//! 팜관련 아이템 리스트를 얻는데 성공하였다.
	virtual void onRecvFarmGetFarmItemListOK(const std::vector<FarmItemInfo>&	vecItems);

	//! 팜관련 아이템 리스트를 모두 다 받았다. 
	virtual void onRecvFarmGetFarmItemListAll(const size_t& totalCount);

	//! 팜관련 아이템 리스트를 얻는데 실패하였다.
	virtual void onRecvFarmGetFarmItemListFailed();

	//! 팜 관련 특정 아이템 목록을 받았다.
	virtual void onRecvFarmGetFarmItemListExOK(const std::vector<FarmItemInfo>&	vecItems);

	//! 길드팜 관련 특정 아이템 목록을 받았다.
	virtual void onRecvFarmGetGuileFarmItemListExOK(const int iGuildNum, const std::vector<FarmItemInfo>&	vecItems);

	//! 팜관련 맵정보를 얻는데 성공하였다.
	virtual void onRecvFarmGetFarmMapInfoOK(const int iFarmUniqueNum, const int iFarmMapType, const std::vector<RecvFarmMapObjectInfo>& vecMapInfo, const std::vector<RecvFarmMapVoxelsInfo>& vecVoxelInfo);
	//! 팜의 맵정보를 리로드했다.
	virtual void onRecvFarmReloadFarmMapInfo(const int iFarmUniqueNum, const int iFarmTypeNum, const int iFarmSkyBoxNum, const int iFarmWeatherNum, const std::vector<RecvFarmMapObjectInfo>& vecMapInfo, const std::vector<RecvFarmMapVoxelsInfo>& vecVoxelInfo);

	//! 팜관련 맵정보를 얻는데 실패하였다.
	virtual void onRecvFarmGetFarmMapInfoFailed(const int iFarmUniqueNum);


	//! 맵정보를 초기화하는데 성공하였다.
	virtual void onRecvFarmClearFarmMapInfoOK(const int iFarmUniqueNum);

	//! 맵정보를 초기화하는데 실패하였다.
	virtual void onRecvFarmClearFarmMapInfoFailed(const int iFarmUniqueNum);

	//! 팜맵 수정 관련 서버로부터 정보를 받았다
	virtual void onRecvFarmModifyFarmMapInfoOK(const int iFarmUniqueNum, mapObjectModifyResult& mapObjectResultList);

	//! 나의 팜 슬롯 리스트를 읽는데 성공하였다.  
	virtual void onRecvFarmGetFarmSlotListOK(std::vector<FarmSlotInfo> & vecFarmSlotInfo);

	//! 나의 팜 슬롯 리스트를 읽는데 실패하였다.  
	virtual void onRecvFarmGetFarmSlotListFailed(const eFarm_GET_FARM_SLOT_LIST_FAILED_REASON& failedReason);

	//! 나의 팜 슬롯을 저장하는데 성공하였다.  
	virtual void onRecvFarmSaveFarmSlotInfoOK(const int iFarmSlotNum, const FarmSlotInfo& eResult);

	//! 나의 팜 슬롯을 저장하는데 실패하였다.  
	virtual void onRecvFarmSaveFarmSlotInfoFailed(const eFarm_SAVE_FARM_SLOTINFO_FAILED_REASON& failedReason );

	//! 나의 팜 슬롯을 초기화하는데 성공하였다.  
	virtual void onRecvFarmClearFarmSlotInfoOK(const int iFarmSlotNum);

	//! 나의 팜 슬롯을 초기화하는데 실패하였다.  
	virtual void onRecvFarmClearFarmSlotInfoFailed(const eFarm_CLEAR_FARM_SLOTINFO_FAILED_REASON& failedReason);

	//! 팜관련 슬롯 맵정보를 얻는데 성공하였다.
	virtual void onRecvFarmGetFarmMapSlotInfoOK(const int iFarmUniqueNum, const int iFarmMapType, const int iFarmSkyBoxNum, const int iFarmWeatherNum, const std::vector<RecvFarmMapObjectInfo>& vecMapInfo, const std::vector<RecvFarmMapVoxelsInfo>& vecVoxelInfo);

	//! 팜관련 슬롯 맵정보를 얻는데 실패하였다.
	virtual void onRecvFarmGetFarmMapSlotInfoFailed(const int iFarmUniqueNum);

	//! 나의 팜 슬롯을 불러오기 하는데 성공하였다.  
	virtual void onRecvFarmGetFarmSlotInfoOK(const int newFarmMapType, std::vector<ItemMsgInfo> & vecItemMsgInfo);

	//! 나의 팜 슬롯을 불러오기 하는데 실패하였다.  
	virtual void onRecvFarmGetFarmSlotInfoFailed(const eFarm_GET_FARM_SLOTINFO_FAILED_REASON& failedReason);

	//! 나의 팜 슬롯을 결재 하는데 성공하였다.  
	virtual void onRecvFarmPayFarmSlotResultOK(const int iFarmSlotNum);

	//! 나의 팜 슬롯을 결재 하는데 실패하였다.  
	virtual void onRecvFarmPayFarmSlotResultFailed(const eFarm_PAY_FARM_SLOT_RESULT_FAILED_REASON& failedReason);

	//! 나의 팜 번호를 얻는데 성공하였다.
	virtual void onRecvFarmGetMyFarmUniqueNumOK(const int iFarmUniqueNum);

	//! 나의 팜 정보를 얻는데 실패하였다.
	virtual void onRecvFarmGetMyFarmUniqueNumFailed();

	//! 특정 팜의 퍼미션 정보를 얻는데 성공하였습니다.
	virtual void onRecvFarmGetFarmPermisionInfoOK(const int iFarmUniqueNum, FarmPermisionInfo& rPermisionInfo);

	//! 특정 팜의 퍼미션 정보를 얻는데 실패하였습니다.
	virtual void onRecvFarmGetFarmPermisionInfoFailed(const int iFarmUniqueNum);

	//! 팜 아이템의 능력치를 얻는데 성공하였다.
	virtual void onRecvFarmGetFarmItemAttrListOK(const int iFarmUniqueNum, std::map< __int64, std::map<int, FarmItemAttrInfo > >& mapFamrItemAttr, const bool bGetOnlySetUpObjectAttrInfo, const bool bDataReplace);

	//! 팜 아이템의 능력치를 얻는데 실패하였다.
	virtual void onRecvFarmGetFarmItemAttrListFailed();

	//! 특정 팜의 퍼미션 정보 리스트를 얻는데 성공하였습니다.
	virtual void onRecvFarmGetFarmPermisionInfoListOK(const int iFarmUniqueNum, std::vector<UserFarmPermisionInfo>&		rVecFarmPermisionInfo );

	//! 특정 팜의 퍼미션 정보를 얻는데 실패하였습니다.
	virtual void onRecvFarmGetFarmPermisionInfoListFailed(const int iFarmUniqueNum);

	//!< 특정 팜의 사용기간이 종료되었습니다. 
	virtual void onRecvFarmExpirationPeriodNotify(const int iFarmUniqueNum, const bool isExitFarmFlag); 

	//!< 팜에 설치된 아이템이 제거되었다.
	virtual void onRecvFarmDeleteMapItemNotify(const __int64 iOID);

	//!< 팜 포인트를 이용한 팜의 사용기간 갱신요청을 성공할 경우 호출. (요청한 유저에게만 전달된다.)
	virtual void onRecvFarmRenewalPeriodByFarmPointOK(const int refreshFarmPoint, const FarmInfo myFarmInfo); 

	//!< 팜 포인트를 이용한 팜의 사용기간 갱신요청을 실패할 경우 호출. (요청한 유저에게만 전달된다.)
	virtual void onRecvFarmRenewalPeriodByFarmPointFailed(const eFarm_RENEWAL_FARM_PERIOD_FAILED_REASON failedReason); 

	//!< 팜 아이템을 이용한 팜의 사용기간 갱신요청을 성공할 경우 호출. (요청한 유저에게만 전달된다.)
	virtual void onRecvFarmRenewalPeriodByItemOK(const int iRenewalItemDescNum, const FarmInfo myFarmInfo); 

	//!< 팜 아이템을 이용한 팜의 사용기간 갱신요청을 실패할 경우 호출. (요청한 유저에게만 전달된다.)
	virtual void onRecvFarmRenewalPeriodByItemFailed(const eFarm_RENEWAL_FARM_PERIOD_FAILED_REASON failedReason); 

	//!< 팜에 설치된 아이템에 특정 아이템을 사용할 경우 성공했을 때 호출. 
	virtual void onRecvFarmUseFarmItemToFarmObjectOK(/* 정보 날려야하나.. */); 

	//!< 팜에 설치된 아이템에 특정 아이템을 사용할 경우 실패했을 때 호출. 
	virtual void onRecvFarmUseFarmItemToFarmObjectFailed(const eFarm_USED_FARMITEM_TO_FARMOBJECT_FAILED_REASON failedReason/*itemtype, ...*/); 

	//!< 특정 유저의 팜 기간이 갱신되었을 경우 공통으로 전달되는 정보. (갱신된 방에 있는 팜장을 제외한 유저들에게 전송된다.)
	virtual void onRecvFarmRenewalPeriodNotify(const int farmUniqueNum, const FarmInfo userFarmInfo); 

	//!< 팜 오브젝트 경험치 충전 요청에 대한 응답
	virtual void onRecvFarmObjectExpCharge( const int iPlayerIndex, const __int64 iObjectID, const int iObjectExp, const int iFarmPoint, const int iPremiumFarmPoint, const int iView, int iChargeItemNum);

	//!< 팜 오브젝트 경험치 충전이 알수 없는 이유로 실패했다.
	virtual void onRecvFarmObjectExpChargeFailed(eServerResult eFailedReason);

	//!< 팜 오브젝트의 수확가능 개수 충전 요청이 성공했을 경우 호출. 
	virtual void onRecvFarmObjectHarvestCountChargeOK( const __int64& appliedObjectID, const int& renewalCount, int iUsedItemDescNum); 

	//!< 팜 오브젝트의 수확가능 개수 충전 요청이 실패했을 경우 호출. 
	virtual void onRecvFarmObjectHarvestCountChargeFailed( const eFarm_OBJECT_HARVEST_COUNT_CHARGE_FAILED_REASON& failedReason);

	//!< 팜 동물의 사이즈 1단계 키우기 요청이 성공했을 경우 호출. 
	virtual void onRecvFarmIncreaseAnimalSizeOK(const __int64 appliedObjectID, const int view); 

	//!< 팜 동물의 사이즈 1단계 키우기 요청이 실패했을 경우 호출. 
	virtual void onRecvFarmIncreaseAnimalSizeFailed(const __int64 failedObjectID, const eFarm_INCREASE_ANIMAL_SIZE_FAILED_REASON failedReason); 

	//!< 팜 동물을 기본 사이즈로 복원 요청이 성공했을 경우 호출. 
	virtual void onRecvFarmRestoreAnimalDefaultSizeOK(const __int64 appliedObjectID, const int view); 

	//!< 팜 동물을 기본 사이즈로 복원 요청이 실패했을 경우 호출. 
	virtual void onRecvFarmRestoreAnimalDefaultSizeFailed(const __int64 failedObjectID, const eFarm_RESTORE_ANIMAL_DEFAULT_SIZE_FAILED_REASON failedReason); 

	//!< 초대에 대한 응답처리 실패. 
	virtual void onRecvFarmGoTogetherFarmRoomFailed(const eFarm_GO_TOGETHER_FARM_ROOM_FAILED_REASON& failedReason);

	//!< 팜 지형변경 아이템 사용 요청이 성공했을 경우 호출. 
	//!< 성공시 반드시, 팜 맵 정보를 재요청해야한다. 
	virtual void onRecvFarmChangeMapTypeOK(const int& farmUniqueNum, const int& newFarmMapType); 

	//!< 팜 지형변경 아이템 사용 요청이 실패했을 경우 호출. 
	virtual void onRecvFarmChangeMapTypeFailed( const eFarm_CHANGE_FARM_MAP_TYPE_FAILED_REASON& failedReason); 

	//!< 팜 팻말의 내용을 받았다.
	virtual void onRecvFarmNoticeBoardInfo(const __int64 iOID, const std::string & strBoardInfo); 

	//!< 팜 팻말의 내용을 변경하였다.
	virtual void onRecvFarmModifyNoticeBoardInfo(const __int64 iOID); 

	//!< 팜 팻말의 내용 변경에 실패하였다.
	virtual void onRecvFarmModifyNoticeBoardInfoFailed(const __int64 iOID);

	//!< 팜 오브젝트의 속성 값 정보가 변경되었다.
	virtual void onRecvFarmModifyObjectValueInfo(const __int64 iOID, const int iValue); 

	//!< 팜 오브젝트의 뷰정보 변경에 실패하였다.
	virtual void onRecvFarmModifyObjectValueInfoFailed(const __int64 iOID); 

	//!< 팜 아이템을 사용해 스카이박스 변경을 성공했을 경우 호출.
	virtual void onRecvFarmChangeSkyboxTypeOK(const int& farmUniqueNum, const int& newSkyBoxType); 

	//!< 팜 아이템을 사용해 스카이박스 변경을 실패했을 경우 호출. 
	virtual void onRecvFarmChangeSkyboxTypeFailed( const eFarm_CHANGE_FARM_SKYBOX_TYPE_FAILED_REASON& failedReason ); 

	//!< 팜 아이템을 사용해 날씨 변경을 성공했을 경우 호출. 
	virtual void onRecvFarmChangeWeatherTypeOK(const int& farmUniqueNum, const int& newWeatherType); 

	//!< 팜 아이템을 사용해 날씨 변경을 실패했을 경우 호출. 
	virtual void onRecvFarmChangeWeatherTypeFailed( const eFarm_CHANGE_FARM_WEATHER_TYPE_FAILED_REASON& failedReason ); 

	//!< 팜 포인트를 이용한 아이템 구매를 성공했다. 
	virtual void onRecvFarmBuyProductsUseFarmPointOK( const int& remainFarmPoint, std::vector<int> successItemList ); 

	//!< 팜 포인트를 이용한 아이템 구매를 실패했다. 
	virtual void onRecvFarmBuyProductsUseFarmPointFailed(const eFarm_BUY_PRODUCTS_USE_FARMPOINT_FAILED_REASON& failedReason); 

	/// 유저 정보를 얻는데 실패하였다. 
	virtual void onRecvFarmGetMasterUserInfoFailed(const eFarm_GET_MASTER_USER_INFO_FAILED_REASON& failedReason, const int& farmUniqueNum);

	/// 특정 팜의 아이템 속성정보가 갱신되었다는 통지를 받음. 
	virtual void onRecvUpdateFarmItemPropertyNotify( std::vector<RecvFarmMapObjectInfo>& farmItemList ); 

	/// 팜아이템의 기간 만료 여부 체크에 성공했다.
	virtual void onRecvCheckFarmItemPeriodOK();

	/// 팜아이템의 기간 만료 여부 체크에 실패했다.
	virtual void onRecvCheckFarmItemPeriodFailed(eServerResult eFailedReason);

	/// 팜 아이템의 메시지를 받았다.
	virtual void onRecvGetFarmItemMsgOK(const std::vector<ItemMsgInfo>& vecItemMsgInfo);

	/// 팜 아이템의 메시지를 받는데 실패했다.
	virtual void onRecvGetFarmItemMsgFailed(eServerResult eFailedReason);

	/// 팜 즐겨찾기 문에 정보를 셋팅했다.
	virtual void onRecvSetFarmPortalInfo(const __int64 m_iObjectID, const int m_iFarmMasterUserNum, const std::string &m_strMemo);

	/// 팜 즐겨찾기 문의 정보 셋팅을 실패했다.
	virtual void onRecvSetFarmPortalInfoFailed(const eFarm_SET_FARM_PORTAL_INFO_FAILED_REASON eFailedReason);

	/// 팜 즐겨찾기 문의 정보를 받았다.
	virtual void onRecvGetFarmPortalInfo(const __int64 iObjectID, const int iFarmMasterUserNum, const std::string &strFarmMasterNickname, const std::string &strMemo);

	/// 팜 즐겨찾기 문의 정보 받기를 실패했다.
	virtual void onRecvGetFarmPortalInfoFailed(const eFarm_GET_FARM_PORTAL_INFO_FAILED_REASON eFailedReason);

	//! 채팅팜 신고요청이 처리되었다.
	virtual void onRecvAccuseChattingFarm(int iFarmUniqueNum, int iCautionCount);

	//! 채팅팜 신고요청이 실패했다.
	virtual void onRecvAccuseChattingFarmFailed(int iFarmUniqueNum);

	//!< 시간제 수확 팜 아이템의 시간 갱신 결과를 받았다
	//!< 시간제 수확 팜 아이템의 시간 갱신 결과를 받았다
	virtual void onRecvFarmObjectInfo(const int farmUniqueNum, const UINT iGameIndex, std::vector<FarmItemInfo>& farmItemList);

	//! 팜 명찰 아이템 사용시 명찰 부여 처리
	virtual void onRecvFarmNameTagSetting( const unsigned int iPlayerIndex, const unsigned int iItemKind, const std::string& strNameTag );

	//! 팜장이 팜원에게 명찰 등록 할것인지 여부를 묻는다.
	virtual void onRecvFarmNameTagCheck( const unsigned int iPlayerIndex, const std::string& strNameTag );

	//! 팜 명찰을 사용하는 룸에 새로운 유저 접속시 기존 룸의 명찰 정보들을 알려준다.
	virtual void onRecvFarmNameTagNewUser( std::map<unsigned int, NameTagInfo>& mapFarmNameTagList );

	//! 팜 명찰을 사용하는 룸에 팜장이 팜에서 나갔을 때 처리
	virtual void onRecvLeaveRoom(unsigned int iPlayerIndex);

	//! 팜 명찰을 사용할때 실패 처리
	virtual void onRecvFarmNameTagFliled( const eFarmNameTagResult& result );

	virtual void onRecvFarmNameTagRemove(const unsigned int iPlayerIndex);


	/// 팜에서 쓰이는 응답들 끝
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	/// 마이룸에서 쓰이는 응답들 시작

	virtual void onRecvMyRoomTransaction(const bool& bTransaction);

	/// 마이룸에서 나의 캐릭터들의 리스트를 얻었다.
	virtual void onRecvMyRoomMyCharacterList(const std::vector < cpk_type > & characterList);

	/// 마이룸에서 나의 캐릭터들의 리스트를 얻는데 실패했다. 치명적인 오류다.
	virtual void onRecvMyRoomMyCharacterListFail();

	/// 마이룸에서 특정 캐릭터의 설정을 얻었다.
	virtual void onRecvMyRoomGetMyCharacterSetting(const AvatarInfo & realAvatarInfo);

	/// 마이룸에서 특정 캐릭터의 설정을 얻는데 실패했다.
	virtual void onRecvMyRoomGetMyCharacterSettingFail();

	/// 마이룸에서 특정 캐릭터의 설정을 저장하는 데 성공했다.
	virtual void onRecvMyRoomSetCharacterSetting();

	/// 마이룸에서 특정 캐릭터의 설정을 저장하는 데 실패했다.
	virtual void onRecvMyRoomSetCharacterSettingFail();

	///마이룸에서 TR 영구 아이템을 되 파는데 성공 했다.
	virtual void onRecvSellTRItemOK(int iItemNum, int iSellPrice);
	///마이룸에서 TR 영구 아이템을 되 파는데 실패 했다.
	virtual void onRecvSellTRItemFailed(eSellTRItemFailedReason eFailedReason);
	/// 기본 캐릭터 설정을 저장하는데 성공했다.
	virtual void onRecvMyRoomSetDefaultCharacterOK();

	/// 기본 캐릭터 설정을 저장하는데 실패했다.
	virtual void onRecvMyRoomSetDefaultCharacterFail();

	/// 케릭터 스탯 리셋 성공했다.
	virtual void onRecvMyRoomCharacterStatResetOK(const int iStatNum, const UserItemAttrInfo & charAttr);

	/// 케릭터 스탯 리셋 실패했다.
	virtual void onRecvMyRoomCharacterStatResetFail(eMyRoomProtocol_STAT_RESET_FAILED_REASON failedReason);

	/// 케릭터 스탯 리셋 동의 성공했다.
	virtual void onRecvMyRoomCharacterStatConfirmOK(const UserItemAttrInfo& useritemAttr);

	/// 케릭터 스탯 리셋 동의 실패했다.
	virtual void onRecvMyRoomCharacterStatConfirmFail(eMyRoomProtocol_STAT_RESET_FAILED_REASON failedReason);

	/// 나의 트로피 리스트를 받았다.
	virtual void onRecvMyRoomGetMyTrophyList(const std::vector < int > & trophyList);

	/// 나의 트로피 리스트를 받는데 실패했다.
	virtual void onRecvMyRoomGetMyTrophyListFailed();

#ifdef _SELECTIVE_PACKAGE_
	///< 선택의 상자 사용하는데 성공했다.
	void onRecvOpenSelectivePackageOK( int usedItemNum, const std::vector<RewardInfo> & rewardLis);

	///< 선택의 상자 사용하는데 실패했다.
	void onRecvOpenSelectivePackageFailed(const eShopFailed_REASON failedReason, int requsetUseItemNum, eServerResult eResult);
#endif
	/// 복주머니를 사용하는데 성공했다.
	virtual void onRecvMyRoomUseLuckyBagOK( int usedItemNum, const std::map<int, BYTE/*count*/> & resultLottoItems, BYTE iCount);

	/// 복주머니를 사용하는데 실패했다.
	virtual void onRecvMyRoomUseLuckyBagFailed(int requsetUseItemNum, eServerResult eResult);

	/// 뽑기판의 정보를 가져오기 성공했다.
	virtual void onRecvMyRoomGetLotteryStageInfoOK(const int lotteryNum, const std::vector <LotteryStateInfo> & myLotteryStageInfo);

	/// 뽑기판의 정보를 가져오기 실패했다.
	virtual void onRecvMyRoomGetLotteryStageInfoFailed(const int lotteryNum, eServerResult eResult);

	/// 뽑기 아이템을 사용하는데 성공했다.
	virtual void onRecvMyRoomUseLotteryOk(const int lotteryNum, eLotteryRewardType eRewardType, const int rewardValue);

	/// 뽑기 아이템을 사용하는데 실패했다.
	virtual void onRecvMyRoomUseLotteryFailed(const int lotteryNum, eServerResult eResult);



	/// 마이룸에서 쓰이는 응답들 끝
	//////////////////////////////////////////////////////////////////////////

	/// 팜의 기본 정보를 받았다. 
	virtual void onRecvEnterFarmInfo(const FarmInfo& info, const FarmChattingInfo& farmChattingInfo);

	/// 방에 입장했다.
	virtual void onRecvEnterRoom(const EnterRoomInfo & info, const std::vector<RecvFarmMapObjectInfo>& farmMapObjectInfoList, const std::vector<RecvFarmMapVoxelsInfo>& vecVoxels);

	/// 새로운 클라이언트가 방에 들어왔다.
	virtual void addNewClient(int iPlayerIndex,const bool bReady,const BYTE followIndex,const int iState,const bool bIsNewEnterUser,const CNetPlayer * netPlayer);
	// 나의 playerindex 를 받았다.
	virtual void onRecvMyPlayerIndex(int iPlayerIndex);

	/// 새로운 방장이다.
	virtual void onRecvSetMaster(unsigned int iPlayerIndex);

	/// 현재 방의 모든 유저들에게 보내는 메시지를 받았다.
	virtual void onRecvForwardToAllRoomUser(const CPacketChunk & v);

	/// 현재 방의 우리 팀에게 보내는 메시지를 받았다.
	virtual void onRecvForwardToMyTeamUser(const CPacketChunk & v);

	/// 현재 방의 특정 유저가 나에게 보내는 메시지를 받았다.
	virtual void onRecvForwardToRoomUser(const size_t from,const CPacketChunk & data);

	/// 채팅 메시지를 받았다.
	virtual void onRecvChattingMsg(unsigned int nPlayerIndex, const char* data, size_t len);

	/// 특정 캐릭터의 위치를 받았다.
	virtual void onRecvClientCharacterPosition(const BYTE numGameIndex, const ClientCharacterPosition & pos, const CPacketChunk & binData);

	/// on receive new follow index. if index indicate self, no follow move
	virtual void onRecvUpdateFollowIndex(const BYTE from, const BYTE to);

	/// 캐릭터가 바뀌었다.
	virtual void onRecvChangeAvatar(unsigned int numPlayerIndex, const AdvancedAvatarInfo & advancedAvatarInfo);

	/// 특정 유저의 복장정보가 갱신되었다.(현제 게임룸에서만 호출됨.
	virtual void onRecvUpdateAvatar(unsigned int numPlayerIndex, const AdvancedAvatarInfo & advancedAvatarInfo);

	/// 특정 유저의 OnOff아이템 정보가 갱신되었다(현재 게임룸에서만 호출됨).
	virtual void onRecvUpdateOnOffItem(unsigned int numGameIndex,const int iItemDescNum,const bool bOnOff);

	/// 특정 유저의 탑승 동물 정보가 바뀌었다.
	virtual void onRecvChangeAnimalAvatar(unsigned int numPlayerIndex, const AnimalRacingAnimalAvatar & avatarInfo);

	/// 특정 유저의 탑승 동물 정보가 바뀌었다.
	virtual void onRecvUpdateAnimalAvatar(unsigned int numPlayerIndex, const AnimalRacingAnimalAvatar & avatarInfo);

	/// 방에서 특정 유저가 오브젝트에 어떠한 행위를 했다.
	virtual void onRecvNotifyUserAction(BYTE byGameIndex, BYTE byAction, __int64 iOID);

	/// 레디 상태를 받았다.
	virtual void onRecvReadyStatus(unsigned int nPlayerIndex, bool bReady);

	/// 맵이 변경되었다.
	virtual void onRecvMapChanged(const int numMap);

	/// 팀이 변경되었다.
	virtual void onRecvRoomPlayerSelectTeam(BYTE byGameIndex, eTeam byTeamColor);

	/// 이미 레디 중이어서 팀 선택을 실패했다.
	virtual void onRecvRoomPlayerSelectTeamFailedAlreadyReady();

	/// 이어달리기에서 팀의 위치가 변경되었다.
	virtual void onRecvRoomPlayerSelectRelayTeam(BYTE byGameIndex, eRelayTeamPosition byRelayTeamColor, eTeam eTeamColor);

	/// 이어달리기에서 슬롯 상태가 변경되었다.
	virtual void onRecvChangeSlotStateRelayTeam(eRelayTeam relayTeam, bool bClose);

	/// 이어달리기에서 슬롯 상태가 변경되었다.
	virtual void onRecvChangeSlotStateQuizTeam(eRelayTeamPosition relayTeam, bool bClose);

	/// 이어달리기에서 슬롯 상태를 변경하는데 실패했다.
	virtual void onRecvChangeSlotStateRelayTeamFailed();

	/// 이어달리기에서 다음 주자를 준비한다.
	virtual void onRecvRelayPrepareNextRunner(BYTE numGameIndex);

	/// 이어달리기에서 바톤 터치 구간에 들어왔다.
	virtual void onRecvEnterBatonTouchArea(BYTE numGameIndex);

	/// 이어달리기에서 바톤 터치 구간을 통과했다.
	virtual void onRecvLeaveBatonTouchArea(BYTE numGameIndex);

	/// 이어달리기에서 바톤 터치 결과가 왔다.
	virtual void onRecvBatonInput(BYTE numGameIndex, eBatonInput batonInput, int iParam);

	/// (방 안에서)길드 이름이 업데이트되었다.
	virtual void onRecvUpdateGuildInfo(BYTE numGameIndex, const std::string & strGuildName, int iGuildNum, eGuildMemberGrade eGrade, eGuildKind guildKind, const short guildLevel);

	/// (방 안에서)커플 정보가 업데이트되었다.
	virtual void onRecvUpdateCoupleInfo(BYTE numGameIndex, const CoupleInfo & coupleInfo);

	/// 이혼소송 정보를 초기화 하는데 실패했다.
	virtual void onRecvWeddingInitDivorceRequestInfoFailed();

	/// 이혼소송 요청에 대한 결과가 왔다.
	virtual void onRecvWeddingSuitForDivorceResult(const eServerResult eResult, const std::string & strMateNickname, eWeddingDivorceType eDivorceType);

	/// 이혼소송 요청에 대한 실패 결과가 왔다.
	virtual void onRecvWeddingSuitForDivorceResultFailed();

	/// 이혼 요청에 대한 결과가 왔다.
	virtual void onRecvWeddingDivorceResult(const std::string & strMateNickname, eWeddingDivorceType eDivorceType, bool bEnforce);

	/// 이혼 요청이 대한 실패했다.
	virtual void onRecvWeddingDivorceResultFailed();

	/// 선물 교환권의 보상 내용을 받았다.
	virtual void onRecvGiftCouponRewardListInfo(int iCouponItemNum, std::map<eRewardCondition, std::vector<int> > & mapRewardInfoList);

	/// 선물 교환권의 보상 내용을 받는데 실패했다.
	virtual void onRecvGiftCouponRewardListInfoFailed();

	/// 선물 교환권 사용에 대한 결과가 왔다.
	virtual void onRecvGiftCouponReward(int iCouponItemNum, eRewardCondition eRewardType, int iReward);

	/// 선물 교환권 사용을 실패했다.
	virtual void onRecvGiftCouponRewardFailed();

	/// 카드 선물 전송에 대한 처리결과가 왔다.
	virtual void onRecvGiftCardSendResult(const eServerResult eResult, const std::string strRecvNickname);

	/// 넷이서 한마음에서 키를 밟은 정보가 왔다.
	virtual void onRecvKeyInDoor(const OneInFour_KeyInDoor & info);

	/// 슬롯 상태가 변경되었다.
	virtual void onRecvRoomSlotChangeState(BYTE slotNum, bool bClosed);

	/// 방 제목이 바뀌었다.
	virtual void onRecvRoomTitleChange(const std::string & strTitle);

	/// 방 암호가 바뀌었다.
	virtual void onRecvRoomPasswordChange(const std::string & strPassword);

	/// 방의 경쟁 모드가 바뀌었다.
	virtual void onRecvRoomSteppingModeChange(const bool bSteppingMode);

	/// 방의 아이템 모드가 바뀌었다.
	virtual void onRecvRoomItemModeChange(const eItemMode itemMode);

	/// 방의 옵션(방제,패스워드,경쟁모드,아이템모드,스피드퀴즈모드)이 바뀌었다.
	virtual void onRecvModifyRoomOption(const std::string strRoomTitle, const std::string strRoomPassword, 
										const bool bSteppingMode, const eItemMode itemMode
										);

	/// 강퇴되었다.
	virtual void onRecvRoomKicked(const BYTE numGameIndex);

	/// 강퇴 경고 정보를 받았다.
	virtual void onRecvRoomKickOutWarning(const KickOutWarning& beforeKickOutWarning, const KickOutWarning& kickOutWarning, bool bShowMessage);
	virtual void onRecvRoomKickOutWarningFailed();

	/// 커플 경험치 추가 아이템을 사용했다.
	virtual void onRecvMyRoomUseCoupleExpAdd(int iItemNum, bool bSelf);
	virtual void onRecvMyRoomUseCoupleExpAddFailed(eServerResult result);

	///마이룸 슬롯
	//마이룸 슬롯 : 저장을 실패함 
	void onRecvMyRoomSetSlotSettingFailed(eServerResult result);
	//마이룸 슬롯: 슬롯의 이름정보를 불러오는데 실패함
	void onRecvMyRoomGetUserSlotInfoFailed();
	//마이룸 슬롯: 슬롯 아이템 세팅을 성공함
	void onRecvMyRoomSetSlotItemSetting(int slotNum, AvatarInfo avatarInfo, std::string slotName);
	//마이룸 슬롯: 슬롯 아이템 정보를 불러옴
	void onRecvMyRoomGetUserSlotInfo(std::vector<MyRoomSlotInfo> vecSlotInfo);
	//마이룸 슬롯 :마이룸 슬롯을 구매하는데 성공함
	void onRecvMyRoomPayMyRoomSlotResultOK(int iMySlot);
	//마이룸 슬롯 :마이룸 슬롯을 구매하는데 실패함
	void onRecvMyRoomPayMyRoomSlotResultFailed(const eMyRoomProtocol_PAY_MYROOM_SLOT_RESULT_FAILED_REASON& failedreson);

	virtual void onRecvMyRoomFavoriteList(USER::eFavorite_LIST_RESULT result, const std::vector<int>& favorites);
	virtual void onRecvMyRoomFavoriteAddListAck(USER::eFavorite_ADD_RESULT result, int item);
	virtual void onRecvMyRoomFavoriteRemoveListAck(USER::eFavorite_REMOVE_RESULT result, int item);

	/// 올림픽 방에서 경기일정 종료로 인해 퇴장당했다.
	virtual void onRecvOlympicRoomKicked();

	/// 게임 시작 카운팅을 해도 된다.
	virtual void onRecvStartCounting();

	/// 게임 시작 카운팅을 할 수 없는 상태이다.
	virtual void onRecvNotStartCounting(CStartCountFail::STATUS status);

	/// 게임 시작 카운팅 중 취소되었다는 메시지...
	virtual void onRecvStartCountingCancel();

	/// 로딩을 시작하자는 메시지를 받았다.
	virtual void onRecvStartLoading(const int numMap, const int iRandomSeed);

	/// 로딩 시작이 실패했다는 메시지를 받았다.
	virtual void onRecvStartLoadingFail(eStartLoadingFail failNum);

	/// Mesh 로딩이 끝났다는 메시지를 받았다.
	virtual void onRecvEndMeshLoading(int iPlayerIndex);

	/// 모든 이들의 Mesh 로딩이 끝났다고 받았다.
	virtual void onRecvAllUserEndMeshLoading();

	/// 로딩이 끝났다는 메시지를 받았다.
	virtual void onRecvEndLoading(int iPlayerIndex);

	/// 모든 이들의 로딩이 끝났다고 받았다.
	virtual void onRecvAllUserEndLoading();

	/// 실제 게임을 시작하라는 메시지를 받았다.
	virtual void onRecvStartGame(int iGameStartTick, int iNumberOfItem);

	/// 내가 보너스 EX를 먹었다
	virtual void onRecvBonusExEat(const int eatBonusIndex, std::vector<RewardInfo>& rewardList);

	/// 게임 중 data 를 받았다.
	virtual void onRecvData(int iPlayerIndex, const CPacketChunk & data);

	/// 게임 중 event 를 받았다.
	virtual void onRecvDataWithConfirm(int iPlayerIndex, int iEventType, const CPacketChunk & data);

	/// 게임의 tick 을 받는다.
	virtual int getTick() const;

	/// 방장으로부터의 tick 을 받았다.
	/// iGameTick 은 방장이 메시지를 보낼 때의 tick
	/// dwPingLoopTime 은 방장이 나와의 ping 을 보낸 후 받기까지의 시간. 즉 /2 를 하면 오는데 걸린 시간이다.
	virtual void onRecvMasterTick(int iGameTick, DWORD dwPingLoopTime);

	/// 이번 판의 Random seed 를 받는다.
	virtual void setRandomSeed(int);

	/// 누군가 아이템을 먹었다.
	virtual void onRecvEatItem(int iPlayerIndex, int iItemID, int iGameTick, int iItemKind, const int iMadeNextItemID, bool bMakeAndEat, int eatParam);

	/// 아이템 먹기를 실패했다.
	virtual void onRecvEatItemFailed(int iPlayerIndex, int iItemID, int iGameTick, int iMadeNextItemID, int iHaveItemID, int iHaveItemKind);

	/// 누군가 맵에서 생성된 아이템을 먹었다.
	virtual void onRecvEatItemForRoomGenerate(int iPlayerIndex, const std::vector<MapEatItemInfo>& eat_item_list);

	/// 누군가 맵에서 생성된 아이템을 떨어뜨렸다.
	virtual void onRecvDropItemForRoomGenerate(const std::vector<MapDropedItemInfo>& dropItemList, BYTE byUserIndex, int iSeed);

	/// 쿨타임 문제로 make&eat를 실패했다. LeftCoolTime = 서버가 패킷 전송시에 남은 쿨타임 시간. msec
	virtual void onRecvMakeEatItemCoolTimeFailed(int iItemKind, eRequestItem requestItemData, eGameItemMakeAndEat_Method gameItemMakeAndEat_Method, int argument, int leftCoolTime);

	/// 드랍된 아이템 삭제한다. (맵 생성 아이템)
	virtual void onRecvDeleteDropedItemForRoomGenerate(const std::vector<int>& itemIDList, BYTE byUserIndex);

	/// 유저가 소유한 아이템 삭제한다. (맵 생성 아이템)
	virtual void onRecvDeleteEquipedItemForRoomGenerate(const std::vector<int>& itemIDList, BYTE byUserIndex);

	/// 유저의 아이템 획득/삭제에 따라 점수가 변동되었다.(맵 성성 아이템)
	virtual void onRecvPointNotifyForRoomGenerate(int user_index, const std::vector<int>& user_delta, const std::vector<int>& team_delta, const std::map<int/*user index*/, int/*point*/>& user_points, const std::map<eTeam, int>& team_points);

	/// 누군가 유니크 아이템을 먹었다.
	virtual void onRecvGetUniqueItem(BYTE byPlayerIndex, int iItemID, int iGameTick, const int iMadeNextItemID);

	/// 누군가 보스 공격 아이템을 먹었다.
	virtual void onRecvGetBossAttackItem(BYTE byPlayerIndex, int iItemID, int iGameTick, const int iMadeNextItemID);

	/// 누군가 오브젝트 리소스 아이템을 먹었다.
	virtual void onRecvGetObjectResourceItem(BYTE byPlayerIndex, int iItemID, int iGameTick, const int iMadeNextItemID);

	/// 누군가 아이템을 사용했다.
	virtual void onRecvUseItem(int iPlayerIndex, int iItemKind, int iGameTick, const CPacketChunk & useInfo);

	/// 아이템을 사용하는데 실패하였다.
	virtual void onRecvUseItemFailed();

	/// 아이템을 지우는 처리를 한다.
	virtual void onRecvRemoveItem( int iPlayerIndex, bool isSuccess = true);

	/// 스패셜 어시스트 아이템을 받았다.
	virtual void onRecvSpecialAssistItem(const std::vector < int > & assistItems);

	/// 어시스트 아이템을 사용했다.
	virtual void onRecvUseAssistItem(int iPlayerIndex, int iItemID);

	/// 어시스트 아이템을 사용하는데 실패하였다.
	virtual void onRecvUseAssistItemFailed(int iPlayerIndex, int iItemID);

	/// 누군가 아이템을 만들라고 했다.
	virtual void onRecvMakeItem(int iCanEatTick, int iItemKind, int iItemID, const CPacketChunk & data);

	/// 아이템을 다시 만들어라.
	virtual void onRecvRegenItem(GAME_ITEM iItemKind);

	/// 누군가 맵에서 생성되는 아이템을 만들라고 했다.
	virtual void onRecvMakeItemForMapGenerate(int iCanEatGameTick, eMapGenerateItemType itemType, int iMadeNewItemID, const CPacketChunk & Data);

	/// 누군가 생일 축하 모자 아이템을 밟았다. 앞의 인자가 밟힌 유저 인덱스, 뒤가 밟은 유저 인덱스
	virtual void onRecvStepBirthdayCap(const BYTE numSteppedUserGameIndex, const BYTE numStepUserGameIndex);

	/// 발판을 만든다.
	virtual void onRecvMakeFootBoard(const int iNumberOfFootBoard );

	/// 발판을 밟았을때 처리를 한다.
	virtual void onRecvStepFootBoard(const int iFootBoardIndex, const BYTE numPlayerIndex );

	/// 발판 지역(?) 을 통과 후 처리를 한다.
	virtual void onRecvPassFootBoardArea();

	/// 어뷰징 유저가 아니다..
	virtual void onRecvAbusingUserListInfo(std::map<BYTE, AbusingInfo> & abusingInfoList);

	/// 누군가 서바이벌 맵(보스맵포함)에서 GameOver 했다.
	virtual void onRecvGameOver(BYTE byPlayerIndex, eGameUserEventTypeResponse response);

	/// 누군가 서바이벌 맵에서 혼자 살아남았다.
	virtual void onRecvGameOverSurvive(std::vector<BYTE>& goalinList);

#ifdef _RANDOM_GAMEOVER

	/// 탈락 서바이벌 모드에서 체크 포인트를 통과했다.
	virtual void onRecvServivalRandomGameoverCheckPoint(const BYTE channelCheckPoint, const BYTE byGameIndex, const std::vector<BYTE> & gameoverRankList);

	/// 탈락 서바이벌 모드에서 체크 포인트 거리를 받았다.
	virtual void onRecvServivalRandomGameoverRaceLengthOK(const BYTE channelCheckPoint);
	virtual void onRecvServivalRandomGameoverRaceLengthFailed(const BYTE channelCheckPoint);

	/// 탈락 서바이벌 모드에서 탈락유저에게 알려준다
	virtual void onRecvServivalRandomGameoverNotify(const BYTE channelCheckPoint, const bool isGameOver);

#endif

	/// 서바이벌 암산왕 맵에서 특정 체크 포인트를 통과했다.
	virtual void onRecvPassSuvivalArithmeticCheckPoint(const DWORD dwLapTime, const int iTimeLimit, const int dwBonusTime, const bool bShow);

	/// 서바이벌 암산왕에서 이 유저가 최초로 골 발판을 밟았다.
	virtual void onRecvPassSteppedGoalBoard(BYTE byGameIndex, const int iRank);	

	/// 달리기 퀴즈모드(세계왕) 퀴즈 리스트를 받아왔다.
	virtual void onRecvRunQuizModeGetQuizList(RunQuizModeSelectData& runQuizInfo);

	/// 달리기 퀴즈모드(세계왕) 퀴즈 리스트를 받기 실패 이유.
	virtual void onRecvRunQuizModeGetQuizListFailed( eRunQuizModeResult reason );

	/// 1등 유저가 골인 발판을 밟아서 타임아웃 카운트 정보가 왔다.(아직 골인은 아님, 1등 유저를 지외한 인원들에게만 뿌려짐.)
	virtual void onRecvTimeOutCount(const DWORD dwLapTime, const int iTimeLimit);

	/// 누군가 골인했다.
	virtual void onRecvGoalInData(BYTE numPlayerIndex, DWORD dwLapTime, eGoalin flag);

	/// 혼인서약 단계로 넘어간다.
	virtual void onRecvWeddingChangeAgreeState(eServerResult eResult);

	/// 혼인 서약에 동의 했다.
	virtual void onRecvWeddingAgree(eServerResult eResult);

	/// 결혼을 하여 부부의 관계가 되었다.
	virtual void onRecvWeddingCreateCouple(eServerResult eResult, __int64 iCeremonyOfficerID);

	/// 게임 시각이 dwGametime 때부터 타임 몬스터 카운터를 시작해라.
	virtual void onRecvStartTimeOutCount(DWORD dwGametime, BYTE nTimeOutSeconds);

	/// 게임 결과 보상 아이템 목록을 받았다.
	virtual void onRecvGameResultRewardInfo(std::vector<GameResultReward>& resultRewardList);

	/// 게임 결과를 받았다.
	virtual void onRecvGameResult(const GameResult& gameResult);

	/// 게임 결과를 받았다.
	virtual void onRecvGameResultItemEvent(std::vector<GameResultReward>& itemList);

	/// 내가 레벨업을 했다.
	virtual void onRecvLevelUpMe(eLevelUPKind levelKind, int iLevel);

	/// 같은 방의 특정 유저가 레벨업을 했다.
	virtual void onRecvLevelUp(eLevelUPKind levelKind, BYTE byGameIndex, exp_type exp);

	/// 게임방에서 다른 사람이 나갔다.
	virtual void onRecvOtherPlayerOut(size_t iPlayerIndex);

	/// 게임방에서 자신이 나갔다.
	virtual void onRecvThisPlayerOut(size_t iPlayerIndex);

	/// 게임 시상 화면을 끝내고 게임룸으로 돌아가라.
	virtual void onRecvMoveToGameRoom();

	///< 대운동회 카운팅을 멈춰라.
	virtual void onRecvCancelSportsCount();

	///< 대운동회 카운팅을 시작해라.
	virtual void onRecvStartSportsCount(const time_type tRemainTime);

	/// 네트웍이 끊어졌다.... network error
	virtual void onDisconnectedFromServer();

	/// 메시지 박스를 보여주라고 받았다.
	virtual void onRecvShowMsg(const std::string & strMsg);

	/// 자동사용되는 아이템 정보를 받았다.
	virtual void onRecvAutoUseItemInfo(const std::map<int,int>& useInfo );

	/// 이 유저의 아이템이 시간이 지났다.
	virtual void onRecvRoomUserFuncItemTimeOut(const BYTE numGameIndex, int iItemNum);
	virtual void onRecvRoomUserFuncItemTimeOut(const BYTE numGameIndex, const CActiveItems activeItems);

	/// 이 유저의 버프가 다 되었다.
	virtual void onRecvRoomUserBuffItemTimeOut(const BYTE numGameIndex, int iItemNum);

	/// 서버와의 접속이 끊어졌다.
	virtual void onRecvDisconnectFromServer(eServerResult eResult);

	/// 이 유저의 피로도 시간은 받는다.
	virtual void onRecvFatigue(const int iFatigueMinute);

	// 서버로 부터 유효한 길드 이름인지 체크 결과를 받았다. bVaildGuildName == true 이면 유효한 길드 이름
	virtual void onRecvGuildCheckValidGuildNameResult(eGuildNameCheckResult byCheckResult);

	// 서버로 부터 길드를 만드는데 성공했다는 결과를 받았다.
	virtual void onRecvGuildMakeGuildSuccess();

	// 서버로 부터 길드를 만드는데 실패했다는 결과를 받았다.
	virtual void onRecvGuildMakeGuildFailed(eGuildMakeFailedReason byFailedReason);

	/// 길드 해체 요청을 처리했다.
	virtual void onRecvGuildDeleteGuild();
	virtual void onRecvGuildDeleteGuildFailed(eGuildFailReason eReason);

	/// 길드 리스트를 받았다.
	virtual void onRecvGuildGetGuildList(const std::vector<GuildInfo>& guildList, int totalGuildListCount, const GuildSearchArg& arg);
	virtual void onRecvGuildGetGuildListFailed();

	/// 길드 가입 대기자 리스트를 받았다.
	virtual void onRecvGuildGetJoinWaitMemberList(const std::vector<GuildWaiterInfo>& guildWaiterList);
	virtual void onRecvGuildGetJoinWaitMemberListFailed();

	/// 길드 가입 요청의 결과를 받았다.
	virtual void onRecvGuildJoinRequest(eGuildJoinMethod eMethod, const std::string& strGuildName);
	virtual void onRecvGuildJoinRequestFailed(eGuildFailReason eReason, int iLimmitCount);

	/// 길드 가입 신청 취소 결과를 받았다.
	virtual void onRecvGuildCancelPropose(const std::string& strGuildName);
	virtual void onRecvGuildCancelProposeFailed(eGuildFailReason eReason);

	/// 길드 길드 관련 알람 메시지를 받았다.
	virtual void onRecvGuildNotify(const UserAlarmInfo& guildNotice);

	/// 길드 가입 요청의 수락/거절 처리를 했다.
	virtual void onRecvGuildProcessJoinRequest(const std::string& strNickName, bool bAccept);
	virtual void onRecvGuildProcessJoinRequestFailed(eGuildFailReason eReason);

	/// 길드에서 떠나기 요청을 처리했습니다.(자탈/추방)
	virtual void onRecvGuildProcessLeave(const std::string& strMemberNickName, bool bBySelf, const int guildLevel);
	virtual void onRecvGuildProcessLeaveFailed(eGuildFailReason eReason);

	// 길드 가입 가능 레벨 설정 요청을 처리했습니다.
	virtual void onRecvGuildModifyJoinLimmitLevel(short iLevel);
	virtual void onRecvGuildModifyJoinLimmitLevelFailed(eGuildFailReason eReason);

	// 길드 가입 절차 설정 요청을 처리했습니다.
	virtual void onRecvGuildModifyJoinMethod(eGuildJoinMethod eMethod);
	virtual void onRecvGuildModifyJoinMethodFailed(eGuildFailReason eReason);

	// 길드 마크 설정 요청을 처리했습니다.
	virtual void onRecvGuildModifyMark(int iMark);
	virtual void onRecvGuildModifyMarkFailed(eGuildFailReason eReason);

	// 길드원의 등급 변경 요청을 처리했습니다.
	virtual void onRecvGuildModifyMemberGrade(const std::string& strMemberNickName, eGuildMemberGrade eGrade);
	virtual void onRecvGuildModifyMemberGradeFailed(eGuildFailReason eReason);

	// 길드의 메시지 변경 요청을 처리했습니다.
	virtual void onRecvGuildModifyMessage(const std::string& strMessage);
	virtual void onRecvGuildModifyMessageFailed(eGuildFailReason eReason);

	// 길드의 이름 변경 요청을 처리했습니다.
	virtual void onRecvGuildModifyName(const std::string& strBeforeName, const std::string& strName, int iItemNum, int iRemainItemCount);
	virtual void onRecvGuildModifyNameFailed(const std::string& strName, int iItemNum, eGuildFailReason eReason);

	// 길드 레벨업 요청을 처리했습니다.
	virtual void onRecvGuildLevelUp(short iLevel);
	virtual void onRecvGuildLevelUpFailed(eGuildFailReason eReason);

	// 길드 정보 요청을 처리했습니다.
	virtual void onRecvGuildGetGuildInfo(const GuildDetailInfo & info);
	virtual void onRecvGuildGetGuildInfoFailed(eGuildFailReason eReason);

	// 길드 마스터 권한 이양을 처리했습니다.
	virtual void onRecvGuildConveyanceMaster(const std::string& strNewMasterNickName, int iItemNum, int iRemainCount);
	virtual void onRecvGuildConveyanceMasterCandidates(std::vector<std::string> vecCandidate);
	virtual void onRecvGuildConveyanceMasterFailed(eGuildFailReason eReason);

	// 길드 포인트 추가 아이템을 사용했습니다.
	virtual void onRecvGuildIncreaseGuildPoint(int iItemNum, int iRemainCount);
	virtual void onRecvGuildIncreaseGuildPointFailed(eGuildFailReason eReason);

	// 내가 가입 신청한 길드 리스트를 받았다.
	virtual void onRecvGuildProposeListNotify();

	// 길드 공헌포인트 요청을 처리했습니다.
	virtual void onRecvGuildGetMyContributionPoint(const int iContributionPoint);
	virtual void onRecvGuildGetMyContributionPointFailed(eGuildFailReason eReason);

	// 길드 포인트 요청을 처리했습니다.
	virtual void onRecvGuildGetGuildPoint(const __int64 iGuildPoint);
	virtual void onRecvGuildGetGuildPointFailed(eGuildFailReason eReason);

	// 길드 마스터의 선물 아이템을 사용에 대한 결과를 받았다.
	virtual void onRecvGuildUseGiftBox(int iReceivedItemNum, int iGiftBoxItemNum, int iReaminItemCount);
	virtual void onRecvGuildUseGiftBoxFailed(eGuildFailReason eReason);

	// 시스템 길드 졸업을 했다
	virtual void onRecvGuildGraduationOK();
	virtual void onRecvGuildGraduationFailed();

	// 스킬 습득 요청에 관한 결과를 받았다.
	virtual void onRecvGuildSkillAdd( GuildDetailInfo& guildInfo, std::map<int, int> &mapItemList );
	virtual void onRecvGuildSkillAddFailed( eGuildSkillCheckAvailabilityType result );

	virtual void onRecvGuildSkillReset( GuildDetailInfo& guildInfo );
	virtual void onRecvGuildSkillResetFailed( eGuildSkillCheckAvailabilityType result );

	/// 길드 공방 관련 알람 메시지를 받았다.
	virtual void onRecvGuildPlantNotify(const UserAlarmInfo& guildNotice);

	//!< 길드 운영 TR  요청 정보를 받았다.
	virtual void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR);
	virtual void onRecvGuildPlantGetGuildManagerTRFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드 운영 TR 를 투자에 성공했다.
	virtual void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR);
	//!< 길드 운영 TR 를 투자에 실패하였다.
	virtual void onRecvGuildPlantInvestGuildManagerTRFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드 운영 TR 창고 확장 정보를 요청 성공했다.
	virtual void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue);
	//!< 길드 운영 TR 창고 확장 정보를 요청 실패하였다.
	virtual void onRecvGuildPlantGetStorageExtendFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드공방 아이템 제작 등록을 성공했다.
	virtual void onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR);
	//!< 길드공방 아이템 제작 등록을 실패하였다.
	virtual void onRecvGuildPlantRegisterItemFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드공방 제작 진행 아이템 정보를 요청 성공했다
	virtual void onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind);
	//!< 길드공방 제작 진행 아이템 정보를 요청 실패하였다.
	virtual void onRecvGuildPlantGetMakeProgressItemFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드공방 제작 대기 아이템 리스트를 요청 성공했다
	virtual void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant);
	//!< 길드공방 제작 대기 아이템 리스트를 요청 실패하였다.
	virtual void onRecvGuildPlantGetMakeStandByItemFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드공방 제작 기여 아이템을 변경 성공했다.
	virtual void onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum);
	//!< 길드공방 제작 기여 아이템을 변경 실패하였다.
	virtual void onRecvGuildPlantChangeMyConstributionPointItemFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드 운영 TR 투자자 리스트를 요청 성공했다
	virtual void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList);
	//!< 길드 운영 TR 투자자 리스트를 요청 실패하였다.
	virtual void onRecvGuildPlantGetInvestorManagerTRFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드 재화 지출 리스트를 요청 성공했다
	virtual void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList);
	//!< 길드 재화 지출 리스트를 요청  실패하였다.
	virtual void onRecvGuildPlantGetExpenseListFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드공방 아이템 기여도 순위 리스트를 요청 성공했다
	virtual void onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList);
	//!< 길드공방 아이템 기여도 순위 리스트를 요청 실패하였다.
	virtual void onRecvGuildPlantGetItemContributeRankLIstFailed(eGuildPlantFailReason iFailedReason);

	//!< 아이템 지급 가능 길드원 리스트를 요청 성공했다.
	virtual void onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList);
	//!< 아이템 지급 가능 길드원 리스트를 요청 실패하였다.
	virtual void onRecvGuildPlantGetGivePossibleUserListFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드공방 아이템 지급를 요청 성공했다.
	virtual void onRecvGuildPlantGiveGiftOK(int iItemIndexNum);
	//!< 길드공방 아이템 지급를 요청 실패하였다.
	virtual void onRecvGuildPlantGiveGiftFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드공방 아이템 리스트를 요청 성공했다
	virtual void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList);
	//!< 길드공방 아이템 리스트를 요청 실패하였다.
	virtual void onRecvGuildPlantGetPlantItemListFailed(eGuildPlantFailReason iFailedReason);

	//!< 길드공방 아이템 구매를 요청 성공했다
	virtual void onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount);
	//!< 길드공방 아이템 구매를 요청 실패하였다.
	virtual void onRecvGuildPlantBuyItemFailed(eGuildPlantFailReason iFailedReason);

	/// 핫타임 이벤트 정보를 받았다.
	virtual void onRecvHotTimeEventInfoAck(const std::map<__int64, HotTimeEventInfo> & hotTimeEventInfo);

	/// 유저가 핫타임 정보를 받았다.
	virtual void onRecvHotTimeEventSettingAck(const bool bUpdateSetting, const HotTimeEventInfo & hotTimeEventInfo);

	/// 핫타임 이벤트 정보 설정이 실패하였다
	virtual void onRecvHotTimeEventSettingFaildAck(eHotTimeEventFailedReason failReason);

	/// 핫타임 이벤트 정보를 삭제했다.
	virtual void onRecvHotTimeEventDeleteAck(const __int64 iHotTimeEventID);

	/// 유저가 핫타임 이벤트 응모에 성공했다.
	virtual void onRecveHotTimeEventApplyAck(const __int64 iHotTimeEventID);

	/// 유저가 핫타임 이벤트 응모에 실패했다.
	virtual void onRecveHotTimeEventApplyFaildAck(const eHottimApplyFailedReason hotTimeResult, const __int64 iHotTimeEventID);

	/// 튜토리얼 코드 (Agent 서버에 데이터를 DB에 저장하도록 요청에 대한 성공 결과를 받았다.)
	virtual void onRecvTutorialInsertMyData(std::string strValue, int iValue);

	/// 튜토리얼 코드 (Agent 서버에 데이터를 DB에 저장하도록 요청에 대한 실패 결과를 받았다.)
	virtual void onRecvTutorialInsertMyDataFailed(eServerResult eResult);

	/// 튜토리얼 코드 (Room 서버에 데이터를 DB에 갱신에 대한 성공 결과를 받았다.)
	virtual void onRecvTutorialUpdateMyDataFailed(std::string strValue, int iValue);

	/// 튜토리얼 코드 (Room 서버에 데이터를 DB에 갱신에 대한 실패 결과를 받았다.)
	virtual void onRecvTutorialUpdateMyDataFailed(eServerResult eResult);

	////////////////////////////////////////////////////////////////////////////////
	/// 길드전 관련

	/// 길드전에 대한 길드의 정보를 받음
	virtual void onRecvGuildMatchGetGuildInfo( const eOCCUPATION_AREA_TYPE eOccupationAreaType, std::vector<GuildMatchRankInfo> rankInfo);

	/// 길드전에 대한 길드 정보 받기 실패
	virtual void onRecvGuildMatchGetGuildInfoFailed(eGuildMatchType matchType, eGuildMatchFailedReason failedReason);

	/// 길드전 최근 전적에 대한 정보를 받음
	virtual void onRecvGuildMatchGetLatestInfo(eGuildMatchType matchType, std::vector<GuildMatchLatest> matchLatest);

	/// 길드전 최근 전적에 대한 정보 받기 실패
	virtual void onRecvGuildMatchGetLatestInfoFailed(eGuildMatchType matchType, eGuildMatchFailedReason failedReason);

	/// 길드전 랭킹 정보를 받음
	virtual void onRecvGuildMatchRankInfo(eServerResult result, eGuildMatchFailedReason failedReason, eRequestRankKind rankKind, std::vector<GuildMatchRankInfo>& rankList);

	/// 길드전 나의 길드의 랭킹 정보를 받음
	virtual void onRecvGuildMatchMyGuildRankInfo(eRequestRankKind rankKind, GuildMatchRankInfo rankInfo);

	/// 길드전 랭킹 정보 받기를 실패했음
	virtual void onRecvGuildMatchMyGuildRankInfoFailed(eRequestRankKind rankKind, eGuildMatchFailedReason failedReason);

	/// 다음 공식 길드전 공지 정보를 받았다..
	virtual void onRecvGuildMatchNoticeNextOfficialGameInfo(OlympicGameInfo& gameInfo);

	/// 다음 공식 길드전 게임 정보를 받았다..
	virtual void onRecvGuildMatchNextOfficialGameInfo(OlympicGameInfo& gameInfo);

	/// 공식 길드전 일정이 없다
	virtual void onRecvGuildMatchOfficialEmpty();

	/// 길드 검색을 완료하였다
	virtual void onRecvGuildMatchSearchGuildPartyOK();

	/// 길드전 매치 동작을 성공하였다
	virtual void onRecvGuildMatchActionOK(eGuildMatchAction action);

	/// 길드전 매치 동작을 실패하였다
	virtual void onRecvGuildMatchActionFailed(eGuildMatchAction action, eGuildMatchFailedReason failedReason);

	/// 길드전 등록을 성공
	virtual void onRecvGuildMatchRegistMatchOK(eGuildMatchType matchType, const bool bAllReady);

	/// 길드전 매칭 동작에 대한 통지
	virtual void onRecvGuildMatchActionNotify(eGuildMatchAction action, GuildMatchPartyInfo& partyInfo, bool bRequestParty, eRoomKind roomKind);

	/// 나의 파티 정보 받기를 성공
	virtual void onRecvGuildMatchMyPartyInfoOK(const bool success, GuildMatchPartyInfo& partyInfo);

	/// 나의 파티 정보 받기를 실패
	virtual void onRecvGuildMatchMyPartyInfoFailed();

	/// 길드전 상대팀 파티의 정보를 얻었다
	virtual void onRecvGuildMatchOtherPartyInfoOK(const bool success, GuildMatchPartyInfo& partyInfo);

	/// 나의 파티 ID 할당을 성공
	virtual void onRecvGuildMatchGetPartyIDOK(const __int64 partyID);

	/// 나의 파티 ID 할당을 실패
	virtual void onRecvGuildMatchGetPartyIDFailed(eGuildMatchFailedReason failedReason);
	
	/// 파티의 마스터가 변경되었다
	virtual void onRecvGuildMatchChangePartyMaster(const __int64 partyID, const UINT masterIndex);

	/// 게임이 끝날때까지 Scene 대기를 한다
	virtual void onRecvGuildMatchRemakePartyWaitSceneChange(eRoomKind roomKind);

	/// 룸을 변경해라
	virtual void onRecvGuildMatchChangeRoomKindNotify(const eRoomKind roomKind);

	/// 파티 등록이 취소되었다
	virtual void onRecvGuildMatchUnRegistPartyACK(const bool bSuccess);

	/// 길드 매치 동작을 처리한다 (취소, 거절, 수락 상황일때 실패를 대비한 같은팀의 UI닫기 처리를 위한것
	virtual void onRecvGuildMatchMatchActionACK(eGuildMatchAction action);

	/// 매칭 검색을 다시 해라
	virtual void onRecvGuildMatchSearchingPartyRetry();

	/// 매칭 시작 요청을 성공하였다
	virtual void onRecvGuildMatchSearchingPartyStartACK(eGuildMatchType matchType,const bool bSuccess);

	/// 매칭 검색을 하려고 하는데 잘못되어 실패했다 (에러 상황)
	virtual void onRecvGuildMatchSearchingPartyFailed(eGuildMatchFailedReason failedReason);

	/// 매칭 검색을 그만둔다, 매칭을 성공하지 못했다
	virtual void onRecvGuildMatchSearchingMatchStop();

	/// 길드전 길드 메시지
	virtual void onRecvGuildMatchGuildMsg(eGuildMatchType matchType, std::string& oppGuildName, bool bWinTeam, const int successiveWin);

	/// 매칭을 취소하였다
	virtual void onRecvGuildMatchSearchingPartyCancel();

	/// 옵저버가 길드전 매칭룸에 따라 들어가기를 예약했다
	virtual void onRecvGuildMatchObserverEnterRoomReservationOK();

	/// 옵저버가 길드전 매칭룸에 따라 들어가기 예약을 실패했다
	virtual void onRecvGuildMatchObserverEnterRoomReservationFailed(eGuildMatchFailedReason failedReason);

	/// 유저가 초대해야 할 옵저버의 닉네임을 받았다
	virtual void onRecvGuildMatchObserverEnterRoomData(std::string observerNickName);

	/// 길드매치 플레이횟수 제한 있는경우 매칭 실패 매세지
	virtual void onRecvGuildMatchPlayStartLimitFailed(eGuildMatchFailedReason failedReason);

#ifdef _RAINBOW_LEAGUE
	///< 레인보우 리그 유저정보를 받았다
	virtual void onRecvRainbowGetUserInfoOK(RainbowLeagueUserInfo & userInfo);
	virtual void onRecvRainbowGetUserInfoFailed(eRainbowLeagueFailedReason failedReason);

	///< 배치 결과를 받았다
	virtual void onRecvRainbowGetDispositionResultOK(bool bIsResult, eRainbowLeagueType leagueType, int iTotalPoint);
	virtual void onRecvRainbowGetDispositionResultFailed(eRainbowLeagueFailedReason failedReason);

	///< 명예, 업적보상 지급
	virtual void onRecvRainbowDispositionRewardOK(eLevelUPKind rewardType, eRainbowLeagueKind leagueKind, int rewardLevel, std::vector<RewardInfo> & vecRewardInfo);
	virtual void onRecvRainbowDispositionRewardFailed(eRainbowLeagueFailedReason failedReason);

	///< 레인보우 리그 경기 기록 을 받았다
	virtual void onRecvRainbowGetLatestRecordOK(int iMapNum, RainbowLeagueLatestInfo & latestInfo, eRainbowLeagueKind matchKind, eRainbowLeagueType matchType, int iPoint);
	virtual void onRecvRainbowGetLatestRecordFailed(eRainbowLeagueFailedReason failedReason);

	///< 매칭 미니게임 시작을 받았다
	virtual void onRecvRainbowMiniGameStartOK();
	virtual void onRecvRainbowMiniGameStartFailed(eRainbowLeagueFailedReason failedReason);

	///< 매칭 미니게임 결과를 받았다
	virtual void onRecvRainbowMiniGamePointOK(exp_type iExp, int iGameMoney);
	virtual void onRecvRainbowMiniGamePointFailed(eRainbowLeagueFailedReason failedReason);

	/// 경쟁 리그 배치 받기 결과를 받았다
	virtual void onRecvRainbowLeagueKindChangeAck(eRainbowLeagueKind leagueKind, eRainbowLeagueType leagueType, std::vector<RewardInfo> & vecConsumeList);
	virtual void onRecvRainbowLeagueKindChangeFailed(eRainbowLeagueFailedReason failedReason);

	///< 대전하기 요청이 성공하였다
	virtual void onRecvRainbowLeagueSearchingDoingAck(int iEntryTime);

	///< 대전하기 다시 요청을 해라
	virtual void onRecvRainbowLeagueSearchingRetry();

	///< 마땅한 상대를 찾지 못했다(서버가 클라에게 그만하라고 알린다)
	virtual void onRecvRainbowLeagueSearchingMatchStop();

	///< 대전 상대 못찾은게 아니라 뭔가가 잘못되어 에러처리 된 상황
	virtual void onRecvRainbowLeagueSearchingFailed(eRainbowLeagueFailedReason failedReason);

	///< 레인보우 파티 정보를 알려준다
	virtual void onRecvRainbowLeagueMyPartyInfoNotify(RainbowLeaguePartyInfo & partyInfo);

	///< 레인보우 파티 마스터에게 알려준다. 방을 만들어라
	virtual void onRecvRainbowLeagueActionNotify(eRainbowLeaguePartyState state, int iMatchingPointAVG);

	///< 레인보우 맵 최고 기록을 받았다
	virtual void onRecvRainbowLeagueTopRecordNotify(int iClearTime);

	///< 대전하기 유저의 취소에 의해 그만둔다
	virtual void onRecvRainbowLeagueSearchingCancel();

	///< 레인보우 패널티 정보를 받았다
	virtual void onRecvRainbowLeaguePenaltyNotify(int restrictTime);

	///< 레인보우 패널티 결과정보를 받았다
	virtual void onRecvRainbowLeaguePenaltyResultNotify(eRainbowLeagueKind matchKind, eRainbowLeagueType matchType, eRainbowLeagueResult rainbowLeagueResult, int iResultPoint
#ifdef _CHAMPIONS_CUP
		, bool bIsAddPlayCount
#endif		
		);

	///< 레인보우 랭킹 요청
	virtual void onRecvRainbowLeagueRankInfo(eServerResult result, eRainbowLeagueFailedReason failedReason, eRequestRankKind rankKind, eRankDetailKind rankDetailKind, const std::vector<RainbowLeagueRankInfo> & rankInfo);

	///< 나의 레인보우 랭킹 결과
	virtual void onRecvRainbowLeagueMyRankInfo(eRequestRankKind rankKind, eRankDetailKind rankDetailKind, RainbowLeagueRankInfo & rankInfo);
	virtual void onRecvRainbowLeagueMyRankInfoFailed(eRequestRankKind rankKind, eRankDetailKind rankDetailKind, eRainbowLeagueFailedReason failedReason);

#endif

	//////////////////////////////////////////////////////////////////////////
	/// 카드팩 관련

	// 카드팩 열어 보상을 받았다. 
	virtual void onRecvCardPackOpenReward(const int cardPackNum, const short openType, std::vector<RewardInfo> & vRewardItem);

	// 카드팩 열어 보상을 받기 실패했다.
	virtual void onRecvCardPackOpenFailed( eCardPackOpenRewardFailedReason failedreason );

	//////////////////////////////////////////////////////////////////////////

	// 다른 유저가 닉네임을 변경했다고 받았다.
	virtual void onRecvNickNameChangeNotify(const std::string& strNewNickName, const std::string& strOldNickName);

	// GM 경고 메시지
	virtual void onRecvGMWarningMsg(std::string& msg);

	/// 유저의 퀘스트 정보를 받았음
	virtual void onRecvQuestUserInfo(eQuestServerResult result, const bool bComplete, QuestUserInfoMap& questUserInfoMap);

	/// 퀘스트 도전에 대한 결과
	virtual void onRecvQuestAddAck(eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList);

	/// 퀘스트 포기에 대한 결과
	virtual void onRecvQuestRemoveAck(eQuestServerResult result, const int questNum);

	/// 퀘스트 완료에 대한 결과
	virtual void onRecvQuestRewardAck(eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList);

	/// 이벤트 퀘스트 정보 수신
	virtual void onRecvQuestEventNotify(bool bActive, std::set<int>& questNumList);


#ifdef NPC_EVENT
	/// 퀘스트 질문하기 정보
	virtual void onRecvQuestInterrogationInfoAck(eQuestServerResult result, const QuestInterrogationInfo questInterrogationInfo);

	/// 퀘스트 질문하기 비용차감
	virtual void onRecvQuestInterrogationConsumeAck(eQuestServerResult result, const int npcNum);

	/// 퀘스트 질문하기 답변 저장
	virtual void onRecvQuestInterrogationQuestionAck(eQuestServerResult result, const int npcNum, std::vector<int>& nextNumList);

	/// 퀘스트 질문하기 완료에 대한 결과 (보상)
	virtual void onRecvQuestInterrogationFinishAck(eQuestServerResult result, const int npcNum, const int iLevel, std::vector<IntegratedReward>& rewardList);

	/// NPC 질문하기 결과 (보상)
	virtual void onRecvQuestInterrogationRewardAck(eQuestServerResult result, const int npcNum, const int iLevel, std::vector<IntegratedReward>& rewardList);

	/// NPC 질문하기 스케쥴
	virtual void onRecvQuestInterrogationScheduleAck(std::map<int, QuestInterrogationScheduleInfo>& schedule);
#endif

#ifdef LOBBY_QUEST_CHANNEL_SYSTEM
	/// 유저의 채널퀘스트 정보를 받았음
	virtual void onRecvLobbyQuestUserInfo(eQuestServerResult result, const bool bComplete, QuestUserInfoMap& questUserInfoMap);

	/// 채널퀘스트 도전에 대한 결과
	virtual void onRecvLobbyQuestAddAck(eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList);

	/// 채널퀘스트 포기에 대한 결과
	virtual void onRecvLobbyQuestRemoveAck(eQuestServerResult result, const int questNum);

	/// 채널퀘스트 완료에 대한 결과 (보상)
	virtual void onRecvLobbyQuestRewardAck(eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList);

	/// 이벤트 채널퀘스트 정보 수신
	virtual void onRecvLobbyQuestEventNotify(bool bActive, std::set<int>& questNumList);
#endif

	/// 간편 아이디가 사용할 수 없는 컨텐츠임을 알려준다
	virtual void onRecvSimpleIDInvalidContentsNotify();

	/// Room Kind 의 속성을 받았음.
	virtual void onRecvRoomKindAttr(const RoomKindAttr& roomKindAttr, bool bValid);

	/// 아누비스 원정대 정보를 받았다.
	virtual void onRecvAnubisExpeditionGetInfo(const AnubisExpeditionInfo & scheduleInfo, std::map<eRoomKind, int> & runInfo);

	/// 아누비스 원정대 유저 정보를 받았다.
	virtual void onRecvAnubisExpeditionGetUserInfo(const int iPoint);
 
	/// 아누비스 원정대 게임 종료 공지를 받았다.
	virtual void onRecvAnubisExpeditionEndGameNotify();

#ifdef SPORTS_PLAY_LIMIT_CHECK
	/// 대운동회 일별 시작시간을 받았음
	virtual void onRecvSportsPlayLimit(const UserSportsPlayLimit& sportsPlayLimit, BOOL playable);
#endif

	//////////////////////////////////////////////////////////////////////////

#ifdef _EXCHANGE_SYSTEM
	/// 교환 시스템 사용 정보
	virtual void onRecvExchangeSystemGetUseInfo(eExchangeSystem systemType, const eExchangeSystemResult result);

	/// 교환 시스템 교환 성공
	virtual void onRecvExchangeSystemExchangeOK(std::vector<RewardInfo>& resultList, int count);

	/// 교환 시스템 교환 실패
	virtual void onRecvExchangeSystemExchangeFailed(eExchangeSystemResult result);
#endif

#ifdef _COMBINATION_SHOP_
	/// 매점 시스템 사용 정보
	virtual void onRecvCombinationShopGetUseInfo(eCombinationShop systemType, const eCombinationShopResult result);

	/// 매점 시스템 시작,종료 공지
	virtual void onRecvCombinationShopNotify(eCombinationShop systemType, const bool bIsVisible);

	/// 매점 시스템 갯수 제한 리스트 성공
	virtual void onRecvCombinationShopGetLimitInfoInfoOK(eCombinationShop systemType, std::map<int, int>& countList);

	/// 매점 시스템 갯수 제한 리스트 실패
	virtual void onRecvCombinationShopGetLimitInfoInfoFailed(eCombinationShop systemType, eCombinationShopResult result);

	/// 매점 시스템 실시간 변경 아이템 리스트 성공
	virtual void onRecvCombinationShopGetItemDetailInfoOK(std::map<int, CombinationShopItemDetailInfo>& itemList);

	/// 매점 시스템 교환 성공
	virtual void onRecvCombinationShopExchangeOK(bool bSucess, std::vector<RewardInfo>& resultList);

	/// 매점 시스템 교환 실패
	virtual void onRecvCombinationShopExchangeFailed(eCombinationShopResult result);
#endif

	/// 아이템 변환 결과
	virtual void OnRecvItemConvertAck(const item_convert::CDoConvertResult& result);

	//!< DB 저장 스크립트 업데이트 결과
	virtual void OnRecvEventStatusUpdateAck(const CEventStatusUpdateAck& ack);
	//!< DB 저장 스크립트 서버 실행 결과
	virtual void OnRecvEventStatusExecAck(const CEventStatusExecAck& ack);
	//!< DB 저장 스크립트 쿼리 결과
	virtual void OnRecvEventStatusQueryAck(const CEventStatusQueryAck& ack);


	//////////////////////////////////////////////////////////////////////////
	// 커뮤니티 서버 관련 시작

	/// 커뮤니티 서버에 접속 실패
	virtual void community_onConnectFail(eCommunityConnectFail failReason);

	/// 친구 아바타 정보를 받았다.
	virtual void community_onRecvFriendAvatarInfo(const std::string & strFriendNickname, const exp_type iExp
#ifdef _NUMBERS
		, const int iNumbers
#endif
		, const AvatarInfo & avatarInfo);


	/// 메시지를 받았다.
	virtual void community_onRecvMsg(const std::string & strNickname, const std::string & strMsg);

	/// 메세지에 대한 응답을 받았다.
	virtual void community_onRecvMsgAck(const std::string& strNickName, const std::string& strMsg, eMessageResult messageResult);

	/// 메시지를 보내지 못하고 다시 받음
	virtual void community_onRecvForwardingMsgFailed(const std::string & strFromNickName, eForwardingFailed eResult);

	/// 채팅 귓말 메세지 요청을 받았다.
	virtual void community_onRecvWhisperMsgReq(const std::string & strNickname, const byte byUserAttr, const std::string & strMsg);

	/// 채팅 귓말 메세지 응답을 받았다.
	virtual void community_onRecvWhisperMsgAck(const std::string & strNickname, const byte byUserAttr, const std::string & strMsg, const eWhisperRequestResult whisperRequestResult);

	/// 일반, 가족, 길드 채팅 메세지를 받았다.
	virtual void community_onRecvChatting(const std::string & strNickname, const std::string & strMsg, eChattingType chattingType);

	/// 누군가의 상태를 받았다.
	virtual void community_onRecvState(const std::string & strNickname, const UserState & state);

	/// 친구 추가가 성공했다.
	virtual void onRecvAddFriendOK(const std::string & strNickname);

	/// 친구의 게임 상태를 받았다.
	virtual void community_onRecvGameState(const std::string & strFriendNickname, bool bPlayGame);

	/// 친구 추가가 실패했다.
	virtual void onRecvAddFriendFailed(const std::string & strNickname, eAddFriendFailed addFriendFailed);

	/// 친구 수락이 성공했다.
	virtual void community_onRecvAcceptFriendOK(const std::string & strNickname);

	/// 친구 수락이 실패했다.
	virtual void community_onRecvAcceptFriendFailed(const std::string & strNickname, eCommunityAcceptFriendFailedReason reason);

	/// 친구 거절을 성공했다.
	virtual void community_onRecvDeclineFriendOK(const std::string & strNickname);

	/// 친구 거절을 실패했다.
	virtual void community_onRecvDeclineFriendFailed(const std::string & strNickname);

	/// 친구 등록을 거절당했다.
	virtual void community_onRecvDeclineFriend(const std::string & strNickname);

	/// 친구를 블럭하는데 성공했다.
	virtual void community_blockFriendOK(const std::string & strFriendNickname);

	/// 친구를 블럭하는데 실패했다.
	virtual void community_blockFriendFailed(const std::string & strFriendNickname, eRemoveFriendFailed eFailedReason);

	/// 친구 블럭을 취소하는데 성공했다.
	virtual void community_unblockFriendOK(const std::string & strFriendNickname);

	/// 친구 블럭을 취소하는데 실패했다.
	virtual void community_unblockFriendFailed(const std::string & strFriendNickname);

	/// 친구를 삭제 표시하는데 성공했다.
	virtual void community_deleteFriendOK(const std::string & strFriendNickname);

	/// 친구를 삭제 표시하는데 실패했다.
	virtual void community_deleteFriendFailed(const std::string & strFriendNickname, eRemoveFriendFailed eFailedReason);

	/// 친구를 삭제 표시 제거하는데 성공했다.
	virtual void community_undeleteFriendOK(const std::string & strFriendNickname);

	/// 친구를 삭제 표시 제거하는데 실패했다.
	virtual void community_undeleteFriendFailed(const std::string & strFriendNickname);

	/// 친구 등록 대기 중인 친구를 제거하는데 성공했다.
	virtual void community_cancelAddFriendOK(const std::string & strNickname);

	/// 친구 등록 대기 중인 친구를 제거하는데 실패했다.
	virtual void community_cancelAddFriendFailed(const std::string & strNickname);

	/// 그룹 operation 결과
	virtual void community_onRecvGroupOperate(eCommunityGroupOperationType type,vCommunityGroupInfo& vecGroupInfo);

	/// 그룹 operation 결과가 실패하였다
	virtual void community_onRecvGroupOperateFailed(eCommunityGroupOperationType type, eCommunityGroupResult result, short groupNum);

	/// 그룹 멤버 이동 결과
	virtual void community_onRecvMoveGroupMember(eCommunityGroupResult result);

	/// 대화명 변경
	virtual void community_onRecvOnlineIDSet(bool isSuccess, std::string strOnlineID);


	/// 상대로부터 친구 리스트로부터 자신을 삭제라하는 통지를 받았다.
	virtual void community_onRecvDeleteFriend(const std::string & strFromNickname);

	/// 친구의 팜 정보가 변경되었다는 통지를 받았다. 
	virtual void community_onRecvFarmInfoToFriend(const std::string& strFromNickname, const FarmShortInfo& info); 

	/// 친구의 팜 사용기간이 만료되었다는 통지를 받았다. 
	virtual void community_onRecvFarmPeriodExpiredToFriend(const std::string& strFromNickname); 

	/// 친구의 팜 사용기간을 갱신했다는 통지를 받았다. 
	virtual void community_onRecvFarmPeriodRenewalToFriend(const std::string& strFromNickname, const FarmShortInfo& info); 

	/// 나를 친구로 등록한 게 있다.
	virtual void onRecvRequestToMeFriend(const std::string & strNickname,const std::string & strInviteMessage );

	//[mirime 2019-02-21] 친구 등록을 체크해봐라.
	virtual void community_onRecvCheckFriendRequest(bool reqeustAdd, const std::string & nickname) override;

	/// 누가 자기 방에 들어오라고 했다.
	virtual void community_onRecvJoinMe(const std::string & strNickname, eRoomKind roomKind, int iRoomServerNum, unsigned int hRoom, const std::string & strPassword, const int iAttribute, const bool bRequireACK, const __int64 partyID = -1);

	/// 누군가를 초대했었는데 못 들어온다고 한다.
	virtual void community_onRecvJoinMeFail(const std::string & strNickname, const bool bAutoReply,const int iAtrribute);

	/// 따가가리를 실패하였다.
	virtual void community_onRecvFindGoFailed(const std::string & strNickname );

	/// 1대1 대화를 요청한다.
	virtual void community_onRecvRequest1on1Chat( const std::string& strNickname );

	/// 1대1 대화를 수락상태를 돌려준다.
	virtual void community_onRecvResponse1on1Chat(const std::string& strNickname, bool bOK);

	/// 친구가 로그인되었다.
	virtual void community_onRecvFriendOnline(const std::string & strFriendNickname);

	/// 가족이 로그인되었다.
	virtual void community_onRecvFamilyOnline(const std::string & strNickname);

	/// 길드원이 로그인되었다.
	virtual void community_onRecvGuildOnline(const std::string & strNickname);

	/// 친구가 로그오프되었다.
	virtual void community_onRecvFriendOffline(const std::string & strFriendNickname);

	/// 가족이 로그오프되었다.
	virtual void community_onRecvFamilyOffline(const std::string & strNickname);

	/// 길드원이 로그오프되었다.
	virtual void community_onRecvGuildOffline(const std::string & strNickname);

	/// 상대로부터 프로포즈 받았다.
	virtual void community_onRecvCoupleProposeRequest(const std::string & strFromNickname, const std::string & strCoupleName, const std::string & strCoupleDesc, const int iJewelBoxNum, const bool bMeetingDependency);

	/// 프로포즈에 대한 승인여부를 받았다.
	virtual void community_onRecvCoupleProposeResponse(const std::string & strFromNickname, const bool bOK, const eCoupleProposeReject eReason, const int iCoupleNum, const int iCoupleRingNum);

	/// 상대로부터 커플을 끊겠다는 통지를 받았다.
	virtual void community_onRecvCoupleSayGoodBye(const std::string & strFromNickname);

	/// 상대로부터 커플링을 변경했다 통지를 받았다.
	virtual void community_onRecvCoupleRingChanged(const std::string & strFromNickname, const int iCoupleRingNum);

	/// 상대로부터 커플명을 변경했다 통지를 받았다.
	virtual void community_onRecvCoupleNameChanged(const std::string & strFromNickname, const std::string & strCoupleName);

	/// 상대로부터 커플소개가 변경했다 통지를 받았다.
	virtual void community_onRecvCoupleDescModify(const std::string & strFromNickname);

	/// 상대로부터 이혼 소송(동의를 구하기 위한)을 했다는 통지를 받았다.
	virtual void community_onRecvWeddingSuitForDivorce(const std::string & strFromNickname, const eWeddingDivorceType eDivorceType);

	/// 상대로부터 이혼에 동의하지 않는다는 통지를 받았다.
	virtual void community_onRecvWeddingDisagreeForDivorce(const std::string & strFromNickname, eWeddingDisagreeDivorceType eDisagreeType);

	/// 상대로부터 이혼했다는 통지를 받았다.
	virtual void community_onRecvWeddingDivorced(const std::string & strFromNickname, const eWeddingDivorceType eDivorceType, const bool bEnforce);

	/// 상대방에게 커플 전용 아이템을 구매했음을 통지 받았다.
	virtual void community_onRecvBuyCoupleItem(const std::string & strFromNickname);

	/// 상대에게 가족 맺기 요청을 받았다.
	virtual void community_onRecvFamilyPropose(const std::string& strFromNickname, bool bParents);

	/// 상대에게 가족 맺기 요청에 대한 승인여부 통지를 받았다.
	virtual void community_onRecvFamilyProposeResponse(const std::string& strFromNickname, bool bSummit, eFamilyProposeReject eReason, bool bParents);

	/// 상대에게 가족 맺어짐을 통보 받았다.
	virtual void community_onRecvFamilyMakeNotify(const std::string& strFromNickName, bool bParents);

	/// 상대로 부터 가족 끊기 통보를 받았다.
	virtual void community_onRecvFamilyBreakNotify(const std::string& strFromNickName);

	/// 상대에게 삐에로 올림픽 같은팀에 가입하자고 요청을 받았다.
	virtual void community_onRecvPieroOlympicJoinPartyPropose(const std::string& strFromNickname, const ePieroOlympicPartyType ePartyType);

	/// 상대로부터 오픈 TV를 시청중이라는 통지를 받았다.
	virtual void community_onRecvWatchingOpenTV();

	/// 상대로부터 로그인을 했는지 확인 요청을 받았다.
	virtual void community_onRecvRequestLogin(const std::string& strFromNickname);

	/// 상대로부터 로그인을 했다는 응답을 받았다.
	virtual void community_onRecvResponseLogin(const std::string& strFromNickname, bool isBlocking);

	/// 길드가 레벨업 되었음을 길드 마스터로 부터 통지 받았다.
	virtual void community_onRecvGuildLevelUp(short iGuildLevel);

	/// 길드 맴버가 탈퇴 되었음을 통지 받았다.
	virtual void community_onRecvGuildMemberLeave(const std::string& strNickName);

	/// 길드원들의 기여도 포인트를 받았다. 
	virtual void community_guildMemberContributeRefresh();	

	/// 길드 가입 추천을 받았다.
	virtual void community_onRecvGuildProposeRecommend(const std::string& strFromNickname, const GuildInfo& guildInfo, const bool & bInternJoin );

	/// 길드 마스터 이양을 추천받았다.
	virtual void community_onRecvGuildConveyMasterPropose(const std::string& strFromNickname);

	///< 길드원에게 길드 마스터를 이양받을지 물어본다.
	virtual void community_onRecvGuildConveyMasterProposeResult(const std::string& strFromNickname, bool bAccept);

	/// 친구 리스트가 업데이트 되었다.
	virtual void onFriendListUpdate();

	/// 현재 초대받을 수 있는 상태인가.
	virtual bool canInvited() const;

	/// 현재 1대1 대화를 할수 있는 상태인가?
	virtual e1on1ChatOption can1on1ChatInvited() const;

	/// 튜토리얼 코드 (친구에게 데이터를 받았다.)
	virtual void community_onRecvTutorialSendMyDataToFriend(const std::string& strFromNickname, std::string strValue, int iValue);

	/// 어떤 허그유저가 추천인으로 등록한것을 알린다.
	virtual void community_onRecvHugSystemRecommendUser(const std::string & strFromNickname);

	/// 추천인이 레벨업을 했다고 알려준다.
	virtual void community_onRecvHugSystemLevelUp(const std::string & strFromNickname, short iHugLevel, eHugUserType eUserType);

	/// 피추천인이 추천인을 삭제했다고 알려준다.
	virtual void community_onRecvHugSystemRemoveRecommendUser(const std::string & strFromNickname);	

#ifdef _PERSONAL_CONNECTIONS

	// 인맥시스템 등록 여부 
	virtual void community_onRecvPersonalConnectionsIsRegisterOK(const bool bRegister, const time_type infoEditDate, const __int64 authNum);
	virtual void community_onRecvPersonalConnectionsIsRegisterFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 등록 요청 
	virtual void community_onRecvPersonalConnectionsRegisterOK(ePersonalConnectionsResult dwResult);

	// 인맥시스템 나의정보 설정 
	virtual void community_onRecvPersonalConnectionsSetInfoOK();
	virtual void community_onRecvPersonalConnectionsSetInfoFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 나의정보 요청 
	virtual void community_onRecvPersonalConnectionsGetInfoOK(const PersonalConnectionsInfo & infoList);
	virtual void community_onRecvPersonalConnectionsGetInfoFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 검색횟수 요청 
	virtual void community_onRecvPersonalConnectionsCountInfoOK(const ePersonalConnectionsKind eKind, const int iCount);
	virtual void community_onRecvPersonalConnectionsCountInfoFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 이전 검색 요청 
	virtual void community_onRecvPersonalConnectionsBeforeSearchOK(const ePersonalConnectionsKind eKind, const std::map<std::string, PersonalConnectionsSearch> & resultList);
	virtual void community_onRecvPersonalConnectionsBeforeSearchFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 검색 요청 
	virtual void community_onRecvPersonalConnectionsSearchOK(const ePersonalConnectionsKind eKind, const std::map<std::string, PersonalConnectionsSearch> & resultList);
	virtual void community_onRecvPersonalConnectionsSearchFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 이상형월드컵 출전횟수/우승횟수 요청 
	virtual void community_onRecvPersonalConnectionsIdealTypeCountOK(const int iEntryCount, const int iWinCount);
	virtual void community_onRecvPersonalConnectionsIdealTypeCountFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 오늘의 친구 설정 
	virtual void community_onRecvPersonalConnectionsTodayFriendOK(const bool bRegister);
	virtual void community_onRecvPersonalConnectionsTodayFriendFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 데이트, 이상형 설정 
	virtual void community_onRecvPersonalConnectionsSelectUserOK(const ePersonalConnectionsKind eKind);
	virtual void community_onRecvPersonalConnectionsSelectUserFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 데이트 슬롯 오픈 
	virtual void community_onRecvPersonalConnectionsOpenSlotOK(const ePersonalConnectionsKind eKind);
	virtual void community_onRecvPersonalConnectionsOpenSlotFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 프로필 요청 
	virtual void community_onRecvPersonalConnectionsProfileOK(const ePersonalConnectionsKind eKind, const PersonalConnectionsProfile & infoList);
	virtual void community_onRecvPersonalConnectionsProfileDetailOK(const PersonalConnectionsProfileDetail & infoList);
	virtual void community_onRecvPersonalConnectionsProfileFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 호감주기 
	virtual void community_onRecvPersonalConnectionsSetPointOK(const std::string & strTargetNickName, const std::string & strTargetAnotherName, const int iPoint);
	virtual void community_onRecvPersonalConnectionsSetPointFailed(ePersonalConnectionsResult dwResult);

	// 인맥시스템 지난 내역보기 요청 성공 
	virtual void community_onRecvPersonalConnectionsHistoryOK(const ePersonalConnectionsKind eKind, unsigned short numPage, unsigned short totalCount, const std::map <std::string, PersonalConnectionsSearch> & historyList);
	// 인맥시스템 지난 내역보기 요청 실패 
	virtual void community_onRecvPersonalConnectionsHistoryFailed(ePersonalConnectionsResult dwResult);

	/// 인맥시스템 상대방으로부터 호감을 받았다.
	virtual void community_onRecvPersonalConnectionsSendPointNotify(const std::string& strFromNickName, const std::string& strAnotherName, const int iPoint);

	/// 인맥시스템 전용 1대1 대화를 요청한다.
	virtual void community_onRecvPersonalConnectionsRequest1on1Chat(const std::string& strNickName);

	/// 인맥시스템 전용 1대1 대화상태를 알려준다.
	virtual void community_onRecvPersonalConnectionsResponse1on1Chat(const std::string& strNickName, bool bOK);

	/// 인맥시스템 상대방으로부터 전용 대화 메세지를 받았다.
	virtual void community_onRecvPersonalConnectionsMsg(const std::string & strFromNickName, const std::string & strFromAnotherName, const std::string & strMsg);

	/// 인맥시스템 메세지에 대한 응답을 받았다.
	virtual void community_onRecvPersonalConnectionsMsgAck(const std::string& strNickName, const std::string& strMsg, eMessageResult messageResult);

	/// 인맥시스템 상대가 나의 정보를 요청했다.
	virtual void community_onRecvPersonalConnections1on1nfoRequest(const std::string& strNickName);

	/// 인맥시스템 상대방 정보를 받았다.
	virtual void community_onRecvPersonalConnections1on1nfoResponse(const std::string& strNickName, PersonalConnectionsSearch & info);
#endif


	virtual void community_onRecvFarmNameTagRequest(const std::string & strFromNickname, const std::string & strNameTag);

	virtual void community_onRecvFarmNameTagResponse(const std::string & strFromNickname, const std::string & strNameTag, const bool bOK, const eFarmNameTagResult eResult);


#ifdef _PARTY_SYSTEM
	/// 파티 초대에 대한 거절
	virtual void community_onRecvPartyInviteRefuse(const std::string& strNickName);
	
	/// 파티 지원요청에 대한 알림
	virtual void community_onRecvPartySupportBoardJoin(const std::string& strNickName);
#endif

	// 커뮤니티 서버 관련 끝
	//////////////////////////////////////////////////////////////////////////

#ifdef COUNTERATTACK_OF_ANUBIS
	// 아누비스 관련
	///경기가 시작되서 현재 웨이브 정보를 받았다.
	virtual void onRecvAnubisStartGame(const AnubisWaveInfo& waveInfo);

	///진행중인 웨이브가 종료 되었다.
	virtual void onRecvAnubisEndGame(eAnubisGameResult eResult);

	///게임 시작 예정 공지를 받았다.
	virtual void onRecvAnubisNextGameNotify(eAnubisWaveGrade eWaveGrade);

	///룸 리스트를 받았다.
	virtual void onRecvAnubisGetGateList(const std::vector<AnubisGateInfo>& roomList);

	///남은 게이트 갯수를 받았다.
	virtual void onRecvAnubisGetRemainGateCount(const int iRemainGateCount);

	///게이트 클리어 공지를 받았다.
	virtual void onRecvAnubisGateClearNotify(const eRoomKind roomKind, const int iGateNum);
#endif //COUNTERATTACK_OF_ANUBIS


#ifdef SMART_CHANNEL_SYSTEM
	virtual void onRecvSmartChannelScheduleInfo(std::map<time_type, time_type> & scheduleInfo);
	virtual void onRecvSmartChannelModeInfo(std::map<int/*modeNum*/, SmartChannel> & channelinfo);
	virtual void onRecvSmartChannelUserInfo(bool result, UserSmartChannel& userChannelInfo);

#endif

#ifdef _SCHOOL_BATTLE
	/// 학교대항전 내정보를 받음
	virtual void onRecvSchoolBattleMyInfo(const SchoolBattleInfo& info, eSchoolBattleResult result);

	/// 학교대항전 Top10 랭킹 받음
	virtual void onRecvSchoolBattleTopRank(const std::vector<SchoolBattleInfo>& topTenRank, eSchoolBattleResult result);
#endif

	virtual void onRecvRoomKindPenaltyInfo(std::map<eRoomKind, int>& penaltyInfo);

	/// 아이템을 사용했다.
	virtual void onRecvAssaultModeUseItemOK(const int iItemDescNum, const int iItemCount);

	///NPC정보를 세팅하는데 성공했다.
	virtual void onRecvAssaultModeSetObjectInfoOK(const std::vector<AssaultModeObjectInfo>& objectInfo);

	///NPC정보를 세팅하는데 실패했다.
	virtual void onRecvAssaultModeSetObjectInfoFailed(const std::vector<int> & fail_list);

	///캐릭터 에너지를 세팅했다.
	virtual void onRecvAssaultModeSetCharacterEnergyInfo(const std::map<int/*playerIndex*/, int/*energy*/>& playerList);

	///캐릭터의 에너지가 차감됐다.
	virtual void onRecvAssaultModeDecreaseCharacterEnergyOK(const int iPlayerIndex, const int iEnergy);

	///캐릭터의 에너지 차감에 실패했다.
	virtual void onRecvAssaultModeDecreaseCharacterEnergyFailed(const int iObjectNum, const int flag);

	///캐릭터의 에너지를 충전에 성공 / 실패..
	virtual void onRecvAssaultModeChargeCharacterEnergyResult(const int nResultValue,const int nPlayerIndex,const int nEnergy);

	///NPC의 에너지가 차감됐다.
	virtual void onRecvAssaultModeDecreaseObjectEnergyOK(const int iPlayerIndex, const int iObjectNum, const int iEnergy, const int iDelta, int iAttacker);

	///NPC의 에너지 차감에 실패했다.
	virtual void onRecvAssaultModeDecreaseObjectEnergyFailed(const int iObjectNum);

	///NPC 보상 정보를 받았다.
	virtual void onRecvAssaultModeGetObjectRewardInfo(const int iObjectNum, const std::vector<AssaultModeGotRewardInfo>& rewardInfo);

	virtual void onRecvAssaultModeChargeObjectEnergy(std::vector<std::pair<int,int>> & vecObjectChargeEnergyInfo);

	///NPC의 에너지충전에 실패하였다.
	virtual void onRecvAssaultModeChargeObjectEnergyFailed(std::vector<int> & list);

	///아이템 획득 성공.
	virtual void onRecvAssaultModeEatItemOK(const AssaultModeGotRewardInfo& rewardInfo);


	///아이템 획득 실패.
	virtual void onRecvAssaultModeEatItemFailed();

	///부활 아이템을 사용했다.
	virtual void onRecvAssaultModeRebirthOK(const int iPlayerIndex, const int iEnergy,const eAssaultModeRebirthType eFlag);

	///부활 아이템 사용에 실패했다.
	virtual void onRecvAssaultModeRebirthFailed(eAssaultModeUseItemFailed eFailed,const eAssaultModeRebirthType eFlag);

	// 보너스 아이템 만들기 성공
	virtual void onRecvAssaultModeBonusItemMakeOK();

	// 보너스 아이템 만들기 실패
	virtual void onRecvAssaultModeBonusItemMakeFailed();

	// 보너스 아이템 먹기 성공
	virtual void onRecvAssaultModeBonusItemEatOK(const int index, RewardInfo& reward);

	// 보너스 아이템 먹기 실패
	virtual void onRecvAssaultModeBonusItemEatFailed();

	// 맵 발판 밟기 결과
	virtual void onRecvMapBoardStepACK(const int boardIndex, eMapBoardType boardType, std::vector<BYTE>& userList);

	// 랜덤 인스턴스 팀이 결정되었다.
	virtual void onRecvSelectRandomInstanceTeam(eTeam randomTeam, eInstanceTeam iInstanceTeam, eTeam otherTeam, eInstanceTeam iInstanceOtherTeam);

	// 팀별 포인트를 받았다.
	virtual void onRecvTeamPoint(int teamPoint[eTeam_MAX]);

	//////////////////////////////////////////////////////////////////////////
#ifdef JOURNEY_TO_THE_WEST
	///서유기 경기 정보를 받았다.
	virtual void onRecvJourneyToTheWestGetScheduleInfoOK(const time_type & tStartTime, const time_type & tCloseTime);

	///서유기 유저 정보를 받았다.
	virtual void onRecvJourneyToTheWestGetUserInfoOK();

	///서유기 팀 정보를 받았다.
	virtual void onRecvJourneyToTheWestGetPartyInfoOK();

	///서유기 팀 가입 결과를 받았다.
	virtual void onRecvJourneyToTheWestJoinPartyOK();

	///서유기 팀 가입에 실패했다.
	virtual void onRecvJourneyToTheWestJoinPartyFailed(eJourneyToTheWestJoinPartyMsg eMsg);

	///서유기 정보가 갱신되었다고 받았다. 
	virtual void onRecvJourneyToTheWestUpdateNotify(bool bSeasonOn);

	///서유기 유저 팀 정보가 리셋되었다.
	virtual void onRecvJourneyToTheWestResetUserPartyNotify();
#endif
	//////////////////////////////////////////////////////////////////////////

	//////////////////////임시 보관함 관련////////////////////
	/// 구매 결정 대기 목록을 받았다.
	virtual void onRecvStandbyPurchaseDicisionGetListOk();
	/// 구매 결정 대기 목록을 받기를 실패 하였다.
	virtual void onRecvStandbyPurchaseDicisionGetListFail(eServerResult eResult);
	/// 구매 결정 대기 목록 추가되었다.
	virtual void onRecvStandbyPurchaseDicisionAddListOk();
	/// 구매 결정 대기 목록 추가 실패하였다.
	virtual void onRecvStandbyPurchaseDicisionAddListFail(eShopFailed_REASON eResult);
	/// 구매 결정 대기 목록 제거되었다.
	virtual void onRecvStandbyPurchaseDicisionRemoveListOk(int iItemNum, bool bCancellation, int iShopItemNum);
	/// 구매 결정 대기 목록 제거가 실패되었다.
	virtual void onRecvStandbyPurchaseDicisionRemoveListFail(eServerResult eResult);
	/// 구매 결정 대기 목록의 기간 만료 체크 결과 알림
	virtual void onRecvStandbyPurchaseDicisionExistExpireNontify();
	/// Nexon PC방 만료 경고 메시지
	virtual void onRecvAlertMessageNontify(eAlertMessage iMessageType, int iRemainMinutes);
	/////////////////////////////////////////////////////////////

	/// 서버에서 유저의 정보가 필요한지 여부를 받는다.
	virtual void onRecvUserSystemInfo(const bool bSendUserInfo);


	/// 이벤트 보너스 정보를 받았다
	virtual void onRecvEventBonusNofity(const int userIndex, const float bonusExpRatio, const float bonusTRRatio);
#ifdef _COMPETITION_EVENT
	virtual void onRecvEventAccumulateBonusNofity(const std::map<eEventPartyType, CompetitionEventBuffBonusInfo> & bonusInfo);
#endif

	/// 경쟁이벤트 룸카인드 별 인원정보를 받았다
	virtual void OnRecvCompetitionEventRoomKindPlayerList(const std::map<int, RoomKind_UserMinMax>& RoomKindList);

	/// GM명령어, 외치기 제한 걸기 성공
	virtual void onRecvGMCommandShoutRestrictOK(const bool bAddMode, const std::string& nickName, const std::string& startTime, const std::string& endTime);

	/// GM명령어, 외치기 제한 걸기 실패
	virtual void onRecvGMCommandShoutRestrictFailed(const bool bAddMode, eServerResult result);

	//////////////////////////////////////////////////////////////////////////

#ifdef _CHAOS
	/// 카오스 다음게임에 대한 공지를 받음
	virtual void onRecvChaosNoticeNextGameInfo(OlympicGameInfo& gameInfo);

	/// 카오스 다음 게임에 대한 정보를 받음
	virtual void onRecvChaosNextGameInfo(OlympicGameInfo& gameInfo);

	/// 카오스 일정이 비어있다
	virtual void onRecvChaosGameEmpty();

	/// 카오스 승리팀에 대한 공지
	virtual void onRecvChaosNoticeWinnerParty(std::map<int, eEventPartyType>& territoryWinners, const bool chaosGroupSeasonOff);

	/// 카오스 전쟁 지역에 대한 정보 받음
	virtual void onRecvChaosTerritoryInfoOK(std::map<int, std::map<eEventPartyType, __int64> >& territoryInfo, std::map<int, std::pair<eEventPartyType, std::string> >& territoryWinners);

	/// 카오스 전쟁 지역에 대한 정보 받기 실패
	virtual void onRecvChaosTerritoryInfoFailed(eChaosResult result, const int territoryNum);

	/// 카오스 전쟁 지역에 대한 유저의 정보 받음
	virtual void onRecvChaosTerritoryUserInfoOK(std::map<int, __int64>& territoryUserInfo);

	/// 카오스 전쟁 지역에 대한 유저의 정보 받기 실패
	virtual void onRecvChaosTerritoryUserInfoFailed(eChaosResult result);

	/// 카오스 지역에 대한 정보 갱신하라고 받음
	virtual void onRecvChaosTerritoryInfoRefresh();
#endif

	/// 이벤트 채널 포인트 별 보상 받기 성공
	virtual void onRecvEventPointRewardOK(short rewardLevel, std::vector<RewardInfo>& rewardList);

	/// 이벤트 채널 보상 받을 수 있는 시각 정보 받기 성공
	virtual void onRecvEventRewardLimitTimeOK(const time_type& startTime, const time_type& endTime);

	/// 이벤트 채널 보상 리스트를 받음
#ifdef _CHAOS_ZERO_
	virtual void onRecvEventChannelRewardListOK(const std::map<int, std::pair<eEventPartyType, bool> > rewardList, const std::map<int, bool > & JoinList);
#else
	virtual void onRecvEventChannelRewardListOK(const std::map<int, std::pair<eEventPartyType, bool> > rewardList);
#endif

	/// 이벤트 채널 실패 메시지
	virtual void onRecvCompetitionEventFailed(eCompetitionEventResult result);

	/// 이벤트 채널 시작 종료 승리팀에 대한 공지를 받음
	virtual void onRecvEventChannelNoticeOnOff(const bool bStartNotice, const eEventPartyType winnerParty);	

	//////////////////////////////////////////////////////////////////////////

	/// 유저의 뽑기 정보 받음
	virtual void onRecvPickBoardUserInfoACK(const int pickBoardNum, PickBoardUserInfo& pickBoardUserInfo);
	/// 유저의 뽑기 정보 받기를 실패 했다.
	virtual void onRecvGetPickBoardStateFailed(const int pickBoardNum, ePickBoardResult eResult);

	/// 뽑기에 대한 결과
	virtual void onRecvPickBoardUseOK(const int pickBoardNum, const int order, RewardInfo& reward);
	virtual void onRecvPickBoardUseFailed(const int pickBoardNum, ePickBoardResult result);

#ifdef _EVENTPICKBOARD_
	/// 유저의 이벤트 뽑기 정보 받음
	virtual void onRecvEventPickBoardUserInfoACK(const EventPickBoardInfo & pickboardInfo, const BYTE nPickBoardStep, PickBoardUserInfo& pickBoardUserInfo);
	/// 유저의 이벤트 뽑기 정보 받기를 실패 했다.
	virtual void onRecvEventPickBoardUserInfoFailed(const int pickBoardNum, ePickBoardResult eResult);

	/// 이벤트 뽑기에 대한 결과
	virtual void onRecvEventPickBoardUseOK(const int pickBoardNum, const BYTE nPickBoardStep, const int order, RewardInfo& reward, const BYTE nNextStep, const bool bIsReset);
	virtual void onRecvEventPickBoardUseFailed(const int pickBoardNum, ePickBoardResult result);

	/// 이벤트 뽑기 받기/선물
	virtual void onRecvEventPickBoardGiveOK(const bool bIsGift, RewardInfo& reward);
	virtual void onRecvEventPickBoardGiveFailed(ePickBoardResult result);

	/// 이벤트 뽑기 리셋
	virtual void onRecvEventPickBoardResetNotify(const std::vector<int> & initPickBoard);
#endif

#ifdef _ASSAULT_RAID
	/// 오늘의 레이드 스케줄을 받았다.
	virtual void onRecvAssaultRaidTodayScheduleNotify(const AssaultRaidScheduleList& scheduleList);

	/// 레이드 게임 시작, 종료 공지를 받았다.
	virtual void onRecvAssaultRaid_Start_End_Notify(const AssaultRaidState& state);

	/// 나의 레이드 포인트를 받았다.
	virtual void onRecvAssaultRaidMyPoint(const UserChannelPoint& info);

	/// 기여포인트 보상을 받았다.
	virtual void onRecvAssaultRaidPointRewardOK(BYTE iRewardLevel, const std::vector<RewardInfo>& rewardList);
	virtual void onRecvAssaultRaidPointRewardFailed(BYTE iRewardLevel, eCompetitionEventResult result);
#endif

	/// 던전 레이드 스케줄 정보를 받았다.
	virtual void onRecvDungeonRaidScheduleInfoNotify(const DungeonRaidInfo& scheduleInfo);

	/// 던전 레이드 게임 시작, 종료 공지를 받았다.
	virtual void onRecvDungeonRaid_Start_End_Notify(const eRaidChannelGateState dungeonRaidstate);

	/// 나의 던전 레이드 포인트를 받았다.
	virtual void onRecvtDungeonRaidMyPoint(const int dungeonRaidPoint);

	//////////////////////////////////////////////////////////////////////////

#ifdef _PARTY_SYSTEM

	/// 파티 시스템, 파티를 가입하라는 요청
	virtual void onRecvPartyInviteRequest(PartyRequestInfo& requestInfo, const int masterServerNum, std::string& masterNickName);

	/// 파티 시스템, 파티 초대 요청 실패
	virtual void onRecvPartyInviteRequest_Failed(PartyRequestInfo& requestInfo, std::string& invitedNickName);

	/// 파티 초대에 대한 수락 실패
	virtual void onRecvPartyInviteAck_Failed(PartyRequestInfo& requestInfo, std::string& invitedNickName);

	/// 내가 소속되어있는 파티의 정보를 받음
	virtual void onRecvPartyInfo(PartyRequestInfo& requestInfo, InvitationPartyInfo& partyInfo);

	/// 내가 소속된 파티에 새로운 멤버가 들어옴
	virtual void onRecvParty_NewUserInfo(InvitationPartyUserInfo& newUserInfo);

	/// 내가 소속된 파티에 유저가 나감
	virtual void onRecvParty_LeaveUser(std::string& leaveUserNickName, ePartyLeaveType leaveType);

	/// 내가 소속된 파티에 마스터가 변경됨
	virtual void onRecvParty_SetMaster(std::string& masterNickName);

	/// 내가 파티에서 나가졌다
	virtual void onRecvParty_LeaveAck(ePartyLeaveType leaveType);

	/// 파티 게시글 등록 성공 실패여부
	virtual void onRecvPartyBoardAddRequest(const PartyRequestInfo& requestInfo);

	/// 파티 게시글 삭제 성공 실패 여부
	virtual void onRecvPartyBoardDelRequest(const PartyRequestInfo& requestInfo);

	/// 파티 게시글 목록 받음
	virtual void onRecvPartyBoardList(const int iCurPageIndex, const int iMaxPageIndex, std::vector<PartyBoardInfo>& vecPartyBoardList);

	/// 파티 게시글 목록 실패
	virtual void onRecvPartyBoardListFailed(const PartyRequestInfo& requestInfo);

	/// 파티 게시글 지원요청 성공
	virtual void onRecvPartyBoardJoin(const PartyRequestInfo& requestInfo, std::string& strMasterNickName);

	/// 파티 게시글 지원요청 실패
	virtual void onRecvPartyBoardJoinFailed(const PartyRequestInfo& requestInfo);

	/// 파티 게시글 지원자 목록보기( 파티글 작성한 유저가 보는 것 )
	virtual void onRecvPartyBoardRequestUserList( std::vector<InvitationPartyUserInfo>& vecPartyBoardUserList, const int iTotalPageIndex, const int iCurPageIndex );

	/// 파티 게시글 지원자 목록보기 실패
	virtual void onRecvPartyBoardRequestUserListFailed(const PartyRequestInfo& requestInfo);

	/// 파티 요청 목록에서 거절
	virtual void onRecvPartyBoardJoinRefusalAck(const PartyRequestInfo& requestInfo, std::string& strTargetNickName);

	/// 파티 게시글의 지원요청 창을 통하여 파티 가입에 성공(파티 가입 성공시 파티 지원 리스트 재갱신 위해 사용)
	virtual void onRecvPartyBoardJoinOK(const PartyRequestInfo& requestInfo);

	/// 유저가 선택한 파티 게시글의 파티원 목록보기
	virtual void onRecvPartyBoardJoinList( std::vector<InvitationPartyUserInfo>& vecPartyJoinUserList, const std::string& strMasterNickName );

	/// 유저가 선택한 파티 게시글의 파티원 목록보기 실패
	virtual void onRecvPartyBoardJoinListFailed( const PartyRequestInfo& requestInfo );

	/// 파티원의 정보가 변경됨을 알림
	virtual void onRecvPartyModifyUserInfo(InvitationPartyUserInfo& userInfo);

	/// 파티 시스템 TR,EXP 보너스 공지를 받았다.
	virtual void onRecvPartyBuffBonusNotify(const BuffBonusInfo& buffBonus);
#endif

	//////////////////////////////////////////////////////////////////////////

	/// 경쟁 이벤트 공지 알림
	virtual void onRecvCompetitionEventGameNotify(const bool bStartNotice, const int interval);

	/// 경쟁 이벤트 다음 게임에 대한 정보를 받음
	virtual void onRecvCompetitionEventNextGameInfo(OlympicGameInfo& gameInfo);

	/// 경쟁 이벤트 파티에 대한 유저의 정보 받음
	virtual void onRecvCompetitionEventPartyUserInfoOK(eEventPartyType partyType, const __int64& point, const __int64& accPoint);

	/// 경쟁 이벤트 파티에 대한 유저 정보 받기 실패
	virtual void onRecvCompetitionEventPartyUserInfoFailed(eCompetitionEventResult result);

	/// 경쟁 이벤트 일정이 더이상 없음
	virtual void onRecvCompetitionEventGameEmpty();

	/// 경쟁 이벤트 오늘의 일정
	virtual void onRecvCompetitionEventTodayGameInfo(const std::vector<OlympicGameInfo>& competionEventGameList);

	/// 경쟁 이벤트 파티에 가입 결과
	virtual void onRecvCompetitionEventPartyJoinOK(eEventPartyType partyType, std::vector<RewardInfo>& rewardList);

	/// 경쟁 이벤트 파티 가입 실패
	virtual void onRecvCompetitionEventPartyJoinFailed(eCompetitionEventResult result);

	/// 경쟁 이벤트 파티에 대한 정보 받음
	virtual void onRecvCompetitionEventPartyInfo(std::map<eEventPartyType, CompetitionPartyInfo>& partyInfo);

	/// 경쟁 이벤트 승리팀 보상을 받음
	virtual void onRecvCompetitionEventWinnerPartyRewardOK(std::vector<RewardInfo>& rewardList);

	/// 경쟁 이벤트 승리팀 보상 받기 실패
	virtual void onRecvCompetitionEventWinnerPartyRewardFailed(eCompetitionEventResult result);

	/// 경쟁 이벤트 아이템 기여 결과
	virtual void onRecvCompetitionEventPointAddUseItem(int iAddPoint);
	virtual void onRecvCompetitionEventPointAddUsePotionItem(int iAddPoint);
	virtual void onRecvCompetitionEventPointAddUseItemFailed(eCompetitionEvent_POINT_ADD_RESULT result);

	virtual void onRecvCompetitionEventPersonalPoint(int m_StepNum, int m_Point, bool isReward);
	virtual void onRecvCompetitionEventPersonalReward(int m_RefreshItemNum, bool isReward);

#ifdef _CHAOS_ZERO_
	/// 경쟁 이벤트 지역정보
	virtual void onRecvCompetitionEventTerritoryInfoOK(std::map<int, std::pair<eEventPartyType, int> > & territoryWinners, std::map<std::pair<int/*StageNum*/, eEventPartyType>, INT64 > & territoryTalesKnightsWinInfo);
	virtual void onRecvCompetitionEventTerritoryInfoFailed(eCompetitionEventResult result, int territoryNum);
#endif

#ifdef _OFFICIAL_COMPETITION_CHANNEL
	/// 채널 정보를 받았다. 주의 : room kind가 일치하는 것만 정보 업데이트!
	virtual void onRecvChannelInfo(const GAMECHANNEL::CHANNEL_INFO_MAP& info);

	/// 유저 포인트 정보를 받았다. 주의 : 정보 인덱스가 일치하는 것만 업데이트.
	virtual void onRecvUserPointInfo(eUserPointType pointType, const USER::UserPoint& pointInfo);
#endif


	/// 특정모드(ex)로얄럼블)에서 실제 카운팅 시작 요청에 대한 결과 받음
	virtual void onRecvTimeCountStartAck(const bool result, const short playTime, const byte countIndex);

	/// 특정모드(ex)로얄럼블)에서 카운팅이 끝났음을 알림
	virtual void onRecvTimeCountEndAck(const byte countIndex, const short playTime, const bool checkAlivePlayer, std::vector<unsigned int>& alivePlayerList);

#ifdef PROMOTION_SALE
	/// 매출 프로모션 아이템의 갯수 갱신
	virtual void onRecvPromotionItemCount();
#endif

#ifdef _SHU_SYSTEM_

	//!<--------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------
	// 슈 아이템 정보 
	// --------------------------------------------------------------------------------------------


	//!< 슈 아이템 정보를 갱신하였다..
	virtual void onRecvUpdateShuItemInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CUserShuItemInfo> & update_Info);

	//!< 특정 슈캐릭터(eCharacterShuKind)의 전용 아이템 정보를 갱신하였다.
	virtual void onRecvUpdateShuItemByCharacter(const eCharacterShuKind character,std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CUserShuItemInfo> & update_Info);

	//!< 특정 포지션의 모든 아이템 정보를 갱신하였다.
	virtual void onRecvUpdateShuItemByPosition(const SHU_ITEM_POSITION position,std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CUserShuItemInfo> & update_Info);

	//!< 슈 아이템 상태 정보를 갱신하였다.
	virtual void onRecvUpdateShuItemState(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::eItem_curr_state> & update_Info);


	// --------------------------------------------------------------------------------------------
	// 슈캐릭터 정보
	// --------------------------------------------------------------------------------------------


	//!< 슈 알아이템을 사용하여 슈캐릭터 정보를 생성하는데 성공하였다.
	virtual void onRecvCreateShuCharacterSucess(const SHU_SYSTEM::CTRShuItemID & eggItemID,const SHU_SYSTEM::CTRShuItemID & shuCharItemID);

	//!< 현재 선택된 슈캐릭터를 변경하였다.
	virtual void onRecvUpdateSelectCurrentShuCharacter(const SHU_SYSTEM::CTRShuItemID & itemID);

	//!< 슈 캐릭터 상태를 갱신하였다.
	virtual void onRecvShuCharStatusInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::ShuStatusInfo> & update_info);

	//!<  슈캐릭터 정보를 갱신하였다.
	virtual void onRecvUpdateShuCharacterInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CMyShuCharacterInfo> & update_Info);

	//!< 슈 캐릭터 아바타 정보를 갱신하였다
	virtual void onRecvUpdateShuAvatarInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::MyShuAvatarInfo> & update_Info);

	//!< 슈 캐릭터 아바타 정보를 변경하였다.
	virtual void onRecvChangeShuAvatarInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::MyShuAvatarInfo>& update_Info);

	//!< 슈 캐릭터명을 변경 하였다.
	virtual void onRecvChangeShuCharacterName(const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const std::string & name);

	//!< 슈 관리포인터를 사용하여 특정 액션을 취하였다.
	virtual void onRecvShuCharManagerAction(const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const eShuManagerActionType action,
											const std::map<eShuStatusType, int> & apply_value,const int remainMP);

	//!< 슈 캐릭터의 경험치를 감소시켜 아이템 보상을 완료하였다.
	virtual void onRecvSuccessShuCharGiftToThisPlayer(const SHU_SYSTEM::CTRShuItemID & from_ShuCharItemID,const int current_exp,const std::vector<RewardInfo> & reward_list);


	//!< 슈 캐릭터에게 특정 아이템을 사용하여 결과를 받았다.
	virtual void onRecvShuCharUseItemSuccess(const SHU_SYSTEM::CTRShuItemID & charItemID,const SHU_ITEM_POSITION useItemPosition,
		                                     const SHU_SYSTEM::CTRShuItemID & useItemID,const int useItemNumber,const int useCount);

	//!< 슈 캐릭터가 레벨 정보가 변경 되었다.
	virtual void onRcvShuCharLevelModify(const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const int preLevel,const int currLevel);

	// --------------------------------------------------------------------------------------------
	// 슈캐릭터를 이요한 탐색정보
	// --------------------------------------------------------------------------------------------

	//!< 현재 진행 중인 탐사 지역 정보를 갱신하였다.
	virtual void onRecvShuCharExploreZoneInfo(std::vector<BYTE/*zoneNumber*/> & zone_list);

	//!< 특정 탐사 지역의 탐사를 시작한다.
	virtual void onRecvShuCharExploreZone_Start(const BYTE zone_number,const SHU_SYSTEM::CTRShuItemID & shuCharItemID);

	//!< 특정 탐사 지역의 탐사를 중지하였다.
	virtual void onRecvShuCharExploreZone_Stop(const BYTE zone_number,const SHU_SYSTEM::CTRShuItemID & shuCharItemID);

	//!< 특정 탐사 지역의 보상을 받았다.(탐사 완료)
	virtual void onRecvShuCharExploreZone_Reward(const BYTE zone_number,const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const std::vector<RewardInfo> & reward_list);

	// --------------------------------------------------------------------------------------------
	// IN GAME SHU EVENT
	// --------------------------------------------------------------------------------------------

	//!< 게임 안에서 캐릭터 --> 슈 태그 액션을 시작했다..
	virtual void onRecvShuCharIngameTagAction_Start(const int nPlayerIndex,const int characterAvatarItemNum);

	//!< 게임 안에서 슈 --> 캐릭터 태그 액션을 종료하였다.
	virtual void onRecvShuCharIngameTagAction_End(const int nPlayerIndex,const SHU_SYSTEM::eIN_GAME_SHU_TAG_END_TYPE end_type);
	
	//!< 게임 안아세 로컬유저의 슈 태그 액션 시작을 실패하였다.
	virtual void onRecvThisPlayerShuCharIngameTagAction_Start_failed();

	//!< 게임방 안에서 특정 유저의 슈 캐릭터 정보가 변경되었다.
	virtual void onRecvPlayerShuCharInfoModify(const int nPlayerIndex,const SHU_SYSTEM::CPlayerShuCharacterInfo & updateInfo);
	//!<--------------------------------------------------------------------------------------------

#endif // _SHU_SYSTEM_

	//////////////////////////////////////////////////////////////////////////
#ifdef _DRAWING_OF_THE_MONTH

	//!< 이달의 뽑기 정보를 받았다.
	virtual void onRecvMonthlyGotchaSystemInfo(eDOMResult result);

	//!< 이달의 뽑기 나의 정보를 받았다.
	virtual void onRecvMonthlyGotchaSystemUserInfo(eDOMResult result);

	//!< 이달의 뽑기 쿠폰을 사용했다.
	virtual void onRecvMonthlyGotchaSystemUseCoupon(eDOMResult result, int id, std::vector<DOM::DOM_ITEM>& resultItem);

	//!< 이달의 뽑기 확정 보상을 받았다.
	virtual void onRecvMonthlyGotchaSystemFixReward(eDOMResult result, int id, int resultItem);

#endif
	//////////////////////////////////////////////////////////////////////////
	/// 창고 처리 결과를 받았다.
	virtual void onRecvStorageResult();

	/// 보관함에 아이템 저장 요청 결과를 받았다.
	virtual void onRecvStorage_SaveItem_Result(eStorage_Request_Result result);

	/// 보관함에 있는 아이템 선물 요청 결과를 받았다.
	virtual void onRecvStorage_Gift_Item_Result();

	/// 창고에 있는 아이템 마이룸에 받기 요청 결과를 받았다.
	virtual void onRecvStorage_Get_Item_Result(std::vector<int> item);

	/// 정액권 사용 기간 만료를 통보 받았다.
	virtual void onRecvFreePass_Expire_Notify(const UserFreePassDesc& fDesc);
	virtual void onRecvFreePass_Expire_Notify();

	/// 정액권 사용 시작 통보 받았다.
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
	// 길드 매치 점령전
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///< 길드 점령전 길드 획득 포인트 및 오늘 참여 횟수 응답
	virtual void onRecvGuildMatchArea_Point_Info( int iOneDayJoinCount, std::map<eOCCUPATION_AREA_TYPE, int>& mapGuildMatchAreaInfo ) ;
	///< 길드 점령전 길드 획득 포인트 및 오늘 참여 횟수 응답 실패
	virtual void onRecvGuildMatchArea_Point_Info_Failed( GuildMatchRequestInfo& requestInfo );
	///< 길드 점령전 지역별 랭킹 정보 응답
	virtual void onRecvGuildMatchOccupation_Area_Rank_Info( bool bRequestByGuild, std::map<eOCCUPATION_AREA_TYPE, std::map<int, GuildMatchOccupationRank_Info>>& list );
	///< 길드 점령전 지역별 갱킹 정보 응답 실패
	virtual void onRecvGuildMatchOccupation_Area_Rank_Info_Failed( GuildMatchRequestInfo& requestInfo );
	///< 길드 점령전 종합 랭킹 정보 응답
	virtual void onRecvGuildMatchOccupation_Rank_Range( std::map<int, GuildMatchOccupationRank_Info>& list, const eGUILDMATCH_OCCUPATION_RANK_SEARCH_TYPE eSearchType );
	///< 길드 점령전 종합 랭킹 정보 응답 실패
	virtual void onRecvGuildMatchOccupation_Rank_Range_Failed( GuildMatchRequestInfo& requestInfo );
	///< 길드 점령전 스케쥴이 오픈 됨을 알려줌
	virtual void onRecvGuildMatchOccupation_OpenSchedule();
	///< 길드 점령전 핫플레이스 정보 응답
	virtual void onRecvGuildMatchOccupation_HotPlace_Info( std::map<eOCCUPATION_AREA_TYPE, std::map<byte, RewardInfo>>& list );
	///< 길드 점령전 핫플레이스 정보 응답 실패
	virtual void onRecvGuildMatchOccupation_HotPlace_Info_Failed( GuildMatchRequestInfo& requestInfo );

	// 기차놀이
	virtual void OnRecvTrainRun_team(const std::vector<int> (&team)[eTeam_MAX]);
	virtual void OnRecvTrainRun_game_timer(GAMELOGIC::eTrainRunTimerID timer);
	virtual void OnRecvTrainRun_KillLeaderAck(GAMELOGIC::eTRAINRUN_ACK ack);
	virtual void OnRecvTrainRun_Suicide();
	virtual void OnRecvTrainRun_ReviveAck(GAMELOGIC::eTRAINRUN_ACK ack, int iUserCount);

#ifdef _KNIGHT_FLOWERS_
	// 공원 칼뽑기
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

	// 방장 버프 메세지
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
	
	// 팜 크레프트
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


