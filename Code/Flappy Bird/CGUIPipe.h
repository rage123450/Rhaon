#pragma once
#include "CGUIImgObject.h"
class CGUIPipe :
	public CGUIImgObject
{
private:
	int m_nPipeType;
	int m_nSpeed = 1;
	int m_nExp = 0;

public:
	CGUIPipe();
	CGUIPipe(CGUIDialog* pDlg);
	CGUIPipe(CGUIDialog* pDlg, int nPipeType, int nPosX, int nPosY);
	virtual ~CGUIPipe();

public:
	// CGUIImgObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;

public:
	virtual void Move(int m_nMoveX, int m_nMoveY) override;
};

