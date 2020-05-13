#include "stdafx.h"
#include "TRWorkshopController.h"

#include "TRWorkshopBase.h"
#include "TRWorkshopProduction.h"
#include "TRWorkshopList.h"
#include "TRGuildWorkshop_ManagementDlg.h"

CTRWorkshopController::CTRWorkshopController()
	: m_arrControlName{ "", "Close", "Workshop_ManagementBtn", "Workshop_ProductionBtn", "Workshop_ListBtn", "MiniGameBtn" }
{
	for (int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		switch (i)
		{
		case EWorkshop::MANAGEMENT:
			m_arrBase[i] = new CTRGuildWorkshop_ManagementDlg();
			break;

		case EWorkshop::PRODUCTION:
			m_arrBase[i] = new CTRWorkshopProduction();
			break;

		case EWorkshop::LIST:
			m_arrBase[i] = new CTRWorkshopList();
			break;
		}
	}
}

CTRWorkshopController::~CTRWorkshopController()
{
	for (int i = 0; i < EWorkshop::END; ++i)
	{
		SAFE_DELETE(m_arrBase[i]);
	}

	SAFE_DELETE(m_pLoader);

	closeDialog();
}

void CTRWorkshopController::onRecvCurrentGuildPoint(__int64 iGuildPt)
{
	for (int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if (m_arrBase[i])
		{
			m_arrBase[i]->onRecvCurrentGuildPoint(iGuildPt);
		}
	}
}

void CTRWorkshopController::onRecvCurrentMyGuildPoint(int iMyGuildPt)
{
	for (int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if (m_arrBase[i])
		{
			m_arrBase[i]->onRecvCurrentMyGuildPoint(iMyGuildPt);
		}
	}
}

void CTRWorkshopController::onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR)
{
	for (int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if (m_arrBase[i])
		{
			m_arrBase[i]->onRecvGuildPlantGetGuildManagerTR(iGuildManagerTR);
		}
	}
}

void CTRWorkshopController::onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR)
{
	for(int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if(m_arrBase[i])
		{
			m_arrBase[i]->onRecvGuildPlantInvestGuildManagerTR(iGuildManagerTR);
		}
	}
}

void CTRWorkshopController::onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue)
{
	for(int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if(m_arrBase[i])
		{
			m_arrBase[i]->onRecvGuildPlantGetStorageExtendOK(iExtendCount, iExtendValue, iUserInvestCount, iUserInvestValue);
		}
	}
}

void CTRWorkshopController::onRecvGuildPlantRegisterItemOK(exp_type iGuildManagerTR)
{
	for(int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if(m_arrBase[i])
		{
			m_arrBase[i]->onRecvGuildPlantRegisterItemOK(iGuildManagerTR);
		}
	}
}

void CTRWorkshopController::onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList)
{
	for(int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if(m_arrBase[i])
		{
			m_arrBase[i]->onRecvGuildPlantGetInvestorManagerTRListOK(userList);
		}
	}
}

void CTRWorkshopController::onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList)
{
	for(int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if(m_arrBase[i])
		{
			m_arrBase[i]->onRecvGuildPlantGetExpenseListOK(pointType, iMonth, useList);
		}
	}
}

void CTRWorkshopController::onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind)
{
	for (int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if (m_arrBase[i])
		{
			m_arrBase[i]->onRecvGuildPlantGetMakeProgressItemOK(guildplantMakeInfo, iMyContributionPoint, distributeKind);
		}
	}
}

void CTRWorkshopController::onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant)
{
	for (int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if (m_arrBase[i])
		{
			m_arrBase[i]->onRecvGuildPlantGetMakeStandByItemListOK(guildplant);
		}
	}
}

void CTRWorkshopController::onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList)
{
	for (int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if (m_arrBase[i])
		{
			m_arrBase[i]->onRecvGuildPlantGetPlantItemListOK(useList);
		}
	}
}

void CTRWorkshopController::onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList)
{
	if (m_arrBase[PRODUCTION])
	{
		m_arrBase[PRODUCTION]->onRecvGuildPlantGetGivePossibleUserListOK(userList);
	}
}

void CTRWorkshopController::onRecvGuildPlantGiveGiftOK(int iItemIndexNum)
{
	if (m_arrBase[PRODUCTION])
	{
		m_arrBase[PRODUCTION]->onRecvGuildPlantGiveGiftOK(iItemIndexNum);
	}
}

void CTRWorkshopController::onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList)
{
	if (m_arrBase[PRODUCTION])
	{
		m_arrBase[PRODUCTION]->onRecvGuildPlantGetItemContributeRankLIstOK(userList);
	}
}

void CTRWorkshopController::onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum)
{
	if(m_arrBase[PRODUCTION])
	{
		m_arrBase[PRODUCTION]->onRecvGuildPlantChangeMyConstributionPointItemOK(iItemIndexNum);
	}
}

void CTRWorkshopController::onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount)
{
	if (m_arrBase[LIST])
	{
		m_arrBase[LIST]->onRecvGuildPlantBuyItemOK(iSellNum, iItemNum, iBuyCount);
	}
}

tuple<CTRWorkshopController::EWorkshop, int> CTRWorkshopController::Init(string _strControlName)
{
	if (nullptr == m_pLoader)
	{
		m_pLoader = new CTRGuildPlanInfoLoader();
		m_pLoader->Init();
	}

	for (int i = 0; i < EWorkshop::END; i++)
	{
		if (_strControlName == m_arrControlName[i])
		{
			if (i == EWorkshop::CLOSE)
			{
				return { EWorkshop::CLOSE, -1 };
			}
			else if (i == EWorkshop::ETC)
			{
				return { EWorkshop::ETC, -1 };
			}
			else if (i == EWorkshop::MANAGEMENT)
			{
				return { EWorkshop::MANAGEMENT, i };
			}
			else
			{
				return { EWorkshop::END, i };
			}
		}
	}

	return { EWorkshop::CLOSE, -1 };
}

void CTRWorkshopController::showDialog(int _nIndex)
{
	if (m_arrBase[_nIndex])
	{
		if(EWorkshop::MANAGEMENT == _nIndex)
		{
			static_cast<CTRGuildWorkshop_ManagementDlg*>(m_arrBase[_nIndex])->loadItemList(m_pLoader);
		}

		if(EWorkshop::PRODUCTION == _nIndex)
		{
			static_cast<CTRWorkshopProduction*>(m_arrBase[_nIndex])->LoadGuideList(m_pLoader);
		}

		if(EWorkshop::LIST == _nIndex)
		{
			static_cast<CTRWorkshopList*>(m_arrBase[_nIndex])->LoadGuideList(m_pLoader);
		}

		m_arrBase[_nIndex]->showDialog();
	}
}

void CTRWorkshopController::closeDialog()
{
	for (int i = EWorkshop::MANAGEMENT; i < EWorkshop::END; ++i)
	{
		if (m_arrBase[i])
		{
			m_arrBase[i]->closeDialog();
		}
	}
}