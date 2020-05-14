/* ---------------------------------------------------------------
*
* Copyright 2008 by Rhaon Ent.
*
* TRCoupleRequestDlg.h
*
* 2008. 1. Im Cheolsu.
* 
* ---------------------------------------------------------------
*/


#pragma once

#include "gameui/YesNoDialog.h"

class CGUIItemImageCtrl;

class CTRCoupleRequestDlg : public CCommandTarget
{

public:	
	CTRCoupleRequestDlg();
	virtual ~CTRCoupleRequestDlg();

	void showDialog(int jewelBoxItemNum, const bool bMeetingSystem = false);
	void closeDialog();

	void closeOKDialog();

	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID);
	virtual bool onKeyDown(WPARAM wParam);

	bool isVisible();

	void onRecvCoupleCheckProposeInfo(eServerResult eResult, const bool bMeetingDependency);

private:
	void sendCoupleRequest();

private:
	CGUIDialog		*m_pDlg;		//!< 베이스 다이얼로그
	CGUIComboBoxDropList	*m_pUserList;	//!< 커플을 맺을 친구 리스트 컨트롤
	CGUIEditCtrl			*m_pCoupleNameCtrl;	//!< 커플 이름 컨트롤
	CGUIEditCtrl			*m_pCoupleIntroCtrl;//!< 커플 설명 컨트롤

	CYesNoDialogEx<CTRCoupleRequestDlg> m_yesNoDlg;
	COKDialog m_OKDlg;

	string m_toNickName;
	string m_coupleName;
	string m_coupleDesc;

	int m_jewelBoxItemNum;
	bool m_bMeetingDependency;
};



// 커플 성공 다이얼로그
class CTRCoupleSuccessDlg : public COkDialogEx
{
public:
	CTRCoupleSuccessDlg();
	virtual ~CTRCoupleSuccessDlg();

	virtual void showDialog(int boxItem, int ringItem);
private:

};


// 커플 이름 교체 요청 다이얼로그
class CTRCoupleNameChangeDlg : public CYesNoDialog
{
public:
	CTRCoupleNameChangeDlg();
	virtual ~CTRCoupleNameChangeDlg(){}

	//다이얼로그가 열릴때
	virtual void onShowDialog();

	//닫이얼로그가 닫길깨
	virtual void onCloseDialog();

	//예를 눌렸을대
	virtual void onYes();

	//아니오를 눌렸을때
	virtual void onNo();

	void onRecvCoupleModifyCoupleNameResultFailed(eServerResult eResult);

private:
	bool checkChangeCoupleName(string coupleName);
	void resetInput();

private:
	COKDialog m_OKDlg;
};

// 커플명 변경 성공 다이얼로그
class CTRCoupleNameChangeSuccessDlg : public COKDialog
{
public:
	CTRCoupleNameChangeSuccessDlg();
	virtual ~CTRCoupleNameChangeSuccessDlg();

	virtual void showDialog(string message);
	void onRecvCoupleModifyCoupleNameResultFailed(eServerResult eResult);
};


// 커플링 변경 알림 다이얼로그
class CTRCoupleRingChangeResultDlg : public COKDialog
{
public:	
	CTRCoupleRingChangeResultDlg(){}
	virtual ~CTRCoupleRingChangeResultDlg(){}

	virtual void showDialog(int OrgRingItemNum,int ChangeRingItemNum);

private:
	void _showChangeRingDialog(int ringItemNum);
	void _showAddItemChangeRingDialog(int OrgRingItemNum,int ChangeRingItemNum);
};

