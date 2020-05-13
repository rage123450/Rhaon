#include "stdafx.h"
#include "TRScissorsRockPaper_GameAlone.h"
//
#include "gui/GUIItemImageCtrl.h"
#include "gui/GUIObjectView.h"
#include "gameui/ClientItemInfoLoader.h"
#include "language/LanguageHeader.h"
#include "park/TRGameParkUI.h"
//
#include "TRScissorsRockPaper_RewardDlg.h"

CTRScissorsRockPaper_GameAlone::CTRScissorsRockPaper_GameAlone() : m_rewardDlg(this)
{
}

CTRScissorsRockPaper_GameAlone::~CTRScissorsRockPaper_GameAlone()
{
	closeDialog();
}

bool CTRScissorsRockPaper_GameAlone::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
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

void CTRScissorsRockPaper_GameAlone::showDialog()
{
	__super::showDialog();

	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().setControlLimit(true);
		CTRGameParkUI::getInstance().setCollisionReaction(false);
	}

	m_bInGame = true;
	InitNPCMent();
	CTaskManager::getInstance().addTask(this);
	ChangeGameStep(EGameStep::GS_WAIT_START);
	get<2>(m_arrayButton[EButtonName::BN_BASE_STARTBTN])->setVisible(true);
}

void CTRScissorsRockPaper_GameAlone::closeDialog()
{
	if(m_bInGame)
	{
		m_bInGame = false;
		CNetClientManager::getInstance().requestPrivateRSPClosed();
	}

	StopSoundSRP(ESoundName::SN_END, true);

	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().setControlLimit(false);
		CTRGameParkUI::getInstance().setCollisionReaction(true);
	}

	for(auto& x : m_arrayDlg)
	{
		if(x)
		{
			x->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
			x = nullptr;
		}
	}

	m_yesNoDlg.closeDialog();

	if(m_pRewardDlg)
	{
		m_pRewardDlg->closeDialog();
	}

	CTaskManager::getInstance().removeTask(this);
}

void CTRScissorsRockPaper_GameAlone::InitName()
{
	InitGUIName({
		make_tuple<EGUIName, string>(EGUIName::GN_BASE, "gui/park/RockPaperScissor/RockPaperScissor_Base.gui"),
		make_tuple<EGUIName, string>(EGUIName::GN_ITEMDLG, "gui/park/RockPaperScissor/RockPaperScissor_ItemDlg.gui"),
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

			// RoundDlg
			"Round",
		});

	InitControlName(EControlType::CT_IMAGECONTROL,
		{
			// Base
			"Win","Lose","Draw","Time",
			// ItemDlg
			"Item1","Item2","Item3","Item4","Round1","Round2","Round3","Round4",
		});
}

void CTRScissorsRockPaper_GameAlone::InitGUI()
{
	string errmsg;

	for(int i = 0; i < EGUIName::GN_END; i++)
	{
		switch(i)
		{
		case CTRScissorsRockPaper_GameAlone::GN_BASE:
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

		case CTRScissorsRockPaper_GameAlone::GN_ITEMDLG:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_arrayDlg[EGUIName::GN_BASE]->getControlID(), m_mapGUIName[i], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->setClientPos(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_FRAME][EFrameName::FN_BASE_ITEMDLG], GUI_SUB_CONTROL_FRAME)->getClientRect());
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
			}
			break;
		
		case CTRScissorsRockPaper_GameAlone::GN_REWARD:
			break;
		
		case CTRScissorsRockPaper_GameAlone::GN_ROUND:
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

void CTRScissorsRockPaper_GameAlone::InitButton()
{
	if(m_arrayDlg[EGUIName::GN_BASE] == nullptr)
	{
		return;
	}

	for(int i = 0; i <= EButtonName::BN_BASE_PAPERBTNDIS3; i++)
	{
		get<0>(m_arrayButton[i]) = m_arrayName[EControlType::CT_BUTTON][i];
		
		switch(i)
		{
		case CTRScissorsRockPaper_GameAlone::BN_BASE_SCISSORBTN1:
			get<1>(m_arrayButton[i]) = [&]()
			{
				PlaySoundSRP(ESoundName::SN_BUTTON_CLICK);
				UpdateSelectSRP(ESelectSRP::SS_SCISSORS);
			};
			get<2>(m_arrayButton[i]) = static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_SCISSORBTN1], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;

		case CTRScissorsRockPaper_GameAlone::BN_BASE_ROCKBTN2:
			get<1>(m_arrayButton[i]) = [&]()
			{
				PlaySoundSRP(ESoundName::SN_BUTTON_CLICK);
				UpdateSelectSRP(ESelectSRP::SS_ROCK);
			};
			get<2>(m_arrayButton[i]) = static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_ROCKBTN2], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;
		
		case CTRScissorsRockPaper_GameAlone::BN_BASE_PAPERBTN3:
			get<1>(m_arrayButton[i]) = [&]()
			{
				PlaySoundSRP(ESoundName::SN_BUTTON_CLICK);
				UpdateSelectSRP(ESelectSRP::SS_PAPER);
			};
			get<2>(m_arrayButton[i]) = static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_PAPERBTN3], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;

		case CTRScissorsRockPaper_GameAlone::BN_BASE_CLOSEBTN:
			get<1>(m_arrayButton[i]) = [&]()
			{
				if(GetCurGameStep() == EGameStep::GS_WAIT_START || GetCurGameStep() == EGameStep::GS_WAIT_SELECT)
				{
					// StringTable : 소비한 정화의 돌은 돌려받을 수 없습니다.
					m_yesNoDlg.showDialog(_STR(SRP_CANT_RETURN), this, &CTRScissorsRockPaper_GameAlone::showGiveYes, nullptr);
				}
			};
			get<2>(m_arrayButton[i]) = static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_CLOSEBTN], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;

		case CTRScissorsRockPaper_GameAlone::BN_BASE_STARTBTN:
			get<1>(m_arrayButton[i]) = [&]()
			{
				PlaySoundSRP(ESoundName::SN_BUTTON_CLICK);
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

				get<2>(m_arrayButton[EButtonName::BN_BASE_STARTBTN])->setVisible(false);
				CNetClientManager::getInstance().requestPrivateRSPGameStart(0);
			};
			get<2>(m_arrayButton[i]) = static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_STARTBTN], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;
		
		case CTRScissorsRockPaper_GameAlone::BN_BASE_SCISSORBTNDIS1:
			get<1>(m_arrayButton[i]) = [&]() {};
			get<2>(m_arrayButton[i]) = static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_SCISSORBTNDIS1], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;
		
		case CTRScissorsRockPaper_GameAlone::BN_BASE_ROCKBTNDIS2:
			get<1>(m_arrayButton[i]) = [&]() {};
			get<2>(m_arrayButton[i]) = static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_ROCKBTNDIS2], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;

		case CTRScissorsRockPaper_GameAlone::BN_BASE_PAPERBTNDIS3:
			get<1>(m_arrayButton[i]) = [&]() {};
			get<2>(m_arrayButton[i]) = static_cast<CGUIImageButton*>(m_arrayDlg[EGUIName::GN_BASE]->findControl(m_arrayName[EControlType::CT_BUTTON][EButtonName::BN_BASE_PAPERBTNDIS3], GUI_SUB_CONTROL_IMAGE_BUTTON));
			break;
		}
	}
}

void CTRScissorsRockPaper_GameAlone::InitStaticText()
{
}

void CTRScissorsRockPaper_GameAlone::InitFormatedText()
{
	if(m_arrayDlg[EGUIName::GN_BASE] == nullptr)
	{
		return;
	}

	m_arrayFormatedText[EFormatedTextName::FTN_BASE_NPCMENT]
		= static_cast<CFormatedStaticText*>(m_arrayDlg[EGUIName::GN_BASE]
			->findControl(m_arrayName[EControlType::CT_FORMATEDTEXT][EFormatedTextName::FTN_BASE_NPCMENT], GUI_SUB_CONTROL_FORMATED_STATIC_TEXT));
}

void CTRScissorsRockPaper_GameAlone::InitImageControl()
{
	if(m_arrayDlg[EGUIName::GN_BASE] == nullptr)
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

void CTRScissorsRockPaper_GameAlone::InitImageText()
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

void CTRScissorsRockPaper_GameAlone::InitUserControl()
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

void CTRScissorsRockPaper_GameAlone::onFrameMove(float fElapsed)
{
	m_diceObjView.frameMove(fElapsed);
	UpdateTimeFunc(fElapsed);
}

void CTRScissorsRockPaper_GameAlone::UpdateGameStep_WaitStart()
{
	m_tupleRoundResult = make_tuple<int, int>(0, 0);
	m_nCurRound = 0;

	get<2>(m_arrayButton[BN_BASE_SCISSORBTNDIS1])->setVisible(false);
	get<2>(m_arrayButton[BN_BASE_ROCKBTNDIS2])->setVisible(false);
	get<2>(m_arrayButton[BN_BASE_PAPERBTNDIS3])->setVisible(false);

	SettingResultImage(ERoundResult::RR_END);

	m_arrayDlg[EGUIName::GN_ROUND]->setVisible(false);

	InitRoundItem();
	UpdateRoundItem();

	UpdateNPCMent(EProgressStep::PS_BASE_SCREEN);

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
		}, false);
}

void CTRScissorsRockPaper_GameAlone::UpdateGameStep_EndStart()
{
}

void CTRScissorsRockPaper_GameAlone::UpdateGameStep_WaitSelect()
{
	UpdateNPCMent(EProgressStep::PS_START_SELECTION_TIMER);

	m_arrayDlg[EGUIName::GN_ROUND]->setAnimator(new CGUIAnimatorFadeIn(0.3f, true));
	m_arrayDlg[EGUIName::GN_ROUND]->pushAnimator(new CGUIAnimatorDelay(0.5f));
	m_arrayDlg[EGUIName::GN_ROUND]->pushAnimator(new CGUIAnimatorFadeOutHide(0.3f));

	ChangeImageText(EImageTextName::ITN_ROUND_NUM, format("%d", (m_nCurRound) % 10));

	ToggleCheckedButton(ESelectSRP::SS_END, false);

	UpdateCurRoundItem();

	SettingResultImage(ERoundResult::RR_END);

	m_nUnmanipulated = 0;

	AddTimeFunc([](float) {}, [&](float) {PlaySoundSRP(ESoundName::SN_RPS_COUNT); }, 1.0f);

	m_arrayDlg[EGUIName::GN_ROUND]->pushAnimator(new CGUIAnimatorGameGroup(USER_SELECT_TIME + 0.1f,
		[]() {},
		CGUIAnimatorGameGroup::EFuncType::FT_VOID,
		[&](float _fTime)
	{
		if(GetCurGameStep() != EGameStep::GS_WAIT_SELECT)
		{
			return;
		}

		int nRemainTime = static_cast<int>(USER_SELECT_TIME - static_cast<int>(_fTime));
		if(nRemainTime <= 0)
		{
			ToggleImageText(EImageTextName::ITN_SELECT_TIME, false);
		}
		else
		{
			ChangeRoundMent(nRemainTime * 10);

			if(!m_arrayImageText[EImageTextName::ITN_SELECT_TIME]->isVisible())
			{
				m_arrayImageText[EImageTextName::ITN_SELECT_TIME]->setVisible(true);
			}
			ChangeImageText(EImageTextName::ITN_SELECT_TIME, format("%d", nRemainTime));
		}
	}));
}

void CTRScissorsRockPaper_GameAlone::UpdateGameStep_EndSelect()
{
	m_arrayDlg[GN_BASE]->setAnimator(new CGUIAnimatorGameGroup(RESULT_NEXT_STEP,
		[&]()
	{
		ChangeGameStep(EGameStep::GS_END_RESULT);
	}, CGUIAnimatorGameGroup::EFuncType::FT_VOID_END));
}

void CTRScissorsRockPaper_GameAlone::UpdateGameStep_WaitResult()
{
}

void CTRScissorsRockPaper_GameAlone::UpdateGameStep_EndResult()
{
	if(m_nUnmanipulated == -1)
	{
		UpdateNPCMent(EProgressStep::PS_SELECT_TIMER_END);
	}

	switch(m_eRoundResult)
	{
	case CTRScissorsRockPaper_GameAlone::RR_WIN:
		SettingResultImage(ERoundResult::RR_WIN);
		get<ERoundResult::RR_WIN>(m_tupleRoundResult) += 1;
		if(IsGameEndResult(m_tupleRoundResult))
		{
			UpdateCurRoundItem(MAX_WIN);

			m_arrayDlg[GN_BASE]->setAnimator(new CGUIAnimatorGameGroup(RESULT_NEXT_STEP,
				[&]()
			{
				CreateRewardDlg();
			}, CGUIAnimatorGameGroup::EFuncType::FT_VOID_END));
		}
		break;

	case CTRScissorsRockPaper_GameAlone::RR_LOSE:
		SettingResultImage(ERoundResult::RR_LOSE);
		get<ERoundResult::RR_LOSE>(m_tupleRoundResult) += 1;
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

	case CTRScissorsRockPaper_GameAlone::RR_DRAW:
		SettingResultImage(ERoundResult::RR_DRAW);
		break;
	}
}

void CTRScissorsRockPaper_GameAlone::onSendGiveMsg(std::string & nickname, std::string & strMemo, int iItemNum)
{
	m_rewardDlg.closeDialog();

	closeDialog();
}

void CTRScissorsRockPaper_GameAlone::InitRoundItem()
{
	if(m_arrayDlg[EGUIName::GN_ITEMDLG] == nullptr)
	{
		return;
	}

	for(int i = 0; i < MAX_ROUNDITEM; i++)
	{
		m_arrayRoundItem[i].m_pItemImage 
			= static_cast<CGUIItemImageCtrl*>(m_arrayDlg[EGUIName::GN_ITEMDLG]
				->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][i + IN_ITEMDLG_ITEM1], GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
		
		m_arrayRoundItem[i].m_pImage 
			= static_cast<CGUIImageCtrl*>(m_arrayDlg[EGUIName::GN_ITEMDLG]
				->findControl(m_arrayName[EControlType::CT_IMAGECONTROL][i + IN_ITEMDLG_ROUND1], GUI_SUB_CONTROL_IMAGE_CTRL));
	}
}

void CTRScissorsRockPaper_GameAlone::UpdateRoundItem()
{
	if(m_item_list.empty())
	{
		return;
	}

	for(int i = 0; i < MAX_ROUNDITEM; i++)
	{
		const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getRealItemInfo(m_item_list[i]);
		if(pItemInfo && m_arrayRoundItem[i].m_pItemImage)
			m_arrayRoundItem[i].m_pItemImage->setRealItemImage(pItemInfo);
	}
}

void CTRScissorsRockPaper_GameAlone::InitCurRoundItem()
{
	for(int i = 0; i < MAX_ROUNDITEM; i++)
	{
		m_arrayRoundItem[i].m_pImage->setVisible(false);
	}
}

void CTRScissorsRockPaper_GameAlone::UpdateCurRoundItem(int _nRound)
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

void CTRScissorsRockPaper_GameAlone::InitNPCMent()
{
	ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(0, PS_BASE_SCREEN, 0)]);
}

void CTRScissorsRockPaper_GameAlone::UpdateNPCMent(EProgressStep _eCurMent)
{
	switch(_eCurMent)
	{
	case CTRScissorsRockPaper_GameAlone::PS_BASE_SCREEN:
	// "좋아, 보상을 줄게.<br>허나, 그냥은 심심하지…<br>게임 한번 어때?"
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(0, _eCurMent, 0)]);
		break;

	case CTRScissorsRockPaper_GameAlone::PS_START_SELECTION_TIMER:
	// "가위! 바위! 보!<br>할 줄 알지?!"
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(0, _eCurMent, 0)]);
		break;

	case CTRScissorsRockPaper_GameAlone::PS_SELECT_TIMER_END:
	// "확실해?<br>그걸로 할 거야?"
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(0, _eCurMent, 0)]);
		break;

	case CTRScissorsRockPaper_GameAlone::PS_USER_NO_OPERATION:
	// "날 놀리는 건가?"
	// "뭐 하는 거야?"
	// "아아~ 오랜만에 놀 거리가<br>생기나 했는데~"
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(0, _eCurMent, m_nUnmanipulated)]);
		break;

	case CTRScissorsRockPaper_GameAlone::PS_USER_LOSE:
	// "내가 이겼네?<br>미안해서 어쩌나?"
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(0, _eCurMent, 0)]);
		break;

	case CTRScissorsRockPaper_GameAlone::PS_USER_WIN:
	// "그래…<br>이 정도는 되어야지!"
	// "으음…<br>좀 하는걸??"
	// "아~ 졌다 졌어.<br>오랜만에 재미있었어!"
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(0, _eCurMent, get<ERoundResult::RR_WIN>(m_tupleRoundResult) - 1)]);
		break;

	case CTRScissorsRockPaper_GameAlone::PS_USER_DRAW:
	// "오오!!<br>흥미진진 한 걸?!"
		ChangeFormatedText(EFormatedTextName::FTN_BASE_NPCMENT, m_mapMent[make_tuple(0, _eCurMent, 0)]);
		break;
	}
}

void CTRScissorsRockPaper_GameAlone::InitSelectSRP()
{
	m_eSelectSRP = ESelectSRP::SS_END;
}

void CTRScissorsRockPaper_GameAlone::UpdateSelectSRP(ESelectSRP _eSelectSRP)
{
	if(GetCurGameStep() != EGameStep::GS_WAIT_SELECT || !IsPlaySoundSRP(ESoundName::SN_RPS_COUNT))
	{
		return;
	}

	StopSoundSRP(ESoundName::SN_RPS_COUNT);
	m_arrayDlg[EGUIName::GN_ROUND]->setVisible(false);

	m_eSelectSRP = _eSelectSRP;
	m_nUnmanipulated = -1;

	ToggleCheckedButton(m_eSelectSRP, true);

	CNetClientManager::getInstance().requestPrivateRSPSelection(selectRSP(m_eSelectSRP), m_nCurRound);
}

void CTRScissorsRockPaper_GameAlone::ChangeUserView_Yeono(ESelectSRP _eSelectSRP)
{
	switch (_eSelectSRP)
	{
	case CTRScissorsRockPaper_GameAlone::SS_SCISSORS:
		GUI_OBJECT::setPartGroup(&m_diceObjView, format("yeono_scissors"));
		GUI_OBJECT::setPopAnimation(&m_diceObjView, format("ready_02"));
		break;

	case CTRScissorsRockPaper_GameAlone::SS_ROCK:
		GUI_OBJECT::setPartGroup(&m_diceObjView, format("yeono_rock"));
		GUI_OBJECT::setPopAnimation(&m_diceObjView, format("ready_02"));
		break;

	case CTRScissorsRockPaper_GameAlone::SS_PAPER:
		GUI_OBJECT::setPartGroup(&m_diceObjView, format("yeono_paper"));
		GUI_OBJECT::setPopAnimation(&m_diceObjView, format("ready_02"));
		break;

	case CTRScissorsRockPaper_GameAlone::SS_END:
		break;
	}
}

bool CTRScissorsRockPaper_GameAlone::IsGameEndResult(std::tuple<int, int> _tupleResult)
{
	if(get<ERoundResult::RR_WIN>(_tupleResult) >= MAX_WIN
		|| get<ERoundResult::RR_LOSE>(_tupleResult) >= MAX_LOSE
		|| m_nUnmanipulated >= MAX_UNMANIPULATED)
	{
		return true;
	}

	return false;
}

void CTRScissorsRockPaper_GameAlone::SettingResultImage(ERoundResult _eRoundReulst)
{
	m_arrayImageCtrl[EImageCtrlName::IN_BASE_WIN]->setVisible(false);
	m_arrayImageCtrl[EImageCtrlName::IN_BASE_LOSE]->setVisible(false);
	m_arrayImageCtrl[EImageCtrlName::IN_BASE_DRAW]->setVisible(false);

	switch(_eRoundReulst)
	{
	case CTRScissorsRockPaper_GameAlone::RR_WIN:
		AddTimeFunc([](float) {}, [&](float) {PlaySoundSRP(ESoundName::SN_RPS_WIN); PlaySoundSRP(ESoundName::SN_RPS_WIN1); }, RESULT_DELAY_TIME);
		AddTimeFunc([](float) {}, [&](float) {UpdateNPCMent(EProgressStep::PS_USER_WIN); }, RESULT_WAIT_TIME);
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_WIN]->setAnimator(new CGUIAnimatorDelay(RESULT_DELAY_TIME));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_WIN]->pushAnimator(new CGUIAnimatorFadeIn(0.3f, true));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_WIN]->pushAnimator(new CGUIAnimatorDelay(0.5f));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_WIN]->pushAnimator(new CGUIAnimatorFadeOutHide(0.2f));
		break;

	case CTRScissorsRockPaper_GameAlone::RR_LOSE:
		AddTimeFunc([](float) {}, [&](float) {PlaySoundSRP(ESoundName::SN_RPS_LOSE); PlaySoundSRP(ESoundName::SN_RPS_FAIL1); }, RESULT_DELAY_TIME);
		AddTimeFunc([](float) {}, [&](float) {UpdateNPCMent(EProgressStep::PS_USER_LOSE); }, RESULT_WAIT_TIME);
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_LOSE]->setAnimator(new CGUIAnimatorDelay(RESULT_DELAY_TIME));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_LOSE]->pushAnimator(new CGUIAnimatorFadeIn(0.3f, true));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_LOSE]->pushAnimator(new CGUIAnimatorDelay(0.5f));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_LOSE]->pushAnimator(new CGUIAnimatorFadeOutHide(0.2f));
		break;

	case CTRScissorsRockPaper_GameAlone::RR_DRAW:
		AddTimeFunc([](float) {}, [&](float) {PlaySoundSRP(ESoundName::SN_RPS_DRAW); PlaySoundSRP(ESoundName::SN_RPS_DRAW1); }, RESULT_DELAY_TIME);
		AddTimeFunc([](float) {}, [&](float) {UpdateNPCMent(EProgressStep::PS_USER_DRAW); }, RESULT_WAIT_TIME);
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_DRAW]->setAnimator(new CGUIAnimatorDelay(RESULT_DELAY_TIME));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_DRAW]->pushAnimator(new CGUIAnimatorFadeIn(0.3f, true));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_DRAW]->pushAnimator(new CGUIAnimatorDelay(0.5f));
		m_arrayImageCtrl[EImageCtrlName::IN_BASE_DRAW]->pushAnimator(new CGUIAnimatorFadeOutHide(0.2f));
		break;
	}
}

void CTRScissorsRockPaper_GameAlone::CreateRewardDlg()
{
	m_bInGame = false;

	PlaySoundSRP(ESoundName::SN_CARD_GET);

	RewardInfo tRewardInfo;
	tRewardInfo.iRewardID = GetFinalItemIndex();
	tRewardInfo.eRewardType = eRewardCondition::eRewardCondition_ITEM;
	tRewardInfo.iRewardCount = 1;
	m_rewardDlg.showDialog(tRewardInfo, "gui/park/RockPaperScissor/RockPaperScissor_Reward.gui");
}

void CTRScissorsRockPaper_GameAlone::showGiveYes()
{
	CNetClientManager::getInstance().requestPrivateRSPClosed();

	m_nCurRound -= m_nCurRound != 0 ? 1 : 0;
	CreateRewardDlg();
}

void CTRScissorsRockPaper_GameAlone::ChangeStaticText(EStaticTextName _eName, string _strText)
{
	if(m_arrayStaticText[_eName])
	{
		m_arrayStaticText[_eName]->setText(_strText);
	}
}

void CTRScissorsRockPaper_GameAlone::ChangeFormatedText(EFormatedTextName _eName, string _strText)
{
	if(m_arrayFormatedText[_eName])
	{
		m_arrayFormatedText[_eName]->setText(_strText);
	}
}

void CTRScissorsRockPaper_GameAlone::ChangeImageText(EImageTextName _eName, string _strText)
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

void CTRScissorsRockPaper_GameAlone::ChangeRoundMent(int _nTime)
{
	if(m_nUnmanipulated != -1)
	{
		if(28 < _nTime && _nTime <= 35)
		{
			m_nUnmanipulated = 0;
			UpdateNPCMent(EProgressStep::PS_USER_NO_OPERATION);
		}
		else if(15 < _nTime && _nTime <= 25)
		{
			m_nUnmanipulated = 1;
			UpdateNPCMent(EProgressStep::PS_USER_NO_OPERATION);
		}
		else if(5 < _nTime && _nTime <= 15)
		{
			m_nUnmanipulated = 2;
			UpdateNPCMent(EProgressStep::PS_USER_NO_OPERATION);
		}
	}
	else if(5 < _nTime && _nTime <= 15)
	{
		UpdateNPCMent(EProgressStep::PS_SELECT_TIMER_END);
	}
}

void CTRScissorsRockPaper_GameAlone::ToggleImageText(EImageTextName _eName, bool _bOn)
{
	if(m_arrayImageText[_eName])
	{
		m_arrayImageText[_eName]->setVisible(_bOn ? true : false);
	}
}

void CTRScissorsRockPaper_GameAlone::ToggleCheckedButton(ESelectSRP _eSelectSRP, bool _bOn)
{
	get<2>(m_arrayButton[BN_BASE_SCISSORBTN1])->setChecked(false);
	get<2>(m_arrayButton[BN_BASE_ROCKBTN2])->setChecked(false);
	get<2>(m_arrayButton[BN_BASE_PAPERBTN3])->setChecked(false);

	switch(_eSelectSRP)
	{
	case CTRScissorsRockPaper_GameAlone::SS_SCISSORS:
		get<2>(m_arrayButton[BN_BASE_SCISSORBTN1])->setChecked(_bOn ? true : false);
		break;

	case CTRScissorsRockPaper_GameAlone::SS_ROCK:
		get<2>(m_arrayButton[BN_BASE_ROCKBTN2])->setChecked(_bOn ? true : false);
		break;

	case CTRScissorsRockPaper_GameAlone::SS_PAPER:
		get<2>(m_arrayButton[BN_BASE_PAPERBTN3])->setChecked(_bOn ? true : false);
		break;
	}
}

CTRScissorsRockPaper_GameAlone::ESelectSRP CTRScissorsRockPaper_GameAlone::selectSRP(eRSP_SELECTION eRsp)
{
	switch (eRsp)
	{
	case eRSP_SELECTION_R: return ESelectSRP::SS_ROCK;
	case eRSP_SELECTION_S: return ESelectSRP::SS_SCISSORS;
	case eRSP_SELECTION_P: return ESelectSRP::SS_PAPER;
	}

	return ESelectSRP::SS_END;
}

eRSP_SELECTION CTRScissorsRockPaper_GameAlone::selectRSP(ESelectSRP eRsp)
{
	switch (eRsp)
	{
	case SS_SCISSORS: return eRSP_SELECTION_S;
	case SS_ROCK: return eRSP_SELECTION_R;
	case SS_PAPER: return eRSP_SELECTION_P;
	}

	return eRSP_SELECTION_COUNT;
}

//!< 입장 완료. 혹은 실패. 보상 리스트 데이터. 현재 0단계 보상 확정.
void CTRScissorsRockPaper_GameAlone::OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state)
{
	if (m_arrayDlg[GN_BASE] == nullptr)
		return;

	m_item_list.assign(begin(item_list), end(item_list));

	UpdateRoundItem();
}

//!< 현재 확정 보상 단계 데이터. 타이머 시간. 남은 단계 수.
void CTRScissorsRockPaper_GameAlone::OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state)
{
	if(m_arrayDlg[GN_BASE] == nullptr)
		return;

	m_nCurRound = current_reward_state;
	m_left_time = left_time;

	ChangeGameStep(EGameStep::GS_WAIT_SELECT);
}

//!< 승, 패, 무승부. 시간 오버. 현재 보상 단계 데이터.
void CTRScissorsRockPaper_GameAlone::OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward)
{
	if(m_arrayDlg[GN_BASE] == nullptr)
		return;

	if(m_arrayImageText[EImageTextName::ITN_SELECT_TIME])
	{
		m_arrayImageText[EImageTextName::ITN_SELECT_TIME]->setVisible(false);
	}
	
	PlaySoundSRP(ESoundName::SN_RPS_1);

	ChangeUserView_Yeono(selectSRP(server_selection));

	switch(r)
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
		m_eRoundResult = ERoundResult::RR_DRAW;
		ChangeGameStep(EGameStep::GS_END_RESULT);
		break;

	case eRSP_SELECTION_RESULT_TIME_OVER:
		m_eRoundResult = ERoundResult::RR_LOSE;
		ChangeGameStep(EGameStep::GS_END_SELECT);
		break;
	}
}
