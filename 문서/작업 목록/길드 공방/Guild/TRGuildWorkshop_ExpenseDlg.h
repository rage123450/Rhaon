/* ---------------------------------------------------------------
 *
 * Copyright 2019 by Rhaon Ent.
 *
 * TRGuildWorkshop_ExpenseDlg.h
 *
 * 2019. 12. Han Younho
 *
 * ---------------------------------------------------------------
 */

#pragma once

#include "gameui/TRUserInterface.h"

 ////////////////////////////////////////////////////////////////////////////////////
 // ��ȭ ���� ��Ȳ ���̾�α�
class CTRGuildWorkshop_ExpenseDlg : public CTRCommandTarget
{
public:
	CTRGuildWorkshop_ExpenseDlg();
	virtual ~CTRGuildWorkshop_ExpenseDlg();

public:
	bool isVisible() const;

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

public:
	void showDialog();
	void closeDialog();

public:	// ��� ��ȭ ���� ����Ʈ ��û ����
	void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList);

private:
	void _setListDialog();
	void _setListPieceDialog();

private:
	void _setInvestorListByPage(int page);							// ������ �������� ���� ����Ʈ ����
	void _setInvestorListCondition(eRewardCondition eCondition);	// ��� ����Ʈ��, ��� � ����Ʈ�Ŀ� ���� ����Ʈ �κ��� �ٲ��

private:
	void _setPage(bool bInit = false);

private:
	void _setButtonChecked(const std::string& name, bool b);
	void _setStaticText(CGUIControlID ctrlID, const std::string& name, const std::string& message);	// CGUIStaticText�� �ؽ�Ʈ ����
	void _setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string& name);		// parent�� name ��Ʈ�� ��ġ�� child�� ��ġ��Ų��

private:
	CGUIControlID	m_dlgID;		// �� ���̾�α�
	CGUIControlID	m_listDlgID;	// ���� ����Ʈ ���̾�α�

	std::vector<CGUIControlID>			m_vecListPiece;		// ���� ���� ���̾�α� �����̳�
	std::vector<GuildPlantPointUseInfo>	m_vecExpenseList;	// ���� ���� �����̳�

	eRewardCondition	m_eCurCondition;	// ���� ����Ʈ ����

	int	m_iCurPage;		// ���� ������
	int	m_iMaxPage;		// �ִ� ������
	int	m_iSelMonth;	// ���� ������ ��
};