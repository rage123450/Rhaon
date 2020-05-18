#pragma once
#include "TRMiniGameAssist.h"

class CTRMiniGameQuestion;
class CTRMiniGameAnswer;

class CTRMiniGameBase :
	public CMiniGameAssist,
	public IntTask
{
public:
	enum STATE
	{
		STATE_NONE,
		STATE_OPEN,				
		STATE_WAIT,				
		STATE_READY,
		STATE_START,
		STATE_PLAYING,
		STATE_RESULT,
		STATE_END,
	};

protected:
	shared_ptr<CTRMiniGameQuestion> m_pQuestion = nullptr;
	shared_ptr<CTRMiniGameAnswer> m_pAnswer = nullptr;

protected:
	STATE m_eState = STATE_NONE;
	std::string errmsg;

public:
	CTRMiniGameBase();
	virtual ~CTRMiniGameBase();

public:
	// CMiniGameAssist을(를) 통해 상속됨
	virtual void showDialog() override;
	virtual void closeDialog() override;

	// IntTask으로부터 상속받음
	virtual void onFrameMove(float fElapsed) {}

	virtual void initSubDlg() abstract;
	virtual void onOpen() abstract;
	virtual void onWait() abstract;
	virtual void onReady() abstract;
	virtual void onStart() abstract;
	virtual void onPlaying() abstract;
	virtual void onResult() abstract;
	virtual void onEnd() abstract;
	
public:
	void initQuestionDlg(int iType);
	void initAnswerDlg(int iType);

protected:
	inline STATE ChangeState(STATE _eState) 
	{
		if(getState() == _eState)
		{
			return _eState;
		}

		DBG_OUTPUT("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
		setState(_eState); 
		switch(_eState)
		{
		case CTRMiniGameBase::STATE_OPEN: onOpen(); break;
		case CTRMiniGameBase::STATE_WAIT: onWait(); break;
		case CTRMiniGameBase::STATE_READY: onReady();  break;
		case CTRMiniGameBase::STATE_START: onStart();  break;
		case CTRMiniGameBase::STATE_PLAYING: onPlaying();  break;
		case CTRMiniGameBase::STATE_RESULT: onResult();  break;
		}
		return getState(); 
	}

public:
	void setState(STATE eState) { m_eState = eState; }
	STATE getState()const { return m_eState; }
};

