#pragma once
#include "IGUICommand.h"
class CGUIJumpCommand :
	public IGUICommand
{
public:
	CGUIJumpCommand();
	virtual ~CGUIJumpCommand();

public:
	// IGUICommand��(��) ���� ��ӵ�
	virtual void Execute(class CGUIImgObject * pObj) override;
};

