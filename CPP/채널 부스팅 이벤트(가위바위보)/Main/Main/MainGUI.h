#pragma once
#include "BaseGUI.h"
class CMainGUI
	: public CBaseGUI
{
private:
	enum ERewardLevel
	{
		RL_0,
		RL_1,
		RL_2,
		RL_3,
		RL_END
	};

	enum EResultRound
	{
		RR_WIN,
		RR_LOSE,
		RR_DRAW,
		RR_END
	};

	enum EScissorsRockPaper
	{
		SRP_SCISSORS,
		SRP_ROCK,
		SRP_PAPER,
		SRP_END
	};

	enum ENPCMent
	{
		NM_BEFORESTART,		// 게임 시작전
		NM_INGAME,			// 게임 중
		NM_UNMANIPULATED,	// 미조작
		NM_ROUNDWIN,		// 라운드 승리
		NM_ROUNDDRAW,		// 라운드 무승부
		NM_ROUNDLOSE,		// 라운드 패배
	};

private:
	array<SImageCtrl, ERewardLevel::RL_END> m_arrayImage;

	int m_nCurRewardLevel = 0;

	EScissorsRockPaper m_eScissorsRockPaper = EScissorsRockPaper::SRP_END;

	map<tuple<int, int>, string> m_mapMent;

public:
	CMainGUI();
	virtual ~CMainGUI();

public:
	// CBaseGUI을(를) 통해 상속됨
	virtual bool onButtonClick() override;
	virtual void showDialog() override;
	virtual void closeDialog() override;

private:
	void InitMent();

	void UpdateRewardItem();
	void UpdateRewardSparkle(int& _nRewardLevel);
	void UpdateMent();

public:
	// Server
	void ReceiveRewardItemInfo();	// 보상 목록 정보
	void RequestItemInfo();

	void ReceiveGameResult(int _nResult);		// 가위바위보 결과
	void RequestGameResult(EScissorsRockPaper m_eScissorsRockPaper);
};

