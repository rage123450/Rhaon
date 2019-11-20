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
	// IGUICommandHandler��(��) ���� ��ӵ�
	virtual bool InputKey(class CGUIImgObject* pObj,WPARAM wParam) override;
};

