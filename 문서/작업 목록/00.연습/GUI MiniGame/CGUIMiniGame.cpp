#include "stdafx.h"
#include "CGUIMiniGame.h"

CGUIMiniRPG::CGUIMiniRPG()
{
}

CGUIMiniRPG::~CGUIMiniRPG()
{
}

bool CGUIMiniRPG::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	string name;

	CGUIControl* pCtrl = ctrlID.findControl();
	if(pCtrl)
	{
		name = pCtrl->getName();
	}

	if(name == "Exit")
	{
		closeDialog();
		return true;
	}

	return false;
}

bool CGUIMiniRPG::onKeyDown(WPARAM wParam)
{
	if(!isVisible()) return false;

	switch(wParam)
	{
	case VK_LEFT:
		m_nPlayerMoveDir = m_nPlayerMoveDir != EPlayerDirection::LEFT ? EPlayerDirection::LEFT : m_nPlayerMoveDir;
		MovePlayer();
		break;

	case VK_RIGHT:
		m_nPlayerMoveDir = m_nPlayerMoveDir != EPlayerDirection::RIGHT ? EPlayerDirection::RIGHT : m_nPlayerMoveDir;
		MovePlayer();
		break;

	case VK_SPACE:
		if(m_eJump == EJump::IDLE)
		{
			m_eJump = EJump::UP;
		}
		break;

	case 'A':
		if(m_eJump != EJump::IDLE)
		{
			break;
		}

		for(int i = 0; i < BULLET_MAX; ++i)
		{
			if(!m_vecBullet[i].bLife)
			{
				m_vecBullet[i].pBullet = CGUIManager::getInstance().createControl<CGUIImageCtrl>(m_pDlg->getControlID());
				if(m_vecBullet[i].pBullet)
				{
					m_vecBullet[i].pBullet->setImage("gui\\itemicon.png");
					m_vecBullet[i].pBullet->setSrcRect(BULLET_CUTPOSX, BULLET_CUTPOSY, BULLET_WIDTH, BULLET_HEIGHT);
					m_vecBullet[i].pBullet->setClientPos(m_nPlayerPosX - PLAYER_WIDTH / 4, m_vecBullet[i].nPosY, BULLET_WIDTH, BULLET_HEIGHT);
					m_vecBullet[i].pBullet->setName("Bullet" + to_string(i));
				
					m_vecBullet[i].nPosX = m_nPlayerPosX - PLAYER_WIDTH / 4;
				}

				m_vecBullet[i].bLife = true;
				break;
			}
		}
		break;

	case 'S':
		if(m_nMP >= m_nSKillPower)
		{
			m_nMP -= m_nSKillPower;
			m_pSkillCut->setVisible(true);
			m_pSkillCut->setAnimator(new CGUIAnimatorRotateInFadeIn(1.0f, CONST_PI * 8, GUI_HALIGN_CENTER, GUI_VALIGN_CENTER));
			m_nSkillCount = m_nSkillMaxCount;

			for(int i = 0; i < m_vecBomb.size(); ++i)
			{
				if(m_vecBomb[i].bLife)
				{
					m_vecBomb[i].nPosX = rand() % (MAP_WIDTH - BOMB_WIDTH);
					m_vecBomb[i].nPosY = BOMB_HEIGHT;
					m_vecBomb[i].bLife = false;
					m_vecBomb[i].pImg->setVisible(false);
				}
			}
		}
		break;
	}

	return __super::onKeyDown(wParam);
}

void CGUIMiniRPG::onFrameMove(float fElapsed)
{
	JumpPlayer();
	MoveBullet();
	MoveBomb();
	UpdatePlayer();
}

bool CGUIMiniRPG::isVisible()
{
	if(m_pDlg)
	{
		return m_pDlg->isVisible();
	}

	return false;
}

void CGUIMiniRPG::showDialog()
{
	closeDialog();

	m_pDlg = CGUIManager::getInstance().createControl<CGUIDialog>();
	m_pDlg->setClientPos(0, 0, MAP_WIDTH, MAP_HEIGHT);

	if(!m_pDlg)
	{
		_ASSERTE(false);
		return;
	}

	m_pDlg->setZOrder(1.f);
	m_pDlg->centerPosition();
	m_pDlg->setModalDialog(true);
	m_pDlg->setDialogListener(getCommandTargetID());

	CGUIManager::getInstance().setFocus(m_pDlg->getControlID());

	m_pExit = CGUIManager::getInstance().createControl<CGUIImageButton>(m_pDlg->getControlID());
	if(m_pExit)
	{
		m_pExit->getImageCtrl()->setImage("gui\\guibasic.png");
		m_pExit->getImageOverCtrl()->setImage("gui\\guibasic.png");
		m_pExit->getImageDownCtrl()->setImage("gui\\guibasic.png");
		m_pExit->getImageCtrl()->setSrcRect(48, 1, 19, 19);
		m_pExit->getImageOverCtrl()->setSrcRect(48, 1, 19, 19);
		m_pExit->getImageDownCtrl()->setSrcRect(48, 1, 19, 19);
		m_pExit->setClientPos(MAP_WIDTH - EXIT_WIDTH, 0, EXIT_WIDTH, EXIT_HEIGHT);
		m_pExit->setName("Exit");
	}

	m_pFace = CGUIManager::getInstance().createControl<CGUIImageCtrl>(m_pDlg->getControlID());
	if(m_pFace)
	{
		m_pFace->setImage("gui\\Renewal_Char_select02.png");
		m_pFace->setSrcRect(0, 0, FACE_WIDTH, FACE_HEIGHT);
		m_pFace->setClientPos(0, 0, FACE_WIDTH, FACE_HEIGHT);
		m_pFace->setName("Face");
	}

	m_pPlayer = CGUIManager::getInstance().createControl<CGUIImageCtrl>(m_pDlg->getControlID());
	if(m_pPlayer)
	{
		m_pPlayer->setImage("gui\\Renewal_Char_select02.png");
		m_pPlayer->setSrcRect(FACE_WIDTH * 2 + 10, 0, PLAYER_WIDTH, PLAYER_HEIGHT);
		m_pPlayer->setClientPos(m_nPlayerPosX, m_nPlayerPosY, PLAYER_WIDTH, PLAYER_HEIGHT);
		m_pPlayer->setScale(0.5f);
		m_pPlayer->setName("Player");
		m_pPlayerColor = m_pPlayer->getColor();
	}

	for(int i = 0; i < BULLET_MAX; ++i)
	{
		SBullet sBullet;
		sBullet.pBullet = CGUIManager::getInstance().createControl<CGUIImageCtrl>(m_pDlg->getControlID());
		sBullet.bLife = false;
		sBullet.nPosX = m_nPlayerPosX - PLAYER_WIDTH / 4;
		sBullet.nPosY = MAP_HEIGHT - FACE_HEIGHT / 2 - PLAYER_HEIGHT;
		
		m_vecBullet.push_back(sBullet);
	}

	m_pHP = CGUIManager::getInstance().createControl<CGUIStaticText>(m_pDlg->getControlID());
	if(m_pHP)
	{
		m_pHP->setText("HP  " + to_string(m_nHP));
		m_pHP->setFgColor(CColor::RED);
		m_pHP->setClientPos(FACE_WIDTH, HP_POSY);
	}

	m_pMP = CGUIManager::getInstance().createControl<CGUIStaticText>(m_pDlg->getControlID());
	if(m_pMP)
	{
		m_pMP->setText("MP  " + to_string(m_nMP));
		m_pMP->setFgColor(CColor::BLUE);
		m_pMP->setClientPos(FACE_WIDTH, MP_POSY);
	}

	m_pEXP = CGUIManager::getInstance().createControl<CGUIStaticText>(m_pDlg->getControlID());
	if(m_pEXP)
	{
		m_pEXP->setText("EXP " + to_string(m_nEXP));
		m_pEXP->setFgColor(CColor::GREEN);
		m_pEXP->setClientPos(FACE_WIDTH, EXP_POSY);
	}

	for(int i = 0; i < BOMB_MAX; ++i)
	{
		SBomb sBomb;
		sBomb.nPosX = rand() % (MAP_WIDTH - BOMB_WIDTH);
		sBomb.nPosY = 0;
		sBomb.bLife = false;

		sBomb.pImg = CGUIManager::getInstance().createControl<CGUIImageCtrl>(m_pDlg->getControlID());
		sBomb.pImg->setImage("gui\\itemicon.png");
		sBomb.pImg->setSrcRect(BOMB_CUTPOSX, BOMB_CUTPOSY, BOMB_WIDTH, BOMB_HEIGHT);
		sBomb.pImg->setClientPos(sBomb.nPosX, sBomb.nPosY, BULLET_WIDTH, BULLET_HEIGHT);
		sBomb.pImg->setVisible(false);
		
		m_vecBomb.push_back(sBomb);
	}

	m_pSkillCut = CGUIManager::getInstance().createControl<CGUIImageCtrl>(m_pDlg->getControlID());
	m_pSkillCut->setImage("gui\\itemicon.png");
	m_pSkillCut->setSrcRect(0, 0, 256, 256);
	m_pSkillCut->setClientPos(100, 0, BOMB_WIDTH * 7, BOMB_HEIGHT * 7);
	m_pSkillCut->setVisible(false);

	CTaskManager::getInstance().addTask(this);
}

void CGUIMiniRPG::closeDialog()
{
	if(m_pDlg)
	{
		CGUIManager::getInstance().removeControl(m_pDlg);
		m_pDlg = nullptr;
	}
}

void CGUIMiniRPG::MovePlayer()
{
	if(m_pPlayer)
	{
		if(m_nPlayerMoveDir > 0 && m_nPlayerPosX < MAP_WIDTH - PLAYER_WIDTH / 2 ||
			m_nPlayerMoveDir < 0 && m_nPlayerPosX > PLAYER_WIDTH / 2)
		{
			m_nPlayerPosX += m_nPlayerMoveDir * m_nPlayerMoveSpeedX;
			m_pPlayer->setClientPos(m_nPlayerPosX, m_nPlayerPosY, PLAYER_WIDTH, PLAYER_HEIGHT);
			m_pPlayer->setScale(0.5f);
		}
	}
}

void CGUIMiniRPG::JumpPlayer()
{
	switch(m_eJump)
	{
	case CGUIMiniRPG::UP:
		if(m_nPlayerPosY >= MAP_HEIGHT - FACE_HEIGHT / 2 - m_nPlayerMaxJump)
		{
			m_nPlayerPosY -= m_nPlayerMoveSpeedY;
			m_pPlayer->setClientPos(m_nPlayerPosX, m_nPlayerPosY, PLAYER_WIDTH, PLAYER_HEIGHT);
			m_pPlayer->setScale(0.5f);
		}
		else
		{
			m_eJump = EJump::DOWN;
		}
		break;
	
	case CGUIMiniRPG::DOWN:
		if(m_nPlayerPosY<= MAP_HEIGHT - FACE_HEIGHT / 2)
		{
			m_nPlayerPosY += m_nPlayerMoveSpeedY;
			m_pPlayer->setClientPos(m_nPlayerPosX, m_nPlayerPosY, PLAYER_WIDTH, PLAYER_HEIGHT);
			m_pPlayer->setScale(0.5f);
		}
		else
		{
			m_eJump = EJump::IDLE;
		}
		break;
	}
}

void CGUIMiniRPG::MoveBullet()
{
	for(int i = 0; i < BULLET_MAX; ++i)
	{
		if(m_vecBullet[i].bLife)
		{
			m_vecBullet[i].nPosY -= m_nBulletSpeed;
			m_vecBullet[i].pBullet->setClientPos(m_vecBullet[i].nPosX, m_vecBullet[i].nPosY);

			if(m_vecBullet[i].nPosY <= 0)
			{
				CGUIManager::getInstance().removeControl(m_vecBullet[i].pBullet);
				m_vecBullet[i].bLife = false;
				m_vecBullet[i].nPosX = m_nPlayerPosX - PLAYER_WIDTH / 4;
				m_vecBullet[i].nPosY = MAP_HEIGHT - FACE_HEIGHT / 2 - PLAYER_HEIGHT;
				continue;
			}

			for(int j = 0; j < BOMB_MAX; ++j)
			{
				if(m_vecBomb[j].nPosX - m_nCollRange < m_vecBullet[i].nPosX && m_vecBomb[j].nPosX + m_nCollRange > m_vecBullet[i].nPosX &&
					m_vecBomb[j].nPosY - m_nCollRange < m_vecBullet[i].nPosY && m_vecBomb[j].nPosY + m_nCollRange > m_vecBullet[i].nPosY)
				{
					CGUIManager::getInstance().removeControl(m_vecBullet[i].pBullet);
					m_vecBomb[j].pImg->setVisible(false);
					m_vecBullet[i].bLife = false;
					m_vecBullet[i].nPosX = m_nPlayerPosX - PLAYER_WIDTH / 4;
					m_vecBullet[i].nPosY = MAP_HEIGHT - FACE_HEIGHT / 2 - PLAYER_HEIGHT;

					m_vecBomb[j].nPosX = rand() % (MAP_WIDTH - BOMB_WIDTH);
					m_vecBomb[j].nPosY = BOMB_HEIGHT;
					m_vecBomb[j].bLife = false;
					m_vecBomb[j].pImg->setVisible(false);

					m_nMP += 1;
					m_pMP->setText("MP  " + to_string(m_nMP));
					break;
				}
			}
		}
	}
}

void CGUIMiniRPG::MoveBomb()
{
	if(m_pSkillCut->isVisible())
	{
		return;
	}

	for(int i = 0; i < BOMB_MAX; ++i)
	{
		if(!m_vecBomb[i].bLife && rand() % BOMB_SPAWNTIME == 1)
		{
			m_vecBomb[i].bLife = true;
		}

		if(m_vecBomb[i].pImg && m_vecBomb[i].bLife)
		{
			m_vecBomb[i].pImg->setVisible(true);

			m_vecBomb[i].nPosY += m_nBombSpeed;
			m_vecBomb[i].pImg->setClientPos(m_vecBomb[i].nPosX, m_vecBomb[i].nPosY);

			if(m_vecBomb[i].nPosY >= MAP_HEIGHT - BOMB_HEIGHT)
			{
				m_vecBomb[i].nPosX = rand() % (MAP_WIDTH - BOMB_WIDTH);
				m_vecBomb[i].nPosY = BOMB_HEIGHT;
				m_vecBomb[i].bLife = false;
				m_vecBomb[i].pImg->setVisible(false);

				m_pPlayer->setColor(CColor::RED);
				m_nHitCount = PLAYER_HITTIME;
				m_nHP -= 1;
				m_pHP->setText("HP  " + to_string(m_nHP));
			}
		}
	}

	//if(m_sBomb.pImg)
	//{
	//	m_sBomb.nPosY += m_nBombSpeed;
	//	m_sBomb.pImg->setClientPos(m_sBomb.nPosX, m_sBomb.nPosY);

	//	if(m_sBomb.nPosY >= MAP_HEIGHT - BOMB_HEIGHT)
	//	{
	//		m_sBomb.nPosX = rand() % (800 - BOMB_WIDTH);
	//		m_sBomb.nPosY = 0;
	//	}
	//}
}

void CGUIMiniRPG::UpdatePlayer()
{
	if(--m_nHitCount < 0)
	{
		m_pPlayer->setColor(m_pPlayerColor);
	}
	else
	{
		if(m_nHitCount % 10 == 0)
		{
			m_pPlayer->setColor(m_pPlayer->getColor() == CColor::RED ? m_pPlayerColor : CColor::RED);
		}
	}

	if(m_pSkillCut->isVisible() && --m_nSkillCount < 0)
	{
		m_pSkillCut->setVisible(false);
	}
}
