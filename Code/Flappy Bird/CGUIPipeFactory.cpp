#include "stdafx.h"
#include "CGUIPipeFactory.h"
//
#include "CGUIPipe.h"

CGUIPipeFactory::CGUIPipeFactory()
{
}

CGUIPipeFactory::CGUIPipeFactory(CGUIDialog * pDlg)
{
	m_pDlg = pDlg;
}

CGUIPipeFactory::~CGUIPipeFactory()
{
}

CGUIPipe * CGUIPipeFactory::Create(EPipeType eType, int nPosX, int nPosY)
{
	switch(eType)
	{
	case CGUIPipeFactory::RED:
		return new CGUIPipe(m_pDlg, 1, nPosX, nPosY);

	case CGUIPipeFactory::ORANGE:
		return new CGUIPipe(m_pDlg, 2, nPosX, nPosY);

	case CGUIPipeFactory::YELLOW:
		return new CGUIPipe(m_pDlg, 3, nPosX, nPosY);

	case CGUIPipeFactory::GREEN:
		return new CGUIPipe(m_pDlg, 4, nPosX, nPosY);

	case CGUIPipeFactory::BLUE:
		return new CGUIPipe(m_pDlg, 5, nPosX, nPosY);

	case CGUIPipeFactory::NAVY:
		return new CGUIPipe(m_pDlg, 6, nPosX, nPosY);

	case CGUIPipeFactory::PURPLE:
		return new CGUIPipe(m_pDlg, 7, nPosX, nPosY);

	case CGUIPipeFactory::BLACK:
		return new CGUIPipe(m_pDlg, 8, nPosX, nPosY);
	}

	return nullptr;
}
