#include "stdafx.h"
#include "CGUIImgObject.h"

CGUIImgObject::CGUIImgObject()
{
}

CGUIImgObject::CGUIImgObject(CGUIDialog * pDlg)
	: m_pDlg(pDlg)
{
	m_pImg = CGUIManager::getInstance().createControl<CGUIImageCtrl>(m_pDlg->getControlID());
}

CGUIImgObject::~CGUIImgObject()
{
}

bool CGUIImgObject::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	return false;
}

bool CGUIImgObject::onKeyDown(WPARAM wParam)
{
	return false;
}

void CGUIImgObject::Jump()
{
}

void CGUIImgObject::Move(int m_nMoveX, int m_nMoveY)
{
	if(m_pImg)
	{
		m_pImg->setClientPos(m_nPosX + m_nMoveX, m_nPosY + m_nMoveY, m_nWidth, m_nHeight);

		m_nPosX += m_nMoveX;
		m_nPosY += m_nMoveY;
	}
}
