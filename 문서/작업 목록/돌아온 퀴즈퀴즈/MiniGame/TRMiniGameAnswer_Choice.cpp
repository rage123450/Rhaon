#include "stdafx.h"
#include "TRMiniGameAnswer_Choice.h"
#include "gui/GUIControlUserValue.h"

void CTRMiniGameAnswer_Choice::InitBtnAct(CGUIDialog * _pDlg, std::vector<std::tuple<std::string, std::function<bool(CGUIControl*)>, std::string, int>> _vecData)
{
	InitButton(m_vecBtnActName, _pDlg, _vecData);
}

void CTRMiniGameAnswer_Choice::InitBtnDis(CGUIDialog * _pDlg, std::vector<std::tuple<std::string, std::function<bool(CGUIControl*)>, std::string, int>> _vecData)
{
	InitButton(m_vecBtnDisName, _pDlg, _vecData);
}

void CTRMiniGameAnswer_Choice::ToggleBtn(bool _bOn)
{
	for(auto& i : m_vecBtnActName)
	{
		m_umapBtn[i]->setVisible(_bOn ? true : false);
	}
	for(auto& i : m_vecBtnDisName)
	{
		m_umapBtn[i]->setVisible(!_bOn ? true : false);
	}
}

void CTRMiniGameAnswer_Choice::ToggleBtnCheck(int _nNum)
{
	for(auto& i : m_vecBtnActName)
	{
		static_cast<CGUIButton*>(m_umapBtn[i])->setChecked(false);
	}

	if(_nNum != -1)
	{
		static_cast<CGUIButton*>(m_umapBtn[m_vecBtnActName[_nNum]])->setChecked(true);
	}
}

void CTRMiniGameAnswer_Choice::ResetBtnCheck()
{
	for(auto& i : m_vecBtnActName)
	{
		static_cast<CGUIButton*>(m_umapBtn[i])->setChecked(false);
	}
}

void CTRMiniGameAnswer_Choice::SetBtnText(std::vector<string> _vecText)
{
	for(size_t i = 0; i < m_vecBtnActName.size(); i++)
	{
		if(m_umapBtn[m_vecBtnActName[i]])
		{
			m_umapBtn[m_vecBtnActName[i]]->setText(_vecText[i]);
		}
	}
}

void CTRMiniGameAnswer_Choice::InitButton(std::vector<std::string>& _vecBtnName, CGUIDialog * _pDlg, std::vector<std::tuple<std::string, std::function<bool(CGUIControl*)>, std::string, int>> _vecData)
{
	_vecBtnName.clear();
	vector<string>().swap(_vecBtnName);
	_vecBtnName.reserve(4);

	std::string strBtnName;
	std::function<bool(CGUIControl*)> funcBtnName;
	std::string strKey;
	int nValue;

	for(auto& i : _vecData)
	{
		std::tie(strBtnName, funcBtnName, strKey, nValue) = i;
		BindBtnAndData(_pDlg, strBtnName, funcBtnName, strKey, nValue);
		_vecBtnName.push_back(strBtnName);
	}
}

void CTRMiniGameAnswer_Choice::bindBtn(CGUIDialog * _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func)
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

void CTRMiniGameAnswer_Choice::BindBtnAndData(CGUIDialog * _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func, std::string key, int data)
{
	bindBtn(_pDlg, btnName, func);
	setCtrlUserData(btnName, key, data);
}

void CTRMiniGameAnswer_Choice::setCtrlUserData(std::string ctrlName, std::string key, int data)
{
	if(m_umapBtn.find(ctrlName) != m_umapBtn.end())
	{
		m_umapBtn[ctrlName]->enableUsingUserData(true)->value.append(key.c_str(), data);
	}
}
