#include "stdafx.h"
#include "CGUIPipeFactoryManager.h"
//
#include "CGUIPipeFactory.h"
#include "CGUIPipe.h"

CGUIPipeFactoryManager::CGUIPipeFactoryManager(CGUIDialog * pDlg)
{
	m_pFactory = new CGUIPipeFactory(pDlg);
}

CGUIPipeFactoryManager::~CGUIPipeFactoryManager()
{
	SAFE_DELETE(m_pFactory);
}

void CGUIPipeFactoryManager::Init()
{
	if(m_pFactory)
	{
		for(int i = 0; i < 8; ++i)
		{
			m_vecPipe.push_back(m_pFactory->Create(static_cast<CGUIPipeFactory::EPipeType>(rand() % 8), 100 * i, 0));
		}

		for(int i = 0; i < 8; ++i)
		{
			int nRand = rand() % 8;
			m_vecPipe.push_back(m_pFactory->Create(static_cast<CGUIPipeFactory::EPipeType>(nRand), 100 * i, 600 - (32 * nRand)));
		}
	}

	for each (CGUIPipe* var in m_vecPipe)
	{
		if(var)
		{
			var->Init();
		}
	}
}

void CGUIPipeFactoryManager::Update()
{
	for each (CGUIPipe* var in m_vecPipe)
	{
		var->Update();
	}
}