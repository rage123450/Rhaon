#include "stdafx.h"
#include "CGUIBird.h"
//
#include "CGUICommandHandlerBird.h"

CGUIBird::CGUIBird()
{
}

CGUIBird::CGUIBird(CGUIDialog * pDlg)
	: CGUIImgObject(pDlg)
{
}

CGUIBird::~CGUIBird()
{
	SAFE_DELETE(m_pHandler);
}

void CGUIBird::Init()
{
	m_nPosX = 200;
	m_nPosY = 300;
	m_nWidth = 256/9;
	m_nHeight = 256/12;
	m_strName = "Bird";

	m_pImg->setImage("gui\\rankicon.png");
	m_pImg->setSrcRect(0, 0, m_nWidth, m_nHeight);
	m_pImg->setClientPos(m_nPosX, m_nPosY, m_nWidth, m_nHeight);
	m_pImg->setFlip(true, false);
	m_pImg->setName(m_strName);

	SAFE_DELETE(m_pHandler);
	m_pHandler = new CGUICommandHandlerBird();
}

void CGUIBird::Update()
{
	m_nJumpCnt = m_nJumpCnt == 0 ? m_nJumpCnt : m_nJumpCnt - 1;

	if(m_nJumpCnt == 0)
	{
		Move(0, JUMPDOWN_SPEED);
	}
	else
	{
		Move(0, -JUMPUP_SPEED);
	}

	if(m_nPosY >= 600)
	{
		m_nPosY = 300;
	}
}

bool CGUIBird::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	return true;
}

bool CGUIBird::onKeyDown(WPARAM wParam)
{
	return m_pHandler->InputKey(this, wParam);
}

void CGUIBird::Jump()
{
	if(m_nJumpCnt == 0)
	{
		m_nJumpCnt = JUMP_MAXCOUNT;
	}
}
