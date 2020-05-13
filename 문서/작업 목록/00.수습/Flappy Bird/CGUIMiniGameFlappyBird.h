#pragma once
#include "gameui/TRUserInterface.h"
class CGUIMiniGameFlappyBird :
	public CTRCommandTarget,
	public IntTask
{
private:
	const int MAP_WIDTH = 800;
	const int MAP_HEIGHT = 600;

	const int EXIT_WIDTH = 30;
	const int EXIT_HEIGHT = 30;

private:
	CGUIDialog* m_pDlg = nullptr;
	CGUIImageButton* m_pExit = nullptr;
	CGUIImageButton* m_pMain = nullptr;
	vector<CGUIDialog*> m_vecDlg;

private:
	vector<class CGUIImgObject*> m_vecImgObject;
	class CGUIBird* m_pBird = nullptr;
	class CGUIPipeFactoryManager* m_pPipeFactoryManager = nullptr;

public:
	CGUIMiniGameFlappyBird();
	virtual ~CGUIMiniGameFlappyBird();

public:
	virtual void onFrameMove(float fElapsed);
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID);
	virtual bool onKeyDown(WPARAM wParam);

public:
	bool isVisible();
	void showDialog();
	void closeDialog();

private:
	void Init();
	void Destory();
};

