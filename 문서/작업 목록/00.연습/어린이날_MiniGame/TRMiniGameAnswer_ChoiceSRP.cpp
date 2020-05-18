#include "stdafx.h"
#include "TRMiniGameAnswer_ChoiceSRP.h"

CTRMiniGameAnswer_ChoiceSRP::CTRMiniGameAnswer_ChoiceSRP() : CTRMiniGameAnswer(Answer_SRP)
{
}

CTRMiniGameAnswer_ChoiceSRP::~CTRMiniGameAnswer_ChoiceSRP()
{
}

void CTRMiniGameAnswer_ChoiceSRP::Init()
{
	m_eCurSelectSRP = ESelectSRP::SS_END;
}

void CTRMiniGameAnswer_ChoiceSRP::InitSelectSRP(CGUIDialog * _pDlg, std::vector<std::tuple<std::string, std::function<bool(CGUIControl*)>, std::string, int>> _vecData)
{
	m_vecBtnName.clear();
	vector<string>().swap(m_vecBtnName);
	m_vecBtnName.reserve(ESelectSRP::SS_END);

	std::string strBtnName;
	std::function<bool(CGUIControl*)> funcBtnName;
	std::string strKey;
	int nValue;

	for(auto& i : _vecData)
	{
		std::tie(strBtnName, funcBtnName, strKey, nValue) = i;
		BindBtnAndData(_pDlg, strBtnName, funcBtnName, strKey, nValue);
		m_vecBtnName.push_back(strBtnName);
	}
}

void CTRMiniGameAnswer_ChoiceSRP::InitDisSRP(CGUIDialog * _pDlg, std::vector<std::tuple<std::string, std::function<bool(CGUIControl*)>, std::string, int>> _vecData)
{
	m_vecBtnDisName.clear();
	vector<string>().swap(m_vecBtnDisName);
	m_vecBtnDisName.reserve(ESelectSRP::SS_END);

	std::string strBtnName;
	std::function<bool(CGUIControl*)> funcBtnName;
	std::string strKey;
	int nValue;

	for(auto& i : _vecData)
	{
		std::tie(strBtnName, funcBtnName, strKey, nValue) = i;
		BindBtnAndData(_pDlg, strBtnName, funcBtnName, strKey, nValue);
		m_vecBtnDisName.push_back(strBtnName);
	}
}

bool CTRMiniGameAnswer_ChoiceSRP::UpdateSelectSRP(int _nSRP)
{
	ESelectSRP eSelectSRP = GetESelectSRPToInt(_nSRP);

	if(m_eCurSelectSRP == eSelectSRP)
	{
		return false;
	}

	m_eCurSelectSRP = eSelectSRP;

	ToggleCheckedButton(eSelectSRP);

	return true;
}

void CTRMiniGameAnswer_ChoiceSRP::ToggleSelectSRP(bool _bOn)
{
	for(auto& i : m_vecBtnName)
	{
		m_umapBtn[i]->setVisible(_bOn ? true : false);
	}
	for(auto& i : m_vecBtnDisName)
	{
		m_umapBtn[i]->setVisible(!_bOn ? true : false);
	}
}

void CTRMiniGameAnswer_ChoiceSRP::ToggleCheckedButton(ESelectSRP _eSelectSRP)
{
	for(auto& i : m_vecBtnName)
	{
		static_cast<CGUIButton*>(m_umapBtn[i])->setChecked(false);
	}

	static_cast<CGUIButton*>(m_umapBtn[m_vecBtnName[_eSelectSRP]])->setChecked(true);
}
