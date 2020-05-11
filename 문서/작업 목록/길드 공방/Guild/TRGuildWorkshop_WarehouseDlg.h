/* ---------------------------------------------------------------
 *
 * Copyright 2019 by Rhaon Ent.
 *
 * TRGuildWorkshop_WarehouseDlg.h
 *
 * 2019. 12. Han Younho
 *
 * ---------------------------------------------------------------
 */

#pragma once

#include "gameui/TRUserInterface.h"
#include "gameui/YesNoDialog.h"

////////////////////////////////////////////////////////////////////////////////////
// � TR â�� ���̾�α�
class CTRGuildWorkshop_WarehouseDlg : public CTRCommandTarget
{
public:
	CTRGuildWorkshop_WarehouseDlg();
	virtual ~CTRGuildWorkshop_WarehouseDlg();

public:
	bool isVisible() const;

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

public:
	void showDialog();
	void closeDialog();

public:
	// ��� � TR ��û ����
	void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR);
	// ��� � TR ���ڿ� ����
	void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR);
	// � TR â�� Ȯ������ ��û ����
	void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue);
	// ������ ����Ʈ�� ��û ����
	void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList);

private:
	void _setManage();
	void _setInvestorList();
	void _setInvestorListPiece();

private:
	void _setPage(bool bInit = false);

private:
	void _setInvestorListVisible(bool b);	// ������ ����Ʈ Ȱ��ȭ ����
	void _setInvestorListByPage(int page);	// ������ ����Ʈ�� �������� ���� ����

private:
	bool _cheackJoinWithin7Days(time_type joinDate);	// �������� 7�� �̳����� �˻�

private:
	void _hideInvestButton();	// ���� ��ư(���� ��Ʈ�� ����) ��Ȱ��ȭ

private:
	void _yesnoDialogPopup();
	void _operationalTRInvestment();	// � TR â�� Ȯ��

private:
	void _setButtonChecked(const std::string& name, bool b);
	void _setStaticText(CGUIControlID ctrlID, const std::string& name, const std::string& message);	// CGUIStaticText�� �ؽ�Ʈ ����
	void _setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string& name);		// parent�� name ��Ʈ�� ��ġ�� child�� ��ġ��Ų��

private:
	CGUIControlID	m_dlgID;			// �� ���̾�α�
	CGUIControlID	m_manageID;			// ��� � TR ���� ���̾�α�
	CGUIControlID	m_investorListID;	// ������ ����Ʈ ���̾�α�

	CYesNoDialogEx<CTRGuildWorkshop_WarehouseDlg>	m_yesnoDialog;	// ���� ���� ���̾�α�

	std::vector<CGUIControlID>					m_vecInvestorListPiece;	// ������ ����Ʈ ���̾�α� �����̳�
	std::vector<std::pair<int, std::string>>	m_vecInvestorList;		// ������ ���� �����̳�

	__int64	m_iCurGuildManageTR;	// ���� ��� � TR
	__int64	m_iMaxGuildManageTR;	// ��� � TR â���� �ִ� �ݾ�

	int	m_iCurPage;	// ���� ������
	int	m_iMaxPage;	// �ִ� ������

	bool	m_bCheckInvest;	// �����ߴ��� üũ
};