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
	COUPLE_RING_GRADE_FIRST = 1,  // 2��
	COUPLE_RING_GRADE_SECOND = 2, // 22��
	COUPLE_RING_GRADE_THIRD = 3,  // 50��
	COUPLE_RING_GRADE_FOURTH = 4, // 100��
	COUPLE_RING_GRADE_FIFTH = 5,  // 200��
	COUPLE_RING_GRADE_SIXTH = 6,  // 300��
	COUPLE_RING_GRADE_SEVEN = 7,  // 1��(�ѱ� ����)
	COUPLE_RING_GRADE_EIGHTH = 8,
};

class CTRCoupleSystem
{

public:	
	CTRCoupleSystem();
	virtual ~CTRCoupleSystem();

	static CTRCoupleSystem &getInstacne();

	void closeCoupleSysUI();     // Ŀ�� �ý����� ui �ݱ�
	void closeCoupleSysParkUI(); // ���� ���� ui �ݱ�
	void showProposeDlg();   
	void checkCoupleMsg();     // ������, ���̵���, �̴ϰ�����, �̱��÷��̿��� ���� Ŀ�� �޼����� ó�� ���� �Ŀ� ó��

    void onProcessMeLogOff();  // ���� �α׿������� �� ��뿡�� �α׿����� �����Ѵٰ� �˸�

	bool _checkCouplePropose(int & iBuyItemNum);
	void onReadyCouplePropose();		 // ��뿡�� ���������ϱ� �ϱ� ���� �غ� �۾�
	void onReadyCouplePropose_Meeting(); // ��뿡�� ���������ϱ� �ϱ� ���� �غ� �۾�(���� ������)

	void onChangeCoupleRingYesNo(int coupleLevel);
	void onChangeCoupleRing();   // Ŀ�ø� ��ü
	void onChangeCoupleName();   // Ŀ�� �̸� ��ü
	void onRemoveCoupleRing();   // Ŀ�� ����
	void onGiftToMyCouple();	 // Ŀ�ÿ��� ����
 
	void onLoginProcess();       // �α������� �� Ŀ�� �޼��� ó��(������ Ŀ�� 22��°�϶� Ŀ�ø��� �ٲܼ� �ִٰ� �˸�)

	void showBuyDialogJewelBoxItem();  // �������ڱ��� â�� ����.
	//void showChangeCoupleRingDlg();    // Ŀ�� ��üâ�� ����.
	void showChangeCoupleNameDlg();    // Ŀ�� �̸� ��ü â�� ����.

	void requestCoupleRemoveCouple();  // ������ Ŀ�� ���´ٰ� �˸�

	int getMyCoupleDay();              // ���� Ŀ��Day�� ��´�.(Ŀ���� �ƴ϶�� 0�� ��´�.)
	int getMyCoupleLevel();              // ���� Ŀ��Level�� ��´�.(Ŀ���� �ƴ϶�� 0�� ��´�.)
	bool isHaveCouple();               // �� Ŀ���� ������ �ִ���.

	void setCurWedding(bool bSet) { m_bCurWedding = bSet; }
	bool isCurWedding() { return m_bCurWedding; }

	bool checkNextJewelBox(int &jewelBoxItemNum);						//���� �������� �������� �ʿ��� ������ ������ ��ȣ�� ��ȯ
	bool checkKeepNextJewelBox(int &jewelBoxItemNum);						//������ �ִ� jewelBoxItem �߿��� ���� �������� �ʿ��� �������� �ִ��� üũ, �ش� ������ ������ ��ȣ�� ��ȯ

	bool checkRingRequirementDay(CoupleInfo coupleInfo, int &nextLevel);	// ������ �����۹�ȣ�� CoupleInfo�� ������ �ش� Ŀ���� ������ ���׷��̵尡 �������� bool�� ��ȯ 
	bool checkRingRequirementDay(CoupleInfo coupleInfo);
	time_type checkMyExpRingMinuteTime(CoupleInfo coupleInfo);			// CoupleInfo�� ������ �ش� Ŀ���� ä���� ������ ��¥�� ��ȯ�Ѵ�.

	bool isBuyCoupleSystem(){ return m_bBuyJewelBoxByCoupleSystem; }  // ���� ����â�� �ɼ��� �ֱ����� �Լ�(����â ������ �̹����� ����â�� �߻�)

	void checkChallengeSubjeck(int ringNum);   // Ŀ�� ��ü �������� üũ

	void setCoupleDataRecvLimit(bool bLimit){ m_bRecvLimit = bLimit; }

	bool checkAbleChangeCoupleRing(int changeCoupleLevel);	// ������ �ִ� Ŀ�ú��� ���ڷ� ��ü �������� üũ

	int getNextChangeCoupleLevel(int nowcoupleRingLevel);	// Ŀ�ø������� ���ڰ����� �Ͽ� ���� �ܰ��� Ŀ�ø� ������ ��ȣ�� ��ȯ

	void setNeedUpdate() {m_bNeedUpdate = true;}
	void checkNeedUpdate();
	void updateRingItem(int ringItemNum);

	/// ��뿡�� ���������Ѵ�.
	void community_requestPropose(const std::string & strToNickname, const std::string & strCoupleName, const std::string & strCoupleDesc, const int iJewelBoxNum, const bool bMeetingDependency);

	/// ���κ��� �������� �޾Ҵ�.
	void community_onRecvCoupleProposeRequest(const std::string & strFromNickname, const std::string & strCoupleName, const std::string & strCoupleDesc, const int iJewelBoxNum, const bool bMeetingDependency);

	/// ������� ���� ���ο��θ� �޾Ҵ�.
	void community_onRecvCoupleProposeResponse(const std::string & strFromNickname, const bool bOK, const eCoupleProposeReject eReason, const int iCoupleNum, const int iCoupleRingNum);

	/// ���κ��� Ŀ�ø��� �����ߴ� ������ �޾Ҵ�.
	void community_onRecvCoupleRingChanged(const std::string & strFromNickname, const int iCoupleRingNum);

	/// ���κ��� Ŀ�ø��� �����ߴ� ������ �޾Ҵ�.
	void community_onRecvCoupleNameChanged(const std::string & strFromNickname, const std::string & strCoupleName);

	/// ���κ��� Ŀ�üҰ��� �����ߴ� ������ �޾Ҵ�.
	void community_onRecvCoupleDescModify(const std::string & strFromNickname);

	/// Ŀ�� ������û�� ���� ������ �޾Ҵ�.
	void onRecvCoupleCreateCoupleInfo(eServerResult eResult, const int iCoupleNum, const int iCoupleRingNum);

	/// �������� ������ üũ�Ѵ�.
	void onRecvCoupleCheckProposeInfo(eServerResult eResult, const bool bMeetingDependency);

	/// Ŀ�� ������û�� ���� ������ �޾Ҵ�.
	void onRecvCoupleRemoveCoupleInfo(std::string strMateName);

	/// �������� ���� �ʱ�ȭ�� �����ߴ�.
	void onRecvCoupleInitRecvProposeInfoOK();

	//! ���� Ŀ�� ������ ���� �޾Ҵ�.
	void onRecvCoupleUpdateCoupleInfo(const CoupleInfo & conpleInfo);

	/// ���κ��� Ŀ���� ���ڴٴ� ������ �޾Ҵ�.
	void community_onRecvCoupleSayGoodBye(const std::string & strFromNickname);

	//! Ŀ�ø� ��ü�� �����ߴ�.
	void onRecvCoupleChangeCoupleRingOK(const CoupleInfo & OrgCoupleInfo ,const CoupleInfo & ChangeCoupleInfo);

	//! Ŀ�ø� ��ü�� �����ߴ�.
	void onRecvCoupleChangeCoupleRingFailed(eCoupleChangeCoupleRing failedReason);

	/// Ŀ���̸� ���� ó���� �����ߴ�.
	void onRecvCoupleModifyCoupleNameResult(eServerResult eResult, std::string strCoupleName);	

	/// �������� ����� �ƺ�Ÿ ������ �޴´�.
	void onRecvAvatarInfo(const AdvancedAvatarInfo & advancedAvatarInfo);

	/// �������� ������ �Ϸ�Ǿ��ٰ� �޴´�.
	void onRecvMyRoomSetCharacterSetting();

	/// �� Ŀ�ÿ� ���� ������ �޾Ҵ�.
	void onRecvDivinationCoupleExAbilitiesResult(const ExtraAbilityInfo & appliedExtraAbilities, std::string strDivinationDesc);



private:
	void onResetCoupleInfo();   // Ŀ�� ������ �ʱ�ȭ

	void onYesCoupleConsent();  // ������� �޾����� yesó��
	void onNoCoupleConsent();   // ������� �޾����� noó��

	void showCoupleProposeResponse(bool bOk, eCoupleProposeReject eReason); // ���������� ����ui�� �����ش�.
	bool checkCoupleChangeNotify();        // �� Ŀ�� �ϼ��� Ŀ�ø��� ��ü�ҽñ����� üũ

	void showBuyDialogCoupleNameChangeItem();
	void showGiftDialogSendGiftItem();

	bool checkCoupleRecvNoLimit();


private:
	CTRCoupleRequestDlg m_proposeDlg;                               // �������� ��âDlg
	CTRCoupleNameChangeDlg m_coupleNameChangeDlg;				    // Ŀ�� �̸� ��üDlg
	CTRCoupleSuccessDlg m_coupleSuccDlg;                            // �������� ����Dlg
	CTRCoupleNameChangeSuccessDlg m_coupleNameChangeSuccDlg;        // Ŀ�� �̸� ��ü ���� Dlg
	CTRCoupleRingChangeResultDlg m_coupleRingChangeResultDlg;       // Ŀ�ø� ��ü ����Dlg
	CTRDivinationResultDlg m_resultCard;                            // Ŀ�ÿ�� �޾��� ��Dlg
	CYesNoDialogEx<CTRCoupleSystem> m_yesNoDlg;                     // Ŀ�� �ý��ۿ� ���Ǵ� yesNoDlg
	COKDialog m_OKDlg;												// Ŀ�� �ý��ۿ� ���Ǵ� OkDlg

	// Ŀ�� ó���� �ʿ��� ������
	string m_coupleName;
	string m_coupleDes;
	string m_fromNickname;
	int m_iCoupleRingNum;											// ���� ������ �ش�Ǵ� Ŀ�ø� ��ȣ
	int m_iOrgCoupleRingNum; //!< ����Ŀ�ø� ��ȣ
	int m_iJewelBoxNum;
	bool m_bMeetingDependency;	// ���ýý����� �̿��Ͽ� Ŀ�ý�û�� �ߴ°�?

	string m_coupleDivination;
	ExtraAbilityInfo m_appliedExtraAbility;
	

	///////////////////////////

	bool m_bProposeResponse;        // �������� ���� ����
	eCoupleProposeReject m_eReason; // �������� ���� ����

	bool m_bCurProposeSend;			// �������� ���� ����� ���� ����
	bool m_bCurProposeRecv;			// �������� ���� ����
	bool m_bCoupleBreak;			// ���� ���� ������� ���� ���ٰ� �˸��� ����
	bool m_bCoupleRingChangeRecv;   // ���� ���� Ŀ�ø��� ��ü�Ǿ��ٰ� �˸��� ����
	bool m_bCoupleNameChangeRecv;   // �������� Ŀ�� ����(Ŀ���̸�)�� �ٲ���ٰ� �˸��� ����
	bool m_bCoupleDescChangeRecv;   // ���� ���� Ŀ�� ������ ����Ǿ��ٴ� �˸��� ����
	bool m_bCoupleDivinationRecv;   // ��밡 Ŀ�� ���� �ôٰ� �˸��� ����

	bool m_bChangeMyAvatar;         // ���� �� �ƹ�Ÿ �������̴�.

	bool m_bBuyJewelBoxByCoupleSystem;  // Ŀ�� ��û�߿� �������ڸ� �������ΰ�.
	bool m_bChangeCoupleRing;

	///////////////////////////////////
	bool m_bRecvLimit;               // Ŀ�� ������ �޾����� ������ �����Ѵ�.

	///////////////////////////////////
	map<int, int> m_mapRingDayGradeTable;

	// ��ȥ ���ΰ�
	bool m_bCurWedding;
	bool m_bCoupleRingnumDirty;
	bool m_bNeedUpdate = false;
	
};