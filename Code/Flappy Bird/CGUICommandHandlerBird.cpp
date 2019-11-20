#include "stdafx.h"
#include "CGUICommandHandlerBird.h"
//
#include "CGUIJumpCommand.h"
#include "CGUIImgObject.h"

CGUICommandHandlerBird::CGUICommandHandlerBird()
{
}

CGUICommandHandlerBird::~CGUICommandHandlerBird()
{
}

bool CGUICommandHandlerBird::InputKey(CGUIImgObject * pObj, WPARAM wParam)
{
	switch(wParam)
	{
	case VK_SPACE:
		if(m_pJump == nullptr)
		{
			m_pJump = new CGUIJumpCommand();
		}
		m_pJump->Execute(pObj);
		return true;

	default:
		return false;
	}
}
