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
 // 재화 지출 현황 다이얼로그
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

public:	// 길드 재화 지출 리스트 요청 성공
	void onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList);

private:
	void _setListDialog();
	void _setListPieceDialog();

private:
	void _setInvestorListByPage(int page);							// 선택한 페이지에 따라 리스트 갱신
	void _setInvestorListCondition(eRewardCondition eCondition);	// 길드 포인트냐, 길드 운영 포인트냐에 따라 포인트 부분이 바뀐다

private:
	void _setPage(bool bInit = false);

private:
	void _setButtonChecked(const std::string& name, bool b);
	void _setStaticText(CGUIControlID ctrlID, const std::string& name, const std::string& message);	// CGUIStaticText의 텍스트 변경
	void _setClientPos(CGUIControlID parentID, CGUIControlID childID, const std::string& name);		// parent의 name 컨트롤 위치에 child를 위치시킨다

private:
	CGUIControlID	m_dlgID;		// 주 다이얼로그
	CGUIControlID	m_listDlgID;	// 길드원 리스트 다이얼로그

	std::vector<CGUIControlID>			m_vecListPiece;		// 길드원 정보 다이얼로그 컨테이너
	std::vector<GuildPlantPointUseInfo>	m_vecExpenseList;	// 지출 정보 컨테이너

	eRewardCondition	m_eCurCondition;	// 현재 포인트 종류

	int	m_iCurPage;		// 현재 페이지
	int	m_iMaxPage;		// 최대 페이지
	int	m_iSelMonth;	// 현재 선택한 달
};