#pragma once
#define KMW_TEST
#include "TRMiniGameSRP.h"

class CTRMiniGameSRP_Single :
	public CTRMiniGameSRP
{
private:
	static constexpr int MAX_ROUNDNUM = 4;
	static constexpr int MAX_WIN = 3;

private:
	CGUIImageButton* m_pStartBtn = nullptr;
	


public:
	CTRMiniGameSRP_Single();
	virtual ~CTRMiniGameSRP_Single();

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
	void UpdateUnmanipulated(int _nTime);

public:
	// ==================================================================
	// 개인전 : 서버
	// ==================================================================
	//!< 입장 완료. 혹은 실패. 보상 리스트 데이터. 현재 0단계 보상 확정.
	virtual void OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state);

	//!< 현재 확정 보상 단계 데이터. 타이머 시간. 남은 단계 수.
	virtual void OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state);

	//!< 승, 패, 무승부. 시간 오버. 현재 보상 단계 데이터.
	virtual void OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward);
};

