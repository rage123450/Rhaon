#include "stdafx.h"
#include "CGUIPipe.h"

CGUIPipe::CGUIPipe()
{
}

CGUIPipe::CGUIPipe(CGUIDialog * pDlg)
	: CGUIImgObject(pDlg)
{
}

CGUIPipe::CGUIPipe(CGUIDialog * pDlg, int nPipeType, int nPosX, int nPosY)
	: CGUIImgObject(pDlg)
	, m_nPipeType(nPipeType)
{
	m_nPosX = nPosX;
	m_nPosY = nPosY;
}

CGUIPipe::~CGUIPipe()
{
}

void CGUIPipe::Init()
{
	//m_nPosX = 0;
	//m_nPosY = 600 - 256;
	m_nWidth = 256 / 8;
	m_nHeight = 256;
	m_strName = "Pipe";

	m_pImg->setImage("gui\\TalkBoxColor.png");

	//m_pImg->setSrcRect(0, 0, m_nWidth, m_nHeight/8);
	//m_pImg->setClientPos(m_nPosX, m_nPosY, m_nWidth, m_nHeight / 8);

	//m_pImg->setSrcRect(0, 0, m_nWidth, (m_nHeight / 8) * 2);
	//m_pImg->setClientPos(m_nPosX, m_nPosY, m_nWidth, (m_nHeight / 8) * 2);

	m_pImg->setSrcRect(0, 0, m_nWidth, (m_nHeight / 8) * m_nPipeType);
	m_pImg->setClientPos(m_nPosX, m_nPosY, m_nWidth, (m_nHeight / 8) * m_nPipeType);

	m_pImg->setName(m_strName);
}

void CGUIPipe::Update()
{
	Move(-m_nSpeed, 0);
}

void CGUIPipe::Move(int m_nMoveX, int m_nMoveY)
{
	if(m_pImg)
	{
		m_nPosX += m_nMoveX;
		m_nPosY += m_nMoveY;

		if(m_nPosX <= -m_nWidth)
		{
			/*m_nSpeed = m_nExp++ > 1 ? m_nSpeed + 1 : m_nSpeed;*/

			m_nPosX = 800 + m_nWidth;
			m_nPipeType = rand() % 8 + 1;
		
			m_pImg->setSrcRect(0, 0, m_nWidth, (m_nHeight / 8) * m_nPipeType);
		}
		
		if(m_nPosY == 0)
		{
			m_pImg->setClientPos(m_nPosX, m_nPosY, m_nWidth, (m_nHeight / 8) * m_nPipeType);
		}
		else
		{
			m_nPosY = 600 - (m_nHeight / 8) * m_nPipeType;
			m_pImg->setClientPos(m_nPosX, m_nPosY, m_nWidth, (m_nHeight / 8) * m_nPipeType);
		}
	}
}
