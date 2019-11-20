#pragma once
#include "gameui/TRUserInterface.h"

class CGUIPang :
	public CTRCommandTarget,
	public IntTask
{
private:
	enum EPang
	{
		NONE,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		END
	};

private:
	const int DIALOG_WIDTH = 400;
	const int DIALOG_HEIGHT = 600;
	const int PANG_WIDTH = 50;
	const int PANG_HEIGHT = 50;
	const int PANG_SIZEX = 256 / 10;
	const int PANG_SIZEY = 256 / 12;
	const int START_POSX = 50;
	const int START_POSY = 200;
	const int CELL_X = 5;
	const int CELL_Y = 5;

private:
	struct SPang
	{
		CGUIImageButton* pImg;
		bool bClick;
		EPang ePang;
		int nIndexY, nIndexX;
	};

private:
	CGUIDialog* m_pDlg = nullptr;
	CGUIStaticText* m_pTitle = nullptr;
	CGUIStaticText* m_pTime = nullptr;
	CGUIStaticText* m_pCurPoint = nullptr;
	CGUIStaticText* m_pCurPointText = nullptr;
	CGUIStaticText* m_pClearPoint = nullptr;
	CGUIStaticText* m_pClearPointText = nullptr;

	SPang m_arrPang[5][5];
	SPang m_sTempPang;
	EPang m_arrEPang[5][5];

public:
	CGUIPang();
	virtual ~CGUIPang();

public:
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID);
	virtual bool onKeyDown(WPARAM wParam);
	virtual void onFrameMove(float fElapsed);

public:
	void showDialog();
	void closeDialog();


private:
	EPang GetRandomEPang();
	void UpdatePang();
	void GeneratePang();
	void MarkingPang();

	// black Pang!
	void CheckPang();

	// if~
	void CheckIfPang();
	
	// Recursion~
	void CheckRecursionPang();
	int MatchPang_Width(int i, int j, int nValue);
	int MatchPang_Height(int i, int j, int nValue);
	int MatchPang_CrossR(int i, int j, int nValue);
	int MatchPang_CrossL(int i, int j, int nValue);
};

