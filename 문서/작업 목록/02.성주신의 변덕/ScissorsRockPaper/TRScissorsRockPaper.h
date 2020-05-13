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
// ���⿡ ���� �Լ�
	//!< ���� �Ϸ�. Ȥ�� ����. ���� ����Ʈ ������. ���� 0�ܰ� ���� Ȯ��.
	void OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state);

	//!< ���� Ȯ�� ���� �ܰ� ������. Ÿ�̸� �ð�. ���� �ܰ� ��.
	void OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state);

	//!< ��, ��, ���º�. �ð� ����. ���� ���� �ܰ� ������.
	void OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward);

	//!< ���ֽź��� �̺�Ʈ(��ü ����������) ���� �˸�. �޼��� ����. ���۱��� ���� �ð�. (���� �ð��� 0�϶� �̺�Ʈ ����)
	void OnGlobalRSPStartNotify(int message_in_str_table, int left_time);

	//!< ���� ���� Ȥ�� ����
	void OnGlobalRSPEnterAck(eServer_GLOBAL_RSP_ENTER_ACK_TYPE ack, int base_reward, const std::vector<int>& round_rewards, int selection_limit, int time2round_start);

	//!< ���� �÷������� ���� ��.  (���� : �̺�Ʈ�� �߻� �Ҷ����� �������� �����Ƿ�, ��¥ ī��Ʈ �ִϸ��̼��� �ʿ�������...)
	void OnGlobalRSPCurrentUserNotify(int delta_user, int user_in_playing);

	//!< ���� ���� �˸�. �Է¿Ϸ���� ���� �ð�.
	void OnGlobalRSPGameStartNotify(int left_time_to_input, int current_state);

	//!< ���� ����, ����. ���� Ȯ�� ���� ������ ������ STATE
	void OnGlobalRSPSelectionAck(eServer_GLOBAL_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION selection, int left_selection_count, int current_reward_state);

	//!< ��ü ����, ����, �� ���� ����. (���� : �̺�Ʈ�� �߻� �Ҷ����� �������� �����Ƿ�, ��¥ ī��Ʈ �ִϸ��̼��� �ʿ�������...)
	void OnGlobalRSPSelectionInfoNotify(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT]);

	//����� �й���,  �̹� �������� ���޵Ǿ� �ִ�.
	void OnGlobalRSPSelectionResultNotify(eRSP_SELECTION selection, eRSP_SELECTION_RESULT result, int current_reward_state, int current_state);
};
