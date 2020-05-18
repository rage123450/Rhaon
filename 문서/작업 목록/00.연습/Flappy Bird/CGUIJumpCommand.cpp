#include "stdafx.h"
#include "CGUIJumpCommand.h"
//
#include "CGUIImgObject.h"

CGUIJumpCommand::CGUIJumpCommand()
{
}

CGUIJumpCommand::~CGUIJumpCommand()
{
}

void CGUIJumpCommand::Execute(CGUIImgObject * pObj)
{
	pObj->Jump();
}
