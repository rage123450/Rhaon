#pragma once
#include "TRScissorsRockPaper_Game.h"
//
#include "gameui/YesNoDialog.h"
#include "gameui/TRObjectView.h"
#include "gameui/TRRewardItemInfoDlg.h"

class CTRScissorsRockPaper_RewardDlg;

class CTRScissorsRockPaper_GameGroup :
	public IntTask,
	public IntRewardGiveMessageHandler,
	public CTRScissorsRockPaper_Game,
	public enable_shared_from_this<CTRScissorsRockPaper_GameGroup>
{
private:
	static constexpr int MAX_ROUNDITEM = 11;
	static constexpr int MAX_GAUGENUM = 3;
	static constexpr int MAX_UNMANIPULATED = 1;
	static constexpr int MAX_WIN = 10;
	static constexpr int MAX_LOSE = 1;
	static constexpr int MAX_NUMBER_OF_CHANGES = 3;
	static constexpr int TIME_END_START = 10;

	static constexpr float USER_SELECT_TIME = 5.0f;
	static constexpr float CHANGE_GAUGE_TIME = 1.0f;
	static constexpr float RESULT_DELAY_TIME = 2.67f;
	static constexpr float RESULT_NEXT_STEP = RESULT_DELAY_TIME + 2.0f;
	static constexpr float WAITEND_NEXT_STEP = 3.0f;

private:
	enum EProgressStep		// ���� �ܰ�
	{
		PS_WAIT_START,				// ���� �����		
		PS_WAIT_END,				// ���� ��� ����
		PS_START_SELECTION_TIMER,	// ���� Ÿ�̸� ����
		PS_SELECT_TIMER_END,		// ���� Ÿ�̸� ����
		PS_WIN_OVER_NPC,			// �������� �¸�
		PS_LOSE_OVER_NPC,			// �������� �й�
		PS_WAIT_ROUNDRESULT,		// ������ ���� �����
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
		GN_ITEMDLG2,
		GN_BASEINFO,
		GN_GAUGEDLG,
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

		// BaseInfo
		STN_CHANGE_WAITINGTIME_MENT,
		STN_CHANGE_WAITINGTIME,
		STN_SURVIVORMENT,
		STN_SURVIVOR,

		// GaugeDlg
		STN_GAUGEDLG_NUMBER,
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

		// GaugeDlg
		FN_GAUGEDLG_GAUGE,

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
		IN_ITEMDLG2_ITEM1,
		IN_ITEMDLG2_ITEM2,
		IN_ITEMDLG2_ITEM3,
		IN_ITEMDLG2_ITEM4,
		IN_ITEMDLG2_ITEM5,
		IN_ITEMDLG2_ITEM6,
		IN_ITEMDLG2_ITEM7,
		IN_ITEMDLG2_ITEM8,
		IN_ITEMDLG2_ITEM9,
		IN_ITEMDLG2_ITEM10,
		IN_ITEMDLG2_ITEM11,
		IN_ITEMDLG2_ROUND1,
		IN_ITEMDLG2_ROUND2,
		IN_ITEMDLG2_ROUND3,
		IN_ITEMDLG2_ROUND4,
		IN_ITEMDLG2_ROUND5,
		IN_ITEMDLG2_ROUND6,
		IN_ITEMDLG2_ROUND7,
		IN_ITEMDLG2_ROUND8,
		IN_ITEMDLG2_ROUND9,
		IN_ITEMDLG2_ROUND10,
		IN_ITEMDLG2_ROUND11,

		// GaugeDlg
		IN_GAUGEDLG_GAUGEIMG,
		IN_GAUGEDLG_SCISSORIMG1,
		IN_GAUGEDLG_ROCKIMG2,
		IN_GAUGEDLG_PAPERIMG3,
		IN_END
	};

	enum EImageTextName
	{
		ITN_SELECT_TIME,	// 1~5
		ITN_ROUND_NUM,		// 1~10
		ITN_END
	};

private:
	struct SGauge
	{
		CGUIDialog* pDlg = nullptr;
		CGUIStaticText* pText = nullptr;
		CGUIImageCtrl* pImage = nullptr;
		CGUIImageCtrl* pScissorImg1 = nullptr;
		CGUIImageCtrl* pRockImg2 = nullptr;
		CGUIImageCtrl* pPaperImg3 = nullptr;
		CGUIFrameImage* pFrame = nullptr;

		int nCur = 0;	// ���� ��ġ
		int nMov = 0;	// �����ؾ� �ϴ� ��ġ
		int nCurNum = 0;
		int nMovNum = 0;
	};

private:
	std::array<CGUIDialog*, EGUIName::GN_END> m_arrayDlg = { nullptr, };
	std::array<tuple<string, std::function<void(void)>, CGUIImageButton*>, EButtonName::BN_END> m_arrayButton;
	std::array<CGUIStaticText*, EStaticTextName::STN_END> m_arrayStaticText = { nullptr, };
	std::array<CFormatedStaticText*, EFormatedTextName::FTN_END> m_arrayFormatedText = { nullptr, };
	std::array<CGUIImageCtrl*, EImageCtrlName::IN_END> m_arrayImageCtrl = { nullptr, };
	std::array<CGUIImageText*, EImageTextName::ITN_END> m_arrayImageText = { nullptr, };
	std::array<SGauge, MAX_GAUGENUM> m_arrayGauge;
	std::array<SRoundItem, MAX_ROUNDITEM> m_arrayRoundItem;

	CGUIUserControl* m_pDiceViewCtrl = nullptr;
	CTRObjectView m_diceObjView;

	int m_nCurRound = 0;
	int m_nUnmanipulated = 0;

	int m_nTotalPeople = 0;		
	int m_nRemainPeople = 0;		
	float m_fCurWaitTime = 0.0f;
	float m_fMaxWaitTime = 0.0f;
	int m_nCurNumberOfChanges = 0;	

	ESelectSRP m_eSelectSRP = ESelectSRP::SS_END;
	ESelectSRP m_eCurSelectSRP = ESelectSRP::SS_END;
	std::tuple<int, int> m_tupleRoundResult;
	ERoundResult m_eRoundResult = ERoundResult::RR_END;

	CRectInfo m_rtGaugeCtrl;
	CRectInfo m_rtGaugeSrc;
	
	bool m_bSelectAck = true;

private:	// Dialog
	std::shared_ptr<CTRScissorsRockPaper_RewardDlg> m_pRewardDlg = nullptr;
	CYesNoDialogEx<CTRScissorsRockPaper_GameGroup> m_pYesNoDlg;
	CTRShowRewardItemInfoDlg m_rewardDlg;

public:
	CTRScissorsRockPaper_GameGroup();
	virtual ~CTRScissorsRockPaper_GameGroup();

public:
	// CTRCommandTarget(CCommandTarget)���κ��� ��ӹ���
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

	// CTRScissorsRockPaper_GUI���κ��� ��ӹ���
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

	// IntTask���κ��� ��ӹ���
	virtual void onFrameMove(float fElapsed) override;

	// CTRScissorsRockPaper_Game���κ��� ��ӹ���
	virtual void UpdateGameStep_WaitStart() override;
	virtual void UpdateGameStep_EndStart() override;
	virtual void UpdateGameStep_WaitSelect() override;
	virtual void UpdateGameStep_EndSelect() override;
	virtual void UpdateGameStep_WaitResult() override;
	virtual void UpdateGameStep_EndResult() override;

	// IntRewardGiveMessageHandle���κ��� ��ӹ���
	virtual void onSendGiveMsg(std::string & nickname, std::string & strMemo, int iItemNum = 0);

private:
	void InitGauge();
	void UpdateGauge();

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

	void ShowYes();

	void ChangeStaticText(EStaticTextName _eName, string _strText);
	void ChangeFormatedText(EFormatedTextName _eName, string _strText);
	void ChangeImageText(EImageTextName _eName, string _strText);
	void ChangeGauge(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT]);

	void ToggleImageText(EImageTextName _eName,bool _bOn);
	void ToggleCheckedButton(ESelectSRP _eSelectSRP, bool _bOn);
	eRSP_SELECTION selectRSP(ESelectSRP eRsp);
	ESelectSRP selectSRP(eRSP_SELECTION eRsp);
	eRSP_SELECTION GetIntToRSP(int _nValue);
	eRSP_SELECTION_RESULT GetRoundResultToESR(ERoundResult _eRoundResult);

private:
	inline int GetIncrementCode(const int& _nMov, const int& _nCur)
	{
		return _nMov == _nCur ? 0 : _nMov - _nCur > 0 ? 1 : -1;
	}

public:	// Accessor
	inline int GetFinalItemIndex()const { return !m_item_list.empty() ? m_item_list[m_nCurRound] : 0; }

public:	// Server
	std::vector<int> m_item_list;
	int m_user_in_playing = 0;
	int m_left_time = 0;
	int m_left_time_to_input = 0;

	//!< ���ֽź��� �̺�Ʈ(��ü ����������) ���� �˸�. �޼��� ����. ���۱��� ���� �ð�. (���� �ð��� 0�϶� �̺�Ʈ ����)
	virtual void OnGlobalRSPStartNotify(int message_in_str_table, int left_time);

	//!< ���� ���� Ȥ�� ����
	virtual void OnGlobalRSPEnterAck(eServer_GLOBAL_RSP_ENTER_ACK_TYPE ack, int base_reward, const std::vector<int>& round_rewards, int selection_limit, int time2round_start);

	//!< ���� �÷������� ���� ��.  (���� : �̺�Ʈ�� �߻� �Ҷ����� �������� �����Ƿ�, ��¥ ī��Ʈ �ִϸ��̼��� �ʿ�������...)
	virtual void OnGlobalRSPCurrentUserNotify(int delta_user, int user_in_playing);

	//!< ���� ���� �˸�. �Է¿Ϸ���� ���� �ð�.
	virtual void OnGlobalRSPGameStartNotify(int left_time_to_input, int current_state);

	//!< ���� ����, ����. ���� Ȯ�� ���� ������ ������ STATE
	virtual void OnGlobalRSPSelectionAck(eServer_GLOBAL_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION selection, int left_selection_count, int current_reward_state);

	//!< ��ü ����, ����, �� ���� ����. (���� : �̺�Ʈ�� �߻� �Ҷ����� �������� �����Ƿ�, ��¥ ī��Ʈ �ִϸ��̼��� �ʿ�������...)
	virtual void OnGlobalRSPSelectionInfoNotify(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT]);

	//����� �й���,  �̹� �������� ���޵Ǿ� �ִ�.
	virtual void OnGlobalRSPSelectionResultNotify(eRSP_SELECTION selection, eRSP_SELECTION_RESULT result, int current_reward_state, int current_state);
};

