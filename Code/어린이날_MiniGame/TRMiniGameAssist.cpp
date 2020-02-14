#include "stdafx.h"
#include "TRMiniGameAssist.h"
//
#include "gui/GUIControlUserValue.h"

CMiniGameAssist::CMiniGameAssist()
{
}

CMiniGameAssist::~CMiniGameAssist()
{
}

void CMiniGameAssist::ChangeStaticText(CGUIStaticText * _pText, string _strText)
{
	if(_pText!=nullptr)
	{
		_pText->setText(_strText);
	}
}

void CMiniGameAssist::ChangeFormatedText(CFormatedStaticText * _pText, string _strText)
{
	if(_pText != nullptr)
	{
		_pText->setText(_strText);
	}
}

void CMiniGameAssist::AddTimeFunc(std::function<void(float)> _funTime, std::function<void(float)> _funTimeEnd, float _fLifeTime)
{
	m_listTimeFunc.emplace_back(make_shared<CTimeFunc>(_funTime, _funTimeEnd, _fLifeTime));
	m_listTimeFunc.unique();
}

void CMiniGameAssist::UpdateTimeFunc(float _fElapsed)
{
	if(m_listTimeFunc.empty())
	{
		return;
	}

	for(auto iter = m_listTimeFunc.begin(); iter != m_listTimeFunc.end();)
	{
		(*iter)->m_fTime += _fElapsed;
		if((*iter)->m_fTime <= (*iter)->m_fLifeTime)
		{
			(*iter)->m_funTime((*iter)->m_fTime);
			iter++;
		}
		else
		{
			(*iter)->m_funTimeEnd((*iter)->m_fTime);
			iter = m_listTimeFunc.erase(iter);
		}
	}
}

void CMiniGameAssist::SetBtnFunction(CGUIDialog * _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func)
{
	if(_pDlg == nullptr || btnName.empty())
	{
		return;
	}

	CGUIControl * pCtrl = _pDlg->findControl(btnName);
	if(pCtrl != nullptr)
	{
		pCtrl->clearButtonClickCmdFunc();
		pCtrl->bindButtonClickCmdFunc(func);
	}
}

void CMiniGameAssist::SetCtrlUserData(CGUIDialog * _pDlg, std::string ctrlName, std::string key, std::string data)
{
	if(_pDlg == nullptr || ctrlName.empty())
	{
		return;
	}

	CGUIControl * pCtrl = _pDlg->findControl(ctrlName);
	if(pCtrl != nullptr)
	{
		pCtrl->enableUsingUserData(true)->value.append(key.c_str(), data);
	}
}

void CMiniGameAssist::SetCtrlUserData(CGUIDialog * _pDlg, std::string ctrlName, std::string key, int data)
{
	if(_pDlg == nullptr || ctrlName.empty())
	{
		return;
	}

	CGUIControl * pCtrl = _pDlg->findControl(ctrlName);
	if(pCtrl != nullptr)
	{
		pCtrl->enableUsingUserData(true)->value.append(key.c_str(), data);
	}
}
