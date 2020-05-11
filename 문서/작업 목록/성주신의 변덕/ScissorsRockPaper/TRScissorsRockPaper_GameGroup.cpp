#include "stdafx.h"
#include "TRScissorsRockPaper_GameGroup.h"
//
#include "gui/GUIItemImageCtrl.h"
#include "gui/GUIObjectView.h"
#include "gameui/ClientItemInfoLoader.h"
#include "language/LanguageHeader.h"
//
#include "TRScissorsRockPaper_RewardDlg.h"

CTRScissorsRockPaper_GameGroup::CTRScissorsRockPaper_GameGroup() : m_rewardDlg(this)
{
}

CTRScissorsRockPaper_GameGroup::~CTRScissorsRockPaper_GameGroup()
{
	closeDialog();
}

bool CTRScissorsRockPaper_GameGroup::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	CGUIControl* pCtrl = ctrlID.findControl();
	if(!pCtrl)
	{
		return false;
	}

	string name = pCtrl->getName();

	for(auto& x : m_arrayButton)
	{
		if(get<0>(x) == name)
		{
			get<1>(x)();
			break;
		}
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRScissorsRockPaper_GameGroup::showDialog()
{
	__super::showDialog();

	m_bInGame = true;
	m_user_in_playing = 1;
	InitNPCMent();
	CTaskManager::getInstance().addTask(this);
	PlaySoundSRP(ESoundName::SN_END);
}

void CTRScissorsRockPaper_GameGroup::closeDialog()
{
	if(m_bInGame)
	{
		m_bInGame = false;
		CNetClientManager::getInstance().requestGlobalRSPClose();
	}

	StopSoundSRP(ESoundName::SN_END, true);
	
	for(auto& x : m_arrayDlg)
	{
		if(x)
		{
			x->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
			x = nullptr;
		}
	}

	for(auto& x : m_arrayGauge)
	{
		if(x.pDlg)
		{
			x.pDlg->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
			x.pDlg = nullptr;
		}
	}

	CTaskManager::getInstance().removeTask(this);
}

void CTRScissorsRockPaper_GameGroup::InitName()
{
	InitGUIName({
		make_tuple<EGUIName, string>(EGUIName::GN_BASE, "gui/park/RockPaperScissor/RockPaperScissor_Base.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_BASEINFO, "gui/park/RockPaperScissor/RockPaperScissor_BaseInfo.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_GAUGEDLG, "gui/park/RockPaperScissor/RockPaperScissor_GaugeDlg.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_ITEMDLG2, "gui/park/RockPaperScissor/RockPaperScissor_ItemDlg2.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_REWARD, "gui/park/RockPaperScissor/RockPaperScissor_Reward.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_ROUND, "gui/park/RockPaperScissor/RockPaperScissor_RoundDlg.gui"),
		});

	InitControlName(EControlType::CT_BUTTON,
		{
			// Base
			"ScissorBtn1","RockBtn2","PaperBtn3","CloseBtn","StartBtn","ScissorBtnDis1","RockBtnDis2","PaperBtnDis3",
		});

	InitControlName(EControlType::CT_STATICTEXT,
		{
			// Base

			// BaseInfo
			"Change_WaitingTime_Ment","Change_WaitingTime","SurvivorMent","Survivor",

			// GaugeDlg
			"Number",
		});

	InitControlName(EControlType::CT_FORMATEDTEXT,
		{
			// Base
			"NpcMent",
		});

	InitControlName(EControlType::CT_FRAME,
		{
			// Base
			"BaseFrame","ItemDlg","BaseInfoDlg","RoundDlg","GageDlg1","GageDlg2","GageDlg3","Base_Bk",

			// GaugeDlg
			"Gauge",

			// RoundDlg
			"Round",
		});

	InitControlName(EControlType::CT_IMAGECONTROL,
		{
			// Base
			"Win","Lose","Draw","Time",

			// ItemDlg
			"Item1","Item2","Item3","Item4","Item5","Item6","Item7","Item8","Item9","Item10","Item11",
			"Round1","Round2","Round3","Round4","Round5","Round6","Round7","Round8","Round9","Round10","Round11",

			// GaugeDlg
			"GaugeImg","ScissorImg1","RockImg2","PaperImg3",
		});
}

void CTRScissorsRockPaper_GameGroup::InitGUI()
{
	string errmsg;

	for(int i = 0; i < EGUIName::GN_END; i++)
	{
		switch(i)
		{
		case CTRScissorsRockPaper_GameGroup::GN_BASE:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[i], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->centerPosition();
				m_arrayDlg[i]->setModalDialog(true);
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
				CGUIManager::getInstance().setFocus(m_arrayDlg[i]->getControlID());
				m_arrayDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
			break;

		case CTRScissorsRockPaper_GameGroup::GN_BASEINFO:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_arrayDlg[EGUIName::GN_BASE]->getControlID(), m_mapGUIName[i], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->setClientPos(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_FRAME][EFrameName::FN_BASE_BASEINFODLG], GUI_SUB_CONTROL_FRAME)->getClientRect());
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
			}
			break;

		case CTRScissorsRockPaper_GameGroup::GN_GAUGEDLG:
			InitGauge();
			break;

		case CTRScissorsRockPaper_GameGroup::GN_ITEMDLG2:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_arrayDlg[EGUIName::GN_BASE]->getControlID(), m_mapGUIName[i], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->setClientPos(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_FRAME][EFrameName::FN_BASE_ITEMDLG], GUI_SUB_CONTROL_FRAME)->getClientRect());
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
			}
			break;

		case CTRScissorsRockPaper_GameGroup::GN_REWARD:
			break;

		case CTRScissorsRockPaper_GameGroup::GN_ROUND:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_arrayDlg[EGUIName::GN_BASE]->getControlID(), m_mapGUIName[i], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->setClientPos(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_FRAME][EFrameName::FN_BASE_ROUNDDLG], GUI_SUB_CONTROL_FRAME)->getClientRect());
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
			}
			break;
		}
	}
}

void CTRScissorsRockPaper_GameGroup::InitButton()
{
	if(m_arrayDlg[EGUIName::GN_BASE] == nullptr)
	{
		return;
	}

	for(int i = 0; i < EButtonName::BN_END; i++)
	{
		get<0>(m_arrayButton[i]) = m_arrayName[EControlType::CT_BUTTON][i];

		switch(i)
		{
		case CTRScissorsRockPaper_GameGroup::BN_BASE_SCISSORBTN1:
			get<1>(m_arrayButton[i]) = [&]()
			{
				PlaySoundSRP(ESoundName::SN_BUTTON_CLICK);
				UpdateSelectSRP(ESelectSRP::SS_SCISSORS);
			};

			get<2>(m_arrayButton[i])
				= static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]
					->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_SCISSORBTN1], GUI_SUB_CONTROL_IMAGE_BUTTON));
			get<2>(m_arrayButton[i])->setVisible(true);
			break;

		case CTRScissorsRockPaper_GameGroup::BN_BASE_ROCKBTN2:
			get<1>(m_arrayButton[i]) = [&]()
			{
				PlaySoundSRP(ESoundName::SN_BUTTON_CLICK);
				UpdateSelectSRP(ESelectSRP::SS_ROCK);
			};

			get<2>(m_arrayButton[i])
				= static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]
					->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_ROCKBTN2], GUI_SUB_CONTROL_IMAGE_BUTTON));
			get<2>(m_arrayButton[i])->setVisible(true);
			break;

		case CTRScissorsRockPaper_GameGroup::BN_BASE_PAPERBTN3:
			get<1>(m_arrayButton[i]) = [&]()
			{
				PlaySoundSRP(ESoundName::SN_BUTTON_CLICK);
				UpdateSelectSRP(ESelectSRP::SS_PAPER);
			};

			get<2>(m_arrayButton[i])
				= static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]
					->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_PAPERBTN3], GUI_SUB_CONTROL_IMAGE_BUTTON));
			get<2>(m_arrayButton[i])->setVisible(true);
			break;

		case CTRScissorsRockPaper_GameGroup::BN_BASE_CLOSEBTN:
			get<1>(m_arrayButton[i]) = [&]()
			{
				switch(GetCurGameStep())
				{
				case CTRScissorsRockPaper_Game::GS_WAIT_START:
					closeDialog();
					break;

				case CTRScissorsRockPaper_Game::GS_WAIT_SELECT:
					// StringTable : 종료 시, 이번 미니게임은 참여할 수 없습니다.종료하시겠습니까 ?
					m_pYesNoDlg.showDialog(_STR(QUESTION_EXIT_CANTJOIN_INTHIS_MINIGAME), this, &CTRScissorsRockPaper_GameGroup::ShowYes, nullptr);
					break;
				}
			};

			get<2>(m_arrayButton[i])
				= static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]
					->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_CLOSEBTN], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;

		case CTRScissorsRockPaper_GameGroup::BN_BASE_STARTBTN:
			get<1>(m_arrayButton[i]) = [](){};
			get<2>(m_arrayButton[i])
				= static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]
					->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_STARTBTN], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;

		case CTRScissorsRockPaper_GameGroup::BN_BASE_SCISSORBTNDIS1:
			get<1>(m_arrayButton[i]) = [&]() {};
			get<2>(m_arrayButton[i])
				= static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]
					->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_SCISSORBTNDIS1], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;

		case CTRScissorsRockPaper_GameGroup::BN_BASE_ROCKBTNDIS2:
			get<1>(m_arrayButton[i]) = [&]() {};
			get<2>(m_arrayButton[i])
				= static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]
					->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_ROCKBTNDIS2], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;

		case CTRScissorsRockPaper_GameGroup::BN_BASE_PAPERBTNDIS3:
			get<1>(m_arrayButton[i]) = [&]() {};
			get<2>(m_arrayButton[i])
				= static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]
					->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_PAPERBTNDIS3], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;
		}
	}
}

void CTRScissorsRockPaper_GameGroup::InitStaticText()
{
	if(!m_arrayDlg[EGUIName::GN_BASEINFO])
	{
		return;
	}

	// BaseInfo
	m_arrayStaticText[EStaticTextName::STN_CHANGE_WAITINGTIME_MENT]
		= static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_BASEINFO]
			->findControl(m_arrayName[EControlType::CT_STATICTEXT][EStaticTextName::STN_CHANGE_WAITINGTIME_MENT], GUI_SUB_CONTROL_STATIC_TEXT));

	m_arrayStaticText[EStaticTextName::STN_CHANGE_WAITINGTIME]
		= static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_BASEINFO]
			->findControl(m_arrayName[EControlType::CT_STATICTEXT][EStaticTextName::STN_CHANGE_WAITINGTIME], GUI_SUB_CONTROL_STATIC_TEXT));

	m_arrayStaticText[EStaticTextName::STN_SURVIVORMENT]
		= static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_BASEINFO]
			->findControl(m_arrayName[EControlType::CT_STATICTEXT][EStaticTextName::STN_SURVIVORMENT], GUI_SUB_CONTROL_STATIC_TEXT));

	m_arrayStaticText[EStaticTextName::STN_SURVIVOR]
		= static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_BASEINFO]
			->findControl(m_arrayName[EControlType::CT_STATICTEXT][EStaticTextName::STN_SURVIVOR], GUI_SUB_CONTROL_STATIC_TEXT));
}

void CTRScissorsRockPaper_GameGroup::InitFormatedText()
{
	// Base
	if(!m_arrayDlg[EGUIName::GN_BASE])
	{
		return;
	}

	m_arrayFormatedText[EFormatedTextName::FTN_BASE_NPCMENT]
		= static_cast<CFormatedStaticText*>(m_arrayDlg[EGUIName::GN_BASE]
			->findControl(m_arrayName[EControlType::CT_FORMATEDTEXT][EFormatedTextName::FTN_BASE_NPCMENT], GUI_SUB_CONTROL_FORMATED_STATIC_TEXT));
}

void CTRScissorsRockPaper_GameGroup::InitImageText()
{
	// Base
	if(m_arrayImageCtrl[EImageCtrlName::IN_BASE_TIME] != nullptr && m_arrayImageCtrl[EImageCtrlName::IN_BASE_TIME]->getImage() != nullptr)
	{
		// Select_Time
		m_arrayImageText[EImageTextName::ITN_SELECT_TIME] = CGUIManager::getInstance().createControl<CGUIImageText>(m_arrayDlg[EGUIName::GN_BASE]->getControlID());
		if(m_arrayImageText[EImageTextName::ITN_SELECT_TIME])
		{
			m_arrayImageCtrl[EImageCtrlName::IN_BASE_TIME]->setVisible(false);

			m_arrayImageText[EImageTextName::ITN_SELECT_TIME]->setClientPos(m_arrayImageCtrl[EImageCtrlName::IN_BASE_TIME]->getClientRect());
			m_arrayImageText[EImageTextName::ITN_SELECT_TIME]->setAlign(GUI_HALIGN_CENTER);
			m_arrayImageText[EImageTextName::ITN_SELECT_TIME]->setCharInfo('1', '5', m_arrayImageCtrl[EImageCtrlName::IN_BASE_TIME]->getImage()->getFileName(), CRectWH(529, 660, 99, 156), CPointInfo(99, 0));
		}

		// Round_Time
		m_arrayImageText[EImageTextName::ITN_ROUND_NUM] = CGUIManager::getInstance().createControl<CGUIImageText>(m_arrayDlg[EGUIName::GN_ROUND]->getControlID());
		if(m_arrayImageText[EImageTextName::ITN_ROUND_NUM])
		{
			m_arrayImageText[EImageTextName::ITN_ROUND_NUM]->setClientPos(m_arrayDlg[EGUIName::GN_ROUND]->findControl(m_arrayName[EControlType::CT_FRAME][FN_ROUNDDLG_ROUND], GUI_SUB_CONTROL_FRAME)->getClientRect());
			m_arrayImageText[EImageTextName::ITN_ROUND_NUM]->setAlign(GUI_HALIGN_CENTER);
			m_arrayImageText[EImageTextName::ITN_ROUND_NUM]->setCharInfo('1', '8', m_arrayImageCtrl[EImageCtrlName::IN_BASE_TIME]->getImage()->getFileName(), CRectWH(0, 818, 115, 103), CPointInfo(115, 0));
			m_arrayImageText[EImageTextName::ITN_ROUND_NUM]->setCharInfo('9', '9', m_arrayImageCtrl[EImageCtrlName::IN_BASE_TIME]->getImage()->getFileName(), CRectWH(0, 818 + 103, 115, 103), CPointInfo(115, 0));
			m_arrayImageText[EImageTextName::ITN_ROUND_NUM]->setCharInfo('0', '0', m_arrayImageCtrl[EImageCtrlName::IN_BASE_TIME]->getImage()->getFileName(), CRectWH(0 + 115, 818 + 103, 115, 103), CPointInfo(115, 0));
		}
	}
}

void CTRScissorsRockPaper_GameGroup::InitUserControl()
{
	if(m_pDiceViewCtrl == nullptr)
	{
		m_pDiceViewCtrl = static_cast<CGUIUserControl*>(m_arrayDlg[EGUIName::GN_BASE]->findControl("CharacterView", GUI_SUB_CONTROL_USER_CTRL));
	}

	if(m_pDiceViewCtrl)
	{
		std::string modelName = "SRP_Yeono";

		if(modelName.empty() == false)
		{
			GUI_OBJECT::createEffectView(&m_diceObjView, m_pDiceViewCtrl, modelName);
			GUI_OBJECT::setFovy(&m_diceObjView, CONST_PI / 10);
			GUI_OBJECT::setAnimation(&m_diceObjView, format("ready"), true);
			GUI_OBJECT::setRadius(&m_diceObjView, 35.f, 115.f);
		}
	}
}

void CTRScissorsRockPaper_GameGroup::onFrameMove(float fElapsed)
{
	m_diceObjView.frameMove(fElapsed);
	UpdateTimeFunc(fElapsed);
}

void CTRScissorsRockPaper_GameGroup::UpdateGameStep_WaitStart()
{
	m_tupleRoundResult = make_tuple<int, int>(0, 0);
	m_nCurRound = 0;

	SettingResultImage(ERoundResult::RR_END);

	m_arrayDlg[EGUIName::GN_ROUND]->setVisible(false);

	InitRoundItem();

	ChangeStaticText(EStaticTextName::STN_SURVIVOR, format("%d", m_nRemainPeople));

	m_nCurNumberOfChanges = 0;
	ChangeStaticText(EStaticTextName::STN_CHANGE_WAITINGTIME, to_string(m_nCurNumberOfChanges) + " / " + to_string(MAX_NUMBER_OF_CHANGES));

	UpdateRoundItem();

	UpdateNPCMent(EProgressStep::PS_WAIT_START);

	PlaySoundSRP(ESoundName::SN_STARTMENT1);

	ToggleButtonSRP(
		{
			get<2>(m_arrayButton[BN_BASE_SCISSORBTN1]),
			get<2>(m_arrayButton[BN_BASE_ROCKBTN2]),
			get<2>(m_arrayButton[BN_BASE_PAPERBTN3]),
		}, 
		{
			get<2>(m_arrayButton[BN_BASE_SCISSORBTNDIS1]),
			get<2>(m_arrayButton[BN_BASE_ROCKBTNDIS2]),
			get<2>(m_arrayButton[BN_BASE_PAPERBTNDIS3])
		},false);

	// StringTable : 대기 시간
	ChangeStaticText(EStaticTextName::STN_CHANGE_WAITINGTIME_MENT, _STR(MSG_WAITTIME));

	AddTimeFunc([&](float _fTime)
	{
		int nRemainTime = static_cast<int>(m_fCurWaitTime - _fTime);
		if(nRemainTime < TIME_END_START && GetCurGameStep() == EGameStep::GS_WAIT_START)
		{
			ChangeGameStep(EGameStep::GS_END_START);
		}
		ChangeStaticText(EStaticTextName::STN_CHANGE_WAITINGTIME, format("%d", nRemainTime));
	}, [&](float _fTime) {}, m_fCurWaitTime);
}

void CTRScissorsRockPaper_GameGroup::UpdateGameStep_EndStart()
{
	ToggleButtonSRP(
		{
			get<2>(m_arrayButton[BN_BASE_SCISSORBTN1]),
			get<2>(m_arrayButton[BN_BASE_ROCKBTN2]),
			get<2>(m_arrayButton[BN_BASE_PAPERBTN3]),
		},
		{
			get<2>(m_arrayButton[BN_BASE_SCISSORBTNDIS1]),
			get<2>(m_arrayButton[BN_BASE_ROCKBTNDIS2]),
			get<2>(m_arrayButton[BN_BASE_PAPERBTNDIS3])
		}, true);

	UpdateNPCMent(EProgressStep::PS_WAIT_END);
	PlaySoundSRP(ESoundName::SN_STARTMENT2);
}

void CTRScissorsRockPaper_GameGroup::UpdateGameStep_WaitSelect()
{
	UpdateNPCMent(EProgressStep::PS_START_SELECTION_TIMER);

	m_arrayDlg[EGUIName::GN_ROUND]->setAnimator(new CGUIAnimatorFadeIn(0.3f, true));
	m_arrayDlg[EGUIName::GN_ROUND]->pushAnimator(new CGUIAnimatorDelay(0.5f));
	m_arrayDlg[EGUIName::GN_ROUND]->pushAnimator(new CGUIAnimatorFadeOutHide(0.3f));

	ChangeImageText(EImageTextName::ITN_ROUND_NUM, format("%d", (m_nCurRound) % 10));

	ToggleCheckedButton(ESelectSRP::SS_END, false);

	UpdateCurRoundItem();

	InitSelectSRP();

	for(auto& i : m_arrayGauge)
	{
		i.nCurNum = i.nMovNum;
	}

	// StringTable : 변경가능횟수
	ChangeStaticText(EStaticTextName::STN_CHANGE_WAITINGTIME_MENT, _STR(MSG_CONVEYANCE_POSSIBLE_COUNT));

	m_nCurNumberOfChanges = 0;
	ChangeStaticText(EStaticTextName::STN_CHANGE_WAITINGTIME, to_string(m_nCurNumberOfChanges) + " / " + to_string(MAX_NUMBER_OF_CHANGES));

	AddTimeFunc([](float) {}, [&](float) {PlaySoundSRP(ESoundName::SN_RPS_COUNT); }, 1.0f);

	m_arrayDlg[EGUIName::GN_ROUND]->pushAnimator(new CGUIAnimatorGameGroup(USER_SELECT_TIME + 0.1f,
		[]() {},
		CGUIAnimatorGameGroup::EFuncType::FT_VOID,
		[&](float _fTime)
	{
		int nRemainTime = static_cast<int>(USER_SELECT_TIME - static_cast<int>(_fTime));
		if(nRemainTime <= 0)
		{
			ToggleImageText(EImageTextName::ITN_SELECT_TIME, false);
		}
		else
		{
			if(!m_arrayImageText[EImageTextName::ITN_SELECT_TIME]->isVisible())
			{
				m_arrayImageText[EImageTextName::ITN_SELECT_TIME]->setVisible(true);
			}
			ChangeImageText(EImageTextName::ITN_SELECT_TIME, format("%d", nRemainTime));
		}
	}
	));

	for(int i = 0; i < MAX_GAUGENUM; i++)
	{
		m_arrayGauge[i].pText->setAnimator(new CGUIAnimatorIncDecText(1.0f, m_arrayGauge[i].nCurNum, m_arrayGauge[i].nMovNum));
	}
}

void CTRScissorsRockPaper_GameGroup::UpdateGameStep_EndSelect()
{
}

void CTRScissorsRockPaper_GameGroup::UpdateGameStep_WaitResult()
{
}

void CTRScissorsRockPaper_GameGroup::UpdateGameStep_EndResult()
{
	switch(m_eRoundResult)
	{
	case CTRScissorsRockPaper_GameGroup::RR_WIN:
	case CTRScissorsRockPaper_GameGroup::RR_DRAW:
		SettingResultImage(ERoundResult::RR_WIN);
		get<ERoundResult::RR_WIN>(m_tupleRoundResult) += 1;
		UpdateNPCMent(EProgressStep::PS_WIN_OVER_NPC);
		if(IsGameEndResult(m_tupleRoundResult))
		{
			UpdateCurRoundItem(MAX_WIN);

			m_arrayDlg[EGUIName::GN_BASE]->setAnimator(new CGUIAnimatorGameGroup(RESULT_NEXT_STEP,
				[&]()
			{
				CreateRewardDlg();
			}, CGUIAnimatorGameGroup::EFuncType::FT_VOID_END));
		}
		break;

	case CTRScissorsRockPaper_GameGroup::RR_LOSE:
		SettingResultImage(ERoundResult::RR_LOSE);
		get<ERoundResult::RR_LOSE>(m_tupleRoundResult) += 1;
		UpdateNPCMent(EProgressStep::PS_LOSE_OVER_NPC);
		if(IsGameEndResult(m_tupleRoundResult))
		{
			m_arrayDlg[GN_BASE]->setAnimator(new CGUIAnimatorGameGroup(RESULT_NEXT_STEP,
				[&]()
			{
				m_nCurRound -= m_nCurRound != 0 ? 1 : 0;
				CreateRewardDlg();
			}, CGUIAnimatorGameGroup::EFuncType::FT_VOID_END));
		}
		break;
	}
}

void CTRScissorsRockPaper_GameGroup::onSendGiveMsg(std::string & nickname, std::string & strMemo, int iItemNum)
{
	m_rewardDlg.closeDialog();
}

void CTRScissorsRockPaper_GameGroup::InitImageControl()
{
	// Base
	if(!m_arrayDlg[EGUIName::GN_BASE])
	{
		return;
	}

	m_arrayImageCtrl[EImageCtrlName::IN_BASE_WIN]
		= static_cast<CGUIImageCtrl*>(m_arrayDlg[EGUIName::GN_BASE]
			->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][EImageCtrlName::IN_BASE_WIN], GUI_SUB_CONTROL_IMAGE_CTRL));

	m_arrayImageCtrl[EImageCtrlName::IN_BASE_LOSE]
		= static_cast<CGUIImageCtrl*>(m_arrayDlg[EGUIName::GN_BASE]
			->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][EImageCtrlName::IN_BASE_LOSE], GUI_SUB_CONTROL_IMAGE_CTRL));

	m_arrayImageCtrl[EImageCtrlName::IN_BASE_DRAW]
		= static_cast<CGUIImageCtrl*>(m_arrayDlg[EGUIName::GN_BASE]
			->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][EImageCtrlName::IN_BASE_DRAW], GUI_SUB_CONTROL_IMAGE_CTRL));

	m_arrayImageCtrl[EImageCtrlName::IN_BASE_TIME]
		= static_cast<CGUIImageCtrl*>(m_arrayDlg[EGUIName::GN_BASE]
			->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][EImageCtrlName::IN_BASE_TIME], GUI_SUB_CONTROL_IMAGE_CTRL));
}

void CTRScissorsRockPaper_GameGroup::InitGauge()
{
	if(m_arrayDlg[EGUIName::GN_BASE] == nullptr)
	{
		return;
	}

	string errmsg;
	for(int i = 0; i < MAX_GAUGENUM; i++)
	{
		m_arrayGauge[i].pDlg = CTRUserInterface::loadGUI(m_arrayDlg[EGUIName::GN_BASE]->getControlID(), m_mapGUIName[GN_GAUGEDLG], errmsg);
		m_arrayGauge[i].pDlg->setClientPos(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_FRAME][EFrameName::FN_BASE_GAGEDLG1 + i], GUI_SUB_CONTROL_FRAME)->getClientRect());
		m_arrayGauge[i].pDlg->setDialogListener(getCommandTargetID());

		m_arrayGauge[i].pText = static_cast<CGUIStaticText*>(m_arrayGauge[i].pDlg->findControl(m_arrayName[EControlType::CT_STATICTEXT][STN_GAUGEDLG_NUMBER], GUI_SUB_CONTROL_STATIC_TEXT));
		m_arrayGauge[i].pImage = static_cast<CGUIImageCtrl*>(m_arrayGauge[i].pDlg->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][IN_GAUGEDLG_GAUGEIMG], GUI_SUB_CONTROL_IMAGE_CTRL));
	
		m_arrayGauge[i].pScissorImg1 = static_cast<CGUIImageCtrl*>(m_arrayGauge[i].pDlg->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][IN_GAUGEDLG_SCISSORIMG1], GUI_SUB_CONTROL_IMAGE_CTRL));
		m_arrayGauge[i].pRockImg2 = static_cast<CGUIImageCtrl*>(m_arrayGauge[i].pDlg->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][IN_GAUGEDLG_ROCKIMG2], GUI_SUB_CONTROL_IMAGE_CTRL));
		m_arrayGauge[i].pPaperImg3 = static_cast<CGUIImageCtrl*>(m_arrayGauge[i].pDlg->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][IN_GAUGEDLG_PAPERIMG3], GUI_SUB_CONTROL_IMAGE_CTRL));

		m_arrayGauge[i].pScissorImg1->setVisible(false);
		m_arrayGauge[i].pRockImg2->setVisible(false);
		m_arrayGauge[i].pPaperImg3->setVisible(false);

		switch(i)
		{
		case CTRScissorsRockPaper_GameGroup::SS_SCISSORS:
			m_arrayGauge[i].pScissorImg1->setVisible(true);
			break;
		case CTRScissorsRockPaper_GameGroup::SS_ROCK:
			m_arrayGauge[i].pRockImg2->setVisible(true);
			break;
		case CTRScissorsRockPaper_GameGroup::SS_PAPER:
			m_arrayGauge[i].pPaperImg3->setVisible(true);
			break;
		}
		
		m_arrayGauge[i].pFrame = static_cast<CGUIFrameImage*>(m_arrayGauge[i].pDlg->findControl(m_arrayName[EControlType::CT_FRAME][FN_GAUGEDLG_GAUGE], GUI_SUB_CONTROL_FRAME));

		CRectInfo rt = m_arrayGauge[i].pFrame->getClientRect();

		m_arrayGauge[i].nMov = 0;
		m_arrayGauge[i].nCur = 0;

		m_rtGaugeCtrl = m_arrayGauge[i].pImage->getClientRect();
		m_arrayGauge[i].pImage->getSrcRect(m_rtGaugeSrc);
		m_arrayGauge[i].pImage->setClientPos(CRectInfo(rt.left, rt.top, rt.left, rt.bottom));

		m_arrayGauge[i].pText->setText(to_string(m_arrayGauge[i].nCurNum));
	}
}

void CTRScissorsRockPaper_GameGroup::UpdateGauge()
{
	CRectInfo rt;
	int dir = 0;
	int dirNum = 0;

	for(int i = 0; i < MAX_GAUGENUM; i++)
	{
		rt = m_arrayGauge[i].pFrame->getClientRect();

		dir = GetIncrementCode(m_arrayGauge[i].nMov, m_arrayGauge[i].nCur);
		if(m_arrayGauge[i].nCur != m_arrayGauge[i].nMov)
		{
			m_arrayGauge[i].nCur += 1 * dir;

			int nWidth = m_rtGaugeCtrl.width() * m_arrayGauge[i].nCur / static_cast<float>(m_user_in_playing);
			m_arrayGauge[i].pImage->setClientPos(CRectInfo(rt.left, rt.top, rt.left + nWidth, rt.top + rt.height()));

			int nSrcWidth = m_rtGaugeSrc.width() * m_arrayGauge[i].nCur / static_cast<float>(m_user_in_playing);
			CRectInfo srt;
			m_arrayGauge[i].pImage->getSrcRect(srt);
			m_arrayGauge[i].pImage->setSrcRect(CRectInfo(srt.left, srt.top, srt.left + nSrcWidth, srt.top + srt.height()));
		}
	}
}

void CTRScissorsRockPaper_GameGroup::InitRoundItem()
{
	if(m_arrayDlg[EGUIName::GN_ITEMDLG2] == nullptr)
	{
		return;
	}

	for(int i = 0; i < MAX_ROUNDITEM; i++)
	{
		m_arrayRoundItem[i].m_pItemImage
			= static_cast<CGUIItemImageCtrl*>(m_arrayDlg[EGUIName::GN_ITEMDLG2]
				->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][i + IN_ITEMDLG2_ITEM1], GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));

		m_arrayRoundItem[i].m_pImage
			= static_cast<CGUIImageCtrl*>(m_arrayDlg[EGUIName::GN_ITEMDLG2]
				->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][i + IN_ITEMDLG2_ITEM1 + MAX_ROUNDITEM], GUI_SUB_CONTROL_IMAGE_CTRL));
	}
}

void CTRScissorsRockPaper_GameGroup::UpdateRoundItem()
{
	if(m_item_list.empty())
	{
		return;
	}

	for(int i = 0; i < MAX_ROUNDITEM; i++)
	{
		const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getRealItemInfo(m_item_list[i]);
		if(pItemInfo && m_arrayRoundItem[i].m_pItemImage)
		{
			m_arrayRoundItem[i].m_pItemImage->setRealItemImage(pItemInfo);
			m_arrayRoundItem[i].m_pItemImage->setViewItemDetail(false);
		}
	}
}

void CTRScissorsRockPaper_GameGroup::InitCurRoundItem()
{
	for(int i = 0; i < MAX_ROUNDITEM; i++)
	{
		m_arrayRoundItem[i].m_pImage->setVisible(false);
	}
}

void CTRScissorsRockPaper_GameGroup::UpdateCurRoundItem(int _nRound)
{
	InitCurRoundItem();

	if(_nRound == -1)
	{
		m_arrayRoundItem[m_nCurRound != 0 ? m_nCurRound - 1 : m_nCurRound].m_pImage->setVisible(true);
	}
	else
	{
		m_arrayRoundItem[_nRound].m_pImage->setVisible(true);
	}
}

void CTRScissorsRockPaper_GameGroup::InitNPCMent()
{
	if(m_arrayFormatedText[EFormatedTextName::FTN_BASE_NPCMENT])
	{
		m_arrayFormatedText[EFormatedTextName::FTN_BASE_NPCMENT]->setText(m_mapMent[make_tuple(0, PS_WAIT_START, 0)]);
	}
}

void CTRScissorsRockPaper_GameGroup::UpdateNPCMent(EProgressStep _eCurMent)
{
	switch(_eCurMent)
	{
	case CTRScissorsRockPaper_GameGroup::PS_WAIT_START:
	// "다들 모여봐… 후훗."
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(1, _eCurMent, 0)]);
		break;

	case CTRScissorsRockPaper_GameGroup::PS_WAIT_END:
	// "자! 충분히 모인 것 같군…<br>시작해보자!!"
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(1, _eCurMent, 0)]);
		break;

	case CTRScissorsRockPaper_GameGroup::PS_START_SELECTION_TIMER:
	// "가위… 날카로운 칼과 같지…" "바위… 무겁고 강력하게…" "보… 상냥한 포용과도 같지…" "이번엔 뭘 낼까…?<br>후후훗."
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(1, _eCurMent, CRandomGen::instance.iRandom(0, 3))]);
		break;

	case CTRScissorsRockPaper_GameGroup::PS_SELECT_TIMER_END:
	// "확실해?<br>그걸로 할 거야?"
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(1, _eCurMent, 0)]);
		break;

	case CTRScissorsRockPaper_GameGroup::PS_WIN_OVER_NPC:
	// "그래…<br>이 정도는 되어야지!"
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(1, _eCurMent, 0)]);
		break;

	case CTRScissorsRockPaper_GameGroup::PS_LOSE_OVER_NPC:
	// "내가 이겼네?<br>미안해서 어쩌나?"
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(1, _eCurMent, 0)]);
		break;
	}
}

void CTRScissorsRockPaper_GameGroup::InitSelectSRP()
{
	m_eSelectSRP = ESelectSRP::SS_END;
	m_bSelectAck = true;
}

void CTRScissorsRockPaper_GameGroup::UpdateSelectSRP(ESelectSRP _eSelectSRP)
{
	m_eCurSelectSRP = _eSelectSRP;

	if(GetCurGameStep() != EGameStep::GS_WAIT_SELECT || m_nCurNumberOfChanges >= MAX_NUMBER_OF_CHANGES || !m_bSelectAck || m_eSelectSRP == _eSelectSRP)
	{
		return;
	}

	m_bSelectAck = false;
	m_arrayDlg[EGUIName::GN_ROUND]->setVisible(false);

	CNetClientManager::getInstance().requestGlobalRSPSelect(selectRSP(_eSelectSRP), m_nCurRound);
}

void CTRScissorsRockPaper_GameGroup::ChangeUserView_Yeono(ESelectSRP _eSelectSRP)
{
	switch (_eSelectSRP)
	{
	case CTRScissorsRockPaper_GameGroup::SS_SCISSORS:
		GUI_OBJECT::setPartGroup(&m_diceObjView, format("yeono_scissors"));
		GUI_OBJECT::setPopAnimation(&m_diceObjView, format("ready_02"));
		break;

	case CTRScissorsRockPaper_GameGroup::SS_ROCK:
		GUI_OBJECT::setPartGroup(&m_diceObjView, format("yeono_rock"));
		GUI_OBJECT::setPopAnimation(&m_diceObjView, format("ready_02"));
		break;

	case CTRScissorsRockPaper_GameGroup::SS_PAPER:
		GUI_OBJECT::setPartGroup(&m_diceObjView, format("yeono_paper"));
		GUI_OBJECT::setPopAnimation(&m_diceObjView, format("ready_02"));
		break;

	case CTRScissorsRockPaper_GameGroup::SS_END:
		break;
	}
}

bool CTRScissorsRockPaper_GameGroup::IsGameEndResult(std::tuple<int, int> _tupleResult)
{
	if(get<ERoundResult::RR_WIN>(_tupleResult) >= MAX_WIN
		|| get<ERoundResult::RR_LOSE>(_tupleResult) >= MAX_LOSE
		|| m_nUnmanipulated >= MAX_UNMANIPULATED)
	{
		return true;
	}

	return false;
}

void CTRScissorsRockPaper_GameGroup::SettingResultImage(ERoundResult _eRoundReulst)
{
	m_arrayImageCtrl[EImageCtrlName::IN_BASE_WIN]->setVisible(false);
	m_arrayImageCtrl[EImageCtrlName::IN_BASE_LOSE]->setVisible(false);
	m_arrayImageCtrl[EImageCtrlName::IN_BASE_DRAW]->setVisible(false);

	switch(_eRoundReulst)
	{
	case CTRScissorsRockPaper_GameGroup::RR_WIN:
		AddTimeFunc([](float) {}, [&](float) {PlaySoundSRP(ESoundName::SN_RPS_WIN); PlaySoundSRP(ESoundName::SN_RPS_WIN1); }, RESULT_DELAY_TIME);
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_WIN]->setAnimator(new CGUIAnimatorDelay(RESULT_DELAY_TIME));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_WIN]->pushAnimator(new CGUIAnimatorFadeIn(0.3f, true));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_WIN]->pushAnimator(new CGUIAnimatorDelay(0.5f));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_WIN]->pushAnimator(new CGUIAnimatorFadeOutHide(0.2f));
		break;

	case CTRScissorsRockPaper_GameGroup::RR_LOSE:
		AddTimeFunc([](float) {}, [&](float) {PlaySoundSRP(ESoundName::SN_RPS_LOSE); PlaySoundSRP(ESoundName::SN_RPS_FAIL1); }, RESULT_DELAY_TIME);
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_LOSE]->setAnimator(new CGUIAnimatorDelay(RESULT_DELAY_TIME));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_LOSE]->pushAnimator(new CGUIAnimatorFadeIn(0.3f, true));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_LOSE]->pushAnimator(new CGUIAnimatorDelay(0.5f));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_LOSE]->pushAnimator(new CGUIAnimatorFadeOutHide(0.2f));
		break;

	case CTRScissorsRockPaper_GameGroup::RR_DRAW:
		AddTimeFunc([](float) {}, [&](float) {PlaySoundSRP(ESoundName::SN_RPS_WIN); PlaySoundSRP(ESoundName::SN_RPS_WIN1); }, RESULT_DELAY_TIME);
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_DRAW]->setAnimator(new CGUIAnimatorDelay(RESULT_DELAY_TIME));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_DRAW]->pushAnimator(new CGUIAnimatorFadeIn(0.3f, true));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_DRAW]->pushAnimator(new CGUIAnimatorDelay(0.5f));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_DRAW]->pushAnimator(new CGUIAnimatorFadeOutHide(0.2f));
		break;
	}
}

void CTRScissorsRockPaper_GameGroup::CreateRewardDlg()
{
	m_bInGame = false;

	RewardInfo tRewardInfo;
	tRewardInfo.iRewardID = GetFinalItemIndex();
	tRewardInfo.eRewardType = eRewardCondition::eRewardCondition_ITEM;
	tRewardInfo.iRewardCount = 1;
	m_rewardDlg.showDialog(tRewardInfo, "gui/park/RockPaperScissor/RockPaperScissor_Reward.gui");

	closeDialog();

	PlaySoundSRP(ESoundName::SN_CARD_GET);
}

void CTRScissorsRockPaper_GameGroup::ShowYes()
{
	m_nCurRound -= m_nCurRound != 0 ? 1 : 0;
	CreateRewardDlg();
}

void CTRScissorsRockPaper_GameGroup::ChangeStaticText(EStaticTextName _eName, string _strText)
{
	if(m_arrayStaticText[_eName])
	{
		m_arrayStaticText[_eName]->setText(_strText);
	}
}

void CTRScissorsRockPaper_GameGroup::ChangeFormatedText(EFormatedTextName _eName, string _strText)
{
	if(m_arrayFormatedText[_eName])
	{
		m_arrayFormatedText[_eName]->setText(_strText);
	}
}

void CTRScissorsRockPaper_GameGroup::ChangeImageText(EImageTextName _eName, string _strText)
{
	if(m_arrayImageText[_eName])
	{
		std::string strPrevText = "";
		m_arrayImageText[_eName]->getText(strPrevText);
		if (strPrevText != _strText)
		{
			m_arrayImageText[_eName]->setText(_strText);
			if(_eName == EImageTextName::ITN_SELECT_TIME)
			{
				m_arrayImageText[_eName]->setAnimator(new CGUIAnimatorScale(0.2f, 2.f, 1.f));
			}
		}
	}
}

void CTRScissorsRockPaper_GameGroup::ChangeGauge(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT])
{
	for(size_t i = 0; i < m_arrayGauge.size(); i++)
	{
		switch(i)
		{
		case CTRScissorsRockPaper_GameGroup::SS_SCISSORS:
			m_arrayGauge[i].nCurNum = m_arrayGauge[i].nMovNum;
			m_arrayGauge[i].nMov = selection_count[eRSP_SELECTION::eRSP_SELECTION_S];
			m_arrayGauge[i].nMovNum = selection_count[eRSP_SELECTION::eRSP_SELECTION_S];
			break;

		case CTRScissorsRockPaper_GameGroup::SS_ROCK:
			m_arrayGauge[i].nCurNum = m_arrayGauge[i].nMovNum;
			m_arrayGauge[i].nMov = selection_count[eRSP_SELECTION::eRSP_SELECTION_R];
			m_arrayGauge[i].nMovNum = selection_count[eRSP_SELECTION::eRSP_SELECTION_R];
			break;

		case CTRScissorsRockPaper_GameGroup::SS_PAPER:
			m_arrayGauge[i].nCurNum = m_arrayGauge[i].nMovNum;
			m_arrayGauge[i].nMov = selection_count[eRSP_SELECTION::eRSP_SELECTION_P];
			m_arrayGauge[i].nMovNum = selection_count[eRSP_SELECTION::eRSP_SELECTION_P];
			break;
		}
	}

	m_arrayDlg[EGUIName::GN_BASE]->setAnimator(new CGUIAnimatorGameGroup(CHANGE_GAUGE_TIME,
		[&]()
	{
		UpdateGauge();
	}));

	for(int i = 0; i < MAX_GAUGENUM; i++)
	{
		m_arrayGauge[i].pText->setAnimator(new CGUIAnimatorIncDecText(CHANGE_GAUGE_TIME, m_arrayGauge[i].nCurNum, m_arrayGauge[i].nMovNum));
	}
}

void CTRScissorsRockPaper_GameGroup::ToggleImageText(EImageTextName _eName, bool _bOn)
{
	if(m_arrayImageText[_eName])
	{
		m_arrayImageText[_eName]->setVisible(_bOn ? true : false);
	}
}

void CTRScissorsRockPaper_GameGroup::ToggleCheckedButton(ESelectSRP _eSelectSRP, bool _bOn)
{
	get<2>(m_arrayButton[BN_BASE_SCISSORBTN1])->setChecked(false);
	get<2>(m_arrayButton[BN_BASE_ROCKBTN2])->setChecked(false);
	get<2>(m_arrayButton[BN_BASE_PAPERBTN3])->setChecked(false);

	switch(_eSelectSRP)
	{
	case CTRScissorsRockPaper_GameGroup::SS_SCISSORS:
		get<2>(m_arrayButton[BN_BASE_SCISSORBTN1])->setChecked(_bOn ? true : false);
		break;

	case CTRScissorsRockPaper_GameGroup::SS_ROCK:
		get<2>(m_arrayButton[BN_BASE_ROCKBTN2])->setChecked(_bOn ? true : false);
		break;

	case CTRScissorsRockPaper_GameGroup::SS_PAPER:
		get<2>(m_arrayButton[BN_BASE_PAPERBTN3])->setChecked(_bOn ? true : false);
		break;
	}
}

eRSP_SELECTION CTRScissorsRockPaper_GameGroup::selectRSP(ESelectSRP eRsp)
{
	switch (eRsp)
	{
	case SS_SCISSORS: return eRSP_SELECTION_S;
	case SS_ROCK: return eRSP_SELECTION_R;
	case SS_PAPER: return eRSP_SELECTION_P;
	}

	return eRSP_SELECTION_COUNT;
}

CTRScissorsRockPaper_GameGroup::ESelectSRP CTRScissorsRockPaper_GameGroup::selectSRP(eRSP_SELECTION eRsp)
{
	switch(eRsp)
	{
	case eRSP_SELECTION_R: return ESelectSRP::SS_ROCK;
	case eRSP_SELECTION_S: return ESelectSRP::SS_SCISSORS;
	case eRSP_SELECTION_P: return ESelectSRP::SS_PAPER;
	}

	return ESelectSRP::SS_END;
}

eRSP_SELECTION CTRScissorsRockPaper_GameGroup::GetIntToRSP(int _nValue)
{
	switch(_nValue)
	{
	case 0: return eRSP_SELECTION_S;
	case 1: return eRSP_SELECTION_R;
	case 2: return eRSP_SELECTION_P;
	}

	return eRSP_SELECTION_COUNT;
}

eRSP_SELECTION_RESULT CTRScissorsRockPaper_GameGroup::GetRoundResultToESR(ERoundResult _eRoundResult)
{
	switch(_eRoundResult)
	{
	case CTRScissorsRockPaper_GameGroup::RR_WIN:
		return eRSP_SELECTION_RESULT::eRSP_SELECTION_RESULT_WIN;
	case CTRScissorsRockPaper_GameGroup::RR_LOSE:
		return eRSP_SELECTION_RESULT::eRSP_SELECTION_RESULT_LOSE;
	case CTRScissorsRockPaper_GameGroup::RR_DRAW:
		return eRSP_SELECTION_RESULT::eRSP_SELECTION_RESULT_TIE;
	}

	return eRSP_SELECTION_RESULT();
}

//!< 성주신변덕 이벤트(전체 가위바위보) 시작 알림. 메세지 포함. 시작까지 남은 시간. (남은 시간이 0일때 이벤트 시작)
void CTRScissorsRockPaper_GameGroup::OnGlobalRSPStartNotify(int message_in_str_table, int left_time)
{
	if(m_arrayDlg[GN_BASE] == nullptr)
		return;

	m_arrayStaticText[EStaticTextName::STN_CHANGE_WAITINGTIME]->setText(format("%d", GetMSToSecond(left_time)));
}

//!< 입장 실패 혹은 성공
void CTRScissorsRockPaper_GameGroup::OnGlobalRSPEnterAck(eServer_GLOBAL_RSP_ENTER_ACK_TYPE ack, int base_reward, const std::vector<int>& round_rewards, int selection_limit, int time2round_start)
{
	if (m_arrayDlg[GN_BASE] == nullptr)
		return;

	m_fCurWaitTime = static_cast<float>(GetMSToSecond(time2round_start));

	switch(ack)
	{
	case eServer_GLOBAL_RSP_ENTER_ACK_OK:
		m_item_list.clear();
		std::vector<int>().swap(m_item_list);

		m_item_list.emplace_back(base_reward);
		m_item_list.insert(m_item_list.begin() + m_item_list.size(), round_rewards.begin(), round_rewards.end());

		ChangeGameStep(EGameStep::GS_WAIT_START);
		break;

	case eServer_GLOBAL_RSP_ENTER_ACK_NOT_GAME_TIME:
		break;

	case eServer_GLOBAL_RSP_ENTER_ACK_TOO_LATE:
		break;

	case eServer_GLOBAL_RSP_ENTER_ACK_DUPLICATED_ENTRANCE:
		break;
	}
}

//!< 현재 플레이중인 유저 수.  (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
void CTRScissorsRockPaper_GameGroup::OnGlobalRSPCurrentUserNotify(int delta_user, int user_in_playing)
{
	if(m_arrayDlg[GN_BASE] == nullptr || !m_bInGame)
		return;

	m_user_in_playing = user_in_playing <= 0 ? 1 : user_in_playing;
	ChangeStaticText(EStaticTextName::STN_SURVIVOR, format("%d", m_user_in_playing));
}

//!< 게임 시작 알림. 입력완료까지 남은 시간.
void CTRScissorsRockPaper_GameGroup::OnGlobalRSPGameStartNotify(int left_time_to_input, int current_state)
{
	if(m_arrayDlg[GN_BASE] == nullptr || !m_bInGame)
		return;

	m_nCurRound = current_state;
	m_left_time_to_input = left_time_to_input;

	ResetTimeFunc();
	ChangeGameStep(EGameStep::GS_WAIT_SELECT);
}

//!< 선택 성공, 실패. 현재 확정 보상 아이템 데이터 STATE
void CTRScissorsRockPaper_GameGroup::OnGlobalRSPSelectionAck(eServer_GLOBAL_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION selection, int left_selection_count, int current_reward_state)
{
	if(m_arrayDlg[GN_BASE] == nullptr || !m_bInGame)
		return;

	switch(ack)
	{
	case eServer_GLOBAL_RSP_SELECTION_ACK_OK:
		m_bSelectAck = true;
		m_nCurNumberOfChanges += 1;
		m_eSelectSRP = m_eCurSelectSRP;
		ToggleCheckedButton(m_eSelectSRP, true);
		ChangeStaticText(EStaticTextName::STN_CHANGE_WAITINGTIME, to_string(m_nCurNumberOfChanges) + " / " + to_string(MAX_NUMBER_OF_CHANGES));
		break;

	case eServer_GLOBAL_RSP_SELECTION_ACK_LIMIT_OVER:
		break;
	case eServer_GLOBAL_RSP_SELECTION_ACK_TIME_OVER:
		break;
	case eServer_GLOBAL_RSP_SELECTION_ACK_NOT_IN_GAME:
		break;
	case eServer_GLOBAL_RSP_SELECTION_ACK_NOT_GAME_TIME:
		break;
	}
}

//!< 전체 가위, 바위, 보 선택 정보. (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
void CTRScissorsRockPaper_GameGroup::OnGlobalRSPSelectionInfoNotify(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT])
{
	if(m_arrayDlg[GN_BASE] == nullptr || !m_bInGame || GetCurGameStep() != EGameStep::GS_WAIT_SELECT)
		return;

	ChangeGauge(selection_count_delta, selection_count);
}

//결과가 패배라면,  이미 아이템이 지급되어 있다.
void CTRScissorsRockPaper_GameGroup::OnGlobalRSPSelectionResultNotify(eRSP_SELECTION selection, eRSP_SELECTION_RESULT result, int current_reward_state, int current_state)
{
	if(m_arrayDlg[GN_BASE] == nullptr || !m_bInGame)
		return;

	PlaySoundSRP(ESoundName::SN_RPS_1);

	ChangeUserView_Yeono(selectSRP(selection));

	switch(result)
	{
	case eRSP_SELECTION_RESULT_WIN:
		m_eRoundResult = ERoundResult::RR_WIN;
		ChangeGameStep(EGameStep::GS_END_RESULT);
		break;

	case eRSP_SELECTION_RESULT_LOSE:
		m_eRoundResult = ERoundResult::RR_LOSE;
		ChangeGameStep(EGameStep::GS_END_RESULT);
		break;

	case eRSP_SELECTION_RESULT_TIE:
		m_eRoundResult = ERoundResult::RR_WIN;
		ChangeGameStep(EGameStep::GS_END_RESULT);
		break;

	case eRSP_SELECTION_RESULT_TIME_OVER:
		m_eRoundResult = ERoundResult::RR_LOSE;
		ChangeGameStep(EGameStep::GS_END_SELECT);
		break;
	}

	if (m_arrayImageText[EImageTextName::ITN_SELECT_TIME])
	{
		m_arrayImageText[EImageTextName::ITN_SELECT_TIME]->setVisible(false);
	}
}



