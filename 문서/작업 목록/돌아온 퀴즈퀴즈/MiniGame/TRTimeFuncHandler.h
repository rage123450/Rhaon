#pragma once
class CTRTimeFunc;
class CTRTimeFuncHandler
{
private:
	std::list<std::shared_ptr<CTRTimeFunc>> m_listTimeFunc;
	std::list<std::shared_ptr<CTRTimeFunc>> m_listTimeFunc2;

public:
	CTRTimeFuncHandler() = default;
	~CTRTimeFuncHandler() = default;

public:
	void Add(std::function<void(float)> _funTime, std::function<void(float)> _funTimeEnd, float _fLifeTime);
	void Add(std::function<void(float, float)> _funTime, std::function<void(float, float)> _funTimeEnd, float _fLifeTime);
	void Update(float _fElapsed);
	void Reset();
};

class CTRTimeFunc
{
public:
	CTRTimeFunc(std::function<void(float)>& _funTime, std::function<void(float)>& _funTimeEnd, float _fLifeTime)
		:m_funTime(_funTime), m_funTimeEnd(_funTimeEnd), m_fLifeTime(_fLifeTime), m_fTime(0.0f) {}
	CTRTimeFunc(std::function<void(float, float)>& _funTime, std::function<void(float, float)>& _funTimeEnd, float _fLifeTime)
		:m_funTime2(_funTime), m_funTimeEnd2(_funTimeEnd), m_fLifeTime(_fLifeTime), m_fTime(0.0f) {}

public:
	std::function<void(float)> m_funTime;
	std::function<void(float)> m_funTimeEnd;
	std::function<void(float,float)> m_funTime2;
	std::function<void(float, float)> m_funTimeEnd2;
	float m_fLifeTime;
	float m_fTime;
};

