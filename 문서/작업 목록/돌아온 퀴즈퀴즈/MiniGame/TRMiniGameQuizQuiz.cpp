#include "stdafx.h"

#ifdef _QUIZ_QUIZ_
#include "TRMiniGameQuizQuiz.h"
#include "TRTimeFuncHandler.h"
#include "gui/GUIControlUserValue.h"
#include "gui/GUIItemImageCtrl.h"
#include "gameui/ClientItemInfoLoader.h"
#include "language/LanguageHeader.h"
#include "language/UnicodeTextFile.h"
#include "gui/GUIObjectView.h"
#include "gameui/TRShortTimeMessage.h"
#include "game/TRRewardManager.h"

CTRMiniGameQuizQuiz::CTRMiniGameQuizQuiz() :m_rewardDlg(this)
{
}

CTRMiniGameQuizQuiz::~CTRMiniGameQuizQuiz()
{
	closeDialog();
}

void CTRMiniGameQuizQuiz::showDialog()
{
	closeDialog();
	CTaskManager::getInstance().addTask(this);
	__pTimeFuncHandler = make_shared<CTRTimeFuncHandler>();
	__eGameStep = EGameStep::GAMESTEP_BEGIN_BEFORE;
}

void CTRMiniGameQuizQuiz::closeDialog()
{
	if(m_pDlgMain)
	{
		m_pDlgMain->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_pDlgMain = nullptr;
	}
	if(m_pDlgBase)
	{
		m_pDlgBase->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_pDlgBase = nullptr;
	}

	m_yesNoDlg.closeDialog();

	if(m_mainObjView.hasCharInst())
		m_mainObjView.releaseObjectInst();
	if(m_pMainViewCtrl)
	{
		m_pMainViewCtrl = nullptr;
	}

	if(m_goStopObjView.hasCharInst())
		m_goStopObjView.releaseObjectInst();
	if(m_pGoStopViewCtrl)
	{
		m_pGoStopViewCtrl = nullptr;
	}

	CTaskManager::getInstance().removeTask(this);
}

void CTRMiniGameQuizQuiz::onFrameMove(float _fTime)
{
	__super::onFrameMove(_fTime);
	__pTimeFuncHandler.get()->Update(_fTime);

	m_mainObjView.frameMove(_fTime);
	m_goStopObjView.frameMove(_fTime);
}

void CTRMiniGameQuizQuiz::BeginBefore()
{
	LoadText();

	string errmsg;
	m_pDlgMain = CTRUserInterface::loadGUI("gui/park/QuizQuiz2020/QuizQuiz_Main.gui", errmsg);
	if(!m_pDlgMain)
	{
		return;
	}
	m_pDlgMain->setZOrder(ZORDER_BASE);
	m_pDlgMain->centerPosition();
	m_pDlgMain->setModalDialog(true);
	m_pDlgMain->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
	CGUIManager::getInstance().setFocus(m_pDlgMain->getControlID());

	m_pMent = static_cast<CGUIStaticText*>(m_pDlgMain->findControl("Ment", GUI_SUB_CONTROL_STATIC_TEXT));
	// StringTable : 오너라 런너들아…!!\n너희들의 쌓인 피로들을\n한 번에 날려주마!! 
	SetText(m_pMent, ReplaceNewLineSTR(_STR(QUIZQUIZ_MAINMENT)));

	m_pTakeNumber = static_cast<CGUIStaticText*>(m_pDlgMain->findControl("TakeNumber", GUI_SUB_CONTROL_STATIC_TEXT));
	int iDailyLimit = atoi(CNetClientManager::getInstance().getServerSetting("QuizQuiz_LimitPlayCount", "5").c_str());
	int iPlayCount = CTRUserInterface::getInstance().getQuizQuizPlayCount();
	m_nParticipation = __super::GetSafeNum((iDailyLimit - iPlayCount), 0, iDailyLimit);
	// StringTable : 참여가능횟수: %d 
	SetText(m_pTakeNumber, format(_STR(QUIZQUIZ_PARTICIPATION), m_nParticipation));

	SetBtnFunction(m_pDlgMain, "StartBtn", [&](CGUIControl*)
	{
#ifdef KMW_TEST
		__eGameStep = EGameStep::GAMESTEP_BEGIN_WHILE;
#else
		std::vector<int> vecTickets = CClientItemList::getInstance().getItemInfo(eCharacterKind_NONE, eFuncItemPosition_QUIZQUIZ);
		if(!vecTickets.empty())
			CNetClientManager::getInstance().requestQUIZQUIZ_Start(vecTickets[0]);
		else
			DBG_OUTPUT("error - Not defined item");
#endif // KMW_TST
		return true;
	});

	SetBtnFunction(m_pDlgMain, "CloseBtn", [&](CGUIControl*)
	{
		closeDialog();
		return true;
	});

	InitViewCtrl(m_pMainViewCtrl, m_pDlgMain, "QuizQuiz_Henry", m_mainObjView);

	m_nRound = 0;
}

void CTRMiniGameQuizQuiz::BeginWhile()
{
	SetAnimator(m_pDlgMain, new CGUIAnimatorFadeOutHide(0.25f));

	string errmsg;
	m_pDlgBase = CTRUserInterface::loadGUI("gui/park/QuizQuiz2020/QuizQuiz_Base.gui", errmsg);
	if(!m_pDlgBase)
	{
		return;
	}
	m_pDlgBase->setZOrder(ZORDER_BASE);
	m_pDlgBase->centerPosition();
	m_pDlgBase->setModalDialog(true);
	m_pDlgBase->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
	CGUIManager::getInstance().setFocus(m_pDlgBase->getControlID());

	m_pQuestionCount = static_cast<CGUIStaticText*>(m_pDlgBase->findControl("QuestionCount", GUI_SUB_CONTROL_STATIC_TEXT));
	m_nQuestionCount = 1;
	UpdateQuestionCount(m_nQuestionCount);
	m_nCorrect = 0;

	m_pQuestion = make_unique<CTRMiniGameQuestion_Text>();
	m_pQuestion->LoadText(CTRMiniGameQuestion_Text::ELoadTextType::LOADTEXTTYPE_QUIZQUIZ);
	m_pQuestion->InitText(m_pDlgBase, "QuestionMent", CTRMiniGameQuestion_Text::TEXTTYPE_STATIC);

	m_pCorrect = static_cast<CGUIStaticText*>(m_pDlgBase->findControl("Correct", GUI_SUB_CONTROL_STATIC_TEXT));
	UpdateCorrectCount(m_nCorrect);

	m_pSubject = static_cast<CGUIStaticText*>(m_pDlgBase->findControl("Subject", GUI_SUB_CONTROL_STATIC_TEXT));
	SetText(m_pSubject, "");

	m_pHandImg = static_cast<CGUIImageCtrl*>(m_pDlgBase->findControl("HandImg", GUI_SUB_CONTROL_IMAGE_CTRL));

	m_pItemImg = static_cast<CGUIItemImageCtrl*>(m_pDlgBase->findControl("ItemImg", GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
	if(m_pItemImg)
	{
		m_pItemImg->setViewItemDetail(false);
	}
	UpdateRoundItem();

	SetBtnFunction(m_pDlgBase, "CloseBtn", [&](CGUIControl*)
	{
		closeDialog();
		return true;
	});
	SetBtnVisible(m_pDlgBase, "CloseBtn", false);

	m_pDlgAnswer = CTRUserInterface::loadGUI(m_pDlgBase->getControlID(), "gui/park/QuizQuiz2020/QuizQuiz_AnswerDlg.gui", errmsg);
	if(!m_pDlgAnswer)
	{
		return;
	}
	m_pDlgAnswer->setClientPos(m_pDlgBase->findControl("QuizQuiz_AnswerDlg", GUI_SUB_CONTROL_FRAME)->getClientRect());
	m_pDlgAnswer->setVisible(false);
	m_pAnswer = make_unique<CTRMiniGameAnswer_Choice>();
	m_pAnswer->InitBtnAct(m_pDlgAnswer,
		{
			{"AnswerBtn1",std::bind(&CTRMiniGameQuizQuiz::FuncBtnAnswer,this,placeholders::_1),"answer",0},
			{"AnswerBtn2",std::bind(&CTRMiniGameQuizQuiz::FuncBtnAnswer,this,placeholders::_1),"answer",1},
			{"AnswerBtn3",std::bind(&CTRMiniGameQuizQuiz::FuncBtnAnswer,this,placeholders::_1),"answer",2},
			{"AnswerBtn4",std::bind(&CTRMiniGameQuizQuiz::FuncBtnAnswer,this,placeholders::_1),"answer",3},
		});

	m_pDlgAnswer2 = CTRUserInterface::loadGUI(m_pDlgBase->getControlID(), "gui/park/QuizQuiz2020/QuizQuiz_AnswerDlg2.gui", errmsg);
	if(!m_pDlgAnswer2)
	{
		return;
	}
	m_pDlgAnswer2->setClientPos(m_pDlgBase->findControl("QuizQuiz_AnswerDlg", GUI_SUB_CONTROL_FRAME)->getClientRect());
	m_pDlgAnswer2->setVisible(false);
	m_pAnswer2 = make_unique<CTRMiniGameAnswer_Choice>();
	m_pAnswer2->InitBtnAct(m_pDlgAnswer2,
		{
			{"TrueBtn1",std::bind(&CTRMiniGameQuizQuiz::FuncBtnAnswer2,this,placeholders::_1),"ox",0 },
			{"FalseBtn2",std::bind(&CTRMiniGameQuizQuiz::FuncBtnAnswer2,this,placeholders::_1),"ox",1 },
		});

	m_pDlgAnswer3 = CTRUserInterface::loadGUI(m_pDlgBase->getControlID(), "gui/park/QuizQuiz2020/QuizQuiz_AnswerDlg3.gui", errmsg);
	if(!m_pDlgAnswer3)
	{
		return;
	}
	m_pDlgAnswer3->setClientPos(m_pDlgBase->findControl("QuizQuiz_AnswerDlg", GUI_SUB_CONTROL_FRAME)->getClientRect());
	m_pDlgAnswer3->setVisible(false);
	m_pAnswer3 = make_unique<CTRMiniGameAnswer_Text>();
	SetBtnFunction(m_pDlgAnswer3, "EnterBtn", std::bind(&CTRMiniGameQuizQuiz::FuncBtnAnswer3, this, placeholders::_1));
	m_pAnswer3->__pEdit = static_cast<CGUIEditCtrl*>(m_pDlgAnswer3->findControl("ChatInput", GUI_SUB_CONTROL_EDIT));
	if(m_pAnswer3->__pEdit)
	{
		m_pAnswer3->__pEdit->setMaxNumChars(20);
		m_pAnswer3->__pEdit->setEnableInput(true);
		m_pAnswer3->__pEdit->setText("");
	}

	m_pDlgResult = CTRUserInterface::loadGUI(m_pDlgBase->getControlID(), "gui/park/QuizQuiz2020/QuizQuiz_Result.gui", errmsg);
	if(!m_pDlgResult)
	{
		return;
	}
	m_pDlgResult->setVisible(false);
	m_pStampImg = static_cast<CGUIImageCtrl*>(m_pDlgResult->findControl("Img2", GUI_SUB_CONTROL_IMAGE_CTRL));
	m_pSuccess_1 = static_cast<CGUIImageCtrl*>(m_pDlgResult->findControl("Success_1", GUI_SUB_CONTROL_IMAGE_CTRL));
	m_pSuccess_2 = static_cast<CGUIImageCtrl*>(m_pDlgResult->findControl("Success_2", GUI_SUB_CONTROL_IMAGE_CTRL));
	m_pSuccess_3 = static_cast<CGUIImageCtrl*>(m_pDlgResult->findControl("Success_3", GUI_SUB_CONTROL_IMAGE_CTRL));
	m_pFail_1 = static_cast<CGUIImageCtrl*>(m_pDlgResult->findControl("Fail_1", GUI_SUB_CONTROL_IMAGE_CTRL));
	InitStampImg(m_pStampImg);


	// SubPopup
	m_pDlgSubPopup = CTRUserInterface::loadGUI(m_pDlgBase->getControlID(), "gui/park/QuizQuiz2020/QuizQuiz_SubPopup.gui", errmsg);
	if(!m_pDlgSubPopup)
	{
		return;
	}
	SetBtnFunction(m_pDlgSubPopup, "GoBtn", std::bind(&CTRMiniGameQuizQuiz::FuncBtnGo, this, placeholders::_1));
	SetBtnFunction(m_pDlgSubPopup, "StopBtn", std::bind(&CTRMiniGameQuizQuiz::FuncBtnStop, this, placeholders::_1));

	m_pSubPopupMent = static_cast<CGUIStaticText*>(m_pDlgSubPopup->findControl("Ment", GUI_SUB_CONTROL_STATIC_TEXT));

	ToggleBtnGoStop(true);

	m_pTime = CGUIManager::getInstance().createControl<CGUIImageText>(m_pDlgSubPopup->getControlID());
	if(m_pTime)
	{
		CGUIImageCtrl* pCtrl = static_cast<CGUIImageCtrl*>(m_pDlgSubPopup->findControl("Time", GUI_SUB_CONTROL_IMAGE_CTRL));
		pCtrl->setVisible(false);

		m_pTime->setClientPos(pCtrl->getClientRect());
		m_pTime->setAlign(GUI_HALIGN_CENTER);
		m_pTime->setCharInfo('1', '5', pCtrl->getImage()->getFileName(), CRectWH(292, 398, 73, 114), CPointInfo(-73, 0));
	}

	InitViewCtrl(m_pGoStopViewCtrl, m_pDlgSubPopup, "QuizQuiz_Henry", m_goStopObjView);

	m_pDlgSubPopup->setVisible(false);


	// SubPopup_ItemInfo
	m_pDlgSubPopup_ItemInfo = CTRUserInterface::loadGUI(m_pDlgSubPopup->getControlID(), "gui/park/QuizQuiz2020/QuizQuiz_SubPopup_ItemInfo.gui", errmsg);
	m_pDlgSubPopup_ItemInfo->setClientPos(m_pDlgSubPopup->findControl("ItemInfoDlg", GUI_SUB_CONTROL_FRAME)->getClientRect());
	if(!m_pDlgSubPopup_ItemInfo)
	{
		return;
	}
	m_pGo_Stage = static_cast<CGUIStaticText*>(m_pDlgSubPopup_ItemInfo->findControl("Go_Stage", GUI_SUB_CONTROL_STATIC_TEXT));
	m_pStop_Stage = static_cast<CGUIStaticText*>(m_pDlgSubPopup_ItemInfo->findControl("Stop_Stage", GUI_SUB_CONTROL_STATIC_TEXT));
	m_pGo_ItemImage = static_cast<CGUIItemImageCtrl*>(m_pDlgSubPopup_ItemInfo->findControl("Go_ItemImage", GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
	if(m_pGo_ItemImage)
	{
		m_pGo_ItemImage->setViewItemDetail(false);
	}
	m_pStop_ItemImage = static_cast<CGUIItemImageCtrl*>(m_pDlgSubPopup_ItemInfo->findControl("Stop_ItemImage", GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
	if(m_pStop_ItemImage)
	{
		m_pStop_ItemImage->setViewItemDetail(false);
	}
	UpdateRoundItemSub();
	m_pDlgSubPopup_ItemInfo->setVisible(false);

	m_pGauge = static_cast<CGUIFrameImage*>(m_pDlgBase->findControl("Gauge", GUI_SUB_CONTROL_FRAME));
	m_pGaugeImg = static_cast<CGUIImageCtrl*>(m_pDlgBase->findControl("GaugeImg", GUI_SUB_CONTROL_IMAGE_CTRL));
	InitBar(m_pGauge, m_pGaugeImg);

	m_pHandImg->setClientPos(HAND_POSX, HAND_POSY);
	PlayInitHandImg();

#ifdef KMW_TEST
	//int fdQuizNum = /*1*/822;
	m_nQuizNum = 822;
	m_pQuestion->UpdateText(m_nQuizNum, TIME_TEXT_PRODUCE);

	SelectDlgAnswer(m_nQuizNum);
	UpdateSubject(m_nQuizNum);
	m_fTextLength = static_cast<float>(m_pQuestion->GetTextLengthUTF8(m_nQuizNum));

	PlayInitHandImg();
	__pTimeFuncHandler.get()->Add(
		[&](float _fTime, float)
	{
		PlayHandImg(_fTime, m_nQuizNum);
	},
		[&](float, float)
	{
		__eGameStep = EGameStep::GAMESTEP_SELECT_BEFORE;
	}, TIME_TEXT_PRODUCE + TIME_TEXT_SUPPLE);
#else
	CNetClientManager::getInstance().requestQUIZQUIZ_Question();
#endif // KMW_TEST
}

void CTRMiniGameQuizQuiz::BeginAfter()
{
}

void CTRMiniGameQuizQuiz::SelectBefore()
{
	__pTimeFuncHandler.get()->Add(
		[&](float fElapsed)
	{
		UpdateTimeBar(m_pGauge, m_pGaugeImg, TIME_LIMIT_SUBMIT, fElapsed);
	},
		[&](float)
	{
#ifdef KMW_TEST
		nResult = -1;
#endif // KMW_TEST
		__eGameStep = EGameStep::GAMESTEP_RESULT_BEFORE;
	}, TIME_LIMIT_SUBMIT);
}

void CTRMiniGameQuizQuiz::SelectWhile()
{
}

void CTRMiniGameQuizQuiz::SelectAfter()
{
}

void CTRMiniGameQuizQuiz::ResultBefore()
{
#ifdef KMW_TEST
	ToggleDialog(m_pDlgResult, true);

	nResult = nResult == -1 ? 1 : 0/*CRandomGen::instance.iRandom(0, 1)*/;
	PlayResult(nResult);

	switch(nResult)
	{
	case EResult::RESULT_WIN:
		__pTimeFuncHandler.get()->Add([&](float) {},
			[&](float)
		{
			ToggleDialog(m_pDlgResult, false);

			m_nCorrect += 1;
			UpdateCorrectCount(m_nCorrect);

			if(m_nQuestionCount == MAX_QUIZ)
			{
				__eGameStep = EGameStep::GAMESTEP_EXIT_BEFORE;
				CreateRewardDlg();
			}
			else if(m_nQuestionCount % 2 == 0 && m_nQuestionCount != MAX_QUIZ)
			{
				__eGameStep = EGameStep::GAMESTEP_RESULT_WHILE;
			}
			else
			{
				__eGameStep = EGameStep::GAMESTEP_RESULT_AFTER;
			}
		}, TIME_MARK_SHOW);
		break;

	case EResult::RESULT_LOSE:
		__pTimeFuncHandler.get()->Add([&](float) {},
			[&](float)
		{
			ToggleDialog(m_pDlgResult, false);
			__eGameStep = EGameStep::GAMESTEP_EXIT_BEFORE;
			closeDialog();
		}, TIME_MARK_SHOW);
		break;
	}
#endif // KMW_TEST
}

void CTRMiniGameQuizQuiz::ResultWhile()
{
	UpdateRoundItemSub();
	UpdateGoStopRoundItem();

	ToggleDialog(m_pDlgSubPopup, true);
	ToggleDialog(m_pDlgSubPopup_ItemInfo, true);

	SetBtnVisible(m_pDlgBase, "CloseBtn", false);

	// StringTable : %d단계 통과를 축하 드립니다!\n더 좋은 보상을 원한다면\nGO 버튼을 눌러주세요!!
	SetText(m_pSubPopupMent, format(ReplaceNewLineSTR(_STR(QUIZQUIZ_GOSTOP)).c_str(), __super::GetSafeNum(m_nRound + 1, 1, 4)));
}

void CTRMiniGameQuizQuiz::ResultAfter()
{
#ifdef KMW_TEST
	//int nTempQuizNum = m_nQuestionCount;
	m_nQuizNum = /*CRandomGen::instance.iRandom(1, 1054)*/2;
	switch(m_pQuestion->GetQuizTable(m_nQuizNum).nType)
	{
	case 1:
		if(m_pAnswer)
		{
			m_pAnswer->ResetBtnCheck();
		}
		break;

	case 3:
		if(m_pAnswer2)
		{
			m_pAnswer2->ResetBtnCheck();
		}
		break;
	}
#endif // KMW_TEST

	UpdateTimeBar(m_pGauge, m_pGaugeImg, TIME_LIMIT_SUBMIT, 0.0f);

	m_nQuestionCount += 1;
	UpdateQuestionCount(GetSafeNum(m_nQuestionCount));

#ifdef KMW_TEST
	//nTempQuizNum += 1;
	m_pQuestion->UpdateText(m_nQuizNum, TIME_TEXT_PRODUCE);
	SelectDlgAnswer(m_nQuizNum);
	UpdateSubject(m_nQuizNum);

	UpdateRoundItem();

	m_pHandImg->setClientPos(HAND_POSX, HAND_POSY);
	m_fTextLength = static_cast<float>(m_pQuestion->GetTextLengthUTF8(m_nQuizNum));
	PlayInitHandImg();
	__pTimeFuncHandler.get()->Add(
		[&](float _fTime, float)
	{
		PlayHandImg(_fTime, m_nQuizNum);
	},
		[&](float, float)
	{
		__eGameStep = EGameStep::GAMESTEP_SELECT_BEFORE;
	}, TIME_TEXT_PRODUCE + TIME_TEXT_SUPPLE);
#else
	CNetClientManager::getInstance().requestQUIZQUIZ_Question();
#endif // KMW_TEST
}

void CTRMiniGameQuizQuiz::ExitBefore()
{
}

void CTRMiniGameQuizQuiz::ExitWhile()
{
}

void CTRMiniGameQuizQuiz::ExitAfter()
{
}

void CTRMiniGameQuizQuiz::onSendGiveMsg(std::string & nickname, std::string & strMemo, int iItemNum)
{
	m_rewardDlg.closeDialog();

	closeDialog();
}

bool CTRMiniGameQuizQuiz::onKeyDown(WPARAM wParam)
{
	if(!(__eGameStep == EGameStep::GAMESTEP_SELECT_BEFORE))
	{
		return false;
	}

	switch(wParam)
	{
	case VK_RETURN:
		FuncBtnUpdateAnswer3();
		return true;
	}

	return __super::onKeyDown(wParam);
}

// iUseItemNum : 사용권 번호, iRemainCount : 진행한 플레이 횟수
void CTRMiniGameQuizQuiz::OnRecv_QuizQuizStartAck(int iUseItemNum, int iPlayCount)
{
	int iDailyLimit = atoi(CNetClientManager::getInstance().getServerSetting("QuizQuiz_LimitPlayCount", "5").c_str());
	m_nParticipation = __super::GetSafeNum((iDailyLimit - iPlayCount), 0, iDailyLimit);

	__eGameStep = EGameStep::GAMESTEP_BEGIN_WHILE;
}

// iIndexNum : 순서번호, iQuestionNum : 문제 고유번호
void CTRMiniGameQuizQuiz::OnRecv_QuizQuizQuestionAck(int iIndexNum, int iQuestionNum)
{
	m_nQuizNum = iQuestionNum;
	switch(m_pQuestion->GetQuizTable(m_nQuizNum).nType)
	{
	case 1:
		if(m_pAnswer)
		{
			m_pAnswer->ResetBtnCheck();
		}
		break;

	case 3:
		if(m_pAnswer2)
		{
			m_pAnswer2->ResetBtnCheck();
		}
		break;
	}

	m_pQuestion->UpdateText(m_nQuizNum, TIME_TEXT_PRODUCE);

	SelectDlgAnswer(m_nQuizNum);
	UpdateSubject(m_nQuizNum);

	UpdateRoundItem();

	m_pHandImg->setClientPos(HAND_POSX, HAND_POSY);
	m_fTextLength = static_cast<float>(m_pQuestion->GetTextLengthUTF8(m_nQuizNum));

	PlayInitHandImg();
	__pTimeFuncHandler.get()->Add(
		[&](float _fTime, float)
	{
		PlayHandImg(_fTime, m_nQuizNum);
	},
		[&](float, float)
	{
		__eGameStep = EGameStep::GAMESTEP_SELECT_BEFORE;
	}, TIME_TEXT_PRODUCE + TIME_TEXT_SUPPLE);
}

void CTRMiniGameQuizQuiz::OnRecv_QuizQuizAnswerAck(eServerResult eResult)
{
	switch(eResult)
	{
	case eServerResult_OK_ACK:
		CAudioManager::getInstance().playAudioEffectByFileName("sound\\buil_success.wav");
		PlayResult(EResult::RESULT_WIN);

		__pTimeFuncHandler.get()->Add([&](float) {},
			[&](float)
		{
			ToggleDialog(m_pDlgResult, false);

			m_nCorrect += 1;
			UpdateCorrectCount(m_nCorrect);

			if(m_nQuestionCount == MAX_QUIZ)
			{
				__eGameStep = EGameStep::GAMESTEP_EXIT_BEFORE;
				CNetClientManager::getInstance().requestQUIZQUIZ_Reward();
			}
			else if(m_nQuestionCount % 2 == 0 && m_nQuestionCount != MAX_QUIZ)
			{
				__eGameStep = EGameStep::GAMESTEP_RESULT_WHILE;
			}
			else
			{
				__eGameStep = EGameStep::GAMESTEP_RESULT_AFTER;
			}
		}, TIME_MARK_SHOW);
		break;
	}
}

// strCorrectAnswer : 정답문자열
void CTRMiniGameQuizQuiz::OnRecv_QuizQuizIncorrectAnswerAck(const std::string &strCorrectAnswer)
{
	__pTimeFuncHandler.get()->Reset();

	__eGameStep = EGameStep::GAMESTEP_RESULT_BEFORE;
	ToggleDialog(m_pDlgResult, true);

	CAudioManager::getInstance().playAudioEffectByFileName("sound\\buil_fail.wav");
	PlayResult(EResult::RESULT_LOSE);

	__pTimeFuncHandler.get()->Add([&](float) {},
		[&](float)
	{
		ToggleDialog(m_pDlgResult, false);
		__eGameStep = EGameStep::GAMESTEP_EXIT_BEFORE;
		closeDialog();
	}, TIME_MARK_SHOW);
}

// iRewardItemNum : 보상아이템번호
void CTRMiniGameQuizQuiz::OnRecv_QuizQuizRewardAck(int iRewardItemNum)
{
	CreateRewardDlg(iRewardItemNum);
}

void CTRMiniGameQuizQuiz::OnRecv_QuizQuizFailedAck(eServerResult eResult)
{
	switch(eResult)
	{
	case eServerResult_QUIZQUIZ_INVALID_ITEM:
		// StringTable : 잘못된 사용권 입니다.
		CTRShortTimeMessage::showMessage(_STR(QUIZQUIZ_INVALID_ITEM), 1.0f, ZORDER_POPUP);
		break;

	case eServerResult_QUIZQUIZ_NOTENOUGH_ITEM:
		// StringTable : 사용권이 부족합니다.
		CTRShortTimeMessage::showMessage(_STR(QUIZQUIZ_NOTENOUGH_ITEM), 1.0f, ZORDER_POPUP);
		break;

	case eServerResult_QUIZQUIZ_NOTENOUGH_QUESTION:
		// StringTable : 더 이상 문제가 없습니다.
		CTRShortTimeMessage::showMessage(_STR(QUIZQUIZ_NOTENOUGH_QUESTION), 1.0f, ZORDER_POPUP);
		break;

	case eServerResult_QUIZQUIZ_NOT_PLAYER:
		// StringTable : 플레이중이 아닙니다.
		CTRShortTimeMessage::showMessage(_STR(QUIZQUIZ_NOT_PLAYER), 1.0f, ZORDER_POPUP);
		break;

	case eServerResult_QUIZQUIZ_INCORRECT_ANSWER:
		// StringTable : 오답입니다.
		CTRShortTimeMessage::showMessage(_STR(QUIZQUIZ_INCORRECT_ANSWER), 1.0f, ZORDER_POPUP);
		break;

	case eServerResult_QUIZQUIZ_INVALID_QUESTION:
		// StringTable : 문제가 존재하지 않습니다.
		CTRShortTimeMessage::showMessage(_STR(QUIZQUIZ_INVALID_QUESTION), 1.0f, ZORDER_POPUP);
		break;

	case eServerResult_QUIZQUIZ_PLAY_LIMIT:
		// StringTable : 하루 플레이 횟수 제한에 걸렸습니다.
		CTRShortTimeMessage::showMessage(_STR(QUIZQUIZ_PLAY_LIMIT), 1.0f, ZORDER_POPUP);
		break;

	case eServerResult_QUIZQUIZ_NOT_REWARD_CONDITION:
		// StringTable : 보상 받을 수 없는 상태입니다.
		CTRShortTimeMessage::showMessage(_STR(QUIZQUIZ_NOT_REWARD_CONDITION), 1.0f, ZORDER_POPUP);
		break;

	case eServerResult_QUIZQUIZ_PLAYING_YET:
		// StringTable : 플레이 할 수 없는 상태입니다.
		CTRShortTimeMessage::showMessage(_STR(QUIZQUIZ_PLAYING_YET), 1.0f, ZORDER_POPUP);
		break;

	}
}

bool CTRMiniGameQuizQuiz::FuncBtnAnswer(CGUIControl * _pCtrl)
{
	if(!(__eGameStep == EGameStep::GAMESTEP_SELECT_BEFORE))
	{
		return false;
	}

	if(m_pAnswer)
	{
		m_pAnswer->ToggleBtnCheck(_pCtrl->getUserDataValue()->value.asInt("answer"));
		std::string strValue = to_string(_pCtrl->getUserDataValue()->value.asInt("answer") + 1);

#ifndef KMW_TEST
		CNetClientManager::getInstance().requestQUIZQUIZ_ANSWER(strValue);
#endif // !KMW_TEST
	}

	ToggleDialog(m_pDlgResult, true);
	__pTimeFuncHandler.get()->Reset();
	__eGameStep = EGameStep::GAMESTEP_RESULT_BEFORE;

	return true;
}

bool CTRMiniGameQuizQuiz::FuncBtnAnswer2(CGUIControl * _pCtrl)
{
	if(!(__eGameStep == EGameStep::GAMESTEP_SELECT_BEFORE))
	{
		return false;
	}

	if(m_pAnswer2)
	{
		m_pAnswer2->ToggleBtnCheck(_pCtrl->getUserDataValue()->value.asInt("ox"));
		std::string strValue = GetBtnValueOX(_pCtrl->getUserDataValue()->value.asInt("ox"));

#ifndef KMW_TEST
		CNetClientManager::getInstance().requestQUIZQUIZ_ANSWER(strValue);
#endif // !KMW_TEST
	}

	ToggleDialog(m_pDlgResult, true);
	__pTimeFuncHandler.get()->Reset();
	__eGameStep = EGameStep::GAMESTEP_RESULT_BEFORE;

	return true;
}

bool CTRMiniGameQuizQuiz::FuncBtnAnswer3(CGUIControl * _pCtrl)
{
	if(!(__eGameStep == EGameStep::GAMESTEP_SELECT_BEFORE))
	{
		return false;
	}

	FuncBtnUpdateAnswer3();

	return true;
}

void CTRMiniGameQuizQuiz::FuncBtnUpdateAnswer3()
{
	if(m_pAnswer3)
	{
		string temp = m_pAnswer3->__strText;
		CNetClientManager::getInstance().requestQUIZQUIZ_ANSWER(m_pAnswer3->__strText);
	}

	ToggleDialog(m_pDlgResult, true);
	__pTimeFuncHandler.get()->Reset();
	__eGameStep = EGameStep::GAMESTEP_RESULT_BEFORE;
}

bool CTRMiniGameQuizQuiz::FuncBtnGo(CGUIControl * _pCtrl)
{
	OffAllDlgAnswer({ m_pDlgAnswer ,m_pDlgAnswer2 ,m_pDlgAnswer3 });

	SetAnimator(m_pQuestion->__pStaticText, new CGUIAnimatorFadeOutHide(0.2f));
	SetAnimator(m_pHandImg, new CGUIAnimatorFadeOutHide(0.2f));

	ToggleBtnGoStop(false);
	ToggleDialog(m_pDlgSubPopup_ItemInfo, false);

	//SetBtnVisible(m_pDlgBase, "CloseBtn", true);

	// StringTable : %d교시 시작!!\n자리에 앉아!
	SetText(m_pSubPopupMent, format(ReplaceNewLineSTR(_STR(QUIZQUIZ_START)).c_str(), __super::GetSafeNum(m_nRound + 2, 1, 5)));
	SetVisible(m_pTime, true);

	__pTimeFuncHandler.get()->Add(
		[&](float _fTime)
	{
		int n = _fTime;
		m_pTime->setText(format("%d", static_cast<int>(TIME_TEXT_PRODUCE) - static_cast<int>(_fTime)));
	},
		[&](float)
	{
		ToggleDialog(m_pDlgSubPopup, false);

		SetText(m_pQuestion->__pStaticText, "");
		SetVisible(m_pQuestion->__pStaticText, true);
		SetVisible(m_pHandImg, true);
		SetVisible(m_pTime, false);
		ToggleBtnGoStop(true);

		m_nRound += 1;

		__eGameStep = EGameStep::GAMESTEP_RESULT_AFTER;
	}, TIME_TEXT_PRODUCE + TIME_TEXT_SUPPLE);
	return true;
}

bool CTRMiniGameQuizQuiz::FuncBtnStop(CGUIControl * _pCtrl)
{
	// StringTable : 퀴즈를 포기하고 보상을 획득하시겠습니까?
	m_yesNoDlg.showDialog(_STR(QUIZQUIZ_REWARD), this, &CTRMiniGameQuizQuiz::showStop, nullptr, "yesno.gui", ZORDER_POPUP);
	return true;
}

void CTRMiniGameQuizQuiz::OffAllDlgAnswer(std::vector<CGUIDialog*> _vecDlg)
{
	for(auto& i : _vecDlg)
	{
		if(i)
		{
			ToggleDialog(i, false);
		}
	}
}

void CTRMiniGameQuizQuiz::SelectDlgAnswer(int _nNum)
{
	OffAllDlgAnswer({ m_pDlgAnswer ,m_pDlgAnswer2 ,m_pDlgAnswer3 });

	if(!m_pQuestion)
	{
		return;
	}

	switch(m_pQuestion->GetQuizTable(_nNum).nType)
	{
	case 1:
		ToggleDialog(m_pDlgAnswer, true);
		m_pAnswer->SetBtnText(
			{
				m_pQuestion->GetQuizTable(_nNum).strFirst,
				m_pQuestion->GetQuizTable(_nNum).strSecond,
				m_pQuestion->GetQuizTable(_nNum).strThird,
				m_pQuestion->GetQuizTable(_nNum).strFourth
			});
		break;
	case 2:
		ToggleDialog(m_pDlgAnswer3, true);
		if(m_pAnswer3 && m_pAnswer3->__pEdit)
		{
			m_pDlgAnswer3->setDialogListener(getCommandTargetID());
			CGUIManager::getInstance().setFocus(m_pAnswer3->__pEdit->getControlID());
			m_pAnswer3->__pEdit->setText("");
		}
		break;
	case 3:
		ToggleDialog(m_pDlgAnswer2, true);
		break;
	}
}

void CTRMiniGameQuizQuiz::PlayResult(int _nResult)
{
	SetVisible(m_pStampImg, false);
	SetVisible(m_pSuccess_1, false);
	SetVisible(m_pSuccess_2, false);
	SetVisible(m_pSuccess_3, false);
	SetVisible(m_pFail_1, false);

	switch(_nResult)
	{
	case 0:
		CAudioManager::getInstance().playAudioEffectByFileName("sound\\buil_success.wav");
		SetVisible(m_pStampImg, true);
		UpdateStampImg(m_pStampImg, EResult::RESULT_WIN);
		SetAnimator(m_pStampImg, new CGUIAnimatorScale(0.2f, 2.f, 1.f));
		SetVisible(m_pSuccess_1, true);
		SetVisible(m_pSuccess_2, true);
		SetVisible(m_pSuccess_3, true);
		break;

	case 1:
		CAudioManager::getInstance().playAudioEffectByFileName("sound\\buil_fail.wav");
		SetVisible(m_pStampImg, true);
		UpdateStampImg(m_pStampImg, EResult::RESULT_LOSE);
		SetAnimator(m_pStampImg, new CGUIAnimatorScale(0.2f, 2.f, 1.f));
		SetVisible(m_pFail_1, true);
		break;
	}
}

void CTRMiniGameQuizQuiz::PlayInitHandImg()
{
	m_nCharIdx = 0;
}

void CTRMiniGameQuizQuiz::PlayHandImg(float _fTime, int _fdQuizNum)
{
	m_fElapsed += _fTime;

	if(m_fElapsed >= TIME_TEXT_PRODUCE * (1.0f / m_fTextLength))
	{
		m_fElapsed = 0.0f;

		if(!m_pQuestion)
		{
			return;
		}

		std::vector<int> vecChar = m_pQuestion->GetTextSentence(_fdQuizNum);
		if(vecChar.empty())
		{
			DBG_OUTPUT("%s, %d", __FUNCTION__, _fdQuizNum);
			closeDialog();
			return;
		}

		int nIdx = vecChar[m_nCharIdx];
		switch(nIdx)
		{
		case 0:
			m_pHandImg->setClientPos(m_pHandImg->getClientRect().left + HAND_GAPX, m_pHandImg->getClientRect().top);
			break;

		case 1:
			m_pHandImg->setClientPos(m_pHandImg->getClientRect().left + HAND_GAPX_SPACE, m_pHandImg->getClientRect().top);
			break;

		case 2:
			m_pHandImg->setClientPos(HAND_POSX + HAND_POSX_SUPPLE, m_pHandImg->getClientRect().top + HAND_GAPY);
			break;
		}

		m_nCharIdx += 1;
	}
}

void CTRMiniGameQuizQuiz::UpdateQuestionCount(int _nCount)
{
	SetText(m_pQuestionCount, format("문제%d", GetSafeNum(_nCount)));
}

void CTRMiniGameQuizQuiz::UpdateCorrectCount(int _nCount)
{
	SetText(m_pCorrect, format("%02d/%02d", __super::GetSafeNum(_nCount, 0, MAX_QUIZ), MAX_QUIZ));
}

void CTRMiniGameQuizQuiz::showStop()
{
	__eGameStep = EGameStep::GAMESTEP_EXIT_BEFORE;

#ifdef KMW_TEST
	CreateRewardDlg();
#else
	CNetClientManager::getInstance().requestQUIZQUIZ_Reward();
#endif // KMW_TEST
}

void CTRMiniGameQuizQuiz::CreateRewardDlg()
{
#ifdef KMW_TEST
	RewardInfo tRewardInfo;
	//tRewardInfo.iRewardID = arrTest[m_nRound];
	tRewardInfo.iRewardID = m_vecReward[m_nRound];
	tRewardInfo.eRewardType = eRewardCondition::eRewardCondition_ITEM;
	tRewardInfo.iRewardCount = 1;
	m_rewardDlg.showDialog(tRewardInfo, "gui/park/QuizQuiz2020/QuizQuiz_RewardPopup.gui", ZORDER_POPUP);
#endif // KMW_TEST
}

void CTRMiniGameQuizQuiz::CreateRewardDlg(int _nRewardItemNum)
{
	RewardInfo tRewardInfo;
	tRewardInfo.iRewardID = _nRewardItemNum;
	tRewardInfo.eRewardType = eRewardCondition::eRewardCondition_ITEM;
	tRewardInfo.iRewardCount = 1;
	m_rewardDlg.showDialog(tRewardInfo, "gui/park/QuizQuiz2020/QuizQuiz_RewardPopup.gui", ZORDER_POPUP);

	CTRRewardManager::getInstance().getReward(eRewardCondition_ITEM, _nRewardItemNum, 1, true);
}

void CTRMiniGameQuizQuiz::UpdateRoundItem()
{
#ifdef KMW_TEST
	//const int iUnique = arrTest[__super::GetSafeNum(m_nRound, 0, 4)];
	const int iUnique = m_vecReward[__super::GetSafeNum(m_nRound, 0, 4)];
#else
	const int iUnique = m_vecReward[__super::GetSafeNum(m_nRound, 0, 4)];
#endif // KMW_TEST

	const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getRealItemInfo(iUnique);
	if(pItemInfo && m_pItemImg)
	{
		m_pItemImg->setRealItemImage(pItemInfo);
	}
}

void CTRMiniGameQuizQuiz::UpdateRoundItemSub()
{
#ifdef KMW_TEST
	//const int iGoUnique = arrTest[__super::GetSafeNum(m_nRound + 1, 0, 4)];
	//const int iStopUnique = arrTest[__super::GetSafeNum(m_nRound, 0, 3)];
	const int iGoUnique = m_vecReward[__super::GetSafeNum(m_nRound + 1, 0, 4)];
	const int iStopUnique = m_vecReward[__super::GetSafeNum(m_nRound, 0, 3)];
#else
	const int iGoUnique = m_vecReward[__super::GetSafeNum(m_nRound + 1, 0, 4)];
	const int iStopUnique = m_vecReward[__super::GetSafeNum(m_nRound, 0, 3)];
#endif // KMW_TEST

	const CItemInfoNode *pGoItemInfo = CClientItemList::getInstance().getRealItemInfo(iGoUnique);
	if(pGoItemInfo && m_pGo_ItemImage)
	{
		m_pGo_ItemImage->setRealItemImage(pGoItemInfo);
	}

	const CItemInfoNode *pStopItemInfo2 = CClientItemList::getInstance().getRealItemInfo(iStopUnique);
	if(pStopItemInfo2 && m_pStop_ItemImage)
	{
		m_pStop_ItemImage->setRealItemImage(pStopItemInfo2);
	}
}

void CTRMiniGameQuizQuiz::UpdateGoStopRoundItem()
{
	SetText(m_pGo_Stage, format("%d단계", __super::GetSafeNum(m_nRound + 2, 0, 5)));
	SetText(m_pStop_Stage, format("%d단계", __super::GetSafeNum(m_nRound + 1, 0, 4)));
}

void CTRMiniGameQuizQuiz::InitStampImg(CGUIImageCtrl * _pImg)
{
	if(_pImg)
	{
		CRectInfo RectInfo;
		_pImg->getSrcRect(RectInfo);

		m_StampWin = CRectInfo(RectInfo.left, RectInfo.top, RectInfo.left + RectInfo.width(), RectInfo.top + RectInfo.height());
		m_StampLose = CRectInfo(RectInfo.left + RectInfo.width(), RectInfo.top, (RectInfo.left + RectInfo.width()) + RectInfo.width(), RectInfo.height());
	}
}

void CTRMiniGameQuizQuiz::UpdateStampImg(CGUIImageCtrl * _pImg, EResult _eResult)
{
	if(!_pImg)
	{
		return;
	}

	switch(_eResult)
	{
	case CTRMiniGameQuizQuiz::RESULT_WIN:
		_pImg->setSrcRect(m_StampWin);
		break;
	case CTRMiniGameQuizQuiz::RESULT_LOSE:
		_pImg->setSrcRect(m_StampLose);
		break;
	}
}

void CTRMiniGameQuizQuiz::ToggleBtnGoStop(bool _bVisible)
{
	SetBtnVisible(m_pDlgSubPopup, "GoBtn", _bVisible);
	SetBtnVisible(m_pDlgSubPopup, "StopBtn", _bVisible);
}

std::string CTRMiniGameQuizQuiz::GetBtnValueOX(int _nValue)
{
	switch(_nValue)
	{
	case 0: return "o";
	case 1: return "x";
	}

	return std::string();
}

void CTRMiniGameQuizQuiz::UpdateSubject(int _nNum)
{
	if(!m_pQuestion)
	{
		return;
	}

	std::string strSubject;
	switch(m_pQuestion->GetQuizTable(_nNum).nSubject)
	{
	case 1: strSubject = "상식"; break;
	case 2: strSubject = "사회"; break;
	case 3: strSubject = "넌센스"; break;
	case 4: strSubject = "수도"; break;
	case 5: strSubject = "테런"; break;
	}

	SetText(m_pSubject, strSubject);
}

bool CTRMiniGameQuizQuiz::LoadText()
{
	CTextFileToPackage filereader(true);
	if(!filereader.open("script\\Content\\EssenQuizQuiz_Reward.txt"))
	{
		return false;
	}

	try
	{
		boost::regex re_info(
			"(.+?),"
			"(.+?)"
		);

		std::string buf;

		while(filereader.getLine(buf))
		{
			stringutil::strip(buf);

			// 빈줄은 걸러낸다.
			if(buf.empty())
			{
				continue;
			}

			// 주석은 걸러낸다.
			if(stringutil::startswith(buf, "//"))
			{
				continue;
			}

			// 정규식으로 파싱한다.
			boost::smatch results;
			boost::regex_match(buf, results, re_info);

			if(results.size() < 3)
			{
				throw exception(("[results Err]" + buf).c_str());
			}

			m_vecReward.push_back(atoi(results[2].str().c_str()));
		}
	}
	catch(const std::exception& e)
	{
		TRDBG_OUTPUT_ERROR("%s - %s", __FUNCTION__, e.what());
		_ASSERTE(FALSE);
		return false;
	}

	return true;
}

void CTRMiniGameQuizQuiz::InitViewCtrl(CGUIUserControl * _pViewCtrl, CGUIDialog * _pDlg, std::string _strModelName, CTRObjectView & _ObjView)
{
	if(_pViewCtrl == nullptr)
	{
		_pViewCtrl = static_cast<CGUIUserControl*>(_pDlg->findControl("CharacterView", GUI_SUB_CONTROL_USER_CTRL));
	}

	if(_pViewCtrl)
	{
		std::string modelName = _strModelName;

		if(modelName.empty() == false)
		{
			GUI_OBJECT::createEffectView(&_ObjView, _pViewCtrl, modelName);
			GUI_OBJECT::setFovy(&_ObjView, CONST_PI / 10);
			GUI_OBJECT::setAnimation(&_ObjView, format("ready"), true);
			GUI_OBJECT::setRadius(&_ObjView, 35.f, 115.f);
		}
	}
}
#endif // _QUIZ_QUIZ_