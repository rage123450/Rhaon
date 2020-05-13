#pragma once
#include "CGUIFactoryManager.h"
class CGUIPipeFactoryManager :
	public CGUIFactoryManager
{
private:
	class CGUIPipeFactory* m_pFactory = nullptr;
	vector<class CGUIPipe*> m_vecPipe;

public:
	CGUIPipeFactoryManager(CGUIDialog* pDlg);
	virtual ~CGUIPipeFactoryManager();

public:
	// CGUIFactoryManager��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
};

