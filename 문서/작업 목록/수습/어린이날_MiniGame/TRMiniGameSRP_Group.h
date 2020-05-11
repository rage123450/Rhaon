#pragma once
#include "TRMiniGameSRP.h"

class CTRMiniGameSRP_Group :
	public CTRMiniGameSRP
{
public:
	CTRMiniGameSRP_Group();
	virtual ~CTRMiniGameSRP_Group();

public:
	// CMiniGameSRP -> CMiniGameBase -> CMiniGameAssist을(를) 통해 상속됨
	virtual void showDialog() override;
	virtual void closeDialog() override;

	// CMiniGameSRP -> CMiniGameBase을(를) 통해 상속됨
	virtual void onOpen() override;
	virtual void onWait() override;
	virtual void onReady() override;
	virtual void onStart() override;
	virtual void onPlaying() override;
	virtual void onResult() override;
	virtual void onEnd() override;

	// CMiniGameSRP -> CMiniGameBase -> IntTask으로부터 상속받음
	virtual void onFrameMove(float fElapsed) override;

	// CMiniGameSRP을(를) 통해 상속됨
	virtual bool Func_CloseBtn(CGUIControl* _pDlg) override;
	virtual bool Func_ScissorsBtn(CGUIControl* _pDlg) override;
	virtual bool Func_RockBtn(CGUIControl* _pDlg) override;
	virtual bool Func_PaperBtn(CGUIControl* _pDlg) override;
	virtual bool Func_StartBtn(CGUIControl* _pDlg) override;

	virtual string GetNPCMent(ENpcMent _eCurNpcMent) override;

public:
	// ==================================================================
	// 단체전
	// ==================================================================
	int m_user_in_playing = 0;
	int m_left_time_to_input = 0;

	//!< 성주신변덕 이벤트(전체 가위바위보) 시작 알림. 메세지 포함. 시작까지 남은 시간. (남은 시간이 0일때 이벤트 시작)
	virtual void OnGlobalRSPStartNotify(int message_in_str_table, int left_time);

	//!< 입장 실패 혹은 성공
	virtual void OnGlobalRSPEnterAck(eServer_GLOBAL_RSP_ENTER_ACK_TYPE ack, int base_reward, const std::vector<int>& round_rewards, int selection_limit, int time2round_start);

	//!< 현재 플레이중인 유저 수.  (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
	virtual void OnGlobalRSPCurrentUserNotify(int delta_user, int user_in_playing);

	//!< 게임 시작 알림. 입력완료까지 남은 시간.
	virtual void OnGlobalRSPGameStartNotify(int left_time_to_input, int current_state);

	//!< 선택 성공, 실패. 현재 확정 보상 아이템 데이터 STATE
	virtual void OnGlobalRSPSelectionAck(eServer_GLOBAL_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION selection, int left_selection_count, int current_reward_state);

	//!< 전체 가위, 바위, 보 선택 정보. (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
	virtual void OnGlobalRSPSelectionInfoNotify(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT]);

	//결과가 패배라면,  이미 아이템이 지급되어 있다.
	virtual void OnGlobalRSPSelectionResultNotify(eRSP_SELECTION selection, eRSP_SELECTION_RESULT result, int current_reward_state, int current_state);
};

