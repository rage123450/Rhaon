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
// 운영 TR 창고 다이얼로그
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
	// 길드 운영 TR 요청 성공
	void onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR);
	// 길드 운영 TR 투자에 성공
	void onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR);
	// 운영 TR 창고 확장정보 요청 성공
	void onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue);
	// 투자자 리스트를 요청 성공
	void onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList);

private:
	void _setManage();
	void _setInvestorList();
	void _setInvestorListPiece();

private:
	void _setPage(bool bInit = false);

private:
	void _setInvestorListVisible(bool b);	// 투자자 리스트 활성화 여부
	void _setInvestorListByPage(int page);	// 투자자 리스트를 페이지에 따라 갱신

private:
	bool _cheackJoinWithin7Days(time_type joinDate);	// 가입한지 7일 이내인지 검사

private:
	void _hideInvestButton();	// 투자 버튼(에딧 컨트롤 포함) 비활성화

private:
	void _yesnoDialogPopup();
	void _operationalTRInvestment();	// 운영 TR 창고 확장

private:
	void _setButtonChecked(const std::string& name, bool b);
	void _setStaticText(CGUIControlID ctrlID, const std::string& name, const std::string& message);	// CGUIStaticText의 텍스트 변경
	void _setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string& name);		// parent의 name 컨트롤 위치에 child를 위치시킨다

private:
	CGUIControlID	m_dlgID;			// 주 다이얼로그
	CGUIControlID	m_manageID;			// 길드 운영 TR 투자 다이얼로그
	CGUIControlID	m_investorListID;	// 투자자 리스트 다이얼로그

	CYesNoDialogEx<CTRGuildWorkshop_WarehouseDlg>	m_yesnoDialog;	// 투자 여부 다이얼로그

	std::vector<CGUIControlID>					m_vecInvestorListPiece;	// 투자자 리스트 다이얼로그 컨테이너
	std::vector<std::pair<int, std::string>>	m_vecInvestorList;		// 투자자 정보 컨테이너

	__int64	m_iCurGuildManageTR;	// 현재 길드 운영 TR
	__int64	m_iMaxGuildManageTR;	// 길드 운영 TR 창고의 최대 금액

	int	m_iCurPage;	// 현재 페이지
	int	m_iMaxPage;	// 최대 페이지

	bool	m_bCheckInvest;	// 투자했는지 체크
};