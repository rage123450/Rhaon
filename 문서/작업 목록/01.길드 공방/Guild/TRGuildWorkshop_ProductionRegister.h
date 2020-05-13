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
// 공방 제작 등록 다이얼로그
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
	void _registerItemToGuildPlant();	// 길드공방 제작 등록

private:
	CTRGuildWorkshop_ManagementDlg*	m_pOwner;		// 부모 다이얼로그
	GuildPlantItemInfo*				m_pItemInfo;	// 현재 선택된 아이템 정보

	CGUIControlID	m_dlgID;		// 메인 다이얼로그
	CGUIControlID	m_itemDlgID;	// 아이템 정보 표시 다이얼로그
};