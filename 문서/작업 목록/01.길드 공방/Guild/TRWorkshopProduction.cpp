#include "stdafx.h"
#include "TRWorkshopProduction.h"
//
#include "TRGuildWorkshop_ProductionDlg.h"
#include "NetClientManager.h"

CTRWorkshopProduction::CTRWorkshopProduction()
{
	m_pDlg = m_pDlg == nullptr ? make_shared<CTRGuildWorkshop_ProductionDlg>() : 
								[&]() {
										m_pDlg = nullptr;
										return make_shared<CTRGuildWorkshop_ProductionDlg>(); 
									  }();
}

CTRWorkshopProduction::~CTRWorkshopProduction()
{
}

void CTRWorkshopProduction::showDialog()
{
	if(m_pDlg)
	{
		m_pDlg->showDialog();
	}
}

void CTRWorkshopProduction::closeDialog()
{
	if(m_pDlg)
	{
		m_pDlg->closeDialog();
	}
}

void CTRWorkshopProduction::onRecvGuildPlantGetMakeStandByItemListOK(std::map<int, GuildPlantMakeInfo> guildplant)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetMakeStandByItemListOK(guildplant);
	}
}

void CTRWorkshopProduction::onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetGivePossibleUserListOK(userList);
	}
}

void CTRWorkshopProduction::onRecvGuildPlantGetItemContributeRankLIstOK(std::multimap<int, std::string> userList)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetItemContributeRankLIstOK(userList);
	}
}

void CTRWorkshopProduction::onRecvGuildPlantGetMakeProgressItemOK(GuildPlantMakeInfo guildplantMakeInfo, int iMyContributionPoint, eGuildPlantDistributeKind distributeKind)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetMakeProgressItemOK(guildplantMakeInfo, iMyContributionPoint, distributeKind);
	}
}

void CTRWorkshopProduction::onRecvGuildPlantChangeMyConstributionPointItemOK(int iItemIndexNum)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantChangeMyConstributionPointItemOK(iItemIndexNum);
	}
}

void CTRWorkshopProduction::onRecvGuildPlantGiveGiftOK(int iItemIndexNum)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGiveGiftOK(iItemIndexNum);
	}
}

void CTRWorkshopProduction::onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetGuildManagerTR(iGuildManagerTR);
	}
}

void CTRWorkshopProduction::onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantInvestGuildManagerTR(iGuildManagerTR);
	}
}

void CTRWorkshopProduction::onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetStorageExtendOK(iExtendCount, iExtendValue, iUserInvestCount, iUserInvestValue);
	}
}

void CTRWorkshopProduction::onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetInvestorManagerTRListOK(userList);
	}
}

void CTRWorkshopProduction::onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetExpenseListOK(pointType, iMonth, useList);
	}
}

void CTRWorkshopProduction::LoadGuideList(CTRGuildPlanInfoLoader * pLoader)
{
	if(m_pDlg)
	{
		m_pDlg->LoadGuideList(pLoader);
	}
}
