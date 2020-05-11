#include "stdafx.h"
#include "TRWorkshopBase.h"

#include "language/LanguageHeader.h"
#include "language/UnicodeTextFile.h"

CTRGuildPlanInfoLoader::CTRGuildPlanInfoLoader()
{
	m_mapGuildPlantItemList.clear();
	m_mapGuildPlantNeedPoint.clear();
	m_mapGuildPlantGuideList.clear();
}

CTRGuildPlanInfoLoader::~CTRGuildPlanInfoLoader()
{
	for (auto& pair : m_mapGuildPlantItemList)
	{
		if (pair.second)
		{
			SAFE_DELETE(pair.second);
		}
	}

	m_mapGuildPlantItemList.clear();

	for (auto& pair : m_mapGuildPlantNeedPoint)
	{
		std::vector<stGuildPlantNeedPointInfo*> vecNeedInfo = pair.second;
		for (auto& info : vecNeedInfo)
		{
			SAFE_DELETE(info);
		}
	}

	m_mapGuildPlantNeedPoint.clear();

	for (auto& pair : m_mapGuildPlantGuideList)
	{
		if (pair.second)
		{
			SAFE_DELETE(pair.second);
		}
	}

	m_mapGuildPlantGuideList.clear();
}

void CTRGuildPlanInfoLoader::Init()
{
	if (m_mapGuildPlantItemList.empty())
	{
		if (false == loadGuildPlantItemInfo("script\\EssenGuildPlantItemInfo.txt"))
		{
			DBG_DEMO_OUTPUT("%s - Reason[%s]", "loadGuildPlantItemInfo", _STR(HS_ERR_ANTICPXCNT_FILE_NOT_FOUND));
		}
	}

	if (m_mapGuildPlantNeedPoint.empty())
	{
		if (false == loadGuildPlantNeedPointInfo("script\\EssenGuildPlantItemNeePointInfo.txt"))
		{
			DBG_DEMO_OUTPUT("%s - Reason[%s]", "loadGuildPlantNeedPointInfo", _STR(HS_ERR_ANTICPXCNT_FILE_NOT_FOUND));
		}
	}

	if(m_mapGuildPlantGuideList.empty())
	{
		if(false == loadGuildPlantGuideInfo("script\\EssenGuildPlantGuideInfo.txt"))
		{
			DBG_DEMO_OUTPUT("%s - Reason[%s]", "loadGuildPlantGuideInfo", _STR(HS_ERR_ANTICPXCNT_FILE_NOT_FOUND));
		}
	}
}

bool CTRGuildPlanInfoLoader::loadGuildPlantItemInfo(const std::string& strFileName)
{
	CTextFileToPackage filereader(true);

	if (false == filereader.open(strFileName))
	{
		// 파일열기 실패
		return false;
	}

	try
	{
		for (auto& pair : m_mapGuildPlantItemList)
		{
			if (pair.second)
			{
				SAFE_DELETE(pair.second);
			}
		}

		m_mapGuildPlantItemList.clear();

		std::string buf;
		while (filereader.getLine(buf))
		{
			//! 주석이면 넘어간다
			if (stringutil::startswith(buf, "//"))
			{
				continue;
			}

			std::vector<std::string> lineInfoStr;
			std::stringstream ss(buf);

			//! ','로 구분하여 파싱한다
			stringutil::split(lineInfoStr, ss, ',');

			if (lineInfoStr.size() < 8)
			{
				throw exception(buf.c_str());
			}

			GuildPlantItemInfo* pInfo = new GuildPlantItemInfo();
			pInfo->iIndex = atoi(lineInfoStr[0].c_str());
			pInfo->iCategory = atoi(lineInfoStr[1].c_str());
			pInfo->iRegisterPointKind = atoi(lineInfoStr[2].c_str());
			pInfo->iOrder = atoi(lineInfoStr[3].c_str());
			pInfo->iItemNum = atoi(lineInfoStr[4].c_str());
			pInfo->iDurationDay = atoi(lineInfoStr[5].c_str());
			pInfo->iSellPointKind = atoi(lineInfoStr[6].c_str());
			pInfo->iSellPointValue = atoi(lineInfoStr[7].c_str());

			std::map<int, GuildPlantItemInfo*>::iterator itr =	m_mapGuildPlantItemList.find(pInfo->iIndex);
			if (itr == m_mapGuildPlantItemList.end())
			{
				m_mapGuildPlantItemList.insert(std::make_pair(pInfo->iIndex, pInfo));
			}
		}
	}
	catch (const exception& e)
	{
		TRDBG_OUTPUT_ERROR("loadGuildPlantItemInfo - %s", e.what());
		_ASSERTE(FALSE);
		return false;
	}

	return true;
}

bool CTRGuildPlanInfoLoader::loadGuildPlantNeedPointInfo(const std::string& strFileName)
{
	CTextFileToPackage filereader(true);

	if (false == filereader.open(strFileName))
	{
		// 파일열기 실패
		return false;
	}

	try
	{
		m_mapGuildPlantNeedPoint.clear();

		std::string buf;
		while (filereader.getLine(buf))
		{
			//! 주석이면 넘어간다
			if (stringutil::startswith(buf, "//"))
			{
				continue;
			}

			std::vector<std::string> lineInfoStr;
			std::stringstream ss(buf);

			//! ','로 구분하여 파싱한다
			stringutil::split(lineInfoStr, ss, ',');

			if (lineInfoStr.size() < 5)
			{
				throw exception(buf.c_str());
			}

			stGuildPlantNeedPointInfo* pInfo = new stGuildPlantNeedPointInfo();
			pInfo->iIndex = atoi(lineInfoStr[0].c_str());
			pInfo->iDistributeKind = atoi(lineInfoStr[1].c_str());
			pInfo->iLimitBuyCount = atoi(lineInfoStr[2].c_str());
			pInfo->iRegisterTR = atoi(lineInfoStr[3].c_str());
			pInfo->iRegisterGP = atoi(lineInfoStr[4].c_str());

			std::map<int, std::vector<stGuildPlantNeedPointInfo*>>::iterator itr = m_mapGuildPlantNeedPoint.find(pInfo->iIndex);
			if (itr != m_mapGuildPlantNeedPoint.end())
			{
				(itr->second).push_back(pInfo);
			}
			else
			{
				std::vector<stGuildPlantNeedPointInfo*> vecNeedPoint;
				vecNeedPoint.push_back(pInfo);

				m_mapGuildPlantNeedPoint.insert(std::make_pair(pInfo->iIndex, vecNeedPoint));
			}
		}
	}
	catch (const exception& e)
	{
		TRDBG_OUTPUT_ERROR("loadGuildPlantNeedPointInfo - %s", e.what());
		_ASSERTE(FALSE);
		return false;
	}

	return true;
}

bool CTRGuildPlanInfoLoader::loadGuildPlantGuideInfo(const std::string & strFileName)
{
	CTextFileToPackage filereader(true);

	if (false == filereader.open(strFileName))
	{
		// 파일열기 실패
		return false;
	}

	try
	{
		m_mapGuildPlantGuideList.clear();

		std::string buf;
		while (filereader.getLine(buf))
		{
			//! 주석이면 넘어간다
			if (stringutil::startswith(buf, "//"))
			{
				continue;
			}

			std::vector<std::string> lineInfoStr;
			std::stringstream ss(buf);

			//! '@'로 구분하여 파싱한다
			stringutil::split(lineInfoStr, ss, '@');

			if (lineInfoStr.size() < 4)
			{
				throw exception(buf.c_str());
			}

			GuildPlantGuideInfo* pInfo = new GuildPlantGuideInfo();
			pInfo->iIndex = atoi(lineInfoStr[0].c_str());
			pInfo->iSubIndex = atoi(lineInfoStr[1].c_str());
			pInfo->title = lineInfoStr[2];
			pInfo->body = lineInfoStr[3];

			stringutil::replaceString(pInfo->body, "<BR>", "\n");
			stringutil::replaceString(pInfo->body, "<br>", "\n");

			m_mapGuildPlantGuideList.insert(std::make_pair(std::make_pair(pInfo->iIndex, pInfo->iSubIndex), pInfo));
		}
	}
	catch (const exception& e)
	{
		TRDBG_OUTPUT_ERROR("loadGuildPlantGuideInfo - %s", e.what());
		_ASSERTE(FALSE);
		return false;
	}

	return true;
}

bool CTRGuildPlanInfoLoader::isValidIndexItemNum(int iIndexItemnum)
{
	if (iIndexItemnum < 1)
		return false;

	MAP_ITEMLIST::iterator itr = m_mapGuildPlantItemList.find(iIndexItemnum);
	if (itr != m_mapGuildPlantItemList.end())
		return true;

	return false;
}

std::vector<int> CTRGuildPlanInfoLoader::getDistributeKind(int iIndex, int iRegisterPointKind)
{
	std::vector<int> vecValue;

	std::map<int, std::vector<stGuildPlantNeedPointInfo*>>::iterator itr = m_mapGuildPlantNeedPoint.find(iIndex);
	if (itr != m_mapGuildPlantNeedPoint.end())
	{
		std::vector<stGuildPlantNeedPointInfo*> vecNeedPoint = itr->second;
		for (auto& needInfo : vecNeedPoint)
		{
			if (needInfo)
			{
				int iDistibuteKind = needInfo->iDistributeKind;
				bool bFind = false;
				for (size_t i=0; i<vecValue.size(); i++)
				{
					if (vecValue[i] == iDistibuteKind)
					{
						bFind = true;
						continue;
					}						
				}

				if (!bFind)
				{
					if (iRegisterPointKind == eRewardCondition_GUILD_POINT && needInfo->iRegisterGP > 0)
						vecValue.push_back(iDistibuteKind);
					else if (iRegisterPointKind == eRewardCondition_GUILD_MANAGER_TR && needInfo->iRegisterTR > 0)
						vecValue.push_back(iDistibuteKind);
				}
			}
		}
	}

	return vecValue;
}

std::vector<int> CTRGuildPlanInfoLoader::getLimtBuyCount(int iIndex, int iDistributeKind, int iRegisterPointKind)
{
	std::vector<int> vecValue;

	std::map<int, std::vector<stGuildPlantNeedPointInfo*>>::iterator itr = m_mapGuildPlantNeedPoint.find(iIndex);
	if (itr != m_mapGuildPlantNeedPoint.end())
	{
		std::vector<stGuildPlantNeedPointInfo*> vecNeedPoint = itr->second;
		for (auto& needInfo : vecNeedPoint)
		{
			if (needInfo && needInfo->iDistributeKind == iDistributeKind)
			{
				if (iRegisterPointKind == eRewardCondition_GUILD_POINT && needInfo->iRegisterGP > 0)
					vecValue.push_back(needInfo->iLimitBuyCount);
				else if (iRegisterPointKind == eRewardCondition_GUILD_MANAGER_TR && needInfo->iRegisterTR > 0)
					vecValue.push_back(needInfo->iLimitBuyCount);
			}
		}
	}

	return vecValue;
}

int CTRGuildPlanInfoLoader::getNeedPoint(int iIndex, int iDistributeKind, int iLimitBuyCount, int iRegisterPointKind)
{
	int iValue = 0;

	std::map<int, std::vector<stGuildPlantNeedPointInfo*>>::iterator itr = m_mapGuildPlantNeedPoint.find(iIndex);
	if (itr != m_mapGuildPlantNeedPoint.end())
	{
		std::vector<stGuildPlantNeedPointInfo*> vecNeedPoint = itr->second;
		for (auto& needInfo : vecNeedPoint)
		{
			if (needInfo)
			{
				if (needInfo->iDistributeKind == iDistributeKind && needInfo->iLimitBuyCount == iLimitBuyCount)
				{
					iValue = needInfo->iRegisterTR;
				}
			}
		}
	}

	return iValue;
}