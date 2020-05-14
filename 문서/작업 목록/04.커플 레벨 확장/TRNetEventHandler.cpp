/* ---------------------------------------------------------------
*
* Copyright 2005 by Rhaon Ent.
*
* TRNetEventHandler.cpp
*
* 2006.6.30 Pyo, Taesu.
* 
* ---------------------------------------------------------------
*/

#include "stdafx.h"

#include "LocalOptions.h"

#include "TRNetEventHandler.h"
#include "AbuseReport.h"
#include "ClientStartupWindow.h"
#include "AdvertisementManager.h"
#include "etc/SimpleErrorReport.h"
#include "findCraker/FindCracker.h"
#include "findCraker/delayFoundHackMessage.h"
#include "game/NetProxyObjectManager.h"
#include "game/GameItemManager.h"
#include "game/TRNetDataCashManager.h"
#include "game/TRRankInfoManager.h"
#include "game/TRGameGuildMatchManager.h"
#include "game/GamePeterPanGoalManager.h"
#include "game/GameTriggerManager.h"
#include "game/TRRewardManager.h"
#include "game/TRPeriodCharacterTimeoutManager.h"
#include "game/TRGameRoomChangeManager.h"
#include "game/TRStartCharacterUI.h"
#include "game/TRAssistItemManager.h"
#include "gameobj/GameGeneratorObj.h"
#include "gameobj/GameEffectObject.h"
#include "gameobj/TRQuestionManager.h"
#include "gameobj/GameActionObject.h"
#include "gameobj/TRActionObjectManager.h"
#include "gameobj/SettingGameObjectEventProcessor.h"
#include "gameui/TRFarmUI.h"
#include "gameui/TRFarmShopUI.h"
#include "gameui/TRFarmMyroomUI.h"
#include "gameui/TRPlayerPopup.h"
#include "gameui/TRLobbyLoadingUI.h"
#include "gameui/TRLobbyUI.h"
#include "gameui/TRCourtUI.h"
#include "gameui/TRRankUI.h"
#include "gameui/TRAlchemistUI.h"
#include "gameui/TRAlchemistRecipeUI.h"
#include "gameui/TRGameRoomUI.h"
#include "gameui/TRGameSportsRoomUI.h"
#include "gameui/TRGameUI.h"
#include "gameui/TRTutorialGameUI.h"
#include "gameui/TRGameGoalPhotoUI.h"
#include "gameui/TRFatalErrorUI.h"
#include "gameui/TRSystemNotice.h"
#include "gameui/TRNicknameDialog.h"
#include "gameui/TRCharacterSelectUI.h"
#include "gameui/TRTutorialUI.h"
#include "gameui/TREventFailDialog.h"
#include "gameui/TRRelayGameExitDialog.h"
#include "gameui/TRTeamplayGameExitDialog.h"
#include "gameui/GameResultCeremonyDirector.h"
#include "gameui/TRTutorialRoomUI.h"
#include "gameui/TRTrophyRoom.h"
#include "gameui/TRInviteDialog.h"
#include "gameui/ChatItemProcessor.h"
#include "gameui/TRShopGoodsListDialog.h"
#include "gameui/TRShopGiftDialog.h"
#include "gameui/TRGameRoomUIGuildMatchParty.h"
#include "gameui/TRMyRoomGiftDialog.h"
#include "gameui/TRMyRoomGoodsListDialog.h"
#include "gameui/TRGameTraceCameraUI.h"
#include "gameui/UsePetItemDlg.h"
#include "gameui/TRMyRoomDelDialog.h"
#include "gameui/TRExitDialog.h"
#include "gameui/TRItemTimeOverManager.h"
#include "gameui/TRGameOptionDialog.h"
#include "gameui/TRMiniGameGameUI.h"
#include "gameui/TRGoldMoneyDialog.h"
#include "gameui/TRChallengeSubjectManager.h"
#include "gameui/TRLuckyBagDialog.h"
#include "gameui/TRMyRoomLotteryDialog.h"
#include "gameui/TRNicknameChangeProcess.h"
#include "gameui/TRFarmShopUI.h"
#include "gameui/TRWaitLoginUI.h"
#include "gameui/TRFatigueLimitDlg.h"
#include "gameui/TRHotTimeEventManager.h"
#include "gameui/TRUserAlarm.h"
#include "gameui/TRFarmLobbyUI.h"
#include "gameui/TRFarmSignboardDlg.h"
#include "gameui/TREmblemUI.h"
#include "gameui/TREmblemManager.h"
#include "gameui/TREmblemMissionChallengeDlg.h"
#include "gameui/TRBossGameUI.h"
#include "gameui/TRLoginPromptUI.h"
#include "gameui/TRLoginPromptUI.h"
#include "gameui/TRGameInfoRecordManager.h"
#include "gameui/TRPieroOlympicRoomUI.h"
#include "gameui/TRUserBookDlg.h"
#include "gameui/TRUserBookDlg.h"
#include "gameui/TRLotteryMainDialog.h"
#include "gameui/TRHugSystemManager.h"
#include "gameui/TRTicketScrambleRoomUI.h"
#include "gameui/TRAssaultGameUI.h"
#include "gameui/TRAniAlarmDlg.h"
#include "gameui/TRAnubisRoomUI.h"
#include "gameui/TRSubDialogInterface.h"
#include "gameui/TREventChannelManager.h"
#include "gameui/TRMyKeepGoodsList.h"
#include "gameui/TRShopDlg.h"
#include "gameui/TRMyroomDlg.h"
#include "guild/TRGuildInfoDlg.h"
#include "guild/TRGuildJoinDlg.h"
#include "guild/TRGuildFarmUI.h"
#include "mission/TRGameMissionManager.h"
#include "mission/TROneDayMissionManager.h"
#include "mission/TROptionalMissionManager.h"
#include "mission/TRGameGuildMissionManager.h"
#include "netcommon/ItemAttrTable.h"
#include "park/TREventItemExchangeDlg.h"
#include "park/TRGameParkUI.h"
#include "park/TRCoupleSystem.h"
#include "park/ParkChangeManager.h"
#include "gameui/TRAnubisExpeditionManager.h"
#include "gameui/TRDungeonRaidDlg.h"
#include "gameui/EventChannel/TREventChannelFunc.h"
#include "gameui/TRInGameBonusDialog.h"

#include "gameui/TRInGameModeControlManager.h"
#include "game/TRInGameModeMsgProc.h"

#include "gameui/messenger/TRChattingDialog.h"
#include "game/UserPointForClient.h"

#include "game/etc/TROptionFileLoader.h"
#include "posteffect/PostEffectFXAA.h"
#include "posteffect/PostEffectManager.h"

#ifdef _RUNNING_MAN2
#include "gameui/TRRunningMan2RoomUI.h"
#endif

#ifdef COUNTERATTACK_OF_ANUBIS
#include "gameui/TRAnubisUIManager.h"
#include "gameui/TRAnubisManager.h"
#endif

#ifdef JOURNEY_TO_THE_WEST
#include "gameui/TRJourneyToTheWestChannelRoomCrowdUI.h"
#endif

#ifdef _CHAOS
#include "gameui/Chaos/TRChaosRoomUI.h"
#include "gameui/Chaos/TRChaosChannelDialog.h"
#endif

#ifdef _HERO_WAR
#include "gameui/HeroWar/TRHeroWarChannelDlg.h"
#include "gameui/HeroWar/TRHeroWarRoomUI.h"
#endif

#ifdef _ASSAULT_RAID
#include "gameui/AssaultRaid/TRAssaultRaidChannelDlg.h"
#endif

#ifdef COLLECTION_SYSTEM
#include "mission/TRCollectionMissionManager.h"
#endif

#ifdef _WINTER_FESTIVAL
#include "gameui/WinterFestival/TRWinterFestivalChannelDlg.h"
#include "gameui/WinterFestival/TRWinterFestivalRoomUI.h"
#endif


#ifdef _GENDER_WAR
#include "gameui/EventChannel/GenderWar/TRGenderWarRoomUI.h"
#endif

#ifdef _SNOW_QUEEN_CHANNEL
#include "gameui/EventChannel/SnowQueenChannel/TRSnowQueenRoomUI.h"
#endif

#include "system/MemoryUtil.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef XTRAP
#include "xTrap/Xtrap_C_Interface.h"
#endif

#ifdef HACKSHIELD
#include "AhnHackShield/HSFunction.h"
#endif


#ifdef LOBBY_QUEST_CHANNEL_SYSTEM
#include "quest/TRLobbyQuestManager.h"
#include "gameui/TRLobbyQuestChannelDlg.h"
#endif

#ifdef SMART_CHANNEL_SYSTEM
#include "netcommon/SmartChannelInfo.h"
#endif

#include "game/TRInGameModeProcessorImpl.h"
#include "gameui/TRPickBoardDialog.h"

#ifdef ENTRY_SYSTEM
#include "gameui/EntrySystem/TREntrySystemManager.h"
#endif

#ifdef _HORROR_PARK_CHANNEL
#include "gameui/HorrorPark/TRHorrorParkChannelDlg.h"
#include "gameui/HorrorPark/TRHorrorParkRoomUI.h"
#endif
#ifdef PROMOTION_SALE
#include "gameui/TRSalePromotionPopup.h"
#endif

#ifdef _SHU_SYSTEM_
	#include "gameui/Shu/TRShuUI_Management.h"
	#include "gameui/Shu/TRShuDlg_Management.h"
	#include "shusystem/TRGameShuSystem.h"
#endif
#include "gameobj/GameEvent.h"
#include "gameobj/GameEventSync.h"
#include "gameobj/GameEventSync_Factroy.h"

#ifdef _OFFICIAL_COMPETITION_CHANNEL
#include "gameui/CompetitionChannel/TRCompetitionChannelRoomUI.h"
#endif

#ifdef _ITEM_ONOFF
#include "netcommon/PROTOCOL/itemonoff.h"
#endif

#ifdef _SECOND_PASSWORD_
#include "gameui/TRSecondPassword.h"
#endif
#include "gameui/GameChatView.h"
#include "netcommon/PROTOCOL/game_logic_round.h"

#ifdef _EVENTPICKBOARD_
#include "gameui/EventPickBoard/TREventPickBoardUI.h"
#endif

#ifdef _CHALLENGE_MODE
#include "gameui/SingleChallenge/TRSingleChallengeManager.h"
#include "gameui/SingleChallenge/TRSingleChallengeGameUI.h"
#endif

#ifdef _TREASURE_HUNT
#include "park/TRTreasureHunt.h"
#endif

#ifdef _AUCTION_SYSTEM_
#include "gameui/AuctionSystem/TRAuctionSystemManager.h"
#endif

#ifdef _RAINBOW_LEAGUE
#include "gameui/RainbowLeague/TRRainbowLeagueManager.h"
#include "gameui/RainbowLeague/TRRainbowLeagueRoomUI.h"
#endif

#ifdef _EXCHANGE_SYSTEM

#include "gameui/TRExchangeSystemDlg.h"
#endif

#ifdef _KNIGHT_FLOWERS_
#include "gameui/KnightFlowers/TRKnightFlowersRoomUI.h"
#endif

#include "system/ScreenResolutionSettings.h"
#include "gameui/TRItemDetailViewManager.h"

// GUILD_SKILL_TREE
#include "guild/TRGuild_SkillManager.h"
// 길드매치 recv interface
#include "gameui/GuildMatchRecvInterface.h"

#ifdef _SHOP_RENEWAL_
#include "gameui/Shop/TRShopManager.h"
#include "gameui/Shop/TRShopRenewalUI.h"
#endif

#ifdef _ITEM_CUBE
#include "gameui/TRItemCubeDlg.h"
#endif
#ifdef _USER_REPORT_SYSTEM
#include "gameui/UserReport/TRUserReportDlg.h"
#include "gameui/UserReport/TRUserTrialRoomUI.h"
#endif

#include "gameui/Salon/TRSalonManager.h"

#ifdef _CHAOS_ZERO_
#include "gameui/ChaosZero/TRChaosZeroChannelDlg.h"
#include "gameui/ChaosZero/TRChaosZeroRoomUI.h"
#endif
#ifdef _TR_KNIGHTAGE_
#include "gameui/TRKnights/TRKnightageManager.h"
#endif

#ifdef _NEWBIE_RETURNER_
#include "mission/TRNewbieReturnerMissionManager.h"
#endif

#ifdef _FISHING_
#include "gameui/Fishing/TRFishingSystemManager.h"
#endif

#ifdef _DEV_FESTIVAL_
#include "gameui/DevFestival/TRDevFestivalChannelDlg.h"
#include "gameui/DevFestival/TRDevFestivalRoomUI.h"
#endif
#ifdef _FASHION_COORDI_KING_
#include "gameui/FashionCoordiKing/TRFashionCoordiKingManager.h"
#endif
#ifdef _TALES_ACADEMY_
#include "gameui/TalesAcademy/TRTalesAcademyRoomUI.h"
#include "gameui/TalesAcademy/TRTalesAcademyChannelDlg.h"
#endif
#ifdef _COMBINATION_SHOP_
#include "gameui/CombinationShop/TRCombinationShopManager.h"
#endif

#ifdef _TALES_TALK_RUEGO
#include "mission/TRTalesTalkRuegoManager.h"
#endif

#ifdef _HUMONG_PICKBOARD_
#include "gameui/PaperPickBoard/TRPaperPickBoardDialog.h"
#endif

#ifdef _RUNLYMPIC
#include "gameui/Runlympic/TRRunlympicDlg.h"
#include "gameui/Runlympic/TRRunlympicRoomUI.h"
#endif

#ifdef _TUTORIAL_CHANNEL_
#include "gameui/TutorialRenewal/TRChannelTutorialUI.h"
#endif

#ifdef _TALES_MARBLE_
#include "gameui/DiceBoard/TRDiceBoardManager.h"
#endif

#ifdef _ARCHIVES_
#include "gameui/Archives/TRArchivesDlg.h"
#include "gameui/Archives/TRStoryBookDlg.h"
#include "gameui/Archives/TRArtifactDlg.h"
#endif

#ifdef _TALES_FRONTIER_
#include "gameui/TalesFrontier/TRTalesFrontierChannelDlg.h"
#include "gameui/TalesFrontier/TRTalesFrontierRoomUI.h"
#endif

#include "gameui/EventChannel/TREventChannelUserNumInfo.h"
#include "gameui/EventChannel/TREventChannelSelectModeDlg.h"

#ifdef _TOWER_OF_ORDEAL_
#include "park/TRParkTowerOfOrdealManager.h"
#endif

#ifdef _THANK_OFFERING_
#include "gameui/ThankOffering/TRThankOfferingChannelDlg.h"
#include "gameui/ThankOffering/TRThankOfferingRoomUI.h"
#endif

#ifdef _WINTER_CHANNEL_2019_
#include "gameui/EventChannel/WinterChannel2019/TRWinterChannel2019RoomUI.h"
#endif

#ifdef _SPRING_CHANNEL_2020_
#include "gameui/EventChannel/SpringChannel2020/TRSpringChannel2020RoomUI.h"
#endif

#include "stove/StoveRogTranslator.h"

//////////////////////////////////////////////////////////////////////////

#ifdef XIGNCODE
#include "xigncode/XigncodeClient.h"
#endif

//////////////////////////////////////////////////////////////////////////

CTRNetEventHandler::CTRNetEventHandler()
{
	m_pNetPlay = NULL;
	m_pNetEventListener = NULL;
	m_pGameRoomUI = NULL;
	m_bRecvLevelUPAck = false;

	CTRGameResultUIRegister::registerGameResultUI();
}

//////////////////////////////////////////////////////////////////////////
// 네트워크 관련 이벤트--------------------------------------

/// 서버로 부터 설정 정보를 얻었다.
void CTRNetEventHandler::onRecvServerSettingInfo()
{
	CTRUserInterface::getInstance().onRecvServerSettingInfo();

	DBG_OUTPUT(60, "onRecvServerSettingInfo");
}

/// 서버의 설정 정보가 바뀌었다.
void CTRNetEventHandler::onRecvServerSettingInfoChanged()
{
	DBG_OUTPUT(60, "onRecvServerSettingInfoChanged");
	CAdvertisementManager::getInstance().onRecvServerSettingInfoChanged();
	CTRUserInterface::getInstance().onRecvServerSettingInfoChanged();
#ifdef _RAINBOW_LEAGUE
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvServerSettingInfoChanged();
#endif

#ifdef _PARK_DROP_BOX_EVENT_
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().setDropBoxEventState();
	}
#endif
}

/// 서버로 부터 인증 결과.
void CTRNetEventHandler::onRecvLoginAuth(eServerResult eResult, const std::string& strMyID)
{
	DBG_OUTPUT(60, "onRecvLoginAuth(%d, %s)", eResult, strMyID.c_str());

	if(m_pNetPlay)
	{
		m_pNetPlay->onRecvLoginAuth();
	}

	if (m_pNetEventListener)
	{
		if (m_pNetEventListener->onRecvLoginAuth(eResult, strMyID))
		{
			return;
		}
	}

	if (eServerResult_OK_ACK != eResult)
	{
		// 인증 실패.
		CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), _STR(ERR_AUTHENTICATION_FAILED), true);
	}
}

//! 접속 여부를 알린다.
void CTRNetEventHandler::LoadBalance_Connect(eLoadBalanceProtocolResult eResult)
{
	CClientStartupWindow::getInstance().onLoadBalanceServerConnected(eResult);
}

//! 서버로 부터 접속이 끊겼다.
void CTRNetEventHandler::LoadBalance_Disconnect()
{
	CClientStartupWindow::getInstance().onLoadBalanceServerDisconnected();
}

//! 유저가 가장 작게 들어있는 서버의 주소와 포트를 얻는다.
void CTRNetEventHandler::LoadBalance_Login( const std::string & serverIP, const int & nPort, bool bHash)
{
	CClientStartupWindow::getInstance().onLoadBalanceServerLoginResult(serverIP, nPort, bHash);
}


/// 아이템 메세지를 성공적으로 받았다.
void CTRNetEventHandler::onRecvGetItemMsgOK(std::vector<ItemMsgInfo>& vecItemMsgInfo)
{
	CTRItemTimeOverManager::getInstance().onRecvGetItemMsgOK(vecItemMsgInfo);
	CTRUserInterface::getInstance().onRecvGetItemMsgOK(vecItemMsgInfo);
}

/// 선물 아이템 메세지를 성공적으로 받았다.
void CTRNetEventHandler::onRecvGetGiftItemMsgOK(std::vector<ItemMsgInfo>& vecItemMsgInfo)
{
	CTRItemTimeOverManager::getInstance().onRecvGetGiftItemMsgOK(vecItemMsgInfo);
}

/// 임시보관함 아이템 메세지를 성공적으로 받았다.
void CTRNetEventHandler::onRecvGetOutboxItemMsgOK(std::vector<ItemMsgInfo>& vecItemMsgInfo)
{
	CTRItemTimeOverManager::getInstance().onRecvGetOutboxItemMsgOK(vecItemMsgInfo);
}

/// 아이템 메세지를 받는데 실패하였다.
void CTRNetEventHandler::onRecvGetItemMsgFailed()
{

}

/// 클라이언트 해쉬값이 동일한지 체크한 결과를 얻었다.
void CTRNetEventHandler::onRecvClientHashCheck(eClientHashCheck eResult)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvClientHashCheck");
#ifdef TR_RELEASE_PROJECT
	CClientStartupWindow::getInstance().onRecvClientHashCheck(eResult);
#endif

}

/// 서버의 시간을 받았다.
void CTRNetEventHandler::onRecvServerTime(const time_type & serverTime, bool bCheckTime)
{	
	string timeString;	
	CCurrentTime::formatSimple(serverTime, timeString);
	DBG_OUTPUT(60, "onRecvServerTime: %s", timeString.c_str());
	CServerTime::getInstance().onRecvServerTime(serverTime);
	CTRLobbyUI::getInstance().onRecvServerTime(serverTime, bCheckTime);

#ifdef _GAME_OPTION_
	CNetClientManager::getInstance().requestUserGameOption();
#endif
#ifdef _SECOND_PASSWORD_
	CTRSecondPassword::getInstance().setCertifyType(CNetClientManager::getInstance().getCertifyTyp());
#endif

	CNetClientManager::getInstance().requestCashBalance();

#ifdef _AUCTION_SYSTEM_
	Auction_System::CTRAuctionSystemManager::getInstance().requestAuctionSchedule();
#endif
}

/// 나는 해킹 의심 유저다.
void CTRNetEventHandler::onRecvHackingTime(const time_type& hackingTime )
{
	if (hackingTime == 0) return;

	CTRUserInterface & userInterface = CTRUserInterface::getInstance();
	CGUIDialog * dialog = userInterface.loadGUI(userInterface.getCurrentUI()->getRootGUIControlID(),"gui/HackAlarmPopup.gui");

	if (dialog != NULL)
	{
		dialog->centerScreenPosition();
		dialog->setZOrder(-15.f);
		dialog->pushAnimator(new  CGUIAnimatorFadeIn(0.5f, true));
		dialog->pushAnimator(new  CGUIAnimatorDelay(20.f));
		dialog->pushAnimator(new  CGUIAnimatorFadeOutRemove(0.5f));
	}
}

// 로그인 실패...
void CTRNetEventHandler::onRecvLoginFail(eServerResult eError , BYTE byDetail)
{
	DBG_OUTPUT(60, "onRecvLoginFail: %d,%d", eError,byDetail);

	if (m_pNetEventListener)
	{
		if (m_pNetEventListener->onRecvLoginFail(eError, byDetail))
		{
			return;
		}
	}

	switch(eError)
	{
	case eServerResult_NOTIFY_NEW_CLIENT_FAILED_LOGIN: // 인증 실패.
		CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), _STR(ERR_AUTHENTICATION_FAILED));
		break;
	case eServerResult_NOTIFY_NEW_CLIENT_FAILED_HASH_MISS_MATCH_ACK: // 해시값 틀림.
		CSimpleErrorReport::reportErrorFileList("", "hash", "hash failed!");
		CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), _STR(ERR_INVALID_CLIENT_VERSION));
		break;
	case eServerResult_LOGIN_FAILED_SERVER_NOT_READY_ACK: // 서버가 점검 중인 상태 혹은 hash 가 0 인 상태이다.
		CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), _STR(ERR_SERVER_NOT_READY));
		break;
	case eServerResult_LOGIN_FAILED_DUPLICATE_ID:
		CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), _STR(ERR_DUPLICATE_USER_ID));
		break;
	case eServerResult_LOGIN_FAILED_MISS_MATCH_PROTOCOL_VERSION_ACK:
		CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), _STR(ERR_PROTOCOL_MISMATCH));
		break;
	case eServerResult_LOGIN_FAILED_SERVER_FULL_ACK:
		CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), _STR(ERR_SERVER_FULL));
		break;

	default:
		{
			switch(byDetail)
			{
			case eLoginFail_BLACK_LIST:
				CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), _STR(ERR_BLOCK_ID));
				break;
			case eLoginFail_INVALID_COUNTRY:
				CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), "INVALID COUNTRY");
				break;
			case eLoginFail_BAD_NUMBER_FOR_PREVENT_ABUSING:
				CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), _STR(ERR_BLOCK_BAD_NUMBER_FOR_PREVENT_ABUSING));

				break;
			default:
				CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), format("error code: %d-%d", eError, byDetail));
				break;
			}

			_ASSERTE(false);

		}

		break;
	}
}

void CTRNetEventHandler::onRecvLoginFailByBlock( int iBlockReason, time_type tBlockStartTime, time_type tBlockEndTime )
{
	const time_type blockTime = ((tBlockEndTime - tBlockStartTime) / 1000) / 60;	//!< 분단위

	if(blockTime >= 60 * 24 * 365 * 2)	//!> 2년 이상
	{
		CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), _STR(ERR_LOGIN_BLOCK_USER));
	}
	else
	{
		CTRFatalErrorUI::showScreen(_STR(ERR_LOGIN_FAILED), format(_STR(ERR_LOGIN_TRY_HACKING_BLOCK), max(blockTime, 1)));
	}

	TRDBG_OUTPUT_ERROR("%s iBlockReason[%d], tBlockStartTime[%I64d], tBlockEndTime[%I64d]", __FUNCTION__, iBlockReason, tBlockStartTime, tBlockEndTime);
}

/// 샨다 로그인 성공. 
void CTRNetEventHandler::onRecvSnDALoginOK(void)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvSnDALoginOK");
}

/// 샨다 로그인 정보 부족으로 실패.. 추가요청 필요. 
void CTRNetEventHandler::onRecvSnDALoginNotEnoughInfoFailed(const eServerResult& failedReason, const std::string& addtionInfo)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvSnDALoginNotEnoughInfoFailed failedReason = %d",failedReason);

	//CSNDAPasswordProtectorDlg::getInstance().onRecvSnDALoginNotEnoughInfoFailed(failedReason, addtionInfo);
	if(m_pNetEventListener)
		m_pNetEventListener->onRecvSnDALoginNotEnoughInfoFailed(failedReason, addtionInfo);
}

/// 
void CTRNetEventHandler::onRecvSnDALoginFailed(void)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvSnDALoginFailed");
}

/// 추가된 해킹툴 해쉬값을 받았다.
void CTRNetEventHandler::onRecvAddHackingToolHack(const std::vector<std::string>& vecHackingToolHash, const std::vector<std::string>& vecAllowingHackingToolHash)
{
	CFindCracker::getInstance().onRecvAddHackingToolHack(vecHackingToolHash, vecAllowingHackingToolHash);
}

/// 길드명을 받았다.
void CTRNetEventHandler::onRecvGetGuildName(const std::string& strGuildName, const std::string & strGuildMarkURL)
{
	// 길드명을 받는다. 
}

/// 레더정보를받았다.
void CTRNetEventHandler::onRecvGetLadderInfo(const int & iLadderPoint, const int & iLadderRank)
{
	CTRLobbyUI::getInstance().onRecvGetLadderInfo(iLadderPoint, iLadderRank);
	CTRGameSportsRoomUI::getInstance().onRecvGetLadderInfo(iLadderPoint, iLadderRank);
}

/// PC방 관련 아이템을 받았다.
void CTRNetEventHandler::onRecvGetPCRoomItem(const std::set<int> & setPCRoomItem)
{
	CKeepItemList::getInstance().insertPCRoomItem(setPCRoomItem);
}

/// PC방 타입이 변경되었다.
void CTRNetEventHandler::onRecvGetPCRoomRivalType()
{
	m_pNetPlay->onRecvGetPCRoomRivalType();
}

/// 하루한번 리셋해야한다.(인맥시스템외)
void CTRNetEventHandler::onRecvGetResetNotify()
{
#ifdef _PERSONAL_CONNECTIONS
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->onRecvGetResetNotify();
#endif
}

/// 멤버십 관련 아이템을 받았다.
void CTRNetEventHandler::onRecvGetMembershipItem(const std::vector<int> & vecMembershipItem)
{
	CKeepItemList::getInstance().insertMembershipItem(vecMembershipItem);
	CTRMyRoomGoodsListDialog::getInstance().onUpdateGoodsList();
}

/// 멤버십 관련 아이템을 지우라는 요청을 받았다.
void CTRNetEventHandler::onRecvRemoveMembershipItem(const std::vector<int> & vecMembershipItem)
{
	CKeepItemList::getInstance().deleteMembershipItem(vecMembershipItem);
	CTRMyRoomGoodsListDialog::getInstance().onUpdateGoodsList();
}

/// 펫 업그레이드를 성공했다.
void CTRNetEventHandler::onRecvMyRoomPetUpgradeOK()
{
	CUseItemDlg::getInstance().onRecvMyRoomPetUpgradeOK();
}

/// 펫 업그레이드를 실패했다.
void CTRNetEventHandler::onRecvMyRoomPetUpgradeFailed(eMyRoomProtocol_PET_UPGRADE_FAILED_REASON failedReason)
{
	CUseItemDlg::getInstance().onRecvMyRoomPetUpgradeFailed(failedReason);
}

/// 아이템을 지우는데 성공했다.
void CTRNetEventHandler::onRecvMyRoomDeleteItemOK(const int iDeleteItemItemDescNum)
{
	if( !CKeepItemList::getInstance().eraseItem(iDeleteItemItemDescNum))
	{
		DBG_OUTPUT("CTRNetEventHandler::onRecvMyRoomDeleteItemFaild=[%d]",iDeleteItemItemDescNum);
		// 아이템 삭제 실패시 목록을 다시 읽어온다.
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iDeleteItemItemDescNum);
	}

	if(CTRMyRoomDelDialog::getInstance().isVisible()) CTRMyRoomDelDialog::getInstance().onRecvMyRoomDeleteItemOK();
}

/// 아이템을 지우는데 실패했다.
void CTRNetEventHandler::onRecvMyRoomDeleteItemFailed(eDeleteItemFailedReason failedReason)
{
	CTRMyRoomDelDialog::getInstance().onRecvMyRoomDeleteItemFailed(failedReason);
}

/// 나의 탑승동물 아바타를 얻어오는데 성공했다.
void CTRNetEventHandler::onRecvMyRoomGetAnimalAvatarOK(AnimalRacingAnimalAvatar & animalRacingAvatar)
{
	CNetClientManager::getInstance().requestItemMsg();
	CTRShopDlg::getInstance().onRecvMyRoomGetAnimalAvatarOK(animalRacingAvatar);
	CTRMyroomDlg::getInstance().onRecvMyRoomGetAnimalAvatarOK(animalRacingAvatar);
}

/// 나의 탑승동물 아바타를 얻어오는데 실패했다.
void CTRNetEventHandler::onRecvMyRoomGetAnimalAvatarFailed()
{
	CTRShopDlg::getInstance().onRecvMyRoomGetAnimalAvatarFailed();
	CTRMyroomDlg::getInstance().onRecvMyRoomGetAnimalAvatarFailed();
}

/// 마이룸에서 탑승동물 아바타 설정을 저장하는 데 성공했다.
void CTRNetEventHandler::onRecvMyRoomSetAnimalRacingAvatarInfoSettingOK(AnimalRacingAnimalAvatar & animalRacingAvatar)
{
	DBG_OUTPUT("onRecvMyRoomSetAnimalRacingAvatarInfoSettingOK");
	CTRNetPlayManager::getInstance().setAnimalAvatarInfo(animalRacingAvatar);
	CTRMyroomDlg::getInstance().onRecvMyRoomSetAnimalRacingAvatarInfoSettingOK(animalRacingAvatar);
}

/// 마이룸에서 탑승동물 아바타 설정을 저장하는 데 실패했다.
void CTRNetEventHandler::onRecvMyRoomSetAnimalRacingAvatarInfoSettingFailed(int nReason)
{
	DBG_OUTPUT("onRecvMyRoomSetAnimalRacingAvatarInfoSettingFailed %d", nReason);
	CTRMyroomDlg::getInstance().onRecvMyRoomSetAnimalRacingAvatarInfoSettingFailed(nReason);
}

/// 마이룸에서 탑승동물 먹이주는데 성공했다.
void CTRNetEventHandler::onRecvMyRoomAnimalRacingFeedAnimalOK(int nTargetAnimalDescNum, int nFeedItemDescNum)
{
	DBG_OUTPUT("onRecvMyRoomAnimalRacingFeedAniamlOK");
	CUseItemDlg::getInstance().onRecvMyRoomUseAnimalFeedOK(nTargetAnimalDescNum, nFeedItemDescNum);
}

/// 마이룸에서 탑승동물 먹이주는데 실패했다.
void CTRNetEventHandler::onRecvMyRoomAnimalRacingFeedAnimalFailed(byte nReason)
{	
	DBG_OUTPUT("onRecvMyRoomAnimalRacingFeedAniamlFailed");
	CUseItemDlg::getInstance().onRecvMyRoomAnimalRacingFeedFailed(nReason);
}

/// 이 방의 유저들의 경험치를 받았다.
void CTRNetEventHandler::onRecvRoomExpOfUsers(const std::map < BYTE, exp_type > indexToExp)
{
	CTRNetPlayManager::getInstance().onRecvRoomExpOfUsers(indexToExp);
}

/// 게임이 끝나고 보너스를 받았다.
void CTRNetEventHandler::onRecvEndGameBonus(eEndGameBonus eType, BYTE byBoardNum)
{
	CGameManager::getInstance().onRecvEndGameBonus(eType, byBoardNum);
}

/// 나의 카드 및 레시피 목록들을 얻었다.
void CTRNetEventHandler::onRecvMyCardRecipeKeepList(const std::vector< CardRecipeKeepInfo > & keepList, bool bReplace)
{
	CKeepAlchemistItemList::getInstance().onRecvMyCardRecipeKeepList(keepList,bReplace);

#ifdef _EXCHANGE_SYSTEM
	if (CTRLobbyUI::getInstance().isActive()) {
		CTRLobbyUI::getInstance().updateExchangeList();
	}

#ifdef _ARCHIVES_
	if (ARCHIVES::CTRArchivesDlg::getInstance().isVisible()) ARCHIVES::CTRArchivesDlg::getInstance().updateExchangeList();
#endif
#endif
}

/// 나의 카드 및 레시피 목록들을 얻는데 실패했다.
void CTRNetEventHandler::onRecvMyCardRecipeFailed()
{
	CTRShortTimeMessage::showMessage(_STR(GET_MY_CARD_FAILED), 1.5f);
}

/// 수리 아이템을 쓰는데 성공했다.
void CTRNetEventHandler::onRecvMyRoomUseRepairItemOK(const int iTargetItemDescNum, const int iRepairItemdDescNum)
{
	CUseItemDlg::getInstance().onRecvMyRoomUseRepairItemOK(iTargetItemDescNum, iRepairItemdDescNum);
	CTRAlchemistUI::getInstance().onRecvMyRoomUseRepairItemOK(iTargetItemDescNum);

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_USE_ITEM, iRepairItemdDescNum);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_USE_ITEM_COUNT);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 수리 아이템을 쓰는데 실패했다.
void CTRNetEventHandler::onRecvMyRoomUseRepairItemFailed(eMyRoomProtocol_USE_REPAIR_ITEM_FAILED_REASON failedReason,const int iTargetItemDescNum, const int iRepairItemDescNum)
{
	CUseItemDlg::getInstance().onRecvMyRoomUseRepairItemFailed(failedReason, iTargetItemDescNum, iRepairItemDescNum);
}

/// 친구 확장권 아이템 사용를 성공했다.
void CTRNetEventHandler::onRecvMyRoomUseAddFriendOK(const int iItemDescNum, const int iFriendAddCount)
{	
	int iAddFriendExpand = CTRMessengerMainUI::FRIEND_MAX_INDEX + iFriendAddCount;

	COkDialogEx::getInstance().showDialog(format(_STR(MESSAGE_SYMTEM_FRIEND_REGISTER_COUNT_INCREASED_BY_FRIEND_EXPAND_ITEM), iAddFriendExpand));

	CTRMessengerMainUI::getInstance().update(true);

	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iItemDescNum);
}

/// 친구 확장권 아이템 사용를 실패했다.
void CTRNetEventHandler::onRecvMyRoomUseAddFriendFailed(eMyRoomProtocol_ADDFRIEND_FAILED_REASON failedReason)
{
	string msg = "";
	switch(failedReason)
	{
	case eMyRoomProtocol_ADDFRIEND_FAILED_REASON_DB_ERROR:	///< DB 에러이다.
		msg = _STR(FAILED_DB_ERROR);
		break;

	case eMyRoomProtocol_ADDFRIEND_FAILED_REASON_ENOUGHT_ADDFRIEND_ITEM:	///< 메신저에 늘릴 수 있는 친구 수가  가득 차 실패. 
		msg = _STR(MESSAGE_SYMTEM_CANNOT_INCREASE_FRIEND_REGISTER_COUNT);
		break;

	case eMyRoomProtocol_ADDFRIEND_FAILED_REASON_NO_ITEM:	///< 아이템이 없다.
		msg = _STR(MSG_FARM_HARVEST_CHARGE_FAILE_NOT_HAS_ITEM);
		break;
	}

	COkDialogEx::getInstance().showDialog(msg);
	TRDBG_OUTPUT_ERROR("%s - %s (%d)", __FUNCTION__, msg.c_str(), failedReason);
}

/// 펫 먹이 아이템을 쓰는데 성공했다.
void CTRNetEventHandler::onRecvMyRoomUsePetFeedOK(const int iTargetPetDescNum, const int iFeedItemDescNum)
{
	CUseItemDlg::getInstance().onRecvMyRoomUsePetFeedOK(iTargetPetDescNum, iFeedItemDescNum);
}

/// 펫 먹이 아이템을 쓰는데 실패했다.
void CTRNetEventHandler::onRecvMyRoomUsePetFeedFailed(eMyRoomProtocol_USE_PET_FEED_FAILED_REASON failedReason)
{
	CUseItemDlg::getInstance().onRecvMyRoomUsePetFeedFailed(failedReason);
}

/// 펫 부활 아이템을 쓰는데 성공했다.
void CTRNetEventHandler::onRecvMyRoomUsePetRebirthOK(const std::vector<int> petItemNumList, int iPetRebirthItemNum)
{
	if(petItemNumList.empty()) return;	

	string strMsg;

	if(petItemNumList.size() > 1)
	{
		strMsg = _STR(MSG_PET_ITEM_USE_ALL_PET_REBIRTH_OK);

	}
	else if(petItemNumList.size() == 1)
	{
		int iPetItemDescNum = petItemNumList[0];
		const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getItemInfo(iPetItemDescNum);
		if(pItemInfo)
		{
			strMsg = format(_STR(MSG_PET_ITEM_USE_REBIRTH_OK) ,pItemInfo->m_name.c_str());
		}
	}

	if(!strMsg.empty()) COkDialogEx::getInstance().showDialog(strMsg);

	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNumList(petItemNumList);
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iPetRebirthItemNum);

	CUseItemDlg::getInstance().onRecvMyRoomUsePetRebirthOK(petItemNumList, iPetRebirthItemNum);
}

/// 펫 부활 아이템을 쓰는데 실패했다.
void CTRNetEventHandler::onRecvMyRoomUsePetRebirthFailed(const int iTargetPetItemDescNum,eMyRoomProtocol_USE_PET_REBIRH_FAILED_REASON failedReason)
{
	CUseItemDlg::getInstance().onRecvMyRoomUsePetRebirthFailed(iTargetPetItemDescNum, failedReason);
}

/// 서버와 완전한 연결을 이루었다(TCP 연결 및 UDP 교환도 이루어졌다)
void CTRNetEventHandler::onCompleteFullConnection()
{
	DBG_OUTPUT(60, "onCompleteFullConnection");

	CTRLobbyLoadingUI::getInstance().onCompleteFullConnection();
	CTRWaitLoginUI::getInstance().onCompleteFullConnection();

	CStoveRogTranslator::getInstance().sendLog_Stove(eStove_Log_Category_Client_Exec);

#ifdef XTRAP
	std::string strID       = CNetClientManager::getInstance().getMyUserID();
	std::string strNick     = CNetClientManager::getInstance().getMyNickname();
	std::string strServerIP = CNetClientManager::getInstance().getServerIP();

	XTrap_C_SetUserInfoEx(strID.c_str(),strServerIP.c_str(), strNick.c_str(), "", (DWORD)0, NULL);
#endif
}

void CTRNetEventHandler::onRecvEnterNickname()
{
	CTRNicknameDialog::getInstance().onRecvEnterNickname();
}


/// 닉네임이 잘 입력되었다.
void CTRNetEventHandler::onRecvEnterMyNicknameOK()
{
	CTRNicknameDialog::getInstance().onRecvEnterMyNicknameOK();
}


/// 사용가능한 닉네임인지를 체크하는 결과가 왔다.
void CTRNetEventHandler::onRecvCheckNicknameResult(const std::string & strNickname, eServerResult result)
{
	CTRNameChangeManager::getInstance().onRecvCheckNicknameResult(strNickname, result);
}

/// 넣을 수 없는 닉네임이었다.
void CTRNetEventHandler::onRecvEnterMyNicknameFailed(const DWORD & dwResult)
{
	CTRNicknameDialog::getInstance().onRecvEnterMyNicknameFailed(dwResult);
};

/// 닉네임이 변경되었다.
void CTRNetEventHandler::onRecvChangeMyNicknameOK()
{
	CTRNameChangeManager::getInstance().onRecvChangeMyNicknameOK();
	//CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(GAME_CHARACTER_NONE, eFuncItemPosition_CHANGE_NICKNAME);
}

/// 닉네임 변경에 실패했다.
void CTRNetEventHandler::onRecvChangeMyNicknameFailed(const DWORD & dwResult)
{
	if(dwResult == eServerResult_NICKNAME_CHANGE_FAILED_DUPLICATE_USER_ACK)
	{
		// 이미 닉네임 변경 요청을 한 유저이다.
		CTRShortTimeMessage::showMessage(_STR(FAILED_NICKNAME_CHANGE_DUPLICATE_REQUEST));
	}
	else
	{
		// 알수 없는 이유로 닉네임 변경을 실패하였습니다.
		CTRShortTimeMessage::showMessage(_STR(FAILED_NICKNAME_CHANGE));
		DBG_OUTPUT("CTRNetEventHandler::onRecvChangeMyNicknameFailed() result = %d", dwResult);
		_ASSERTE(false);
	}	
}

/// 나의 닉네임을 받았다.
void CTRNetEventHandler::onRecvMyNickname(const std::string & strNickname)
{
	CTRNicknameDialog::getInstance().onRecvMyNickname(strNickname);
};

/// 특정 유저의 닉네임을 받았다.
void CTRNetEventHandler::onRecvGetUserNickname(const int iUserNum, const std::string &strNickname)
{
	CTRNetDataCashManager::getInstance().onCashUserNickname(iUserNum,strNickname);
}

/// 특정 유저의 닉네임을 가져오기를 실패했다.
void CTRNetEventHandler::onRecvGetUserNicknameFailed(const eServer_GET_USER_NICKNAME_FAILED_REASON eFailedReason)
{
	DBG_DEMO_OUTPUT("%s(line: %d) eFailedReason: %d",__FUNCTION__,__LINE__,eFailedReason);
}

/// 경험치를 새로 받았다.
void CTRNetEventHandler::onRecvExp(eLevelUPKind levelKind, const exp_type iExp)
{
	if (levelKind == eLevelUPKind_RUN)
	{
		CTRUserInterface::getInstance().onRecvUserExp(levelKind);
	}
	else if (eLevelUPKind_FARM == levelKind && CTRFarmUI::getInstance().isActive())
	{
		CTRFarmUI::getInstance().getFarmSkillExpDlg().setExp(CNetClientManager::getInstance().getMyFarmInfo().m_iFarmExp);
	}

	if (m_bRecvLevelUPAck)
	{
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_USER_LEVEL);
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();
		CTRQuestManager::getInstance().inspectTriggerQuestFromUpperLevel(false, CNetClientManager::getInstance().getMyLevel());
		m_bRecvLevelUPAck = false;
	}
}

/// 서버의 시스템 시간을 받았다.
void CTRNetEventHandler::onRecvServerSystemTime(time_type tServerTime)
{
	CTRHotTimeEventManager::getinstance().onRecveHotTimeServerTimeCheck(tServerTime);
	CServerTime::getInstance().onRecvServerTime(tServerTime);
}

/// XTrap 인증 패킷을 받았다.
void CTRNetEventHandler::onRecvXTrapCSPacket(char * data, size_t size)
{
#ifdef XTRAP
	char sendData[200];
	DWORD dwResult = XTrap_CS_Step2(data, sendData, XTRAP_PROTECT_PE|XTRAP_PROTECT_TEXT|XTRAP_PROTECT_EXCEPT_VIRUS);

	CNetClientManager::getInstance().sendNXTrapCSAuthAnswer(sendData, 200);
#endif
}

/// Xigncode 보안 패킷을 받았다.
void CTRNetEventHandler::onRecvXigncodeCSPacket(char * data, size_t size)
{
#ifdef XIGNCODE
	DBG_OUTPUT(DBG_TYPE_SECURITY, "=========================================================");
	DBG_OUTPUT(DBG_TYPE_SECURITY, "[XIGNCODE] RECV PACKET");
	if(!ZCWAVE_ProbeEx(data, size, OnProbeComplete, NULL))
	{
		ULONG ErrorCode = GetLastError();
		DBG_OUTPUT(DBG_TYPE_SECURITY, "[XIGNCODE] eServer_XIGNCODE_RECV error (%08X)", ErrorCode);
		CStoveRogTranslator::getInstance().sendLog_Stove(eStove_Log_Category_Security_Exec, false, eError_SecurityExec_Error);
	}
	DBG_OUTPUT(DBG_TYPE_SECURITY, "=========================================================");
#endif
}

void CTRNetEventHandler::onRecvAhnHSAuthMSG(unsigned char * pbyRequest, unsigned long ulLength)
{
#ifdef HACKSHIELD
	AHNHS_TRANS_BUFFER ahnPackResponce;
	ZeroMemory(&ahnPackResponce,sizeof(ahnPackResponce));

	HS_MakeResponse(pbyRequest,ulLength,&ahnPackResponce);

	CNetClientManager::getInstance().sendAhnHSAuthAnswer(ahnPackResponce.byBuffer,ahnPackResponce.nLength);
	DBG_OUTPUT("CTRNetEventHandler::onRecvAhnHSAuthMSG");
#endif
}

#ifdef _ITEM_ONOFF
/// 실시간 으로 변경 해야되는 아이템 정보를 받았다.
void CTRNetEventHandler::onRecvRealTimeItemInfo(RT_ITEM::CPacket_RealTimeItemInfo & data)
{
	CClientItemList::getInstance().onRecvRealTimeItemInfo(data);


	if(CTRMawooShopDlg::getInstance().isVisible())	CTRMawooShopDlg::getInstance().refreshGoodsList();
	if(CTRFarmShopUI::getInstance().isVisible())	CTRFarmShopUI::getInstance().refreshGoodsList();
	if(CTRShopDlg::getInstance().isVisible())		CTRShopGoodsListDialog::getInstance().refreshGoodsList();
	if(CTRAlchemistUI::getInstance().isActive())	CTRAlchemistUI::getInstance().refreshGoodsList();

	CTRGuildFarmUI::getInstance().refreshGoodsList();
#ifdef _SHU_SYSTEM_
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().refreshGoodsList();
#endif //_SHU_SYSTEM_

}
#endif//_ITEM_ONOFF

/// 나의 활성화된 기능성 아이템을 받았다.
void CTRNetEventHandler::onRecvGetActiveFuncItem(const CActiveItems & activeItems)
{
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().refreshOneDayMissionInfo();
	if(!CTRNetPlayManager::getInstance().isAvatarLockLoad())
		CNetClientManager::getInstance().requestAvatarLockLoad();

	if (CTRMyroomDlg::getInstance().isVisible()) CTRMyroomDlg::getInstance().updateCharPropertyBar();
	else if (CTRShopDlg::getInstance().isVisible()) CTRShopDlg::getInstance().updateCharPropertyBar();
	else if (CTRGuildFarmUI::getInstance().isActive()) CTRGuildFarmUI::getInstance().updateCharPropertyBar();
#ifdef _SHOP_RENEWAL_
	else if (CTRShopManager::getInstance().GetShopDialog()) CTRShopManager::getInstance().GetShopDialog()->updateCharPropertyBar();
#endif
}

/// 나의 아이템 능력치를 받았다.
void CTRNetEventHandler::onRecvGetUserItemAttr(const CUserItemAttrManager& useritemAttr)
{
	CTRMyRoomGoodsListDialog::getInstance().onRecvGetUserItemAttr();
}

/// 나의 아이템 능력치를 받는데 실패하였다.
void CTRNetEventHandler::onRecvGetUserItemAttrFailed()
{
	DBG_OUTPUT(60, "CTRNetEventHandler::onRecvGetUserItemAttrFailed");
}

/// 나의 케릭터 능력치를 받았다.
void CTRNetEventHandler::onRecvGetUserCharAttr(const CUserItemAttrManager& useritemAttr)
{

}

/// 나의 케릭터 능력치를 받는데 실패하였다.
void CTRNetEventHandler::onRecvGetUserCharAttrFailed()
{
	
}

void CTRNetEventHandler::onRecvGetUserStrengthenItemInfo()
{

}

void CTRNetEventHandler::onRecvGetUserStrengthenItemInfoFailed()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGetUserStrengthenItemInfoFailed ");
}

/// 게임룸안에 있는 사용자의 활성화된 아이템 정보가 바뀌었다.
void CTRNetEventHandler::onRecvChangeUserActiveItems( BYTE playerIndex , const CActiveItems & activeItems)
{
	CTRGameParkUI::getInstance().onRecvChangeUserActiveItems(playerIndex , activeItems );
	CTRFarmUI::getInstance().onRecvChangeUserActiveItems(playerIndex , activeItems );

	if(m_pGameRoomUI)
		m_pGameRoomUI->onRecvChangeUserActiveItems(playerIndex);
		
		
}

/// 게임룸안에 있는 사용자의 활성화된 하나의 아이템 정보가 바뀌었다.
void CTRNetEventHandler::onRecvChangeUserActiveItemsOne( BYTE playerIndex , const CActiveItems & activeItems, const CUserItemAttrManager & useritemattr, const eChangeUserActiveItemFlag changeFlag)
{
	if(m_pGameRoomUI)
		m_pGameRoomUI->onRecvChangeUserActiveItemsOne(playerIndex, activeItems, useritemattr, changeFlag);
	else
	{
		CTRGameParkUI::getInstance().onRecvChangeUserActiveItemsOne(playerIndex, activeItems, useritemattr, changeFlag);
		CTRFarmUI::getInstance().onRecvChangeUserActiveItemsOne(playerIndex, activeItems, useritemattr, changeFlag);
	}
}

/// 게임룸안에 있는 사용자의 아이템 능력치 정보가 바뀌었다.
void CTRNetEventHandler::onRecvChangeUserItemAttr( BYTE playerIndex,const CUserItemAttrManager& useritemattr)
{

}

/// 특정유저의 상태정보가 바뀌었다.
void CTRNetEventHandler::onRecvUserState(BYTE playerIndex , const int iState )
{
	CTRUserInterface::getInstance().onRecvUserState(playerIndex , iState);
}

/// 나의 활성화된 기능성 아이템을 받는데 실패했다.
void CTRNetEventHandler::onRecvGetActiveFuncItemFailed()
{
}

/// 나의 활성화된 기능성 아이템이 시간이 지났다.
void CTRNetEventHandler::onRecvActiveFuncItemTimeOut( const int iItemDescNum)
{
	//TRDBG_OUTPUT_SYSTEM("onRecvActiveFuncItemTimeOut(cpk=%d,%d,%d, desc#=%d)", info.m_character, info.m_position, info.m_kind, info.m_iItemDescNum);

	const CItemInfoNode * goodsinfo = CClientItemList::getInstance().getItemInfo(iItemDescNum);

	_ASSERTE(goodsinfo);
	if( goodsinfo )
	{
		//if(goodsinfo->m_position == ITEM_POSITION_CHARACTER && goodsinfo->m_dwType == CItemInfoNode::ITEMTYPE_PARENTDESC)
		if(goodsinfo->m_position == ITEM_POSITION_CHARACTER)	// 기간이 만료된 아이템이 캐릭터라면 
		{
			DBG_OUTPUT("%s called CharacterTimeOut character= %d ", __FUNCTION__ , goodsinfo->m_character);
			CTRPeriodCharacterTimeoutManager::getInstance().onRecvPeriodCharacterTimeOver(iItemDescNum);	// 타임오버 메시지를 보낸다.
		}		

		CKeepItemList::getInstance().eraseItem(iItemDescNum);
		DBG_OUTPUT("onRecvActiveFuncItemTimeOut(%d)", iItemDescNum);

		//if (bLevelLimit)
		//{
		//	// TO : true일 경우에 레벨 제한으로 인해서 벗겨진 아이템 리스트들을 요청하고 보여줘야 한다. gui도 필요
		//}

		CTRMyroomDlg::getInstance().onRecvActiveFuncItemTimeOut(iItemDescNum);

		if( goodsinfo->m_position == eFuncItemPosition_JEWEL_ITEM )
		{
#ifdef _SHOP_RENEWAL_
			if (CTRShopManager::getInstance().GetShopDialog()) CTRShopManager::getInstance().GetShopDialog()->updateAvatarSlotView();
#endif
			if( CTRMawooShopDlg::getInstance().isVisible() )	CTRMawooShopDlg::getInstance().updateAvatarSlotView();
			if( CTRMyroomDlg::getInstance().isVisible() )		CTRMyroomDlg::getInstance().updateAvatarSlotView();
			if( CTRShopDlg::getInstance().isVisible() )	CTRShopDlg::getInstance().updateAvatarSlotView();
		}
	}

	CTRMyRoomGoodsListDialog::getInstance().onRecvActiveFuncItemTimeOut();

	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().refreshOneDayMissionInfo();

	// onRecvRoomUserFuncItemTimeOut(const BYTE numGameIndex, const NetItemInfo & info)가
	// 호출되므로 clearInvalidAvatarItems(true) 함수 호출은 필요없음.
}

void CTRNetEventHandler::onRecvActiveFuncItemTimeOut()
{
	CTRFishingSystemManager::getInstance().onRecvActiveFuncItemTimeOut();
}

/// 나의 버프 아이템이 시간이 지났다.
void CTRNetEventHandler::onRecvBuffItemTimeOut(const int iItemDescNum)
{
	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_EXTRA_ABILITY);

	const CItemInfoNode * goodsinfo = CClientItemList::getInstance().getItemInfo(iItemDescNum);
	if(goodsinfo == NULL)
	{
		DBG_OUTPUT("CTRNetEventHandler::onRecvBuffItemTimeOut ItemInfo Error");
		return;
	}

	DBG_OUTPUT("CTRNetEventHandler::onRecvBuffItemTimeOut %s", goodsinfo->m_name.c_str());

	if(CTRMyroomDlg::getInstance().isVisible())
	{
		CTRMyroomDlg::getInstance().onRecvActiveFuncItemTimeOut(iItemDescNum);

		//if (bLevelLimit)
		//{
		//	// TO : true일 경우에 레벨 제한으로 인해서 벗겨진 아이템 리스트들을 요청하고 보여줘야 한다. gui도 필요
		//}
	}
}

/// 클라이언트가 쓰일 웹 페이지의 url 을 받았다.
void CTRNetEventHandler::onRecvClientWebPageURL(eWebPageReq reqKind, const std::string & strURL)
{
	if(strURL == "")
	{
		DBG_OUTPUT(60, "CTRNetEventHandler::onRecvClientWebPageURL URL empty", (int)reqKind);
		CTRWebPageDialog::getInstance().setWebViewGuiType(0);  // webViewGuiType 초기화
		return;
	}

	switch ( reqKind )
	{
	case eWebPageReq_GATE_NOTICE:
		CTRWebPageDialog::getInstance().openDialog(strURL,WEBPAGE_NOTICE);
		break;
	case eWebPageReq_BILLING_PAGE:
		{
			switch(CTRUserInterface::getInstance().getCurrentUIType())
			{
			case GUI_TYPE_SHOP:
			case GUI_TYPE_MYROOM:
			case GUI_TYPE_ALCHEMIST:
			case GUI_TYPE_FARMLOBBY:
			case GUI_TYPE_FARM:
			case GUI_TYPE_PARK:
			case GUI_TYPE_RANK:
			case GUI_TYPE_GUILD_FARM:
			case GUI_TYPE_MAWOO_SHOP:
			case GUI_TYPE_SHU_ROOM:
			case GUI_TYPE_GAMEROOM:
			case GUI_TYPE_CROWD_GAMEROOM:
			case GUI_TYPE_NORMALPLAY_GAMEROOM:
			case GUI_TYPE_TEAMPLAY_GAMEROOM:
			case GUI_TYPE_RELAY_GAMEROOM:
			case GUI_TYPE_NORMALPLAY_MULTI_MINIGAME_GAMEROOM:
			case GUI_TYPE_TEAMPLAY_MULTI_MINIGAME_GAMEROOM:
#ifdef _TR_KNIGHTAGE_
			case GUI_TYPE_LOBBY:
#endif
				CTRWebPageDialog::getInstance().openDialog(strURL,WEBPAGE_BILLINGPAGE);
				break;
			}
		}
		/*TRShopUI::getInstance().onRecvBillingPageURL(strURL);
		CTRMawooShopUI::getInstance().onRecvBillingPageURL(strURL);
		CTRMyRoomUI::getInstance().onRecvBillingPageURL(strURL);
		CTRGameParkUI::getInstance().onRecvBillingPageURL(strURL);
		CTRFarmUI::getInstance().onRecvBillingPageURL(strURL);
		CTRAlchemistUI::getInstance().onRecvBillingPageURL(strURL);
		CTRGuildFarmUI::getInstance().onRecvBillingPageURL(strURL);
		CTRRankUI::getInstance().onRecvBillingPageURL(strURL);*/
//#ifdef _SHU_SYSTEM_
//		SHU_SYSTEM::CTRShuUI_Management::getInstance().onRecvBillingPageURL(strURL);
//#endif //_SHU_SYSTEM_
		break;
	case eWebPageReq_GIFT_TICKET:
		{
			switch(CTRUserInterface::getInstance().getCurrentUIType())
			{
			case GUI_TYPE_SHOP:
			case GUI_TYPE_MYROOM:
			case GUI_TYPE_ALCHEMIST:
			case GUI_TYPE_FARMLOBBY:
			case GUI_TYPE_FARM:
			case GUI_TYPE_PARK:
			case GUI_TYPE_RANK:
			case GUI_TYPE_GUILD_FARM:
			case GUI_TYPE_MAWOO_SHOP:
			case GUI_TYPE_SHU_ROOM:
				CTRWebPageDialog::getInstance().openDialog(strURL,WEBPAGE_GIFTTICKET);
				break;
			}
		}		
		//CTRShopUI::getInstance().onRecvGiftTicketPageURL(strURL);
//		CTRMawooShopUI::getInstance().onRecvGiftTicketPageURL(strURL);
//		CTRMyRoomUI::getInstance().onRecvGiftTicketPageURL(strURL);
//		CTRGameParkUI::getInstance().onRecvGiftTicketPageURL(strURL);
//		CTRFarmUI::getInstance().onRecvGiftTicketPageURL(strURL);
//		CTRAlchemistUI::getInstance().onRecvGiftTicketPageURL(strURL);
//		CTRGuildFarmUI::getInstance().onRecvGiftTicketPageURL(strURL);
//		CTRRankUI::getInstance().onRecvGiftTicketPageURL(strURL);
//
//#ifdef _SHU_SYSTEM_
//		SHU_SYSTEM::CTRShuUI_Management::getInstance().onRecvGiftTicketPageURL(strURL);
//#endif //_SHU_SYSTEM_
		break;

	case eWebPageReq_BOOKY_PAGE:
		CTRUserBookDlg::getInstance().onRecvBookyPageURL(strURL);
		break;

	case eWebPageReq_GUILD_BOOKY_PAGE:
		CTRLobbyUI::getInstance().onRecvFamilyBookyPageURL(strURL);
		CTRGameParkUI::getInstance().onRecvFamilyBookyPageURL(strURL);
		CTRFarmUI::getInstance().onRecvFamilyBookyPageURL(strURL);
		break;
	case eWebPageReq_GUILD_BOARD_PAGE:
		CTRGuildDlg::getInstance().onRecvGuildBoardPageURL(strURL);
		break;

	case eWebPageReq_QUIT_PAGE:
		CTRExitDialog::getInstance().onRecvQuitConfirmPageURL(strURL);
		break;
	case eWebPageReq_EVERYDAYEVENT_PAGE:
		CTRLobbyUI::getInstance().onRecvEveryDayEventPageURL(strURL);
		CTRGameParkUI::getInstance().onRecvEveryDayEventPageURL(strURL);
		CTRFarmLobbyUI::getInstance().onRecvEveryDayEventPageURL(strURL);
		CTRFarmUI::getInstance().onRecvEveryDayEventPageURL(strURL);
		CTRShopUI::getInstance().onRecvEveryDayEventPageURL(strURL);
		CTRMawooShopUI::getInstance().onRecvEveryDayEventPageURL(strURL);
		CTRMyRoomUI::getInstance().onRecvEveryDayEventPageURL(strURL);
		CTRAlchemistUI::getInstance().onRecvEveryDayEventPageURL(strURL);
		CTRRankUI::getInstance().onRecvEveryDayEventPageURL(strURL);

#ifdef _SHOP_RENEWAL_
		CTRShopRenewalUI::getInstance().onRecvEveryDayEventPageURL(strURL);
#endif

#ifdef _SHU_SYSTEM_
		SHU_SYSTEM::CTRShuUI_Management::getInstance().onRecvEveryDayEventPageURL(strURL);
#endif //_SHU_SYSTEM_
		break;
	case eWebPageReq_OPENTV_PAGE:
		CTRGameParkUI::getInstance().onRecvOpenTVPageURL(strURL);
		break;
	case eWebPageReq_FARM_GUESTBOOK_PAGE:
	case eWebPageReq_DONATION_EVENT:
		CTRFarmUI::getInstance().onRecvFamrGuestBookPageURL(strURL);
		break;
	case eWebPageReq_PIEROOLYMPIC_SIGNPOST_PAGE:
		CTRGameParkUI::getInstance().onRecvPieroOlympicSignPostPageURL(strURL);
		CTRLobbyUI::getInstance().onRecvPieroOlympicSignPostPageURL(strURL);
		break;
	case eWebPageReq_PIEROOLYMPIC_SCHEDULE_PAGE:

		break;
	case eWebPageReq_FIND_FRIEND_PAGE:
		CTRLobbyUI::getInstance().onRecvFindFriendPageURL(strURL);
		break;
	case eWebPageReq_NEW_CHAOS_SCHEDULE_PAGE:
		
		break;
	case eWebPageReq_NEW_CHAOS_RANKER_ITEM_GUIDE_PAGE:
		
		break;
	case eWebPageReq_BIG_SPORTS_HALL_OF_FAME_PAGE:
		CTRGameParkUI::getInstance().onRecvBigSportsHallOfFamePageURL(strURL);
		break;
	case eWebPageReq_DRAGON_CARTOON_PAGE:
		CTRGameParkUI::getInstance().onRecvDragonCartoonPageURL(strURL);
		break;
	case eWebPageReq_FREE_CHANNEL_HALL_OF_FAME_PAGE:
		CTRGameParkUI::getInstance().onRecvFreeChHallOfFamePageURL(strURL);
		break;
	case eWebPageReq_THIS_MONTH_OF_LOTTERY :
		if(!strURL.empty())
            CTRWebPageDialog::getInstance().openDialog(strURL, WEBPAGE_THIS_MONTH_OF_LOTTERY,true,false,true);
		break;

	case eWebPageReq_CHAOS_GUIDE_PAGE:
	case eWebPageReq_CHAOS_SCHEDULE_PAGE:
	case eWebPageReq_CHAOS_TEAM_BOARD_PAGE:
	case eWebPageReq_COMPETITION_EVENT_GUIDE_PAGE:	// 영웅전 가이드 페이지
	case eWebPageReq_COMPETITION_EVENT_TEAM_BOARD:
		CTRLobbyUI::getInstance().onRecvEventGameWebPageURL(reqKind, strURL);
		break;
#ifdef ENTRY_SYSTEM
	case eWebPageReq_ENTRY_SYSTEM:
		CTREntrySystemManager::getInstance().onRecvWebPageURL(reqKind, strURL);
		break;
#endif

	case eWebPageReq_REGISTER_GUILD_MARK:
		CTRWebPageDialog::getInstance().openDialog( strURL, WEBPAGE_REGISTER_GUILD_MARK );
		break;

	case eWebPageReq_EVERYDAYATTENDANCE_PAGE:
		CTRLobbyUI::getInstance().onRecvEveryDayAttendanceURL(strURL);
		break;

	case eWebPageReq_EVENT_CALENDAR:
		CTRLobbyUI::getInstance().onRecvEventCalendarURL(strURL);
		break;

	default:
		_ASSERTE(false);
		DBG_OUTPUT(60, "CTRNetEventHandler::onRecvClientWebPageURL unknown kind", (int)reqKind);
		return;
	}
}


/// 공지사항을 받았다.
void CTRNetEventHandler::onRecvNoticeMsg(const NOTICE& notice)
{
	DBG_DEMO_OUTPUT(60, "onRecvNoticeMsg: Type [%d] msg [%s]", static_cast<int>(notice.m_type), notice.m_strNotice.c_str());
	
	if(CTRUserInterface::getInstance().isShowNotice())
	{
		CTRUserInterface::getInstance().onRecvNoticeMsg(notice.m_type, notice.m_strNotice);
	}
	else
	{
		CTRSystemNotice::getInstance().showMessageEx(notice);
	}
}
/// 외치기 아이템을 사용했다.
void CTRNetEventHandler::onRecvUseShoutItem(eServerResult dwResult,const int iShoutItemDescNum, std::string& restrictEndTime)
{
	string strMsg;
	DBG_OUTPUT(60, "CTRNetEventHandler::onRecvUseShoutItem : %d", dwResult);

	switch(dwResult)
	{
	case eServerResult_OK_ACK :
		CKeepItemList::getInstance().eraseItem(iShoutItemDescNum);
		CTRUserInterface::getInstance().onRecvUseShoutItem(iShoutItemDescNum);
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_USE_ITEM, iShoutItemDescNum);
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_USE_ITEM_COUNT);
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();
		break;
	case eServerResult_USE_SHOUT_ITEM_FAILED_MSG_EMPTY_ACK :
		strMsg = format(_STR(ERR_SHOUT_ITEM_FAILED_EMPTY));
		CTRUserInterface::getInstance().onRecvUseShoutItemFailed(strMsg);
		break;
	case eServerResult_USE_SHOUT_ITEM_FAILED_GM_COMMAND_ACK:
		strMsg = format(_STR(FAILED_USE_SHOUT_ITEM_GM_COMMAND), restrictEndTime.c_str());
		CTRUserInterface::getInstance().onRecvUseShoutItemFailed(strMsg);
		break;
	case eServerResult_USE_SHOUT_ITEM_FAILED_ACK :
	default :
		strMsg = format(_STR(ERR_SHOUT_ITEM_FAILED));
		CTRUserInterface::getInstance().onRecvUseShoutItemFailed(strMsg);
		break;
	}
}

/// 외치기 메세지
void CTRNetEventHandler::onRecvShoutItemMsg(const UserShoutInfo& info)
{
	string strMsg = info.m_strNickName + ": " + info.m_strMsg;
	DWORD dwShoutItemOption = static_cast<DWORD>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(info.m_iShoutItemDescNum).m_attr[eItemAttr_Shout_Otion]);
	bool bMyMessage = false;

	
	CTRChattingManager::CHAT_ITEM_TYPE chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV1;

	CTRRankInfoManager & rankInfo = CTRRankInfoManager::getInstance();

	int iLevel = rankInfo.getGameLevelFromExp(eLevelUPKind_RUN, info.m_iExp);
	int iShape, iColor;

	if(info.m_strNickName == CNetClientManager::getInstance().getMyNickname())
	{
		bMyMessage = true;
	}

	if(rankInfo.getRankShapeByLevel(iLevel, iShape, iColor))
	{
		if(iShape >= 0 && iShape< 6)
		{
			chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV1;
		}
		else if(iShape == 6)
		{
			chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV2;
		}
		else if(iShape == 7)
		{
			chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV3;
		}
		else if(iShape == 8)
		{
			chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV4;
		}
		else if(iShape == 9)
		{
			chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV5;
		}
		else if(iShape == 10)
		{
			chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV6;
		}
		else if(iShape == 11)
		{
			chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV7;
		}
		else if(iShape == 12)
		{
			chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV8;
		}
		else if(iShape == 13)
		{
			chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV9;
		}
		else if(iShape == 14)
		{
			chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV10;
		}
		else if(iShape >= 15)
		{
			chatType = CTRChattingManager::CHAT_ITEM_SHOUT_LV11;
		}
	}
	
	CTRUserInterface::getInstance().onRecvShoutItemMsg(eShoutItemOtion_CHAT, strMsg, chatType, bMyMessage);
}

/// 커플생성 축하 외치기 메세지
void CTRNetEventHandler::onRecvShoutCoupleCreateCoupleMsg(const UserShoutInfo& info)
{
	vector<string> splitBuf;

	stringstream ss(info.m_strMsg);
	stringutil::split(splitBuf,ss,'/');
	if(splitBuf.size() == 2 && !CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_COUPLE_MESSAGE_INFO)))
	{
		string strMsg = format(_STR(COUPLESYS_PROPOSE_MSG_CREATE_COUPLE_SHOUT), splitBuf[0].c_str(), splitBuf[1].c_str());
		CTRUserInterface::getInstance().onRecvShoutItemMsg(eShoutItemOtion_CHAT, strMsg, CTRChattingManager::CHAT_ITEM_COUPLE_CREATE, false);
	}	
}

/// 가족맺기 축하 외치기 메세지
void CTRNetEventHandler::onRecvShoutCoupleCreateFamilyMsg(const UserShoutInfo& info)
{
	//사용 안함
	/*
	DBG_OUTPUT("CTRNetEventHandler::onRecvShoutCoupleCreateFamilyMsg...");
	vector<string> splitBuf;

	stringutil::split(splitBuf, stringstream(info.m_strMsg),'/');
	if(splitBuf.size() == 2)
	{
		string strMsg = format(_STR(FAMILY_MSG_SHOUT_CREATE_FAMILY), splitBuf[0].c_str(), splitBuf[1].c_str());

		CTRChattingManager::getInstance().insertItemChatData(
			strMsg, CTRChattingManager::CHATTING_MODE_SHOUT, CTRChattingManager::CHAT_ITEM_COUPLE_CREATE, false);
		CTRUserInterface::getInstance().onRecvShoutItemMsg(eShoutItemOtion_CHAT, strMsg, CTRChattingManager::CHAT_ITEM_COUPLE_CREATE, false);
	}
	*/
}

/// 결혼 축하 메세지
void CTRNetEventHandler::onRecvShoutWeddingMarchMsg(const UserShoutInfo& info)
{
	vector<string> splitBuf;

	stringstream ss(info.m_strMsg);
	stringutil::split(splitBuf,ss,'/');
	if(splitBuf.size() == 2 && !CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_COUPLE_MESSAGE_INFO)))
	{
		string strMsg = format(_STR(WEDDING_SHOUT_WEDDING_SUCCESS), splitBuf[0].c_str(), splitBuf[1].c_str());
		CTRUserInterface::getInstance().onRecvShoutItemMsg(eShoutItemOtion_CHAT, strMsg, CTRChattingManager::CHAT_ITEM_WEDDING_EVENT, false);
	}
}

/// 삐에로 올림픽 방해성장수 메세지
void CTRNetEventHandler::onRecvShoutInterruptObjectMsg(const UserShoutInfo& info)
{
	vector<string> splitBuf;

	stringstream ss(info.m_strMsg);
	stringutil::split(splitBuf,ss,'/');

	if(splitBuf.size() == 1)
	{
		string strColor = "";
		
		ePieroOlympicPartyType ePieroPartyType = (ePieroOlympicPartyType)atoi(splitBuf[0].c_str());

		strColor = CTREventSportsManager::getInstance().colorToString(ePieroPartyType);

		string attackMsg = "";
		
		switch(CTREventSportsManager::getInstance().getEventSportsType())
		{
		case CTREventSportsManager::ePieroOlympic_LoveBattle1:
			attackMsg = _STR(NOTIFY_ATTACK_PIERO_PLANT);
			break;
		case CTREventSportsManager::ePieroOlympic_LoveBattle2:
			attackMsg = _STR(NOTIFY_ATTACK_PIERO_BUILDING);
			break;
		case CTREventSportsManager::ePieroOlympic_New:
			attackMsg = _STR(NOTIFY_ATTACK_PIERO_CYLINDER);
			break;
		}

		string strMsg = '[' + (string)_STR(CHARACTER_PIERO_NAME) + ']' + strColor.c_str() + attackMsg.c_str();

		if(CLanguageFile::getInstance().isHongkong())				// 국가 별로 어순이나 표기 방법이 다른 경우가 있음
		{
			strMsg = (string)strColor.c_str() + (string)_STR(CHARACTER_PIERO_NAME) + attackMsg.c_str();
		}
		
		CTRUserInterface::getInstance().onRecvShoutItemMsg(eShoutItemOtion_CHAT, strMsg, CTRChattingManager::CHAT_ITEM_INTERRUPT_OBJECT, false);
	}
}

/// 길드 레벨업 메시지
void CTRNetEventHandler::onRecvShoutGuildLevelUpMsg(const UserShoutInfo& info)
{
	string strMsg = format(_STR(INFORMATION_GUILD_LEVEL_UP_SHOUT), info.m_strNickName.c_str(), info.m_iShoutItemDescNum);

	CTRUserInterface::getInstance().onRecvShoutItemMsg(eShoutItemOtion_CHAT,strMsg,CTRChattingManager::CHAT_ITEM_GUILD_LEVEL_UP,false);
}

/// 커플링 교체 축하 외치기 메세지
void CTRNetEventHandler::onRecvShoutCoupleChangeRingMsg(const UserShoutInfo& info)
{
	vector<string> splitBuf;

	int requirementLevel = static_cast<int>(CItemAttrTable::getInstance().getItemAttrFromItemDescNum(info.m_iShoutItemDescNum).m_attr[eItemAttr_Couple_Level]);

	stringstream ss(info.m_strMsg);
	stringutil::split(splitBuf,ss,'/');
	
	//!< 커플레벨 기준값(10레벨) 서버세팅값으로 체크함
	int iCoupleLevel10 = atoi(CNetClientManager::getInstance().getServerSetting("CoupleLevelConditionCheck", "10").c_str());

	if(splitBuf.size() == 2 && requirementLevel >= iCoupleLevel10 && !CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_COUPLE_MESSAGE_INFO)))
	{
		string strMsg = format(_STR(COUPLESYS_CHANGE_MSG_RING_CHANGE_SHOUT), splitBuf[0].c_str(), splitBuf[1].c_str(), requirementLevel);
		CTRUserInterface::getInstance().onRecvShoutItemMsg(eShoutItemOtion_CHAT,strMsg,CTRChattingManager::CHAT_ITEM_COUPLE_CHANGE_RING,false);
	}
}


void CTRNetEventHandler::onRecvUseChargeCommunityMoneyItem(eServerResult dwResult,const int iItemDescNum, std::string stdUserID)
{
	string strMsg;
	DBG_OUTPUT(60, "CTRNetEventHandler::onRecvUseChargeCommunityMoneyItem : %d", dwResult);

	switch(dwResult)
	{
	case eServerResult_OK_ACK :
		CKeepItemList::getInstance().eraseItem(iItemDescNum);
		CTRMyRoomGoodsListDialog::getInstance().onRecvUseChargeCommunityMoneyItem();
		strMsg = format(_STR(ITEM_USE_CHARGE_CUMMUNITY_MONEY_ITEM_OK));
		break;
	case eServerResult_USE_CHARGE_CUMMUNITY_MONEY_ITEM_INVALID_USER_ACK :			//!< 커뮤니티에 계정이 존재하지 않는 유저.
		strMsg = format(_STR(ERR_CHARGE_CUMMUNITY_MONEY_ITEM_INVALID_USER));
		break;
	case eServerResult_USE_CHARGE_CUMMUNITY_MONEY_ITEM_FAILED_ACK :					//!< 알수 없는 이유로 실패.
	default :
		strMsg = format(_STR(ERR_CHARGE_CUMMUNITY_MONEY_ITEM_FAILED));
		break;
	}
	CTRGoldMoneyDialog::getInstance().onRecvUseChargeCommunityMoneyItem(strMsg);
}

/// 이벤트에 실패했다.
void CTRNetEventHandler::onRecvEventFail()
{
	DBG_OUTPUT(60, "CTRNetEventHandler::onRecvEventFail()");
	CTREventFailDialog::getInstance().showDialog(_STR(MSG_EVENT_FAIL));
}


/// 유저 정보가 왔다.
void CTRNetEventHandler::onRecvGetUserInfoOK(const UserInfo & userInfo, AvatarLock & avatarLock)
{
	DBG_OUTPUT(60, "onRecvGetUserInfo: %s", userInfo.m_strUserNickName.c_str());

	if(userInfo.m_advancedAvatarInfo.isPieroAvatar())
	{
		CTRShortTimeMessage::getInstance().showMessage(_STR(MSG_FARM_MASTER_PIERO_INFO_SECRET));
		return;
	}

	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		if("true" == CNetClientManager::getInstance().getServerSetting("EnableBookSystem", "false"))
			CTRUserBookDlg::getInstance().showUI(userInfo, false, avatarLock);
		else
			CTRShortTimeMessage::getInstance().showMessage(_STR(MSG_CANNOT_USE_TALES_BOOK));
	}
}

/// 유저 정보를 얻는데 실패하였다.
void CTRNetEventHandler::onRecvGetUserInfoFailed(const std::string & stdNickName)
{
	// TODO: 작성 바람
	// 유저 정보를 얻는데 실패하였다.
	_ASSERTE(FALSE);
}

//////////////////////////////////////////////////////////////////////////

/// 유저 옵션 정보가 왔다.
void CTRNetEventHandler::onRecvSetUserOptionOK(const int iOption)
{
	DBG_DEMO_OUTPUT("%s - GameOption : %d", __FUNCTION__, iOption);

	if( CTRUserBookDlg::getInstance().isVisible() )
	{
		CTRUserBookDlg::getInstance().onRecvSetUserOptionOK();
	}
}

/// 유저 옵션 정보를 얻는데 실패하였다.
void CTRNetEventHandler::onRecvUserOptionFailed()
{	
	TRDBG_OUTPUT_ERROR("%s", __FUNCTION__);
}

#ifdef _ITEM_COLLECTION
/// 유저 아이템 컬력션 정보이다.
void CTRNetEventHandler::onRecvItemCollectionInfoOK(const std::string & strNickName, const exp_type iPoint, const int iRank)
{
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().onRecvItemCollectionInfoOK(strNickName, iPoint, iRank);
}

/// 유저 아이템 컬력션 아이템 정보이다.
void CTRNetEventHandler::onRecvItemCollectionListOK(const std::string & strNickName, const std::vector<int> & vItemList)
{
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().onRecvItemCollectionListOK(strNickName, vItemList);
}

/// 유저 아이템 컬력션 대표 아이템 등록에 성공했다.
void CTRNetEventHandler::onRecvItemCollectionAddOK()
{
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().onRecvItemCollectionAddOK();
}

///  유저 아이템 컬력션 관련하여 실패하였다.
void CTRNetEventHandler::onRecvItemCollectionFailed(const eServerResult & dwResult)
{
	std::string strMent = _STR(ERR_UNKNOWN);

	switch(dwResult)
	{
	case eServerResult_ITEM_COLLECTION_ADD_FAILED_ACK:
		strMent = _STR(FAILED_ITEM_COLLECTION_ADD);
		break;

	case eServerResult_ITEM_COLLECTION_CLOSED_ACK:
		strMent = _STR(FAILED_ITEM_COLLECTION_CLOSED);
		break;
	}

	CTRShortTimeMessage::showMessage(strMent);
}

#endif

//////////////////////////////////////////////////////////////////////////

/// 랭킹 정보를 받는데 실패했다.
void CTRNetEventHandler::onRecvRankInfoFailed(void)
{
	CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_RANK_INFO_FAILED));
	CTRRankUI::getInstance().onRecvRankInfoFailed();
}

/// 랭킹 정보가 왔다.
void CTRNetEventHandler::onRecvRankInfo(const eRequestRankKind rankKind, const std::vector < CRankListData > & rankList, const std::vector<CoupleRankInfo>& coupleRankList)
{
	DBG_OUTPUT(60, "onRecvRankInfo");
	CTRRankUI::getInstance().onRecvRankInfo(rankKind,rankList,coupleRankList);
}

/// 내 랭킹 정보가 왔다.
void CTRNetEventHandler::onRecvMyRankInfo(const eRequestRankKind rankKind, const CRankListData & rankData, const CoupleRankInfo& coupleRankInfo)
{
	DBG_OUTPUT(60, "onRecvMyRankInfo");
	CTRRankUI::getInstance().onRecvMyRankInfo(rankKind, rankData, coupleRankInfo);
}

/// 내 랭킹 정보를 받는데 실패했다.
void CTRNetEventHandler::onRecvMyRankInfoFailed(eRequestRankKind rankKind)
{
	CTRRankUI::getInstance().onRecvMyRankInfoFailed(rankKind);
}


/// 재판소를 진행하라고 왔다.
void CTRNetEventHandler::onRecvCourtResult(const int judgementNum, const eCourtKind kind, const BYTE punishcount, const bool infinity)
{
	DBG_OUTPUT(60, "onRecvCourtResult");
	CTRCourtUI::getInstance().onRecvCourtResult(judgementNum, kind, punishcount, infinity);
}

/// 재판소할 것이 없다고 왔다.
void CTRNetEventHandler::onRecvCourtNoResult()
{
	DBG_OUTPUT(60, "onRecvCourtNoResult");
	CTRCourtUI::getInstance().onRecvCourtNoResult();
}

/// 불량유저 신고 응답이 왔다.
void CTRNetEventHandler::onRecvBadUserResult(const eCourtKind kind, const eServerResult dwResult)
{
	switch (dwResult)
	{
	case eServerResult_OK_ACK:
		CTRShortTimeMessage::showMessage(_STR(INFORMATION_ABUSEREPORT));
		break;
	case eServerResult_DB_FAILED_ACK:
		CTRShortTimeMessage::showMessage(_STR(PERSONALCONNECIONS_REPORT_ERROR));
		break;
	}
}
//////////////////////////////////////////////////////////////////////////
// MiniGame 관련 시작..

//!< 미니게임 맵 정보를 받는 데 성공하였다.
void CTRNetEventHandler::onRecvMiniGameGetMapInfoOK(const int numMap,const int nMapPrice,const int nRewardPoint,const int nLife,const int nItemDescNum)
{
	CTRGameParkUI::getInstance().onRecvMiniGameGetMapInfoOK(numMap, nMapPrice, nRewardPoint, nLife, nItemDescNum);
}

//!< 미니게임 맵 정보를 받는 데 실패하였다.
void CTRNetEventHandler::onRecvMiniGameGetMapInfoFailed()
{

}

//!< 미니게임을 시작해도 좋다.
void CTRNetEventHandler::onRecvMiniGameStartOK(const int numMap, const int iRandomSeed,const int iRemainGameMoney)
{
	if(CGameManager::getInstance().isGameModeMiniGame())
	{
		CTRMiniGameGameUI::getInstance().onRecvMiniGameStartOK();
		CGameManager::getInstance().setRandomSeed(iRandomSeed);
		m_pNetPlay->startGame();

		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_MAP, numMap);
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();
	}
	else
	{
		// 미니게임이 아닌데 이 메시지를 받으면 안된다.
		_ASSERTE(false);
	}

}

//!< 게임 머니가 부족하여 시작을 하지 못했다.
void CTRNetEventHandler::onRecvMiniGameStartFailedPayGameMoney(const int numMap, const int iRemainGameMoney)
{
	CTRMiniGameGameUI::getInstance().doExitGame();
}

//!< 유효하지 않는 맵을 시작하려고 했다.
void CTRNetEventHandler::onRecvMiniGameStartFailedInvalidMapNum()
{
	CTRMiniGameGameUI::getInstance().doExitGame();
}

//!< 미니게임 랭킹 정보를 얻었다.
void CTRNetEventHandler::onRecvMiniGameGetRankOK(const int numMap, const std::vector<MiniGameRankInfo>& rankInfo, const int nMyRank, const DWORD dwMyPoint)
{
	CTRGameParkUI::getInstance().onRecvMiniGameGetRankOK(numMap, rankInfo, nMyRank, dwMyPoint);
}

//!< 미니게임 랭킹 정보를 얻는데 실패하였다(맵번호가 유효하지 않음.)
void CTRNetEventHandler::onRecvMiniGameGetRankFailedInvalidMapNum()
{

}

//!< 미니게임 끝 성공.
void CTRNetEventHandler::onRecvMiniGameOverOK(const int myBestPoint, const int myRank,const int nRewardItemDescNum , DWORD dwRewardPoint)
{
	CTRMiniGameGameUI::getInstance().onRecvMiniGameOverOK(myBestPoint, myRank, nRewardItemDescNum, dwRewardPoint);

	//! 도전 미션이 있는지 확인한다.
	CMissionMsgDispatcher::getInstance().setConditionCheckValue_Bool(CHECK_VALUE_BOOL_COMPLETE_MINI_GAMEPLAY, true);

	CMissionMsgDispatcher::getInstance().onRecvRoomResultForMissionCheckNotify();
	CMissionMsgDispatcher::getInstance().processEndGame();
}

//!< 미니게임 끝 실패.
void CTRNetEventHandler::onRecvMiniGameOverFailed(eServerResult eResult)
{
	CTRMiniGameGameUI::getInstance().onRecvMiniGameOverFailed(eResult);
}

// MiniGame 관련 끝..
//////////////////////////////////////////////////////////////////////////

//! 나의 알림 정보를 얻었다.
void CTRNetEventHandler::onRecvUserAlarmInfo(std::vector<UserAlarmInfo> vAlarmInfoList)
{
	CTRUserAlarmManager::getInstacne().onRecvUserAlarmInfo(vAlarmInfoList);
}

// 커플시스템 관련 시작...

//! 프로포즈 정보를 체크한다.
void CTRNetEventHandler::onRecvCoupleCheckProposeInfo(eServerResult eResult, bool bMeetingDependency)
{
	// 서버에 커플 정보의 체크 결과를 받는다.
	CTRCoupleSystem::getInstacne().onRecvCoupleCheckProposeInfo(eResult, bMeetingDependency);	
}

//! 커플링 교체에 성공했다.
void CTRNetEventHandler::onRecvCoupleChangeCoupleRingOK(const CoupleInfo & OrgCoupleInfo ,const CoupleInfo & ChangeCoupleInfo)
{
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvCoupleChangeCoupleRing(OrgCoupleInfo.coupleRingInfo.iCoupleRingNum);
#endif
	CTRMyroomDlg::getInstance().onRecvCoupleChangeCoupleRing(OrgCoupleInfo.coupleRingInfo.iCoupleRingNum);
	CTRShopDlg::getInstance().onRecvCoupleChangeCoupleRing(OrgCoupleInfo.coupleRingInfo.iCoupleRingNum);
	CTRCoupleSystem::getInstacne().onRecvCoupleChangeCoupleRingOK(OrgCoupleInfo,ChangeCoupleInfo);

}

//! 커플링 교체에 실패했다.
void CTRNetEventHandler::onRecvCoupleChangeCoupleRingFailed(eCoupleChangeCoupleRing failedReason)
{
	CTRCoupleSystem::getInstacne().onRecvCoupleChangeCoupleRingFailed(failedReason);
	DBG_OUTPUT("CTRNetEventHandler::onRecvCoupleChangeCoupleRingFailed...reason=[%d]", failedReason);
}

//! 프로포즈 정보 초기화에 성공했다.
void CTRNetEventHandler::onRecvCoupleInitRecvProposeInfoOK()
{
	CTRCoupleSystem::getInstacne().onRecvCoupleInitRecvProposeInfoOK();
}

//! 프로포즈 정보 초기화에 실패했다.
void CTRNetEventHandler::onRecvCoupleInitRecvProposeInfoFailed()
{
    DBG_OUTPUT("CTRNetEventHandler::onRecvCoupleInitRecvProposeInfoFailed...");
}

//! 커플 생성요청에 대한 응답을 받았다.	
void CTRNetEventHandler::onRecvCoupleCreateCoupleInfo(eServerResult eResult, const int iCoupleNum, const int iCoupleRingNum)
{
	CTRCoupleSystem::getInstacne().onRecvCoupleCreateCoupleInfo(eResult, iCoupleNum, iCoupleRingNum);	
}

//!< 커플정보 변경 처리가 성공했다.
void CTRNetEventHandler::onRecvCoupleModifyCoupleInfoOK()
{
	CTRShortTimeMessage::showMessage(_STR(MSG_MODIFY_COUPLE_DESC));
}

//!< 커플정보 변경 처리가 실패했다.
void CTRNetEventHandler::onRecvCoupleModifyCoupleInfoFailed()
{
    DBG_OUTPUT("CTRNetEventHandler::onRecvCoupleModifyCoupleInfoFailed...");
}

//!< 커플이름 변경 처리가 성공했다.
void CTRNetEventHandler::onRecvCoupleModifyCoupleNameResult(eServerResult eResult, std::string strCoupleName)
{
	CTRCoupleSystem::getInstacne().onRecvCoupleModifyCoupleNameResult(eResult, strCoupleName);
}

//! 커플 삭제요청에 대한 응답을 받았다.
void CTRNetEventHandler::onRecvCoupleRemoveCoupleInfo(std::string strMateName)
{
	CTRCoupleSystem::getInstacne().onRecvCoupleRemoveCoupleInfo(strMateName);
}

//! 커플 삭제요청에 대한 실패응답을 받았다.
void CTRNetEventHandler::onRecvCoupleRemoveCoupleInfoFailed()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvCoupleRemoveCoupleInfoFailed...");
}

//! 상대방의 커플 정보를 받았다.
void CTRNetEventHandler::onRecvCoupleGetCoupleInfo(std::string strCoupleName, std::string strCoupleDesc, CoupleInfo & info, std::map<std::string, AvatarInfo> & mapCoupleAvatarInfo, bool bForTalesBook)
{
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		if (CTRUserBookDlg::getInstance().isVisible())
		{
			CTRUserBookDlg::getInstance().onRecvCoupleGetCoupleInfo(strCoupleName, strCoupleDesc, info, mapCoupleAvatarInfo);
		}
		else
		{
			CTRRankUI::getInstance().onRecvCoupleGetCoupleInfo(strCoupleName, strCoupleDesc, info, mapCoupleAvatarInfo, bForTalesBook);
		}
	}
}

//! 상대방의 커플 정보를 받는데 실패햇다.
void CTRNetEventHandler::onRecvCoupleGetCoupleInfoFailed()
{
	CTRUserBookDlg::getInstance().onRecvCoupleGetCoupleInfoFailed();
}

//! 나의 커플 정보를 갱신 받았다.
void CTRNetEventHandler::onRecvCoupleUpdateCoupleInfo(const CoupleInfo & conpleInfo)
{
	CTRCoupleSystem::getInstacne().onRecvCoupleUpdateCoupleInfo(conpleInfo);
	CTRUserBookDlg::getInstance().onRecvCoupleUpdateCoupleInfo(conpleInfo);
}

//! 나의 커플 정보를 갱신 받는데 실패했다.
void CTRNetEventHandler::onRecvCoupleUpdateCoupleInfoFailed()
{
    DBG_OUTPUT("CTRNetEventHandler::onRecvCoupleUpdateCoupleInfoFailed...");
}

// 커플시스템 관련 끝..
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 가족 시스템

//! 가족의 정보를 받는다.
void CTRNetEventHandler::onRecvFamilyGetFamilyInfo(const std::map<eFAMILY_UNIT_TYPE, const std::map<std::string, FamilyUnitInfo> > familyInfoList, std::string strNickName, int iParentsCoupleNum, int iMyCoupleNum, eCoupleType eMyCoupleType)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFamilyGetFamilyInfo...");
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRUserBookDlg::getInstance().showFamilyInfoDlg(familyInfoList, strNickName, iParentsCoupleNum, iMyCoupleNum, eMyCoupleType);
	}
}

//! 가족의 정보를 받는데 실패했다.
void CTRNetEventHandler::onRecvFamilyGetFamilyInfoFailed(eServerResult failedReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFamilyGetFamilyInfoFailed...");
}

//! 가족 맺기 가능한지 체크 요청에 대한 성공 메시지를 받았다.
void CTRNetEventHandler::onRecvFamilyCheckProposeCondition(std::string strNickName, bool bParents)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFamilyCheckProposeCondition...");
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRShortTimeMessage::showMessage(_STR(FAMILY_MSG_FAMILY_PROPOSE_WAIT), 1.5f);
	}
}
//! 가족 맺기 가능한지 체크 요청에 대한 실패 메시지를 받았다.
void CTRNetEventHandler::onRecvFamilyCheckProposeConditionFailed(eServerResult failedReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFamilyCheckProposeConditionFailed...%d", failedReason);

	if (!CTRNetPlayManager::getInstance().isGameStateNoGame()) return;

	string msg;
	switch(failedReason)
	{
	case eServerResult_FAMILY_CHECK_CONDITION_FULL_CHILD:
		//!< 자식을 더이상 추가 할 수 없다.
		msg = _STR(FAMILY_MSG_FULL_CHILD);
		break;
	case eServerResult_FAMILY_CHECK_CONDITION_I_AM_NOT_MARRIED:
		//!< 내가 결혼을 안해서 자식을 추가할 수 없다.
		msg = _STR(FAMILY_MSG_FAILED_ADD_CHILD_NOTMARRIED);
		break;
	case eServerResult_FAMILY_CHECK_CONDITION_TARGET_IS_NOT_MARRIED:
		//!< 상대가 결혼을 안해서 자식을 추가할 수 없다.
		msg = _STR(FAMILY_MSG_TARGET_NOT_MARRIED);
		break;
	case eServerResult_FAMILY_CHECK_CONDITION_ALREADY_CONNECTED_BY_CHILD:
		//!< 나는 이미 부모를 갖고 있다.
		msg = _STR(FAMILY_MSG_FAILED_AREADY_HAS_PARENT);
		break;
	case eServerResult_FAMILY_CHECK_CONDITION_ALREADY_CONNECTED_WITH_ANOTHER:
		//!< 상대는 이미 부모를 갖고 있다.
		msg = _STR(FAMILY_MSG_FAILED_AREADY_HAS_PARENT);
		break;
	case eServerResult_FAMILY_CHECK_CONDITION_TABOO1:
		//!< 상대방이 이미 내 가족이다.
		msg = _STR(FAMILY_MSG_FAILED_IN_FAMILY_1);
		break;
	case eServerResult_FAMILY_CHECK_CONDITION_TABOO2:
		//!< 상대방의 커플이 내 가족이다.
		msg = _STR(FAMILY_MSG_FAILED_IN_FAMILY_2);
		break;
	case eServerResult_FAMILY_CHECK_CONDITION_TABOO3:
		//!< 내 커플이 상대방의 가족이다.
		msg = _STR(FAMILY_MSG_FAILED_IN_FAMILY_3);
		break;
	case eServerResult_FAMILY_DISSOLVE_FAMILY_INVALID_FAMILY_UNIT_TYPE:
		//!< 내가족에 없는 가족 구성 타입이다.	
		msg = _STR(FAMILY_MSG_FAILED_FAMILY_UNIT_TYPE);
		break;
	case eServerResult_FAMILY_DISSOLVE_FAMILY_INVALID_NICKNAME:
		//!< 내가족에 없는 닉네임이다.
		msg = _STR(FAILED_INVALID_NICKNAME);
		break;
	case eServerResult_FAMILY_DISSOLVE_FAMILY_I_AM_NOT_PARENTS:
		//!< 자신이 부모가 아닌데 자식을 끊으려고 한다.
		msg = _STR(FAMILY_MSG_FAILED_ERROR);
		break;
	case eServerResult_FAMILY_DISSOLVE_FAMILY_I_HAVE_NO_PARENTS:
		//!< 부모가 없는데 부모를 끊으려고 한다.
		msg = _STR(FAMILY_MSG_FAILED_ERROR);
		break;
	case eServerResult_FAMILY_DBFAILED_ACK:
	default:
		//!< 디비 에러
		msg = _STR(FAMILY_MSG_DB_FAILED_ERROR);
		break;
	}
	if(!msg.empty())
	{
		COkDialogEx::getInstance().showDialog(msg);
	}
}

//! 가족의 맺기에 성공했다.
void CTRNetEventHandler::onRecvFamilyMakeFamily(std::string strTargetNickName, const std::map<eFAMILY_UNIT_TYPE, const std::map<std::string, FamilyUnitInfo> > familyInfoList, std::string strMyNickName, int iParentsCoupleNum, int iMyCoupleNum, bool bParents, eCoupleType eMyCoupleType)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFamilyMakeFamily...");
	CTRUserBookDlg::getInstance().setFamilyinfo(familyInfoList, strMyNickName, iParentsCoupleNum, iMyCoupleNum, eMyCoupleType);
	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_FAMILY_PROPOSE_ITEM);

	//가족 맺기 성공
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		string msg;
		if(bParents)
		{
			msg = format(_STR(FAMILY_MSG_MAKE_PARENT_OK), strTargetNickName.c_str());
		}
		else
		{
			msg = format(_STR(FAMILY_MSG_MAKE_CHILD_OK), strTargetNickName.c_str());
		}
		COkDialogEx::getInstance().showDialog(msg,"gui\\Family\\FamilySuccess.gui", -1.f, false);
	}
	else
	{
		UserAlarmInfo info;
		info.alarmMsg = eALARM_MSG_FAMILY_LINKING;
		info.strExt = strTargetNickName;
		info.iExt1 = (int)bParents;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(info);
	}
	CNetClientManager::getInstance().community_sendFamilyMakeNotify(strTargetNickName, !bParents);
}

//! 가족의 맺기에 실패했다.
void CTRNetEventHandler::onRecvFamilyMakeFamilyFailed(std::string strNickName, eServerResult failedReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFamilyMakeFamilyFailed...");
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		COkDialogEx::getInstance().showDialog(_STR(FAMILY_MSG_FAILED_ADD_FAMILY));
	}

	CNetClientManager::getInstance().community_responseFamilyPropose(strNickName, false, eFamilyProposeReject_NONE, false);
}

//! 가족의 끊기에 성공했다.
void CTRNetEventHandler::onRecvFamilyDissolveFamily(std::string strTargetNickName, const std::map<eFAMILY_UNIT_TYPE, const std::map<std::string, FamilyUnitInfo> > familyInfoList, std::string strMyNickName, int iParentsCoupleNum, int iMyCoupleNum, bool bParents, eCoupleType eMyCoupleType)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFamilyDissolveFamily...");

	CTRUserBookDlg::getInstance().setFamilyinfo(familyInfoList, strMyNickName, iParentsCoupleNum, iMyCoupleNum, eMyCoupleType);

	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		COkDialogEx::getInstance().showDialog(_STR(FAMILY_MSG_BREAK_FAMILY_OK));
	}

	CNetClientManager::getInstance().community_requestFamilyBreakNotify(strTargetNickName, bParents);
}

//! 가족의 끊기에 실패했다.
void CTRNetEventHandler::onRecvFamilyDissolveFamilyFailed(eServerResult failedReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFamilyDissolveFamilyFailed...");
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		COkDialogEx::getInstance().showDialog(_STR(FAMILY_MSG_FAILED_BREAK_FAMILY));
	}
}


//////////////////////////////////////////////////////////////////////////
// 혼자달리기 관련 시작...

/// 게임을 시작하라는 허락을 받았다.
void CTRNetEventHandler::onRecvAloneRunStartGameOK( const int numMap )
{
	if(CGameManager::getInstance().isGameModePractice())
	{
		//CMissionMsgDispatcher::getInstance().reset();
		m_pNetPlay->startGame();
	}
	else
	{
		// 혼자달리기가 아닌데 이 메시지를 받으면 안된다.
		_ASSERTE(false);
	}
}

/// 그냥 끝났다.
void CTRNetEventHandler::onRecvAloneRunGoalInNormal( DWORD dwLapTime )
{
	DBG_DEMO_OUTPUT(60, "onRecvAloneRunGoalInNormal - dwLapTime : %lu", dwLapTime);

	const CGameMapDescInfo *pGameMapDescInfo = CGameManager::getInstance().getCurrentGameMapDesc();
	if(pGameMapDescInfo)
	{
		const int iMapID = static_cast<int>(pGameMapDescInfo->getMapID()._getIdentifierValue());

		CMissionMsgDispatcher &rMissionMsgDispatcher = CMissionMsgDispatcher::getInstance();
		rMissionMsgDispatcher.setConditionCheckValue_Int(eCHECK_VALUE_INT_GOALINE_MAP_ID, iMapID);
		rMissionMsgDispatcher.addMissionConditionEvent(eMissionConditionType_COMPLETE_RUN);
		rMissionMsgDispatcher.addMissionConditionEvent(eMissionConditionType_TIME_RECORD, dwLapTime);
		rMissionMsgDispatcher.checkCompleteCondition();

		DBG_DEMO_OUTPUT("CTRNetEventHandler::onRecvAloneRunGoalInNormal MapIndex=[%d]", iMapID);


		CMissionMsgDispatcher::getInstance().onRecvRoomResultForMissionCheckNotify();	///< 혼자달리기는 없기 때문에, 강제로 호출해준다.
		CMissionMsgDispatcher::getInstance().processEndGame();
	}
}

/// 이상한 랩 타임이다. 스피드핵을 썼을지도...
void CTRNetEventHandler::onRecvAloneRunGoalInFailedNotCorrectLapTime()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvAloneRunGoalInFailedNotCorrectLapTime...");
#ifdef TR_RELEASE_PROJECT
	CCommandManager::getInstance().postWindowCloseMessage();
#else
	COkDialogEx::getInstance().showDialog(_STR(ERR_HACKING_DETECTED));
#endif
	_ASSERTE(false);
}

/// 해킹툴 유저로 등록되어 있다.
void CTRNetEventHandler::onRecvAloneRunGoalInFailedHackingToolUser()
{
	CTRTutorialGameUI::getInstance().doExitGame();

	COkDialogEx::getInstance().showDialog(_STR(MSG_TIME_ATTACK_GOALIN_HACKING_TOOL_USER));

	if(!CGameManager::getInstance().isGameModePractice())
	{
		DBG_OUTPUT("CTRNetEventHandler::onRecvAloneRunGoalInFailedHackingToolUser Not TimeAttack Mode!!!");
	}
}

// 골인에 실패하였다
void CTRNetEventHandler::onRecvAloneRunGameOver()
{
	// TODO : 필요한 작업이 있다면 추가하도록..
	DBG_OUTPUT("%s", __FUNCTION__);
}
// 혼자달리기 관련 끝...
//////////////////////////////////////////////////////////////////////////

/// 상점에서 물건들 여러 개를 사는것이 성공했다.

void CTRNetEventHandler::onRecvShopBuyProductsTogetherSuccess(const std::vector <BuyingItemInfo> & successItemList, const std::map<__int64,int>& mapItemID, const std::map<int, int> & soldOutItemDesc, const std::vector<int>& discountCouponList)
{

	bool bStandbyPurchase = false;
	std::vector<BuyingItemInfo> vecFiltingSuccessList;
	for( size_t i = 0; i < successItemList.size(); ++i )
	{
		if( !successItemList[i].m_bStandbyPurchaseDicision )
		{
			vecFiltingSuccessList.push_back(successItemList[i]);
		}
		else
		{
			bStandbyPurchase = true;
		}
	}

	DBG_OUTPUT( DBG_TYPE_SYSTEM, "%s Item Buy State[%s]", __FUNCTION__, (!bStandbyPurchase ? "All Buy" : vecFiltingSuccessList.empty() ? "AllRefund" : "Mix") );

	std::map<__int64,int>::const_iterator iter;
	for (iter = mapItemID.begin(); iter != mapItemID.end(); ++iter)
	{
		DBG_OUTPUT("onRecvShopBuyProductsTogetherSuccess ID:%I64d, DescNum: %d", iter->first, iter->second);

		const CItemInfoNode * itemInfo = CClientItemList::getInstance().getItemInfo(iter->second);

	}

	if (!vecFiltingSuccessList.empty())
	{
		switch(CTRUserInterface::getInstance().getCurrentUIType())
		{
		case GUI_TYPE_SHU_ROOM:
#ifdef _SHU_SYSTEM_
			SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvShopBuyProductsTogetherSuccess(vecFiltingSuccessList,mapItemID);
#endif //_SHU_SYSTEM_
			break;
		default:
			{
#ifdef _SHOP_RENEWAL_
				CTRShopManager::getInstance().onRecvShopBuyProductsTogetherSuccess(vecFiltingSuccessList, mapItemID);
#endif
				CTRShopDlg::getInstance().onRecvShopBuyProductsTogetherSuccess(vecFiltingSuccessList, mapItemID);
				CTRMawooShopDlg::getInstance().onRecvShopBuyProductsTogetherSuccess(vecFiltingSuccessList, mapItemID);
				CTRGameParkUI::getInstance().onRecvShopBuyProductsTogetherSuccess(vecFiltingSuccessList,mapItemID,soldOutItemDesc);
				CTRAlchemistUI::getInstance().onRecvArinShopBuyProductsSuccess(soldOutItemDesc);
			}
		}


		for (size_t i = 0;  i< discountCouponList.size(); ++i){
			CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(discountCouponList[i]);
		}
	}
	else
	{	
		COkDialogEx::getInstance().showDialog( _STR(ITEM_BUY_OK) );
#ifdef _SHOP_RENEWAL_
		CTRShopManager::getInstance().RemoveBuyDialog();
#endif
		CTRShopBuyAllDialog::getInstance().closeDialog();
		CNetClientManager::getInstance().requestCurrentTR();

#ifdef _BILLING_CASHINFO_RESPONSE	
		CNetClientManager::getInstance().requestCashBalanceResponseInfo();
#else	
#ifdef _BILLING_CHANNELING_PLAYNET
		CNetClientManager::getInstance().requestCashBalance(true);
#else
		CNetClientManager::getInstance().requestCashBalance();
#endif
#endif
	}

	if(bStandbyPurchase) CTRMyRoomGiftDialog::getInstance().updateOutBox();

#ifdef PROMOTION_SALE
	CTRSalePromotionPopup::getInstance().onRecvShopBuyProductsTogetherSuccess();
#endif
}

/// 상점에서 물건들 어려개를 사는 것이 실패했다.
void CTRNetEventHandler::onRecvShopBuyProductsTogetherFailed(const eShopFailed_REASON failedReason, const std::vector < BuyingItemInfo > & successItemList, const std::vector < BuyingItemInfo > & failedItemList, const std::map<__int64,int>& mapItemID, const std::map<int, int> & soldOutItemDesc)
{
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvShopBuyProductsTogetherFailed(failedReason, successItemList, failedItemList);
#endif
	CTRShopDlg::getInstance().onRecvShopBuyProductsTogetherFailed(failedReason, successItemList, failedItemList);	
	CTRMawooShopDlg::getInstance().onRecvShopBuyProductsTogetherFailed(failedReason, successItemList, failedItemList);	
	CTRGameParkUI::getInstance().onRecvShopBuyProductsTogetherFailed(failedReason, successItemList, failedItemList);
	CTRAlchemistUI::getInstance().onRecvShopBuyProductsTogetherFailed(failedReason, successItemList, failedItemList);
}

/// 상점에서 캐시를 받았다.
void CTRNetEventHandler::onRecvShopCash(int iCash)
{
	CTRLobbyUI::getInstance().onRecvShopCash(iCash);
	CTRGameParkUI::getInstance().onRecvShopCash(iCash);
	CTRFarmUI::getInstance().onRecvShopCash(iCash);
	CTRFarmShopUI::getInstance().onRecvShopCash(iCash);
	CTRFarmMyroomUI::getInstance().onRecvShopCash(iCash);
	CTRMyroomDlg::getInstance().onRecvShopCash(iCash);
	CTRShopDlg::getInstance().onRecvShopCash(iCash);
	CTRMyRoomUI::getInstance().onRecvShopCash(iCash);
	CTRShopUI::getInstance().onRecvShopCash(iCash);
	CTRAlchemistUI::getInstance().onRecvShopCash(iCash);
	CTRMawooShopDlg::getInstance().onRecvShopCash(iCash);
	CTRMawooShopUI::getInstance().onRecvShopCash(iCash);
#ifdef _SHOP_RENEWAL_
	CTRShopRenewalUI::getInstance().onRecvShopCash(iCash);
	CTRShopManager::getInstance().onRecvShopCash(iCash);
#endif
#ifdef _SHU_SYSTEM_
	SHU_SYSTEM::CTRShuUI_Management::getInstance().onRecvShopCash(iCash);
#endif
}

/// 상점에서 캐시를 받는데 실패했다.
void CTRNetEventHandler::onRecvShopCashFailed()
{
	CTRGameParkUI::getInstance().onRecvShopCashFailed();
	CTRFarmUI::getInstance().onRecvShopCashFailed();
	CTRFarmShopUI::getInstance().onRecvShopCashFailed();
	CTRFarmMyroomUI::getInstance().onRecvShopCashFailed();
	CTRMyRoomUI::getInstance().onRecvShopCashFailed();
	CTRShopUI::getInstance().onRecvShopCashFailed();
	CTRAlchemistUI::getInstance().onRecvShopCashFailed();
	CTRShortTimeMessage::showMessage(_STR(FAILED_GET_CASH), 1.5f);
	CTRMawooShopUI::getInstance().onRecvShopCashFailed();
#ifdef _SHOP_RENEWAL_
	CTRShopRenewalUI::getInstance().onRecvShopCashFailed();
	CTRShopManager::getInstance().onRecvShopCashFailed();
#endif
#ifdef _SHU_SYSTEM_
	SHU_SYSTEM::CTRShuUI_Management::getInstance().onRecvShopCashFailed();
#endif
}

/// 빌링 서버의 에러를 받았다.
void CTRNetEventHandler::onRecvBillingError(eBillingError billingError)
{
	TRDBG_OUTPUT_ERROR("%s Error[%d]", __FUNCTION__, billingError);

	string errMsg;

	switch(billingError)
	{
	case eBillingError_DBERROR :		///< DB 에러
		errMsg = _STR(MSG_BILLING_ERROR_DB_ERROR);
		break;
	case eBillingError_NOT_ENOUGH_CASH :		///< 잔액 부족
		errMsg = format("%s [%d]", _STR(MSG_BILLING_ERROR_NOT_ENOUGH_CASH), (int)billingError );
		break;
	case eBillingError_USER_ID_NO_EXIST	:		///< 유저 아이디 없음
		errMsg = _STR(MSG_BILLING_ERROR_USER_ID_NO_EXIST);
		break;
	case eBillingError_INVALID_BILLING_INFO	:		///< 내용 불일치
		errMsg = _STR(MSG_BILLING_ERROR_INVALID_BILLING_INFO);
		break;
	case eBillingError_BUY_FAIL	:		///< 구매 실패(내부 Exception 발생)
		errMsg = _STR(MSG_BILLING_ERROR_BUY_FAIL);
		break;
	case eBillingError_GIFT_AGE_ERROR :		///< 선물 나이 에러(음수 또는 NULL)
		errMsg = _STR(MSG_BILLING_ERROR_GIFT_AGE_ERROR); 
		break;
	case eBillingError_JUNIOR_CASH_GIFT_VIOLATION :		///< 14세 미만 선물 금지
		errMsg = _STR(MSG_BILLING_ERROR_JUNIOR_GIFT_VIOLATION);
		break;
	case eBillingError_GIFT_LIMMIT :		///< 선물한도 초과
		errMsg = _STR(MSG_BILLING_ERROR_GIFT_LIMMIT);
		break;
	case eBillingError_SYSTEM_EXCEPTION	:		///< 시스템 예외 사항 발생
		errMsg = _STR(MSG_BILLING_ERROR_SYSTEM_EXCEPTION);
		break;
	case eBillingError_BUY_LIMMIT :	///< 구매한도 초과
		errMsg = _STR(MSG_BILLING_ERROR_BUY_LIMMIT);
		break;
	case eBillingError_CASH_LOCK:	///< 사용자 캐시 잠금 기능 활성화(잠김)
		errMsg = _STR(MSG_BILLING_ERROR_CASH_LOCK);
		break;
	case eBillingError_USER_INFO_QUERY_ERROR :	///< 사용자 정보 조회중 오류
		errMsg = _STR(MSG_BILLING_ERROR_USER_INFO_QUERY_ERROR);
		break;
	case eBillingError_USER_INFO_NO_EXIST :	///< 존재하지 않는 사용자
		errMsg = _STR(MSG_BILLING_ERROR_USER_INFO_NO_EXIST);
		break;
	case eBillingError_GIFT_LIMMIT_CHECK_FAIL :	///< 선물한도 체크 실패
		errMsg = _STR(MSG_BILLING_ERROR_GIFT_LIMMIT_CHECK_FAIL);
		break;
	case eBillingError_UNKNOWN_ERROR :	///< 정의되지 않은 오류(결제불가 기타사유)
		errMsg = _STR(MSG_BILLING_ERROR_UNKNOWN_ERROR);
		break;
	case eBillingError_CONNECT_ERROR :	///< 결제 가능 여부 체크 오류(연결오류)
		errMsg = _STR(MSG_BILLING_ERROR_CONNECT_ERROR);
		break;
	case eBillingError_NOT_ENOUGH_CASH2 :	///< 잔액 부족2
		errMsg = format("%s [%d]", _STR(MSG_BILLING_ERROR_NOT_ENOUGH_CASH), (int)billingError );
		break;
	case eBillingError_USER_ID_NO_EXIST_FOR_GIFT :	///< 선물보낼때 넥슨에서 결제 성공후 페이레터에서 유저의 정보를 확인 할 수 없음
		errMsg = format("%s [%d]", _STR(FAILED_FARM_PORTAL_SET_NOT_EXIST_NICKNAME), (int)billingError );
		break;
	default:
		errMsg = format("%s [%d]", _STR(ITEM_BUY_BILLING_SERVER_FAILED), (int)billingError);
		break;
	}

	if (CTRShopGiftDialog::getInstance().isVisible())
	{
		CTRShopGiftDialog::getInstance().closeDialog();
	}

	COkDialogEx::getInstance().showDialog(errMsg,-10.f);
}

//--------------------------------------------아린의 연금 관련 이벤트 핸들러------------------------------------------------------------------------------------------

/// 강화 아이템 목록을 정상적으로 받았다. 
void CTRNetEventHandler::onRecvStrengthenItemListOK(const std::vector<CStrengthenItemDesc> & strengthens)
{
	DBG_OUTPUT("%s" , __FUNCTION__);
}

/// 강화 아이템 목록을 받던 도중 문제 발생.
void CTRNetEventHandler::onRecvStrengthenItemListFailed(eStrengthenItemListFailedReason failedReason)
{
	DBG_OUTPUT("%s", __FUNCTION__);
}

/// 아이템 강화를 성공했다. 
void CTRNetEventHandler::onRecvReInforceItemOK(const eStrengthenReInforceResponse response, const int & reInforcedItemNum, const unsigned short & reInforcedSlotIndex, const int & remainGameMoney, const int & remainReInforceCnt)
{
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(reInforcedItemNum);		
	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE,eFuncItemPosition_RECHARGE_REINFORCE_CHANCE);
	CNetClientManager::getInstance().requestCurrentTR();
	CTRMyroomDlg::getInstance().onRecvReInforceItemOK(response,reInforcedItemNum, reInforcedSlotIndex, remainGameMoney, remainReInforceCnt);
	CTRGameIndividualRecordManager::getInstance().onUpdateIndividualRecord(GAME_PLAY_INFO_ARIN_STRENGTHEN_COUNT);
}

/// 아이템 강화를 실패했다. 
void CTRNetEventHandler::onRecvReInforceItemFailed(const eStrengthenReInforceFailedReason & failedReason, const int & reInforceItemNum, const unsigned short & reInforceSlotIdx)
{
	CTRMyroomDlg::getInstance().onRecvReInforceItemFailed(failedReason, reInforceItemNum, reInforceSlotIdx);
}

/// 아이템 정화를 성공했다. 
void CTRNetEventHandler::onRecvPurifyItemOK(const int & purifiedItemNum, const unsigned short & purifySlotIndex, const int & usedItemDescNum, const unsigned short & remainPurifyItemCount)
{
	COkDialogEx::getInstance().showDialog(_STR(ARIN_ALCHEMIST_PURIFY_OK_MSG));
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(purifiedItemNum);	
	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE,eFuncItemPosition_PREMIUM_PURIFY_ITEM_SLOT);
	CNetClientManager::getInstance().requestCurrentTR();
	CTRMyroomDlg::getInstance().onRecvPurifyItemOK(purifiedItemNum, purifySlotIndex, usedItemDescNum, remainPurifyItemCount);
	CTRGameIndividualRecordManager::getInstance().onUpdateIndividualRecord(GAME_PLAY_INFO_ARIN_PURIFY_COUNT);
}

/// 아이템 정화를 실패했다.  
void CTRNetEventHandler::onRecvPurifyItemFailed(const eStrengthenPurifyFailedReason & failedReason, const int & purifyItemNum, const unsigned short & purifySlotIdx)
{
	CTRMyroomDlg::getInstance().onRecvPurifyItemFailed(failedReason, purifyItemNum, purifySlotIdx);
}

/// 아이템의 강화 횟수 충전을 성공했다. 
void CTRNetEventHandler::onRecvReChargeReInforceChanceOK(const int & rechargedItemNum, const unsigned short & refreshChanceCnt, const int & usedItemNum)
{
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(rechargedItemNum);		
	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE,eFuncItemPosition_RECHARGE_REINFORCE_CHANCE);
	CNetClientManager::getInstance().requestCurrentTR();
	CTRMyroomDlg::getInstance().onRecvReChargeReInforceChanceOK(rechargedItemNum, refreshChanceCnt, usedItemNum);
	CUseItemDlg::getInstance().onRecvReChargeReInforceChanceOK(rechargedItemNum, refreshChanceCnt, usedItemNum);
}

/// 아이템의 강화 횟수 충전을 실패했다. 
void CTRNetEventHandler::onRecvReChargeReInforceChanceFailed(const eStrengthenRechargeReInforceChanceFailedReason & failedReason, const unsigned int & rechargeItemNum, const unsigned int & usingItemNum)
{
	CTRMyroomDlg::getInstance().onRecvReChargeReInforceChanceFailed(failedReason, rechargeItemNum, usingItemNum);
	CUseItemDlg::getInstance().onRecvReChargeReInforceChanceFailed(failedReason, rechargeItemNum, usingItemNum);
}

/// 아이템의 슬롯 개수 증가를 성공했다. 
void CTRNetEventHandler::onRecvIncreaseSlotCountOK(const int & increasedItemNum, const unsigned short & refreshedSlotCnt, const int & usedItemNum)
{
	CUseItemDlg::getInstance().onRecvIncreaseSlotCountOK(increasedItemNum, refreshedSlotCnt , usedItemNum);	
}

/// 아이템의 슬롯 개수 증가를 실패했다. 
void CTRNetEventHandler::onRecvIncreaseSlotCountFailed(const eStrengthenIncreaseSlotCountFailedReason & failedReason, const int & increaseItemNum, const int & usingItemNum)
{
	CUseItemDlg::getInstance().onRecvIncreaseSlotCountFailed(failedReason, increaseItemNum, usingItemNum);	
}

/// 아이템의 특정 슬롯 특화계열 정보변경을 성공했다. 
void CTRNetEventHandler::onRecvChangeSlotSpecializedTypeOK(const int & changedItemNum, const unsigned short & changedSlotIdx, const unsigned short & refreshedType, const int & usedItemNum)
{
	CTRMyroomDlg::getInstance().onRecvChangeSlotSpecializedTypeOK(changedItemNum, changedSlotIdx, refreshedType, usedItemNum);
	CUseItemDlg::getInstance().closeUI();
}

/// 아이템의 특정 슬롯 특화계열 정보변경을 실패했다. 
void CTRNetEventHandler::onRecvChangeSlotSpecializedTypeFailed(const eStrengthenChangeSlotSpecializedTypeFailedReason & failedReason, const unsigned int & targetItemNum, const int & usingItemNum)
{
	CTRMyroomDlg::getInstance().onRecvChangeSlotSpecializedTypeFailed(failedReason, targetItemNum, usingItemNum);
	CUseItemDlg::getInstance().closeUI();
}
/// 무료 망치 정보를 얻거나 무료 망치를 갖는다.
void CTRNetEventHandler::onRecvGetFreeHammer(const eItemStrengthenGetFreeHammerType & type, const byte & bAcquisitionCount, const byte & bRemainingCount, const byte & bPossessionCount, time_type & lastAcquisitionTime )
{
	CTRGameParkUI::getInstance().onRecvGetFreeHammer(type, bAcquisitionCount, bRemainingCount, bPossessionCount, lastAcquisitionTime );

	if(type == eItemStrengthenGetFreeHammerType_ITEM)
	{
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_GUI_EVENT, static_cast<int>(eMissionConditionGUIEventType_GET_STRENGTHEN_ITEM));
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();

		const CItemInfoNode * pItem = CClientItemList::getInstance().getItemInfo(ItemKeyInfo(eCharacterKind_NONE,eFuncItemPosition_RECHARGE_REINFORCE_CHANCE,2));
		if(pItem)
			CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(pItem->m_iUniqueNumber);
	}
}
/// 무료 망치 정보를 얻거나 무료 망치를 갖지 못하였다.
void CTRNetEventHandler::onRecvGetFreeHammerFailed(const eItemStrengthenGetFreeHammerType & type, const eItemStrengthenGetFreeHammerFailedReason & failedReason )
{
	CTRGameParkUI::getInstance().onRecvGetFreeHammerFailed(type, failedReason );
}


/// 아린의 연금상점의 판매 물품을 받았다.
void CTRNetEventHandler::onRecvPremiumArinShopItemListOK(const std::map<int, ArinShopItemInfo> & itemTable)
{	
	CTRAlchemistUI::getInstance().onRecvPremiumArinShopItemListOK(itemTable);	
	CTRGameParkUI::getInstance().onRecvPremiumArinShopItemListOK(itemTable);	
}

/// 아린의 연금상점의 판매 물품을 받지 못했다. 
void CTRNetEventHandler::onRecvPremiumArinShopItemListFailed(const ePremiumArinShopItemListFailedReason & failedReason)
{	
	if(failedReason == ePremiumArinShopItemListFailedReason_DB_PROBLEM)
	{
		CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_DB_ERROR));
	}
	else if(failedReason == ePremiumArinShopItemListFailedReason_NOT_EXIST_SELLING_LIST)
	{
		CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_NOT_EXIST_SELLING_LIST));
	}
	TRDBG_OUTPUT_ERROR("%s - reason (%d)", __FUNCTION__, failedReason);
}

/// 아이템 변형 요청에 성공했다.
void CTRNetEventHandler::onRecvTransformItemOK(cpk_type iCharacter, cpk_type iPosition, cpk_type iTransKind, int iTransItemNum)
{
	CNetClientManager::getInstance().requestUserItemAttr(); //! 아이템능력치를 요청한다.

	const ClientTransformItem * pTransformInfo = CClientItemList::getInstance().getTransformItemInfo(ItemQuery(iCharacter,iPosition,iTransKind));

	if (pTransformInfo != NULL)
	{
		const CItemInfoNode * pOrgItemInfo = CClientItemList::getInstance().getItemInfo(ItemKeyInfo(pTransformInfo->m_iCharacter,pTransformInfo->m_iPosition,pTransformInfo->m_iOriginKind));

		if (pOrgItemInfo != NULL)
		{
			std::string strMsg = "";

			switch(pTransformInfo->m_transformType)
			{
			case eItemTransformType_COLORING:
				{
					strMsg = format(_STR(TRANSFORM_OK_INFO),pOrgItemInfo->m_name.c_str(),pTransformInfo->m_strDetail.c_str());
					COkDialogEx::getInstance().showDialog(strMsg);
				}
				break;
			case eItemTransformType_UPGRADE:
				{
					strMsg = format(_STR(TRANSFORM_UP_OK_INFO),pOrgItemInfo->m_name.c_str(),pTransformInfo->m_strDetail.c_str());
					COkDialogExItem2::getInstance().showDialog(strMsg, pOrgItemInfo->m_iUniqueNumber, "alchemist\\Upgrade_Success3.gui", -1.f, iTransKind, false);
				}
				break;
			}
		}
	}
	else
	{
		const CItemInfoNode * pOrgItemInfo = CClientItemList::getInstance().getItemInfo(ItemKeyInfo(iCharacter,iPosition,iTransKind));
		if(pOrgItemInfo)
		{	
			string strMsg = format(_STR(ARIN_ALCHEMIST_SUCCESS_CHANGE_ORIGINAL_COLOR), pOrgItemInfo->m_name.c_str());
			COkDialogEx::getInstance().showDialog(strMsg);
			CUseItemDlg::getInstance().closeUI();
		}
	}

	const CItemInfoNode * pTransformItem = CClientItemList::getInstance().getItemInfo(iTransItemNum);
	if (pTransformItem == NULL) return;

	CKeepItemList::getInstance().eraseItem(pTransformItem);
	if ( CTRMyRoomGoodsListDialog::getInstance().isVisible() )
		CTRMyRoomGoodsListDialog::getInstance().onUpdateGoodsList();
}

/// 아이템 변형 요청에 실패했다.
void CTRNetEventHandler::onRecvTransformItemFailed(eItemTransformFailedReason eReason)
{
	std::string strFailedMsg = "";
	switch(eReason)
	{
	case eItemTransformFailedReason_NO_TRANSFORM_ITEM:		 // 변형 아이템을 갖고 있지 않음.
		strFailedMsg = _STR(TRANSFORM_NO_TRANSFORM_ITEM);
		break;
	case eItemTransformFailedReason_ITEM_DELETE_ERROR:		// 변형 아이템 삭제중 오류.
		strFailedMsg = _STR(TRANSFORM_ITEM_DELETE_ERROR);
		break;
	case eItemTransformFailedReason_INVALID_TRANSFORM_INFO: // 변형 정보가 올바르지 않음.
		strFailedMsg = _STR(TRANSFORM_INVALID_TRANSFORM_INFO);
		break;
	case eItemTransformFailedReason_INVALID_TRANSFORM_ITEM: // 변형 아이템 정보가 올바르지 않음.
		strFailedMsg = _STR(TRANSFORM_INVALID_TRANSFORM_ITEM);
		break;
	case eItemTransformFailedReason_NO_TARGET_ITEM:			 // 변형 대상 아이템을 갖고 있지 않음.
	case eItemTransformFailedReason_DB_ERROR:				// DB 에러.
		strFailedMsg =_STR(FAILED_DB_ERROR);
		break;
	case eItemTransformFailedReason_TARGET_ITEM_IS_EXPIRED: //! 내구도가 없다.
		strFailedMsg =_STR(ALCHEMIST_MIX_ERR_ENOUGH_UNCONSUMED_ITEM);
		break;
	case eItemTransformFailedReason_TARGET_ITEM_IS_ALREADY_TRANSFORMED: // 변형 대상 아이템이 이미 같은 것으로 변경 되었음.
		strFailedMsg = _STR(TRANSFORM_ALREADY_APPLY_THIS_ITEM);
		break;
	case eItemTransformFailedReason_TARGET_ITEM_IS_ALREADY_UPGRADED:
		strFailedMsg = _STR(TRANSFORM_UP_ALREADY_APPLY_THIS_ITEM);
		break;
	default:
	case eItemTransformFailedReason_UNKNOWN_ERROR:			// 알수 없는 에러.
		strFailedMsg = _STR(ERR_UNKNOWN);
		break;
	}
	DBG_OUTPUT("CTRNetEventHandler::onRecvTransformItemFailed %s", strFailedMsg.c_str());

	CTRShortTimeMessage::getInstance().showMessage(strFailedMsg,3.f);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// 기념 대상 오브젝트에 특정 행위에 대한 성공 응답을 받았다.
void CTRNetEventHandler::onRecvAnniversaryObjectActionOK(const AnniversaryObjectAction & objectAction, AnniversaryAction action)
{
	if (CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvAnniversaryObjectActionOK(objectAction, action);
	}
	DBG_OUTPUT("%s[%d]",__FUNCTION__,objectAction.m_iObjectNum);
}

/// 기념 대상 오브젝트에 특정 행위에 대한 실패 응답을 받았다.
void CTRNetEventHandler::onRecvAnniversaryObjectActionFailed(int iObjectNum)
{
	DBG_OUTPUT("%s[%d]",__FUNCTION__,iObjectNum);
	if (iObjectNum == eParkFreelyGiveTreeTypeGrowth_Garaetteok)
	{
		CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_ANNIVERSARY_OBJECT_ACTION), 2.f);
	}
}

/// 기념 대상 오브젝트의 값을 받았다.
void CTRNetEventHandler::onRecvAnniversaryObjectValueOK(std::map<int,int> objectValueMap)
{
	for (std::map<int,int>::iterator iter = objectValueMap.begin(); iter != objectValueMap.end(); ++iter)
	{
		DBG_OUTPUT("%s[%d]=[%d]",__FUNCTION__,iter->first,iter->second);
	}

	if (CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvAnniversaryObjectValueOK(objectValueMap, 0);
	}	
}

/// 기념 대상 오브젝트의 값을 받았다. INT64
void CTRNetEventHandler::onRecvAnniversaryObjectValueOK64(std::map<int, __int64> objectValueMap)
{
	for (std::map<int, INT64>::iterator iter = objectValueMap.begin(); iter != objectValueMap.end(); ++iter)
	{
		DBG_DEMO_OUTPUT("%s[%d]=[%I64d]",__FUNCTION__,iter->first,iter->second);
	}

	if (CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvAnniversaryObjectValueOK64(objectValueMap, 0);
	}	
}

/// 기념 대상 오브젝트의 값 받기에 실패했다.
void CTRNetEventHandler::onRecvAnniversaryObjectValueFailed(std::map<int,int> objectValueMap)
{
	std::map<int,int>::iterator iter = objectValueMap.begin();
	for (; iter != objectValueMap.end();++iter)
	{
		TRDBG_OUTPUT_ERROR("%s[%d]",__FUNCTION__,iter->first);
	}
}

void CTRNetEventHandler::onRecvAnniversaryObjectValueFailed64(std::map<int,__int64> objectValueMap)
{
	std::map<int,__int64>::iterator iter = objectValueMap.begin();
	for (; iter != objectValueMap.end();++iter)
	{
		TRDBG_OUTPUT_ERROR("%s[%I64d]",__FUNCTION__,iter->first);
	}
}

/// 기념 대상 오브젝트의 유저 정보를 받았다.
void CTRNetEventHandler::onRecvAnniversaryGetUserInfo(int objectNum, int iRank, int value)
{
	if (CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvAnniversaryGetUserInfo(objectNum, iRank, value);
	}
}

/// 기념 대상 오브젝트에 값이 추가되었다.
void CTRNetEventHandler::onRecvAnniversaryAddObjectValueOK(const AnniversaryObjectAction & objectAction, int iValue)
{
	DBG_OUTPUT("%s[%d]=[%d]",__FUNCTION__,objectAction.m_iObjectNum,iValue);

	std::map<int,int> MapobjectValue;
	MapobjectValue.insert(make_pair(objectAction.m_iObjectNum,iValue));

	if (CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvAnniversaryObjectValueOK(MapobjectValue, objectAction.m_iActionNum);
	}
}

/// 기념 대상 오브젝트에 값이 추가되었다. INT64
void CTRNetEventHandler::onRecvAnniversaryAddObjectValueOK64(const AnniversaryObjectAction & objectAction, __int64 iValue)
{
	DBG_OUTPUT("%s[%d]=[%I64d]",__FUNCTION__,objectAction.m_iObjectNum,iValue);

	std::map<int, INT64> MapobjectValue;
	MapobjectValue.insert(make_pair(objectAction.m_iObjectNum, iValue));

	if (CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvAnniversaryObjectValueOK64(MapobjectValue, objectAction.m_iActionNum);
	}
}

/// 기념 대상 오브젝트에 값이 감소되었다.
void CTRNetEventHandler::onRecvAnniversarySubstractObjectValueOK(const AnniversaryObjectAction & objectAction, int iValue)
{
	std::map<int,int> MapobjectValue;
	MapobjectValue.insert(make_pair(objectAction.m_iObjectNum,iValue));

	if (CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvAnniversaryObjectValueOK(MapobjectValue, objectAction.m_iActionNum);
	}
}

void CTRNetEventHandler::onRecvAnniversarySubstractObjectValueOK64(const AnniversaryObjectAction & objectAction, __int64 iValue)
{
	std::map<int,__int64> MapobjectValue;
	MapobjectValue.insert(make_pair(objectAction.m_iObjectNum,iValue));

	if (CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvAnniversaryObjectValueOK64(MapobjectValue, objectAction.m_iActionNum);
	}
}


/// 기념 대상 오브젝트에 값이 감소실패되었다.
void CTRNetEventHandler::onRecvAnniversarySubstractObjectValueFailed(ePieroOlympicFailedReason eReason)
{
	CTREventSportsManager::ePieroOlympicType type = CTREventSportsManager::getInstance().getEventSportsType();
	string str = _STR(FAILED_CANNOT_INTURRUPT_GROWTH);

	if(type == CTREventSportsManager::ePieroOlympic_New)
	{
		str = _STR(FAILED_CANNOT_INTURRUPT_PURIFY);
	}
	else if(type == CTREventSportsManager::ePieroOlympic_LoveBattle2)
	{
		str = _STR(FAILED_CANNOT_USE_MOLE_FEED);
	}
	
	CTRShortTimeMessage::getInstance().showMessage(str);
	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_TREE_INTERRUPT_ITEM);
}

// 기념 대상 오브젝트로 부터 받은 보상 단계 리스트를 받았다.
void CTRNetEventHandler::onRecvAnniversaryGetReveivedRewardGradeList(int iObjectNum, __int64 iValue, std::vector<BYTE> grades)
{
	CTRGameParkUI::getInstance().onRecvAnniversaryGetReveivedRewardGradeList(iObjectNum, iValue, grades);
}

// 기념 대상 오브젝트로 부터 해당 등급의 보상을 받았다.
void CTRNetEventHandler::onRecvAnniversaryReceiveReward(eAnniversaryActionResult result, const RewardInfo& reward)
{
	CTRGameParkUI::getInstance().onRecvAnniversaryReceiveReward(result, reward);
}
#ifdef _DUCTILITY_SYSTEM_

// 연성시스템 오브젝트에 특정 행위에 대한 응답을 받았다.
void CTRNetEventHandler::onRecvDuctilityObjectActionOK(const AnniversaryObjectAction & objectAction, DuctilityAction action)
{
	//!< 사용한 아이템 갱신을 해준다.
	if (CClientItemList::getInstance().getItemInfo(action.m_iValue) != NULL)
	{	
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(action.m_iValue);
	}
}

// 연성 시스템 대상 오브젝트의 회차별 보상을 받았다.
void CTRNetEventHandler::onRecvDuctilityObjectStepReward(eDuctilityResult result, int iObjectNum, int iStepNum, RewardInfo& rewardInfo)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvDuctilityObjectStepReward(iObjectNum, rewardInfo);
	}	
}

// 연성 시스템 연성 후 조건 보상을 받았다.
void CTRNetEventHandler::onRecvDuctilityConditionRewardList(eDuctilityResult result, int iConditionNum, std::vector<RewardInfo>& rewardList)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvDuctilityConditionRewardList(rewardList);
	}
}
#endif

#ifdef _TREASURE_HUNT

// 보물찾기 시스템이 시작되엇다.
void CTRNetEventHandler::onRecvTreasureHuntStart()
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntStart();
}

// 보물찾기 시스템이 끝났다.
void CTRNetEventHandler::onRecvTreasureHuntEnd()
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntEnd();
}

// 보물찾기 시작 정보를 받았다.
void CTRNetEventHandler::onRecvTreasureHuntStartInfo(time_type tStartTime, bool bStart, int iEndTime, int iFreePlayCount, int iTicketPlayCount)
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntStartInfo(tStartTime,bStart,iEndTime,iFreePlayCount,iTicketPlayCount);
}

// 주기적으로 보내주는 보물찾기 정보를 받았다.
void CTRNetEventHandler::onRecvTreasureHuntInfo(int iFullCount, int iCurrCount, eTreasure_Boost_Level eBoostLevel)
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntInfo(iFullCount,iCurrCount,(eTreasure_Boost_Level)eBoostLevel);
}

// 보물찾기 시스템에서 부스트가 발동되었다.
void CTRNetEventHandler::onRecvTreasureHuntBoost(int iFullCount, int iCurrCount, eTreasure_Boost_Level eBoostLevel)
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntBoost(iFullCount,iCurrCount,(eTreasure_Boost_Level)eBoostLevel);
}

// 패스워드에 대한 응답을 받았다.
void CTRNetEventHandler::onRecvTreasureHuntPasswordAck(eTreasure_BOXACT eBoxAct, Treasure_Box sTreasureBox, int iPassword)
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntPasswordAck((eTreasure_BOXACT)eBoxAct,sTreasureBox,iPassword);
}

// 보물이 삭제되었다.
void CTRNetEventHandler::onRecvTreasureHuntDelete(Treasure_Box sTreasureBox)
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntDelete(sTreasureBox);
}

// 보물을 찾았다.
void CTRNetEventHandler::onRecvTreasureHuntFindAck(eTreasure_BOXACT eBoxAct, Treasure_Box sTreasureBox, int itemNum)
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntFindAck((eTreasure_BOXACT)eBoxAct, sTreasureBox, itemNum);
}

// 보물을 찾지 못했다.
void CTRNetEventHandler::onRecvTreasureHuntFindFailed()
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntFailed(TreasureHunt::eTreasureHuntFail_ALREDY_FIND);
}

// 보물상자에 대한 데이터를 받았다.
void CTRNetEventHandler::onRecvTreasureHuntBoxData(std::map<int, Tower_BoxData>& boxList)
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntBoxData(boxList);
}

// 보물찾기에 참가하였다.
void CTRNetEventHandler::onRecvTreasureHuntEnterAck(bool bUsetTicket, bool bReEnter)
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntEnterAck(bUsetTicket,bReEnter);
}

// 보물찾기 참가에 실패했다.
void CTRNetEventHandler::onRecvTreasureHuntEnterFailed(eTreasure_Result JoinResult)
{
	switch(JoinResult)
	{
	case eTreasure_Result_Failed_Unknown:
		TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntFailed(TreasureHunt::eTreasureHuntFail_UNKNOWN);
		break;
	case eTreasure_Result_Failed_Not_EventTime:
		TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntFailed(TreasureHunt::eTreasureHuntFail_NOT_EVENT_TIME);
		break;
	case eTreasure_Result_Failed_Cannot_joint_today_Anymore:
		TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntFailed(TreasureHunt::eTreasureHuntFail_CANNOT_JOINT_TODAY);
		break;
	case eTreasure_Result_Failed_not_Have_Ticket:
		TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntFailed(TreasureHunt::eTreasureHuntFail_NOT_HAVE_TICKET);
		break;
	}
}

// 보물찾기를 포기했다.
void CTRNetEventHandler::onRecvTreasureHuntGiveUpAck()
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntGiveUpAck();
}

// 보물찾기 포기에 실패했다.
void CTRNetEventHandler::onRecvTreasureHuntGiveUpFailed()
{
	TreasureHunt::CTRTreasureHuntManager::getInstance().onRecvTreasureHuntFailed(TreasureHunt::eTreasureHuntFail_NOT_ENTER_EVENT);
}
#endif

// 통합 보상을 받았다.
void CTRNetEventHandler::onRecvInegratedRewardGiveRewardOK(std::vector<IntegratedReward> rewardList, const AnniversaryObjectAction & objectAction)
{
	if (CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvInegratedRewardGiveRewardOK(rewardList, objectAction);
	}

	vector<RewardInfo> vecRewardInfoList;
	for (size_t i = 0; i < rewardList.size(); ++i)
	{
		RewardInfo info;
		info.eRewardType = static_cast<eRewardCondition>(rewardList[i].m_eRewardCondition);
		info.iRewardID = rewardList[i].m_iRewardItem;
		info.iRewardCount = rewardList[i].m_iRewardCount;
		vecRewardInfoList.push_back(info);
		DBG_DEMO_OUTPUT("%s - item num=[%d], count=[%d], type=[%d]", __FUNCTION__, info.iRewardID, info.iRewardCount, info.eRewardType);
	}
	CTRRewardManager::getInstance().getReward(vecRewardInfoList, true);

	DBG_OUTPUT("%s[%d]",__FUNCTION__,rewardList.size());
}

#ifdef _ONEDAY_BUFF_SYSTEM_

void CTRNetEventHandler::onRecvOneDayBuffLevelUP(const std::vector<RewardInfo>& rewardList, const OneDayBuffData& buffData, eOneDayBuff_Result result)
{
#ifdef _EVENTPAGE_RENEWAL_
	if(result == eOneDayBuff_Result_OK)
	{
		time_type curTime = CServerTime::getInstance().getCurrentTime();
		CTRNetPlayManager::getInstance().setOneDayBuffLimitTime(curTime + ((time_type)(buffData.m_tLimitTime * 1000 + 15000)));
	}
#endif
	CTRLobbyUI::getInstance().onRecvOneDayBuffLevelUP(rewardList, buffData, result);
}

void CTRNetEventHandler::onRecvOneDayBuffStartNotify(const OneDayBuffData& buffData)
{
#ifdef _EVENTPAGE_RENEWAL_
	time_type curTime = CServerTime::getInstance().getCurrentTime();
	CTRNetPlayManager::getInstance().setOneDayBuffLimitTime(curTime + ((time_type)(buffData.m_tLimitTime * 1000 + 15000)));
#endif
	CTRNetPlayManager::getInstance().setNotTimeOneDayBuff(false);
	CTRLobbyUI::getInstance().onRecvOneDayBuffStartNotify(buffData);
}

void CTRNetEventHandler::onRecvOneDayBuffFinishNotify(const OneDayBuffData& buffData)
{
#ifdef _EVENTPAGE_RENEWAL_
	time_type curTime = CServerTime::getInstance().getCurrentTime();
	CTRNetPlayManager::getInstance().setOneDayBuffLimitTime(curTime + ((time_type)(buffData.m_tLimitTime * 1000 + 15000)));
#endif
	CTRNetPlayManager::getInstance().setNotTimeOneDayBuff(true);
	CTRLobbyUI::getInstance().onRecvOneDayBuffFinishNotify(buffData);
}
#endif

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
/// 비밀번호 존재 여부에 대한 정보를 받았음.
void CTRNetEventHandler::onRecvIsExistConfirmationPasswordOK(bool bIsExistConfirmationPassword)
{

}

/// 비밀번호 존재 여부에 대한 정보를 받기 실패했음.
void CTRNetEventHandler::onRecvIsExistConfirmationPasswordFailed(eServer_IS_EXIST_CONFIRMATION_PASSWORD_FAILED_REASON eFailedReason)
{
#ifdef TR_CONFIRMATION_PASSWORDCHECK
	string msg;
	switch(eFailedReason)
	{
	case eServer_IS_EXIST_CONFIRMATION_PASSWORD_FAILED_REASON_DB_ERROR:			///< DB 에러
		msg = _STR(FAILED_CONFIRMATION_PASSWORD_DB_ERROR);
		break;
	}

	CTRShortTimeMessage::showMessage(msg);
	DBG_OUTPUT("CTRNetEventHandler::onRecvIsExistConfirmationPasswordFailed %s", msg.c_str());
#endif //TR_CONFIRMATION_PASSWORDCHECK
}

/// 비밀번호 셋팅을 성공했음.
void CTRNetEventHandler::onRecvSetConfirmationPasswordOK()
{
#ifdef TR_CONFIRMATION_PASSWORDCHECK
	CTRUserBookDlg::getInstance().onRecvSetConfirmationPasswordOK();
#endif //TR_CONFIRMATION_PASSWORDCHECK
}

/// 비밀번호 셋팅을 실패했음.
void CTRNetEventHandler::onRecvSetConfirmationPasswordFailed(eServer_SET_CONFIRMATION_PASSWORD_FAILED_REASON eFailedReason)
{
#ifdef TR_CONFIRMATION_PASSWORDCHECK
	string msg;
	switch(eFailedReason)
	{
	case eServer_SET_CONFIRMATION_PASSWORD_FAILED_REASON_DB_ERROR:					///< DB 에러
		msg = _STR(FAILED_SET_CONFIRMATION_PASSWORD_DB_ERROR);
		break;
	case eServer_SET_CONFIRMATION_PASSWORD_FAILED_REASON_INCORRECT_PASSWORD:		///< 비번이 틀렸음
		msg = _STR(INCORRECT_PASSWORD);
		break;
	case eServer_SET_CONFIRMATION_PASSWORD_FAILED_REASON_TOO_SHORT_PASSWORD:		///< 비번이 짧음
		msg = _STR(FAILED_SET_CONFIRMATION_SHORT_PASSWORD);
		break;
	case eServer_SET_CONFIRMATION_PASSWORD_FAILED_REASON_TOO_LONG_PASSWORD:			///< 비번이 긺
		msg = _STR(FAILED_SET_CONFIRMATION_LONG_PASSWORD);
		break;
	case eServer_SET_CONFIRMATION_PASSWORD_FAILED_REASON_EXIST_SPACE_IN_PASSWORD:	///< 비번에 공백이 있음
		msg = _STR(FAILED_SET_CONFIRMATION_EXIST_SPACE_IN_PASSWORD);
		break;
	}

	CTRShortTimeMessage::showMessage(msg);
	CTRUserBookDlg::getInstance().onRecvSetConfirmationPasswordFailed();
	DBG_OUTPUT("CTRNetEventHandler::onRecvSetConfirmationPasswordFailed %s", msg.c_str());
#endif //TR_CONFIRMATION_PASSWORDCHECK
}

/// 비밀번호 체크를 성공했음.
void CTRNetEventHandler::onRecvCheckConfirmationPasswordOK()
{
#ifdef TR_CONFIRMATION_PASSWORDCHECK
	CTRConfirmationPasswordCheckDlg::getInstance().onRecvCheckConfirmationPasswordOK();
#endif //TR_CONFIRMATION_PASSWORDCHECK
}

/// 비밀번호 체크를 실패했음.
void CTRNetEventHandler::onRecvCheckConfirmationPasswordFailed(eServer_CHECK_CONFIRMATION_PASSWORD_FAILED_REASON eFailedReason)
{
#ifdef TR_CONFIRMATION_PASSWORDCHECK
	string msg;
	switch(eFailedReason)
	{
	case eServer_CHECK_CONFIRMATION_PASSWORD_FAILED_REASON_DB_ERROR:			///< DB 에러
		msg = _STR(FAILED_CHECK_CONFIRMATION_PASSWORD_DB_ERROR);
		break;
	case eServer_CHECK_CONFIRMATION_PASSWORD_FAILED_REASON_INCORRECT_PASSWORD:	///< 비번이 틀렸음
		msg = _STR(INCORRECT_PASSWORD);
		break;
	}

	CTRShortTimeMessage::showMessage(msg, 1.2f, -3.5f);
	CTRConfirmationPasswordCheckDlg::getInstance().onRecvCheckConfirmationPasswordFailed(eFailedReason);
	DBG_OUTPUT("CTRNetEventHandler::onRecvCheckConfirmationPasswordFailed %s", msg.c_str());
#endif //TR_CONFIRMATION_PASSWORDCHECK
}

/// 이벤트 아이템으로 교환할 수 있는 아이템 목록을 받았음.
void CTRNetEventHandler::onRecvEventItemExchangeItemListOK(int iEventNum, const std::vector<RewardItemInfo> &vecRewardList)
{
	CTREventItemExchangeDlg::getInstance().onRecvEventItemExchangeItemListOK(iEventNum, vecRewardList);
}

/// 이벤트 아이템으로 교환할 수 있는 아이템 목록받기를 실패했음.
void CTRNetEventHandler::onRecvEventItemExchangeItemListFailed(int iEventNum, eServer_EVENT_ITEM_EXCHANGE_ITEM_LIST_FAILED_REASON eFailedReason)
{
	string msg;
	switch(eFailedReason)
	{
	case eServer_EVENT_ITEM_EXCHANGE_ITEM_LIST_FAILED_REASON_INVALID_EVENT_NUM:	///< 유효하지 않은 이벤트 번호
		msg = _STR(FAILED_INVALID_EVENT_NUM);
		break;
	case eServer_EVENT_ITEM_EXCHANGE_ITEM_LIST_FAILED_REASON_INVALID_EVENT:		///< 유효하지 않은 이벤트 (이벤트 기간이 만료됐거나 이벤트 목록에서 보여주지 않는 경우)
		msg = _STR(FAILED_INVALID_EVENT);
		break;
	}

	CTRShortTimeMessage::showMessage(msg);
	CTREventItemExchangeDlg::getInstance().onRecvEventItemExchangeItemListFailed(iEventNum, eFailedReason);
	DBG_OUTPUT("CTRNetEventHandler::onRecvEventItemExchangeItemListFailed %s", msg.c_str());
}

/// 이벤트 아이템 교환을 성공했음.
void CTRNetEventHandler::onRecvExchangeEventItemOK(int iEventNum, eRewardCondition eRewardType, int iReward)
{
	CTREventItemExchangeDlg::getInstance().onRecvExchangeEventItemOK(iEventNum, eRewardType,iReward);
}

/// 이벤트 아이템 교환을 실패했음.
void CTRNetEventHandler::onRecvExchangeEventItemFailed(int iEventNum, eServer_EXCHANGE_EVENT_ITEM_FAILED_REASON eFailedReason)
{
	string msg;
	switch(eFailedReason)
	{
	case eServer_EXCHANGE_EVENT_ITEM_FAILED_REASON_DB_ERROR:			///< DB 에러
		msg = _STR(FAILED_EXCHANGE_EVENT_ITEM_DB_ERROR);
		break;
	case eServer_EXCHANGE_EVENT_ITEM_FAILED_REASON_INVALID_EVENT_NUM:	///< 유효하지 않은 이벤트 번호
		msg = _STR(FAILED_INVALID_EVENT_NUM);
		break;
	case eServer_EXCHANGE_EVENT_ITEM_FAILED_REASON_INVALID_EVENT:		///< 유효하지 않은 이벤트 (이벤트 기간이 만료됐거나 이벤트 목록에서 보여주지 않는 경우)
		msg = _STR(FAILED_INVALID_EVENT);
		break;
	case eServer_EXCHANGE_EVENT_ITEM_FAILED_REASON_NO_MORE_APPLIEABLE:	///< 이미 응모한 중복 불가능한 이벤트
		msg = _STR(FAILED_EXCHANGE_EVENT_ITEM_NO_MORE_APPLIEABLE);
		break;
	case eServer_EXCHANGE_EVENT_ITEM_FAILED_REASON_INSUFFICIENT_ITEM:	///< 이벤트 응모에 필요한 아이템 부족
		msg = _STR(FAILED_EXCHANGE_EVENT_ITEM_INSUFFICIENT_ITEM);
		break;
	case eServer_EXCHANGE_EVENT_ITEM_FAILED_REASON_INVALID_APPLY:		///< 유효하지 않은 이벤트 응모 요청
		msg = _STR(FAILED_EXCHANGE_EVENT_ITEM_INVALID_APPLY);
		break;
	case eServer_EXCHANGE_EVENT_ITEM_FAILED_REASON_REWARD_FAILED:		///< 보상(아이템 or 경험치 or TR or ...) 지급 실패
		msg = _STR(FAILED_EXCHANGE_EVENT_ITEM_REWARD_FAILED);
		break;
	case eServer_EXCHANGE_EVENT_ITEM_FAILED_REASON_INVALID_REWARD_TYPE:	///< 교환할 수 없는 보상 타입
		msg = _STR(FAILED_EXCHANGE_EVENT_ITEM_INVALID_REWARD_TYPE);
		break;
	}

	CTRShortTimeMessage::showMessage(msg);
	CTREventItemExchangeDlg::getInstance().onRecvExchangeEventItemFailed(iEventNum, eFailedReason);
	DBG_OUTPUT("CTRNetEventHandler::onRecvExchangeEventItemFailed %s", msg.c_str());
}

/// 점술이 무료로 가능한지 불가능한지를 받았다.(bFree = TRUE : 무료, FALSE : 유료)
void CTRNetEventHandler::onRecvDivinationCheckFree( bool bFree, eDivinationType requestType)
{
	CTRGameParkUI::getInstance().onRecvDivinationCheckFree(bFree, requestType);
}

/// 점술 무료 조회가 실패했다.
void CTRNetEventHandler::onRecvDivinationCheckFreeFailed(eDivinationType requestType)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvDivinationCheckFreeFailed requestType = %d",requestType);
}

/// 점괘를 받았다.
void CTRNetEventHandler::onRecvDivinationResult(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities, eDivinationType requestType)
{
	if(0 == appliedExtraAbilities.size()) return;

	eBUFF_SET_RESULT eResult = CTRExtraAbility::getInstace().setBuffItem(appliedExtraAbilities[0], true);

	CTRGameParkUI::getInstance().onRecvDivinationResult(appliedExtraAbilities[0], eResult);
	CTRFarmUI::getInstance().onRecvDivinationResult(appliedExtraAbilities[0], eResult);
}

/// 점보기가 실패했다.
void CTRNetEventHandler::onRecvDivinationResultFailed(eDivinationFailReason failReason, eDivinationType requestType)
{
	CTRGameParkUI::getInstance().onRecvDivinationResultFailed(failReason, requestType);
}

/// 내 커플에 의해 버프를 받았다.
void CTRNetEventHandler::onRecvDivinationCoupleExAbilitiesResult(const ExtraAbilityInfo & appliedExtraAbilities, std::string strDivinationDesc)
{
	CTRExtraAbility::getInstace().onRecvDivinationCoupleExAbilitiesResult(appliedExtraAbilities);

	CTRCoupleSystem::getInstacne().onRecvDivinationCoupleExAbilitiesResult(appliedExtraAbilities, strDivinationDesc);
}

void CTRNetEventHandler::onRecvDivinationCoupleExAbilitiesResultFailed()
{
	CTRShortTimeMessage::getInstance().showMessage(_STR(HS_ERR_UNKNOWN));
}


/// 요청한 특별 능력의 목록(특별한 능력치-버프-가 적용되는 아이템 목록)을 받았다.
void CTRNetEventHandler::onRecvExtraAbilities(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities)
{
	CTRExtraAbility::getInstace().onRecvExtraAbilities(appliedExtraAbilities);
}

/// 특별 능력치 받기가 실패했다.
void CTRNetEventHandler::onRecvExtraAbilitiesFailed()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvExtraAbilitiesFailed");
}

/// 특별 능력치(버프)아이템 사용을 성공했다.
void CTRNetEventHandler::onRecvUseExtraAbilityItem(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities,eDivinationType requestType, int iUseItemNum, int iRemainUseItemCount)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvUseExtraAbilityItem");
	if(0 == appliedExtraAbilities.size()) return;

	eBUFF_SET_RESULT eResult = CTRExtraAbility::getInstace().setBuffItem(appliedExtraAbilities[0], true);

	switch(eResult)
	{
	case eBUFF_SET_RESULT_FIRST:
	case eBUFF_SET_RESULT_DUPLICATE:
		CTRUserInterface::getInstance().showBuffIcon();
		break;
	}
	CKeepItemList::getInstance().eraseItem(iUseItemNum);
	const CItemInfoNode * pItem = CClientItemList::getInstance().getItemInfo(iUseItemNum);
	if (pItem)
	{
		COkDialogEx::getInstance().showDialog(_STR(USE_EXTRA_ABILITY_ITEM_OK), pItem->m_name);
	}
}

/// 특별 능력치(버프)아이템 사용을 실패했다.
void CTRNetEventHandler::onRecvUseExtraAbilityItemFailed(eUseExtraAbilityItemFailReason failReason, eDivinationType requestType)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvUseExtraAbilityItemFailed");
}

/// 미션 보상 특별 능력치(버프)아이템 사용을 성공했다.
void CTRNetEventHandler::onRecvUseMissionExtraAbilityItem(const std::vector<ExtraAbilityInfo> & appliedExtraAbilities,eMissionKind missionKind)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvUseMissionExtraAbilityItem");
	if(appliedExtraAbilities.empty()) return;

	CTRExtraAbility::getInstace().setBuffItem(appliedExtraAbilities[0], true);	

	CTROneDayMissionManager::getInstance().onRecvOneDayMissionAllClearReward(missionKind);
}

/// 미션 보상 특별 능력치(버프)아이템 사용을 실패했다.
void CTRNetEventHandler::onRecvUseMissionExtraAbilityItemFailed(eUseExtraAbilityItemFailReason failReason, eMissionKind missionKind)
{
	CTROneDayMissionManager::getInstance().onRecvOneDayMissionAllClearRewardFailed(failReason, missionKind);
}

//////////////////////////////////////////////////////////////////////////

///<! 동물레이싱 관련 이벤트 핸들러
// 동물 길들이기에 성공했다.
void CTRNetEventHandler::onRecvAnimalRacingPetTrainingOK(__int64 nFarmItemID, int nFarmPetDescNum, int nRidingPetDescNum)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvAnimalRacingPetTrainingOK nFarmItemID:%I64d, nFarmPetDescNum:%d, nRidingPetDescNum:%d", nFarmItemID, nFarmPetDescNum, nRidingPetDescNum);
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(nRidingPetDescNum);
	const int iMyFarmNum = CNetClientManager::getInstance().getMyFarmUniuqeNum();
	CNetClientManager::getInstance().requestGetFarmItemAttrList(iMyFarmNum, false, nFarmPetDescNum);
	CTRShopDlg::getInstance().onRecvAnimalRacingPetTrainingOK(nFarmItemID, nFarmPetDescNum, nRidingPetDescNum);
	CTRMyroomDlg::getInstance().onRecvAnimalRacingPetTrainingOK(nFarmItemID, nFarmPetDescNum, nRidingPetDescNum);
	CTRFarmUI::getInstance().onRecvAnimalRacingPetTrainingOK(nFarmItemID, nFarmPetDescNum, nRidingPetDescNum);
	
}

// 동물 길들이기에 실패했다.
void CTRNetEventHandler::onRecvAnimalRacingPetTrainingFailed(__int64 nFarmItemID, int nItemDescNum, int nReturnValue)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvAnimalRacingPetTrainingFailed nFarmItemID:%I64d, nItemDescNum:%d, nReturnValue:%d", nFarmItemID, nItemDescNum, nReturnValue);
	CTRShopDlg::getInstance().onRecvAnimalRacingPetTrainingFailed(nFarmItemID, nItemDescNum, nReturnValue);
	CTRMyroomDlg::getInstance().onRecvAnimalRacingPetTrainingFailed(nFarmItemID, nItemDescNum, nReturnValue);
	CTRFarmUI::getInstance().onRecvAnimalRacingPetTrainingFailed(nFarmItemID, nItemDescNum, nReturnValue);
}

// 기본 동물 받기 성공
void CTRNetEventHandler::onRecvAnimalRacingGetDefaultAnimalOK()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvAnimalRacingGetDefaultAnimalOK");
	CNetClientManager::getInstance().requestSetCurrentAnimalRacingAvatarSetting();
	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_ANIMALRACING_RIDABLE_PET);
	CTRTutorialGameUI::getInstance().onRecvAnimalRacingGetDefaultAnimalOK();
}

// 기본 동물 받기 실패
void CTRNetEventHandler::onRecvAnimalRacingGetDefaultAnimalFailed(int nReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvAnimalRacingGetDefaultAnimalFailed %d", nReason);
	CTRTutorialGameUI::getInstance().onRecvAnimalRacingGetDefaultAnimalFailed(nReason);
}

// 만료된 동물 리스트 받기 성공
void CTRNetEventHandler::onRecvAnimalRacingGetExpiredAnimalAvatarListOK(std::vector<int> & nAnimalKindList)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvAnimalRacingGetExpiredAnimalAvatarListOK size : %d", nAnimalKindList.size());
	const AnimalRacingAnimalAvatar& animalAvatar = CTRNetPlayManager::getInstance().getAnimalAvatarInfo();
	for(size_t i = 0; i < nAnimalKindList.size(); ++i)
	{
		if(animalAvatar.m_animal == nAnimalKindList[i])
		{
			CNetClientManager::getInstance().requestSetCurrentAnimalRacingAvatarSetting();
			return;
		}
	}
}

// 만료된 동물 리스트 받기 실패
void CTRNetEventHandler::onRecvAnimalRacingGetExpiredAnimalAvatarListFailed()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvAnimalRacingGetExpiredAnimalAvatarListFailed");
}

//////////////////////////////////////////////////////////////////////////
void CTRNetEventHandler::onRecvUserProfile( const UserProfile & stUserProfile)
{

}

// 유저 프로필을 제대로 받지 못하였다.
void CTRNetEventHandler::onRecvUserProfileFailed()
{

}

//유저 프로필을 설정한다.
void CTRNetEventHandler::onRecvSetUserProfile(const UserProfile & stUserProfile)
{
	
}

// 유저 프로필을 제대로 설정하지 못했다.
void CTRNetEventHandler::onRecvSetUserProfileFailed()
{

}

#ifdef _GAME_OPTION_
// 유저 게임옵션 정보 받았다.
void CTRNetEventHandler::onRecvUserGameOptionOK(std::string & sMacro, std::string & sShare, GameOptionInfo & gameOption)
{
	COptionLoadInfo loadInfo;
	loadInfo.setLoadTypeServer();
	loadInfo.load(sMacro, sShare);

    if(CLocalOptions::getInstance().hasErrorLastExcuted()){
        loadInfo.setSafemode();

        gameOption.bEdgeEffect = false;
        gameOption.bPostEffect = false;

        auto* pRenderSettings = CProgramSettings::Context()->renderSettings();

        pRenderSettings->setAntialisasingState(VISUAL_ANTI_NONE);
        pRenderSettings->setRenderScaleSize(VISUAL_VALUE_RENDERSCALE[VISUAL_INDEX_DEFAULT_RENDERSCALE]);
        pRenderSettings->storeLocalSetting();

        CTRShortTimeMessage::showMessage("이전 게임이 비정상 종료되어 그래픽 옵션을 변경합니다.", 5.f);
        DBG_OUTPUT("CTRNetEventHandler::onRecvUserGameOptionOK(...) : graphic option reset");
    }

	CTRGameOptionDialog::getInstance().load(loadInfo, gameOption);

	CProgramSettings::getInstance().updateSettingInfo(&CTRGameOptionInfo::instance);
	CProgramSettings::getInstance().updateSetting(&CTRGameOptionInfo::instance) ;
}

// 유저 게임옵션 정보 받지 못하였다.
void CTRNetEventHandler::onRecvUserGameOptionFailed()
{

}
//유저 게임옵션 정보 설정한다.
void CTRNetEventHandler::onRecvSetUserGameOptionOK()
{
}
// 유저 게임옵션 정보 설정하지 못했다.
void CTRNetEventHandler::onRecvSetUserGameOptionFailed()
{
}
#endif

#ifdef _SECOND_PASSWORD_
// 2차 비밀번호 요청 한다. 
void CTRNetEventHandler::onRecvSecondPasswordInfo()
{
	COkDialogEx::getInstance().showDialog(_STR(SECONDPASSWORD_NEED_CHECK), "gui\\ok.gui");
}
// 2차 비밀번호 설정 성공.
void CTRNetEventHandler::onRecvSetSecondPasswordOK()
{
	CTRSecondPassword::getInstance().onRecvSetSecondPasswordOK();
}
// 2차 비밀번호 설정 실패.
void CTRNetEventHandler::onRecvSetSecondPasswordFailed()
{
	CTRSecondPassword::getInstance().onRecvSetSecondPasswordFailed();
}
// 2차 비밀번호 확인 성공.
void CTRNetEventHandler::onRecvCheckSecondPasswordOK(eCERTIFY_TYPE certifyType)
{
	CTRSecondPassword::getInstance().onRecvCheckSecondPasswordOK(certifyType);
}
// 2차 비밀번호 확인 실패.
void CTRNetEventHandler::onRecvCheckSecondPasswordFailed(eSecondPassword_FAILED_REASON eFailedReason, int iFailedCount, time_type tFailedDate)
{
	CTRSecondPassword::getInstance().onRecvSecondPasswordFailed(eFailedReason, iFailedCount, tFailedDate);
}
// 2차 비밀번호 변경 성공.
void CTRNetEventHandler::onRecvChangeSecondPasswordOK(eCERTIFY_TYPE certifyType)
{
	CTRSecondPassword::getInstance().onRecvChangeSecondPasswordOK(certifyType);
}
// 2차 비밀번호 변경 실패.
void CTRNetEventHandler::onRecvChangeSecondPasswordFailed(eSecondPassword_FAILED_REASON eFailedReason, int iFailedCount, time_type tFailedDate)
{
	CTRSecondPassword::getInstance().onRecvSecondPasswordFailed(eFailedReason, iFailedCount, tFailedDate);
}
// 2차 비밀번호 인증변경 성공.
void CTRNetEventHandler::onRecvCertifySecondPasswordOK()
{
	CTRSecondPassword::getInstance().onRecvCertifySecondPasswordOK();
}
// 2차 비밀번호 인증변경 실패.
void CTRNetEventHandler::onRecvCertifySecondPasswordFailed(eSecondPassword_FAILED_REASON eFailedReason)
{
	CTRSecondPassword::getInstance().onRecvSecondPasswordFailed(eFailedReason);
}
// 2차 비밀번호 사용 해제 성공.
void CTRNetEventHandler::onRecvSecondPasswordUseCancelOK(eCERTIFY_TYPE certifyType)
{
	CTRSecondPassword::getInstance().onRecvSecondPasswordUseCancelOK(certifyType);
}
// 2차 비밀번호 사용 해제 실패.
void CTRNetEventHandler::onRecvSecondPasswordUseCancelFailed(eSecondPassword_FAILED_REASON eFailedReason, eCERTIFY_TYPE certifyType, int iFailedCount, time_type tFailedDate)
{
	CTRSecondPassword::getInstance().onRecvSecondPasswordFailed(eFailedReason, iFailedCount, tFailedDate);
}
#endif // _SECOND_PASSWORD_

//////////////////////////////////////////////////////////////////////////
/// 팜에서 쓰이는 응답들 시작

//! 팜을 생성하는데 성공하였다.
void CTRNetEventHandler::onRecvFarmCreateFarmOK(const FarmInfo& farmInfo)
{
	CUseItemDlg::getInstance().closeUI();
	CTRFarmLobbyUIDlg::getInstance().onRecvFarmCreateFarmOK(farmInfo);
}

//! 추가된 맵 오브젝트 아이템 처리. 
void CTRNetEventHandler::onRecvFarmModifyByInsertOK(const RecvFarmMapObjectInfo& mapObject)
{
	//! 현재는 사용안함
	DBG_OUTPUT("Insert m_iFarmItemID [%d]",  mapObject.m_iFarmItemID);
}

//! 위치나 방향등이 변경된 맵 오브젝트 아이템 처리. n
void CTRNetEventHandler::onRecvFarmModifyByModifyOK(const RecvFarmMapObjectInfo& mapObject)
{
	//! 현재는 사용안함
	DBG_OUTPUT("Modify m_iFarmItemID [%d]",  mapObject.m_iFarmItemID);
}

//! 삭제된 맵 오브젝트 아이템 처리.
void CTRNetEventHandler::onRecvFarmModifyByDeleteOK(const __int64& iFarmDescNum)
{
	//! 현재는 사용안함
	DBG_OUTPUT("Delete m_iFarmItemID [%d]",  iFarmDescNum);
}

//! 팜을 생성하는데 실패하였다.
void CTRNetEventHandler::onRecvFarmCreateFarmFailed(const eFarm_CREATE_FARM_FAILED_REASON eResult)
{
	string strMsg;

	switch(eResult)
	{
	case eFarm_CREATE_FARM_FAILED_REASON_UNKNOWN:
		strMsg = _STR(FAILED_CREATE_FARM_FAILED_REASON_UNKNOWN);
		break;
	case eFarm_CREATE_FARM_FAILED_REASON_DB_ERROR:
		strMsg = _STR(FAILED_CREATE_FARM_FAILED_REASON_DB_ERROR);
		break;
	case eFarm_CREATE_FARM_FAILED_REASON_EXIST_FARM_ERROR:
		strMsg = _STR(FAILED_CREATE_FARM_FAILED_REASON_EXIST_FARM_ERROR);
		break;
	case eFarm_CREATE_FARM_FAILED_REASON_DUPLICATE_FARM_NAME_ERROR:
		strMsg = _STR(FAILED_CREATE_FARM_FAILED_REASON_DUPLICATE_FARM_NAME_ERROR);
		break;
	case eFarm_CREATE_FARM_FAILED_REASON_INVALID_FARM_NAME_ERROR:
		strMsg = _STR(FAILED_CREATE_FARM_FAILED_REASON_INVALID_FARM_NAME_ERROR);
		break;
	}

	DBG_OUTPUT("onRecvFarmCreateFarmFailed : %s", strMsg.c_str());

	CUseItemDlg::getInstance().closeUI();
	CTRFarmLobbyUIDlg::getInstance().onRecvFarmCreateFarmFailed(eResult);
}

//! 동물or식물한테 수확하는데 성공하였다.
void CTRNetEventHandler::onRecvFarmHarvestOK(const __int64 intiTargetItemID,const std::vector<FarmHarvestInfo>& vecResultItem)
{
	CTRFarmUI::getInstance().onRecvFarmHarvestOK(intiTargetItemID, vecResultItem);
//	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HARVEST_FARM);

	//!< 수확 관련 컨디션 체크
	const int itemNum = CTRFarmItemObjectManager::getInstance().getFarmItemDescNum(intiTargetItemID);
	const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(itemNum);
	if(pItem && pItem->m_pFarmItemInfo)
	{
		const eFarmItemPosition farmItemPosition = static_cast<eFarmItemPosition>(pItem->m_pFarmItemInfo->getFarmPosition());

		//!< 동물은 체크하지 않음
		if(farmItemPosition != eFarmItemPosition_HARVEST_ANIMAL)
		{
			CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HARVEST_FARM);
			CMissionMsgDispatcher::getInstance().checkCompleteCondition();
		}
	}
}

//! 동물한테 수확하는데 실패하였다.
void CTRNetEventHandler::onRecvFarmHarvestFailed(const eServerResult& eResult, const __int64 intiTargetItemID)
{
	string msg;

	switch(eResult)
	{
	case eServerResult_FARM_ANIMAL_HARVEST_FAILED_ACK:
		//! 팜 아이템 수확을 연속으로 할 경우 나오는 메세지 제거
		//msg = _STR(FAILED_FARM_ANIMAL_HARVEST_FAILED_ACK);
		break;
	case eServerResult_FARM_ANIMAL_HARVEST_EMPTY_FARMUNIQUENUM_FAILED_ACK:
		msg = _STR(FAILED_FARM_ANIMAL_HARVEST_EMPTY_FARMUNIQUENUM_FAILED_ACK);
		break;
	case eServerResult_FARM_ANIMAL_HARVEST_INVALID_ITEMID_FAILED_ACK:
		msg = _STR(FAILED_FARM_ANIMAL_HARVEST_INVALID_ITEMID_FAILED_ACK);
		break;
	case eServerResult_FARM_ANIMAL_HARVEST_DIFFERENT_OWNER_ITEM_FAILED_ACK:
		msg = _STR(FAILED_FARM_ANIMAL_HARVEST_DIFFERENT_OWNER_ITEM_FAILED_ACK);
		break;
	case eServerResult_FARM_ANIMAL_HARVEST_EXPIRE_DATETIME_ITEM_FAILED_ACK:
		msg = _STR(FAILED_FARM_ANIMAL_HARVEST_EXPIRE_DATETIME_ITEM_FAILED_ACK);
		break;
	case eServerResult_FARM_ANIMAL_HARVEST_INVALID_HARVEST_ATTR_FAILED_ACK:
		msg = _STR(FAILED_FARM_ANIMAL_HARVEST_INVALID_HARVEST_ATTR_FAILED_ACK);
		break;
	case eServerResult_FARM_ANIMAL_HARVEST_EMPTY_HARVEST_COUNT_FAILED_ACK:
		msg = _STR(FAILED_FARM_ANIMAL_HARVEST_EMPTY_HARVEST_COUNT_FAILED_ACK);
		break;
	case eServerResult_FARM_ANIMAL_HARVEST_INVALID_MAXEXP_FAILD_ACK:
		msg = _STR(FAILED_FARM_ANIMAL_HARVEST_INVALID_MAXEXP_FAILD_ACK);
		break;
	case eServerResult_FARM_ANIMAL_HARVEST_YET_HARVEST_FAILED_ACK:
		msg = _STR(FAILED_FARM_ANIMAL_HARVEST_YET_HARVEST_FAILED_ACK);
		break;
	case eServerResult_FARM_ANIMAL_HARVEST_GIVERESULTITEM_FAILED_ACK:
		msg = _STR(FAILED_FARM_ANIMAL_HARVEST_GIVERESULTITEM_FAILED_ACK);
		break;
	case eServerResult_FARM_ANIMAL_HARVEST_SETEXP_ZERO_FAILED_ACK:
		msg = _STR(FAILED_FARM_ANIMAL_HARVEST_SETEXP_ZERO_FAILED_ACK);
		break;
	}

	DBG_OUTPUT("onRecvFarmHarvestFailed : %s", msg.c_str());

	if(!msg.empty())
	{
		COkDialogEx::getInstance().showDialog(msg, "gui\\ok.gui");
	}
}
//! 랜덤 팜 포인트를 지급하는데 성공 하였다.
void CTRNetEventHandler::onRecvFarmGiveMeRandomFarmPointOK(const __int64 iFarmItemID, const int iRemainFarmPoint, const int iGiveFarmPoint)
{
	CTRFarmUI::getInstance().onRecvFarmGiveMeRandomFarmPointOK(iFarmItemID, iRemainFarmPoint, iGiveFarmPoint);
}

//! 나의 팜 포인트를 얻는데 성공하였습니다.
void CTRNetEventHandler::onRecvFarmGetMyFarmPointOK(const int iFarmPoint)
{
	CTRFarmLobbyUIDlg::getInstance().onRecvFarmGetMyFarmPointOK(iFarmPoint);
	CTRFarmShopUI::getInstance().onRecvFarmGetMyFarmPointOK(iFarmPoint);
	CTRFarmMyroomUI::getInstance().onRecvFarmGetMyFarmPointOK(iFarmPoint);
	CTRGameParkUI::getInstance().onRecvFarmGetMyFarmPointOK(iFarmPoint);
}

//! 나의 팜 포인트를 얻는데 실패하였습니다.
void CTRNetEventHandler::onRecvFarmGetMyFarmPointFailed()
{
	CTRFarmLobbyUIDlg::getInstance().onRecvFarmGetMyFarmPointFailed();
	DBG_OUTPUT("onRecvFarmGetMyFarmPointFailed");
}

//! 랜덤 팜 포인트를 지급하는데 실패하였다.
void CTRNetEventHandler::onRecvFarmGiveMeRandomFarmPointFailed(const __int64 iFarmItemID)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFarmGiveMeRandomFarmPointFailed");
}

//! 팜을 삭제하는데 성공하였다. 
void CTRNetEventHandler::onRecvFarmDestroyFarmOK(const int iFarmUniqueNum)
{
	DBG_OUTPUT("onRecvFarmDestroyFarmOK");
}

//! 팜을 삭제하는데 실패하였다. 
void CTRNetEventHandler::onRecvFarmDestroyFarmFailed(const int iFarmUniqueNum)
{
	DBG_OUTPUT("onRecvFarmDestroyFarmFailed [ iFarmUniqueNum %d ]", iFarmUniqueNum);
}

//! 팜 오브젝트 점유 정보 리스트를 받았다.
void CTRNetEventHandler::onRecvFarmObjectLockInfoList(std::map<FarmObjectIDIndex, BYTE> mapFarmObjectLockInfoList)
{
	CTRActionObjectManager::getInstance().onRecvFarmObjectLockInfoList(mapFarmObjectLockInfoList);
}

//! 팜 오브젝트 점유 정보가 변경되었다.
void CTRNetEventHandler::onRecvFarmModifyObjectLockInfo(eServerResult eResult, FarmObjectIDIndex stOIDIndex, BYTE iGameIndex, bool bLock)
{
	bool bMsgOutput = false;
	switch(eResult)
	{
	case eServerResult_OK_ACK:
		CTRActionObjectManager::getInstance().onRecvFarmModifyObjectLockInfo(eResult, stOIDIndex, iGameIndex, bLock);
		break;
	case eServerResult_FARM_ALREADY_LOCKED_OBJECT:			//!< 이미 누군가 점유한 오브젝트다.
		bMsgOutput = true;
		break;
	case eServerResult_FARM_OBJECT_LOCKED_BY_OTHER:			//!< 오브젝트를 점유 중인사람은 내가 아니다.(타인이 점유중)
		bMsgOutput = true;
		break;
	case eServerResult_FARM_OBJECT_UNLOCK_STATE:			//!< 아무도 그 오브젝트를 점유하고 있지 않다.(나도 아니고 타인도 점유중이지 않음)
		bMsgOutput = true;
		break;
	}

	if(bMsgOutput)
	{
		DBG_OUTPUT("CTRNetEventHandler::onRecvFarmModifyObjectLockInfo Result=[%d]", (int)eResult);
	}
}

//! 팜 이름을 변경하였다.
void CTRNetEventHandler::onRecvFarmChangeFarmName( const int iFarmUniqueNum, const std::string strFarmName)
{
	m_pNetPlay->_getGameRoomInfo().m_roomTitle = strFarmName;
	CTRFarmUI::getInstance().onRecvFarmChangeFarmName(iFarmUniqueNum, strFarmName);
}

//! 팜 이름 변경을 실패하였다.
void CTRNetEventHandler::onRecvFarmChangeFarmNameFailed( const eServerResult eResult, const eFarm_CHANGE_FARM_NAME_FAILED_REASON failedReason)
{
	if(eResult != eServerResult_FARM_CHANGE_FARM_NAME_FAILED_ACK)
	{
		CTRShortTimeMessage::showMessage(_STR(FAILED_FARM_NAME_MODIFY));
		DBG_OUTPUT("onRecvFarmChangeFarmNameFailed - No farm name change result..");
		return;
	}

	std::string strMent = _STR(FAILED_FARM_NAME_MODIFY);

	switch(failedReason)
	{
	case eFarm_CHANGE_NAME_FAILED_REASON_UNKNOWN:							//!< 알수 없는 실패. 
		strMent = _STR(FAILED_FARM_NAME_MODIFY);
		break;

	case eFarm_CHANGE_FARM_NAME_FAILED_REASON_DB_ERROR:						//!< DB 에러이다. 
		strMent = _STR(FAILED_DB_ERROR);
		break;

	case eFarm_CHANGE_FARM_NAME_FAILED_REASON_NOT_IN_FARM_ERROR:			//!< 팜에 입장한 상태가 아니다. 
		strMent = _STR(FAILED_MSG_NO_IN_FARM);
		break;

	case eFarm_CHANGE_FARM_NAME_FAILED_REASON_INVALID_NAME_ERROR:			//!< 유효하지 않은 팜 이름이다. 
		strMent = _STR(FAILED_INVALID_ROOMTITLE);
		break;

	case eFarm_CHANGE_FARM_NAME_FAILED_REASON_EXCEED_LENGTH_ERROR:			//!< 이름의 길이가 DB 레코드에 지정한 길이를 초과하였다. 
		strMent = _STR(FAILED_MSG_EXCEED_LENGTH);
		break;

	case eFarm_CHANGE_FARM_NAME_FAILED_REASON_EXPIRATION_ERROR:				//!< 기간 만료된 팜에 대한 이름변경 요청. 
		strMent = _STR(MSG_USE_FARM_PERIOD_END);
		break;

	case eFarm_CHANGE_FARM_NAME_FAILED_REASON_NOT_EXIST_FARM_ERROR:			//!< 존재하지 않는 팜에 대한 이름변경 요청. 	
		strMent = _STR(FAILED_MSG_NOT_EXIST_FARM);
		break;

	case eFarm_CHANGE_FARM_NAME_FAILED_REASON_NOT_HAS_PERMISSION_ERROR:		//!< 변경 권한을 가지지 않은 사람이 이름 변경 요청.
		strMent = _STR(FAILED_CHANGE_FARM_MAP_TYPE_FAILED_REASON_NOT_HAS_PERMISSION_ERROR);
		break;
	}

	CTRShortTimeMessage::showMessage(strMent);
	DBG_OUTPUT("onRecvFarmChangeFarmName :  %s", strMent.c_str());
}

//! 프리미엄팜 타입을 변경하였다.
void CTRNetEventHandler::onRecvFarmChangePremiumFarmType( const eServerResult eResult, const int iFarmUniqueNum, const ePremiumFarmType premiumFarmType)
{
	if(eResult == eServerResult_OK_ACK)
	{
		m_pNetPlay->_getGameRoomInfo().m_farmInfo.m_premiumFarmType = premiumFarmType;
		CTRFarmUI::getInstance().onRecvFarmChangePremiumFarmType();
	}
	else if(eResult == eServerResult_FARM_CHANGE_PREMIUMFARM_TYPE_FAILED_ACK)
	{
		CTRShortTimeMessage::showMessage(_STR(FAILED_PREMIUM_FARM_TYPE_MODIFY));
		DBG_OUTPUT("onRecvFarmChangePremiumFarmType : %s", _STR(FAILED_PREMIUM_FARM_TYPE_MODIFY));
	}

}

//! 팜 공개/비공개(비밀번호) 변경을 성공하였다. 
void CTRNetEventHandler::onRecvFarmChangePublicModeOK( const int iFarmUniqueNum, const bool bPublic )
{
	DBG_OUTPUT("onRecvFarmChangePublicModeOK");

	if(m_pNetPlay->getGameRoomInfo().m_farmInfo.m_iFarmUniqueNum == iFarmUniqueNum)
	{
		m_pNetPlay->_getGameRoomInfo().m_farmInfo.m_bIsPublic = bPublic;
	}

	CTRFarmUI::getInstance().onRecvFarmChangePublicModeOK(iFarmUniqueNum, bPublic);
}

//! 팜 공개/비공개(비밀번호) 변경을 실패하였다. 
void CTRNetEventHandler::onRecvFarmChangePublicModeFailed( const eFarm_CHANGE_FARM_PASSWORD_FAILED_REASON byReason )
{
	string strMsg;

	switch(byReason)
	{
	case eFarm_CHANGE_FARM_PASSWORD_FAILED_REASON_UNKNOWN:					//!< 알수 없는 실패. 
		strMsg = _STR(FAILED_CHANGE_FARM_PASSWORD_FAILED_REASON_UNKNOWN);
		break;
	case eFarm_CHANGE_FARM_PASSWORD_FAILED_REASON_NOT_EXIST_FARM_ERROR:		//!< 존재하지 않는 팜에 대한 비밀번호 변경 요청. 
		strMsg = _STR(FAILED_CHANGE_FARM_PASSWORD_FAILED_REASON_NOT_EXIST_FARM_ERROR);
		break;
	case eFarm_CHANGE_FARM_PASSWORD_FAILED_REASON_EXPIRATION_ERROR:			//!< 기간 만료된 팜에 대한 비밀번호 변경 요청. 
		strMsg = _STR(FAILED_CHANGE_FARM_PASSWORD_FAILED_REASON_EXPIRATION_ERROR);
		break;
	case eFarm_CHANGE_FARM_PASSWORD_FAILED_REASON_DB_ERROR:					//!< DB 에러이다. 
		strMsg = _STR(FAILED_CHANGE_FARM_PASSWORD_FAILED_REASON_DB_ERROR);
		break;
	case eFarm_CHANGE_FARM_PASSWORD_FAILED_REASON_NOT_INT_FARM_ERROR:		//!< 팜에 입장한 상태가 아니다. 
		strMsg = _STR(FAILED_CHANGE_FARM_PASSWORD_FAILED_REASON_NOT_INT_FARM_ERROR);
		break;
	case eFarm_CHANGE_FARM_PASSWORD_FAILED_REASON_EXCEED_LENGTH_ERROR:		//!< 패스워드 길이가 DB 레코드에 지정한 길이를 초과하였다.  
		strMsg = _STR(FAILED_CHANGE_FARM_PASSWORD_FAILED_REASON_EXCEED_LENGTH_ERROR);
		break;
	case eFarm_CHANGE_FARM_PASSWORD_FAILED_REASON_NOT_HAS_PERMISSION_ERROR:	//!< 변경 권한을 가지지 않은 사람이 비밀번호 변경 요청. 
		strMsg = _STR(FAILED_CHANGE_FARM_PASSWORD_FAILED_REASON_NOT_HAS_PERMISSION_ERROR);
		break;
	}

	DBG_OUTPUT("onRecvFarmChangePublicModeFailed :  %s", strMsg.c_str());

	CTRFarmUI::getInstance().onRecvFarmChangePublicModeFailed(byReason);
}

//! 팜 Talking-Mode 설정을 변경하였다. 
void CTRNetEventHandler::onRecvFarmChangeTalkingMode( const eServerResult eResult, const bool bTalkOn, const FarmChattingInfo& farmChattingInfo, const ePremiumFarmType premiumFarmType)
{
	if(eResult == eServerResult_OK_ACK)
	{
		m_pNetPlay->onRecvFarmChangeTalkingMode(bTalkOn, farmChattingInfo, premiumFarmType);
		CTRFarmUI::getInstance().onRecvFarmChangeTalkingMode(bTalkOn, farmChattingInfo, premiumFarmType);
	}
	else
	{
		std::string msg = _STR(FAILED_FARM_CHANGE_FARM_TALKING);
		switch (eResult)
		{
		case eServerResult_FARM_CHANGE_FARM_TALKING_FAILED_ACK:
			msg = _STR(FAILED_FARM_CHANGE_FARM_TALKING);
			break;
		case eEnterRoomResult_FAILED_INVALID_CHATTING_FARM_SUBJECT:	///< 유효하지 않는 채팅팜 제목 입니다.
			msg = _STR(ERR_CANNOT_USE_CHAR);
			break;
		}
			
		DBG_OUTPUT("onRecvFarmChangeTalkingMode [ %s ]", msg.c_str());
		COkDialogEx::getInstance().showDialog(msg, "gui\\ok.gui");
	}
}

//! 랜덤 팜 입장이 가능하다. 
void CTRNetEventHandler::onRecvFarmJoinOnRamdonOK( const int& farmUniqueNum )
{
	const bool bEnableEnterFarm = ("true" == CNetClientManager::getInstance().getServerSetting("EnableEnterFarm", "true"));
	if(!bEnableEnterFarm)
	{
		COkDialogEx::getInstance().showDialog(_STR(ERR_FARMJOIN), "gui\\ok.gui");
	}
	else
	{
		CTRFarmChangeManager::getInstance().processMoveToFarm(farmUniqueNum);		
	}
}

//! 랜덤 팜 입장을 실패하였다. 
void CTRNetEventHandler::onRecvFarmJoinOnRandomFailed( const eFarm_JOIN_TALKFARM_ON_RANDOM_JOIN_FAILED_REASON& failedReason)
{
	CTRFarmLobbyUIDlg::getInstance().onRecvFarmJoinOnRandomFailed(failedReason);
}

//! 닉네임을 통한 팜 검색 성공. 
void CTRNetEventHandler::onRecvFarmSearchByNickNameOK( const int iFarmUniqueNum, const bool isPublic)
{
	CTRFarmLobbyUIDlg::getInstance().onRecvFarmSearchByNickNameOK(iFarmUniqueNum, isPublic);
	DBG_OUTPUT("onRecvFarmSearchByNickNameOK [UniqueNum : %d], [Public : %s]", iFarmUniqueNum, (isPublic) ? "true" : "false"); 
}
//! 유저번호를 통한 팜 검색 성공. 
void CTRNetEventHandler::onRecvFarmSearchByUserNumOK(const int iFarmUniqueNum, const bool isPublic)
{
	CTRFarmLobbyUIDlg::getInstance().onRecvFarmSearchByNickNameOK(iFarmUniqueNum, isPublic);
	DBG_OUTPUT("onRecvFarmSearchByUserNumOK [UniqueNum : %d], [Public : %s]", iFarmUniqueNum, (isPublic) ? "true" : "false"); 
}

//! 유저번호를 통한 팜 검색 실패. 
void CTRNetEventHandler::onRecvFarmSearchByUserNumFailed(const eFarm_SEARCH_FARM_FAILED_REASON failedReason)
{
	CTRFarmLobbyUIDlg::getInstance().onRecvFarmSearchByNickNameFailed(failedReason);
}

//! 닉네임을 통한 팜 검색 실패. 
void CTRNetEventHandler::onRecvFarmSearchByNickNameFailed( const eFarm_SEARCH_FARM_FAILED_REASON& failedReason)
{
	CTRFarmLobbyUIDlg::getInstance().onRecvFarmSearchByNickNameFailed(failedReason);
}


//! 팜정보를 얻는데 성공하였다.
void CTRNetEventHandler::onRecvFarmGetFarmInfoOK(const int iFarmUniqueNum,const FarmInfo& info)
{
	DBG_OUTPUT("onRecvFarmGetFarmInfoOK [ iFarmUniqueNum : %d, FarmName : %s ]",iFarmUniqueNum, info.m_strFarmName.c_str());
}

//! 팜정보를 얻는데 실패하였다.
void CTRNetEventHandler::onRecvFarmGetFarmInfoFailed(const int iFarmUniqueNum)
{
	DBG_OUTPUT("onRecvFarmGetFarmInfoFailed [ iFarmUniqueNum %d ]", iFarmUniqueNum);
}

//! 자신의 팜정보를 얻는데 성공하였다. 
void CTRNetEventHandler::onRecvFarmGetMyFarmInfoOK(const FarmInfo& info)
{
	DBG_OUTPUT("onRecvFarmGetMyFarmInfoOK");
}

//! 자신의 팜정보를 얻는데 실패하였다. 
void CTRNetEventHandler::onRecvFarmGetMyFarmInfoFailed(void)
{
	DBG_OUTPUT("onRecvFarmGetMyFarmInfoFailed");
}

//! 길드 팜정보를 얻는데 성공하였다. 
void CTRNetEventHandler::onRecvFarmGetGuildFarmInfoOK(const FarmInfo& info)
{	
	// 길드 팜 정보 갱신
	CTRFarmLobbyUIDlg::getInstance().updateGuildFarmInfo();
}

//! 길드 팜정보를 얻는데 실패하였다. 
void CTRNetEventHandler::onRecvFarmGetGuildFarmInfoFailed(void)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFarmGetGuildFarmInfoFailed");	
	COkDialogEx::getInstance().showDialog(_STR(GUILD_FARM_INFO_GET_FAILED) ,"gui\\ok.gui");
}

//! 길드팜 맵 타입이 변경되었다
void CTRNetEventHandler::onRecvGuildFarmGetChangeMapType(const int iGuildNum, const int iFarmUniqueNum, const int iGuildFarmType)
{
	DBG_OUTPUT("onRecvGuildFarmGetChangeMapType MapType[%d]", iGuildFarmType);
	CTRGuildFarmUI::getInstance().onRecvGuildFarmGetChangeMapType(iGuildNum , iFarmUniqueNum , iGuildFarmType);
}

//! 길드팜 맵 타입이 실패하였다
void CTRNetEventHandler::onRecvGuildFarmGetChangeMapTypeFailed( const eFarm_GET_GUILDFARM_INFO_FAILED_REASON & byReason )
{
	DBG_OUTPUT("onRecvGuildFarmGetChangeMapTypeFailed [%d] ", byReason);
	COkDialogEx::getInstance().showDialog(_STR(MSG_ERROR_CHANGE_GUILD_FARM_MAP) ,"gui\\ok.gui");
}

//! 길드팜 오브젝트의 능력치를 얻는데 성공하였다.
void CTRNetEventHandler::onRecvFarmGetGuildFarmObjectAttrListOK(const int iGuildNum, std::map<int, GuildFarmItemAttrInfo > & mapFamrItemAttr)
{
	DBG_OUTPUT("onRecvFarmGetGuildFarmObjectAttrListOK");	
	bool bMoveRevivalPt = false;	
	for(map<int, GuildFarmItemAttrInfo >::iterator iter = mapFamrItemAttr.begin() ; iter != mapFamrItemAttr.end() ; ++iter)
	{
		int ItemNum = (*iter).first;
		GuildFarmItemAttrInfo attrInfo = (*iter).second;
		DBG_OUTPUT("AttrID[%d] Attr[%s  %f  %d]", ItemNum, attrInfo.m_AttrString.c_str(), attrInfo.m_AttrNumber, attrInfo.m_isBuild);
	}
	if(mapFamrItemAttr.size() == 0)
	{
		DBG_OUTPUT("%s Size Zero", __FUNCTION__);
	}	
	else
	{
		// 새로운 오브젝트가 추가 되었을때 
		if((CKeepGuildFarmItemList::getInstance().getGuildStructureNum() > 0) && (mapFamrItemAttr.size() > CKeepGuildFarmItemList::getInstance().getGuildStructureNum() ))	
			bMoveRevivalPt = true; 
		CKeepGuildFarmItemList::getInstance().onRecvFarmGetGuildFarmObjectAttrListOK(mapFamrItemAttr);
	}
	CTRGuildFarmUI::getInstance().onRecvFarmGetGuildFarmObjectAttrOK(mapFamrItemAttr);
	if(bMoveRevivalPt)	CTRGuildFarmUI::getInstance().moveRevivalPoint();
	
}

//! 길드팜 오브젝트의 능력치를 얻는데 실패하였다.
void CTRNetEventHandler::onRecvFarmGetGuildFarmObjectAttrListFailed()
{
	DBG_OUTPUT("onRecvFarmGetGuildFarmObjectAttrListFailed");	
	COkDialogEx::getInstance().showDialog(_STR(GUILD_FARM_OBJECT_ATTR_GET_FAILED),"gui\\ok.gui");
}

//! 길드팜 식물 수확에 성공하였다.
void CTRNetEventHandler::onRecvGuildFarmGetHarvestOK(const int iGuildNum, const __int64 iOID, const bool bDelete)
{
	CTRGuildFarmUI::getInstance().onRecvGuildFarmGetHarvestOK(iGuildNum, iOID , bDelete);
}

//! 길드팜 식물 수확에 실패하였다.
void CTRNetEventHandler::onRecvGuildFarmGetHarvestFailed(const eServerResult& eResult,const __int64 intiTargetItemID)
{
	DBG_OUTPUT("onRecvGuildFarmGetHarvestFailed result[%d]", eResult);
	CTRGuildFarmUI::getInstance().onRecvGuildFarmGetHarvestFailed(eResult, intiTargetItemID);
}

//!< 길드집사 팻말의 내용을 변경하였다.
void CTRNetEventHandler::onRecvFarmModifyGuildFarmNoticeBoardInfo(const int iGuildNum, const std::string & strBoardInfo)
{
	DBG_OUTPUT("onRecvFarmModifyGuildFarmNoticeBoardInfo");
	CTRGuildFarmUI::getInstance().onRecvFarmModifyGuildFarmNoticeBoardInfo(iGuildNum, strBoardInfo);
} 

//!< 길드집사 팻말의 내용 변경에 실패하였다.
void CTRNetEventHandler::onRecvFarmModifyGuildFarmNoticeBoardInfoFailed(const int iGuildNum)
{
	DBG_OUTPUT("onRecvFarmModifyGuildFarmNoticeBoardInfoFailed guidNum[%d] ", iGuildNum);	
	COkDialogEx::getInstance().showDialog(_STR(GUILD_FARM_NOTICE_MODIFY_FAILED),"gui\\ok.gui");
}

//! 팜관련 아이템 리스트 갱신을 시작한다. 
void CTRNetEventHandler::onRecvFarmGetFarmItemListBegin(void)
{
	DBG_OUTPUT("onRecvFarmGetFarmItemListBegin");
	CKeepFarmItemList::getInstance().onRecvFarmGetFarmItemListBegin();
}

//! 팜관련 아이템 리스트를 얻는데 성공하였다.
void CTRNetEventHandler::onRecvFarmGetFarmItemListOK(const std::vector<FarmItemInfo>&	vecItems)
{
	CKeepFarmItemList::getInstance().onRecvFarmItemList(vecItems);
	CTRFarmItemObjectManager::getInstance().onRecvFarmItemList(vecItems);
	DBG_OUTPUT("onRecvFarmGetFarmItemListOK");
}

//! 팜관련 아이템 리스트를 모두 다 받았다. 
void CTRNetEventHandler::onRecvFarmGetFarmItemListAll(const size_t& totalCount)
{
	DBG_OUTPUT("onRecvFarmGetFarmItemListAll");
	CKeepFarmItemList::getInstance().onRecvFarmGetFarmItemListAll(totalCount);
}

//! 팜관련 아이템 리스트를 얻는데 실패하였다.
void CTRNetEventHandler::onRecvFarmGetFarmItemListFailed()
{
	DBG_OUTPUT("onRecvFarmGetFarmItemListFailed");
}

//! 팜 관련 특정 아이템 목록을 받았다.
void CTRNetEventHandler::onRecvFarmGetFarmItemListExOK(const std::vector<FarmItemInfo>&	vecItems)
{
	CKeepFarmItemList::getInstance().onRecvFarmItemList(vecItems);
	CTRFarmItemObjectManager::getInstance().onRecvFarmItemList(vecItems);
	CTRFarmMyroomUI::getInstance().refresh();
	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvFarmGetFarmItemListExOK();
	CTRLobbyUI::getInstance().onRecvFarmGetFarmItemListExOK();
}

//! 길드팜 관련 특정 아이템 목록을 받았다.
void CTRNetEventHandler::onRecvFarmGetGuileFarmItemListExOK(const int iGuildNum, const std::vector<FarmItemInfo>& vecItems)
{
	CKeepGuildFarmItemList::getInstance().onRecvFarmGetGuileFarmItemListExOK(vecItems);
	CTRGuildFarmUI::getInstance().onRecvFarmGetGuileFarmItemListExOK(vecItems);
}

//! 팜관련 맵정보를 얻는데 성공하였다.
void CTRNetEventHandler::onRecvFarmGetFarmMapInfoOK( const int iFarmUniqueNum, 
													const int iFarmMapType,
													const std::vector<RecvFarmMapObjectInfo>& vecMapInfo,
													const std::vector<RecvFarmMapVoxelsInfo>& vecVoxelInfo )
{
	TRDBG_OUTPUT_ERROR("onRecvFarmGetFarmMapInfoOK[%d]",vecMapInfo.size());

	CTRFarmUI::getInstance().onRecvFarmGetFarmMapInfoOK( iFarmUniqueNum, iFarmMapType, vecMapInfo, vecVoxelInfo );

	if (iFarmUniqueNum == CNetClientManager::getInstance().getMyFarmUniuqeNum())
	{
		const int nInstallCount = CTRFarmItemObjectManager::getInstance().getValueByEmblemMissionCondition(eMissionConditionType_INSTALL_HARVESTABLE_FARM_ITEM);
		if(nInstallCount > 0)
		{	
			CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_INSTALL_HARVESTABLE_FARM_ITEM,nInstallCount);	
			CMissionMsgDispatcher::getInstance().checkCompleteCondition();
		}
	}
}

//! 팜관련 맵정보를 얻는데 실패하였다.
void CTRNetEventHandler::onRecvFarmGetFarmMapInfoFailed(const int iFarmUniqueNum)
{
	DBG_OUTPUT("onRecvFarmGetFarmMapInfoFailed");
}

//! 팜의 맵정보를 리로드했다.
void CTRNetEventHandler::onRecvFarmReloadFarmMapInfo( const int iFarmUniqueNum, 
													  const int iFarmTypeNum, 
													  const int iFarmSkyBoxNum, 
													  const int iFarmWeatherNum, 
													  const std::vector<RecvFarmMapObjectInfo>& vecMapInfo,
													  const std::vector<RecvFarmMapVoxelsInfo>& vecVoxelInfo )
{
	CTRFarmUI::getInstance().onRecvFarmReloadFarmMapInfo(iFarmUniqueNum, iFarmTypeNum, iFarmSkyBoxNum, iFarmWeatherNum, vecMapInfo, vecVoxelInfo );

	TRDBG_OUTPUT_ERROR("onRecvFarmReloadFarmMapInfo[%d]",vecMapInfo.size());

	if (CNetClientManager::getInstance().getMyFarmUniuqeNum() == iFarmUniqueNum)
	{
		const int nInstallCount = CTRFarmItemObjectManager::getInstance().getValueByEmblemMissionCondition(eMissionConditionType_INSTALL_HARVESTABLE_FARM_ITEM);
		if(nInstallCount > 0)
		{	
			CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_INSTALL_HARVESTABLE_FARM_ITEM, nInstallCount);
			CMissionMsgDispatcher::getInstance().checkCompleteCondition();
		}
	}
}
//! 맵정보를 초기화하는데 성공하였다.
void CTRNetEventHandler::onRecvFarmClearFarmMapInfoOK(const int iFarmUniqueNum)
{
	CTRFarmItemObjectManager::getInstance().clearAllInstallObject();
	if(CTRVoxelWorld::Inst().IsEmpty() == false)
	{
		CTRFarmUI::getInstance().removeAllVoxel();
		CKeepFarmItemList::getInstance().doModifyCraftItem(true);
		RecvFarmMapVoxelsInfo voxelInfo;
		CNetClientManager::getInstance().requestFarmCraft_CompressSaveInstallData(voxelInfo);
	}
	else
	{
		COkDialogEx::getInstance().showDialog(_STR(MSG_FARM_ITEM_SAVE), "gui\\ok.gui");
	}
}

//! 맵정보를 초기화하는데 실패하였다.
void CTRNetEventHandler::onRecvFarmClearFarmMapInfoFailed(const int iFarmUniqueNum)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFarmClearFarmMapInfoFailed");
}
//! 팜맵 수정 관련 서버로부터 정보를 받았다
void CTRNetEventHandler::onRecvFarmModifyFarmMapInfoOK(const int iFarmUniqueNum, mapObjectModifyResult& mapObjectResultList)
{
	CTRFarmItemObjectManager::getInstance().onRecvFarmModifyFarmMapInfo(iFarmUniqueNum,mapObjectResultList);
}
//! 나의 팜 슬롯 리스트를 읽는데 성공하였다.  
void CTRNetEventHandler::onRecvFarmGetFarmSlotListOK(std::vector<FarmSlotInfo> & vecFarmSlotInfo)
{
	DBG_OUTPUT("onRecvFarmGetFarmSlotListOK");
	CTRFarmMyroomUI::getInstance().onRecvFarmGetFarmSlotListOK(vecFarmSlotInfo);
}

//! 나의 팜 슬롯 리스트를 읽는데 실패하였다.  
void CTRNetEventHandler::onRecvFarmGetFarmSlotListFailed(const eFarm_GET_FARM_SLOT_LIST_FAILED_REASON& failedReason)
{
	DBG_OUTPUT("onRecvFarmGetFarmSlotListFailed");
}

//! 나의 팜 슬롯을 저장하는데 성공하였다.  
void CTRNetEventHandler::onRecvFarmSaveFarmSlotInfoOK(const int iFarmSlotNum, const FarmSlotInfo& eResult)
{
	DBG_OUTPUT("onRecvFarmSaveFarmSlotInfoOK");
	CTRFarmMyroomUI::getInstance().onRecvFarmSaveFarmSlotInfoOK(iFarmSlotNum, eResult);
}

//! 나의 팜 슬롯을 저장하는데 실패하였다.  
void CTRNetEventHandler::onRecvFarmSaveFarmSlotInfoFailed(const eFarm_SAVE_FARM_SLOTINFO_FAILED_REASON& failedReason )
{
	DBG_OUTPUT("onRecvFarmSaveFarmSlotInfoFailed");

	if(failedReason == eFarm_SAVE_FARM_SLOTINFO_FAILED_REASON_INVALID_TITLE)
	{
		CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_INVALID_STRING));
	}
	else
	{
		CTRShortTimeMessage::getInstance().showMessage(format(_STR(FAILED_SAVE_FARM_SLOT_INFO),failedReason));	
	}	
}

//! 나의 팜 슬롯을 초기화하는데 성공하였다.  
void CTRNetEventHandler::onRecvFarmClearFarmSlotInfoOK(const int iFarmSlotNum)
{
	DBG_OUTPUT("onRecvFarmClearFarmSlotInfoOK");
	CTRFarmMyroomUI::getInstance().onRecvFarmClearFarmSlotInfoOK(iFarmSlotNum);
}

//! 나의 팜 슬롯을 초기화하는데 실패하였다.  
void CTRNetEventHandler::onRecvFarmClearFarmSlotInfoFailed(const eFarm_CLEAR_FARM_SLOTINFO_FAILED_REASON& failedReason)
{
	DBG_OUTPUT("onRecvFarmClearFarmSlotInfoFailed");
}
//! 팜관련 슬롯 맵정보를 얻는데 성공하였다.
void CTRNetEventHandler::onRecvFarmGetFarmMapSlotInfoOK( const int iFarmUniqueNum, 
														 const int iFarmMapType,
														 const int iFarmSkyBoxNum,
														 const int iFarmWeatherNum,
														 const std::vector<RecvFarmMapObjectInfo>& vecMapInfo,
														 const std::vector<RecvFarmMapVoxelsInfo>& vecVoxelInfo )
{
	CTRFarmUI::getInstance().onRecvFarmGetFarmMapSlotInfoOK(iFarmUniqueNum, iFarmMapType, iFarmSkyBoxNum, iFarmWeatherNum, vecMapInfo, vecVoxelInfo);
}

//! 팜관련 슬롯 맵정보를 얻는데 실패하였다.
void CTRNetEventHandler::onRecvFarmGetFarmMapSlotInfoFailed(const int iFarmUniqueNum)
{
	DBG_OUTPUT("onRecvFarmGetFarmMapSlotInfoFailed");
}

//! 나의 팜 슬롯을 불러오기 하는데 성공하였다.  
void CTRNetEventHandler::onRecvFarmGetFarmSlotInfoOK(const int newFarmMapType, std::vector<ItemMsgInfo> & vecItemMsgInfo)
{
	DBG_OUTPUT("onRecvFarmGetFarmSlotInfoOK");
	CTRItemTimeOverManager::getInstance().onRecvFarmGetFarmSlotInfoOK(vecItemMsgInfo);
	CTRFarmItemObjectManager::getInstance().removeAllObject();
	CTRFarmUI::getInstance().removeAllVoxel();
	CTRFarmMyroomUI::getInstance().onRecvFarmGetFarmSlotInfoOK();
	CNetClientManager::getInstance().requestUpdateFarmMapSlotInfo(CNetClientManager::getInstance().getMyFarmUniuqeNum());
}

//! 나의 팜 슬롯을 불러오기 하는데 실패하였다.  
void CTRNetEventHandler::onRecvFarmGetFarmSlotInfoFailed(const eFarm_GET_FARM_SLOTINFO_FAILED_REASON& failedReason)
{
	DBG_OUTPUT("onRecvFarmGetFarmSlotInfoFailed");
}

//! 나의 팜 슬롯을 결재 하는데 성공하였다.  
void CTRNetEventHandler::onRecvFarmPayFarmSlotResultOK(const int iFarmSlotNum)
{
	DBG_OUTPUT("onRecvFarmPayFarmSlotResultOK");
	CTRFarmMyroomUI::getInstance().onRecvFarmPayFarmSlotResultOK(iFarmSlotNum);
}

//! 나의 팜 슬롯을 결재 하는데 실패하였다.  
void CTRNetEventHandler::onRecvFarmPayFarmSlotResultFailed(const eFarm_PAY_FARM_SLOT_RESULT_FAILED_REASON& failedReason)
{
	DBG_OUTPUT("onRecvFarmPayFarmSlotResultFailed");
	CTRFarmMyroomUI::getInstance().onRecvFarmPayFarmSlotResultFailed(failedReason);
}

//! 나의 팜 번호를 얻는데 성공하였다.
void CTRNetEventHandler::onRecvFarmGetMyFarmUniqueNumOK(const int iFarmUniqueNum)
{
	DBG_OUTPUT("onRecvFarmGetMyFarmUniqueNumOK");
}

//! 나의 팜 정보를 얻는데 실패하였다.
void CTRNetEventHandler::onRecvFarmGetMyFarmUniqueNumFailed()
{
	DBG_OUTPUT("onRecvFarmGetMyFarmUniqueNumFailed");
}

//! 특정 팜의 퍼미션 정보를 얻는데 성공하였습니다.
void CTRNetEventHandler::onRecvFarmGetFarmPermisionInfoOK(const int iFarmUniqueNum, FarmPermisionInfo& rPermisionInfo)
{

}

//! 특정 팜의 퍼미션 정보를 얻는데 실패하였습니다.
void CTRNetEventHandler::onRecvFarmGetFarmPermisionInfoFailed(const int iFarmUniqueNum)
{

}

//! 팜 아이템의 능력치를 얻는데 성공하였다.
void CTRNetEventHandler::onRecvFarmGetFarmItemAttrListOK(const int iFarmUniqueNum, std::map< __int64, std::map<int, FarmItemAttrInfo > >& mapFamrItemAttr, const bool bGetOnlySetUpObjectAttrInfo, const bool bDataReplace)
{
	CTRFarmItemObjectManager::getInstance().onRecvFarmGetFarmItemAttrListOK(iFarmUniqueNum, mapFamrItemAttr, bGetOnlySetUpObjectAttrInfo, bDataReplace);
}

//! 자시늬 팜 아이템의 능력치를 얻는데 실패하였다.
void CTRNetEventHandler::onRecvFarmGetFarmItemAttrListFailed()
{
	DBG_OUTPUT("onRecvFarmGetFarmItemAttrListFailed");
}

//! 특정 팜의 퍼미션 정보 리스트를 얻는데 성공하였습니다.
void CTRNetEventHandler::onRecvFarmGetFarmPermisionInfoListOK(const int iFarmUniqueNum, std::vector<UserFarmPermisionInfo>&		rVecFarmPermisionInfo )
{

}

//! 특정 팜의 퍼미션 정보를 얻는데 실패하였습니다.
void CTRNetEventHandler::onRecvFarmGetFarmPermisionInfoListFailed(const int iFarmUniqueNum)
{
}

//!< 특정 팜의 사용기간이 종료되었습니다. 
void CTRNetEventHandler::onRecvFarmExpirationPeriodNotify(const int iFarmUniqueNum, const bool isExitFarmFlag)
{
	//! 삐에로나 옵져버일가 아닐경우만 방을 나간다.
	if(!(CNetClientManager::getInstance().isPiero() || CNetClientManager::getInstance().isObserver()))
	{
		CTRFarmChangeManager::getInstance().setMoveFarmLobby(true);
		CNetClientManager::getInstance().requestLeaveRoom();
	}

	COkDialogEx::getInstance().showDialog(_STR(MSG_USE_FARM_PERIOD_END), "gui\\ok.gui");
}

//!< 팜에 설치된 아이템이 제거되었다.
void CTRNetEventHandler::onRecvFarmDeleteMapItemNotify(const __int64 iOID)
{
	CKeepFarmItemList::getInstance().eraseItem(iOID);
	CTRFarmItemObjectManager::getInstance().setRemoveDelay(iOID);
	CTRFarmItemObjectManager::getInstance().deleteOnGridObject(iOID, true);
}

//!< 팜 포인트를 이용한 팜의 사용기간 갱신요청을 성공할 경우 호출. (요청한 유저에게만 전달된다.)
void CTRNetEventHandler::onRecvFarmRenewalPeriodByFarmPointOK(const int refreshFarmPoint, const FarmInfo myFarmInfo)
{
	CTRFarmLobbyUIDlg::getInstance().onRecvFarmRenewalPeriodNotifyOK(myFarmInfo);
}

//!< 팜 포인트를 이용한 팜의 사용기간 갱신요청을 실패할 경우 호출. (요청한 유저에게만 전달된다.)
void CTRNetEventHandler::onRecvFarmRenewalPeriodByFarmPointFailed(const eFarm_RENEWAL_FARM_PERIOD_FAILED_REASON failedReason)
{
	DBG_OUTPUT("onRecvFarmRenewalPeriodByFarmPointFailed");
}

//!< 팜 아이템을 이용한 팜의 사용기간 갱신요청을 성공할 경우 호출. (요청한 유저에게만 전달된다.)
void CTRNetEventHandler::onRecvFarmRenewalPeriodByItemOK(const int iRenewalItemDescNum, const FarmInfo myFarmInfo)
{	
	CTRFarmLobbyUIDlg::getInstance().onRecvFarmRenewalPeriodNotifyOK(myFarmInfo);
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iRenewalItemDescNum);

	vector<NetItemInfo> vecKeepTicketItemList;
	CKeepItemList::getInstance().getItemList(eCharacterKind_NONE, eFuncItemPosition_FARM_TICKET, vecKeepTicketItemList);
	if(!vecKeepTicketItemList.empty())
	{
		const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getItemInfo(vecKeepTicketItemList[0]);
		if(pItemInfo)
		{
			CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(pItemInfo->m_iUniqueNumber);
		}
	}
}

//!< 팜 아이템을 이용한 팜의 사용기간 갱신요청을 실패할 경우 호출. (요청한 유저에게만 전달된다.)
void CTRNetEventHandler::onRecvFarmRenewalPeriodByItemFailed(const eFarm_RENEWAL_FARM_PERIOD_FAILED_REASON failedReason)
{
	DBG_OUTPUT("onRecvFarmRenewalPeriodByItemFailed");
}

//!< 팜에 설치된 아이템에 특정 아이템을 사용할 경우 성공했을 때 호출. 
void CTRNetEventHandler::onRecvFarmUseFarmItemToFarmObjectOK(/* 정보 날려야하나.. */)
{

}

//!< 팜에 설치된 아이템에 특정 아이템을 사용할 경우 실패했을 때 호출. 
void CTRNetEventHandler::onRecvFarmUseFarmItemToFarmObjectFailed(const eFarm_USED_FARMITEM_TO_FARMOBJECT_FAILED_REASON failedReason/*itemtype, ...*/)
{
	DBG_OUTPUT("onRecvFarmUseFarmItemToFarmObjectFailed");
}

//!< 특정 유저의 팜 기간이 갱신되었을 경우 공통으로 전달되는 정보. (갱신된 방에 있는 팜장을 제외한 유저들에게 전송된다.)
void CTRNetEventHandler::onRecvFarmRenewalPeriodNotify(const int farmUniqueNum, const FarmInfo userFarmInfo)
{

}

//!< 팜 오브젝트 경험치 충전 요청에 대한 응답
void CTRNetEventHandler::onRecvFarmObjectExpCharge(const int iPlayerIndex, const __int64 iObjectID, const int iObjectExp, const int iFarmPoint, const int iPremiumFarmPoint, const int iView, int iChargeItemNum)
{
	CTRFarmUI::getInstance().onRecvFarmObjectExpCharge(iPlayerIndex, iObjectID, iObjectExp, iFarmPoint, iPremiumFarmPoint, iView, iChargeItemNum);
}

//!< 팜 오브젝트 경험치 충전이 알수 없는 이유로 실패했다.
void CTRNetEventHandler::onRecvFarmObjectExpChargeFailed(eServerResult eFailedReason)
{
	CTRFarmUI::getInstance().onRecvFarmObjectExpChargeFailed(eFailedReason);
	DBG_OUTPUT("CTRNetEventHandler::onRecvFarmObjectExpChargeFailed reason = %d", eFailedReason);
}

//!< 팜 오브젝트의 수확가능 개수 충전 요청이 성공했을 경우 호출. 
void CTRNetEventHandler::onRecvFarmObjectHarvestCountChargeOK( const __int64& appliedObjectID, const int& renewalCount, int iUsedItemDescNum)
{
	CTRFarmUI::getInstance().onRecvFarmObjectHarvestCountChargeOK(appliedObjectID, renewalCount, iUsedItemDescNum);
}

//!< 팜 오브젝트의 수확가능 개수 충전 요청이 실패했을 경우 호출. 
void CTRNetEventHandler::onRecvFarmObjectHarvestCountChargeFailed( const eFarm_OBJECT_HARVEST_COUNT_CHARGE_FAILED_REASON& failedReason)
{
	CTRFarmUI::getInstance().onRecvFarmObjectHarvestCountChargeFailed(failedReason);
	DBG_OUTPUT("CTRNetEventHandler::onRecvFarmObjectHarvestCountChargeFailed reason = %d", failedReason);
}

//!< 팜 동물의 사이즈 1단계 키우기 요청이 성공했을 경우 호출. 
void CTRNetEventHandler::onRecvFarmIncreaseAnimalSizeOK(const __int64 appliedObjectID, const int view)
{
	CTRFarmItemObjectManager::getInstance().onRecvFarmIncreaseAnimalSizeOK(appliedObjectID, view);
}

//!< 팜 동물의 사이즈 1단계 키우기 요청이 실패했을 경우 호출. 
void CTRNetEventHandler::onRecvFarmIncreaseAnimalSizeFailed(const __int64 failedObjectID, const eFarm_INCREASE_ANIMAL_SIZE_FAILED_REASON failedReason)
{
	string msg;

	switch(failedReason)
	{
	case eFarm_INCREASE_ANIMAL_SIZE_FAILED_REASON_UNKNOWN:					///< 알수없음. 
		msg = _STR(ERR_UNKNOWN);
		break;
	case eFarm_INCREASE_ANIMAL_SIZE_FAILED_REASON_DB_ERROR:					///< DB 에러. 
		msg = _STR(FAILED_FARM_INCREASE_ANIMAL_SIZE_DB_ERROR);
		break;
	case eFarm_INCREASE_ANIMAL_SIZE_FAILED_REASON_NOT_HAS_ITEMS_ERROR:		///< 보유한 아이템이 없음.  
		msg = _STR(FAILED_FARM_INCREASE_ANIMAL_SIZE_NOT_HAS_ITEMS_ERROR);
		break;
	case eFarm_INCREASE_ANIMAL_SIZE_FAILED_REASON_INVALID_TARGET_ERROR:		///< 사이즈 키우기 불가능한 오브젝트. 
		msg = _STR(FAILED_FARM_INCREASE_ANIMAL_SIZE_INVALID_TARGET_ERROR);
		break;
	case eFarm_INCREASE_ANIMAL_SIZE_FAILED_REASON_GROWTH_LEVEL_IS_MAX_ERROR: ///< 이미 동물이 최대 사이즈인 경우. 
		msg = _STR(FAILED_FARM_INCREASE_ANIMAL_SIZE_GROWTH_LEVEL_IS_MAX_ERROR);
		break;
	}

	DBG_OUTPUT("onRecvFarmIncreaseAnimalSizeFailed : %s", msg.c_str());
	COkDialogEx::getInstance().showDialog(msg);
}

//!< 팜 동물을 기본 사이즈로 복원 요청이 성공했을 경우 호출. 
void CTRNetEventHandler::onRecvFarmRestoreAnimalDefaultSizeOK(const __int64 appliedObjectID, const int view)
{
	CTRFarmItemObjectManager::getInstance().onRecvFarmRestoreAnimalDefaultSizeOK(appliedObjectID, view);
}

//!< 팜 동물을 기본 사이즈로 복원 요청이 실패했을 경우 호출. 
void CTRNetEventHandler::onRecvFarmRestoreAnimalDefaultSizeFailed(const __int64 failedObjectID, const eFarm_RESTORE_ANIMAL_DEFAULT_SIZE_FAILED_REASON failedReason)
{
	string msg;

	switch(failedReason)
	{
	case eFarm_RESTORE_ANIMAL_DEFAULT_SIZE_FAILED_REASON_UNKNOWN:						///< 알수없음. 
		msg = _STR(ERR_UNKNOWN);
		break;
	case eFarm_RESTORE_ANIMAL_DEFAULT_SIZE_FAILED_REASON_DB_ERROR:						///< DB 에러. 
		msg = _STR(FAILED_FARM_RESTORE_ANIMAL_DEFAULT_SIZE_DB_ERROR);
		break;
	case eFarm_RESTORE_ANIMAL_DEFAULT_SIZE_FAILED_REASON_NOT_HAS_ITEMS_ERROR:			///< 보유한 아이템이 없음.  
		msg = _STR(FAILED_FARM_RESTORE_ANIMAL_DEFAULT_SIZE_NOT_HAS_ITEMS_ERROR);
		break;
	case eFarm_RESTORE_ANIMAL_DEFAULT_SIZE_FAILED_REASON_INVALID_TARGET_ERROR:			///< 사이즈 복원 불가능한 오브젝트. 
		msg = _STR(FAILED_FARM_RESTORE_ANIMAL_DEFAULT_SIZE_INVALID_TARGET_ERROR);
		break;
	case eFarm_RESTORE_ANIMAL_DEFAULT_SIZE_FAILED_REASON_GROWTH_LEVEL_IS_DEFAULT_ERROR: ///< 사이즈 키우기 불가능한 오브젝트. 
		msg = _STR(FAILED_FARM_RESTORE_ANIMAL_DEFAULT_SIZE_GROWTH_LEVEL_IS_DEFAULT_ERROR);
		break;
	}

	DBG_OUTPUT("onRecvFarmRestoreAnimalDefaultSizeFailed : %s", msg.c_str());
	COkDialogEx::getInstance().showDialog(msg);
}

//!< 초대에 대한 응답처리 실패. 
void CTRNetEventHandler::onRecvFarmGoTogetherFarmRoomFailed(const eFarm_GO_TOGETHER_FARM_ROOM_FAILED_REASON& failedReason)
{
	string msg;
	switch(failedReason)
	{
	case eFarm_GO_TOGETHER_FARM_ROOM_FAILED_REASON_UNKNOWN:
		msg = _STR(FAILED_GO_TOGETHER_FARM_ROOM_FAILED_REASON_UNKNOWN);
		break;
	case eFarm_GO_TOGETHER_FARM_ROOM_FAILED_REASON_DB_ERROR:
		msg = _STR(FAILED_GO_TOGETHER_FARM_ROOM_FAILED_REASON_DB_ERROR);
		break;
	case eFarm_GO_TOGETHER_FARM_ROOM_FAILED_REASON_USER_FULL_ERROR:
		msg = _STR(FAILED_GO_TOGETHER_FARM_ROOM_FAILED_REASON_USER_FULL_ERROR);
		COkDialogEx::getInstance().showDialog(msg);
		break;
	case eFarm_GO_TOGETHER_FARM_ROOM_FAILED_REASON_NOT_EXIST_ROOM_ERROR:
		msg = _STR(FAILED_GO_TOGETHER_FARM_ROOM_FAILED_REASON_NOT_EXIST_ROOM_ERROR);
		COkDialogEx::getInstance().showDialog(msg);
		break;
	case eFarm_GO_TOGETHER_FARM_ROOM_FAILED_REASON_CHATTING_USER_LIMIT_ERROR:
		msg = _STR(FAILED_GO_TOGETHER_FARM_ROOM_FAILED_REASON_CHATTING_USER_LIMIT_ERROR);
		COkDialogEx::getInstance().showDialog(msg);
		break;
	}

	CTRFarmLobbyUIDlg::getInstance().setJoinRoom(false);
	m_pNetPlay->openFarmLobbyUI();

	DBG_OUTPUT("onRecvFarmGoTogetherFarmRoomFailed [%s]", msg.c_str());
}

//!< 팜 지형변경 아이템 사용 요청이 성공했을 경우 호출. 
//!< 성공시 반드시, 팜 맵 정보를 재요청해야한다. ( 팜주인만 받는 메세지 )
void CTRNetEventHandler::onRecvFarmChangeMapTypeOK(const int& farmUniqueNum, const int& newFarmMapType)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFarmChangeMapTypeOK farmUniqueNum=[%d], newFarmMapType=[%d]", farmUniqueNum, newFarmMapType);

	CTRGameRoomInfo & roominfo = m_pNetPlay->_getGameRoomInfo();
	roominfo.m_farmInfo.m_iFarmTypeNum = newFarmMapType;

	if(CTRFarmItemObjectManager::getInstance().isBuyItem())
	{
		std::map<__int64,int> mapItemID;
		CTRFarmItemObjectManager::getInstance().getBuyItemID(mapItemID);
		std::map<__int64,int>::iterator iter = mapItemID.begin();
		bool bCheckItem = false;
		bool bMapChange = false;
		while(iter != mapItemID.end())
		{
			const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getItemInfo(iter->second);
			if(pItemInfo && pItemInfo->m_pFarmItemInfo)
			{
				if(pItemInfo->m_pFarmItemInfo->isFarmSkyBoxItem())
				{
					CNetClientManager::getInstance().requestFarmChangeFarmSkyBoxType(pItemInfo->m_iUniqueNumber);
				}
				else if(pItemInfo->m_pFarmItemInfo->isFarmWeatherItem())
				{
					CNetClientManager::getInstance().requestFarmChangeWeatherType(pItemInfo->m_iUniqueNumber);
				}
				else 
				{
					if(pItemInfo->m_pFarmItemInfo->isFarmMapItem()) bMapChange = true;
					else bCheckItem = true;
				}
			}
			++iter;
		}

		if(bMapChange)
		{
			if(bCheckItem)
			{
				CTRFarmItemObjectManager::getInstance().onCheckItemSaveMap();
			}
			else
			{
				CTRFarmUI::getInstance().loadMap(roominfo.m_farmInfo);
				if(CTRFarmItemObjectManager::getInstance().checkItem(true))
				{
					CNetClientManager::getInstance().requestUpdateFarmMapInfo(farmUniqueNum);
				}
			}
		}
	}
	else
	{
		CNetClientManager::getInstance().requestUpdateFarmMapInfo(farmUniqueNum);
	}

	CTRFarmUI::getInstance().moveRevivalPoint();
}

//!< 팜 지형변경 아이템 사용 요청이 실패했을 경우 호출. 
void CTRNetEventHandler::onRecvFarmChangeMapTypeFailed( const eFarm_CHANGE_FARM_MAP_TYPE_FAILED_REASON& failedReason)
{
	string msg;
	switch(failedReason)
	{
	case eFarm_CHANGE_FARM_MAP_TYPE_FAILED_REASON_UNKNOWN:						///< 알수없음. 
		msg = _STR(ERR_UNKNOWN);
		break;
	case eFarm_CHANGE_FARM_MAP_TYPE_FAILED_REASON_DB_ERROR:						///< DB 에러. 
		msg = _STR(FAILED_CHANGE_FARM_MAP_TYPE_FAILED_REASON_DB_ERROR);
		break;
	case eFarm_CHANGE_FARM_MAP_TYPE_FAILED_REASON_NOT_HAS_FARM_ERROR:			///< 팜을 가지고 있지 않음. 
		msg = _STR(FAILED_CHANGE_FARM_MAP_TYPE_FAILED_REASON_NOT_HAS_FARM_ERROR);
		break;
	case eFarm_CHANGE_FARM_MAP_TYPE_FAILED_REASON_NOT_HAS_PERMISSION_ERROR:		///< 팜에 대한 권한을 가지고 있지 않음. 
		msg = _STR(FAILED_CHANGE_FARM_MAP_TYPE_FAILED_REASON_NOT_HAS_PERMISSION_ERROR);
		break;
	case eFarm_CHANGE_FARM_MAP_TYPE_FAILED_REASON_NOT_HAS_ITEMS_ERROR:			///< 보유한 아이템이 없음. 
		msg = _STR(FAILED_CHANGE_FARM_MAP_TYPE_FAILED_REASON_NOT_HAS_ITEMS_ERROR);
		break;
	}

	COkDialogEx::getInstance().showDialog(msg);
	DBG_OUTPUT("onRecvFarmChangeMapTypeFailed [%s]", msg.c_str());
}

//!< 팜 팻말의 내용을 받았다.
void CTRNetEventHandler::onRecvFarmNoticeBoardInfo(const __int64 iOID, const std::string & strBoardInfo)
{
	CTRFarmSignboardInputDlg::getInstance().showSignboard(iOID, strBoardInfo);
}

//!< 팜 팻말의 내용을 변경하였다.
void CTRNetEventHandler::onRecvFarmModifyNoticeBoardInfo(const __int64 iOID)
{
	CTRFarmSignboardInputDlg::getInstance().closeDialog();
	COkDialogEx::getInstance().showDialog(_STR(MSG_MODIFY_SIGNBOARD_INFO), "gui\\ok.gui");
}

//!< 팜 팻말의 내용 변경에 실패하였다.
void CTRNetEventHandler::onRecvFarmModifyNoticeBoardInfoFailed(const __int64 iOID)
{
	CTRFarmSignboardInputDlg::getInstance().closeDialog();
	COkDialogEx::getInstance().showDialog(_STR(FAILED_MODIFY_SIGNBOARD_INFO), "gui\\ok.gui");

	DBG_OUTPUT("CTRNetEventHandler::onRecvFarmModifyNoticeBoardInfoFailed");
}

//!< 팜 오브젝트의 속성 값 정보가 변경되었다.
void CTRNetEventHandler::onRecvFarmModifyObjectValueInfo(const __int64 iOID, const int iValue)
{
	CTRFarmUI::getInstance().onRecvFarmModifyObjectValueInfo(iOID, iValue);
}

//!< 팜 오브젝트의 뷰정보 변경에 실패하였다.
void CTRNetEventHandler::onRecvFarmModifyObjectValueInfoFailed(const __int64 iOID)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFarmModifyNoticeBoardInfoFailed");
}

//!< 팜 아이템을 사용해 스카이박스 변경을 성공했을 경우 호출.
void CTRNetEventHandler::onRecvFarmChangeSkyboxTypeOK(const int& farmUniqueNum, const int& newSkyBoxType)
{
	CTRGameRoomInfo & roominfo = m_pNetPlay->_getGameRoomInfo();
	roominfo.m_farmInfo.m_iFarmSkyBoxNum = newSkyBoxType;

	CTRFarmUI::getInstance().loadSkyBox(newSkyBoxType);
}

//!< 팜 아이템을 사용해 스카이박스 변경을 실패했을 경우 호출. 
void CTRNetEventHandler::onRecvFarmChangeSkyboxTypeFailed( const eFarm_CHANGE_FARM_SKYBOX_TYPE_FAILED_REASON& failedReason )
{
	string msg;
	switch(failedReason)
	{
	case eFarm_CHANGE_FARM_SKYBOX_TYPE_FAILED_REASON_UNKNOWN:						///< 알수없음. 
		msg = _STR(ERR_UNKNOWN);
		break;
	case eFarm_CHANGE_FARM_SKYBOX_TYPE_FAILED_REASON_DB_ERROR:						///< DB 에러. 
		msg = _STR(FAILED_CHANGE_FARM_SKYBOX_TYPE_FAILED_REASON_DB_ERROR);
		break;
	case eFarm_CHANGE_FARM_SKYBOX_TYPE_FAILED_REASON_NOT_HAS_FARM_ERROR:			///< 팜을 가지고 있지 않음. 
		msg = _STR(FAILED_CHANGE_FARM_MAP_TYPE_FAILED_REASON_NOT_HAS_FARM_ERROR);
		break;
	case eFarm_CHANGE_FARM_SKYBOX_TYPE_FAILED_REASON_NOT_HAS_PERMISSION_ERROR:		///< 팜에 대한 권한을 가지고 있지 않음. 
		msg = _STR(FAILED_CHANGE_FARM_MAP_TYPE_FAILED_REASON_NOT_HAS_PERMISSION_ERROR);
		break;
	case eFarm_CHANGE_FARM_SKYBOX_TYPE_FAILED_REASON_NOT_HAS_ITEMS_ERROR:			///< 보유한 아이템이 없음. 
		msg = _STR(FAILED_CHANGE_FARM_SKYBOX_TYPE_FAILED_REASON_NOT_HAS_ITEMS_ERROR);
		break;
	}

	COkDialogEx::getInstance().showDialog(msg);
	DBG_OUTPUT("onRecvFarmChangeSkyboxTypeFailed [%s]", msg.c_str());
}

//!< 팜 아이템을 사용해 날씨 변경을 성공했을 경우 호출. 
void CTRNetEventHandler::onRecvFarmChangeWeatherTypeOK(const int& farmUniqueNum, const int& newWeatherType)
{
	CTRGameRoomInfo & roominfo = m_pNetPlay->_getGameRoomInfo();
	roominfo.m_farmInfo.m_iFarmWeatherNum = newWeatherType;

	CTRFarmUI::getInstance().loadWeather(newWeatherType);
}

//!< 팜 아이템을 사용해 날씨 변경을 실패했을 경우 호출. 
void CTRNetEventHandler::onRecvFarmChangeWeatherTypeFailed( const eFarm_CHANGE_FARM_WEATHER_TYPE_FAILED_REASON& failedReason )
{
	string msg;
	switch(failedReason)
	{
	case eFarm_CHANGE_FARM_WEATHER_TYPE_FAILED_REASON_UNKNOWN:						///< 알수없음. 
		msg = _STR(ERR_UNKNOWN);
		break;
	case eFarm_CHANGE_FARM_WEATHER_TYPE_FAILED_REASON_DB_ERROR:						///< DB 에러. 
		msg = _STR(FAILED_CHANGE_FARM_WEATHER_TYPE_FAILED_REASON_DB_ERROR);
		break;
	case eFarm_CHANGE_FARM_WEATHER_TYPE_FAILED_REASON_NOT_HAS_FARM_ERROR:			///< 팜을 가지고 있지 않음. 
		msg = _STR(FAILED_CHANGE_FARM_MAP_TYPE_FAILED_REASON_NOT_HAS_FARM_ERROR);
		break;
	case eFarm_CHANGE_FARM_WEATHER_TYPE_FAILED_REASON_NOT_HAS_PERMISSION_ERROR:		///< 팜에 대한 권한을 가지고 있지 않음. 
		msg = _STR(FAILED_CHANGE_FARM_MAP_TYPE_FAILED_REASON_NOT_HAS_PERMISSION_ERROR);
		break;
	case eFarm_CHANGE_FARM_WEATHER_TYPE_FAILED_REASON_NOT_HAS_ITEMS_ERROR:			///< 보유한 아이템이 없음. 
		msg = _STR(FAILED_CHANGE_FARM_WEATHER_TYPE_FAILED_REASON_NOT_HAS_ITEMS_ERROR);
		break;
	}

	COkDialogEx::getInstance().showDialog(msg);
	DBG_OUTPUT("onRecvFarmChangeWeatherTypeFailed [%s]", msg.c_str());
}


//!< 팜 포인트를 이용한 아이템 구매를 성공했다. 
void CTRNetEventHandler::onRecvFarmBuyProductsUseFarmPointOK( const int& remainFarmPoint, std::vector<int> successItemList )
{
	CTRGameParkUI::getInstance().onRecvFarmBuyProductsUseFarmPointOK(remainFarmPoint, successItemList);
}

//!< 팜 포인트를 이용한 아이템 구매를 실패했다. 
void CTRNetEventHandler::onRecvFarmBuyProductsUseFarmPointFailed(const eFarm_BUY_PRODUCTS_USE_FARMPOINT_FAILED_REASON& failedReason)
{
	CTRGameParkUI::getInstance().onRecvFarmBuyProductsUseFarmPointFailed(failedReason);
}

/// 유저 정보를 얻는데 실패하였다. 
void CTRNetEventHandler::onRecvFarmGetMasterUserInfoFailed(const eFarm_GET_MASTER_USER_INFO_FAILED_REASON& failedReason, const int& farmUniqueNum)
{
	string msg;
	switch(failedReason)
	{
	case eFarm_GET_MASTER_USER_INFO_FAILED_REASON_UNKNOWN:						///< 알수없음. 
		msg = _STR(ERR_UNKNOWN);
		break;
	case eFarm_GET_MASTER_USER_INFO_FAILED_REASON_DB_ERROR:						///< DB 에러. 
		msg = _STR(FAILED_MASTER_USER_INFO_FAILED_REASON_DB_ERROR);
		break;
	case eFarm_GET_MASTER_USER_INFO_FAILED_REASON_INVALID_FARMUNIQUENUM_ERROR:	///< 유효하지 않은 팜의 정보를 요청하였음
		msg = _STR(FAILED_MASTER_USER_INFO_FAILED_REASON_INVALID_FARMUNIQUENUM_ERROR);
		break;
	}

	COkDialogEx::getInstance().showDialog(msg);
	DBG_OUTPUT("onRecvFarmGetMasterUserInfoFailed [%s]", msg.c_str());
}

/// 특정 팜의 아이템 속성정보가 갱신되었다는 통지를 받음. 
void CTRNetEventHandler::onRecvUpdateFarmItemPropertyNotify( std::vector<RecvFarmMapObjectInfo>& farmItemList )
{
	CTRFarmUI::getInstance().loadFarmObjects(farmItemList);
	TRDBG_OUTPUT_ERROR("onRecvUpdateFarmItemPropertyNotify farmItemList size : %d", (int)farmItemList.size());
}

/// 팜아이템의 기간 만료 여부 체크에 성공했다.
void CTRNetEventHandler::onRecvCheckFarmItemPeriodOK()
{
	CTRFarmUI::getInstance().onRecvCheckFarmItemPeriodOK();
}

/// 팜아이템의 기간 만료 여부 체크에 실패했다.
void CTRNetEventHandler::onRecvCheckFarmItemPeriodFailed(eServerResult eFailedReason)
{
	string msg;
	switch(eFailedReason)
	{
	case eServerResult_DB_FAILED_ACK:							///< 알수없음. 
		msg = _STR(ERR_UNKNOWN);
		break;
	}

	DBG_OUTPUT("onRecvCheckFarmItemPeriodFailed [%s]", msg.c_str());
	//COkDialogEx::getInstance().showDialog(msg);
}

/// 팜 아이템의 메시지를 받았다.
void CTRNetEventHandler::onRecvGetFarmItemMsgOK(const std::vector<ItemMsgInfo>& vecItemMsgInfo)
{
	CKeepFarmItemList::getInstance().onRecvGetFarmItemMsgOK(vecItemMsgInfo);
	CTRFarmUI::getInstance().onRecvGetFarmItemMsgOK(vecItemMsgInfo);
}

/// 팜 아이템의 메시지를 받는데 실패했다.
void CTRNetEventHandler::onRecvGetFarmItemMsgFailed(eServerResult eFailedReason)
{
	string msg;
	switch(eFailedReason)
	{
	case eServerResult_FARM_I_AM_NOT_IN_FARM:					///< 알수없음. 
		msg = _STR(ERR_UNKNOWN);
		break;
	}

	DBG_OUTPUT("onRecvGetFarmItemMsgFailed [%s]", msg.c_str());
	COkDialogEx::getInstance().showDialog(msg);
}
/// 팜 즐겨찾기 문에 정보를 셋팅했다.
void CTRNetEventHandler::onRecvSetFarmPortalInfo(const __int64 m_iObjectID, const int m_iFarmMasterUserNum, const std::string &m_strMemo)
{
	CTRFarmItemObjectManager::getInstance().onRecvSetFarmPortalInfoOk(m_iObjectID, m_iFarmMasterUserNum, m_strMemo);
	DBG_DEMO_OUTPUT("%s(line: %d) m_iObjectID: %I64d, m_iFarmMasterUserNum: %d, m_strMemo: %s",__FUNCTION__,__LINE__,m_iObjectID,m_iFarmMasterUserNum,m_strMemo.data());
}

/// 팜 즐겨찾기 문의 정보 셋팅을 실패했다.
void CTRNetEventHandler::onRecvSetFarmPortalInfoFailed(const eFarm_SET_FARM_PORTAL_INFO_FAILED_REASON eFailedReason)
{
	string msg;
	switch(eFailedReason)
	{
		case eFarm_SET_FARM_PORTAL_INFO_FAILED_REASON_DB_ERROR:					///< DB 에러
			msg = _STR(ERR_UNKNOWN);
			break;
		case eFarm_SET_FARM_PORTAL_INFO_FAILED_REASON_INVALID_NICKNAME:			///< 유효하지 않은 닉네임
			msg = _STR(FAILED_FARM_PORTAL_SET_INVALID_NICKNAME);
			break;
		case eFarm_SET_FARM_PORTAL_INFO_FAILED_REASON_NOT_EXIST_NICKNAME:		///< 존재하지 않은 닉네임
			msg = _STR(FAILED_FARM_PORTAL_SET_NOT_EXIST_NICKNAME);
			break;
	}
	if (msg.size())
	{
		COkDialogEx::getInstance().showDialog(msg);
	}
	DBG_DEMO_OUTPUT("%s(line: %d) eFailedReason: %d",__FUNCTION__,__LINE__,eFailedReason);
}

/// 팜 즐겨찾기 문의 정보를 받았다.
void CTRNetEventHandler::onRecvGetFarmPortalInfo(const __int64 iObjectID, const int iFarmMasterUserNum, const std::string &strFarmMasterNickname, const std::string &strMemo)
{
	CTRFarmItemObjectManager::getInstance().onRecvGetFarmPortalInfoOk(iObjectID, iFarmMasterUserNum, strFarmMasterNickname, strMemo);
	DBG_DEMO_OUTPUT("%s(line: %d) m_iObjectID: %I64d, strFarmMasterNickname: %s, m_strMemo: %s",__FUNCTION__,__LINE__,iObjectID,strFarmMasterNickname.data(),strMemo.data());
}

/// 팜 즐겨찾기 문의 정보 받기를 실패했다.
void CTRNetEventHandler::onRecvGetFarmPortalInfoFailed(const eFarm_GET_FARM_PORTAL_INFO_FAILED_REASON eFailedReason)
{
	string msg;
	switch(eFailedReason)
	{
	case eFarm_SET_FARM_PORTAL_INFO_FAILED_REASON_DB_ERROR:					///< DB 에러
		msg = _STR(ERR_UNKNOWN);
		break;
	}
	if (msg.size())
	{
		COkDialogEx::getInstance().showDialog(msg);
	}
	DBG_DEMO_OUTPUT("%s(line: %d) eFailedReason: %d",__FUNCTION__,__LINE__,eFailedReason);
}

//! 채팅팜 신고요청이 처리되었다.
void CTRNetEventHandler::onRecvAccuseChattingFarm(int iFarmUniqueNum, int iCautionCount)
{
	CTRShortTimeMessage::getInstance().showMessage(_STR(INFORMATION_ABUSEREPORT));
	DBG_DEMO_OUTPUT("%s(line: %d) Success abuse. Farm UniqueNum : %d , Caution Count : %d", __FUNCTION__, __LINE__, iFarmUniqueNum, iCautionCount);
}

//! 채팅팜 신고요청이 실패했다.
void CTRNetEventHandler::onRecvAccuseChattingFarmFailed(int iFarmUniqueNum)
{
	CTRShortTimeMessage::getInstance().showMessage(_STR(INFORMATION_ABUSEREPORT_DUPLICATION));
	DBG_DEMO_OUTPUT("%s(line: %d) Failed abuse. Farm UniqueNum : %d", __FUNCTION__, __LINE__, iFarmUniqueNum);
}

void CTRNetEventHandler::onRecvFarmObjectInfo(const int farmUniqueNum, const UINT iGameIndex, std::vector<FarmItemInfo>& farmItemList)
{
	CTRFarmItemObjectManager::getInstance().onRecvFarmObjectInfo(farmUniqueNum,iGameIndex,farmItemList);

	if (CNetClientManager::getInstance().getMyFarmUniuqeNum() == farmUniqueNum)
	{
		CKeepFarmItemList::getInstance().onRecvFarmItemList(farmItemList,true);
	}
}

void CTRNetEventHandler::onRecvFarmNameTagSetting( const unsigned int iPlayerIndex, const unsigned int iItemKind, const std::string& strNameTag )
{
	CTRFarmUI::getInstance().onRecvFarmNameTagSetting(iPlayerIndex, iItemKind, strNameTag);
}

void CTRNetEventHandler::onRecvFarmNameTagCheck(const unsigned int iPlayerIndex, const std::string& strNameTag)
{
}

void CTRNetEventHandler::onRecvFarmNameTagNewUser(std::map<unsigned int, NameTagInfo>& mapFarmNameTagList)
{
	CTRFarmUI::getInstance().onRecvFarmNameTagNewUser(mapFarmNameTagList);
}

void CTRNetEventHandler::onRecvLeaveRoom(unsigned int iPlayerIndex)
{
	if(CTRFarmUI::getInstance().isActive())
	{
		CTRFarmUI::getInstance().onRecvFarmNameTagMasterTag(iPlayerIndex);
	}
}

void CTRNetEventHandler::onRecvFarmNameTagFliled(const eFarmNameTagResult& result)
{

}

void CTRNetEventHandler::onRecvFarmNameTagRemove(const unsigned int iPlayerIndex)
{
	CTRFarmUI::getInstance().onRecvFarmNameTagRemove(iPlayerIndex);
}


/// 팜에서 쓰이는 응답들 끝
//////////////////////////////////////////////////////////////////////////

void CTRNetEventHandler::onRecvMyRoomTransaction(const bool& bTransaction)
{
}

/// 마이룸에서 나의 캐릭터들의 리스트를 얻었다.
void CTRNetEventHandler::onRecvMyRoomMyCharacterList(const std::vector < cpk_type > & characterList)
{
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvMyRoomMyCharacterList(characterList);
#endif
	CTRShopDlg::getInstance().onRecvMyRoomMyCharacterList(characterList);
	CTRMyroomDlg::getInstance().onRecvMyRoomMyCharacterList(characterList);
	CTRMawooShopDlg::getInstance().onRecvMyRoomMyCharacterList(characterList);

	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvMyRoomMyCharacterList(characterList);
	else  CTRAlchemistUI::getInstance().onRecvMyRoomMyCharacterList(characterList);

	if(CTRGuildFarmUI::getInstance().isActive()) CTRGuildFarmUI::getInstance().onRecvMyRoomMyCharacterList(characterList);

	CTRPeriodCharacterTimeoutManager::getInstance().onRecvMyRoomMyCharacterList(characterList);
	CMissionMsgDispatcher::getInstance().setMyCharacterList(characterList);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HAS_ITEM);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_NOT_EXIST_ITEM);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
	
	if(m_pNetPlay && m_pNetPlay->inRoom())
	{
		m_pNetPlay->setThisCanReadyState(false);
	}
}

/// 마이룸에서 나의 캐릭터들의 리스트를 얻는데 실패했다. 치명적인 오류다.
void CTRNetEventHandler::onRecvMyRoomMyCharacterListFail()
{
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvMyRoomMyCharacterListFail();
#endif
	CTRShopDlg::getInstance().onRecvMyRoomMyCharacterListFail();
	CTRMyroomDlg::getInstance().onRecvMyRoomMyCharacterListFail();
	CTRMawooShopDlg::getInstance().onRecvMyRoomMyCharacterListFail();

	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvMyRoomMyCharacterListFail();
	else  CTRAlchemistUI::getInstance().onRecvMyRoomMyCharacterListFail();

	if(CTRGuildFarmUI::getInstance().isActive()) CTRGuildFarmUI::getInstance().onRecvMyRoomMyCharacterListFail();

	CTRPeriodCharacterTimeoutManager::getInstance().onRecvMyRoomMyCharacterListFail();
}

/// 마이룸에서 특정 캐릭터의 설정을 얻었다.
void CTRNetEventHandler::onRecvMyRoomGetMyCharacterSetting(const AvatarInfo & realAvatarInfo)
{
	CNetClientManager::getInstance().requestItemMsg();
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvMyRoomGetMyCharacterSetting(realAvatarInfo);
#endif
	CTRShopDlg::getInstance().onRecvMyRoomGetMyCharacterSetting(realAvatarInfo);
	CTRMyroomDlg::getInstance().onRecvMyRoomGetMyCharacterSetting(realAvatarInfo);
	CTRMawooShopDlg::getInstance().onRecvMyRoomGetMyCharacterSetting(realAvatarInfo);

	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvMyRoomGetMyCharacterSetting(realAvatarInfo);
	else  CTRAlchemistUI::getInstance().onRecvMyRoomGetMyCharacterSetting(realAvatarInfo);

	if(CTRGuildFarmUI::getInstance().isActive())	CTRGuildFarmUI::getInstance().onRecvMyRoomGetMyCharacterSetting(realAvatarInfo);

	CTRPeriodCharacterTimeoutManager::getInstance().onRecvMyRoomGetMyCharacterSetting(realAvatarInfo);
}

/// 마이룸에서 특정 캐릭터의 설정을 얻는데 실패했다.
void CTRNetEventHandler::onRecvMyRoomGetMyCharacterSettingFail()
{
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvMyRoomGetMyCharacterSettingFail();
#endif
	CTRShopDlg::getInstance().onRecvMyRoomGetMyCharacterSettingFail();
	CTRMyroomDlg::getInstance().onRecvMyRoomGetMyCharacterSettingFail();
	CTRMawooShopDlg::getInstance().onRecvMyRoomGetMyCharacterSettingFail();
	if(CTRGuildFarmUI::getInstance().isActive())	CTRGuildFarmUI::getInstance().onRecvMyRoomGetMyCharacterSettingFail();
	CTRPeriodCharacterTimeoutManager::getInstance().onRecvMyRoomGetMyCharacterSettingFail();
}


/// 마이룸에서 특정 캐릭터의 설정을 저장하는 데 성공했다.
void CTRNetEventHandler::onRecvMyRoomSetCharacterSetting()
{
	DBG_OUTPUT("%s", __FUNCTION__);
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvMyRoomSetCharacterSetting();
#endif
	CTRMyroomDlg::getInstance().onRecvMyRoomSetCharacterSetting();
	CTRShopDlg::getInstance().onRecvMyRoomSetCharacterSetting();
	CTRCoupleSystem::getInstacne().onRecvMyRoomSetCharacterSetting();
	CTRPeriodCharacterTimeoutManager::getInstance().onRecvMyRoomSetCharacterSetting();
	CTRGuildFarmUI::getInstance().onRecvMyRoomSetCharacterSetting();
	CTRMawooShopDlg::getInstance().onRecvMyRoomSetCharacterSetting();
	CTRUserBookDlg::getInstance().onRecvMyRoomSetCharacterSetting();
	CTRGuildDlg::getInstance().onRecvMyRoomSetCharacterSetting();
	CTRGameParkUI::getInstance().onRecvMyRoomSetCharacterSetting();
	CTRFarmUI::getInstance().onRecvMyRoomSetCharacterSetting();

	if (m_pNetEventListener)
	{
		m_pNetEventListener->onRecvMyRoomSetCharacterSetting();
	}
	
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_DEFAULT_CHARACTER_NUMBER);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 마이룸에서 특정 캐릭터의 설정을 저장하는 데 실패했다.
void CTRNetEventHandler::onRecvMyRoomSetCharacterSettingFail()
{
	DBG_OUTPUT("%s", __FUNCTION__);
	CTRMyroomDlg::getInstance().onRecvMyRoomSetCharacterSettingFail();
	CTRPeriodCharacterTimeoutManager::getInstance().onRecvMyRoomSetCharacterSettingFail();
	CNetClientManager::getInstance().requestItemMsg();
	CTRGameParkUI::getInstance().onRecvMyRoomSetCharacterSettingFail();
	CTRFarmUI::getInstance().onRecvMyRoomSetCharacterSettingFail();
	CTRGuildFarmUI::getInstance().onRecvMyRoomSetCharacterSettingFail();
}

///마이룸에서 TR 영구 아이템을 되 파는데 성공 했다.
void CTRNetEventHandler::onRecvSellTRItemOK(int iItemNum, int iSellPrice)
{
	string strMessage = _STR(MSG_SUCCESS_SELL_TRITEM);

	const CItemInfoNode * pIteminfo = CClientItemList::getInstance().getItemInfo(iItemNum);

	if(pIteminfo != NULL)
	{
		strMessage = format(strMessage.c_str(),pIteminfo->m_name.c_str(),iSellPrice);

		COkDialogEx::getInstance().showDialog(strMessage);

		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iItemNum);
		CNetClientManager::getInstance().requestCurrentTR();		
	}
}

///마이룸에서 TR 영구 아이템을 되 파는데 실패 했다.
void CTRNetEventHandler::onRecvSellTRItemFailed(eSellTRItemFailedReason eFailedReason)
{
	DBG_OUTPUT("onRecvSellTRItemFailed[%d]",(int)eFailedReason);
	string strErrorMsg;

	switch(eFailedReason)
	{
	default:
	case eSellTRItemFailedReason_DB_ERROR:
	case eSellTRItemFailedReason_NOT_EXIST_SERVER_SETTING:
	case eSellTRItemFailedReason_ITEM_DELETE_FAILED:
		strErrorMsg =_STR(FAILED_SELL_ITEM_UNKNOWN);
		break;
	case eSellTRItemFailedReason_NOT_HAS_ITEM:
		strErrorMsg =_STR(FAILED_SELL_ITEM_NOT_HAS_ITEM);
		break;
	case eSellTRItemFailedReason_UNSELLABLE_ITEM:
		strErrorMsg =_STR(FAILED_SELL_ITEM_UNSELLABLE_ITEM);
		break;
	case eSellTRItemFailedReason_TR_ITEM_SALE_IS_DISABLED:
		strErrorMsg =_STR(FAILED_SELL_ITEM_SALE_IS_DISABLED);
		break;
	case eSellTRItemFailedReason_USING_ITEM:
		strErrorMsg =_STR(MSG_SELL_TRITEM_ERROR_USINGITEM);
		break;
	}	
	COkDialogEx::getInstance().showDialog(strErrorMsg);	

	CTRMyRoomGoodsListDialog::getInstance().update();
}

/// 기본 캐릭터 설정을 저장하는데 성공했다.
void CTRNetEventHandler::onRecvMyRoomSetDefaultCharacterOK()
{
	DBG_OUTPUT("%s", __FUNCTION__);
	CTRMyroomDlg::getInstance().onRecvMyRoomSetDefaultCharacterOK();

	if (m_pNetEventListener)
	{
		m_pNetEventListener->onRecvMyRoomSetDefaultCharacterOK();
	}

	if(m_pNetPlay && m_pNetPlay->inRoom())
	{
		const CGameUserInfo *pThisGameUser = m_pNetPlay->getThisGameUser();
		if(pThisGameUser)
		{
			m_pNetPlay->setThisCanReadyState(!pThisGameUser->m_bReadyState);
		}
	}

	//! 아이템 속성을 다시 얻어 온다.[신연금 관련]
	CNetClientManager::getInstance().requestUserItemAttr();
	if(CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvMyRoomSetDefaultCharacterOK();
	else  CTRAlchemistUI::getInstance().onRecvMyRoomSetDefaultCharacterOK();
}

/// 기본 캐릭터 설정을 저장하는데 실패했다.
void CTRNetEventHandler::onRecvMyRoomSetDefaultCharacterFail()
{
	DBG_OUTPUT("%s", __FUNCTION__);
	CTRMyroomDlg::getInstance().onRecvMyRoomSetDefaultCharacterFail();
}

/// 케릭터 스탯 리셋 성공했다.
void CTRNetEventHandler::onRecvMyRoomCharacterStatResetOK(const int iStatNum, const UserItemAttrInfo & charAttr)
{
	if(CTRMyroomDlg::getInstance().isVisible()) CTRMyroomDlg::getInstance().onRecvMyRoomCharacterStatResetOK(iStatNum, charAttr);
	else if(CTRShopDlg::getInstance().isVisible()) CTRShopDlg::getInstance().onRecvMyRoomCharacterStatResetOK(iStatNum, charAttr);
	else if(CTRMawooShopDlg::getInstance().isVisible()) CTRMawooShopDlg::getInstance().onRecvMyRoomCharacterStatResetOK(iStatNum, charAttr);
	else if(CTRGuildFarmUI::getInstance().isActive()) CTRGuildFarmUI::getInstance().onRecvMyRoomCharacterStatResetOK(iStatNum, charAttr);
}

/// 케릭터 스탯 리셋 실패했다.
void CTRNetEventHandler::onRecvMyRoomCharacterStatResetFail(eMyRoomProtocol_STAT_RESET_FAILED_REASON failedReason)
{
	if(CTRMyroomDlg::getInstance().isVisible()) CTRMyroomDlg::getInstance().onRecvCharacterStatResetFail(failedReason);
	else if(CTRShopDlg::getInstance().isVisible()) CTRShopDlg::getInstance().onRecvCharacterStatResetFail(failedReason);
	else if(CTRMawooShopDlg::getInstance().isVisible()) CTRMawooShopDlg::getInstance().onRecvCharacterStatResetFail(failedReason);
	else if(CTRGuildFarmUI::getInstance().isActive()) CTRGuildFarmUI::getInstance().onRecvCharacterStatResetFail(failedReason);
}

/// 케릭터 스탯 리셋 동의 성공했다.
void CTRNetEventHandler::onRecvMyRoomCharacterStatConfirmOK(const UserItemAttrInfo& useritemAttr)
{
	if(CTRMyroomDlg::getInstance().isVisible())
	{		
		CTRMyroomDlg::getInstance().onRecvMyRoomCharacterStatConfirmOK();
		CTRMyroomDlg::getInstance().updateCharPropertyBar();	
	}
	else if(CTRShopDlg::getInstance().isVisible())
	{		
		CTRShopDlg::getInstance().onRecvMyRoomCharacterStatConfirmOK();
		CTRShopDlg::getInstance().updateCharPropertyBar();
	}
	else if(CTRMawooShopDlg::getInstance().isVisible())
	{		
		CTRMawooShopDlg::getInstance().onRecvMyRoomCharacterStatConfirmOK();
		CTRMawooShopDlg::getInstance().updateCharPropertyBar();
	}
	else if(CTRGuildFarmUI::getInstance().isActive())
	{		
		CTRGuildFarmUI::getInstance().onRecvMyRoomCharacterStatConfirmOK();
		CTRGuildFarmUI::getInstance().updateCharPropertyBar();
	}
}

/// 케릭터 스탯 리셋 동의 실패했다.
void CTRNetEventHandler::onRecvMyRoomCharacterStatConfirmFail(eMyRoomProtocol_STAT_RESET_FAILED_REASON failedReason)
{
	if(CTRMyroomDlg::getInstance().isVisible()) CTRMyroomDlg::getInstance().onRecvCharacterStatResetFail(failedReason);
	else if(CTRShopDlg::getInstance().isVisible()) CTRShopDlg::getInstance().onRecvCharacterStatResetFail(failedReason);
	else if(CTRMawooShopDlg::getInstance().isVisible()) CTRMawooShopDlg::getInstance().onRecvCharacterStatResetFail(failedReason);
	else if(CTRGuildFarmUI::getInstance().isActive()) CTRGuildFarmUI::getInstance().onRecvCharacterStatResetFail(failedReason);
}

/// 나의 도전과제진행 정보 리스트를 받았다.
void CTRNetEventHandler::onRecvChallengeUserMissionInfo(std::map <int,UserChallengeInfo> mUserChallengeInfoList)
{
	DBG_OUTPUT("%s - list size : %d", __FUNCTION__, (int)mUserChallengeInfoList.size());

//	CTRChallengeSubjectManager:::getInstance().onRecvChallengeUserMissionInfo(mUserChallengeInfoList);	
}
/// 나의 도전과제정보의 갱신결과를 받았다.(그룹 단위)
void CTRNetEventHandler::onRecvChallengeUpdateGroupResult(const int iGroupNum, const int iSubNum, const bool bComplete, const int iAchieveNum, const eRewardCondition iRewardClass)
{
	UserChallengeInfo ChallengeInfo;
	ChallengeInfo.iGroupNum	= iGroupNum;
	ChallengeInfo.iGroupChallengeNum = iSubNum;
	ChallengeInfo.bComplete	= bComplete;
	ChallengeInfo.iAchievePoint = iAchieveNum;
//	CTRChallengeSubjectManager:::getInstance().onRecvChallengeUpdateGroupResult(ChallengeInfo,iRewardClass);
}

/// 도전과제정보 갱신이 실패했다.(그룹 단위)
void CTRNetEventHandler::onRecvChallengeUpdateGroupResultDBFailed(const int iGroupNum)
{
	TRDBG_OUTPUT_ERROR("CTRNetEventHandler::onRecvChallengeUpdateGroupResultDBFailed iGroupNum = %d", iGroupNum);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 통합미션관련..

/// 모든 미션 리스트를 받았다.
void CTRNetEventHandler::onRecvMissionInfo(std::vector<MissionInfoForClient>& missionInfo)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionInfo(missionInfo);
}

/// 유저의 미션 리스트를 받았다.
void CTRNetEventHandler::onRecvMissionUserListOK(const MissionUserInfoMap& missionUserInfo)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserListOK(missionUserInfo);

	//!< 일일 미션의 각 미션 리스트를 요청한다.
	std::vector<eMissionKind> missionKindList;
	missionKindList.push_back(eMissionKind_ONEDAY_MAIN);
	missionKindList.push_back(eMissionKind_ONEDAY_SPECIAL);

#ifdef CONTENTS_ONEDAY_MISSION_PCROOM
	missionKindList.push_back(eMissionKind_ONEDAY_PCROOM);
#endif

	if(CTROneDayMissionManager::getInstance().isEventMissionDay())
		missionKindList.push_back(eMissionKind_ONEDAY_EVENT);

	CNetClientManager::getInstance().requestOneDayMissionGetUserOneDayMissionList(missionKindList);

	//! 일일미션 완료 횟수 요청
	CNetClientManager::getInstance().requestOneDayMissionGetUserMissionFinishCount();

#ifdef CONTENTS_OPTIONAL_MISSSION
	
	//!< !! 기능성 미션 자동도전 옵션 추가로 서버에서 관리하여 도전함. !!
	
	/*std::vector<eOptionalMissionType> filter;
	if(CNetClientManager::getInstance().isPremiumPCRoom())
	{
		filter.push_back(eOptionalMissionType_Access_Maintain_PC);
	}
	else
	{
		filter.push_back(eOptionalMissionType_Access_Maintain);
	}	
	filter.push_back(eOptionalMissionType_Map_Clear);
	filter.push_back(eOptionalMissionType_Commuter_Ticket_Reward);	//!< 정액권이 있을 때 무조건 진행되므로 추가

	CTROptionalMissionManager::getInstance().onRequestAddMissionFiltered(filter);*/
	

	//!< 기능성 미션 추가 정보 요청 (완료 횟수)
	CNetClientManager::getInstance().requestOptionalMissionGetUserInfo();

#endif

#if defined(COLLECTION_SYSTEM) && defined(CONSTELLATION_COLLECTION_MISSION)
    CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_Constellation);
#endif

#if defined(COLLECTION_SYSTEM) && defined(TREASURE_HUNT_MISSION)
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_TreasureHunt);
#endif

#if defined(COLLECTION_SYSTEM) && defined(SUN_MOON_STAR_COLLECTION_MISSION)
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_SunMoonStar);
#endif

#if defined(COLLECTION_SYSTEM) && defined(OLYMPOS_COLLECTION_MISSION)
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_Olympos);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_Olympos_2);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_Olympos_3);
#endif

#ifdef COLLECTION_SYSTEM
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_AnimalGods_1);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_AnimalGods_2);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_AnimalGods_3);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_AngelAndDevil_1);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_AngelAndDevil_2);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_AngelAndDevil_3);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_AngelAndDevil_4);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_BirthDayFlower_1);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_BirthDayFlower_2);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_BirthDayFlower_3);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_TAROT_CARD_1);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_TAROT_CARD_2);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_TAROT_CARD_3);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_SeaSecret);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_Chess_1);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_Chess_2);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_Chess_3);
	CNetClientManager::getInstance().requestCollectionMissionGetUserMissionList(eCollectionType_Darjeeling);
#endif

#ifdef CONTENTS_HUG
	//간편 유저는 허그 시스템을 시작하지 않는다.
	if(!CNetClientManager::getInstance().isSimpleIDUser())
	{
		//! 게임 플레이 중이 아닐때에만 허그 시스템 시작요청한다
		if (!m_pNetPlay->isGameStatePlaying())
		{
			//! 허그 조건 확인 해서 일일 허그 시스템 시작 요청
			CTRHugSystemManager::getInstance().onStartHugSystem();
		}
	}
#endif

	//!< 미션 목록을 받았을 때 바로 채널 입장 체크를 하기 위해 추가함
	if(CChannelRoomMode::getInstance().getChannelMode() == CChannelRoomMode::CHANNELMODE_LOBBY_QUEST_CHANNEL)
	{
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_GUI_EVENT, eMissionConditionGUIEventType_ENTER_LOBBY_QUEST_CHANNEL);
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();
	}

#ifdef _TUTORIAL_RENEWAL_
#ifdef LOBBY_QUEST_CHANNEL_SYSTEM
#ifndef _TUTORIAL_CHANNEL_
	eQuestChallengeState eQuestState = eQuestChallengeState_NOT_PROCEEDING;
	CTRLobbyQuestManager::getInstance().getQuestState(eQuestState, 1);
	CTRLobbyUI::getInstance().openLobbyQuestStart(eQuestState != eQuestChallengeState_REWARD_COMPLETE && CNetClientManager::getInstance().getMyLevel() < eUserJoinLevel_POWER_WINGBOOTS);
#endif
#endif
#endif

#ifdef _NEWBIE_RETURNER_
	CTRNewbieReturnerMissionManager::getInstance().onMissionAdd();
#endif
}

/// 유저의 미션 리스트 받기를 실패했다.
void CTRNetEventHandler::onRecvMissionUserListFailed(const eMissionFailedReason failedReason)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserListFailed(failedReason);
}

/// 유저의 미션 리스트에 미션 추가를 성공했다.
void CTRNetEventHandler::onRecvMissionUserMissionAddOK(const MissionRequestInfo& requestInfo, const time_type& challengeExpireTime)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserMissionAddOK(requestInfo,challengeExpireTime);

	CTRUserBookDlg::getInstance().showEmblem(true, 0, requestInfo.m_iMissionNum);

#ifdef _NEWBIE_RETURNER_
	if(requestInfo.m_eMissionKind == eMissionKind_NEWBIE_RETURNER)
		CTRNetPlayManager::getInstance().showNewbieReturnerRewardDlg(true);
#endif
}

/// 유저의 미션 리스트에 미션 추가를 실패했다.
void CTRNetEventHandler::onRecvMissionUserMissionAddFailed(const MissionRequestInfo& requestInfo, const eMissionFailedReason failedReason)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserMissionAddFailed(requestInfo,failedReason);
}

/// 특정 시간에 유저의 일일 미션 도전 리스트 추가 통지
void CTRNetEventHandler::onRecvMissionUserMissionGroupAddOK(std::vector<MissionRequestDetailInfo>& requestInfo)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserMissionGroupAddOK(requestInfo);

#ifdef CONTENTS_HUG
	CTRHugSystemManager::getInstance().onRecvMissionUserMissionGroupAddOK();
#endif
}

/// 특정 시간에 유저의 일일 미션 도전 리스트 추가 실패 통지
void CTRNetEventHandler::onRecvMissionUserMissionGroupAddFailed(const eMissionKind missionKind, const eMissionFailedReason failedReason)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserMissionGroupAddFailed(missionKind, failedReason);
}

/// 유저의 미션 리스트의 미션 제거를 성공했다.
void CTRNetEventHandler::onRecvMissionUserMissionRemoveOK(const MissionRequestInfo& requestInfo)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserMissionRemoveOK(requestInfo);

	CTRUserBookDlg::getInstance().showEmblem(true, 0, requestInfo.m_iMissionNum);
}

/// 유저의 미션 리스트의 미션 제거를 실패했다.
void CTRNetEventHandler::onRecvMissionUserMissionRemoveFailed(const MissionRequestInfo& requestInfo, const eMissionFailedReason failedReason)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserMissionRemoveFailed(requestInfo,failedReason);
}

/// 유저의 미션 리스트 업데이트를 성공했다.
void CTRNetEventHandler::onRecvMissionUserMissionUpdateOK(const MissionRequestInfo& requestInfo, const MissionConditionAchievedPoint& achievedPoint)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserMissionUpdateOK(requestInfo,achievedPoint);
}

/// 유저의 미션 리스트 업데이트를 실패했다.
void CTRNetEventHandler::onRecvMissionUserMissionUpdateFailed(const MissionRequestInfo& requestInfo, const int conditionNum, const eMissionFailedReason failedReason)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserMissionUpdateFailed(requestInfo,conditionNum,failedReason);
}

/// 유저의 미션이 완료되었음을 알린다.
void CTRNetEventHandler::onRecvMissionUserMissionCompleteCheckOK(const MissionRequestInfo& requestInfo, const eMissionCompleteType checkTyp)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserMissionCompleteCheckOK(requestInfo,checkTyp);	

#ifdef CONTENTS_HUG
	//<! 주의! 현재 허그 시스템이 사용하는 미션 숫자가 하나라서 미션 옵저버 상속받지 않고 작업됨. 추후 미션 추가 시 옵저버 등록해서 재작업 해야합니다.
 	if (CTRHugSystemManager::getInstance().isHugMission(requestInfo.m_eMissionKind))
 	{
 		CTRHugSystemManager::getInstance().onRecvMissionUserMissionCompleteCheckOK(requestInfo, checkTyp);
 	}
#endif
}

#ifdef CONTENTS_OPTIONAL_MISSSION
/// 기능성 미션 전용
void CTRNetEventHandler::onRecvMissionUserMissionCompleteCheckOK_For_OptionalMission(const MissionRequestInfo& requestInfo, const eMissionCompleteType completeType, const int completeCount)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserMissionCompleteCheckOK(requestInfo, completeType);
    
	CTROptionalMissionManager::getInstance().onRecvMissionCompleteCount(requestInfo.m_iMissionNum, completeCount);;
}
#endif

/// 유저의 미션이 완료되지 않았음을 알린다.
void CTRNetEventHandler::onRecvMissionUserMissionCompleteCheckFailed(const MissionRequestInfo& requestInfo, const int conditionNum, const eMissionFailedReason& failedReason)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionUserMissionCompleteCheckFailed(requestInfo,conditionNum,failedReason);
}

/// 유저가 완료한 미션의 보상 받기를 성공했다.
void CTRNetEventHandler::onRecvMissionGiveRewardOK(const std::vector<MissionRequestInfo> vecRequestInfo,const std::vector<RewardInfo>& rewardList)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionGiveRewardOK(vecRequestInfo,rewardList);

#ifdef _EVENTPICKBOARD_
	bool bRefresh;
	for (size_t i = 0; i < vecRequestInfo.size(); ++i)
	{
		EVENT_PICKBOARD::CTREventPickBoardManager* pEventPickBoardMng = CNetClientManager::getInstance().getEventPickBoardManager();
		if (pEventPickBoardMng->checkUseMission(vecRequestInfo.at(i).m_iMissionNum))
		{
			if (EVENT_PICKBOARD::CTREventPickBoardUI::getInstance().isVisible())
			{
				bRefresh = true;
			}
			else
			{
				pEventPickBoardMng->setRecvCoinReward(true);
				pEventPickBoardMng->checkRecvCoinReward();
			}
		}
	}

	EVENT_PICKBOARD::CTREventPickBoardUI::getInstance().refreshCoinInfo();
#endif
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvMissionGiveRewardOK(vecRequestInfo.at(0), rewardList);
#endif
}

/// 유저가 완료한 미션의 보상 받기를 실패했다.
void CTRNetEventHandler::onRecvMissionGiveRewardFailed(const MissionRequestInfo& requestInfo, const eMissionFailedReason& faliedReason)
{
	CMissionMsgDispatcher::getInstance().onRecvMissionGiveRewardFailed(requestInfo,faliedReason);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! 길드 미션
/// 유저가 가입되어있는 길드의 길드 미션 리스트를 얻어왔다.
void CTRNetEventHandler::onRecvUserGuildMissionListOK(const std::vector<GuildMissionInfoForClient>& guildMisionInfo, std::vector<int>& nextMasterMissionNum)
{
	CTRGameGuildMissionManager::getInstance().onRecvUserGuildMissionListOK(guildMisionInfo,nextMasterMissionNum);
}

/// 유저가 가입되어있는 길드의 길드 미션 리스트 받아오기를 실패했다.
void CTRNetEventHandler::onRecvUserGuildMissionListFailed(const eGuildMissionFailedReason& failedReason)
{
	CTRGameGuildMissionManager::getInstance().onRecvUserGuildMissionListFailed(failedReason);
}

/// 길드 마스터 미션 설정 성공
void CTRNetEventHandler::onRecvGuildMissionSetMasterMissionOK(std::vector<int>& nextMasterMissionList)
{
	CTRGameGuildMissionManager::getInstance().onRecvGuildMissionSetMasterMissionOK(nextMasterMissionList);
}

/// 길드 마스터 미션 설정 실패
void CTRNetEventHandler::onRecvGuildMissionSetMasterMissionFailed(const eGuildMissionFailedReason& failedReason)
{
	CTRGameGuildMissionManager::getInstance().onRecvGuildMissionSetMasterMissionFailed(failedReason);
}

/// 특정 시간에 유저의 길드 미션 도전 리스트 제거 통지
void CTRNetEventHandler::onRecvGuildMissionUserMissionDeleteNotify(const int notifyType)
{
	CTRGameGuildMissionManager::getInstance().onRecvGuildMissionUserMissionDeleteNotify(notifyType);
}

//////////////////////////////////////////////////////////////////////////
// 일일 미션

/// 유저 일일 미션 리스트를 얻어왔다.
void CTRNetEventHandler::onRecvUserOneDayMissionListOK(const std::map<eMissionKind, std::vector<OneDayMissionInfoForClient> >& oneDayMisionInfo, const std::map<eMissionKind, bool>& oneDayMissionBuff)
{
	CTROneDayMissionManager::getInstance().onRecvUserOneDayMissionListOK(oneDayMisionInfo, oneDayMissionBuff);

	if(CTRUserBookDlg::getInstance().isVisible() && CTRUserBookDlg::getInstance().getCurTab() == CTRBookPageMoveInterface::eBOOK_TAB_ONEDAYMISSION)
	{
		CTRUserBookDlg::getInstance().closeUI();
	}
}

/// 유저 일일 미션 리스트 받아오기를 실패했다.
void CTRNetEventHandler::onRecvUserOneDayMissionListFailed(const eOneDayMissionFailedReason& failedReason)
{
	CTROneDayMissionManager::getInstance().onRecvUserOneDayMissionListFailed(failedReason);
}

/// 유저 일일 미션 완료 횟수를 얻어왔다.
void CTRNetEventHandler::onRecvUserOneDayMissionFinishCountOK(const std::map<eMissionKind, int>& oneDayMissionFinishCount)
{
	CTROneDayMissionManager::getInstance().onRecvUserOneDayMissionFinishCountOK(oneDayMissionFinishCount);
}

/// 유저 일일 미션 완료 횟수 받아오기를 실패했다.
void CTRNetEventHandler::onRecvUserOneDayMissionFinishCountFailed(const eOneDayMissionFailedReason& failedReason)
{
	CTROneDayMissionManager::getInstance().onRecvUserOneDayMissionFinishCountFailed(failedReason);
}

/// 이벤트 미션 여부.	
void CTRNetEventHandler::onRecvOneDayMissionGetEventMissionStatusOK(CMissionEventInfo& missionEventInfo)
{
	CTROneDayMissionManager::getInstance().onRecvOneDayMissionGetEventMissionStatusOK(missionEventInfo);
}

/// 이벤트 미션 기간이 아니다
void CTRNetEventHandler::onRecvOneDayMissionGetEventMissionStatusFailed(const eMissionFailedReason& failedReason)
{
	CTROneDayMissionManager::getInstance().onRecvOneDayMissionGetEventMissionStatusFailed(failedReason);
}

/// 특정 시간에 유저의 일일 미션 도전 리스트 제거 통지
void CTRNetEventHandler::onRecvOneDayMissionUserMissionDeleteNotify(std::vector<eMissionKind>& missionKindList, const int notifyType)
{
	DBG_OUTPUT(DBG_TYPE_MISSION, "%s - kind list size : %d, notify type : %d", __FUNCTION__, missionKindList.size(), notifyType);

	CTROneDayMissionManager::getInstance().onRecvOneDayMissionUserMissionDeleteNotify(missionKindList, notifyType);
	
#ifdef CONTENTS_HUG
	CTRHugSystemManager::getInstance().onRecvHugMissionUserMissionDeleteNotify();		// 허그 미션 초기화 통지	
#endif
}

#ifdef CONTENTS_OPTIONAL_MISSSION
/// 유저의 기능성 미션에 대한 정보를 받음 
void CTRNetEventHandler::onRecvOptionalMissionUserInfoOK(std::map<int, OptionalMissionInfoForClient>& userOptionalMissionInfo)
{
	CTROptionalMissionManager::getInstance().onRecvOptionalMissionUserInfo(userOptionalMissionInfo);
}

/// 유저의 기능성 미션에 대한 정보 받기를 실패
void CTRNetEventHandler::onRecvOptionalMissionUserInfoFailed(eOptionalMissionResult result)
{	
	TRDBG_OUTPUT_ERROR("CTRNetEventHandler::onRecvOptionalMissionUserInfoFailed : %d", (int)result);

	CTROptionalMissionManager::getInstance().onRecvOptionalMissionUserInfoFailed(result);
}

/// 기능성 미션이 초기화되었다
#ifdef _EVENTPICKBOARD_
void CTRNetEventHandler::onRecvOptionalMissionInit(std::vector<int> initMissionList)
{
	DBG_OUTPUT(DBG_TYPE_MISSION, "!!!! %s - size(%d)", __FUNCTION__, initMissionList.size());
	CTROptionalMissionManager::getInstance().onRecvOptionalMissionInit(initMissionList);

#ifdef _FISHING_
	CTRFishingSystemManager::getInstance().SetMissionInit(true);
	CTRUserBookDlg::getInstance().fishingMissionListUpdate();
#endif
}
#else
void CTRNetEventHandler::onRecvOptionalMissionInit()
{
	CTROptionalMissionManager::getInstance().onRecvOptionalMissionInit();
}
#endif

/// 웹에서 뽑은 아이템 내역 요청에 대한 결과를 받음
void CTRNetEventHandler::onRecvLotteryCouponChangeOK(std::vector<RewardInfo>& rewardList, const bool bExchangeMode)
{
    if(!rewardList.empty())
	{
		CTRRewardManager::getInstance().getReward(rewardList,true);
	}

	COkDialogEx::getInstance().showDialog(_STR(MSG_BUY_ITME_FARM_POINT));

	//!< 뽑기 조각 갱신
	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(0, eFuncItemPosition_WEB_LOTTERY_COUPON_PIECE);
}

/// 웹에서 뽑은 아이템 내역 요청에 대한 결과를 받지 못함
void CTRNetEventHandler::onRecvLotteryCouponChangeFailed()
{
	TRDBG_OUTPUT_ERROR("CTRNetEventHandler::onRecvWebLotteryRewardListFailed");
}
#endif

#ifdef COLLECTION_SYSTEM
/// 나의 콜렉션 미션 정보 리스트를 받았다.
void CTRNetEventHandler::onRecvUserCollectionMissionListOK(const eCollectionType collectionType, std::vector<CollectionMissionInfoForClient>& collectionUserInfoList)
{
    CTRCollectionMissionManager::getInstance().onRecvUserCollectionMissionListOK(collectionType, collectionUserInfoList);
}

/// 나의 콜렉션 미션 정보 리스트 받기를 실패
void CTRNetEventHandler::onRecvUserCollectionMissionListFailed(const eMissionFailedReason failedReason)
{
    DBG_OUTPUT("CTRNetEventHandler::onRecvUserCollectionMissionListFailed  %d", failedReason);
    CMissionMsgDispatcher::getInstance().onRecvMissionUserListFailed(failedReason);
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 엠블럼

/// 엠블럼 이벤트 정보 리스트를 받았다.
void CTRNetEventHandler::onRecvEmblemEventInfo(std::vector<EmblemEventInfo>& emblemEventInfoList)
{
	//! 히든엠블럼에 대한 날짜 정보 & 개수
	CTREmblemManager::getInstance().onRecvEmblemEventInfo(emblemEventInfoList);
}

/// 나의 엠블럼 정보 리스트를 받았다.
void CTRNetEventHandler::onRecvEmblemUserInfoResultOK(std::vector<EmblemUserInfo>& emblemUserInfoList)
{
	//! 미션이 한개라도 완료 했다면 그에 대한 유저에 대한 엠블럼 정보를 넘겨 준다.
	//CTREmblemUI::getInstance().refreshEmblemMissionDlg();
}

/// 나의 엠블럼 정보 리스트를 받아오기를 실패했다.
void CTRNetEventHandler::onRecvEmblemUserInfoResultFailed(eEmblemFailedReason eReason)
{
	string msg  = CTREmblemManager::getInstance().getEmblemFailedMessage(eReason);
	COkDialogEx::getInstance().showDialog(msg);
	DBG_OUTPUT("onRecvEmblemUserInfoResultFailed [%s]", msg.c_str());
}

/// 엠블럼 획득 요청에 대한 결과를 받았다.
void CTRNetEventHandler::onRecvEmblemAquireResultOK(int iEmblemNum)
{
	//! 엠블럼도 아이템이기 때문에 아이템 업데이트를 한다.
	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_EMBLEM_ITEM);

	CTRUserBookDlg::getInstance().onRecvEmblemAquireResultOK(iEmblemNum);
	//CTREmblemUI::getInstance().onRecvEmblemAquireResultOK(iEmblemNum);
}

/// 엠블럼 획득 요청을 실패했다.
void CTRNetEventHandler::onRecvEmblemAquireResultFailed(int iEmblemNum, eEmblemFailedReason eReason)
{
	string msg = CTREmblemManager::getInstance().getEmblemFailedMessage(eReason);

	COkDialogEx::getInstance().showDialog(msg);
	CTRUserBookDlg::getInstance().onRecvEmblemAquireResultFailed(iEmblemNum);
	//CTREmblemUI::getInstance().onRecvEmblemAquireResultFailed(iEmblemNum);
	DBG_OUTPUT("onRecvEmblemAquireResultFailed=[%s] EmblemNum=[%d]", msg.c_str(), iEmblemNum);
}

/// 엠블럼 선착순 획득 이벤트 시작/종료를 알린다.
void CTRNetEventHandler::onRecvEmblemFirstComeFirstServerdEventEndNotify(int iEmblemNum, bool bEventStart)
{
	CTRUserBookDlg::getInstance().onRecvEmblemFirstComeFirstServerdEventEndNotify(iEmblemNum, bEventStart);
	//CTREmblemUI::getInstance().onRecvEmblemFirstComeFirstServerdEventEndNotify(iEmblemNum, bEventStart);
}

/// 엠블럼 획득을 공지한다.
void CTRNetEventHandler::onRecvEmblemAcquisitionNotify(int iEmblemNum, int iRank, const std::string& strNickName)
{
	CTRUserBookDlg::getInstance().onRecvEmblemAcquisitionNotify(iEmblemNum,iRank,strNickName);
	//CTREmblemUI::getInstance().knownToAllEmblemAcquired(iEmblemNum,iRank,strNickName);
}

/// 혼돈의 엠블럼 획득 유저의 닉네임과 순위를 요청에 대한 결과를 받았다.
void CTRNetEventHandler::onRecvChaosEmblemAcquisitionUserListOK(eEmblemType emblemType, std::vector<EmblemAcquisitonUserInfo>& emblemAcquisitionUserInfoList)
{
	DBG_OUTPUT(60, "onRecvChaosEmblemAcquisitionUserListOK");

	switch(emblemType)
	{
	case eEmblemType_CHAOS:
		CTRGameParkUI::getInstance().openChaosEmblemAcquisitionUserListDlg(emblemAcquisitionUserInfoList);
		break;
	}
}

/// 혼돈의 엠블럼 획득 유저의 닉네임과 순위를 요청에 실패했다.
void CTRNetEventHandler::onRecvChaosEmblemAcquisitionUserListFailed(eEmblemFailedReason eReason, eEmblemType emblemType)
{
	DBG_OUTPUT(60, "onRecvChaosEmblemAcquisitionUserListFailed");
}
void CTRNetEventHandler::onRecvRoomResultForMissionCheckNotify()
{
	DBG_OUTPUT("%s(line: %d)",__FUNCTION__,__LINE__);
	m_pNetPlay->onRecvRoomResultForMissionCheckNotify();
}
//////////////////////////////////////////////////////////////////////////

/// 허그유저정보를 얻어온다.
void CTRNetEventHandler::onRecvHugSystemGetUserInfoOK()
{
	CTRHugSystemManager::getInstance().onRecvHugSystemGetUserInfoOK();
}

/// 허그유저정보를 얻어오는데 실패했다.
void CTRNetEventHandler::onRecvHugSystemGetUserInfoFailed()
{
	CTRHugSystemManager::getInstance().onRecvHugSystemGetUserInfoFailed();
}

/// 허그유저가 추천하기를 성공했다.
void CTRNetEventHandler::onRecvHugSystemRecommendUserOK(const std::string & recommendNickName, int iRewardGroupID)
{
	CTRHugSystemManager::getInstance().onRecvHugSystemRecommendUserOK(recommendNickName, iRewardGroupID);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HAS_RECOMMENDED_HUG);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 허그유저가 추천하기를 실패했다.
void CTRNetEventHandler::onRecvHugSystemRecommendUserFailed(std::string& recommenderNickName, eHugSystemFailed recommendUserFailed)
{
	CTRHugSystemManager::getInstance().onRecvHugSystemRecommendUserFailed(recommenderNickName, recommendUserFailed);
}

/// 허그 유저가 레벨업에 성공했다.
void CTRNetEventHandler::onRecvHugSystemLevelUpOK(int iRewardGroupID, short iHugLevel, eHugUserType eUserType)
{
	CTRHugSystemManager::getInstance().onRecvHugSystemLevelUpOK(iRewardGroupID, iHugLevel, eUserType);
}

/// 허그 유저가 레벨업에 실패했다.
void CTRNetEventHandler::onRecvHugSystemLevelUpFailed( eHugSystemFailed eHugLevelFailed )
{
	CTRHugSystemManager::getInstance().onRecvHugSystemLevelUpFailed(eHugLevelFailed);
}

/// 추천인이 선물을 받았다.
void CTRNetEventHandler::onRecvHugSystemReceiveGiftOK(const std::string& strNickName, int iRewardGroupID)
{
	CTRHugSystemManager::getInstance().onRecvHugSystemReceiveGiftOK(strNickName, iRewardGroupID);
}

/// 추천인이 선물을 받기를 실패했다.
void CTRNetEventHandler::onRecvHugSystemReceiveGiftFailed( eHugSystemFailed failReason )
{
	CTRHugSystemManager::getInstance().onRecvHugSystemReceiveGiftFailed(failReason);
}

/// 피추천인 리스트를 받았다.
void CTRNetEventHandler::onRecvHugSystemGetRecommendUserListOK( const std::vector<RecommendedUserInfo>& recommendedUserInfoList )
{
	CTRHugSystemManager::getInstance().onRecvHugSystemGetRecommendUserListOK(recommendedUserInfoList);
}

/// 피추천인 리스트 받기를 실패했다.
void CTRNetEventHandler::onRecvHugSystemGetRecommendUserListFailed( eHugSystemFailed failReason )
{
	CTRHugSystemManager::getInstance().onRecvHugSystemGetRecommendUserListFailed(failReason);
}

/// 피추천인을 제거한다.
void CTRNetEventHandler::onRecvHugSystemRemoveRecommendedUserOK( const std::string& strNickName )
{
	CTRHugSystemManager::getInstance().onRecvHugSystemRemoveRecommendedUserOK(strNickName);
}

/// 피추천인을 제거에 실패했다.
void CTRNetEventHandler::onRecvHugSystemRemoveRecommendedUserFailed( eHugSystemFailed failReason )
{
	CTRHugSystemManager::getInstance().onRecvHugSystemRemoveRecommendedUserFailed(failReason);
}

/// 특정 유저의 신규, 허그 추천정보가 갱신되었다.
void CTRNetEventHandler::onRecvHugSystemUpdateRecommend( unsigned int numPlayerIndex, bool bIsNotRecommendUser )
{
	m_pNetPlay->onRecvHugSystemUpdateRecommend(numPlayerIndex, bIsNotRecommendUser);
}

//////////////////////////////////////////////////////////////////////////

/// 카오스 엔젤/데빌 연금 가능함 알린다.
void CTRNetEventHandler::onRecvChaosAngelDevilAlchemistOpenNotify()
{
	CTRGameParkUI::getInstance().onRecvChaosAngelDevilAlchemistOpenNotify(true);
}

//////////////////////////////////////////////////////////////////////////
/// 개인 정보 게임 상세 정보를 알려준다.
void CTRNetEventHandler::onRecvIndividualGameNodify(const stIndividualRecordGame& stRecordGame)
{
	CTRGameIndividualRecordManager::getInstance().onRecvIndividualGameNodify(stRecordGame);
}

/// 개인 정보 기타 정보를 알려준다.
void CTRNetEventHandler::onRecvIndividualMiscellaneousNodify(const stIndividualRecordMiscellaneous& recordMiscellaneous)
{
	CTRGameIndividualRecordManager::getInstance().onRecvIndividualMiscellaneousNodify(recordMiscellaneous);
}

//////////////////////////////////////////////////////////////////////////
/// 캡슐 뽑기기계 정보 요청에 대한 결과를 받았다.
void CTRNetEventHandler::onRecvCapsuleMachineGetMachineInfo( CapsuleItemListMap mapMachineInfo, int iMachineNum, eCapsuleMachineKind iMachineKind, int iMachineGroupNum, int iMyPoint, int iUsePoint, int usedCountMax, int usedCount, int luckyCount, bool bIsWinnerParty, bool bIsTodayMachine, bool bIsOlympicGameTime )
{
	CTRGameParkUI::getInstance().onRecvCapsuleMachineGetMachineInfo(mapMachineInfo, (int)iMachineNum, iMachineKind, iMachineGroupNum, iMyPoint, iUsePoint, usedCountMax, usedCount, luckyCount, bIsWinnerParty, bIsTodayMachine, bIsOlympicGameTime);
	CTRGuildFarmUI::getInstance().onRecvCapsuleMachineGetMachineInfo(mapMachineInfo, (int)iMachineNum, iMachineKind, iMachineGroupNum, iMyPoint, iUsePoint, usedCountMax, usedCount, luckyCount, bIsWinnerParty, bIsTodayMachine, bIsOlympicGameTime);
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvCapsuleMachineGetMachineInfo(mapMachineInfo, iMachineNum, iMachineKind, iMachineGroupNum, iMyPoint, iUsePoint, usedCountMax, usedCount, luckyCount, bIsWinnerParty, bIsTodayMachine, bIsOlympicGameTime);
	DBG_OUTPUT("%s - bMachineNum[%d] MachineKind[%d] myPoint[%d] usingPoing[%d] count[%d/%d] isWinner[%d] isTodayMachineUse[%d] isOlympicGameTime[%d] luckyCount[%d]", __FUNCTION__, iMachineNum, iMachineKind, iMyPoint, iUsePoint, usedCount, usedCountMax, bIsWinnerParty, bIsTodayMachine, bIsOlympicGameTime, luckyCount);
}

#ifdef _VALENTINE
void CTRNetEventHandler::onRecvCapsuleMachineGetMachineInfo(CapsuleItemListMap mapMachineInfo, int iMachineNum, eCapsuleMachineKind iMachineKind, int iMachineGroupNum, int iMyPoint, int iUsingPoint, int usedCountMax, int usedCount, int luckyCount, const SENDER_NICK& sender_nick)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvCapsuleMachineGetMachineInfo(mapMachineInfo, (int)iMachineNum, iMachineKind, iMachineGroupNum, iMyPoint, iUsingPoint, usedCountMax, usedCount, luckyCount, false, false, false);
		CTRGameParkUI::getInstance().setGiftSendUser(sender_nick);
	}

	if(CTRGuildFarmUI::getInstance().isActive())
	{
		CTRGuildFarmUI::getInstance().onRecvCapsuleMachineGetMachineInfo(mapMachineInfo, (int)iMachineNum, iMachineKind, iMachineGroupNum, iMyPoint, iUsingPoint, usedCountMax, usedCount, luckyCount, false, false, false);
		CTRGuildFarmUI::getInstance().setGiftSendUser(sender_nick);
	}
		
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if(pDlg && pDlg->isVisible())
	{
		pDlg->getEventHandler().onRecvCapsuleMachineGetMachineInfo(mapMachineInfo, iMachineNum, iMachineKind, iMachineGroupNum, iMyPoint, iUsingPoint, usedCountMax, usedCount, luckyCount, false, false, false);
		pDlg->getEventHandler().setGiftSendUser(sender_nick);
	}

	DBG_OUTPUT("%s - bMachineNum[%d] MachineKind[%d] myPoint[%d] usingPoing[%d] count[%d/%d] luckyCount[%d] giftUserSize[%d]", __FUNCTION__, iMachineNum, iMachineKind, iMyPoint, iUsingPoint, usedCount, usedCountMax, luckyCount, sender_nick.size());
}
#endif

/// 캡슐 뽑기기계 정보 요청에 대한 비정상 결과를 받았다.
void CTRNetEventHandler::onRecvCapsuleMachineGetMachineInfoFailed(int bMachineNum, int iMachineGroupNum, byte bFailReason)
{
	CTRGameParkUI::getInstance().onRecvCapsuleMachineGetMachineInfoFailed(bMachineNum, iMachineGroupNum, bFailReason);
	CTRGuildFarmUI::getInstance().onRecvCapsuleMachineGetMachineInfoFailed(bMachineNum, iMachineGroupNum, bFailReason);
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvCapsuleMachineGetMachineInfoFailed(bMachineNum, iMachineGroupNum, bFailReason);
	DBG_OUTPUT("%s - bMachineNum: %d, iMachineGroupNum: %d, bFailReason: %d", __FUNCTION__, bMachineNum, iMachineGroupNum, (int)bFailReason);
}

/// 캡슐 뽑은 결과를 받았다.
void CTRNetEventHandler::onRecvCapsuleMachineSelect(int bMachineNum, int itemNum)
{
	CTRGameParkUI::getInstance().onRecvCapsuleMachineSelect(bMachineNum, itemNum);
	CTRGuildFarmUI::getInstance().onRecvCapsuleMachineSelect(bMachineNum, itemNum);
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvCapsuleMachineSelect(bMachineNum, itemNum);
	DBG_OUTPUT("%s - bMachineNum: %d, itemNum: %d",__FUNCTION__, bMachineNum, itemNum );
}

/// 캡슐 뽑은 결과가 비정상이다.
void CTRNetEventHandler::onRecvCapsuleMachineSelectFailed(int bMachineNum,byte bFailedReason)
{
	CTRGameParkUI::getInstance().onRecvCapsuleMachineSelectFailed(bMachineNum, bFailedReason);
	CTRGuildFarmUI::getInstance().onRecvCapsuleMachineSelectFailed(bMachineNum, bFailedReason);
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvCapsuleMachineSelectFailed(bMachineNum, bFailedReason);
	DBG_OUTPUT("%s - bMachineNum: %d, reason: %d", __FUNCTION__, bMachineNum, (int)bFailedReason);
}

/// 신규 행운캡슐 뽑은 결과를 받았다.
void CTRNetEventHandler::onRecvCapsuleMachineSelectEx(int bMachineNum, int itemNum)
{
	CTRGameParkUI::getInstance().onRecvCapsuleMachineSelectEx(bMachineNum, itemNum);

	DBG_OUTPUT("%s - bMachineNum: %d, item: %d", __FUNCTION__, bMachineNum, itemNum);
}

/// 신규 행운캡슐 뽑은 결과가 비정상이다.
void CTRNetEventHandler::onRecvCapsuleMachineSelectExFailed(int bMachineNum, eCapsuleMachine_FAILED_REASON eFail)
{
	CTRGameParkUI::getInstance().onRecvCapsuleMachineSelectExFailed(eFail);

	DBG_OUTPUT("%s - bMachineNum: %d, eFail: %d", __FUNCTION__, bMachineNum, (int)eFail);
}

/// 캡슐 뽑은 아이템을 지급요청에 대한 응답을 받았다.
void CTRNetEventHandler::onRecvCapsuleMachineGive(int itemNum)
{
	CTRGameParkUI::getInstance().onRecvCapsuleMachineGive(itemNum);
	CTRGuildFarmUI::getInstance().onRecvCapsuleMachineGive(itemNum);
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvCapsuleMachineGive(itemNum);
	DBG_OUTPUT("%s - itemNum: %d", __FUNCTION__, itemNum);
}

/// 캡슐 뽑은 아이템 지급 실패하였다.
void CTRNetEventHandler::onRecvCapsuleMachineGiveFailed(byte failedReason)
{
	CTRGameParkUI::getInstance().onRecvCapsuleMachineGiveFailed(failedReason);
	CTRGuildFarmUI::getInstance().onRecvCapsuleMachineGiveFailed(failedReason);
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvCapsuleMachineGiveFailed(failedReason);
	DBG_OUTPUT("%s - reason: %d", __FUNCTION__, (int)failedReason);
}

/// 캡슐 뽑은 결과를 공지한다.
void CTRNetEventHandler::onRecvCapsuleMachineNotify(byte type, int bMachineNum, int itemNum, std::string nickname, ePieroOlympicPartyType ePartyType)
{
	//if(CTRUserInterface::getInstance().isShowNotice())
	//{
	//	CTRUserInterface::getInstance().onRecvNoticeMsg(strMsg);
	//}
	//else
	//{
	//	CTRSystemNotice::getInstance().showMessage(strMsg);
	//}

	CTRGameParkUI::getInstance().onRecvCapsuleMachineNotify(type,bMachineNum,itemNum,nickname,ePartyType);
	CTRGuildFarmUI::getInstance().onRecvCapsuleMachineNotify(type,bMachineNum,itemNum,nickname,ePartyType);
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvCapsuleMachineNotify(type,bMachineNum,itemNum,nickname,ePartyType);
	DBG_OUTPUT("%s - type: %d, bMachineNum: %d, itemNum: %d, nickname: %s", __FUNCTION__, (int)type, bMachineNum, itemNum, nickname.data());
}

#ifdef _AUCTION_SYSTEM_
/// 경매 시스템 스케쥴 받았다
void CTRNetEventHandler::onRecvAuctionSchedule(int iAuctionNum, time_type tSDate, time_type tEDate, eAuctionState	auctionState)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionSchedule(iAuctionNum, tSDate, tEDate, auctionState);
}

/// 경매 시스템 세레머니 받았다
void CTRNetEventHandler::onRecvAuctionCermony(int iItemNum, std::string & sBeforeNickName, std::string & sNextNickName, int iBeforeTR, int iNextTR)
{
	std::string itemName;
	const CItemInfoNode* pItemInfo = CClientItemList::getInstance().getRealItemInfo(iItemNum);
	if (pItemInfo)
		itemName = pItemInfo->m_name; 

	if (sBeforeNickName.empty())
		sBeforeNickName = _STR(AUCTION_SYSTEM_ANONYMITY);
	if (sNextNickName.empty())
		sNextNickName = _STR(AUCTION_SYSTEM_ANONYMITY);

	std::string notice = format(_STR(AUCTION_SYSTEM_CERMONY), sNextNickName.c_str(), itemName.c_str(), sBeforeNickName.c_str(), iNextTR, iBeforeTR);

	if(CTRUserInterface::getInstance().isShowNotice())
	{
		CTRUserInterface::getInstance().onRecvNoticeMsg(eNoticeType_NORMAL, notice);
	}
	else
	{
		CTRSystemNotice::getInstance().showMessage(notice);
	}
}

/// 경매 시스템 리스트 받았다.
void CTRNetEventHandler::onRecvAuctionListOK(eAuctionKind auctionKind, int iAuctionNum, time_type tSDate, time_type tEDate, std::map<int, AuctionLIst> & mapAuctionList, int iTotalCount)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionListOK(auctionKind, iAuctionNum, tSDate, tEDate, mapAuctionList, iTotalCount);
}

void CTRNetEventHandler::onRecvAuctionListFailed(const DWORD & dwResult)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionListFailed(dwResult);
}

/// 경매 시스템 물품등록 결과를 받았다.
void CTRNetEventHandler::onRecvAuctionRegisterOK(const DWORD & dwResult, INT64 iStorageNum)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionRegisterOK(dwResult, iStorageNum);
}

void CTRNetEventHandler::onRecvAuctionRegisterFailed(const DWORD & dwResult)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionRegisterFailed(dwResult);
}

/// 경매 시스템 물품 채크 결과를 받았다.
void CTRNetEventHandler::onRecvAuctionRegisterItemCheckOK(int iPrice)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionRegisterItemCheckOK(iPrice);
}

void CTRNetEventHandler::onRecvAuctionRegisterItemCheckFailed(const DWORD & dwResult)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionRegisterItemCheckFailed(dwResult);
}

/// 경매 시스템 나의 물품등록 정보 받았다.
void CTRNetEventHandler::onRecvAuctionRegisterListOK(std::vector<std::pair<int,int> > & vecList)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionRegisterListOK(vecList);
}

void CTRNetEventHandler::onRecvAuctionRegisterListFailed(const DWORD & dwResult)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionRegisterListFailed(dwResult);
}

/// 경매 시스템 입찰 결과를 받았다..
void CTRNetEventHandler::onRecvAuctionTenderOK(const DWORD & dwResult)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionTenderOK(dwResult);
}
void CTRNetEventHandler::onRecvAuctionTenderChangePrice(const DWORD & dwResult, int iPrice)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionTenderChangePrice(dwResult, iPrice);
}
void CTRNetEventHandler::onRecvAuctionTenderFailed(const DWORD & dwResult)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionTenderFailed(dwResult);
}

/// 경매 시스템 나의 입찰 정보 받았다.
void CTRNetEventHandler::onRecvAuctionMyTenderListOK(std::vector<std::pair<int,int> > & vecList)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionMyTenderListOK(vecList);
}

void CTRNetEventHandler::onRecvAuctionMyTenderListFailed(const DWORD & dwResult)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionMyTenderListFailed(dwResult);
}

/// 경매 시스템 지난 낙찰 내역 받았다.
void CTRNetEventHandler::onRecvAuctionHistoryInfoOK(std::vector<std::pair<int,std::string> > & vecList, std::string & sMaxTR_NickName, int iMaxTR, int iMaxCountTR, int iMaxCount)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionHistoryInfoOK(vecList, sMaxTR_NickName, iMaxTR, iMaxCountTR, iMaxCount);
}

void CTRNetEventHandler::onRecvAuctionHistoryInfoFailed(const DWORD & dwResult)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionHistoryInfoFailed(dwResult);
}

/// 경매 시스템 최고 입찰가를 받았다.
void CTRNetEventHandler::onRecvAuctionTenderPriceOK(eAuctionKind auctionKind, int iAuctionNum, int iMaxPrice)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionTenderPriceOK(auctionKind, iAuctionNum, iMaxPrice);
}

void CTRNetEventHandler::onRecvAuctionTenderPriceFailed(const DWORD & dwResult)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionTenderPriceFailed(dwResult);
}

/// 경매 시스템 최저 입찰횟수를 받았다.
void CTRNetEventHandler::onRecvAuctionTenderCountOK(int iAuctionNum, int iCount)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionTenderCountOk(iAuctionNum,iCount);
}

void CTRNetEventHandler::onRecvAuctionTenderCountFailed(const DWORD & dwResult)
{
	Auction_System::CTRAuctionSystemManager::getInstance().onRecvAuctionTenderCountFailed(dwResult);
}
#endif
//////////////////////////////////////////////////////////////////////////

#ifdef ENTRY_SYSTEM

/// 응모 시스템 응모기간 스케쥴 받았다.
void CTRNetEventHandler::onRecvEntrySystemPeriodSchedule(eEntrySystemShopType shopType, bool bOpen, time_type tOpenTime, time_type tCloseTime, int iScheduleNum)
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemPeriodSchedule(shopType, bOpen, tOpenTime, tCloseTime, iScheduleNum);
}

/// 응모 시스템 상점 스케쥴 받았다
void CTRNetEventHandler::onRecvEntrySystemShopSchedule(eEntrySystemShopType shopType, bool bReset, time_type tOpenTime)
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemShopSchedule(shopType, bReset, tOpenTime);
}

/// 응모 시스템 정보 받았다
void CTRNetEventHandler::onRecvEntrySystemGetMachineInfo(int iScheduleNum, eEntrySystemShopType shopType, int iCategoryNum, EntrySystemListMap& mapSystemList)
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemGetMachineInfo(iScheduleNum, shopType, iCategoryNum, mapSystemList);
}

/// 응모 시스템 정보한 비정상 결과를 받았다.
void CTRNetEventHandler::onRecvEntrySystemGetMachineInfoFailed(eEntrySystemShopType shopType, int iCategoryNum, byte bFailReason)
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemGetMachineInfoFailed(shopType, iCategoryNum, bFailReason);
}

/// 응모 시스템 뽑은 결과를 받았다.
void CTRNetEventHandler::onRecvEntrySystemSelect(int iUniqueNum, bool bSucess, int itemNum)
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemSelect(iUniqueNum, bSucess, itemNum);
}

/// 응모 시스템 뽑은 결과가 비정상이다.
void CTRNetEventHandler::onRecvEntrySystemSelectFailed(int iUniqueNum, byte bFailedReason)
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemSelectFailed(iUniqueNum, bFailedReason);
}

/// 응모 뽑은 아이템을 지급요청에 대한 응답을 받았다.
void CTRNetEventHandler::onRecvEntrySystemGive(int itemNum)
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemGive(itemNum);
}

/// 응모 뽑은 아이템 지급 실패하였다.
void CTRNetEventHandler::onRecvEntrySystemGiveFailed(byte failedReason)
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemGiveFailed(failedReason);
}

/// 응모 시스템 당첨 결과 리스트를 받았다.
void CTRNetEventHandler::onRecvEntrySystemResult(eEntrySystemShopType shopType, int iTotalCount, unsigned short numPage, std::vector<EntrySystemResultInfo>&	vEntrySystemResult)
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemResult(shopType, iTotalCount, numPage, vEntrySystemResult);
}

/// 응모 시스템 당첨 결과 리스트를 받기 실패했다.
void CTRNetEventHandler::onRecvEntrySystemResultDBFailed()
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemResultDBFailed();
}

/// 응모 시스템 당첨 결과를 받았다.
void CTRNetEventHandler::onRecvEntrySystemResultView(int iScheduleNum, int iSelectNum, int iUniqueNum, bool bSucess, bool bUse, int itemNum)
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemResultView(iScheduleNum, iSelectNum, iUniqueNum, bSucess, bUse, itemNum);
}

/// 응모 시스템 당첨 결과가 비정상이다.
void CTRNetEventHandler::onRecvEntrySystemResultViewFailed(byte bFailedReason)
{
	CTREntrySystemManager::getInstance().onRecvEntrySystemResultViewFailed(bFailedReason);
}
#endif

//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////
/// 나이키 카드 이벤트 응모에 대한 결과를 받았다.
void CTRNetEventHandler::onRecvApplyEventResult(const int iEventNum, const int iTotalCardAmount, const bool bSuccess)
{
	// TODO 부철 : 퀘스트 삭제하면서 주석 처리
	//CTRParkQuestManager::getInstance().onRecvEventJoinTRState(iEventNum, iTotalCardAmount, bSuccess);
}

/// 나이키 카드 이벤트 응모에 대한 결과를 받았다.(DB error)
void CTRNetEventHandler::onRecvApplyEventResultDBFailed()
{
	// TODO 부철 : 퀘스트 삭제하면서 주석 처리
	//CTRParkQuestManager::getInstance().onRecvApplyEventResultDBFailed();
}

/// 연금 응모권 이벤트 응모에 대한 결과를 받았다.(정상적 결과)
void CTRNetEventHandler::onRecvApplyEventTicketResult(const int iEventNum, std::map<int, int> & mApplyInfoList, const bool bSuccess)
{
	// TODO 부철 : 퀘스트 삭제하면서 주석 처리
	//CTRParkQuestManager::getInstance().onRecvEventJoinGradeState(iEventNum, mApplyInfoList, bSuccess);
}


/// 연금 응모권 이벤트 응모에 대한 결과를 받았다.(DB error)
void CTRNetEventHandler::onRecvApplyEventTicketResultDBFailed()
{
	// TODO 부철 : 퀘스트 삭제하면서 주석 처리
	//CTRParkQuestManager::getInstance().onRecvApplyEventResultDBFailed();
}

/// 아이템 - TR 교환 요청에 대한 결과를 받았다.
void CTRNetEventHandler::onRecvExchangeItemToTRResult(const int iItemNum, const int iRewardTR, const int iCount)
{	
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iItemNum);

	const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getItemInfo(iItemNum);

	if(pItemInfo == NULL) return;

	if(pItemInfo->m_position == eFuncItemPosition_CHAOS_CRYSTAL)	// 되판 아이템이 결정체 일 경우
	{
		CTRGameParkUI::getInstance().onRecvExchangeItemToTRResult(iItemNum, iRewardTR,iCount);
		return ; 
	}

	string msg1 = format("<normal><color=ffffff>%s<br>[%d%s]</color></normal>", pItemInfo->m_name.c_str(), iCount, _STR(ITEM_PIECE));

	string msg2 = format(_STR(MSG_GET_RESULT_ITEM_TOTAL), iRewardTR, _STR(MONEY_TR));

	CDetailMessageOKDialog::getInstance().showDialog(msg1, msg2, "gui\\park\\FarmChangeCompletePopup.gui");

	CNetClientManager::getInstance().requestCurrentTR();
}

/// 아이템 - TR 교환 요청에 대한 결과를 받았다.(DB Error)
void CTRNetEventHandler::onRecvExchangeItemToTRResultFailed()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvExchangeItemToTRResultFailed / Item Exchange Fail!!!!");
}

/// 농작물 수확 아이템의 보상요청에 대한 결과 받음
void CTRNetEventHandler::onRecvFarmHarvestItemExchangeReward( const int iItemNum, const int iCount, std::vector<RewardInfo>& rewardList )
{
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iItemNum);
	if (!rewardList.empty()) CTRRewardManager::getInstance().getReward(rewardList,true);

	if(CTRFarmUI::getInstance().isActive())
		CTRFarmUI::getInstance().onRecvFarmHarvestItemExchangeReward(iItemNum, iCount, rewardList);

#ifdef _FISHING_
	CTRFishingSystemManager::getInstance().onRecvFarmHarvestItemExchangeReward(iItemNum, iCount, rewardList);
#endif

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_GUI_EVENT, static_cast<int>(eMissionConditionGUIEventType_FARM_HARVEST_ITEM_EXCHANGE));
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 농작물 수확 아이템의 보상요청이 실패했다
void CTRNetEventHandler::onRecvFarmHarvestItemExchangeRewardFailed()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvFarmHarvestItemExchangeRewardFailed");
}

/// 새로운 팜 목록을 받았다. 
void CTRNetEventHandler::onRecvFarmList(eFarmListKind farmListKind, const std::vector < CFarmListData > & farmList, const std::vector < unsigned int > & notExistFarmRoomList, unsigned int thisPageIndex, unsigned int numFarmListPageCount )
{
	CTRFarmLobbyUIDlg::getInstance().onRecvRoomList(farmListKind, farmList, notExistFarmRoomList, thisPageIndex, numFarmListPageCount);
}

/// 새로운 방 목록을 받았다.
void CTRNetEventHandler::onRecvRoomList(eRoomKind roomKind, const std::vector < CRoomListData > & roomList, unsigned int numRoomListPage, unsigned int numRoomListPageCount)
{
	CTRUserInterface::getInstance().onRecvRoomList(roomKind, roomList, numRoomListPage, numRoomListPageCount);
}

/// 방 만들기가 실패했다.
void CTRNetEventHandler::onRecvMakeRoomFail(eMakeRoomFail makeRoomFail, unsigned int hRoom)
{
	string message;
	switch(makeRoomFail)
	{
	case eMakeRoomFail_PIERO_ONLY:
		message = _STR(FAILED_ONLY_MAKEROOM_PIERO);
		DBG_OUTPUT(60, "eMakeRoomFail_PIERO_ONLY");
		break;
	case eMakeRoomFail_OTHER:
		message = _STR(FAILED_RETRY_AFTER_MINUTE);
		DBG_OUTPUT(60, "eMakeRoomFail_OTHER");
		break;
	case eMakeRoomFail_EXIST_NUBER_ROOM :
		// 이미 존재하는 방이다.
		// hRoom으로 넘어온 방으로 join해야한다.(공원)
		break;

	case eMakeRoomFail_ALREADY_IN_ROOM:
		message = _STR(FAILED_RETRY_AFTER_MINUTE);
		DBG_OUTPUT(60, "eMakeRoomFail_ALREADY_IN_ROOM");
		break;

	case eMakeRoomFail_ROOM_TRANSACTION:
		message = _STR(FAILED_RETRY_AFTER_MINUTE);
		DBG_OUTPUT(60, "eMakeRoomFail_ROOM_TRANSACTION");
		break;

	case eMakeRoomFail_NO_TICKET:
		message = _STR(INFORMATION_TICKET_ZERO);
		DBG_OUTPUT(60, "eMakeRoomFail_NO_TICKET");
		break;

	case eMakeRoomFail_LIMITED_LEVEL:              // 자기의 레벨에 맞지 않은 채널에서 방을 만들었을 때
		message= _STR(FAILED_MAKE_ROOM_LIMITED_LEVEL);
		DBG_OUTPUT(60,"eMakeRoomFail_LIMITED_LEVEL");
		break;

	case eMakeRoomFail_LIMITED_MAP_RULE:
		DBG_OUTPUT(60,"eMakeRoomFail_LIMITED_MAP_RULE");
		break;
	case eMakeRoomFail_NOT_SPORTS_TIME:
		DBG_OUTPUT(60,"eMakeRoomFail_NOT_SPORTS_TIME");
		message= _STR(FAILED_ROOM_NOT_SPORTS_TIME);
		break;
	case eMakeRoomFail_LIMITED_ROOM_COUNT:
		DBG_OUTPUT(60,"eMakeRoomFail_LIMITED_ROOM_COUNT");
		message= _STR(FAILED_MAKE_ROOM_LIMITED_COUNT);
		break;
	case eMakeRoomFail_INVALID_MAP_NUM:
		DBG_OUTPUT(60,"eMakeRoomFail_INVALID_MAP_NUM");
		message= _STR(FAILED_MAKE_MAP_IN_UNITYMODE);
		break;
	default: 
		_ASSERTE(false);
		break;
	}
	CParkChangeManager::getInstance().clear();
	CTRFarmLobbyUIDlg::getInstance().onRecvMakeRoomFail(makeRoomFail);
	if(!message.empty()) CTRShortTimeMessage::showMessage(message,1.5f);
}

/// 팜의 기본 정보를 받았다. 
void CTRNetEventHandler::onRecvEnterFarmInfo(const FarmInfo& info, const FarmChattingInfo& farmChattingInfo)
{
	CTRGameRoomInfo & roominfo = m_pNetPlay->_getGameRoomInfo();
	roominfo.m_farmInfo = info;
	roominfo.m_farmChattingInfo = farmChattingInfo;	
}

void CTRNetEventHandler::onRecvEnterRoom( const EnterRoomInfo & info, 
										  const std::vector<RecvFarmMapObjectInfo>& farmMapObjectInfoList, 
										  const std::vector<RecvFarmMapVoxelsInfo>& vecVoxels)
{
	//[mirime 2018-10-29] 로딩전 현재 메모리
	MemoryLog ml("onRecvEnterRoom. MapNum=%d RoomKind=%d", info.m_numMap, info.m_roomKind);

	DBG_OUTPUT(60, "onRecvEnterRoom: roomKind=%d, iRoomID=%d, strRoomTitle=%s, numMap=%d", info.m_roomKind, info.m_hRoom, info.m_strRoomTitle.c_str(), info.m_numMap);

	CTRRelayGameExitDialog::getInstance().closeDialog();
	CTRRelayGameExitDialog::getInstance().m_bChecked = false;
	CTRRelayGameExitDialog::getInstance().m_bTeamDrop = false;

	CTRTeamplayGameExitDialog::getInstance().closeDialog();
	CTRTeamplayGameExitDialog::getInstance().m_bChecked = false;

	CTRGameRoomInfo & roominfo = m_pNetPlay->_getGameRoomInfo();

	roominfo.clear();
	roominfo.m_hRoom = info.m_hRoom;
	roominfo.setRoomKind(info.m_roomKind);
	roominfo.m_iRoomNumber = info.m_numRoomNo;
	roominfo.m_roomTitle = info.m_strRoomTitle;
	roominfo.setGameMap(info.m_numMap);
	roominfo.setGameMapChecker(info.m_numMap);
	if(!roominfo.isEnableMapNumber())
	{
		return;
	}
	roominfo.m_iNumUsers = 0;
	roominfo.m_sTeamPlayMode = info.m_sTeamPlayMode;
	roominfo.m_slotInfo = info.m_slotInfo;
	roominfo.setSteppingMode(info.m_bSteppingMode);
	roominfo.setItemMode(info.m_eItemMode);
	roominfo.setChannelInfo(info.m_iChannelInfo);
	roominfo.m_tRoomCreateTime = info.m_tRoomCreateTime;

	if(m_pNetPlay)
	{
		m_pNetPlay->openGameRoomUI();
		m_pNetPlay->setThisCanReadyState(true);
	}

	// 팜 모드 일때 
	if(isFarmMode(info.m_roomKind))
	{
		CTRFarmLobbyUIDlg::getInstance().setJoinRoom(false);

		//! 팜 모드일때 맵 로드를 한다.
		if(CTRFarmUI::getInstance().loadMap(roominfo.m_farmInfo))		
		{
			CTRFarmUI::getInstance().loadMap(farmMapObjectInfoList, vecVoxels);

			if (roominfo.m_farmInfo.m_iFarmUniqueNum == CNetClientManager::getInstance().getMyFarmUniuqeNum())
			{
				const int nInstallCount = CTRFarmItemObjectManager::getInstance().getValueByEmblemMissionCondition(eMissionConditionType_INSTALL_HARVESTABLE_FARM_ITEM);
				if(nInstallCount > 0)
				{	
					CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_INSTALL_HARVESTABLE_FARM_ITEM,nInstallCount);	
					CMissionMsgDispatcher::getInstance().checkCompleteCondition();
				}
			}
		}
		else
		{
			DBG_OUTPUT("onRecvEnterFarmInfo [Farm Map Load Failed]");
			_ASSERT(false);
		}
	}

	 //길드 팜 모드 일때 
	else if(isGuildFarmMode(info.m_roomKind))
	{		
		CTRFarmLobbyUIDlg::getInstance().setJoinRoom(false);		
		// 길드 팜 모드일때 맵 로드를 함		
		if(!CTRGuildFarmUI::getInstance().loadMap(roominfo.m_farmInfo))
		{
			DBG_OUTPUT("onRecvEnterGuildFarmInfo [GuildFarm Map Load Failed] num[%d]", roominfo.m_farmInfo.m_iFarmTypeNum);
			_ASSERT(false);
		}		
	}

	else if (isParkMode(info.m_roomKind))
	{
	}
	//옵저버 관련 예외처리... 지우면 정상동작합니다.
	else if(isPlaygroundMultiMiniGame(info.m_roomKind) && CNetClientManager::getInstance().isObserver())
	{
		COkDialogEx::getInstance().showDialog(_STR(OBSERVER_CANNOT_ENTER_THIS_CHANNEL));
		CNetClientManager::getInstance().requestLeaveRoom(false);
	}
	else
	{
		// 방만들기에 성공했다면 처리
		if (CNetClientManager::getInstance().getMyIndex() == 0)
		{
			CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_GUI_EVENT, static_cast<int>(eMissionConditionGUIEventType_MAKE_ROOM));
			CMissionMsgDispatcher::getInstance().checkCompleteCondition();
		}
	}
#ifdef _REGIST_REWARD_ITEM
	CNetClientManager::getInstance().getRegisterRewardItemMgr()->clear();
#endif
}

void CTRNetEventHandler::addNewClient(int iPlayerIndex,const bool bReady,const BYTE followIndex,const int iState,const bool bIsNewEnterUser,const CNetPlayer * netPlayer)
{
	if(CTRFarmUI::getInstance().isActive() && bIsNewEnterUser && CTRNetPlayManager::getInstance().isNetworkPlayHost()){
		//! 팜이고 새로운 유저가 들어왔으며 방장일때, 이동 오브젝트의 대한 정보를 보낸다.
		CTRFarmItemObjectManager::getInstance().sendFarmObjectMoveEvent(iPlayerIndex);
	}

	m_pNetPlay->addNewClient(iPlayerIndex,bReady,followIndex, iState,bIsNewEnterUser,netPlayer);
}

#ifdef _SHOP_RENEWAL_
//////////////////////////////////////////////////////////////////////////
// 상점 리뉴얼

/// 상점 카테고리를 받았다
void CTRNetEventHandler::onRecvShopCategoryACK(std::vector < ShopCategory > & vecCategory, std::multimap<int, ShopCategoryPurchasing > & mapShopCategoryPurchasing)
{
	CTRShopManager::getInstance().onRecvShopCategoryACK(vecCategory, mapShopCategoryPurchasing);
}

void CTRNetEventHandler::onRecvShopCategoryFailed(eServerResult dwResult)
{
	CTRShopManager::getInstance().onRecvShopCategoryFailed(dwResult);
}

/// 상점 전시 리스트를 받았다.
void CTRNetEventHandler::onRecvShopDisplayLIstACK(SHOP_DISPLAY_LIST & list)
{
	CTRShopManager::getInstance().onRecvShopDisplayLIstACK(list);
}

void CTRNetEventHandler::onRecvShopItemSellLIstACK(std::multimap<int, ShopItemSellList > & list)
{
	CTRShopManager::getInstance().onRecvShopItemSellLIstACK(list);
}

void CTRNetEventHandler::onRecvShopDisplayDateLIstACK(SHOP_DISPLAY_DATE_LIST & list)
{
	CTRShopManager::getInstance().onRecvShopDisplayDateLIstACK(list);
}

void CTRNetEventHandler::onRecvShopBuyLimitCountLIstACK(SHOP_BUY_LIMIT_COUNT_LIST & list)
{
	CTRShopManager::getInstance().onRecvShopBuyLimitCountLIstACK(list);
}

void CTRNetEventHandler::onRecvShopBuyAddBenefitLIstACK(SHOP_BUY_ADD_BENEFIT_LIST & list)
{
	CTRShopManager::getInstance().onRecvShopBuyAddBenefitLIstACK(list);
}

void CTRNetEventHandler::onRecvShopBuyAddSellPriceLIstACK(SHOP_BUY_ADD_SELL_PRICE_LIST & list)
{
	CTRShopManager::getInstance().onRecvShopBuyAddSellPriceLIstACK(list);
}

void CTRNetEventHandler::onRecvShopDisplayLIstFailed(eServerResult dwResult)
{
	CTRShopManager::getInstance().onRecvShopDisplayLIstFailed(dwResult);
}

/// 상점 전시 리스트 리로드 공지를 받았다.
void CTRNetEventHandler::onRecvShopDisplayReloadNotify()
{
	CTRShopManager::getInstance().onRecvShopDisplayReloadNotify();
}

/// 유저의 VIP 상점 레벨 공지를 받았다.
void CTRNetEventHandler::onRecvShopVipLevelNotify(const int iVipLevel)
{
	CTRShopManager::getInstance().onRecvShopVipLevelNotify(iVipLevel);
}

/// 유저의 VIP 상점 레벨 리셋 공지를 받았다.
void CTRNetEventHandler::onRecvShopVipLevelResetNotify()
{
	CTRShopManager::getInstance().onRecvShopVipLevelResetNotify();
}

/// 상점 랭크 초기화 공지를 받았다.
void CTRNetEventHandler::onRecvShopRanklResetNotify()
{
	CTRShopManager::getInstance().onRecvShopRanklResetNotify();
}

/// 상점 구매횟수 리셋 공지를 받았다.
void CTRNetEventHandler::onRecvShopBuyCountResetNotify()
{
	CTRShopManager::getInstance().onRecvShopBuyCountResetNotify();
}

/// 상점 구매횟수 리스트를 받았다.
void CTRNetEventHandler::onRecvShopUserBuyCountLIstACK(SHOP_BUY_LIMIT_COUNT_LIST & list, std::map<int/*SellItemNum*/, int/*ShopBuyAddSellPrice.m_iCount*/> & sellList)
{
	CTRShopManager::getInstance().onRecvShopUserBuyCountLIstACK(list, sellList);
}
void CTRNetEventHandler::onRecvShopUserBuyCountLIstFailed(eServerResult dwResult)
{
	CTRShopManager::getInstance().onRecvShopUserBuyCountLIstFailed(dwResult);
}

/// 상점 구매횟수 리스트를 받았다.
void CTRNetEventHandler::onRecvShopBuyCountLIstACK( std::map<int/*ShopDisplayNum*/, int/*ShopBuyLimitCount.m_iTotalPurchasingLimit*/> & sellList)
{
	CTRShopManager::getInstance().onRecvShopBuyCountLIstACK(sellList);
}
void CTRNetEventHandler::onRecvShopBuyCountLIstFailed(eServerResult dwResult)
{
	CTRShopManager::getInstance().onRecvShopBuyCountLIstFailed(dwResult);
}

// 상점 랭크 리스트를 받았다.
void CTRNetEventHandler::onRecvShopRankACK(int iCategory1, int iCategory2, int iCategory3, std::map<int, int> & list)
{
	CTRShopManager::getInstance().onRecvShopRankACK(iCategory1, iCategory2, iCategory3, list);
}
void CTRNetEventHandler::onRecvShopRankFailed(eServerResult dwResult)
{
	CTRShopManager::getInstance().onRecvShopRankFailed(dwResult);
}

// 상점 찜 리스트를 받았다.
void CTRNetEventHandler::onRecvShopUserWishLIstACK(std::map<int, time_type> & list)
{
	CTRShopManager::getInstance().onRecvShopUserWishLIstACK(list);
}
void CTRNetEventHandler::onRecvShopUserWishLIstFailed(eServerResult dwResult)
{
	CTRShopManager::getInstance().onRecvShopUserWishLIstFailed(dwResult);
}

// 상점 찜 리스트에 등록 결과를 받았다.
void CTRNetEventHandler::onRecvShopSetUserWishLIstACK(eShopWishListType wishType, int iDisplayNum)
{
	CTRShopManager::getInstance().onRecvShopSetUserWishLIstACK(wishType, iDisplayNum);
}
void CTRNetEventHandler::onRecvShopSetUserWishLIstFailed(eServerResult dwResult)
{
	CTRShopManager::getInstance().onRecvShopSetUserWishLIstFailed(dwResult);
}

#endif

/// 현재 TR 을 받았다.
void CTRNetEventHandler::onRecvCurrentGameMoney(const int iGameMoney)
{
	CTRLobbyUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRGameParkUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRFarmUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRFarmShopUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRFarmMyroomUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRMyRoomUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRMyroomDlg::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRAlchemistUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRShopDlg::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRShopUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRMawooShopDlg::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRMawooShopUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
	CTRUserBookDlg::getInstance().onRecvUpdateTR();
	CTRGuildFarmUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
#ifdef _SHOP_RENEWAL_
	CTRShopRenewalUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
#endif
#ifdef _SHU_SYSTEM_
	SHU_SYSTEM::CTRShuUI_Management::getInstance().onRecvCurrentGameMoney(iGameMoney);
#endif
#ifdef _RAINBOW_LEAGUE
	CTRLobbyUI::getInstance().onRecvCurrentGameMoney(iGameMoney);
#endif
}


//! 연금술사에서 아이템 분해를 한다.
void CTRNetEventHandler::onRecvAlchemistDisjoint(eServerResult eResult,const int iItemDescNum)
{
	CTRAlchemistUI::getInstance().onRecvAlchemistDisjoint(eResult, iItemDescNum);
	CTRGameParkUI::getInstance().onRecvAlchemistDisjoint(eResult, iItemDescNum);
}

//! 연금술사 조합을 시작하겠다.
void CTRNetEventHandler::onRecvAlchemistMixBegin(eServerResult eResult)
{
	//! 현재 사용하지 않는다..
}

/// 연금술사 조합이 성공했다.
void CTRNetEventHandler::onRecvAlchemistMixEndOK(const UserItemAttrInfo& itemInfo)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvAlchemistMixEndOK[%d]",itemInfo.m_iItemDescNum);

	CNetClientManager & rCNetClientManager = CNetClientManager::getInstance();
	//! 보유 카드 리스트 및 현재 TR 및 캐쉬 요청
	
	rCNetClientManager.requestCurrentTR();

#ifdef _BILLING_CHANNELING_PLAYNET
	rCNetClientManager.requestCashBalance(true);
#else
	rCNetClientManager.getInstance().requestCashBalance();
#endif

	//! 연금의 조합이 성공했으므로 관련 이벤트 실행...
	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvAlchemistMixEndOK();
	else CTRAlchemistUI::getInstance().onRecvAlchemistMixEndOK();

	const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getItemInfo(itemInfo.m_iItemDescNum);

	if(pItemInfo != NULL)
	{
		if(pItemInfo->m_position == eFuncItemPosition_FARM)
		{
			set<int> farmItemNumList;
			farmItemNumList.insert(pItemInfo->m_iUniqueNumber);
			rCNetClientManager.requestGetFarmItemListEx(farmItemNumList);

			//! 팜 관련 아이템 능력치 요청
			const int iMyFarmNum = rCNetClientManager.getMyFarmUniuqeNum();
			rCNetClientManager.requestGetFarmItemAttrList(iMyFarmNum, false);

			//! 게임정보 기록 중 팜관련 아이템카운트 증가
			CTRGameIndividualRecordManager::getInstance().onUpdateIndividualRecord(itemInfo.m_iItemDescNum,1);
		}
		else
		{
			CTRGameIndividualRecordManager::getInstance().onUpdateAlchemistIndividualRecord(pItemInfo);
		}
	}
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HAS_ITEM);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_NOT_EXIST_ITEM);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 연금술사 조합이 실패
void CTRNetEventHandler::onRecvAlchemistMixEndFailed(eAlchemistMixFailedReason reason)
{
	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvAlchemistMixRecipeFailed(reason);
	else CTRAlchemistUI::getInstance().onRecvAlchemistMixRecipeFailed(reason);
}

/// 연금 아이템의 등급 인첸트에 성공했다.
void CTRNetEventHandler::onRecvAlchemistEnchantGradeOK(const UserItemAttrInfo& itemInfo, bool bSuccess)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvAlchemistEnchantGradeOK[%d][%d]",itemInfo.m_iItemDescNum,bSuccess);

	CNetClientManager::getInstance().requestCurrentTR();
	
#ifdef _BILLING_CHANNELING_PLAYNET
	CNetClientManager::getInstance().requestCashBalance(true);
#else
	CNetClientManager::getInstance().requestCashBalance();
#endif

	//! 연금의 조합이 성공했으므로 관련 이벤트 실행...
	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvAlchemistEnchantGradeOK(itemInfo, bSuccess);
	else CTRAlchemistUI::getInstance().onRecvAlchemistEnchantGradeOK(itemInfo, bSuccess);

	const CItemInfoNode * pItemInfo = CClientItemList::getInstance().getItemInfo(itemInfo.m_iItemDescNum);	
	if(pItemInfo) CTRGameIndividualRecordManager::getInstance().onUpdateAlchemistIndividualRecord(pItemInfo);

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_GUI_EVENT, static_cast<int>(eMissionConditionGUIEventType_ALCHEMIST_ENCHANT_GRADE));
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 연금 아이템의 등급 인첸트에 실패했다.
void CTRNetEventHandler::onRecvAlchemistEnchantGradeFailed(eAlchemistEnchantGradeFailedReason reason)
{
	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvAlchemistEnchantGradeFailed(reason);
	else CTRAlchemistUI::getInstance().onRecvAlchemistEnchantGradeFailed(reason);
}

/// 아이템 제작 가능한 시간 요청에 성공했다.
void CTRNetEventHandler::onRecvItemManufactureCoolTimeOK(int iManufactureNum, time_type tAlchemistCoolTime)
{
	DBG_OUTPUT("%s(line: %d)",__FUNCTION__,__LINE__);
	//SYSTEMTIME systemTime;
	//CCurrentTime::fromTimeToSystemTime(tAlchemistCoolTime, systemTime);
	CTRManufactureManager::getInstance().onRecvManufactureItemCoolTimeOK(iManufactureNum,tAlchemistCoolTime);
}

/// 아이템 제작 가능한 시간 요청에 실패했다.
void CTRNetEventHandler::onRecvItemManufactureCoolTimeFailed(int iManufactureNum)
{
	DBG_OUTPUT("%s(line: %d)",__FUNCTION__,__LINE__);
}

/// 아이템 제작 요청에 성공했다.
void CTRNetEventHandler::onRecvItemManufactureMakeOK(int iManufactureNum)
{
	DBG_OUTPUT("%s(line: %d)",__FUNCTION__,__LINE__);
	CTRManufactureManager::getInstance().onRecvManufactureOK(iManufactureNum);
}

/// 아이템 제작 요청에 실패했다.
void CTRNetEventHandler::onRecvItemManufactureMakeFailed(int iManufactureNum, eItemManufactureFailedReason reason)
{
	DBG_OUTPUT("%s(line: %d) iManufactureNum: %d, reason: %d",__FUNCTION__,__LINE__,iManufactureNum,reason);
}

/// 혼돈의 완성체 보너스 정보를 받았다.
void CTRNetEventHandler::onRecvChaosCompletionUnitBonus(const BuffBonusInfo& bonusInfo)
{
	CTRUserInterface::getInstance().onRecvChaosCompletionUnitBonus(bonusInfo);
}

/// 삐에로 참여 보너스 정보를 받았다.
void CTRNetEventHandler::onRecvPieroJoinBuffBonus( const BuffBonusInfo& bonusInfo )
{
	CTRUserInterface::getInstance().onRecvPieroJoinBuffBonus(bonusInfo);
}

/// 이 방에 있는 영웅 등급 유저중 최고 경험치 유저의 상태 변경을 받았다.
void CTRNetEventHandler::onRecvSortedHeroClassGameIndices( const std::vector<BYTE>& heroClassGameIndices )
{
	if (m_pNetPlay != NULL)
	{
		m_pNetPlay->onRecvSortedHeroClassGameIndices(heroClassGameIndices);
	}

	if (m_pGameRoomUI != NULL)
	{
		m_pGameRoomUI->onRecvSortedHeroClassGameIndices(heroClassGameIndices);
	}
}

/// 영웅 등급 보너스 버프 정보를 받았다.
void CTRNetEventHandler::onRecvHeroClassBuffBonusNotify( const BuffBonusInfo& bonusInfo )
{
	CTRUserInterface::getInstance().onRecvHeroClassBuffBonus(bonusInfo);
}

/// 길드 보너스 정보를 받았다.
void CTRNetEventHandler::onRecvGuildUnitNotice(const BuffBonusInfo &bonusInfo)
{
	CTRUserInterface::getInstance().onRecvGuildUnitNotice(bonusInfo);
}
/// 드래곤 세트 보너스 정보를 받았다.
void CTRNetEventHandler::onRecvDragonAlchemistUnitBouns(const DragonAlchemistItemBonus& bonusInfo)
{
	CTRUserInterface::getInstance().onRecvDragonAlchemistUnitBouns(bonusInfo);
}

// 프리미엄 방장의 정보를 받았다
void CTRNetEventHandler::onRecvSuperRoomMasterInfo(const SuperRoomMasterInfo& bonusInfo)
{
	CTRUserInterface::getInstance().onRecvSuperRoomMasterBonus(bonusInfo);
}

/// 스페셜 게임 보상 통지를 받았다
void CTRNetEventHandler::onRecvSpecialGameRewardNotify(JackPotReward& rewardInfo)
{
	DBG_OUTPUT("onRecvSpecialGameRewardNotify (%d)", rewardInfo.m_rewardInfo.iRewardID);
	CTRUserInterface::getInstance().onRecvSpecialGameRewardNotify(rewardInfo);
}

void CTRNetEventHandler::onRecvSelectStartCharacter()
{
	CTRCharacterSelectUI::getInstance().onRecvSelectStartCharacter();
}

void CTRNetEventHandler::onRecvSelectStartChracterOK()
{
	CTRCharacterSelectUI::getInstance().onRecvSelectStartChracterOK();
}

/// 시작 아바타를 선택하는데 DB Error 로 인한 심각한 에러다.
void CTRNetEventHandler::onRecvSelectStartCharacterFail()
{
	CTRShortTimeMessage::showMessage(_STR(ERR_STARTCHARACTERSELECTION_FAILED));
}

void CTRNetEventHandler::onRecvAvatarInfo(const AdvancedAvatarInfo & advancedAvatarInfo)
{	
	DBG_OUTPUT("CTRNetEventHandler::onRecvAvatarInfo...");
	m_pNetPlay->setAdvancedAvatarInfo(advancedAvatarInfo);

	CTRCharacterSelectUI::getInstance().onRecvAvatarInfo(advancedAvatarInfo);
	CTRCoupleSystem::getInstacne().onRecvAvatarInfo(advancedAvatarInfo);

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_ACTIVE_ITEM);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 나의 동물레이싱 아바타 정보를 받았다.
void CTRNetEventHandler::onRecvAnimalRacingAvatarInfo(const AnimalRacingAnimalAvatar& animalRacingAvatarInfo)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvAnimalRacingAvatarInfo...%d", animalRacingAvatarInfo.m_animal);

	m_pNetPlay->setAnimalAvatarInfo(animalRacingAvatarInfo);
}

/// 동물레이싱 아바타를 받는데 실패했다.
void CTRNetEventHandler::onRecvAnimalRacingAvatarFail()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvAnimalRacingAvatarFail...");
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		COkDialogEx::getInstance().showDialog(_STR(FAILED_RECV_RACING_ANIMAL_AVATAR));
	}
}

/// 동물레이싱 아바타가 없다. 튜토리얼에 참여해야한다.
void CTRNetEventHandler::onRecvHaveNoAnimalRacingAvatar()
{

}

void CTRNetEventHandler::onRecvChangeAvatar(unsigned int numPlayerIndex, const AdvancedAvatarInfo & advancedAvatarInfo)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvChangeAvatar(%d)...", numPlayerIndex);

	m_pNetPlay->onRecvChangeAvatar(numPlayerIndex, advancedAvatarInfo);

	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		// 게임중엔 아바타가 변하지 않도록 한다.
		CTRUserInterface::getInstance().onPlayerAvatarChange(CGamePlayerID(numPlayerIndex), advancedAvatarInfo);
	}
}

void CTRNetEventHandler::onRecvUpdateAvatar(unsigned int numPlayerIndex, const AdvancedAvatarInfo & advancedAvatarInfo)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvUpdateAvatar(%d)...", numPlayerIndex);

	m_pNetPlay->onRecvUpdateAvatar(numPlayerIndex, advancedAvatarInfo);

	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		// 게임중엔 아바타가 변하지 않도록 한다.
		CTRUserInterface::getInstance().onPlayerAvatarChange(CGamePlayerID(numPlayerIndex), advancedAvatarInfo);
	}
}

void CTRNetEventHandler::onRecvUpdateOnOffItem(unsigned int numGameIndex,const int iItemDescNum,const bool bOnOff)
{
	m_pNetPlay->onRecvUpdateOnOffItem(numGameIndex, iItemDescNum, bOnOff);

	CTRUserInterface::getInstance().onRecvUpdateOnOffItem(numGameIndex, iItemDescNum, bOnOff);
	CTRUserInterface::getInstance().onUpdateRoomUsers();

	DBG_OUTPUT("CTRNetEventHandler::onRecvUpdateOnOffItem");
}

/// 특정 유저의 탑승 동물 정보가 바뀌었다.
void CTRNetEventHandler::onRecvChangeAnimalAvatar(unsigned int numPlayerIndex, const AnimalRacingAnimalAvatar & avatarInfo)
{
	DBG_DEMO_OUTPUT("CTRNetEventHandler::onRecvChangeAnimalAvatar_PlayerIndex=[%d]AnimalKind[%d]",numPlayerIndex,avatarInfo.m_animal);

	m_pNetPlay->onRecvChangeAnimalAvatar(numPlayerIndex, avatarInfo);

	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		// 게임중엔 아바타가 변하지 않도록 한다.
		CTRUserInterface::getInstance().onPlayerAnimalAvatarChange(CGamePlayerID(numPlayerIndex), avatarInfo);
	}
	else if(m_pNetPlay->getThisPlayerIndex() == numPlayerIndex)
	{
		//게임중에 바꼈다고 오면 기간만료
		UserAlarmInfo info;
		info.alarmMsg = eALARM_ANIMAL_AVATAR_EXPIRED_TIME;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(info, true);
	}
}

/// 특정 유저의 탑승 동물 정보가 바뀌었다.
void CTRNetEventHandler::onRecvUpdateAnimalAvatar(unsigned int numPlayerIndex, const AnimalRacingAnimalAvatar & avatarInfo)
{
	DBG_DEMO_OUTPUT("CTRNetEventHandler::onRecvUpdateAnimalAvatar_PlayerIndex=[%d]AnimalKind[%d]",numPlayerIndex,avatarInfo.m_animal);

	m_pNetPlay->onRecvChangeAnimalAvatar(numPlayerIndex, avatarInfo);

	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		// 게임중엔 아바타가 변하지 않도록 한다.
		CTRUserInterface::getInstance().onPlayerAnimalAvatarChange(CGamePlayerID(numPlayerIndex), avatarInfo);
	}
	else if(m_pNetPlay->getThisPlayerIndex() == numPlayerIndex)
	{
		//게임중에 바꼈다고 오면 기간만료
		UserAlarmInfo info;
		info.alarmMsg = eALARM_ANIMAL_AVATAR_EXPIRED_TIME;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(info, true);
	}
}

/// 방에서 특정 유저가 오브젝트에 어떠한 행위를 했다.
void CTRNetEventHandler::onRecvNotifyUserAction(BYTE byGameIndex, BYTE byAction, __int64 iOID)
{
	CTRActionObjectManager::getInstance().onRecvNotifyUserAction(byGameIndex, byAction, iOID);
}

/// 메시지 박스를 보여주라고 받았다.
void CTRNetEventHandler::onRecvShowMsg(const std::string & strMsg)
{
	CTRShortTimeMessage::showMessage(strMsg, 2.5f);
}

/// 이 유저의 피로도 시간은 받는다.
void CTRNetEventHandler::onRecvFatigue(const int iFatigueMinute)
{
#ifdef FATIGUESYSTEM
	CTRFatigueManager::getInstance().onBeginFatigueCheck(iFatigueMinute);
#endif
}

// 서버로 부터 유효한 길드 이름인지 체크 결과를 받았다. 
void CTRNetEventHandler::onRecvGuildCheckValidGuildNameResult(eGuildNameCheckResult byCheckResult)
{
	if(CTRNameChangeManager::getInstance().getCurrActiveType() == CTRNameChangeManager::ACTIVE_TYEP_CHANGE_GUILDNAME) // 길드명 변경 아이템 사용 했을 때
	{
		CTRNameChangeManager::getInstance().onRecvGuildCheckValidGuildNameResult(byCheckResult);
	}
	else 
	{
		CTRGameParkUI::getInstance().onRecvGuildCheckValidGuildNameResult(byCheckResult);	
	}
}

// 서버로 부터 길드를 만드는데 성공했다는 결과를 받았다.
void CTRNetEventHandler::onRecvGuildMakeGuildSuccess()
{
	CTRGameParkUI::getInstance().onRecvGuildMakeGuildSuccess();
}

// 서버로 부터 길드를 만드는데 실패했다는 결과를 받았다.
void CTRNetEventHandler::onRecvGuildMakeGuildFailed(eGuildMakeFailedReason byFailedReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildMakeGuildFailed eGuildMakeFailedReason:%d", byFailedReason);
	CTRGameParkUI::getInstance().onRecvGuildMakeGuildFailed(byFailedReason);
}

/// 길드 해체 요청을 처리했다.
void CTRNetEventHandler::onRecvGuildDeleteGuild()
{
	CTRGameParkUI::getInstance().onRecvGuildDeleteGuild();
}
void CTRNetEventHandler::onRecvGuildDeleteGuildFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildDeleteGuildFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

/// 길드 리스트를 받았다.
void CTRNetEventHandler::onRecvGuildGetGuildList(const std::vector<GuildInfo>& guildList, int totalGuildListCount, const GuildSearchArg& arg)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildGetGuildList");
	CTRGameParkUI::getInstance().onRecvGuildGetGuildList(guildList, totalGuildListCount, arg);
}
void CTRNetEventHandler::onRecvGuildGetGuildListFailed()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildGetGuildListFailed");
}

/// 길드 가입 대기자 리스트를 받았다.
void CTRNetEventHandler::onRecvGuildGetJoinWaitMemberList(const std::vector<GuildWaiterInfo>& guildWaiterList)
{
	CTRGuildDlg::getInstance().onRecvGuildGetJoinWaitMemberList(guildWaiterList);
}
void CTRNetEventHandler::onRecvGuildGetJoinWaitMemberListFailed()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildGetJoinWaitMemberListFailed");
}

/// 길드 가입 요청의 결과를 받았다.
void CTRNetEventHandler::onRecvGuildJoinRequest(eGuildJoinMethod eMethod, const std::string& strGuildName)
{
	CTRGuildJoinDlg::getInstance().onRecvGuildJoinRequest(eMethod, strGuildName);
	CTRGameParkUI::getInstance().onRecvGuildJoinRequest(eMethod, strGuildName);
}
void CTRNetEventHandler::onRecvGuildJoinRequestFailed(eGuildFailReason eReason, int iLimmitCount)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildJoinRequestFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

/// 길드 가입 신청 취소 결과를 받았다.
void CTRNetEventHandler::onRecvGuildCancelPropose(const std::string& strGuildName)
{
	CTRGameParkUI::getInstance().onRecvGuildCancelPropose(strGuildName);
}
void CTRNetEventHandler::onRecvGuildCancelProposeFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildCancelProposeFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}
/// 길드 길드 관련 알람 메시지를 받았다.
void CTRNetEventHandler::onRecvGuildNotify(const UserAlarmInfo& guildNotice)
{
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		string message;
		string guiFileName = "gui\\ok.gui";
		bool bChangeWidth = true;
		switch(guildNotice.alarmMsg)
		{
		case eALARM_MSG_GUILD_JOIN:
			message = format(_STR(INFORMATION_GUILD_JOIN_OK), guildNotice.strExt.c_str());
			CTRGameParkUI::getInstance().refreshtGuildSearchList();
			guiFileName = "gui\\Guild\\GuildLevelUpOK.gui";
			bChangeWidth = false;
			break;
		case eALARM_MSG_GUILD_REFUSE_PROPOSE:
			message = format(_STR(INFORMATION_GUILD_JOIN_DENIAL), guildNotice.strExt.c_str());
			CTRGameParkUI::getInstance().refreshtGuildSearchList();
			break;
		case eALARM_MSG_GUILD_LEAVE:
			{
				message = format(_STR(INFORMATION_GUILD_BANISHED), guildNotice.strExt.c_str());

				if(CTRGuildDlg::getInstance().isVisible()) CTRGuildDlg::getInstance().closeDialog();
				CTRGuildFarmUI::getInstance().onLeaveGuildFarm();

				if (m_pNetPlay != NULL && m_pNetPlay->inRoom() && m_pGameRoomUI != NULL && (m_pGameRoomUI->getUIType() == GUI_TYPE_GUILD_MATCH_PARTYROOM
					|| m_pGameRoomUI->getUIType()  == GUI_TYPE_GUILD_MATCH_GAMEROOM))
				{
					CNetClientManager::getInstance().requestLeaveRoom();
				}
			}
			break;
		case eALARM_MSG_GUILD_MODIFY_MEMBER_GRADE:
			{
				string strGuildMemberGrade;
				switch(guildNotice.iExt1)
				{
				case eGuildMemberGrade_MASTER:
					strGuildMemberGrade = _STR(GUILD_MEMBER_GRADE_MASTER);
					break;
				case eGuildMemberGrade_SUBMASTER:
					strGuildMemberGrade = _STR(GUILD_MEMBER_GRADE_SUBMASTER);
					break;
				case eGuildMemberGrade_HONOR:
					strGuildMemberGrade = _STR(GUILD_MEMBER_GRADE_HONOR);
					break;
				case eGuildMemberGrade_BEST:
					strGuildMemberGrade = _STR(GUILD_MEMBER_GRADE_BEST);
					break;
				case eGuildMemberGrade_NORMAL:
					strGuildMemberGrade = _STR(GUILD_MEMBER_GRADE_NORMAL);
					break;
				case eGuildMemberGrade_BEGINNER:
					strGuildMemberGrade = _STR(GUILD_MEMBER_GRADE_BEGINNER);
					break;
				case eGuildMemberGrade_INTERN:
					strGuildMemberGrade = _STR(GUILD_MEMBER_GRADE_INTERN);
					break;
				}
				message = format(_STR(INFORMATION_GUILD_CHANGE_GRADE_OK2), CNetClientManager::getInstance().getMyGuildName().c_str(), guildNotice.strExt.c_str(), strGuildMemberGrade.c_str());
				if(CTRGuildDlg::getInstance().isVisible()) CTRGuildDlg::getInstance().showDialog();
			}
			break;
		case eALARM_MSG_GUILD_LEVELUP:
			{
				string message = format(_STR(INFORMATION_GUILD_LEVEL_UP), guildNotice.strExt.c_str(), guildNotice.iExt1);
				string strOption;
				CTREssenGuild & guildLevelingInfo = CKeepGuildFarmItemList::getInstance().m_guildLevelingInfo;
				guildLevelingInfo.getDescByLevel(guildNotice.iExt1,strOption);

				CDetailMessageOKDialog::getInstance().showDialog(message,strOption, "gui\\Guild\\GuildLevelUp.gui");
				if(CTRGuildDlg::getInstance().isVisible()) CTRGuildDlg::getInstance().showDialog();
				return;
			}
			break;
		case eALARM_MSG_SYSTEM_GUILD_LEAVE:
			{
				message = format(_STR(INFORMATION_SYSTEM_GUILD_BANISHED), guildNotice.strExt.c_str());

				if(CTRGuildDlg::getInstance().isVisible()) CTRGuildDlg::getInstance().closeDialog();
			}
			break;
		}
		COkDialogEx::getInstance().showDialog(message, guiFileName, -1.f, bChangeWidth);
	}
	else
	{
		UserAlarmInfo tempguildNotice = guildNotice;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(tempguildNotice, true);
	}
}

/// 길드 가입 요청의 수락/거절 처리를 했다.
void CTRNetEventHandler::onRecvGuildProcessJoinRequest(const std::string& strNickName, bool bAccept)
{
	CTRGuildDlg::getInstance().onRecvGuildProcessJoinRequest(strNickName, bAccept);
}

void CTRNetEventHandler::onRecvGuildProcessJoinRequestFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildProcessJoinRequestFailed eGuildFailReason:%d", eReason);
	CTRGuildDlg::getInstance().onRecvGuildProcessJoinRequestFailed(eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

/// 길드에서 떠나기 요청을 처리했습니다.(자탈/추방)
void CTRNetEventHandler::onRecvGuildProcessLeave(const std::string& strMemberNickName, bool bBySelf, const int guildLevel)
{
	CTRGuildDlg::getInstance().onRecvGuildProcessLeave(strMemberNickName, bBySelf);

	// 자탈일 경우 길드 팜에서 -> 로비로 이동 
	if(bBySelf)
	{
		CTRGuildFarmUI::getInstance().onLeaveGuildFarm();

		int iGuildBuffItem;
		if(CKeepGuildFarmItemList::getInstance().m_guildLevelingInfo.getSupplyBuffItemNumByLevel(guildLevel, iGuildBuffItem))
		{
			const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(iGuildBuffItem);
			if(pItem && pItem->m_position == eFuncItemPosition_EXTRA_ABILITY)
			{
				std::vector<int> items;
				items.push_back(iGuildBuffItem);
				CNetClientManager::getInstance().requestActiveFuncItemLIst(items);
			}
		}
	}
}
void CTRNetEventHandler::onRecvGuildProcessLeaveFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildProcessLeaveFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 길드 가입 가능 레벨 설정 요청을 처리했습니다.
void CTRNetEventHandler::onRecvGuildModifyJoinLimmitLevel(short iLevel)
{
	CTRGuildDlg::getInstance().onRecvGuildModifyJoinLimmitLevel(iLevel);
}
void CTRNetEventHandler::onRecvGuildModifyJoinLimmitLevelFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildModifyJoinLimmitLevelFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 길드 가입 절차 설정 요청을 처리했습니다.
void CTRNetEventHandler::onRecvGuildModifyJoinMethod(eGuildJoinMethod eMethod)
{
	CTRGuildDlg::getInstance().onRecvGuildModifyJoinMethod(eMethod);
}
void CTRNetEventHandler::onRecvGuildModifyJoinMethodFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildModifyJoinMethodFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 길드 마크 설정 요청을 처리했습니다.
void CTRNetEventHandler::onRecvGuildModifyMark(int iMark)
{
}
void CTRNetEventHandler::onRecvGuildModifyMarkFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildModifyMarkFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 길드원의 등급 변경 요청을 처리했습니다.
void CTRNetEventHandler::onRecvGuildModifyMemberGrade(const std::string& strMemberNickName, eGuildMemberGrade eGrade)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildModifyMemberGrade strMemberNickName:%s eGrade:%d", strMemberNickName.c_str(), eGrade);
	CTRGuildDlg::getInstance().onRecvGuildModifyMemberGrade(strMemberNickName, eGrade);
}
void CTRNetEventHandler::onRecvGuildModifyMemberGradeFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildModifyMemberGradeFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 길드의 메시지 변경 요청을 처리했습니다.
void CTRNetEventHandler::onRecvGuildModifyMessage(const std::string& strMessage)
{
	CTRGuildDlg::getInstance().onRecvGuildModifyMessage(strMessage);
}
void CTRNetEventHandler::onRecvGuildModifyMessageFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildModifyMessageFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 길드의 이름 변경 요청을 처리했습니다.
void CTRNetEventHandler::onRecvGuildModifyName(const std::string& strBeforeName, const std::string& strName, int iItemNum, int iRemainItemCount)
{
	if (!strName.empty())
	{
		CTRGuildDlg::getInstance().onRecvGuildModifyName();
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iItemNum);
		CTRShortTimeMessage::showMessage(_STR(MSG_CHANGE_GUILDNAME_OK));
	}
}
void CTRNetEventHandler::onRecvGuildModifyNameFailed(const std::string& strName, int iItemNum, eGuildFailReason eReason)
{
	CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
}

// 길드 레벨업 요청을 처리했습니다.
void CTRNetEventHandler::onRecvGuildLevelUp(short iLevel)
{
	string guildName = CNetClientManager::getInstance().getMyGuildName();

	if (CTRNetPlayManager::getInstance().isGameStateNoGame())	
	{
		
		string message = format(_STR(INFORMATION_GUILD_LEVEL_UP), guildName.c_str(), iLevel);
		string strOption;
		CTREssenGuild & guildLevelingInfo = CKeepGuildFarmItemList::getInstance().m_guildLevelingInfo;
		guildLevelingInfo.getDescByLevel(iLevel,strOption);

		CTRGuildDlg::getInstance().onRecvGuildLevelUp(iLevel);

		CDetailMessageOKDialog::getInstance().showDialog(message,strOption, "gui\\Guild\\GuildLevelUp.gui");
	}
	else
	{
		UserAlarmInfo info;
		info.alarmMsg = eALARM_MSG_GUILD_LEVELUP;
		info.strExt = guildName;
		info.iExt1 = iLevel;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(info);
	}
	if(CTRGuildDlg::getInstance().isVisible())	CTRGuildDlg::getInstance().showDialog();
	CTRGuildFarmUI::getInstance().onRecvGuildLevelUp(iLevel);
	CTRFarmLobbyUIDlg::getInstance().updateGuildFarmInfo();
}
void CTRNetEventHandler::onRecvGuildLevelUpFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildLevelUpFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}
// 길드 정보 요청을 처리했습니다.
void CTRNetEventHandler::onRecvGuildGetGuildInfo(const GuildDetailInfo & info)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildGetGuildInfo");
	if(CTRGuildDlg::getInstance().isVisible())
	{
		CTRGuildDlg::getInstance().onRecvGuildGetGuildInfo(info);
	}

	if(CTRUserBookDlg::getInstance().isVisible())
	{
		CTRUserBookDlg::getInstance().onRecvGuildGetGuildInfo(info);
	}
}
void CTRNetEventHandler::onRecvGuildGetGuildInfoFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildGetGuildInfoFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 길드 마스터 권한 이양을 처리했습니다.
void CTRNetEventHandler::onRecvGuildConveyanceMaster(const std::string& strNewMasterNickName, int iItemNum, int iRemainCount)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildConveyanceMaster");

	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildConveyanceMaster(strNewMasterNickName, iItemNum, iRemainCount);

		if(CTRGuildDlg::getInstance().isVisible() || CTRUserBookDlg::getInstance().isVisible())
		{
			CNetClientManager::getInstance().requestGuild_getGuildInfo(strNewMasterNickName);
		}
	}

	if(iRemainCount > 0)
		CKeepItemList::getInstance().modifyItemCount(iItemNum, iRemainCount);
	else
		CKeepItemList::getInstance().eraseItem( iItemNum );
}

void CTRNetEventHandler::onRecvGuildConveyanceMasterCandidates(std::vector<std::string> vecCandidate)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildConveyanceMasterCandidates size:%d", (int)vecCandidate.size());

	vector<NetItemInfo> destLIst; 
	CKeepItemList::getInstance().getItemList(eCharacterKind_NONE, eFuncItemPosition_CONVEYANCE_MASTER, destLIst);				
	if(!destLIst.empty())
	{
		CTRGuildConvMasterDlg::getInstance().showDialog(destLIst[0].m_iItemDescNum, vecCandidate);
	}
}

void CTRNetEventHandler::onRecvGuildConveyanceMasterFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildConveyanceMasterFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 길드 포인트 추가 아이템을 사용했습니다.
void CTRNetEventHandler::onRecvGuildIncreaseGuildPoint(int iItemNum, int iRemainCount)
{
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iItemNum);

	const CItemAttr itemAttr = CItemAttrTable::getInstance().getItemAttrFromItemDescNum(iItemNum);
	int iAddPoint = (int)itemAttr.m_attr[eItemAttr_GuildPoint_Bonus];

	const GuildDetailInfo& info = CNetClientManager::getInstance().getGuildInfo();
	CNetClientManager::getInstance().requestGuild_getGuildPoint(info.m_iNum);

	COkDialogEx::getInstance().showDialog(format(_STR(MGS_INCREASE_GUILD_POINT_OK), iAddPoint));
}
void CTRNetEventHandler::onRecvGuildIncreaseGuildPointFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildIncreaseGuildPointFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 내가 가입 신청한 길드 리스트를 받았다.
void CTRNetEventHandler::onRecvGuildProposeListNotify()
{

}

// 길드 공헌포인트 요청을 처리했습니다.
void CTRNetEventHandler::onRecvGuildGetMyContributionPoint(const int iContributionPoint)
{
	CTRGuildFarmUI::getInstance().onRecvCurrentMyGuildPoint(iContributionPoint);
}
void CTRNetEventHandler::onRecvGuildGetMyContributionPointFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildGetMyContributionPointFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 길드 포인트 요청을 처리했습니다.
void CTRNetEventHandler::onRecvGuildGetGuildPoint(const __int64 iGuildPoint)
{
	CTRGuildFarmUI::getInstance().onRecvCurrentGuildPoint(iGuildPoint);
}
void CTRNetEventHandler::onRecvGuildGetGuildPointFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildGetGuildPointFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 길드 마스터의 선물 아이템을 사용에 대한 결과를 받았다.
void CTRNetEventHandler::onRecvGuildUseGiftBox(int iReceivedItemNum, int iGiftBoxItemNum, int iReaminItemCount)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildUseGiftBox iReceivedItemNum:%d, iGiftBoxItemNum:%d, iReaminItemCount:%d", iReceivedItemNum, iGiftBoxItemNum, iReaminItemCount);	
	CKeepItemList::getInstance().eraseItem(iGiftBoxItemNum);

	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iGiftBoxItemNum);
}

void CTRNetEventHandler::onRecvGuildUseGiftBoxFailed(eGuildFailReason eReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildUseGiftBoxFailed eGuildFailReason:%d", eReason);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRGuildDlg::getInstance().onRecvGuildFailed(eReason);
	}
}

// 시스템 길드 졸업을 했다
void CTRNetEventHandler::onRecvGuildGraduationOK()
{
	DBG_OUTPUT("%s", __FUNCTION__);

	if(CNetClientManager::getInstance().isSystemGuild())
	{
		CTRGuildDlg::getInstance().setGraduationPopup(true);
	}
}

void CTRNetEventHandler::onRecvGuildGraduationFailed()
{
	DBG_OUTPUT("%s", __FUNCTION__);

}

// 스킬 습득을 성공 하였다.
void CTRNetEventHandler::onRecvGuildSkillAdd( GuildDetailInfo& guildInfo, std::map<int, int> &mapItemList )
{
	GUILD_SKILL_TREE::CTRGuildSkillManager::getInstance().onRecvGuildSkillAdd( guildInfo, mapItemList );
}

// 스킬 습득을 실패 하였다.
void CTRNetEventHandler::onRecvGuildSkillAddFailed( eGuildSkillCheckAvailabilityType result )
{
	GUILD_SKILL_TREE::CTRGuildSkillManager::getInstance().onRecvGuildSkillDataUpdateFailed( result );
}

// 스킬 초기화 성공
void CTRNetEventHandler::onRecvGuildSkillReset( GuildDetailInfo& guildInfo )
{
	GUILD_SKILL_TREE::CTRGuildSkillManager::getInstance().onRecvGuildSkillReset( guildInfo );
}

// 스킬 초기화 실패
void CTRNetEventHandler::onRecvGuildSkillResetFailed( eGuildSkillCheckAvailabilityType result )
{
	GUILD_SKILL_TREE::CTRGuildSkillManager::getInstance().onRecvGuildSkillDataUpdateFailed( result );
}

/// 길드 공방 관련 알람 메시지를 받았다.
void CTRNetEventHandler::onRecvGuildPlantNotify(const UserAlarmInfo& guildNotice)
{
	DBG_OUTPUT("%s - AlarmMessage[%s]", __FUNCTION__, guildNotice.strExt.c_str());

	CTRAniAlarmDlg::getInstance().isVisible() ?
		CTRAniAlarmDlg::getInstance().pushMessage(eVIEW_TYPE_GUILD_PLANT_COMPLETE, guildNotice.strExt) :
		CTRAniAlarmDlg::getInstance().showDialog(eVIEW_TYPE_GUILD_PLANT_COMPLETE, guildNotice.strExt);
}

//!< 길드 운영 TR  요청 정보를 받았다.
void CTRNetEventHandler::onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR)
{
	DBG_OUTPUT("%s - iGuildManagerTR[%I64d]", __FUNCTION__, iGuildManagerTR);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetGuildManagerTR(iGuildManagerTR);
}

void CTRNetEventHandler::onRecvGuildPlantGetGuildManagerTRFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetGuildManagerTRFailed(iFailedReason);
}

//!< 길드 운영 TR 를 투자에 성공했다.
void CTRNetEventHandler::onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR)
{
	DBG_OUTPUT("%s - iGuildManagerTR[%I64d]", __FUNCTION__, iGuildManagerTR);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantInvestGuildManagerTR(iGuildManagerTR);
}

//!< 길드 운영 TR 를 투자에 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantInvestGuildManagerTRFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantInvestGuildManagerTRFailed(iFailedReason);
}

//!< 길드 운영 TR 창고 확장 정보를 요청 성공했다.
void CTRNetEventHandler::onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue)
{
	DBG_OUTPUT("%s - iExtendCount[%d], iExtendValue[%d], iUserInvestCount[%d],", __FUNCTION__, iExtendCount, iExtendValue, iUserInvestCount);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetStorageExtendOK(iExtendCount, iExtendValue, iUserInvestCount, iUserInvestValue);
}

//!< 길드 운영 TR 창고 확장 정보를 요청 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantGetStorageExtendFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetStorageExtendFailed(iFailedReason);
}

//!< 길드공방 아이템 제작 등록을 성공했다.
void CTRNetEventHandler::onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR)
{
	DBG_OUTPUT("%s - iGuildManagerTR[%I64d]", __FUNCTION__, iGuildManagerTR);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantRegisterItemOK(iGuildManagerTR);
}

//!< 길드공방 아이템 제작 등록을 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantRegisterItemFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantRegisterItemFailed(iFailedReason);
}

//!< 길드공방 제작 진행 아이템 정보를 요청 성공했다
void CTRNetEventHandler::onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind)
{
	DBG_OUTPUT("%s - iMyContributionPoint[%d], distributeKind[%d]", __FUNCTION__, iMyContributionPoint, distributeKind);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetMakeProgressItemOK(guildplantMakeInfo, iMyContributionPoint, distributeKind);
}

//!< 길드공방 제작 진행 아이템 정보를 요청 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantGetMakeProgressItemFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetMakeProgressItemFailed(iFailedReason);
}

//!< 길드공방 제작 대기 아이템 리스트를 요청 성공했다
void CTRNetEventHandler::onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant)
{
	DBG_OUTPUT("%s - Itemlist size[%d]", __FUNCTION__, (int)guildplant.size());
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetMakeStandByItemListOK(guildplant);
}

//!< 길드공방 제작 대기 아이템 리스트를 요청 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantGetMakeStandByItemFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetMakeStandByItemFailed(iFailedReason);
}

//!< 길드공방 제작 기여 아이템을 변경 성공했다.
void CTRNetEventHandler::onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum)
{
	DBG_OUTPUT("%s - iItemIndexNum[%d]", __FUNCTION__, iItemIndexNum);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantChangeMyConstributionPointItemOK(iItemIndexNum);
}

//!< 길드공방 제작 기여 아이템을 변경 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantChangeMyConstributionPointItemFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantChangeMyConstributionPointItemFailed(iFailedReason);
}

//!< 길드 운영 TR 투자자 리스트를 요청 성공했다
void CTRNetEventHandler::onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList)
{
	DBG_OUTPUT("%s - UserList size[%d]", __FUNCTION__, (int)userList.size());
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetInvestorManagerTRListOK(userList);
}

//!< 길드 운영 TR 투자자 리스트를 요청 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantGetInvestorManagerTRFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetInvestorManagerTRFailed(iFailedReason);
}

//!< 길드 재화 지출 리스트를 요청 성공했다
void CTRNetEventHandler::onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList)
{
	DBG_OUTPUT("%s - iMonth[%d], UseList size[%d], iUserInvestCount[%d],", __FUNCTION__, iMonth, (int)useList.size());
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetExpenseListOK(pointType, iMonth, useList);
}

//!< 길드 재화 지출 리스트를 요청  실패하였다.
void CTRNetEventHandler::onRecvGuildPlantGetExpenseListFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetExpenseListFailed(iFailedReason);
}

//!< 길드공방 아이템 기여도 순위 리스트를 요청 성공했다
void CTRNetEventHandler::onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList)
{
	DBG_OUTPUT("%s - UserList size[%d]", __FUNCTION__, (int)userList.size());
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetItemContributeRankLIstOK(userList);
}

//!< 길드공방 아이템 기여도 순위 리스트를 요청 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantGetItemContributeRankLIstFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetItemContributeRankLIstFailed(iFailedReason);
}

//!< 아이템 지급 가능 길드원 리스트를 요청 성공했다.
void CTRNetEventHandler::onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList)
{
	DBG_OUTPUT("%s - UserList size[%d]", __FUNCTION__, (int)userList.size());
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetGivePossibleUserListOK(userList);
}

//!< 아이템 지급 가능 길드원 리스트를 요청 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantGetGivePossibleUserListFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetGivePossibleUserListFailed(iFailedReason);
}

//!< 길드공방 아이템 지급를 요청 성공했다.
void CTRNetEventHandler::onRecvGuildPlantGiveGiftOK(int iItemIndexNum)
{
	DBG_OUTPUT("%s - iItemIndexNum[%d]", __FUNCTION__, iItemIndexNum);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGiveGiftOK(iItemIndexNum);
}

//!< 길드공방 아이템 지급를 요청 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantGiveGiftFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGiveGiftFailed(iFailedReason);
}

//!< 길드공방 아이템 리스트를 요청 성공했다
void CTRNetEventHandler::onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList)
{
	DBG_OUTPUT("%s - UserList size[%d]", __FUNCTION__, (int)useList.size());
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetPlantItemListOK(useList);
}

//!< 길드공방 아이템 리스트를 요청 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantGetPlantItemListFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantGetPlantItemListFailed(iFailedReason);
}

//!< 길드공방 아이템 구매를 요청 성공했다
void CTRNetEventHandler::onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount)
{
	DBG_OUTPUT("%s - iSellNum[%d], iItemNum[%d], iBuyCount[%d]", __FUNCTION__, iSellNum, iItemNum, iBuyCount);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantBuyItemOK(iSellNum, iItemNum, iBuyCount);
}

//!< 길드공방 아이템 구매를 요청 실패하였다.
void CTRNetEventHandler::onRecvGuildPlantBuyItemFailed(eGuildPlantFailReason iFailedReason)
{
	DBG_OUTPUT("%s - Reason[%d]", __FUNCTION__, iFailedReason);
	CTRGuildFarmUI::getInstance().onRecvGuildPlantBuyItemFailed(iFailedReason);
}


/// 핫타임 이벤트 정보를 받았다.
void CTRNetEventHandler::onRecvHotTimeEventInfoAck( const std::map<__int64, HotTimeEventInfo> & hotTimeEventInfo )
{
	DBG_OUTPUT("%s, hotTimeEventInfo Size : %d", __FUNCTION__, hotTimeEventInfo.size());
	CTRHotTimeEventManager::getinstance().onRecvHotTimeEventInfoAck(hotTimeEventInfo);
}

/// 유저가 핫타임 정보를 받았다.
void CTRNetEventHandler::onRecvHotTimeEventSettingAck( const bool bUpdateSetting, const HotTimeEventInfo & hotTimeEventInfo )
{
	DBG_OUTPUT("%s, bUpdateSetting : %d, iHotTimeEventID : %I64d, tHotTimeStrtTime = %I64d, tHotTimeFinishTime = %I64d, tHotTimeRequireTime = %I64d, RewardSize : %d, iHotTimeEventUserNum : %d",
		__FUNCTION__, bUpdateSetting, hotTimeEventInfo.iHotTimeEventID, hotTimeEventInfo.tHotTimeStartTime, hotTimeEventInfo.tHotTimeFinishTime, hotTimeEventInfo.tHotTimeRequireTime, hotTimeEventInfo.vecRewardList.size(), hotTimeEventInfo.iHotTimeEventUserNum);
	CTRHotTimeEventManager::getinstance().onRecvHotTimeEventSettingAck(bUpdateSetting, hotTimeEventInfo);
}

/// 핫타임 이벤트 정보 설정이 실패하였다
void CTRNetEventHandler::onRecvHotTimeEventSettingFaildAck( eHotTimeEventFailedReason failReason )
{
	DBG_OUTPUT("%s, FailReason : %d", __FUNCTION__, failReason);
	CTRHotTimeEventManager::getinstance().onRecvHotTimeEventSettingFaildAck(failReason);
}

/// 핫타임 이벤트 정보를 삭제했다.
void CTRNetEventHandler::onRecvHotTimeEventDeleteAck( const __int64 iHotTimeEventID )
{
	DBG_OUTPUT("%s, iHotTimeEventID : %I64d", __FUNCTION__, iHotTimeEventID);
	CTRHotTimeEventManager::getinstance().onRecvHotTimeEventDeleteAck(iHotTimeEventID);
}

/// 유저가 핫타임 이벤트 응모에 성공했다.
void CTRNetEventHandler::onRecveHotTimeEventApplyAck( const __int64 iHotTimeEventID )
{
	DBG_OUTPUT("%s, iHotTimeEventID : %I64d", __FUNCTION__, iHotTimeEventID);
	CTRHotTimeEventManager::getinstance().onRecveHotTimeEventApplyAck(iHotTimeEventID);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOTTIME_ENTRY);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 유저가 핫타임 이벤트 응모에 실패했다.
void CTRNetEventHandler::onRecveHotTimeEventApplyFaildAck( const eHottimApplyFailedReason hotTimeResult, const __int64 iHotTimeEventID )
{
	DBG_OUTPUT("%s, FailedReason : %d, iHotTimeEventID : %I64d", __FUNCTION__, hotTimeResult, iHotTimeEventID);
	CTRHotTimeEventManager::getinstance().onRecveHotTimeEventApplyFaildAck(hotTimeResult);
}

void CTRNetEventHandler::OnRecvItemConvertAck(const item_convert::CDoConvertResult& result)
{
	std::string strMent = "";

	const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(result.source_item());

	if(result.result() == item_convert::CDoConvertResult::eRESULT_SUCCESS)
	{	
		if(pItem != NULL)
		{
			strMent = format(_STR(MSG_ITEM_CONVERT_OK), result.receiver().c_str(), pItem->m_name.c_str());
			CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(pItem->m_iUniqueNumber);
		}
	}
	else
	{
		if(pItem != NULL)
		{
			switch(result.result())
			{
			case item_convert::CDoConvertResult::eRESULT_FAIL_BY_LIMITED_COUNT:
				{
					item_convert::CDoConvertResult::ERROR_DESC_eRESULT_FAIL_BY_LIMITED_COUNT desc;
					result.error_desc(desc);
#ifdef _VALENTINE
					strMent = format(_STR(MSG_ITEM_CONVERT_FAIL_LIMIT_COUNT_TODAY), result.receiver().c_str(), desc.limit, pItem->m_name.c_str(), desc.limit - desc.prev_count);
#else
					strMent = format(_STR(MSG_ITEM_CONVERT_FAIL_LIMIT_COUNT), result.receiver().c_str(), desc.limit, desc.limit - desc.prev_count);
#endif
				}			
				break;

			case item_convert::CDoConvertResult::eRESULT_NO_TARGET_USER:
				strMent = _STR(ITEM_STORAGE_INVALID_GIFT_USER);
				break;
			case item_convert::CDoConvertResult::eRESULT_NOT_PROPER_SENDER_OR_RECEIVER:
#ifdef _VALENTINE
				strMent = _STR(MSG_ITEM_CONVERT_INVALID_SENDER_OR_RECEIVER);
#else
				strMent = format(_STR(MSG_ITEM_CONVERT_CANNOT_SEND), result.receiver().c_str());
#endif
				break;

			case item_convert::CDoConvertResult::eRESULT_FAIL_TO_CHECK_CONDITION:
			case item_convert::CDoConvertResult::eRESULT_FAIL_TO_DELETE_SOURCE_ITEM:
			case item_convert::CDoConvertResult::eRESULT_NOT_COVERTABLE_ITEM:
			case item_convert::CDoConvertResult::eRESULT_NOT_ENOUGH_SOURCE:
			case item_convert::CDoConvertResult::eRESULT_FAIL_TO_SEND_ITEM:
				strMent = format(_STR(MSG_ITEM_CONVERT_CANNOT_SEND), result.receiver().c_str());
				break;
			}
		}
	}

	DBG_DEMO_OUTPUT(123, "%s - %s", __FUNCTION__, strMent.c_str());

	if(!strMent.empty())
	{
		COkDialogEx::getInstance().showDialog(strMent);
	}
}

void CTRNetEventHandler::OnRecvEventStatusUpdateAck(const CEventStatusUpdateAck& ack)
{
//	CTRUserInterface::getInstance().onUserEvent("OneShotEvent_Update");
}

void CTRNetEventHandler::OnRecvEventStatusExecAck(const CEventStatusExecAck& ack)
{
	CTRUserInterface::getInstance().onUserEvent("OneShotEvent_Exec");
}

void CTRNetEventHandler::OnRecvEventStatusQueryAck(const CEventStatusQueryAck& ack)
{
	CTRUserInterface::getInstance().onUserEvent("OneShotEvent_Popup");
}

void CTRNetEventHandler::community_onConnectFail(eCommunityConnectFail failReason)
{
	string msg;
	switch(failReason)
	{
	case eCommunityConnectFail_QUOTA: /// 서버의 접속한계를 초과했다.
		msg = _STR(FAILED_LOGIN_COMMUNITY_SERVER_FULL);
		break;
	case eCommunityConnectFail_DUPLICATE_NICKNAME: /// 커뮤니티 서버에 중복 로그인
		msg = _STR(FAILED_LOGIN_COMMUNITY_DUPLICATE_NICKNAME);
		break;
	case eCommunityConnectFail_NO_NICKNAME: /// 닉네임이 없다.
		msg = _STR(FAILED_LOGIN_COMMUNITY_NO_NICKNAME);
		break;
	case eCommunityConnectFail_UNKNOWN: /// 알 수 없는 이유...
		msg = _STR(FAILED_LOGIN_COMMUNITY_UNKNOWN);
		break;
	}
	CTRShortTimeMessage::showMessage(msg);
}

/// 친구 아바타 정보를 받았다.
void CTRNetEventHandler::community_onRecvFriendAvatarInfo(const std::string & strFriendNickname, const exp_type iExp
#ifdef _NUMBERS
														  , const int iNumbers
#endif
														  , const AvatarInfo & avatarInfo)
{
	DBG_OUTPUT(60, "community_onRecvFriendAvatarInfo");
	CTRMessengerMainUI::getInstance().community_onRecvFriendAvatarInfo(strFriendNickname, iExp
#ifdef _NUMBERS
		, iNumbers
#endif
		, avatarInfo);
}

void CTRNetEventHandler::community_onRecvMsg(const std::string & strNickname, const std::string & strMsg)
{
	DBG_OUTPUT(60, "community_onRecvMsg");

	bool bSendMsgAck = false;
	eMessageResult messageResult;
	
	std::string strConvertMsg;
	cutInvalidCharacter(strMsg, strConvertMsg, "([\n\r])");

	if(CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_1ON1CHAT)))
	{
		bSendMsgAck = true;
		messageResult = eMessageResult_OK;
	}
	else
	{
		if(CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_1ON1CHAT_FRIEND)))
		{
			const FriendInfo * pInfo = CNetClientManager::getInstance().getFriendInfo(strNickname);
			if(pInfo)
			{
				if(pInfo->m_eState == eUserState_OffLine)
				{
					CTRShortTimeMessage::showMessage(_STR(MSG_OFFLINE_USER));
					return;
				}
				else if(pInfo->m_eState == eUserState_WaitAccept)
				{
					bSendMsgAck = false;
					messageResult = eMessageResult_REFUSE_FRIEND;
				}

				if(pInfo->m_bBlocked)
				{
					CTRShortTimeMessage::showMessage(_STR(MSG_BLOCKED_USER));

					bSendMsgAck = false;
					messageResult = eMessageResult_REJECTION;
				}

				bSendMsgAck = true;
				messageResult = eMessageResult_OK;
			}
			else
			{
				bSendMsgAck = false;
				messageResult = eMessageResult_REFUSE_FRIEND;
			}
		}
		else
		{
			bSendMsgAck = false;
			messageResult = eMessageResult_REJECTION;
		}
	}

	if(bSendMsgAck)
	{
		if(CTRNetPlayManager::getInstance().isGameStateNoGame() || !CGameManager::getInstance().isGameModeNetworkPlay())
		{
				if(CTRGameParkUI::getInstance().getMyUserState() == PARK_MYSTATE_IN_OPENTV)
				{
					CTRGameParkUI::getInstance().onRecvWhisperMessage(strNickname, strConvertMsg);
					CTRMessengerMainUI::getInstance().community_onRecvMsg(strNickname, "", strConvertMsg, eChatting_Type_NORMAL_TALK);		// OpenTV 채팅 때도 메신저에 남겨둔다.
				}
				else
				{
					CTRMessengerMainUI::getInstance().community_onRecvMsg(strNickname, "", strConvertMsg, eChatting_Type_NORMAL_TALK);
				}
			}
		else
		{
			CChatItemProcessor::getInstance().community_onRecvMsg(strNickname, strConvertMsg);
			CTRMessengerMainUI::getInstance().community_onRecvMsg(strNickname, "", strConvertMsg, eChatting_Type_NORMAL_TALK);		// 게임 중이고, 네트워크 상태라면...메신저 채팅창에도 남긴다.
		}

		CTRChattingManager::getInstance().saveNickname(strNickname);
	}

	CNetClientManager::getInstance().community_sendChatMsgAck(strNickname, strConvertMsg, messageResult);
}

/// 메세지에 대한 응답을 받았다.
void CTRNetEventHandler::community_onRecvMsgAck(const std::string& strNickName, const std::string& strMsg, eMessageResult messageResult)
{
	DBG_OUTPUT(60, "community_onRecvMsgAck");

	std::string strConvertMsg;
	cutInvalidCharacter(strMsg, strConvertMsg, "([\n\r])");

	if(!CTRNetPlayManager::getInstance().isGameStateNoGame() && CGameManager::getInstance().isGameModeNetworkPlay())
	{
		CChatItemProcessor::getInstance().community_onRecvMsgAck(strNickName, strConvertMsg, messageResult);
	}

	CTRMessengerMainUI::getInstance().community_onRecvMsgAck(strNickName, strConvertMsg, messageResult, eChatting_Type_NORMAL_TALK);
}

/// 메시지를 보내지 못하고 다시 받음
void CTRNetEventHandler::community_onRecvForwardingMsgFailed(const std::string & strFromNickName, eForwardingFailed eResult)
{
	CTRMessengerMainUI::getInstance().community_onRecvForwardingMsgFailed(strFromNickName, eResult);
}

/// 채팅 귓말 메세지 요청을 받았다.
void CTRNetEventHandler::community_onRecvWhisperMsgReq(const std::string & strNickname, const byte byUserAttr, const std::string & strMsg)
{
	DBG_OUTPUT(60, "community_onRecvWhisperMsgReq");

	std::string strConvertMsg;
	cutInvalidCharacter(strMsg, strConvertMsg, "([\n\r])");

	//차단된 유저인지 체크 하는 부분

	const FriendInfo *pFriendInfo = CNetClientManager::getInstance().getFriendInfo(strNickname);

	if(pFriendInfo && pFriendInfo->m_bBlocked)
	{
		CNetClientManager::getInstance().community_sendWhisperMsgAck(strNickname, byUserAttr, strConvertMsg, eWhisperRequestResult_BLOCKED);
		return;
	}

	//! 옵션에 귓말이 껴져 있을 경우
	if(!CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_WHISPER_CONSENT)) && byUserAttr == eAccountAttrType_Normal)
	{
		if(CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_WHISPER_FRIEND)))
		{
			if(pFriendInfo == NULL)
			{
				CNetClientManager::getInstance().community_sendWhisperMsgAck(strNickname, byUserAttr, strConvertMsg, eWhisperRequestResult_REFUSE_WHISPER);
				return;
			}
		}
		else
		{
			CNetClientManager::getInstance().community_sendWhisperMsgAck(strNickname, byUserAttr, strConvertMsg, eWhisperRequestResult_REFUSE_WHISPER);
			return;
		}
	}

	std::string chatMsg = format(_STR(FORMAT_CHAT_WHISPER_RECV), strNickname.c_str(), strConvertMsg.c_str());
	if(CTRNetPlayManager::getInstance().isGameStateNoGame() || !CGameManager::getInstance().isGameModeNetworkPlay())
	{
			if(CTRGameParkUI::getInstance().getMyUserState() == PARK_MYSTATE_IN_OPENTV)
			{
				CTRGameParkUI::getInstance().onRecvWhisperMessage(strNickname, strConvertMsg);
			}
			else
			{
				if(CNetClientManager::getInstance().getRoomHandle() != 0)
				{
					CTRChattingManager::getInstance().insertWhisperChatData(chatMsg,CColor::GREEN,false);
					CTRUserInterface::getInstance().updateChat();
				}
				else 
				{
					CNetClientManager::getInstance().community_sendWhisperMsgAck(strNickname, byUserAttr, strConvertMsg, eWhisperRequestResult_NOT_ROOM_IN);
					return;
				}
			}
		}
	else
	{
		CTRChattingManager::getInstance().insertWhisperChatData(chatMsg,CColor::GREEN,true);
		CChatItemProcessor::getInstance().saveNickname(const_cast<string&>(strNickname));
	}
	CTRChattingManager::getInstance().saveNickname(const_cast<string&>(strNickname));
	CNetClientManager::getInstance().community_sendWhisperMsgAck(strNickname, byUserAttr, strConvertMsg, eWhisperRequestResult_OK);
}

/// 채팅 귓말 메세지 응답을 받았다.
void CTRNetEventHandler::community_onRecvWhisperMsgAck(const std::string & strNickname, const byte byUserAttr, const std::string & strMsg, const eWhisperRequestResult whisperRequestResult)
{
	DBG_OUTPUT(60, "community_onRecvWhisperMsgAck");

	string chatMsg;

	CColor color;

	std::string strConvertMsg;
	cutInvalidCharacter(strMsg, strConvertMsg, "([\n\r])");

	switch(whisperRequestResult)
	{
	case eWhisperRequestResult_OK:
	case eWhisperRequestResult_BLOCKED :
		chatMsg = format(_STR(FORMAT_CHAT_WHISPER_SEND), strNickname.c_str(), strConvertMsg.c_str());
		color = CColor(1.f, 0.75f, 0.f);
		break;
	case eWhisperRequestResult_NOT_CONNECT:			///< 유저가 접속되어 있지 않다.
		break;
	case eWhisperRequestResult_REFUSE_WHISPER:		///< 유저가 귓말 거부가 되어 있다.
		chatMsg = format(_STR(MSG_WHISPER_REFUSE), strNickname.c_str());
		color = CColor::RED;
		break;
	case eWhisperRequestResult_NOT_ROOM_IN:			///< 귓말을 받을수 없는곳에 있다.
		chatMsg = format(_STR(MSG_WHISPER_NOT_ROOM_IN), strNickname.c_str());
		color = CColor::RED;
		break;
	case eWhisperRequestResult_UNKNOWN:
		break;
	}

	if(CTRNetPlayManager::getInstance().isGameStateNoGame() || !CGameManager::getInstance().isGameModeNetworkPlay())
	{
			if(CTRGameParkUI::getInstance().getMyUserState() == PARK_MYSTATE_IN_OPENTV)
			{
				CTRGameParkUI::getInstance().onRecvWhisperMessage(strNickname, strConvertMsg, true);
			}
			else
			{
				if(CNetClientManager::getInstance().getRoomHandle() != 0)
				{
					CTRChattingManager::getInstance().insertWhisperChatData(chatMsg, color,false);
					CTRUserInterface::getInstance().updateChat();
				}
				else 
				{
					return;
				}
			}
		}
	else
	{
		CTRChattingManager::getInstance().insertWhisperChatData(chatMsg, color,true);
	}

	if(whisperRequestResult == eWhisperRequestResult_OK)
	{
		CTRChattingManager::getInstance().saveNickname(strNickname);
	}
}

/// 일반, 가족, 길드, 파티 채팅 메세지를 받았다.
void CTRNetEventHandler::community_onRecvChatting(const std::string & strNickname, const std::string & strMsg, eChattingType chattingType)
{
	DBG_DEMO_OUTPUT("CTRNetEventHandler::community_onRecvChatting Nickname=[%s], Msg=[%s], chattingType=[%d]", strNickname.c_str(), strMsg.c_str(), (int)chattingType);

	std::string strConvertMsg;
	cutInvalidCharacter(strMsg, strConvertMsg, "([\n\r])");

	CTRChattingManager::getInstance().community_onRecvChatting(strNickname,strConvertMsg,chattingType); //! 유저에게 직접표현해주진 않는다 데이터만 누적시킨다..

	//! 실제적인 유저에게 표현해준다..(데이터 삽입하지 말것 중복된다)
	CTRUserInterface::getInstance().community_onRecvChatting(strNickname, strConvertMsg, chattingType);
}

/// 누군가의 상태를 받았다.
void CTRNetEventHandler::community_onRecvState(const std::string & strNickname, const UserState & state)
{
	DBG_OUTPUT(60, "community_onRecvState");

	CTRMessengerMainUI::getInstance().community_onRecvState(strNickname, state);
	CTRPlayerPopup::getInstance().community_onRecvState(strNickname, state);
}

/// 친구 추가가 성공했다.
void CTRNetEventHandler::onRecvAddFriendOK(const std::string & strNickname)
{
	DBG_OUTPUT(60, "onRecvAddFriendOK");
	CTRMessengerMainUI::getInstance().onRecvAddFriendOK(strNickname);

	//! 도전 미션이 있는지 확인한다.
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_PARENT);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_BROTHER);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_CHILD);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_FRIEND);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 친구의 게임 상태를 받았다.
void CTRNetEventHandler::community_onRecvGameState(const std::string & strFriendNickname, bool bPlayGame)
{
	DBG_OUTPUT(60, "community_onRecvGameState");
	CTRMessengerMainUI::getInstance().community_onRecvGameState(strFriendNickname, bPlayGame);
}

/// 친구 추가가 실패했다.
void CTRNetEventHandler::onRecvAddFriendFailed(const std::string & strNickname, eAddFriendFailed addFriendFailed)
{
	DBG_OUTPUT(60, "onRecvAddFriendFailed");
	CTRMessengerMainUI::getInstance().onRecvAddFriendFailed(strNickname, addFriendFailed);
}


/// 친구 수락이 성공했다.
void CTRNetEventHandler::community_onRecvAcceptFriendOK(const std::string & strNickname)
{
	DBG_OUTPUT(60, "community_onRecvAcceptFriendOK");

	//! 도전 미션이 있는지 확인한다.
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_PARENT);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_BROTHER);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_CHILD);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_FRIEND);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 친구 수락이 실패했다.
void CTRNetEventHandler::community_onRecvAcceptFriendFailed(const std::string & strNickname, eCommunityAcceptFriendFailedReason reason)
{
	DBG_OUTPUT(60, "community_onRecvAcceptFriendFailed");
	CTRMessengerMainUI::getInstance().community_onRecvAcceptFriendFailed(strNickname,reason);

}

/// 나를 친구로 등록한 게 있다.
void CTRNetEventHandler::onRecvRequestToMeFriend(const std::string & strNickname, const std::string & strInviteMessage)
{
	DBG_OUTPUT(60, "onRecvRequestToMeFriend");

	if(!CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_ADD_FRIEND_ACCEPT)))
	{
		CNetClientManager::getInstance().community_declineFriend(strNickname);
		return;
	}

	CTRMessengerMainUI::getInstance().onRecvRequestToMeFriend(strNickname,strInviteMessage);
	CTRUserInterface::getInstance().onRecvRequestToMeFriend();
	CTRLobbyUI::getInstance().onRecvRequestToMeFriend();
	CTRGameRoomCrowdUI::getInstance().onRecvRequestToMeFriend();
	CTRGameRoomRelayUI::getInstance().onRecvRequestToMeFriend();
	CTRGameRoomUINormalPlay::getInstance().onRecvRequestToMeFriend();
	CTRGameRoomUITeamPlay::getInstance().onRecvRequestToMeFriend();
	CTRMyRoomUI::getInstance().onRecvRequestToMeFriend();
	CTRShopUI::getInstance().onRecvRequestToMeFriend();
	CTRGameParkUI::getInstance().onRecvRequestToMeFriend();
	CTRFarmUI::getInstance().onRecvRequestToMeFriend();
}

//==================================================
//	[mirime 2019-02-21] Create
//==================================================
void CTRNetEventHandler::community_onRecvCheckFriendRequest(bool reqeustAdd, const std::string & nickname)
{
	if (reqeustAdd == false)
	{
		//[mirime 2019-02-21] cancel add friend
		CTRMessengerMainUI::getInstance().removeRequestToMeFriend(nickname);
	}
}

/// 친구 거절을 성공했다.
void CTRNetEventHandler::community_onRecvDeclineFriendOK(const std::string & strNickname)
{
	DBG_OUTPUT(60, "community_onRecvDeclineFriendOK");
	if(CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_ADD_FRIEND_ACCEPT)))
	{
		CTRMessengerMainUI::getInstance().community_onRecvDeclineFriendOK(strNickname);
	}
}

/// 친구 거절을 실패했다.
void CTRNetEventHandler::community_onRecvDeclineFriendFailed(const std::string & strNickname)
{
	DBG_OUTPUT(60, "community_onRecvDeclineFriendFailed");
	if(CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_ADD_FRIEND_ACCEPT)))
	{
		CTRMessengerMainUI::getInstance().community_onRecvDeclineFriendFailed(strNickname);
	}
}

/// 친구 등록을 거절당했다.
void CTRNetEventHandler::community_onRecvDeclineFriend(const std::string & strNickname)
{
	DBG_OUTPUT(60, "community_onRecvDeclineFriend");
	CTRMessengerMainUI::getInstance().community_onRecvDeclineFriend(strNickname);
}

/// 친구를 블럭하는데 성공했다.
void CTRNetEventHandler::community_blockFriendOK(const std::string & strFriendNickname)
{
	DBG_OUTPUT(60, "community_blockFriendOK");
	CTRMessengerMainUI::getInstance().community_blockFriendOK(strFriendNickname);
}

/// 친구를 블럭하는데 실패했다.
void CTRNetEventHandler::community_blockFriendFailed(const std::string & strFriendNickname, eRemoveFriendFailed eFailedReason)
{
	DBG_OUTPUT(60, "community_blockFriendFailed");
	CTRMessengerMainUI::getInstance().community_blockFriendFailed(strFriendNickname);
}

/// 친구 블럭을 취소하는데 성공했다.
void CTRNetEventHandler::community_unblockFriendOK(const std::string & strFriendNickname)
{
	DBG_OUTPUT(60, "community_unblockFriendOK");
	CTRMessengerMainUI::getInstance().community_unblockFriendOK(strFriendNickname);
}

/// 친구 블럭을 취소하는데 실패했다.
void CTRNetEventHandler::community_unblockFriendFailed(const std::string & strFriendNickname)
{
	DBG_OUTPUT(60, "community_unblockFriendFailed");
	CTRMessengerMainUI::getInstance().community_unblockFriendFailed(strFriendNickname);
}

/// 친구를 삭제 표시하는데 성공했다.
void CTRNetEventHandler::community_deleteFriendOK(const std::string & strFriendNickname)
{
	DBG_OUTPUT(60, "community_deleteFriendOK");
	CTRMessengerMainUI::getInstance().community_deleteFriendOK(strFriendNickname);
}

/// 친구를 삭제 표시하는데 실패했다.
void CTRNetEventHandler::community_deleteFriendFailed(const std::string & strFriendNickname, eRemoveFriendFailed eFailedReason)
{
	DBG_OUTPUT(60, "community_deleteFriendFailed");
	CTRMessengerMainUI::getInstance().community_deleteFriendFailed(strFriendNickname, eFailedReason);
}

/// 친구를 삭제 표시 제거하는데 성공했다.
void CTRNetEventHandler::community_undeleteFriendOK(const std::string & strFriendNickname)
{
	DBG_OUTPUT(60, "community_undeleteFriendOK");
	CTRMessengerMainUI::getInstance().community_undeleteFriendOK(strFriendNickname);
}

/// 친구를 삭제 표시 제거하는데 실패했다.
void CTRNetEventHandler::community_undeleteFriendFailed(const std::string & strFriendNickname)
{
	DBG_OUTPUT(60, "community_undeleteFriendFailed");
	CTRMessengerMainUI::getInstance().community_undeleteFriendFailed(strFriendNickname);
}

/// 친구 등록 대기 중인 친구를 제거하는데 성공했다.
void CTRNetEventHandler::community_cancelAddFriendOK(const std::string & strNickname)
{
	DBG_OUTPUT(60, "community_cancelAddFriendOK");
	CTRMessengerMainUI::getInstance().community_cancelAddFriendOK(strNickname);
}

/// 친구 등록 대기 중인 친구를 제거하는데 실패했다.
void CTRNetEventHandler::community_cancelAddFriendFailed(const std::string & strNickname)
{
	DBG_OUTPUT(60, "community_cancelAddFriendFailed");
	CTRMessengerMainUI::getInstance().community_cancelAddFriendFailed(strNickname);
}

/// 그룹 operation 결과
void CTRNetEventHandler::community_onRecvGroupOperate(eCommunityGroupOperationType type,vCommunityGroupInfo& vecGroupInfo)
{
	switch(type)
	{
	case eCommunityGroupOperationType_GET:		
	case eCommunityGroupOperationType_DEL:
		CTRMessengerMainUI::getInstance().update();
		break;
	case eCommunityGroupOperationType_ADD:
	case eCommunityGroupOperationType_MOD:
		CTRMessengerMainUI::getInstance().update(true);
		break;
	}

	DBG_DEMO_OUTPUT("CTRNetEventHandler::community_onRecvGroupOperate type=[%d] size=[%d]", (int)type, (int)vecGroupInfo.size());
}

/// 그룹 operation 결과가 실패하였다
void CTRNetEventHandler::community_onRecvGroupOperateFailed(eCommunityGroupOperationType type, eCommunityGroupResult result, short groupNum)
{
	string strMsg;
	switch(result)
	{
	case eCommunityGroupResult_SUCCESS:
		CTRMessengerMainUI::getInstance().update();
		break;
	case eCommunityGroupResult_UNKNOWN:		// 알 수 없는 에러
		strMsg = _STR(FAILED_GROUP_RESULT_UNKNOWN);
		break;
	case eCommunityGroupResult_DB:			// DB 에러
		strMsg = _STR(FAILED_GROUP_RESULT_DB);
		break;
	case eCommunityGroupResult_NO_GROUP:	// update나 delete 할 그룹이 없다
		strMsg = _STR(FAILED_GROUP_RESULT_NO_GROUP);
		break;
	case eCommunityGroupResult_NO_DEFAULTGROUP:
		strMsg = _STR(FAILED_INVALID_GROUP_NAME);
		break;
	case eCommunityGroupResult_DUPLICATION:	// // 동일 그룹명으로 insert하거나 modify 했다
		strMsg = _STR(FAILED_DUPLICATION_GROUP_NAME);
		break;	
	}

	if(!strMsg.empty()) COkDialogEx::getInstance().showDialog(strMsg);
	DBG_OUTPUT("CTRNetEventHandler::community_onRecvGroupOperateFailed type=[%d], Msg=[%s] GroupNum=[%d]", (int)type, strMsg.c_str(), (int)groupNum);
}

/// 그룹 멤버 이동 결과
void CTRNetEventHandler::community_onRecvMoveGroupMember(eCommunityGroupResult result)
{
	string strMsg;
	switch(result)
	{
	case eCommunityGroupResult_SUCCESS:
		CTRMessengerMainUI::getInstance().update();
		break;
	case eCommunityGroupResult_UNKNOWN:		// 알 수 없는 에러
		strMsg = _STR(FAILED_GROUP_RESULT_UNKNOWN);
		break;
	case eCommunityGroupResult_DB:			// DB 에러
		strMsg = _STR(FAILED_GROUP_RESULT_DB);
		break;
	case eCommunityGroupResult_NO_GROUP:	// update나 delete 할 그룹이 없다
		strMsg = _STR(FAILED_GROUP_RESULT_NO_GROUP);
		break;
	case eCommunityGroupResult_NO_DEFAULTGROUP:
		strMsg = _STR(FAILED_INVALID_GROUP_NAME);
		break;
	}

	if(!strMsg.empty()) COkDialogEx::getInstance().showDialog(strMsg);
	DBG_OUTPUT("CTRNetEventHandler::community_onRecvMoveGroupMember result=[%d], Msg=[%s]", (int)result, strMsg.c_str());
}

/// 대화명 변경
void CTRNetEventHandler::community_onRecvOnlineIDSet(bool isSuccess, std::string strOnlineID)
{
	DBG_DEMO_OUTPUT("CTRNetEventHandler::community_onRecvOnlineIDSet Success=[%d], OnlineID=[%s]", (int)isSuccess, strOnlineID.c_str());

	if(isSuccess)
	{
		CTRMessengerMainUI::getInstance().updateOnlineIDSet(strOnlineID);
	}
}

/// 상대로부터 친구 리스트로부터 자신을 삭제라하는 통지를 받았다.
void CTRNetEventHandler::community_onRecvDeleteFriend(const std::string & strFromNickname)
{
	DBG_OUTPUT(60, "calledByCommunity_onRecvDeleteFriend");	

	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		string msg = format(_STR(FRIEND_BREAK_ALRAM), strFromNickname.c_str());
		COkDialogEx::getInstance().showDialog(msg);
	}
	else
	{
		UserAlarmInfo info;
		info.alarmMsg = eALARM_MSG_DELETE_FRIEND;
		info.strExt = strFromNickname;
		CTRUserAlarmManager::getInstacne().onSetUserAlarmInfo(info);
	}
}

/// 친구의 팜 정보가 변경되었다는 통지를 받았다. 
void CTRNetEventHandler::community_onRecvFarmInfoToFriend(const std::string& strFromNickname, const FarmShortInfo& info)
{
	DBG_OUTPUT(60, "community_onRecvFarmInfoToFriend");
	CTRMessengerMainUI::getInstance().community_onRecvFarmInfoToFriend(strFromNickname, info);
}

/// 친구의 팜 사용기간이 만료되었다는 통지를 받았다. 
void CTRNetEventHandler::community_onRecvFarmPeriodExpiredToFriend(const std::string& strFromNickname)
{
	
}

/// 친구의 팜 사용기간을 갱신했다는 통지를 받았다. 
void CTRNetEventHandler::community_onRecvFarmPeriodRenewalToFriend(const std::string& strFromNickname, const FarmShortInfo& info)
{
	
}


/// 누가 자기 방에 들어오라고 했다.
void CTRNetEventHandler::community_onRecvJoinMe(const std::string & strNickname, eRoomKind roomKind, int iRoomServerNum, unsigned int hRoom, const std::string & strPassword, const int iAttribute, const bool bRequireACK, const __int64 partyID)
{
	DBG_DEMO_OUTPUT(60, "community_onRecvJoinMe[%d]iRoomServerNum[%d]hRoom[%d]bRequireACK[%d]partyID[%ld]",(int)roomKind,(int)iRoomServerNum,(int)hRoom,bRequireACK,partyID);

	//! Open TV 시청중일때는 응답할 수 없다.
	if(CTRGameParkUI::getInstance().getMyUserState() == PARK_MYSTATE_IN_OPENTV)
	{
		CNetClientManager::getInstance().community_sendWatchingOpenTV(strNickname);
		return;
	}

	if(CTRFarmUI::getInstance().isActive() && CTRFarmUI::getInstance().getExperience())
	{
		if(bRequireACK) CNetClientManager::getInstance().community_cantJoinYou(strNickname, true);
		return;
	}

#ifdef _PERSONAL_CONNECTIONS
	if(CTRMessengerMainUI::getInstance().isVisiblePersonalConnection())
	{
		if(bRequireACK) CNetClientManager::getInstance().community_cantJoinYou(strNickname, true);
		return;
	}
#endif

#ifdef _ENCHANT_SYSTEM_
	if(ItemDetailView::CTRItemDetailViewManager::getInstance().isTrading())
	{
		if(bRequireACK) CNetClientManager::getInstance().community_cantJoinYou(strNickname, true);
		return;
	}
#endif

#ifdef _ARCHIVES_
	if (ARCHIVES::CTRArtifactDlg::getInstance().isVisible())
	{
		if (bRequireACK) CNetClientManager::getInstance().community_cantJoinYou(strNickname, true);
		return;
	}
#endif

	//if (CTREmblemUI::getInstance().isActive())
	//{
	//	CNetClientManager::getInstance().community_cantJoinYou(strNickname, true);
	//	return;
	//}

	//  런닝맨 / 대운동회 룸일 경우 친구 초대를거부한다.
	if( CTRTicketScrambleRoomUI::getInstance().isActive()
		|| CTRGameSportsRoomUI::getInstance().isActive() 
#ifdef _RUNNING_MAN2
		|| CTRRunningMan2RoomUI::getInstance().isActive() 
#endif		
		
#ifdef SMART_CHANNEL_SYSTEM		
		|| (m_pNetPlay->inRoom() && m_pNetPlay->getGameRoomKind() == eRoomKind_SMART_CHANNEL)
#endif

#ifdef _ASSAULT_RAID
		|| CTRAssaultRaidCrowdGameRoomUI::getInstance().isActive()
#endif

#ifdef _HORROR_PARK_CHANNEL
		|| CTRHorrorParkRoomUI::getInstance().isActive()
#endif

#ifdef _GENDER_WAR
		|| CTRGenderWarRoomUI::getInstance().isActive()
#endif

#ifdef _SNOW_QUEEN_CHANNEL
		|| (isSnowQueenTrainingMode(roomKind) && CTRSnowQueenTeamRoomUI::getInstance().isActive())
		|| (isSnowQueenBossEasyMode(roomKind) && CTRSnowQueenNormalRoomUI::getInstance().isActive())
		|| (isSnowQueenBossHardMode(roomKind) && CTRSnowQueenNormalRoomUI::getInstance().isActive())
		|| (isSnowQueenBossNewMode(roomKind) && CTRSnowQueenNormalRoomUI::getInstance().isActive())
		|| (isSnowQueenForzenCorpseMode(roomKind) && CTRSnowQueenCrowdRoomUI::getInstance().isActive())
#endif

#ifdef _OFFICIAL_COMPETITION_CHANNEL
		|| CTRRoyalRumbleCrowdRoomUI::getInstance().isActive()
		|| CTRFrozenCorpseCrowdRoomUI::getInstance().isActive()
		|| CTRHammerGameCrowdRoomUI::getInstance().isActive()
		|| CTRBattleSurvivalCrowdRoomUI::getInstance().isActive()
#endif
#ifdef _RAINBOW_LEAGUE
		|| RainbowLeague::CTRRainbowLeagueRoomUI::getInstance().isActive()
		|| RainbowLeague::CTRRainbowLeagueManager::getInstance().getGameState()
#endif
#ifdef _CHAMPIONS_CUP
		|| RainbowLeague::CTRChampionsCupRoomUI::getInstance().isActive()
#endif
		)
	{
		if(bRequireACK) CNetClientManager::getInstance().community_cantJoinYou(strNickname, true);
		return;
	}
// 	else if(!isNewbieOnlyChannel(roomKind) && CTRGuideManager::getInstance().isBeginnerUser())	// 2011.12 초보 유저가 다른 채널에서도 초대되도록 주석처리
// 	{
// 		//상대가 병아리 채널이 아니고, 내가 아직 초보가이드를 해야하는 상황이라면 초대를 거부한다.
// 		CNetClientManager::getInstance().community_cantJoinYou(strNickname, true);
// 		return;
// 	}
	else if (isGuildMatchChannel(roomKind))
	{
		if (CNetClientManager::getInstance().isObserver())
		{
			if (m_pNetPlay != NULL && !m_pNetPlay->inRoom())
			{
				CTRInviteDialog::getInstance().community_onRecvJoinMe(strNickname, roomKind, iRoomServerNum, hRoom, strPassword, iAttribute, bRequireACK, partyID);
			}
			return;
		}

		if (!CGamePartyID(partyID).isValid() || !CNetClientManager::getInstance().hasGuild())
		{
			if(bRequireACK) CNetClientManager::getInstance().community_cantJoinYou(strNickname, true);
			TRDBG_OUTPUT_ERROR("%s(line: %ld)PartyID_is_Invalid",__FUNCTION__,__LINE__,partyID);
			return;
		}
	}
	CTRUserInterface::getInstance().community_onRecvJoinMe(strNickname, roomKind, iRoomServerNum, hRoom, strPassword, iAttribute, bRequireACK, partyID);
}

/// 누군가를 초대했었는데 못 들어온다고 한다.
void CTRNetEventHandler::community_onRecvJoinMeFail(const std::string & strNickname, const bool bAutoReply,const int iAtrribute)
{
	DBG_OUTPUT(60, "community_onRecvJoinMeFail");
	CTRUserInterface::getInstance().community_onRecvJoinMeFail(strNickname, bAutoReply, iAtrribute);
}

/// 따가가리를 실패하였다.
void CTRNetEventHandler::community_onRecvFindGoFailed(const std::string & strNickname )
{
	DBG_OUTPUT(60, "community_onRecvFindGoFailed");
	CTRUserInterface::getInstance().community_onRecvFindGoFailed(strNickname);
}

/// 1대1 대화를 요청한다.
void CTRNetEventHandler::community_onRecvRequest1on1Chat( const std::string& strNickname )
{
	//! Open TV 시청중일때는 응답할 수 없다.
	if(CTRGameParkUI::getInstance().getMyUserState() == PARK_MYSTATE_IN_OPENTV)
	{
		CNetClientManager::getInstance().community_sendWatchingOpenTV(strNickname);
		return;
	}

	DBG_OUTPUT(60, "community_onRecvRequest1on1Chat");
	CTRGameParkUI::getInstance().community_onRecvRequest1on1Chat( strNickname );
	CTRFarmUI::getInstance().community_onRecvRequest1on1Chat( strNickname );
}

/// 1대1 대화를 수락상태를 돌려준다.
void CTRNetEventHandler::community_onRecvResponse1on1Chat(const std::string& strNickname, bool bOK)
{
	DBG_OUTPUT(60, "community_onRecvResponse1on1Chat");
	CTRGameParkUI::getInstance().community_onRecvResponse1on1Chat( strNickname, bOK );
	CTRFarmUI::getInstance().community_onRecvResponse1on1Chat( strNickname, bOK );	
	CTRGuildFarmUI::getInstance().community_onRecvResponse1on1Chat( strNickname, bOK );
}

/// 친구가 로그인 되었다.
void CTRNetEventHandler::community_onRecvFriendOnline(const std::string & strFriendNickname)
{
	DBG_OUTPUT(60, "community_onRecvFriendOnline");

	//친구일때만 체크 하는 부분 
	vector<FriendInfo> friendList = CNetClientManager::getInstance().getFriendList();
	bool bFriend = false;
	for(size_t i=0; i < friendList.size(); ++i)
	{
		if(friendList[i].m_strNickname == strFriendNickname)
		{
			if( !friendList[i].m_bBlocked &&
				!friendList[i].m_bDeleted)
			{
				bFriend = true;
			}
			break;
		}
	}

	if(CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_FRIEND_LOGIN_INFO)) && bFriend)
	{
		CTRUserInterface::getInstance().community_onRecvFriendOnline(strFriendNickname);
	}	
}

/// 가족이 로그인되었다.
void CTRNetEventHandler::community_onRecvFamilyOnline(const std::string & strNickname)
{
	DBG_OUTPUT(60, "community_onRecvFamilyOnline");

	//가족일때만 체크 하는 부분 
	vector< FamilyCommunityInfo > familyList = CNetClientManager::getInstance().getFamilyMember();
	bool bFamily = false;
	for(size_t i=0; i < familyList.size(); ++i)
	{
		if(familyList[i].m_strNickname == strNickname)
		{
			bFamily = true;
			break;
		}
	}

	if(CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_FRIEND_LOGIN_INFO)) && bFamily)
	{
		CTRUserInterface::getInstance().community_onRecvFamilyOnline(strNickname);
	}
}

/// 길드원이 로그인되었다.
void CTRNetEventHandler::community_onRecvGuildOnline(const std::string & strNickname)
{
	DBG_OUTPUT(60, "community_onRecvGuildOnline");

	//길드일때만 체크 하는 부분 
	vector< GuildCommunityInfo > guildList = CNetClientManager::getInstance().getGuildMember();
	bool bGuild = false;
	for(size_t i=0; i < guildList.size(); ++i)
	{
		if(guildList[i].m_strNickname == strNickname)
		{
			bGuild = true;
			break;
		}
	}

	if(!CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_GUILD_LOGIN_INFO)) && bGuild)
	{
		CTRUserInterface::getInstance().community_onRecvGuildOnline(strNickname);
	}
}

/// 친구가 로그오프되었다.
void CTRNetEventHandler::community_onRecvFriendOffline(const std::string & strFriendNickname)
{
	DBG_OUTPUT(60, "community_onRecvFriendOffline");

	//친구일때만 체크 하는 부분 
	vector<FriendInfo> friendList = CNetClientManager::getInstance().getFriendList();
	bool bFriend = false;
	for(size_t i=0; i < friendList.size(); ++i)
	{
		if(friendList[i].m_strNickname == strFriendNickname)
		{
			if( !friendList[i].m_bBlocked &&
				!friendList[i].m_bDeleted)
			{
				bFriend = true;
			}
			break;
		}
	}

	if(CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_FRIEND_LOGIN_INFO))  && bFriend)
	{
		CTRUserInterface::getInstance().community_onRecvFriendOffline(strFriendNickname);
	}
	CTRMessengerMainUI::getInstance().community_onRecvFriendOffline(strFriendNickname);
}

/// 가족이 로그오프되었다.
void CTRNetEventHandler::community_onRecvFamilyOffline(const std::string & strNickname)
{
	DBG_OUTPUT(60, "community_onRecvFamilyOffline");

	//가족일때만 체크 하는 부분 
	vector< FamilyCommunityInfo > familyList = CNetClientManager::getInstance().getFamilyMember();
	bool bFamily = false;
	for(size_t i=0; i < familyList.size(); ++i)
	{
		if(familyList[i].m_strNickname == strNickname)
		{
			bFamily = true;
			break;
		}
	}

	if(CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_FRIEND_LOGIN_INFO))  && bFamily)
	{
		CTRUserInterface::getInstance().community_onRecvFamilyOffline(strNickname);
	}
	CTRMessengerMainUI::getInstance().community_onRecvFamilyOffline(strNickname);
}

/// 길드원이 로그오프되었다.
void CTRNetEventHandler::community_onRecvGuildOffline(const std::string & strNickname)
{
	DBG_OUTPUT(60, "community_onRecvGuildOffline");

	//길드일때만 체크 하는 부분 
	vector< GuildCommunityInfo > guildList = CNetClientManager::getInstance().getGuildMember();
	bool bGuild = false;
	for(size_t i=0; i < guildList.size(); ++i)
	{
		if(guildList[i].m_strNickname == strNickname)
		{
			bGuild = true;
			break;
		}
	}

	if(!CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_GUILD_LOGIN_INFO))  && bGuild)
	{
		CTRUserInterface::getInstance().community_onRecvGuildOffline(strNickname);
	}
	CTRMessengerMainUI::getInstance().community_onRecvGuildOffline(strNickname);
}

/// 상대로부터 프로포즈 받았다.
void CTRNetEventHandler::community_onRecvCoupleProposeRequest(const std::string & strFromNickname, const std::string & strCoupleName, const std::string & strCoupleDesc, const int iJewelBoxNum, const bool bMeetingDependency)
{
	CTRCoupleSystem::getInstacne().community_onRecvCoupleProposeRequest(strFromNickname, strCoupleName, strCoupleDesc, iJewelBoxNum, bMeetingDependency);
}

/// 프로포즈에 대한 승인여부를 받았다.
void CTRNetEventHandler::community_onRecvCoupleProposeResponse(const std::string & strFromNickname, const bool bOK, const eCoupleProposeReject eReason, const int iCoupleNum, const int iCoupleRingNum)
{
	CTRCoupleSystem::getInstacne().community_onRecvCoupleProposeResponse(strFromNickname, bOK, eReason, iCoupleNum, iCoupleRingNum);	
}

/// 상대로부터 커플을 끊겠다는 통지를 받았다.
void CTRNetEventHandler::community_onRecvCoupleSayGoodBye(const std::string & strFromNickname)
{
	const int & iOriCoupleRingNum = CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.iCoupleRingNum;
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvCoupleChangeCoupleRing(iOriCoupleRingNum);
#endif
	CTRMyroomDlg::getInstance().onRecvCoupleChangeCoupleRing(iOriCoupleRingNum);
	CTRShopDlg::getInstance().onRecvCoupleChangeCoupleRing(iOriCoupleRingNum);

	CTRCoupleSystem::getInstacne().community_onRecvCoupleSayGoodBye(strFromNickname);
}

/// 상대로부터 커플링을 변경했다 통지를 받았다.
void CTRNetEventHandler::community_onRecvCoupleRingChanged(const std::string & strFromNickname, const int iCoupleRingNum)
{
	const int & iOriCoupleRingNum = CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.iCoupleRingNum;
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvCoupleChangeCoupleRing(iOriCoupleRingNum);
#endif
	CTRMyroomDlg::getInstance().onRecvCoupleChangeCoupleRing(iOriCoupleRingNum);
	CTRShopDlg::getInstance().onRecvCoupleChangeCoupleRing(iOriCoupleRingNum);
	CTRCoupleSystem::getInstacne().community_onRecvCoupleRingChanged(strFromNickname, iCoupleRingNum);
}

/// 상대로부터 커플명을 변경했다 통지를 받았다.
void CTRNetEventHandler::community_onRecvCoupleNameChanged(const std::string & strFromNickname, const std::string & strCoupleName)
{
	CTRCoupleSystem::getInstacne().community_onRecvCoupleNameChanged(strFromNickname, strCoupleName);
}

/// 상대로부터 커플소개가 변경했다 통지를 받았다.
void CTRNetEventHandler::community_onRecvCoupleDescModify(const std::string & strFromNickname)
{
	CTRCoupleSystem::getInstacne().community_onRecvCoupleDescModify(strFromNickname);
}

/// 상대로부터 이혼 소송(동의를 구하기 위한)을 했다는 통지를 받았다.
void CTRNetEventHandler::community_onRecvWeddingSuitForDivorce(const std::string & strFromNickname, const eWeddingDivorceType eDivorceType)
{
	DBG_OUTPUT("CTRNetEventHandler::community_onRecvWeddingSuitForDivorce...");
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTWeddingDivorceRecvYesNoDialog::getInstance().showDialog(strFromNickname, eDivorceType);
	}
	else
	{
		UserAlarmInfo info;
		info.alarmMsg = eALARM_MSG_WEDDING_SUIT_FOR_DIVORCE;
		info.strExt = strFromNickname;
		info.iExt1 = (int)eDivorceType;
		CTRUserAlarmManager::getInstacne().onSetUserAlarmInfo(info);
	}
	
}

/// 상대로부터 이혼에 동의하지 않는다는 통지를 받았다.
void CTRNetEventHandler::community_onRecvWeddingDisagreeForDivorce(const std::string & strFromNickname, eWeddingDisagreeDivorceType eDisagreeType)
{
	DBG_OUTPUT("CTRNetEventHandler::community_onRecvWeddingDisagreeForDivorce...");
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		switch(eDisagreeType)
		{
		case eWeddingDisagreeDivorceType_SayNo:
			COkDialogEx::getInstance().showDialog(_STR(WEDDING_MSG_FAILED_DIVORCE_SEND_NO));
			break;
		case eWeddingDisagreeDivorceType_Disconnect:
			COkDialogEx::getInstance().showDialog(_STR(WEDDING_MSG_FAILED_DIVORCE_OFFLINE));
		    break;
		}
		
	}
	else
	{
		UserAlarmInfo info;
		info.alarmMsg = eALARM_MSG_WEDDING_DISAGREE_WITH_DIVORCE;
		info.strExt = strFromNickname;
		info.iExt1 = (int)eDisagreeType;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(info);

	}
}

/// 상대로부터 이혼했다는 통지를 받았다.
void CTRNetEventHandler::community_onRecvWeddingDivorced(const std::string & strFromNickname, const eWeddingDivorceType eDivorceType, const bool bEnforce)
{
	DBG_OUTPUT("CTRNetEventHandler::community_onRecvWeddingDivorced...");
	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_WEDDING_DIVORCE_ITEM);

	bool bVisible = CTRUserBookDlg::getInstance().isFamilyDlgVisible();

	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		string guiFilename;

		switch(eDivorceType)
		{
		case eWeddingDivorceType_MaintainRelation:
			if(bEnforce) guiFilename = "gui\\Family\\ItemBreak_Wed.gui";
			else guiFilename = "gui\\Family\\Break_Wed.gui";
			break;
		case eWeddingDivorceType_BreakRelation:
		case eWeddingDivorceType_ForceBreakRelation:
			if(bEnforce) guiFilename = "gui\\Family\\ItemBreak_All.gui";
			else guiFilename = "gui\\Family\\Break_All.gui";
			CTRGameParkUI::getInstance().onCoupleInfoChange();
			break;
		}

		COkDialogEx::getInstance().showDialog(_STR(WEDDING_MSG_FAILED_DIVORCE_OK), guiFilename, -1.f, false);
	}
	else
	{
		UserAlarmInfo info;
		info.alarmMsg = eALARM_MSG_WEDDING_DIVORCE;
		info.strExt = bEnforce ? strFromNickname : CNetClientManager::getInstance().getMyNickname();
		info.iExt1 = (int)eDivorceType;
		info.iExt2 = (bool)bEnforce;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(info);

		bVisible = false;
	}

	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvCoupleChangeCoupleRing(CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
#endif
	CTRMyroomDlg::getInstance().onRecvCoupleChangeCoupleRing(CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
	CTRShopDlg::getInstance().onRecvCoupleChangeCoupleRing(CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
	CNetClientManager::getInstance().requestMyCharacter();
	CNetClientManager::getInstance().requestFamilyInfo(CNetClientManager::getInstance().getMyNickname(), !bVisible);
	CKeepFarmItemList::getInstance().update(false);
}

/// 상대방에게 커플 전용 아이템을 구매했음을 통지 받았다.
void CTRNetEventHandler::community_onRecvBuyCoupleItem(const std::string & strFromNickname)
{

}

/// 상대에게 가족 맺기 요청을 받았다.
void CTRNetEventHandler::community_onRecvFamilyPropose(const std::string& strFromNickname, bool bParents)
{
	DBG_OUTPUT("CTRNetEventHandler::community_onRecvFamilyPropose...");
	if(CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRUserBookDlg::getInstance().community_onRecvFamilyPropose(strFromNickname, bParents);
	}
	else
	{
		CNetClientManager::getInstance().community_responseFamilyPropose(strFromNickname, false, eFamilyProposeReject_CANNOT_RESPONSE, bParents);
	}
}

/// 상대에게 가족 맺기 요청에 대한 승인여부 통지를 받았다.
void CTRNetEventHandler::community_onRecvFamilyProposeResponse(const std::string& strFromNickname, bool bSummit, eFamilyProposeReject eReason, bool bParents)
{
	DBG_OUTPUT("CTRNetEventHandler::community_onRecvFamilyProposeResponse...");
	if(bSummit)
	{
		_ASSERT(true);
		DBG_OUTPUT("CTRNetEventHandler::community_onRecvFamilyProposeResponse...bSummit = true");
	}
	else
	{
		if(CTRNetPlayManager::getInstance().isGameStateNoGame())
		{
			switch(eReason)
			{
			case eFamilyProposeReject_NONE:
				COkDialogEx::getInstance().showDialog(_STR(FAMILY_MSG_FAILED_ADD_FAMILY));
				break;
			case eFamilyProposeReject_DISAGREE:
				COkDialogEx::getInstance().showDialog("", "gui\\Family\\FamilyFailed.gui", -1.f, false);
				break;
			case eFamilyProposeReject_LOGOUT:
				COkDialogEx::getInstance().showDialog(_STR(FAMILY_MSG_FAMILY_PROPOSE_FAILED_LOGOUT));
				break;
			case eFamilyProposeReject_CANNOT_RESPONSE:
				COkDialogEx::getInstance().showDialog(_STR(ERROR_CAN_NOT_RESPONCE));
				break;
			case eFamilyProposeReject_MY_COUPLE_EXIST_TARGET_FAMILY:
				//!< 내 커플이 상대방의 가족이다.
				COkDialogEx::getInstance().showDialog(_STR(FAMILY_MSG_FAILED_IN_FAMILY_3));
				break;
				
			}
		}
	}
	
}

/// 상대에게 가족 맺어짐을 통보 받았다.
void CTRNetEventHandler::community_onRecvFamilyMakeNotify(const std::string& strFromNickName, bool bParents)
{
	DBG_OUTPUT("CTRNetEventHandler::community_onRecvFamilyMakeNotify...");
	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_FAMILY_PROPOSE_ITEM);
	if(CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRUserBookDlg::getInstance().community_onRecvFamilyMakeNotify(strFromNickName, bParents);
	}
	else
	{
		UserAlarmInfo info;
		info.alarmMsg = eALARM_MSG_FAMILY_LINKING;
		info.strExt = strFromNickName;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(info);

	}
}

/// 상대로 부터 가족 끊기 통보를 받았다.
void CTRNetEventHandler::community_onRecvFamilyBreakNotify(const std::string& strFromNickName)
{
	DBG_OUTPUT("CTRNetEventHandler::community_onRecvFamilyBreakNotify...");
	if(CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CTRUserBookDlg::getInstance().community_onRecvFamilyBreakNotify(strFromNickName);
	}
	else
	{
		UserAlarmInfo info;
		info.alarmMsg = eALARM_MSG_FAMILY_DISSOLVE;
		info.strExt = strFromNickName;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(info);
	}
}


/// 상대에게 삐에로 올림픽 같은팀에 가입하자고 요청을 받았다.
void CTRNetEventHandler::community_onRecvPieroOlympicJoinPartyPropose(const std::string& strFromNickname, const ePieroOlympicPartyType ePartyType)
{
	DBG_OUTPUT("%s strFromNickname[%s], PartyType[%d]", __FUNCTION__, strFromNickname, ePartyType);
	CTRGameParkUI::getInstance().community_onRecvPieroOlympicJoinPartyPropose(strFromNickname, ePartyType);
}

/// 상대로부터 오픈 TV를 시청중이라는 통지를 받았다.
void CTRNetEventHandler::community_onRecvWatchingOpenTV()
{
	CTRShortTimeMessage::getInstance().showMessage(_STR(MSG_OPEN_TV_SEE), 1.5f);
}

/// 상대로부터 로그인을 했는지 확인 요청을 받았다.
void CTRNetEventHandler::community_onRecvRequestLogin(const std::string& strFromNickname)
{
	DBG_DEMO_OUTPUT("CTRNetEventHandler::community_onRecvRequestLogin");

	const bool bWhisper = CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_WHISPER_CONSENT));
	CNetClientManager::getInstance().community_responseLogin(strFromNickname, bWhisper);
}

/// 상대로부터 로그인을 했다는 응답을 받았다.
void CTRNetEventHandler::community_onRecvResponseLogin(const std::string& strFromNickname, bool isBlocking)
{
	DBG_DEMO_OUTPUT("CTRNetEventHandler::community_onRecvResponseLogin");
	CTRUserInterface::getInstance().community_onRecvResponseLogin(strFromNickname, isBlocking);
}

/// 길드가 레벨업 되었음을 길드 마스터로 부터 통지 받았다.
void CTRNetEventHandler::community_onRecvGuildLevelUp(short iGuildLevel)
{
	string guildName = CNetClientManager::getInstance().getMyGuildName();

	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		string message = format(_STR(INFORMATION_GUILD_LEVEL_UP), guildName.c_str(), iGuildLevel);
		string strOption;
		CTREssenGuild & guildLevelingInfo = CKeepGuildFarmItemList::getInstance().m_guildLevelingInfo;
		guildLevelingInfo.getDescByLevel(iGuildLevel,strOption);

		CTRGuildDlg::getInstance().onRecvGuildLevelUp(iGuildLevel);

		CDetailMessageOKDialog::getInstance().showDialog(message,strOption, "gui\\Guild\\GuildLevelUp.gui");
	}
	else
	{
		UserAlarmInfo info;
		info.alarmMsg = eALARM_MSG_GUILD_LEVELUP;
		info.strExt = guildName;
		info.iExt1 = iGuildLevel;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(info);
	}
	if(CTRGuildDlg::getInstance().isVisible())	CTRGuildDlg::getInstance().showDialog();
	CTRGuildFarmUI::getInstance().onRecvGuildLevelUp(iGuildLevel);
	CTRFarmLobbyUIDlg::getInstance().updateGuildFarmInfo();
}

/// 길드 맴버가 탈퇴 되었음을 통지 받았다.
void CTRNetEventHandler::community_onRecvGuildMemberLeave(const std::string& strNickName)
{
	CTRMessengerMainUI::getInstance().community_onRecvGuildMemberLeave(strNickName);
	CTRGuildDlg::getInstance().community_onRecvGuildMemberLeave(strNickName);

}

/// 길드원들의 기여도 포인트를 받았다. 
void CTRNetEventHandler::community_guildMemberContributeRefresh()
{
	CTRGuildDlg::getInstance().community_guildMemberContributeRefresh();
}

/// 길드 가입 추천을 받았다.
void CTRNetEventHandler::community_onRecvGuildProposeRecommend(const std::string& strFromNickname, const GuildInfo& guildInfo, const bool & bInternJoin )
{
	if(!CTRGuildJoinDlg::getInstance().isVisible() && !CInviteGuildJoinYesNoDlg::getInstance().isVisible() && CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		CInviteGuildJoinYesNoDlg::getInstance().showDialog(strFromNickname, guildInfo, bInternJoin );
	}
}

/// 길드 마스터 이양을 추천받았다.
void CTRNetEventHandler::community_onRecvGuildConveyMasterPropose(const std::string& strFromNickname)
{
}

///< 길드원에게 길드 마스터를 이양받을지 물어본다.
void CTRNetEventHandler::community_onRecvGuildConveyMasterProposeResult(const std::string& strFromNickname, bool bAccept)
{
}


/// 친구 리스트가 업데이트 되었다.
void CTRNetEventHandler::onFriendListUpdate()
{
	DBG_OUTPUT(60, "onFriendListUpdate");
	CTRMessengerMainUI::getInstance().onFriendListUpdate();
	CTRPlayerPopup::getInstance().onFriendListUpdate();

	//! 도전 미션이 있는지 확인한다.
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_PARENT);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_BROTHER);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_CHILD);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HOW_MANY_FRIEND);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();

	DBG_DEMO_OUTPUT("%s - friend list : %d", __FUNCTION__, (int)CNetClientManager::getInstance().getFriendList().size());
}

#ifdef _PERSONAL_CONNECTIONS

// 인맥시스템 등록 여부 
void CTRNetEventHandler::community_onRecvPersonalConnectionsIsRegisterOK(const bool bRegister, const time_type infoEditDate, const __int64 authNum)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsIsRegisterOK(bRegister, infoEditDate, authNum);
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsIsRegisterFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsIsRegisterFailed(dwResult);
}

// 인맥시스템 등록 요청 
void CTRNetEventHandler::community_onRecvPersonalConnectionsRegisterOK(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsRegisterOK(dwResult);
}

// 인맥시스템 나의정보 설정 
void CTRNetEventHandler::community_onRecvPersonalConnectionsSetInfoOK()
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsSetInfoOK();
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsSetInfoFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsSetInfoFailed(dwResult);
}

// 인맥시스템 나의정보 요청 
void CTRNetEventHandler::community_onRecvPersonalConnectionsGetInfoOK(const PersonalConnectionsInfo & infoList)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsGetInfoOK(infoList);
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsGetInfoFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsGetInfoFailed(dwResult);
}

// 인맥시스템 검색횟수 요청 
void CTRNetEventHandler::community_onRecvPersonalConnectionsCountInfoOK(const ePersonalConnectionsKind eKind, const int iCount)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsCountInfoOK(eKind, iCount);
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsCountInfoFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsCountInfoFailed(dwResult);
}

// 인맥시스템 이전 검색 요청 
void CTRNetEventHandler::community_onRecvPersonalConnectionsBeforeSearchOK(const ePersonalConnectionsKind eKind, const std::map<std::string, PersonalConnectionsSearch> & resultList)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsBeforeSearchOK(eKind, resultList);
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsBeforeSearchFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsBeforeSearchFailed(dwResult);
}

// 인맥시스템 검색 요청 
void CTRNetEventHandler::community_onRecvPersonalConnectionsSearchOK(const ePersonalConnectionsKind eKind, const std::map<std::string, PersonalConnectionsSearch> & resultList)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsSearchOK(eKind, resultList);
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsSearchFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsSearchFailed(dwResult);
}

// 인맥시스템 이상형월드컵 출전횟수/우승횟수 요청 
void CTRNetEventHandler::community_onRecvPersonalConnectionsIdealTypeCountOK(const int iEntryCount, const int iWinCount)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsIdealTypeCountOK(iEntryCount, iWinCount);
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsIdealTypeCountFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsIdealTypeCountFailed(dwResult);
}

// 인맥시스템 오늘의 친구 설정 
void CTRNetEventHandler::community_onRecvPersonalConnectionsTodayFriendOK(const bool bRegister)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsTodayFriendOK(bRegister);
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsTodayFriendFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsTodayFriendFailed(dwResult);
}

// 인맥시스템 데이트, 이상형 설정 
void CTRNetEventHandler::community_onRecvPersonalConnectionsSelectUserOK(const ePersonalConnectionsKind eKind)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsSelectUserOK(eKind);
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsSelectUserFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsSelectUserFailed(dwResult);
}

// 인맥시스템 데이트 슬롯 오픈 
void CTRNetEventHandler::community_onRecvPersonalConnectionsOpenSlotOK(const ePersonalConnectionsKind eKind)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsOpenSlotOK(eKind);
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsOpenSlotFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsOpenSlotFailed(dwResult);
}

// 인맥시스템 프로필 요청 
void CTRNetEventHandler::community_onRecvPersonalConnectionsProfileOK(const ePersonalConnectionsKind eKind, const PersonalConnectionsProfile & infoList)
{
	if (eKind == ePersonalConnectionsKind_PROFILE_TALESBOOK)
	{
		CTRUserBookDlg::getInstance().onRecvSetUserProfile(infoList);
	}
	else
	{
		CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsProfileOK(eKind, infoList);
	}
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsProfileDetailOK(const PersonalConnectionsProfileDetail & infoList)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsProfileDetailOK(infoList);	
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsProfileFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsProfileFailed(dwResult);
}

// 인맥시스템 호감주기 
void CTRNetEventHandler::community_onRecvPersonalConnectionsSetPointOK(const std::string & strTargetNickName, const std::string & strTargetAnotherName, const int iPoint)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsSetPointOK(strTargetNickName, strTargetAnotherName, iPoint);

	CTRMessengerMainUI::getInstance().community_onRecvPersonalConnectionsSendExpressedLikeableOK(strTargetAnotherName, iPoint);

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_GUI_EVENT, static_cast<int>(eMissionConditionGUIEventType_GIFT_HEART));
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

void CTRNetEventHandler::community_onRecvPersonalConnectionsSetPointFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsSetPointFailed(dwResult);
}

// 인맥시스템 지난 내역보기 요청 성공 
void CTRNetEventHandler::community_onRecvPersonalConnectionsHistoryOK(const ePersonalConnectionsKind eKind, unsigned short numPage, 
																	  unsigned short totalCount, const std::map <std::string, PersonalConnectionsSearch> & historyList)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsHistoryOK(eKind, numPage, totalCount, historyList);
}

// 인맥시스템 지난 내역보기 요청 실패 
void CTRNetEventHandler::community_onRecvPersonalConnectionsHistoryFailed(ePersonalConnectionsResult dwResult)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnectionsHistoryFailed(dwResult);
}

/// 인맥시스템 상대방으로부터 호감을 받았다.
void CTRNetEventHandler::community_onRecvPersonalConnectionsSendPointNotify(const std::string& strFromNickName, const std::string& strAnotherName, const int iPoint)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->SetPoint(iPoint);
	CTRMessengerMainUI::getInstance().community_onRecvPersonalConnectionsSendPointNotify(strFromNickName, strAnotherName, iPoint);
}

/// 인맥시스템 전용 1대1 대화를 요청한다.
void CTRNetEventHandler::community_onRecvPersonalConnectionsRequest1on1Chat(const std::string& strNickName)
{
	if(CTRGameParkUI::getInstance().getMyUserState() == PARK_MYSTATE_IN_OPENTV)
	{
		CNetClientManager::getInstance().community_sendWatchingOpenTV(strNickName);
	}
	else
	{
		DBG_OUTPUT(80, "PersonalConnectionsRequest1on1Chat");

//		bool bOk = CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_MEETING_CHAT));

		CNetClientManager::getInstance().community_personalConnectionsResponse1on1Chat(strNickName, true);
	}
}

/// 인맥시스템 전용 1대1 대화상태를 알려준다.
void CTRNetEventHandler::community_onRecvPersonalConnectionsResponse1on1Chat(const std::string& strNickName, bool bOK)
{
	if(bOK == true)
	{
		CTRMessengerMainUI::getInstance().openChattingDialog(strNickName, eChatting_Type_MEETING_TALK);
	}
	else
	{
		COkDialogEx::getInstance().showDialog(format(_STR(MSG_MEETINGCHAT_REFUSE), strNickName.c_str()), "gui\\ok.gui", -2.1f);
	}
}

/// 인맥시스템 상대방으로부터 전용 대화 메세지를 받았다.
void CTRNetEventHandler::community_onRecvPersonalConnectionsMsg(const std::string & strFromNickName, const std::string & strFromAnotherName, const std::string & strMsg)
{
	std::string strConvertMsg;
	cutInvalidCharacter(strMsg, strConvertMsg, "([\n\r])");

	bool bSendMsgAck = true;
	eMessageResult messageResult = eMessageResult_OK;

	const FriendInfo * pInfo = CNetClientManager::getInstance().getFriendInfo(strFromNickName);
	if(pInfo && pInfo->m_bBlocked)
	{
		bSendMsgAck = false;
		messageResult = eMessageResult_BLOCKED;
	}

	if(bSendMsgAck)
	{
		if(CTRNetPlayManager::getInstance().isGameStateNoGame() || !CGameManager::getInstance().isGameModeNetworkPlay())
		{
			if(CTRGameParkUI::getInstance().getMyUserState() == PARK_MYSTATE_IN_OPENTV)
			{
				CTRGameParkUI::getInstance().onRecvWhisperMessage(strFromNickName, strConvertMsg);
				CTRMessengerMainUI::getInstance().community_onRecvMsg(strFromNickName, strFromAnotherName, strConvertMsg, eChatting_Type_MEETING_TALK);		// OpenTV 채팅 때도 메신저에 남겨둔다.
			}
			else
			{
				CTRMessengerMainUI::getInstance().community_onRecvMsg(strFromNickName, strFromAnotherName, strConvertMsg, eChatting_Type_MEETING_TALK);
			}
		}
		else
		{
			CChatItemProcessor::getInstance().community_onRecvMsg(strFromNickName, strConvertMsg);
			CTRMessengerMainUI::getInstance().community_onRecvMsg(strFromNickName, strFromAnotherName, strConvertMsg, eChatting_Type_MEETING_TALK);		// 게임 중이고, 네트워크 상태라면...메신저 채팅창에도 남긴다.
		}

		CTRChattingManager::getInstance().saveNickname(strFromNickName);
	}

	CNetClientManager::getInstance().community_personalConnectionsSendMsgAck(strFromNickName, strConvertMsg, messageResult);
}

/// 인맥시스템 메세지에 대한 응답을 받았다.
void CTRNetEventHandler::community_onRecvPersonalConnectionsMsgAck(const std::string& strNickName, const std::string& strMsg, eMessageResult messageResult)
{
	if(!CTRNetPlayManager::getInstance().isGameStateNoGame() && CGameManager::getInstance().isGameModeNetworkPlay())
	{
		CChatItemProcessor::getInstance().community_onRecvMsgAck(strNickName, strMsg, messageResult);
	}

	CTRMessengerMainUI::getInstance().community_onRecvMsgAck(strNickName, strMsg, messageResult, eChatting_Type_MEETING_TALK);
}

/// 인맥시스템 상대가 나의 정보를 요청했다.
void CTRNetEventHandler::community_onRecvPersonalConnections1on1nfoRequest(const std::string& strNickName)
{

}

/// 인맥시스템 상대방 정보를 받았다.
void CTRNetEventHandler::community_onRecvPersonalConnections1on1nfoResponse(const std::string& strNickName, PersonalConnectionsSearch & info)
{
	CTRNetPlayManager::getInstance().getPersonalConnectionsManager()->community_onRecvPersonalConnections1on1nfoResponse(strNickName, info);
	CTRMessengerMainUI::getInstance().community_onRecvPersonalConnections1on1nfoResponse(strNickName, info);
}
#endif


void CTRNetEventHandler::community_onRecvFarmNameTagRequest(const std::string & strFromNickname, const std::string & strNameTag)
{
	CTRFarmUI::getInstance().community_onRecvFarmNameTagRequest(strFromNickname, strNameTag);
}

void CTRNetEventHandler::community_onRecvFarmNameTagResponse(const std::string & strFromNickname, const std::string & strNameTag, const bool bOK, const eFarmNameTagResult eResult)
{
	CTRFarmUI::getInstance().community_onRecvFarmNameTagResponse(strFromNickname, strNameTag, bOK, eResult);
}


#ifdef _PARTY_SYSTEM
/// 파티 초대에 대한 거절
void CTRNetEventHandler::community_onRecvPartyInviteRefuse(const std::string& strNickName)
{
	CTRMessengerMainUI::getInstance().community_onRecvPartyInviteRefuse(strNickName);
}

/// 파티 지원요청에 대한 알림
void CTRNetEventHandler::community_onRecvPartySupportBoardJoin(const std::string& strNickName)
{
	CTRMessengerMainUI::getInstance().community_onRecvPartySupportBoardJoin(strNickName);
}

#endif

/// 현재 초대받을 수 있는 상태인가.
bool CTRNetEventHandler::canInvited() const
{
	return CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_INVITE_CONSENT));
}

/// 현재 1대1 대화를 할수 있는 상태인가?
e1on1ChatOption CTRNetEventHandler::can1on1ChatInvited() const
{
	e1on1ChatOption eOption = e1on1ChatOption_ALLOW;

	if( CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_1ON1CHAT)))
	{
		eOption = e1on1ChatOption_ALLOW;
	}
	else
	{
		if(CTRGameOptionInfo::instance.isAttrBitsTrue(OPTION_BIT64::get(OPTION_ATTR_1ON1CHAT_FRIEND)))
		{
			eOption = e1on1ChatOption_FRIEND;
		}
		else
		{
			eOption = e1on1ChatOption_REJECTION;
		}
	}
	return eOption;
}


void CTRNetEventHandler::onRecvRoomUserFuncItemTimeOut(const BYTE numGameIndex, int iItemNum)
{
	TRDBG_OUTPUT_SYSTEM("onRecvRoomUserFuncItemTimeOut(player=%d, cpk=%d,%d,%d, desc#=%d)", numGameIndex, iItemNum);

	// 타임아웃되거나 존재하지 않은 복장아이템을 입고 있는지
	// 체크해서 벗긴다.

	if (!CGameManager::getInstance().isActive())
	{
		// 게임중(결과화면포함)엔 무시.
		m_pNetPlay->clearInvalidAvatarItems(true);
	}
}

void CTRNetEventHandler::onRecvRoomUserFuncItemTimeOut(const BYTE numGameIndex, const CActiveItems activeItems)
{
	for (const auto& item : activeItems.getVector())
	{
		TRDBG_OUTPUT_SYSTEM("onRecvRoomUserFuncItemTimeOut(player=%d, itemnum=%d)", numGameIndex, item.m_iItemDescNum);
	}

	if (!CGameManager::getInstance().isActive())
	{
		// 게임중(결과화면포함)엔 무시.
		m_pNetPlay->clearInvalidAvatarItems(true);
	}
}

/// 이 유저의 버프가 다 되었다.
void CTRNetEventHandler::onRecvRoomUserBuffItemTimeOut(const BYTE numGameIndex, int iItemNum)
{

}

#pragma warning (disable:4063)
/// 서버와의 접속이 끊어졌다.
void CTRNetEventHandler::onRecvDisconnectFromServer(eServerResult eResult)
{
	switch(eResult)
	{
	case eServer_DISCONNECT_FROM_SERVER_ACK:
		{
			CTRFatalErrorUI::showScreen(_STR(ERR_DISCONNECTED_FROM_SERVER), _STR(ERR_DISCONNECTED_FROM_SERVER_DESC), true);
		}
		break;
	case eServerResult_DUPLICATE_LOGIN_OHTER_USER_TRY:
		{
			CTRFatalErrorUI::showScreen(_STR(ERR_DISCONNECTED_FROM_SERVER), _STR(ERR_DUPLICATE_USER_ID_OTHER_PLACE), true);
		}
		break;
	case eServerResult_XTRAP_FAILED_ACK:
		{
			CTRFatalErrorUI::showScreen(_STR(ERR_DISCONNECTED_FROM_SERVER), _STR(HS_ERR_START_ENGINE_FAILED), true);
		}
		break;
	case eServerResult_XTRAP_FAILED_DETECT_ACK:
		{
			CTRFatalErrorUI::showScreen(_STR(ERR_DISCONNECTED_FROM_SERVER), format("%s (by XTRAP)", _STR(ERR_HACKING_DETECTED)), true);
		}
		break;
	case eServerResult_XIGNCODE_FAILED_DETECT_ACK:
		{
			CTRFatalErrorUI::showScreen(_STR(ERR_DISCONNECTED_FROM_SERVER), format("%s (by XIGNCODE)", _STR(ERR_HACKING_DETECTED)), true);
		}
		break;
	}
}
#pragma warning (default:4063)


/// 현재 방의 우리 팀에게 보내는 메시지를 받았다.
void CTRNetEventHandler::onRecvForwardToMyTeamUser(const CPacketChunk & v)
{

}

/// 블로킹 메시지를 받았다는 응답이 왔다.
void CTRNetEventHandler::onRecvBlockingResult(eBlockReason reason)
{
	if(reason == eBlockReason_BAD_NUMBER_FOR_PREVENT_ABUSING)
	{
		if(m_pNetPlay != NULL)
		{
			m_pNetPlay->onShowAbusingPrevent(false);
		}

		CTRFatalErrorUI::showScreen(_STR(ERR_DISCONNECTED_FROM_SERVER), _STR(ERR_BAD_NUMBER_FOR_PREVENT_ABUSING), true);
	}
	else if(reason == eBlockReason_CHANGE_PACKAGE_FILE)
	{
		if(m_pNetPlay != NULL) m_pNetPlay->onShowAbusingPrevent(false);

		CTRFatalErrorUI::showScreen(_STR(PROGRAM_TERMINATE), _STR(ERR_INVALID_PACKAGE_FILE), true);
	}
	else
	{
		DBG_OUTPUT("CTRNetEventHandler::onRecvBlockingResult(%d)", reason);
		//CTRFatalErrorUI::showScreenHackingDetected();
		//CFindCracker::getInstance().showFindCrackMessage();
		CDelayFoundHackMessage::getInstance().found();
	}	
}

/// 상점에서 대기 중인 선물을 받았음.
void CTRNetEventHandler::onRecvAcceptGiftOK(std::vector<int> vecGiftNum)
{
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvAcceptGiftOK(vecGiftNum);
#endif
	CTRMyRoomGiftDialog::getInstance().onRecvAcceptGiftOK(vecGiftNum);

	for (size_t i = 0; i < vecGiftNum.size(); ++i)
	{
		int iItemDescNum = vecGiftNum.at(i);
		const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getItemInfo(iItemDescNum);
		if (pItemInfo != NULL)
		{
			const CItemAttr & itemAttr = CItemAttrTable::getInstance().getItemAttrFromItemDescNum(iItemDescNum);
			const float fLucky = itemAttr.m_attr[eItemAttr_Lucky];
			if (fLucky != 0.f)
			{
				CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_LUCKY_ITEM_GIFT_GIVE, iItemDescNum);
				CMissionMsgDispatcher::getInstance().checkCompleteCondition();
			}
			else
			{
				CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_ITEM_GIFT_RECEIVE, iItemDescNum);
				CMissionMsgDispatcher::getInstance().checkCompleteCondition();
			}
			//! 도전 미션이 있는지 확인한다.
			//CTRGameMissionConditionManager::getInstance().checkMissionProgress(eMISSION_PROGRESS_CHECK_ITEM_ACQUISITION);
		}
	}	
}

/// 상점에서 대기 중인 선물을 받는데 실패
void CTRNetEventHandler::onRecvAcceptGiftFailed(const eGiftAcceptFailedReason failedReason)
{
	CTRMyRoomGiftDialog::getInstance().onRecvAcceptGiftFailed(failedReason);
}

/// 받은 선물 리스트를 받았다.
void CTRNetEventHandler::onRecvAcceptWaitGiftList(const unsigned short numPage,const unsigned short ItemCountPerPage, const std::vector < AcceptWaitItem > & v,int iTotalCount)
{
	CTRMyRoomGiftDialog::getInstance().onRecvAcceptWaitGiftList(numPage, ItemCountPerPage, v, iTotalCount);
}

/// 받은 선물 리스트를 받는데 실패했다.
void CTRNetEventHandler::onRecvAcceptWaitGiftListFailed()
{
	CTRMyRoomGiftDialog::getInstance().onRecvAcceptWaitGiftListFailed();
}

//////////////////////////////////////////////////////////////////////////

/// 닉네임 검색 성공
void CTRNetEventHandler::onRecvSearchNickNameOK(const std::string & strSearchNickname)
{
	CTRMessengerMainUI::getInstance().onRecvSearchNickNameOK(strSearchNickname);
}

/// 쪽지 보내는 것을 성공
void CTRNetEventHandler::onRecvMessageSendOK(MessageSystemInfo & messageInfo)
{
	switch(messageInfo.m_eMessageKind)
	{
	case eMessageKind_PERSONAL_CONNECTIONS_OPEN_PROFILE:
	case eMessageKind_PERSONAL_CONNECTIONS_SELECT_IDALTYPE:
		//!< 인맥시스템 내 프로필보기 / 이상향 선택관련 쪽지는 별도 저장하지 않도록 한다..
		//!< DB에서도 저장을 하지 않는다.
		break;
	default:
		CTRMessengerMainUI::getInstance().onRecvSendMessage(messageInfo);
		CTRShortTimeMessage::showMessage(_STR(MESSAGE_SYMTEM_SUCCESS_SEND_MESSAGE));
		break;
	}
}

/// App에서 쪽지 보내는 것을 성공
void CTRNetEventHandler::onRecvMessageAppSendOK(std::vector<MessageSystemInfo>& messageInfo)
{
	for(size_t i = 0; i < messageInfo.size(); ++i )
	{
		CTRMessengerMainUI::getInstance().onRecvMessageAppSendOK( messageInfo[i] );
	}
}

/// 쪽지를 체크하라고 받았다.
void CTRNetEventHandler::onRecvCheckMessage(MessageSystemInfo & messageInfo)
{
	CTRMessengerMainUI::getInstance().onRecvCheckMessage(messageInfo);
}

void CTRNetEventHandler::onRecvCheckMessage(const std::map <__int64, MessageSystemInfo >& newArrivalMessageList)
{
	for (map<__int64, MessageSystemInfo>::const_iterator iter = newArrivalMessageList.begin(); iter != newArrivalMessageList.end(); ++iter )
	{
		MessageSystemInfo info = iter->second;
		CTRMessengerMainUI::getInstance().onRecvCheckMessage(info);
	}
}

/// 쪽지함 목록을 받았다
void CTRNetEventHandler::onRecvMessageBoxList(const eMessageBoxType & messageBoxType, const unsigned short numPage, const unsigned short totalCount, const std::map <__int64, MessageSystemInfo > & messageMap)
{
	CTRMessengerMainUI::getInstance().onRecvMessageBoxList(messageBoxType, numPage, totalCount, messageMap);
}

void CTRNetEventHandler::onRecvReadMessageOK(const __int64 iMessageNum)
{
	CTRMessengerMainUI::getInstance().onRecvReadMessageOK(iMessageNum);
}

/// 쪽지 신고 성공.
void CTRNetEventHandler::onRecvAccuseMessageOK(const __int64 iMessageNum)
{
	CTRMessengerMainUI::getInstance().onRecvAccuseMessageOK(iMessageNum);
}

/// 쪽지 삭제 성공.
void CTRNetEventHandler::onRecvDeleteMessageOK(const eMessageBoxType & messageBoxType, const bool isAll, std::vector<__int64>& vecMessageNum)
{
	CTRMessengerMainUI::getInstance().onRecvDeleteMessageOK(messageBoxType, isAll, vecMessageNum);
}

/// 쪽지 보관 성공.
void CTRNetEventHandler::onRecvKeepMessageOK(const __int64 iMessageNum)
{
	CTRMessengerMainUI::getInstance().onRecvKeepMessageOK(iMessageNum);
}

/// 친구 추가권 가능 횟수
void CTRNetEventHandler::onRecvGetFriendAddFriendOK()
{
	CTRMessengerMainUI::getInstance().update();
}

/// 쪽지 관련 실패
void CTRNetEventHandler::onRecvMessageFailed(const eMessageBoxFailed failedReason)
{
	CTRMessengerMainUI::getInstance().onRecvMessageFailed(failedReason);
}

/// 쪽지 옵션 읽기.
void CTRNetEventHandler::onRecvGetMessageOptionOK(const eMessageBoxOption & messageOption)
{
	CTRMessengerMainUI::getInstance().onRecvGetMessageOptionOK(messageOption);
}

//////////////////////////////////////////////////////////////////////////

/// 선물 보내는 것을 성공
void CTRNetEventHandler::onRecvGiftProductOK(const int iItemDescNum, const int iGameMoney)
{
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvGiftProductOK(iItemDescNum,iGameMoney);
#endif
	CTRShopGiftDialog::getInstance().onRecvGiftProductOK(iItemDescNum,iGameMoney);

	//! 연금상점으로 전달...
	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvGiftProductOK(iItemDescNum,iGameMoney);
	else  CTRAlchemistUI::getInstance().onRecvGiftProductOK(iItemDescNum,iGameMoney);

	const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getItemInfo(iItemDescNum);
	if(pItemInfo != NULL)
	{
		const CItemAttr & itemAttr = CItemAttrTable::getInstance().getItemAttrFromItemDescNum(pItemInfo->m_iUniqueNumber);
		const float fLucky = itemAttr.m_attr[eItemAttr_Lucky];
		if(fLucky != 0.f)
		{
			CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_LUCKY_ITEM_GIFT_GIVE, iItemDescNum);
		}

		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_ITEM_GIFT_GIVE, iItemDescNum);
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();
	}
}

/// 선물 보내는 것을 실패
void CTRNetEventHandler::onRecvGiftProductFailed(const eGiftItemFailed failedReason)
{
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvGiftProductFailed(failedReason);
#endif
	CTRShopGiftDialog::getInstance().onRecvGiftProductFailed(failedReason);

	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvGiftProductFailed(failedReason);
	else  CTRAlchemistUI::getInstance().onRecvGiftProductFailed(failedReason);
}

/// 선물을 체크하라고 받았다.
void CTRNetEventHandler::onRecvCheckGift(const std::vector<eNewGiftMessagType>& msgList)
{
	for(size_t i = 0; i < msgList.size(); ++i)
	{
		if(msgList.at(i) == eNewGiftMessagType_MYROOM_GIFT)
		{
			CTRMyRoomGiftDialog::getInstance().setWaitGift(true);
		}
	}

	CTRUserInterface::getInstance().onRecvCheckGift(msgList);
}

/// 아이템 목록을 받았다.
void CTRNetEventHandler::onRecvGetAvatarItemList(const cpk_type character, const std::vector < NetItemInfo > & ItemList)
{
#ifdef TR_RELEASE_PROJECT
	DBG_DEMO_OUTPUT("onRecvGetAvatarItemList[%d][%d]",character,ItemList.size());
#endif

	CKeepItemList::getInstance().clearCharecterItemList(character);
	CKeepItemList::getInstance().setThisCharOnceRecvItemList(character);
	CKeepItemList::getInstance().insertItemList(character,ItemList);
	CTRMyroomDlg::getInstance().onRecvGetAvatarItemList();

	if (character == eCharacterKind_NONE)
	{
		CNetClientManager::getInstance().requestActiveFuncItem(false);
		CTRExtraAbility::getInstace().onRecvGetAvatarItemList();
	}
	else
	{
		CTRGameParkUI::getInstance().onRecvGetAvatarItemList(character);
		CTRFarmUI::getInstance().onRecvGetAvatarItemList(character);
	}
	
	static bool bCheckAutoUseItem = false;
	if( bCheckAutoUseItem != true )
	{
		CKeepItemList::getInstance().mustUseOneAutoItem();
		bCheckAutoUseItem = true;
	}	
	
	CTRLobbyUI::getInstance().onRecvGetAvatarItemList();

	if (CTRGameParkUI::getInstance().isActive()) 
		CTRGameParkUI::getInstance().onRecvGetAvatarItemList(character);

	else if(CTRAlchemistUI::getInstance().isActive())
		CTRAlchemistUI::getInstance().onRecvGetAvatarItemList();

	ItemDetailView::CTRItemDetailViewManager::getInstance().notifyRefreshItem();

	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().setCoupon();
	
	//! 도전 미션이 있는지 확인한다.
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HAS_ITEM);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_ITEM_COUNT);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HAS_EMBLEM);	// 엠블렘 체크는 가지고 있는지 여부로 체크하기 때문에, 아이템 리스트를 받았을 때 처리한다.
    CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_EMBLEM_COUNT);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_NOT_EXIST_ITEM);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();

	CTRQuestManager::getInstance().inspectTriggerQuestFromHasItem(true, -1);

	if(CNetClientManager::getInstance().getMyActiveItems().getOnItemList(eFuncItemPosition_SKIN).size() == 0)
	{
		const CItemInfoNode* pBasicSkinItem = CClientItemList::getInstance().getItemInfo(ItemKeyInfo(0,eFuncItemPosition_SKIN,1));
		CNetClientManager::getInstance().requestItemOnOff(pBasicSkinItem->m_iUniqueNumber,true);
	}

#ifdef _ARCHIVES_
	if (ARCHIVES::CTRArchivesDlg::getInstance().isVisible()) ARCHIVES::CTRArchivesDlg::getInstance().updateExchangeList();
#endif
}

/// 아이템 목록을 받았다.
void CTRNetEventHandler::onRecvGetAvatarItemList(const cpk_type character, const int iPosition, const std::vector < NetItemInfo > & ItemList)
{
	CKeepItemList::getInstance().clearCharecterItemListByPosition(character, static_cast<cpk_type>(iPosition));
	CKeepItemList::getInstance().setThisCharOnceRecvItemList(character);
	CKeepItemList::getInstance().addItemList(character, ItemList);

	CTRMyroomDlg::getInstance().onRecvGetAvatarItemList();
	if (character == eCharacterKind_NONE) 
	{
		CNetClientManager::getInstance().requestActiveFuncItem(iPosition);
		CTRExtraAbility::getInstace().onRecvGetAvatarItemList();
	}
	else if(iPosition ==  eFuncItemPosition_EXPANSION_VOICE)
	{
		CTRFarmUI::getInstance().onRecvGetAvatarItemList(character);
		CTRGameParkUI::getInstance().onRecvGetAvatarItemList(character);
	}
	
	static bool bCheckAutoUseItem = false;
	if( bCheckAutoUseItem != true )
	{
		CKeepItemList::getInstance().mustUseOneAutoItem();
		bCheckAutoUseItem = true;
	}
	
	CTRLobbyUI::getInstance().onRecvGetAvatarItemList();

	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvGetAvatarItemList(character);
	else  CTRAlchemistUI::getInstance().onRecvGetAvatarItemList();

	ItemDetailView::CTRItemDetailViewManager::getInstance().notifyRefreshItem();

	if(iPosition == eFuncItemPosition_LOTTERY_COUPON)
	{
		CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
		if (pDlg) pDlg->getEventHandler().setCoupon();
	}

	//! 도전 미션이 있는지 확인한다.
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HAS_ITEM);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_ITEM_COUNT);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HAS_EMBLEM);	// 엠블렘 체크는 가지고 있는지 여부로 체크하기 때문에, 아이템 리스트를 받았을 때 처리한다.
    CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_EMBLEM_COUNT);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_NOT_EXIST_ITEM);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();

	CTRQuestManager::getInstance().inspectTriggerQuestFromHasItem(true, -1);

#ifdef _ARCHIVES_
	if (ARCHIVES::CTRArchivesDlg::getInstance().isVisible()) ARCHIVES::CTRArchivesDlg::getInstance().updateExchangeList();
#endif
}

/// 아이템 목록 받기 실패
void CTRNetEventHandler::onRecvGetAvatarItemsFailed()
{
	CTRShortTimeMessage::showMessage(_STR(ERR_RECVITEMLIST_FAILED),1.5f);
}

/// 특정 아이템의 정보를 받았다.
void CTRNetEventHandler::onRecvGetAvatarItemInfo(const NetItemInfo & ItemInfo)
{
	if(ItemInfo.m_iItemDescNum <= 0) return;

	const CItemInfoNode * pItem = CClientItemList::getInstance().getItemInfo(ItemInfo.m_iItemDescNum);

	if(pItem == NULL)return;

	DBG_DEMO_OUTPUT("onRecvGetAvatarItemInfo[%s][%d]",pItem->m_name.c_str(),ItemInfo.m_count);

	CKeepItemList::getInstance().modifyCharacterItemList(ItemInfo.m_character,ItemInfo);

	if(ItemInfo.m_count > 0)
	{	 
		 std::vector<int> items;
		 if(pItem && pItem->m_dwType == CItemInfoNode::ITEMTYPE_NODESC)
		 {
			 if(pItem->m_position >= ITEM_POSITION_HEAD && pItem->m_position < ITEM_POSITION_COUNT)
				 items.push_back(pItem->m_iUniqueNumber);
		 }

		 if(!items.empty())
			 CNetClientManager::getInstance().requestPermanenceItem(items);
	}

	CTRMyroomDlg::getInstance().onRecvGetAvatarItemList();

	if((ItemInfo.m_bHasExpireTime || ItemInfo.m_count >= 0))
	{
		const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(ItemInfo.m_iItemDescNum);
		if(pItem != NULL &&
			((pItem->m_position > ITEM_POSITION_CHARACTER && pItem->m_position < ITEM_POSITION_COUNT && pItem->m_dwType == CItemInfoNode::ITEMTYPE_PARENTDESC)
			|| (pItem->m_position > eFuncItemPosition_NONE && (pItem->getOnOffType() != CItemInfoNode::ITEMINFO_ONOFF_TYPE_NO || CNetClientManager::getInstance().isNeedRefreshActiveItem(pItem->m_position)))))
		{
			std::vector<int> items;
			items.push_back(ItemInfo.m_iItemDescNum);
			CNetClientManager::getInstance().requestActiveFuncItemLIst(items);
		}
	}
	else if(ItemInfo.m_position ==  eFuncItemPosition_EXPANSION_VOICE)
	{
		CTRFarmUI::getInstance().onRecvGetAvatarItemList(ItemInfo.m_character);
		CTRGameParkUI::getInstance().onRecvGetAvatarItemList(ItemInfo.m_character);
	}
	CTRExtraAbility::getInstace().onRecvGetAvatarItemList();

	static bool bCheckAutoUseItem = false;
	if( bCheckAutoUseItem != true )
	{
		CKeepItemList::getInstance().mustUseOneAutoItem();
		bCheckAutoUseItem = true;
	}
	
	CTRLobbyUI::getInstance().onRecvGetAvatarItemList();
	ItemDetailView::CTRItemDetailViewManager::getInstance().onRecvGetAvatarItemList();

	if (CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvGetAvatarItemList();
	else  CTRAlchemistUI::getInstance().onRecvGetAvatarItemList();

	ItemDetailView::CTRItemDetailViewManager::getInstance().notifyRefreshItem();

	if(ItemInfo.m_position == eFuncItemPosition_LOTTERY_COUPON)
	{
		CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
		if (pDlg) pDlg->getEventHandler().setCoupon();
	}	

	if (ItemInfo.m_position ==  eFuncItemPosition_CHAOS_CRYSTAL)
	{
		CTRManufactureManager::getInstance().onRecvGetAvatarItemInfo(ItemInfo);
	}
	
	CTRGameParkUI::getInstance().onRecvGetAvatarItemInfo(ItemInfo);

	if (eFuncItemPosition_FARM_HARVEST_ITEM == ItemInfo.m_position)
	{
		CTRFarmUI::getInstance().onUpdateFarmHarvestList();
	}
	
	CTRFarmUI::getInstance().onRecvCompleteBuy();

	//! 해제 아이템 구매 결과를 다이얼로그에 알려줌
	CTRUserBookDlg::getInstance().onRecvBuyItem();

#ifdef _EXCHANGE_SYSTEM
	//!< 교환아이템 재료 갱신
	if(CTRLobbyUI::getInstance().isActive()) CTRLobbyUI::getInstance().onUpdateExchangeSystemInfo();
	if(CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onUpdateExchangeSystemInfo();
	if(CTRAlchemistUI::getInstance().isActive()) CTRAlchemistUI::getInstance().onUpdateExchangeSystemInfo();
#endif

	//! 도전 미션이 있는지 확인한다.
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HAS_ITEM);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_ITEM_COUNT);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HAS_EMBLEM);	// 엠블렘 체크는 가지고 있는지 여부로 체크하기 때문에, 아이템 리스트를 받았을 때 처리한다.
    CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_EMBLEM_COUNT);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_NOT_EXIST_ITEM);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();

	if (ItemInfo.m_count > 0)
	{
		CTRQuestManager::getInstance().inspectTriggerQuestFromHasItem(false, ItemInfo.m_iItemDescNum);
	}
	else
	{
		CTRQuestManager::getInstance().removeTriggerQuestFromHasItem(ItemInfo.m_iItemDescNum);
	}

#ifdef ENTRY_SYSTEM
	CTREntrySystemManager::getInstance().onRecvGetAvatarItemInfo();
#endif

	if(CTRShopGoodsListDialog::getInstance().isVisible())
	{
		CTRShopGoodsListDialog::getInstance().onRecvGetAvatarItemInfo();
	}
	else if(CTRMyRoomGoodsListDialog::getInstance().isVisible())
	{
		CTRMyRoomGoodsListDialog::getInstance().onRecvGetAvatarItemInfo();
	}
#ifdef _SHOP_RENEWAL_
	else if (CTRShopManager::getInstance().GetShopDialog())
	{
		CTRShopManager::getInstance().onRecvGetAvatarItemInfo();
	}
#endif

#ifdef _EVENTPICKBOARD_
	EVENT_PICKBOARD::CTREventPickBoardUI::getInstance().refreshCoinInfo();
#endif

#ifdef _FISHING_
	CTRFishingSystemManager::getInstance().ReFreshChangeDialog();
#endif

#ifdef _ARCHIVES_
	if (ARCHIVES::CTRArchivesDlg::getInstance().isVisible()) ARCHIVES::CTRArchivesDlg::getInstance().updateExchangeList();
#endif
}

/// 특정 아이템의 정보를 받기 실패했다.
void CTRNetEventHandler::onRecvGetAvatarItemInfoFailed()
{
	CTRShortTimeMessage::showMessage(_STR(ERR_RECVITEMLIST_FAILED),1.5f);
}

/// 특정 아이템들의 정보를 받았다.(캐릭터 및 카드 아이템은 제외한다..)
void CTRNetEventHandler::onRecvGetAvatarItemInfoList(const std::vector<NetItemInfo> & iteminfoList)
{
	DBG_DEMO_OUTPUT("CTRNetEventHandler::onRecvGetAvatarItemInfoList[%d]",iteminfoList.size());

	if(iteminfoList.empty())return;

	std::vector<int> vecFuncItems;

	std::map<int,std::vector<NetItemInfo> >  modifyList;

	for (size_t nIndex = 0; nIndex < iteminfoList.size(); ++ nIndex)
	{
		modifyList[iteminfoList[nIndex].m_character].push_back(iteminfoList[nIndex]);
#ifndef TR_RELEASE_PROJECT

		if (iteminfoList[nIndex].m_count < 0)
		{
			DBG_DEMO_OUTPUT("CTRNetEventHandler::remove[%d]",iteminfoList[nIndex].m_iItemDescNum);
		}
#endif

		//!< 온오프 가능한 기능성 아이템은 따로 담아서 갱신해야 함.
		const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(iteminfoList[nIndex].m_iItemDescNum);
		if(pItem != NULL
		&& pItem->m_position > eFuncItemPosition_NONE
		&& (pItem->getOnOffType() != CItemInfoNode::ITEMINFO_ONOFF_TYPE_NO || CNetClientManager::getInstance().isNeedRefreshActiveItem(pItem->m_position)))
		{
			vecFuncItems.push_back(pItem->m_iUniqueNumber);
		}
	}

	if(!vecFuncItems.empty())
	{	
		CNetClientManager::getInstance().requestActiveFuncItemLIst(vecFuncItems);
	}
	
	for (std::map<int,std::vector<NetItemInfo> >::iterator itor = modifyList.begin(); itor != modifyList.end(); ++itor)
	{
		CKeepItemList::getInstance().modifyCharacterItemList(itor->first,itor->second);
	}
	
	CTRExtraAbility::getInstace().onRecvGetAvatarItemList();
	CTRLobbyUI::getInstance().onRecvGetAvatarItemList();

	if (CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvGetAvatarItemList();
	}
	else
	{
		CTRAlchemistUI::getInstance().onRecvGetAvatarItemList();
	}

	CTRMyroomDlg::getInstance().onRecvGetAvatarItemList();

	ItemDetailView::CTRItemDetailViewManager::getInstance().notifyRefreshItem();

	if(CTRShopGoodsListDialog::getInstance().isVisible())
	{
		CTRShopGoodsListDialog::getInstance().onRecvGetAvatarItemInfo();
	}
	else if(CTRMyRoomGoodsListDialog::getInstance().isVisible())
	{
		CTRMyRoomGoodsListDialog::getInstance().onRecvGetAvatarItemInfo();
	}
#ifdef _SHOP_RENEWAL_
	else if (CTRShopManager::getInstance().GetShopDialog())
	{
		CTRShopManager::getInstance().onRecvGetAvatarItemInfo();
	}
#endif

	//!< 도전 미션이 있는지 확인한다.
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HAS_ITEM);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_ITEM_COUNT);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_NOT_EXIST_ITEM);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();

	CTRQuestManager::getInstance().inspectTriggerQuestFromHasItem(true, -1);

#ifdef _ARCHIVES_
	if (ARCHIVES::CTRArchivesDlg::getInstance().isVisible()) ARCHIVES::CTRArchivesDlg::getInstance().updateExchangeList();
#endif
}

/// 아이템의 수량을 받았다.
void CTRNetEventHandler::onRecvGetRemainCountAvatarItem(const int itemDescNum, time_type expireTime, int remainCount)
{
	//!< 뽑기 쿠폰 관련
	const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getItemInfo(itemDescNum);
	if(pItemInfo)
	{
		if(pItemInfo->m_position == eFuncItemPosition_LOTTERY_COUPON)
		{
			if((int)pItemInfo->getKeepCount() != remainCount)
			{
				CNetClientManager::getInstance().requestActiveFuncItem(eFuncItemPosition_LOTTERY_COUPON);
				CTRLotteryPopup::getInstance().showDialog();
				CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
				if (pDlg) pDlg->getEventHandler().setCoupon(remainCount);
			}
		}
	}
}

/// 아이템의 수량을 받지 못했다.
void CTRNetEventHandler::onRecvGetRemainCountAvatarItemFailed(eServerResult eResult, const int itemDescNum)
{
	if(eResult != eServerResult_OK_ACK)
	{
		_ASSERTE(false);
		return;
	}

	CTRShortTimeMessage::showMessage(_STR(ERR_UNKNOWN),1.5f);
}

/// 마이룸 아이템을 사용하였다.
void CTRNetEventHandler::onRecvMyRoomUseItem(eServerResult eResult, const int iItemNum, const int iItemRemainCount )
{
	if(eResult != eServerResult_OK_ACK)
	{
		_ASSERTE(false);
		return;
	}

	CTRMyRoomGoodsListDialog::getInstance().onUpdateGoodsList();
}

/// 쿨타임이 있는 아이템을 사용했다.
void CTRNetEventHandler::onRecvUseItemEx(eServerResult eResult, int iItemDescNum, int iItemRemainCount, time_type tNextUsableTime)
{
	switch(eResult)
	{
	case eServerResult_OK_ACK:
		{
			CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iItemDescNum);

			CTRGameUI::getInstance().onRecvUseItemEx(iItemDescNum, iItemRemainCount);
			CTRSurvivalGameUI::getInstance().onRecvUseItemEx(iItemDescNum, iItemRemainCount);
		}
		break;
	case eServerResult_USE_ITEM_EX_FAILED_ACK:
		//!< 알수 없는 이유로 아이템 사용에 실패했다.
		//DBG_OUTPUT("CTRNetEventHandler::onRecvUseItemEx eServerResult_USE_ITEM_EX_FAILED_ACK");
	    break;
	case eServerResult_USE_ITEM_EX_REMAIN_COOL_TIME_ACK:
		//!< 쿨타임이 남아서 아이템 사용에 실패했다.
		//DBG_OUTPUT("CTRNetEventHandler::onRecvUseItemEx eServerResult_USE_ITEM_EX_REMAIN_COOL_TIME_ACK");
		break;
	}
}

/// 특정 유저가 특정 아이템을 사용했다.
void CTRNetEventHandler::onRecvRoomUseItemNotify(BYTE iUserGameIndex, BYTE iTargetGameIndex, int iItemDescNum)
{

}

/// 맵 이벤트 발생 통지를 받았다.
void CTRNetEventHandler::onRecvMapEvent(eMapEventType byEventType, DWORD dwEventTime)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvMapEvent type = %d, time = %d", byEventType, dwEventTime);
	CGameTriggerManager::getInstance().onRecvMapEvent(byEventType, dwEventTime);
}

/// 다음 올림픽 게임 공지 정보를 받았다..
void CTRNetEventHandler::onRecvNextOlympicGameInfo(const OlympicGameInfo & gameInfo)
{
	CTREventLeageManager::getInstance().onRecvNextOlympicGameInfo(gameInfo);
}

/// 다음 올림픽 게임 공지 정보를 받았다..
void CTRNetEventHandler::onRecvNextOlympicGameNoticeInfo(const OlympicGameInfo & gameInfo)
{
	CTREventLeageManager::getInstance().onRecvNextOlympicGameNoticeInfo(gameInfo);	
}

//////////////////////////////////////////////////////////////////////////
// 삐에로 올림픽

/// 다음 삐에로 올림픽 경기 일정을 받았다.
void CTRNetEventHandler::onRecvNextPieroOlympicGameNoticeInfo(const std::vector<OlympicGameInfo>& pieroOlympicGameInfoList)
{
	CTREventSportsManager::getInstance().onRecvTodayOlympicGameInfo(pieroOlympicGameInfoList);
	CTRLobbyUI::getInstance().onUpdatePieroOlympicInfo(CTRPieroOlympicChannelDlg::eChannelUpdateFlag_GameInfo);

	DBG_OUTPUT("%s - pieroOlympicGameInfo size : %d", __FUNCTION__, (int)pieroOlympicGameInfoList.size());
}

//!< 다음 삐에로 올림픽 게임 시작 예정 공지를 받았다.
void CTRNetEventHandler::onRecvPieroOlympicNextGameStartScheduleNotice(const OlympicGameInfo & gameInfo)
{
	CTREventSportsManager::getInstance().onRecvPieroGameScheduleNotice(gameInfo);
}

//!< 현재 삐에로 올림픽 게임 종료 예정 공지를 받았다.
void CTRNetEventHandler::onRecvPieroOlympicThisGameFinishScheduleNotice(const OlympicGameInfo & gameInfo)
{
	CTREventSportsManager::getInstance().onRecvPieroGameScheduleNotice(gameInfo, false);
}

//!< 현재 삐에로 올림픽 게임 종료 공지를 받았다. (승리팀)
void CTRNetEventHandler::onRecvPieroOlympicThisGameFinisheNotice(ePieroOlympicPartyType winnerParty)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicThisGameFinisheNotice(winnerParty);
	DBG_OUTPUT("%s - win team : %d", __FUNCTION__, (int)winnerParty);
}

//!< 현재 삐에로 올림픽 상점 이용가능한 팀 공지를 받았다.(상점이용가능 복수 팀)
void CTRNetEventHandler::onRecvPieroOlympicShopUsablePartyNotice(const std::vector<ePieroOlympicPartyType>& partyTypeList)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicShopUsablePartyNotice(partyTypeList);
}

//!< 현재 삐에로 올림픽 상점이 모든 팀에게 개방하기까지 남은 시간을 공지 받았다.
void CTRNetEventHandler::onRecvPieroOlympicShopUsablePartyRemainTimeNotice(const time_type remainTime)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicShopUsablePartyRemainTimeNotice(remainTime);
}

//!< 삐에로 연금 아이템 EXP 보너스 공지를 받았다.
void CTRNetEventHandler::onRecvPieroOlympicPieroAlchemistItemEXPBonusNotice(const std::map<ePieroOlympicPartyType, int>& PieroOlympicEXPBonusMap)
{
	if(CTRPieroOlympicRoomUI::getInstance().isActive())
	{
		CTRPieroOlympicRoomUI::getInstance().onRecvPieroOlympicPieroAlchemistItemEXPBonusNotice(PieroOlympicEXPBonusMap);
	}	
}

//!< New 삐에로 드래곤 착용 EXP보너스 공지를 받았다.
void CTRNetEventHandler::onRecvPieroOlympicDragonEXPBonusNotice(int iEXPBonus)
{
	if(CTRPieroOlympicRoomUI::getInstance().isActive())
	{
		CTRPieroOlympicRoomUI::getInstance().onRecvPieroOlympicDragonEXPBonusNotice(iEXPBonus);
	}
}

//!< 삐에로방 TR,EXP 보너스 공지를 받았다.
void CTRNetEventHandler::onRecvPieroOlympicPieroBonusNotice(std::map<ePieroOlympicPartyType, BuffBonusInfo> pieroOlympicPieroBonusMap)
{
	CTRUserInterface::getInstance().onRecvPieroOlympicPieroBonusNotice(pieroOlympicPieroBonusMap);
}

/// 나의 삐에로 올림픽 정보를 요청을 성공했다.
void CTRNetEventHandler::onRecvPieroOlympicGetMyPieroOlympicInfoOK(const PieroOlympicUserInfo& pieroOlympicUserInfo)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicGetMyPieroOlympicInfo(pieroOlympicUserInfo);
	CTRLobbyUI::getInstance().onUpdatePieroOlympicInfo(CTRPieroOlympicChannelDlg::eChannelUpdateFlag_MyPoint);
	DBG_OUTPUT("%s - myTeam : %d, contribute point : %d",
						__FUNCTION__, (int)pieroOlympicUserInfo.m_pieroOlympicPartyType, pieroOlympicUserInfo.m_iContributionPoint);
}

/// 나의 삐에로 올림픽 정보를 요청을 실패했다.
void CTRNetEventHandler::onRecvPieroOlympicGetMyPieroOlympicInfoFailed(ePieroOlympicFailedReason failedReason)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicFailed(failedReason);
	DBG_OUTPUT("%s", __FUNCTION__);
}

/// 나의 삐에로 올림픽 기여포인트 요청을 성공했다.
void CTRNetEventHandler::onRecvPieroOlympicGetMyContributionPointOK(int iContributionPoint, int iAccumulationPoint)
{
	CTREventSportsManager::getInstance().onRecvMyContributionPoint(iContributionPoint, iAccumulationPoint);
	CTRLobbyUI::getInstance().onUpdatePieroOlympicInfo(CTRPieroOlympicChannelDlg::eChannelUpdateFlag_MyPoint);

	DBG_OUTPUT("%s - my contribution point : %d", __FUNCTION__, iContributionPoint);
}

/// 나의 삐에로 올림픽 기여포인트 요청을 실패했다.
void CTRNetEventHandler::onRecvPieroOlympicGetMyContributionPointFailed(ePieroOlympicFailedReason failedReason)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicFailed(failedReason);
}

/// 오늘의 성장포인트를 요청을 성공했다.
void CTRNetEventHandler::onRecvPieroOlympicGetThisSeasonGrowthPointOK(const std::vector<PieroOlympicPartyInfo>& todaysGrowthPointList)
{
	CTREventSportsManager::getInstance().onRecvPieroGamePointInfo(todaysGrowthPointList);
	DBG_OUTPUT("%s - todaysGrowthPointList size : %d", __FUNCTION__, (int)todaysGrowthPointList.size());

	if (CTREventSportsManager::getInstance().isOlympicEnterTime())
	{
		CTRLobbyUI::getInstance().onUpdatePieroOlympicInfo(CTRPieroOlympicChannelDlg::eChannelUpdateFlag_TodayPoint);
	}
	else
	{
		CTRLobbyUI::getInstance().onUpdatePieroOlympicInfo(CTRPieroOlympicChannelDlg::eChannelUpdateFlag_NewPieroTodayPoint);
	}

	for(size_t i = 0; i < todaysGrowthPointList.size(); ++i)
	{
		const PieroOlympicPartyInfo& info = todaysGrowthPointList.at(i);
		DBG_OUTPUT("%s - %d, %I64d", __FUNCTION__, (int)info.m_pieroOlympicPartyType, info.m_iGrowthPoint);
	}
}

/// 오늘의 성장포인트를 요청을 실패했다.
void CTRNetEventHandler::onRecvPieroOlympicGetThisSeasonGrowthPointFailed(ePieroOlympicFailedReason failedReason)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicFailed(failedReason);
}

/// 방해 성장포인트를 요청을 성공했다.
void CTRNetEventHandler::onRecvPieroOlympicGetInterruptGrowthPointOK(const std::vector<PieroOlympicInterruptGrowthInfo>& interruptGrowthPointList)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicGetInterruptGrowthPointOK(interruptGrowthPointList);
	
	int iInterpolation = 1;

	if(CTREventSportsManager::getInstance().isEventSportsType(CTREventSportsManager::ePieroOlympic_New))
	{
		iInterpolation = 18;
	}
	else if(CTREventSportsManager::getInstance().isEventSportsType(CTREventSportsManager::ePieroOlympic_LoveBattle2))
	{
		iInterpolation = 25;
	}

	std::map<int,int> mapValues;
	for(int i = 1; i < ePieroOlympicPartyType_MAX; ++i)
		mapValues.insert(make_pair(i+iInterpolation,i));		// 삐에로 올림픽 오브젝트 번호는 2번 부터 시작..뉴 삐에로(카오스3차)는 19번부터 시작...

	if(CTRGameParkUI::getInstance().isActive())
		CTRGameParkUI::getInstance().onRecvAnniversaryObjectValueOK(mapValues, 3);
}

/// 방해 성장포인트를 요청을 실패했다.
void CTRNetEventHandler::onRecvPieroOlympicGetInterruptGrowthPointFailed(ePieroOlympicFailedReason failedReason)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicFailed(failedReason);
}

/// 전체 성장포인트를 요청을 성공했다.
void CTRNetEventHandler::onRecvPieroOlympicGetTotalGrowthPointOK(const std::vector<PieroOlympicPartyInfo>& totalGrowthPointList)
{
	CTREventSportsManager::getInstance().onRecvPieroTotalPointInfo(totalGrowthPointList);	
	DBG_DEMO_OUTPUT("%s - totalGrowthPointList size : %d", __FUNCTION__, (int)totalGrowthPointList.size());

	for(size_t i = 0; i < totalGrowthPointList.size(); ++i)
	{
		const PieroOlympicPartyInfo& info = totalGrowthPointList.at(i);
		DBG_DEMO_OUTPUT("%s - %d, %I64d", __FUNCTION__, (int)info.m_pieroOlympicPartyType, info.m_iGrowthPoint);
	}

	CTRLobbyUI::getInstance().onUpdatePieroOlympicInfo(CTRPieroOlympicChannelDlg::eChannelUpdateFlag_TotalPoint);
}

/// 전체 성장포인트를 요청을 실패했다.
void CTRNetEventHandler::onRecvPieroOlympicGetTotalGrowthPointFailed(ePieroOlympicFailedReason failedReason)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicFailed(failedReason);
}

/// 삐에로 나무가 레벨업 했을때 보상 아이템을 요청에 성공했다.
void CTRNetEventHandler::onRecvPieroOlympicGiveLevelUpRewardOK(int iRewardItemNum)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicGiveLevelUpRewardOK(iRewardItemNum);
	DBG_OUTPUT("%s itemNum[%d]", __FUNCTION__, iRewardItemNum);
}

/// 삐에로 나무가 레벨업 했을때 보상 아이템을 요청에 실패했다.
void CTRNetEventHandler::onRecvPieroOlympicGiveLevelUpRewardFailed(ePieroOlympicFailedReason failedReason)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicFailed(failedReason);
	DBG_OUTPUT("%s FailReason[%d]", __FUNCTION__, failedReason);
}

/// 삐에로 올림픽 팀 가입 요청을 성공했다.
void CTRNetEventHandler::onRecvPieroOlympicJoinPartyOK(ePieroOlympicPartyType ePartyType, int iRewardItemNum)
{
	CTRGameParkUI::getInstance().onRecvPieroOlympicJoinPartyOK(ePartyType, iRewardItemNum);
	DBG_OUTPUT("%s PartyType[%d] RewardItemNum[%d]", __FUNCTION__, ePartyType, iRewardItemNum);
}

/// 삐에로 올림픽 팀 가입 요청을 실패했다.
void CTRNetEventHandler::onRecvPieroOlympicJoinPartyFailed(ePieroOlympicFailedReason eFailedReason)
{
	CTRGameParkUI::getInstance().onRecvPieroOlympicJoinPartyFailed(eFailedReason);
	DBG_OUTPUT("%s FailReason[%d]", __FUNCTION__, eFailedReason);
}

/// 삐에로 올림픽 팀 같이 가입 성공했다.
void CTRNetEventHandler::onRecvPieroOlympicJoinPartyPurposeInfoOK(ePieroOlympicPartyType ePartyType, int iRewardItemNum)
{
	CTRGameParkUI::getInstance().onRecvPieroOlympicJoinPartyOK(ePartyType, iRewardItemNum);
	DBG_OUTPUT("%s PartyType[%d] RewardItemNum[%d]", __FUNCTION__, ePartyType, iRewardItemNum);
}

/// 삐에로 올림픽 팀 같이 가입 실패했다.
void CTRNetEventHandler::onRecvPieroOlympicJoinPartyPurposeInfoFailed(ePieroOlympicFailedReason eFailedReason)
{
	CTRGameParkUI::getInstance().onRecvPieroOlympicJoinPartyFailed(eFailedReason);
	DBG_OUTPUT("%s FailReason[%d]", __FUNCTION__, eFailedReason);
}

/// 삐에로 상점에서 아이템 구매시 구매 요청에 성공했다.
void CTRNetEventHandler::onRecvPieroOlympicShopBuyItemOK(const std::vector<PieroOlympicShopInfo>& shopInfo)
{
	CTRLobbyUI::getInstance().onRecvPieroOlympicShopBuyItemOK(shopInfo);
}

/// 삐에로 상점에서 아이템 구매시 구매 요청에 실패했다.
void CTRNetEventHandler::onRecvPieroOlympicShopBuyItemFailed(ePieroOlympicShopFailedReason failedReason, int iItemNum)
{
	CTRLobbyUI::getInstance().onRecvPieroOlympicShopBuyItemFailed(failedReason, iItemNum);
	DBG_OUTPUT("%s FailReason[%d]", __FUNCTION__, failedReason);
}

/// 삐에로 상점에서 판매하는 아이템리스트 요청에 성공했다.
void CTRNetEventHandler::onRecvPieroOlympicGetShopInfoOK(const std::vector<PieroOlympicShopInfo>& itemList, const std::vector<ePieroOlympicPartyType>& partyList, const bool bActiveShop, const bool bShopUsableWinnerParty)
{
	CTRLobbyUI::getInstance().onRecvPieroOlympicGetShopInfoOK(itemList, partyList, bActiveShop, bShopUsableWinnerParty);
}

/// 삐에로 상점에서 판매하는 아이템리스트 요청에 실패했다.
void CTRNetEventHandler::onRecvPieroOlympicGetShopInfoFailed()
{
	CTRLobbyUI::getInstance().onRecvPieroOlympicGetShopInfoFailed();
	DBG_OUTPUT("%s", __FUNCTION__);
}

/// 대전 팀 정보를 받았다.
void CTRNetEventHandler::onRecvPieroOlympicGetCompetitionTeamInfo(eCompetitionRule rule, const std::vector<ePieroOlympicPartyType>& teamInfo)
{
	CTREventSportsManager::getInstance().onRecvPieroOlympicGetCompetitionTeamInfo(rule, teamInfo);
}

void CTRNetEventHandler::onRecvCompetitionInfoOK()
{

}

// 삐에로 올림픽 끝
//////////////////////////////////////////////////////////////////////////


///티켓 쟁탈전 팀가입을 받았다.
void CTRNetEventHandler::onRecvTicketScrambleJoinPartyOK(ePieroOlympicPartyType ePartyType)
{
	CTRGameParkUI::getInstance().onRecvTicketScrambleJoinPartyOK(ePartyType);
	DBG_OUTPUT("%s PartyType[%d]", __FUNCTION__, ePartyType);
}

///티켓 쟁탈전 팀가입에 실패했다.
void CTRNetEventHandler::onRecvTicketScrambleJoinPartyFailed(ePieroOlympicFailedReason failedReason)
{
	CTRGameParkUI::getInstance().onRecvTicketScrambleJoinPartyFailed(failedReason);
	DBG_OUTPUT("%s FailReason[%d]", __FUNCTION__, failedReason);
}

///티켓 쟁탈전 정보를 받았다.
void CTRNetEventHandler::onRecvTicketScrambleGetInfoOK(const TicketScrambleInfo& ticketScrambleInfo)
{

}

///티켓 쟁탈전 정보 요청에 실패했다.
void CTRNetEventHandler::onRecvTicketScrambleGetInfoFailed()
{

}

///티켓 충전을 받았다.
void CTRNetEventHandler::onRecvTicketScrambleRechargeTicketOK(int iTicketCount)
{
	CTRLobbyUI::getInstance().onRecvTicketScrambleRechargeTicketOK(iTicketCount);
	DBG_OUTPUT("%s Ticket Count = %d", __FUNCTION__, iTicketCount);
}

///티켓 충전을 실패했다.
void CTRNetEventHandler::onRecvTicketScrambleRechargeTicketFailed()
{
	CTRLobbyUI::getInstance().onRecvTicketScrambleRechargeTicketFailed();
	DBG_OUTPUT("%s", __FUNCTION__);
}

///티켓 쟁탈전 결과 보상아이템을 받았다.
void CTRNetEventHandler::onRecvTicketScrambleResultReward(const RewardInfo & rewardInfo)
{
	CTRLobbyUI::getInstance().onRecvTicketScrambleResultReward(rewardInfo);
}

void CTRNetEventHandler::onRecvTicketScrambleInitInfo()
{
	CTRLobbyUI::getInstance().onRecvTicketScrambleInitInfo();

	CNetClientManager::getInstance().requestTicketScrambleGetInfo();
}

///////////////////////////////////////////////////////////////////////////
/// 런닝맨2
#ifdef _RUNNING_MAN2

/// 다음 런닝맨2 경기 일정을 받았다.
void CTRNetEventHandler::onRecvNextRunningMan2GameNoticeInfo(const std::vector<OlympicGameInfo>& gameInfoList)
{
	CTREventSportsManager::getInstance().onRecvTodayOlympicGameInfo(gameInfoList);
}

///런닝맨2 팀가입을 받았다.
void CTRNetEventHandler::onRecvRunningMan2JoinPartyOK(ePieroOlympicPartyType ePartyType)
{
	CTRGameParkUI::getInstance().onRecvRunningMan2JoinPartyOK(ePartyType);
}

///런닝맨2 팀가입에 실패했다.
void CTRNetEventHandler::onRecvRunningMan2JoinPartyFailed(ePieroOlympicFailedReason failedReason)
{
	CTRGameParkUI::getInstance().onRecvRunningMan2JoinPartyFailed(failedReason);
}

///런닝맨2 정보를 받았다.
void CTRNetEventHandler::onRecvRunningMan2GetInfoOK(const TicketScrambleInfo& ticketScrambleInfo)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_RUNNINGMAN2)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRRunningMan2ChannelUI* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRRunningMan2ChannelUI>(SUB_PTR_DIALOG_TYPE_EVENT_RUNNINGMAN2);
		if(pChannelUI) pChannelUI->updateTicketInfo();
	}
}

///런닝맨2 정보 요청에 실패했다.
void CTRNetEventHandler::onRecvRunningMan2GetInfoFailed()
{
}

///런닝맨2 티켓 충전을 받았다.
void CTRNetEventHandler::onRecvRunningMan2RechargeTicketOK(const TicketScrambleInfo& ticketScrambleInfo)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_RUNNINGMAN2)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRRunningMan2ChannelUI* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRRunningMan2ChannelUI>(SUB_PTR_DIALOG_TYPE_EVENT_RUNNINGMAN2);
		if(pChannelUI)
		{
			COkDialogEx::getInstance().showDialog( format(_STR(TICKET_SCRAMBLE_RECHARGE_TICKET), ticketScrambleInfo.m_iMyTicket) );
			pChannelUI->updateTicketInfo();
		}
	}
}

///런닝맨2 티켓 충전을 실패했다.
void CTRNetEventHandler::onRecvRunningMan2RechargeTicketFailed()
{
	COkDialogEx::getInstance().showDialog(_STR(FAILED_TICKET_RECHARGE));
}

///런닝맨2 결과 보상아이템을 받았다.
void CTRNetEventHandler::onRecvRunningMan2ResultReward(const RewardInfo & rewardInfo)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_RUNNINGMAN2)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRRunningMan2ChannelUI* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRRunningMan2ChannelUI>(SUB_PTR_DIALOG_TYPE_EVENT_RUNNINGMAN2);
		if(pChannelUI) pChannelUI->onRecvRunningMan2ResultReward(rewardInfo);
	}
}

///런닝맨2 정보 초기화를 받았다.
void CTRNetEventHandler::onRecvRunningMan2InitInfo()
{
}

/// 런닝맨2 상점에서 아이템 구매시 구매 요청에 성공했다.
void CTRNetEventHandler::onRecvRunningMan2ShopBuyItemOK(int iItemNum, const std::vector<PieroOlympicShopInfo>& shopInfo)
{
	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRRunningMan2ChannelUI* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRRunningMan2ChannelUI>(SUB_PTR_DIALOG_TYPE_EVENT_RUNNINGMAN2);
		if(pChannelUI) pChannelUI->onRecvRunningMan2ShopBuyItemOK(iItemNum, shopInfo);
	}
}

/// 런닝맨2 상점에서 아이템 구매시 구매 요청에 실패했다.
void CTRNetEventHandler::onRecvRunningMan2ShopBuyItemFailed(ePieroOlympicShopFailedReason failedReason, int iItemNum)
{
	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRRunningMan2ChannelUI* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRRunningMan2ChannelUI>(SUB_PTR_DIALOG_TYPE_EVENT_RUNNINGMAN2);
		if(pChannelUI) pChannelUI->onRecvRunningMan2ShopBuyItemFailed(failedReason, iItemNum);
	}
}

/// 런닝맨2 상점 정보 요청에 성공했다.
void CTRNetEventHandler::onRecvRunningMan2GetShopInfoOK(const std::vector<PieroOlympicShopInfo>& shoInfo)
{
	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRRunningMan2ChannelUI* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRRunningMan2ChannelUI>(SUB_PTR_DIALOG_TYPE_EVENT_RUNNINGMAN2);
		if(pChannelUI) pChannelUI->onRecvRunningMan2GetShopInfoOK(shoInfo);
	}
}

/// 런닝맨2 상점 정보 요청에 실패했다.
void CTRNetEventHandler::onRecvRunningMan2GetShopInfoFailed()
{
}

#endif	// _RUNNING_MAN2


/// 유저의 마지막 클리어한 맵룰 정보를 받았다.
void CTRNetEventHandler::onRecvCorunModeGetUserLastClearedMapRuleInfoOK()
{
#pragma message("TODO : 체크 필요.. onRecvCorunModeGetUserLastClearedMapRuleInfoOK 사용 하지 않음")
}

/// 유저의 마지막 클리어한 맵룰 정보 받기를 실패했다.
void CTRNetEventHandler::onRecvCorunModeGetUserLastClearedMapRuleInfoFailed(eCorunModeFailedReason eFailedReason)
{
	string strMsg;

	switch(eFailedReason)
	{
	case eCorunModeFailedReason_DB_ERROR:					//!< DB 에러
		strMsg = _STR(FAILED_DB_ERROR);
		break;
	case eCorunModeFailedReason_INVALID_BOSS_ENERGY:		//!< 유효하지 않은 보스 에너지 값
		strMsg = _STR(FAILED_INVALID_BOSS_ENERGY);
		break;
	case eCorunModeFailedReason_BOSS_ENERGY_IS_ALREADY_SET:	//!< 보스 에너지가 이미 설정되었음
		strMsg = _STR(FAILED_BOSS_ENERGY_IS_ALREADY_SET);
		break;
	}

	DBG_OUTPUT("CTRNetEventHandler::onRecvCorunModeGetUserLastClearedMapRuleInfoFailed [%s]", strMsg.c_str());
}

/// 유저의 마지막 클리어한 맵룰 정보가 업데이트되었다.
void CTRNetEventHandler::onRecvCorunModeUpdateUserLastClearedMapRuleInfo()
{
#pragma message("TODO : 체크 필요.. onRecvCorunModeUpdateUserLastClearedMapRuleInfo 사용 하지 않음")
}

/// 현재 맵의 최고 기록을 받았다. (협동 달리기 모드에서 방장이 게임 로딩 시작을 요청하면 서버에서 보내줌)
void CTRNetEventHandler::onRecvCorunModeTopRecord(eCorunModeRank eRank, int iClearTime, std::vector<std::string> &vecUserNickname)
{
	CGameManager::getInstance().onRecvCorunModeTopRecord(eRank,iClearTime,vecUserNickname);
	DBG_OUTPUT("CTRNetEventHandler::onRecvCorunModeTopRecord");
}

/// 시간이 흐는 구간의 클리어 제한 시간을 설정해라.
void CTRNetEventHandler::onRecvCorunModeSetClearLimitTime(int iClearLimitTime)
{	
	CGameManager & rGameManager = CGameManager::getInstance();

	if (rGameManager.isGameMapBossMode())
	{
		CGameManager::getInstance().onRecvCorunModeSetClearLimitTime(iClearLimitTime);
	}
	else if (rGameManager.isGameMapRevivalAndDieMode())
	{
		CInGameModeControlManager_RevivalandDie::getinstance().onRecvCorunModeSetClearLimitTime(iClearLimitTime, 1);
	}
	else if (rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_FLAG_WAR) || 
			 rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_FROZEN_CORPSE) ||
			 rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_RUN_QUIZ_MODE) || 
			 rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_HAMMER_GAME) ||
			 rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_GHOST_MODE_SURVIVAL) ||
			 rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_RANDOM_EXAMPLE_MODE) ||
			 rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_INGAME_SPECIAL_ABILITY_SURVIVAL) ||
			 rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_TYPING_RUN) ||
			 rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_RANDOM_BAT) ||
			 rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_ICE_FLOWER))
 	{
		rGameManager.getInGameMode()->notifyIntValue("recv_limitTime", iClearLimitTime);
 	}
	else
	{
		CTRGameUI::getInstance().onRecvSetClearLimitTime(iClearLimitTime);
		CTRAssaultGameUI::getInstance().onRecvSetStartLimitTime(iClearLimitTime);
	}
}

void CTRNetEventHandler::onRecvCorunModeTriggerMapEvent(BYTE byEventNum, int iEventLapTime)
{
	CGameTriggerManager::getInstance().onRecvTriggerMapEvent(byEventNum, iEventLapTime);

	DBG_OUTPUT("CTRNetEventHandler::onRecvCorunModeTriggerMapEvent : EventNum[%d],EventLapTime[%d]",(int)byEventNum,iEventLapTime);
}

/// 오브젝트 이벤트가 발생했다.
void CTRNetEventHandler::onRecvCorunModeTriggerObjectEvent(int iObjectIndex, eCorunModeObjectEventType eEventType,unsigned int iValue)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvCorunModeTriggerObjectEvent[%d][%d][%d]",iObjectIndex,eEventType,iValue);
	CGameManager::getInstance().onRecvCorunModeTriggerObjectEvent(iObjectIndex,eEventType,iValue);
}
// 오브젝트 점유 체크 후 이벤트가 발생한다.
void CTRNetEventHandler::onRecvCorunModeTriggerCheckInObjectEvent(const BYTE numGameIndex, int iObjectIndex, int iLockIndex, eCorunModeObjectEventType eEventType,unsigned int iValue)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvCorunModeTriggerCheckInObjectEvent[%d][%d][%d]",numGameIndex,iObjectIndex,iLockIndex,iValue);
	CGameManager::getInstance().onRecvCorunModeTriggerCheckInObjectEvent(static_cast<int>(numGameIndex),iObjectIndex,iLockIndex,eEventType,iValue);
}

/// 폭탄 설치 모션 이벤트가 발생했다.
void CTRNetEventHandler::onRecvCorunModeTriggerBombMotionEvent(byte byEventNum, byte byManagerIndex, byte byGeneratorIndex, byte byObjectIndex)
{
	CGameManager::getInstance().onRecvCorunModeTriggerBombMotionEvent(byEventNum,byManagerIndex,byGeneratorIndex,byObjectIndex);

#ifndef TR_RELEASE_PROJECT
	DBG_OUTPUT("CTRNetEventHandler::onRecvCorunModeTriggerBombMotionEvent byEventNum[%d]byManagerIndex[%d]byGeneratorIndex[%d]byObjectIndex[%d]",(int)byEventNum,(int)byManagerIndex,(int)byGeneratorIndex,(int)byObjectIndex);
#endif //TR_RELEASE_PROJECT
}

/// 시간이 흐르는 구간에 누군가 입장했다.
void CTRNetEventHandler::onRecvCorunModeEnterTimeSection(BYTE bySectionNum, int iClearLimitTime, int iBonusTime)
{
	DBG_DEMO_OUTPUT("CTRNetEventHandler::onRecvCorunModeEnterTimeSection SectionNum=[%d], ClearLimitTime=[%d], BonusTime=[%d]", (int)bySectionNum, iClearLimitTime, iBonusTime);

	CGameManager & rGameManager =  CGameManager::getInstance();

	if (rGameManager.isGameMapRevivalAndDieMode())
	{
		CInGameModeControlManager_RevivalandDie::getinstance().onRecvCorunModeSetClearLimitTime(iClearLimitTime, static_cast<int>(bySectionNum));
	}
	else if(rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_FLAG_WAR) ||
			rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_FROZEN_CORPSE) ||
			rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_HAMMER_GAME) ||
			rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_RUN_QUIZ_MODE) ||
			rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_GHOST_MODE_SURVIVAL) ||
			rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_RANDOM_EXAMPLE_MODE) ||
			rGameManager.isCurrInGameMode(GAME_MODE_PROCESSOR_INGAME_SPECIAL_ABILITY_SURVIVAL))
 	{
		rGameManager.getInGameMode()->notifyIntValue("recv_limitTime", iClearLimitTime);
 	}
	else
	{
		CGameManager::getInstance().onRecvCorunModeEnterTimeSection(bySectionNum, iClearLimitTime, iBonusTime);
		CTRAssaultGameUI::getInstance().onRecvSetStartLimitTime(iBonusTime);
	}
}

/// 시간이 흐르는 구간을 마지막 유저가 클리어했다.
void CTRNetEventHandler::onRecvCorunModeClearTimeSection(BYTE bySectionNum, int iClearTime, int iBonusTime)
{
	DBG_DEMO_OUTPUT("CTRNetEventHandler::onRecvCorunModeClearTimeSection SectionNum=[%d], ClearTime=[%d], BonusTime=[%d]", (int)bySectionNum, iClearTime, iBonusTime);

	//!< 해당 설정은 보스맵만 사용함
	if(CGameManager::getInstance().isGameMapBossMode())
		CGameManager::getInstance().onRecvCorunModeClearTimeSection(bySectionNum, iClearTime, iBonusTime);
}

/// 보스 에너지를 설정했다.
void CTRNetEventHandler::onRecvCorunModeSetBossEnergyOK(int iObjectIndex)
{
	CGameManager::getInstance().onRecvCorunModeSetBossEnergyOK(iObjectIndex);
}

/// 보스 에너지 설정을 실패했다.
void CTRNetEventHandler::onRecvCorunModeSetBossEnergyFailed(eCorunModeFailedReason eFailedReason)
{
	string strMsg;
	switch(eFailedReason)
	{
	case eCorunModeFailedReason_DB_ERROR:					//!< DB 에러
		strMsg = _STR(FAILED_BOSS_ENERGY_DB_ERROR);
		DBG_OUTPUT("CTRNetEventHandler::onRecvCorunModeSetBossEnergyFailed [%s]", strMsg.c_str());
		break;
	case eCorunModeFailedReason_INVALID_BOSS_ENERGY:		//!< 유효하지 않은 보스 에너지 값
		strMsg = _STR(FAILED_BOSS_INVALID_BOSS_ENERGY);
		DBG_OUTPUT("CTRNetEventHandler::onRecvCorunModeSetBossEnergyFailed [%s]", strMsg.c_str());
		break;
	case eCorunModeFailedReason_BOSS_ENERGY_IS_ALREADY_SET:	//!< 보스 에너지가 이미 설정되었음
		strMsg = _STR(FAILED_BOSS_ENERGY_IS_ALREADY_SET);
		//! 8명이 전원 날리는데...첫번째를 제외한 뒤에 모두가 이 메세지를 받게 되어 있다..(추후에 수정)
		break;
	}
}

/// 보스 에너지를 차감했다.
void CTRNetEventHandler::onRecvCorunModeDecreaseBossEnergy(int iBossEnergy, int iObjectIndex)
{
	CGameManager::getInstance().onRecvCorunModeDecreaseBossEnergy(iBossEnergy, iObjectIndex);
}
/// 오브젝트 보스 에너지 설정을 성공했다.
void CTRNetEventHandler::onRecvCorunModeSetObjectBossEnergyOK(int iObjectType, int iObjectIndex, int iValue)
{
	CGameManager::getInstance().onRecvCorunModeSetObjectBossEnergyOK(iObjectType,iObjectIndex,iValue);
}

/// 오브젝트 보스 에너지 설정을 실패했다.
void CTRNetEventHandler::onRecvCorunModeSetObjectBossEnergyFailed(int iObjectType, int iObjectIndex, int iValue, eCorunModeFailedReason eFailedReason)
{
	TRDBG_OUTPUT_ERROR("CTRNetEventHandler::onRecvCorunModeSetObjectBossEnergyFailed::[%d][%d][%d][%d]",iObjectType,iObjectIndex,iValue,(int)eFailedReason);
}

/// 오브젝트 보스 에너지를 차감했다.
void CTRNetEventHandler::onRecvCorunModeDecreaseObjectBossEnergy(int iObjectType, int iObjectIndex, int iValue, int iBossEnergy)
{
	CGameManager::getInstance().onRecvCorunModeDecreaseObjectBossEnergy(iObjectType,iObjectIndex,iValue,iBossEnergy);
}
/// 오브젝트 보스 에너지를 증가시켰다.
void CTRNetEventHandler::onRecvCorunModeIncreaseObjectBossEnergy(int iObjectType, int iObjectIndex, int iValue, int iBossEnergy)
{
	CGameManager::getInstance().onRecvCorunModeIncreaseObjectBossEnergy(iObjectType,iObjectIndex,iValue,iBossEnergy);
}


/// 나의 트로피 리스트를 받았다.
void CTRNetEventHandler::onRecvMyRoomGetMyTrophyList(const std::vector < int > & trophyList)
{
	CTRTrophyRoom::getInstance().onRecvMyRoomGetMyTrophyList(trophyList);
}

/// 나의 트로피 리스트를 받는데 실패했다.
void CTRNetEventHandler::onRecvMyRoomGetMyTrophyListFailed()
{
	CTRShortTimeMessage::showMessage(_STR(ERR_TROPHY_LIST_FAILED),1.5f);
}

#ifdef _SELECTIVE_PACKAGE_
///< 선택의 상자 사용하는데 성공했다.
void CTRNetEventHandler::onRecvOpenSelectivePackageOK( int usedItemNum, const std::vector<RewardInfo> & rewardList)
{
	DBG_DEMO_OUTPUT(123, "%s - used item : %d, result size : %d", __FUNCTION__, usedItemNum, rewardList.size());

	//!< 보상 연출
	if(CTRMyRoomGoodsListDialog::getInstance().isVisible())
	{
		CTRMyRoomGoodsListDialog::getInstance().onRecvSelectivePackageRewardOK(true, rewardList);
	}
	else if(CTRShopGoodsListDialog::getInstance().isVisible())
	{
		CTRShopGoodsListDialog::getInstance().onRecvSelectivePackageRewardOK(true, rewardList);
	}
#ifdef _SHOP_RENEWAL_
	if (CTRShopManager::getInstance().GetShopDialog())
	{
		CTRShopManager::getInstance().GetShopDialog()->onRecvSelectivePackageRewardOK(true, rewardList);
	}
#endif

	//!< 아이템 갱신
	CTRRewardManager::getInstance().addReqestitemList(usedItemNum);
	CTRRewardManager::getInstance().getReward(rewardList, true);
}
///< 선택의 상자 사용하는데 실패했다.
void CTRNetEventHandler::onRecvOpenSelectivePackageFailed(const eShopFailed_REASON failedReason, int requsetUseItemNum, eServerResult eResult)
{
	DBG_DEMO_OUTPUT(123, "%s - eShopFailed_REASON : %d, eServerResult : %d", __FUNCTION__, failedReason, eResult);

	std::string strFailedMent = CTRShopBuyAllDialog::getInstance().getShopBuyFailedMent(failedReason);
	CTRShortTimeMessage::showMessage(strFailedMent);

	if(CTRMyRoomGoodsListDialog::getInstance().isVisible())
	{
		CTRMyRoomGoodsListDialog::getInstance().onRecvSelectivePackageRewardOK(false, std::vector<RewardInfo>());
	}
	else if(CTRShopGoodsListDialog::getInstance().isVisible())
	{
		CTRShopGoodsListDialog::getInstance().onRecvSelectivePackageRewardOK(false, std::vector<RewardInfo>());
	}
#ifdef _SHOP_RENEWAL_
	if (CTRShopManager::getInstance().GetShopDialog())
	{
		CTRShopManager::getInstance().GetShopDialog()->onRecvSelectivePackageRewardOK(false, std::vector<RewardInfo>());
	}
#endif
}
#endif

/// 복주머니를 사용하는데 성공했다.
void CTRNetEventHandler::onRecvMyRoomUseLuckyBagOK( int usedItemNum, const std::map<int, BYTE/*count*/> & resultLottoItems, BYTE iCount)
{
	if(!resultLottoItems.size())
	{
		CTRShortTimeMessage::showMessage(_STR(ERR_USE_LUCKY_BAG), 1.5f);
		return;
	}

	std::map<int, BYTE> resultLuckyBagItems = resultLottoItems;

	DBG_OUTPUT(123, "%s - size : %d", __FUNCTION__, resultLuckyBagItems.size());
	std::map<int, BYTE/*count*/>::iterator itr = resultLuckyBagItems.begin();
	while(itr != resultLuckyBagItems.end())
	{
		int iItemNum = itr->first;
		const CItemInfoNode * pItemInfo = CClientItemList::getInstance().getItemInfo(iItemNum);
		if(pItemInfo != NULL)
		{
			DBG_OUTPUT(123, "%s - Item : %s, %d", __FUNCTION__, pItemInfo->m_name.c_str(), itr->second);
		}
		else
		{
			DBG_OUTPUT(123, "%s - Invalid ItemNum : %d", __FUNCTION__, iItemNum);
		}

		itr++;
	}

	CTRLuckyBagDialog::getInstance().showDialog(resultLuckyBagItems, false, usedItemNum, iCount);

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_USE_ITEM, usedItemNum);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_USE_ITEM_COUNT);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 복주머니를 사용하는데 실패했다.
void CTRNetEventHandler::onRecvMyRoomUseLuckyBagFailed(int requsetUseItemNum, eServerResult eResult)
{
	if(eResult == eServerResult_USE_LUCKY_BAG_FAILED_ACK)
	{
		CTRShortTimeMessage::showMessage(_STR(ERR_USE_LUCKY_BAG), 1.5f);
		DBG_OUTPUT(60, "onRecvMyRoomUseLuckyBagFailed : ItemNum = %d", requsetUseItemNum);
	}
	if(eResult == eServerResult_USE_LUCKY_BAG_NO_ITEM)
	{
		CTRShortTimeMessage::showMessage(_STR(ERR_USE_LUCKY_BAG_NO_ITEM), 1.5f);
		DBG_OUTPUT(60, "onRecvMyRoomUseLuckyBagFailed : ItemNum = %d", requsetUseItemNum);
	}
	if(eResult == eServerResult_USE_LUCKY_BAG_NO_MATERIAL)
	{
		CTRShortTimeMessage::showMessage(_STR(ERR_USE_LUCKY_BAG_NO_MATERIAL), 1.5f);
		DBG_OUTPUT(60, "onRecvMyRoomUseLuckyBagFailed : ItemNum = %d", requsetUseItemNum);
	}
	if(eResult == eServerResult_USE_LUCKY_BAG_INVALID_TIME)
	{
		CTRShortTimeMessage::showMessage(_STR(ERR_USE_LUCKY_BAG_INVALID_TIME), 1.5f);
		DBG_OUTPUT(60, "onRecvMyRoomUseLuckyBagFailed : ItemNum = %d", requsetUseItemNum);
	}
	if (eResult == eServerResult_ALREADY_HAVE_LUCKY_BAG_ITEM)
	{
		CTRShortTimeMessage::showMessage(_STR(ERR_HAVEA_ITEM), 1.5f);
		DBG_OUTPUT(60, "onRecvMyRoomUseLuckyBagFailed : ItemNum = %d", requsetUseItemNum);
	}
}

/// 뽑기판의 정보를 가져오기 성공했다.
void CTRNetEventHandler::onRecvMyRoomGetLotteryStageInfoOK(const int lotteryNum, const std::vector <LotteryStateInfo> & myLotteryStageInfo)
{
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvMyRoomGetLotteryStageInfoOK(lotteryNum, myLotteryStageInfo);
}

/// 뽑기판의 정보를 가져오기 실패했다.
void CTRNetEventHandler::onRecvMyRoomGetLotteryStageInfoFailed(const int lotteryNum, eServerResult eResult)
{
	DBG_OUTPUT(60, "onRecvMyRoomGetLotteryStageInfoFailed : lotteryNum = %d", lotteryNum);

	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvMyRoomGetLotteryStageInfoFailed(lotteryNum, eResult);
}

/// 뽑기 아이템을 사용하는데 성공했다.
void CTRNetEventHandler::onRecvMyRoomUseLotteryOk(const int lotteryNum, eLotteryRewardType eRewardType, const int rewardValue)
{
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvMyRoomUseLotteryOk(lotteryNum, eRewardType, rewardValue);
}

/// 뽑기 아이템을 사용하는데 실패했다.
void CTRNetEventHandler::onRecvMyRoomUseLotteryFailed(const int lotteryNum, eServerResult eResult)
{
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvMyRoomUseLotteryFailed(lotteryNum, eResult);
}

/// 방 입장이 실패했다.
void CTRNetEventHandler::onRecvEnterRoomFailed(eEnterRoomResult enterRoomResult, const eRoomKind roomKind, const int numMaxPlayer, const int restrictTime)
{
#ifndef TR_RELEASE_PROJECT
	DBG_OUTPUT(60, "onRecvEnterRoomFailed enterRoomResult=[%d],roomKind=[%d], CurRoomKind=[%d]", (int)enterRoomResult, (int)roomKind, (int)CChannelRoomMode::getInstance().getCurRoomKind());
#endif	//TR_RELEASE_PROJECT

	string joinFailMsg;
	if(roomKind == eRoomKind_NORMAL_PARK)
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			CNetClientManager::getInstance().makeRoom("Park","",roomKind, PARK_ENTER_LIMIT_USER_NUM, NOT_TEAMMODE, true, eItemMode_OLD);
			DBG_OUTPUT(60, "onRecvEnterRoomFail_makePark");
		}
		return;
	}
	else if(isSportsChannel(roomKind))
	{
		const bool bCoupleLeague = CNetClientManager::getInstance().getServerSetting("sportsPlayCoupleLeague", "false") == "true";
		std::string roomNameSports = bCoupleLeague == true ? _STR(ROOMNAME_SPORTS_COUPLELEAGUE) : _STR(ROOMNAME_SPORTS); 

		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			// 운동회 채널일때 퀵조인 실패시 방을 새로 생성
			string maxNumText = CNetClientManager::getInstance().getServerSetting("SportsMaxUserNum","30");
			int numMaxPlayers = (BYTE)atoi(maxNumText.c_str());

#ifdef _SPORTS_JOBWAR
			eItemMode itemMode = eItemMode_NEW;
#else
			eItemMode itemMode = eItemMode_OLD;
#endif

			if(CLanguageFile::getInstance().isHongkong() || CLanguageFile::getInstance().isTaiwan())
			{
				itemMode = (eItemMode)(rand()%3);
			}			

#ifdef _SPORTS_JOBWAR
			CNetClientManager::getInstance().makeRoom(roomNameSports,"",roomKind, numMaxPlayers, false, true, itemMode, 0);
#else
			CNetClientManager::getInstance().makeRoom(roomNameSports,"",roomKind, numMaxPlayers, NOT_TEAMMODE, true, itemMode);
#endif
			
				
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_ROOM_LIMITED_SPORTSROOM_OUT), roomNameSports.c_str(), roomNameSports.c_str());
		}
	}
	else if(isOlympicChannel(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			CTREventLeageManager::getInstance().onMakeEventGameRoom();
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = _STR(FAILED_ENTER_ROOM_LIMITED_OLYMPICROOM_OUT);
		}
	}
#ifdef _CHAOS
	else if(isChaosChannel(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			EnterRoomInfo ChaosRoominfo = CNetClientManager::getInstance().getEnterRoomInfo();
			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_CHAOS), "", roomKind, 30, false, ChaosRoominfo.m_bSteppingMode, ChaosRoominfo.m_eItemMode, ChaosRoominfo.m_iChannelInfo);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format("<normal>%s</normal>", _STR(FAILED_ENTER_ROOM_LIMITED_CHAOSROOM_OUT));
		}
	}
#endif

	else if(isPieroOlympicChannel(roomKind))
	{	
		//! 방 입장 실패 ( 삐에로 올림픽 )
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			// 퀵조인 실패시 방을 새로 생성
			CTREventSportsManager::getInstance().onMakeEventGameRoom();
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = _STR(FAILED_ENTER_ROOM_LIMITED_LOVEBATTLE_OUT);
		}
	}
	else if(isLoveBattle2Channel(roomKind))
	{	
		//! 방 입장 실패 ( 러브 배틀2 )
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			// 퀵조인 실패시 방을 새로 생성
			CTREventSportsManager::getInstance().onMakeEventGameRoom();
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = _STR(FAILED_ENTER_ROOM_LIMITED_LOVEBATTLE_OUT);
		}
	}
	else if(isNewPieroOlympicChannel(roomKind))
	{
		//! 방 입장 실패 ( 뉴 삐에로 올림픽(카오스 3) )
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			// 퀵조인 실패시 방을 새로 생성
			CTREventSportsManager::getInstance().onMakeEventGameRoom();
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = _STR(FAILED_ENTER_ROOM_LIMITED_CHAOSROOM_OUT);
		}
	}
	else if (isGuildMatchPlayingRoom(roomKind))
	{
		if (enterRoomResult == eEnterRoomResult_FAILED_INVALID_MY_MATCHING_ROOM)
		{
			int iRoomServerNum;
			unsigned int hRoom;
			if (m_pNetPlay != NULL && m_pNetPlay->getGuildMatchManager()->getMyPartyRoomServerInfo(iRoomServerNum,hRoom))
			{
				eRoomKind changeRoomKind = eRoomKind_GUILDMATCH_PARTY;
				if ( isGuildMatchOfficial( roomKind ) )
				{
					changeRoomKind = eRoomKind_GUILDMATCH_PARTY_OFFICIAL;
				}
				else if ( isGuildMatchOccupationChannel_8Play( roomKind ) )
				{
					changeRoomKind = eRoomKind_GUILDMATCH_PARTY_OCCUPATION_8;
				}
				else if ( isGuildMatchOccupationChannel_16Play( roomKind ) )
				{
					changeRoomKind = eRoomKind_GUILDMATCH_PARTY_OCCUPATION_16;
				}

				DBG_DEMO_OUTPUT( "enterroom fail!! roomkind[%d]  changeroomkind[%d] ", roomKind, changeRoomKind );
				__int64 iPartyID = CNetClientManager::getInstance().getMyPartyID();
				CNetClientManager::getInstance().requestJoinRoomEx(iRoomServerNum,hRoom,changeRoomKind,"4321", iPartyID);

				CTRShortTimeMessage::showMessage(_STR(ERR_FARM_JOIN_MESSAGE_LEGACY_USER),2.5f);	

				return;
			}
		}
	}
#ifdef SMART_CHANNEL_SYSTEM
	else if (isSmartChannel(roomKind))
	{
		if (enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			if(SmartChannel * pChannelInfo = CTRNetPlayManager::getInstance().getSmartChannelInfo()->getSelectedModeInfo())
			{
				ROOM_TEAMINFO teamModeInfo = (pChannelInfo->m_bTeamPlayMode ? DEFAULT_TEAMMODE : NOT_TEAMMODE);
				CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_SMART),"",eRoomKind_SMART_CHANNEL, pChannelInfo->m_iMaxUserNum, teamModeInfo, pChannelInfo->m_bSteppingMode, pChannelInfo->m_eItemMode, pChannelInfo->m_iModeNum);
				return;
			}
			else
			{
				//선택된 채널이 없음..
				_ASSERTE(false);
			}
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_SMART_CHANNEL_NOT_IN_TIME)
		{
			CTRShortTimeMessage::showMessage(_STR(FAILED_NOT_OPEN_TIME), 2.5f);
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_SMART_CHANNEL_INVALID_MODE_NUM)
		{
			CTRShortTimeMessage::showMessage(_STR(FAILED_INVALID_MODE), 2.5f);
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_SMART_CHANNEL_LEVEL_LIMIT)
		{
			CTRShortTimeMessage::showMessage(_STR(FAILED_ENTER_ROOM_LIMITED_LEVEL), 2.5f);
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			string timeStr = CServerTime::getInstance().getStringToTimeText(restrictTime, 2, 4, 1);
			joinFailMsg = format(_STR(FAILED_ENTER_PENALTY_MENT), timeStr.c_str());
		}
		else
		{
			_ASSERTE(false);
		}
	}
#endif

	else if(isTicketScrambleChannel(roomKind))
	{	
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			// 티켓쟁탈전 채널일때 퀵조인 실패시 방을 새로 생성
			string maxNumText = CNetClientManager::getInstance().getServerSetting("SportsMaxUserNum","30");
			int numMaxPlayers = (BYTE)atoi(maxNumText.c_str());
			CNetClientManager::getInstance().makeRoom(_STR(MSG_TICKET_SCRAMBLE),"",roomKind, numMaxPlayers, NOT_TEAMMODE, true, eItemMode_OLD);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = _STR(FAILED_ENTER_ROOM_LIMITED_TICKETROOM_OUT);
		}
	}
#ifdef _RUNNING_MAN2
	else if(isRunningMan2Channel(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			eItemMode itemMode = eItemMode_OLD;

#ifdef CONTENTS_ITEMMODE_2
			itemMode = eItemMode_NEW;
#endif
			// 런닝맨2 채널일때 퀵조인 실패시 방을 새로 생성
			CNetClientManager::getInstance().makeRoom(_STR(MSG_RUNNING_MAN2),"",roomKind, 8, false, true, itemMode);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = _STR(FAILED_ENTER_ROOM_LIMITED_TICKETROOM_OUT);
		}
	}

#endif

#ifdef COUNTERATTACK_OF_ANUBIS
	else if(isAnubisChannel(roomKind))
	{
		CChannelRoomMode & ChennelRoommode = CChannelRoomMode::getInstance();
		
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			const int iCurGateUniqueNum = CTRAnubisManager::getInstance().getCurGateUniqueNum();
			// 아누비스 채널일때 퀵조인 실패시 방을 새로 생성
			CNetClientManager::getInstance().makeRoom(_STR(COUNTERATTACK_OF_ANUBIS_NAME),"",roomKind, 8, false, false, eItemMode_OFF, iCurGateUniqueNum);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL), _STR(ANUBIS), _STR(ANUBIS));
		}

		// 아누비스 방을 만들 수 없는 상태 일 경우에는 현재 채널 상태를 아누비스 채널에서 일반 모드 채널로 바꿔준다.
		if (isAnubisEasyChannelMode(roomKind))
		{
			ChennelRoommode.setChannelMode(CChannelRoomMode::CHANNELMODE_EASY);
			ChennelRoommode.setRoomMode(CChannelRoomMode::ROOMMODE_NORMAL);
		}
		else if (isAnubisNormalChannelMode(roomKind))
		{
			ChennelRoommode.setChannelMode(CChannelRoomMode::CHANNELMODE_NORMAL);
			ChennelRoommode.setRoomMode(CChannelRoomMode::ROOMMODE_NORMAL);
		}
		else if (isAnubisNewbieonlyChannelMode(roomKind))
		{
			ChennelRoommode.setChannelMode(CChannelRoomMode::CHANNELMODE_NEWBIEONLY);
			ChennelRoommode.setRoomMode(CChannelRoomMode::ROOMMODE_NORMAL);
		}
	}
#endif

	// 아누비스 원정대 모드
	else if(isAnubisExpeditionChannel(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			// 아누비스 채널일때 퀵조인 실패시 방을 새로 생성
			const int iMapNum = CTRAnubisExpeditionManager::getInstance().getMapNum();
			CNetClientManager::getInstance().makeRoom(_STR(ANUBIS),"",roomKind, 8, NOT_TEAMMODE, false, eItemMode_OFF, iMapNum);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL), _STR(ANUBIS), _STR(ANUBIS));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_UNITY);
	}

	// 어썰트 협동 모드
	else if (isAssaultCorunMode(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			CNetClientManager & rNetClientManager = CNetClientManager::getInstance();
			const int iJourneyToTheWestMapNum = rNetClientManager.getEnterRoomInfo().m_numMap;

			rNetClientManager.makeRoom(_STR(JOURNEY_TO_THE_WEST),"",roomKind, 8, NOT_TEAMMODE, false, eItemMode_OFF, iJourneyToTheWestMapNum);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_ROOM_PENALTY), _STR(BULLDEVILKING_TITLE), _STR(BULLDEVILKING_TITLE));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_ASSAULT_CORUN_MODE);
	}

	// 서유기 채널 맵
	else if (isJourneyToTheWestMode(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			CNetClientManager & rNetClientManager	= CNetClientManager::getInstance();
			const int iJourneyToTheWestMapNum		= rNetClientManager.getEnterRoomInfo().m_numMap;
			const bool bSteppingMode				= rNetClientManager.getEnterRoomInfo().m_bSteppingMode;
			const eItemMode eJWItemMode				= rNetClientManager.getEnterRoomInfo().m_eItemMode;

			// 서유기 8인
			if (isJourneyToTheWestNormalMode(roomKind))
			{
				rNetClientManager.makeRoom(_STR(JOURNEY_TO_THE_WEST),"",roomKind, 8, NOT_TEAMMODE, bSteppingMode, eJWItemMode, iJourneyToTheWestMapNum);
				return;
			}

			// 서유기 30 인
			else if (isJourneyToTheWestCrowdMode(roomKind))
			{
				rNetClientManager.makeRoom(_STR(JOURNEY_TO_THE_WEST),"",roomKind, 30, NOT_TEAMMODE, bSteppingMode, eJWItemMode, iJourneyToTheWestMapNum);
				return;
			}
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL), _STR(JOURNEY_TO_THE_WEST), _STR(JOURNEY_TO_THE_WEST));
		}
		
		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_JOURNEY_TO_THE_WEST_NORMAL);
	}
#ifdef _HERO_WAR
	else if (isHeroWarChannel(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const int iMapNum = CNetClientManager::getInstance().getEnterRoomInfo().m_numMap;
			const eItemMode ItemMode = CNetClientManager::getInstance().getEnterRoomInfo().m_eItemMode;
			const int iMaxUser = numMaxPlayer;
			
			CNetClientManager::getInstance().makeRoom(_STR(MSG_HERO_WAR), "", roomKind, iMaxUser, true, false, ItemMode, iMapNum);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL), _STR(MSG_HERO_WAR), _STR(MSG_HERO_WAR));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_HERO_WAR);
	}
#endif

#ifdef _ASSAULT_RAID
	else if (isRaidChannel(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const int iRaidMapNum   = CNetClientManager::getInstance().getEnterRoomInfo().m_numMap;
			eItemMode eRaidItemMode = CNetClientManager::getInstance().getEnterRoomInfo().m_eItemMode;

			CNetClientManager::getInstance().makeRoom(format("%s %s", _STR(NAME_RAID),_STR(CHANNEL)), "", roomKind, 20, false, false, eRaidItemMode, iRaidMapNum);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL), _STR(NAME_RAID), _STR(NAME_RAID));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_RAID);
	}
#endif

#ifdef _WINTER_FESTIVAL
	else if(isWinterFestivalMode(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;

			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_WINTER_FESTIVAL), "", roomKind, iMaxUser,
														enterRoomInfo.m_sTeamPlayMode,enterRoomInfo.m_bSteppingMode,
														enterRoomInfo.m_eItemMode,enterRoomInfo.m_numMap);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_WINTER_FESTIVAL), _STR(ITEM_TIME_MINUTE_FIVE), _STR(CHANNEL_WINTER_FESTIVAL));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_WINTER_FESTIVAL);
	}
#endif

#ifdef _HORROR_PARK_CHANNEL
	else if(isHorrorParkMode(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;

			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_NAME_HORROR_PARK), "", roomKind, iMaxUser,
				enterRoomInfo.m_sTeamPlayMode,enterRoomInfo.m_bSteppingMode,
				enterRoomInfo.m_eItemMode,enterRoomInfo.m_numMap);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_NAME_HORROR_PARK), _STR(ITEM_TIME_MINUTE_FIVE), _STR(CHANNEL_NAME_HORROR_PARK));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_HORROR_PARK);
	}
#endif

#ifdef _GENDER_WAR
	else if(isGenderWar(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;

			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_NAME_GENDER_WAR), "", roomKind, iMaxUser,
				enterRoomInfo.m_sTeamPlayMode,enterRoomInfo.m_bSteppingMode,
				enterRoomInfo.m_eItemMode,enterRoomInfo.m_numMap);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_NAME_GENDER_WAR), _STR(ITEM_TIME_MINUTE_FIVE), _STR(CHANNEL_NAME_GENDER_WAR));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_GENDER_WAR);
	}
#endif

#ifdef _SNOW_QUEEN_CHANNEL
	else if(isSnowQueenMode(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;

			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_NAME_SNOW_QUEEN), "", roomKind, iMaxUser,
				enterRoomInfo.m_sTeamPlayMode,enterRoomInfo.m_bSteppingMode,
				enterRoomInfo.m_eItemMode,enterRoomInfo.m_numMap);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_NAME_SNOW_QUEEN), _STR(ITEM_TIME_MINUTE_FIVE), _STR(CHANNEL_NAME_SNOW_QUEEN));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_SNOW_QUEEN);
	}
#endif

#ifdef _KNIGHT_FLOWERS_
	else if(isKnightFlowersMode(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;

			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_NAME_KNIGHT_FLOWERS), "", roomKind, iMaxUser,
				enterRoomInfo.m_sTeamPlayMode,enterRoomInfo.m_bSteppingMode,
				enterRoomInfo.m_eItemMode,enterRoomInfo.m_numMap);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_NAME_KNIGHT_FLOWERS), _STR(ITEM_TIME_MINUTE_ONE), _STR(CHANNEL_NAME_KNIGHT_FLOWERS));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_KNIGHT_FLOWERS);
	}
#endif

#ifdef _CHAOS_ZERO_
	else if(isChaosZeroChannel(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;

			CNetClientManager::getInstance().makeRoom(_STR(MSG_CHAOS_GENERATION), "", roomKind, iMaxUser,
				enterRoomInfo.m_sTeamPlayMode,enterRoomInfo.m_bSteppingMode,
				enterRoomInfo.m_eItemMode,enterRoomInfo.m_numMap);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(MSG_CHAOS_GENERATION), _STR(ITEM_TIME_MINUTE_ONE), _STR(MSG_CHAOS_GENERATION));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_CHAOS_ZERO);
	}
#endif

#ifdef _RUNLYMPIC
	else if(isRunlympic_formula(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;

			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_RUNLYMPIC), "", roomKind, iMaxUser,
				enterRoomInfo.m_sTeamPlayMode,enterRoomInfo.m_bSteppingMode,
				enterRoomInfo.m_eItemMode,enterRoomInfo.m_numMap);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_RUNLYMPIC), _STR(ITEM_TIME_MINUTE_ONE), _STR(CHANNEL_RUNLYMPIC));
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_CAN_NOT_ENTER_ROOM)
		{
			joinFailMsg = format(_STR(FAILED_NOT_JOIN_WITH_IN_TARGET_CHANNEL), _STR(CHANNEL_RUNLYMPIC));
			CTRShortTimeMessage::showMessage(joinFailMsg);
		}

		if (isTalesAcademyRunlympic(roomKind))
			CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_TALES_ACADEMY); // 런림픽이 이벤트채널에 들어갈때마다 변경 필요
		else if (isTalesFrontierRunlympic(roomKind))
			CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_TALES_FRONTIER);
	}
#endif

#ifdef _TALES_ACADEMY_
	else if(isTalesAcademyChannel(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;

			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_NAME_TALES_ACADEMY), "", roomKind, iMaxUser,
				enterRoomInfo.m_sTeamPlayMode,enterRoomInfo.m_bSteppingMode,
				enterRoomInfo.m_eItemMode,enterRoomInfo.m_numMap);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_NAME_TALES_ACADEMY), _STR(ITEM_TIME_MINUTE_ONE), _STR(CHANNEL_NAME_TALES_ACADEMY));
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_CAN_NOT_ENTER_ROOM)
		{
			joinFailMsg = format(_STR(FAILED_NOT_JOIN_WITH_IN_TARGET_CHANNEL), _STR(CHANNEL_NAME_TALES_ACADEMY));
			CTRShortTimeMessage::showMessage(joinFailMsg);
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_TALES_ACADEMY);
	}
#endif

#ifdef _TALES_FRONTIER_
	else if (isTalesFrontierChannel(roomKind))
	{
		if (enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;

			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_NAME_TALES_FRONTIER), "", roomKind, iMaxUser,
				enterRoomInfo.m_sTeamPlayMode, enterRoomInfo.m_bSteppingMode,
				enterRoomInfo.m_eItemMode, enterRoomInfo.m_numMap);
			return;
		}
		else if (enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_NAME_TALES_FRONTIER), _STR(ITEM_TIME_MINUTE_ONE), _STR(CHANNEL_NAME_TALES_FRONTIER));
		}
		else if (enterRoomResult == eEnterRoomResult_FAILED_CAN_NOT_ENTER_ROOM)
		{
			joinFailMsg = format(_STR(FAILED_NOT_JOIN_WITH_IN_TARGET_CHANNEL), _STR(CHANNEL_NAME_TALES_FRONTIER));
			CTRShortTimeMessage::showMessage(joinFailMsg);
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_TALES_FRONTIER);
	}
#endif

#ifdef _WINTER_CHANNEL_2019_
	else if(isWinterChannel2019(roomKind)){
	if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN){
		const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
		const int iMaxUser = numMaxPlayer;

		CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_NAME_WINTER_2019), "", roomKind,iMaxUser,
			enterRoomInfo.m_sTeamPlayMode,enterRoomInfo.m_bSteppingMode,
			enterRoomInfo.m_eItemMode,enterRoomInfo.m_numMap);
		return;
	} else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER){
		joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_NAME_WINTER_2019), _STR(ITEM_TIME_MINUTE_ONE), _STR(CHANNEL_NAME_WINTER_2019));
	} else if(enterRoomResult == eEnterRoomResult_FAILED_CAN_NOT_ENTER_ROOM){
		joinFailMsg = format(_STR(FAILED_NOT_JOIN_WITH_IN_TARGET_CHANNEL), _STR(CHANNEL_NAME_WINTER_2019));
		CTRShortTimeMessage::showMessage(joinFailMsg);
	}

	CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_WINTER_CHANNEL_2019);
	}
#endif

#ifdef _SPRING_CHANNEL_2020_
	else if (isSpringChannel2020(roomKind)) {
	if (enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN) {
		const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
		const int iMaxUser = numMaxPlayer;

		CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_NAME_SPRING_2020), "", roomKind, iMaxUser,
			enterRoomInfo.m_sTeamPlayMode, enterRoomInfo.m_bSteppingMode,
			enterRoomInfo.m_eItemMode, enterRoomInfo.m_numMap);
		return;
	}
	else if (enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER) {
		joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_NAME_SPRING_2020), _STR(ITEM_TIME_MINUTE_ONE), _STR(CHANNEL_NAME_SPRING_2020));
	}
	else if (enterRoomResult == eEnterRoomResult_FAILED_CAN_NOT_ENTER_ROOM) {
		joinFailMsg = format(_STR(FAILED_NOT_JOIN_WITH_IN_TARGET_CHANNEL), _STR(CHANNEL_NAME_SPRING_2020));
		CTRShortTimeMessage::showMessage(joinFailMsg);
	}

	CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_SPRING_CHANNEL_2020);
	}
#endif

#ifdef _OFFICIAL_COMPETITION_CHANNEL
	else if (isOfficialCompetitionChannel(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;

			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_COMPETITION_OFFICAL), "", roomKind, iMaxUser,
				enterRoomInfo.m_sTeamPlayMode,enterRoomInfo.m_bSteppingMode,
				enterRoomInfo.m_eItemMode,enterRoomInfo.m_numMap);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_COMPETITION_OFFICAL), _STR(ITEM_TIME_MINUTE_FIVE), _STR(CHANNEL_COMPETITION_OFFICAL));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_OFFICIAL_COMPETITION);
	}
#endif

#ifdef _DEV_FESTIVAL_
	else if(isDevFestivalChannel(roomKind))
	{
		if(enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{	
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;
			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_NAME_DEV_FESTIVAL), "", roomKind, iMaxUser,
				enterRoomInfo.m_sTeamPlayMode,enterRoomInfo.m_bSteppingMode,
				enterRoomInfo.m_eItemMode,enterRoomInfo.m_numMap);
			return;
		}
		else if(enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_NAME_DEV_FESTIVAL), _STR(ITEM_TIME_MINUTE_ONE), _STR(CHANNEL_NAME_DEV_FESTIVAL));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_DEV_FESTIVAL);
	}
#endif

#ifdef _THANK_OFFERING_
	else if (isThankOfferingChannel(roomKind))
	{
		if (enterRoomResult == eEnterRoomResult_FAILED_QUICK_JOIN)
		{
			const EnterRoomInfo enterRoomInfo = CNetClientManager::getInstance().getEnterRoomInfo();
			const int iMaxUser = numMaxPlayer;
			CNetClientManager::getInstance().makeRoom(_STR(CHANNEL_NAME_THANK_OFFERING_LEAGUE), "", roomKind, iMaxUser,
				enterRoomInfo.m_sTeamPlayMode, enterRoomInfo.m_bSteppingMode,
				enterRoomInfo.m_eItemMode, enterRoomInfo.m_numMap);
			return;
		}
		else if (enterRoomResult == eEnterRoomResult_FAILED_LIMITED_USER)
		{
			joinFailMsg = format(_STR(FAILED_ENTER_CHANNEL2), _STR(CHANNEL_NAME_THANK_OFFERING_LEAGUE), _STR(ITEM_TIME_MINUTE_ONE), _STR(CHANNEL_NAME_THANK_OFFERING_LEAGUE));
		}

		CChannelRoomMode::getInstance().setChannelMode(CChannelRoomMode::CHANNELMODE_THANK_OFFERING);
	}
#endif

	CTRNetPlayManager::getInstance().openLobby();
	CTRLobbyUI::getInstance().setJoinRoom(false);

	if(isFarmMode(roomKind))
	{		
		if(m_pNetPlay) m_pNetPlay->openFarmLobbyUI();
		CTRFarmLobbyUIDlg::getInstance().setJoinRoom(false);		
	}
	else
	{
		CTRUserInterface::openUISingleton<CTRLobbyUI>();
		CTRLobbyUI::getInstance().setJoinRoom(false);

		//! 내팜안에서 내팜으로 이동시 roomKind가 팜으로 안넘어 올때를 대비
		CTRFarmLobbyUIDlg::getInstance().setJoinRoom(false);		
	}

	switch ( enterRoomResult )
	{
	case eEnterRoomResult_FAILED_NO_ROOM:				///< 그런 방을 찾을 수 없다.
		DBG_OUTPUT(60, "onRecvEnterRoomFail_NoRoom");
		CTRShortTimeMessage::showMessage(_STR(FAILED_ENTER_ROOM_DOES_NOT_EXISTS));
		break;
	case eEnterRoomResult_FAILED_FULL_ROOM:				///< 인원이 다 찬 방이다.
		DBG_OUTPUT(60, "onRecvEnterRoomFail_FullRoom");
		CTRShortTimeMessage::showMessage(_STR(FAILED_ENTER_ROOM_IS_FULL));
		break;
	case eEnterRoomResult_FAILED_ALREADY_START_GAME:	///< 이미 게임이 시작되었다.
		DBG_OUTPUT(60, "onRecvConnectAlreadyStartedGame");
		CTRShortTimeMessage::showMessage(_STR(FAILED_ENTER_ROOM_ALREADY_GAME_STARTED));
		break;
	case eEnterRoomResult_FAILED_KICKED_PLAYER:			///< 강퇴된 플레이어이다.
		DBG_OUTPUT(60, "onRecvEnterRoomFail_KickedPlayer");
		CTRShortTimeMessage::showMessage(_STR(FAILED_ENTER_HAVE_BEEN_KICKED));
		break;
	case eEnterRoomResult_FAILED_DIFF_PASSWORD:			///< 암호가 틀렸다.
		if(isFarmMode(roomKind)) CTRFarmLobbyUIDlg::getInstance().onRecvEnterRoomFailedDiffPassword();
		else CTRLobbyUI::getInstance().onRecvEnterRoomFailedDiffPassword();
		break;
	case eEnterRoomResult_FAILED_SAME_NICKNAME:			///< 이미 같은 닉네임을 쓰는 사람이 있다.
		_ASSERTE(false);
		CTRShortTimeMessage::showMessage(_STR(FAILED_ENTER_ROOM_DUPLICATE_NICKNAME));
		break;
	case eEnterRoomResult_FAILED_ALREADY_OBSERVER:		///< 이 방에는 이미 옵져버가 있다.
		CTRShortTimeMessage::showMessage(_STR(FAILED_ENTER_ROOM_DUPLICATE_OBSERVER));
		break;
	case eEnterRoomResult_FAILED_NO_TICKET:				///< 티켓 채널인데 티켓이 없다.
		CTRShortTimeMessage::showMessage(_STR(INFORMATION_TICKET_ZERO));
		break;
	case eEnterRoomResult_FAILED_QUICK_JOIN:				///< 빠른 입장에 실패했다.
		DBG_OUTPUT(60, "onRecvQuickJoinFailed");
		CTRShortTimeMessage::showMessage(_STR(QUICK_JOIN_FAILED));
		break;
	case eEnterRoomResult_FAILED_QUICK_JOIN_RETRY:
		DBG_OUTPUT(60, "onRecvQuickJoinRetryFailed");
		CTRShortTimeMessage::showMessage(_STR(QUICK_JOIN_FAILED));
		break;
	case eEnterRoomResult_FAILED_LIMITED_LEVEL:         /// 레벨에 맞지 않은 채널에서 방참여를 했을 때
		CTRShortTimeMessage::showMessage(_STR(FAILED_ENTER_ROOM_LIMITED_LEVEL));        
		break;
	case eEnterRoomResult_FAILED_NOT_SPORTS_TIME:          /// 운동회 채널에서 운동회 시간외에 방만들때 처리
		{
			if(isAnubisExpeditionChannel(roomKind))
				CTRShortTimeMessage::showMessage(_STR(FAILED_ROOM_NOT_ANUBIS_SPORTS_TIME));
			else
				CTRShortTimeMessage::showMessage(_STR(FAILED_ROOM_NOT_SPORTS_TIME));
		}
		break;
	case eEnterRoomResult_FAILED_SPORTS_PLAY_TIME_LIMIT: ///< 플레이 시간 제한으로 대운동회에 입장할 수 없습니다.
		COkDialogEx::getInstance().showDialog(_STR(MSG_CANNOT_USE_OUT_OF_TIME));
		break;
	case eEnterRoomResult_FAILED_SPORTS_PLAY_COUNT_LIMIT:///< 플레이 횟수 제한으로 대운동회에 입장할 수 없습니다.:
		COkDialogEx::getInstance().showDialog(_STR(FAILED_ANUBIS_JOIN_ERROR_JOIN_COUNT));
		break;
	case eEnterRoomResult_FAILED_LIMITED_USER:          /// 운동회 방에서 강제 종료로 3분간 입장이 제한	(카오스 채널은 30분간)
		COkDialogEx::getInstance().showDialog(joinFailMsg);
		break;
	case eEnterRoomResult_FAILED_NEED_GUILD_JOIN:		///< 길드에 가입되어 있지 않아서 입장할 수 없다.
		CTRShortTimeMessage::showMessage(_STR(MGS_NEED_JOIN_GUILD_TO_ENTERANCE));
		break;
	case eEnterRoomResult_FAILED_FARM_EXPIRED_PERIOD:	///< 팜 사용기간이 만료되어 입장할 수 없다.
		CTRShortTimeMessage::showMessage(_STR(MSG_USE_FARM_PERIOD_END));
		break;
	case eEnterRoomResult_FAILED_FARM_STRANGE_DATA:	///< 팜 구성정보가 유효하지 않아 입장할 수 없다.
		CTRShortTimeMessage::showMessage(_STR(MSG_USE_FARM_PERIOD_END));
		break;
	case eEnterRoomResult_FAILED_LOCKED_FARM_ROOM:		///< 팜이 정보 수정을 위해 잠금 상태에 있어 입장할 수 없다. 
		CTRShortTimeMessage::showMessage(_STR(FAILED_ENTER_FARM_ONLOCK_SAVING));
		break;
	case eEnterRoomResult_FAILED_NOT_WAR_TIME:			///< 카오스 채널 전쟁 시간이 아니다
		CTRShortTimeMessage::showMessage(_STR(FAILED_ENTER_CHAOS_WAR_NO_TIME));
		break;
	case eEnterRoomResult_FAILED_NOT_JOINED_PARTY:		///< 카오스 진영에 가입하지 않았다.
		CTRShortTimeMessage::showMessage(_STR(FAILED_CHAOS_NOT_JOINED));
		break;
	case eEnterRoomResult_FAILED_LEGACY_USER:		
		CTRShortTimeMessage::showMessage(_STR(ERR_FARM_JOIN_MESSAGE_LEGACY_USER),2.5f);					
		break;
	case eEnterRoomResult_FAILED_NOT_SAME_GUILD:
		{
			COkDialogEx::getInstance().showDialog(_STR(MSG_NO_ENTER_GUILD_ROOM_NOT_GUILDMEMBER));
		}

	case eEnterRoomResult_FAILED_PARTY_IS_FULL:
		CTRShortTimeMessage::showMessage(_STR(FAILED_MESSAGE_PARTY_IS_FULL),2.5f);
		break;
	case eEnterRoomResult_FAILED_NOT_MY_GUILD_PARTY:
		CTRShortTimeMessage::showMessage(_STR(MSG_NO_ENTER_GUILD_ROOM_NOT_GUILDMEMBER),2.5f);
		break;
	case eEnterRoomResult_FAILED_CAN_NOT_SETTING_MY_PARTY_INFO:
	case eEnterRoomResult_FAILED_NOT_FOUND_GUILDMATCH_PARTY_ROOM:
	case eEnterRoomResult_FAILED_NOT_FOUND_OTHER_PARTY_INFO:
	case eEnterRoomResult_FAILED_NOT_FOUND_ROOMSERVER_REMAKE:
	case eEnterRoomResult_FAILED_ROOM_KIND_DIFFERENT:
		COkDialogEx::getInstance().showDialog(format("%s,%s=[%d]",_STR(FAILED_MESSAGE_NOT_FOUND_GUILDMATCH_PARTY_ROOM),_STR(ERROR_UI_TITLE),(int)enterRoomResult));
		break;
	case eEnterRoomResult_FAILED_NOT_FOUND_ITEM:
		CTRShortTimeMessage::showMessage(_STR(MSG_FRIEND_ANUBIS_JOIN_ITEM_NO_EXIST), 2.5f);
		break;

	case eEnterRoomResult_FAILED_NOT_COMPETITION_EVENT_TIME:
		CTRShortTimeMessage::showMessage(_STR(FAILED_ROOM_NOT_SPORTS_TIME));
		break;

	case eEnterRoomResult_FAILED_ALREADY_IN_ROOM:			///< 이미 방에 들어가있다.
		DBG_OUTPUT(60, "onRecvEnterRoomFail_ALREADY_IN_ROOM");
		break;
	case eEnterRoomResult_FAILED_NOT_FOUND_AGENT_SERVER:	///< 에이전트 서버를 찾을 수가 없다.
		DBG_OUTPUT(60, "onRecvEnterRoomFail_NOT_FOUND_AGENT_SERVER");
		break;
	case eEnterRoomResult_FAILED_CAN_NOT_ENTER_ROOM:		///< 들어갈 수 없는 방이다.
		DBG_OUTPUT(60, "onRecvEnterRoomFail_CAN_NOT_ENTER_ROOM");
		break;
	case eEnterRoomResult_FAILED_QUICK_JOIN_OPTION_ERROR:	///< 퀵 조인 옵션이 잘못 됨
		DBG_OUTPUT(60, "onRecvEnterRoomFail_QUICK_JOIN_OPTION_ERROR");
		break;
	case eEnterRoomResult_FAILED_NOT_JOIN_ITEM_ERROR:
		CTRShortTimeMessage::showMessage(_STR(MSG_FRIEND_ANUBIS_JOIN_ITEM_NO_EXIST));
		break;
	case eEnterRoomResult_FAILED_LIMITED_LICENSE:
		CTRShortTimeMessage::showMessage(_STR(MSG_NO_LICENSE));
		break;
	case eEnterRoomResult_FAILED_NOT_ASSAULT_RAID_TIME:
		CTRShortTimeMessage::showMessage(_STR(FAILED_ROOM_NOT_SPORTS_TIME));
		break;
	case eEnterRoomResult_FAILED_INVALID_CHATTING_FARM_SUBJECT:	///< 유효하지 않는 채팅팜 제목 입니다.
		CTRShortTimeMessage::showMessage(_STR(ERR_CANNOT_USE_CHAR));
		break;
	case eEnterRoomResult_FAILED_NOT_PROGRESS_MAP:
		CTRShortTimeMessage::showMessage(_STR(MSG_PLAY_MATCH_GAME_MAP_NONE));
		break;
	case eEnterRoomResult_FAILED_NOT_COUPLE_FOR_SPORTS:
		// 커플인 유저만 참가 가능한 채널입니다.
		CTRShortTimeMessage::showMessage(_STR(MENT_COUPLE_LEAGUE_FAIL_1));
		break;
	case eEnterRoomResult_FAILED_CLOSE_GUILDMATCH_ROOM:
		CTRShortTimeMessage::showMessage(_STR(MSG_GUILD_MATCH_FAILED_CLOSE_GUILDMATCH_ROOM));
		break;
	
	case eEnterRoomResult_FAILED_JUROR_RESTRICTED:
		CTRShortTimeMessage::showMessage(_STR(TRIAL_CANNOT_JOIN_AS_JUROR));
		break;

	case eEnterRoomResult_FAILED_COURT_JUROR_QUICK_JOIN:
		CTRShortTimeMessage::showMessage(_STR(TRIAL_NO_TRIAL_WAITING_ROOM));
		break;

	case eEnterRoomResult_FAILED_COURT_AUDIENCE_QUICK_JOIN:
		CTRShortTimeMessage::showMessage(_STR(TRIAL_NO_TRIAL_WAITING_AND_ONGOING_ROOM));
		break;

	case eEnterRoomResult_FAILED_COURT_CANNOT_USE_WITH_PUNISHMENT:
		CTRShortTimeMessage::showMessage(_STR(USER_REPORT_CANNOT_USE));
		break;
	case eEnterRoomResult_FAILED_SUMMER_ISLAND_NOCOUNT:
		CTRShortTimeMessage::showMessage(_STR(MESSAGE_ENTER_NOT_ENOUGH_POINT));
		break;

	default:
		_ASSERTE(false);
		DBG_OUTPUT(60, "recv unknown room enter failed...");
	}
}


// 나의 playerindex 를 받았다.
void CTRNetEventHandler::onRecvMyPlayerIndex(int iPlayerIndex)
{
	DBG_OUTPUT(60, "onRecvMyPlayerIndex: %d", iPlayerIndex);

	m_pNetPlay->onRecvMyPlayerIndex(iPlayerIndex);

	CTRUserInterface::getInstance().onUpdateRoomUsers();
}


/// 당신이 새로운 방장이다.
void CTRNetEventHandler::onRecvSetMaster(unsigned int iPlayerIndex)
{
	DBG_OUTPUT(60, "onRecvSetMaster: iPlayerIndex=%d", iPlayerIndex);

	m_pNetPlay->onRecvSetMaster(iPlayerIndex);

	CTRUserInterface::getInstance().onUpdateRoomUsers();
}


/// 현재 방의 특정 유저가 나에게 보내는 메시지를 받았다.
void CTRNetEventHandler::onRecvForwardToRoomUser(const size_t from,const CPacketChunk & data)
{
	if (data.empty()) return;

	if (m_pNetPlay == NULL)return;

	if (m_pNetEventListener != NULL)
	{
		m_pNetEventListener->onRecvForwardToRoomUser(from,data);
	}

}


/// 현재 방의 모든 유저들에게 보내는 메시지를 받았다.
void CTRNetEventHandler::onRecvForwardToAllRoomUser(const CPacketChunk & v)
{
	if (v.empty()) return;

	const NETWORK_PLAY_EVENT_TYPE iEventType = (NETWORK_PLAY_EVENT_TYPE)v[0];

	switch(iEventType)
	{
	case NETWORK_PLAY_EVENT_CHARACTER_ATTACKED_BY:
		if (sizeof(CCharacterAttackedByEventData) == v.size())
		{
			CCharacterAttackedByEventData * pEventData = (CCharacterAttackedByEventData *)&v[0];
			CTRGameTraceCameraUI::getInstance().showTraceCamera(pEventData->m_attackerPlayerID, pEventData->m_playerID, pEventData->m_fBonusDashGauge);
			DBG_OUTPUT("NETWORK_PLAY_EVENT_CHARACTER_ATTACKED_BY : attacker:%d, target:%d ", pEventData->m_attackerPlayerID._getIdentifierValue(), pEventData->m_playerID._getIdentifierValue());
		}
		else
		{
			_ASSERTE(false);
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHARACTER_ATTACKED_BY: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_CHARACTER_DEFENCE_BY:
		if (sizeof(CCharacterDefenceByEventData) == v.size())
		{
			//방어 했다.
			CGameManager::getInstance().onRecvCharacterDefenceBy((CCharacterDefenceByEventData *)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHARACTER_DEFENCE_BY: incorrect struct size!");
		}
		break;

	case NETWORK_PLAY_EVENT_APPEARANCE_BLOCK_GENERATE:
		if (sizeof(CAppearanceBlockGenerateEventData) == v.size())
		{
			CGameManager::getInstance().onRecvAppearanceBlockGenerate((CAppearanceBlockGenerateEventData *)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_APPEARANCE_BLOCK_GENERATE: incorrect struct size!");
		}
		break;

	case NETWORK_PLAY_EVENT_CARD_SOLDIER_FALL:
		if (sizeof(CCardSoldierFallEventData) == v.size())
		{
			CGameManager::getInstance().onRecvCardSoldierFall((CCardSoldierFallEventData *)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CARD_SOLDIER_FALL: incorrect struct size!");
		}
		break;

	case NETWORK_PLAY_EVENT_CARD_SOLDIER_ATTACK:
		if (sizeof(CCardSoldierAttackEventData) == v.size())
		{
			CGameManager::getInstance().onRecvCardSoldierAttack((CCardSoldierAttackEventData *)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CARD_SOLDIER_ATTACK: incorrect struct size!");
		}
		break;

	case NETWORK_PLAY_EVENT_STEPPED_DOKEBI_FALL:
		if (sizeof(CSteppedDokebiFallEventData) == v.size())
		{
			CGameManager::getInstance().onRecvSteppedDokebiFall((CSteppedDokebiFallEventData *)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_STEPPED_DOKEBI_FALL: incorrect struct size!");
		}
		break;

	case NETWORK_PLAY_EVENT_STEPPED_DOKEBI_ATTACK:
		if (sizeof(CSteppedDokebiAttackEventData) == v.size())
		{
			CGameManager::getInstance().onRecvSteppedDokebiAttack((CSteppedDokebiAttackEventData *)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_STEPPED_DOKEBI_ATTACK: incorrect struct size!");
		}
		break;

	case NETWORK_PLAY_EVENT_GET_INTO_CARRY_CONTAINER:
		if (sizeof(CGetIntoCarryContainerEventData) == v.size())
		{
			CGameManager::getInstance().onRecvGetIntoCarryContainer((CGetIntoCarryContainerEventData *)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_GET_INTO_CARRY_CONTAINER: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_CONTACT_ELECTRIC_SHOT_BAR:
		if (sizeof(CContactElectricShotBarEventData) == v.size())
		{
			CGameManager::getInstance().onRecvContactElectricShotBar((CContactElectricShotBarEventData *)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CONTACT_ELECTRIC_SHOT_BAR: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_CONTACT_DAMAGE_AREA_BY_CONTANER:
		if (sizeof(CContactDamageAreaByContainer) == v.size())
		{
			CGameManager::getInstance().onRecvContactDamageAreaByContainer((CContactDamageAreaByContainer *)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CONTACT_DAMAGE_AREA_BY_CONTANER: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_LAND_CHECK:
		if (sizeof(CLandCheckEventData) == v.size())
		{
			CGameManager::getInstance().onRecvLandCheckEvent((CLandCheckEventData *)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_LAND_CHECK: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_GET_COIN_AREA_CHECK:
		if (sizeof(CGetCoinCheckEventData) == v.size())
		{
			CGameManager::getInstance().onRecvGetCoinEventCheck((CGetCoinCheckEventData *)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_GET_COIN_EVENT: incorrect struct size!");
		}
		break;

	case NETWORK_PLAY_EVENT_CHANGE_REMOTE_OBJECT_STATE:
		if (sizeof(CContactObjRemoteData) == v.size())
		{
			CGameManager::getInstance().RecveContactObjectRemoteBlock((CContactObjRemoteData*)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHANGE_REMOTE_OBJECT_STATE: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_PUSH_SHAPE_OBJECT:
		if (sizeof(CContactObjRandomShapeData) == v.size())
		{
			CGameManager::getInstance().onRecvRandomShapeEvent((CContactObjRandomShapeData*)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_PUSH_SHAPE_OBJECT: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_MOVE_SET_OBJECT:
		if (sizeof(CContactMoveSetObjData) == v.size())
		{
			CGameManager::getInstance().onRecvMoveSetEvent((CContactMoveSetObjData*)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_MOVE_SET_OBJECT: incorrect struct size!");
		} 
		break;
	case NETWORK_PLAY_EVENT_BREAK_DOOR_OBJECT:
		if (sizeof(CContactBreakDoorObjData) == v.size())
		{
			CGameManager::getInstance().onRecvBreakDoorEvent((CContactBreakDoorObjData*)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_BREAK_DOOR_OBJECT: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_CHARACTER_BOMB:
		if (sizeof(CContactBombObjData) == v.size())
		{
			CGameManager::getInstance().onRecvBombEvent((CContactBombObjData*)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHARACTER_BOMB: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_TRIGGER_CONDITION:
		if (sizeof(CContactTriggerConditionData) == v.size())
		{
			CGameManager::getInstance().onRecvTriggerConditionEvent((CContactTriggerConditionData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_TRIGGER_CONDITION: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_TRAINING_BOSS_ATTACK:
		if (sizeof(CTrainingBossAttackObjEventData) == v.size())
		{
			CGameManager::getInstance().onRecvTrainingBossAttackObjEvent((CTrainingBossAttackObjEventData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_TRAINING_BOSS_ATTACK: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_CONTAINER_FOOTING_TREAD:
		if (sizeof(CContainerFootingTreadData) == v.size())
		{
			CGameManager::getInstance().onRecvContainerFootingTreadEvent((CContainerFootingTreadData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CONTAINER_FOOTING_TREAD: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_GAMEITEM_EVENT:
		if (sizeof(CGameItemEventData) == v.size())
		{
			CGameManager::getInstance().onRecvGameItemEvent((CGameItemEventData*)&v[0]);
		}
		break;
	case NETWORK_PLAY_EVENT_CONTAINER_MOVE:
		if (sizeof(CContainerMoveData) == v.size())
		{
			CGameManager::getInstance().onRecvContainerMoveEvent((CContainerMoveData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CONTAINER_MOVE: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_CONTAINER_COLLISION:
		if (sizeof(CContainerCollisionData) == v.size())
		{
			CGameManager::getInstance().onRecvContainerCollisionEvent((CContainerCollisionData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CONTAINER_COLLISION: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_CONTAINER_CHANGE_PLAYER_ITEM:
		if (sizeof(CContainerChangePlayerItemData) == v.size())
		{
			CGameManager::getInstance().onRecvContainerChangePlayerItemEvent((CContainerChangePlayerItemData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CONTAINER_CHANGE_PLAYER_ITEM: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_ONEDIRMOVEOBJECTEVENT:
		if (sizeof(COneDirMoveObjectEventData) == v.size())
		{
			CGameManager::getInstance().OnRecvOneDirMoveObjectEvent((COneDirMoveObjectEventData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_ONEDIRMOVEOBJECTEVENT: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_VARIETY_THROWING_ATTACK:
		if (sizeof(CVarietyThrowingAttackData) == v.size())
		{
			CGameManager::getInstance().onRecvVarietyThrowingAttackEvent((CVarietyThrowingAttackData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_VARIETY_THROWING_ATTACK: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_VARIETY_ATTACK:
		if (sizeof(CVarietyAttackTreadData) == v.size())
		{
			CGameManager::getInstance().onRecvVarietyAttackTreadEvent((CVarietyAttackTreadData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_VARIETY_ATTACK: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_GAME_OBJ_ENABLE:
		if (sizeof(CGameObjEnableData) == v.size())
		{
			CGameManager::getInstance().onRecvGameObjEnableEvent((CGameObjEnableData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_GAME_OBJ_ENABLE: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_ATTACK_MOVE_OBJECT_EVENT:
		if (sizeof(CAttackMoveObjEventData) == v.size())
		{
			CGameManager::getInstance().OnRecvAttackPatternMoveObjEvent((CAttackMoveObjEventData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_ATTACK_MOVE_OBJECT_EVENT: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_FLAME_OF_HELL_BOSS:
		if (sizeof(CFlameOfHellBossData) == v.size())
		{
			CGameManager::getInstance().onRecvFlameOfHellBossEvent((CFlameOfHellBossData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_FLAME_OF_HELL_BOSS: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_BREAK_WALL_OBJECT:
		if (sizeof(CContactBreakWallObjData) == v.size())
		{
			CGameManager::getInstance().onRecvBreakWallEvent((CContactBreakWallObjData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_BREAK_WALL_OBJECT: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_FARM_PET_GAME_EVENT:
		if (sizeof(CFarmPetGameEventData) == v.size())
		{
			CGameManager::getInstance().onRecvFarmPetGameEvent((CFarmPetGameEventData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_FARM_PET_GAME_EVENT: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_CHANGEOBSTACLE_EVENT:
		if (sizeof(ChangeObstacleObjEventData) == v.size())
		{
			CGameManager::getInstance().onRecvChangeObstacleObjectState((ChangeObstacleObjEventData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHANGEOBSTACLE_EVENT: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_DYNAMIC_BREAK_DOOR_MANAGE_AREA_EVENT:
		if (sizeof(DynamicBreakDoorManageAreaEventData) == v.size())
		{
			CGameManager::getInstance().onRecvDynamicBreakDoorManageAreaEvent((DynamicBreakDoorManageAreaEventData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_DYNAMIC_BREAK_DOOR_MANAGE_AREA_EVENT: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_DYNAMIC_BREAK_DOOR_CONTACT_EVENT:
		if (sizeof(DynamicBreakDoorContactEventData) == v.size())
		{
			CGameManager::getInstance().onRecvDynamicBreakDoorContactEvent((DynamicBreakDoorContactEventData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_DYNAMIC_BREAK_DOOR_CONTACT_EVENT: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_CAN_MANUFACTURE_CREATE_EVENT:
		if (sizeof(CanManufactureObjMakeEvent) == v.size())
		{
			CGameManager::getInstance().onRecvCanManufactureObjMakeEvent((CanManufactureObjMakeEvent*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CAN_MANUFACTURE_CREATE_EVENT : incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_GAMEOBJE_CHANGESTATE_EVENT:
		if (sizeof(GameObjectChangeStateData) == v.size())
		{
			CGameManager::getInstance().onRecvGameObjectChageState((GameObjectChangeStateData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_GAMEOBJE_CHANGESTATE_EVENT: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_CHANGE_PARTS_OBJ_EVENT:
		if (sizeof(ChangePartsEventData) == v.size())
		{
			CGameManager::getInstance().onRecvChangePartsObjEvent((ChangePartsEventData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHANGE_PARTS_OBJ_EVENT: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_CHANGE_OBJECT_STATE_PARAM2:
		if (sizeof(CGameObjStateChangeParam2Data) == v.size())
		{
			CGameManager::getInstance().onRecvStateCheckParam2Event((CGameObjStateChangeParam2Data*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHANGE_OBJECT_STATE_PARAM2: incorrect struct size!");
		}
		break;	
	case NETWORK_PLAY_EVENT_CHANGE_OBJECT_STATE_TCP:
		if (sizeof(CStateCheckObjEventDataEX) == v.size())
		{
			CGameManager::getInstance().onRecvStateCheckObjByTcpVer((CStateCheckObjEventDataEX*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHANGE_OBJECT_STATE_TCP: incorrect struct size!");
		}
		break;	
	case NETWORK_PLAY_EVENT_CHANGE_GAME_PUT_ON_ITEM:
		if (sizeof(CGameCharacterPutOnItemData) == v.size())
		{
			CGameManager::getInstance().onRecGameCharacterPutOnItemData((CGameCharacterPutOnItemData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHANGE_GAME_PUT_ON_ITEM: incorrect struct size!");
		}
		break;

	case NETWORK_PLAY_EVENT_PLAYER_CHANGE_EVENT:
		if (sizeof(CGamePlayerCharacterChangeEventData) == v.size())
		{
			CGameManager::getInstance().onRecvPlayerCharacterEvent((CGamePlayerCharacterChangeEventData*)&v[0]);
		}
		else
		{
			
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHANGE_GAME_PUT_ON_ITEM: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_FOOTHOLD_OBJECT:
		if (sizeof(CContactObjRandomFootholdData) == v.size())	
		{
			CGameManager::getInstance().onRecvRandomFootholdEvent((CContactObjRandomFootholdData*)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_FOOTHOLD_OBJECT: incorrect struct size!");
		}
		break;

	case NETWORK_PLAY_EVENT_CHARACTER_GET_GAME_ITEM:
		if(sizeof(CCharacterGetGameItemData) == v.size())
		{
			CGameManager::getInstance().onRecvCharacterGetGameItemData((CCharacterGetGameItemData*)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHARACTER_GET_GAME_ITEM: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_ASSAULT_OBJECT_SYNC:
		{
			CGameManager::getInstance().onRecvAssaultObjectDataToAllRoomUser( PTR_ELEMENT_VEC( v ), v.size() );
		}
		break;
	case NETWORK_PLAY_EVENT_INGAMEMODE_MANAGER_STATE:
		if (sizeof(InGameModeControlManagerStateData) == v.size())	
		{
			CGameManager::getInstance().onRecvInGameModeControlManagerState((InGameModeControlManagerStateData*)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_INGAMEMODE_MANAGER_STATE: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_GAME_MGR_DATA:
		{
			
			CGameManager::getInstance().onRecvNotifyRoomUser( PTR_ELEMENT_VEC( v ) );
		}
		break;
	case NETWORK_PLAY_EVENT_CHANGE_GAME_PUT_ON_UNIQUE_ITEM:
		if (sizeof(CCharacterGamePutOnMapGenerateItemTypeData) == v.size())
		{
			CGameManager::getInstance().onRecCharacterGamePutOnMapGenerateItemType((CCharacterGamePutOnMapGenerateItemTypeData*)&v[0]);
		}
		else
		{
			TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHANGE_GAME_PUT_ON_UNIQUE_ITEM: incorrect struct size!");
		}
		break;
	case NETWORK_PLAY_EVENT_SETTING_GAME_OBJECT:
		{
			if (sizeof(settingGameObjectSendData) == v.size())
			{
				CGameManager::getInstance().onRecvDataToAllRoomUser_settingGameObject((settingGameObjectSendData *)&v[0]);
			}
			else
			{
				TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_SETTING_GAME_OBJECT: incorrect struct size!");
			}

		}
		break;
	case NETWORK_PLAY_EVENT_SYNC_GAME_EVENT:
		{
			CSyncBuffer buff;
			buff.convert_data( &v[0] );
			int iPlayerID = buff.m_nSendPlayerIndex;
			int iSize = buff.pop<int>();

			CGamePlayerID id(iPlayerID);
			
			std::vector<CGameEventSync *> vecGameEventList;
			for(int i = 0 ; i < iSize ; ++i)
			{
				int iType = buff.pop<int>();
				CGameEventSync * pEvent = CGameEventSync_Factroy::createGameSyncByChunk((GAME_EVENT)iType,buff);
				if(pEvent != NULL)
				{
					vecGameEventList.push_back(pEvent);
				}
			}

			CGameManager::getInstance().onRecvSyncGameEvent(id,vecGameEventList);
		}
		break;

	case NETWORK_PLAY_EVENT_CHARACTER_TRANSFORM:
		{
			if (sizeof(CCharacterTransformEventDataEx) == v.size())
			{
				CCharacterTransformEventDataEx* p = (CCharacterTransformEventDataEx*)&v[0];
				CGameManager::getInstance().onRecvCharacterTransform(p->m_playerID, (CCharacterTransformEventData*)p);
			}
			else
			{
				TRDBG_OUTPUT_ERROR("NETWORK_PLAY_EVENT_CHARACTER_TRANSFORM: incorrect struct size!");
			}
		}
		break;
	}
}

/// 채팅 메시지를 받았다.
void CTRNetEventHandler::onRecvChattingMsg(unsigned int nPlayerIndex, const char* data, size_t len )
{
	if( !data || len == 0 )
		return;

	const CHAT_MSG_TYPE iType = (CHAT_MSG_TYPE)data[0];

	switch(iType)
	{
	case CHAT_MSG_CHATTING:
		{
			std::string msg(&data[1], len - 1);
			msg.resize(strlen(msg.c_str())); // 가끔 data 뒤에 몇바트의 더미가 붙는 경우가 있다.
			std::string strConvertMsg;
			cutInvalidCharacter(msg, strConvertMsg, "([\n\r])");
			CAbuseReportMng::getInstance().addChat(nPlayerIndex,strConvertMsg);
			CTRUserInterface::getInstance().onRecvChattingMessage(nPlayerIndex, strConvertMsg);
		}
		break;
	case CHAT_MSG_COMMAND:
		{
			const CHAT_COMMAND_MSG_TYPE iType = static_cast<CHAT_COMMAND_MSG_TYPE>(data[1]);

			CTRUserInterface::getInstance().onProcessChattingCommandMessage(nPlayerIndex,iType, &data[2],len-2);
		}
		break;
	case CHAT_MSG_GAME_START_COUNT:
	case CHAT_MSG_GAME_WAIT_COUNT:
		if (len == 1 + sizeof(int))
		{
			CTRUserInterface::getInstance().onRecvGameStartCount(iType,nPlayerIndex, *(const int *)&data[1]);
		}
		else
		{
			_ASSERTE(false);
		}
		break;
	case CHAT_MSG_OPEN_TV_CHATTING:
		{
			string msg(&data[1], len - 1);
			msg.resize(strlen(msg.c_str())); // 가끔 data 뒤에 몇바트의 더미가 붙는 경우가 있다.
			std::string strConvertMsg;
			cutInvalidCharacter(msg, strConvertMsg, "([\n\r])");
			CAbuseReportMng::getInstance().addChat(nPlayerIndex,strConvertMsg);
			CTRGameParkUI::getInstance().onRecvOpenTVChattingMessage(nPlayerIndex, strConvertMsg);
		}
		break;
	default:
		_ASSERTE(false);
		break;
	}
}

/// 특정 캐릭터의 위치를 받았다.
void CTRNetEventHandler::onRecvClientCharacterPosition(const BYTE numGameIndex, const ClientCharacterPosition & pos, const CPacketChunk & binData)
{

}

/// on receive new follow index. if index indicate self, no follow move
void CTRNetEventHandler::onRecvUpdateFollowIndex(const BYTE from, const BYTE to)
{
	CTRNetPlayManager::getInstance().onRecvUpdateFollowIndex(from, to);
}

/// 레디 상태를 받았다.
void CTRNetEventHandler::onRecvReadyStatus(unsigned int nPlayerIndex, bool bReady)
{
	DBG_OUTPUT(60, "onRecvReadyStatus: playerIndex=%d, bReady=%s", nPlayerIndex, bReady ? "true":"false");
	// 레디 상태의 변경 체크. 자신의 ready 변경도 이것을 받아야함.

	m_pNetPlay->onRecvReadyStatus(nPlayerIndex, bReady);
	CTRUserInterface::getInstance().onPlayerStateChanged(nPlayerIndex);
}

/// 맵이 변경되었다.
void CTRNetEventHandler::onRecvMapChanged(const int numMap)
{
	DBG_OUTPUT(60, "onRecvMapChanged: %d", numMap);

	// 잘못된 맵 선택시 로비로 내보내기
 	CGameMapID mapID(numMap);
 	if(!CChannelRoomMode::getInstance().isInvalidMapInChannelRoom(mapID))
 	{
 		TRDBG_OUTPUT_ERROR("%s : %d", __FUNCTION__, mapID._getIdentifierValue());
 		CTRShortTimeMessage::getInstance().showMessage(_STR(MSG_MAPSELECT_NOT_USE));
 		CNetClientManager::getInstance().requestLeaveRoom();
 		return;
 	}

	m_pNetPlay->_getGameRoomInfo().setGameMap(numMap);
	m_pNetPlay->_getGameRoomInfo().setGameMapChecker(numMap);
	if(!m_pNetPlay->_getGameRoomInfo().isEnableMapNumber())
	{
		//todo:: kach 해킹체크

	}
	CTRUserInterface::getInstance().onGameMapChanged();

	// 운동회나 티켓쟁탈전일 경우 맵 유효성 검사 아닐경우 랜덤맵으로 교체
	eRoomKind roomKind = CChannelRoomMode::getInstance().getCurRoomKind();
	if(isTicketScrambleChannel(roomKind) || isSportsChannel(roomKind))
	{
		const CTRGameRoomInfo & roomInfo = CTRNetPlayManager::getInstance().getGameRoomInfo();
		CGameMapID mapID = roomInfo.getGameMapID();
		if(!CChannelRoomMode::getInstance().isInvalidMapInChannelRoom(mapID))
		{
			size_t randomMapIndex = 0;
			CGameMapID mapID = CChannelRoomMode::getInstance().getChannnelMap(roomKind, randomMapIndex);

			m_pNetPlay->_getGameRoomInfo().setGameMap(mapID._getIdentifierValue());
			m_pNetPlay->_getGameRoomInfo().setGameMapChecker(mapID._getIdentifierValue());
			if(!m_pNetPlay->_getGameRoomInfo().isEnableMapNumber())
			{
				//todo:: kach 해킹체크

			}
			CTRUserInterface::getInstance().onGameMapChanged();
		}
	}
}


/// 팀이 변경되었다.
void CTRNetEventHandler::onRecvRoomPlayerSelectTeam(BYTE byGameIndex, eTeam byTeamColor)
{
	DBG_OUTPUT(60, "onRecvRoomPlayerSelectTeam:%d %d", byGameIndex, byTeamColor);

	m_pNetPlay->onRecvRoomPlayerSelectTeam(byGameIndex, byTeamColor);
	CTRUserInterface::getInstance().onUpdateRoomUsers();
}


/// 이미 레디 중이어서 팀 선택을 실패했다.
void CTRNetEventHandler::onRecvRoomPlayerSelectTeamFailedAlreadyReady()
{
	DBG_OUTPUT(60, "onRecvRoomPlayerSelectTeamFailedAlreadyReady");
	//TODO: ...
}

/// 이어달리기에서 팀의 위치가 변경되었다.
void CTRNetEventHandler::onRecvRoomPlayerSelectRelayTeam(BYTE byGameIndex, eRelayTeamPosition byRelayTeamColor, eTeam eTeamColor)
{
	DBG_OUTPUT(60, "onRecvRoomPlayerSelectRelayTeam:%d %d %d ", byGameIndex, byRelayTeamColor, eTeamColor);

	m_pNetPlay->onRecvRoomPlayerSelectRelayTeam(byGameIndex, byRelayTeamColor, eTeamColor);
	CTRUserInterface::getInstance().onUpdateRoomUsers();
}

/// 이어달리기에서 슬롯 상태가 변경되었다.
void CTRNetEventHandler::onRecvChangeSlotStateRelayTeam(eRelayTeam relayTeam, bool bClose)
{
	DBG_OUTPUT(60, "onRecvChangeSlotStateRelayTeam:%d %d", relayTeam, bClose);

	int teamIndex = getRelayTeamIndex(relayTeam);

	if(teamIndex == -1)
	{
		_ASSERTE(false);
		return;
	}

	int iTeamCloseCount[eRelayTeam_MAX];

	memset(iTeamCloseCount, 0, sizeof(iTeamCloseCount));

	for ( size_t i = eRelayTeamPosition_A_1 ; i < eRelayTeamPosition_MAX; ++i )
	{
		eRelayTeam tempRelayTeam = getRelayTeamFromRelayTeamPosition((eRelayTeamPosition)i);

		if ( relayTeam == tempRelayTeam )
		{
			if ( bClose )
			{
				m_pNetPlay->_getGameRoomInfo().m_slotInfo.closeSlot((BYTE)(i - eRelayTeamPosition_A_1));
			}
			else
			{
				m_pNetPlay->_getGameRoomInfo().m_slotInfo.openSlot((BYTE)(i - eRelayTeamPosition_A_1));
			}
		}
	}

	CTRUserInterface::getInstance().onUpdateRoomUsers();
}

/// 이어달리기에서 슬롯 상태가 변경되었다.
void CTRNetEventHandler::onRecvChangeSlotStateQuizTeam(eRelayTeamPosition relayTeam, bool bClose)
{
	DBG_OUTPUT(60, "onRecvChangeSlotStateQuizTeam:%d %d", relayTeam, bClose);

	// 퀴즈모드 방이라면
	if (m_pNetPlay->getGameRoomKind() == DEPRECATED___eRoomKind_QUIZ_STAR ||
		m_pNetPlay->getGameRoomKind() == DEPRECATED___eRoomKind_QUIZ_EXAM)
	{
		if (bClose)
			m_pNetPlay->_getGameRoomInfo().m_slotInfo.closeSlot(relayTeam - eRelayTeamPosition_A_1);
		else
			m_pNetPlay->_getGameRoomInfo().m_slotInfo.openSlot(relayTeam - eRelayTeamPosition_A_1);
	}

	CTRUserInterface::getInstance().onUpdateRoomUsers();
}

/// 이어달리기에서 슬롯 상태를 변경하는데 실패했다.
void CTRNetEventHandler::onRecvChangeSlotStateRelayTeamFailed()
{
	DBG_OUTPUT(60, "onRecvChangeSlotStateRelayTeamFailed");
	CTRShortTimeMessage::showMessage(_STR(FAILED_CHANGE_GAME_ROOM_SLOT_STATE));
}


/// 이어달리기에서 다음 주자를 준비한다.
void CTRNetEventHandler::onRecvRelayPrepareNextRunner(BYTE numGameIndex)
{
	CGameManager::getInstance()._processPrepareBatonTouchZone(CGamePlayerID(numGameIndex));
}

/// 이어달리기에서 바톤 터치 구간에 들어왔다.
void CTRNetEventHandler::onRecvEnterBatonTouchArea(BYTE numGameIndex)
{
	CGameManager::getInstance()._processEnterBatonTouchZone(CGamePlayerID(numGameIndex));
}

/// 이어달리기에서 바톤 터치 구간을 통과했다.
void CTRNetEventHandler::onRecvLeaveBatonTouchArea(BYTE numGameIndex)
{
	CGameManager::getInstance()._processLeaveBatonTouchZone(CGamePlayerID(numGameIndex));
}

/// 이어달리기에서 바톤 터치 결과가 왔다.
void CTRNetEventHandler::onRecvBatonInput(BYTE numGameIndex, eBatonInput batonInput, int iParam)
{
	if (0 == iParam)
	{
		CGameManager::getInstance().onRecvGiveBatonInput(CGamePlayerID(numGameIndex), batonInput);
	}
	else
	{
		CGameManager::getInstance().onRecvTakeBatonInput(CGamePlayerID(numGameIndex), batonInput);
	}
}

/// (방 안에서)길드 이름이 업데이트되었다.
void CTRNetEventHandler::onRecvUpdateGuildInfo(BYTE numGameIndex, const std::string & strGuildName, int iGuildNum, eGuildMemberGrade eGrade, eGuildKind guildKind, const short guildLevel)
{
	CTRNetPlayManager::getInstance().onRecvGuildInfoUpdate( numGameIndex, strGuildName, iGuildNum, eGrade, guildKind, guildLevel );
	CTRUserInterface::getInstance().onRecvUpdateGuildInfo(numGameIndex, strGuildName, iGuildNum,eGrade, guildKind, guildLevel);
}

/// (방 안에서)커플 정보가 업데이트되었다.
void CTRNetEventHandler::onRecvUpdateCoupleInfo(BYTE numGameIndex, const CoupleInfo & coupleInfo)
{
	CTRGameParkUI::getInstance().onRecvUpdateCoupleInfo(numGameIndex, coupleInfo);

}

/// 이혼소송 정보를 초기화 하는데 실패했다.
void CTRNetEventHandler::onRecvWeddingInitDivorceRequestInfoFailed()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvWeddingInitDivorceRequestInfoFailed...");
	//거절을 실패했을경우
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		COkDialogEx::getInstance().showDialog(_STR(WEDDING_MSG_FAILED_DIVORCE_ERROR));
	}
}

/// 이혼소송 요청에 대한 결과가 왔다.
void CTRNetEventHandler::onRecvWeddingSuitForDivorceResult(const eServerResult eResult, const std::string & strMateNickname, eWeddingDivorceType eDivorceType)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvWeddingSuitForDivorceResult...%d", eResult);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{		
		switch(eResult)
		{
		case eServerResult_OK_ACK:
			{
				const FriendInfo *pFriendInfo = CNetClientManager::getInstance().getFriendInfo(strMateNickname);
				if(pFriendInfo)
				{
					if(pFriendInfo->m_eState == eUserState_OnLine)
					{
						CNetClientManager::getInstance().community_sendWeddingSuitForDivorce(strMateNickname,  eDivorceType);
					}
				}
				COkDialogEx::getInstance().showDialog(_STR(WEDDING_MSG_DIVORCE_WAIT));
			}
			break;
		case eServerResult_WEDDING_ALREADY_EXIST_REQUEST_DIVORCE_INFO_ACK:
			COkDialogEx::getInstance().showDialog(_STR(WEDDING_MSG_DIVORCE_FAILED_AREADY));
			break;
		}
	}
	
}

/// 이혼소송 요청에 대한 실패 결과가 왔다.
void CTRNetEventHandler::onRecvWeddingSuitForDivorceResultFailed()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvWeddingSuitForDivorceResultFailed...");
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{		
		COkDialogEx::getInstance().showDialog(_STR(WEDDING_MSG_FAILED_DIVORCE_ERROR));
	}
}

/// 이혼 요청에 대한 결과가 왔다.
void CTRNetEventHandler::onRecvWeddingDivorceResult(const std::string & strMateNickname, eWeddingDivorceType eDivorceType, bool bEnforce)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvWeddingDivorceResult...");
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		string msg;
		string guiFilename;

		switch(eDivorceType)
		{
		case eWeddingDivorceType_MaintainRelation:
			msg = _STR(WEDDING_MSG_DIVORCE_OK_1);
			guiFilename = "gui\\Family\\Break_Wed.gui";
			break;
		case eWeddingDivorceType_BreakRelation:
		case eWeddingDivorceType_ForceBreakRelation:
			CTRGameParkUI::getInstance().onCoupleInfoChange();		// 점술상점 커플점을 보는지 체크

			msg = _STR(WEDDING_MSG_DIVORCE_OK_2);
			guiFilename = "gui\\Family\\Break_All.gui";
			break;
		}
		COkDialogEx::getInstance().showDialog(msg, guiFilename, -1.f, false);
	}
	else
	{
		UserAlarmInfo info;
		info.alarmMsg = eALARM_MSG_WEDDING_DIVORCE;
		info.strExt = bEnforce ? CNetClientManager::getInstance().getMyNickname() : strMateNickname;
		info.iExt1 = (int)eDivorceType;
		info.iExt2 = (bool)bEnforce;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(info);
	}

	CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_WEDDING_DIVORCE_ITEM);
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
	CNetClientManager::getInstance().requestCoupleUpdateCoupleInfo();
	CNetClientManager::getInstance().requestFamilyInfo(CNetClientManager::getInstance().getMyNickname(), false);
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvCoupleChangeCoupleRing(CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
#endif
	CTRMyroomDlg::getInstance().onRecvCoupleChangeCoupleRing(CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
	CTRShopDlg::getInstance().onRecvCoupleChangeCoupleRing(CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
	CTRCoupleSystem::getInstacne().updateRingItem(CNetClientManager::getInstance().getMyCoupleInfo().coupleRingInfo.iCoupleRingNum);
	CNetClientManager::getInstance().requestMyCharacter();
	CKeepFarmItemList::getInstance().update(false);
}

/// 이혼 요청이 대한 실패했다.
void CTRNetEventHandler::onRecvWeddingDivorceResultFailed()
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvWeddingDivorceResultFailed...");
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		COkDialogEx::getInstance().showDialog(_STR(WEDDING_MSG_FAILED_DIVORCE_ERROR));
	}
	CNetClientManager::getInstance().requestWeddingInitDivorceRequestInfo(eWeddingDisagreeDivorceType_CANT_RESPONSE);
}

/// 선물 교환권의 보상 내용을 받았다.
void CTRNetEventHandler::onRecvGiftCouponRewardListInfo(int iCouponItemNum, std::map<eRewardCondition, std::vector<int> > & mapRewardInfoList)
{
	CTRFarmUI::getInstance().onRecvGiftCouponRewardListInfo(iCouponItemNum, mapRewardInfoList);
	CTRGameParkUI::getInstance().onRecvGiftCouponRewardListInfo(iCouponItemNum, mapRewardInfoList);
}

/// 선물 교환권의 보상 내용을 받는데 실패했다.
void CTRNetEventHandler::onRecvGiftCouponRewardListInfoFailed()
{
     DBG_OUTPUT("CTRNetEventHandler::onRecvGiftCouponRewardListInfoFailed");
}

/// 선물 교환권 사용에 대한 결과가 왔다.
void CTRNetEventHandler::onRecvGiftCouponReward(int iCouponItemNum, eRewardCondition eRewardType, int iReward)
{
    DBG_OUTPUT("CTRNetEventHandler::onRecvGiftCouponReward...iCouponItemNum = %d, eRewardType = %d, iReward = %d", iCouponItemNum, eRewardType, iReward);
	CTRFarmUI::getInstance().onRecvGiftCouponReward(iCouponItemNum, eRewardType, iReward);
	CTRGameParkUI::getInstance().onRecvGiftCouponReward(iCouponItemNum, eRewardType, iReward);

	if(eRewardType == eRewardCondition_TRMONEY)
		CNetClientManager::getInstance().requestCurrentTR();
	else if(eRewardType == eRewardCondition_ITEM)
	{
		const CItemInfoNode * pItem = CClientItemList::getInstance().getItemInfo(iReward);
		if(pItem)		
			CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(pItem->m_iUniqueNumber);		
	}
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iCouponItemNum);
}

/// 선물 교환권 사용을 실패했다.
void CTRNetEventHandler::onRecvGiftCouponRewardFailed()
{
	 DBG_OUTPUT("CTRNetEventHandler::onRecvGiftCouponRewardFailed");
}

/// 카드 선물 전송에 대한 처리결과가 왔다.
void CTRNetEventHandler::onRecvGiftCardSendResult(const eServerResult eResult, const std::string strRecvNickname)
{
	if(eResult == eServerResult_OK_ACK)
	{
		if(!COkDialogEx::getInstance().isVisible())
		{
			COkDialogEx::getInstance().showDialog(_STR(MSG_WEDDING_GIFT_SEDN_SUCCESS));

			CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(eCharacterKind_NONE, eFuncItemPosition_CARD_GIFT_ITEM);
		}
	}
	else //if(eResult == eServerResult_CANT_RECIEVE_GIFTCARD)
	{
		_ASSERTE(false);
		TRDBG_OUTPUT_ERROR("CTRNetEventHandler::onRecvGiftCardSendResult eResult(%d)", eResult);
	}	
}

/// 넷이서 한마음에서 키를 밟은 정보가 왔다.
void CTRNetEventHandler::onRecvKeyInDoor(const OneInFour_KeyInDoor & info)
{
	CGameManager::getInstance().onRecvInsertKeyInDoor(info);
}

/// 슬롯 상태가 변경되었다.
void CTRNetEventHandler::onRecvRoomSlotChangeState(BYTE slotNum, bool bClosed)
{
	DBG_OUTPUT(60, "onRecvRoomSlotChangeState:%d %d", slotNum, bClosed);

	if(!bClosed)
	{
		m_pNetPlay->_getGameRoomInfo().m_slotInfo.openSlot(slotNum);
	}
	else
	{
		m_pNetPlay->_getGameRoomInfo().m_slotInfo.closeSlot(slotNum);
	}

	CTRUserInterface::getInstance().onUpdateRoomUsers();
}


/// 방제가 바뀌었다.
void CTRNetEventHandler::onRecvRoomTitleChange(const std::string & strTitle)
{
	m_pNetPlay->_getGameRoomInfo().m_roomTitle = strTitle;

	if(m_pGameRoomUI)
		m_pGameRoomUI->onRecvRoomTitleChange(strTitle);	
}

/// 방암호가 바뀌었다
void CTRNetEventHandler::onRecvRoomPasswordChange(const std::string & strPassword)
{
	if(m_pGameRoomUI)
		m_pGameRoomUI->onRecvRoomPasswordChange(strPassword);
}

/// 방의 경쟁 모드가 바뀌었다.
void CTRNetEventHandler::onRecvRoomSteppingModeChange(const bool bSteppingMode)
{
	if(m_pNetPlay != NULL && m_pGameRoomUI != NULL && m_pNetPlay->inRoom())
	{	
		CTRGameRoomInfo & roominfo = m_pNetPlay->_getGameRoomInfo();

		roominfo.setSteppingMode(bSteppingMode);
		m_pGameRoomUI->onUpdateRoomUI();
	}
}

/// 방의 아이템 모드가 바뀌었다.
void CTRNetEventHandler::onRecvRoomItemModeChange(const eItemMode itemMode)
{
	if(m_pNetPlay != NULL && m_pGameRoomUI != NULL && m_pNetPlay->inRoom())
	{	
		CTRGameRoomInfo & roominfo = m_pNetPlay->_getGameRoomInfo();

		roominfo.setItemMode(itemMode);

		m_pGameRoomUI->onUpdateRoomUI();
	}
}

/// 방의 옵션(방제목,비밀번호,경쟁모드,아이템모드,스피드퀴즈모드)이 바뀌었다.
void CTRNetEventHandler::onRecvModifyRoomOption(const std::string strRoomTitle, const std::string strRoomPassword, 
												const bool bSteppingMode, const eItemMode itemMode
												)
{
	if(m_pNetPlay != NULL && m_pGameRoomUI != NULL && m_pNetPlay->inRoom())
	{
		CTRAssistItemManager *pAssistMgr = m_pNetPlay->getAssistItemManager();
		if (pAssistMgr)
		{
			pAssistMgr->removeNotProperAvailableItem(m_pNetPlay->getGameRoomKind(), itemMode, CNetClientManager::getInstance().getMyExp());
		}

		m_pGameRoomUI->onRecvModifyRoomOption(strRoomTitle, strRoomPassword, bSteppingMode, itemMode);		// 옵션 변경 처리...
	}
}

/// 강퇴되었다.
void CTRNetEventHandler::onRecvRoomKicked(const BYTE numGameIndex)
{
	if(m_pGameRoomUI)
		m_pGameRoomUI->onRecvRoomKicked(numGameIndex);

	if(m_pNetPlay->getThisPlayerIndex() == (size_t)numGameIndex)
	{
		CTRFarmChangeManager::getInstance().setRoomServerNumChangeFarm(false);
		CTRShortTimeMessage::showMessage(_STR(KICKED_FROM_THE_ROOM));
		m_pNetPlay->onRecvRoomKicked();
	}
}

/// 강퇴 경고 정보를 받았다.
void CTRNetEventHandler::onRecvRoomKickOutWarning(const KickOutWarning& beforeKickOutWarning, const KickOutWarning& kickOutWarning, bool bShowMessage)
{
	if(m_pGameRoomUI)
	{
		m_pGameRoomUI->onRecvRoomKickOutWarning(beforeKickOutWarning, kickOutWarning, bShowMessage);
	}

	if(beforeKickOutWarning.m_level != eKickOutWarningLevel_3 && kickOutWarning.m_level == eKickOutWarningLevel_3)
	{
		UserAlarmInfo info;
		info.alarmMsg = eALARM_MSG_DELAY_KICK_LIMIT_RELEASE;
		info.fDelayTime = (float)kickOutWarning.m_iRemainDisableTime;
		CTRUserAlarmManager::getInstacne().onPushUserAlarmInfo(info);
	}
}

void CTRNetEventHandler::onRecvRoomKickOutWarningFailed()
{
	if(m_pGameRoomUI)
	{
		m_pGameRoomUI->onRecvRoomKickOutWarningFailed();
	}
}

/// 커플 경험치 추가 아이템을 사용했다.
void CTRNetEventHandler::onRecvMyRoomUseCoupleExpAdd(int iItemNum, bool bSelf)
{
	if(!bSelf) return;
	DBG_DEMO_OUTPUT("onRecvMyRoomUseCoupleExpAdd itemnum:%d", iItemNum);
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iItemNum);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		COkDialogEx::getInstance().showDialog(_STR(COUPLESYS_USE_COUPLE_EXP_INCREASE_ITEM));
	}
}
void CTRNetEventHandler::onRecvMyRoomUseCoupleExpAddFailed(eServerResult result)
{
	DBG_DEMO_OUTPUT("onRecvMyRoomUseCoupleExpAddFailed eServerResult:%d", result);
	if (CTRNetPlayManager::getInstance().isGameStateNoGame())
	{
		string errMsg;
		switch (result)
		{
		case eServerResult_COUPLE_EXP_ADD_INVALID_ITEM:
			errMsg = _STR(ERR_USE_ITEM);	// 아이템 사용에 실패하였습니다.
			break;

		case eServerResult_COUPLE_EXP_ADD_NOT_ENOUGH_ITEM:
			errMsg = _STR(MSG_FARM_HARVEST_CHARGE_FAILE_NOT_HAS_ITEM);	// 사용할 아이템이 없습니다
			break;

		case eServerResult_COUPLE_EXP_NOT_COUPLE:
			errMsg = _STR(COUPLESYS_NAME_CHANGE_ERR_USE_ITEM);	// <smallbold>커플을 맺지 않아서 해당아이템을 사용할 수 없습니다.<br>(먼저 커플을 맺으세요)<smallbold>
			break;

		case eServerResult_COUPLE_EXP_LEVEL_UP_PROSSIBLE:
			errMsg = _STR(COUPLESYS_CHANGE_MSG_CAN_CHANGE_RING_UPGRADE);	// 커플 레벨 업이 가능한 상태입니다.<BR>[테일즈북] - [인맥] - [커플정보]나 공원 커플 삐에로에게<BR>레벨 업이 가능합니다.
			break;

		case eServerResult_COUPLE_EXP_MAX_LEVEL:
			errMsg = _STR(MSG_NOT_USE_LIMIT_MAX_LEVEL);	// 최고 레벨에 도달하여 사용 할 수 없습니다.
			break;

		default:
			errMsg = _STR(ERR_USE_ITEM);	// 아이템 사용에 실패하였습니다.
			break;
		}

		COkDialogEx::getInstance().showDialog(errMsg);
	}
}

///마이룸 슬롯
//마이룸 슬롯 : 저장을 실패함 
void CTRNetEventHandler::onRecvMyRoomSetSlotSettingFailed(eServerResult result)
{
	CTRMyroomDlg::getInstance().onRecvMyRoomSetSlotSettingFailed(result);
}

//마이룸 슬롯: 슬롯의 이름정보를 불러오는데 실패함
void CTRNetEventHandler::onRecvMyRoomGetUserSlotInfoFailed()
{
	CTRMyroomDlg::getInstance().onRecvMyRoomGetUserSlotInfoFailed();
}

//마이룸 슬롯: 슬롯 아이템 세팅을 성공함
void CTRNetEventHandler::onRecvMyRoomSetSlotItemSetting(int slotNum, AvatarInfo avatarInfo, std::string slotName)
{
	CTRMyroomDlg::getInstance().onRecvMyRoomSetSlotItemSetting(slotNum, avatarInfo, slotName);
}

//마이룸 슬롯: 슬롯 아이템 정보를 불러옴
void CTRNetEventHandler::onRecvMyRoomGetUserSlotInfo(std::vector<MyRoomSlotInfo> vecSlotInfo)
{

	for (size_t i = 0; i < vecSlotInfo.size(); ++i)
		CTRSalonManager::getInstance().SetAvatarInfoDyeData(vecSlotInfo[i].m_AvatarInfo);

	if(CTRMyroomDlg::getInstance().isVisible())
	{
		CTRMyroomDlg::getInstance().onRecvMyRoomGetUserSlotInfo(vecSlotInfo);
	}
	else
	{
#ifdef _RAINBOW_LEAGUE
#ifdef _CHAMPIONS_CUP
		int iLeagueType = RainbowLeague::CTRRainbowLeagueManager::getInstance().getLeagueEventType();
		if(iLeagueType == 2)
		{
			RainbowLeague::CTRChampionsCupRoomUI::getInstance().onRecvMyRoomGetUserSlotInfo(vecSlotInfo);
		}
		else if(iLeagueType == 1)
#endif
		{
			RainbowLeague::CTRRainbowLeagueRoomUI::getInstance().onRecvMyRoomGetUserSlotInfo(vecSlotInfo);
		}
#endif
	}
}

//마이룸 슬롯 :마이룸 슬롯을 구매하는데 성공함
void CTRNetEventHandler::onRecvMyRoomPayMyRoomSlotResultOK(int iMySlot)
{
	CTRMyroomDlg::getInstance().onRecvMyRoomPayMyRoomSlotResultOK(iMySlot);
}

//마이룸 슬롯 :마이룸 슬롯을 구매하는데 실패함
void CTRNetEventHandler::onRecvMyRoomPayMyRoomSlotResultFailed(const eMyRoomProtocol_PAY_MYROOM_SLOT_RESULT_FAILED_REASON& failedreson)
{
	CTRMyroomDlg::getInstance().onRecvMyRoomPayMyRoomSlotResultFailed( failedreson );
}

void CTRNetEventHandler::onRecvMyRoomFavoriteList(USER::eFavorite_LIST_RESULT result, const std::vector<int>& favorites)
{
	switch(result)
	{
	case USER::eFavorite_LIST_OK:
		CTRNetPlayManager::getInstance().setFavoriteList(favorites);
		break;
	case USER::eFavorite_LIST_DB:
		CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_CREATE_FAMILY_DB_ERROR));
		break;
	case USER::eFavorite_LIST_ON_PROCESSING:
		CNetClientManager::getInstance().requestFavoriteList();
		break;
	}
}

void CTRNetEventHandler::onRecvMyRoomFavoriteAddListAck(USER::eFavorite_ADD_RESULT result, int item)
{
	switch(result)
	{
	case USER::eFavorite_ADD_OK:
		CTRNetPlayManager::getInstance().addFavoriteList(item);
		break;
	case USER::eFavorite_ADD_MAX_LIST:
		CTRShortTimeMessage::getInstance().showMessage(_STR(FAVORITE_MAXIMUM_OVER));
		break;
	case USER::eFavorite_ADD_UNKNOWN:
		CTRShortTimeMessage::getInstance().showMessage(_STR(FAVOR_SLOT_RESULT_FAILED_REASON_UNKNOWN));
		break;
	}
}

void CTRNetEventHandler::onRecvMyRoomFavoriteRemoveListAck(USER::eFavorite_REMOVE_RESULT result, int item)
{
	switch(result)
	{
	case USER::eFavorite_REMOVE_OK:
		CTRNetPlayManager::getInstance().removeFavoriteList(item);
		break;
	case USER::eFavorite_REMOVE_NO_ITEM:
		CTRShortTimeMessage::getInstance().showMessage(_STR(FAVORITE_NOT_LIST));
		break;
	case USER::eFavorite_REMOVE_UNKNOWN:
		CTRShortTimeMessage::getInstance().showMessage(_STR(FAVOR_SLOT_RESULT_FAILED_REASON_UNKNOWN));
		break;
	}
}

/// 올림픽 방에서 경기일정 종료로 인해 퇴장당했다.
void CTRNetEventHandler::onRecvOlympicRoomKicked()
{
	string msg = _STR(MSG_ROOM_OUT_OLYMPICROOM_AS_TIMEOUT);
	COkDialogEx::getInstance().showDialog("<normal>" + msg + "</normal>");

	DBG_OUTPUT(60, "onRecvOlympicRoomKicked");

	CNetClientManager::getInstance().requestLeaveRoom();
}

/// 게임 시작 카운팅을 해도 된다.
void CTRNetEventHandler::onRecvStartCounting()
{	
	DXUTSetTitleBarDragOnOff(true);

	CTRGuildDlg::getInstance().closeDialog();
	CTRMessengerMainUI::getInstance().closeDialog();
	CTRUserBookDlg::getInstance().closeUI();
	CTRShopBuyAllDialog::getInstance().closeDialog();
	
	CTRUserInterface::getInstance().onRecvStartCounting();
	m_pNetPlay->onRecvStartCounting();
}


/// 게임 시작 카운팅을 할 수 없는 상태이다.
void CTRNetEventHandler::onRecvNotStartCounting(CStartCountFail::STATUS status)
{
	DXUTSetTitleBarDragOnOff(false);

	if(status == CStartCountFail::NOT_WAITING_STATE)
	{
		CTRShortTimeMessage::showMessage(_STR(FAILED_START_GAME_INVALID_STATE));
	}
	else if(status == CStartCountFail::FAILED_INVALID_GAME)
	{
		TRDBG_OUTPUT_ERROR("%s[%d] FAILED_INVALID_GAME",__FUNCTION__,__LINE__);
	}
	else if(status == CStartCountFail::NOT_MATCH_TEAM)
	{
		TRDBG_OUTPUT_ERROR("%s[%d] NOT_MATCH_TEAM",__FUNCTION__,__LINE__);
	}
	else if(status == CStartCountFail::CANT_START_LOADING_STATE)
	{
		TRDBG_OUTPUT_ERROR("%s[%d] CANT_START_LOADING_STATE",__FUNCTION__,__LINE__);
	}
	else if(status == CStartCountFail::JUST_ONE_PLAYER)
	{
		TRDBG_OUTPUT_ERROR("%s[%d] JUST_ONE_PLAYER",__FUNCTION__,__LINE__);
	}
	else if(status == CStartCountFail::NOT_READY_PLAYER_EXIST)
	{
		TRDBG_OUTPUT_ERROR("%s[%d] NOT_READY_PLAYER_EXIST",__FUNCTION__,__LINE__);
	}
	else if(status == CStartCountFail::INVALID_MAP)
	{
		TRDBG_OUTPUT_ERROR("%s[%d] INVALID_MAP",__FUNCTION__,__LINE__);
	}
	else if(status == CStartCountFail::INVALID_MASTER_REWARD_RANK)
	{
		CTRShortTimeMessage::showMessage(_STR(FAILED_START_GAME_INVALID_MASTER_REWARD_RANK));
		TRDBG_OUTPUT_ERROR("%s[%d] INVALID_MASTER_REWARD_RANK",__FUNCTION__,__LINE__);
	}
	else if(status == CStartCountFail::MAP_CHANGE_CONSTRAINT_TIME)
	{
#ifdef _RAINBOW_LEAGUE
		if(isRainbowLeagueChannel(m_pNetPlay->getGameRoomKind()) == false)
#endif
			CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_START_GAME_MAP_CHANGED));
	}
}


/// 게임 시작 카운팅 중 취소되었다는 메시지...
void CTRNetEventHandler::onRecvStartCountingCancel()
{
	DXUTSetTitleBarDragOnOff(false);

	CTRUserInterface::getInstance().onRecvStartCountingCancel();

	m_pNetPlay->onRecvStartCountingCancel();

	if (m_pNetPlay != NULL && isGuildMatchPlayingRoom(m_pNetPlay->getGameRoomKind()))
	{
		m_pNetPlay->getGuildMatchManager()->setBooleanValue(GUILD_MATCH_CHEK_REQ_START_GAME_COUNT,false);
	}
}


/// 로딩을 시작하자는 메시지를 받았다.
void CTRNetEventHandler::onRecvStartLoading(const int numMap, const int iRandomSeed)
{
	// 리펙토링 요망
	CGameChatFrame::getInstance().setVisible(true);

	DXUTSetTitleBarDragOnOff(false);

	if (GAME_STATE_NO_GAME == m_pNetPlay->getGameState())
	{
		// TODO 부철 : reset 타이밍 startLoading 안으로 이동.. 
		//CMissionMsgDispatcher::getInstance().reset();

		CTRUserInterface::getInstance().closeUI();

		CGameMapID mapID = CGameMapID(numMap);

		if(COkDialogEx::getInstance().isVisible()) COkDialogEx::getInstance().closeDialog();  // 게임시작전에 열려있는 ok창을 닫는다.

		// TODO: random seed 설정...
		CGameManager::getInstance().setRandomSeed(iRandomSeed);
		m_pNetPlay->startLoading(mapID, GAME_MODE_NETWORK_PLAY);
	}

	else
	{
		_ASSERTE(false);
		TRDBG_OUTPUT_WARNING("onRecvStartLoading: m_iGameState(%d) != GAME_STATE_NO_GAME(%d)", m_pNetPlay->getGameState(), GAME_STATE_NO_GAME);
	}
}


/// 로딩 시작이 실패했다는 메시지를 받았다.
void CTRNetEventHandler::onRecvStartLoadingFail(eStartLoadingFail failNum)
{
	DXUTSetTitleBarDragOnOff(false);

	string message;
	switch(failNum)
	{
	case eStartLoadingFail_JUST_ONE_PLAYER : // 한 명은 시작할 수 없다. -> 인원이 부족합니다.
		message = _STR(FAILED_START_GAME_INSUFFICIENT_PLAYER);
		break;
	case eStartLoadingFail_NOT_READY_PLAYER_EXIST : // Ready 를 안한 플레이어가 있다.
		message = _STR(FAILED_START_GAME_UNPREPARED_PLAYER);
		break;
	case eStartLoadingFail_CANT_START_LOADING_STATE : // 시작할 수 있는 상태가 아니다.
		message = _STR(FAILED_START_GAME_INVALID_STATE);
		break;
	case eStartLoadingFail_NOT_MATCH_TEAM : // 팀이 맞지 않는다.
		message = _STR(MISMATCHED_TEAM);
		break;
 	case eStartLoadingFail_NOT_FOUND_REQUIRE_ITEM :
 		message = _STR(MSG_FRIEND_RECALL_ITEM_NO_EXIST_NOT_GAME);
 		break;
	default: 
		message = _STR(FAILED_START_LOADING_UNKNOWN);
		_ASSERTE(false);
	}

	CTRShortTimeMessage::showMessage(message);

	if (m_pNetPlay != NULL && isGuildMatchPlayingRoom(m_pNetPlay->getGameRoomKind()))
	{
		m_pNetPlay->getGuildMatchManager()->setBooleanValue(GUILD_MATCH_CHEK_REQ_START_GAME_COUNT,false);
	}
}


/// Mesh 로딩이 끝났다는 메시지를 받았다.
void CTRNetEventHandler::onRecvEndMeshLoading(int iPlayerIndex)
{
	DBG_OUTPUT(60, "onRecvEndMeshLoading: %d", iPlayerIndex);

	m_pNetPlay->onRecvEndMeshLoading(iPlayerIndex);
}

/// 모든 이들의 Mesh 로딩이 끝났다고 받았다.
void CTRNetEventHandler::onRecvAllUserEndMeshLoading()
{
	//...
}


/// 로딩이 끝났다는 메시지를 받았다.
void CTRNetEventHandler::onRecvEndLoading(int iPlayerIndex)
{
	DBG_OUTPUT(60, "onRecvEndLoading: %d", iPlayerIndex);

	m_pNetPlay->onRecvEndLoading(iPlayerIndex);
}


/// 모든 이들의 로딩이 끝났다고 받았다.
void CTRNetEventHandler::onRecvAllUserEndLoading()
{
	DBG_OUTPUT(60, "onRecvAllUserEndLoading");

	m_pNetPlay->onRecvAllUserEndLoading();
}


/// 실제 게임을 시작하라는 메시지를 받았다.
void CTRNetEventHandler::onRecvStartGame(int iGameStartTick, int iNumberOfItem)
{
	DBG_OUTPUT(60, "onRecvStartGame: iGameStartTick=%d, iNumberOfItem=%d (CurTick=%d)", iGameStartTick, iNumberOfItem, CGameClock::getInstance().getTickCount());

	m_pNetPlay->onRecvStartGame(iGameStartTick, iNumberOfItem);
}

/// 보너스Ex 를 먹었다
void CTRNetEventHandler::onRecvBonusExEat( const int eatBonusIndex, std::vector<RewardInfo>& rewardList )
{
	DBG_OUTPUT(60, "[%s] - [%d]", __FUNCTION__, rewardList.size());
	
	CGameManager::getInstance().onRecvBonusExEat(eatBonusIndex, rewardList);
}

/// 게임 중 data 를 받았다.
void CTRNetEventHandler::onRecvData(int iPlayerIndex, const CPacketChunk & _data)
{
	if (_data.empty()) return;
	const NETWORK_PLAY_EVENT_TYPE iEventType = (NETWORK_PLAY_EVENT_TYPE)_data[0];


	switch(iEventType)
	{
	case NETWORK_PLAY_EVENT_PROXYOBJ_SYNC_KEY_STATE_CHANGED:
	case NETWORK_PLAY_EVENT_PROXYOBJ_SYNC_PERIODIC_STATES:
	case NETWORK_PLAY_EVENT_PROXYOBJ_SYNC_TRANSFER_INFO:
		CNetProxyObjectManager::getInstance().onRecvData(CGamePlayerID(iPlayerIndex), _data);
		return;
		break;
	}

	if (m_pNetEventListener)
	{
		m_pNetEventListener->onRecvP2PData(iPlayerIndex, &_data[0], _data.size(), false);
	}
}


void CTRNetEventHandler::onRecvDataWithConfirm(int iPlayerIndex, int _iEventType_not_use, const CPacketChunk & data)
{
	if (m_pNetEventListener)
	{
#ifndef TR_RELEASE_PROJECT
		DBG_OUTPUT("CTRNetEventHandler::onRecvDataWithConfirm");
#endif
		m_pNetEventListener->onRecvP2PData(iPlayerIndex, &data[0], data.size(), true);
	}
}


int CTRNetEventHandler::getTick() const
{
	return CGameClock::getInstance().getTickCount();
}


void CTRNetEventHandler::onRecvMasterTick(int iGameTick, DWORD dwPingLoopTime)
{
	// 예측Tick === iGameTick시간 + dwPingLoopTime * 0.5

	const int iCurTick = CGameClock::getInstance().getTickCount();
	const float fEstimatedTick = iGameTick + float(dwPingLoopTime) / (2000.f * GAME_TIME_STEP);

	m_fMasterTickDiffs.push_back(fEstimatedTick - iCurTick);

	if (m_fMasterTickDiffs.size() >= 5)
	{
		sort(m_fMasterTickDiffs.begin(), m_fMasterTickDiffs.end());
		m_fMasterTickDiffs.erase(m_fMasterTickDiffs.begin());
		m_fMasterTickDiffs.erase(m_fMasterTickDiffs.end() - 1);

		float fAveTickDiff = 0;
		for(size_t i = 0 ; i < m_fMasterTickDiffs.size() ; ++i )
		{
			fAveTickDiff += m_fMasterTickDiffs[i];
		}

		fAveTickDiff /= m_fMasterTickDiffs.size();

		DBG_OUTPUT(60, "CTRNetPlayManager::onRecvMasterTick: fAveTickDiff = %.f", fAveTickDiff);

		m_fMasterTickDiffs.clear();

		CGameClock::getInstance().setTickCount(int(iCurTick + fAveTickDiff));
	}
}


void CTRNetEventHandler::setRandomSeed(int)
{
}


/// 누군가 아이템을 먹었다.
void CTRNetEventHandler::onRecvEatItem(int iPlayerIndex, int iItemID, int iGameTick, int iItemKind, const int iMadeNextItemID, bool bMakeAndEat, int eatParam)
{
	//쌍둥의 맵의 반란일 경우.
	//eatParam = 1: 진짜 아이템
	//eatParam = 0: 가짜 아이템
	//기타 맵
	//eatParam = 0

	CGameItemID nextNewItemID;

	if (iMadeNextItemID > 0)
	{
		// 생성된 아이템이 있음.
		nextNewItemID = CGameItemID(iMadeNextItemID);
	}

	CGameManager::getInstance().onRecvEatItem(CGamePlayerID(iPlayerIndex), CGameItemID(iItemID), nextNewItemID, iGameTick, iItemKind, bMakeAndEat, eatParam);
}


/// 아이템 먹기를 실패했다.
void CTRNetEventHandler::onRecvEatItemFailed(int iPlayerIndex, int iItemID, int iGameTick, int iMadeNextItemID, int iHaveItemID, int iHaveItemKind)
{
	DBG_OUTPUT("EatItemFailed");
	CGameItemID nextNewItemID;

	if (iMadeNextItemID > 0)
	{
		// 생성된 아이템이 있음.
		nextNewItemID = CGameItemID(iMadeNextItemID);
	}

	CGameManager::getInstance().onRecvEatItemFailed(CGamePlayerID(iPlayerIndex), CGameItemID(iItemID), nextNewItemID, iGameTick, CGameItemID(iHaveItemID), iHaveItemKind);

}

/// 누군가 맵에서 생성된 아이템을 먹었다.
void CTRNetEventHandler::onRecvEatItemForRoomGenerate( int iPlayerIndex, const std::vector<MapEatItemInfo>& eat_item_list)
{
	for (size_t i = 0; i < eat_item_list.size(); ++i)
	{
 		CGameItemID ItemID;
	 
 		if (eat_item_list[i].item_id() > 0)
 		{
 			ItemID = CGameItemID(eat_item_list[i].item_id());
 		}
	 
 		CGameManager::getInstance().onRecvEatItemForRoomGenerate(CGamePlayerID(iPlayerIndex), ItemID, eat_item_list[i].itemtype());
	}
}

/// 누군가 맵에서 생성된 아이템을 떨어뜨렸다.
void CTRNetEventHandler::onRecvDropItemForRoomGenerate( const std::vector<MapDropedItemInfo>& dropItemList, BYTE byUserIndex, int iSeed )
{
	if (!dropItemList.empty())
	{
		CGameManager::getInstance().onRecvDropItemForRoomGenerate(dropItemList, CGamePlayerID(byUserIndex), iSeed);
	}
}

void CTRNetEventHandler::onRecvMakeEatItemCoolTimeFailed(int iItemKind, eRequestItem requestItemData, eGameItemMakeAndEat_Method gameItemMakeAndEat_Method, int argument, int leftCoolTime)
{
	CGameManager::getInstance().onRecvMakeEatItemCoolTimeFailed(iItemKind,requestItemData,gameItemMakeAndEat_Method,argument,leftCoolTime);
}

/// 드랍된 아이템 삭제한다. (맵 생성 아이템)
void CTRNetEventHandler::onRecvDeleteDropedItemForRoomGenerate( const std::vector<int>& itemIDList, BYTE byUserIndex )
{
	if (!itemIDList.empty())
	{
		CGameManager::getInstance().onRecvDeleteDropedItemForRoomGenerate(itemIDList, CGamePlayerID(byUserIndex));
	}
}

/// 유저가 소유한 아이템 삭제한다. (맵 생성 아이템)
void CTRNetEventHandler::onRecvDeleteEquipedItemForRoomGenerate( const std::vector<int>& itemIDList, BYTE byUserIndex )
{
	if (!itemIDList.empty())
	{
		CGameManager::getInstance().onRecvDeleteEquipedItemForRoomGenerate(itemIDList, CGamePlayerID(byUserIndex));
	}
}

/// 유저의 아이템 획득/삭제에 따라 점수가 변동되었다.(맵 성성 아이템)
void CTRNetEventHandler::onRecvPointNotifyForRoomGenerate(int user_index, const std::vector<int>& user_delta, const std::vector<int>& team_delta, const std::map<int/*user index*/, int/*point*/>& user_points, const std::map<eTeam, int>& team_points)
{
	if(!user_points.empty() || !team_points.empty())
	{
		CGameManager::getInstance().onRecvPointNotifyForRoomGenerate(user_index, user_delta, team_delta, user_points, team_points);
	}
}

/// 누군가 유니크 아이템을 먹었다.
void CTRNetEventHandler::onRecvGetUniqueItem(BYTE byPlayerIndex, int iItemID, int iGameTick, const int iMadeNextItemID)
{
	if (iMadeNextItemID > 0)
	{
		// 유니크 아이템을 먹은 경우에 자동 생성되는 아이템은 없다.
		_ASSERTE(false);
	}	
}

/// 누군가 보스 공격 아이템을 먹었다.
void CTRNetEventHandler::onRecvGetBossAttackItem(BYTE byPlayerIndex, int iItemID, int iGameTick, const int iMadeNextItemID)
{
	CGameManager::getInstance().onRecvGetBossAttackItem(CGamePlayerID((size_t)byPlayerIndex), iItemID, iGameTick, iMadeNextItemID);
}

/// 누군가 오브젝트 리소스 아이템을 먹었다.
void CTRNetEventHandler::onRecvGetObjectResourceItem(BYTE byPlayerIndex, int iItemID, int iGameTick, const int iMadeNextItemID)
{
	CGameManager::getInstance().onRecvGetObjectResourceItem(CGamePlayerID((size_t)byPlayerIndex), iItemID, iGameTick, iMadeNextItemID);
}

/// 누군가 아이템을 사용했다.
void CTRNetEventHandler::onRecvUseItem(int iPlayerIndex, int iItemKind, int iGameTick,
									   const CPacketChunk & useInfo)
{
	CGameManager::getInstance().onRecvUseItem(CGamePlayerID(iPlayerIndex), iItemKind, iGameTick, &useInfo[0], useInfo.size());
}

/// 아이템을 사용하는데 실패하였다.
void CTRNetEventHandler::onRecvUseItemFailed()
{
	CGameManager::getInstance().onRecvUseItemFailed();
}

/// 아이템을 지우는 처리를 한다.
void CTRNetEventHandler::onRecvRemoveItem( int iPlayerIndex, bool isSuccess /*= true*/)
{
	CGameManager::getInstance().onRecvRemoveItem(iPlayerIndex);
}

/// 누군가 아이템을 만들라고 했다.
void CTRNetEventHandler::onRecvMakeItem(int iCanEatTick, int iItemKind, int iItemID, const CPacketChunk & data)
{
	if (sizeof(CMakeItemEventData) > data.size())
	{
		_ASSERTE(false);
		return;
	}
	switch(reinterpret_cast<const CMakeItemEventData *>(&data[0])->m_iEventType)
	{
	case NETWORK_PLAY_MAKE_ITEM_EVENT_ITEM_GENERATOR:
		if (sizeof(CMakeItemItemGeneratorEventData) == data.size())
		{
			const CMakeItemItemGeneratorEventData * pEventData = reinterpret_cast<const CMakeItemItemGeneratorEventData *>(&data[0]);
			CGameItemGeneratorObj::_processRecvMakeItem(
				CGameItemID(iItemID),
				(GAME_ITEM)iItemKind,
				iCanEatTick,
				*pEventData);
		}
		else
		{
			_ASSERTE(false);
		}
		break;
	case NETWORK_PLAY_MAKE_ITEM_EVENT_FRIED_OCTOPUS:
		if (sizeof(CMakeItemFriedOctopusEventData) == data.size())
		{
			const CMakeItemFriedOctopusEventData * pEventData = reinterpret_cast<const CMakeItemFriedOctopusEventData *>(&data[0]);
			CGameManager::getInstance()._processMakeItemFriedOctopus(
				pEventData->m_srcOctopusItemID,
				CGameItemID(iItemID),
				iCanEatTick,
				pEventData->m_iTrack,
				pEventData->m_pos, pEventData->m_vel, pEventData->m_bSister);
		}
		else
		{
			_ASSERTE(false);
		}
		break;
	case NETWORK_PLAY_MAKE_MULTI_MAKEITEM:
		if (sizeof(CMultiMakeItemEventData) == data.size())
		{
			const CMultiMakeItemEventData * pEventData = reinterpret_cast<const CMultiMakeItemEventData *>(&data[0]);
			CGameManager::getInstance().onRecvMultiMakeItem(pEventData,iCanEatTick,(GAME_ITEM)iItemKind,CGameItemID(iItemID));
		}
		break;
	case NETWORK_PLAY_MAKE_ITEM_EVENT_RICE_CAKE_SALESWOMAN:
		if (sizeof(CMakeItemRiceCakeSaleswomanEventData) == data.size())
		{
			const CMakeItemRiceCakeSaleswomanEventData * pEventData = reinterpret_cast<const CMakeItemRiceCakeSaleswomanEventData *>(&data[0]);
			CGameManager::getInstance()._processMakeItemRiceCakeSaleswoman(
				CGameItemID(iItemID),
				pEventData->m_iObjectIndex,
				pEventData->m_bLimitedGen,
				iCanEatTick,
				pEventData->m_pos,
				pEventData->m_vel);
		}
		else
		{
			_ASSERTE(false);
		}
		break;
	case NETWORK_PLAY_MAKE_ITEM_EVENT_BY_CHARACTER:
		if (sizeof(CMakeItemByCharacterEventData) == data.size())
		{
			const CMakeItemByCharacterEventData * pEventData = reinterpret_cast<const CMakeItemByCharacterEventData *>(&data[0]);
			CGameManager::getInstance()._processMakeItemByCharacter(
				CGameItemID(iItemID),
				pEventData->m_playerID,
				pEventData->m_iGameItem,
				iCanEatTick,
				pEventData->m_iTrack,
				pEventData->m_pos,
				pEventData->m_vel);
		}
		else
		{
			_ASSERTE(false);
		}
		break;
	case NETWORK_PLAY_MAKE_BOX_GEN_AREA_MAKE_ITEM_EVENT:
		if (sizeof(CBoxGenAreaMakeItemkEventData) == data.size())
		{
			const CBoxGenAreaMakeItemkEventData * pEventData = reinterpret_cast<const CBoxGenAreaMakeItemkEventData *>(&data[0]);
			switch (static_cast<MAKEITEM_SUB_TYPE>(pEventData->m_subType))
			{
			case MAKEITEM_SUB_TYPE_ATTACK_OBJECT:
				{
					CGameManager::getInstance()._processMakeItemBoxGenAreaItem(
						CGameItemID(iItemID),
						pEventData->m_iAreaIndex,
						pEventData->m_iObjectIndex,
						pEventData->m_playerID,
						pEventData->m_bObjectGenerator,
						pEventData->m_iGameItem,
						iCanEatTick,
						pEventData->m_vPos);
				}
				break;

			case MAKEITEM_SUB_TYPE_ASSUALT_ATTACK_OBJECT:
				{
					CGameManager::getInstance()._processMakeAssaultItemBoxGenAreaItem(
						CGameItemID(iItemID),
						pEventData->m_iAreaIndex,
						pEventData->m_iObjectIndex,
						pEventData->m_playerID,
						pEventData->m_bObjectGenerator,
						pEventData->m_iGameItem,
						iCanEatTick,
						pEventData->m_vPos);
				}
				break;
			}
			
		}
		else
		{
			_ASSERTE(false);
		}
		break;
	case NETWORK_PLAY_MAKE_ATTACK_ITEM_EVENT:
		if (sizeof(CMakeAttackEventData) == data.size())
		{
			const CMakeAttackEventData * pEventData = reinterpret_cast<const CMakeAttackEventData *>(&data[0]);
			CGameManager::getInstance()._processMakeItemAttackItem(
				CGameItemID(iItemID),
				pEventData->m_iObjectIndex,
				pEventData->m_playerID,
				pEventData->m_iGameItem,
				iCanEatTick,
				pEventData->m_vPos);
		}
		else
		{
			_ASSERTE(false);
		}
		break;
	case NETWORK_PLAY_MAKE_OBJ_ITEM_EVENT:
		if (sizeof(CMakeMakeItemEventData) == data.size())
		{
			const CMakeMakeItemEventData * pEventData = reinterpret_cast<const CMakeMakeItemEventData *>(&data[0]);
			CGameManager::getInstance()._processMakeObjectMakeItem(
				CGameItemID(iItemID),
				pEventData->m_iObjectIndex,
				pEventData->m_playerID,
				pEventData->m_iGameItem,
				iCanEatTick,
				pEventData->m_vPos);
		}
		else
		{
			_ASSERTE(false);
		}
		break;
	case NETWORK_PLAY_MAKE_EVENT_GAMEITEM:
		if (sizeof(CMakeItemGameItemEventData) == data.size())
		{
			const CMakeItemGameItemEventData * pEventData = reinterpret_cast<const CMakeItemGameItemEventData *>(&data[0]);
			CGameManager::getInstance()._processMakeEventGameItem(
				CGameItemID(iItemID),
				iCanEatTick,
				*pEventData);
		}
		else
		{
			_ASSERTE(false);
		}
		break;
	case NETWORK_PLAY_MAKE_EVENT_ITEMBOX:
		{
			if (sizeof(CMakeItemBoxGameItemEventData) == data.size())
			{
				const CMakeItemBoxGameItemEventData * pEventData = reinterpret_cast<const CMakeItemBoxGameItemEventData *>(&data[0]);

				CGameManager::getInstance()._processMakeItemBoxEvent(
					CGameItemID(iItemID),
					iCanEatTick,
					*pEventData);
			}
			else
			{
				_ASSERTE(false);
			}
		}
		break;

	case NETWORK_PLAY_MAKE_ITEM_ATTACK_OBJ:
		{
			if (sizeof(CSelfMakeItemEventData) == data.size())
			{
				const CSelfMakeItemEventData * pEventData = reinterpret_cast<const CSelfMakeItemEventData *>(&data[0]);

				CGameManager::getInstance().onRecvSyncSelfMakeGameItem(CGameItemID(iItemID), pEventData);
			}
			else
			{
				_ASSERTE(false);
			}
		}
		break;
	case NETWORK_PLAY_MAKE_SETTING_GAMEITEM:
		{
			if (sizeof(CMakeSettingGameItemEventData) == data.size())
			{
				const CMakeSettingGameItemEventData * pEventData = reinterpret_cast<const CMakeSettingGameItemEventData *>(&data[0]);
				CGameManager::getInstance()._processMakeSettingGameItem(
					CGameItemID(iItemID),
					(GAME_ITEM)iItemKind,
					iCanEatTick,
					*pEventData);
			}
			else
			{
				_ASSERTE(false);
			}
		}
		break;
	}
}


/// 누군가 아이템을 만들라고 했다.
void CTRNetEventHandler::onRecvRegenItem(GAME_ITEM iItemKind)
{
	// 이 패킷을 받은 유저만 재생성.
	CGameManager::getInstance().onRecvRegenItem(iItemKind);
}

/// 누군가 맵에서 생성되는 아이템을 만들라고 했다.
void CTRNetEventHandler::onRecvMakeItemForMapGenerate( int iCanEatGameTick, eMapGenerateItemType itemType, int iMadeNewItemID, const CPacketChunk & Data )
{
	if (sizeof(CMakeBounsItemEventData) > Data.size())
	{
		_ASSERTE(false);
		return;
	}

	switch(reinterpret_cast<const CMakeBounsItemEventData *>(&Data[0])->m_iEventType)
	{
	case NETWORK_PLAY_MAKE_BONUS_ITEM_EVENT:
		if (sizeof(CMakeBounsItemEventData) == Data.size())
		{
			const CMakeBounsItemEventData * pEventData = reinterpret_cast<const CMakeBounsItemEventData *>(&Data[0]);
			CGameManager::getInstance().onRecvMakeItemForMapGenerate(pEventData->m_type, CGameItemID(iMadeNewItemID), pEventData->m_pos, pEventData->m_move, pEventData->m_playerID, pEventData->m_bDrop, pEventData->m_iObjectIndex);
		}
		break;
	}

}

/// 누군가 생일 축하 모자 아이템을 밟았다. 앞의 인자가 밟힌 유저 인덱스, 뒤가 밟은 유저 인덱스
void CTRNetEventHandler::onRecvStepBirthdayCap(const BYTE numSteppedUserGameIndex, const BYTE numStepUserGameIndex)
{
	CGameManager::getInstance().onRecvStepBirthdayCap(CGamePlayerID(numSteppedUserGameIndex), CGamePlayerID(numStepUserGameIndex));	

}

/// 발판을 만든다.
void CTRNetEventHandler::onRecvMakeFootBoard(const int iNumberOfFootBoard )
{

}

/// 발판을 밟았을때 처리를 한다.
void CTRNetEventHandler::onRecvStepFootBoard(const int iFootBoardIndex, const BYTE numPlayerIndex )
{
	if(CGameManager::getInstance().isGameMapAmsanMode())
	{
		CTRQuestionManager::getInstance().onRecvSteppedButton(iFootBoardIndex, numPlayerIndex);
	}
}

/// 발판 지역(?) 을 통과 후 처리를 한다.
void CTRNetEventHandler::onRecvPassFootBoardArea()
{

}

void CTRNetEventHandler::onRecvAbusingUserListInfo(std::map<BYTE, AbusingInfo> & abusingInfoList)
{
	CTRNetPlayManager::getInstance().onRecvAbusingUser(abusingInfoList);
}

/// 누군가 서바이벌 맵에서 GameOver 했다.
void CTRNetEventHandler::onRecvGameOver(BYTE byPlayerIndex, eGameUserEventTypeResponse response)
{
	DBG_OUTPUT(60, "(%s)=[%d][%d]",__FUNCTION__,(int)byPlayerIndex,(int)response);

	CGameManager::getInstance().onRecvGameOver(CGamePlayerID(byPlayerIndex),response);
}

/// 누군가 서바이벌 맵에서 혼자 살아남았다.
void CTRNetEventHandler::onRecvGameOverSurvive(std::vector<BYTE>& goalinList)
{
	if(!goalinList.empty()) DBG_OUTPUT(60, "onRecvGameOverSurvive: byGameIndex=%d", goalinList[0]);

	CGameManager::getInstance().onRecvGameOverSurvive(goalinList);
}

#ifdef _RANDOM_GAMEOVER

/// 탈락 서바이벌 모드에서 체크 포인트를 통과했다.
void CTRNetEventHandler::onRecvServivalRandomGameoverCheckPoint(const BYTE channelCheckPoint, const BYTE byGameIndex, const std::vector<BYTE> & gameoverRankList)
{
	if(CGameManager::getInstance().getInGameMode()->getProcessorType() == GAME_MODE_PROCESSOR_RANDOM_GAMEOVER)
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CDropRankNotify(channelCheckPoint, gameoverRankList));
	}
}

/// 탈락 서바이벌 모드에서 체크 포인트 거리를 받았다.
void CTRNetEventHandler::onRecvServivalRandomGameoverRaceLengthOK(const BYTE channelCheckPoint)
{}

void CTRNetEventHandler::onRecvServivalRandomGameoverRaceLengthFailed(const BYTE channelCheckPoint)
{}

/// 탈락 서바이벌 모드에서 탈락유저에게 알려준다
void CTRNetEventHandler::onRecvServivalRandomGameoverNotify(const BYTE channelCheckPoint, const bool isGameOver)
{
	if(isGameOver)
	{
		CGameManager::getInstance().getInGameMode()->notifyIntValue("GameOver", channelCheckPoint);
	}	
}

#endif

/// 서바이벌 암산왕 맵에서 특정 체크 포인트를 통과했다.
void CTRNetEventHandler::onRecvPassSuvivalArithmeticCheckPoint(const DWORD dwLapTime, const int iTimeLimit, const int dwBonusTime, const bool bShow)
{
	CTRQuestionManager::getInstance().onRecvPassSuvivalArithmeticCheckPoint(dwLapTime, iTimeLimit, dwBonusTime, bShow);
}

/// 서바이벌 암산왕에서 이 유저가 최초로 골 발판을 밟았다.
void CTRNetEventHandler::onRecvPassSteppedGoalBoard(BYTE byGameIndex, const int iRank)
{
	CGameManager::getInstance().onRecvPassSteppedGoalBoard(byGameIndex, iRank);
}

/// 달리기 퀴즈모드(세계왕) 퀴즈 리스트를 받아왔다.
void CTRNetEventHandler::onRecvRunQuizModeGetQuizList(RunQuizModeSelectData& runQuizInfo)
{	
	CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CRunQuizModeQuizListPush(runQuizInfo));
}

void CTRNetEventHandler::onRecvRunQuizModeGetQuizListFailed( eRunQuizModeResult reason )
{

}

/// 1등 유저가 골인 발판을 밟아서 타임아웃 카운트 정보가 왔다.(아직 골인은 아님, 1등 유저를 지외한 인원들에게만 뿌려짐.)
void CTRNetEventHandler::onRecvTimeOutCount(const DWORD dwLapTime, const int iTimeLimit)
{
	CGameManager::getInstance().onRecvTimeOutCount(dwLapTime, iTimeLimit);
}

/// 누군가 골인했다.
void CTRNetEventHandler::onRecvGoalInData(BYTE numPlayerIndex, DWORD dwLapTime, eGoalin flag)
{
	DBG_OUTPUT(60, "onRecvGoalInData: iPlayerIndex=%d, dwLapTime=%d, flag: %d", numPlayerIndex, dwLapTime,(int)flag);

	// 누군가 골인했을 때의 처리...
	CGameManager::getInstance().onRecvGoalInData(CGamePlayerID(numPlayerIndex), dwLapTime, flag);

	CMissionMsgDispatcher & rMissionMsgDispatcher = CMissionMsgDispatcher::getInstance();

	if(m_pNetPlay->getThisPlayerIndex() == (size_t)numPlayerIndex)
	{
		const CGameMapDescInfo *pGameMapDescInfo = CGameManager::getInstance().getCurrentGameMapDesc();
		if(pGameMapDescInfo)
		{
			const int iMapID = static_cast<int>(pGameMapDescInfo->getMapID()._getIdentifierValue());
			
			rMissionMsgDispatcher.setConditionCheckValue_Int(eCHECK_VALUE_INT_GOALINE_MAP_ID, iMapID);
			rMissionMsgDispatcher.addMissionConditionEvent(eMissionConditionType_COMPLETE_RUN);
			rMissionMsgDispatcher.addMissionConditionEvent(eMissionConditionType_TIME_RECORD, dwLapTime);
			rMissionMsgDispatcher.checkCompleteCondition();

			DBG_OUTPUT("CTRNetEventHandler::onRecvGoalInData MapIndex=[%d]", iMapID);
		}
	}

	rMissionMsgDispatcher.addGoalPlayerIndex((unsigned int)numPlayerIndex);

	CTRGameUI::getInstance().on_close_timeLimitUI();
	CTRUserInterface::getInstance().onRecvGoalInData(numPlayerIndex);
}

/// 혼인서약 단계로 넘어간다.
void CTRNetEventHandler::onRecvWeddingChangeAgreeState(eServerResult eResult)
{
	 DBG_OUTPUT("CTRNetEventHandler::onRecvWeddingChangeAgreeState eResult %d", eResult);
	CTRFarmUI::getInstance().onRecvWeddingChangeAgreeState(eResult);
}

/// 혼인 서약에 동의 했다.
void CTRNetEventHandler::onRecvWeddingAgree(eServerResult eResult)
{
    DBG_OUTPUT("CTRNetEventHandler::onRecvWeddingAgree %d", eResult);
	CTRFarmUI::getInstance().onRecvWeddingAgree(eResult);
}

/// 결혼을 하여 부부의 관계가 되었다.
void CTRNetEventHandler::onRecvWeddingCreateCouple(eServerResult eResult, __int64 iCeremonyOfficerID)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvWeddingCreateCouple eResult %d iCeremonyOfficerID %d", eResult, iCeremonyOfficerID);
	CTRFarmUI::getInstance().onRecvWeddingCreateCouple(eResult, iCeremonyOfficerID);
}

/// 이 tick 때 타임 몬스터를 시작해라.
void CTRNetEventHandler::onRecvStartTimeOutCount(DWORD dwGametime, BYTE nTimeOutSeconds)
{
	DBG_OUTPUT(60, "onRecvStartTimeOutCount: dwGametime=%d, nTimeOutSeconds=%d", dwGametime, nTimeOutSeconds);

	CGameManager::getInstance().onStartTimeOutCount(int(dwGametime / 1000.0f / GAME_TIME_STEP), nTimeOutSeconds);

}


/// 상점이 닫혀있다. 서버가 종료를 대기하거나, 시작 중이다.
void CTRNetEventHandler::onRecvShopClosed()
{
	DBG_OUTPUT(60, "onRecvShopClosed");

	CTRShortTimeMessage::showMessage(_STR(ERR_SHOPCLOSE),1.0);
	CTRShopDlg::getInstance().onRecvShopClosed();
	CTRMawooShopDlg::getInstance().onRecvShopClosed();
}

/// 게임 시작 화면을 끝내고 게임룸으로 돌아가라.
void CTRNetEventHandler::onRecvMoveToGameRoom()
{
	DBG_OUTPUT(60, "onRecvMoveToGameRoom");

	m_pNetPlay->returnToGameRoom();
	//	CGameChatFrame::getInstance().setVisible(false);
}

///< 대운동회 카운팅을 멈춰라.
void CTRNetEventHandler::onRecvCancelSportsCount()
{
	CTRGameSportsRoomUI::getInstance().onRecvCancelSportsCount();
	CTRPieroOlympicRoomUI::getInstance().onRecvCancelSportsCount();
	CTRTicketScrambleRoomUI::getInstance().onRecvCancelSportsCount();

#ifdef _RUNNING_MAN2
	CTRRunningMan2RoomUI::getInstance().onRecvCancelSportsCount();

#endif
	
	CTRAnubisRoomUI::getInstance().onRecvCancelAnubisCount();

#ifdef JOURNEY_TO_THE_WEST
	CTRJourneyToTheWestChannelRoomCrowdUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _CHAOS
	CTRChaosRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _ASSAULT_RAID
	CTRAssaultRaidCrowdGameRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _HORROR_PARK_CHANNEL
	CTRHorrorParkRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _GENDER_WAR
	CTRGenderWarRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _SNOW_QUEEN_CHANNEL
	CTRSnowQueenTeamRoomUI::getInstance().onRecvCancelSportsCount();
	CTRSnowQueenNormalRoomUI::getInstance().onRecvCancelSportsCount();
	CTRSnowQueenCrowdRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _OFFICIAL_COMPETITION_CHANNEL
	CTRRoyalRumbleCrowdRoomUI::getInstance().onRecvCancelSportsCount();
	CTRFrozenCorpseCrowdRoomUI::getInstance().onRecvCancelSportsCount();
	CTRHammerGameCrowdRoomUI::getInstance().onRecvCancelSportsCount();
	CTRBattleSurvivalCrowdRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _WINTER_FESTIVAL
	CTRWinterFestivalRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _KNIGHT_FLOWERS_
	CTRKnightFlowersTeamRoomUI::getInstance().onRecvCancelSportsCount();
	CTRKnightFlowersNormalRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _CHAOS_ZERO_
	CTRChaosZeroRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _DEV_FESTIVAL_
	CTRDevFestivalRoomUI::getInstance().onRecvCancelSportsCount();
#endif
#ifdef _TALES_ACADEMY_
	CTRTalesAcademyRoomUI::getInstance().onRecvCancelSportsCount();
	CTRTalesAcademyPersonalRoomUI::getInstance().onRecvCancelSportsCount();
#endif
#ifdef _RUNLYMPIC
	CTRRunlympicRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _TALES_FRONTIER_
	CTRTalesFrontierRoomUI::getInstance().onRecvCancelSportsCount();
	CTRTalesFrontierPersonalRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _THANK_OFFERING_
	CTRThankOfferingRoomUI::getInstance().onRecvCancelSportsCount();
#endif

#ifdef _SPRING_CHANNEL_2020_
	CTRSpringChannel2020RoomUI::getInstance().onRecvCancelSportsCount();
#endif
}

///< 대운동회 카운팅을 시작해라.
void CTRNetEventHandler::onRecvStartSportsCount(const time_type tRemainTime)
{
	CTRGameSportsRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
	CTRPieroOlympicRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
	CTRTicketScrambleRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);

#ifdef _RUNNING_MAN2
	CTRRunningMan2RoomUI::getInstance().onRecvStartSportsCount(tRemainTime);

#endif //_RUNNING_MAN2

	CTRAnubisRoomUI::getInstance().onRecvStartAnubisCount(tRemainTime);

#ifdef JOURNEY_TO_THE_WEST
	CTRJourneyToTheWestChannelRoomCrowdUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _CHAOS
	CTRChaosRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _ASSAULT_RAID
	CTRAssaultRaidCrowdGameRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _HORROR_PARK_CHANNEL
	CTRHorrorParkRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _GENDER_WAR
	CTRGenderWarRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _SNOW_QUEEN_CHANNEL
	CTRSnowQueenTeamRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
	CTRSnowQueenNormalRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
	CTRSnowQueenCrowdRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _OFFICIAL_COMPETITION_CHANNEL
	CTRRoyalRumbleCrowdRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
	CTRFrozenCorpseCrowdRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
	CTRHammerGameCrowdRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
	CTRBattleSurvivalCrowdRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _WINTER_FESTIVAL
	CTRWinterFestivalRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif 

#ifdef _KNIGHT_FLOWERS_
	CTRKnightFlowersTeamRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
	CTRKnightFlowersNormalRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _CHAOS_ZERO_
	CTRChaosZeroRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _DEV_FESTIVAL_
	CTRDevFestivalRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _TALES_ACADEMY_
	CTRTalesAcademyRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
	CTRTalesAcademyPersonalRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _RUNLYMPIC
	CTRRunlympicRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _TALES_FRONTIER_
	CTRTalesFrontierRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
	CTRTalesFrontierPersonalRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _THANK_OFFERING_
	CTRThankOfferingRoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif

#ifdef _SPRING_CHANNEL_2020_
	CTRSpringChannel2020RoomUI::getInstance().onRecvStartSportsCount(tRemainTime);
#endif
}

/// 네트웍이 끊어졌다.... network error
void CTRNetEventHandler::onDisconnectedFromServer()
{
	DBG_OUTPUT(60, "onDisconnectedFromServer");

	if(CNetClientManager::getInstance().isLoginAuthenTransaction())  // 비번보호기 인증 중인가...
	{	
		COkDialogEx::getInstance().showDialog(_STR(SNDA_LOGIN_FAILED_TIMEOUT));
		CTRLoginPromptUI::getInstance().onReadyConnect();
	}
	else
	{
		CTRFatalErrorUI::showScreen(_STR(ERR_DISCONNECTED_FROM_SERVER), _STR(ERR_DISCONNECTED_FROM_SERVER_DESC), true);
	}
}

struct GameResultReceiverInfo
{
	GAMERESULT_UI_TYPE gameResultUIType;
	CGameResultCeremonyDirector * pCeremonyDirector; 

	GameResultReceiverInfo()
	{
		gameResultUIType = GAMERESULT_UI_NONE;
		pCeremonyDirector = NULL;
	}
};

GameResultReceiverInfo getGameResultReceiverInfo(CChannelRoomMode::CHANNELMODE channelMode, CChannelRoomMode::ROOMMODE roomMode)
{
	GameResultReceiverInfo info;

	//! 결과 UI
	const CGameMapDescInfo* mapInfo = CGameManager::getInstance().getCurrentGameMapDesc();
	if (mapInfo != NULL && mapInfo->m_iGameMapSubType == GAME_MAP_SUB_ASSAULT_RAID_TEAM_MODE)
	{
		info.gameResultUIType = GAMERESULT_UI_TEAM_ASSAULT_RAID;
	}
	else if(mapInfo != NULL && mapInfo->m_iGameMapType == GAME_MAP_BONUS_STAGE)
	{		
		info.pCeremonyDirector = &CGameResultCeremonyDirector::getInstance();
		ROOM_TEAMINFO teamPlayMode = CTRNetPlayManager::getInstance().getGameRoomInfo().m_sTeamPlayMode;
		if(is_three_team(teamPlayMode))
		{
			info.gameResultUIType = GAMERESULT_UI_THREE_TEAM;
		}
		else if(is_two_team(teamPlayMode))
		{
			info.gameResultUIType = GAMERESULT_UI_TEAM;
		}
		else
		{
			info.gameResultUIType = GAMERESULT_UI_NORMAL;
		}
	}
	else if(mapInfo != NULL && mapInfo->m_iGameMapSubType == GAME_MAP_SUB_MAP_RUNLYMPIC)
	{
		info.gameResultUIType = GAMERESULT_UI_NORMAL;
		if(channelMode == CChannelRoomMode::CHANNELMODE_EASY
			|| channelMode == CChannelRoomMode::CHANNELMODE_NORMAL
			|| channelMode == CChannelRoomMode::CHANNELMODE_NEWBIEONLY)
			info.pCeremonyDirector = &CGameResultCeremonyDirector::getInstance();
	}
	else if(channelMode == CChannelRoomMode::CHANNELMODE_UNITY
		|| (channelMode == CChannelRoomMode::CHANNELMODE_NEW_PIERO_OLYMPIC_CHAOS && roomMode == CChannelRoomMode::ROOMMODE_UNITY_CROWD)
		|| (channelMode == CChannelRoomMode::CHANNELMODE_SNOW_QUEEN && (roomMode == CChannelRoomMode::ROOMMODE_SNOW_QUEEN_BOSS_EASY
																	 || roomMode == CChannelRoomMode::ROOMMODE_SNOW_QUEEN_BOSS_HARD
																	 || roomMode == CChannelRoomMode::ROOMMODE_SNOW_QUEEN_BOSS_NEW)))
	{
		//! 협력모드용 게임 결과창
		info.gameResultUIType = GAMERESULT_UI_BOSS;
	}
	else if (channelMode == CChannelRoomMode::CHANNELMODE_ANUBIS_EASY 
		|| channelMode == CChannelRoomMode::CHANNELMODE_ANUBIS_NORMAL 
		|| channelMode == CChannelRoomMode::CHANNELMODE_ANUBIS_NEWBIEONLY
		|| channelMode == CChannelRoomMode::CHANNELMODE_ANUBIS_EXPEDITION_MODE
		|| channelMode == CChannelRoomMode::CHANNELMODE_ASSAULT_CORUN_MODE)
	{
		//! 어썰트모드용 게임 결과창
		info.gameResultUIType = GAMERESULT_UI_ASSAULT;
	}
	else if (channelMode == CChannelRoomMode::CHANNELMODE_ASSAULT_RAID
		|| channelMode == CChannelRoomMode::CHANNELMODE_DUNGEON_RAID)
	{
		info.gameResultUIType = GAMERESULT_UI_ASSAULT_RAID;
	}
	else if (channelMode == CChannelRoomMode::CHANNELMODE_PLAYGROUND)
	{
		// 멀티 미니게임 게임 결과창
		if(is_team_mode(CTRNetPlayManager::getInstance().getGameRoomInfo().m_sTeamPlayMode))
		{
			info.gameResultUIType = GAMERESULT_UI_TEAM_MULTI_MINIGAME;
		}
		else
		{
			info.gameResultUIType = GAMERESULT_UI_MULTI_MINIGAME;
		}
	}
	else
	{
		//결과 시상대도 게임 결과 이벤트를 받는다.(게임결과에 따라 시상대에 올라갈 유저 결정)
		info.pCeremonyDirector = &CGameResultCeremonyDirector::getInstance();

		if(roomMode == CChannelRoomMode::ROOMMODE_RELAY)
		{
			info.gameResultUIType = GAMERESULT_UI_RELAY;
		}	
		else
		{
			ROOM_TEAMINFO teamPlayMode = CTRNetPlayManager::getInstance().getGameRoomInfo().m_sTeamPlayMode;
			IntTRUserInterface * pInterface = CTRUserInterface::getInstance().getCurrentUI();

			{
				if(is_three_team(teamPlayMode))
				{
					info.gameResultUIType = GAMERESULT_UI_THREE_TEAM;
				}
				else if(is_two_team(teamPlayMode))
				{
					if(mapInfo != NULL && mapInfo->m_bTeamPlayGoalMore)
					{
						info.gameResultUIType = GAMERESULT_UI_NORMAL;
					}
					else
					{
						info.gameResultUIType = GAMERESULT_UI_TEAM;
					}
				}
				else
				{
					info.gameResultUIType = GAMERESULT_UI_NORMAL;
				}
			}
		}
	}

	return info;
}

/// 게임 결과 보상 아이템 목록을 받았다.
void CTRNetEventHandler::onRecvGameResultRewardInfo(std::vector<GameResultReward>& resultRewardList)
{
	DBG_OUTPUT("onRecvGameResultRewardInfo");

	if(resultRewardList.empty()) return;

	// 잭팟 리워드 창을 제일 처음 보여주기위해서 순서 바꿈 
	JackPotReward jpReward = CGameManager::getInstance().getJackPotReward();

	if(jpReward.isEnable())
	{
		std::vector<GameResultReward>::iterator iter;
		for( iter = resultRewardList.begin();  iter != resultRewardList.end(); ++iter)
		{
			if(jpReward.isEnableItem((*iter).m_iItemNum))
			{
				if(resultRewardList.begin() != iter)
				{
					std::iter_swap(resultRewardList.begin(), iter);
				}
				break;
			}
		}
	}

	CChannelRoomMode & ChannelRoommode = CChannelRoomMode::getInstance();

	GameResultReceiverInfo info = getGameResultReceiverInfo(ChannelRoommode.getChannelMode(), ChannelRoommode.getRoomMode());

	std::vector<int> shuItemNums;
	std::vector<int> updateItemNums;
	std::set<int> updateFarmItemNums;

	//!< 아이템 보상 구조체를 변경해야한다..카운트가 없어 하나의 아이템을 2개 이상 보여줄수가 없음!!
	//!< 같은 아이템 번호로 중복 갱신을 막기위해 임시처리한다!!
	std::set<int> sync_itemNumber;

	for(size_t nIndex = 0; nIndex < resultRewardList.size(); ++nIndex )
	{
		if (resultRewardList[nIndex].m_iItemNum <= 0)
		{
			continue;
		}

		bool bIsCardPackItem = false;

		const int itemNum = resultRewardList[nIndex].m_iItemNum;

		const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getItemInfo(itemNum);
		if (pItemInfo != NULL)
		{
			if (pItemInfo->getPosition() == eFuncItemPosition_SHU_ITEM)
			{
				//!< 슈아이템은 다른 요청 루틴을 탄다..
				if (sync_itemNumber.count(pItemInfo->m_iUniqueNumber) == 0)
				{
					shuItemNums.push_back(pItemInfo->m_iUniqueNumber);
					sync_itemNumber.insert(pItemInfo->m_iUniqueNumber);
				}
			}
			else if(pItemInfo->getPosition() == eFuncItemPosition_ADD_EXP)
			{
				CNetClientManager::getInstance().requestExp(eLevelUPKind_RUN);
			}
			else if(pItemInfo->getPosition() == eFuncItemPosition_FARM)
			{
				updateFarmItemNums.insert(pItemInfo->m_iUniqueNumber);
			}
			else
			{
				if (pItemInfo->getPosition() == eFuncItemPosition_CARD_PACK)
				{
					bIsCardPackItem = true;
				}

				if (sync_itemNumber.count(pItemInfo->m_iUniqueNumber) == 0)
				{
					updateItemNums.push_back(pItemInfo->m_iUniqueNumber);
					sync_itemNumber.insert(pItemInfo->m_iUniqueNumber);
				}
			}
		}

		if(ChannelRoommode.getCurRoomDesc().m_bDoNotNotifyRecvItem) continue;

		RESULT_REWARD_UI_PIECE_TYPE rewardUIType = REWARD_NORMAL_PIECE_MAX;

		// 기존 보너스 처리
		if (bIsCardPackItem == false) //!< 카드팩 보상아이템은 연출이 틀리다!!
		{	
			CTRAniAlarmDlg::getInstance().isVisible() ? CTRAniAlarmDlg::getInstance().pushItem(resultRewardList[nIndex]) :
				CTRAniAlarmDlg::getInstance().showDialog(eVIEW_TYPE_GAME_RESULT_ITEM, "", resultRewardList[nIndex]);
		}
		else
		{
			rewardUIType = REWARD_NORMAL_PIECE_CARDPACK;
			DBG_OUTPUT(26, "onRecvGameResultRewardInfo() item(%d) Cardpack!", itemNum);
		}

		JackPotReward reward = CGameManager::getInstance().getJackPotReward();
		if(reward.isEnableItem(itemNum))
		{
			rewardUIType = REWARD_NORMAL_PIECE_JACPOT;
			DBG_OUTPUT(26, "onRecvGameResultRewardInfo() item(%d) Jackpot!", itemNum);
		}

		if(resultRewardList[nIndex].m_type == eGameResultRewardType_PRIZE_ITEM)
		{
			rewardUIType = REWARD_NORMAL_PIECE_PRIZEITEM;
			DBG_OUTPUT(26, "onRecvGameResultRewardInfo() item(%d) Prize!", itemNum);
		}

		if(IntTRGameResultUI * pGameResultUI = CTRGameResultUIRegister::getGameResultUI(info.gameResultUIType))
		{
			pGameResultUI->showRewardUI(rewardUIType, itemNum);
		}

		DBG_OUTPUT("CTRNetEventHandler::onRecvGameResultRewardInfo item : %d %s", itemNum, pItemInfo->m_name.c_str());
	}

	//!< 갱신할 아이템 요청
	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNumList(updateItemNums);

	CNetClientManager::getInstance().requestGetFarmItemListEx(updateFarmItemNums);

	//!< 목록이 비어있지 않다면 보상 아이템 체크
	if(resultRewardList.empty() == false)
	{
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_GAME_RESULT_REWARD_ITEM);
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();
	}

#ifdef _SHU_SYSTEM_
	//!< 슈아이템 목록을 요청한다..
	if(shuItemNums.empty() == false)
	{
		SHU_SYSTEM::ShuSystemManager::getInstance().requestGetItemsInfoByDescNum(shuItemNums);
	}
#endif //_SHU_SYSTEM_
}



/// 게임 결과를 받았다.
void CTRNetEventHandler::onRecvGameResult(const GameResult& gameResult)
{
	CGameManager::getInstance().onRecvGameResult();

	MemoryLog ml("onRecvGameResult. MapNum=%d RoomKind=%d", m_pNetPlay->getGameRoomInfo().getGameMap(), m_pNetPlay->getGameRoomKind());

	DBG_OUTPUT(60, "onRecvGameResult");

	m_pNetPlay->onRecvGameResult(gameResult);	

	GameResultReceiverInfo receiver = getGameResultReceiverInfo(CChannelRoomMode::getInstance().getChannelMode(), CChannelRoomMode::getInstance().getRoomMode());

	if(IntTRGameResultUI * pGameResultUI = CTRGameResultUIRegister::getGameResultUI(receiver.gameResultUIType))
	{
		pGameResultUI->onGameResult(gameResult);
	}

	if(receiver.pCeremonyDirector)
	{
		receiver.pCeremonyDirector->onGameResult(gameResult.m_rankList);
		
		//일단 임시 처리....
		if(CChannelRoomMode::getInstance().getRoomMode() != CChannelRoomMode::ROOMMODE_RELAY && is_team_mode(m_pNetPlay->getGameRoomInfo().m_sTeamPlayMode))
		{
			receiver.pCeremonyDirector->setWinTeam(gameResult.m_winTeamColor);
		}
	}

	// UI는 시간에 맞춰서 CTRGameGoalPhotoUI클래스가 연다.
	CTRUserInterface::openUISingleton<CTRGameGoalPhotoUI>();

	CTRGameGoalPhotoUI::getInstance().setGameResultUIType(receiver.gameResultUIType);
	CTRGameGoalPhotoUI::getInstance().onRecvGameResultCheckPoint(gameResult.m_CheckPointInfo);


	if(CGameManager::getInstance().isGameMapAmsanMode())
	{
		CTRQuestionManager::getInstance().onRecvGameResult();
	}

	if (CGameManager::getInstance().isGameMapRevivalAndDieMode())
	{
		CInGameModeControlManager_RevivalandDie::getinstance().onRecvGameResult();
	}

	//!< 카드 보상 체크위해
	if(!CNetClientManager::getInstance().getGameResultItemList().empty())
	{
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_GAME_RESULT_REWARD_ITEM);
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();
	}
}

void CTRNetEventHandler::onRecvGameResultItemEvent(std::vector<GameResultReward>& itemList)
{
	DBG_OUTPUT(60, "onRecvGameResultItemEvent");

	GameResultReceiverInfo receiver = getGameResultReceiverInfo(CChannelRoomMode::getInstance().getChannelMode(), CChannelRoomMode::getInstance().getRoomMode());

	if(IntTRGameResultUI * pGameResultUI = CTRGameResultUIRegister::getGameResultUI(receiver.gameResultUIType))
	{
		pGameResultUI->onRecvGameResultItemEvent(itemList);
	}

	//!< 목록이 비어있지 않을때
	if(!itemList.empty())
	{
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_GAME_RESULT_REWARD_ITEM);
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();
	}
}

/// 내가 레벨업을 했다.
void CTRNetEventHandler::onRecvLevelUpMe(eLevelUPKind levelKind, int iLevel)
{
	if(levelKind == eLevelUPKind_RUN
	|| levelKind == eLevelUPKind_FARM
#ifdef _ITEM_COLLECTION
	|| levelKind == eLevelUPKind_ITEM_COLLECTION
#endif
	)
	{
		CTRLevelUpManager::getInstance().onRecvLevelUpMe(levelKind, iLevel);

		if (eLevelUPKind_FARM == levelKind && CTRFarmUI::getInstance().isActive())
		{
			CTRFarmUI::getInstance().getFarmSkillExpDlg().setExp(CNetClientManager::getInstance().getMyFarmInfo().m_iFarmExp, true);
		}

		//!< 게임중 미션완료로 인한 레벨업 체크 표시를 위함
		eGUI_TYPE guiType = CTRUserInterface::getInstance().getCurrentUIType();
		if(guiType == GUI_TYPE_GAMEROOM
			|| guiType == GUI_TYPE_SMART_GAMEROOM
			|| guiType == GUI_TYPE_CROWD_GAMEROOM
			|| guiType == GUI_TYPE_RELAY_GAMEROOM
			|| guiType == GUI_TYPE_ANIMAL_GAMEROOM
			|| guiType == GUI_TYPE_TEAMPLAY_GAMEROOM
			|| guiType == GUI_TYPE_NORMALPLAY_GAMEROOM
			|| guiType == GUI_TYPE_DUNGEON_RAID_ROOM
			)
		{
			m_pGameRoomUI->openLevelUpCheck(CGUIControlID::INVALID_ID, levelKind);
		}
		else if(guiType == GUI_TYPE_FARM)
		{
			CTRFarmUI::getInstance().openLevelUpCheck(CGUIControlID::INVALID_ID, levelKind);
		}
		else if(CTRUserBookDlg::getInstance().isVisible())
		{
			CTRUserBookDlg::getInstance().openLevelUpCheck(CGUIControlID::INVALID_ID, levelKind);
		}
		else if(guiType == GUI_TYPE_PARK)
		{
			CTRGameParkUI::getInstance().openLevelUpCheck(CGUIControlID::INVALID_ID, levelKind);
		}
		else if (guiType == GUI_TYPE_LOBBY)
		{
			// 아누비스 입장 레벨 제한 체크 때문에 레벨업 시 업데이트를 한번 함.
			CTRLobbyUI::getInstance().anubisExpeditionUpdateUI();			
		}
		else if (guiType == GUI_TYPE_MYROOM)
		{
			CTRMyRoomUI::getInstance().openLevelUpCheck(CGUIControlID::INVALID_ID, levelKind);
		}

#ifdef _PARTY_SYSTEM
		//!< 파티에 가입되어 있을 경우 파티원에게 레벨업을 알려준다.
		CTRMessengerMainUI::getInstance().onRecvLevelUpMe();
#endif

#ifdef _SHOP_RENEWAL_
		CTRShopManager::getInstance().UpdateLevelUp();
#endif
	}
}

/// 같은 방의 특정 유저가 레벨업을 했다.
void CTRNetEventHandler::onRecvLevelUp(eLevelUPKind levelKind, BYTE byGameIndex, exp_type exp)
{
	if (levelKind == eLevelUPKind_RUN)
	{
		const int iLevel = CTRRankInfoManager::getInstance().getGameLevelFromExp(eLevelUPKind_RUN, exp);
		CTRLevelUpManager::getInstance().onRecvLevelUpPlayer(byGameIndex, iLevel);

		std::map < BYTE, exp_type > indexToExp;

		indexToExp.insert(make_pair(byGameIndex, exp));

		m_pNetPlay->onRecvRoomExpOfUsers(indexToExp);

		m_bRecvLevelUPAck = byGameIndex == CTRNetPlayManager::getInstance().getThisPlayerIndex();

		//!< 게임중 미션완료로 인한 레벨업 체크 표시를 위함
		eGUI_TYPE guiType = CTRUserInterface::getInstance().getCurrentUIType();
		if(guiType == GUI_TYPE_GAMEROOM
			|| guiType == GUI_TYPE_SMART_GAMEROOM
			|| guiType == GUI_TYPE_CROWD_GAMEROOM
			|| guiType == GUI_TYPE_RELAY_GAMEROOM
			|| guiType == GUI_TYPE_ANIMAL_GAMEROOM
			|| guiType == GUI_TYPE_TEAMPLAY_GAMEROOM
			|| guiType == GUI_TYPE_NORMALPLAY_GAMEROOM
			|| guiType == GUI_TYPE_DUNGEON_RAID_ROOM
			)
		{
			m_pGameRoomUI->openLevelUpCheck(CGUIControlID::INVALID_ID, eLevelUPKind_RUN);
			m_pGameRoomUI->onUpdateRoomUsers();
		}
		else if(guiType == GUI_TYPE_FARM)
		{
			CTRFarmUI::getInstance().openLevelUpCheck(CGUIControlID::INVALID_ID, eLevelUPKind_RUN);
		}
		else if(CTRUserBookDlg::getInstance().isVisible())
		{
			CTRUserBookDlg::getInstance().openLevelUpCheck(CGUIControlID::INVALID_ID, eLevelUPKind_RUN);
		}
		else if(guiType == GUI_TYPE_PARK)
		{
			CTRGameParkUI::getInstance().openLevelUpCheck(CGUIControlID::INVALID_ID, eLevelUPKind_RUN);
		}
	}
}

/// 게임방에서 다른 사람이 나갔다.
void CTRNetEventHandler::onRecvOtherPlayerOut(size_t iPlayerIndex)
{
	DBG_OUTPUT(60, "onRecvOtherPlayerOut: iPlayerIndex=%d", iPlayerIndex);

	m_pNetPlay->onRecvOtherPlayerOut(iPlayerIndex);
}

/// 게임방에서 자신이 나갔다.
void CTRNetEventHandler::onRecvThisPlayerOut(size_t iPlayerIndex)
{
	DBG_OUTPUT(60, "onRecvThisPlayerOut: iPlayerIndex=%d", iPlayerIndex);

	m_pNetPlay->onRecvThisPlayerOut(iPlayerIndex);
}
void CTRNetEventHandler::onRecvRoomEvent(eRoomEvent eEventType, BYTE playerIndex, BYTE eventID )
{
	if(CGameManager::getInstance().isGameMapAmsanMode())
	{
		switch(eEventType)
		{
		case eRoomEvent_QUIZ_ANSWER_COUNT:
			CTRQuestionManager::getInstance().onRecvStartLimitCount((int)eventID);
			break;
		case eRoomEvent_QUIZ_SHOW_QUESTION:
			CTRQuestionManager::getInstance().onRecvShowQuestion((int)eventID);
		default:
			break;
		}
	}
	else
	{
		switch(eEventType)
		{
		case eRoomEvent_QUIZ_SHOW_QUESTION:
			{	
				CGameManager::getInstance().getInGameMode()->notifyIntValue("ShowQuestion", eventID);
			}			
			break;

		default:
			break;
		}
	}	
}

/// 서버에서 유저의 정보가 필요한지 여부를 받는다.
void CTRNetEventHandler::onRecvUserSystemInfo(const bool bSendUserInfo)
{
	CTRLobbyLoadingUI::getInstance().onRecvUserSystemInfoReq(bSendUserInfo);
	// 로그인 성공이면 광고를 켠다.
	CAdvertisementManager::getInstance().startAdvertise();
}

void CTRNetEventHandler::onRecvItemOnOff( const eServerResult eResult, const int iItemDescNum,const bool bOnOff )
{
	// eServerResult_ITEM_ONOFF_FAILED_ACK인 경우 실패
	if( eResult != eServerResult_OK_ACK)
	{
		// 실패!!!!
		return;
	}
	CKeepItemList::getInstance().setUsingItem( iItemDescNum, bOnOff );
	CTRMyRoomGoodsListDialog::getInstance().onUpdateGoodsList();
	CTRUserBookDlg::getInstance().onRecvItemOnOff();

	const CItemInfoNode* pItemInfo = CClientItemList::getInstance().getItemInfo(iItemDescNum);

	if( pItemInfo && pItemInfo->m_position == eFuncItemPosition_JEWEL_ITEM )
	{
#ifdef _SHOP_RENEWAL_
		if (CTRShopManager::getInstance().GetShopDialog())
		{
			CTRShopManager::getInstance().GetShopDialog()->updateAvatarSlotView();
		}
#endif
		if( CTRMawooShopDlg::getInstance().isVisible() )	
		{
			CTRMawooShopDlg::getInstance().updateAvatarSlotView();
			CTRMawooShopDlg::getInstance().setShowDescItemIndex(iItemDescNum);
		}
		if( CTRMyroomDlg::getInstance().isVisible() )	
		{
			CTRMyroomDlg::getInstance().updateAvatarSlotView();
			CTRMyRoomGoodsListDialog::getInstance().setShowDescItemIndex(iItemDescNum);
		}
		if( CTRShopDlg::getInstance().isVisible() )	
		{
			CTRShopDlg::getInstance().updateAvatarSlotView();
			CTRShopGoodsListDialog::getInstance().setShowDescItemIndex(iItemDescNum);
		}
	}

	else if(pItemInfo && pItemInfo->m_position == eFuncItemPosition_SKIN && !bOnOff)
	{
		const CItemInfoNode* pBasicSkinItem = CClientItemList::getInstance().getItemInfo(ItemKeyInfo(0,eFuncItemPosition_SKIN,1));
		if(pBasicSkinItem)
		{
			CNetClientManager::getInstance().requestItemOnOff(pBasicSkinItem->m_iUniqueNumber,true);
		}
	}
}

/// 로그인 대기를 해라.
void CTRNetEventHandler::onRecvNoticeWaitForLogin(const size_t iRemainUserCount, const DWORD dwEstimatedRemainTime)
{
	CTRWaitLoginUI::getInstance().onRecvNoticeWaitForLogin(iRemainUserCount, dwEstimatedRemainTime);
}

/// 남은 로그인 대기자, 대기예상 시간 정보를 받았다.
void CTRNetEventHandler::onRecvNoticeRemainUserNumAndTimeInfo(const size_t iRemainUserCount, const DWORD dwEstimatedRemainTime)
{
	CTRWaitLoginUI::getInstance().onRecvNoticeRemainUserNumAndTimeInfo(iRemainUserCount, dwEstimatedRemainTime);
}

void CTRNetEventHandler::onRecvAutoUseItemInfo( const std::map<int,int>& useInfo )
{	// 사용된 아이템 정보와 남은 갯수를 인자로 받는다.
	
	DBG_DEMO_OUTPUT("CTRNetEventHandler::onRecvAutoUseItemInfo Size=[%d]", (int)useInfo.size());

	CColor msgColor = CColor(1,0.5f,1);

	std::map<int,int>::const_iterator it;
	for( it = useInfo.begin(); it != useInfo.end(); ++it )
	{
		int uniqueNum = it->first;
		int count = it->second;
		const CItemInfoNode* pItemInfo = CClientItemList::getInstance().getItemInfo(uniqueNum);
		if( NULL == pItemInfo )
			continue;

		string strMsg;
		if( count > 0)
		{
			strMsg = format( _STR(ITEM_USE_NUMBER), pItemInfo->m_name.c_str(), 1 );
			
			CTRChattingManager::getInstance().onRecvChatMessage(strMsg,msgColor,CTRChattingManager::CHAT_ITEM_NO,true);
			strMsg = format( _STR(ITEM_REMAIN_COUNT), count );

			CKeepItemList::getInstance().modifyItemCount(uniqueNum, count);
		}
		else
		{
			strMsg = format("%s %s", _STR(ITEM_ALL_CONSUMPTION), pItemInfo->m_name.c_str() );//format(_STR(FORMAT_CHATDIALOG_MSG_USER_LOGIN), strFriendNickname.c_str());
			CKeepItemList::getInstance().eraseItem( uniqueNum );

			ItemMsgInfo info;
			info.m_nItemNum = uniqueNum;
			info.m_nDateTime = 0;
			info.m_nMsgSubType = 0;
			info.m_nMsgType = 0;
			vector<ItemMsgInfo> v;
			v.push_back( info );
			CTRItemTimeOverManager::getInstance().onRecvGetItemMsgOK(v);
		}
		CTRChattingManager::getInstance().onRecvChatMessage(strMsg,msgColor,CTRChattingManager::CHAT_ITEM_NO,true);
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(uniqueNum);
	}
}
/// 길드전에 대한 길드의 정보를 받음
void CTRNetEventHandler::onRecvGuildMatchGetGuildInfo( const eOCCUPATION_AREA_TYPE eOccupationAreaType, std::vector<GuildMatchRankInfo> rankInfo)
{
	if (CTRLobbyUI::getInstance().isActive())
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchGetGuildInfo( eOccupationAreaType, rankInfo );
	}
}

/// 길드전에 대한 길드 정보 받기 실패
void CTRNetEventHandler::onRecvGuildMatchGetGuildInfoFailed(eGuildMatchType matchType, eGuildMatchFailedReason failedReason)
{
	TRDBG_OUTPUT_ERROR("%s(line: %d) eGuildMatchType = %d eFailedReason: %d",__FUNCTION__,__LINE__,matchType,failedReason);
}

/// 길드전 최근 전적에 대한 정보를 받음
void CTRNetEventHandler::onRecvGuildMatchGetLatestInfo(eGuildMatchType matchType, std::vector<GuildMatchLatest> matchLatest)
{
	if (CTRGuildDlg::getInstance().isVisible())
	{
		CTRGuildDlg::getInstance().onRecvGuildMatchGetLatestInfo(matchType, matchLatest);
	}
	else if(CTRUserBookDlg::getInstance().isVisible())
	{
		CTRUserBookDlg::getInstance().onRecvGuildMatchGetLatestInfo(matchType, matchLatest);
	}
	else if (CTRLobbyUI::getInstance().isActive())
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchGetLatestInfo(matchType, matchLatest);
	}	
}

/// 길드전 최근 전적에 대한 정보 받기 실패
void CTRNetEventHandler::onRecvGuildMatchGetLatestInfoFailed(eGuildMatchType matchType, eGuildMatchFailedReason failedReason)
{
	TRDBG_OUTPUT_ERROR("%s(line: %d) eGuildMatchType = %d eFailedReason: %d",__FUNCTION__,__LINE__,matchType,failedReason);
}

/// 길드전 랭킹 정보를 받음
void CTRNetEventHandler::onRecvGuildMatchRankInfo(eServerResult result, eGuildMatchFailedReason failedReason, eRequestRankKind rankKind, std::vector<GuildMatchRankInfo>& rankList)
{
	IntTRUserInterface * pInterface = CTRUserInterface::getInstance().getCurrentUI();
	if(pInterface != NULL && pInterface->getUIType() == GUI_TYPE_LOBBY)static_cast<CTRLobbyUI*>(pInterface)->onRecvGuildMatchRankInfo(result,failedReason,rankKind,rankList);
}

/// 길드전 나의 길드의 랭킹 정보를 받음
void CTRNetEventHandler::onRecvGuildMatchMyGuildRankInfo(eRequestRankKind rankKind, GuildMatchRankInfo rankInfo)
{
	if (CTRLobbyUI::getInstance().isActive())
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchMyGuildRankInfo(rankKind, rankInfo);
	}
}

/// 길드전 랭킹 정보 받기를 실패했음
void CTRNetEventHandler::onRecvGuildMatchMyGuildRankInfoFailed(eRequestRankKind rankKind, eGuildMatchFailedReason failedReason)
{
	TRDBG_OUTPUT_ERROR("%s(line: %d) eRankKind = %d eFailedReason: %d",__FUNCTION__,__LINE__,rankKind,failedReason);

	IntTRUserInterface * pInterface = CTRUserInterface::getInstance().getCurrentUI();
	if(pInterface != NULL && pInterface->getUIType() == GUI_TYPE_LOBBY)static_cast<CTRLobbyUI*>(pInterface)->onRecvGuildMatchMyGuildRankInfoFailed(rankKind,failedReason);
}


/// 다음 공식 길드전 공지 정보를 받았다..
void CTRNetEventHandler::onRecvGuildMatchNoticeNextOfficialGameInfo( OlympicGameInfo& gameInfo )
{
	CTREventLeageManager::getInstance().onRecvNextOlympicGameNoticeInfo(gameInfo);

	if (CTRLobbyUI::getInstance().isActive())
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchNextOfficialGameInfo(gameInfo);
	}
}

/// 다음 공식 길드전 게임 정보를 받았다..
void CTRNetEventHandler::onRecvGuildMatchNextOfficialGameInfo( OlympicGameInfo& gameInfo )
{
	CTREventLeageManager::getInstance().onRecvNextOlympicGameInfo(gameInfo);

	if (CTRLobbyUI::getInstance().isActive())
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchNextOfficialGameInfo(gameInfo);
	}
}

/// 공식 길드전 일정이 없다
void CTRNetEventHandler::onRecvGuildMatchOfficialEmpty()
{
	CTREventLeageManager::getInstance().clearGameInfo();
	if (CTRLobbyUI::getInstance().isActive())
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchOfficialEmpty();
	}
}

/// 길드 검색을 완료하였다
void CTRNetEventHandler::onRecvGuildMatchSearchGuildPartyOK()
{

}

/// 길드전 매치 동작을 성공하였다
void CTRNetEventHandler::onRecvGuildMatchActionOK(eGuildMatchAction action)
{
	DBG_OUTPUT("CTRNetEventHandler::eGuildMatchAction_[%d]",(int)action);
}

/// 길드전 매치 동작을 실패하였다
void CTRNetEventHandler::onRecvGuildMatchActionFailed(eGuildMatchAction action, eGuildMatchFailedReason failedReason)
{
	TRDBG_OUTPUT_ERROR("CTRNetEventHandler::onRecvGuildMatchActionFailed __[%d][%d]",(int)action,(int)failedReason);
}

/// 길드전 등록을 성공
void CTRNetEventHandler::onRecvGuildMatchRegistMatchOK(eGuildMatchType matchType, const bool bAllReady)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildMatchRegistMatchOK()");

	if (m_pNetPlay != NULL && m_pNetPlay->inRoom() && isGuildMatchPartyRoom(m_pNetPlay->getGameRoomKind()))
	{
		if (bAllReady)
		{
			m_pNetPlay->getGuildMatchManager()->setCurrMatchType(matchType);
			m_pNetPlay->getGuildMatchManager()->setPlayState(eGUILD_MATCH_PLAY_STATE_COMPLETE_PARTY);
			if(m_pGameRoomUI != NULL)m_pGameRoomUI->onUpdateRoomUI();

			if (m_pNetPlay->isNetworkPlayHost())
			{
				if (eGuildMatchType_SELECT == matchType)
				{
					CNetClientManager::getInstance().requestRefreshRoomList(CChannelRoomMode::getInstance().getCurRoomKind(), 0, GUILD_MATCH_UI::CTRGameGuildMatchRoomListDlg::eMaxList, eGameMode_TEAM_MODE_ON, eSteppingMode_NOT_CHECK, eItemMode_NOT_CHECK);
				}
				else
				{
					CNetClientManager::getInstance().requestGuildMatchSearchingParty(matchType);
				}
			}
		}
		else
		{
			if(m_pNetPlay->isNetworkPlayHost())
			{
				CTRShortTimeMessage::showMessage(_STR(FAILED_START_GAME_UNPREPARED_PLAYER),1.f,-2.f,"gui\\message.gui");
			}
			if(m_pGameRoomUI != NULL)
				m_pGameRoomUI->onUpdateRoomUsers();
		}
	}
}

/// 길드전 매칭 동작에 대한 통지
void CTRNetEventHandler::onRecvGuildMatchActionNotify(eGuildMatchAction action, GuildMatchPartyInfo& partyInfo, bool bRequestParty, eRoomKind roomKind)
{
	DBG_OUTPUT("%s - action[%d], bRequestParty[%d]roomKInd[%d]", __FUNCTION__, action, bRequestParty,(int)roomKind);

	if (m_pNetPlay != NULL && m_pNetPlay->inRoom() && isGuildMatchPartyRoom(CChannelRoomMode::getInstance().getCurRoomKind()) && m_pGameRoomUI != NULL && 
		m_pGameRoomUI->getUIType() == GUI_TYPE_GUILD_MATCH_PARTYROOM)
	{
		if (eGuildMatchAction_ACCEPT == action)
		{
			if (!isGuildMatchPlayingRoom(roomKind))return;

			m_pNetPlay->getGuildMatchManager()->setPlayState(eGUILD_MATCH_PLAY_STATE_MATCH_OK);

			if (bRequestParty)
			{
				const GuildMatchPartyInfo * pInfo = m_pNetPlay->getGuildMatchManager()->getMyGuildPartyInfo();
				if (pInfo != NULL)
				{
					m_pNetPlay->getGuildMatchManager()->setMyPartyRoomServerInfo(pInfo->m_iRoomServerNum,pInfo->m_hRoom);
					m_pNetPlay->onJoinGameRoom(partyInfo.m_iRoomServerNum,partyInfo.m_hRoom,roomKind,"4321");
				}
			}
			else 
			{
				m_pNetPlay->_getGameRoomInfo().setRoomKind(roomKind);
				m_pNetPlay->openGameRoomUI();
			}
		}
		else
		{
			dynamic_cast< CGuildMatchRecvInterface* >( m_pGameRoomUI )->onRecvGuildMatchActionNotify(action, partyInfo, bRequestParty);
		}
	}
}
/// 나의 파티 정보 받기를 성공
void CTRNetEventHandler::onRecvGuildMatchMyPartyInfoOK(const bool success, GuildMatchPartyInfo & partyInfo)
{
	if (m_pNetPlay != NULL)
	{
		m_pNetPlay->onRecvGuildMatchMyPartyInfoOK(success,partyInfo);
	}
}
/// 나의 파티 정보 받기를 실패
void CTRNetEventHandler::onRecvGuildMatchMyPartyInfoFailed()
{
	TRDBG_OUTPUT_ERROR("ERROR %s(line: %d)",__FUNCTION__,__LINE__);
}
/// 길드전 상대팀 파티의 정보를 얻었다
void CTRNetEventHandler::onRecvGuildMatchOtherPartyInfoOK(const bool success, GuildMatchPartyInfo & partyInfo)
{
	if (m_pNetPlay != NULL)
	{
		m_pNetPlay->onRecvGuildMatchOtherPartyInfoOK(success,partyInfo);
	}
}

/// 나의 파티 ID 할당을 성공
void CTRNetEventHandler::onRecvGuildMatchGetPartyIDOK(const __int64 partyID)
{
//	if (m_pNetPlay != NULL && isGuildMatchChannel(CChannelRoomMode::getInstance().getCurRoomKind()))
	if (m_pNetPlay != NULL)
	{
		m_pNetPlay->getGuildMatchManager()->onRecvGuildMatchGetPartyIDOK();
	}
}

/// 나의 파티 ID 할당을 실패
void CTRNetEventHandler::onRecvGuildMatchGetPartyIDFailed(eGuildMatchFailedReason failedReason)
{
	TRDBG_OUTPUT_ERROR("ERROR %s(line: %d) : %d",__FUNCTION__, __LINE__, failedReason);

	if(m_pNetPlay)
	{
		m_pNetPlay->onRecvGuildMatchGetPartyIDFailed(failedReason);
	}
}

/// 파티의 마스터가 변경되었다
void CTRNetEventHandler::onRecvGuildMatchChangePartyMaster(const __int64 partyID, const UINT masterIndex)
{
	DBG_OUTPUT(60, "onRecvGuildMatchChangePartyMaster: iPlayerIndex=%d", masterIndex);

	if (m_pNetPlay != NULL)
	{
		m_pNetPlay->onRecvGuildMatchChangePartyMaster(partyID,masterIndex);

		if (isGuildMatchChannel(m_pNetPlay->getGameRoomKind()))
		{
			CTRUserInterface::getInstance().onUpdateRoomUsers();
		}
	}
}
void CTRNetEventHandler::onRecvGuildMatchRemakePartyWaitSceneChange(eRoomKind roomKind)
{
	if (m_pNetPlay != NULL && isGuildMatchChannel(roomKind))
	{
		m_pNetPlay->getGuildMatchManager()->onRecvGuildMatchRemakePartyWaitSceneChange(roomKind);
	}
}
/// 룸을 변경해라
void CTRNetEventHandler::onRecvGuildMatchChangeRoomKindNotify(const eRoomKind roomKind)
{
	if (m_pNetPlay != NULL && isGuildMatchChannel(roomKind))
	{
		m_pNetPlay->getGuildMatchManager()->onRecvGuildMatchChangeRoomKindNotify(roomKind);
	}
}
/// 파티 등록이 취소되었다
void CTRNetEventHandler::onRecvGuildMatchUnRegistPartyACK(const bool bSuccess)
{
	DBG_OUTPUT("%s(line: %d)",__FUNCTION__,__LINE__);

	if (m_pNetPlay != NULL && m_pNetPlay->inRoom() && m_pGameRoomUI != NULL && m_pGameRoomUI->getUIType() == GUI_TYPE_GUILD_MATCH_PARTYROOM)
	{
		//! 상대방길드와 매칭이 이루워지기 전까지만..
		eGUILD_MATCH_PLAY_STATE ePlayState = m_pNetPlay->getGuildMatchManager()->getPlayState();
		if ( ePlayState != eGUILD_MATCH_PLAY_STATE_MATCH_OK) 
		{
			m_pNetPlay->getGuildMatchManager()->setPlayState(eGUILD_MATCH_PLAY_STATE_INCOMPLETE_PARTY);
			dynamic_cast< CGuildMatchRecvInterface* >( m_pGameRoomUI )->onRecvGuildMatchUnRegistPartyACK();
			if (!bSuccess)
			{
				TRDBG_OUTPUT_ERROR("%s(line: %d)",__FUNCTION__,__LINE__);
			}
		}
	}
}
/// 길드 매치 동작을 처리한다 (취소, 거절, 수락 상황일때 실패를 대비한 같은팀의 UI닫기 처리를 위한것
void CTRNetEventHandler::onRecvGuildMatchMatchActionACK(eGuildMatchAction action)
{
	if (m_pGameRoomUI != NULL && m_pNetPlay != NULL && isGuildMatchPartyRoom(m_pNetPlay->getGameRoomKind()))
	{
		if (m_pGameRoomUI->getUIType() == GUI_TYPE_GUILD_MATCH_PARTYROOM)
		{
			dynamic_cast< CGuildMatchRecvInterface* >( m_pGameRoomUI )->onRecvGuildMatchMatchActionACK(action);
		}
	}
}

/// 매칭 시작 요청을 성공하였다
void CTRNetEventHandler::onRecvGuildMatchSearchingPartyStartACK(eGuildMatchType matchType,const bool bSuccess)
{
	DBG_OUTPUT("%s(line: %d)[%d]",__FUNCTION__,__LINE__,(int)bSuccess);

	if (m_pGameRoomUI != NULL && m_pNetPlay != NULL && isGuildMatchPartyRoom(m_pNetPlay->getGameRoomKind()))
	{
		if (m_pGameRoomUI->getUIType() == GUI_TYPE_GUILD_MATCH_PARTYROOM)
		{
			dynamic_cast< CGuildMatchRecvInterface* >( m_pGameRoomUI )->onRecvGuildMatchSearchingPartyStartACK( matchType, bSuccess );

			if (bSuccess)
			{
				m_pNetPlay->getGuildMatchManager()->setPlayState(eGUILD_MATCH_PLAY_STATE_SEARCHING_PARTY);
			}
			else
			{	
				m_pNetPlay->getGuildMatchManager()->setBooleanValue(GUILD_MATCH_CHEK_REQ_SEARCHING_PARTY,true);
			}
			m_pGameRoomUI->onUpdateRoomUI();
		}
	}
}
/// 매칭 검색을 다시 해라
void CTRNetEventHandler::onRecvGuildMatchSearchingPartyRetry()
{
	if(m_pGameRoomUI != NULL && m_pNetPlay != NULL && isGuildMatchPartyRoom(m_pNetPlay->getGameRoomKind()))
	{
		if (m_pGameRoomUI->getUIType() == GUI_TYPE_GUILD_MATCH_PARTYROOM)
		{
			m_pNetPlay->getGuildMatchManager()->setBooleanValue(GUILD_MATCH_CHEK_RE_SEARCHING_PARTY,true);
			dynamic_cast< CGuildMatchRecvInterface* >( m_pGameRoomUI )->onRecvGuildMatchSearchingPartyRetry();
		}
	}
}
/// 매칭 검색을 하려고 하는데 잘못되어 실패했다 (에러 상황)
void CTRNetEventHandler::onRecvGuildMatchSearchingPartyFailed(eGuildMatchFailedReason failedReason)
{
	TRDBG_OUTPUT_ERROR("ERROR_%s(line: %d)[%d]",__FUNCTION__,__LINE__,(int)failedReason);
}

/// 매칭 검색을 그만둔다, 매칭을 성공하지 못했다
void CTRNetEventHandler::onRecvGuildMatchSearchingMatchStop()
{
	TRDBG_OUTPUT_ERROR("%s(line: %d)",__FUNCTION__,__LINE__);

	if(m_pGameRoomUI != NULL && m_pNetPlay != NULL && isGuildMatchPartyRoom(m_pNetPlay->getGameRoomKind()))
	{
		m_pNetPlay->getGuildMatchManager()->setBooleanValue(GUILD_MATCH_CHEK_RE_SEARCHING_PARTY,false);
		m_pNetPlay->getGuildMatchManager()->setBooleanValue(GUILD_MATCH_CHEK_REQ_SEARCHING_PARTY,false);
		m_pNetPlay->getGuildMatchManager()->setPlayState(eGUILD_MATCH_PLAY_STATE_INCOMPLETE_PARTY);

		if (m_pGameRoomUI->getUIType() == GUI_TYPE_GUILD_MATCH_PARTYROOM)
		{
			dynamic_cast< CGuildMatchRecvInterface* >( m_pGameRoomUI )->onRecvGuildMatchSearchingMatchStop();
		}
	}
}
/// 매칭을 취소하였다
void CTRNetEventHandler::onRecvGuildMatchSearchingPartyCancel()
{
	if(m_pGameRoomUI != NULL && m_pNetPlay != NULL && isGuildMatchPartyRoom(m_pNetPlay->getGameRoomKind()))
	{
		m_pNetPlay->getGuildMatchManager()->setPlayState(eGUILD_MATCH_PLAY_STATE_INCOMPLETE_PARTY);
		m_pNetPlay->getGuildMatchManager()->setBooleanValue(GUILD_MATCH_CHEK_REQ_SEARCHING_PARTY,false);
		m_pNetPlay->getGuildMatchManager()->setBooleanValue(GUILD_MATCH_CHEK_RE_SEARCHING_PARTY,false);

		if (m_pGameRoomUI->getUIType() == GUI_TYPE_GUILD_MATCH_PARTYROOM)
		{
			dynamic_cast< CGuildMatchRecvInterface* >( m_pGameRoomUI )->onRecvGuildMatchSearchingPartyCancel();
		}
	}
}

/// 옵저버가 길드전 매칭룸에 따라 들어가기를 예약했다
void CTRNetEventHandler::onRecvGuildMatchObserverEnterRoomReservationOK()
{
	COkDialogEx::getInstance().showDialog(_STR(MSG_PROCESS_SUCCESS));
}
/// 옵저버가 길드전 매칭룸에 따라 들어가기 예약을 실패했다
void CTRNetEventHandler::onRecvGuildMatchObserverEnterRoomReservationFailed(eGuildMatchFailedReason failedReason)
{
	COkDialogEx::getInstance().showDialog(_STR(FAILED_EMBLEM_UNKNOWN_ERROR));
}

/// 유저가 초대해야 할 옵저버의 닉네임을 받았다
void CTRNetEventHandler::onRecvGuildMatchObserverEnterRoomData(std::string observerNickName)
{
	if (m_pNetPlay != NULL && isGuildMatchChannel(m_pNetPlay->getGameRoomKind()) && m_pNetPlay->inRoom() && m_pNetPlay->isNetworkPlayHost())
	{
		m_pNetPlay->getGuildMatchManager()->insertInviteObserverName(observerNickName);
		DBG_OUTPUT("CTRNetEventHandler::onRecvGuildMatchObserverEnterRoomData[%s]",observerNickName.c_str());
	}
}
/// 길드전 길드 메시지
void CTRNetEventHandler::onRecvGuildMatchGuildMsg(eGuildMatchType matchType, std::string& oppGuildName, bool bWinTeam, const int successiveWin)
{
	CTRUserInterface::getInstance().community_onRecvGuildMatchResultGuildMsg(matchType,oppGuildName,bWinTeam,successiveWin);
}

/// 길드매치 플레이횟수 제한 있는경우 매칭 실패 매세지
void CTRNetEventHandler::onRecvGuildMatchPlayStartLimitFailed(eGuildMatchFailedReason failedReason)
{
	DBG_OUTPUT("CTRNetEventHandler::onRecvGuildMatchPlayStartLimitFailed[%d]",failedReason);

	std::string msg = "";
	switch ( failedReason )
	{
	default:
	case eGuildMatchFailedReason_UNKNOWN:
		msg = _STR( HS_ERR_UNKNOWN );
		break;
	case eGuildMatchFailedReason_DBERROR:
		msg = _STR( FAILED_DB_ERROR );
	case eGuildMatchFailedReason_NOT_FOUND_GUILD_RANK:
		msg = _STR( MSG_FAILED_GUILD_MATCH_NOT_FOUND_GUILD_RANK );
		break;
	case eGuildMatchFailedReason_NOT_JOIN_GUILD:
		msg = _STR( MSG_FAILED_GUILD_MATCH_NOT_JOIN_GUILD );
		break;
	case eGuildMatchFailedReason_NOT_FOUND_ACCEPT_PARTY:
		msg = _STR( MSG_FAILED_GUILD_MATCH_NOT_FOUND_ACCEPT_PARTY );
		break;
	case eGuildMatchFailedReason_NOT_FOUND_REQUEST_PARTY:
		msg = _STR( MSG_FAILED_GUILD_MATCH_NOT_FOUND_REQUEST_PARTY );
		break;
	case eGuildMatchFailedReason_NOT_FOUND_ROOM_SERVER:
		msg = _STR( MSG_FAILED_GUILD_MATCH_NOT_FOUND_ROOM_SERVER );
		break;
	case eGuildMatchFailedReason_DONT_MATCH_ACTION_PROCESS:
		msg = _STR( MSG_FAILED_GUILD_MATCH_DONT_MATCH_ACTION_PROCESS );
		break;
	case eGuildMatchFailedReason_INVALID_MATCH_TYPE:
		msg = _STR( MSG_FAILED_GUILD_MATCH_INVALID_MATCH_TYPE );
		break;
	case eGuildMatchFailedReason_NOT_USE_GUILDMATCH:
		msg = _STR( MSG_FAILED_GUILD_MATCH_NOT_USE_GUILDMATCH );
		break;
	case eGuildMatchFailedReason_PARTY_MAX_COUNT_OVER:
		msg = _STR( MSG_FAILED_GUILD_MATCH_PARTY_MAX_COUNT_OVER );
		break;
	case eGuildMatchFailedReason_MATCHING_PLAYER_GUILD:
		msg = _STR( MSG_FAILED_GUILD_MATCH_MATCHING_PLAYER_GUILD );
		break;
	case eGuildMatchFailedReason_PLAY_LIMIT_COUNT:
		msg = _STR( MSG_FAILED_GUILD_MATCH_PLAY_LIMIT_COUNT );
		break;
	case eGuildMatchFailedReason_SCHEDULE_OFF:
		msg = _STR( MSG_FAILED_GUILD_MATCH_INVALID_ERR );
		break;
	case eGuildMatchFailedReason_CLOSE_CHANNEL:
		msg = _STR( MSG_FAILED_GUILD_MATCH_CLOSE_CHANNEL );		
		break;
	}

	CTRShortTimeMessage::showMessage( msg, 1.5f );
}

#ifdef _RAINBOW_LEAGUE
///< 레인보우 리그 유저정보를 받았다
void CTRNetEventHandler::onRecvRainbowGetUserInfoOK(RainbowLeagueUserInfo & userInfo)
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueUserInfoAck(userInfo);
}

void CTRNetEventHandler::onRecvRainbowGetUserInfoFailed(eRainbowLeagueFailedReason failedReason)
{
	DBG_OUTPUT("onRecvUserInfoFailed");
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueFailed(failedReason);
}

///< 배치 결과를 받았다
void CTRNetEventHandler::onRecvRainbowGetDispositionResultOK(bool bIsResult, eRainbowLeagueType leagueType, int iTotalPoint)
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueDispositionResultAck(bIsResult, leagueType, iTotalPoint);
}

void CTRNetEventHandler::onRecvRainbowGetDispositionResultFailed(eRainbowLeagueFailedReason failedReason)
{
	DBG_OUTPUT("onRecvDispositionResultFailed");
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueFailed(failedReason);
}

///< 명예, 업적보상 지급
void CTRNetEventHandler::onRecvRainbowDispositionRewardOK(eLevelUPKind rewardType, eRainbowLeagueKind leagueKind, int rewardLevel, std::vector<RewardInfo> & vecRewardInfo)
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowDispositionRewardOK(rewardType,leagueKind,rewardLevel,vecRewardInfo);
}

void CTRNetEventHandler::onRecvRainbowDispositionRewardFailed(eRainbowLeagueFailedReason failedReason)
{
	DBG_OUTPUT("onRecvDispositionRewardFailed");
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueFailed(failedReason);
}

///< 레인보우 리그 경기 기록 을 받았다
void CTRNetEventHandler::onRecvRainbowGetLatestRecordOK(int iMapNum, RainbowLeagueLatestInfo & latestInfo, eRainbowLeagueKind matchKind, eRainbowLeagueType matchType, int iPoint)
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueGetLatestRecordAck(iMapNum, latestInfo, matchKind, matchType, iPoint);
}

void CTRNetEventHandler::onRecvRainbowGetLatestRecordFailed(eRainbowLeagueFailedReason failedReason)
{
	DBG_OUTPUT("onRecvLatestRecordFailed");
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueFailed(failedReason);
}

///< 매칭 미니게임 시작을 받았다
void CTRNetEventHandler::onRecvRainbowMiniGameStartOK()
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueMiniGameStart();
}

void CTRNetEventHandler::onRecvRainbowMiniGameStartFailed(eRainbowLeagueFailedReason failedReason)
{
	DBG_OUTPUT("onRecvRainbowMiniGameStartFailed");
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueFailed(failedReason);
}

///< 매칭 미니게임 결과를 받았다
void CTRNetEventHandler::onRecvRainbowMiniGamePointOK(exp_type iExp, int iGameMoney)
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowMiniGamePointOK(iExp, iGameMoney);
}

void CTRNetEventHandler::onRecvRainbowMiniGamePointFailed(eRainbowLeagueFailedReason failedReason)
{
	DBG_OUTPUT("onRecvMiniGamePointFailed");
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueFailed(failedReason);
}


/// 경쟁 리그 배치 받기 결과를 받았다
void CTRNetEventHandler::onRecvRainbowLeagueKindChangeAck(eRainbowLeagueKind leagueKind, eRainbowLeagueType leagueType, std::vector<RewardInfo> & vecConsumeList) 
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueKindChangeAck(leagueKind,leagueType,vecConsumeList);
}

void CTRNetEventHandler::onRecvRainbowLeagueKindChangeFailed(eRainbowLeagueFailedReason failedReason)
{
	DBG_OUTPUT("onRecvLeagueKindChangeFailed");
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueFailed(failedReason);
}

///< 대전하기 요청이 성공하였다
void CTRNetEventHandler::onRecvRainbowLeagueSearchingDoingAck(int iEntryTime)
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueSearchingDoingAck(iEntryTime);
}

///< 대전하기 다시 요청을 해라
void CTRNetEventHandler::onRecvRainbowLeagueSearchingRetry()
{
	COkDialogEx::getInstance().showDialog("다시 요청해주세요.","gui\\ok.gui");
}

///< 마땅한 상대를 찾지 못했다(서버가 클라에게 그만하라고 알린다)
void CTRNetEventHandler::onRecvRainbowLeagueSearchingMatchStop()
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueSearchingMatchStop();
}

///< 대전 상대 못찾은게 아니라 뭔가가 잘못되어 에러처리 된 상황
void CTRNetEventHandler::onRecvRainbowLeagueSearchingFailed(eRainbowLeagueFailedReason failedReason)
{
	DBG_OUTPUT("onRecvSearchingFailed");
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueFailed(failedReason);
}

///< 레인보우 파티 정보를 알려준다
void CTRNetEventHandler::onRecvRainbowLeagueMyPartyInfoNotify(RainbowLeaguePartyInfo & partyInfo)
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueMyPartyInfoNotify(partyInfo);
}

///< 레인보우 파티 마스터에게 알려준다. 방을 만들어라
void CTRNetEventHandler::onRecvRainbowLeagueActionNotify(eRainbowLeaguePartyState state, int iMatchingPointAVG)
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueActionNotify(state, iMatchingPointAVG);
}

///< 레인보우 맵 최고 기록을 받았다
void CTRNetEventHandler::onRecvRainbowLeagueTopRecordNotify(int iClearTime)
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueTopRecordNotify(iClearTime);
}

///< 대전하기 유저의 취소에 의해 그만둔다
void CTRNetEventHandler::onRecvRainbowLeagueSearchingCancel()
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueSearchingCancel();
}

///< 레인보우 패널티 정보를 받았다
void CTRNetEventHandler::onRecvRainbowLeaguePenaltyNotify(int restrictTime)
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeaguePenaltyNotify(restrictTime);
}

///< 레인보우 패널티 결과정보를 받았다
void CTRNetEventHandler::onRecvRainbowLeaguePenaltyResultNotify(eRainbowLeagueKind matchKind, eRainbowLeagueType matchType, eRainbowLeagueResult rainbowLeagueResult, int iResultPoint
#ifdef _CHAMPIONS_CUP
																, bool bIsAddPlayCount
#endif
																)
{
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeaguePenaltyResultNotify(matchKind, matchType, rainbowLeagueResult, iResultPoint
#ifdef _CHAMPIONS_CUP
		, bIsAddPlayCount
#endif
		);
}

///< 레인보우 랭킹 요청
void CTRNetEventHandler::onRecvRainbowLeagueRankInfo(eServerResult result, eRainbowLeagueFailedReason failedReason, eRequestRankKind rankKind, eRankDetailKind rankDetailKind, const std::vector<RainbowLeagueRankInfo> & rankInfo)
{
	if(rankKind == eRequestRankKind_RAINBOWLEAGUE)
	{
		CTRRankUI::getInstance().onRecvRainbowLeagueRankInfo(rankKind, rankDetailKind, rankInfo);
	}
	else if(rankKind == eRequestRankKind_RAINBOWLEAGUE_MINIGAME)
	{
		RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvMiniGameRank(rankInfo);
	}
}

///< 나의 레인보우 랭킹 결과
void CTRNetEventHandler::onRecvRainbowLeagueMyRankInfo(eRequestRankKind rankKind, eRankDetailKind rankDetailKind, RainbowLeagueRankInfo & rankInfo)
{
	CTRRankUI::getInstance().onRecvRainbowLeagueMyRankInfo(rankKind, rankDetailKind, rankInfo);
}

void CTRNetEventHandler::onRecvRainbowLeagueMyRankInfoFailed(eRequestRankKind rankKind, eRankDetailKind rankDetailKind, eRainbowLeagueFailedReason failedReason)
{
	CTRRankUI::getInstance().onRecvRainbowLeagueMyRankInfoFailed(rankKind, rankDetailKind, failedReason);
	RainbowLeague::CTRRainbowLeagueManager::getInstance().onRecvRainbowLeagueFailed(failedReason);
}

#endif


/// 튜토리얼 코드 (Agent 서버에 데이터를 DB에 저장하도록 요청에 대한 성공 결과를 받았다.)
void CTRNetEventHandler::onRecvTutorialInsertMyData(std::string strValue, int iValue){}

/// 튜토리얼 코드 (Agent 서버에 데이터를 DB에 저장하도록 요청에 대한 실패 결과를 받았다.)
void CTRNetEventHandler::onRecvTutorialInsertMyDataFailed(eServerResult eResult){}

/// 튜토리얼 코드 (Room 서버에 데이터를 DB에 갱신에 대한 성공 결과를 받았다.)
void CTRNetEventHandler::onRecvTutorialUpdateMyDataFailed(std::string strValue, int iValue){}

/// 튜토리얼 코드 (Room 서버에 데이터를 DB에 갱신에 대한 실패 결과를 받았다.)
void CTRNetEventHandler::onRecvTutorialUpdateMyDataFailed(eServerResult eResult){}

/// 튜토리얼 코드 (친구에게 데이터를 받았다.)
void CTRNetEventHandler::community_onRecvTutorialSendMyDataToFriend(const std::string& strFromNickname, std::string strValue, int iValue){}

/// 어떤 허그유저가 추천인으로 등록한것을 알린다.
void CTRNetEventHandler::community_onRecvHugSystemRecommendUser(const std::string & strFromNickname )
{
	CTRHugSystemManager::getInstance().community_onRecvHugSystemRecommendUser(strFromNickname);
}

/// 추천인이 레벨업을 했다고 알려준다.
void CTRNetEventHandler::community_onRecvHugSystemLevelUp(const std::string & strFromNickname, short iHugLevel, eHugUserType eUserType )
{
	CTRHugSystemManager::getInstance().community_onRecvHugSystemLevelUp(strFromNickname, iHugLevel, eUserType);

	if (!CGameManager::getInstance().isPlaying())
	{
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_UNIQUE_USER_COUNT);
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();
	}
}

/// 피추천인이 추천인을 삭제했다고 알려준다.
void CTRNetEventHandler::community_onRecvHugSystemRemoveRecommendUser(const std::string & strFromNickname )
{
	CTRHugSystemManager::getInstance().community_onRecvHugSystemRemoveRecommendUser(strFromNickname);
}
/// 추천해준 유저중 유니크 유저가 된 유저수를 받았다.
void CTRNetEventHandler::onRecvHugSystemGetUniqueUserCountOK(short iUniqueUserCount)
{
	if (!CGameManager::getInstance().isPlaying())
	{
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_UNIQUE_USER_COUNT);
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();
	}
}
/// 추천해준 유저중 유니크 유저가 된 유저수를 받는데 실패했다.
void CTRNetEventHandler::onRecvHugSystemGetUniqueUserCountFailed(eHugSystemFailed failReason)
{
	CTRHugSystemManager::getInstance().onRecvHugSystemGetUniqueUserCountFailed(failReason);
}

/// 레벨업 경험치에 대한 정보를 받았다
void CTRNetEventHandler::onRecvLevelUPInfo(std::map<eLevelUPKind, LevelUPExp>& levelUPInfo)
{
	if(levelUPInfo.empty())return;

	CTRRankInfoManager::getInstance().onRecvLevelUPInfo(levelUPInfo);
}
//! 팜 수확물에서 수확을 성공하였다
void CTRNetEventHandler::onRecvFarmHarvestCropHarvestOK(__int64 & farmItemID, std::vector<RewardInfo> & rewardList)
{
	if (m_pNetPlay != NULL && m_pNetPlay->isMyFarmRoom())
	{
		if (rewardList.empty())
		{
			TRDBG_OUTPUT_ERROR("onRecvFarmHarvestCropHarvestOK[%d]",rewardList.size());
		}
		else
		{
			CTRFarmItemObjectManager::getInstance().onRecvFarmHarvestCropHarvestOK(farmItemID,rewardList);

			const int nInstallCount = CTRFarmItemObjectManager::getInstance().getValueByEmblemMissionCondition(eMissionConditionType_INSTALL_HARVESTABLE_FARM_ITEM);
			if(nInstallCount > 0)
			{	
				CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_INSTALL_HARVESTABLE_FARM_ITEM, nInstallCount);
				CMissionMsgDispatcher::getInstance().checkCompleteCondition();
			}

			//!< 수확 관련 컨디션 체크
			const int itemNum = CTRFarmItemObjectManager::getInstance().getFarmItemDescNum(farmItemID);
			const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(itemNum);
			if(pItem)
			{
				const eFarmItemPosition farmItemPosition = static_cast<eFarmItemPosition>(pItem->m_pFarmItemInfo->getFarmPosition());
				switch(farmItemPosition)
				{
				case eFarmItemPosition_FARM_TIME_HARVEST_OBJECT:
					CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HARVEST_FARM);
					CMissionMsgDispatcher::getInstance().checkCompleteCondition();
					break;

				case eFarmItemPosition_FARM_BUILDING:
					CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_FARM_BUILDING_HARVEST, itemNum);
					CMissionMsgDispatcher::getInstance().checkCompleteCondition();
					break;
				}
			}
		}
	}
}
//! 팜 수확물에서 수확을 실패하였다
void CTRNetEventHandler::onRecvFarmHarvestCropHarvestFailed(__int64& farmItemID)
{
	TRDBG_OUTPUT_ERROR("CTRNetEventHandler::onRecvFarmHarvestCropHarvestFailed");
}

//! 팜 생산 건물에서 아이템 생성을 성공하였다
void CTRNetEventHandler::onRecvFarmHarvestBuildingMakeItemAcOK( const __int64 buildingItemID, const int makeItemNum )
{
	CTRFarmItemObjectManager::getInstance().onRecvFarmHarvestBuildingMakeItemAcOK(buildingItemID, makeItemNum);
	if (m_pNetPlay != NULL && m_pNetPlay->isMyFarmRoom())
		CTRFarmUI::getInstance().onRecvFarmHarvestBuildingMakeItemAcOK(buildingItemID, makeItemNum);
}

//! 팜 생산 건물에서 아이템 생성을 실패하였다
void CTRNetEventHandler::onRecvFarmHarvestBuildingMakeItemFailed( const __int64 buildingItemID )
{
	TRDBG_OUTPUT_ERROR("%s - buildingItemID : %I64d", __FUNCTION__, buildingItemID);
}

/// Shutdown 공지를 받았다.
void CTRNetEventHandler::onRecvShutdownNotify(eShutdownNotification eNotification, const std::string& strServerMessage)
{
	if( !strServerMessage.empty() )
	{
		CTRFatalErrorUI::showScreen(_STR(PROGRAM_TERMINATE) ,strServerMessage ,false, "gui\\fatalerror01.gui");
	}
	else if (!CNetClientManager::getInstance().getMyNickname().empty())
	{
		if( strServerMessage.empty() )
		{
			switch(eNotification)
			{
			case eShutdownNotification_Expired:
			case eShutdownNotification_NoPlayTime:
				CTRFatalErrorUI::showScreen(_STR(PROGRAM_TERMINATE),_STR(MSG_POSITIVE_SHUTDOWNSYSTEM_NOTICE),false,"gui\\fatalerror01.gui");
				break;

			case eShutdownNotification_InvalidUser:
			case eShutdownNotification_UNKnown:
				break;

			case eShutdownNotification_Forced_Shutdown:
				CTRFatalErrorUI::showScreen(_STR(PROGRAM_TERMINATE),stringutil::format(_STR(MSG_SHUTDOWNSYSTEM_NOTICE_END),
					atoi(CNetClientManager::getInstance().getServerSetting("ShutDownSystemLimitAge","16").c_str())),false,"gui\\fatalerror01.gui");
				break;
			}
		}
	}
}
void CTRNetEventHandler::onRecvCardPackOpenReward(const int cardPackNum, const short openType, std::vector<RewardInfo> & vRewardItem)
{
	CTRUserBookDlg::getInstance().onRecvOpenCardPack(cardPackNum,openType,vRewardItem);

	if(!vRewardItem.empty()) CTRRewardManager::getInstance().getReward(vRewardItem, true);
}

void CTRNetEventHandler::onRecvCardPackOpenFailed( eCardPackOpenRewardFailedReason failedreason )
{
	string	err_msg = "";
	switch(failedreason)
	{
	case eCardPackOpenRewardFailedReason_UNKWON:	//<알수없는 에러
		TRDBG_OUTPUT_ERROR("eCardPackOpenRewardFailedReason_UNKWON");
		err_msg = _STR(HS_ERR_UNKNOWN); break;
	case eCardPackOpenRewardFailedReason_Invalid_CardPack:	//<유효하지 않는 카드 번호
		TRDBG_OUTPUT_ERROR("eCardPackOpenRewardFailedReason_Invalid_CardPack");
		err_msg = _STR(MSG_CARDPACK_INVALID_CARDPACK); break;
	case eCardPackOpenRewardFailedReason_NO_NEED_ITEM:	//<필요한 아이템이 없다.
		TRDBG_OUTPUT_ERROR("eCardPackOpenRewardFailedReason_NO_NEED_ITEM");
		err_msg = _STR(MSG_CARDPACK_NO_NEED_ITEM); break;
	case eCardPackOpenRewardFailedReason_NO_NEED_TR:	//<필요한 TR이 부족하다.
		TRDBG_OUTPUT_ERROR("eCardPackOpenRewardFailedReason_NO_NEED_TR");
		err_msg = _STR(ERR_NO_TR_MONEY_BREAK); break;
	case eCardPackOpenRewardFailedReason_GIVE_REWARD_ERROR:	//<보상 과정에서 에러 발생
		TRDBG_OUTPUT_ERROR("eCardPackOpenRewardFailedReason_GIVE_REWARD_ERROR");
		err_msg = _STR(FAILED_CHAOS_REWARD_EXCHANGE_FAILED); break;
	case eCardPackOpenRewardFailedReason_DB_TIME_ERROR:	//<DB 허용 시간 허용
		TRDBG_OUTPUT_ERROR("eCardPackOpenRewardFailedReason_DB_TIME_ERROR");
		err_msg = _STR(FAILED_DB_ERROR); break;
	case eCardPackOpenRewardFailedReason_Invalid_OpenType:	//<해당 아이템팩에 존재하지 않는 열기 타입이다.
		TRDBG_OUTPUT_ERROR("eCardPackOpenRewardFailedReason_Invalid_OpenType");
		err_msg = _STR(MSG_CARDPACK_INVALID_OPENTYPE); break;
	}

	CTRShortTimeMessage::showMessage(err_msg, 1.5f);
}

// 다른 유저가 닉네임을 변경했다고 받았다.
void CTRNetEventHandler::onRecvNickNameChangeNotify(const std::string& strNewNickName, const std::string& strOldNickName)
{
	if(CMessengerChatBufferManager::getInstance().onRecvNickNameChangeNotify(strNewNickName, strOldNickName))
	{
		CTRChattingDialog::getInstance().onRecvNickNameChangeNotify(strNewNickName, strOldNickName);
	}
	CTRMessengerMainUI::getInstance().update(true);
}


/// 게임룸안에 있는 사용자의 어시스트 아이템 정보가 바뀌었다.
void CTRNetEventHandler::onRecvChangeUserAssistItems( std::vector< AssistItemBuyInfo > & assistItemBuyInfo )
{
	DBG_OUTPUT("%s - size : %d", __FUNCTION__, assistItemBuyInfo.size());
	if (m_pNetPlay != NULL)
	{
		m_pNetPlay->onRecvChangeUserAssistItems(assistItemBuyInfo);
	}

	CTRUserInterface::getInstance().onRecvChangeUserAssistItems();
}

/// 스패셜 어시스트 아이템을 받았다.
void CTRNetEventHandler::onRecvSpecialAssistItem( const std::vector < int > & assistItems )
{
	if (m_pNetPlay != NULL && m_pNetPlay->inRoom() == true)
	{
		IntTRUserInterface * pInterface = CTRUserInterface::getInstance().getCurrentUI();
		if(pInterface )
		{
			CTRGameRoomUIBase * pGameRoomUIBase = (CTRGameRoomUIBase *)pInterface;

			pGameRoomUIBase->onRecvSpecialAssistItem(assistItems);
		}	
	}
}

/// 어시스트 아이템을 사용했다.
void CTRNetEventHandler::onRecvUseAssistItem( int iPlayerIndex, int iItemID )
{
	CTRUserInterface::getInstance().onUseAssistItem(iPlayerIndex, iItemID);
}

/// 어시스트 아이템을 사용하는데 실패하였다.
void CTRNetEventHandler::onRecvUseAssistItemFailed( int iPlayerIndex, int iItemID )
{
	// 어시스트 아이템의 경우 클라이언트에서 무조건 사용을 하기 때문에 호출해준다.
	CTRUserInterface::getInstance().onUseAssistItem(iPlayerIndex, iItemID);}

//////////////////////////////////////////////////////////////////////////
// GM 경고 메시지
void CTRNetEventHandler::onRecvGMWarningMsg( std::string& msg )
{
	COkDialogEx::getInstance().showDialog(msg);
}

#ifdef COUNTERATTACK_OF_ANUBIS
// 아누비스의 역습
///경기가 시작되서 현재 웨이브 정보를 받았다.
void CTRNetEventHandler::onRecvAnubisStartGame(const AnubisWaveInfo& waveInfo)
{
	CTRAnubisUIManager & anubisUIManager = CTRAnubisUIManager::getInstance();
	CTRAnubisManager & AnubisManager = CTRAnubisManager::getInstance();
	CTRLobbyUI & lobbyUI = CTRLobbyUI::getInstance();
	
	if (waveInfo.m_eWaveGrade != eAnubisWaveGrade_NONE)
	{
		AnubisManager.onRecvAnubisStartGame();
		
		if (lobbyUI.isActive()) anubisUIManager.onRecvAnubisStartGame();
	}
	else
	{
		AnubisManager.onRecvAnubisResetGame();
		AnubisManager.clear();
		if (lobbyUI.isActive())
		{
			lobbyUI.anubisGateVisiblefalse();
			
			anubisUIManager.closeDialog();
			anubisUIManager.closeEffectDialog();
		}
	}

	CNetClientManager::getInstance().requestAnubisGetRemainGateCount();
}

///진행중인 웨이브가 종료 되었다.
void CTRNetEventHandler::onRecvAnubisEndGame(eAnubisGameResult eResult)
{
	CTRLobbyUI & lobbyUI = CTRLobbyUI::getInstance();
	if (lobbyUI.isActive()) lobbyUI.anubisGateVisiblefalse();

	CTRAnubisManager::getInstance().onRecvAnubisEndGame(eResult);
	CTRAnubisUIManager::getInstance().onRecvAnubisEndGame(eResult);
}

///게임 시작 예정 공지를 받았다.
void CTRNetEventHandler::onRecvAnubisNextGameNotify(eAnubisWaveGrade eWaveGrade)
{
	CTRAnubisManager::getInstance().onRecvAnubisNextGameNotify(eWaveGrade);
	CNetClientManager::getInstance().requestAnubisGetRemainGateCount();
}

///룸 리스트를 받았다.
void CTRNetEventHandler::onRecvAnubisGetGateList(const std::vector<AnubisGateInfo>& roomList)
{
	CTRAnubisManager::getInstance().onRecvAnubisGetGateList(roomList);
}

///남은 게이트 갯수를 받았다.
void CTRNetEventHandler::onRecvAnubisGetRemainGateCount( const int iRemainGateCount )
{
	CTRAnubisUIManager::getInstance().setAnubisGateListCount(iRemainGateCount);
}

///게이트 클리어 공지를 받았다.
void CTRNetEventHandler::onRecvAnubisGateClearNotify(const eRoomKind roomKind, const int iGateNum)
{
	CTRAnubisManager::getInstance().onGateDeleteLeaveRoom(roomKind, iGateNum);
	CNetClientManager::getInstance().requestAnubisGetRemainGateCount();
}

#endif //COUNTERATTACK_OF_ANUBIS


#ifdef SMART_CHANNEL_SYSTEM

void CTRNetEventHandler::onRecvSmartChannelScheduleInfo(std::map<time_type, time_type> & scheduleInfo)
{
	m_pNetPlay->onRecvSmartChannelScheduleInfo(scheduleInfo);
}

void CTRNetEventHandler::onRecvSmartChannelModeInfo(std::map<int/*modeNum*/, SmartChannel> & channelinfo)
{
	m_pNetPlay->onRecvSmartChannelModeInfo(channelinfo);
}

void CTRNetEventHandler::onRecvSmartChannelUserInfo(bool result, UserSmartChannel& userChannelInfo)
{
	m_pNetPlay->onRecvSmartChannelUserInfo(result, userChannelInfo);
}

#endif

#ifdef _SCHOOL_BATTLE
void CTRNetEventHandler::onRecvSchoolBattleMyInfo(const SchoolBattleInfo& info, eSchoolBattleResult result)
{
	if (result == eSchoolBattleResult_OK)
	{
		m_pNetPlay->onRecvSchoolBattleMyInfo(info);
	}

	CTRLobbyUI::getInstance().onRecvSchoolBattleMyInfo(result);
}

void CTRNetEventHandler::onRecvSchoolBattleTopRank(const std::vector<SchoolBattleInfo>& topTenRank, eSchoolBattleResult result)
{
	CTRLobbyUI::getInstance().onRecvSchoolBattleTopRank(topTenRank, result);
}
#endif

void CTRNetEventHandler::onRecvRoomKindPenaltyInfo(std::map<eRoomKind, int>& penaltyInfo)
{
	m_pNetPlay->onRecvRoomKindPenaltyInfo(penaltyInfo);
}

/// 아이템을 사용했다.
void CTRNetEventHandler::onRecvAssaultModeUseItemOK( const int iItemDescNum, const int iItemCount )
{
	CKeepItemList::getInstance().modifyItemCount(iItemDescNum, iItemCount);
}

///NPC정보를 세팅하는데 성공했다.
void CTRNetEventHandler::onRecvAssaultModeSetObjectInfoOK(const std::vector<AssaultModeObjectInfo> & objectInfo)
{
	CGameManager::getInstance().onRecvAssaultModeSetObjectInfoOK(objectInfo);
}

///NPC정보를 세팅하는데 실패했다.
void CTRNetEventHandler::onRecvAssaultModeSetObjectInfoFailed( const std::vector<int> & fail_list )
{
	std::string strTemp = "[";
	for (size_t i = 0; i < fail_list.size(); ++i)
	{
		strTemp += format("%d, ", fail_list[i]);
	}
	strTemp += "]";

	TRDBG_OUTPUT_ERROR("%s_%d_%d_%s",__FUNCTION__,__LINE__, fail_list.size(), strTemp.c_str());
}

///캐릭터 에너지를 세팅했다.
void CTRNetEventHandler::onRecvAssaultModeSetCharacterEnergyInfo(const std::map<int/*playerIndex*/, int/*energy*/>& playerList)
{
	CGameManager::getInstance().onRecvAssaultModeSetCharacterEnergyInfo(playerList);
}


///캐릭터의 에너지가 차감됐다.
void CTRNetEventHandler::onRecvAssaultModeDecreaseCharacterEnergyOK(const int iPlayerIndex, const int iEnergy)
{
	CGameManager::getInstance().onRecvAssaultModeDecreaseCharacterEnergyOK(iPlayerIndex, iEnergy);
}

///캐릭터의 에너지 차감에 실패했다.
void CTRNetEventHandler::onRecvAssaultModeDecreaseCharacterEnergyFailed(const int iObjectNum, const int flag)
{
	TRDBG_OUTPUT_ERROR("%s_%d == [%d]",__FUNCTION__,__LINE__,iObjectNum + 123);
}

///캐릭터의 에너지를 충전에 성공 / 실패..
void CTRNetEventHandler::onRecvAssaultModeChargeCharacterEnergyResult(const int nResultValue,const int nPlayerIndex,const int nEnergy)
{
	if (nResultValue == ASSAULT_MODE_CHARGE_CHARACTER_ENERGY_RESULT_OK)
	{
		CGameManager::getInstance().onRecvAssaultModeChargeCharacterEnergyOK(nPlayerIndex,nEnergy);
	}
	else
	{
		TRDBG_OUTPUT_ERROR("%s_%d == [%d]",__FUNCTION__,__LINE__,nResultValue);
	}
}
///NPC의 에너지가 차감됐다.
void CTRNetEventHandler::onRecvAssaultModeDecreaseObjectEnergyOK(const int iPlayerIndex, const int iObjectNum, const int iEnergy, const int iDelta, int iAttacker)
{
	CGameManager::getInstance().onRecvAssaultModeDecreaseObjectEnergyOK(iPlayerIndex,iObjectNum, iEnergy, iDelta, iAttacker);
}

///NPC의 에너지 차감에 실패했다.
void CTRNetEventHandler::onRecvAssaultModeDecreaseObjectEnergyFailed(const int iObjectNum)
{
	TRDBG_OUTPUT_ERROR("%s_%d==[%d]",__FUNCTION__,__LINE__,iObjectNum + 123);
}

///NPC 보상 정보를 받았다.
void CTRNetEventHandler::onRecvAssaultModeGetObjectRewardInfo(const int iObjectNum, const std::vector<AssaultModeGotRewardInfo>& rewardInfo)
{
	CGameManager::getInstance().onRecvAssaultModeGetObjectRewardInfo(iObjectNum,rewardInfo );
}

///NPC의 에너지가 충전되었다.
void CTRNetEventHandler::onRecvAssaultModeChargeObjectEnergy(std::vector<std::pair<int,int> > & vecObjectChargeEnergyInfo)
{
	CGameManager::getInstance().onRecvAssaultModeChargeObjectEnergy(vecObjectChargeEnergyInfo);
}

///NPC의 에너지충전에 실패하였다.
void CTRNetEventHandler::onRecvAssaultModeChargeObjectEnergyFailed(std::vector<int> & list)
{
	TRDBG_OUTPUT_ERROR("%s_%d==[%d]",__FUNCTION__,__LINE__, list.size());
}

///아이템 획득 성공.
void CTRNetEventHandler::onRecvAssaultModeEatItemOK(const AssaultModeGotRewardInfo& rewardInfo)
{
	CGameManager::getInstance().onRecvAssaultModeEatItemOK(rewardInfo);
}

///아이템 획득 실패.
void CTRNetEventHandler::onRecvAssaultModeEatItemFailed()
{
	DBG_OUTPUT("onRecvAssaultModeEatItemFailed");
}

///부활 아이템을 사용했다.
void CTRNetEventHandler::onRecvAssaultModeRebirthOK(const int iPlayerIndex, const int iEnergy,const eAssaultModeRebirthType eFlag)
{
	CGameManager::getInstance().onRecvAssaultModeRebirthOK(iPlayerIndex, iEnergy,eFlag);
}

///부활 아이템 사용에 실패했다.
void CTRNetEventHandler::onRecvAssaultModeRebirthFailed(eAssaultModeUseItemFailed eFailed,const eAssaultModeRebirthType eFlag)
{
	switch (eFailed)
	{
	case eAssaultModeUseItemFailed_NOT_FOUNT_ITEM:
		CTRShortTimeMessage::showMessage(_STR(MSG_REVIVAL_STONE_ITEM_NO_EXIST), 1.5f);
		break;

	case eAssaultModeUseItemFailed_END_GAME:
		CTRShortTimeMessage::showMessage(_STR(MSG_REVIVAL_STONE_NO_USE_GAMEOVER), 1.5f);
		break;
		
	case eAssaultModeUseItemFailed_NO_GAME_OVER:	
	case eAssaultModeUseItemFailed_DB_ERROR:
	default:
		DBG_OUTPUT("%s eFailed = %d", __FUNCTION__, eFailed);
	}
}

void CTRNetEventHandler::onRecvQuestUserInfo(eQuestServerResult result, const bool bComplete, QuestUserInfoMap& questUserInfoMap)
{
	DBG_OUTPUT(DBG_TYPE_QUEST, "onRecvQuestUserInfo - result[%d], size[%d]", result, questUserInfoMap.size());

	switch(result)
	{
	case eQuestServerResult_OK:
		CTRQuestManager::getInstance().onRecvQuestUserInfo(bComplete, questUserInfoMap);
		break;
	case eQuestServerResult_DBERROR:
		break;
	case eQuestServerResult_NOT_EXIST_QUESTNUM:
		break;
	case eQuestServerResult_ALREADY_PROCEEDING:
		break;
	case eQuestServerResult_NOT_ENOUGH_EXP:
		break;
	case eQuestServerResult_NOT_COMPLETE_PRECEDE_QUEST:
		break;
	case eQuestServerResult_NOT_ENOUGH_ITEM_COUNT:
		break;
	case eQuestServerResult_NOT_PROCEEDING_QUEST:
		break;
	case eQuestServerResult_COMPLETE_COUNT_OVER:
		break;
	}
}

/// 퀘스트 도전에 대한 결과
void CTRNetEventHandler::onRecvQuestAddAck(eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList)
{
	DBG_OUTPUT(DBG_TYPE_QUEST, "onRecvQuestAddAck - result[%d], num[%d]", result, questNum);

	switch(result)
	{
	case eQuestServerResult_OK:
		CTRQuestManager::getInstance().onRecvAddProcessQuestWithReward(questNum, rewardList);
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_QUEST_ACCEPTED, questNum);
		CMissionMsgDispatcher::getInstance().checkCompleteCondition();
		break;
	default:
		_processQuestServerResultFailed(result);
	}
}

/// 퀘스트 포기에 대한 결과
void CTRNetEventHandler::onRecvQuestRemoveAck(eQuestServerResult result, const int questNum)
{
	DBG_OUTPUT(DBG_TYPE_QUEST, "onRecvQuestRemoveAck - result[%d], num[%d]", result, questNum);

	switch(result)
	{
	case eQuestServerResult_OK:
		CTRQuestManager::getInstance().removeProcessQuest(questNum, true);
		CTRUserBookDlg::getInstance().onRecvQuestRemoveAck(questNum);
		break;
	default:
		_processQuestServerResultFailed(result);
	}
}

/// 퀘스트 완료에 대한 결과
void CTRNetEventHandler::onRecvQuestRewardAck(eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList)
{
	DBG_OUTPUT(DBG_TYPE_QUEST, "onRecvQuestRewardAck - result[%d], num[%d]", result, questNum);

	switch(result)
	{
	case eQuestServerResult_OK:
		CTRQuestManager::getInstance().onRecvQuestRewardAck(questNum, rewardList);
		break;
	default:
		_processQuestServerResultFailed(result);
	}
}

/// 이벤트 퀘스트 정보 수신
void CTRNetEventHandler::onRecvQuestEventNotify(bool bActive, std::set<int>& questNumList)
{
	DBG_OUTPUT(DBG_TYPE_QUEST, "onRecvQuestEventNotify - bActive[%d], size[%d]", bActive, questNumList.size());

	CTRQuestManager::getInstance().onRecvQuestEventNotify(bActive, questNumList);
}

#ifdef NPC_EVENT
// NPC_EVENT
/// 퀘스트 질문하기 정보
void CTRNetEventHandler::onRecvQuestInterrogationInfoAck(eQuestServerResult result, const QuestInterrogationInfo questInterrogationInfo)
{
}

/// 퀘스트 질문하기 비용차감
void CTRNetEventHandler::onRecvQuestInterrogationConsumeAck(eQuestServerResult result, const int npcNum)
{
	if (result == eQuestServerResult_OK)
	{
		if (CTRGameParkUI::getInstance().isActive())
			CTRGameParkUI::getInstance().showNPCEventDlg(npcNum);
	}
}

/// 퀘스트 질문하기 답변 저장
void CTRNetEventHandler::onRecvQuestInterrogationQuestionAck(eQuestServerResult result, const int npcNum, std::vector<int>& nextNumList)
{
	if (result == eQuestServerResult_OK)
	{
		if (CTRGameParkUI::getInstance().isActive())
			CTRGameParkUI::getInstance().onRecvQuestInterrogationQuestionAck(npcNum, nextNumList);
	}
}

/// 퀘스트 질문하기 완료에 대한 결과 (보상)
void CTRNetEventHandler::onRecvQuestInterrogationFinishAck(eQuestServerResult result, const int npcNum, const int iLevel, std::vector<IntegratedReward>& rewardList)
{
	if (result == eQuestServerResult_OK)
	{
		if (CTRGameParkUI::getInstance().isActive())
			CTRGameParkUI::getInstance().onRecvQuestInterrogationFinishAck(npcNum, iLevel, rewardList);
	}
}

/// NPC 질문하기 결과 (보상)
void CTRNetEventHandler::onRecvQuestInterrogationRewardAck(eQuestServerResult result, const int npcNum, const int iLevel, std::vector<IntegratedReward>& rewardList)
{
	switch (result)
	{
	case eQuestServerResult_OK:
		if (CTRGameParkUI::getInstance().isActive())
			CTRGameParkUI::getInstance().onRecvQuestInterrogationRewardAck(npcNum, iLevel, rewardList);
		break;
	case eQuestServerResult_NOT_DATE_INTERROGATION_REWARD:
		COkDialogEx::getInstance().showDialog(_STR(HUG_MSG_REWARD_GIVE_ERROR));
		break;
	case eQuestServerResult_ALREADY_INTERROGATION_REWARD:
		COkDialogEx::getInstance().showDialog(_STR(FAILED_AREADY_REWARD_RECIEVED));
		break;
	case eQuestServerResult_NOT_ENTER_INTERROGATION:
		CTRShortTimeMessage::getInstance().showMessage(_STR(NPC_EVENT_NOT_ENTER_INTERROGATION));
		break;
	}

}

/// NPC 질문하기 스케쥴
void CTRNetEventHandler::onRecvQuestInterrogationScheduleAck(std::map<int, QuestInterrogationScheduleInfo>& schedule)
{
}

#endif 

#ifdef LOBBY_QUEST_CHANNEL_SYSTEM
/// 유저의 채널퀘스트 정보를 받았음
void CTRNetEventHandler::onRecvLobbyQuestUserInfo( eQuestServerResult result, const bool bComplete, QuestUserInfoMap& questUserInfoMap )
{
	DBG_OUTPUT(DBG_TYPE_LOBBYQUEST, "onRecvLobbyQuestUserInfo - result[%d], size[%d]", result, questUserInfoMap.size());

	switch(result)
	{
	case eQuestServerResult_OK:
		CTRLobbyQuestManager::getInstance().onRecvLobbyQuestUserInfo(bComplete, questUserInfoMap);
		break;
	case eQuestServerResult_DBERROR:
		break;
	case eQuestServerResult_NOT_EXIST_QUESTNUM:
		break;
	case eQuestServerResult_ALREADY_PROCEEDING:
		break;
	case eQuestServerResult_NOT_ENOUGH_EXP:
		break;
	case eQuestServerResult_NOT_COMPLETE_PRECEDE_QUEST:
		break;
	case eQuestServerResult_NOT_ENOUGH_ITEM_COUNT:
		break;
	case eQuestServerResult_NOT_PROCEEDING_QUEST:
		break;
	case eQuestServerResult_COMPLETE_COUNT_OVER:
		break;
	}

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRLobbyQuestChannelBase* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRLobbyQuestChannelBase>(SUB_PTR_DIALOG_TYPE_LOBBY_QUEST_CHANNEL);
		if(pChannelUI && pChannelUI->isVisible()) pChannelUI->_showSceneDialog(eLobbyQuestChannelSceneType_Main);
	}
}

/// 채널퀘스트 도전에 대한 결과
void CTRNetEventHandler::onRecvLobbyQuestAddAck( eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList )
{
	DBG_OUTPUT(DBG_TYPE_LOBBYQUEST, "onRecvLobbyQuestAddAck - result[%d], questNum[%d], size[%d]", result, questNum, rewardList.size());

	switch(result)
	{
	case eQuestServerResult_OK:
		CTRLobbyQuestManager::getInstance().onRecvLobbyQuestAddAck(questNum, rewardList);
		break;
	default:
		_processQuestServerResultFailed(result);
		break;
	}

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRLobbyQuestChannelBase* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRLobbyQuestChannelBase>(SUB_PTR_DIALOG_TYPE_LOBBY_QUEST_CHANNEL);
		if(pChannelUI && pChannelUI->isVisible()) pChannelUI->_showSceneDialog(eLobbyQuestChannelSceneType_Main);
	}
}

/// 채널퀘스트 포기에 대한 결과
void CTRNetEventHandler::onRecvLobbyQuestRemoveAck( eQuestServerResult result, const int questNum )
{
	DBG_OUTPUT(DBG_TYPE_LOBBYQUEST, "onRecvLobbyQuestRemoveAck - result[%d], num[%d]", result, questNum);

	switch(result)
	{
	case eQuestServerResult_OK:
		CTRLobbyQuestManager::getInstance().onRecvLobbyQuestRemoveAck(questNum);
		break;
	default:
		_processQuestServerResultFailed(result);
		break;
	}

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRLobbyQuestChannelBase* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRLobbyQuestChannelBase>(SUB_PTR_DIALOG_TYPE_LOBBY_QUEST_CHANNEL);
		if(pChannelUI && pChannelUI->isVisible()) pChannelUI->_showSceneDialog(eLobbyQuestChannelSceneType_Main);
	}
}

/// 채널퀘스트 완료에 대한 결과 (보상)
void CTRNetEventHandler::onRecvLobbyQuestRewardAck( eQuestServerResult result, const int questNum, std::vector<IntegratedReward>& rewardList )
{
	DBG_OUTPUT(DBG_TYPE_LOBBYQUEST, "onRecvLobbyQuestRewardAck - result[%d], num[%d]", result, questNum);

	switch(result)
	{
	case eQuestServerResult_OK:
		CTRLobbyQuestManager::getInstance().onRecvLobbyQuestRewardAck(questNum, rewardList);
		break;
	default:
		_processQuestServerResultFailed(result);
		break;
	}

	// 로비퀘스트 결과를 받으면 메인으로 보낸다
	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRLobbyQuestChannelBase* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRLobbyQuestChannelBase>(SUB_PTR_DIALOG_TYPE_LOBBY_QUEST_CHANNEL);
		if(pChannelUI) pChannelUI->_showSceneDialog(eLobbyQuestChannelSceneType_Main);
	}
}

/// 이벤트 채널퀘스트 정보 수신
void CTRNetEventHandler::onRecvLobbyQuestEventNotify( bool bActive, std::set<int>& questNumList )
{
	DBG_OUTPUT(DBG_TYPE_LOBBYQUEST, "onRecvLobbyQuestEventNotify - bActive[%d], size[%d]", bActive, questNumList.size());
	CTRLobbyQuestManager::getInstance().onRecvLobbyQuestEventNotify(bActive, questNumList);

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRLobbyQuestChannelBase* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRLobbyQuestChannelBase>(SUB_PTR_DIALOG_TYPE_LOBBY_QUEST_CHANNEL);
		if(pChannelUI && pChannelUI->isVisible()) pChannelUI->_showSceneDialog(eLobbyQuestChannelSceneType_Main);
	}
}
#endif

/// 간편 아이디가 사용할 수 없는 컨텐츠임을 알려준다
void CTRNetEventHandler::onRecvSimpleIDInvalidContentsNotify()
{
	DBG_OUTPUT("onRecvSimpleIDInvalidContentsNotify");

	if(CNetClientManager::getInstance().isSimpleIDUser())
	{
		CTRUserInterface::getInstance().showSimpleUserPopupDlg();
	}
}
/// Room Kind 의 속성을 받았음.
void CTRNetEventHandler::onRecvRoomKindAttr(const RoomKindAttr& roomKindAttr, bool bValid)
{
	if (m_pNetPlay != NULL)
	{
		m_pNetPlay->onRecvInGameProperty(roomKindAttr,bValid);
	}
}

void CTRNetEventHandler::_processQuestServerResultFailed(eQuestServerResult result)
{
	string ErrString;
	switch(result)
	{
	case eQuestServerResult_DBERROR:
		ErrString = _STR(FAILED_DB_ERROR);
		break;
	case eQuestServerResult_NOT_EXIST_QUESTNUM:
		ErrString = _STR(FAILED_QUEST_NOT_EXIST_NUM);
		break;
	case eQuestServerResult_ALREADY_PROCEEDING:
		ErrString = _STR(FAILED_QUEST_ALREADY_PROCEEDING);
		break;
	case eQuestServerResult_NOT_ENOUGH_EXP:
		ErrString = _STR(FAILED_QUEST_NOT_ENOUGH_EXP);
		break;
	case eQuestServerResult_NOT_COMPLETE_PRECEDE_QUEST:
		ErrString = _STR(FAILED_QUEST_NOT_COMPLETE_PRECEDE_QUEST);
		break;
	case eQuestServerResult_NOT_ENOUGH_ITEM_COUNT:
		ErrString = _STR(FAILED_QUEST_NOT_ENOUGH_ITEM_COUNT);
		break;
	case eQuestServerResult_NOT_PROCEEDING_QUEST:
		ErrString = _STR(FAILED_QUEST_NOT_PROCEEDING_QUEST);
		break;
	case eQuestServerResult_MAX_CHALLENGE_COUNT:
		ErrString = _STR(FAILED_QUEST_MAX_CHALLENGE_COUNT);
		break;
	case eQuestServerResult_NOT_COMPLETE_MISSION:
		ErrString = _STR(FAILED_QUEST_NOT_COMPLETE_MISSION);
		break;
	case eQuestServerResult_COMPLETE_COUNT_OVER:
		ErrString = _STR(FAILED_QUEST_COMPLETE_COUNT_OVER);
		break;
	case eQuestServerResult_NOT_CHALLENGE_QUEST:
		ErrString = _STR(FAILED_QUEST_NOT_CHALLENGE_QUEST);
		break;
	case eQuestServerResult_CONNECT_QUEST_CHALLENGED:
		ErrString = _STR(FAILED_QUEST_CONNECT_QUEST_CHALLENGED);
		break;
	case eQuestServerResult_NOT_ENOUGH_CONSUME_ITEM:
		ErrString = _STR(FAILED_QUEST_NOT_ENOUGH_CONSUME_ITEM);
		break;
	case eQuestServerResult_CAN_NOT_COMPLETE_QUEST:
		ErrString = _STR(FAILED_QUEST_CAN_NOT_COMPLETE_QUEST);
		break;
	default:
		ErrString = _STR(FAILED_QUEST_CAN_NOT_CHALLENGE_QUEST);
		break;
	}

	COkDialogEx::getInstance().showDialog(ErrString);
	TRDBG_OUTPUT_ERROR("%s - %s (%d)", __FUNCTION__, ErrString.c_str(), result);
}

void CTRNetEventHandler::onRecvAnubisExpeditionGetInfo(const AnubisExpeditionInfo & scheduleInfo, std::map<eRoomKind, int> & runInfo)
{
	CTRAnubisExpeditionManager::getInstance().onRecvAnubisExpeditionGetInfo(scheduleInfo, runInfo);
	CTRLobbyUI::getInstance().anubisExpeditionUpdateUI();
}

void CTRNetEventHandler::onRecvAnubisExpeditionGetUserInfo( const int iPoint)
{
	CTRAnubisExpeditionManager::getInstance().onRecvAnubisExpeditionGetUserInfo(iPoint);
	CTRLobbyUI::getInstance().anubisExpeditionUpdateUI();
}

void CTRNetEventHandler::onRecvAnubisExpeditionEndGameNotify()
{
	CTRAnubisExpeditionManager::getInstance().onRecvAnubisExpeditionEndGameNotify();
}

#ifdef SPORTS_PLAY_LIMIT_CHECK
void CTRNetEventHandler::onRecvSportsPlayLimit(const UserSportsPlayLimit& sportsPlayLimit, BOOL playable)
{
	if(CTRLobbyUI::getInstance().isActive())
	{
		CTRLobbyUI::getInstance().onRecvSportsPlayLimit(playable);
	}
}
#endif

//////////////////////////////////////////////////////////////////////////
#ifdef _EXCHANGE_SYSTEM
/// 교환 시스템 사용 정보
void CTRNetEventHandler::onRecvExchangeSystemGetUseInfo(eExchangeSystem systemType, const eExchangeSystemResult result)
{
	DBG_DEMO_OUTPUT(2, "%s - %d : %d", __FUNCTION__, (int)systemType, (int)result);

	//if(result != eExchangeSystemResult_OK)
	//{
	//	string strMent = "";

	//	switch(result)
	//	{
	//	case eExchangeSystemResult_DBERROR:
	//		strMent = _STR(FAILED_DB_ERROR);
	//		break;

	//	case eExchangeSystemResult_CAN_NOT_USE:
	//		strMent = _STR(MSG_NOT_USABLE_SYSTEM);	//!< 변경 요청시 새로 추가해야할 멘트
	//		break;

	//	case eExchangeSystemResult_NOT_USE_TIME:
	//		strMent = _STR(MSG_CANNOT_USE_OUT_OF_TIME);
	//		break;
	//	
	//	case eExchangeSystemResult_ONLY_USE_WINNER_PARTY:
	//		strMent = _STR(CAPSULE_CANNOT_USING_USER);
	//		break;
	//	}

	//	if(!strMent.empty()) CTRShortTimeMessage::showMessage(strMent);
	//}

	if(CTRLobbyUI::getInstance().isActive()) CTRLobbyUI::getInstance().onRecvExchangeSystemGetUseInfo(systemType, result);
	if(CTRAlchemistUI::getInstance().isActive()) CTRAlchemistUI::getInstance().onRecvExchangeSystemGetUseInfo(systemType, result);
	if(CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvExchangeSystemGetUseInfo(systemType, result);
#ifdef _ARCHIVES_
	if(ARCHIVES::CTRArchivesDlg::getInstance().isVisible()) ARCHIVES::CTRArchivesDlg::getInstance().onRecvExchangeSystemGetUseInfo(systemType, result);
#endif
}

/// 교환 시스템 교환 성공
void CTRNetEventHandler::onRecvExchangeSystemExchangeOK(std::vector<RewardInfo>& resultList, int count)
{
	DBG_DEMO_OUTPUT(2, "%s - %d", __FUNCTION__, resultList.size());

#ifdef _ENCHANT_SYSTEM_
	bool bProcessed = ItemDetailView::CTRItemDetailViewManager::getInstance().onRecvExchangeSystemExchangeOK(resultList, count);
	if(bProcessed) return;	//!< 상세뷰 교환창으로 처리되었다면 통과
#endif
	
	if(CTRLobbyUI::getInstance().isActive()) CTRLobbyUI::getInstance().onRecvExchangeSystemExchangeOK(resultList, count);
	if(CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvExchangeSystemExchangeOK(resultList, count);
	if(CTRAlchemistUI::getInstance().isActive()) CTRAlchemistUI::getInstance().onRecvExchangeSystemExchangeOK(resultList, count);
#ifdef _ARCHIVES_
	if(ARCHIVES::CTRArchivesDlg::getInstance().isVisible()) ARCHIVES::CTRArchivesDlg::getInstance().onRecvExchangeSystemExchangeOK(resultList, count);
#endif
}

/// 교환 시스템 교환 실패
void CTRNetEventHandler::onRecvExchangeSystemExchangeFailed(eExchangeSystemResult result)
{
	string strMent = _STR(EXCHANGE_SYSTEM_ERROR);

	switch(result)
	{
	case eExchangeSystemResult_DBERROR:
		strMent += "<br>";
		strMent += _STR(FAILED_DB_ERROR);
		break;

	case eExchangeSystemResult_NOT_ENOUGH_CONSUME_ITEM:
		strMent = _STR(FAILED_EXCHANGE_SYSTEM_NOT_ENOUGH_CONSUME_ITEM);
		break;

	case eExchangeSystemResult_WEAR_ITEM:
		strMent = _STR(FAILED_EXCHANGE_SYSTEM_CONSUME_ITEM_WEAR);
		break;
	
	case eExchangeSystemResult_AREADY_HAVE_ITEM:
		strMent = _STR(FAILED_EXCHANGE_SYSTEM_ALEADY_HAVE_ITEM);
		break;

	case eExchangeSystemResult_ONLY_USE_WINNER_PARTY:
		strMent = _STR(FAILED_EXCHANGE_SYSTEM_ONLY_USE_WINNER_PARTY);
		break;
	}

	COkDialogEx::getInstance().showDialog(strMent, -2.1f);
	TRDBG_OUTPUT_ERROR("%s - %s (%d)", __FUNCTION__, strMent.c_str(), result);
}
#endif

#ifdef _COMBINATION_SHOP_
/// 매점 시스템 사용 정보
void CTRNetEventHandler::onRecvCombinationShopGetUseInfo(eCombinationShop systemType, const eCombinationShopResult result)
{
	COMBINATION_SHOP::CTRManager *pManager = CNetClientManager::getInstance().getCombinationShopManager();
	if(pManager) pManager->onRecvCombinationShopGetUseInfo(systemType, result);
}

/// 매점 시스템 시작,종료 공지
void CTRNetEventHandler::onRecvCombinationShopNotify(eCombinationShop systemType, const bool bIsVisible)
{
	COMBINATION_SHOP::CTRManager *pManager = CNetClientManager::getInstance().getCombinationShopManager();
	if(pManager) pManager->onRecvCombinationShopNotify(systemType, bIsVisible);
}

/// 매점 시스템 갯수 제한 리스트 성공
void CTRNetEventHandler::onRecvCombinationShopGetLimitInfoInfoOK(eCombinationShop systemType, std::map<int, int>& countList)
{
	COMBINATION_SHOP::CTRManager *pManager = CNetClientManager::getInstance().getCombinationShopManager();
	if(pManager) pManager->onRecvCombinationShopGetLimitInfoOK(systemType, countList);
}

/// 매점 시스템 갯수 제한 리스트 실패
void CTRNetEventHandler::onRecvCombinationShopGetLimitInfoInfoFailed(eCombinationShop systemType, eCombinationShopResult result)
{
	COMBINATION_SHOP::CTRManager *pManager = CNetClientManager::getInstance().getCombinationShopManager();
	if(pManager) pManager->onRecvCombinationShopGetLimitInfoFailed(systemType, result);
}

/// 매점 시스템 실시간 변경 아이템 리스트 성공
void CTRNetEventHandler::onRecvCombinationShopGetItemDetailInfoOK(std::map<int, CombinationShopItemDetailInfo>& itemList)
{
	COMBINATION_SHOP::CTRManager *pManager = CNetClientManager::getInstance().getCombinationShopManager();
	if(pManager) pManager->onRecvCombinationShopGetItemDetailInfoOK(itemList);
}

/// 매점 시스템 교환 성공
void CTRNetEventHandler::onRecvCombinationShopExchangeOK(bool bSucess, std::vector<RewardInfo>& resultList)
{
	COMBINATION_SHOP::CTRManager *pManager = CNetClientManager::getInstance().getCombinationShopManager();
	if(pManager) pManager->onRecvCombinationShopExchangeOK(bSucess, resultList);
}

/// 매점 시스템 교환 실패
void CTRNetEventHandler::onRecvCombinationShopExchangeFailed(eCombinationShopResult result)
{
	COMBINATION_SHOP::CTRManager *pManager = CNetClientManager::getInstance().getCombinationShopManager();
	if(pManager) pManager->onRecvCombinationShopExchangeFailed(result);
}
#endif


//////////////////////////////////////////////////////////////////////////
#ifdef JOURNEY_TO_THE_WEST
///서유기 경기 정보를 받았다.
void CTRNetEventHandler::onRecvJourneyToTheWestGetScheduleInfoOK(const time_type & tStartTime, const time_type & tCloseTime)
{
	DBG_DEMO_OUTPUT("%s - s : %I64d, c : %I64d", __FUNCTION__, tStartTime, tCloseTime);
	if(CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().onRecvJourneyToTheWestGetScheduleInfoOK(tStartTime, tCloseTime);
}

///서유기 유저 정보를 받았다.
void CTRNetEventHandler::onRecvJourneyToTheWestGetUserInfoOK()
{
	DBG_DEMO_OUTPUT("%s", __FUNCTION__);
	if(CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().onRecvJourneyToTheWestGetUserInfoOK();
}

///서유기 팀 정보를 받았다.
void CTRNetEventHandler::onRecvJourneyToTheWestGetPartyInfoOK()
{
	DBG_DEMO_OUTPUT("%s", __FUNCTION__);
	if(CTRLobbyUI::getInstance().isActive())
        CTRLobbyUI::getInstance().onRecvJourneyToTheWestGetPartyInfoOK();
}

///서유기 팀 가입 결과를 받았다.
void CTRNetEventHandler::onRecvJourneyToTheWestJoinPartyOK()
{
	DBG_DEMO_OUTPUT("%s", __FUNCTION__);
	if(CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().onRecvJourneyToTheWestJoinPartyOK();
}

///서유기 팀 가입에 실패했다.
void CTRNetEventHandler::onRecvJourneyToTheWestJoinPartyFailed(eJourneyToTheWestJoinPartyMsg eMsg)
{
	DBG_DEMO_OUTPUT("%s - reason : %d", __FUNCTION__, (int)eMsg);

	string strMent = _STR(HS_ERR_UNKNOWN);
	switch(eMsg)
	{
	case eJourneyToTheWestJoinPartyMsg_NOT_PLAY_TIME:
		strMent = _STR(FAILED_JOURNEY_TO_THE_WEST_PARTY_MSG_NOT_PLAY_TIME);
		break;

	case eJourneyToTheWestJoinPartyMsg_ALREAD_PARTY:
		strMent = _STR(FAILED_PIERO_OLYMPIC_ALREADY_JOINED);
		break;

	case eJourneyToTheWestJoinPartyMsg_INVALID_PARTY_TYPE:
		strMent = _STR(FAILED_JOURNEY_TO_THE_WEST_PARTY_MSG_INVALID_PARTY_TYPE);
		break;

	case eJourneyToTheWestJoinPartyMsg_DB_ERROR:
		strMent = _STR(FAILED_DB_ERROR);
		break;
	}

	COkDialogEx::getInstance().showDialog(strMent);
}

///서유기 정보가 갱신되었다고 받았다. 
void CTRNetEventHandler::onRecvJourneyToTheWestUpdateNotify(bool bSeasonOn)
{
	DBG_DEMO_OUTPUT("%s - season %s", __FUNCTION__, bSeasonOn ? "on" : "off");
	if(CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().onRecvJourneyToTheWestUpdateNotify(bSeasonOn);
}

void CTRNetEventHandler::onRecvJourneyToTheWestResetUserPartyNotify()
{
	DBG_DEMO_OUTPUT("%s", __FUNCTION__);
	if(CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().onRecvJourneyToTheWestResetUserPartyNotify();
}
#endif

//////////////////////임시 보관함 관련////////////////////
/// 구매 결정 대기 목록을 받았다.
void CTRNetEventHandler::onRecvStandbyPurchaseDicisionGetListOk()
{
	CTRMyRoomGiftDialog::getInstance().updateOutBox();
}

/// 구매 결정 대기 목록을 받기를 실패 하였다.
void CTRNetEventHandler::onRecvStandbyPurchaseDicisionGetListFail(eServerResult eResult)
{
	TRDBG_OUTPUT_ERROR("%s eResult[%d]", __FUNCTION__, eResult);

	COkDialogEx::getInstance().showDialog(_STR(FAILED_MSG_GET_OUTBOX_LIST));
}

/// 구매 결정 대기 목록 추가되었다.
void CTRNetEventHandler::onRecvStandbyPurchaseDicisionAddListOk()
{
	DBG_OUTPUT(DBG_TYPE_SYSTEM, "%s", __FUNCTION__);

#ifdef _SHOP_RENEWAL_
	CNetClientManager::getInstance().requestShopUserBuyCountList();
	CNetClientManager::getInstance().getUserPointAccess()->update_sync_gameUserPoint(eUserPointType_MILEAGE_CASH_POINT);
	CNetClientManager::getInstance().getUserPointAccess()->update_sync_gameUserPoint(eUserPointType_MILEAGE_ETC_POINT);

	CNetClientManager::getInstance().getUserPointAccess()->update_sync_gameUserPoint(eUserPointType_RENEWAL_SHOP_CASH_POINT);
#endif
}

/// 구매 결정 대기 목록 추가 실패하였다.
void CTRNetEventHandler::onRecvStandbyPurchaseDicisionAddListFail(eShopFailed_REASON eResult)
{
	TRDBG_OUTPUT_ERROR("%s eResult[%d]", __FUNCTION__, eResult);

	CTRShopDlg::getInstance().onRecvStandbyPurchaseDicisionAddListFail(eResult);
}

/// 구매 결정 대기 목록 제거되었다.
void CTRNetEventHandler::onRecvStandbyPurchaseDicisionRemoveListOk(int iItemNum, bool bCancellation, int iShopItemNum)
{
	CNetClientManager &rNetClientMgr = CNetClientManager::getInstance();
	if( !bCancellation )
	{
		std::vector<int> vecItemNum;
		vecItemNum.push_back(iItemNum);
		CTRMyRoomGiftDialog::getInstance().onRecvAcceptGiftOK(vecItemNum);
		
		// 넥슨, 플레이넷, 카툰네트워크 유저에 대해서 뽑기 쿠폰 갱신 요청
	//	if (rNetClientMgr.isNexonUser() || rNetClientMgr.isPlayNetUser() || rNetClientMgr.isTooniLandUser())
		if (rNetClientMgr.isNexonUser() || rNetClientMgr.isPlayNetUser())
		{
			int iCouponNum = 4813;
			CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iCouponNum);
		}

#ifdef _SHOP_RENEWAL_
		if (iShopItemNum > 0)
			CTRShopManager::getInstance().onRecvStandbyPurchaseDicisionRemoveListOk(iShopItemNum);
#endif
	}
	else COkDialogEx::getInstance().showDialog( _STR(MSG_PROCESS_SUCCESS) );
	CTRMyRoomGiftDialog::getInstance().updateOutBox();
	rNetClientMgr.requestCashBalance();
	rNetClientMgr.requestCurrentTR();

#ifdef _SHOP_RENEWAL_
	CNetClientManager::getInstance().requestShopUserBuyCountList();
	CNetClientManager::getInstance().getUserPointAccess()->update_sync_gameUserPoint(eUserPointType_MILEAGE_CASH_POINT);
	CNetClientManager::getInstance().getUserPointAccess()->update_sync_gameUserPoint(eUserPointType_MILEAGE_ETC_POINT);
	CNetClientManager::getInstance().getUserPointAccess()->update_sync_gameUserPoint(eUserPointType_RENEWAL_SHOP_CASH_POINT);
#endif
}

/// 구매 결정 대기 목록 제거가 실패되었다.
void CTRNetEventHandler::onRecvStandbyPurchaseDicisionRemoveListFail(eServerResult eResult)
{
	TRDBG_OUTPUT_ERROR("%s eResult[%d]", __FUNCTION__, eResult);

	COkDialogEx::getInstance().showDialog( format("%s [%d]", _STR(FAILED_MSG_REMOVE_OUTBOX_LIST), eResult) );
}

/// 구매 결정 대기 목록의 기간 만료 체크 결과 알림
void CTRNetEventHandler::onRecvStandbyPurchaseDicisionExistExpireNontify()
{
	DBG_OUTPUT(DBG_TYPE_SYSTEM, "%s", __FUNCTION__);
	CTRMyRoomGiftDialog::getInstance().pleaseUpdateOutboxMsg();
	if( CTRMyRoomGiftDialog::getInstance().isVisible() && CTRMyRoomGiftDialog::getInstance().getCurrentState() == CTRMyRoomGiftDialog::MYROOM_GIFT_STATE_OUTBOX )
	{
		CTRMyRoomGiftDialog::getInstance().updateOutBox();
	}
}

/// Nexon PC방 만료 경고 메시지
void CTRNetEventHandler::onRecvAlertMessageNontify(eAlertMessage iMessageType, int iRemainMinutes)
{
	DBG_OUTPUT(DBG_TYPE_SYSTEM, "%s Type[%d] Time[%d] ", __FUNCTION__, iMessageType, iRemainMinutes);
	std::string strMsg;
	switch (iMessageType)
	{
	case eAlterMessage_NexonPCBangExpire :
		strMsg = format( _STR(MSG_PCROOM_TIME_ALM), iRemainMinutes );
		break;
	case eAlertMessage_Shutdown :
	case eAlertMessage_ForceShutdown :
		strMsg = format( _STR(MSG_SHUTDOWN_TIME_ALM), iRemainMinutes );
		break;
	
	}
	if(CTRUserInterface::getInstance().isShowNotice())
	{
		CTRUserInterface::getInstance().onRecvNoticeMsg(eNoticeType_NORMAL, strMsg);
	}
	else
	{
		CTRSystemNotice::getInstance().showMessage(strMsg);
	}
}
/////////////////////////////////////////////////////////////

// 보너스 아이템 만들기 성공
void CTRNetEventHandler::onRecvAssaultModeBonusItemMakeOK()
{
	DBG_OUTPUT("%s", __FUNCTION__);
}
// 보너스 아이템 만들기 실패
void CTRNetEventHandler::onRecvAssaultModeBonusItemMakeFailed()
{
	DBG_OUTPUT("%s", __FUNCTION__);
}
// 보너스 아이템 먹기 성공
void CTRNetEventHandler::onRecvAssaultModeBonusItemEatOK(const int index, RewardInfo& reward)
{
	CGameManager::getInstance().onRecvAssaultModeBonusItemEatOK(index, reward);
}
// 보너스 아이템 먹기 실패
void CTRNetEventHandler::onRecvAssaultModeBonusItemEatFailed()
{
	DBG_OUTPUT("%s", __FUNCTION__);
}

// 맵 발판 밟기 결과
void CTRNetEventHandler::onRecvMapBoardStepACK( const int boardIndex, eMapBoardType boardType, std::vector<BYTE>& userList )
{
	CInGameModeControlManager_RevivalandDie::getinstance().onRecvMapBoardStepACK(boardIndex, boardType, userList);
}

// 랜덤 인스턴스 팀이 결정되었다.
void CTRNetEventHandler::onRecvSelectRandomInstanceTeam(eTeam randomTeam, eInstanceTeam iInstanceTeam, eTeam otherTeam, eInstanceTeam iInstanceOtherTeam)
{	
	CGameManager::getInstance().onRecvSelectRandomInstanceTeam(randomTeam, iInstanceTeam, otherTeam, iInstanceOtherTeam);
}

// 팀별 깃발 포인트를 받았다.
void CTRNetEventHandler::onRecvTeamPoint(int teamPoint[eTeam_MAX])
{
#pragma message("CRecvTeamPoint 변경 필요")
	CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CRecvTeamPoint(teamPoint[eTeam_RED], teamPoint[eTeam_BLUE]));
}

/// 이벤트 보너스 정보를 받았다
void CTRNetEventHandler::onRecvEventBonusNofity(const int userIndex, const float bonusExpRatio, const float bonusTRRatio)
{
	CTRUserInterface::getInstance().onRecvEventBonusNofity(userIndex,bonusExpRatio,bonusTRRatio);
}

#ifdef _COMPETITION_EVENT
void CTRNetEventHandler::onRecvEventAccumulateBonusNofity(const std::map<eEventPartyType, CompetitionEventBuffBonusInfo> & bonusInfo)
{
	CTRUserInterface::getInstance().onRecvEventAccumulateBonusNofity(bonusInfo);
}
#endif

void CTRNetEventHandler::OnRecvCompetitionEventRoomKindPlayerList(const std::map<int, RoomKind_UserMinMax>& RoomKindList)
{
	CTREventChannelUserNumInfo::getInstance().SetUserMinMax(RoomKindList);
}

/// GM명령어, 외치기 제한 걸기 성공
void CTRNetEventHandler::onRecvGMCommandShoutRestrictOK(const bool bAddMode, const std::string& nickName, const std::string& startTime, const std::string& endTime)
{
	string strMsg;

	if (bAddMode)
	{
		strMsg = format(_STR(MSG_GM_COMMAND_SHOUT_RESTRICT), nickName.c_str(), startTime.c_str(), endTime.c_str());
		CTRUserInterface::getInstance().onRecvUseShoutItemFailed(strMsg);
	}
	else
	{
		strMsg = format(_STR(MSG_GM_COMMAND_SHOUT_RESTRICT_RELEASE));
		CTRUserInterface::getInstance().onRecvUseShoutItemFailed(strMsg);
	}
}

/// GM명령어, 외치기 제한 걸기 실패
void CTRNetEventHandler::onRecvGMCommandShoutRestrictFailed(const bool bAddMode, eServerResult result)
{
	string strMsg;

	switch (result)
	{
	case eServerResult_USE_SHOUT_RESTRICT_NOT_EXIST_USER :
		strMsg = format(_STR(FAILED_USE_SHOUT_RESTRICT_NOT_EXIST_USER));
		CTRUserInterface::getInstance().onRecvUseShoutItemFailed(strMsg);
		break;
	case eServerResult_USE_SHOUT_RESTRICT_ALREADY_ADD:
		strMsg = format(_STR(FAILED_USE_SHOUT_RESTRICT_ALREADY_ADD));
		CTRUserInterface::getInstance().onRecvUseShoutItemFailed(strMsg);
		break;
	default:
		strMsg = format(_STR(ERR_UNKNOWN));
		CTRUserInterface::getInstance().onRecvUseShoutItemFailed(strMsg);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////

#ifdef _CHAOS
/// 카오스 다음게임에 대한 공지를 받음
void CTRNetEventHandler::onRecvChaosNoticeNextGameInfo(OlympicGameInfo& gameInfo)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosChannelDialog* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosChannelDialog>(SUB_PTR_DIALOG_TYPE_EVENT_CHAOS);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosNoticeNextGameInfo(gameInfo);
		}
	}
}

/// 카오스 다음 게임에 대한 정보를 받음
void CTRNetEventHandler::onRecvChaosNextGameInfo(OlympicGameInfo& gameInfo)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosChannelDialog* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosChannelDialog>(SUB_PTR_DIALOG_TYPE_EVENT_CHAOS);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosNextGameInfo(gameInfo);
		}
	}
}

/// 카오스 일정이 비어있다
void CTRNetEventHandler::onRecvChaosGameEmpty()
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosChannelDialog* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosChannelDialog>(SUB_PTR_DIALOG_TYPE_EVENT_CHAOS);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosGameEmpty();
		}
	}
}

/// 카오스 승리팀에 대한 공지
void CTRNetEventHandler::onRecvChaosNoticeWinnerParty( std::map<int, eEventPartyType>& territoryWinners, const bool chaosGroupSeasonOff )
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosChannelDialog* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosChannelDialog>(SUB_PTR_DIALOG_TYPE_EVENT_CHAOS);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosNoticeWinnerParty(territoryWinners, chaosGroupSeasonOff);
		}
	}
}

/// 카오스 전쟁 지역에 대한 정보 받음
void CTRNetEventHandler::onRecvChaosTerritoryInfoOK(std::map<int, std::map<eEventPartyType, __int64> >& territoryInfo, std::map<int, std::pair<eEventPartyType, std::string> >& territoryWinners)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosChannelDialog* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosChannelDialog>(SUB_PTR_DIALOG_TYPE_EVENT_CHAOS);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosTerritoryInfoOK(territoryInfo, territoryWinners);
		}
	}
}

/// 카오스 전쟁 지역에 대한 정보 받기 실패
void CTRNetEventHandler::onRecvChaosTerritoryInfoFailed(eChaosResult result, const int territoryNum)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosChannelDialog* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosChannelDialog>(SUB_PTR_DIALOG_TYPE_EVENT_CHAOS);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosTerritoryInfoFailed(result, territoryNum);
		}
	}
}

/// 카오스 전쟁 지역에 대한 유저의 정보 받음
void CTRNetEventHandler::onRecvChaosTerritoryUserInfoOK(std::map<int, __int64>& territoryUserInfo)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosChannelDialog* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosChannelDialog>(SUB_PTR_DIALOG_TYPE_EVENT_CHAOS);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosTerritoryUserInfoOK(territoryUserInfo);
		}
	}

	//! 다른채널에서 게임을 하는 동안 카오스전쟁이 종료되었을 경우 엠블럼 미션 확인
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_OCCUPIED_TERRITORY);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_CHAOS_CONTRIBUTED_POINT);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 카오스 전쟁 지역에 대한 유저의 정보 받기 실패
void CTRNetEventHandler::onRecvChaosTerritoryUserInfoFailed(eChaosResult result)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosChannelDialog* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosChannelDialog>(SUB_PTR_DIALOG_TYPE_EVENT_CHAOS);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosTerritoryUserInfoFailed(result);
		}
	}
}

/// 카오스 지역에 대한 정보 갱신하라고 받음
void CTRNetEventHandler::onRecvChaosTerritoryInfoRefresh()
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosChannelDialog* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosChannelDialog>(SUB_PTR_DIALOG_TYPE_EVENT_CHAOS);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosTerritoryInfoRefresh();
		}
	}
}
#endif

//////////////////////////////////////////////////////////////////////////

/// 이벤트 채널 포인트 별 보상 받기 성공
void CTRNetEventHandler::onRecvEventPointRewardOK(short rewardLevel, std::vector<RewardInfo>& rewardList)
{
#ifdef _HERO_WAR
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HERO_WAR)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRHeroWarChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHeroWarChannelDlg>(SUB_PTR_DIALOG_TYPE_HERO_WAR_CHANNEL);
		if(pChannelUI)
		{
			pChannelUI->onRecvHeroWarPointReward(rewardLevel, rewardList);
		}
	}

	if (!rewardList.empty()) CTRRewardManager::getInstance().getReward(rewardList,true);
#endif

#ifdef _WINTER_FESTIVAL
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_WINTER_FESTIVAL)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRWinterFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRWinterFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_WINTER_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->showReward(rewardList);
		}
	}
#endif

#ifdef _HORROR_PARK_CHANNEL
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HORROR_PARK)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRHorrorParkChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHorrorParkChannelDlg>(SUB_PTR_DIALOG_TYPE_HORROR_PARK);
		if(pChannelUI)
		{
			pChannelUI->showReward(rewardList);
		}
	}
#endif

#ifdef _DRHELL_BATTLE
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvEventPointRewardOK(rewardLevel, rewardList);
	}
#endif

#ifdef _CHAOS_ZERO_
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS_ZERO)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosZeroChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosZeroChannelDlg>(SUB_PTR_DIALOG_TYPE_CHAOS_ZERO);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosZeroPointReward(rewardLevel, rewardList);
		}
	}

	if (!rewardList.empty()) CTRRewardManager::getInstance().getReward(rewardList,true);
#endif

	CTRLobbyUI::getInstance().onRecvEventPointRewardOK(rewardLevel, rewardList);
}

/// 이벤트 채널 보상 받을 수 있는 시각 정보 받기 성공
void CTRNetEventHandler::onRecvEventRewardLimitTimeOK(const time_type& startTime, const time_type& endTime)
{
#ifdef _HERO_WAR
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HERO_WAR)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRHeroWarChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHeroWarChannelDlg>(SUB_PTR_DIALOG_TYPE_HERO_WAR_CHANNEL);
		if(pChannelUI)
		{
			pChannelUI->onRecvHeroWarRewardLimitTimeOK();
		}
	}
#endif

#ifdef _WINTER_FESTIVAL
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_WINTER_FESTIVAL)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRWinterFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRWinterFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_WINTER_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->onRecvRewardLimitTimeOK();
		}
	}
#endif

	CTRLobbyUI::getInstance().onRecvEventRewardLimitTimeOK(startTime, endTime);
}

/// 이벤트 채널 보상 리스트를 받음
#ifdef _CHAOS_ZERO_
void CTRNetEventHandler::onRecvEventChannelRewardListOK(const std::map<int, std::pair<eEventPartyType, bool> > rewardList, const std::map<int, bool > & JoinList)
#else
void CTRNetEventHandler::onRecvEventChannelRewardListOK(const std::map<int, std::pair<eEventPartyType, bool> > rewardList)
#endif
{
#ifdef _HORROR_PARK_CHANNEL
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HORROR_PARK)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRHorrorParkChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHorrorParkChannelDlg>(SUB_PTR_DIALOG_TYPE_HORROR_PARK);
		if(pChannelUI)
		{
			pChannelUI->onRecvHorrorParkChannelRewardListOK(rewardList);
		}
	}
#endif

#ifdef _CHAOS_ZERO_
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS_ZERO)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosZeroChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosZeroChannelDlg>(SUB_PTR_DIALOG_TYPE_CHAOS_ZERO);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosZeroChannelRewardListOK(rewardList, JoinList);
		}
	}
#endif

	CTRLobbyUI::getInstance().onRecvEventChannelRewardListOK(rewardList);
}

/// 이벤트 채널 실패 메시지
void CTRNetEventHandler::onRecvCompetitionEventFailed(eCompetitionEventResult result)
{
	CTRLobbyUI::getInstance().onRecvCompetitionEventFailed(result);
}

/// 이벤트 채널 시작 종료 승리팀에 대한 공지를 받음
void CTRNetEventHandler::onRecvEventChannelNoticeOnOff(const bool bStartNotice, const eEventPartyType winnerParty)
{
	eCompetitionEventType competitionEventType = static_cast<eCompetitionEventType>(atoi(CNetClientManager::getInstance().getServerSetting("useCompetitionEvent", "0").c_str()));
	if (competitionEventType == 0)
		return;

	CTRNetPlayManager& netPlayMgr = CTRNetPlayManager::getInstance();
	std::string strNotifyMent = _STR(MSG_MISSION_EVENT);

	if(competitionEventType == eCompetitionEventType_DRHELL_BATTLE)
	{
		if(bStartNotice)
		{
			strNotifyMent = _STR(MSG_DRHELL_BATTLE_NOTIFY_START);
		}
		else
		{
			strNotifyMent = _STR(MSG_DRHELL_BATTLE_NOTIFY_CLOSE);
		}
	}
	else if(competitionEventType == eCompetitionEventType_CHAOS_ZERO)
	{
		if(bStartNotice) strNotifyMent = _STR(CHAOS_ZERO_START_NOTIFY);
		else strNotifyMent = _STR(CHAOS_ZERO_END_NOTIFY);
	}
	else if(competitionEventType == eCompetitionEventType_TALES_ACADEMY)
	{
		if(bStartNotice) strNotifyMent = _STR(MSG_MATCH_START_NOTICE_EX);
		else strNotifyMent = _STR(MSG_MATCH_END_NOTICE_EX);
	}
	else
	{
		strNotifyMent = EVENT_CHANNEL::getEventChannelString();
		if(bStartNotice)
		{
			if (competitionEventType == eCompetitionEventType_WINTER_CHANNEL_2019 ||
				competitionEventType == eCompetitionEventType_SPRING_CHANNEL_2020) {
				strNotifyMent = format("%s %s", strNotifyMent.c_str(), _STR(MSG_MATCH_START_NOTICE_EX));
			}
			else {
				strNotifyMent = format(_STR(MSG_EVENT_GAME_START_MENT),  strNotifyMent.c_str());
			}
		}
		else
		{
			if (competitionEventType == eCompetitionEventType_WINTER_CHANNEL_2019 ||
				competitionEventType == eCompetitionEventType_SPRING_CHANNEL_2020) {
				strNotifyMent = format("%s %s", strNotifyMent.c_str(), _STR(MSG_MATCH_END_NOTICE_EX));
			}
			else {
				strNotifyMent = format(_STR(MSG_EVENT_GAME_END_MENT),  strNotifyMent.c_str());

				const char* pWinTeam = EVENT_CHANNEL::getEventTeamString(winnerParty);
				if (pWinTeam)
				{
					strNotifyMent += " ";
					strNotifyMent += format(_STR(MSG_EVENT_GAME_WIN_MENT), pWinTeam);
				}
			}

			//!< 방에 있을 경우 로비로 내보내기 (경기 종료로 인한 대기실 퇴장은 페널티가 없다)
			if (EVENT_CHANNEL::EventRoomKindContents(netPlayMgr.getGameRoomKind()) && netPlayMgr.inRoom() && netPlayMgr.isGameStateNoGame())
			{
				CNetClientManager::getInstance().requestLeaveRoom();

				std::string leaveMent = format(_STR(MSG_EVENT_GAME_END_MENT), EVENT_CHANNEL::getEventChannelString());
				CTRShortTimeMessage::getInstance().showMessage(leaveMent, 2.5f);
			}
		}
	}

	CTRSystemNotice::getInstance().showMessage(strNotifyMent);

	CTRLobbyUI::getInstance().onRecvEventChannelNoticeOnOff(bStartNotice, winnerParty);

	if(!bStartNotice) CNetClientManager::getInstance().requestCompetitionEventRewardLimitTime();
}

//////////////////////////////////////////////////////////////////////////

/// 유저의 뽑기 정보 받음
void CTRNetEventHandler::onRecvPickBoardUserInfoACK(const int pickBoardNum, PickBoardUserInfo& pickBoardUserInfo)
{
	CTRGameParkUI::getInstance().onRecvPickBoardUserInfoACK(pickBoardNum, pickBoardUserInfo);
}

/// 유저의 뽑기 정보 받기 실패
void CTRNetEventHandler::onRecvGetPickBoardStateFailed(const int pickBoardNum, ePickBoardResult eResult)
{
	CTRGameParkUI::getInstance().onRecvGetPickBoardStateFailed(pickBoardNum, eResult);
}

/// 뽑기에 대한 결과
void CTRNetEventHandler::onRecvPickBoardUseOK(const int pickBoardNum, const int order, RewardInfo& reward)
{
	CTRGameParkUI::getInstance().onRecvPickBoardUseOK(pickBoardNum, order, reward);
}



void CTRNetEventHandler::onRecvPickBoardUseFailed(const int pickBoardNum, ePickBoardResult result)
{
	CTRGameParkUI::getInstance().onRecvPickBoardUseFailed(pickBoardNum, result);
}

#ifdef _EVENTPICKBOARD_
/// 유저의 이벤트 뽑기 정보 받음
void CTRNetEventHandler::onRecvEventPickBoardUserInfoACK(const EventPickBoardInfo & pickboardInfo, const BYTE nPickBoardStep, PickBoardUserInfo& pickBoardUserInfo)
{
	EVENT_PICKBOARD::CTREventPickBoardManager *pManager = CNetClientManager::getInstance().getEventPickBoardManager();
	if (pManager)
	{
		if(pManager->getReserveOpen())
			EVENT_PICKBOARD::CTREventPickBoardUI::getInstance().openDialog(pickboardInfo.m_iPickBoardNum);
		else
		{
			CTRGameParkUI::getInstance().onRecvEventPickBoardUserInfoACK();
		}
		pManager->setReserveOpen(false);
	}
}

/// 유저의 이벤트 뽑기 정보 받기 실패
void CTRNetEventHandler::onRecvEventPickBoardUserInfoFailed(const int pickBoardNum, ePickBoardResult eResult)
{
	EVENT_PICKBOARD::CTREventPickBoardManager *pManager = CNetClientManager::getInstance().getEventPickBoardManager();
	if (pManager)
	{
		if (pManager->getReserveOpen())
			EVENT_PICKBOARD::CTREventPickBoardUI::getInstance().onRecvEventPickBoardFailed(pickBoardNum, eResult);
		pManager->setReserveOpen(false);
	}
}

/// 이벤트 뽑기에 대한 결과
void CTRNetEventHandler::onRecvEventPickBoardUseOK(const int pickBoardNum, const BYTE nPickBoardStep, const int order, RewardInfo& reward, const BYTE nNextStep, const bool bIsReset)
{
	EVENT_PICKBOARD::CTREventPickBoardUI::getInstance().onRecvEventPickBoardUseInfo(pickBoardNum, nPickBoardStep, order, reward, nNextStep, bIsReset);
}

void CTRNetEventHandler::onRecvEventPickBoardUseFailed(const int pickBoardNum, ePickBoardResult result)
{
	EVENT_PICKBOARD::CTREventPickBoardUI::getInstance().onRecvEventPickBoardFailed(pickBoardNum, result);
}

/// 이벤트 뽑기 받기/선물
void CTRNetEventHandler::onRecvEventPickBoardGiveOK(const bool bIsGift, RewardInfo& reward)
{
	if(bIsGift == false)
	{
		// 보상 갱신 요청
		std::vector<RewardInfo> resultList;
		resultList.push_back(reward);
		CTRRewardManager::getInstance().getReward(resultList, true);
	}
	EVENT_PICKBOARD::CTREventPickBoardUI::getInstance().onRecvEventPickBoardGiveOK();
}

void CTRNetEventHandler::onRecvEventPickBoardGiveFailed(ePickBoardResult result)
{
	EVENT_PICKBOARD::CTREventPickBoardUI::getInstance().onRecvEventPickBoardFailed(0, result);
}

/// 이벤트 뽑기 리셋
void CTRNetEventHandler::onRecvEventPickBoardResetNotify(const std::vector<int> & initPickBoard)
{
	EVENT_PICKBOARD::CTREventPickBoardUI::getInstance().refreshBoard();
}
#endif

//////////////////////////////////////////////////////////////////////////

#ifdef _ASSAULT_RAID
/// 오늘의 레이드 스케줄을 받았다.
void CTRNetEventHandler::onRecvAssaultRaidTodayScheduleNotify(const AssaultRaidScheduleList& scheduleList)
{
	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRAssaultRaidChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRAssaultRaidChannelDlg>(SUB_PTR_DIALOG_TYPE_ASSAULT_RAID);
		if(pChannelUI) pChannelUI->updateRoom();
	}

}

/// 레이드 게임 시작, 종료 공지를 받았다.
void CTRNetEventHandler::onRecvAssaultRaid_Start_End_Notify(const AssaultRaidState& state)
{
	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRAssaultRaidChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRAssaultRaidChannelDlg>(SUB_PTR_DIALOG_TYPE_ASSAULT_RAID);
		if(pChannelUI) pChannelUI->updateRoom();
	}

	std::string strNotice;
	switch (state.m_gateState)
	{
	case eRaidChannelGateState_Start:
		strNotice = _STR(MSG_RAID_MATCH_START_NOTICE);
		break;

	case eRaidChannelGateState_End:
		{
			strNotice = _STR(MSG_RAID_MATCH_END_NOTICE);

			//!< 방에 있을 경우 로비로 내보내기 (경기 종료로 인한 대기실 퇴장은 페널티가 없다)
			if (m_pNetPlay && isRaidChannel(m_pNetPlay->getGameRoomKind()) && m_pNetPlay->inRoom() && m_pNetPlay->isGameStateNoGame())
			{
				CNetClientManager::getInstance().requestLeaveRoom();

				std::string leaveMent = format(_STR(MSG_EVENT_GAME_END_MENT), _STR(NAME_RAID));
				CTRShortTimeMessage::getInstance().showMessage(leaveMent, 2.5f);
			}
		}
		break;

	default:
		return;
	}

	CTRSystemNotice::getInstance().showMessage(strNotice);
}

/// 나의 레이드 포인트를 받았다.
void CTRNetEventHandler::onRecvAssaultRaidMyPoint(const UserChannelPoint& info)
{
	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRAssaultRaidChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRAssaultRaidChannelDlg>(SUB_PTR_DIALOG_TYPE_ASSAULT_RAID);
		if(pChannelUI) pChannelUI->onRecvAssaultRaidMyPoint(info);
	}
}

/// 기여포인트 보상을 받았다.
void CTRNetEventHandler::onRecvAssaultRaidPointRewardOK(BYTE iRewardLevel, const std::vector<RewardInfo>& rewardList)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_RAID)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRAssaultRaidChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRAssaultRaidChannelDlg>(SUB_PTR_DIALOG_TYPE_ASSAULT_RAID);
		if(pChannelUI)
		{
			pChannelUI->showReward(iRewardLevel, rewardList);
		}
	}

	if (!rewardList.empty()) CTRRewardManager::getInstance().getReward(rewardList,true);
}

void CTRNetEventHandler::onRecvAssaultRaidPointRewardFailed(BYTE iRewardLevel, eCompetitionEventResult result)
{
	CTRLobbyUI::getInstance().onRecvCompetitionEventFailed(result);
}

#endif

//////////////////////////////////////////////////////////////////////////

/// 던전 레이드 스케줄 정보를 받았다.
void CTRNetEventHandler::onRecvDungeonRaidScheduleInfoNotify(const DungeonRaidInfo& scheduleInfo)
{
#ifdef _DUNGEON_RAID_CHANNEL
	CTRSubDialogManager* pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager != NULL)
	{
		CTRDungeonRaidDlg* pRaidUI = pSubDialogManager->getSubDialogPtr<CTRDungeonRaidDlg>(SUB_PTR_DIALOG_TYPE_DUNGEON_ASSAULT_RAID);
		if(pRaidUI != NULL && pRaidUI->isVisible())
			pRaidUI->updateScheduleInfo(scheduleInfo);
	}
#endif
}

/// 던전 레이드 게임 시작, 종료 공지를 받았다.
void CTRNetEventHandler::onRecvDungeonRaid_Start_End_Notify(const eRaidChannelGateState dungeonRaidstate)
{
#ifdef _DUNGEON_RAID_CHANNEL
	if (isDungeonRaidChannel(m_pNetPlay->getGameRoomKind()) && m_pNetPlay->inRoom() && m_pNetPlay->isGameStateNoGame())
	{
		CNetClientManager::getInstance().requestLeaveRoom();
		CTRShortTimeMessage::getInstance().showMessage(format(_STR(MSG_EVENT_GAME_END_MENT), _STR(MSG_RAID)), 2.5f);
	}
#endif
}

/// 나의 던전 레이드 포인트를 받았다.
void CTRNetEventHandler::onRecvtDungeonRaidMyPoint(const int dungeonRaidPoint)
{
#ifdef _DUNGEON_RAID_CHANNEL
	CTRSubDialogManager* pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager != NULL)
	{
		CTRDungeonRaidDlg* pRaidUI = pSubDialogManager->getSubDialogPtr<CTRDungeonRaidDlg>(SUB_PTR_DIALOG_TYPE_DUNGEON_ASSAULT_RAID);
		if(pRaidUI != NULL && pRaidUI->isVisible())
			pRaidUI->updateDungeonRaidMyPoint();
		else
			CTRExchangeSystemIntegration::getInstance().updateRaidPoint(dungeonRaidPoint);
	}
	CTRExchangeSystemIntegration::getInstance().updatePoint();
#endif
}

//////////////////////////////////////////////////////////////////////////

#ifdef _PARTY_SYSTEM

/// 파티에 가입하라는 요청을 받음 (파티장 또는 파티장이 되려는 유저 -> 파티에 속하지 않은 유저)
void CTRNetEventHandler::onRecvPartyInviteRequest(PartyRequestInfo& requestInfo, const int masterServerNum, std::string& masterNickName)
{
	CTRMessengerMainUI::getInstance().onRecvPartyInviteRequest(requestInfo, masterServerNum, masterNickName);
}

/// 파티 시스템, 파티 초대 요청 실패
void CTRNetEventHandler::onRecvPartyInviteRequest_Failed(PartyRequestInfo& requestInfo, std::string& invitedNickName)
{
	DBG_OUTPUT(123, "%s - target : %s, result : %d", __FUNCTION__, invitedNickName.c_str(), requestInfo.m_result);

	CTRMessengerMainUI::getInstance().onRecvPartyRequestFailed(requestInfo, invitedNickName);
}

void CTRNetEventHandler::onRecvPartyInviteAck_Failed(PartyRequestInfo& requestInfo, std::string& invitedNickName)
{
	DBG_OUTPUT(123, "%s - target : %s, result : %d", __FUNCTION__, invitedNickName.c_str(), requestInfo.m_result);

	CTRMessengerMainUI::getInstance().onRecvPartyRequestFailed(requestInfo, invitedNickName);
}

/// 내가 소속되어있는 파티의 정보를 받음
void CTRNetEventHandler::onRecvPartyInfo(PartyRequestInfo& requestInfo, InvitationPartyInfo& partyInfo)
{
	CTRMessengerMainUI::getInstance().onRecvPartyInfo(requestInfo, partyInfo);
}

/// 내가 소속된 파티에 새로운 멤버가 들어옴
void CTRNetEventHandler::onRecvParty_NewUserInfo(InvitationPartyUserInfo& newUserInfo)
{
	CTRMessengerMainUI::getInstance().onRecvPartyNewUserInfo(newUserInfo);
}

/// 내가 소속된 파티에 유저가 나감
void CTRNetEventHandler::onRecvParty_LeaveUser(std::string& leaveUserNickName, ePartyLeaveType leaveType)
{
	CTRMessengerMainUI::getInstance().onRecvPartyLeaveUser(leaveUserNickName, leaveType);
}

/// 내가 소속된 파티에 마스터가 변경됨
void CTRNetEventHandler::onRecvParty_SetMaster(std::string& masterNickName)
{
	CTRMessengerMainUI::getInstance().onRecvPartySetMaster(masterNickName);
}

/// 내가 파티에서 나가졌다
void CTRNetEventHandler::onRecvParty_LeaveAck(ePartyLeaveType leaveType)
{
	CTRMessengerMainUI::getInstance().onRecvPartyLeaveAck(leaveType);
}

/// 파티 게시글 등록 성공 실패여부
void CTRNetEventHandler::onRecvPartyBoardAddRequest(const PartyRequestInfo& requestInfo)
{
	DBG_OUTPUT(123, "%s - %d", __FUNCTION__, requestInfo.m_result);
	CTRMessengerMainUI::getInstance().onRecvPartyBoardAddRequest(requestInfo);
}

/// 파티 게시글 삭제 성공 실패 여부
void CTRNetEventHandler::onRecvPartyBoardDelRequest(const PartyRequestInfo& requestInfo)
{
	DBG_OUTPUT(123, "%s - %d", __FUNCTION__, requestInfo.m_result);
	CTRMessengerMainUI::getInstance().onRecvPartyBoardDelRequest(requestInfo);
}

/// 파티 게시글 목록 받음
void CTRNetEventHandler::onRecvPartyBoardList(const int iCurPageIndex, const int iMaxPageIndex, std::vector<PartyBoardInfo>& vecPartyBoardList)
{
	CTRMessengerMainUI::getInstance().onRecvPartyBoardList(iCurPageIndex, iMaxPageIndex, vecPartyBoardList);
}

/// 파티 게시글 목록 실패
void CTRNetEventHandler::onRecvPartyBoardListFailed(const PartyRequestInfo& requestInfo)
{
	DBG_OUTPUT(123, "%s - (%d)", __FUNCTION__, requestInfo.m_result);
	CTRMessengerMainUI::getInstance().onRecvPartyBoardListFailed(requestInfo);
}

/// 파티 게시글 지원요청 성공
void CTRNetEventHandler::onRecvPartyBoardJoin(const PartyRequestInfo& requestInfo, std::string& strMasterNickName)
{
	CTRMessengerMainUI::getInstance().onRecvPartyBoardJoin(requestInfo, strMasterNickName);
}

/// 파티 게시글 지원요청 실패
void CTRNetEventHandler::onRecvPartyBoardJoinFailed(const PartyRequestInfo& requestInfo)
{
	DBG_OUTPUT(123, "%s - (%d)", __FUNCTION__, requestInfo.m_result);
	CTRMessengerMainUI::getInstance().onRecvPartyBoardJoinFailed(requestInfo);
}

/// 파티 게시글 지원자 목록보기( 파티글 작성한 유저가 보는 것 )
void CTRNetEventHandler::onRecvPartyBoardRequestUserList(std::vector<InvitationPartyUserInfo>& vecPartyBoardUserList, const int iTotalPageIndex, const int iCurPageIndex )
{
	CTRMessengerMainUI::getInstance().onRecvPartyBoardRequestUserList(vecPartyBoardUserList, iTotalPageIndex, iCurPageIndex);
}

/// 파티 게시글 지원자 목록보기 실패
void CTRNetEventHandler::onRecvPartyBoardRequestUserListFailed(const PartyRequestInfo& requestInfo)
{
	DBG_OUTPUT(123, "%s - (%d)", __FUNCTION__, requestInfo.m_result);
	CTRMessengerMainUI::getInstance().onRecvPartyBoardRequestUserListFailed(requestInfo);
}

/// 파티 요청 목록에서 거절
void CTRNetEventHandler::onRecvPartyBoardJoinRefusalAck(const PartyRequestInfo& requestInfo, std::string& strTargetNickName)
{
	DBG_OUTPUT(123, "%s - (%d)", __FUNCTION__, requestInfo.m_result);
	CTRMessengerMainUI::getInstance().onRecvPartyBoardJoinRefusalAck(requestInfo, strTargetNickName);
}

/// 파티 게시글의 지원요청 창을 통하여 파티 가입에 성공(파티 가입 성공시 파티 지원 리스트 재갱신 위해 사용)
void CTRNetEventHandler::onRecvPartyBoardJoinOK(const PartyRequestInfo& requestInfo)
{
	CTRMessengerMainUI::getInstance().onRecvPartyBoardJoinOK(requestInfo);
}


/// 유저가 선택한 파티 게시글의 파티원 목록보기
void CTRNetEventHandler::onRecvPartyBoardJoinList( std::vector<InvitationPartyUserInfo>& vecPartyJoinUserList, const std::string& strMasterNickName )
{
	CTRMessengerMainUI::getInstance().onRecvPartyBoardJoinList(vecPartyJoinUserList, strMasterNickName);
}

/// 유저가 선택한 파티 게시글의 파티원 목록보기 실패
void CTRNetEventHandler::onRecvPartyBoardJoinListFailed(const PartyRequestInfo& requestInfo)
{
	DBG_OUTPUT(123, "%s - (%d)", __FUNCTION__, requestInfo.m_result);
	CTRMessengerMainUI::getInstance().onRecvPartyBoardJoinListFailed(requestInfo);
}


/// 파티원의 정보가 변경됨을 알림
void CTRNetEventHandler::onRecvPartyModifyUserInfo(InvitationPartyUserInfo& userInfo)
{
	CTRMessengerMainUI::getInstance().onRecvPartyModifyUserInfo(userInfo);
}

/// 파티 시스템 TR,EXP 보너스 공지를 받았다.
void CTRNetEventHandler::onRecvPartyBuffBonusNotify(const BuffBonusInfo& buffBonus)
{
	CTRUserInterface::getInstance().onRecvPartyBuffBonusNotify(buffBonus);
}

#endif

//////////////////////////////////////////////////////////////////////////

/// 경쟁 이벤트 공지 알림
void CTRNetEventHandler::onRecvCompetitionEventGameNotify(const bool bStartNotice, const int interval)
{
	eCompetitionEventType competitionEventType = static_cast<eCompetitionEventType>(atoi(CNetClientManager::getInstance().getServerSetting("useCompetitionEvent", "0").c_str()));

	CTRNetPlayManager& netPlayMgr = CTRNetPlayManager::getInstance();
	std::string strNotifyMent = _STR(MSG_MISSION_EVENT);

	if(competitionEventType == eCompetitionEventType_DRHELL_BATTLE)
	{
		strNotifyMent = format(_STR(MSG_DRHELL_BATTLE_NOTIFY_BEFORE_START), interval);
	}
	else if(competitionEventType == eCompetitionEventType_CHAOS_ZERO)
	{
		if(bStartNotice) strNotifyMent = format(_STR(CHAOS_ZERO_PREV_START_NOTIFY),interval);
		else strNotifyMent = format(_STR(CHAOS_ZERO_PREV_END_NOTIFY),interval);
	}
	else if(competitionEventType == eCompetitionEventType_TALES_ACADEMY)
	{
		if(bStartNotice) strNotifyMent = format(_STR(TALES_ACADEMY_PREV_START_NOTIFY), interval);
		else strNotifyMent = format(_STR(TALES_ACADEMY_PREV_END_NOTIFY), interval);
	}
	else
	{
		strNotifyMent = EVENT_CHANNEL::getEventChannelString();

		if(bStartNotice) strNotifyMent = format(_STR(MSG_EVENT_GAME_START_NOTIFY),  strNotifyMent.c_str(), interval);

		else strNotifyMent = format(_STR(MSG_EVENT_GAME_END_NOTIFY),  strNotifyMent.c_str(), interval);
	}	

	CTRSystemNotice::getInstance().showMessage(strNotifyMent);
}

/// 경쟁 이벤트 다음 게임에 대한 정보를 받음
void CTRNetEventHandler::onRecvCompetitionEventNextGameInfo(OlympicGameInfo& gameInfo)
{
#ifdef _HERO_WAR
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HERO_WAR)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRHeroWarChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHeroWarChannelDlg>(SUB_PTR_DIALOG_TYPE_HERO_WAR_CHANNEL);
		if(pChannelUI)
		{
			pChannelUI->onRecvHeroWarNextGameInfo(gameInfo);
		}
	}
#endif

#ifdef _WINTER_FESTIVAL
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_WINTER_FESTIVAL)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRWinterFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRWinterFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_WINTER_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->onRecvNextGameInfo(gameInfo);
		}
	}
#endif

#ifdef _HORROR_PARK_CHANNEL
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HORROR_PARK)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRHorrorParkChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHorrorParkChannelDlg>(SUB_PTR_DIALOG_TYPE_HORROR_PARK);
		if(pChannelUI)
		{
			pChannelUI->onRecvNextGameInfo();
		}
	}
#endif

#ifdef _CHAOS_ZERO_
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS_ZERO)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosZeroChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosZeroChannelDlg>(SUB_PTR_DIALOG_TYPE_CHAOS_ZERO);
		if(pChannelUI)
		{
			pChannelUI->onRecvChaosZeroNextGameInfo(gameInfo);
		}
	}
#endif

	CTRLobbyUI::getInstance().onRecvCompetitionEventNextGameInfo(gameInfo);
}

/// 경쟁 이벤트 파티에 대한 유저의 정보 받음
void CTRNetEventHandler::onRecvCompetitionEventPartyUserInfoOK(eEventPartyType partyType, const __int64& point, const __int64& accPoint)
{
	CTRSubDialogManager *pSubDialogManager = NULL;

#ifdef _CHAOS
	if(CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS))
	{
		pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
		if (pSubDialogManager)
		{
			CTRChaosChannelDialog* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosChannelDialog>(SUB_PTR_DIALOG_TYPE_EVENT_CHAOS);
			if(pChannelUI)
			{
				pChannelUI->onRecvCompetitionEventPartyUserInfoOK(partyType, point);
			}
		}
	}	
#endif //_CHAOS

#ifdef _HERO_WAR
	if(CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HERO_WAR))
	{
		pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
		if (pSubDialogManager)
		{
			CTRHeroWarChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHeroWarChannelDlg>(SUB_PTR_DIALOG_TYPE_HERO_WAR_CHANNEL);
			if(pChannelUI)
			{
				pChannelUI->onRecvMyHeroWarInfo(partyType, point, accPoint);
			}
		}
	}
#endif

#ifdef _WINTER_FESTIVAL
	if(CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_WINTER_FESTIVAL))
	{
		pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
		if (pSubDialogManager)
		{
			CTRWinterFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRWinterFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_WINTER_FESTIVAL);
			if(pChannelUI)
			{
				pChannelUI->onRecvCompetitionEventPartyUserInfoOK(partyType, point, accPoint);
			}
		}
	}
#endif

#ifdef _HORROR_PARK_CHANNEL
	if(CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HORROR_PARK))
	{
		pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
		if (pSubDialogManager)
		{
			CTRHorrorParkChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHorrorParkChannelDlg>(SUB_PTR_DIALOG_TYPE_HORROR_PARK);
			if(pChannelUI)
			{
				pChannelUI->onRecvCompetitionEventPartyUserInfoOK(partyType);
			}
		}
	}
#endif

#ifdef _CHAOS_ZERO_
	if(CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS_ZERO))
	{
		pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
		if (pSubDialogManager)
		{
			CTRChaosZeroChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosZeroChannelDlg>(SUB_PTR_DIALOG_TYPE_CHAOS_ZERO);
			if(pChannelUI)
			{
				pChannelUI->onRecvMyChaosZeroInfo(partyType, point, accPoint);
			}
		}
	}
#endif

	CTRLobbyUI::getInstance().onRecvCompetitionEventPartyUserInfoOK(partyType, point, accPoint);

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_JOIN_EVENT_PARTY);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_OCCUPIED_TERRITORY);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_CHAOS_CONTRIBUTED_POINT);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_EVENT_PARTY_POINT);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

/// 경쟁 이벤트 파티에 대한 유저 정보 받기 실패
void CTRNetEventHandler::onRecvCompetitionEventPartyUserInfoFailed(eCompetitionEventResult result)
{
	CTRLobbyUI::getInstance().onRecvCompetitionEventFailed(result);
}

/// 경쟁 이벤트 일정이 더이상 없음
void CTRNetEventHandler::onRecvCompetitionEventGameEmpty()
{
#ifdef _HERO_WAR
	if(CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HERO_WAR))
	{
		CTRSubDialogManager* pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
		if (pSubDialogManager)
		{
			CTRHeroWarChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHeroWarChannelDlg>(SUB_PTR_DIALOG_TYPE_HERO_WAR_CHANNEL);
			if(pChannelUI)
			{
				pChannelUI->onRecvHeroWarGameEmpty();
			}
		}
	}
#endif

#ifdef _WINTER_FESTIVAL
	if(CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_WINTER_FESTIVAL))
	{
		CTRSubDialogManager* pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
		if (pSubDialogManager)
		{
			CTRWinterFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRWinterFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_WINTER_FESTIVAL);
			if(pChannelUI)
			{
				pChannelUI->onRecvGameEmpty();
			}
		}
	}
#endif

#ifdef _HORROR_PARK_CHANNEL
	if(CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HORROR_PARK))
	{
		CTRSubDialogManager* pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
		if (pSubDialogManager)
		{
			CTRHorrorParkChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHorrorParkChannelDlg>(SUB_PTR_DIALOG_TYPE_HORROR_PARK);
			if(pChannelUI)
			{
				pChannelUI->onRecvGameEmpty();
			}
		}
	}
#endif

#ifdef _CHAOS_ZERO_
	if(CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS_ZERO))
	{
		CTRSubDialogManager* pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
		if (pSubDialogManager)
		{
			CTRChaosZeroChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosZeroChannelDlg>(SUB_PTR_DIALOG_TYPE_CHAOS_ZERO);
			if(pChannelUI)
			{
				pChannelUI->onRecvChaosZeroGameEmpty();
			}
		}
	}
#endif

	CTRLobbyUI::getInstance().onRecvCompetitionEventGameEmpty();
}

/// 경쟁 이벤트 오늘의 일정
void CTRNetEventHandler::onRecvCompetitionEventTodayGameInfo(const std::vector<OlympicGameInfo>& competionEventGameList)
{
#ifdef _HORROR_PARK_CHANNEL
	if(CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HORROR_PARK))
	{
		CTRSubDialogManager* pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
		if (pSubDialogManager)
		{
			CTRHorrorParkChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHorrorParkChannelDlg>(SUB_PTR_DIALOG_TYPE_HORROR_PARK);
			if(pChannelUI)
			{
				pChannelUI->onRecvCompetitionEventTodayGameInfo(competionEventGameList);
			}
		}
	}
#endif

	CTRLobbyUI::getInstance().onRecvCompetitionEventTodayGameInfo(competionEventGameList);
}

/// 경쟁 이벤트 파티에 가입 결과
void CTRNetEventHandler::onRecvCompetitionEventPartyJoinOK(eEventPartyType partyType, std::vector<RewardInfo>& rewardList)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvCompetitionEventPartyJoin(partyType, rewardList);
	}
	else if(CTRLobbyUI::getInstance().isActive())
	{
		CTRLobbyUI::getInstance().onRecvCompetitionEventPartyJoin(partyType, rewardList);
	}

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_JOIN_EVENT_PARTY);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();

	DBG_OUTPUT("onRecvCompetitionEventPartyJoinOK (%d)", partyType);
}

/// 경쟁 이벤트 파티 가입 실패
void CTRNetEventHandler::onRecvCompetitionEventPartyJoinFailed(eCompetitionEventResult result)
{
	CTRLobbyUI::getInstance().onRecvCompetitionEventFailed(result);
	CTRLobbyUI::getInstance().onRecvCompetitionEventPartyJoinFailed(result);
	if (CTRGameParkUI::getInstance().isActive())
		CTRGameParkUI::getInstance().onRecvCompetitionEventFailed(result);
}

/// 경쟁 이벤트 파티에 대한 정보 받음
void CTRNetEventHandler::onRecvCompetitionEventPartyInfo(std::map<eEventPartyType, CompetitionPartyInfo>& partyInfo)
{
	CTRSubDialogManager *pSubDialogManager = NULL;

#ifdef _HERO_WAR
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HERO_WAR)) return;

	pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRHeroWarChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHeroWarChannelDlg>(SUB_PTR_DIALOG_TYPE_HERO_WAR_CHANNEL);
		if(pChannelUI)
		{
			pChannelUI->onRecvHeroWarPartyPoint(partyInfo);
		}
	}
#endif

#ifdef _WINTER_FESTIVAL
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_WINTER_FESTIVAL)) return;

	pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRWinterFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRWinterFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_WINTER_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->onRecvPartyPoint(partyInfo);
		}
	}
#endif

#ifdef _HORROR_PARK_CHANNEL
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HORROR_PARK)) return;

	pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRHorrorParkChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHorrorParkChannelDlg>(SUB_PTR_DIALOG_TYPE_HORROR_PARK);
		if(pChannelUI)
		{
			pChannelUI->onRecvPartyPoint(partyInfo);
		}
	}
#endif

	CTRLobbyUI::getInstance().onRecvCompetitionEventPartyInfo(partyInfo);
}

/// 경쟁 이벤트 승리팀 보상을 받음
void CTRNetEventHandler::onRecvCompetitionEventWinnerPartyRewardOK( std::vector<RewardInfo>& rewardList )
{
	CTRSubDialogManager *pSubDialogManager = NULL;

#ifdef _HERO_WAR
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HERO_WAR)) return;

	pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRHeroWarChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHeroWarChannelDlg>(SUB_PTR_DIALOG_TYPE_HERO_WAR_CHANNEL);
		if(pChannelUI)
		{
			pChannelUI->onRecvHeroWarWinTeamReward(rewardList);
		}
	}	
#endif

#ifdef _WINTER_FESTIVAL
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_WINTER_FESTIVAL)) return;

	pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRWinterFestivalChannelDlg* pWinterFestivalChannelUI = pSubDialogManager->getSubDialogPtr<CTRWinterFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_WINTER_FESTIVAL);
		if(pWinterFestivalChannelUI)
		{
			pWinterFestivalChannelUI->onRecvWinTeamReward(rewardList);
		}
	}
#endif

#ifdef _HORROR_PARK_CHANNEL
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_HORROR_PARK)) return;

	pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRHorrorParkChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRHorrorParkChannelDlg>(SUB_PTR_DIALOG_TYPE_HORROR_PARK);
		if(pChannelUI)
		{
			pChannelUI->onRecvWinTeamReward(rewardList);		
		}
	}
#endif

#ifdef _CHAOS_ZERO_
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS_ZERO)) return;

	pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosZeroChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosZeroChannelDlg>(SUB_PTR_DIALOG_TYPE_CHAOS_ZERO);
		if(pChannelUI)
		{
			pChannelUI->onRecvWinTeamReward(rewardList);		
		}
	}
#endif

	CTRLobbyUI::getInstance().onRecvCompetitionEventWinnerPartyRewardOK(rewardList);

	if (!rewardList.empty()) CTRRewardManager::getInstance().getReward(rewardList,true);
}

/// 경쟁 이벤트 승리팀 보상 받기 실패
void CTRNetEventHandler::onRecvCompetitionEventWinnerPartyRewardFailed( eCompetitionEventResult result )
{
	CTRLobbyUI::getInstance().onRecvCompetitionEventFailed(result);
}

/// 경쟁 이벤트 아이템 기여 결과
void CTRNetEventHandler::onRecvCompetitionEventPointAddUseItem(int iAddPoint)
{
	CTRShortTimeMessage::showMessage(_STR(MSG_CONTRIBUTE_SUCCESS));
}

void CTRNetEventHandler::onRecvCompetitionEventPointAddUsePotionItem(int iAddPoint)
{
	COkDialogEx::getInstance().showDialog(format(_STR(MSG_ADD_COMPETITION_EVENT_POINT), iAddPoint));
}

void CTRNetEventHandler::onRecvCompetitionEventPointAddUseItemFailed(eCompetitionEvent_POINT_ADD_RESULT result)
{
	std::string strMent = "";

	switch(result)
	{
	case eCompetitionEvent_POINT_ADD_RESULT_UNKOWN:
		strMent = _STR(HS_ERR_UNKNOWN);
		break;

	case eCompetitionEvent_POINT_ADD_RESULT_CANT_GETPOINT_NOMORE:		
		strMent = _STR(FAILED_CANNOT_CONTRIBUTE_MORE_TODAY);
		break;

	case eCompetitionEvent_POINT_ADD_RESULT_NOT_GIVETIME:		
		strMent = _STR(MSG_DRHELL_BATTLE_CANNOT_INPUT);
		break;
	}

	CTRShortTimeMessage::showMessage(strMent);
}

void CTRNetEventHandler::onRecvCompetitionEventPersonalPoint(int m_StepNum, int m_Point, bool isReward)
{
	CTRLobbyUI::getInstance().onRecvCompetitionEventPersonalPoint(m_StepNum, m_Point, isReward);
}

void CTRNetEventHandler::onRecvCompetitionEventPersonalReward(int m_RefreshItemNum, bool isReward)
{
	CTRLobbyUI::getInstance().onRecvCompetitionEventPersonalReward(m_RefreshItemNum, isReward);
}

#ifdef _CHAOS_ZERO_
/// 경쟁 이벤트 지역정보
void CTRNetEventHandler::onRecvCompetitionEventTerritoryInfoOK(std::map<int, std::pair<eEventPartyType, int> > & territoryWinners, std::map<std::pair<int/*StageNum*/, eEventPartyType>, INT64 > & territoryTalesKnightsWinInfo)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS_ZERO)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRChaosZeroChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRChaosZeroChannelDlg>(SUB_PTR_DIALOG_TYPE_CHAOS_ZERO);
		if(pChannelUI)
		{
			pChannelUI->onRecvCompetitionEventTerritoryInfoOK(territoryWinners,territoryTalesKnightsWinInfo);
		}
	}
}

void CTRNetEventHandler::onRecvCompetitionEventTerritoryInfoFailed(eCompetitionEventResult result, int territoryNum)
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_CHAOS_ZERO)) return;

	CTRShortTimeMessage::getInstance().showMessage(_STR(NOT_FOUND_TERRITORY_INFO));
}
#endif

#ifdef _OFFICIAL_COMPETITION_CHANNEL
/// 채널 정보를 받았다. 주의 : room kind가 일치하는 것만 정보 업데이트!
void CTRNetEventHandler::onRecvChannelInfo(const GAMECHANNEL::CHANNEL_INFO_MAP& info)
{
	CTRLobbyUI::getInstance().onRecvChannelInfo(info);
};

/// 유저 포인트 정보를 받았다. 주의 : 정보 인덱스가 일치하는 것만 업데이트.
void CTRNetEventHandler::onRecvUserPointInfo(eUserPointType pointType, const USER::UserPoint& pointInfo)
{
	CTRLobbyUI::getInstance().onRecvUserPointInfo(pointType, pointInfo);
#ifdef _SHOP_RENEWAL_
	CTRShopManager::getInstance().onRecvUserPointInfo(pointType, pointInfo);
#endif

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_USER_POINT_TYPE);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_USER_POINT_TYPE_COUNT);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
};
#endif


void CTRNetEventHandler::onRecvTimeCountStartAck(const bool result, const short playTime, const byte countIndex)
{
	CGameManager::getInstance().onRecvTimeCountStartAck(result,(float)playTime,countIndex);
}

void CTRNetEventHandler::onRecvTimeCountEndAck(const byte countIndex, const short playTime, const bool checkAlivePlayer, std::vector<unsigned int>& alivePlayerList)
{
	CGameManager::getInstance().onRecvTimeCountEndAck(countIndex,(float)playTime,checkAlivePlayer,alivePlayerList);
}

// 매출 프로모션 아이템의 갯수 갱신
#ifdef PROMOTION_SALE
void CTRNetEventHandler::onRecvPromotionItemCount()
{
	if(CTRSalePromotionPopup::getInstance().isVisible())
		CTRSalePromotionPopup::getInstance().updatePromotionItem();
}
#endif

#ifdef _SHU_SYSTEM_
//!<--------------------------------------------------------------------------------------------

//!< 슈 아이템 정보를 갱신하였다..
void CTRNetEventHandler::onRecvUpdateShuItemInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CUserShuItemInfo> & update_Info)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvUpdateShuItem(update_Info);
}

//!< 특정 슈캐릭터(eCharacterShuKind)의 전용 아이템 정보를 갱신하였다.
void CTRNetEventHandler::onRecvUpdateShuItemByCharacter(const eCharacterShuKind character,std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CUserShuItemInfo> & update_Info)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvUpdateShuItemByCharacter(character,update_Info);
}

//!< 특정 포지션의 모든 아이템 정보를 갱신하였다.
void CTRNetEventHandler::onRecvUpdateShuItemByPosition(const SHU_ITEM_POSITION position,std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CUserShuItemInfo> & update_Info)
{

}

//!< 슈 아이템 상태 정보를 갱신하였다.
void CTRNetEventHandler::onRecvUpdateShuItemState(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::eItem_curr_state> & update_Info)
{

}

// --------------------------------------------------------------------------------------------
// 슈캐릭터 정보
// --------------------------------------------------------------------------------------------

//!<  슈캐릭터 정보를 갱신하였다.
void CTRNetEventHandler::onRecvUpdateShuCharacterInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::CMyShuCharacterInfo> & update_Info)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvUpdateShuCharacterInfo(update_Info);
}

//!< 슈 알아이템을 사용하여 슈캐릭터 정보를 생성하는데 성공하였다.
void CTRNetEventHandler::onRecvCreateShuCharacterSucess(const SHU_SYSTEM::CTRShuItemID & eggItemID,const SHU_SYSTEM::CTRShuItemID & shuCharItemID)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvCreateShuCharacterSucess(eggItemID,shuCharItemID);
}

//!< 현재 선택된 슈캐릭터를 변경하였다.
void CTRNetEventHandler::onRecvUpdateSelectCurrentShuCharacter(const SHU_SYSTEM::CTRShuItemID & itemID)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvUpdateSelectCurrentShuCharacter(itemID);
}

//!< 슈 캐릭터 아바타 정보를 갱신하였다
void CTRNetEventHandler::onRecvUpdateShuAvatarInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::MyShuAvatarInfo> & update_Info)
{

}

//!< 슈 캐릭터 아바타 정보를 변경하였다.
void CTRNetEventHandler::onRecvChangeShuAvatarInfo(std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::MyShuAvatarInfo> & update_Info)
{

}

//!< 슈 캐릭터 상태를 갱신하였다.
void CTRNetEventHandler::onRecvShuCharStatusInfo( std::map<SHU_SYSTEM::CTRShuItemID, SHU_SYSTEM::ShuStatusInfo> & update_info)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvShuCharStatusInfo(update_info);
}

//!< 슈 캐릭터명을 변경 하였다.
void CTRNetEventHandler::onRecvChangeShuCharacterName(const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const std::string & name)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvChangeShuCharacterName(shuCharItemID,name);
}

//!< 슈 관리포인터를 사용하여 특정 액션을 취하였다.
void CTRNetEventHandler::onRecvShuCharManagerAction(const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const eShuManagerActionType action,
													const std::map<eShuStatusType, int> & apply_value,const int remainMP)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvShuCharManagerAction(shuCharItemID,action,apply_value,remainMP);
}

//!< 슈 캐릭터에게 특정 아이템을 사용하여 결과를 받았다.
void CTRNetEventHandler::onRecvShuCharUseItemSuccess(const SHU_SYSTEM::CTRShuItemID & charItemID,const SHU_ITEM_POSITION useItemPosition,
													 const SHU_SYSTEM::CTRShuItemID & useItemID,const int useItemNumber,const int useCount)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvShuCharUseItemSuccess(charItemID,useItemPosition,useItemID,useItemNumber);
}

//!< 슈 캐릭터가 레벨 정보가 변경 되었다.
void CTRNetEventHandler::onRcvShuCharLevelModify(const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const int preLevel,const int currLevel)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRcvShuCharLevelModify(shuCharItemID,preLevel,currLevel);
}

// --------------------------------------------------------------------------------------------
// 슈캐릭터를 이요한 탐색정보
// --------------------------------------------------------------------------------------------

//!< 현재 진행 중인 탐사 지역 정보를 갱신하였다.
void CTRNetEventHandler::onRecvShuCharExploreZoneInfo(std::vector<BYTE/*zoneNumber*/> & zone_list)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvShuCharExploreZoneInfo(zone_list);
}

//!< 특정 탐사 지역의 탐사를 시작한다.
void CTRNetEventHandler::onRecvShuCharExploreZone_Start(const BYTE zone_number,const SHU_SYSTEM::CTRShuItemID & shuCharItemID)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvShuCharExploreZone_Start(zone_number,shuCharItemID);
}

//!< 특정 탐사 지역의 탐사를 중지하였다.
void CTRNetEventHandler::onRecvShuCharExploreZone_Stop(const BYTE zone_number,const SHU_SYSTEM::CTRShuItemID & shuCharItemID)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvShuCharExploreZone_Stop(zone_number,shuCharItemID);
}
//!< 특정 탐사 지역의 보상을 받았다.(탐사 완료)
void CTRNetEventHandler::onRecvShuCharExploreZone_Reward(const BYTE zone_number,const SHU_SYSTEM::CTRShuItemID & shuCharItemID,const std::vector<RewardInfo> & reward_list)
{
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvShuCharExploreZone_Reward(zone_number,shuCharItemID,reward_list);
}
//!< 특정 슈의 만랩 선물 보상을 받았다.
void CTRNetEventHandler::onRecvSuccessShuCharGiftToThisPlayer(const SHU_SYSTEM::CTRShuItemID & from_ShuCharItemID,const int current_exp,const std::vector<RewardInfo> & reward_list)
{	
	SHU_SYSTEM::CTRShuDlg_Management::getInstance().onRecvSuccessShuCharGiftToThisPlayer(from_ShuCharItemID,current_exp,reward_list);
}

//!< 게임 안에서 캐릭터 --> 슈 태그 액션을 시작했다..
void CTRNetEventHandler::onRecvShuCharIngameTagAction_Start(const int nPlayerIndex,const int characterAvatarItemNum)
{
	if (m_pNetEventListener != NULL){
		m_pNetEventListener->onRecvShuCharIngameTagAction_Start(nPlayerIndex,characterAvatarItemNum);
	}
}
//!< 게임 안에서 슈 --> 캐릭터 태그 액션을 종료하였다.
void CTRNetEventHandler::onRecvShuCharIngameTagAction_End(const int nPlayerIndex,const SHU_SYSTEM::eIN_GAME_SHU_TAG_END_TYPE end_type)
{
	if (m_pNetEventListener != NULL){
		m_pNetEventListener->onRecvShuCharIngameTagAction_End(nPlayerIndex,end_type);
	}
}

//!< 게임 안아세 로컬유저의 슈 태그 액션 시작을 실패하였다.
void CTRNetEventHandler::onRecvThisPlayerShuCharIngameTagAction_Start_failed()
{
	if (m_pNetEventListener != NULL){
		m_pNetEventListener->onRecvThisPlayerShuCharIngameTagAction_Start_failed();
	}
}

//!< 게임방 안에서 특정 유저의 슈 캐릭터 정보가 변경되었다.
void CTRNetEventHandler::onRecvPlayerShuCharInfoModify(const int nPlayerIndex,const SHU_SYSTEM::CPlayerShuCharacterInfo & updateInfo)
{
	if(m_pNetEventListener != NULL){
		m_pNetEventListener->onRecvPlayerShuCharInfoModify(nPlayerIndex,updateInfo);
	}
}

//!<--------------------------------------------------------------------------------------------
#endif

//////////////////////////////////////////////////////////////////////////
#ifdef _DRAWING_OF_THE_MONTH

//!< 이달의 뽑기 정보를 받았다.
void CTRNetEventHandler::onRecvMonthlyGotchaSystemInfo(eDOMResult result)
{
	if(result != eDOMResult_SUCCESS)
	{
		DBG_OUTPUT(123, "onRecvMonthlyGotchaSystemInfo - %d", result);

		if(result != eDOMResult_SUCCESS_WARNING) return;
	}

	if(CTRShopGoodsListDialog::getInstance().isVisible())
	{
		CTRShopGoodsListDialog::getInstance().updateMonthlyGachaSystemInfo();
	}
	else if(CTRMyRoomGoodsListDialog::getInstance().isVisible())
	{
		CTRMyRoomGoodsListDialog::getInstance().updateMonthlyGachaSystemInfo();
	}
#ifdef _SHOP_RENEWAL_
	else if (CTRShopManager::getInstance().GetShopDialog())
	{
		CTRShopManager::getInstance().updateMonthlyGachaSystemInfo();
	}
#endif
}

//!< 이달의 뽑기 나의 정보를 받았다.
void CTRNetEventHandler::onRecvMonthlyGotchaSystemUserInfo(eDOMResult result)
{
	if(result != eDOMResult_SUCCESS)
	{
		DBG_OUTPUT(123, "onRecvMonthlyGotchaSystemUserInfo - %d", result);

		if(result != eDOMResult_SUCCESS_WARNING) return;
	}

	if(CTRShopGoodsListDialog::getInstance().isVisible())
	{
		CTRShopGoodsListDialog::getInstance().updateMonthlyGachaSystemUserInfo();
	}
	else if(CTRMyRoomGoodsListDialog::getInstance().isVisible())
	{
		CTRMyRoomGoodsListDialog::getInstance().updateMonthlyGachaSystemUserInfo();
	}
#ifdef _SHOP_RENEWAL_
	else if (CTRShopManager::getInstance().GetShopDialog())
	{
		CTRShopManager::getInstance().updateMonthlyGachaSystemUserInfo();
	}
#endif
}

//!< 이달의 뽑기 쿠폰을 사용했다.
void CTRNetEventHandler::onRecvMonthlyGotchaSystemUseCoupon(eDOMResult result, int id, std::vector<DOM::DOM_ITEM>& resultItem)
{
	if(result != eDOMResult_SUCCESS)
	{
		DBG_OUTPUT(123, "onRecvMonthlyGotchaSystemUseCoupon - %d", result);

		if(result != eDOMResult_SUCCESS_WARNING) return;
	}

	if(CTRShopGoodsListDialog::getInstance().isVisible())
	{
		CTRShopGoodsListDialog::getInstance().updateMonthlyGachaSystemUserInfo();
		CTRShopGoodsListDialog::getInstance().onRecvMonthlyGotchaSystemUseCoupon(resultItem);
	}
	else if(CTRMyRoomGoodsListDialog::getInstance().isVisible())
	{
		CTRMyRoomGoodsListDialog::getInstance().updateMonthlyGachaSystemUserInfo();
		CTRMyRoomGoodsListDialog::getInstance().onRecvMonthlyGotchaSystemUseCoupon(resultItem);
	}
#ifdef _SHOP_RENEWAL_
	else if (CTRShopManager::getInstance().GetShopDialog())
	{
		CTRShopManager::getInstance().updateMonthlyGachaSystemUserInfo();
		CTRShopManager::getInstance().onRecvMonthlyGotchaSystemUseCoupon(resultItem);
	}
#endif
}

//!< 이달의 뽑기 확정 보상을 받았다.
void CTRNetEventHandler::onRecvMonthlyGotchaSystemFixReward(eDOMResult result, int id, int resultItem)
{
	if(result != eDOMResult_SUCCESS)
	{
		DBG_OUTPUT(123, "onRecvMonthlyGotchaSystemFixReward - %d", result);

		if(result != eDOMResult_SUCCESS_WARNING) return;		
	}

	if(CTRShopGoodsListDialog::getInstance().isVisible())
	{
		CTRShopGoodsListDialog::getInstance().updateMonthlyGachaSystemUserInfo();
		CTRShopGoodsListDialog::getInstance().onRecvMonthlyGotchaSystemFixReward(resultItem);
	}
	else if(CTRMyRoomGoodsListDialog::getInstance().isVisible())
	{
		CTRMyRoomGoodsListDialog::getInstance().updateMonthlyGachaSystemUserInfo();
		CTRMyRoomGoodsListDialog::getInstance().onRecvMonthlyGotchaSystemFixReward(resultItem);
	}
#ifdef _SHOP_RENEWAL_
	else if (CTRShopManager::getInstance().GetShopDialog())
	{
		CTRShopManager::getInstance().updateMonthlyGachaSystemUserInfo();
		CTRShopManager::getInstance().onRecvMonthlyGotchaSystemFixReward(resultItem);
	}
#endif
}

#endif

//////////////////////////////////////////////////////////////////////////
/// 창고 처리 결과를 받았다.
void CTRNetEventHandler::onRecvStorageResult()
{
	if(CTRMyroomDlg::getInstance().isVisible())
	{
		CTRMyroomDlg::getInstance().updateItemStorageDlg();
	}

	if (CTRFarmUI::getInstance().isActive())
		CTRFarmUI::getInstance().FishingRewardUpdate();
}

/// 보관함에 아이템 저장 요청 결과를 받았다.
void CTRNetEventHandler::onRecvStorage_SaveItem_Result(eStorage_Request_Result result)
{
#ifdef _HUMONG_PICKBOARD_
	CTRPaperPickBoardDialog* pBoardDlg = CTRGameParkUI::getInstance().getHumongPickBoard();
	if(pBoardDlg && pBoardDlg->isVisible())
	{
		pBoardDlg->onRecvStorage_SaveItem_Result(result);
	}
#endif

	if(result != eStorage_Request_Result_OK) return;

	if(CTRMyroomDlg::getInstance().isVisible())
	{
		CTRMyroomDlg::getInstance().updateItemStorageDlg();
	}

	COkDialogEx::getInstance().showDialog(_STR(ITEM_STORAGE_SUCCESS_SAVE_ITEM));

	CTRGameParkUI::getInstance().onRecvCapsuleMachineInsertItemStorage();
	CTRLotteryMainDialog *pDlg = CTRMyroomDlg::getInstance().getLotteryMainDialog();
	if (pDlg) pDlg->getEventHandler().onRecvCapsuleMachineInsertItemStorage();

#ifdef _TR_KNIGHTAGE_
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvStorage_SaveItem_Result();
#endif

#ifdef _TALES_MARBLE_
	{
		DICE_BOARD::CTRDiceBoardManager *pManager = CNetClientManager::getInstance().getDiceBoardManager();
		if(pManager) pManager->onRecvStorage_SaveItem_Result();
	}
#endif
}

/// 보관함에 있는 아이템 선물 요청 결과를 받았다.
void CTRNetEventHandler::onRecvStorage_Gift_Item_Result()
{
	if(CTRMyroomDlg::getInstance().isVisible())
	{
		CTRMyroomDlg::getInstance().updateItemStorageDlg();
	}

	COkDialogEx::getInstance().showDialog(_STR(GIFT_SEND_OK));
}

/// 창고에 있는 아이템 마이룸에 받기 요청 결과를 받았다.
void CTRNetEventHandler::onRecvStorage_Get_Item_Result(std::vector<int> item)
{
	if(CTRMyroomDlg::getInstance().isVisible())
	{
		CTRMyroomDlg::getInstance().updateItemStorageDlg();
	}

	if (item.size() == 1)
	{
		const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(item.at(0));
		if (pItem != NULL && pItem->isFarmItem())
		{
			COkDialogEx::getInstance().showDialog(_STR(MSG_FARM_TRUNK_DEFINITE));
		}
		else
		{
			COkDialogEx::getInstance().showDialog(_STR(ITEM_STORAGE_SUCCESS_GET_ITEM));
		}
	}
	else
	{
		COkDialogEx::getInstance().showDialog(_STR(ITEM_STORAGE_SUCCESS_GET_ALL_ITEM)); 
	}

	bool requestExp = false;
	for (auto&i : item) {
		const CItemInfoNode* goodsInfo = CClientItemList::getInstance().getItemInfo(i);
		if(goodsInfo && goodsInfo->getPosition() == eFuncItemPosition_ADD_EXP) {
			requestExp = true;
		}
	}
	if (requestExp) CNetClientManager::getInstance().requestExp(eLevelUPKind_RUN);
}


//////////////////////////////////////////////////////////////////////////

/// 정액권 사용 기간 만료를 통보 받았다.
void CTRNetEventHandler::onRecvFreePass_Expire_Notify(const UserFreePassDesc& fDesc)
{
	if(CTRMyroomDlg::getInstance().isVisible())
	{
		CTRMyroomDlg::getInstance().updateItemStorageDlg();
	}

	CTRShopBuyAllDialog::getInstance().setFreePassExpired(fDesc.m_type);
}

void CTRNetEventHandler::onRecvFreePass_Expire_Notify()
{
#ifdef _FISHING_
	CTRFishingSystemManager::getInstance().onRecvFreePass_Notify();
#endif
}

/// 정액권 사용 시작 통보 받았다.
void CTRNetEventHandler::onRecvFreePass_Inspire_Notify(const UserFreePassDesc& fDesc)
{
	if(CTRMyroomDlg::getInstance().isVisible())
	{
		CTRMyroomDlg::getInstance().updateItemStorageDlg();
	}

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_HAS_FREE_PASS);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();

#ifdef _FISHING_
	CTRFishingSystemManager::getInstance().onRecvFreePass_Notify();
#endif
}

#ifdef _REGIST_REWARD_ITEM
//getRegisterRewardItemMgr 가 CNetClientManager의 멤버가 되면 안될듯.
void CTRNetEventHandler::OnRecvMasterRegisteredRewardAck(ROOM_REWARD::eResult_MASTER_REGISTER_REWARD result, int item, __int64 storage_num)
{
	CNetClientManager::getInstance().getRegisterRewardItemMgr()->OnRecvMasterRegisteredRewardAck(result, item, storage_num);
}

void CTRNetEventHandler::OnRecvNotifyRoomRewardRegistered(int item, int master_index, const ROOM_REWARD::SELECT_WINNER& select_winner)
{
	CNetClientManager::getInstance().getRegisterRewardItemMgr()->OnRecvNotifyRoomRewardRegistered(item, master_index, select_winner);
}

void CTRNetEventHandler::OnRecvNotifyRoomRewardClear()
{
	CNetClientManager::getInstance().getRegisterRewardItemMgr()->OnRecvNotifyRoomRewardClear();
}

void CTRNetEventHandler::OnRecvNotifyRoomReward(int item, int player_index, const std::string& player_nick)
{
	CNetClientManager::getInstance().getRegisterRewardItemMgr()->OnRecvNotifyRoomReward(item, player_index, player_nick);

	string strMsg;
	if(player_index == -1)
	{
		strMsg = _STR(REWARDITEM_CANCEL_REWARD);
	}
	else
	{
		strMsg = format("[%s]님이 달리기 상품을 획득하였습니다.", player_nick.c_str());
	}

	CTRUserInterface::getInstance().onRecvShoutItemMsg(eShoutItemOtion_CHAT, strMsg, CTRChattingManager::CHAT_ITEM_NO, false);
}
#endif

void CTRNetEventHandler::OnGameRebirthAck(GAMELOGIC::CPacket_GameRebirthAck::RESULT result, unsigned int player_index, int option)
{
	CGameManager::getInstance().OnGameRebirthAck(result,player_index,option);
}

void CTRNetEventHandler::OnSubjectKingQuestion(const std::vector<SUBJECTKING::QUESTION_ANSWER>& questions)
{
	CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CRandomAnswerModeQuizListPush(questions));
}

void CTRNetEventHandler::OnContinuousContributionPointStartAck(GAMELOGIC::eServer_ADD_CONTRIBUTION_POINT_START_ACK_DETAIL detail)
{

}

void CTRNetEventHandler::OnContinuousContributionPointStopAck(GAMELOGIC::eServer_ADD_CONTRIBUTION_POINT_STOP_ACK_DETAIL detail)
{

}

void CTRNetEventHandler::OnContinuousContributionPointNotify(const std::map<unsigned int, int>& current_point, unsigned int user, int user_delta)
{

}


void CTRNetEventHandler::OnPrivateRSPStartAck(eServer_PRIVATE_RSP_START_ACK_TYPE ack, const std::vector<int>& item_list, int current_reward_state)
{//!< 입장 완료. 혹은 실패. 보상 리스트 데이터. 현재 0단계 보상 확정.
	DBG_OUTPUT(111, "%s : ack(%d), item_list.size(%d), current_reward_state(%d)", __FUNCTION__, ack, item_list.size(), current_reward_state);
	if (CTRGameParkUI::getInstance().isActive())
		CTRGameParkUI::getInstance().OnPrivateRSPStartAck(ack, item_list, current_reward_state);
}

void CTRNetEventHandler::OnPrivateRSPGameStartAck(eServer_PRIVATE_RSP_GAME_START_ACK_TYPE ack, int current_reward_state, int left_time, int next_state)
{//!< 현재 확정 보상 단계 데이터. 타이머 시간. 남은 단계 수.
	DBG_OUTPUT(111, "%s : ack(%d), current_reward_state(%d), left_time(%d), next_state(%d)", __FUNCTION__, ack, current_reward_state, left_time, next_state);
	if (CTRGameParkUI::getInstance().isActive())
		CTRGameParkUI::getInstance().OnPrivateRSPGameStartAck(ack, current_reward_state, left_time, next_state);
}

void CTRNetEventHandler::OnPrivateRSPSelectionAck(eServer_PRIVATE_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION_RESULT r, eRSP_SELECTION server_selection, int current_state, int current_state_reward)
{//!< 승, 패, 무승부. 시간 오버. 현재 보상 단계 데이터.
	DBG_OUTPUT(111, "%s : ack(%d), r(%d), server_selection(%d), current_state(%d), current_state_reward(%d)", __FUNCTION__, ack, r, server_selection, current_state, current_state_reward);
	if (CTRGameParkUI::getInstance().isActive())
		CTRGameParkUI::getInstance().OnPrivateRSPSelectionAck(ack, r, server_selection, current_state, current_state_reward);
}

void CTRNetEventHandler::OnGlobalRSPStartNotify(int message_in_str_table, int game_schedule_left_time, int game_entrance_left_time)
{//!< 성주신변덕 이벤트(전체 가위바위보) 시작 알림. 메세지 포함. 
	//!< game_schedule_left_time : 시작까지 남은 시간. (남은 시간이 0일때 이벤트 시작)
	//!< game_entrance_left_time : 입장 완료까지 남은 시간. game_schedule_left_time 가 0이어야 game_entrance_left_time 시간이 흘러간다.
	DBG_OUTPUT(111, "%s : game_schedule_left_time(%d), game_entrance_left_time(%d)", __FUNCTION__, game_schedule_left_time, game_entrance_left_time);
	if (game_schedule_left_time == 0 && game_entrance_left_time > 0)
	{	// 입장 가능
		CTRNetPlayManager::getInstance().setGlobalRSPJoinTime(game_entrance_left_time);

		int iLeftMinute = (game_entrance_left_time/* + 30000*/) / 60000;
		CTRSystemNotice::getInstance().showMessage(format(_STR(SRP_ENTRY_ENDS), iLeftMinute +1));
	}
	else if (game_schedule_left_time > 0)
	{	// 스케쥴 시작
		int iLeftMinute = (game_schedule_left_time/* + 30000*/) / 60000;
		CTRSystemNotice::getInstance().showMessage(format(_STR(SRP_START_EVENT), iLeftMinute +1));
	}
	else
	{
		CTRNetPlayManager::getInstance().setGlobalRSPJoinTime(0);
	}

	if (CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().OnGlobalRSPStartNotify(message_in_str_table, game_schedule_left_time, game_entrance_left_time);
}

void CTRNetEventHandler::OnGlobalRSPEnterAck(eServer_GLOBAL_RSP_ENTER_ACK_TYPE ack, int base_reward, const std::vector<int>& round_rewards, int selection_limit, int time2round_start)
{//!< 입장 실패 혹은 성공. round_reward (0 : 기본 보상, 1: 
	DBG_OUTPUT(111, "%s : ack(%d), base_reward(%d), round_rewards.size(%d), selection_limit(%d), time2round_start(%d)", __FUNCTION__, ack, base_reward, round_rewards.size(), selection_limit, time2round_start);
	if (CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().OnGlobalRSPEnterAck(ack, base_reward, round_rewards, selection_limit, time2round_start);
}

void CTRNetEventHandler::OnGlobalRSPCurrentUserNotify(int delta_user, int user_in_playing)
{//!< 현재 플레이중인 유저 수.  (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
	DBG_OUTPUT(111, "%s : delta_user(%d), user_in_playing(%d)", __FUNCTION__, delta_user, user_in_playing);
	if (CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().OnGlobalRSPCurrentUserNotify(delta_user, user_in_playing);
}

void CTRNetEventHandler::OnGlobalRSPGameStartNotify(int left_time_to_input, int current_state)
{//!< 게임 시작 알림. 입력완료까지 남은 시간.
	DBG_OUTPUT(111, "%s : left_time_to_input(%d), current_state(%d)", __FUNCTION__, left_time_to_input, current_state);
	if (CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().OnGlobalRSPGameStartNotify(left_time_to_input, current_state);
}

void CTRNetEventHandler::OnGlobalRSPSelectionAck(eServer_GLOBAL_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION selection, int left_selection_count, int current_reward_state)
{//!< 선택 성공, 실패. 현재 확정 보상 아이템 데이터 STATE
	DBG_OUTPUT(111, "%s : ack(%d), selection(%d), left_selection_count(%d), current_reward_state(%d)", __FUNCTION__, ack, selection, left_selection_count, current_reward_state);
	if (CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().OnGlobalRSPSelectionAck(ack, selection, left_selection_count, current_reward_state);
}

void CTRNetEventHandler::OnGlobalRSPSelectionInfoNotify(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT])
{//!< 전체 가위, 바위, 보 선택 정보. (주의 : 이벤트가 발생 할때마다 전송하지 않으므로, 가짜 카운트 애니메이션이 필요할지도...)
	DBG_OUTPUT(111, "%s : delta[r(%d), s(%d), p(%d)], select[r(%d), s(%d), p(%d)]", __FUNCTION__, selection_count_delta[0], selection_count_delta[1], selection_count_delta[2], selection_count[0], selection_count[1], selection_count[2]);
	if (CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().OnGlobalRSPSelectionInfoNotify(selection_count_delta, selection_count);
}

void CTRNetEventHandler::OnUpdateRewardInfo(const std::vector<RewardInfo>& rewards)
{
	std::vector<RewardInfo> vecRefreshRewards;
	for (auto &reward : rewards)
	{
		vecRefreshRewards.push_back(reward);
	}

	// 재화 아이템 갱신 요청 추가
	RewardInfo consume;
	consume.eRewardType = eRewardCondition_ITEM;
	consume.iRewardID = atoi(CNetClientManager::getInstance().getServerSetting("PRIVATE_RSP_BASE_ITEM", "0").c_str());
	consume.iRewardCount = atoi(CNetClientManager::getInstance().getServerSetting("PRIVATE_RSP_BASE_ITEM_COUNT", "0").c_str());
	vecRefreshRewards.push_back(consume);

	CTRRewardManager::getInstance().getReward(vecRefreshRewards, true);
}

void CTRNetEventHandler::OnGlobalRSPSelectionResultNotify(eRSP_SELECTION selection, eRSP_SELECTION_RESULT result, int current_reward_state, int current_state)
{//결과가 패배라면,  이미 아이템이 지급되어 있다.
	DBG_OUTPUT(111, "%s : selection(%d), result(%d), current_reward_state(%d), current_state(%d)", __FUNCTION__, selection, result, current_reward_state, current_state);
	if (CTRLobbyUI::getInstance().isActive())
		CTRLobbyUI::getInstance().OnGlobalRSPSelectionResultNotify(selection, result, current_reward_state, current_state);
}

void CTRNetEventHandler::OnSubjectKingAnswerValidation(int question, int answer, SUBJECTKING::eServer_SUBJECTKING_VALIDATE_ANSWER_ACK_TYPE ack)
{
	DBG_OUTPUT("SubjectKing Answer Check %d", ack);
}

void CTRNetEventHandler::OnInGameSpecialAbilityAcquire(int boardindex, int param, int user_index, GAMELOGIC::eRoom_INGAME_SPECIAL_ABILITY_ACQUIRE_ACK_DETAIL detail, int skill_group, int groupType, const std::string& skill_group_name, const std::vector<INGAME_SPECIAL_ABILITY_DETAIL>& skills, rn::blob& clientinfo)
{
	DBG_OUTPUT(123, "%s - player : %d", __FUNCTION__, user_index);

	if(detail != GAMELOGIC::eRoom_INGAME_SPECIAL_ABILITY_ACQUIRE_ACK_OK)
	{
		DBG_OUTPUT(123, "%s Filed (%d)", __FUNCTION__, detail);

#ifndef TR_RELEASE_PROJECT
		CTRShortTimeMessage::showMessage(format("%s - %d", __FUNCTION__, detail));
#endif
		return;
	}

	std::vector<byte> cinfo;
	clientinfo.pop_fast(cinfo);

	void* client_info = NULL;
	size_t client_info_size = 0;
	if(cinfo.empty() == false)
	{
		client_info = &cinfo[0];
		client_info_size = cinfo.size();
	}

	CGameManager::getInstance().onRecvInGameSpecialAbilityAcquire(user_index, skill_group, groupType, skill_group_name, skills);
}

void CTRNetEventHandler::OnInGameSpecialAbilityFire(int group, const INGAME_SPECIAL_ABILITY_DETAIL& skill, int user_index, GAMELOGIC::eRoom_INGAME_SPECIAL_ABILITY_FIRE_ACK_DETAIL detail, rn::blob& clientinfo)
{
	DBG_OUTPUT(123, "%s - player : %d", __FUNCTION__, user_index);

	if(detail != GAMELOGIC::eRoom_INGAME_SPECIAL_ABILITY_FIRE_ACK_OK)
	{
		DBG_OUTPUT(123, "%s Filed (%d)", __FUNCTION__, detail);

#ifndef TR_RELEASE_PROJECT
		CTRShortTimeMessage::showMessage(format("%s - %d", __FUNCTION__, detail));
#endif
		return;
	}

	int iRandomGameOverPlayer = -1;
	if (skill.skill_type == eINGAME_SPECIAL_ABILITY_TYPE_RANDOM_GAME_OVER)
	{
		clientinfo.pop(iRandomGameOverPlayer);
	}

	std::vector<byte> cinfo;
	clientinfo.pop_fast(cinfo);

	void* client_info = NULL;
	size_t client_info_size = 0;
	if(cinfo.empty() == false)
	{
		client_info = &cinfo[0];
		client_info_size = cinfo.size();
	}
	else
	{
		if (skill.skill_type == eINGAME_SPECIAL_ABILITY_TYPE_RANDOM_GAME_OVER)
		{
			client_info_size = (size_t)iRandomGameOverPlayer;
		}
	}

	CGameManager::getInstance().onRecvInGameSpecialAbilityFire(user_index, group, skill, client_info, client_info_size);
}

void CTRNetEventHandler::OnInGameSpecialAbilityRemove(int skill_group, int user_index, GAMELOGIC::eRoom_INGAME_SPECIAL_ABILITY_REMOVE_ACK_DETAIL detail)
{
	DBG_OUTPUT(123, "%s - player : %d", __FUNCTION__, user_index);

	if(detail != GAMELOGIC::eRoom_INGAME_SPECIAL_ABILITY_REMOVE_ACK_OK)
	{
		DBG_OUTPUT(123, "%s Filed (%d)", __FUNCTION__, detail);

#ifndef TR_RELEASE_PROJECT
		CTRShortTimeMessage::showMessage(format("%s - %d", __FUNCTION__, detail));
#endif
		return;
	}

	CGameManager::getInstance().onRecvInGameSpecialAbilityRemove(user_index, skill_group);
}

void CTRNetEventHandler::OnTypingRunQuestionAck(int index, int type, const std::string & question, GAMELOGIC::eQUESTION_ACK ack)
{
	CGameManager::getInstance().onRecvTypingRunQuestion(index, type, question);
}

void CTRNetEventHandler::OnTypingRunTypingDoneAck(int index, int rank, int total_user, int msec)
{
	CGameManager::getInstance().onRecvTypingDone(index, rank, total_user, msec);
}

void CTRNetEventHandler::OnTypingRunGoblinRacingQuestionAck(int index, const std::vector<GAMELOGIC::eGOBLIN_RACE_NOTE>& question, GAMELOGIC::eGOBLIN_RACE_QUESTION_ACK ack)
{
	if(ack == GAMELOGIC::eGOBLIN_RACE_QUESTION_ACK_ACK_OK)
		CGameManager::getInstance().onRecvTypingRunGoblinRacingQuestion(index, question);
}

void CTRNetEventHandler::OnTypingRunGoblinRacingTypingDoneAck(int index, int rank, int total_user, int point, int msec)
{
	CGameManager::getInstance().onRecvTypingGoblinRacingTypingDone(index, rank, total_user, point, msec);
}

void CTRNetEventHandler::OnIceFlowerQuestionAck(int index, const std::vector<GAMELOGIC::TIMING_MENT>& ment, float end_timing, bool gameover, GAMELOGIC::eICEFLOWER_QUESTION_ACK ack)
{
	if (CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_ICE_FLOWER))
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CTimingMentNotify(index, ment, end_timing, gameover));
	}
}

void CTRNetEventHandler::OnGameRoundInformationNotify(std::vector<GAMELOGIC::GAME_ROUND>& round_info)
{
	DBG_OUTPUT(225, "OnGameRoundInformationNotify");
	CGameManager::getInstance().getInGameMode()->notifyDataValue("OnGameRoundInformationNotify", (void*)&round_info);
}

void CTRNetEventHandler::OnGameRoundStartAck(GAMELOGIC::eROUND_START_ACK ack, int playtime_msec, int round, time_type server_now)
{
	DBG_OUTPUT(225, "OnGameRoundStartAck ack(%d) playtime_msec(%d) round(%d) server_now(%d)", ack, playtime_msec, round, server_now);
	CGameManager::getInstance().getInGameMode()->notifyDataValue("OnGameRoundStartAck", (void*)&ack, (void*)&playtime_msec, (void*)&round, (void*)&server_now);
}

void CTRNetEventHandler::OnGameRoundEndNotify(int round, int alive_report_msec, int rest_msec)
{
	DBG_OUTPUT(225, "OnGameRoundEndNotify round(%d) alive_report_msec(%d) rest_msec(%d)", round, alive_report_msec, rest_msec);
	CGameManager::getInstance().getInGameMode()->notifyDataValue("OnGameRoundEndNotify", (void*)&round, (void*)&alive_report_msec, (void*)&rest_msec);
}

void CTRNetEventHandler::OnGameRoundAliveAck(GAMELOGIC::eROUND_ALIVE_ACK ack, int round)
{
	DBG_OUTPUT(225, "OnGameRoundAliveAck ack(%d) round(%d)", ack, round);
	CGameManager::getInstance().getInGameMode()->notifyDataValue("OnGameRoundAliveAck", (void*)&ack, (void*)&round);
}

void CTRNetEventHandler::OnGameRoundStatus(int round, int(&team_point)[eTeam_MAX], int(&delta_team_point)[eTeam_MAX], GAMELOGIC::ROUND_STATUS& myinfo)
{
	try {
		DBG_OUTPUT(225, "OnGameRoundStatus total_value size(%d) round_value size(%d) ----------------------", myinfo.total_value.size(), myinfo.round_value.size());
		DBG_OUTPUT(225, "team point red(%d) blue(%d)", team_point[eTeam_RED], team_point[eTeam_BLUE]);
		DBG_OUTPUT(225, "delta team point red(%d) blue(%d)", delta_team_point[eTeam_RED], delta_team_point[eTeam_BLUE]);
		DBG_OUTPUT(225, "round status total_exp(%d) total_tr(%d) total_competition(%d)", myinfo.total_exp(), myinfo.total_tr(), myinfo.total_competition());
		for (int i = 0; i < round; ++i) {
			DBG_OUTPUT(225, "round status round_exp(%d) round_tr(%d) round_competition(%d)", myinfo.round_exp(round), myinfo.round_tr(round), myinfo.round_competition(round));
		}
		DBG_OUTPUT(225, "OnGameRoundStatus ---------------------------------------------------");
	}
	catch (std::exception& e) {}
	CGameManager::getInstance().getInGameMode()->notifyDataValue("OnGameRoundStatus", (void*)&round, (void*)&team_point, (void*)&delta_team_point, (void*)&myinfo);
}

void CTRNetEventHandler::OnGameRoundStartEnabledNotify(int round, int playtime_msec)
{
	DBG_OUTPUT(225, "OnGameRoundAliveAck round(%d) playtime_msec(%d)", round, playtime_msec);
	CGameManager::getInstance().getInGameMode()->notifyDataValue("OnGameRoundStartEnabledNotify", (void*)&round, (void*)&playtime_msec);
}

void CTRNetEventHandler::OnUserSelection(int seq, const std::vector<int>& users)
{
	if (CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_RANDOM_GAMEOVER_BOMB))
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CSelectBombUserList(seq, users));
	}
}

void CTRNetEventHandler::OnUserRankNotifyEnabled(eRACE_RANK_NOTIFY_METHOD method)
{
	DBG_OUTPUT("%s - %d", __FUNCTION__, (int)method);
	CGameManager::getInstance().setRaceRankNoitify(method);
}

void CTRNetEventHandler::OnBombCountingStartAck(GAMELOGIC::eRoom_BOMB_COUTING_START_ACK_RESULT result)
{
	if (CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_RANDOM_GAMEOVER_BOMB))
	{
		CGameManager::getInstance().getInGameMode()->notifyIntValue("StartBomb", result);
	}
}

void CTRNetEventHandler::OnBombRaceTransferBombAck(int from_user, int to_user, int left_time, GAMELOGIC::eRoom_BOMB_RACE_TRANSFER_BOMB_ACK_RESULT result)
{
	//from_user == -1  : first bomb
	//left time = msec
	if (CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_RANDOM_GAMEOVER_BOMB))
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CTransferBomb(from_user, to_user, left_time, result));
	}
}

void CTRNetEventHandler::OnBombRaceExpldingNotify(int user, int left_bomb_count)
{
	if (CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_RANDOM_GAMEOVER_BOMB))
	{
		CGameManager::getInstance().getInGameMode()->notifyDataValue("ExpldingNotify", &user, &left_bomb_count);
	}
}

void CTRNetEventHandler::OnRabbitTurtleMakeTeam(const std::vector<std::vector<unsigned int/*gameindex*/>>& team, const std::map<unsigned int, RABBIT_TURTLE::eCharacter>& idx2char)
{
	if(CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_HARE_AND_TORTOISE))
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CHareAndTortoiseMakeTeamNotify(team, idx2char));
	}
}

void CTRNetEventHandler::OnRabbitTurtleStatus(const RABBIT_TURTLE::RABBIT_TURTLE_INFO& info)
{
	if(CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_HARE_AND_TORTOISE))
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CHareAndTortoiseTeamStatusNotify(info));
	}
}

void CTRNetEventHandler::OnRabbitTurtleTagAck(RABBIT_TURTLE::eTAG_CHANGE_RESULT r, int remain_sec)
{
	if(CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_HARE_AND_TORTOISE))
	{
		int value = (int)r << 8 | remain_sec;
		CGameManager::getInstance().getInGameMode()->notifyIntValue("TagAck", value);
	}
}

void CTRNetEventHandler::OnRabbitTurtleChangeLeader(unsigned int gameindex)
{
	if(CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_HARE_AND_TORTOISE))
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CHareAndTortoiseLeaderChange(gameindex));
	}
} 

void CTRNetEventHandler::OnRabbitTurtleChangeQueryed(unsigned int requester_gameindex)
{
	if(CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_HARE_AND_TORTOISE))
	{
		CGameManager::getInstance().getInGameMode()->notifyIntValue("RequestChange", requester_gameindex);
	}
}

void CTRNetEventHandler::OnRabbitTurtleChangeAnswer(bool do_change, unsigned int requester_gameindex)
{
	if(CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_HARE_AND_TORTOISE))
	{
		CGameManager::getInstance().getInGameMode()->notifyIntValue("RequestChangeAnswer", requester_gameindex);
	}
}

#ifdef _PLAYGROUND_
void CTRNetEventHandler::OnMultiMiniGame_UpdateResult(BYTE game_index, int total_point)
{
	CGameManager::getInstance().OnMultiMiniGame_UpdateResult(game_index,total_point);
}

void CTRNetEventHandler::OnMultiMiniGame_PointNotification(const MULTIMINIGAME::MINIGAME_POINT& points)
{
	CGameManager::getInstance().OnMultiMiniGame_PointNotification(points);
}
#endif



void CTRNetEventHandler::OnRoundInfoAck(const GAMELOGIC::CGameRoundInfo_set_ack & result)
{
	CGameManager::getInstance().onGameRoundInfoACK(result.round(),result.state_event(),result.result());
}

void CTRNetEventHandler::OnRoundInfoNotify(const GAMELOGIC::CGameRoundInfo_set_notify & result)
{
	CGameManager::getInstance().onGameRoundInfoNotiy(result.round(),result.state_event(),result.expired_time());
}

void CTRNetEventHandler::OnHammderMode_CaculationAck(HAMMERMODE::CHammerMode_CalculatePointAck::RESULT r, int iRedPoint, int iBluePoint, unsigned int iGameIndex)
{
	CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CRecvTeamPoint(iRedPoint, iBluePoint, iGameIndex));
}

void CTRNetEventHandler::onRecvNumberForPreventAbusing(BYTE iNum)
{
	DBG_OUTPUT(125, "%s - %d", __FUNCTION__, iNum);
	if(m_pNetPlay != NULL)
	{
		m_pNetPlay->onRecvNumberForPreventAbusing(iNum);
	}
}

void CTRNetEventHandler::onRecvConfirmNumberForPreventAbusing_OK()
{
	DBG_OUTPUT(125, "%s", __FUNCTION__);
	if(m_pNetPlay != NULL)
	{
		m_pNetPlay->onRecvConfirmNumberForPreventAbusing_OK();
	}
}

void CTRNetEventHandler::onRecvConfirmNumberForPreventAbusing_Fail(int iNum, int iErrCnt)
{
	DBG_OUTPUT(125, "%s - ErrCnt: %d", __FUNCTION__,iErrCnt);
	if(m_pNetPlay != NULL)
	{
		m_pNetPlay->onRecvConfirmNumberForPreventAbusing_Fail(iNum, iErrCnt);
	}
}

#ifdef _CHALLENGE_MODE
void CTRNetEventHandler::OnRecvSetRoomMedal(int mapnum)
{
	CTRUserInterface::getInstance().changeMedalICon(mapnum);
}

void CTRNetEventHandler::OnRecvGetUserInfoAck_ChallengeFullRecord(const std::string& target_nick, const CHALLENGEMODE::MAP2MEDAL& fullrecord, bool bFailed)
{
	if (bFailed)
	{
		CTRShortTimeMessage::showMessage(_STR(FAILED_GUILD_INVALID_USER), 1.5f);
		return;
	}

	const std::string& myNickName = CNetClientManager::getInstance().getMyNickname();
	if (target_nick == myNickName)
	{
		CHALLENGEMODE::CTRSingleChallengeManager::getInstance().OnRecvGetUserInfoAck_ChallengeFullRecord(target_nick, fullrecord);
		CTRLobbyUI::getInstance().OnRecvGetUserInfoAck_ChallengeFullRecord(target_nick, fullrecord);
	}

	if (CTRUserBookDlg::getInstance().isVisible())
	{
		CTRUserBookDlg::getInstance().OnRecvGetUserInfoAck_ChallengeFullRecord(target_nick, fullrecord);
	}
}

void CTRNetEventHandler::OnRecvChallengeMapStartAck(CHALLENGEMODE::eRACE_START_RESULT result)
{
	switch (result)
	{
	case CHALLENGEMODE::eRACE_S_SUCCESS:
		if(CGameManager::getInstance().isGameModeChallenge())
		{
			m_pNetPlay->startGame();
			CNetClientManager::getInstance().requestCurrentTR();
			break;
		}
	case CHALLENGEMODE::eRACE_S_NOT_ENOUGH_COST:
	case CHALLENGEMODE::eRACE_S_SERVER_ERROR:
	case CHALLENGEMODE::eRACE_S_UNKNOWN_ERROR__PREVIOUS_RACE_IS_NOT_OVER:
#ifdef __GHOST_RECORD__
	case CHALLENGEMODE::eRACE_S_INVALID_GHOST_DATA:
#endif
		{
			CHALLENGEMODE::CTRSingleChallengeGameUI::getInstance().doExitGame();
		}
		break;
	default:
		{
			DBG_OUTPUT("CTRNetEventHandler::onRecvChallengeMapStartFailed... (%d)", result);
			CCommandManager::getInstance().postWindowCloseMessage();
			_ASSERTE(false);
		}
		break;
	}
}	

void CTRNetEventHandler::OnRecvChallengeMapEndAck(CHALLENGEMODE::eRACE_END_RESULT result, const CHALLENGEMODE::CMedalInfo& best_info, const CHALLENGEMODE::CMedalInfo& current_info, int map_num)
{
	DBG_OUTPUT("CTRNetEventHandler::OnRecvChallengeMapEndAck result(%d) map_num(%d) best_info type(%d) m_record(%d)", result, map_num, best_info.type(), best_info.record());

	switch (result)
	{
	case CHALLENGEMODE::eRACE_E_SUCCESS:
	case CHALLENGEMODE::eRACE_E_CLIENT_ABORT:
	case CHALLENGEMODE::eRACE_E_CLIENT_RETRY:
	case CHALLENGEMODE::eRACE_E_FAIL:
		CHALLENGEMODE::CTRSingleChallengeGameUI::getInstance().OnRecvChallengeMapEndAck(result, best_info, current_info, map_num);
		break;
	default:
		CHALLENGEMODE::CTRSingleChallengeGameUI::getInstance().doExitGame();
	}
}

void CTRNetEventHandler::OnRecvChallengeMapSummary(const std::map<int, CHALLENGEMODE::SUCCESS_RATIO>& summary)
{
	CHALLENGEMODE::CTRSingleChallengeManager::getInstance().OnRecvChallengeMapSummary(summary);
	CTRLobbyUI::getInstance().OnRecvChallengeMapSummary(summary);
}

#endif

#ifdef _ENCHANT_SYSTEM_

void CTRNetEventHandler::onRecvEnchantSystemGetMyItem(eENCHANT_SYSTEM_RESULT eResult)
{
	DBG_DEMO_OUTPUT(123, "%s", __FUNCTION__);
}

void CTRNetEventHandler::onRecvEnchantSystemMount(eENCHANT_SYSTEM_RESULT eResult, int iItemNum, BYTE iNewSeqNum)
{
	DBG_DEMO_OUTPUT(123, "%s - %d", __FUNCTION__, eResult);

	if(eResult == eENCHANT_SYSTEM_RESULT_OK)	
	{
		ItemDetailView::CTRItemDetailViewManager::getInstance().notifyRefreshItem();

		//!< 부여된 능력치를 결과로 표시해준다.
		UserEnchantItem enchantItem;
		if(CNetClientManager::getInstance().getUserItemEnchantInfo(iItemNum, enchantItem))
		{
			std::map<eItemAttr, float> mapAttr;
			if(enchantItem.getStoneAttr(iNewSeqNum, mapAttr))
			{
				short iAttr;
				float fValue;

				std::map<eItemAttr, float>::iterator itor = mapAttr.begin();
				for(; itor != mapAttr.end(); ++itor)
				{
					if(itor->first != eItemAttr_ENCHANT_SYSTEM_Stone_Accumulate_Point)
					{
						iAttr = itor->first;
						fValue = itor->second;
						break;
					}
				}

				std::string strAttr;
				CTRItemDescWindow::getInstance().getAttrText(iAttr, fValue, strAttr);
				COkDialogEx::getInstance().showDialog(format(_STR(ITEM_ENCHANT_MOUNT_OK), strAttr.c_str()), "myroom/ItemDetailView/ItemDetailView_Ok.gui", -2.1f, false);
			}

			int iStoneItemNum;
			if(enchantItem.getMountStoneNum(iNewSeqNum, iStoneItemNum))
			{
				CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iStoneItemNum);
			}
		}

		onRecvCurrentGameMoney(CNetClientManager::getInstance().getGameMoney());
		onRecvShopCash(CNetClientManager::getInstance().getCashMoney());
	}
	else
	{
		ItemDetailView::CTRItemDetailViewManager::getInstance().showEnchantSystemResult(eResult);
	}
}

void CTRNetEventHandler::onRecvEnchantSystemMove(eENCHANT_SYSTEM_RESULT eResult, int iHammerNum, int iNewItemNum, BYTE iNewSeqNum)
{
	DBG_DEMO_OUTPUT(123, "%s - %d %d", __FUNCTION__, eResult, iHammerNum);

	if(eResult == eENCHANT_SYSTEM_RESULT_OK)
	{
		ItemDetailView::CTRItemDetailViewManager::getInstance().notifyRefreshItem();

		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iHammerNum);

		std::string strMent;

		//!< 적용된 아이템과 적용 능력치를 보여준다.
		const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(iNewItemNum);
		if(pItem != NULL)
		{
			UserEnchantItem enchantItem;
			if(CNetClientManager::getInstance().getUserItemEnchantInfo(iNewItemNum, enchantItem))
			{
				std::map<eItemAttr, float> mapAttr;
				if(enchantItem.getStoneAttr(iNewSeqNum, mapAttr))
				{
					short iAttr;
					float fValue;

					std::map<eItemAttr, float>::iterator itor = mapAttr.begin();
					for(; itor != mapAttr.end(); ++itor)
					{
						if(itor->first != eItemAttr_ENCHANT_SYSTEM_Stone_Accumulate_Point)
						{
							iAttr = itor->first;
							fValue = itor->second;
							break;
						}
					}

					std::string strAttr;
					if(CTRItemDescWindow::getInstance().getAttrText(iAttr, fValue, strAttr))
					{
						strMent = format(_STR(ITEM_ENCHANT_MOVE_OK), pItem->m_name.c_str(), strAttr.c_str());
					}
				}
			}
		}

		if(!strMent.empty())
		{
			COkDialogEx::getInstance().showDialog(strMent, "myroom/ItemDetailView/ItemDetailView_Ok.gui", -2.1f, false);
		}		
	}
	else
	{
		ItemDetailView::CTRItemDetailViewManager::getInstance().showEnchantSystemResult(eResult);
	}
}

void CTRNetEventHandler::onRecvEnchantSystemRemove(eENCHANT_SYSTEM_RESULT eResult, bool bSuccess, int iStoneNum, int iHammerNum)
{
	DBG_DEMO_OUTPUT(123, "%s - %d %s %d %d", __FUNCTION__, eResult, bSuccess ? "T" : "F", iStoneNum, iHammerNum);

	if(eResult == eENCHANT_SYSTEM_RESULT_OK)
	{
		ItemDetailView::CTRItemDetailViewManager::getInstance().notifyRefreshItem();

		std::vector<int> itemList;
		itemList.push_back(iHammerNum);
		itemList.push_back(iStoneNum);
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNumList(itemList);

		const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(iStoneNum);
		if(pItem != NULL)
		{
			std::string strMent;
			if(bSuccess)
			{
				strMent = format(_STR(ITEM_ENCHANT_REMOVE_OK_SUCCESS), pItem->m_name.c_str());
			}
			else
			{
				strMent = format(_STR(ITEM_ENCHANT_REMOVE_OK_FAILED), pItem->m_name.c_str());
			}

			COkDialogEx::getInstance().showDialog(strMent, "myroom/ItemDetailView/ItemDetailView_Ok.gui", -2.1f, false);
		}
	}
	else
	{
		ItemDetailView::CTRItemDetailViewManager::getInstance().showEnchantSystemResult(eResult);
	}
}

void CTRNetEventHandler::onRecvEnchantSystemRemoveSeal(eENCHANT_SYSTEM_RESULT eResult, int iHammerNum)
{
	DBG_DEMO_OUTPUT(123, "%s - %d %d", __FUNCTION__, eResult, iHammerNum);

	if(eResult == eENCHANT_SYSTEM_RESULT_OK)
	{
		ItemDetailView::CTRItemDetailViewManager::getInstance().notifyRefreshItem();

		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iHammerNum);

		COkDialogEx::getInstance().showDialog(_STR(ITEM_ENCHANT_REMOVE_SEAL_OK), "myroom/ItemDetailView/ItemDetailView_Ok.gui", -2.1f, false);
	}
	else
	{
		ItemDetailView::CTRItemDetailViewManager::getInstance().showEnchantSystemResult(eResult);
	}
}

void CTRNetEventHandler::onRecvEnchantSystemStoneHardening(eENCHANT_SYSTEM_RESULT eResult, int iMaterialStoneNum, int iNewStoneNum)
{
	DBG_DEMO_OUTPUT(123, "%s - %d %d %d", __FUNCTION__, eResult, iMaterialStoneNum, iNewStoneNum);

	if(eResult == eENCHANT_SYSTEM_RESULT_OK)
	{
		std::vector<int> itemList;
		if(iMaterialStoneNum != 0) itemList.push_back(iMaterialStoneNum);
		if(iNewStoneNum != 0) itemList.push_back(iNewStoneNum);

		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNumList(itemList);

		CTRMyRoomGoodsListDialog::getInstance().onRecvEnchantSystemStoneHardening(iMaterialStoneNum, iNewStoneNum);

		onRecvCurrentGameMoney(CNetClientManager::getInstance().getGameMoney());
		onRecvShopCash(CNetClientManager::getInstance().getCashMoney());
	}
	else
	{
		ItemDetailView::CTRItemDetailViewManager::getInstance().showEnchantSystemResult(eResult);
	}
}

#endif //_ENCHANT_SYSTEM_

void CTRNetEventHandler::onRecvComeBackRewardUser(bool bNeedReward)
{
	m_pNetPlay->setNeedComeBackUserReward(bNeedReward);
}

void CTRNetEventHandler::onRecvRepairAllMyItemForComeBack(eServerResult result)
{
	DBG_OUTPUT(123, "%s - %d", __FUNCTION__, result);
	CKeepItemList::getInstance().setAllCharacterUpdate(false);
	CKeepItemList::getInstance().setAllPeriodCharacterUpdate(false);
}

void CTRNetEventHandler::onRecvRoomKindEntryCondition()
{
#ifdef _DUNGEON_RAID_CHANNEL
	CTRSubDialogManager* pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager != NULL)
	{
		CTRDungeonRaidDlg* pRaidUI = pSubDialogManager->getSubDialogPtr<CTRDungeonRaidDlg>(SUB_PTR_DIALOG_TYPE_DUNGEON_ASSAULT_RAID);
		if(pRaidUI != NULL && pRaidUI->isVisible())
			pRaidUI->updateEntranceInfo(CNetClientManager::getInstance().getChannelEntryCondition());
	}
#endif
}

#ifdef _BONUS_STAGE_
void CTRNetEventHandler::onRecvBonusStageRewardInfoList(const std::map<int, BonusStageRewardInfo>& mapRewardInfo)
{
	CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CBonusStageRewardInfoList(mapRewardInfo));
}

void CTRNetEventHandler::onRecvBonusStageRankInfoList(const std::map<int, std::string>& mapRankInfo)
{
	CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CBonusStageRankInfoList(mapRankInfo));
}

void CTRNetEventHandler::onRecvBonusStageLastChancePoint(const int iChancePoint)
{
	CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CBonusStageLastChancePoint(iChancePoint));
}

#endif

#ifdef _NUMBERS
void CTRNetEventHandler::OnNumbersRankUpdated(int current_rank, int prev_rank)
{
	//rank == eNUMBERS_OUTOF_RANK : 100드이 이상
	CTRNetPlayManager::getInstance().setNumbersInfo(current_rank, prev_rank);

	switch(CTRUserInterface::getInstance().getCurrentUIType())
	{
		case GUI_TYPE_LOBBY:
			CTRLobbyUI::getInstance().checkNumbersAlarm();
			break;
		case GUI_TYPE_FARM:
			CTRFarmUI::getInstance().checkNumbersAlarm();
			break;
		case GUI_TYPE_PARK:
			CTRGameParkUI::getInstance().checkNumbersAlarm();
			break;
		case GUI_TYPE_GUILD_FARM:
			CTRGuildFarmUI::getInstance().checkNumbersAlarm();
			break;
	}
}
#endif

void CTRNetEventHandler::OnRecvAvatarLockLoad(AvatarLock avatarLock)
{
	CTRNetPlayManager::getInstance().avatarLockLoaded();
	CTRMyroomDlg::getInstance().onRecvAvatarLockLoadAck(avatarLock);
}

#ifdef __NEW_AVATAR_LOCK__
void CTRNetEventHandler::OnRecvAvatarLockSave(AvatarLock avatarLock, const std::vector<int>& lookItems)
{
	DBG_OUTPUT("%s", __FUNCTION__);
	CTRMyroomDlg::getInstance().onRecvAvatarLockSaveAck(avatarLock, lookItems);
}
#else
void CTRNetEventHandler::OnRecvAvatarLockSave(AvatarLock avatarLock)
{
	DBG_OUTPUT("%s", __FUNCTION__);
	CTRMyroomDlg::getInstance().onRecvAvatarLockSaveAck(avatarLock);
}
#endif

void CTRNetEventHandler::OnRecvGuildBuffApplyGuildList(std::vector<int>& guildBufApplyGuildList)
{
	CTRUserInterface::getInstance().onRecvGuildBuffApplyGuildList(guildBufApplyGuildList);
}

void CTRNetEventHandler::onRecvOpenPortalResponse(std::map<eTeam, bool>& PortalData)
{
	CGameManager::getInstance().onRecvPortalActivate(PortalData);
}

void CTRNetEventHandler::onRecvEnterPortalResponse(const size_t iPlayerIndex, const int iMoveIndex)
{
	CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CGameApplyEventDeath(iPlayerIndex, iMoveIndex));
}

#ifdef _ITEM_TRADE
void CTRNetEventHandler::OnItemTrade_Check(ITEM_TRADE::CCheckTradeAck* packet) const
{
	map<int, ItemDetailView::stTradeTicketInfo> mapTicketInfo;
	vector<ItemDetailView::stTradeTicketInfo> vecTicketInfo;
	set<int> setTicketItemNum;
	if(packet->result() == ITEM_TRADE::eTRADE_CHECK_OK || packet->result() == ITEM_TRADE::eTRADE_CHECK_NOT_ENOUGH_STORAGE)
	{
		std::vector<ITEM_TRADE::CTradeInfo> vecTradeInfo = packet->trade_info();
		std::map<int/*ticket*/, int/*count*/> mapTicketCount = packet->ticket_count();

		for(size_t i = 0; i < vecTradeInfo.size(); i++)
		{
			ITEM_TRADE::CTradeInfo info = vecTradeInfo.at(i);
			ItemDetailView::stTradeTicketInfo ticketInfo;

			ticketInfo.m_iTicketItemNum = info.ticket();
			ticketInfo.m_iResultCount = info.result_count();
			ticketInfo.m_mapPosition2ratio = info.position2ratio();

			std::map<int/*ticket*/, int/*count*/>::iterator itr = mapTicketCount.find(info.ticket());
			if(itr != mapTicketCount.end())
				ticketInfo.m_iKeepCount = itr->second;
			else
				ticketInfo.m_iKeepCount = 0;

			//vecTicketInfo.push_back(ticketInfo);
			mapTicketInfo.insert(make_pair(ticketInfo.m_iTicketItemNum, ticketInfo));
		}
	}

	map<int, ItemDetailView::stTradeTicketInfo>::iterator itr = mapTicketInfo.begin();
	for(;itr != mapTicketInfo.end(); itr++)
	{
		vecTicketInfo.push_back(itr->second);
	}

	ItemDetailView::CTRItemDetailViewManager::getInstance().onRecvTradingTicketInfo(packet->result(), vecTicketInfo);
}

void CTRNetEventHandler::OnItemTrade_Trade(ITEM_TRADE::CTradeAck* packet) const
{
	std::map<int,bool> mapTradeItemInfo;
	if(packet->result() == ITEM_TRADE::eTRADE_RESULT_OK)
	{
		std::vector<ITEM_TRADE::TRADE_RESULT> vecTarget_item = packet->target_item();
		for(size_t i = 0; i < vecTarget_item.size(); i++)
		{
			ITEM_TRADE::TRADE_RESULT tradeResult = vecTarget_item.at(i);
			mapTradeItemInfo.insert(make_pair(tradeResult.item, tradeResult.can_move_to_storage));
		}
	}

	ItemDetailView::CTRItemDetailViewManager::getInstance().onRecvTradingItemList(packet->result(), mapTradeItemInfo);
}

void CTRNetEventHandler::OnItemTrade_ResultAction(ITEM_TRADE::CTradeResultActionAck* packet) const
{
	ItemDetailView::CTRItemDetailViewManager::getInstance().onRecvTradingRewardItem(packet->result(), packet->target_item(), packet->source_item(), packet->ticket());
}
#endif

#ifdef _ITEM_CUBE

void CTRNetEventHandler::OnRecvItemCube_check(int cube, int count, int gold_guage, int gold_guage_max, ITEM_CUBE::eCUBE_INFO_RESULT r)
{
	if ( ITEM_CUBE::eCUBE_INFO_RESULT_OK == r )
	{
		ITEM_CUBE::CTRItemCubeDialog::getInstance().onRecvCubeCheck( cube, count, gold_guage, gold_guage_max );
	}
	else
	{
		ITEM_CUBE::CTRItemCubeDialog::getInstance().onRecvCubeCheckFailed( r );
	}
}

void CTRNetEventHandler::OnRecvItemCube_open(int cube, ITEM_CUBE::eCUBE_TYPE cube_type, ITEM_CUBE::eCUBE_OPEN_RESULT r, const std::vector<ITEM_CUBE::ITEM_OPEN_INFO>& open_result, const std::vector<ITEM_CUBE::ITEM_UNOPEN_INFO>& unopen_result, int max_acceptable)
{
	if ( ITEM_CUBE::eCUBE_OPEN_RESULT_OK == r )
	{
		ITEM_CUBE::CTRItemCubeDialog::getInstance().onRecvCubeOpen( cube, cube_type, open_result, unopen_result, max_acceptable );
	}
	else
	{
		ITEM_CUBE::CTRItemCubeDialog::getInstance().onRecvCubeOpenFailed( r );
	}
}

void CTRNetEventHandler::OnRecvItemCube_accept(int cube, ITEM_CUBE::eCUBE_ACCEPT_RESULT result)
{
	if ( ITEM_CUBE::eCUBE_ACCEPT_RESULT_OK == result )
	{
		ITEM_CUBE::CTRItemCubeDialog::getInstance().onRecvCubeAccept( cube );
	}
	else
	{
		ITEM_CUBE::CTRItemCubeDialog::getInstance().onRecvCubeAcceptFailed( result );
	}
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 길드 매치 점령전
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTRNetEventHandler::onRecvGuildMatchArea_Point_Info( int iOneDayJoinCount, std::map<eOCCUPATION_AREA_TYPE, int>& mapGuildMatchAreaInfo )
{
	m_pNetPlay->getGuildMatchManager()->onRecvGuildMatchArea_Point_Info( iOneDayJoinCount, mapGuildMatchAreaInfo );

	if ( m_pGameRoomUI && m_pNetPlay && isGuildMatchPartyRoom( m_pNetPlay->getGameRoomKind() ))
	{
		if ( GUI_TYPE_GUILD_MATCH_PARTYROOM == m_pGameRoomUI->getUIType() )
		{
			dynamic_cast< CGuildMatchRecvInterface* >( m_pGameRoomUI )->onRecvGuildMatchArea_Point_Info();
		}
	}

	if ( CTRLobbyUI::getInstance().isActive() )
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchArea_Point_Info();
	}
}

void CTRNetEventHandler::onRecvGuildMatchArea_Point_Info_Failed( GuildMatchRequestInfo& requestInfo )
{

}

void CTRNetEventHandler::onRecvGuildMatchOccupation_Area_Rank_Info( bool bRequestByGuild, std::map<eOCCUPATION_AREA_TYPE, std::map<int, GuildMatchOccupationRank_Info>>& list )
{
	if ( CTRLobbyUI::getInstance().isActive() )
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchOccupation_Area_Rank_Info( bRequestByGuild, list );
	}
}

void CTRNetEventHandler::onRecvGuildMatchOccupation_Area_Rank_Info_Failed( GuildMatchRequestInfo& requestInfo )
{
	if ( CTRLobbyUI::getInstance().isActive() )
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchOccupation_Area_Rank_Info_Failed( requestInfo );
	}
}

void CTRNetEventHandler::onRecvGuildMatchOccupation_Rank_Range( std::map<int, GuildMatchOccupationRank_Info>& list, const eGUILDMATCH_OCCUPATION_RANK_SEARCH_TYPE eSearchType )
{
	if ( CTRLobbyUI::getInstance().isActive() )
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchOccupation_Rank_Range( list, eSearchType );
	}
}

void CTRNetEventHandler::onRecvGuildMatchOccupation_Rank_Range_Failed( GuildMatchRequestInfo& requestInfo )
{
	if ( CTRLobbyUI::getInstance().isActive() )
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchOccupation_Rank_Range_Failed( requestInfo );
	}
}

void CTRNetEventHandler::onRecvGuildMatchOccupation_OpenSchedule()
{
	if ( CTRLobbyUI::getInstance().isActive() )
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchOccupation_OpenSchedule();
	}
}

void CTRNetEventHandler::onRecvGuildMatchOccupation_HotPlace_Info( std::map<eOCCUPATION_AREA_TYPE, std::map<byte/**rank**/, RewardInfo>>& list )
{
#ifdef _GUILDOCCUPATION_HOTPLACE
	CTRGameGuildMatchManager *pGuildMatchManager = CTRNetPlayManager::getInstance().getGuildMatchManager();
	if(pGuildMatchManager)
	{
		pGuildMatchManager->setHotplaceInfo(list);
	}

	if(CTRLobbyUI::getInstance().isActive())
	{
		CTRLobbyUI::getInstance().onRecvGuildMatchOccupation_HotPlace_Info();
	}
#endif
}

void CTRNetEventHandler::onRecvGuildMatchOccupation_HotPlace_Info_Failed( GuildMatchRequestInfo& requestInfo )
{

}


void CTRNetEventHandler::OnRecvTrainRun_team(const std::vector<int> (&team)[eTeam_MAX])
{
	DBG_OUTPUT("%s - red : %d, blue : %d, green : %d", __FUNCTION__, team[eTeam_RED].size(), team[eTeam_BLUE].size(), team[eTeam_GREEN].size());

#ifdef _TRAIN_RUN_
	if(CGameManager::getInstance().getInGameMode()->getProcessorType() == GAME_MODE_PROCESSOR_TRAIN_RUN)
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CTrainRunTeamNotify(team));
	}
#endif
}

void CTRNetEventHandler::OnRecvTrainRun_game_timer(GAMELOGIC::eTrainRunTimerID timer)
{
#ifdef _TRAIN_RUN_
	if(CGameManager::getInstance().getInGameMode()->getProcessorType() == GAME_MODE_PROCESSOR_TRAIN_RUN)
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CTrainRunOnTimer(timer));
	}
#endif
}

void CTRNetEventHandler::OnRecvTrainRun_KillLeaderAck(GAMELOGIC::eTRAINRUN_ACK ack)
{
#ifdef _TRAIN_RUN_
	if(CGameManager::getInstance().getInGameMode()->getProcessorType() == GAME_MODE_PROCESSOR_TRAIN_RUN)
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CTrainRunKillRiviveNotify(true, false, 0));
	}
#endif
}

void CTRNetEventHandler::OnRecvTrainRun_Suicide()
{
	CGameManager::getInstance().onPlayerGameOver();
}

void CTRNetEventHandler::OnRecvTrainRun_ReviveAck(GAMELOGIC::eTRAINRUN_ACK ack, int iUserCount)
{
#ifdef _TRAIN_RUN_
	if(CGameManager::getInstance().getInGameMode()->getProcessorType() == GAME_MODE_PROCESSOR_TRAIN_RUN)
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CTrainRunKillRiviveNotify(false, true, iUserCount));
	}
#endif
}

#ifdef _KNIGHT_FLOWERS_
void CTRNetEventHandler::OnRecvKnightFlowers_StartNotify(const StepEventScheduleInfo& ScheduleData)
{
	if(CTRLobbyUI::getInstance().isActive() && CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_KNIGHT_FLOWERS))`
	{
		CTRLobbyUI::getInstance().onRecvKnightFlowersSchedule(ScheduleData);
	}
	else if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvKnightFlowers_Schedule();
	}
	CNetClientManager::getInstance().requestKnightFlowers_TeamPoint();
	CNetClientManager::getInstance().requestKnightFlowers_CheckPointList();
	CTRSystemNotice::getInstance().showMessage(format(_STR(KNIGHT_FLOWERS_START_NOTIFY), (ScheduleData.m_StepNum - 1) % 6 + 1 ));
}

void CTRNetEventHandler::OnRecvKnightFlowers_EndNotify(StepEventScheduleInfo& ScheduleData, const bool is_empty)
{
	CTRSystemNotice::getInstance().showMessage(format(_STR(KNIGHT_FLOWERS_END_NOTIFY), (ScheduleData.m_StepNum - 2) % 6 + 1));
	CNetClientManager::getInstance().requestKnightFlowers_Schedule();
}

void CTRNetEventHandler::OnRecvKnightFlowers_Schedule(const StepEventScheduleInfo& ScheduleData)
{
	if(CTRLobbyUI::getInstance().isActive() && CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_KNIGHT_FLOWERS))
	{
		CTRLobbyUI::getInstance().onRecvKnightFlowersSchedule(ScheduleData);
	}
	else if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvKnightFlowers_Schedule();
	}
	CNetClientManager::getInstance().requestKnightFlowers_TeamPoint();
}

void CTRNetEventHandler::OnRecvKnightFlowers_CheckPointList(const std::vector<eEventPartyType>& checkPointlist)
{
	if(CTRLobbyUI::getInstance().isActive() && CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_KNIGHT_FLOWERS))
	{
		CTRLobbyUI::getInstance().onRecvKnightFlowersCheckPointList(checkPointlist);
	}
	else if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvKnightFlowers_CheckPointList(checkPointlist);
	}
	CNetClientManager::getInstance().requestKnightFlowers_TeamPoint();
}

void CTRNetEventHandler::OnRecvKnightFlowers_TeamPoint(const std::map<eEventPartyType, INT64>& TeamPointList)
{
	if(CTRLobbyUI::getInstance().isActive() && CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_KNIGHT_FLOWERS))
	{
		CTRLobbyUI::getInstance().onRecvKnightFlowersTeamPointList(TeamPointList);
	}
	else if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvKnightFlowers_TeamPoint();
	}
}

void CTRNetEventHandler::OnRecvKnightFlowers_WinList(const std::map<int, StepEventWinData>& WinList)
{
	if(CTRLobbyUI::getInstance().isActive() && CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_KNIGHT_FLOWERS))
	{
	}
}

void CTRNetEventHandler::OnRecvKnightFlowers_DrawCount(const int DrawCount, const int StepTotalDrawnCount, const int RewardItemNum, const bool bBoost, const bool bcanReceive)
{
	if(CTRLobbyUI::getInstance().isActive() && CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_KNIGHT_FLOWERS))
	{
	}
	else if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvKnightFlowers_DrawCount();
	}
}

void CTRNetEventHandler::OnRecvKnightFlowers_AddPoint(const eKnightofFlowers_Result eResult)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvKnightFlowers_AddPoint(eResult);
	}
}

void CTRNetEventHandler::OnRecvKnightFlowers_DrawReward(const eKnightofFlowers_Result eResult)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvKnightFlowers_DrawReward(eResult);
	}
}

void CTRNetEventHandler::OnRecvKnightFlowers_TeamReward(const eKnightofFlowers_Result eResult, const int RewardItemNum)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvKnightFlowers_TeamReward(eResult, RewardItemNum);
	}
}

void CTRNetEventHandler::OnRecvKnightFlowers_AccReward(const eKnightofFlowers_Result eResult, const int RewardItemNum)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvKnightFlowers_AccReward(eResult, RewardItemNum);
	}
}

#endif

void CTRNetEventHandler::onRecvIngameUserBonusInfo(eRewardCondition reward, int amount)
{
	std::vector<RewardInfo> vecRewardList;
	vecRewardList.push_back(RewardInfo(reward, 0, amount));
	CGameManager::getInstance().onRecvBonusExEat(0, vecRewardList);
}

#ifdef _VALENTINE_2018_
void CTRNetEventHandler::OnRecvValentineEvent_TalkInfo(int iCombineNum, int iNpcNum)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvValentineEvent_TalkInfo(iCombineNum, iNpcNum);
	}
}

void CTRNetEventHandler::OnRecvValentineEvent_TalkInfo_Failed()
{

}

void CTRNetEventHandler::OnRecvValentineEvent_SetTalkResult(int iNpcNum, int iGoodFeelling, int iItemNum)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvValentineEvent_SetTalkResult(iNpcNum, iGoodFeelling);
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(iItemNum);
	}
}

void CTRNetEventHandler::OnRecvValentineEvent_SetTalkResult_Failed()
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvValentineEvent_SetTalkResult_Failed();
	}
}

void CTRNetEventHandler::OnRecvValentineEvent_GetRewardInfo(const std::map<int, ValentineDay_Talk_RewardInfo>& rewardList)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvValentineEvent_GetRewardInfo(rewardList);
	}
}

void CTRNetEventHandler::OnRecvValentineEvent_GetRewardInfo_Failed()
{

}

void CTRNetEventHandler::OnRecvValentineEvent_GiveReward(const std::vector<RewardInfo>& rewardList)
{
	if(CTRGameParkUI::getInstance().isActive())
	{
		CTRGameParkUI::getInstance().onRecvValentineEvent_GiveReward(rewardList);
	}
}

void CTRNetEventHandler::OnRecvValentineEvent_GiveReward_Failed()
{

}

#endif

void CTRNetEventHandler::OnRecvSiegeMode_change_base_ack(const std::string& base_id, eTeam server_team, SIEGE::eCHANGE_BASE_ACK ack, int useridx, int deltapoint)
{
	if(server_team != eTeam_NONE)
	{
		if(CGameManager::getInstance().getInGameMode()->getProcessorType() == GAME_MODE_PROCESSOR_GUILD_ARENA)
		{
			CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CGuildArenaNPCPoint((BYTE)100, base_id, useridx, deltapoint));
		}
	}
}

void CTRNetEventHandler::OnRecvSiegeMode_point_inc_ack(SIEGE::ePOINT_REQ_ACK r, SIEGE::ePOINT_TYPE type, int useridx, int deltapoint)
{
	if(r == SIEGE::ePOINT_REQ_ACK_OK)
	{
		if(CGameManager::getInstance().getInGameMode()->getProcessorType() == GAME_MODE_PROCESSOR_GUILD_ARENA)
		{
			CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CGuildArenaNPCPoint(type, "", useridx, deltapoint));
		}
	}
}

void CTRNetEventHandler::OnRecvSiegeMode_teampoint_notify(const int (&team_point)[eTeam_MAX], const int (&delta_point)[eTeam_MAX], const std::map<int/*유저인덱스*/, int/*점수*/>& user_point, const std::map<int, int>& user_delta_point)
{//user_point 주의 : 중간에 나간 유저의 인덱스도 포함 될수 있다.
	if(CGameManager::getInstance().getInGameMode()->getProcessorType() == GAME_MODE_PROCESSOR_GUILD_ARENA)
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CGuildArenaTeamNotify(team_point, delta_point, user_point, user_delta_point));
	}
}

void CTRNetEventHandler::OnRecvAreaWarMode_Occupation_Ack(const AreaWarOccupationData & data)
{
	CGameManager::getInstance().onRecvAreaWarOccupationAck(data);
}

void CTRNetEventHandler::OnRecvAreaWarMode_Occupation_Bonus_Notify(const eTeam occupationTeam, const eAreaWarOccupationBonus_TYPE bonusType)
{
	CGameManager::getInstance().onRecvAreaWarOccupationBonusNotify(occupationTeam, bonusType);
}

void CTRNetEventHandler::OnRecvAreaWarMode_Occupation_Data(size_t areaWarOccupationData)
{
	CGameManager::getInstance().onRecvAreaWarOccupationSize(areaWarOccupationData);
}

void CTRNetEventHandler::OnRecvItemListRoomMasterBufMsg(std::vector<NetItemInfo> & info)
{
	std::vector<NetItemInfo>::iterator itor = info.begin();
	while (itor != info.end())
	{
		NetItemInfo itemInfo = *itor;
		std::string strMsg = CTRRoomMasterBuffMsgManager::getInstance().getItemMsg(itemInfo.m_iItemDescNum);
		if(strMsg == "")
		{
			CNetClientManager::getInstance().requestGetRoomMasterBufMsg(itemInfo.m_iItemDescNum);
		}

		itor++;
	}
}

void CTRNetEventHandler::OnRecvRoomMasterBufMsgNotify(RoomMasterBufMsgItem item)
{
	RoomMasterBufMsgItem* pItem = new RoomMasterBufMsgItem(item.getItemNum(), item.getMsg());
	CTRUserInterface::getInstance().OnRecvRoomMasterBufMsgNotify(pItem);
}

void CTRNetEventHandler::OnRecvGetMasterBuffMsgAck(eServerResult eResult, RoomMasterBufMsgItem item)
{
	if(eResult == eServerResult_OK_ACK)
	{
		CTRRoomMasterBuffMsgManager::getInstance().setItemMsg(item.getItemNum(), item.getMsg());
	}
	else
	{
		DBG_OUTPUT(60, "%s - %d", __FUNCTION__, eResult);
	}
}

void CTRNetEventHandler::OnRecvChangeMasterBuffMsgAck(eServerResult eResult, RoomMasterBufMsgItem item)
{
	if(eResult == eServerResult_OK_ACK)
	{
		CTRRoomMasterBuffMsgManager::getInstance().setItemMsg(item.getItemNum(), item.getMsg());
		CTRShortTimeMessage::showMessage(_STR(MSG_PROCESS_SUCCESS), 1.5f);
	}
	else
	{
		DBG_OUTPUT(60, "%s - %d", __FUNCTION__, eResult);
	}
}

#ifdef _PIERO_ELECTION_
void CTRNetEventHandler::OnRecvPieroLeaderAdvertiseAck(eServerResult eResult, int iMissionNum)
{
	if(eResult == eServerResult_OK_ACK)
	{
		CTRShortTimeMessage::showMessage(_STR(PIERO_ELECTION_PR_COMPLETE), 1.5f);

		std::vector<int> vecMissionRequestinfo;
		vecMissionRequestinfo.push_back(iMissionNum);
		CMissionMsgDispatcher::getInstance().addChallengingMission(eMissionKind_OPTIONAL, vecMissionRequestinfo);
	}
	else
	{
		DBG_OUTPUT(60, "%s - %d", __FUNCTION__, eResult);
		switch(eResult)
		{
		case eGiftItemFailed_INVALID_NICKNAME:							///< 알수없음. 
			CTRShortTimeMessage::showMessage(_STR(GIFT_USERNICK_FAILED), 1.5f);
			break;
		}
	}
}
#endif

#ifdef _MOTION_KEY_

void CTRNetEventHandler::OnRecvMotionQuickSlot_Info(const std::map<short,int>& SlotData)
{
	CTRNetPlayManager::getInstance().setMotionList(SlotData);
}

#endif

#ifdef _NEWBIE_RETURNER_
void CTRNetEventHandler::OnRecvNewbieReturner_InitialReward_ACK(const NEWBIE_RETURNER::NEWBIE_RETURNER_STATUS& status, const NEWBIE_RETURNER::REWARDED_ITEM& items, const NEWBIE_RETURNER::eNEWBIE_RETURNER_ACK& ack)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);
	DBG_DEMO_OUTPUT(126, "%s - type : %d", __FUNCTION__, status.initial_reward_type);
	DBG_DEMO_OUTPUT(126, "%s - reward : %s", __FUNCTION__, status.initial_rewarded ? "true" : "false");
	DBG_DEMO_OUTPUT(126, "%s - reward size : %d", __FUNCTION__, status.rewarded_indices.size());
	DBG_DEMO_OUTPUT(126, "%s - today size : %d", __FUNCTION__, status.today_rewarded);

	if(m_pNetPlay != NULL)
	{
		if(ack == NEWBIE_RETURNER::eNEWBIE_RETURNER_ACK_OK)
		{
			m_pNetPlay->setNewbieReturnerRewardInfo(status);
			m_pNetPlay->showNewbieReturnerRewardDlg(true);

			CTRShortTimeMessage::showMessage(_STR(ITEM_STORAGE_SUCCESS_GET_ITEM));
		}
		else
		{
			m_pNetPlay->showNewbieReturnerFailed(ack);
		}
	}

	if(!items.empty())
	{
		std::vector<RewardInfo> vecReward;
		for each(int i in items)
		{
			RewardInfo info;

			info.eRewardType = eRewardCondition_ITEM;
			info.iRewardID = i;

			vecReward.push_back(info);

			DBG_DEMO_OUTPUT(126, "%s - reward item : %d", __FUNCTION__, i);
		}
		CTRRewardManager::getInstance().getReward(vecReward);
	}
}

void CTRNetEventHandler::OnRecvNewbieReturner_Purchase_ACK(const NEWBIE_RETURNER::NEWBIE_RETURNER_STATUS& status, const NEWBIE_RETURNER::REWARDED_ITEM& items, const NEWBIE_RETURNER::eNEWBIE_RETURNER_ACK& ack, bool is_mawoo)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);
	DBG_DEMO_OUTPUT(126, "%s - type : %d", __FUNCTION__, status.initial_reward_type);
	DBG_DEMO_OUTPUT(126, "%s - reward : %s", __FUNCTION__, status.initial_rewarded ? "true" : "false");
	DBG_DEMO_OUTPUT(126, "%s - reward size : %d", __FUNCTION__, status.rewarded_indices.size());
	DBG_DEMO_OUTPUT(126, "%s - today size : %d", __FUNCTION__, status.today_rewarded);

	if(m_pNetPlay != NULL)
	{
		if(ack == NEWBIE_RETURNER::eNEWBIE_RETURNER_ACK_OK)
		{
			m_pNetPlay->setNewbieReturnerRewardInfo(status);
			m_pNetPlay->showNewbieReturnerRewardDlg(true);

			CTRShortTimeMessage::showMessage(_STR(ITEM_STORAGE_SUCCESS_GET_ITEM));
		}
		else
		{
			m_pNetPlay->showNewbieReturnerFailed(ack);
		}
	}

	if(!items.empty())
	{
		std::vector<RewardInfo> vecReward;
		for each(int i in items)
		{
			RewardInfo info;

			info.eRewardType = eRewardCondition_ITEM;
			info.iRewardID = i;

			vecReward.push_back(info);

			DBG_DEMO_OUTPUT(126, "%s - reward item : %d", __FUNCTION__, i);
		}
		CTRRewardManager::getInstance().getReward(vecReward, true);
	}

	CNetClientManager::getInstance().getUserPointAccess()->update_sync_gameUserPoint(eUserPointType_NEWBIE_MISSION_CONDITION_REWARD);
	
	if(is_mawoo)
	{
		CNetClientManager::getInstance().getUserPointAccess()->update_sync_gameUserPoint(eUserPointType_MILEAGE_ETC_POINT);
	}
}

void CTRNetEventHandler::OnRecvNewbieReturner_Status_ACK(const NEWBIE_RETURNER::NEWBIE_RETURNER_STATUS& status, const NEWBIE_RETURNER::eNEWBIE_RETURNER_ACK& ack)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);
	DBG_DEMO_OUTPUT(126, "%s - type : %d", __FUNCTION__, status.initial_reward_type);
	DBG_DEMO_OUTPUT(126, "%s - reward : %s", __FUNCTION__, status.initial_rewarded ? "true" : "false");
	DBG_DEMO_OUTPUT(126, "%s - reward size : %d", __FUNCTION__, status.rewarded_indices.size());
	DBG_DEMO_OUTPUT(126, "%s - today size : %d", __FUNCTION__, status.today_rewarded);

	if(m_pNetPlay != NULL)
	{
		m_pNetPlay->setNewbieReturnerRewardInfo(status);		
		m_pNetPlay->showNewbieReturnerRewardDlg(true);
	}

	CTRUserInterface::getInstance().onUserEvent("checkNewbieReturnerReward");
}

#endif

#ifdef _PARK_DROP_BOX_EVENT_
void CTRNetEventHandler::OnRecvDropBoxEvent_Failed(eDROP_BOX_EVENT_Result eResult)
{
	string strMent;
	switch(eResult)
	{
	case eDROP_BOX_EVENT_Result_EAT_ITEM_FAILED:			// 습득 하려는 아이템이 존재하지 않는다.( 이미 누군가 습득하였거나 셋팅 되어있지 않은 아이템 )
		strMent = _STR(BALLOON_PANG_ALREADY_GET_BOX);
		break;
	case eDROP_BOX_EVENT_Result_EAT_MAX_ITEM:				// 습득할수 있는 아이템수의 최대치에 도달했다.
		strMent = _STR(BALLOON_PANG_EAT_MAX_ITEM);
		break;
	case eDROP_BOX_EVENT_Result_EAT_USE_ITEM:				// 아이템을 누군가 습득중이다. 이아이템은 아직 습득할수 없다.
	case eDROP_BOX_EVENT_Result_EAT_NO_USER_DATA:			// 유저의 데이터가 아직 셋팅되지 않아 습득이 불가능하다
		strMent = _STR(BALLOON_PANG_NOT_EAT_BOX);
		break;
	case eDROP_BOX_EVENT_Result_EAT_INVALID_USER_NUM:		// 잘못된 유저번호
		strMent = _STR(MSG_PARK_DROPBOX_EVENT_EAT_INVALID_USER_NUM);
		break;
	case eDROP_BOX_EVENT_Result_EAT_INVALID_REWARD_LEVEL:	// 잘못된 보상 레벨
		strMent = _STR(MSG_PARK_DROPBOX_EVENT_EAT_INVALID_REWARD_LEVEL);
		break;
	case eDROP_BOX_EVENT_Result_EAT_ITEM_DB_ERROR:			// 알수 없는 이유(DB Error)
		strMent = _STR(FAILED_PIERO_OLYMPIC_UNKNOWN_ERROR);
		break;
	case eDROP_BOX_EVENT_Result_GET_USER_DATA_FAILED:		// 유저의 데이터를 가저올수 있는 상태가 아니다
		strMent = _STR(BALLOON_PANG_CANNOT_GET_USER_DATA);
		break;
	case eDROP_BOX_EVENT_Result_CLOSE_FEVER_TIME:			// 선물 습득 가능한 시간이 아니다
		strMent = _STR(BALLOON_PANG_NOT_FEVER_TIME);
		break;
	case eDROP_BOX_EVENT_Result_CLOSE_DROP_BOX_EVENT:		// 경기 시간이 아니다
		strMent = _STR(BALLOON_PANG_NOT_EVENT_TIME);
		break;
	case eDROP_BOX_EVENT_Result_TODAY_SCHEDULE_NO_DATA:		// 오늘 회차 정보가 존재하지 않는다.
		strMent = _STR(BALLOON_PANG_TODAY_SCHEDULE_NONE);
		break;
	case eDROP_BOX_EVENT_Result_ADD_POINT_EVENT_TYPE_FAILED:	// 아이템을 소모하여 포인트를 적립하고 보상을 받는데 이벤트 타입이 달라서 실패
		strMent = _STR(MSG_PARK_DROPBOX_EVENT_ADD_POINT_ITEM_DELETE_FAILED);
		break;
	case eDROP_BOX_EVENT_Result_ADD_POINT_ITEM_DELETE_FAILED:	// 포인트 적립에 사용되는 아이템이 존재하지않는다.
		if(CTRGameParkUI::getInstance().getParkDropBoxEvnetUseItemNum() != 0)
		{
			const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(CTRGameParkUI::getInstance().getParkDropBoxEvnetUseItemNum());
			if(pItem != NULL) strMent = format(_STR(KNIGHT_FLOWERS_HAVNT_POINT_ITEM), pItem->m_name.c_str());
			else DBG_OUTPUT(67, "CTRNetEventHandler::OnRecvDropBoxEvent_Failed pItem is NULL - eDROP_BOX_EVENT_Result_ADD_POINT_ITEM_DELETE_FAILED");
		}
		else DBG_OUTPUT(67, "CTRNetEventHandler::OnRecvDropBoxEvent_Failed m_iUseItemNum is 0 - eDROP_BOX_EVENT_Result_ADD_POINT_ITEM_DELETE_FAILED");
		break;
	case eDROP_BOX_EVENT_Result_ADD_POINT_ERROR:			// 포인트 적립중 알수없는 이유의 에러
		strMent = _STR(FAILED_PIERO_OLYMPIC_UNKNOWN_ERROR);
		break;
	case eDROP_BOX_EVENT_Result_FEVER_SETTING_TIME:			// 상자 세팅중이다.
		if(CTRGameParkUI::getInstance().getParkDropBoxEvnetUseItemNum() != 0)
		{
			const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(CTRGameParkUI::getInstance().getParkDropBoxEvnetUseItemNum());
			if(pItem != NULL) strMent = format(_STR(MSG_PARK_DROPBOX_EVENT_NOT_POINT_TIME), pItem->m_name.c_str());
			else DBG_OUTPUT(67, "CTRNetEventHandler::OnRecvDropBoxEvent_Failed pItem is NULL - eDROP_BOX_EVENT_Result_FEVER_SETTING_TIME");
		}
		else DBG_OUTPUT(67, "CTRNetEventHandler::OnRecvDropBoxEvent_Failed m_iUseItemNum is 0 - eDROP_BOX_EVENT_Result_FEVER_SETTING_TIME");
		break;
	case eDROP_BOX_EVENT_Result_FEVER_TIME:					// 상자 습득 시간이다.
		if(CTRGameParkUI::getInstance().getParkDropBoxEvnetUseItemNum() != 0)
		{
			const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(CTRGameParkUI::getInstance().getParkDropBoxEvnetUseItemNum());
			if(pItem != NULL) strMent = format(_STR(MSG_PARK_DROPBOX_EVENT_NOT_POINT_TIME), pItem->m_name.c_str());
			else DBG_OUTPUT(67, "CTRNetEventHandler::OnRecvDropBoxEvent_Failed pItem is NULL - eDROP_BOX_EVENT_Result_FEVER_TIME");
		}
		else DBG_OUTPUT(67, "CTRNetEventHandler::OnRecvDropBoxEvent_Failed m_iUseItemNum is 0 - eDROP_BOX_EVENT_Result_FEVER_TIME");
		break;				
	}

	CTRShortTimeMessage::showMessage(strMent);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_GetUserInfo( DropBoxEvent_UserInfo& userInfo )
{
	if(CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvDropBoxEventUserInfo(userInfo);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_GetUserInfo_Failed( eDROP_BOX_EVENT_Result eResult )
{
	OnRecvDropBoxEvent_Failed(eResult);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_SettingBoxList( const std::map<int, DropBoxEvent_SettingInfo>& mapSettingList )
{
	CTRGameParkUI::getInstance().onRecvDropBoxEventSettingBoxList(mapSettingList);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_SettingBoxList_Failed( eDROP_BOX_EVENT_Result eResult )
{
	OnRecvDropBoxEvent_Failed(eResult);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_EatItem( const DropBoxEvent_UserInfo& userinfo, int iItemIndex, int iRewardItemNum )
{
	const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(iRewardItemNum);
	if(pItem)
	{
		CKeepItemList::getInstance().onAddModifyItemCount(pItem->m_iUniqueNumber, 1);
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(pItem->m_iUniqueNumber);
	}

	if(CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvGetDropBoxByIndex(userinfo, iItemIndex);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_EatItem_Failed( eDROP_BOX_EVENT_Result eResult, int iIndex )
{
	switch(eResult)
	{
	case eDROP_BOX_EVENT_Result_EAT_ITEM_FAILED:
		if(CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvRemoveDropBoxByIndex(CGamePlayerID::INVALID_ID , iIndex);
		break;
	}
	OnRecvDropBoxEvent_Failed(eResult);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_Schedule( std::vector<int>& vecPointInfo, time_type tOpenTime, time_type tCloseTime, time_type tFeverStartTime )
{
	CTRGameParkUI::getInstance().onRecvDropBoxEventSchedule(vecPointInfo,tOpenTime,tCloseTime,tFeverStartTime);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_Schedule_Failed( eDROP_BOX_EVENT_Result eResult )
{
	std::vector<int> tempVector;
	for(int i=0; i<4; ++i)
		tempVector.push_back(0);
	CTRGameParkUI::getInstance().onRecvDropBoxEventSchedule(tempVector,0,0,0);
	OnRecvDropBoxEvent_Failed(eResult);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_GetTotalPoint( int iTotalPoint )
{
	if(CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvDropBoxEventCurPoint(iTotalPoint);
}
void CTRNetEventHandler::OnRecvDropBoxEvent_GetTotalPoint_Failed( eDROP_BOX_EVENT_Result eResult )
{
	OnRecvDropBoxEvent_Failed(eResult);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_GetToDaySchedule( std::vector<DropBoxEvent_ScheduleKind> vecSchedule, int iUseItemNum, int iUseItemCount, int iRewardGroupID )
{
	if(CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvDropBoxEventTodaySchedule(vecSchedule, iUseItemNum, iUseItemCount, iRewardGroupID);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_GetToDaySchedule_Failed( eDROP_BOX_EVENT_Result eResult )
{
	std::vector<DropBoxEvent_ScheduleKind> tempVector;
	tempVector.clear();
	if(CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvDropBoxEventTodaySchedule(tempVector, 0, 0, 0);
	OnRecvDropBoxEvent_Failed(eResult);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_AddPointReward( const std::vector<RewardInfo>& rewardList, int iUseItemNum, int iUseItemCount )
{
	CKeepItemList::getInstance().onRemoveModifyItemCount(iUseItemNum, iUseItemCount);

	std::vector<int> vecItem;

	bool bNeedRequestTR = false;
	bool bNeedRequestEXP = false;
	bool bNeedRequestITEM = false;

	for(size_t i=0; i<rewardList.size(); ++i)
	{
		RewardInfo rewardInfo = rewardList.at(i);

		switch(rewardInfo.eRewardType)
		{
		case eRewardCondition_TRMONEY:
			bNeedRequestTR = true;
			break;
		case eRewardCondition_EXP:
			bNeedRequestEXP = true;
			break;
		case eRewardCondition_ITEM:
			{
				const CItemInfoNode* pItem = CClientItemList::getInstance().getItemInfo(rewardInfo.iRewardID);
				if(pItem != NULL)
				{
					if(pItem->m_position == eFuncItemPosition_ADD_TR)
					{
						bNeedRequestTR = true;
					}
					else if(pItem->m_position == eFuncItemPosition_ADD_EXP)
					{
						bNeedRequestEXP = true;
					}
					else
					{
						vecItem.push_back(pItem->m_iUniqueNumber);
						bNeedRequestITEM = true;
					}
				}
			}			
			break;
		default:
			break;
		}
	}

	if(iUseItemNum != 0)
	{
		vecItem.push_back(iUseItemNum);
		bNeedRequestITEM = true;
	}

	if(bNeedRequestTR) CNetClientManager::getInstance().requestCurrentTR();
	if(bNeedRequestEXP) CNetClientManager::getInstance().requestExp(eLevelUPKind_RUN);
	if(bNeedRequestITEM) CNetClientManager::getInstance().requestCharacterAvatarItemByItemNumList(vecItem);

	if(CTRGameParkUI::getInstance().isActive()) CTRGameParkUI::getInstance().onRecvDropBoxEventAddPointReward(rewardList, iUseItemNum, iUseItemCount);
}

void CTRNetEventHandler::OnRecvDropBoxEvent_AddPointReward_Failed( eDROP_BOX_EVENT_Result eResult )
{
	OnRecvDropBoxEvent_Failed(eResult);
}

#endif

void CTRNetEventHandler::onRecvItemDyeingDyedItemListAck(const std::map<int, TintBlendUserData>& list_man, const std::map<int, TintBlendUserData>& list_woman)
{
	CTRSalonManager::getInstance().onRecvItemDyeingDyedItemListAck(list_man, list_woman);
}

void CTRNetEventHandler::onRecvItemDyeingDyeItemAck(int iItemNum, const TintBlendUserData& data, BYTE iGender)
{
	CTRSalonManager::getInstance().onRecvItemDyeingDyeItemAck(iItemNum, data, iGender);
}

void CTRNetEventHandler::onRecvItemDyeingDecolorItemAck(int iItemNum, const TintBlendUserData& data, BYTE iGender)
{
	CTRSalonManager::getInstance().onRecvItemDyeingDecolorItemAck(iItemNum, data, iGender);
}

void CTRNetEventHandler::onRecvItemDyeingDyedItemListFailed(eServerResult result)
{
	CTRSalonManager::getInstance().onRecvItemDyeingDyedItemListFailed(result);
}

void CTRNetEventHandler::onRecvItemDyeingDyeItemFailed(eServerResult result)
{
	CTRSalonManager::getInstance().onRecvItemDyeingDyeItemFailed(result);
}

void CTRNetEventHandler::onRecvItemDyeingDecolorItemFailed(eServerResult result)
{
	CTRSalonManager::getInstance().onRecvItemDyeingDecolorItemFailed(result);
}

#ifdef _USER_REPORT_SYSTEM
//!< 남은 신고하기 횟수 응답
void CTRNetEventHandler::OnRecvAgent_LEFT_ACCUSATION_COUNT_ACK(int left_free_accusationcount, int left_payed_accusationcount, int total_accusation_count, int accusation_point)
{
	DBG_DEMO_OUTPUT(126, "%s - %d, %d, %d, %d", __FUNCTION__, left_free_accusationcount, left_payed_accusationcount, total_accusation_count, accusation_point);
}

//!< 신고하기 응답
void CTRNetEventHandler::OnRecvAgent_DO_ACCUSATION_ACK(const USER_REPORT_SYSTEM::PROSECUTION_TYPE& type, const std::string& target_nick, USER_REPORT_SYSTEM::eUSER_REPORT_ACK ack, int left_free_accusationcount, int left_payed_accusationcount, int total_accusation_count, int accusation_point)
{
	DBG_DEMO_OUTPUT(126, "%s - %d, %d, %d, %d", __FUNCTION__, left_free_accusationcount, left_payed_accusationcount, total_accusation_count, accusation_point);

	CTRShortTimeMessage::showMessage(_STR(INFORMATION_ABUSEREPORT));

	if(ack == USER_REPORT_SYSTEM::eUSER_REPORT_ACK_OK)
	{
		CNetClientManager::getInstance().requestCharacterAvatarItemByPosition(0, eFuncItemPosition_PAYED_ACCUSATION);
	}
}

//!< 신고 상세 내용 추가 응답
void CTRNetEventHandler::OnRecvAgent_DO_ACCUSATION_SET_COMMENT_ACK(USER_REPORT_SYSTEM::ACCUSATION_ID id, const std::string& comment, USER_REPORT_SYSTEM::eUSER_REPORT_ACK ack)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);

	if(m_pNetPlay == NULL) return;

	if(ack == USER_REPORT_SYSTEM::eUSER_REPORT_ACK_OK)
	{
		m_pNetPlay->getUserReportDlgManager()->onRecvRecordDetailOK(id, comment);
	}
}

//!< 신고 리스트 응답
void CTRNetEventHandler::OnRecvAgent_ACCUSATION_LIST_ACK(const std::list<USER_REPORT_SYSTEM::ACCUSATION_INFO>& info, int max_page, USER_REPORT_SYSTEM::eUSER_REPORT_ACK ack)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);

	if(m_pNetPlay == NULL) return;
		
	m_pNetPlay->getUserReportDlgManager()->onRecvRecordList(info, max_page);
}

//!< 유저의 신고 정보
void CTRNetEventHandler::OnRecvAgent_DEMERIT_INFO_ACK(const USER_REPORT_SYSTEM::USER_REPORT& user_report, const std::string& nickname)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);

	if(CTRUserBookDlg::getInstance().isVisible())
	{
		CTRUserBookDlg::getInstance().onRecvUserReportInfo(user_report, nickname);
	}

	if(CNetClientManager::getInstance().getMyNickname() == nickname)
	{
		if(user_report.count_juror > 0)
		{
			CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_TRIAL_JUROR_COUNT);
			CMissionMsgDispatcher::getInstance().checkCompleteCondition();
		}

		if(user_report.count_audience > 0)
		{
			CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_TRIAL_AUDIENCE_COUNT);
			CMissionMsgDispatcher::getInstance().checkCompleteCondition();
		}
	}

	//!< 최초에 한번은 채널 갱신을 위해서 처리
	static bool bFirst = true;
	if(bFirst && CNetClientManager::getInstance().isPenaltyByUserReport() && CTRLobbyUI::getInstance().isActive())
	{	
#ifdef _RAINBOW_LEAGUE
		CTRLobbyUI::getInstance().gotoRainbowChannel();
#endif
	}
	bFirst = false;
}

//------------------------------------------------------------------------
//!< 재판 선택 요청
void CTRNetEventHandler::OnRecvAgent_JUDGMENT_NEED(const USER_REPORT_SYSTEM::USER_REPORT& ur)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);
}

//!< 재판 신청 응답 - 필요 없을듯.. 패킷이 오면 바로 방생성을 한다.
void CTRNetEventHandler::OnRecvAgent_JUDGMENT_ACK(USER_REPORT_SYSTEM::eUSER_REPORT_ACK ack, int judgment_id)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);
}

//!< 방 개수 응답
void CTRNetEventHandler::OnRecvAgent_COURT_ROOM_INFO_ACK(int wait_count, int in_judge_count)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);
}

//!< ???
void CTRNetEventHandler::OnRecvAgent_SET_PUNISHMENT(int period, USER_REPORT_SYSTEM::ePRISONER_TYPE prisoner_type)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);
}

//!< 처벌 시간 경감 아이템 사용시 응답
void CTRNetEventHandler::OnRecvAgent_USE_JAILITEM_ACK(int item, USER_REPORT_SYSTEM::eUSER_REPORT_ACK r)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);
}

//!< 유저 입장 정보 - 배심원 리스트, 방청객 리스트, 새로 들어온 유저, 나간 유저
void CTRNetEventHandler::OnRecvRoom_COURT_INFORMATION(int defendant, const std::vector<int>& juror, const std::vector<int>& audience, int new_added_user, int removed_user)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);

	if(CTRUserInterface::getInstance().getCurrentUIType() != GUI_TYPE_COURT_ROOM) return;

	USER_REPORT_SYSTEM::CTRUserTrialRoomUI* pUI = static_cast<USER_REPORT_SYSTEM::CTRUserTrialRoomUI*>(CTRUserInterface::getInstance().getCurrentUI());
	if(pUI == NULL) return;

	pUI->onRecvTrialEntranceInfo(defendant, juror, audience, new_added_user, removed_user);
}

//!< 재판 진행 시작
void CTRNetEventHandler::OnRecvRoom_COURT_DISCUSSION_START_NOTIFY(const int (&available_punishment)[USER_REPORT_SYSTEM::MAX_AVAILABLE_PUNISHMENT])
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);

	if(CTRUserInterface::getInstance().getCurrentUIType() != GUI_TYPE_COURT_ROOM) return;

	USER_REPORT_SYSTEM::CTRUserTrialRoomUI* pUI = static_cast<USER_REPORT_SYSTEM::CTRUserTrialRoomUI*>(CTRUserInterface::getInstance().getCurrentUI());
	if(pUI == NULL) return;

	pUI->onRecvTrialStart(available_punishment);
}

//
void CTRNetEventHandler::OnRecvRoom_COURT_EARLY_VERDICT_ACK(USER_REPORT_SYSTEM::eUSER_REPORT_ACK r)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);
}

void CTRNetEventHandler::OnRecvRoom_COURT_EARLY_VERDICT_NOTIFY(const std::vector<int>& requested_user)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);

	if(CTRUserInterface::getInstance().getCurrentUIType() != GUI_TYPE_COURT_ROOM) return;

	USER_REPORT_SYSTEM::CTRUserTrialRoomUI* pUI = static_cast<USER_REPORT_SYSTEM::CTRUserTrialRoomUI*>(CTRUserInterface::getInstance().getCurrentUI());
	if(pUI == NULL) return;

	pUI->onRecvTrialSkipUser(requested_user);
}

//!< 판결 응답
void CTRNetEventHandler::OnRecvRoom_COURT_VERDICT_ACK(USER_REPORT_SYSTEM::eUSER_REPORT_ACK result)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);

	if(CTRUserInterface::getInstance().getCurrentUIType() != GUI_TYPE_COURT_ROOM) return;

	USER_REPORT_SYSTEM::CTRUserTrialRoomUI* pUI = static_cast<USER_REPORT_SYSTEM::CTRUserTrialRoomUI*>(CTRUserInterface::getInstance().getCurrentUI());
	if(pUI == NULL) return;

	pUI->onRecvJudgementOK(result);
}

//!< 판결 결과 (진행중)
void CTRNetEventHandler::OnRecvRoom_COURT_VERDICT_INFO_NOTIFY(const USER_REPORT_SYSTEM::VERDICT_RESULT& result, const USER_REPORT_SYSTEM::VERDICT_COMMENT& comments, const USER_REPORT_SYSTEM::EVALUATION_RESULT& evaluation, bool is_final_punishment, int final_punishment, float final_evaluation, const bool (&user_exists)[USER_REPORT_SYSTEM::eCOURT_USER_TYPE_MAX])
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);

	if(CTRUserInterface::getInstance().getCurrentUIType() != GUI_TYPE_COURT_ROOM) return;

	USER_REPORT_SYSTEM::CTRUserTrialRoomUI* pUI = static_cast<USER_REPORT_SYSTEM::CTRUserTrialRoomUI*>(CTRUserInterface::getInstance().getCurrentUI());
	if(pUI == NULL) return;

	pUI->onRecvJudgementNotify(result, comments, evaluation, is_final_punishment, final_punishment, final_evaluation);

	if(is_final_punishment)
	{
		CNetClientManager::getInstance().requestDemeritInfo();
	}
}

//!< 판결 시작
void CTRNetEventHandler::OnRecvRoom_COURT_FORCED_VERDICT_NOTIFY(const int (&available_punishment)[USER_REPORT_SYSTEM::MAX_AVAILABLE_PUNISHMENT])
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);

	if(CTRUserInterface::getInstance().getCurrentUIType() != GUI_TYPE_COURT_ROOM) return;

	USER_REPORT_SYSTEM::CTRUserTrialRoomUI* pUI = static_cast<USER_REPORT_SYSTEM::CTRUserTrialRoomUI*>(CTRUserInterface::getInstance().getCurrentUI());
	if(pUI == NULL) return;

	pUI->onRecvJudgementStart();
}

//!< 재판 관련 시각 정보
void CTRNetEventHandler::OnRecvRoom_COURT_TIME_STATE(const USER_REPORT_SYSTEM::TIME_INFO& time_info)
{
	DBG_DEMO_OUTPUT(126, "%s", __FUNCTION__);

	if(CTRUserInterface::getInstance().getCurrentUIType() != GUI_TYPE_COURT_ROOM) return;

	USER_REPORT_SYSTEM::CTRUserTrialRoomUI* pUI = static_cast<USER_REPORT_SYSTEM::CTRUserTrialRoomUI*>(CTRUserInterface::getInstance().getCurrentUI());
	if(pUI == NULL) return;

	pUI->onRecvTimeInfo(time_info);
}

#endif

void CTRNetEventHandler::OnRecvFarmCraft_GetUserItemInfo( MAP_FARM_CRAFT_MASTER_ITEM_INFO& mapUserItemInfo )
{
	DBG_OUTPUT(60, "%s", __FUNCTION__);
	CKeepFarmItemList::getInstance().onRecvFarmCraftItemInfo(mapUserItemInfo);
}

void CTRNetEventHandler::OnRecvFarmCraft_GetUserItemInfo_Failed( eFARM_CRAFT_Result eResult )
{
	DBG_OUTPUT(60, "%s - %d", __FUNCTION__, eResult);
}

void CTRNetEventHandler::OnRecvFarmCraft_UpdateUserItemInfo( FarmCraft_ItemInfo& info )
{
	DBG_OUTPUT(60, "%s", __FUNCTION__);
	CKeepFarmItemList::getInstance().onRecvUpdateFarmCraftItemInfo(info);
}

void CTRNetEventHandler::OnRecvFarmCraft_UpdateUserItemInfo_Failed( eFARM_CRAFT_Result eResult )
{
	DBG_OUTPUT(60, "%s - %d", __FUNCTION__, eResult);
}

void CTRNetEventHandler::OnRecvFarmCraft_GetVoxelsData( RecvFarmMapVoxelsInfo& voxels, bool bUpdate, bool bEndCheck )
{
	DBG_OUTPUT(60, "%s - bUpdate[%d]", __FUNCTION__, bUpdate);

	//CTRFarmUI::getInstance().removeAllVoxel();
	CTRVoxelWorld::Inst().RemoveAllVoxel();

	vector<RecvFarmMapVoxelsInfo> vecVoxels;
	vecVoxels.push_back(voxels);
	CTRFarmUI::getInstance().loadFarmVoxels(vecVoxels);
}

void CTRNetEventHandler::OnRecvFarmCraft_GetVoxelsData_Failed( eFARM_CRAFT_Result eResult )
{
	DBG_OUTPUT(60, "%s - %d", __FUNCTION__, eResult);
	if(eResult == eFARM_CRAFT_Result_EMPTY_VOXEL_DATA)
	{
		vector<RecvFarmMapVoxelsInfo> vecVoxels;
		CTRFarmUI::getInstance().loadFarmVoxels(vecVoxels, true);
	}
}

void CTRNetEventHandler::OnRecvFarmCraft_SaveVoxelData()
{
	DBG_OUTPUT(60, "%s", __FUNCTION__);

	CTRFarmItemObjectManager::getInstance().onRecvSaveFarmCraftData();
}

void CTRNetEventHandler::OnRecvFarmCraft_SaveVoxelData_Failed( eFARM_CRAFT_Result eResult )
{
	DBG_OUTPUT(60, "%s - %d", __FUNCTION__, eResult);

	string strError;
	switch(eResult)
	{
	case eFARM_CRAFT_Result_DB_ERROR:
		break;
	case eFARM_CRAFT_Result_INVALID_USER_DATA:
		break;
	case eFARM_CRAFT_Result_INVALID_FARM:
		break;
	case eFARM_CRAFT_Result_ITEM_UPDATE_FAILED:
		break;
	case eFARM_CRAFT_Result_IS_NOT_FARM_MASTER:
		break;
	case eFARM_CRAFT_Result_NO_CHANGE_SAVE_VOXELS_DATA:
		break;
	case eFARM_CRAFT_Result_SAVE_VOXELS_DATA_FAILED:
		break;
	case eFARM_CRAFT_Result_SAVE_CHECK_NO_BLOCK_DATA:
		break;
	case eFARM_CRAFT_Result_SAVE_CHECK_ITEM_CHECK_FAILED:
		break;
	case eFARM_CRAFT_Result_SAVE_UN_COMPRESS_FAILED:
		break;
	case eFARM_CRAFT_Result_SAVING_DATA_FAILED:
		break;
	case eFARM_CRAFT_Result_EMPTY_VOXEL_DATA:
		break;
	}
}

void CTRNetEventHandler::OnRecvFarmCraft_ReloadVoxelData_Failed( eFARM_CRAFT_Result eResult )
{
	DBG_OUTPUT(60, "%s - %d", __FUNCTION__, eResult);
}

#ifdef _TR_KNIGHTAGE_
void CTRNetEventHandler::OnRecvTalesKnights_TakeUnitInfo(TalesKnights_UnitInfo &unitInfo, eTALES_KNIGHT_Result eResult)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager)
	{
		if(eResult == eTALES_KNIGHT_RESULT_RESULT_OK)
			pManager->onRecvTakeUnitInfo(unitInfo);
		else
			pManager->errorMessageHandler(eResult);
	}
}

void CTRNetEventHandler::OnRecvTalesKnights_MyUnitInfo(std::vector<TalesKnights_UnitInfo> m_UnitList)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvMyUnitInfo(m_UnitList);
}

void CTRNetEventHandler::OnrecvTalesKnights_MyGroupInfo(std::vector<TalesKnights_GroupInfo> m_GroupList)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvMyArrangementInfo(m_GroupList);
}

void CTRNetEventHandler::OnrecvTalesKnights_MyGroupInfoName(std::vector<TalesKnights_GroupInfo_Name> &vecGroupInfo)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvMyGroupInfo(vecGroupInfo);
}

void CTRNetEventHandler::OnrecvTalesKnights_MyGroupNameUpdateAck(int iGroupNum, std::string &strGroupName)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvUpdateGroupName(iGroupNum, strGroupName);
}

void CTRNetEventHandler::OnrecvTalesKnights_StageInfoAck(std::vector<TalesKnights_StageInfo> &vecStageInfo)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvStageInfo(vecStageInfo);
}

void CTRNetEventHandler::OnrecvTalesKnights_EnterAdventureAck(eTALES_KNIGHT_Result eResult, TalesKnights_GroupInfo_Name &groupInfo)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvAdventureStartAck(groupInfo, eResult);
}

void CTRNetEventHandler::OnrecvTalesKnights_AdventureCancelAck(int iGroupNum)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvAdventureCancelAck(iGroupNum);
}

void CTRNetEventHandler::OnrecvTalesKnights_ResultReward(int iGroupNum, int iStageNum, std::vector<TalesKnightRewardInfo> &vecReward)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvAdventureResultAckReward(iGroupNum, vecReward);

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_KNIGHTS_STAGE_GROUP, iStageNum);
	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_KNIGHTS_COMPLETE_COUNT, iStageNum);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

void CTRNetEventHandler::OnrecvTalesKnights_ResultExp(int iGroupNum, int iStageNum, std::vector<TalesKnight_LevelUpInfo> &vecLevelUpInfo)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvAdventureResultAckExp(iGroupNum, vecLevelUpInfo);
}

void CTRNetEventHandler::OnrecvTalesKnights_ResultDeadUnit(int iGroupNum, int iStageNum, std::vector<int> &vecDeadUnitList)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvAdventureResultAckDeadUnit(iGroupNum, vecDeadUnitList);
}

void CTRNetEventHandler::OnrecvTalesKnights_ResultWinList(std::map<int, eEventPartyType>& WinList)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvWinList(WinList);
}

void CTRNetEventHandler::OnRecvTalesKnights_ResultDamage(int iGroupNum , int Damage)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvAdventureResultAckDamage(iGroupNum, Damage);
}

void CTRNetEventHandler::OnrecvTalesKnights_PvERewardRecv(int iItemNum, eTALES_KNIGHT_Result eResult)
{
	if(eResult == eTALES_KNIGHT_RESULT_RESULT_OK)
		CTRRewardManager::getInstance().getReward(eRewardCondition_ITEM, iItemNum, 1, true);
	else
	{
		KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
		if(pManager) pManager->errorMessageHandler(eResult);
	}
}

void CTRNetEventHandler::OnrecvTalesKnights_PvPBattleAck(int iPlayerIndex, exp_type iExp, int iNumbers, bool bAccept, eTALES_KNIGHT_Result eResult, int iRemainTime)
{
	if(bAccept == false || eResult != eTALES_KNIGHT_RESULT_RESULT_OK)
	{
		KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
		if(pManager) pManager->errorMessageHandler(eResult, iRemainTime);
	}
	else
	{
		eGUI_TYPE eUiType = CTRUserInterface::getInstance().getCurrentUIType();
		if(eUiType == GUI_TYPE_FARM)
			CTRFarmUI::getInstance().onRecvPvPBattleAck(iPlayerIndex, iExp, iNumbers, bAccept, eResult);
		else if(eUiType == GUI_TYPE_PARK)
			CTRGameParkUI::getInstance().onRecvPvPBattleAck(iPlayerIndex, iExp, iNumbers, bAccept, eResult);
		else if(eUiType == GUI_TYPE_GUILD_FARM)
			CTRGuildFarmUI::getInstance().onRecvPvPBattleAck(iPlayerIndex, iExp, iNumbers, bAccept, eResult);
	}
}

void CTRNetEventHandler::OnrecvTalesKnights_PvPReadyNotify(int iTargetIndex, int iTargetGroup, bool bReady)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvPvPReadyNotify(iTargetIndex, iTargetGroup, bReady);
}

void CTRNetEventHandler::OnrecvTalesKnights_PVPCancle(int TargetIndex)
{
	bool bCloseUI = false;
	eGUI_TYPE eUiType = CTRUserInterface::getInstance().getCurrentUIType();
	if(eUiType == GUI_TYPE_FARM)
		bCloseUI = CTRFarmUI::getInstance().onRecvPvPCancel(TargetIndex);
	else if(eUiType == GUI_TYPE_PARK)
		bCloseUI = CTRGameParkUI::getInstance().onRecvPvPCancel(TargetIndex);
	else if(eUiType == GUI_TYPE_GUILD_FARM)
		bCloseUI = CTRGuildFarmUI::getInstance().onRecvPvPCancel(TargetIndex);

	if(bCloseUI)
	{
		KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
		if(pManager) pManager->errorMessageHandler(eTALES_KNIGHT_RESULT_PVP_CANCEL);
	}
}

void CTRNetEventHandler::OnrecvTalesKnights_PvPStartAck(std::string TargetGroupName, std::vector<TalesKnights_GroupInfo> &vecTargetGroupInfo, std::map<short, TalesKnight_PVPReusltInfo> &mapBattleResult, unsigned int iWinnerIndex, int iWinPoint, bool bLadderMatch)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvPvPStartAck(TargetGroupName, vecTargetGroupInfo, mapBattleResult, iWinnerIndex, iWinPoint, bLadderMatch);
}

void CTRNetEventHandler::OnrecvTalesKnights_PvPCommunityNotify(int iPlayerIndex, std::string &msg)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvPvPCommunityNotify(iPlayerIndex, msg);
}

void CTRNetEventHandler::OnrecvTalesKnights_PvPNotifyDuel(int iPlayerIndex, bool bLadder)
{
	eGUI_TYPE eUiType = CTRUserInterface::getInstance().getCurrentUIType();
	if(eUiType == GUI_TYPE_FARM)
		CTRFarmUI::getInstance().onRecvPvPNotifyDuel(iPlayerIndex, bLadder);
	else if(eUiType == GUI_TYPE_PARK)
		CTRGameParkUI::getInstance().onRecvPvPNotifyDuel(iPlayerIndex, bLadder);
	else if(eUiType == GUI_TYPE_GUILD_FARM)
		CTRGuildFarmUI::getInstance().onRecvPvPNotifyDuel(iPlayerIndex, bLadder);
}

void CTRNetEventHandler::OnrecvTalesKnights_PvPLadderInfo(int WinCount, int LoseCount, int WinRate, int LadderPoint, int Rank)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvMyPvPRecordInfo(WinCount, LoseCount, WinRate, LadderPoint, Rank);
}

void CTRNetEventHandler::OnrecvTalesKnights_ReinForceUnitAck(int iUnitNum, int iMaxLevel, bool bSuccess)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvReinforceAsk(iUnitNum, iMaxLevel, bSuccess);
}

void CTRNetEventHandler::OnrecvTalesKnights_UseExpItemAck(TalesKnight_LevelUpInfo &unitInfo, int RefreshItemNum)
{
	KNIGHTAGE::CTRKnightageManager *pManager = CNetClientManager::getInstance().getTRKnightageManager();
	if(pManager) pManager->onRecvUseExpUpAsk(unitInfo, RefreshItemNum);
}

#endif

#ifdef _FISHING_
void CTRNetEventHandler::onRecvFishingMyPictureBookAck(const vector<Fish>& fishList)
{
	CTRFishingSystemManager::getInstance().onRecvFishingMyPictureBookAck(fishList);
}

void CTRNetEventHandler::onRecvFishingMyKeepNetAck(const vector<Fish>& fishList)
{
	CTRFishingSystemManager::getInstance().onRecvFishingMyKeepNetAck(fishList);
}

void CTRNetEventHandler::onRecvFishingProcFishingAck(bool bProc)
{
	CTRFishingSystemManager::getInstance().onRecvFishingProcFishingAck(bProc);
}

void CTRNetEventHandler::onRecvFishingCatchFishNotify(const Fish& fish, int iDecoyNum)
{
	CTRFishingSystemManager::getInstance().onRecvFishingCatchFishNotify(fish, iDecoyNum);
}

void CTRNetEventHandler::onRecvFishingCatchFishNotify(BYTE numGameIndex, int iFishNum, int iFishSize, bool bFarmMasterReward)
{
	CTRFishingSystemManager::getInstance().onRecvFishingCatchFishNotify(numGameIndex, iFishNum, iFishSize, bFarmMasterReward);
}

void CTRNetEventHandler::onRecvFishingReceiveFromKeepNetAck(BYTE iRandomFist1, BYTE iRandomFist2)
{
	CTRFishingSystemManager::getInstance().onRecvFishingReceiveFromKeepNetAck(iRandomFist1, iRandomFist2);
}

void CTRNetEventHandler::onRecvFishingReceiveFromKeepNetAck(const vector<Fish>& fishList)
{
	CTRFishingSystemManager::getInstance().onRecvFishingReceiveFromKeepNetAck(fishList);
}

void CTRNetEventHandler::onRecvFishingMyRankingAck(const vector<FishingRanking>& fishingRankingList)
{
	CTRFishingSystemManager::getInstance().onRecvFishingMyRankingAck(fishingRankingList);
}

void CTRNetEventHandler::onRecvFishingStartMiniGameNotify(const Fish& fish, int iDecoyNum, BYTE iRandomFish, eFishingMiniGameType type)
{
	CTRFishingSystemManager::getInstance().onRecvFishingStartMiniGameNotify(fish, iDecoyNum, iRandomFish, type);
}

void CTRNetEventHandler::onRecvFishingStartMiniGameNotify(BYTE numGameIndex, int iFishNum, int iFishSize)
{
	CTRFishingSystemManager::getInstance().onRecvFishingStartMiniGameNotify(numGameIndex, iFishNum, iFishSize);
}

void CTRNetEventHandler::onRecvFishingMiniGameResultNotify(bool bSuccess, const Fish& fish, int iDecoyNum)
{
	CTRFishingSystemManager::getInstance().onRecvFishingMiniGameResultNotify(bSuccess, fish, iDecoyNum);
}

void CTRNetEventHandler::onRecvFishingMiniGameResultNotify(BYTE numGameIndex, bool bSuccess, int iFishNum, int iFishSize, bool bFarmMasterReward)
{
	CTRFishingSystemManager::getInstance().onRecvFishingMiniGameResultNotify(numGameIndex, bSuccess, iFishNum, iFishSize, bFarmMasterReward);
}

void CTRNetEventHandler::onRecvFishingFarmMasterRewardAck(const std::vector<Fishing_FarmMasterReward>& rewards)
{
	CTRFishingSystemManager::getInstance().onRecvFishingFarmMasterRewardAck(rewards);
}

void CTRNetEventHandler::onRecvFishingFarmMasterRewardAck(const std::vector<int>& rewards)
{
	CTRFishingSystemManager::getInstance().onRecvFishingFarmMasterRewardAck(rewards);
}

void CTRNetEventHandler::onRecvFishingRegistFarmMasterRewardAck(const std::vector<Fishing_FarmMasterReward>& rewards)
{
	CTRFishingSystemManager::getInstance().onRecvFishingRegistFarmMasterRewardAck(rewards);
}

void CTRNetEventHandler::onRecvFishingRemoveFarmMasterRewardAck(const std::vector<Fishing_FarmMasterReward>& rewards)
{
	CTRFishingSystemManager::getInstance().onRecvFishingRemoveFarmMasterRewardAck(rewards);
}

void CTRNetEventHandler::onRecvFishingMyPictureBookFailed(eServerResult result)
{
	CTRFishingSystemManager::getInstance().onRecvFishingMyPictureBookFailed(result);
}

void CTRNetEventHandler::onRecvFishingMyKeepNetFailed(eServerResult result)
{
	CTRFishingSystemManager::getInstance().onRecvFishingMyKeepNetFailed(result);
}

void CTRNetEventHandler::onRecvFishingProcFishingFailed(eServerResult result)
{
	CTRFishingSystemManager::getInstance().onRecvFishingProcFishingFailed(result);
}

void CTRNetEventHandler::onRecvFishingCatchFishFailed(eServerResult result)
{
	CTRFishingSystemManager::getInstance().onRecvFishingCatchFishFailed(result);
}

void CTRNetEventHandler::onRecvFishingReceiveFromKeepNetFailed(eServerResult result)
{
	CTRFishingSystemManager::getInstance().onRecvFishingReceiveFromKeepNetFailed(result);
}

void CTRNetEventHandler::onRecvFishingMyRankingFailed(eServerResult result)
{
	CTRFishingSystemManager::getInstance().onRecvFishingMyRankingFailed(result);
}

void CTRNetEventHandler::onRecvFishingStartMiniGameFailed(eServerResult result)
{
	CTRFishingSystemManager::getInstance().onRecvFishingStartMiniGameFailed(result);
}

void CTRNetEventHandler::onRecvFishingMiniGameResultFailed(eServerResult result)
{
	CTRFishingSystemManager::getInstance().onRecvFishingMiniGameResultFailed(result);
}

void CTRNetEventHandler::onRecvFishingFarmMasterRewardFailed(eServerResult result)
{
	CTRFishingSystemManager::getInstance().onRecvFishingFarmMasterRewardFailed(result);
}

void CTRNetEventHandler::onRecvFishingRegistFarmMasterRewardFailed(eServerResult result)
{
	CTRFishingSystemManager::getInstance().onRecvFishingRegistFarmMasterRewardFailed(result);
}

void CTRNetEventHandler::onRecvFishingRemoveFarmMasterRewardFailed(eServerResult result)
{
	CTRFishingSystemManager::getInstance().onRecvFishingRemoveFarmMasterRewardFailed(result);
}

void CTRNetEventHandler::onRecvFishingRegistFarmMasterRewardNotify(const std::vector<int>& rewards)
{
	CTRFishingSystemManager::getInstance().onRecvFishingRegistFarmMasterRewardNotify(rewards);
}

void CTRNetEventHandler::onRecvFishingRemoveFarmMasterRewardNotify(const std::vector<int>& rewards)
{
	CTRFishingSystemManager::getInstance().onRecvFishingRemoveFarmMasterRewardNotify(rewards);
}
#endif

#ifdef _FASHION_COORDI_KING_
void CTRNetEventHandler::onRecvFashionCoordiKingMySeasonInfoAck(FK_SeasonInfo seasonInfo)
{
	if(CTRMyroomDlg::getInstance().isVisible())
		CTRMyroomDlg::getInstance().onRecvFashionCoordiKingMySeasonInfo(seasonInfo);
}

void CTRNetEventHandler::onRecvFashionCoordiKingCoordiHistoryAck(std::vector<FK_History> historyList)
{
	CTRFashionCoordiKingManager::getInstance().onRecvFashionCoordiKingHistory(historyList);
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().onRecvFashionCoordiKingHistory(historyList);
}

void CTRNetEventHandler::onRecvFashionCoordiKingCoordiSubmitAck(int iEntrynum, int iCoordiModiCount)
{
	if(CTRMyroomDlg::getInstance().isVisible())
		CTRMyroomDlg::getInstance().onRecvFashionCoordiKingSubmit(iEntrynum, iCoordiModiCount);
}

void CTRNetEventHandler::onRecvFashionCoordiKingEntryListAck(std::vector<FK_Screening> screeningList)
{
	if(CTRMyroomDlg::getInstance().isVisible())
		CTRMyroomDlg::getInstance().onRecvFashionCoordiKingEntryList(screeningList);
}

void CTRNetEventHandler::onRecvFashionCoordiKingScreeningAck(int iWinner, int iRoundLevel, int iScreeningCount)
{
	if(CTRMyroomDlg::getInstance().isVisible())
		CTRMyroomDlg::getInstance().onRecvFashionCoordiKingScreening(iWinner, iRoundLevel, iScreeningCount);
}

void CTRNetEventHandler::onRecvFashionCoordiKingBookMarkAck(std::vector<FK_BookMark> bookmarklist)
{
	CTRFashionCoordiKingManager::getInstance().onRecvFashionCoordiKingBookMark(bookmarklist);
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().updateFashionCoordiKingBookMark();
}

void CTRNetEventHandler::onRecvFashionCoordiKingAddBookMarkAck(FK_BookMark bookmark)
{
	CTRFashionCoordiKingManager::getInstance().onRecvFashionCoordiKingAddBookMark(bookmark);
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().updateFashionCoordiKingBookMark();
}

void CTRNetEventHandler::onRecvFashionCoordiKingRemoveBookMarkAck(int iContestNum, int iEntryNum)
{
	CTRFashionCoordiKingManager::getInstance().onRecvFashionCoordiKingRemoveBookMark(iContestNum, iEntryNum);
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().updateFashionCoordiKingBookMark();
	if(iContestNum == CTRFashionCoordiKingManager::getInstance().getContest().m_iContestNum)
		if(CTRMyroomDlg::getInstance().isVisible())
			CTRMyroomDlg::getInstance().onRecvFashionCoordiKingRemoveBookmark(iEntryNum);
}

void CTRNetEventHandler::onRecvFashionCoordiKingCoordiBookAck(std::vector<FK_CoordiBook> coordiBookList)
{
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().onRecvFashionCoordiKingCoordiBook(coordiBookList);
}

void CTRNetEventHandler::onRecvFashionCoordiKingAddCoordiBookAck(FK_CoordiBook coordibook)
{
	CTRFashionCoordiKingManager::getInstance().onRecvFashionCoordiKingAddCoordiBook(coordibook);
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().updateFashionCoordiKingCoordiBook();
}

void CTRNetEventHandler::onRecvFashionCoordiKingRemoveCoordiBookAck(int iContestNum)
{
	CTRFashionCoordiKingManager::getInstance().onRecvFashionCoordiKingRemoveCoordiBook(iContestNum);
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().updateFashionCoordiKingCoordiBook();
}

void CTRNetEventHandler::onRecvFashionCoordiKingModifyCoordiBookAck(FK_CoordiBook coordibook)
{
	CTRFashionCoordiKingManager::getInstance().onRecvFashionCoordiKingModifyCoordiBook(coordibook);
	if(CTRUserBookDlg::getInstance().isVisible())
		CTRUserBookDlg::getInstance().updateFashionCoordiKingCoordiBook();
}

void CTRNetEventHandler::onRecvFashionCoordiKingTop3RankAck(int iContestNum, std::vector<FK_Top3Ranker> rankerList)
{
	CTRFashionCoordiKingManager::getInstance().onRecvFashionCoordiKingTop3Rank(iContestNum, rankerList);
	if(CTRGameParkUI::getInstance().isActive())
		CTRGameParkUI::getInstance().onRecvFashionCoordiKingTop3RankAck(iContestNum,rankerList);
}

void CTRNetEventHandler::onRecvFashionCoordiKingRewardAck(std::vector<int> itemnums)
{
	if(CTRMyroomDlg::getInstance().isVisible())
		CTRMyroomDlg::getInstance().onRecvFashionCoordiKingReward(itemnums);
}

void CTRNetEventHandler::onRecvFashionCoordiKingTop3RankNotify(std::vector<FK_Top3Ranker> rankerList)
{
	CTRFashionCoordiKingManager::getInstance().onRecvFashionCoordiKingTop3Rank(rankerList);
	if(CTRGameParkUI::getInstance().isActive())
		CTRGameParkUI::getInstance().onRecvFashionCoordiKingTop3RankNotify(rankerList);
	CNetClientManager::getInstance().requestFashionCoordiKing_BookMark();
}

void CTRNetEventHandler::onRecvFashionCoordiKingScheduleNotify(std::vector<FK_Schedule> scheduleList)
{
	CTRFashionCoordiKingManager::getInstance().onRecvFashionCoordiKingScheduleNotify(scheduleList);
}

void CTRNetEventHandler::onRecvFashionCoordiKingFailed(eServerResult result)
{
	std::string ment;
	switch(result)
	{
	case eServerResult_NOT_SUBMIT_PERIOD:
		ment = _STR(FASHION_COORDI_KING_NOT_SUBMIT_PERIOD);
		break;
	case eServerResult_NOT_SCREENING_PERIOD:
		ment = _STR(FASHION_COORDI_KING_NOT_SCREENING_PERIOD);
		break;
	case eServerResult_NOT_REST_PERIOD:
		ment = _STR(FASHION_COORDI_KING_NOT_REST_PERIOD);
		break;
	case eServerResult_MODIFY_LIMITED:
		ment = _STR(FASHION_COORDI_KING_MODIFY_LIMITED);
		break;
	case eServerResult_SCREENING_LIMITED:
		ment = _STR(FASHION_COORDI_KING_SCREENING_LIMITED);
		break;
	case eServerResult_INVALID_WINNER:
		ment = _STR(FASHION_COORDI_KING_INVALID_WINNER);
		CTRMyroomDlg::getInstance().onRecvFashionCoordiKingEntryReset();
		break;
	case eServerResult_INVALID_ROUND:
		ment = _STR(FASHION_COORDI_KING_INVALID_ROUND);
		break;
	case eServerResult_INVALID_BOOKMARK:
		ment = _STR(FASHION_COORDI_KING_INVALID_BOOKMARK);
		break;
	case eServerResult_BOOKMARK_LIMITED:
		ment = _STR(FASHOIN_COORDI_KING_BOOKMARK_LIMITED);
		break;
	case eServerResult_COORDIBOOK_LIMITED:
		ment = _STR(FASHION_COORDI_KING_COORDIBOOK_LIMITED);
		break;
	case eServerResult_INVALID_COORDIBOOK:
		ment = _STR(FASHION_COORDI_KING_INVALID_COORDIBOOK);
		break;
	case eServerResult_INVALID_CONTEST:
		ment = _STR(FASHION_COORDI_KING_INVALID_CONTEST);
		break;
	case eServerResult_ALREADY_RECEIVED_REWARD:
		ment = _STR(FASHION_COORDI_KING_ALREADY_RECEIVED_REWARD);
		break;
	case eServerResult_NO_QUALIFICATION:
		ment = _STR(FASHION_COORDI_KING_NO_QUALIFICATION);
		break;
	case eServerResult_INVALID_FASHION_REWARD:
		ment = _STR(FASHION_COORDI_KING_NO_QUALIFICATION);
		break;
	}
	CTRShortTimeMessage::getInstance().showMessage(ment);
}

#endif

#ifdef __EXTREME_COMBO__
void CTRNetEventHandler::OnRecvExtremePointAck(ROOM_RESULT::eServer_EXTREME_POINT_ACK_DETAIL detail)
{

}
#endif

#ifdef _DEV_FESTIVAL_
void CTRNetEventHandler::OnRecvDevFestival_GetUserInfo( DevFestival_info& user_info )
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_DEV_FESTIVAL)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRDevFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRDevFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_DEV_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->OnRecvDevFestival_GetUserInfo(user_info);
		}
	}
}

void CTRNetEventHandler::OnRecvDevFestival_GetUserInfo_Failed( eDevFestival_Result eResult )
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_DEV_FESTIVAL)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRDevFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRDevFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_DEV_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->OnRecvDevFestival_GetUserInfo_Failed(eResult);
		}
	}
}

void CTRNetEventHandler::OnRecvDevFestival_GiveRewardItem()
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_DEV_FESTIVAL)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRDevFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRDevFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_DEV_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->OnRecvDevFestival_GiveRewardItem();
		}
	}
}

void CTRNetEventHandler::OnRecvDevFestival_GiveRewardItem_Failed( eDevFestival_Result eResult )
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_DEV_FESTIVAL)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRDevFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRDevFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_DEV_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->OnRecvDevFestival_GiveRewardItem_Failed(eResult);
		}
	}
}

void CTRNetEventHandler::OnRecvDevFestival_GetStepRewardInfo( MAP_DEV_FESTIVAL_STEP_REWARD& rewardList )
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_DEV_FESTIVAL)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRDevFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRDevFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_DEV_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->OnRecvDevFestival_GetStepRewardInfo(rewardList);
		}
	}
}

void CTRNetEventHandler::OnRecvDevFestival_GetStepRewardInfo_Failed( eDevFestival_Result eResult )
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_DEV_FESTIVAL)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRDevFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRDevFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_DEV_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->OnRecvDevFestival_GetStepRewardInfo_Failed(eResult);
		}
	}
}

void CTRNetEventHandler::OnRecvDevFestival_GiveStepRewardItem( BYTE iRewardLevel, int iRewardItemNum )
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_DEV_FESTIVAL)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRDevFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRDevFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_DEV_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->OnRecvDevFestival_GiveStepRewardItem(iRewardLevel, iRewardItemNum);
		}
	}
}

void CTRNetEventHandler::OnRecvDevFestival_GiveStepRewardItem_Failed( eDevFestival_Result eResult )
{
	if(!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_DEV_FESTIVAL)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRDevFestivalChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRDevFestivalChannelDlg>(SUB_PTR_DIALOG_TYPE_DEV_FESTIVAL);
		if(pChannelUI)
		{
			pChannelUI->OnRecvDevFestival_GiveStepRewardItem_Failed(eResult);
		}
	}
}



void CTRNetEventHandler::OnRecvDevFestival_GetEndingCreditInfo( bool bEndingCreditCheck )
{
	DBG_DEMO_OUTPUT("%s - bEndingCreditCheck[%d]", __FUNCTION__, bEndingCreditCheck);

	CTRGameParkUI::getInstance().OnRecvDevFestival_GetEndingCreditInfo(bEndingCreditCheck);
}

void CTRNetEventHandler::OnRecvDevFestival_GetEndingCreditInfo_Failed( eDevFestival_Result eResult )
{
	DBG_DEMO_OUTPUT("%s - eDevFestival_Result[%d]", __FUNCTION__, eResult);

	CTRGameParkUI::getInstance().onRecvDevFestival_FailedMsg(eResult);
}

void CTRNetEventHandler::OnRecvDevFestival_GiveEndingCreditRewardItem( int iRewardItemNum )
{
	DBG_DEMO_OUTPUT("%s - iRewardItemNum[%d]", __FUNCTION__, iRewardItemNum);

	CTRGameParkUI::getInstance().OnRecvDevFestival_GiveEndingCreditRewardItem(iRewardItemNum);
}

void CTRNetEventHandler::OnRecvDevFestival_GiveEndingCreditRewardItem_Failed( eDevFestival_Result eResult )
{
	DBG_DEMO_OUTPUT("%s - eDevFestival_Result[%d]", __FUNCTION__, eResult);

	CTRGameParkUI::getInstance().onRecvDevFestival_FailedMsg(eResult);
}

#endif
#ifdef _TALES_TALK_RUEGO
void CTRNetEventHandler::OnRecvTalesTalkRuego_GetUserRuegoList( MAP_RUEGO_STATE_INFO& mapRuegoState, MAP_RUEGO_USER_NPC_INFO& mapRuegoUserNpcInfo )
{
	DBG_DEMO_OUTPUT(129, "%s - %d", __FUNCTION__, mapRuegoState.size());

	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvUserRuegoList(mapRuegoState);
	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvUserRuegoNpcPoint(mapRuegoUserNpcInfo);
}

void CTRNetEventHandler::OnRecvTalesTalkRuego_Add( int iRuegoNum, eRuegoState eState )
{
	DBG_OUTPUT(129, "%s - %d %d", __FUNCTION__, iRuegoNum, eState);

	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvUserRuegoState(iRuegoNum, eState);
}

void CTRNetEventHandler::OnRecvTalesTalkRuego_CompleteCheck( int iRuegoNum, eRuegoState eState )
{
	DBG_OUTPUT(129, "%s - %d %d", __FUNCTION__, iRuegoNum, eState);

	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvUserRuegoState(iRuegoNum, eState);
}

void CTRNetEventHandler::OnRecvTalesTalkRuego_CompleteReward( int iRuegoNum, eRuegoState eState, int iNpcNum, INT64 iTotalFavorPoint, std::vector<RewardInfo>& vecRewardList )
{
	DBG_OUTPUT(129, "%s - %d %d %d %I64d %d", __FUNCTION__, iRuegoNum, eState, iNpcNum, iTotalFavorPoint, vecRewardList.size());

	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvUserRuegoState(iRuegoNum, eState);
	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvUserRuegoNpcPoint(iNpcNum, iTotalFavorPoint);
	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvUserRuegoRewardOK(iRuegoNum, iNpcNum, iTotalFavorPoint, vecRewardList);

	CTRRewardManager::getInstance().getReward(vecRewardList, true);
}

void CTRNetEventHandler::OnRecvTalesTalkRuego_CompetitionScheduleInfo( bool bScheduleOnOff, TalesTalk_RuegoCompetitionSchedule_Info& info )
{
	DBG_DEMO_OUTPUT(129, "%s - %s %d", __FUNCTION__, bScheduleOnOff ? "On" : "Off", info.m_iRuegoNum);

	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvSuddenScheduleInfo(bScheduleOnOff, info);
}

void CTRNetEventHandler::OnRecvTalesTalkRuego_CompetitionGameInfo(  bool bGetRewardCheck, VEC_RUEGO_COMPETITION_GAME_INFO& vecCompetitionGameInfo )
{
	std::string str;
	for each(TalesTalk_RuegoCompetitionGame_Info info in vecCompetitionGameInfo)
	{
		str += format("[%d : %d]", info.m_ePartyType, info.m_iTeamPoint);
	}	

	DBG_DEMO_OUTPUT(129, "%s - %s %s", __FUNCTION__, bGetRewardCheck ? "Recv" : "None", str.c_str());

	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvSuddenPointInfo(bGetRewardCheck, vecCompetitionGameInfo);
}
void CTRNetEventHandler::OnRecvTalesTalkRuego_CompetitionReward( std::vector<RewardInfo>& vecRewardList )
{
	DBG_OUTPUT(129, "%s - %d", __FUNCTION__, vecRewardList.size());

	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvSuddenRewardOK(vecRewardList);

	CTRRewardManager::getInstance().getReward(vecRewardList, true);
}

void CTRNetEventHandler::OnRecvTalesTalkRuego_OneDayReset()
{
	DBG_DEMO_OUTPUT(129, "%s", __FUNCTION__);

	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvDayLimitRuegoInitNotify();
}

void CTRNetEventHandler::OnRecvTalesTalkRuego_GetOneDayList( UserTalesTalk_RuegoOneDayInfo& userOneDayInfo )
{
	DBG_DEMO_OUTPUT(129, "%s - %d", __FUNCTION__, userOneDayInfo.m_mapOneDayInfo.size());

	TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvDayLimitRuegoList(userOneDayInfo.m_mapOneDayInfo);
}

void CTRNetEventHandler::OnRecvTalesTalkRuego_Failed(eTalesTalk_RuegoResult eResult, const char* calledFunc, bool bShowFail)
{
	DBG_OUTPUT(129, "%s - %d by %s", __FUNCTION__, eResult, calledFunc);

	if(bShowFail) TALES_TALK_RUEGO::CTRTalesTalkRuegoManager::getInstance().onRecvUserRuegoFailed(eResult);
}

#endif

#ifdef _HUMONG_PICKBOARD_
void CTRNetEventHandler::OnRecvHumong_PickBoard_State_Ack(int iBoardNum, std::vector<HuMongPickBoard_Label>& labels)
{
	DBG_OUTPUT("%s - iBoardNum[%d], size[%d]", __FUNCTION__, iBoardNum, labels.size());

	CTRPaperPickBoardDialog* pDlg = CTRGameParkUI::getInstance().getHumongPickBoard();
	if(pDlg && pDlg->isVisible())
	{
		pDlg->OnRecvHumong_PickBoard_State_Ack(iBoardNum, labels);
	}
}

void CTRNetEventHandler::OnRecvHumong_PickBoard_State_Ack_Failed(eServerResult result)
{
	DBG_OUTPUT("%s - result[%d]", __FUNCTION__, result);

	CTRPaperPickBoardDialog* pDlg = CTRGameParkUI::getInstance().getHumongPickBoard();
	if(pDlg && pDlg->isVisible())
	{
		pDlg->OnRecvHumong_PickBoard_State_Ack_Failed(result);
	}
}

void CTRNetEventHandler::OnRecvHumong_PickBoard_Pick_Ack(int iPos, int iRank, int iAdditionalRewardItemNum)
{
	DBG_OUTPUT("%s - iPos[%d], iRank[%d], iAddRewardItemNum[%d]", __FUNCTION__, iPos, iRank, iAdditionalRewardItemNum);

	const CItemInfoNode *pItemInfo = CClientItemList::getInstance().getItemInfo(iAdditionalRewardItemNum);
	if(pItemInfo)	CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(pItemInfo->m_iUniqueNumber);

	CTRPaperPickBoardDialog* pDlg = CTRGameParkUI::getInstance().getHumongPickBoard();
	if(pDlg && pDlg->isVisible())
	{
		pDlg->OnRecvHumong_PickBoard_Pick_Ack(iPos, iRank);
	}
}

void CTRNetEventHandler::OnRecvHumong_PickBoard_Pick_Ack_Failed(eServerResult result)
{
	DBG_OUTPUT("%s - result[%d]", __FUNCTION__, result);

	CTRPaperPickBoardDialog* pDlg = CTRGameParkUI::getInstance().getHumongPickBoard();
	if(pDlg && pDlg->isVisible())
	{
		pDlg->OnRecvHumong_PickBoard_Pick_Ack_Failed(result);
	}
}

void CTRNetEventHandler::OnRecvHumong_PickBoard_Confirm_Ack(int iPos, int iRewardItemNum, int iAdditionalRewardItemNum)
{
	DBG_OUTPUT("%s - iBoardNum[%d], iPos[%d], iRewardItemNum[%d], Addtional[%d]", __FUNCTION__, iPos, iRewardItemNum, iAdditionalRewardItemNum);

	CTRPaperPickBoardDialog* pDlg = CTRGameParkUI::getInstance().getHumongPickBoard();
	if(pDlg && pDlg->isVisible())
	{
		pDlg->OnRecvHumong_PickBoard_Confirm_Ack(iPos, iRewardItemNum, iAdditionalRewardItemNum);
	}
}

void CTRNetEventHandler::OnRecvHumong_PickBoard_Confirm_Ack_Failed(eServerResult result)
{
	DBG_OUTPUT("%s - result[%d]", __FUNCTION__, result);

	CTRPaperPickBoardDialog* pDlg = CTRGameParkUI::getInstance().getHumongPickBoard();
	if(pDlg && pDlg->isVisible())
	{
		pDlg->OnRecvHumong_PickBoard_Confirm_Ack_Failed(result);
	}
}

void CTRNetEventHandler::OnRecvHumong_PickBoard_Init_Notify(int iBoardNum)
{
	//DBG_OUTPUT("%s - iBoardNum[%d]", __FUNCTION__, iBoardNum);

	CTRPaperPickBoardDialog* pDlg = CTRGameParkUI::getInstance().getHumongPickBoard();
	if(pDlg && pDlg->isVisible())
	{
		pDlg->OnRecvHumong_PickBoard_Init_Notify(iBoardNum);
	}
}

void CTRNetEventHandler::OnRecvHumong_PICKBOARD_GET_MYINFO_ACK(std::map<int, int>& boards)
{
	CTRPaperPickBoardDialog* pDlg = CTRGameParkUI::getInstance().getHumongPickBoard();
	if(pDlg)
	{
		pDlg->OnRecvHumong_PICKBOARD_GET_MYINFO_ACK(boards);
	}
}

#endif

#ifdef _RUNLYMPIC
void CTRNetEventHandler::Room_Runlympic_RACE_INFORMATION_NOTIFY(const RUNLYMPIC::room::RACE_INFORMATOIN& info)
{
	CGameManager::getInstance().getInGameMode()->notifyIntValue("LapCount", info.lap_count);
	CGameManager::getInstance().getInGameMode()->notifyIntValue("TimePerLap", info.limit_time_per_lap);
}

void CTRNetEventHandler::Room_Runlympic_RACE_START_ACK(RUNLYMPIC::room::eRACE_START_ACK ack)
{
	CGameManager::getInstance().getInGameMode()->notifyIntValue("LapStartAck", ack);
}

void CTRNetEventHandler::Room_Runlympic_RACE_END_ACK(RUNLYMPIC::room::eRACE_END_ACK ack)
{
	if(CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_RUNLYMPIC))
	{
		CGameManager::getInstance().getInGameMode()->notifyBoolValue("LapEndAck", ack);
	}
}

void CTRNetEventHandler::Room_Runlympic_RACE_NOTIFY(const RUNLYMPIC::room::RACE_NOTIFY& notify)
{
	if(CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_RUNLYMPIC))
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CRunlympicRaceNotify(notify));
	}
}

void CTRNetEventHandler::Room_Runlympic_GAME_NOTIFY(std::vector<RUNLYMPIC::room::GAME_NOTIFY_RANK>& game_rank, eTeam winner_team, const std::map<eTeam, int>& team_point)
{
	if(CGameManager::getInstance().isCurrInGameMode(GAME_MODE_PROCESSOR_RUNLYMPIC))
	{
		CGameManager::getInstance().getInGameMode()->onMsgDispatch(&MODE_PROC::CRunlympicGameNotify(game_rank, winner_team, team_point));
	}
}

void CTRNetEventHandler::Server_Runlympic_FRONT_INFO_ACK(const RUNLYMPIC::FRONT_INFO& front_info)
{
#ifdef _RUNLYMPIC
	CTRLobbyUI::getInstance().onRecvRunlympicFrontInfo(front_info);
#endif
}

void CTRNetEventHandler::Server_Runlympic_RANK_ACK(const RUNLYMPIC::RANK_INFO& rank_info)
{
#ifdef _RUNLYMPIC
	CTRLobbyUI::getInstance().onRecvRunlympicRankInfo(rank_info);
#endif
}

void CTRNetEventHandler::Server_Runympic_ACCEPT_REWARD_ACK(RUNLYMPIC::REWARD_DONE ack)
{
#ifdef _RUNLYMPIC
	CTRLobbyUI::getInstance().onRecvRunlympicRewardAck(ack);
#endif
}
#endif

#ifdef _GOODBYE_ACADEMY_
void CTRNetEventHandler::OnRecvGraduated_Info_Ack(std::vector<int>& PieceVec, int AlbumNum)
{
	CTRGameParkUI::getInstance().onRecvGraduatedInfoAck(PieceVec, AlbumNum);
}

void CTRNetEventHandler::OnRecvGraduated_Update_Ack(int RefreshItemNum, int RefreshRewardNum, bool UpdateOkay, eGraduated_Result Result)
{
	if(UpdateOkay)
	{
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(RefreshItemNum);
		CNetClientManager::getInstance().requestCharacterAvatarItemByItemNum(RefreshRewardNum);
		CTRGameParkUI::getInstance().onRecvGraduatedUpdateAck(RefreshItemNum,RefreshRewardNum);
	}
	else
	{
		switch(Result)
		{
		case eGraduated_Result_UNKNOWN:
			CTRShortTimeMessage::getInstance().showMessage(_STR(FAILED_PIERO_OLYMPIC_UNKNOWN_ERROR));
			break;
		case eGraduated_Result_NOT_ENOUGH_ITEM:
			CTRShortTimeMessage::getInstance().showMessage(_STR(PERSONALCONNECTIONS_ITEM_TEMPTY_MSG));
			break;
		case eGraduated_Result_WRONG_NUMBER:
			CTRShortTimeMessage::getInstance().showMessage(_STR(LALA_DIARY_INVALID_PAGE_NUM));
			break;
		case eGraduated_Result_ITEM_GIVE_FAILED:
			CTRShortTimeMessage::getInstance().showMessage(_STR(MSG_BILLING_ERROR_DB_ERROR));
			break;
		case eGraduated_Result_ITEM_DELETE_FAILED:
			CTRShortTimeMessage::getInstance().showMessage(_STR(MSG_BILLING_ERROR_DB_ERROR));
			break;
		}
		
	}
}

#endif

#ifdef _TUTORIAL_CHANNEL_
void CTRNetEventHandler::OnRecvTutorial_Channel_UserInfo( TutorialChannel_UserInfo& userInfo )
{
	DBG_OUTPUT("CTRNetEventHandler::OnRecvTutorial_Channel_UserInfo");

	CTRChannelTutorialInfo::getInstance().SetTutorialInfo(userInfo.m_mapUserRewardInfo);

	static bool recvAck = false;
	if (recvAck == false) {
		bool missionEnable = CTRChannelTutorialInfo::getInstance().IsMissionReward();
		bool tutorialEnable = CTRChannelTutorialInfo::getInstance().IsTutorial();
		CTRLobbyUI::getInstance().OpenTutorialChannel(missionEnable && tutorialEnable);
		CTRLobbyUI::getInstance().UpdateTutorialRaceLengthGraph();
		CTRChannelTutorialInfo::getInstance().SettingTutorialEnd();
	}
	recvAck = true;
}

void CTRNetEventHandler::OnRecvTutorial_Channel_GiveRewardInfo( std::vector<RewardInfo>& vecRewardInfo )
{
	DBG_OUTPUT("CTRNetEventHandler::OnRecvTutorial_Channel_GiveRewardInfo");

	eTUTORIAL_CHANNEL_TYPE type = CTRChannelTutorialRewardDlg::getInstance().GetType();
	if (type == eTUTORIAL_CHANNEL_TYPE_MISSION)
		CTRChannelTutorialRewardDlg::getInstance().ShowDialog(vecRewardInfo);
	else if (type == eTUTORIAL_CHANNEL_TYPE_RACE_LENGTH)
		CTRChannelTutorialRewardDlg::getInstance().Complete();

	if (!vecRewardInfo.empty()) CTRRewardManager::getInstance().getReward(vecRewardInfo, true);

	int level = CTRChannelTutorialRewardDlg::getInstance().GetLevel();
	CTRChannelTutorialInfo::getInstance().SetRewardComplete(type, level);

	CTRUserInterface::getInstance().UpdateTutorialRaceLengthGraph();
}

void CTRNetEventHandler::OnRecvTutorial_Channel_Failed(eTUTORIAL_CHANNEL_Result eResult)
{
	DBG_OUTPUT("CTRNetEventHandler::OnRecvTutorial_Channel_Failed (%d)", eResult);
	CTRChannelTutorialInfo::getInstance().OnRecvTutorial_Channel_Failed(eResult);
}
#endif

#ifdef _TALES_MARBLE_

void CTRNetEventHandler::OnRecvTalesMarble_GetUserInfo( TalesMarble_UserBoardInfo& userBoardInfo )
{
	DICE_BOARD::CTRDiceBoardManager *pManager = CNetClientManager::getInstance().getDiceBoardManager();
	if (pManager)
		pManager->OnRecvTalesMarble_GetUserInfo(userBoardInfo);
}

void CTRNetEventHandler::OnRecvTalesMarble_PlayDice( TalesMarble_PlayData& playDiceData )
{
	DICE_BOARD::CTRDiceBoardManager *pManager = CNetClientManager::getInstance().getDiceBoardManager();
	if (pManager)
		pManager->OnRecvTalesMarble_PlayDice(playDiceData);

	if(CTRMyroomDlg::getInstance().isVisible())
		CTRMyroomDlg::getInstance().onRecvGetAvatarItemList();

	CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_TALES_MARBLE_BOARD_NUM, playDiceData.m_iBoardNum);
	if(playDiceData.m_iReturnRewarditem > 0)
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_TALES_MARBLE_COMPLETE_COUNT);
	else
		CMissionMsgDispatcher::getInstance().addMissionConditionEvent(eMissionConditionType_TALES_MARBLE_PLAY_COUNT);
	CMissionMsgDispatcher::getInstance().checkCompleteCondition();
}

void CTRNetEventHandler::OnRecvTalesMarble_OpenBoardInfo( std::set<int>& setTalesMarble_OpenBoard )
{
	DICE_BOARD::CTRDiceBoardManager *pManager = CNetClientManager::getInstance().getDiceBoardManager();
	if (pManager)
		pManager->OnRecvTalesMarble_OpenBoardInfo(setTalesMarble_OpenBoard);
}

void CTRNetEventHandler::OnRecvTalesMarble_GiftItem( eTalesMarble_GiftType giftType, int iBoardNum, int iItemDescNum )
{
	DICE_BOARD::CTRDiceBoardManager *pManager = CNetClientManager::getInstance().getDiceBoardManager();
	if (pManager)
		pManager->OnRecvTalesMarble_GiftItem(giftType, iBoardNum, iItemDescNum);
}

void CTRNetEventHandler::OnRecvTalesMarble_GaugeCharingUseItem( int iBoardNum, int iDiceGauge, int iUseItemNum )
{
	DICE_BOARD::CTRDiceBoardManager *pManager = CNetClientManager::getInstance().getDiceBoardManager();
	if (pManager)
		pManager->OnRecvTalesMarble_GaugeCharingUseItem(iBoardNum, iDiceGauge, iUseItemNum);
}

void CTRNetEventHandler::OnRecvTalesMarble_GetUserGaugeInfo( int iBoardNum, int iDiceGauge )
{
	DICE_BOARD::CTRDiceBoardManager *pManager = CNetClientManager::getInstance().getDiceBoardManager();
	if (pManager)
		pManager->OnRecvTalesMarble_GetUserGaugeInfo(iBoardNum, iDiceGauge);
}

void CTRNetEventHandler::OnRecvTalesMarble_Reset_BoardInfo_UseItem( TalesMarble_UserBoardInfo& userBoardInfo, int iUseItemDescNum )
{
	CKeepItemList::getInstance().eraseItem(iUseItemDescNum);

	DICE_BOARD::CTRDiceBoardManager *pManager = CNetClientManager::getInstance().getDiceBoardManager();
	if (pManager)
		pManager->OnRecvTalesMarble_GetUserInfo(userBoardInfo);

	if (CTRMyroomDlg::getInstance().isVisible())
		CTRMyroomDlg::getInstance().onRecvGetAvatarItemList();
}

void CTRNetEventHandler::OnRecvTalesMarble_Failed(eTalesMarble_Result eResult, const char* calledFunc, bool bShowFail)
{
	DBG_OUTPUT(129, "%s - %d by %s", __FUNCTION__, eResult, calledFunc);
	DICE_BOARD::CTRDiceBoardManager *pManager = CNetClientManager::getInstance().getDiceBoardManager();
	if (pManager)
		pManager->OnRecvTalesMarble_Failed(eResult, bShowFail);
}
#endif

#ifdef _ARCHIVES_
void CTRNetEventHandler::OnRecv_Archives_UserData(std::vector<UserData_Archives>& ArchiveList)
{
	if(!ARCHIVES::CTRArchivesDlg::getInstance().isVisible()) ARCHIVES::CTRArchivesDlg::getInstance().showDialog();
	else ARCHIVES::CTRArchivesDlg::getInstance().updateInfo();
}

void CTRNetEventHandler::OnRecv_Archives_RewardList(std::vector<RewardInfo>& RewardList)
{
	ARCHIVES::CTRStoryBookDlg::getInstance().onRecvReward(RewardList);
}

void CTRNetEventHandler::OnRecv_Archives_Exchange_RewardList(std::map<int,bool>& RewardList, int RefreshItem, eArchives_Result eResult)
{
	switch (eResult)
	{
	case eArchives_Result_UNKNOWN:
		CTRShortTimeMessage::getInstance().showMessage(_STR(ERR_UNKNOWN));
		break;
	case eArchives_Result_OK:
		ARCHIVES::CTRArtifactDlg::getInstance().onRecvOpenArtifact(RewardList, RefreshItem);
		break;
	case eArchives_Result_NOT_ENOUGH_ITEM:
		CTRShortTimeMessage::getInstance().showMessage(_STR(PERSONALCONNECTIONS_ITEM_TEMPTY_MSG));
		break;
	}
}

#endif
void CTRNetEventHandler::OnRecv_FronTier_SchduleInfo(std::vector<Competition_OpenMap_ScheduleInfo>& Schedulelist)
{
#ifdef _TALES_FRONTIER_
	CTREventChannelSelectModeTalesFrontierDlg::SetScheduleList(std::move(Schedulelist));
#endif
#ifdef _WINTER_CHANNEL_2019_
	CTREventChannelWinter2019Dlg::SetScheduleList(std::move(Schedulelist));
#endif
#ifdef _SPRING_CHANNEL_2020_
	CTREventChannelSpring2020Dlg::SetScheduleList(std::move(Schedulelist));
#endif
	CTRLobbyUI::getInstance().OnRecv_FronTier_SchduleInfo();
}

#ifdef _TALES_FRONTIER_
void CTRNetEventHandler::OnRecv_FronTier_SummerBattleInfo(int remainCount)
{
	DBG_OUTPUT("CTRNetEventHandler::OnRecv_FronTier_SummerBattleInfo remainCount(%d)", remainCount);
	CTRLobbyUI::getInstance().OnRecv_FronTier_SummerBattleInfo(remainCount);
}

void CTRNetEventHandler::OnRecv_FronTier_TeamPointInfo(std::map<short, int>& PointList)
{
	CTRLobbyUI::getInstance().OnRecv_FronTier_TeamPointInfo(PointList);
}

void CTRNetEventHandler::OnRecv_FronTier_RewardInfo(bool CanReceive)
{
	CTRLobbyUI::getInstance().OnRecv_FronTier_RewardInfo(CanReceive);
}

void CTRNetEventHandler::OnRecv_FronTier_Reward(std::vector<RewardInfo>& RewardList, bool isWIn)
{
	CTRLobbyUI::getInstance().OnRecv_FronTier_Reward(RewardList, isWIn);
}

#endif

#ifdef _TOWER_OF_ORDEAL_
void CTRNetEventHandler::OnRecv_Tower_Of_Ordeal_Event_Notify(eTowerNotify NotiResult)
{
	std::string strMsg = "";
	switch(NotiResult)
	{
	case eTowerNotify_Before_Start_5Mins:

#if defined(_TREASURE_HUNT_MINIGAME_) && defined(_DEV_2020_)
		strMsg = _STR(TREASURE_MINIGAME_FINDBUG_ALARM);
#elif defined(_TREASURE_HUNT_MINIGAME_)
		strMsg = _STR(NEWYEAR_TREASURE_HUNT_ALARM);
#else
		strMsg = _STR(TOWER_OF_ORDEAL_NOTICE_ALARM);
#endif
		break;

	case eTowerNotify_Start:
#if defined(_TREASURE_HUNT_MINIGAME_) && defined(_DEV_2020_)
		strMsg = _STR(TREASURE_MINIGAME_FINDBUG_START);
#elif defined(_TREASURE_HUNT_MINIGAME_)
		strMsg = _STR(NEWYEAR_TREASURE_HUNT_START);
#else
		strMsg = _STR(TOWER_OF_ORDEAL_NOTICE_START);
#endif
		break;

	case eTowerNotify_End:
#if defined(_TREASURE_HUNT_MINIGAME_) && defined(_DEV_2020_)
		strMsg = _STR(TREASURE_MINIGAME_FINDBUG_END);
#elif defined(_TREASURE_HUNT_MINIGAME_)
		strMsg = _STR(NEWYEAR_TREASURE_HUNT_END);
#else
		strMsg = _STR(TOWER_OF_ORDEAL_NOTICE_END);
#endif
		break;
	}

	if (strMsg.empty() == false)
		CTRSystemNotice::getInstance().showMessage(strMsg);
}

void CTRNetEventHandler::OnRecv_Tower_Of_Ordeal_Event_OpenInfo(TowerGameInfo GameData, bool bEventOpen, time_type NextTime /*= 0*/)
{
	TOWER_OF_ORDEAL::CTRTowerOfOrdealManager *pManager = CNetClientManager::getInstance().getTowerOfOrdealManager();
	if (pManager)
	{
		pManager->onRecvOpenInfo(GameData, bEventOpen, NextTime);
	}
}

void CTRNetEventHandler::OnRecv_Tower_Of_Ordeal_Event_MyInfo(int TodayFreeCount, int TodayCashCount,  int PlayedTime)
{
	TOWER_OF_ORDEAL::CTRTowerOfOrdealManager *pManager = CNetClientManager::getInstance().getTowerOfOrdealManager();
	if (pManager)
		pManager->onRecvMyInfo(TodayFreeCount, TodayCashCount, PlayedTime);
}

void CTRNetEventHandler::OnRecv_Tower_Of_Ordeal_Event_Enter(eTowerResult eEnterResult, int FreeCount, int CashCount, int PlayableTime, bool isFree)
{
	DBG_OUTPUT("%s : %d, %d, %d, %d, %d", __FUNCTION__, eEnterResult, FreeCount, CashCount, PlayableTime, isFree);
	TOWER_OF_ORDEAL::CTRTowerOfOrdealManager *pManager = CNetClientManager::getInstance().getTowerOfOrdealManager();
	if (pManager)
		pManager->onRecvEnter(eEnterResult, FreeCount, CashCount, PlayableTime, isFree);
}

void CTRNetEventHandler::OnRecv_Tower_Of_Ordeal_Event_GetItem(int iBoxGrade, int iRefreshNum, int iBoxIndex, eTowerResult Result)
{
	if (CTRGameParkUI::getInstance().isActive())
	{
		if (Result == eTowerResult_OK)
		{
			CTRGameParkUI::getInstance().onRecvGetDropBoxByIndex(iBoxIndex);

			TOWER_OF_ORDEAL::CTRTowerOfOrdealManager *pManager = CNetClientManager::getInstance().getTowerOfOrdealManager();
			if (pManager)
				pManager->onRecvGetBoxItem(iBoxGrade, iRefreshNum);
		}
		else if (Result == eTowerResult_TAKE_OTHERES)
		{
			CTRGameParkUI::getInstance().onRecvRemoveDropBoxByIndex(CGamePlayerID::INVALID_ID, iBoxIndex);
			CTRGameParkUI::getInstance().closeTreasureMinigame();
#ifdef _DEV_2020_
			CTRShortTimeMessage::getInstance().showMessage(_STR(TREASURE_MINIGAME_FINDBUG_STILL_LUCKYBAG));
#else
			CTRShortTimeMessage::getInstance().showMessage(_STR(NEWYEAR_TREASURE_HUNT_STILL_LUCKYBAG));
#endif // _DEV_2020_
		}
		else
			DBG_OUTPUT("%s : failed %d", __FUNCTION__, Result);
	}
}

void CTRNetEventHandler::OnRecv_Tower_Of_Ordeal_Event_GiveUp()
{
	TOWER_OF_ORDEAL::CTRTowerOfOrdealManager *pManager = CNetClientManager::getInstance().getTowerOfOrdealManager();
	if (pManager)
		pManager->onRecvGiveUp();
}

void CTRNetEventHandler::OnRecv_Tower_Of_Ordeal_EventBoxList(std::map<int, Tower_BoxData>& BoxList)
{
	TOWER_OF_ORDEAL::CTRTowerOfOrdealManager *pManager = CNetClientManager::getInstance().getTowerOfOrdealManager();
	if (pManager)
		pManager->onRecvBoxList(BoxList);
}

void CTRNetEventHandler::OnRecv_Tower_Of_Ordeal_Event_GetBoxCount(std::map<int, int>& BoxCountList)
{
	TOWER_OF_ORDEAL::CTRTowerOfOrdealManager *pManager = CNetClientManager::getInstance().getTowerOfOrdealManager();
	if (pManager)
		pManager->onRecvUserBoxList(BoxCountList);
}

#endif

#ifdef _THANK_OFFERING_
void CTRNetEventHandler::OnRecvThankOffering_Failed( eThankOffering_Result eResult, const char* calledFunc, bool bShowFail )
{
	std::string str;
	switch (eResult)
	{
	case eThankOffering_Result_DB_Error:							// 알수없는 에러
		str = _STR(ERR_UNKNOWN);
		break;
	case eThankOffering_Result_GetUserPoint_Load_Failed:			// 유저 포인트 요청 실패
		str = _STR(ERROR_GET_USERPOINT_LOAD_FAILED);
		break;
	case eThankOffering_Result_ReceiveReward_Time_Failed:			// 보상받을수 있는 시간이 아니다.
		str = _STR(HUG_MSG_REWARD_GIVE_ERROR);
		break;
	case eThankOffering_Result_ReceiveReward_RankNoData_Failed:		// 유저의 랭킹 정보가 존재하지 않는다.(달린적이 없음)
		str = _STR(FAILED_RANK_INFO_FAILED);
		break;
	case eThankOffering_Result_ReceiveReward_Already_Failed:		// 이미 보상을 받았다.
		str = _STR(FAILED_AREADY_REWARD_RECIEVED);
		break;
	case eThankOffering_Result_ReceiveReward_NoRewardData_Failed:	// DB에 보상정보가 없다.
		str = _STR(ERROR_NO_REWARD_DATA);
		break;
	case eThankOffering_Result_GetRankInfo_Settlement_Failed:		// 현재 랭크정보 정산중이라 해당 정보를 요청할수 없다.
		str = _STR(FASHION_COORDI_KING_CALCULATE);
		break;
	}
	COkDialogEx::getInstance().showDialog(str);
}
void CTRNetEventHandler::OnRecvThankOffering_Receive_Reward(std::vector<RewardInfo> vecRewardList, eRoomKind roomkind )
{
	if (!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_THANK_OFFERING)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRThankOfferingChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRThankOfferingChannelDlg>(SUB_PTR_DIALOG_TYPE_THANK_OFFERING);
		if (pChannelUI)
		{
			pChannelUI->OnRecvThankOffering_Receive_Reward(roomkind, vecRewardList);
		}
	}
}

void CTRNetEventHandler::OnRecvThankOffering_UserPointInfo( int iNormal_LadderPoint, int iHardCore_LadderPoint )
{
	if (!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_THANK_OFFERING)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRThankOfferingChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRThankOfferingChannelDlg>(SUB_PTR_DIALOG_TYPE_THANK_OFFERING);
		if (pChannelUI)
		{
			pChannelUI->OnRecvThankOffering_GetUserInfo(iNormal_LadderPoint, iHardCore_LadderPoint);
		}
	}
}

void CTRNetEventHandler::OnRecvThankOffering_CurSchedule( time_type tOpenDate, time_type tCloseDate )
{
	if (!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_THANK_OFFERING)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRThankOfferingChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRThankOfferingChannelDlg>(SUB_PTR_DIALOG_TYPE_THANK_OFFERING);
		if (pChannelUI)
		{
			pChannelUI->OnRecvThankOffering_CurSchedule(tOpenDate,tCloseDate);
		}
	}
}

void CTRNetEventHandler::OnRecvThankOffering_LadderPoint(eRoomKind roomKind, int iLadderPoint)
{
	if (!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_THANK_OFFERING)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRThankOfferingChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRThankOfferingChannelDlg>(SUB_PTR_DIALOG_TYPE_THANK_OFFERING);
		if (pChannelUI)
		{
			pChannelUI->OnRecvThankOffering_LadderPoint(roomKind, iLadderPoint);
		}
	}
}

void CTRNetEventHandler::OnRecvThankOffering_GetRankInfo(ThankOffering_MapRankList& topRankList, ThankOffering_MapRankList& userRankList)
{
	if (!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_THANK_OFFERING)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRThankOfferingChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRThankOfferingChannelDlg>(SUB_PTR_DIALOG_TYPE_THANK_OFFERING);
		if (pChannelUI)
		{
			pChannelUI->OnRecvThankOffering_GetRankInfo(topRankList, userRankList);
		}
	}
}

void CTRNetEventHandler::OnRecvThankOffering_ScheduleOpenCloseNotify(bool bOpenClose)
{
	if (!CTRLobbyUI::getInstance().isOpenEventChannel(EVENT_CHANNEL_THANK_OFFERING)) return;

	CTRSubDialogManager *pSubDialogManager = CTRLobbyUI::getInstance().getSubDialogManager();
	if (pSubDialogManager)
	{
		CTRThankOfferingChannelDlg* pChannelUI = pSubDialogManager->getSubDialogPtr<CTRThankOfferingChannelDlg>(SUB_PTR_DIALOG_TYPE_THANK_OFFERING);
		if (pChannelUI)
		{
			pChannelUI->OnRecvThankOffering_ScheduleOpenCloseNotify(bOpenClose);
		}
	}
}
#endif

#if defined(_WINTER_CHANNEL_2019_) || defined(_SPRING_CHANNEL_2020_)
void CTRNetEventHandler::OnRecv_Winter_Channel_2019_UserWinInfo(std::map<int, std::vector<bool>>& List, int& RewardCount, int& TotalPoint)
{
	DBG_DEMO_OUTPUT("%s - size(%u), count(%d), totalpoint(%d)", __FUNCTION__, List.size(), RewardCount, TotalPoint);
	CTRLobbyUI::getInstance().OnRecv_Winter_Channel_2019_UserWinInfo(List, RewardCount, TotalPoint);
}

void CTRNetEventHandler::OnRecv_Winter_Channel_2019_RewardAck(std::vector<RewardInfo>& List, eWinter2019_Result eResult)
{
	DBG_DEMO_OUTPUT("%s - size(%u), result(%d)", __FUNCTION__, List.size(), eResult);
	CTRLobbyUI::getInstance().OnRecv_Winter_Channel_2019_RewardAck(List, eResult);
}

void CTRNetEventHandler::OnRecv_Winter_Channel_2019_TeamLeagueAck(	std::vector<TeamLeagueRankInfo>&List,
																							std::map<eEventPartyType, int>& RankCountList,
																							TeamLeagueRankInfo& MyRank,
																							INT64& CurPoint,
																							bool&	CanReward,
																							eWinter2019_Result& Result)
{
	CTRLobbyUI::getInstance().OnRecv_Winter_Channel_2019_TeamLeagueAck(List, RankCountList, MyRank, CurPoint, CanReward);
}

void CTRNetEventHandler::OnRecv_Winter_Channel_2019_TeamLeague_NextSchedule_Ack(Competition_OpenMap_ScheduleInfo& NextData)
{
	CTRLobbyUI::getInstance().OnRecv_Winter_Channel_2019_TeamLeague_NextSchedule_Ack(NextData);
}

void CTRNetEventHandler::OnRecv_Winter_Channel_2019_TeamLeague_Rank_Reward_Ack(std::vector<RewardInfo>& List, eWinter2019_Result& Result)
{
	CTRLobbyUI::getInstance().OnRecv_Winter_Channel_2019_TeamLeague_Rank_Reward_Ack(List);
}

#endif

#ifdef _TELEPATHY_
void CTRNetEventHandler::OnRecv_TelepathyMatchingOK(bool bJoin, const AdvancedAvatarInfo& avatarInfo, const std::string& strNickName)
{
	DBG_DEMO_OUTPUT("%s - join[%d], strNickName[%s]", __FUNCTION__, bJoin, strNickName.c_str());
	CTRGameParkUI::getInstance().OnRecv_TelepathyMatchingOK(bJoin, avatarInfo, strNickName);
}

void CTRNetEventHandler::OnRecv_TelepathyMatchingFailed(eServerResult result)
{
	DBG_DEMO_OUTPUT("%s", __FUNCTION__);
	CTRGameParkUI::getInstance().OnRecv_TelepathyMatchingFailed(result);
}

void CTRNetEventHandler::OnRecv_TelepathyChoiceACK(eServerResult result, short iOtherChoice)
{
	DBG_DEMO_OUTPUT("%s - otherChoice[%d]", __FUNCTION__, iOtherChoice);
	CTRGameParkUI::getInstance().OnRecv_TelepathyChoiceACK(result, iOtherChoice);
}

void CTRNetEventHandler::OnRecv_TelepathyGameResultNotify(eServerResult result, BYTE iSuccessCnt, int iRewardItemNum, bool bWin)
{
	DBG_DEMO_OUTPUT("%s - successCnt[%d], rewardItem[%d], bWin[%d]", __FUNCTION__, iSuccessCnt, iRewardItemNum, bWin);
	CTRGameParkUI::getInstance().OnRecv_TelepathyGameResultNotify(result, iSuccessCnt, iRewardItemNum, bWin);
}

void CTRNetEventHandler::OnRecv_TelepathyForceFinishNotify()
{
	DBG_DEMO_OUTPUT("%s", __FUNCTION__);
	CTRGameParkUI::getInstance().OnRecv_TelepathyForceFinishNotify();
}

void CTRNetEventHandler::OnRecv_TelepathyNextQuestionNotify(short iQuestionNum, short iAnswer1, short iAnswer2)
{
	DBG_DEMO_OUTPUT("%s - questionNum[%d], answer1[%d], answer2[%d]", __FUNCTION__, iQuestionNum, iAnswer1, iAnswer2);
	CTRGameParkUI::getInstance().OnRecv_TelepathyNextQuestionNotify(iQuestionNum, iAnswer1, iAnswer2);
}

void CTRNetEventHandler::OnRecv_TelepathyScheduleNotice()
{
	DBG_DEMO_OUTPUT("%s", __FUNCTION__);
	CTRGameParkUI::getInstance().OnRecv_TelepathyScheduleNotice();
}

void CTRNetEventHandler::OnRecv_TelepathyScheduleNotify(bool bOn)
{
	DBG_DEMO_OUTPUT("%s - on/off[%d]", __FUNCTION__, bOn);
	CTRGameParkUI::getInstance().OnRecv_TelepathyScheduleNotify(bOn);
}

void CTRNetEventHandler::OnRecv_TelepathyEventPeriodNotify(time_type tStart, time_type tEnd)
{
	DBG_DEMO_OUTPUT("%s - start[%I64d], end[%I64d]", __FUNCTION__, tStart, tEnd);
	CTRGameParkUI::getInstance().OnRecv_TelepathyEventPeriodNotify(tStart, tEnd);
}
#endif

#ifdef _QUIZ_QUIZ_
void CTRNetEventHandler::OnRecv_QuizQuizTodayPlayCountAck(int iPlayCount)
{
	DBG_OUTPUT("%s : %d", __FUNCTION__, iPlayCount);
	CTRUserInterface::getInstance().OnRecv_QuizQuizTodayPlayCountAck(iPlayCount);
}

void CTRNetEventHandler::OnRecv_QuizQuizStartAck(int iUseItemNum, int iPlayCount)
{
	DBG_OUTPUT("%s, %d, %d", __FUNCTION__, iUseItemNum, iPlayCount);
	CTRUserInterface::getInstance().OnRecv_QuizQuizStartAck(iUseItemNum, iPlayCount);

	if (CTRMyroomDlg::getInstance().isVisible())
		CTRMyroomDlg::getInstance().onRecvGetAvatarItemList();
}

void CTRNetEventHandler::OnRecv_QuizQuizQuestionAck(int iIndexNum, int iQuestionNum)
{
	DBG_OUTPUT("!!!! %s : idx(%d), quiz(%d)", __FUNCTION__, iIndexNum, iQuestionNum);
	CTRUserInterface::getInstance().OnRecv_QuizQuizQuestionAck(iIndexNum, iQuestionNum);
}

void CTRNetEventHandler::OnRecv_QuizQuizAnswerAck(eServerResult eResult)
{
	DBG_OUTPUT("!!!! %s : %d", __FUNCTION__, eResult);
	CTRUserInterface::getInstance().OnRecv_QuizQuizAnswerAck(eResult);
}

void CTRNetEventHandler::OnRecv_QuizQuizIncorrectAnswerAck(const std::string &strCorrectAnswer)
{
	DBG_OUTPUT("!!!! %s : %s", __FUNCTION__, strCorrectAnswer.c_str());
	CTRUserInterface::getInstance().OnRecv_QuizQuizIncorrectAnswerAck(strCorrectAnswer);
}

void CTRNetEventHandler::OnRecv_QuizQuizRewardAck(int iRewardItemNum)
{
	CTRUserInterface::getInstance().OnRecv_QuizQuizRewardAck(iRewardItemNum);
}

void CTRNetEventHandler::OnRecv_QuizQuizFailedAck(eServerResult eResult)
{
	DBG_OUTPUT("!!!! %s : %d", __FUNCTION__, eResult);
	CTRUserInterface::getInstance().OnRecv_QuizQuizFailedAck(eResult);
}
#endif