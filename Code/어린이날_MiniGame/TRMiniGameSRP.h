#pragma once
#include "TRMiniGameBase.h"
//
#include "NetClientManager.h"

class CTRMiniGameQuestion_NpcView;
class CTRMiniGameAnswer_ChoiceSRP;

class CTRMiniGameSRP :
	public CTRMiniGameBase
{
public:
	static constexpr float USER_SELECT_TIME = 5.0f;
	static constexpr float RESULT_DELAY_TIME = 2.67f;
	static constexpr float RESULT_WAIT_TIME = 1.0f;

public:
	enum ESelectSRP
	{
		SS_SCISSORS,
		SS_ROCK,
		SS_PAPER,
		SS_END
	};

	enum ERoundResult
	{
		RR_WIN,
		RR_LOSE,
		RR_DRAW,
		RR_END
	};

	enum ENpcMent
	{
		NMS_BASE_SCREEN,			// 기본 화면
		NMS_START_SELECTION_TIMER,	// 선택 타이머 시작
		NMS_SELECT_TIMER_END,		// 선택 타이머 종료
		NMS_USER_NO_OPERATION,		// 유저 미조작 시
		NMS_USER_LOSE,				// 유저 패배
		NMS_USER_WIN,				// 유저 승리
		NMS_USER_DRAW,				// 유저 무승부

		NMG_WAIT_START,				// 입장 대기중		
		NMG_WAIT_END,				// 입장 대기 종료
		NMG_START_SELECTION_TIMER,	// 선택 타이머 시작
		NMG_SELECT_TIMER_END,		// 선택 타이머 종료
		NMG_WIN_OVER_NPC,			// 연오에게 승리
		NMG_LOSE_OVER_NPC,			// 연오에게 패배
		NMG_WAIT_ROUNDRESULT,		// 라운드결과 이후 대기중

		NM_END
	};

public:		// Name
	enum ESoundName
	{
		SN_BUTTON_CLICK,
		SN_RPS_WIN,
		SN_RPS_LOSE,
		SN_RPS_DRAW,
		SN_CARD_GET,
		SN_RPS_COUNT,
		SN_RPS_1,
		SN_RPS_2,
		SN_RPS_3,
		SN_RPS_DRAW1,
		SN_RPS_FAIL1,
		SN_RPS_FAIL2,
		SN_STARTMENT1,
		SN_STARTMENT2,
		SN_RPS_WIN1,
		SN_RPS_WIN2,
		SN_RPS_WIN3,
		SN_END
	};

public:
	typedef struct tagRoundItem
	{
		CGUIItemImageCtrl* m_pItemImage;
		CGUIImageCtrl* m_pImage;
	}ROUND_ITEM, *PROUND_ITEM;

protected:
	CGUIDialog* m_pDlg = nullptr;
	CGUIDialog* m_pDlgItem = nullptr;
	CGUIDialog* m_pDlgItem2 = nullptr;
	CGUIDialog* m_pDlgRound = nullptr;
	CGUIDialog* m_DlgBaseInfo = nullptr;
	CGUIDialog* m_pDlgReward = nullptr;

	std::shared_ptr<CTRMiniGameQuestion_NpcView> m_pNpcView = nullptr;
	std::shared_ptr<CTRMiniGameAnswer_ChoiceSRP> m_pChoiceSRP = nullptr;

	std::map<std::tuple<int, int, int>, std::string> m_mapMent;

	CFormatedStaticText* m_pNpcMent = nullptr;
	CGUIImageCtrl* m_pTime = nullptr;
	CGUIImageText* m_pRound = nullptr;
	CGUIImageText* m_pSelectTime = nullptr;		// createControl

	std::vector<ROUND_ITEM> m_vecRoundItem;
	int m_nCurRound = 0;
	int m_nUnmanipulated = 0;
	ERoundResult m_eRoundResult = ERoundResult::RR_END;

	CGUIImageCtrl* m_pWin = nullptr;
	CGUIImageCtrl* m_pLose = nullptr;
	CGUIImageCtrl* m_pDraw = nullptr;

	std::tuple<int, int, int> m_tupleResult;	// Win, Lose, Draw

	std::array<CAudioSourcePlayID, ESoundName::SN_END> m_arraySound;
	ESoundName m_eSoundName;

public:
	CTRMiniGameSRP();
	virtual ~CTRMiniGameSRP();

public:
	// CMiniGameBase -> CMiniGameAssist을(를) 통해 상속됨
	virtual void showDialog() override;
	virtual void closeDialog() override;
	virtual bool isVisible() override;

	// CMiniGameBase -> IntTask으로부터 상속받음
	virtual void onFrameMove(float fElapsed) override;

	// CMiniGameBase을(를) 통해 상속됨
	virtual void initSubDlg() override;

	// This
	virtual bool Func_CloseBtn(CGUIControl* _pDlg) abstract;
	virtual bool Func_ScissorsBtn(CGUIControl* _pDlg) abstract;
	virtual bool Func_RockBtn(CGUIControl* _pDlg) abstract;
	virtual bool Func_PaperBtn(CGUIControl* _pDlg) abstract;
	virtual bool Func_StartBtn(CGUIControl* _pDlg);

	virtual void CreateRewardDlg();
	virtual string GetNPCMent(ENpcMent _eCurNpcMent) abstract;

protected:
	// Common
	void ChangeUserView_Yeono(ESelectSRP _eSelectSRP);
	void PlaySoundSRP(ESoundName _eSoundName);
	void StopSoundSRP(ESoundName _eSoundName, bool _bAll = false);
	bool IsPlaySoundSRP(ESoundName _eSoundName);
	void ChangeImageText(CGUIImageText* _pText, string _strText);
	void ChangeSelectTime(int _nTime);
	void PlayRound(int _nRoundNum, float _fFadeIn = 0.3f, float _fDealy = 0.5f, float _fFadeOut = 0.3f);

	void InitRoundItem(int _nRoundItemNum);
	void SettingRoundItem();

	void SettingResultImage(ERoundResult _eRoundReulst);

	ESelectSRP selectSRP(eRSP_SELECTION eRsp);
	eRSP_SELECTION selectRSP(ESelectSRP eRsp);
	eRSP_SELECTION selectRSP(int nRsp);

	void ChangeNPCMent(ENpcMent _eCurNpcMent);
	
private:
	void ChangeRoundNum(int _nRoundNum);
	void PlayRoundAnimation(float _fFadeIn = 0.3f, float _fDealy = 0.5f, float _fFadeOut = 0.3f);

protected:
	inline ESelectSRP To_ESelectSRP(int _nNum)
	{
		switch(_nNum)
		{
		case CTRMiniGameSRP::SS_SCISSORS: return CTRMiniGameSRP::SS_SCISSORS;
		case CTRMiniGameSRP::SS_ROCK: return CTRMiniGameSRP::SS_ROCK;
		case CTRMiniGameSRP::SS_PAPER: return CTRMiniGameSRP::SS_PAPER;
		}
	}

public:	// Server
	std::vector<int> m_item_list;
	int m_left_time = 0;

	// ==================================================================
	// 개인전
	// ==================================================================
	//!< 입장 완료. 혹은 실패. 보상 리스트 데이터. 현재 0단계 보상 확정.
	virtual void OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state) {}

	//!< 현재 확정 보상 단계 데이터. 타이머 시간. 남은 단계 수.
	virtual void OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state) {}

	//!< 승, 패, 무승부. 시간 오버. 현재 보상 단계 데이터.
	virtual void OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward) {}



	// ==================================================================
	// 단체전
	// ==================================================================
	//!< 성주신변덕 이벤트(전체 가위바위보) 시작 알림. 메세지 포함. 시작까지 남은 시간. (남은 시간이 0일때 이벤트 시작)
	virtual void OnGlobalRSPStartNotify(int message_in_str_table, int left_time) {}

	//!< 입장 실패 혹은 성공
	virtual void OnGlobalRSPEnterAck(eServer_GLOBAL_RSP_ENTER_ACK_TYPE ack, int base_reward, const std::vector<int>& round_rewards, int selection_limit, int time2round_start) {}

	//!< 현재 플레이중인 유저 수.  (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
	virtual void OnGlobalRSPCurrentUserNotify(int delta_user, int user_in_playing) {}

	//!< 게임 시작 알림. 입력완료까지 남은 시간.
	virtual void OnGlobalRSPGameStartNotify(int left_time_to_input, int current_state) {}

	//!< 선택 성공, 실패. 현재 확정 보상 아이템 데이터 STATE
	virtual void OnGlobalRSPSelectionAck(eServer_GLOBAL_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION selection, int left_selection_count, int current_reward_state) {}

	//!< 전체 가위, 바위, 보 선택 정보. (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
	virtual void OnGlobalRSPSelectionInfoNotify(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT]) {}

	//결과가 패배라면,  이미 아이템이 지급되어 있다.
	virtual void OnGlobalRSPSelectionResultNotify(eRSP_SELECTION selection, eRSP_SELECTION_RESULT result, int current_reward_state, int current_state) {}
};

