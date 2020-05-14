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
	CGUIDialog		*m_pDlg;		//!< ���̽� ���̾�α�
	CGUIComboBoxDropList	*m_pUserList;	//!< Ŀ���� ���� ģ�� ����Ʈ ��Ʈ��
	CGUIEditCtrl			*m_pCoupleNameCtrl;	//!< Ŀ�� �̸� ��Ʈ��
	CGUIEditCtrl			*m_pCoupleIntroCtrl;//!< Ŀ�� ���� ��Ʈ��

	CYesNoDialogEx<CTRCoupleRequestDlg> m_yesNoDlg;
	COKDialog m_OKDlg;

	string m_toNickName;
	string m_coupleName;
	string m_coupleDesc;

	int m_jewelBoxItemNum;
	bool m_bMeetingDependency;
};



// Ŀ�� ���� ���̾�α�
class CTRCoupleSuccessDlg : public COkDialogEx
{
public:
	CTRCoupleSuccessDlg();
	virtual ~CTRCoupleSuccessDlg();

	virtual void showDialog(int boxItem, int ringItem);
private:

};


// Ŀ�� �̸� ��ü ��û ���̾�α�
class CTRCoupleNameChangeDlg : public CYesNoDialog
{
public:
	CTRCoupleNameChangeDlg();
	virtual ~CTRCoupleNameChangeDlg(){}

	//���̾�αװ� ������
	virtual void onShowDialog();

	//���̾�αװ� �ݱ��
	virtual void onCloseDialog();

	//���� ��������
	virtual void onYes();

	//�ƴϿ��� ��������
	virtual void onNo();

	void onRecvCoupleModifyCoupleNameResultFailed(eServerResult eResult);

private:
	bool checkChangeCoupleName(string coupleName);
	void resetInput();

private:
	COKDialog m_OKDlg;
};

// Ŀ�ø� ���� ���� ���̾�α�
class CTRCoupleNameChangeSuccessDlg : public COKDialog
{
public:
	CTRCoupleNameChangeSuccessDlg();
	virtual ~CTRCoupleNameChangeSuccessDlg();

	virtual void showDialog(string message);
	void onRecvCoupleModifyCoupleNameResultFailed(eServerResult eResult);
};


// Ŀ�ø� ���� �˸� ���̾�α�
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

