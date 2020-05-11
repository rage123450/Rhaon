#include "stdafx.h"
#include "TRWorkshopList.h"
//
#include "TRWorkshop_ListDlg.h"

CTRWorkshopList::CTRWorkshopList()
{
	m_pDlg = m_pDlg == nullptr ? make_shared<CTRWorkshop_ListDlg>() :
								[&]() {
										m_pDlg = nullptr;
										return make_shared<CTRWorkshop_ListDlg>();
									  }();
}

CTRWorkshopList::~CTRWorkshopList()
{
}

void CTRWorkshopList::showDialog()
{
	try
	{
		if(m_pDlg == nullptr)
		{
			throw exception("shared_ptr<CTRWorkshop_ListDlg> var is nullptr!");
		}

		m_pDlg->showDialog();
	}
	catch(const std::exception& e)
	{
		DBG_OUTPUT(e.what());
	}
}

void CTRWorkshopList::closeDialog()
{
	if(m_pDlg)
	{
		m_pDlg->closeDialog();
	}
}

void CTRWorkshopList::onRecvGuildPlantGetPlantItemListOK(std::multimap<time_type, GuildPlantSellInfo> useList)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetPlantItemListOK(useList);
	}
}

void  CTRWorkshopList::onRecvGuildPlantBuyItemOK(int iSellNum, int iItemNum, int iBuyCount)
{
	if (m_pDlg)
	{
		m_pDlg->onRecvGuildPlantBuyItemOK(iSellNum, iItemNum, iBuyCount);
	}
}

void CTRWorkshopList::onRecvGuildPlantGetGuildManagerTR(exp_type iGuildManagerTR)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetGuildManagerTR(iGuildManagerTR);
	}
}

void CTRWorkshopList::onRecvGuildPlantInvestGuildManagerTR(exp_type iGuildManagerTR)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantInvestGuildManagerTR(iGuildManagerTR);
	}
}

void CTRWorkshopList::onRecvGuildPlantGetStorageExtendOK(int iExtendCount, int iExtendValue, int iUserInvestCount, int iUserInvestValue)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetStorageExtendOK(iExtendCount, iExtendValue, iUserInvestCount, iUserInvestValue);
	}
}

void CTRWorkshopList::onRecvGuildPlantGetInvestorManagerTRListOK(std::multimap<int, std::string> userList)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetInvestorManagerTRListOK(userList);
	}
}

void CTRWorkshopList::onRecvGuildPlantGetExpenseListOK(eRewardCondition pointType, int iMonth, std::vector<GuildPlantPointUseInfo> useList)
{
	if(m_pDlg)
	{
		m_pDlg->onRecvGuildPlantGetExpenseListOK(pointType, iMonth, useList);
	}
}

void CTRWorkshopList::LoadGuideList(CTRGuildPlanInfoLoader * pLoader)
{
	if(m_pDlg)
	{
		m_pDlg->LoadGuideList(pLoader);
	}
}
