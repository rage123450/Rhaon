#pragma once
#include "TRScissorsRockPaper_Game.h"
//
#include "gameui/YesNoDialog.h"
#include "gameui/TRObjectView.h"
#include "gameui/TRRewardItemInfoDlg.h"

class CTRScissorsRockPaper_RewardDlg;
class CTRShowDefaultRewardDlg;

class CTRScissorsRockPaper_GameAlone :
	public IntTask,
	public IntRewardGiveMessageHandler,
	public CTRScissorsRockPaper_Game,
	public enable_shared_from_this<CTRScissorsRockPaper_GameAlone>
{
private:
	static constexpr int MAX_ROUNDITEM = 4;
	static constexpr int MAX_UNMANIPULATED = 3;
	static constexpr int MAX_WIN = 3;
	static constexpr int MAX_LOSE = 1;
	static constexpr int GAP_UNMANIPULATED = 15;

	static constexpr float USER_SELECT_TIME = 5.0f;
	static constexpr float RESULT_DELAY_TIME = 2.67f;
	static constexpr float RESULT_NEXT_STEP = RESULT_DELAY_TIME + 2.0f;
	static constexpr float RESULT_WAIT_TIME = 1.0f;

private:
	enum EProgressStep		// 진행 단계
	{
		PS_BASE_SCREEN,				// 기본 화면
		PS_START_SELECTION_TIMER,	// 선택 타이머 시작
		PS_SELECT_TIMER_END,		// 선택 타이머 종료
		PS_USER_NO_OPERATION,		// 유저 미조작 시
		PS_USER_LOSE,				// 유저 패배
		PS_USER_WIN,				// 유저 승리
		PS_USER_DRAW,				// 유저 무승부
		PS_WAIT_ROUNDRESULT,		// 라운드결과 이후 대기중
		PS_END
	};

	enum ERoundResult
	{
		RR_WIN,
		RR_LOSE,
		RR_DRAW,
		RR_END
	};

	enum ESelectSRP
	{
		SS_SCISSORS,
		SS_ROCK,
		SS_PAPER,
		SS_END
	};

private:	// Name
	enum EGUIName
	{
		GN_BASE,
		GN_ITEMDLG,
		GN_REWARD,
		GN_ROUND,
		GN_END
	};

	enum EButtonName
	{
		// Base
		BN_BASE_SCISSORBTN1,
		BN_BASE_ROCKBTN2,
		BN_BASE_PAPERBTN3,
		BN_BASE_CLOSEBTN,
		BN_BASE_STARTBTN,
		BN_BASE_SCISSORBTNDIS1,
		BN_BASE_ROCKBTNDIS2,
		BN_BASE_PAPERBTNDIS3,
		BN_END
	};

	enum EStaticTextName
	{
		// Base
		STN_END
	};

	enum EFormatedTextName
	{
		// Base
		FTN_BASE_NPCMENT,
		FTN_END
	};

	enum EFrameName
	{
		// Base
		FN_BASE_BASEFRAME,
		FN_BASE_ITEMDLG,
		FN_BASE_BASEINFODLG,
		FN_BASE_ROUNDDLG,
		FN_BASE_GAGEDLG1,
		FN_BASE_GAGEDLG2,
		FN_BASE_GAGEDLG3,
		FN_BASE_BASE_BK,

		// RoundDlg
		FN_ROUNDDLG_ROUND,
		FN_END
	};

	enum EImageCtrlName
	{
		// Base
		IN_BASE_WIN,
		IN_BASE_LOSE,
		IN_BASE_DRAW,
		IN_BASE_TIME,

		// ItemDlg
		IN_ITEMDLG_ITEM1,
		IN_ITEMDLG_ITEM2,
		IN_ITEMDLG_ITEM3,
		IN_ITEMDLG_ITEM4,
		IN_ITEMDLG_ROUND1,
		IN_ITEMDLG_ROUND2,
		IN_ITEMDLG_ROUND3,
		IN_ITEMDLG_ROUND4,
		In_END
	};

	enum EImageTextName
	{
		ITN_SELECT_TIME,	// 1~5
		ITN_ROUND_NUM,		// 1~3
		ITN_END
	};

private:
	std::array<CGUIDialog*, EGUIName::GN_END> m_arrayDlg = { nullptr, };
	std::array<tuple<string, std::function<void(void)>, CGUIImageButton*>, EButtonName::BN_END> m_arrayButton;
	std::array<CGUIStaticText*, EStaticTextName::STN_END> m_arrayStaticText = { nullptr, };
	std::array<CFormatedStaticText*, EStaticTextName::STN_END> m_arrayFormatedText = { nullptr, };
	std::array<CGUIImageCtrl*, EImageCtrlName::In_END> m_arrayImageCtrl = { nullptr, };
	std::array<CGUIImageText*, EImageTextName::ITN_END> m_arrayImageText = { nullptr, };
	std::array<SRoundItem, MAX_ROUNDITEM> m_arrayRoundItem;

	CGUIUserControl* m_pDiceViewCtrl = nullptr;
	CTRObjectView m_diceObjView;

	int m_nCurRound = 0;
	int m_nUnmanipulated = 0;

	ESelectSRP m_eSelectSRP = ESelectSRP::SS_END;
	std::tuple<int, int> m_tupleRoundResult;
	ERoundResult m_eRoundResult = ERoundResult::RR_END;

private:	// Dialog
	std::shared_ptr<CTRScissorsRockPaper_RewardDlg> m_pRewardDlg = nullptr;
	CTRShowRewardItemInfoDlg m_rewardDlg;
	CYesNoDialogEx<CTRScissorsRockPaper_GameAlone> m_yesNoDlg;

public:
	CTRScissorsRockPaper_GameAlone();
	virtual ~CTRScissorsRockPaper_GameAlone();

public:
	// CTRCommandTarget(CCommandTarget)으로부터 상속받음
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

	// CTRScissorsRockPaper_GUI으로부터 상속받음
	virtual void showDialog() override;
	virtual void closeDialog() override;

	virtual void InitName() override;
	virtual void InitGUI() override;

	virtual void InitButton() override;
	virtual void InitStaticText() override;
	virtual void InitFormatedText() override;
	virtual void InitImageControl() override;
	virtual void InitImageText() override;
	virtual void InitUserControl() override;

	// IntTask으로부터 상속받음
	virtual void onFrameMove(float fElapsed) override;

	// CTRScissorsRockPaper_Game으로부터 상속받음
	virtual void UpdateGameStep_WaitStart() override;
	virtual void UpdateGameStep_EndStart() override;
	virtual void UpdateGameStep_WaitSelect() override;
	virtual void UpdateGameStep_EndSelect() override;
	virtual void UpdateGameStep_WaitResult() override;
	virtual void UpdateGameStep_EndResult() override;

	// IntRewardGiveMessageHandle으로부터 상속받음
	virtual void onSendGiveMsg(std::string & nickname, std::string & strMemo, int iItemNum = 0);

private:
	void InitRoundItem();
	void UpdateRoundItem();

	void InitCurRoundItem();
	void UpdateCurRoundItem(int _nRound = -1);

	void InitNPCMent();
	void UpdateNPCMent(EProgressStep _eCurMent);

	void InitSelectSRP();
	void UpdateSelectSRP(ESelectSRP _eSelectSRP);

	void ChangeUserView_Yeono(ESelectSRP _eSelectSRP);

	bool IsGameEndResult(std::tuple<int, int> _tupleResult);
	void SettingResultImage(ERoundResult _eRoundReulst);
	void CreateRewardDlg();
	void showGiveYes();

	void ChangeStaticText(EStaticTextName _eName, string _strText);
	void ChangeFormatedText(EFormatedTextName _eName, string _strText);
	void ChangeImageText(EImageTextName _eName, string _strText);
	void ChangeRoundMent(int _nTime);

	void ToggleImageText(EImageTextName _eName, bool _bOn);
	void ToggleCheckedButton(ESelectSRP _eSelectSRP, bool _bOn);
	ESelectSRP selectSRP(eRSP_SELECTION eRsp);
	eRSP_SELECTION selectRSP(ESelectSRP eRsp);

public:	// Accessor
	inline int GetFinalItemIndex()const { return !m_item_list.empty() ? m_item_list[m_nCurRound] : 0; }

public:	// Server
	std::vector<int> m_item_list;
	int m_left_time = 0;

	//!< 입장 완료. 혹은 실패. 보상 리스트 데이터. 현재 0단계 보상 확정.
	virtual void OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state);

	//!< 현재 확정 보상 단계 데이터. 타이머 시간. 남은 단계 수.
	virtual void OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state);

	//!< 승, 패, 무승부. 시간 오버. 현재 보상 단계 데이터.
	virtual void OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward);
};

