#pragma once
class CMiniGameAssist
{
protected:
	class CTimeFunc
	{
	public:
		CTimeFunc(std::function<void(float)>& _funTime, std::function<void(float)>& _funTimeEnd, float _fLifeTime)
			:m_funTime(_funTime), m_funTimeEnd(_funTimeEnd), m_fLifeTime(_fLifeTime), m_fTime(0.0f) {}
	public:
		std::function<void(float)> m_funTime;
		std::function<void(float)> m_funTimeEnd;
		float m_fLifeTime;
		float m_fTime;
	};

protected:
	std::list<std::shared_ptr<CTimeFunc>> m_listTimeFunc;

public:
	CMiniGameAssist();
	virtual ~CMiniGameAssist();

public:
	virtual void showDialog() abstract;
	virtual void closeDialog() abstract;
	virtual bool isVisible() abstract;

protected:
	void ChangeStaticText(CGUIStaticText* _pText, string _strText);
	void ChangeFormatedText(CFormatedStaticText* _pText, string _strText);

public:
	void AddTimeFunc(std::function<void(float)> _funTime, std::function<void(float)> _funTimeEnd, float _fLifeTime);
	void UpdateTimeFunc(float _fElapsed);

	void SetBtnFunction(CGUIDialog* _pDlg, std::string btnName, std::function<bool(CGUIControl*)> func);
	void SetCtrlUserData(CGUIDialog* _pDlg, std::string ctrlName, std::string key, std::string data);
	void SetCtrlUserData(CGUIDialog* _pDlg, std::string ctrlName, std::string key, int data);
};

