#pragma once
class CGUIImgObject
{
protected:
	CGUIDialog* m_pDlg = nullptr;
	CGUIImageCtrl* m_pImg = nullptr;

protected:
	string m_strName = "";
	int m_nPosX = 0;
	int m_nPosY = 0;
	int m_nWidth = 0;
	int m_nHeight = 0;

public:
	CGUIImgObject();
	CGUIImgObject(CGUIDialog* pDlg);
	virtual ~CGUIImgObject();

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	
public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID);
	virtual bool onKeyDown(WPARAM wParam);
	virtual void Jump();

protected:
	virtual void Move(int m_nMoveX, int m_nMoveY);
};

