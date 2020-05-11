#include "stdafx.h"
#include "TRGuildWorkshop_GuideDlg.h"

CTRGuildWorkshop_GuideDlg::CTRGuildWorkshop_GuideDlg()
{
}

CTRGuildWorkshop_GuideDlg::~CTRGuildWorkshop_GuideDlg()
{
	closeDialog();
}

void CTRGuildWorkshop_GuideDlg::showDialog()
{
	__super::showDialog();

	m_nCurIndex = 1;
	m_nCurSubIndex = 1;

	SettingStaticText(EStaticTextName::SN_TITLEMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->title);
	SettingFormatedText(EFormatedTextName::FTN_INFOMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->body);
	SettingStaticText(EStaticTextName::SN_PAGENUM, to_string(m_nCurIndex) + " / " + to_string(m_mapMaxSubIndex[m_nCurIndex]));
}

void CTRGuildWorkshop_GuideDlg::closeDialog()
{
	for(int i = 0; i < m_arrayDlg.size(); i++)
	{
		if(m_arrayDlg[i])
		{
			m_arrayDlg[i]->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
			m_arrayDlg[i] = nullptr;
		}
	}
}

void CTRGuildWorkshop_GuideDlg::LoadGuideList(CTRGuildPlanInfoLoader * pLoader)
{
	if(pLoader)
	{
		m_mapGuideList.clear();
		m_mapGuideList = pLoader->getPlantGuideList();
	}

	int nIndex = 1;
	m_mapMaxSubIndex.clear();
	for(auto& var : m_mapGuideList)
	{
		m_mapMaxSubIndex[var.first.first] += 1;

		if(var.first == make_pair(1, 1))
		{
			m_nCurIndex = var.first.first;
			m_nCurSubIndex = var.first.second;
		}
	}
}

bool CTRGuildWorkshop_GuideDlg::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	CGUIControl* pCtrl = ctrlID.findControl();

	if(pCtrl)
	{
		string name = pCtrl->getName();

		for(int i = 0; i < m_arrayButton.size(); i++)
		{
			if(m_arrayButton[i].pButton->getName() == name)
			{
				m_arrayButton[i].funcEvent();
			}
		}
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRGuildWorkshop_GuideDlg::InitName()
{
	InitGUIName({
		make_tuple<EGUIName,string>(EGUIName::GN_WORKSHOP_GUIDE,"gui/Guild/Workshop/Workshop_Guide.gui"),
		});

	InitControlName(EControl::CONTROL_BUTTON,
		{
			// Workshop_Guide
			"Close","GuideBtn1","GuideBtn2","GuideBtn3","GuideBtn4","PrevBtn","NextBtn"
		});

	InitControlName(EControl::CONTROL_STATICTEXT,
		{
			// Workshop_Guide
			"PageNum","TitleMent"/*,"InfoMent"*/
		});

	InitControlName(EControl::CONTROL_FORMATEDTEXT,
		{
			// Workshop_Guide
			"InfoMent"
		});

	InitControlName(EControl::CONTROL_FRAME,
		{
			// Workshop_Guide
			"GuideImg"
		});

	m_arrayImageName =
	{
		"gui/Guild/Workshop/Workshop_Guide_01.png",
		"gui/Guild/Workshop/Workshop_Guide_02.png",
		"gui/Guild/Workshop/Workshop_Guide_03.png",
	};
}

void CTRGuildWorkshop_GuideDlg::InitGUI()
{
	string errmsg;

	for(int i = 0; i < m_arrayDlg.size(); i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_GuideDlg::GN_WORKSHOP_GUIDE:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_WORKSHOP_GUIDE], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->centerPosition();
				m_arrayDlg[i]->setModalDialog(true);
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
				CGUIManager::getInstance().setFocus(m_arrayDlg[i]->getControlID());
				m_arrayDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
			break;
		}
	}
}

void CTRGuildWorkshop_GuideDlg::InitButton()
{
	if(m_mapGuideList.empty())
	{
		return;
	}

	for(int i = 0; i < m_arrayButton.size(); i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_GuideDlg::BN_CLOSE:
			m_arrayButton[i].pButton = static_cast<CGUIButton*>(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->
				findControl(m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_CLOSE], GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				closeDialog();
			};
			break;

		case CTRGuildWorkshop_GuideDlg::BN_GUIDEBTN1:
			m_arrayButton[i].pButton = static_cast<CGUIButton*>(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->
				findControl(m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_GUIDEBTN1], GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				m_nCurIndex = 1;
				m_nCurSubIndex = 1;
				SettingStaticText(EStaticTextName::SN_TITLEMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->title);
				SettingFormatedText(EFormatedTextName::FTN_INFOMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->body);
				SettingStaticText(EStaticTextName::SN_PAGENUM, to_string(m_nCurSubIndex) + m_strPageNumSign + to_string(m_mapMaxSubIndex[m_nCurIndex]));
				SettingGuideImage(make_pair(m_nCurIndex, m_nCurSubIndex));

				for_each(m_arrayButton.begin(), m_arrayButton.end(), [&](SButton& temp) {temp.pButton->setChecked(false); });
				m_arrayButton[BN_GUIDEBTN1].pButton->setChecked(true);
			};
			break;

		case CTRGuildWorkshop_GuideDlg::BN_GUIDEBTN2:
			m_arrayButton[i].pButton = static_cast<CGUIButton*>(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->
				findControl(m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_GUIDEBTN2], GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				m_nCurIndex = 2;
				m_nCurSubIndex = 1;
				SettingStaticText(EStaticTextName::SN_TITLEMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->title);
				SettingFormatedText(EFormatedTextName::FTN_INFOMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->body);
				SettingStaticText(EStaticTextName::SN_PAGENUM, to_string(m_nCurSubIndex) + m_strPageNumSign + to_string(m_mapMaxSubIndex[m_nCurIndex]));
				SettingGuideImage(make_pair(m_nCurIndex, m_nCurSubIndex));

				for_each(m_arrayButton.begin(), m_arrayButton.end(), [&](SButton& temp) {temp.pButton->setChecked(false); });
				m_arrayButton[BN_GUIDEBTN2].pButton->setChecked(true);
			};
			break;

		case CTRGuildWorkshop_GuideDlg::BN_GUIDEBTN3:
			m_arrayButton[i].pButton = static_cast<CGUIButton*>(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->
				findControl(m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_GUIDEBTN3], GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				m_nCurIndex = 3;
				m_nCurSubIndex = 1;
				SettingStaticText(EStaticTextName::SN_TITLEMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->title);
				SettingFormatedText(EFormatedTextName::FTN_INFOMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->body);
				SettingStaticText(EStaticTextName::SN_PAGENUM, to_string(m_nCurSubIndex) + m_strPageNumSign + to_string(m_mapMaxSubIndex[m_nCurIndex]));
				SettingGuideImage(make_pair(m_nCurIndex, m_nCurSubIndex));

				for_each(m_arrayButton.begin(), m_arrayButton.end(), [&](SButton& temp) {temp.pButton->setChecked(false); });
				m_arrayButton[BN_GUIDEBTN3].pButton->setChecked(true);
			};
			break;

		case CTRGuildWorkshop_GuideDlg::BN_GUIDEBTN4:
			m_arrayButton[i].pButton = static_cast<CGUIButton*>(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->
				findControl(m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_GUIDEBTN4], GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				m_nCurIndex = 4;
				m_nCurSubIndex = 1;
				SettingStaticText(EStaticTextName::SN_TITLEMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->title);
				SettingFormatedText(EFormatedTextName::FTN_INFOMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->body);
				SettingStaticText(EStaticTextName::SN_PAGENUM, to_string(m_nCurSubIndex) + m_strPageNumSign + to_string(m_mapMaxSubIndex[m_nCurIndex]));
				SettingGuideImage(make_pair(m_nCurIndex, m_nCurSubIndex));

				for_each(m_arrayButton.begin(), m_arrayButton.end(), [&](SButton& temp) {temp.pButton->setChecked(false); });
				m_arrayButton[BN_GUIDEBTN4].pButton->setChecked(true);
			};
			break;

		case CTRGuildWorkshop_GuideDlg::BN_PREVBTN:
			m_arrayButton[i].pButton = static_cast<CGUIButton*>(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->
				findControl(m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_PREVBTN], GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				m_nCurSubIndex = m_nCurSubIndex > 1 ? m_nCurSubIndex - 1 : m_nCurSubIndex;
				SettingFormatedText(EFormatedTextName::FTN_INFOMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->body);
				SettingStaticText(EStaticTextName::SN_PAGENUM, to_string(m_nCurSubIndex) + m_strPageNumSign + to_string(m_mapMaxSubIndex[m_nCurIndex]));
				SettingGuideImage(make_pair(m_nCurIndex, m_nCurSubIndex));
			};
			break;

		case CTRGuildWorkshop_GuideDlg::BN_NEXTBTN:
			m_arrayButton[i].pButton = static_cast<CGUIButton*>(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->
				findControl(m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BN_NEXTBTN], GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				m_nCurSubIndex = m_nCurSubIndex < m_mapMaxSubIndex[m_nCurIndex] ? m_nCurSubIndex + 1 : m_nCurSubIndex;
				SettingFormatedText(EFormatedTextName::FTN_INFOMENT, m_mapGuideList[make_pair(m_nCurIndex, m_nCurSubIndex)]->body);
				SettingStaticText(EStaticTextName::SN_PAGENUM, to_string(m_nCurSubIndex) + m_strPageNumSign + to_string(m_mapMaxSubIndex[m_nCurIndex]));
				SettingGuideImage(make_pair(m_nCurIndex, m_nCurSubIndex));
			};
			break;
		}
	}
}

void CTRGuildWorkshop_GuideDlg::InitStaticText()
{
	// Workshop_Guide
	m_arrayStaticText[EStaticTextName::SN_PAGENUM] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->
		findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_PAGENUM], GUI_SUB_CONTROL_STATIC_TEXT));

	m_arrayStaticText[EStaticTextName::SN_TITLEMENT] = static_cast<CGUIStaticText*>(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->
		findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::SN_TITLEMENT], GUI_SUB_CONTROL_STATIC_TEXT));
}

void CTRGuildWorkshop_GuideDlg::InitFormatedText()
{
	m_arrayFormatedText[EFormatedTextName::FTN_INFOMENT] = static_cast<CFormatedStaticText*>(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->
		findControl(m_arrayControlName[EControl::CONTROL_FORMATEDTEXT][EFormatedTextName::FTN_INFOMENT], GUI_SUB_CONTROL_FORMATED_STATIC_TEXT));
}

void CTRGuildWorkshop_GuideDlg::InitImageControl()
{
	if(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE])
	{
		for(int i = 0; i < EImageCtrlName::IN_END; i++)
		{
			m_arrayImageCtrl[i] = CGUIManager::getInstance().createControl<CGUIImageCtrl>(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->getControlID());
			m_arrayImageCtrl[i]->setImage(m_arrayImageName[i]);
			m_arrayImageCtrl[i]->setClientPos(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_GUIDEIMG], GUI_SUB_CONTROL_FRAME)->getClientRect());
			m_arrayImageCtrl[i]->setSrcRect(0, 0, GUIDEIMG_WIDTH, GUIDEIMG_HEIGHT);
			m_arrayImageCtrl[i]->setVisible(false);
		}
	}

	SettingGuideImage(make_pair(1, 1));

	if(m_arrayButton[BN_GUIDEBTN1].pButton)
	{
		m_arrayButton[BN_GUIDEBTN1].pButton->setChecked(true);
	}
}

void CTRGuildWorkshop_GuideDlg::SettingStaticText(EStaticTextName _eStaticText, std::string _strData)
{
	if(m_arrayStaticText[_eStaticText])
	{
		m_arrayStaticText[_eStaticText]->setText(_strData);
	}
}

void CTRGuildWorkshop_GuideDlg::SettingFormatedText(EFormatedTextName _eStaticText, std::string _strData)
{
	if (m_arrayFormatedText[_eStaticText])
	{
		m_arrayFormatedText[_eStaticText]->setText(_strData);
	}
}

void CTRGuildWorkshop_GuideDlg::SettingGuideImage(pair<int, int> _pairPage)
{
	if(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE])
	{
		for(int i = 0; i < EImageCtrlName::IN_END; i++)
		{
			m_arrayImageCtrl[i]->setVisible(false);
		}

		switch(_pairPage.first)
		{
		case 1:
			switch(_pairPage.second)
			{
			case 1:
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setImage(m_arrayImageName[EImageCtrlName::IN_GUIDE01]);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setClientPos(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_GUIDEIMG], GUI_SUB_CONTROL_FRAME)->getClientRect());
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setSrcRect(0, GUIDEIMG_Y01, GUIDEIMG_WIDTH, GUIDEIMG_HEIGHT);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setVisible(true);
				break;
			case 2:
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setImage(m_arrayImageName[EImageCtrlName::IN_GUIDE01]);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setClientPos(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_GUIDEIMG], GUI_SUB_CONTROL_FRAME)->getClientRect());
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setSrcRect(0, GUIDEIMG_Y02, GUIDEIMG_WIDTH, GUIDEIMG_HEIGHT);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setVisible(true);
				break;
			case 3:
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setImage(m_arrayImageName[EImageCtrlName::IN_GUIDE01]);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setClientPos(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_GUIDEIMG], GUI_SUB_CONTROL_FRAME)->getClientRect());
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setSrcRect(0, GUIDEIMG_Y03, GUIDEIMG_WIDTH, GUIDEIMG_HEIGHT);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE01]->setVisible(true);
				break;
			case 4:
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setImage(m_arrayImageName[EImageCtrlName::IN_GUIDE02]);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setClientPos(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_GUIDEIMG], GUI_SUB_CONTROL_FRAME)->getClientRect());
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setSrcRect(0, GUIDEIMG_Y01, GUIDEIMG_WIDTH, GUIDEIMG_HEIGHT);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setVisible(true);
				break;
			}
			break;

		case 2:
			switch(_pairPage.second)
			{
			case 1:
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setImage(m_arrayImageName[EImageCtrlName::IN_GUIDE02]);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setClientPos(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_GUIDEIMG], GUI_SUB_CONTROL_FRAME)->getClientRect());
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setSrcRect(0, GUIDEIMG_Y02, GUIDEIMG_WIDTH, GUIDEIMG_HEIGHT);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setVisible(true);
				break;
			case 2:
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setImage(m_arrayImageName[EImageCtrlName::IN_GUIDE02]);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setClientPos(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_GUIDEIMG], GUI_SUB_CONTROL_FRAME)->getClientRect());
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setSrcRect(0, GUIDEIMG_Y03, GUIDEIMG_WIDTH, GUIDEIMG_HEIGHT);
				m_arrayImageCtrl[EImageCtrlName::IN_GUIDE02]->setVisible(true);
				break;
			}
			break;

		case 3:
			m_arrayImageCtrl[EImageCtrlName::IN_GUIDE03]->setImage(m_arrayImageName[EImageCtrlName::IN_GUIDE03]);
			m_arrayImageCtrl[EImageCtrlName::IN_GUIDE03]->setClientPos(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_GUIDEIMG], GUI_SUB_CONTROL_FRAME)->getClientRect());
			m_arrayImageCtrl[EImageCtrlName::IN_GUIDE03]->setSrcRect(0, GUIDEIMG_Y01, GUIDEIMG_WIDTH, GUIDEIMG_HEIGHT);
			m_arrayImageCtrl[EImageCtrlName::IN_GUIDE03]->setVisible(true);
			break;

		case 4:
			m_arrayImageCtrl[EImageCtrlName::IN_GUIDE03]->setImage(m_arrayImageName[EImageCtrlName::IN_GUIDE03]);
			m_arrayImageCtrl[EImageCtrlName::IN_GUIDE03]->setClientPos(m_arrayDlg[EGUIName::GN_WORKSHOP_GUIDE]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_GUIDEIMG], GUI_SUB_CONTROL_FRAME)->getClientRect());
			m_arrayImageCtrl[EImageCtrlName::IN_GUIDE03]->setSrcRect(0, GUIDEIMG_Y02, GUIDEIMG_WIDTH, GUIDEIMG_HEIGHT);
			m_arrayImageCtrl[EImageCtrlName::IN_GUIDE03]->setVisible(true);
			break;
		}
	}
}
