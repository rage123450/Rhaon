#pragma once
#include "IGUICommandHandler.h"
class CGUICommandHandlerBird :
	public IGUICommandHandler
{
private:
	class CGUIJumpCommand* m_pJump = nullptr;

public:
	CGUICommandHandlerBird();
	virtual ~CGUICommandHandlerBird();

public:
	// IGUICommandHandler을(를) 통해 상속됨
	virtual bool InputKey(class CGUIImgObject* pObj,WPARAM wParam) override;
};

