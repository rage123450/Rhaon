#include "stdafx.h"
#include "TRScissorsRockPaper.h"
//
#include "language/LanguageHeader.h"
#include "language/UnicodeTextFile.h"
#include "TRScissorsRockPaper_GameAlone.h"
#include "TRScissorsRockPaper_GameGroup.h"
#include "gameui/TRShortTimeMessage.h"

CTRScissorsRockPaper::CTRScissorsRockPaper()
{
	LoadNPCMent("script\\Content\\ScissorsRockPaperNPCMent.txt");
}

CTRScissorsRockPaper::~CTRScissorsRockPaper()
{
	closeDialog();
}

void CTRScissorsRockPaper::showDialog(EGameType _eGameType)
{
	m_pGame = GetGame(_eGameType);

	if(m_pGame)
	{
		m_pGame->SetMent(m_mapMent);
		m_pGame->showDialog();
	}
}

void CTRScissorsRockPaper::closeDialog()
{
	if(m_pGame)
	{
		m_pGame->closeDialog();
	}
}

bool CTRScissorsRockPaper::LoadNPCMent(const std::string & strFileName)
{
	CTextFileToPackage filereader(true);
	if(!filereader.open(strFileName))
	{
		return false;
	}
	
	try
	{
		boost::regex re_info(
			"(.+?),"
			"(.+?),"
			"(.+?),"
			"\"(.+?)\"");

		std::string buf;

		while(filereader.getLine(buf))
		{
			stringutil::strip(buf);

			// 빈줄은 걸러낸다.
			if(buf.empty())
			{
				continue;
			}

			// 주석은 걸러낸다.
			if(stringutil::startswith(buf, "//"))
			{
				continue;
			}

			// 정규식으로 파싱한다.
			boost::smatch results;
			boost::regex_match(buf, results, re_info);

			if(results.size() != 5)
			{
				throw exception(("[results Err]" + buf).c_str());
			}

			pair<tuple<int, int, int>, string> pairTemp;
			get<0>(pairTemp.first) = atoi(results[1].str().c_str());
			get<1>(pairTemp.first) = atoi(results[2].str().c_str());
			get<2>(pairTemp.first) = atoi(results[3].str().c_str());
			pairTemp.second = results[4].str();

			m_mapMent.emplace(pairTemp);
		}
	}
	catch(const std::exception& e)
	{
		TRDBG_OUTPUT_ERROR("LoadNPCMent - %s", e.what());
		_ASSERTE(FALSE);
		return false;
	}

	return true;
}

shared_ptr<CTRScissorsRockPaper_Game> CTRScissorsRockPaper::GetGame(EGameType _eGameType)
{
	m_eGameType = _eGameType;

	switch(m_eGameType)
	{
	case CTRScissorsRockPaper::GT_ALONE:
		return make_shared<CTRScissorsRockPaper_GameAlone>();
	case CTRScissorsRockPaper::GT_GROUP:
		return make_shared<CTRScissorsRockPaper_GameGroup>();
	}

	return nullptr;
}

//!< 입장 완료. 혹은 실패. 보상 리스트 데이터. 현재 0단계 보상 확정.
void CTRScissorsRockPaper::OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state)
{
	if (ack == eServer_PRIVATE_RSP_START_ACK_OK)
	{
		showDialog(CTRScissorsRockPaper::GT_ALONE);
		if (m_pGame)
			m_pGame->OnPrivateRSPStartAck(ack, item_list, current_reward_state);
	}
	else
	{
		switch (ack)
		{
		case eServer_PRIVATE_RSP_START_ACK_NOT_ENOUGH_BASE_ITEM:
			// StringTable : SRP_GOODS_LACK : 재화가 부족합니다.
			CTRShortTimeMessage::getInstance().showMessage(_STR(SRP_GOODS_LACK));
			break;
		case eServer_PRIVATE_RSP_START_ACK_INVALID_STATE:
			// StringTable : SRP_NOT_STARTABLE : 시작 가능한 상태가 아닙니다.
			CTRShortTimeMessage::getInstance().showMessage(_STR(SRP_NOT_STARTABLE));
			break;
		case eServer_PRIVATE_RSP_GAME_START_ACK_DB_ERROR:
			CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_DB_ERROR));
			break;
		}
	}
}

//!< 현재 확정 보상 단계 데이터. 타이머 시간. 남은 단계 수.
void CTRScissorsRockPaper::OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state)
{
	if (m_pGame)
		m_pGame->OnPrivateRSPGameStartAck(ack, current_reward_state, left_time, next_state);
}

//!< 승, 패, 무승부. 시간 오버. 현재 보상 단계 데이터.
void CTRScissorsRockPaper::OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward)
{
	if (m_pGame)
		m_pGame->OnPrivateRSPSelectionAck(ack, r, server_selection, current_state, current_state_reward);
}

//!< 성주신변덕 이벤트(전체 가위바위보) 시작 알림. 메세지 포함. 시작까지 남은 시간. (남은 시간이 0일때 이벤트 시작)
void CTRScissorsRockPaper::OnGlobalRSPStartNotify(int message_in_str_table, int left_time)
{
	if (m_pGame)
		m_pGame->OnGlobalRSPStartNotify(message_in_str_table, left_time);
}

//!< 입장 실패 혹은 성공
void CTRScissorsRockPaper::OnGlobalRSPEnterAck(eServer_GLOBAL_RSP_ENTER_ACK_TYPE ack, int base_reward, const std::vector<int>& round_rewards, int selection_limit, int time2round_start)
{
	if (ack == eServer_GLOBAL_RSP_ENTER_ACK_OK)
	{
		showDialog(CTRScissorsRockPaper::GT_GROUP);
		if (m_pGame)
			m_pGame->OnGlobalRSPEnterAck(ack, base_reward, round_rewards, selection_limit, time2round_start);
	}
	else
	{
		switch (ack)
		{
		case eServer_GLOBAL_RSP_ENTER_ACK_NOT_GAME_TIME:
			// StringTable : SRP_NOT_TIME_PARTICIPATE : 참여 가능한 시간이 아닙니다.
			CTRShortTimeMessage::getInstance().showMessage(_STR(SRP_NOT_TIME_PARTICIPATE));
			break;
		case eServer_GLOBAL_RSP_ENTER_ACK_TOO_LATE:
			// StringTable : FAILED_ENTER_ALREADY_GAME_STARTED : 이미 게임이 시작되었습니다.
			CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_ENTER_ALREADY_GAME_STARTED));
			break;
		case eServer_GLOBAL_RSP_ENTER_ACK_DUPLICATED_ENTRANCE:
			// StringTable : SRP_DUPLICATE_ENTRY : 중복 입장입니다.
			CTRShortTimeMessage::getInstance().showMessage(_STR(SRP_DUPLICATE_ENTRY));
			break;
		}
	}
}

//!< 현재 플레이중인 유저 수.  (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
void CTRScissorsRockPaper::OnGlobalRSPCurrentUserNotify(int delta_user, int user_in_playing)
{
	if (m_pGame)
		m_pGame->OnGlobalRSPCurrentUserNotify(user_in_playing, user_in_playing);
}

//!< 게임 시작 알림. 입력완료까지 남은 시간.
void CTRScissorsRockPaper::OnGlobalRSPGameStartNotify(int left_time_to_input, int current_state)
{
	if (m_pGame)
		m_pGame->OnGlobalRSPGameStartNotify(left_time_to_input, current_state);
}

//!< 선택 성공, 실패. 현재 확정 보상 아이템 데이터 STATE
void CTRScissorsRockPaper::OnGlobalRSPSelectionAck(eServer_GLOBAL_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION selection, int left_selection_count, int current_reward_state)
{
	if (m_pGame)
		m_pGame->OnGlobalRSPSelectionAck(ack, selection, left_selection_count, current_reward_state);
}

//!< 전체 가위, 바위, 보 선택 정보. (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
void CTRScissorsRockPaper::OnGlobalRSPSelectionInfoNotify(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT])
{
	if (m_pGame)
		m_pGame->OnGlobalRSPSelectionInfoNotify(selection_count_delta, selection_count);
}

//결과가 패배라면,  이미 아이템이 지급되어 있다.
void CTRScissorsRockPaper::OnGlobalRSPSelectionResultNotify(eRSP_SELECTION selection, eRSP_SELECTION_RESULT result, int current_reward_state, int current_state)
{
	if (m_pGame)
		m_pGame->OnGlobalRSPSelectionResultNotify(selection, result, current_reward_state, current_state);
}