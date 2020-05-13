#pragma once
#ifdef _QUIZ_QUIZ_
#include "TRMiniGameBase.h"
#include "TRMiniGameQuestion_Text.h"
#include "TRMiniGameAnswer_Text.h"
#include "TRMiniGameAnswer_Choice.h"
#include "gameui/YesNoDialog.h"
#include "gameui/TRRewardItemInfoDlg.h"
#include "NetClientManager.h"
#include "gameui/TRObjectView.h"

//#define KMW_TEST


class CTRShowDefaultRewardDlg;

class CTRMiniGameQuizQuiz :
	public CTRMiniGameBase,
	public IntRewardGiveMessageHandler,
	public CTRCommandTarget
{
private:
	static constexpr int MAX_QUIZ = 10;

	static constexpr float TIME_TEXT_PRODUCE = 3.0f;
	static constexpr float TIME_TEXT_SUPPLE = 0.1f;
	static constexpr float TIME_LIMIT_SUBMIT = 5.0f;
	static constexpr float TIME_MARK_SHOW = 2.0f;

	static constexpr int HAND_POSX = 550;
	static constexpr int HAND_POSX_SUPPLE = 18;
	static constexpr int HAND_POSY = 385 + 5;
	static constexpr int HAND_GAPX = 11;
	static constexpr int HAND_GAPX_SPACE = 5 + 5;
	static constexpr int HAND_GAPY = 20;

	static constexpr float ZORDER_BASE = -4.0f;
	static constexpr float ZORDER_POPUP = ZORDER_BASE - 1.0f;

private:
	enum EResult
	{
		RESULT_WIN,
		RESULT_LOSE,
		RESULT_END
	};

private:
	CGUIDialog* m_pDlgMain = nullptr;
	CGUIStaticText* m_pMent = nullptr;
	CGUIStaticText* m_pTakeNumber = nullptr;
	int m_nParticipation = 0;

	CGUIDialog* m_pDlgBase = nullptr;
	CGUIStaticText* m_pQuestionCount = nullptr;
	CGUIStaticText* m_pCorrect = nullptr;
	CGUIStaticText* m_pSubject = nullptr;
	int m_nQuestionCount = 1;
	int m_nCorrect = 0;
	CGUIImageCtrl* m_pHandImg = nullptr;
	CGUIItemImageCtrl* m_pItemImg = nullptr;

	std::unique_ptr<CTRMiniGameQuestion_Text> m_pQuestion = nullptr;

	CGUIFrameImage* m_pGauge = nullptr;
	CGUIImageCtrl* m_pGaugeImg = nullptr;

	CGUIDialog* m_pDlgAnswer = nullptr;		// 4지선다
	CGUIDialog* m_pDlgAnswer2 = nullptr;	// ox
	CGUIDialog* m_pDlgAnswer3 = nullptr;	// 주관식

	std::unique_ptr<CTRMiniGameAnswer_Choice> m_pAnswer = nullptr;
	std::unique_ptr<CTRMiniGameAnswer_Choice> m_pAnswer2 = nullptr;
	std::unique_ptr<CTRMiniGameAnswer_Text> m_pAnswer3 = nullptr;

	CGUIDialog* m_pDlgResult = nullptr;
	CGUIImageCtrl* m_pStampImg = nullptr;
	CGUIImageCtrl* m_pSuccess_1 = nullptr;
	CGUIImageCtrl* m_pSuccess_2 = nullptr;
	CGUIImageCtrl* m_pSuccess_3 = nullptr;
	CGUIImageCtrl* m_pFail_1 = nullptr;

	CGUIDialog* m_pDlgSubPopup = nullptr;
	CGUIDialog* m_pDlgSubPopup_ItemInfo = nullptr;
	CGUIStaticText* m_pGo_Stage = nullptr;
	CGUIStaticText* m_pStop_Stage = nullptr;
	CGUIItemImageCtrl* m_pGo_ItemImage = nullptr;
	CGUIItemImageCtrl* m_pStop_ItemImage = nullptr;
	CGUIStaticText* m_pSubPopupMent = nullptr;
	CGUIImageText* m_pTime = nullptr;

	CYesNoDialogEx<CTRMiniGameQuizQuiz> m_yesNoDlg;
	CTRShowRewardItemInfoDlg m_rewardDlg;

	float m_fElapsed = 0.0f;
	float m_fTextLength = 0.0f;
	int m_nCharIdx = 0;

	CRectInfo m_StampWin;
	CRectInfo m_StampLose;

	int m_nRound = 0;
	std::vector<int> m_vecReward;
	int m_nQuizNum = 0;

	CGUIUserControl* m_pMainViewCtrl = nullptr;
	CTRObjectView m_mainObjView;

	CGUIUserControl* m_pGoStopViewCtrl = nullptr;
	CTRObjectView m_goStopObjView;

#ifdef KMW_TEST
	int arrTest[5] = { 85121,85123,85125,85127,85129 };
	int nResult = 0;
	int temp = 0;
#endif // KMW_TEST

public:
	CTRMiniGameQuizQuiz();
	virtual ~CTRMiniGameQuizQuiz();

public:
	// CTRMiniGameBase을(를) 통해 상속됨
	virtual void showDialog() override;
	virtual void closeDialog() override;

	virtual void onFrameMove(float _fTime) override;

	virtual void BeginBefore() override;
	virtual void BeginWhile() override;
	virtual void BeginAfter() override;

	virtual void SelectBefore() override;
	virtual void SelectWhile() override;
	virtual void SelectAfter() override;

	virtual void ResultBefore() override;
	virtual void ResultWhile() override;
	virtual void ResultAfter() override;

	virtual void ExitBefore() override;
	virtual void ExitWhile() override;
	virtual void ExitAfter() override;

	// IntRewardGiveMessageHandle으로부터 상속받음
	virtual void onSendGiveMsg(std::string & nickname, std::string & strMemo, int iItemNum = 0);

	// CTRCommandTarget으로부터 상속받음
	virtual bool onKeyDown(WPARAM wParam) override;

public: // server 응답 처리
	// void CNetClientManager::requestQUIZQUIZ_Start(재화아이템 번호)
	// void CNetClientManager::requestQUIZQUIZ_Question()
	// void CNetClientManager::requestQUIZQUIZ_ANSWER(const std::string& strAnswer)
	// void CNetClientManager::requestQUIZQUIZ_Reward()
	void OnRecv_QuizQuizStartAck(int iUseItemNum, int iPlayCount);				// 사용권 번호, 남은 개수 
	void OnRecv_QuizQuizQuestionAck(int iIndexNum, int iQuestionNum);				// 순서번호, 문제 고유번호
	void OnRecv_QuizQuizAnswerAck(eServerResult eResult);
	void OnRecv_QuizQuizIncorrectAnswerAck(const std::string &strCorrectAnswer);	// 정답문자열
	void OnRecv_QuizQuizRewardAck(int iRewardItemNum);								// 보상아이템번호
	void OnRecv_QuizQuizFailedAck(eServerResult eResult);

private:
	bool FuncBtnAnswer(CGUIControl* _pCtrl);
	bool FuncBtnAnswer2(CGUIControl* _pCtrl);
	bool FuncBtnAnswer3(CGUIControl* _pCtrl);
	void FuncBtnUpdateAnswer3();

	bool FuncBtnGo(CGUIControl* _pCtrl);
	bool FuncBtnStop(CGUIControl* _pCtrl);

	void OffAllDlgAnswer(std::vector<CGUIDialog*> _vecDlg);
	void SelectDlgAnswer(int _nNum);

	void PlayResult(int _nResult);
	void PlayInitHandImg();
	void PlayHandImg(float _fTime, int _fdQuizNum);

	void UpdateQuestionCount(int _nCount);
	void UpdateCorrectCount(int _nCount);

	int GetSafeNum(int _nNum) { return __super::GetSafeNum(_nNum, 1, MAX_QUIZ); }

	void showStop();
	void CreateRewardDlg();
	void CreateRewardDlg(int _nRewardItemNum);

	void UpdateRoundItem();
	void UpdateRoundItemSub();
	void UpdateGoStopRoundItem();

	void InitStampImg(CGUIImageCtrl* _pImg);
	void UpdateStampImg(CGUIImageCtrl * _pImg, EResult _eResult);

	void ToggleBtnGoStop(bool _bVisible);

	std::string GetBtnValueOX(int _nValue);

	void UpdateSubject(int _nNum);

	bool LoadText();

	void InitViewCtrl(CGUIUserControl * _pViewCtrl, CGUIDialog* _pDlg, std::string _strModelName, CTRObjectView& _ObjView);
};
#endif // _QUIZ_QUIZ_

