#pragma once
#include "TRMiniGameSRP.h"

class CTRMiniGameSRP_Group :
	public CTRMiniGameSRP
{
public:
	CTRMiniGameSRP_Group();
	virtual ~CTRMiniGameSRP_Group();

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
	// ==================================================================
	// ��ü��
	// ==================================================================
	int m_user_in_playing = 0;
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

