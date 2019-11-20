#include "stdafx.h"
#include "CGUIMiniGameFlappyBird.h"
//
#include "CGUIBird.h"
#include "CGUIPipeFactoryManager.h"

CGUIMiniGameFlappyBird::CGUIMiniGameFlappyBird()
{
}

CGUIMiniGameFlappyBird::~CGUIMiniGameFlappyBird()
{
}

void CGUIMiniGameFlappyBird::Init()
{
	closeDialog();

	m_pDlg = CGUIManager::getInstance().createControl<CGUIDialog>();
	m_pDlg->setClientPos(0, 0, MAP_WIDTH, MAP_HEIGHT);

	if(!m_pDlg)
	{
		_ASSERTE(false);
		return;
	}

	m_pDlg->setZOrder(1.f);
	m_pDlg->centerPosition();
	m_pDlg->setModalDialog(true);
	m_pDlg->setDialogListener(getCommandTargetID());

	CGUIManager::getInstance().setFocus(m_pDlg->getControlID());

	for(int i = 0; i < 4; ++i)
	{
		m_vecDlg.push_back(CGUIManager::getInstance().createControl<CGUIDialog>());

		switch(i)
		{
		case 0:
			m_vecDlg[i]->setClientPos(0, 0, 240, 960);
			break;
		case 1:
			m_vecDlg[i]->setClientPos(MAP_WIDTH + 240, 0, 240, 960);
			break;
		case 2:
			m_vecDlg[i]->setClientPos(240, 0, MAP_WIDTH, 180);
			break;
		case 3:
			m_vecDlg[i]->setClientPos(240, MAP_HEIGHT + 180, MAP_WIDTH, 180);
			break;
		}

		if(!m_vecDlg[i])
		{
			_ASSERTE(false);
			return;
		}
		m_vecDlg[i]->setZOrder(-1.f);
	}

	m_pExit = CGUIManager::getInstance().createControl<CGUIImageButton>(m_pDlg->getControlID());
	if(m_pExit)
	{
		m_pExit->getImageCtrl()->setImage("gui\\guibasic.png");
		m_pExit->getImageOverCtrl()->setImage("gui\\guibasic.png");
		m_pExit->getImageDownCtrl()->setImage("gui\\guibasic.png");
		m_pExit->getImageCtrl()->setSrcRect(48, 1, 19, 19);
		m_pExit->getImageOverCtrl()->setSrcRect(48, 1, 19, 19);
		m_pExit->getImageDownCtrl()->setSrcRect(48, 1, 19, 19);
		m_pExit->setClientPos(MAP_WIDTH - EXIT_WIDTH, 0, EXIT_WIDTH, EXIT_HEIGHT);
		m_pExit->setName("Exit");
	}

	m_pMain = CGUIManager::getInstance().createControl<CGUIImageButton>(m_pDlg->getControlID());
	if(m_pMain)
	{
		m_pMain->setClientPos(0, EXIT_HEIGHT, MAP_WIDTH, MAP_HEIGHT - EXIT_HEIGHT);
		m_pMain->setName("Main");
	}

	m_pPipeFactoryManager = new CGUIPipeFactoryManager(m_pDlg);
	m_pPipeFactoryManager->Init();

	m_vecImgObject.push_back(new CGUIBird(m_pDlg));

	for each (CGUIImgObject* var in m_vecImgObject)
	{
		if(var)
		{
			var->Init();
		}
	}
}

void CGUIMiniGameFlappyBird::Destory()
{
	if(m_pDlg)
	{
		for each (CGUIDialog* var in m_vecDlg)
		{
			CGUIManager::getInstance().removeControl(var);
			var = nullptr;
		}

		CGUIManager::getInstance().removeControl(m_pDlg);
		m_pDlg = nullptr;
	}
}

void CGUIMiniGameFlappyBird::onFrameMove(float fElapsed)
{
	for each (CGUIImgObject* var in m_vecImgObject)
	{
		if(var)
		{
			var->Update();
		}
	}

	m_pPipeFactoryManager->Update();
}

bool CGUIMiniGameFlappyBird::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	string name;

	CGUIControl* pCtrl = ctrlID.findControl();
	if(pCtrl)
	{
		name = pCtrl->getName();
	}

	if(name == "Exit")
	{
		closeDialog();
		return true;
	}
	else if(name == "Main")
	{
		for each (CGUIImgObject* var in m_vecImgObject)
		{
			if(var)
			{
				var->onButtonClick(ctrlID, cmdID);
			}
		}
		return true;
	}

	return false;
}

bool CGUIMiniGameFlappyBird::onKeyDown(WPARAM wParam)
{
	for each (CGUIImgObject* var in m_vecImgObject)
	{
		if(var)
		{
			var->onKeyDown(wParam);
		}
	}

	return true;
}

bool CGUIMiniGameFlappyBird::isVisible()
{
	if(m_pDlg)
	{
		return m_pDlg->isVisible();
	}

	return false;
}

void CGUIMiniGameFlappyBird::showDialog()
{
	Init();

	CTaskManager::getInstance().addTask(this);
}

void CGUIMiniGameFlappyBird::closeDialog()
{
	Destory();
}


