#pragma once
#include "IGUICommand.h"
class CGUIJumpCommand :
	public IGUICommand
{
public:
	CGUIJumpCommand();
	virtual ~CGUIJumpCommand();

public:
	// IGUICommand을(를) 통해 상속됨
	virtual void Execute(class CGUIImgObject * pObj) override;
};

