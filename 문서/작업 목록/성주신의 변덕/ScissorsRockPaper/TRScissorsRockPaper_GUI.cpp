#include "stdafx.h"
#include "TRScissorsRockPaper_GUI.h"

CTRScissorsRockPaper_GUI::CTRScissorsRockPaper_GUI()
{
}

CTRScissorsRockPaper_GUI::~CTRScissorsRockPaper_GUI()
{
}

void CTRScissorsRockPaper_GUI::showDialog()
{
	closeDialog();

	Init();
}

void CTRScissorsRockPaper_GUI::Init()
{
	InitName();
	InitGUI();

	InitButton();
	InitStaticText();
	InitEdit();
	InitListBox();
	InitDropListCombo();
	InitSlider();
	InitFrame();
	InitImageControl();
	InitScrollBar();
	InitFormatedText();
	InitImageText();
	InitUserControl();
}

void CTRScissorsRockPaper_GUI::InitGUIName(vector<tuple<int, string>> _vecTemp)
{
	for(auto& i : _vecTemp)
	{
		m_mapGUIName.emplace(make_pair(get<0>(i), get<1>(i)));
	}
}

void CTRScissorsRockPaper_GUI::InitControlName(EControlType _eControlType, vector<string> _vecName)
{
	m_arrayName[_eControlType].assign(begin(_vecName), end(_vecName));
}

void CTRScissorsRockPaper_GUI::AddTimeFunc(std::function<void(float)> _funTime, std::function<void(float)> _funTimeEnd, float _fLifeTime)
{
	m_listTimeFunc.emplace_back(make_shared<CTimeFunc>(_funTime, _funTimeEnd, _fLifeTime));
}

void CTRScissorsRockPaper_GUI::UpdateTimeFunc(float _fElapsed)
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

void CTRScissorsRockPaper_GUI::ResetTimeFunc()
{
	if(m_listTimeFunc.empty())
	{
		return;
	}

	m_listTimeFunc.clear();
}

void CGUIAnimatorGameGroup::onFrameMove(CGUIControl * pCtrl, float fElapsed)
{
	m_fTime += fElapsed;
	
	switch(m_eFuncType)
	{
	case CGUIAnimatorGameGroup::FT_VOID:
		onFrameMove_Func();
		break;

	case CGUIAnimatorGameGroup::FT_VOID_VEC:
		onFrameMove_FuncVec();
		break;

	case CGUIAnimatorGameGroup::FT_VOID_END:
		onFrameMove_FuncEnd();
		break;
	}
}

void CGUIAnimatorGameGroup::onFrameMove_Func()
{
	if(m_fTime < m_fTimeLength)
	{
		m_funcTime(m_fTime);
		m_func();
	}
	else
	{
		onProcessAnimatorEnd();
	}
}

void CGUIAnimatorGameGroup::onFrameMove_FuncVec()
{
	if(m_fTime < m_fTimeLength)
	{
		if(!m_vecFunc.empty())
		{
			for(auto& i : m_vecFunc)
			{
				m_funcTime(m_fTime);
				i();
			}
		}
	}
	else
	{
		onProcessAnimatorEnd();
	}
}

void CGUIAnimatorGameGroup::onFrameMove_FuncEnd()
{
	if(m_fTime < m_fTimeLength)
	{
		m_funcTime(m_fTime);
	}
	else
	{
		if(!m_bFuncEnd)
		{
			m_bFuncEnd = true;
			m_func();
		}
		onProcessAnimatorEnd();
	}
}