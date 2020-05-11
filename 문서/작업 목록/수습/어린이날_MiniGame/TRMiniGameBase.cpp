#include "stdafx.h"
#include "TRMiniGameBase.h"
//
#include "TRMiniGameQuestion_Quiz.h"
#include "TRMiniGameQuestion_NpcView.h"

#include "TRMiniGameAnswer_ChoiceNum.h"
#include "TRMiniGameAnswer_ChoiceOX.h"
#include "TRMiniGameAnswer_ChoiceSRP.h"
#include "TRMiniGameAnswer_StringAnswer.h"

CTRMiniGameBase::CTRMiniGameBase()
{
}

CTRMiniGameBase::~CTRMiniGameBase()
{
}

void CTRMiniGameBase::showDialog()
{
}

void CTRMiniGameBase::closeDialog()
{
}

void CTRMiniGameBase::initQuestionDlg(int iType)
{
	if(m_pQuestion)
	{
		if(m_pQuestion->getType() == iType)
			return;
		else
			m_pQuestion.reset();
	}

	switch(iType)
	{
	case CTRMiniGameQuestion::QuestionType::Question_QUIZ:
		m_pQuestion = make_shared<CTRMiniGameQuestion_Quiz>();
		break;
	case CTRMiniGameQuestion::QuestionType::Question_NPCVIEW:
		m_pQuestion = make_shared<CTRMiniGameQuestion_NpcView>();
		break;
	}
}

void CTRMiniGameBase::initAnswerDlg(int iType)
{
	if(m_pAnswer)
	{
		if(m_pAnswer->getType() == iType)
			return;
		else
			m_pAnswer.reset();
	}

	switch(iType)
	{
	case CTRMiniGameAnswer::AnswerType::Answer_STRING:
		m_pAnswer = make_shared<CTRMiniGameAnswer_StringAnswer>();
		break;
	case CTRMiniGameAnswer::Answer_CHOICENUM:
		m_pAnswer = make_shared<CTRMiniGameAnswer_ChoiceNum>();
		break;
	case CTRMiniGameAnswer::Answer_CHOICEOX:
		m_pAnswer = make_shared<CTRMiniGameAnswer_ChoiceOX>();
		break;
	case CTRMiniGameAnswer::Answer_SRP:
		m_pAnswer = make_shared<CTRMiniGameAnswer_ChoiceSRP>();
		break;
	}
}




