#pragma once
#include "gameui/TRUserInterface.h"

class CTRMiniGameQuestion
{
public:
	enum QuestionType
	{
		Question_NONE,
		Question_QUIZ,
		Question_NPCVIEW,
	};

private:
	QuestionType m_eType;

protected:
	CGUIDialog* m_pDlg = nullptr;

public:
	CTRMiniGameQuestion(QuestionType eType);
	virtual ~CTRMiniGameQuestion();

public:
	virtual void Update(float fElapsed) {}

public:
	QuestionType getType()const { return m_eType; }
};



