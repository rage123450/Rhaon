#include "stdafx.h"
#include "TRMiniGameSRP.h"
//
#include "TRMiniGameQuestion_NpcView.h"
#include "TRMiniGameAnswer_ChoiceSRP.h"
#include "gui/GUIItemImageCtrl.h"
#include "gameui/ClientItemInfoLoader.h"

CTRMiniGameSRP::CTRMiniGameSRP()
{
}

CTRMiniGameSRP::~CTRMiniGameSRP()
{
}

void CTRMiniGameSRP::showDialog()
{
	__super::showDialog();

	CTaskManager::getInstance().addTask(this);

	initSubDlg();

	m_pDlg = CTRUserInterface::loadGUI("gui/park/RockPaperScissor/RockPaperScissor_Base.gui", errmsg);
	if(m_pDlg == nullptr)
	{
		return;
	}

	m_pDlg->centerPosition();
	m_pDlg->setModalDialog(true);
	m_pDlg->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
	CGUIManager::getInstance().setFocus(m_pDlg->getControlID());

	m_pDlgRound = CTRUserInterface::loadGUI(m_pDlg->getControlID(), "gui/park/RockPaperScissor/RockPaperScissor_RoundDlg.gui", errmsg);
	if(m_pDlgRound)
	{
		m_pDlgRound->setClientPos(m_pDlg->findControl("RoundDlg", GUI_SUB_CONTROL_FRAME)->getClientRect());
	}

	m_pTime = static_cast<CGUIImageCtrl*>(m_pDlg->findControl("Time", GUI_SUB_CONTROL_IMAGE_CTRL));
	m_pTime->setVisible(false);

	m_pRound = CGUIManager::getInstance().createControl<CGUIImageText>(m_pDlgRound->getControlID());
	if(m_pRound != nullptr && m_pTime != nullptr)
	{
		m_pRound->setClientPos(m_pDlgRound->findControl("Round", GUI_SUB_CONTROL_FRAME)->getClientRect());
		m_pRound->setAlign(GUI_HALIGN_CENTER);
		m_pRound->setCharInfo('1', '8', m_pTime->getImage()->getFileName(), CRectWH(0, 818, 115, 103), CPointInfo(115, 0));
		m_pRound->setCharInfo('9', '9', m_pTime->getImage()->getFileName(), CRectWH(0, 818 + 103, 115, 103), CPointInfo(115, 0));
		m_pRound->setCharInfo('0', '0', m_pTime->getImage()->getFileName(), CRectWH(0 + 115, 818 + 103, 115, 103), CPointInfo(115, 0));
	}

	m_pSelectTime = CGUIManager::getInstance().createControl<CGUIImageText>(m_pDlg->getControlID());
	if(m_pSelectTime != nullptr && m_pTime != nullptr)
	{
		m_pSelectTime->setClientPos(m_pTime->getClientRect());
		m_pSelectTime->setAlign(GUI_HALIGN_CENTER);
		m_pSelectTime->setCharInfo('1', '5', m_pTime->getImage()->getFileName(), CRectWH(529, 660, 99, 156), CPointInfo(99, 0));
	}

	if(m_pQuestion != nullptr)
	{
		m_pNpcView = std::dynamic_pointer_cast<CTRMiniGameQuestion_NpcView>(m_pQuestion);
		m_pNpcView->Init(m_pDlg, "CharacterView", "SRP_Yeono", "ready", { 35.f, 115.f });
		if(m_pNpcView->LoadMent("script\\Content\\ScissorsRockPaperNPCMent.txt"))
		{
			m_mapMent = m_pNpcView->GetMent();
		}
	}

	m_pNpcMent = static_cast<CFormatedStaticText*>(m_pDlg->findControl("NpcMent", GUI_SUB_CONTROL_FORMATED_STATIC_TEXT));

	m_nCurRound = 0;

	m_pWin = static_cast<CGUIImageCtrl*>(m_pDlg->findControl("Win", GUI_SUB_CONTROL_IMAGE_CTRL));
	m_pLose = static_cast<CGUIImageCtrl*>(m_pDlg->findControl("Lose", GUI_SUB_CONTROL_IMAGE_CTRL));
	m_pDraw = static_cast<CGUIImageCtrl*>(m_pDlg->findControl("Draw", GUI_SUB_CONTROL_IMAGE_CTRL));
}

void CTRMiniGameSRP::closeDialog()
{
	if(!isVisible())
	{
		return;
	}

	if(m_pDlg)
	{
		m_pDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
		m_pDlg = nullptr;
	}

	CTaskManager::getInstance().removeTask(this);
}

bool CTRMiniGameSRP::isVisible()
{
	return m_pDlg == nullptr ? false : m_pDlg->isVisible() ? true : false;
}

void CTRMiniGameSRP::onFrameMove(float fElapsed)
{
	UpdateTimeFunc(fElapsed);
}

void CTRMiniGameSRP::initSubDlg()
{
	initQuestionDlg(CTRMiniGameQuestion::QuestionType::Question_NPCVIEW);
	initAnswerDlg(CTRMiniGameAnswer::AnswerType::Answer_SRP);
}

bool CTRMiniGameSRP::Func_StartBtn(CGUIControl * _pDlg)
{
	return true;
}

void CTRMiniGameSRP::CreateRewardDlg()
{
	PlaySoundSRP(ESoundName::SN_CARD_GET);
}

void CTRMiniGameSRP::InitRoundItem(int _nRoundItemNum)
{
	m_vecRoundItem.clear();
	std::vector<ROUND_ITEM>().swap(m_vecRoundItem);
	m_vecRoundItem.reserve(_nRoundItemNum);
	
	for(size_t i = 0; i < _nRoundItemNum; i++)
	{
		ROUND_ITEM temp;
		temp.m_pItemImage = static_cast<CGUIItemImageCtrl*>(m_pDlgItem->findControl("Item" + to_string(i + 1), GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
		temp.m_pImage = static_cast<CGUIImageCtrl*>(m_pDlgItem->findControl("Round" + to_string(i + 1), GUI_SUB_CONTROL_IMAGE_CTRL));
		m_vecRoundItem.push_back(temp);
	}
}

void CTRMiniGameSRP::SettingRoundItem()
{
	if(m_item_list.empty() || m_vecRoundItem.size() != m_item_list.size())
	{
		return;
	}

	for(size_t i = 0; i < m_item_list.size(); i++)
	{
		const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getRealItemInfo(m_item_list[i]);
		if(pItemInfo && m_vecRoundItem[i].m_pItemImage)
		{
			m_vecRoundItem[i].m_pItemImage->setRealItemImage(pItemInfo);
			m_vecRoundItem[i].m_pItemImage->setViewItemDetail(false);
		}
	}
}

void CTRMiniGameSRP::SettingResultImage(ERoundResult _eRoundReulst)
{
	m_pWin->setVisible(false);
	m_pLose->setVisible(false);
	m_pDraw->setVisible(false);

	switch(_eRoundReulst)
	{
	case CTRMiniGameSRP::RR_WIN:
		AddTimeFunc([](float) {}, [&](float) {PlaySoundSRP(ESoundName::SN_RPS_WIN); PlaySoundSRP(ESoundName::SN_RPS_WIN1); }, RESULT_DELAY_TIME);
		AddTimeFunc([](float) {}, [&](float) {ChangeNPCMent(NMS_USER_WIN); }, RESULT_WAIT_TIME);
		m_pWin->setAnimator(new CGUIAnimatorDelay(RESULT_DELAY_TIME));
		m_pWin->pushAnimator(new CGUIAnimatorFadeIn(0.3f, true));
		m_pWin->pushAnimator(new CGUIAnimatorDelay(0.5f));
		m_pWin->pushAnimator(new CGUIAnimatorFadeOutHide(0.2f));
		break;

	case CTRMiniGameSRP::RR_LOSE:
		AddTimeFunc([](float) {}, [&](float) {PlaySoundSRP(ESoundName::SN_RPS_LOSE); PlaySoundSRP(ESoundName::SN_RPS_FAIL1); }, RESULT_DELAY_TIME);
		AddTimeFunc([](float) {}, [&](float) {ChangeNPCMent(NMS_USER_LOSE); }, RESULT_WAIT_TIME);
		m_pLose->setAnimator(new CGUIAnimatorDelay(RESULT_DELAY_TIME));
		m_pLose->pushAnimator(new CGUIAnimatorFadeIn(0.3f, true));
		m_pLose->pushAnimator(new CGUIAnimatorDelay(0.5f));
		m_pLose->pushAnimator(new CGUIAnimatorFadeOutHide(0.2f));
		break;

	case CTRMiniGameSRP::RR_DRAW:
		AddTimeFunc([](float) {}, [&](float) {PlaySoundSRP(ESoundName::SN_RPS_DRAW); PlaySoundSRP(ESoundName::SN_RPS_DRAW1); }, RESULT_DELAY_TIME);
		AddTimeFunc([](float) {}, [&](float) {ChangeNPCMent(NMS_USER_DRAW); }, RESULT_WAIT_TIME);
		m_pDraw->setAnimator(new CGUIAnimatorDelay(RESULT_DELAY_TIME));
		m_pDraw->pushAnimator(new CGUIAnimatorFadeIn(0.3f, true));
		m_pDraw->pushAnimator(new CGUIAnimatorDelay(0.5f));
		m_pDraw->pushAnimator(new CGUIAnimatorFadeOutHide(0.2f));
		break;
	}
}

CTRMiniGameSRP::ESelectSRP CTRMiniGameSRP::selectSRP(eRSP_SELECTION eRsp)
{
	switch(eRsp)
	{
	case eRSP_SELECTION_R: return ESelectSRP::SS_ROCK;
	case eRSP_SELECTION_S: return ESelectSRP::SS_SCISSORS;
	case eRSP_SELECTION_P: return ESelectSRP::SS_PAPER;
	}

	return ESelectSRP::SS_END;
}

eRSP_SELECTION CTRMiniGameSRP::selectRSP(ESelectSRP eRsp)
{
	switch(eRsp)
	{
	case SS_SCISSORS: return eRSP_SELECTION_S;
	case SS_ROCK: return eRSP_SELECTION_R;
	case SS_PAPER: return eRSP_SELECTION_P;
	}

	return eRSP_SELECTION_COUNT;
}

eRSP_SELECTION CTRMiniGameSRP::selectRSP(int nRsp)
{
	switch(nRsp)
	{
	case 0: return eRSP_SELECTION_S;
	case 1: return eRSP_SELECTION_R;
	case 2: return eRSP_SELECTION_P;
	}

	return eRSP_SELECTION_COUNT;
}

void CTRMiniGameSRP::ChangeNPCMent(ENpcMent _eCurNpcMent)
{
	ChangeFormatedText(m_pNpcMent, GetNPCMent(_eCurNpcMent));
}

void CTRMiniGameSRP::ChangeUserView_Yeono(ESelectSRP _eSelectSRP)
{
	switch(_eSelectSRP)
	{
	case CTRMiniGameSRP::SS_SCISSORS:
		m_pNpcView->ChangeUserView("yeono_scissors", "ready_02");
		break;
	case CTRMiniGameSRP::SS_ROCK:
		m_pNpcView->ChangeUserView("yeono_rock", "ready_02");
		break;
	case CTRMiniGameSRP::SS_PAPER:
		m_pNpcView->ChangeUserView("yeono_paper", "ready_02");
		break;
	}
}

void CTRMiniGameSRP::PlaySoundSRP(ESoundName _eSoundName)
{
	if(m_eSoundName == _eSoundName)
	{
		return;
	}

	m_eSoundName = _eSoundName;

	switch(_eSoundName)
	{
	case CTRMiniGameSRP::SN_BUTTON_CLICK:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\button-click.wav");
		break;

	case CTRMiniGameSRP::SN_RPS_WIN:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_win.wav");
		break;

	case CTRMiniGameSRP::SN_RPS_LOSE:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_lose.wav");
		break;

	case CTRMiniGameSRP::SN_RPS_DRAW:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_draw.wav");
		break;

	case CTRMiniGameSRP::SN_CARD_GET:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\card-get.wav");
		break;

	case CTRMiniGameSRP::SN_RPS_COUNT:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_count.wav");
		break;

	case CTRMiniGameSRP::SN_RPS_1:
	case CTRMiniGameSRP::SN_RPS_2:
	case CTRMiniGameSRP::SN_RPS_3:
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

	case CTRMiniGameSRP::SN_RPS_DRAW1:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_fail1.wav");
		break;

	case CTRMiniGameSRP::SN_RPS_FAIL1:
	case CTRMiniGameSRP::SN_RPS_FAIL2:
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

	case CTRMiniGameSRP::SN_STARTMENT1:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_startment1.wav");
		break;

	case CTRMiniGameSRP::SN_STARTMENT2:
		m_arraySound[_eSoundName] = CAudioManager::getInstance().playAudioEffectByFileName("sound\\rps_startment2.wav");
		break;

	case CTRMiniGameSRP::SN_RPS_WIN1:
	case CTRMiniGameSRP::SN_RPS_WIN2:
	case CTRMiniGameSRP::SN_RPS_WIN3:
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

void CTRMiniGameSRP::StopSoundSRP(ESoundName _eSoundName, bool _bAll)
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

bool CTRMiniGameSRP::IsPlaySoundSRP(ESoundName _eSoundName)
{
	return CAudioManager::getInstance().isPlayingAudioEffect(m_arraySound[_eSoundName]) ? true : false;
}

void CTRMiniGameSRP::ChangeImageText(CGUIImageText * _pText, string _strText)
{
	if(_pText == nullptr)
	{
		return;
	}

	std::string strPrevText = "";
	_pText->getText(strPrevText);
	if(strPrevText != _strText)
	{
		_pText->setText(_strText);
		_pText->setAnimator(new CGUIAnimatorScale(0.2f, 2.f, 1.f));
	}
}

void CTRMiniGameSRP::ChangeSelectTime(int _nTime)
{
	if(m_pSelectTime == nullptr)
	{
		return;
	}

	if(!m_pSelectTime->isVisible())
	{
		m_pSelectTime->setVisible(true);
	}

	_nTime = _nTime < 1 ? 1 : _nTime;
	_nTime = _nTime > 5 ? 5 : _nTime;

	ChangeImageText(m_pSelectTime, format("%d", _nTime));
}

void CTRMiniGameSRP::PlayRound(int _nRoundNum, float _fFadeIn, float _fDealy, float _fFadeOut)
{
	PlayRoundAnimation(_fFadeIn, _fDealy, _fFadeOut);
	ChangeRoundNum(_nRoundNum);
}

void CTRMiniGameSRP::ChangeRoundNum(int _nRoundNum)
{
	if(m_pRound == nullptr)
	{
		return;
	}

	if(!m_pRound->isVisible())
	{
		m_pRound->setVisible(true);
	}

	_nRoundNum = _nRoundNum < 0 ? 0 : _nRoundNum;
	_nRoundNum = _nRoundNum > 9 ? 9 : _nRoundNum;

	ChangeImageText(m_pRound, format("%d", _nRoundNum % 10));
}

void CTRMiniGameSRP::PlayRoundAnimation(float _fFadeIn, float _fDealy, float _fFadeOut)
{
	if(m_pDlgRound == nullptr)
	{
		return;
	}

	m_pDlgRound->setAnimator(new CGUIAnimatorFadeIn(_fFadeIn, true));
	m_pDlgRound->pushAnimator(new CGUIAnimatorDelay(_fDealy));
	m_pDlgRound->pushAnimator(new CGUIAnimatorFadeOutHide(_fFadeOut));
}
