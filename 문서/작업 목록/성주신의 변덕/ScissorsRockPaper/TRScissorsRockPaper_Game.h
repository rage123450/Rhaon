#pragma once
#include "gameui/TRUserInterface.h"
#include "TRScissorsRockPaper_GUI.h"
//
#include "NetClientManager.h"

class CTRScissorsRockPaper_Game :
	public CTRCommandTarget,
	public CTRScissorsRockPaper_GUI
{
public:
	enum EGameStep
	{
		GS_WAIT_START,
		GS_END_START,
		GS_WAIT_SELECT,
		GS_END_SELECT,
		GS_WAIT_RESULT,
		GS_END_RESULT,
		GS_END,
	};

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

private:
	std::array<CAudioSourcePlayID, ESoundName::SN_END> m_arraySound;
	ESoundName m_eSoundName;

protected:
	std::map<tuple<int, int, int>, std::string> m_mapMent;
	std::array<std::function<void(void)>, EGameStep::GS_END> m_arrayGameStep;
	std::pair<EGameStep, EGameStep> m_pairGameStep;	// Prev, Currnet
	bool m_bInGame = false;

protected:
	struct SRoundItem
	{
		CGUIItemImageCtrl* m_pItemImage;
		CGUIImageCtrl* m_pImage;
	};

public:
	CTRScissorsRockPaper_Game();
	virtual ~CTRScissorsRockPaper_Game();

public:
	// CTRCommandTarget(CCommandTarget)으로부터 상속받음
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)override;

	// CTRScissorsRockPaper_GUI으로부터 상속받음
	virtual void showDialog()override;

	// This
	virtual void UpdateGameStep_WaitStart();
	virtual void UpdateGameStep_EndStart();
	virtual void UpdateGameStep_WaitSelect();
	virtual void UpdateGameStep_EndSelect();
	virtual void UpdateGameStep_WaitResult();
	virtual void UpdateGameStep_EndResult();

protected:
	void ChangeGameStep(EGameStep _eNextGameStep);
	void ToggleButtonSRP(vector<CGUIButton*> _vecButton, vector<CGUIButton*> _vecButtonDis, bool _bOn);
	void PlaySoundSRP(ESoundName _eSoundName);
	void StopSoundSRP(ESoundName _eSoundName, bool _bAll = false);
	bool IsPlaySoundSRP(ESoundName _eSoundName);

public:	// inline
	inline float GetMSToSecond(int _nMs) { return _nMs / 1000.0f; }

public:	// Accessor
	inline void SetMent(map<tuple<int, int, int>, string>& _mapMent) { m_mapMent = _mapMent; }
	inline EGameStep GetPrevGameStep()const { return m_pairGameStep.first; }
	inline EGameStep GetCurGameStep()const { return m_pairGameStep.second; }

public:	// Server
	//!< 입장 완료. 혹은 실패. 보상 리스트 데이터. 현재 0단계 보상 확정.
	virtual void OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state) {}
	
	//!< 현재 확정 보상 단계 데이터. 타이머 시간. 남은 단계 수.
	virtual void OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state) {}
	
	//!< 승, 패, 무승부. 시간 오버. 현재 보상 단계 데이터.
	virtual void OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward) {}
	
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

