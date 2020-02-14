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
	// CMiniGameSRP -> CMiniGameBase -> CMiniGameAssist��(��) ���� ��ӵ�
	virtual void showDialog() override;
	virtual void closeDialog() override;
	
	// CMiniGameSRP -> CMiniGameBase��(��) ���� ��ӵ�
	virtual void onOpen() override;
	virtual void onWait() override;
	virtual void onReady() override;
	virtual void onStart() override;
	virtual void onPlaying() override;
	virtual void onResult() override;
	virtual void onEnd() override;

	// CMiniGameSRP -> CMiniGameBase -> IntTask���κ��� ��ӹ���
	virtual void onFrameMove(float fElapsed) override;

	// CMiniGameSRP��(��) ���� ��ӵ�
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
	// ������ : ����
	// ==================================================================
	//!< ���� �Ϸ�. Ȥ�� ����. ���� ����Ʈ ������. ���� 0�ܰ� ���� Ȯ��.
	virtual void OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state);

	//!< ���� Ȯ�� ���� �ܰ� ������. Ÿ�̸� �ð�. ���� �ܰ� ��.
	virtual void OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state);

	//!< ��, ��, ���º�. �ð� ����. ���� ���� �ܰ� ������.
	virtual void OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward);
};

