/* ---------------------------------------------------------------
 *
 * Copyright 2019 by Rhaon Ent.
 *
 * TRGuildWorkshop_ProductionRegister.h
 *
 * 2019. 12. Han Younho
 *
 * ---------------------------------------------------------------
 */

#pragma once

#include "gameui/TRUserInterface.h"

#include "TRWorkshopBase.h"

class CTRGuildWorkshop_ManagementDlg;

////////////////////////////////////////////////////////////////////////////////////
// ���� ���� ��� ���̾�α�
class CTRGuildWorkshop_ProductionRegister : public CTRCommandTarget
{
public:
	CTRGuildWorkshop_ProductionRegister(CTRGuildWorkshop_ManagementDlg* pOwner);
	virtual ~CTRGuildWorkshop_ProductionRegister();

public:
	bool isVisible() const;

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

public:
	void showDialog(GuildPlantItemInfo* pItemInfo);
	void closeDialog();

private:
	void _setItemDialog();

private:
	void _registerItemToGuildPlant();	// ������ ���� ���

private:
	CTRGuildWorkshop_ManagementDlg*	m_pOwner;		// �θ� ���̾�α�
	GuildPlantItemInfo*				m_pItemInfo;	// ���� ���õ� ������ ����

	CGUIControlID	m_dlgID;		// ���� ���̾�α�
	CGUIControlID	m_itemDlgID;	// ������ ���� ǥ�� ���̾�α�
};