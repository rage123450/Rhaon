#include "stdafx.h"
#include "CGUIPang.h"

CGUIPang::CGUIPang()
{
}

CGUIPang::~CGUIPang()
{
}

bool CGUIPang::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	string name;

	CGUIControl* pCtrl = ctrlID.findControl();
	if(pCtrl)
	{
		name = pCtrl->getName();

		if(m_sTempPang.bClick)
		{
			m_sTempPang.bClick = false;

			EPang eTemp = m_arrPang[static_cast<int>(name[0] - '0')][static_cast<int>(name[2] - '0')].ePang;

			m_arrPang[static_cast<int>(name[0] - '0')][static_cast<int>(name[2] - '0')].ePang = m_sTempPang.ePang;
			m_arrPang[m_sTempPang.nIndexY][m_sTempPang.nIndexX].ePang = eTemp;

			UpdatePang();
		}
		else
		{
			m_sTempPang.bClick = true;
			m_sTempPang.ePang = m_arrPang[static_cast<int>(name[0] - '0')][static_cast<int>(name[2] - '0')].ePang;
			m_sTempPang.nIndexX = m_arrPang[static_cast<int>(name[0] - '0')][static_cast<int>(name[2] - '0')].nIndexX;
			m_sTempPang.nIndexY = m_arrPang[static_cast<int>(name[0] - '0')][static_cast<int>(name[2] - '0')].nIndexY;
		}
	}
	return true;
}

bool CGUIPang::onKeyDown(WPARAM wParam)
{
	return __super::onKeyDown(wParam);
}

void CGUIPang::onFrameMove(float fElapsed)
{
	//CheckIfPang();
	CheckRecursionPang();
	CheckPang();
	UpdatePang();
	MarkingPang();
}

void CGUIPang::showDialog()
{
	closeDialog();

	m_pDlg = CGUIManager::getInstance().createControl<CGUIDialog>();
	m_pDlg->setClientPos(0, 0, DIALOG_WIDTH, DIALOG_HEIGHT);
	m_pDlg->setZOrder(1.f);
	m_pDlg->centerPosition();
	m_pDlg->setModalDialog(true);
	m_pDlg->setDialogListener(getCommandTargetID());
	CGUIManager::getInstance().setFocus(m_pDlg->getControlID());

	m_pTitle = CGUIManager::getInstance().createControl<CGUIStaticText>(m_pDlg->getControlID());
	if(m_pTitle)
	{
		m_pTitle->setText("테런 퍼즐게임");
		m_pTitle->setClientPos(DIALOG_WIDTH / 3, 0);
	}

	//m_pTime = CGUIManager::getInstance().createControl<CGUIStaticText>(m_pDlg->getControlID());
	//if(m_pTime)
	//{
	//	m_pTime->setText(to_string(0) + " : " + to_string(0));
	//	m_pTime->setClientPos(DIALOG_WIDTH / 3, 30);
	//}

	//m_pCurPointText = CGUIManager::getInstance().createControl<CGUIStaticText>(m_pDlg->getControlID());
	//if(m_pCurPointText)
	//{
	//	m_pCurPointText->setText("현재 점수");
	//	m_pCurPointText->setClientPos(30, 50);
	//}
	//m_pCurPoint = CGUIManager::getInstance().createControl<CGUIStaticText>(m_pDlg->getControlID());
	//if(m_pCurPoint)
	//{
	//	m_pCurPoint->setText(to_string(0));
	//	m_pCurPoint->setClientPos(30, 70);
	//}

	//m_pClearPointText = CGUIManager::getInstance().createControl<CGUIStaticText>(m_pDlg->getControlID());
	//if(m_pClearPointText)
	//{
	//	m_pClearPointText->setText("클리어 점수");
	//	m_pClearPointText->setClientPos(230, 50);
	//}
	//m_pClearPoint = CGUIManager::getInstance().createControl<CGUIStaticText>(m_pDlg->getControlID());
	//if(m_pClearPoint)
	//{
	//	m_pClearPoint->setText(to_string(0));
	//	m_pClearPoint->setClientPos(230, 70);
	//}

	GeneratePang();

	for(int i = 0; i < CELL_Y; ++i)
	{
		for(int j = 0; j < CELL_X; ++j)
		{
			m_arrPang[i][j].pImg = CGUIManager::getInstance().createControl<CGUIImageButton>(m_pDlg->getControlID());
			m_arrPang[i][j].pImg->getImageCtrl()->setImage("gui\\rankicon.png");
			m_arrPang[i][j].pImg->getImageOverCtrl()->setImage("gui\\rankicon.png");
			m_arrPang[i][j].pImg->getImageDownCtrl()->setImage("gui\\rankicon.png");
			m_arrPang[i][j].pImg->setName(to_string(i) + ":" + to_string(j));

			switch(m_arrPang[i][j].ePang)
			{
			case EPang::ONE:

				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 0, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 0, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 0, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case EPang::TWO:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 1, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 1, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 1, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case CGUIPang::THREE:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 2, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 2, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 2, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case CGUIPang::FOUR:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 3, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 3, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 3, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case CGUIPang::FIVE:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 4, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 4, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 4, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case CGUIPang::SIX:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 5, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 5, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 5, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case CGUIPang::SEVEN:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 6, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 6, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 6, 0, PANG_SIZEX, PANG_SIZEY);
				break;
			}

			m_arrPang[i][j].nIndexX = j;
			m_arrPang[i][j].nIndexY = i;
			m_arrPang[i][j].pImg->setClientPos(START_POSX + PANG_WIDTH * j, START_POSY + PANG_HEIGHT * i, PANG_WIDTH, PANG_HEIGHT);
		}
	}

	CTaskManager::getInstance().addTask(this);
}

void CGUIPang::closeDialog()
{
	if(m_pDlg)
	{
		CGUIManager::getInstance().removeControl(m_pDlg);
		m_pDlg = nullptr;
	}
}

CGUIPang::EPang CGUIPang::GetRandomEPang()
{
	int nPang = (rand() % 7) + 1;

	switch(nPang)
	{
	case 1:
		return CGUIPang::ONE;
	case 2:
		return CGUIPang::TWO;
	case 3:
		return CGUIPang::THREE;
	case 4:
		return CGUIPang::FOUR;
	case 5:
		return CGUIPang::FIVE;
	case 6:
		return CGUIPang::SIX;
	case 7:
		return CGUIPang::SEVEN;
	}
}

void CGUIPang::UpdatePang()
{
	for(int i = 0; i < CELL_Y; ++i)
	{
		for(int j = 0; j < CELL_X; ++j)
		{
			switch(m_arrPang[i][j].ePang)
			{
			case EPang::NONE:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(0, 0, 0, 0);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(0, 0, 0, 0);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(0, 0, 0, 0);
				break;

			case EPang::ONE:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 0, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 0, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 0, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case EPang::TWO:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 1, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 1, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 1, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case CGUIPang::THREE:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 2, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 2, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 2, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case CGUIPang::FOUR:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 3, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 3, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 3, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case CGUIPang::FIVE:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 4, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 4, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 4, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case CGUIPang::SIX:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 5, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 5, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 5, 0, PANG_SIZEX, PANG_SIZEY);
				break;

			case CGUIPang::SEVEN:
				m_arrPang[i][j].pImg->getImageCtrl()->setSrcRect(PANG_SIZEX * 6, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageOverCtrl()->setSrcRect(PANG_SIZEX * 6, 0, PANG_SIZEX, PANG_SIZEY);
				m_arrPang[i][j].pImg->getImageDownCtrl()->setSrcRect(PANG_SIZEX * 6, 0, PANG_SIZEX, PANG_SIZEY);
				break;
			}

			m_arrPang[i][j].nIndexX = j;
			m_arrPang[i][j].nIndexY = i;
			m_arrPang[i][j].pImg->setClientPos(START_POSX + PANG_WIDTH * j, START_POSY + PANG_HEIGHT * i, PANG_WIDTH, PANG_HEIGHT);
		}
	}
}

void CGUIPang::GeneratePang()
{
	for(int i = 0; i < CELL_Y; ++i)
	{
		for(int j = 0; j < CELL_X; ++j)
		{
			m_arrPang[i][j].ePang = GetRandomEPang();
			m_arrPang[i][j].bClick = false;
		}
	}
}

void CGUIPang::MarkingPang()
{
	for(int i = 0; i < CELL_Y; ++i)
	{
		for(int j = 0; j < CELL_X; ++j)
		{
			m_arrEPang[i][j] = m_arrPang[i][j].ePang;
		}
	}
}

void CGUIPang::CheckPang()
{
	int arr[static_cast<int>(EPang::END)];

	for(int i = 0; i < CELL_Y; ++i)
	{
		for(int j = 0; j < CELL_X; ++j)
		{
			if(m_arrPang[i][j].ePang == EPang::NONE)
			{
				for(int k = i; k >= 0; --k)
				{
					if(k != 0)
					{
						m_arrPang[k][j].ePang = m_arrPang[k - 1][j].ePang;
					}
					else
					{
						m_arrPang[k][j].ePang = GetRandomEPang();
					}
				}
			}
			else
			{
				switch(m_arrPang[i][j].ePang)
				{
				case CGUIPang::ONE:
					arr[static_cast<int>(CGUIPang::ONE)]++;
					break;
				case CGUIPang::TWO:
					arr[static_cast<int>(CGUIPang::TWO)]++;
					break;
				case CGUIPang::THREE:
					arr[static_cast<int>(CGUIPang::THREE)]++;
					break;
				case CGUIPang::FOUR:
					arr[static_cast<int>(CGUIPang::FOUR)]++;
					break;
				case CGUIPang::FIVE:
					arr[static_cast<int>(CGUIPang::FIVE)]++;
					break;
				case CGUIPang::SIX:
					arr[static_cast<int>(CGUIPang::SIX)]++;
					break;
				case CGUIPang::SEVEN:
					arr[static_cast<int>(CGUIPang::SEVEN)]++;
					break;
				}
			}
		}
	}

	bool bCheck = false;
	for(int i = 0; i < static_cast<int>(EPang::END); ++i)
	{
		bCheck = false;
		if(arr[i] > 2)
		{
			bCheck = true;
		}
	}

	if(!bCheck)
	{
		GeneratePang();
	}
}

void CGUIPang::CheckIfPang()
{
	for(int i = 0; i < CELL_Y; ++i)
	{
		for(int j = 0; j < CELL_X; ++j)
		{
			if(m_arrPang[i][j].ePang == m_arrPang[i][j + 1].ePang && m_arrPang[i][j + 1].ePang == m_arrPang[i][j + 2].ePang
				&& j + 2 < CELL_X)
			{
				m_arrPang[i][j].ePang = EPang::NONE;
				m_arrPang[i][j + 1].ePang = EPang::NONE;
				m_arrPang[i][j + 2].ePang = EPang::NONE;
			}

			if(m_arrPang[i][j].ePang == m_arrPang[i + 1][j].ePang && m_arrPang[i + 1][j].ePang == m_arrPang[i + 2][j].ePang
				&& i + 2 < CELL_Y)
			{
				m_arrPang[i][j].ePang = EPang::NONE;
				m_arrPang[i + 1][j].ePang = EPang::NONE;
				m_arrPang[i + 2][j].ePang = EPang::NONE;
			}

			if(m_arrPang[i][j].ePang == m_arrPang[i + 1][j + 1].ePang && m_arrPang[i + 1][j + 1].ePang == m_arrPang[i + 2][j + 2].ePang
				&& j + 2 < CELL_X
				&& i + 2 < CELL_Y)
			{
				m_arrPang[i][j].ePang = EPang::NONE;
				m_arrPang[i + 1][j + 1].ePang = EPang::NONE;
				m_arrPang[i + 2][j + 2].ePang = EPang::NONE;
			}

			if(m_arrPang[i][j].ePang == m_arrPang[i + 1][j - 1].ePang && m_arrPang[i + 1][j - 1].ePang == m_arrPang[i + 2][j - 2].ePang
				&& j >= 2
				&& i + 2 < CELL_Y)
			{
				m_arrPang[i][j].ePang = EPang::NONE;
				m_arrPang[i + 1][j - 1].ePang = EPang::NONE;
				m_arrPang[i + 2][j - 2].ePang = EPang::NONE;
			}
		}
	}
}

void CGUIPang::CheckRecursionPang()
{
	for(int i = 0; i < CELL_Y; ++i)
	{
		for(int j = 0; j < CELL_X; ++j)
		{
			if(m_arrPang[i][j].ePang == EPang::NONE)
			{
				continue;
			}

			int nValue = 0;
			
			nValue = MatchPang_Width(i, j, 1);
			
			if(nValue >= 3)
			{
				for(int k = 0; k < nValue; ++k)
				{
					//m_arrPang[i][j + k].ePang = EPang::NONE;
					m_arrEPang[i][j + k] = EPang::NONE;
				}
			}

			nValue = MatchPang_Height(i, j, 1);
			if(nValue >= 3)
			{
				for(int k = 0; k < nValue; ++k)
				{
					//m_arrPang[i + k][j].ePang = EPang::NONE;
					m_arrEPang[i + k][j] = EPang::NONE;
				}
			}

			nValue = MatchPang_CrossR(i, j, 1);
			if(nValue >= 3)
			{
				for(int k = 0; k < nValue; ++k)
				{
					//m_arrPang[i + k][j + k].ePang = EPang::NONE;
					m_arrEPang[i + k][j + k] = EPang::NONE;
				}
			}

			nValue = MatchPang_CrossL(i, j, 1);
			if(nValue >= 3)
			{
				for(int k = 0; k < nValue; ++k)
				{
					//m_arrPang[i + k][j - k].ePang = EPang::NONE;
					m_arrEPang[i + k][j - k] = EPang::NONE;
				}
			}
		}
	}

	for(int i = 0; i < CELL_Y; ++i)
	{
		for(int j = 0; j < CELL_X; ++j)
		{
			if(m_arrEPang[i][j] == EPang::NONE)
			{
				m_arrPang[i][j].ePang = m_arrEPang[i][j];
			}
		}
	}
}

int CGUIPang::MatchPang_Width(int i, int j, int nValue)
{
	if(m_arrPang[i][j].ePang == m_arrPang[i][j + 1].ePang
		&& j + 1 < CELL_X)
	{
		MatchPang_Width(i, j + 1, nValue + 1);
	}
	else
	{
		return nValue;
	}
}

int CGUIPang::MatchPang_Height(int i, int j, int nValue)
{
	if(m_arrPang[i][j].ePang == m_arrPang[i + 1][j].ePang
		&& i + 1 < CELL_Y)
	{
		MatchPang_Height(i + 1, j, nValue + 1);
	}
	else
	{
		return nValue;
	}
}

int CGUIPang::MatchPang_CrossR(int i, int j, int nValue)
{
	if(m_arrPang[i][j].ePang == m_arrPang[i + 1][j + 1].ePang
		&& i + 1 < CELL_Y
		&& j + 1 < CELL_X)
	{
		MatchPang_CrossR(i + 1, j + 1, nValue + 1);
	}
	else
	{
		return nValue;
	}
}

int CGUIPang::MatchPang_CrossL(int i, int j, int nValue)
{
	if(m_arrPang[i][j].ePang == m_arrPang[i + 1][j - 1].ePang
		&& i + 1 < CELL_Y
		&& j - 1 >= 0)
	{
		MatchPang_CrossL(i + 1, j - 1, nValue + 1);
	}
	else
	{
		return nValue;
	}
}
