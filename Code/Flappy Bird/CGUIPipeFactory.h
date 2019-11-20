#pragma once
#include "CGUIFactory.h"
class CGUIPipeFactory :
	public CGUIFactory
{
public:
	enum EPipeType
	{
		RED, ORANGE, YELLOW, GREEN, BLUE, NAVY, PURPLE, BLACK, END
	};

private:
	CGUIDialog* m_pDlg = nullptr;

public:
	CGUIPipeFactory();
	CGUIPipeFactory(CGUIDialog * pDlg);
	virtual ~CGUIPipeFactory();

public:
	class CGUIPipe* Create(EPipeType eType, int nPosX = 0, int nPosY = 0);
};

