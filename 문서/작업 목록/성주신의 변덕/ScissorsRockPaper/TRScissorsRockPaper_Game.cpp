#include "stdafx.h"
#include "TRScissorsRockPaper_Game.h"

CTRScissorsRockPaper_Game::CTRScissorsRockPaper_Game()
{
}

CTRScissorsRockPaper_Game::~CTRScissorsRockPaper_Game()
{
}

bool CTRScissorsRockPaper_Game::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRScissorsRockPaper_Game::showDialog()
{
	__super::showDialog();

	for(size_t i = 0; i < EGameStep::GS_END; i++)
	{
		switch(i)
		{
		case CTRScissorsRockPaper_Game::GS_WAIT_START:
			m_arrayGameStep[i] = std::bind(&CTRScissorsRockPaper_Game::UpdateGameStep_WaitStart, this);
			break;
		case CTRScissorsRockPaper_Game::GS_END_START:
			m_arrayGameStep[i] = std::bind(&CTRScissorsRockPaper_Game::UpdateGameStep_EndStart, this);
			break;
		case CTRScissorsRockPaper_Game::GS_WAIT_SELECT:
			m_arrayGameStep[i] = std::bind(&CTRScissorsRockPaper_Game::UpdateGameStep_WaitSelect, this);
			break;
		case CTRScissorsRockPaper_Game::GS_END_SELECT:
			m_arrayGameStep[i] = std::bind(&CTRScissorsRockPaper_Game::UpdateGameStep_EndSelect, this);
			break;
		case CTRScissorsRockPaper_Game::GS_WAIT_RESULT:
			m_arrayGameStep[i] = std::bind(&CTRScissorsRockPaper_Game::UpdateGameStep_WaitResult, this);
			break;
		case CTRScissorsRockPaper_Game::GS_END_RESULT:
			m_arrayGameStep[i] = std::bind(&CTRScissorsRockPaper_Game::UpdateGameStep_EndResult, this);
			break;
		}
	}

	m_pairGameStep = { EGameStep::GS_END,EGameStep::GS_END };
}

void CTRScissorsRockPaper_Game::UpdateGameStep_WaitStart()
{
}

void CTRScissorsRockPaper_Game::UpdateGameStep_EndStart()
{
}

void CTRScissorsRockPaper_Game::UpdateGameStep_WaitSelect()
{
}

void CTRScissorsRockPaper_Game::UpdateGameStep_EndSelect()
{
}

void CTRScissorsRockPaper_Game::UpdateGameStep_WaitResult()
{
}

void CTRScissorsRockPaper_Game::UpdateGameStep_EndResult()
{
}

void CTRScissorsRockPaper_Game::ChangeGameStep(EGameStep _eNextGameStep)
{
	if(m_pairGameStep.second == _eNextGameStep)
	{
		return;
	}

	m_pairGameStep.first = m_pairGameStep.second;
	m_pairGameStep.second = _eNextGameStep;

	if(m_arrayGameStep[m_pairGameStep.second] != nullptr)
	{
		m_arrayGameStep[m_pairGameStep.second]();
	}
}

void CTRScissorsRockPaper_Game::ToggleButtonSRP(vector<CGUIButton*> _vecButton, vector<CGUIButton*> _vecButtonDis, bool _bOn)
{
	for(auto& i : _vecButton)
	{
		i->setVisible(_bOn ? true : false);
	}

	for(auto& i : _vecButtonDis)
	{
		i->setVisible(_bOn ? false : true);
	}
}

void CTRScissorsRockPaper_Game::PlaySoundSRP(ESoundName _eSoundName)
{
	if(m_eSoundName == _eSoundName)
	{
		return;
	}

	m_eSoundName = _eSoundName;

	switch(_eSoundName)
	{
	case CTRScissorsRockPaper_Game::SN_BUTTON_CLICK:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\button-click.wav");
		break;

	case CTRScissorsRockPaper_Game::SN_RPS_WIN:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_win.wav");
		break;

	case CTRScissorsRockPaper_Game::SN_RPS_LOSE:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_lose.wav");
		break;

	case CTRScissorsRockPaper_Game::SN_RPS_DRAW:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_draw.wav");
		break;

	case CTRScissorsRockPaper_Game::SN_CARD_GET:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\card-get.wav");
		break;

	case CTRScissorsRockPaper_Game::SN_RPS_COUNT:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_count.wav");
		break;

	case CTRScissorsRockPaper_Game::SN_RPS_1:
	case CTRScissorsRockPaper_Game::SN_RPS_2:
	case CTRScissorsRockPaper_Game::SN_RPS_3:
		switch(CRandomGen::instance.iRandom(0, 2))
		{
		case 0:
			m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_1.wav");
			break;
		case 1:
			m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_2.wav");
			break;
		case 2:
			m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_3.wav");
			break;
		}
		break;

	case CTRScissorsRockPaper_Game::SN_RPS_DRAW1:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_fail1.wav");
		break;

	case CTRScissorsRockPaper_Game::SN_RPS_FAIL1:
	case CTRScissorsRockPaper_Game::SN_RPS_FAIL2:
		switch(CRandomGen::instance.iRandom(0, 1))
		{
		case 0:
			m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_fail1.wav");
			break;
		case 1:
			m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_fail2.wav");
			break;
		}
		break;

	case CTRScissorsRockPaper_Game::SN_STARTMENT1:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_startment1.wav");
		break;

	case CTRScissorsRockPaper_Game::SN_STARTMENT2:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_startment2.wav");
		break;

	case CTRScissorsRockPaper_Game::SN_RPS_WIN1:
	case CTRScissorsRockPaper_Game::SN_RPS_WIN2:
	case CTRScissorsRockPaper_Game::SN_RPS_WIN3:
		switch(CRandomGen::instance.iRandom(0, 2))
		{
		case 0:
			m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_win1.wav");
			break;
		case 1:
			m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_win2.wav");
			break;
		case 2:
			m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_win3.wav");
			break;
		}
		break;
	}
}

void CTRScissorsRockPaper_Game::StopSoundSRP(ESoundName _eSoundName, bool _bAll)
{
	if(_bAll)
	{
		for(size_t i = 0; i < ESoundName::SN_END; i++)
		{
			if(m_arraySound[i].isValid())
			{
				CAudioManager::getInstance().stopAudioEffect(m_arraySound[i]);
			}
		}
	}
	else
	{
		if(CAudioManager::getInstance().isPlayingAudioEffect(m_arraySound[_eSoundName]))
		{
			CAudioManager::getInstance().stopAudioEffect(m_arraySound[_eSoundName]);
		}
	}
}

bool CTRScissorsRockPaper_Game::IsPlaySoundSRP(ESoundName _eSoundName)
{
	return CAudioManager::getInstance().isPlayingAudioEffect(m_arraySound[_eSoundName]) ? true : false;
}
