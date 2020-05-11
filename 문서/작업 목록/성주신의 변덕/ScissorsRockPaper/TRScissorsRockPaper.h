#pragma once
#include "CommonLib/netcommon/PROTOCOL/RockSissorsPaper.h"

class CTRScissorsRockPaper_Game;

class CTRScissorsRockPaper
{
public:
	enum EGameType
	{
		GT_ALONE,
		GT_GROUP,
		GT_END
	};

private:
	map<tuple<int, int, int>, string> m_mapMent;
	EGameType m_eGameType = EGameType::GT_END;
	shared_ptr<CTRScissorsRockPaper_Game> m_pGame = nullptr;

public:
	CTRScissorsRockPaper();
	~CTRScissorsRockPaper();

public:
	void showDialog(EGameType _eGameType);
	void closeDialog();

private:
	bool LoadNPCMent(const std::string& strFileName);
	shared_ptr<CTRScissorsRockPaper_Game> GetGame(EGameType _eGameType);

public:		// Accessor
	EGameType GetGameType()const { return m_eGameType; }

public:	// Server
// 여기에 서버 함수
	//!< 입장 완료. 혹은 실패. 보상 리스트 데이터. 현재 0단계 보상 확정.
	void OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state);

	//!< 현재 확정 보상 단계 데이터. 타이머 시간. 남은 단계 수.
	void OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state);

	//!< 승, 패, 무승부. 시간 오버. 현재 보상 단계 데이터.
	void OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward);

	//!< 성주신변덕 이벤트(전체 가위바위보) 시작 알림. 메세지 포함. 시작까지 남은 시간. (남은 시간이 0일때 이벤트 시작)
	void OnGlobalRSPStartNotify(int message_in_str_table, int left_time);

	//!< 입장 실패 혹은 성공
	void OnGlobalRSPEnterAck(eServer_GLOBAL_RSP_ENTER_ACK_TYPE ack, int base_reward, const std::vector<int>& round_rewards, int selection_limit, int time2round_start);

	//!< 현재 플레이중인 유저 수.  (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
	void OnGlobalRSPCurrentUserNotify(int delta_user, int user_in_playing);

	//!< 게임 시작 알림. 입력완료까지 남은 시간.
	void OnGlobalRSPGameStartNotify(int left_time_to_input, int current_state);

	//!< 선택 성공, 실패. 현재 확정 보상 아이템 데이터 STATE
	void OnGlobalRSPSelectionAck(eServer_GLOBAL_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION selection, int left_selection_count, int current_reward_state);

	//!< 전체 가위, 바위, 보 선택 정보. (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
	void OnGlobalRSPSelectionInfoNotify(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT]);

	//결과가 패배라면,  이미 아이템이 지급되어 있다.
	void OnGlobalRSPSelectionResultNotify(eRSP_SELECTION selection, eRSP_SELECTION_RESULT result, int current_reward_state, int current_state);
};
