#include "stdafx.h"
#include "TRMiniGameQuestion_NpcView.h"
#include "language/UnicodeTextFile.h"
#include "gui/GUIObjectView.h"

bool CTRMiniGameQuestion_NpcView::LoadMent(const std::string & strFileName)
{
	CTextFileToPackage filereader(true);
	if(!filereader.open(strFileName))
	{
		return false;
	}

	try
	{
		boost::regex re_info(
			"(.+?),"
			"(.+?),"
			"(.+?),"
			"\"(.+?)\"");

		std::string buf;

		while(filereader.getLine(buf))
		{
			stringutil::strip(buf);

			// 빈줄은 걸러낸다.
			if(buf.empty())
			{
				continue;
			}

			// 주석은 걸러낸다.
			if(stringutil::startswith(buf, "//"))
			{
				continue;
			}

			// 정규식으로 파싱한다.
			boost::smatch results;
			boost::regex_match(buf, results, re_info);

			if(results.size() != 5)
			{
				throw exception(("[results Err]" + buf).c_str());
			}

			pair<tuple<int, int, int>, string> pairTemp;
			get<0>(pairTemp.first) = atoi(results[1].str().c_str());
			get<1>(pairTemp.first) = atoi(results[2].str().c_str());
			get<2>(pairTemp.first) = atoi(results[3].str().c_str());
			pairTemp.second = results[4].str();

			m_mapMent.emplace(pairTemp);
		}
	}
	catch(const std::exception& e)
	{
		TRDBG_OUTPUT_ERROR("LoadNPCMent - %s", e.what());
		_ASSERTE(FALSE);
		return false;
	}

	return true;
}

void CTRMiniGameQuestion_NpcView::InitNpcView(CGUIDialog * _pDlg, std::string _strCtrlName, std::string _strModelName, std::string _strAnimationName, std::tuple<float, float> _tupleRadius, float _fFovy)
{
	m_pDiceViewCtrl = static_cast<CGUIUserControl*>(_pDlg->findControl(_strCtrlName, GUI_SUB_CONTROL_USER_CTRL));

	if(m_pDiceViewCtrl && !_strModelName.empty())
	{
		GUI_OBJECT::createEffectView(&m_diceObjView, m_pDiceViewCtrl, _strModelName);
		GUI_OBJECT::setFovy(&m_diceObjView, _fFovy);
		GUI_OBJECT::setAnimation(&m_diceObjView, format(_strAnimationName.c_str()), true);
		GUI_OBJECT::setRadius(&m_diceObjView, get<0>(_tupleRadius), get<1>(_tupleRadius));
	}
}

void CTRMiniGameQuestion_NpcView::UpdateNpcView(float fElapsed)
{
	m_diceObjView.frameMove(fElapsed);
}

void CTRMiniGameQuestion_NpcView::ChangeNpcView(string _strPartGroupName, string _strAnimationName)
{
	GUI_OBJECT::setPartGroup(&m_diceObjView, format(_strPartGroupName.c_str()));
	GUI_OBJECT::setPopAnimation(&m_diceObjView, format(_strAnimationName.c_str()));
}
