#pragma once
#include "gameui/TRUserInterface.h"
class CGUIMiniRPG :
	public CTRCommandTarget, public IntTask
{
private:
	const int MAP_WIDTH = 800;		
	const int MAP_HEIGHT = 600;

	const int EXIT_WIDTH = 30;
	const int EXIT_HEIGHT = 30;

	const int FACE_WIDTH = 64;
	const int FACE_HEIGHT = 100;

	const int PLAYER_WIDTH = 74;
	const int PLAYER_HEIGHT = 100;
	const int PLAYER_HITTIME = 50;

	const int HP_POSY = 0;
	const int MP_POSY = 20;
	const int EXP_POSY = 40;

	const int BULLET_CUTPOSX = 0;
	const int BULLET_CUTPOSY = 0;
	const int BULLET_WIDTH = 85;
	const int BULLET_HEIGHT = 85;
	const int BULLET_MAX = 10;

	const int BOMB_CUTPOSX = 85;
	const int BOMB_CUTPOSY = 85;
	const int BOMB_WIDTH = 85;
	const int BOMB_HEIGHT = 85;
	const int BOMB_MAX = 10;
	const int BOMB_SPAWNTIME = 500;

private:
	enum EPlayerDirection
	{
		LEFT = -1,
		RIGHT = 1
	};

	enum EJump
	{
		IDLE,
		UP,
		DOWN
	};

private:
	struct SBullet
	{
		CGUIImageCtrl* pBullet;
		bool bLife;
		int nPosX;
		int nPosY;
	};

	struct SBomb
	{
		CGUIImageCtrl* pImg;
		bool bLife;
		int nPosX;
		int nPosY;
	};

private:
	CGUIDialog* m_pDlg = NULL;
	CGUIImageButton* m_pExit = NULL;
	CGUIImageCtrl* m_pFace = NULL;
	CGUIImageCtrl* m_pPlayer = NULL;
	CGUIImageCtrl* m_pBullet = NULL;
	CGUIStaticText* m_pHP = NULL;
	CGUIStaticText* m_pMP = NULL;
	CGUIStaticText* m_pEXP = NULL;
	CGUIImageCtrl* m_pSkillCut = NULL;

private:
	int m_nHP = 10;
	int m_nMP = 0;
	int m_nEXP = 0;

	int m_nPlayerPosX = (MAP_WIDTH - PLAYER_WIDTH) / 2;
	int m_nPlayerPosY = MAP_HEIGHT - FACE_HEIGHT/2;
	int m_nPlayerMoveDir = EPlayerDirection::RIGHT;
	int m_nPlayerMoveSpeedX = 10;
	int m_nPlayerMoveSpeedY = 2;
	int m_nPlayerMaxJump = 200;
	EJump m_eJump = EJump::IDLE;
	CColor m_pPlayerColor;
	int m_nHitCount = 0;

	std::vector<SBullet> m_vecBullet;
	int m_nBulletSpeed = 3;

	SBomb m_sBomb;
	std::vector<SBomb> m_vecBomb;
	int m_nBombSpeed = 1;
	int m_nCollRange = 30;

	int m_nSkillCount = 0;
	int m_nSKillPower = 10;
	int m_nSkillMaxCount = 150;

public:
	CGUIMiniRPG();
	virtual ~CGUIMiniRPG();

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID);
	virtual bool onKeyDown(WPARAM wParam);
	virtual void onFrameMove(float fElapsed);

public:
	bool isVisible();
	void showDialog();
	void closeDialog();

private:
	void MovePlayer();
	void JumpPlayer();
	void MoveBullet();
	void MoveBomb();
	void UpdatePlayer();
};

