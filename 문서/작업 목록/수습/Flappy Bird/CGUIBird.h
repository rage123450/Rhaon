#pragma once
#include "CGUIImgObject.h"
class CGUIBird :
	public CGUIImgObject
{
private:
	const int JUMP_MAXCOUNT = 30;
	const int JUMPUP_SPEED = 2;
	const int JUMPDOWN_SPEED = 3;

private:
	class CGUICommandHandlerBird* m_pHandler = nullptr;

private:
	int m_nJumpCnt = 0;

public:
	CGUIBird();
	CGUIBird(CGUIDialog* pDlg);
	virtual ~CGUIBird();

public:
	// CGUIImgObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;
	virtual bool onKeyDown(WPARAM wParam);
	virtual void Jump();
};

