/* ---------------------------------------------------------------
 *
 * Copyright 2019 by Rhaon Ent.
 *
 * TRGuildWorkshop_ManagementDlg.h
 *
 * 2019. 12. Han Younho
 *
 * ---------------------------------------------------------------
 */

#pragma once

#include "gameui/TRUserInterface.h"

#include "TRWorkshopBase.h"

////////////////////////////////////////////////////////////////////////////////////

class CTRGuildWorkshop_WarehouseDlg;
class CTRGuildWorkshop_ExpenseDlg;
class CTRGuildWorkshop_ProductionRegister;
class CTRGuildWorkshop_GuideDlg;

////////////////////////////////////////////////////////////////////////////////////
// ���� ���� ���̾�α�
class CTRGuildWorkshop_ManagementDlg : public CTRCommandTarget, public CGUIButtonEventNotify, public CTRWorkshopBase
{
public:
	typedef std::map<int, std::vector<GuildPlantItemInfo>>	MAP_ITEMLIST_BASE;
	typedef std::map<int, MAP_ITEMLIST_BASE>				MAP_ITEMLIST;
	typedef std::map<int, int>								MAP_ITEM;

public:
	// ��� ���� ������ ī�װ�
	enum eItemCategory
	{
		eItemCategory_None		= 0,	// None
		eItemCategory_Supplies	= 1,	// �Ҹ�ǰ
		eItemCategory_Equipment	= 2,	// ��� ������
		eItemCategory_Special	= 3,	// �����
		eItemCategory_End				// eItemCategory Count
	};

public:
	CTRGuildWorkshop_ManagementDlg();
	virtual ~CTRGuildWorkshop_ManagementDlg();

public:
	std::string getCurItemDistributeKindString();
	eGuildPlantDistributeKind getCurItemDistributeKindEnum();
	int getCurItemLimitBuyCount();

public:
	bool isVisible() const;

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;
	virtual void onButtonEventNotify(CGUIButton* pButton, GUI_MOUSE_EVENT event) override;

public:
	virtual void showDialog() override;
	virtual void closeDialog() override;

public:
	// ��� ����Ʈ ��û ����
	virtual void onRecvCurrentGuildPoint(__int64 iGuildPt) override;
	// ���� ��� ����Ʈ ��û ����
	virtual void onRecvCurrentMyGuildPoint(int iMyGuildPt) override;
	// ��� � TR ��û ����
	virtual void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR) override;
	// ��� � TR ���ڿ� ����
	virtual void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR) override;
	// ��� � TR â�� Ȯ�� ������ ��û ����
	virtual void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue) override;
	// ������ ������ ���� ����� ����
	virtual void onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR) override;
	// ��� � TR ������ ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList) override;
	// ��� ��ȭ ���� ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList) override;
	// ������ ������ ���� ��û ����
	virtual void onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList) override;
	// ������ ���۴�� ������ ����Ʈ ��û ����
	virtual void onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant) override;

public:
	void loadItemList(CTRGuildPlanInfoLoader* pLoader);
	void updateItemList();

public:
	void removeItem(int iItemCategory, int iConsumptionCategory, int iItemIndex);
	bool isValidIndexItemNum(int iIndexItemnum);

private:
	void _setItem(int index);

private:
	void _setSubDialog();
	void _setGuildPointDialog();
	void _setListDialog();
	void _setListPieceDialog();
	void _setItemDialog();
	void _setProductionDialog();

private:
	void _updateDistubeKindList(int iSelect = 0);				// ���� ��� �з� ��� ����Ʈ ����
	void _updateLimitBuyCountList(int iDistubeKind = 0);		// ���� ���� ���� ��� ����Ʈ ����
	void _updateCurrentItem();									// ���� �����ۿ� ���� ���̾�α׵� ����
	int _getSelectDistributeKind();								// ��� ����Ʈ���� ���� ���õ� ���� ��� �з� ��ȯ
	int _getSelectLimitBuyCount();								// ��� ����Ʈ���� ���� ���õ� ���� ���� ���� ��ȯ
	int _getRegisterNeedPoint();								// ���õ� �����ۿ� �´� ��� ����Ʈ ��ȯ
	std::string _getDistributeKindString(int iDistributeKind);	// ���ϴ� ���� ��� �з� ���ڿ� ��ȯ

private:
	void _setPage();																	// ������ ��ȣ ���� (�ܼ��� ��ȣ �����ϴ� �뵵)
	void _setPage(eItemCategory eItemCategory, eRewardCondition eConsumptionCategory);	// ������ �з��� ���� ������ ���� ����

private:
	void _setItemListByCategory(eRewardCondition eConsumptionCategory);				// �Һ� ��ȭ �з��� ���� ���� ����
	void _setItemListByCategory(eRewardCondition eConsumptionCategory, int page);	// + �������� ���� ���� ����

private:
	void _setButtonChecked(CGUIControlID ctrlID, const std::string& name, bool b);
	void _setItemButtonChecked(int index);
	void _setStaticText(CGUIControlID ctrlID, const std::string& name, const std::string& message);	// CGUIStaticText�� �ؽ�Ʈ ����
	void _setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string& name);		// parent�� name ��Ʈ�� ��ġ�� child�� ��ġ��Ų��

private:
	void _checkForProductionRegistItem(int needPoint);	// ����� �� �ִ� ���������� ����Ʈ �� �� ��ư Ȱ��ȭ

private:
	int _findStandByItemList(int itemIndex);	// ���� ��� ���� ������ ã�� (������ -1 ��ȯ)
	int _findPlantItemList(int itemIndex);		// ���۰��� ��� ������ ã�� (������ -1 ��ȯ)

private:
	CGUIControlID	m_dlgID;			// �� ���̾�α�
	CGUIControlID	m_subDlgID;			// ���� ���̾�α�
	CGUIControlID	m_guildPointDlgID;	// ����Ʈ ��� ���̾�α�
	CGUIControlID	m_listDlgID;		// ������ ����Ʈ ���̾�α�
	CGUIControlID	m_itemDlgID;		// ���õ� ������ ���̾�α�
	CGUIControlID	m_productionDlgID;	// ���� ���� ���̾�α�

	CTRGuildPlanInfoLoader*					m_pLoader;					// ������ ������ ���� �δ� Ŭ����
	CTRGuildWorkshop_WarehouseDlg*			m_pWarehouseDlg;			// � TR â��
	CTRGuildWorkshop_ExpenseDlg*			m_pExpenseDlg;				// ��ȭ ���� ��Ȳ
	CTRGuildWorkshop_ProductionRegister*	m_pProductionRegisterDlg;	// ������ ���� ���
	CTRGuildWorkshop_GuideDlg*				m_pGuideDlg;				// ���̵� ���̾�α�

	MAP_ITEMLIST	m_mapItemList;			// ���� ����� ������ ������ ����Ʈ
	MAP_ITEM		m_mapStandByItemList;	// ���� ����� ������
	MAP_ITEM		m_mapPlantItemList;		// ���۰��� ��� ������

	std::vector<CGUIControlID>	m_vecListPiece;	// ������ ������ �����ִ� ���̾�α� �����̳�

	GuildPlantItemInfo	m_tCurItem;			// ���� ������ ������ ����

	eItemCategory		m_eCurItemCategory;			// ���� ������ ������ �з�
	eItemCategory		m_eSelItemCategory;			// m_pItemtDlg�� ��� �������� ������ �з�
	eRewardCondition	m_eCurConsumptionCategory;	// ���� ������ �Һ� ��ȭ �з�
	eRewardCondition	m_eSelConsumptionCategory;	// m_pItemtDlg�� ��� �������� �Һ� ��ȭ �з�

	__int64	m_iGuildPoint;		// ��� ����Ʈ
	__int64	m_iGuildManagerTR;	// ��� � TR

	int	m_iCurPage;			// ���� ������
	int	m_iSelPage;			// m_pItemtDlg�� ��� �������� ���õ� ������
	int	m_iMaxPage;			// �ִ� ������
	int	m_iSelIndex;		// m_pItemtDlg�� ��� �������� ���õ� m_vecListPiece �����̳��� �ε���
	int	m_iMyGuildPoint;	// ���� ��� ����Ʈ

	bool	m_bClickWorkshopList;	// m_pProductionDlg�� Workshop_List ��ӹڽ��� Ŭ���ߴ°�
	bool	m_bClickLimitList;		// m_pProductionDlg�� LimitList ��ӹڽ��� Ŭ���ߴ°�
};