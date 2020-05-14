/* ---------------------------------------------------------------
*
* Copyright 2008 by Rhaon Ent.
*
* TRCoupleSystem.h
*
* 2008. 2. Im Cheolsu.
* 
* ---------------------------------------------------------------
*/


#pragma once

#include "park/TRCoupleRequestDlg.h"
#include "park/TRDivinationCardBoardDlg.h"
#include "gameui/YesNoDialog.h"

enum
{
	COUPLE_RING_GRADE_FIRST = 1,  // 2일
	COUPLE_RING_GRADE_SECOND = 2, // 22일
	COUPLE_RING_GRADE_THIRD = 3,  // 50일
	COUPLE_RING_GRADE_FOURTH = 4, // 100일
	COUPLE_RING_GRADE_FIFTH = 5,  // 200일
	COUPLE_RING_GRADE_SIXTH = 6,  // 300일
	COUPLE_RING_GRADE_SEVEN = 7,  // 1년(한국 기준)
	COUPLE_RING_GRADE_EIGHTH = 8,
};

class CTRCoupleSystem
{

public:	
	CTRCoupleSystem();
	virtual ~CTRCoupleSystem();

	static CTRCoupleSystem &getInstacne();

	void closeCoupleSysUI();     // 커플 시스템의 ui 닫기
	void closeCoupleSysParkUI(); // 공원 전용 ui 닫기
	void showProposeDlg();   
	void checkCoupleMsg();     // 게임중, 가이드중, 미니게임중, 싱글플레이에서 받은 커플 메세지를 처리 끝난 후에 처리

    void onProcessMeLogOff();  // 내가 로그오프했을 때 상대에게 로그오프로 거절한다고 알림

	bool _checkCouplePropose(int & iBuyItemNum);
	void onReadyCouplePropose();		 // 상대에게 프로포즈하기 하기 위한 준비 작업
	void onReadyCouplePropose_Meeting(); // 상대에게 프로포즈하기 하기 위한 준비 작업(미팅 컨텐츠)

	void onChangeCoupleRingYesNo(int coupleLevel);
	void onChangeCoupleRing();   // 커플링 교체
	void onChangeCoupleName();   // 커플 이름 교체
	void onRemoveCoupleRing();   // 커플 끊기
	void onGiftToMyCouple();	 // 커플에서 선물
 
	void onLoginProcess();       // 로그인했을 때 커플 메세지 처리(오늘이 커플 22일째일때 커플링을 바꿀수 있다고 알림)

	void showBuyDialogJewelBoxItem();  // 보석상자구매 창을 띄운다.
	//void showChangeCoupleRingDlg();    // 커플 교체창을 띄운다.
	void showChangeCoupleNameDlg();    // 커플 이름 교체 창을 띄운다.

	void requestCoupleRemoveCouple();  // 서버에 커플 끊는다고 알림

	int getMyCoupleDay();              // 나의 커플Day를 얻는다.(커플이 아니라면 0을 얻는다.)
	int getMyCoupleLevel();              // 나의 커플Level를 얻는다.(커플이 아니라면 0을 얻는다.)
	bool isHaveCouple();               // 내 커플을 가지고 있는지.

	void setCurWedding(bool bSet) { m_bCurWedding = bSet; }
	bool isCurWedding() { return m_bCurWedding; }

	bool checkNextJewelBox(int &jewelBoxItemNum);						//현재 레벨에서 레벨업에 필요한 보석함 아이템 번호를 반환
	bool checkKeepNextJewelBox(int &jewelBoxItemNum);						//가지고 있는 jewelBoxItem 중에서 다음 레벨업에 필요한 보석함이 있는지 체크, 해당 보석함 아이템 번호를 반환

	bool checkRingRequirementDay(CoupleInfo coupleInfo, int &nextLevel);	// 반지의 아이템번호와 CoupleInfo를 넣으면 해당 커플의 반지가 업그레이드가 가능한지 bool로 반환 
	bool checkRingRequirementDay(CoupleInfo coupleInfo);
	time_type checkMyExpRingMinuteTime(CoupleInfo coupleInfo);			// CoupleInfo를 넣으면 해당 커플의 채워진 반지의 날짜를 반환한다.

	bool isBuyCoupleSystem(){ return m_bBuyJewelBoxByCoupleSystem; }  // 보석 구매창에 옵션을 넣기위함 함수(구매창 아이템 이미지에 설명창을 발생)

	void checkChallengeSubjeck(int ringNum);   // 커플 교체 도전과제 체크

	void setCoupleDataRecvLimit(bool bLimit){ m_bRecvLimit = bLimit; }

	bool checkAbleChangeCoupleRing(int changeCoupleLevel);	// 가지고 있는 커플보석 상자로 교체 가능한지 체크

	int getNextChangeCoupleLevel(int nowcoupleRingLevel);	// 커플링레벨을 인자값으로 하여 다음 단계의 커플링 아이템 번호를 반환

	void setNeedUpdate() {m_bNeedUpdate = true;}
	void checkNeedUpdate();
	void updateRingItem(int ringItemNum);

	/// 상대에게 프로포즈한다.
	void community_requestPropose(const std::string & strToNickname, const std::string & strCoupleName, const std::string & strCoupleDesc, const int iJewelBoxNum, const bool bMeetingDependency);

	/// 상대로부터 프로포즈 받았다.
	void community_onRecvCoupleProposeRequest(const std::string & strFromNickname, const std::string & strCoupleName, const std::string & strCoupleDesc, const int iJewelBoxNum, const bool bMeetingDependency);

	/// 프로포즈에 대한 승인여부를 받았다.
	void community_onRecvCoupleProposeResponse(const std::string & strFromNickname, const bool bOK, const eCoupleProposeReject eReason, const int iCoupleNum, const int iCoupleRingNum);

	/// 상대로부터 커플링을 변경했다 통지를 받았다.
	void community_onRecvCoupleRingChanged(const std::string & strFromNickname, const int iCoupleRingNum);

	/// 상대로부터 커플명을 변경했다 통지를 받았다.
	void community_onRecvCoupleNameChanged(const std::string & strFromNickname, const std::string & strCoupleName);

	/// 상대로부터 커플소개가 변경했다 통지를 받았다.
	void community_onRecvCoupleDescModify(const std::string & strFromNickname);

	/// 커플 생성요청에 대한 응답을 받았다.
	void onRecvCoupleCreateCoupleInfo(eServerResult eResult, const int iCoupleNum, const int iCoupleRingNum);

	/// 프로포즈 정보를 체크한다.
	void onRecvCoupleCheckProposeInfo(eServerResult eResult, const bool bMeetingDependency);

	/// 커플 삭제요청에 대한 응답을 받았다.
	void onRecvCoupleRemoveCoupleInfo(std::string strMateName);

	/// 프로포즈 정보 초기화에 성공했다.
	void onRecvCoupleInitRecvProposeInfoOK();

	//! 나의 커플 정보를 갱신 받았다.
	void onRecvCoupleUpdateCoupleInfo(const CoupleInfo & conpleInfo);

	/// 상대로부터 커플을 끊겠다는 통지를 받았다.
	void community_onRecvCoupleSayGoodBye(const std::string & strFromNickname);

	//! 커플링 교체에 성공했다.
	void onRecvCoupleChangeCoupleRingOK(const CoupleInfo & OrgCoupleInfo ,const CoupleInfo & ChangeCoupleInfo);

	//! 커플링 교체에 실패했다.
	void onRecvCoupleChangeCoupleRingFailed(eCoupleChangeCoupleRing failedReason);

	/// 커플이름 변경 처리가 성공했다.
	void onRecvCoupleModifyCoupleNameResult(eServerResult eResult, std::string strCoupleName);	

	/// 서버에서 변경된 아비타 정보를 받는다.
	void onRecvAvatarInfo(const AdvancedAvatarInfo & advancedAvatarInfo);

	/// 서버에서 세팅이 완료되었다고 받는다.
	void onRecvMyRoomSetCharacterSetting();

	/// 내 커플에 의해 버프를 받았다.
	void onRecvDivinationCoupleExAbilitiesResult(const ExtraAbilityInfo & appliedExtraAbilities, std::string strDivinationDesc);



private:
	void onResetCoupleInfo();   // 커플 정보를 초기화

	void onYesCoupleConsent();  // 프로포즈를 받았을때 yes처리
	void onNoCoupleConsent();   // 프로포즈를 받았을때 no처리

	void showCoupleProposeResponse(bool bOk, eCoupleProposeReject eReason); // 프로포즈의 응답ui를 보여준다.
	bool checkCoupleChangeNotify();        // 내 커플 일수로 커플링을 교체할시기인지 체크

	void showBuyDialogCoupleNameChangeItem();
	void showGiftDialogSendGiftItem();

	bool checkCoupleRecvNoLimit();


private:
	CTRCoupleRequestDlg m_proposeDlg;                               // 프로포즈 요창Dlg
	CTRCoupleNameChangeDlg m_coupleNameChangeDlg;				    // 커플 이름 교체Dlg
	CTRCoupleSuccessDlg m_coupleSuccDlg;                            // 프로포즈 성공Dlg
	CTRCoupleNameChangeSuccessDlg m_coupleNameChangeSuccDlg;        // 커플 이름 교체 성공 Dlg
	CTRCoupleRingChangeResultDlg m_coupleRingChangeResultDlg;       // 커플링 교체 성공Dlg
	CTRDivinationResultDlg m_resultCard;                            // 커플운세를 받았을 때Dlg
	CYesNoDialogEx<CTRCoupleSystem> m_yesNoDlg;                     // 커플 시스템에 사용되는 yesNoDlg
	COKDialog m_OKDlg;												// 커플 시스템에 사용되는 OkDlg

	// 커플 처리에 필요한 변수들
	string m_coupleName;
	string m_coupleDes;
	string m_fromNickname;
	int m_iCoupleRingNum;											// 현재 레벨에 해당되는 커플링 번호
	int m_iOrgCoupleRingNum; //!< 기존커플링 번호
	int m_iJewelBoxNum;
	bool m_bMeetingDependency;	// 미팅시스템을 이용하여 커플신청을 했는가?

	string m_coupleDivination;
	ExtraAbilityInfo m_appliedExtraAbility;
	

	///////////////////////////

	bool m_bProposeResponse;        // 프로포즈 보낸 응답
	eCoupleProposeReject m_eReason; // 프로포즈 거절 사유

	bool m_bCurProposeSend;			// 프로포즈 보낸 응답들 받은 상태
	bool m_bCurProposeRecv;			// 프로포즈 받은 상태
	bool m_bCoupleBreak;			// 상대로 부터 프로포즈를 끊어 졌다고 알림을 받음
	bool m_bCoupleRingChangeRecv;   // 상대로 부터 커플링이 교체되었다고 알림을 받음
	bool m_bCoupleNameChangeRecv;   // 서버에서 커플 정보(커플이름)가 바뀌었다고 알림을 받음
	bool m_bCoupleDescChangeRecv;   // 상대로 부터 커플 정보가 변경되었다는 알림을 받음
	bool m_bCoupleDivinationRecv;   // 상대가 커플 점을 봤다고 알림을 받음

	bool m_bChangeMyAvatar;         // 현재 내 아바타 변경중이다.

	bool m_bBuyJewelBoxByCoupleSystem;  // 커플 신청중에 보석상자를 구매중인가.
	bool m_bChangeCoupleRing;

	///////////////////////////////////
	bool m_bRecvLimit;               // 커플 정보를 받았을때 정보를 제한한다.

	///////////////////////////////////
	map<int, int> m_mapRingDayGradeTable;

	// 결혼 중인가
	bool m_bCurWedding;
	bool m_bCoupleRingnumDirty;
	bool m_bNeedUpdate = false;
	
};