#include "stdafx.h"
#include "TRMiniGameAnswer.h"
//
#include "gui/GUIControlUserValue.h"

CTRMiniGameAnswer::CTRMiniGameAnswer(AnswerType eType)
{
	m_eType = eType;
}

CTRMiniGameAnswer::~CTRMiniGameAnswer()
{
}

void CTRMiniGameAnswer::bindBtn(CGUIDialog * _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func)
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
		m_umapBtn.emplace(btnName, pCtrl);
	}
}

void CTRMiniGameAnswer::setCtrlUserData(CGUIDialog * _pDlg, std::string ctrlName, std::string key, std::string data)
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

void CTRMiniGameAnswer::setCtrlUserData(CGUIDialog * _pDlg, std::string ctrlName, std::string key, int data)
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

std::string CTRMiniGameAnswer::GetUserDataString(std::string ctrlName, std::string key)
{
	if(m_umapBtn[ctrlName] == nullptr)
	{
		return "";
	}

	return m_umapBtn[ctrlName]->getUserDataValue()->value.asString(key.c_str());
}

int CTRMiniGameAnswer::GetUserDataInt(std::string ctrlName, std::string key)
{
	if(m_umapBtn[ctrlName] == nullptr)
	{
		return -1;
	}

	return m_umapBtn[ctrlName]->getUserDataValue()->value.asInt(key.c_str());
}

CGUIControl * CTRMiniGameAnswer::GetButtonControl(std::string btnName)
{
	return m_umapBtn[btnName];
}

void CTRMiniGameAnswer::BindBtnAndData(CGUIDialog * _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func, std::string key, std::string data)
{
	bindBtn(_pDlg, btnName, func);
	setCtrlUserData(btnName, key, data);
}

void CTRMiniGameAnswer::BindBtnAndData(CGUIDialog * _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func, std::string key, int data)
{
	bindBtn(_pDlg, btnName, func);
	setCtrlUserData(btnName, key, data);
}

void CTRMiniGameAnswer::setCtrlUserData(std::string ctrlName, std::string key, std::string data)
{
	if(m_umapBtn[ctrlName] == nullptr)
	{
		return;
	}

	m_umapBtn[ctrlName]->enableUsingUserData(true)->value.append(key.c_str(), data);
}

void CTRMiniGameAnswer::setCtrlUserData(std::string ctrlName, std::string key, int data)
{
	if(m_umapBtn[ctrlName] == nullptr)
	{
		return;
	}

	m_umapBtn[ctrlName]->enableUsingUserData(true)->value.append(key.c_str(), data);

	m_umapBtn[ctrlName]->getUserDataValue();
}


