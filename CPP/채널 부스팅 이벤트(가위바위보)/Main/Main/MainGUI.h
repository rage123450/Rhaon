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
		NM_BEFORESTART,		// ���� ������
		NM_INGAME,			// ���� ��
		NM_UNMANIPULATED,	// ������
		NM_ROUNDWIN,		// ���� �¸�
		NM_ROUNDDRAW,		// ���� ���º�
		NM_ROUNDLOSE,		// ���� �й�
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
	// CBaseGUI��(��) ���� ��ӵ�
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
	void ReceiveRewardItemInfo();	// ���� ��� ����
	void RequestItemInfo();

	void ReceiveGameResult(int _nResult);		// ���������� ���
	void RequestGameResult(EScissorsRockPaper m_eScissorsRockPaper);
};

