#include "stdafx.h"
#include "TRTimeFuncHandler.h"

void CTRTimeFuncHandler::Add(std::function<void(float)> _funTime, std::function<void(float)> _funTimeEnd, float _fLifeTime)
{
	m_listTimeFunc.emplace_back(make_shared<CTRTimeFunc>(_funTime, _funTimeEnd, _fLifeTime));
	m_listTimeFunc.unique();
}

void CTRTimeFuncHandler::Add(std::function<void(float,float)> _funTime, std::function<void(float, float)> _funTimeEnd, float _fLifeTime)
{
	m_listTimeFunc2.emplace_back(make_shared<CTRTimeFunc>(_funTime, _funTimeEnd, _fLifeTime));
	m_listTimeFunc2.unique();
}

void CTRTimeFuncHandler::Update(float _fElapsed)
{
	if(m_listTimeFunc.empty() && m_listTimeFunc2.empty())
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

	for(auto iter = m_listTimeFunc2.begin(); iter != m_listTimeFunc2.end();)
	{
		(*iter)->m_fTime += _fElapsed;
		if((*iter)->m_fTime <= (*iter)->m_fLifeTime)
		{
			(*iter)->m_funTime2(_fElapsed, (*iter)->m_fTime);
			iter++;
		}
		else
		{
			(*iter)->m_funTimeEnd2(_fElapsed, (*iter)->m_fTime);
			iter = m_listTimeFunc2.erase(iter);
		}
	}
}

void CTRTimeFuncHandler::Reset()
{
	m_listTimeFunc.clear();
	m_listTimeFunc2.clear();
}
