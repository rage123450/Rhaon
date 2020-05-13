#pragma once
class CTRScissorsRockPaper_GUI
{
protected:
	enum EControlType
	{
		CT_BUTTON,
		CT_STATICTEXT,
		CT_EDIT,
		CT_LISTBOX,
		CT_DROPLISTCOMBO,
		CT_SLIDER,
		CT_FRAME,
		CT_IMAGECONTROL,
		CT_SCROLLBAR,
		CT_FORMATEDTEXT,
		CT_END
	};

protected:
	class CTimeFunc
	{
	public:
		CTimeFunc(std::function<void(float)>& _funTime, std::function<void(float)>& _funTimeEnd, float _fLifeTime)
			:m_funTime(_funTime), m_funTimeEnd(_funTimeEnd), m_fLifeTime(_fLifeTime), m_fTime(0.0f){}
	public:
		std::function<void(float)> m_funTime;
		std::function<void(float)> m_funTimeEnd;
		float m_fLifeTime;
		float m_fTime;
	};

protected:
	std::map<int, string> m_mapGUIName;
	std::array<std::vector<std::string>, EControlType::CT_END> m_arrayName = { {}, };
	std::list<shared_ptr<CTimeFunc>> m_listTimeFunc;

public:
	CTRScissorsRockPaper_GUI();
	virtual ~CTRScissorsRockPaper_GUI();

public:
	virtual void InitName()abstract;
	virtual void InitGUI()abstract;
	virtual void InitButton() {}
	virtual void InitStaticText() {}
	virtual void InitEdit() {}
	virtual void InitListBox() {}
	virtual void InitDropListCombo() {}
	virtual void InitSlider() {}
	virtual void InitFrame() {}
	virtual void InitImageControl() {}
	virtual void InitScrollBar() {}
	virtual void InitFormatedText() {}
	virtual void InitImageText() {}
	virtual void InitUserControl() {}

public:
	virtual void showDialog();
	virtual void closeDialog()abstract;

public:
	void Init();
	void InitGUIName(vector<tuple<int, string>> _vecTemp);
	void InitControlName(EControlType _eControlType, vector<string> _vecName);
	void AddTimeFunc(std::function<void(float)> _funTime, std::function<void(float)> _funTimeEnd, float _fLifeTime);
	void UpdateTimeFunc(float _fElapsed);
	void ResetTimeFunc();
};

class CGUIAnimatorGameGroup : public CGUIAnimator
{
public:
	enum EFuncType
	{
		FT_VOID,
		FT_VOID_VEC,
		FT_VOID_END,
		FT_TIME,
		FT_END
	};

private:
	float m_fTimeLength;
	float m_fTime;
	
	EFuncType m_eFuncType;
	std::function<void(void)> m_func;
	std::vector<std::function<void(void)>> m_vecFunc;
	bool m_bFuncEnd = false;

	std::function<void(float)> m_funcTime;

public:
	CGUIAnimatorGameGroup(float fTimeLength, std::function<void(void)> _func, EFuncType _eFuncType = EFuncType::FT_VOID, std::function<void(float)> _funcTime = [](float) {})
	{
		m_fTime = 0;
		m_fTimeLength = fTimeLength;
		m_func = _func;
		m_funcTime = _funcTime;
		m_eFuncType = _eFuncType;
		m_bFuncEnd = false;
	}

	virtual bool isActive()
	{
		return true;
	}

	virtual void onFrameMove(CGUIControl * pCtrl, float fElapsed);

	void onFrameMove_Func();
	void onFrameMove_FuncVec();
	void onFrameMove_FuncEnd();

	CGUIAnimator* clone() override
	{
		return new CGUIAnimatorGameGroup(m_fTimeLength, m_func);
	}
};
