#include "stdafx.h"
#include "TRMiniGameSRP_Single.h"
//
#include "TRMiniGameQuestion_NpcView.h"
#include "TRMiniGameAnswer_ChoiceSRP.h"

CTRMiniGameSRP_Single::CTRMiniGameSRP_Single()
{
}

CTRMiniGameSRP_Single::~CTRMiniGameSRP_Single()
{
	closeDialog();
}

void CTRMiniGameSRP_Single::showDialog()
{
	closeDialog();

	__super::showDialog();

	if(m_pAnswer != nullptr)
	{
		m_pChoiceSRP = std::dynamic_pointer_cast<CTRMiniGameAnswer_ChoiceSRP>(m_pAnswer);
		m_pChoiceSRP->Init();

		m_pChoiceSRP->bindBtn(m_pDlg, "CloseBtn", std::bind(&CTRMiniGameSRP_Single::Func_CloseBtn, this, std::placeholders::_1));

		m_pChoiceSRP->InitSelectSRP(m_pDlg,
			{
				{ "ScissorBtn1", std::bind(&CTRMiniGameSRP_Single::Func_ScissorsBtn, this, std::placeholders::_1), "Scissors", 0 },
				{ "RockBtn2", std::bind(&CTRMiniGameSRP_Single::Func_RockBtn, this, std::placeholders::_1), "Rock", 1 },
				{ "PaperBtn3", std::bind(&CTRMiniGameSRP_Single::Func_PaperBtn, this, std::placeholders::_1), "Paper", 2 },
			});

		m_pChoiceSRP->InitDisSRP(m_pDlg,
			{
				{ "ScissorBtnDis1", [](CGUIControl*) {return true; }, "", 0 },
				{ "RockBtnDis2", [](CGUIControl*) {return true; },  "", 0 },
				{ "PaperBtnDis3", [](CGUIControl*) {return true; },  "", 0  },
			});
	}

	m_pDlgItem = CTRUserInterface::loadGUI(m_pDlg->getControlID(), "gui/park/RockPaperScissor/RockPaperScissor_ItemDlg.gui", errmsg);
	if(m_pDlgItem != nullptr)
	{
		m_pDlgItem->setClientPos(m_pDlg->findControl("ItemDlg", GUI_SUB_CONTROL_FRAME)->getClientRect());
	}

	m_pStartBtn = static_cast<CGUIImageButton*>(m_pDlg->findControl("StartBtn", GUI_SUB_CONTROL_IMAGE_BUTTON));
	m_pStartBtn->bindButtonClickCmdFunc(BIND_CMD_FUNC(&CTRMiniGameSRP::Func_StartBtn, this));

	InitRoundItem(MAX_ROUNDNUM);

	m_pChoiceSRP->ToggleSelectSRP(false);

#ifdef KMW_TEST
	OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_OK, { 85121,85123,85125,85127 }, 0);
#endif // KMW_TEST
	ChangeState(STATE::STATE_OPEN);
}

void CTRMiniGameSRP_Single::closeDialog()
{
	__super::closeDialog();
}

void CTRMiniGameSRP_Single::onOpen()
{
	m_pStartBtn->setVisible(true);
	m_pDlgRound->setVisible(false);

	ChangeNPCMent(ENpcMent::NMS_BASE_SCREEN);
}

void CTRMiniGameSRP_Single::onWait()
{
}

void CTRMiniGameSRP_Single::onReady()
{
}

void CTRMiniGameSRP_Single::onStart()
{
	m_nUnmanipulated = 0;
	m_eRoundResult = ERoundResult::RR_END;

	PlayRound(m_nCurRound);
	AddTimeFunc([](float) {}, [&](float) { ChangeState(STATE::STATE_PLAYING); }, 1.0f);
}

void CTRMiniGameSRP_Single::onPlaying()
{
	ChangeNPCMent(ENpcMent::NMS_START_SELECTION_TIMER);

	AddTimeFunc(
		[&](float _fElapsed)
	{
		int nRemainTime = static_cast<int>(m_left_time - static_cast<int>(_fElapsed));
		if(nRemainTime >= 0)
		{
			UpdateUnmanipulated(nRemainTime * 10);
			ChangeSelectTime(nRemainTime);
		}
	}, [&](float) 
	{
#ifdef KMW_TEST
		OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_OK,
			[&]()
		{
			m_pSelectTime->setVisible(false);

			if(m_nUnmanipulated >= 2)
			{
				return eRSP_SELECTION_RESULT_TIME_OVER;
			}

			switch(CRandomGen::instance.iRandom(0, 2))
			{
			case 0: return eRSP_SELECTION_RESULT_WIN;
			case 1: return eRSP_SELECTION_RESULT_LOSE;
			case 2: return eRSP_SELECTION_RESULT_TIE;
			}
		}(),
			[]()
		{
			switch(CRandomGen::instance.iRandom(0, 2))
			{
			case 0: return eRSP_SELECTION_R;
			case 1: return eRSP_SELECTION_S;
			case 2: return eRSP_SELECTION_P;
			}
		}(), 0, 0);
#endif // KMW_TEST
	}, USER_SELECT_TIME + 0.1f);
}

void CTRMiniGameSRP_Single::onResult()
{
	if(m_nUnmanipulated == -1)
	{
		ChangeNPCMent(ENpcMent::NMS_SELECT_TIMER_END);
	}

	SettingResultImage(m_eRoundResult);

	switch(m_eRoundResult)
	{
	case CTRMiniGameSRP::RR_WIN:
		get<ERoundResult::RR_WIN>(m_tupleResult) += 1;
		if(get<ERoundResult::RR_WIN>(m_tupleResult) < MAX_WIN)
		{
#ifdef KMW_TEST
			OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_OK, m_nCurRound + 1, USER_SELECT_TIME, 0);
#endif // KMW_TEST
		}
		else
		{
			ChangeState(STATE::STATE_END);
		}
		break;

	case CTRMiniGameSRP::RR_LOSE:
		get<ERoundResult::RR_LOSE>(m_tupleResult) += 1;
		ChangeState(STATE::STATE_END);
		break;

	case CTRMiniGameSRP::RR_DRAW:
		get<ERoundResult::RR_DRAW>(m_tupleResult) += 1;
#ifdef KMW_TEST
		OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_OK, m_nCurRound, USER_SELECT_TIME, 0);
#endif // KMW_TEST
		break;
	}
}

void CTRMiniGameSRP_Single::onEnd()
{
}

void CTRMiniGameSRP_Single::onFrameMove(float fElapsed)
{
	__super::onFrameMove(fElapsed);

	if(m_pQuestion != nullptr)
	{
		m_pQuestion->Update(fElapsed);
	}
}

bool CTRMiniGameSRP_Single::Func_CloseBtn(CGUIControl * _pDlg)
{
	closeDialog();
	return true;
}

bool CTRMiniGameSRP_Single::Func_ScissorsBtn(CGUIControl * _pDlg)
{
	if(m_pChoiceSRP == nullptr || getState() != STATE::STATE_PLAYING)
	{
		return false;
	}

	if(m_pChoiceSRP->UpdateSelectSRP(0))
	{
#ifdef KMW_TEST
	
#elif
		CNetClientManager::getInstance().requestPrivateRSPSelection(selectRSP(0), m_nCurRound);
#endif // KMW_TEST
	}
	m_nUnmanipulated = -1;

	return true;
}

bool CTRMiniGameSRP_Single::Func_RockBtn(CGUIControl * _pDlg)
{
	if(m_pChoiceSRP == nullptr || getState() != STATE::STATE_PLAYING)
	{
		return false;
	}

	if(m_pChoiceSRP->UpdateSelectSRP(1))
	{
#ifdef KMW_TEST

#elif
		CNetClientManager::getInstance().requestPrivateRSPSelection(selectRSP(1), m_nCurRound);
#endif // KMW_TEST
		m_nUnmanipulated = -1;
	}

	return true;
}

bool CTRMiniGameSRP_Single::Func_PaperBtn(CGUIControl * _pDlg)
{
	if(m_pChoiceSRP == nullptr || getState() != STATE::STATE_PLAYING)
	{
		return false;
	}

	if(m_pChoiceSRP->UpdateSelectSRP(2))
	{
#ifdef KMW_TEST

#elif
		CNetClientManager::getInstance().requestPrivateRSPSelection(selectRSP(2), m_nCurRound);
#endif // KMW_TEST
		m_nUnmanipulated = -1;
	}
	return true;
}

bool CTRMiniGameSRP_Single::Func_StartBtn(CGUIControl * _pDlg)
{
	m_pStartBtn->setVisible(false);
	m_pChoiceSRP->ToggleSelectSRP(true);

#ifdef KMW_TEST
	OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_OK, 1, USER_SELECT_TIME, 0);
#elif
	CNetClientManager::getInstance().requestPrivateRSPGameStart(0);
#endif // KMW_TEST
	return true;
}

string CTRMiniGameSRP_Single::GetNPCMent(ENpcMent _eCurNpcMent)
{
	switch(_eCurNpcMent)
	{
	case CTRMiniGameSRP::NMS_BASE_SCREEN:
		// "좋아, 보상을 줄게.<br>허나, 그냥은 심심하지…<br>게임 한번 어때?"
		return m_mapMent[make_tuple(0, _eCurNpcMent, 0)];

	case CTRMiniGameSRP::NMS_START_SELECTION_TIMER:
		// "가위! 바위! 보!<br>할 줄 알지?!"
		return m_mapMent[make_tuple(0, _eCurNpcMent, 0)];

	case CTRMiniGameSRP::NMS_SELECT_TIMER_END:
		// "확실해?<br>그걸로 할 거야?"
		return m_mapMent[make_tuple(0, _eCurNpcMent, 0)];

	case CTRMiniGameSRP::NMS_USER_NO_OPERATION:
		// "날 놀리는 건가?"
		// "뭐 하는 거야?"
		// "아아~ 오랜만에 놀 거리가<br>생기나 했는데~"
		return m_mapMent[make_tuple(0, _eCurNpcMent, m_nUnmanipulated)];

	case CTRMiniGameSRP::NMS_USER_LOSE:
		// "내가 이겼네?<br>미안해서 어쩌나?"
		return m_mapMent[make_tuple(0, _eCurNpcMent, 0)];

	case CTRMiniGameSRP::NMS_USER_WIN:
		// "그래…<br>이 정도는 되어야지!"
		// "으음…<br>좀 하는걸??"
		// "아~ 졌다 졌어.<br>오랜만에 재미있었어!"
		return m_mapMent[make_tuple(0, _eCurNpcMent, 0)];

	case CTRMiniGameSRP::NMS_USER_DRAW:
		// "오오!!<br>흥미진진 한 걸?!"
		return m_mapMent[make_tuple(0, _eCurNpcMent, 0)];
	}
}

void CTRMiniGameSRP_Single::UpdateUnmanipulated(int _nTime)
{
	if(m_nUnmanipulated != -1)
	{
		if(28 < _nTime && _nTime <= 35)
		{
			m_nUnmanipulated = 0;
			ChangeNPCMent(ENpcMent::NMS_USER_NO_OPERATION);
		}
		else if(15 < _nTime && _nTime <= 25)
		{
			m_nUnmanipulated = 1;
			ChangeNPCMent(ENpcMent::NMS_USER_NO_OPERATION);
		}
		else if(5 < _nTime && _nTime <= 15)
		{
			m_nUnmanipulated = 2;
			ChangeNPCMent(ENpcMent::NMS_USER_NO_OPERATION);
		}
	}
	else if(5 < _nTime && _nTime <= 15)
	{
		ChangeNPCMent(ENpcMent::NMS_USER_NO_OPERATION);
	}
}



// ==================================================================
// 개인전 : 서버
// ==================================================================
void CTRMiniGameSRP_Single::OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state)
{
	m_item_list.assign(begin(item_list), end(item_list));
	SettingRoundItem();
}

void CTRMiniGameSRP_Single::OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state)
{
	m_nCurRound = current_reward_state;
	m_left_time = left_time;

	ChangeState(STATE::STATE_START);
}

void CTRMiniGameSRP_Single::OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward)
{
	if(m_pSelectTime->isVisible())
	{
		m_pSelectTime->setVisible(false);
	}

	ChangeUserView_Yeono(selectSRP(server_selection));

	switch(r)
	{
	case eRSP_SELECTION_RESULT_WIN:
		m_eRoundResult = ERoundResult::RR_WIN;
		ChangeState(STATE::STATE_RESULT);
		break;

	case eRSP_SELECTION_RESULT_LOSE:
	case eRSP_SELECTION_RESULT_TIME_OVER:
		m_eRoundResult = ERoundResult::RR_LOSE;
		ChangeState(STATE::STATE_RESULT);
		break;

	case eRSP_SELECTION_RESULT_TIE:
		m_eRoundResult = ERoundResult::RR_DRAW;
		ChangeState(STATE::STATE_RESULT);
		break;
	}
}
