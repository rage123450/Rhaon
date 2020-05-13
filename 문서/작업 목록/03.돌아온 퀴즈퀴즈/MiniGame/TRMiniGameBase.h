#pragma once
#include "TRTimeFuncHandler.h"

class CTRMiniGameBase :
	public IntTask
{
public:
	enum EGameStep
	{
		GAMESTEP_BEGIN_BEFORE,
		GAMESTEP_BEGIN_WHILE,
		GAMESTEP_BEGIN_AFTER,
		GAMESTEP_SELECT_BEFORE,
		GAMESTEP_SELECT_WHILE,
		GAMESTEP_SELECT_AFTER,
		GAMESTEP_RESULT_BEFORE,
		GAMESTEP_RESULT_WHILE,
		GAMESTEP_RESULT_AFTER,
		GAMESTEP_EXIT_BEFORE,
		GAMESTEP_EXIT_WHILE,
		GAMESTEP_EXIT_AFTER,
		GAMESTEP_END,
	};

protected:
	typedef struct tagTimeFunc
	{
		bool bEnd = false;
		float fElapsed = 0.0f;
		float fLife = 0.0f;
		std::function<void(float)> funcTime = [](float) {};
		std::function<void(float)> funcTimeEnd = [](float) {};
	}TIME_FUNC;

private:
	EGameStep m_eGameStep = EGameStep::GAMESTEP_END;
	bool m_bUpdate = false;
	std::shared_ptr<CTRTimeFuncHandler> m_pTimeFuncHandler = nullptr;

	std::tuple<CRectInfo, float, float> m_tupleBarFrame;	// CRectInfo, Width, Height
	std::tuple<CRectInfo, float, float> m_tupleBarImage;	// CRectInfo, Width, Height

public:
	CTRMiniGameBase() = default;
	virtual ~CTRMiniGameBase() = default;

public:
	virtual void showDialog() abstract;
	virtual void closeDialog() abstract;

	virtual void onFrameMove(float _fTime) override;

	virtual void BeginBefore(float _fTime);
	virtual void BeginWhile(float _fTime);
	virtual void BeginAfter(float _fTime);

	virtual void SelectBefore(float _fTime);
	virtual void SelectWhile(float _fTime);
	virtual void SelectAfter(float _fTime);

	virtual void ResultBefore(float _fTime);
	virtual void ResultWhile(float _fTime);
	virtual void ResultAfter(float _fTime);

	virtual void ExitBefore(float _fTime);
	virtual void ExitWhile(float _fTime);
	virtual void ExitAfter(float _fTime);

	virtual void BeginBefore() abstract;
	virtual void BeginWhile() abstract;
	virtual void BeginAfter() abstract;

	virtual void SelectBefore() abstract;
	virtual void SelectWhile() abstract;
	virtual void SelectAfter() abstract;

	virtual void ResultBefore() abstract;
	virtual void ResultWhile() abstract;
	virtual void ResultAfter() abstract;

	virtual void ExitBefore() abstract;
	virtual void ExitWhile() abstract;
	virtual void ExitAfter() abstract;

protected:
	void SelectGameStep();

	void SetBtnFunction(CGUIDialog* _pDlg, std::string _btnName, std::function<bool(CGUIControl*)> _func);
	void SetBtnVisible(CGUIDialog* _pDlg, std::string _btnName, bool _bVisible);
	void SetCtrlUserData(CGUIDialog* _pDlg, std::string _ctrlName, std::string _key, std::string _data);
	void SetCtrlUserData(CGUIDialog* _pDlg, std::string _ctrlName, std::string _key, int _data);

	void InitBar(CGUIFrameImage* _pFrame, CGUIImageCtrl* _pImage);
	void UpdateTimeBar(CGUIFrameImage* _pFrame, CGUIImageCtrl* _pImage, float _fEndTime, float _fElapsed);
	void UpdateStatisticsBar(CGUIFrameImage* _pFrame, CGUIImageCtrl* _pImage, float _fStart, float _fEnd, float _fTotal, float _fEndTime, float _fElapsed);

	void UpdateTimeFunc(std::reference_wrapper<TIME_FUNC> _refTimeFunc, float _fTime);

	void SetVisible(CGUIControl* _pCtrl, bool _bVisible);
	void SetAnimator(CGUIControl * _pCtrl, CGUIAnimator * _pAnimator, bool _bClearLocalVars = true);
	void SetText(CGUIControl* _pCtrl, string _strText);
	void CloseDialog(CGUIDialog* _pDlg, float _fTimeLength = 0.25f);

	void ToggleDialog(CGUIDialog* _pDlg,bool _bVisible);

	int GetValueInt(CGUIControl* _pCtrl, string _strName);
	std::string ReplaceNewLineSTR(std::string _strData);
	
protected:
	inline bool IsVisible(CGUIDialog* _pDlg) { return _pDlg == nullptr ? false : _pDlg->isVisible() ? true : false; }
	inline int GetSafeNum(int _nNum, int _nMin, int _nMax) { return _nNum<_nMin ? _nMin : _nNum>_nMax ? _nMax : _nNum; }
	
public:
	std::reference_wrapper<const EGameStep> GetGameStep()const { return std::cref(m_eGameStep); }
	void SetGameStep(EGameStep _eGameStep) 
	{ 
		m_eGameStep = _eGameStep; 
		m_bUpdate = false; 
		SelectGameStep(); 
	}
	__declspec(property(get = GetGameStep, put = SetGameStep)) std::reference_wrapper<const EGameStep> __eGameStep;

	std::reference_wrapper<const std::shared_ptr<CTRTimeFuncHandler>> GetTimeFuncHandler()const { return std::cref(m_pTimeFuncHandler); }
	void SetTimeFuncHandler(std::shared_ptr<CTRTimeFuncHandler> _pTimeFuncHandler) { m_pTimeFuncHandler = _pTimeFuncHandler; }
	_declspec(property(get = GetTimeFuncHandler, put = SetTimeFuncHandler)) std::reference_wrapper<const std::shared_ptr<CTRTimeFuncHandler>> __pTimeFuncHandler;

	bool GetIsUpdate()const { return m_bUpdate; }
	void SetIsUpdate(bool _bUpdate) { m_bUpdate = _bUpdate; }
	_declspec(property(get = GetIsUpdate, put = SetIsUpdate)) bool __bUpdate;
};

