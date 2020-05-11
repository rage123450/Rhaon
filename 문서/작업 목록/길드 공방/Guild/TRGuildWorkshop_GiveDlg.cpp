#include "stdafx.h"
#include "TRGuildWorkshop_GiveDlg.h"
//
#include "language/LanguageHeader.h"
#include "NetClientManager.h"
#include "gui/GUIItemImageCtrl.h"
#include "gameui/ClientItemInfoLoader.h"
#include "gameui/TRShortTimeMessage.h"
#include "game/TRRewardManager.h"

CTRGuildWorkshop_GiveDlg::CTRGuildWorkshop_GiveDlg()
{
}

CTRGuildWorkshop_GiveDlg::~CTRGuildWorkshop_GiveDlg()
{
	closeDialog();
}

void CTRGuildWorkshop_GiveDlg::showDialog()
{
	__super::showDialog();

	m_bStart = true;

	map<eGuildPlantGiveCondition, bool> mapCheck;
	mapCheck.insert(make_pair<eGuildPlantGiveCondition, bool>(eGuildPlantGiveCondition_CONTRIBUTE, false));
	mapCheck.insert(make_pair<eGuildPlantGiveCondition, bool>(eGuildPlantGiveCondition_CLASS, false));
	mapCheck.insert(make_pair<eGuildPlantGiveCondition, bool>(eGuildPlantGiveCondition_JOIN, false));
	mapCheck.insert(make_pair<eGuildPlantGiveCondition, bool>(eGuildPlantGiveCondition_INVEST, false));
	CNetClientManager::getInstance().requestGetGuildPlantItemGivePossibleUserList(m_sGuildPlantMakeInfo.m_iItemIndexNum, mapCheck);

	InitSelectDlg();
}

void CTRGuildWorkshop_GiveDlg::closeDialog()
{
	m_bStart = false;

	m_yesNoDlg.closeDialog();

	for(int i = 0; i < m_arrayDlg.size(); i++)
	{
		if(m_arrayDlg[i])
		{
			m_arrayDlg[i]->setAnimator(new CGUIAnimatorFadeOutRemove(0.25f));
			m_arrayDlg[i] = nullptr;
		}
	}
}


bool CTRGuildWorkshop_GiveDlg::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	string name;

	CGUIControl* pCtrl = ctrlID.findControl();
	if(pCtrl)
	{
		name = pCtrl->getName();
		for each (SButtonEvent var in m_arrayButtonEvent)
		{
			if(var.strName == name)
			{
				var.funcEvent();
			}
		}
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRGuildWorkshop_GiveDlg::InitName()
{
	InitGUIName(
		{
			make_tuple<EGUIName, string>(EGUIName::GN_GIVEPOPUP, "gui/Guild/Workshop/Workshop_GivePopup.gui"),
			make_tuple<EGUIName, string>(EGUIName::GN_SELECTITEMDLG, "gui/Guild/Workshop/Workshop_SelectItemDlg.gui")
		});

	InitControlName(EControl::CONTROL_BUTTON,
		{
			// GivePopup
			"Close","GiveBtn","Option1Btn","Option2Btn","Option3Btn","Option4Btn","InBtn","OutBtn"
		});

	InitControlName(EControl::CONTROL_STATICTEXT,
		{
			// GivePopup
			"Title","Option1","Option2","Option3","Option4",
			// SelectItemDlg
			"GoodsName","Day","TypeMent"
		});

	InitControlName(EControl::CONTROL_IMAGECONTROL,
		{
			// GivePopup
			"Base",
			// SelectItemDlg
			"Image","Base"
		});

	InitControlName(EControl::CONTROL_FRAME,
		{
			// GivePopup
			"Workshop_SelectItemDlg"
		});

	InitControlName(EControl::CONTROL_LISTBOX,
		{
			// GivePopup
			"PossibleMember","ReceiveMember"
		});
}

void CTRGuildWorkshop_GiveDlg::InitGUI()
{
	string errmsg;

	for(int i = 0; i < EDialog::DLG_END; i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_GiveDlg::DLG_GIVEPOPUP:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_GIVEPOPUP], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->centerPosition();
				m_arrayDlg[i]->setModalDialog(true);
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
				CGUIManager::getInstance().setFocus(m_arrayDlg[i]->getControlID());
				m_arrayDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
			break;

		case CTRGuildWorkshop_GiveDlg::DLG_SELECTITEMDLG:
			m_arrayDlg[i] = CTRUserInterface::loadGUI(m_mapGUIName[EGUIName::GN_SELECTITEMDLG], errmsg);
			if(m_arrayDlg[i])
			{
				m_arrayDlg[i]->setClientPos(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayControlName[EControl::CONTROL_FRAME][EFrameName::FN_WORKSHOP_SELECTITEMDLG], GUI_SUB_CONTROL_FRAME)->getScreenRect());
				m_arrayDlg[i]->setDialogListener(getCommandTargetID());
				m_arrayDlg[i]->setAnimator(new CGUIAnimatorFadeInTransparency(0.25f, 0.1f, 1.f, true));
			}
			break;
		}
	}
}

void CTRGuildWorkshop_GiveDlg::InitButton()
{
	for(int i = 0; i < m_arrayButtonEvent.size(); i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_GiveDlg::BUTTON_CLOSE:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BUTTON_CLOSE];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				closeDialog();
			};
			break;

		case CTRGuildWorkshop_GiveDlg::BUTTON_GIVE:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BUTTON_GIVE];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				if(m_arrayListBox[EListBoxName::LB_RECEIVEMEMBER].vecName.size() > 0)
				{
					m_yesNoDlg.showDialog(_STR(GUILD_PLANT_NO_CANCLE_ITEM), this, &CTRGuildWorkshop_GiveDlg::showGiveYes, nullptr);
				}
				else
				{
					CTRShortTimeMessage::getInstance().showMessage(_STR(GUILD_PLANT_GIVE_MEMBER_PLEASE));
				}
			};
			break;

		case CTRGuildWorkshop_GiveDlg::BUTTON_OPTION1:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BUTTON_OPTION1];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				m_arrayButton[EButtonName::BUTTON_OPTION1]->setChecked(m_arrayButton[EButtonName::BUTTON_OPTION1]->isChecked() ? false : true);
				UpdateListBox(m_arrayListBox[EListBoxName::LB_POSSIBLEMEMBER]);
				ClearListBox(m_arrayListBox[EListBoxName::LB_RECEIVEMEMBER]);
				CNetClientManager::getInstance().requestGetGuildPlantItemGivePossibleUserList(m_sGuildPlantMakeInfo.m_iItemIndexNum, GetConditionCheck());
			};
			break;

		case CTRGuildWorkshop_GiveDlg::BUTTON_OPTION2:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BUTTON_OPTION2];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				m_arrayButton[EButtonName::BUTTON_OPTION2]->setChecked(m_arrayButton[EButtonName::BUTTON_OPTION2]->isChecked() ? false : true);
				UpdateListBox(m_arrayListBox[EListBoxName::LB_POSSIBLEMEMBER]);
				ClearListBox(m_arrayListBox[EListBoxName::LB_RECEIVEMEMBER]);
				CNetClientManager::getInstance().requestGetGuildPlantItemGivePossibleUserList(m_sGuildPlantMakeInfo.m_iItemIndexNum, GetConditionCheck());
			};
			break;

		case CTRGuildWorkshop_GiveDlg::BUTTON_OPTION3:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BUTTON_OPTION3];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				m_arrayButton[EButtonName::BUTTON_OPTION3]->setChecked(m_arrayButton[EButtonName::BUTTON_OPTION3]->isChecked() ? false : true);
				UpdateListBox(m_arrayListBox[EListBoxName::LB_POSSIBLEMEMBER]);
				ClearListBox(m_arrayListBox[EListBoxName::LB_RECEIVEMEMBER]);
				CNetClientManager::getInstance().requestGetGuildPlantItemGivePossibleUserList(m_sGuildPlantMakeInfo.m_iItemIndexNum, GetConditionCheck());
			};
			break;

		case CTRGuildWorkshop_GiveDlg::BUTTON_OPTION4:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BUTTON_OPTION4];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				m_arrayButton[EButtonName::BUTTON_OPTION4]->setChecked(m_arrayButton[EButtonName::BUTTON_OPTION4]->isChecked() ? false : true);
				UpdateListBox(m_arrayListBox[EListBoxName::LB_POSSIBLEMEMBER]);
				ClearListBox(m_arrayListBox[EListBoxName::LB_RECEIVEMEMBER]);
				CNetClientManager::getInstance().requestGetGuildPlantItemGivePossibleUserList(m_sGuildPlantMakeInfo.m_iItemIndexNum, GetConditionCheck());
			};
			break;

		case CTRGuildWorkshop_GiveDlg::BUTTON_IN:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BUTTON_IN];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				ChangeListBox(m_arrayListBox[EListBoxName::LB_POSSIBLEMEMBER], m_arrayListBox[EListBoxName::LB_RECEIVEMEMBER]);
			};
			break;

		case CTRGuildWorkshop_GiveDlg::BUTTON_OUT:
			m_arrayButtonEvent[i].strName = m_arrayControlName[EControl::CONTROL_BUTTON][EButtonName::BUTTON_OUT];
			m_arrayButtonEvent[i].funcEvent = [&]()
			{
				ChangeListBox(m_arrayListBox[EListBoxName::LB_RECEIVEMEMBER], m_arrayListBox[EListBoxName::LB_POSSIBLEMEMBER]);
			};
			break;
		}
	}

	for(int i = 0; i < EButtonName::BUTTON_END; i++)
	{
		m_arrayButton[i] = static_cast<CGUIButton*>(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayButtonEvent[i].strName, GUI_SUB_CONTROL_IMAGE_BUTTON));
	}
}

void CTRGuildWorkshop_GiveDlg::InitStaticText()
{
	for(int i = 0; i < EStaticTextName::ST_END; i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_GiveDlg::ST_TITLE:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::ST_TITLE], GUI_SUB_CONTROL_STATIC_TEXT));
			break;
		case CTRGuildWorkshop_GiveDlg::ST_OPTION1:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::ST_OPTION1], GUI_SUB_CONTROL_STATIC_TEXT));
			m_arrayStaticText[i]->setText(_STR(GUILD_PLANT_GIVE_CONDITION_1));	//
			break;
		case CTRGuildWorkshop_GiveDlg::ST_OPTION2:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::ST_OPTION2], GUI_SUB_CONTROL_STATIC_TEXT));
			m_arrayStaticText[i]->setText(_STR(GUILD_PLANT_GIVE_CONDITION_2));
			break;
		case CTRGuildWorkshop_GiveDlg::ST_OPTION3:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::ST_OPTION3], GUI_SUB_CONTROL_STATIC_TEXT));
			m_arrayStaticText[i]->setText(_STR(GUILD_PLANT_GIVE_CONDITION_3));
			break;
		case CTRGuildWorkshop_GiveDlg::ST_OPTION4:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::ST_OPTION4], GUI_SUB_CONTROL_STATIC_TEXT));
			m_arrayStaticText[i]->setText(_STR(GUILD_PLANT_GIVE_CONDITION_4));
			break;
		case CTRGuildWorkshop_GiveDlg::ST_SELECTITEM_GOODSNAME:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrayDlg[EDialog::DLG_SELECTITEMDLG]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::ST_SELECTITEM_GOODSNAME], GUI_SUB_CONTROL_STATIC_TEXT));
			m_arrayStaticText[i]->setVisible(false);
			break;
		case CTRGuildWorkshop_GiveDlg::ST_SELECTITEM_DAY:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrayDlg[EDialog::DLG_SELECTITEMDLG]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::ST_SELECTITEM_DAY], GUI_SUB_CONTROL_STATIC_TEXT));
			m_arrayStaticText[i]->setVisible(false);
			break;
		case CTRGuildWorkshop_GiveDlg::ST_SELECTITEM_TYPEMENT:
			m_arrayStaticText[i] = static_cast<CGUIStaticText*>(m_arrayDlg[EDialog::DLG_SELECTITEMDLG]->findControl(m_arrayControlName[EControl::CONTROL_STATICTEXT][EStaticTextName::ST_SELECTITEM_TYPEMENT], GUI_SUB_CONTROL_STATIC_TEXT));
			break;
		}
	}
}

void CTRGuildWorkshop_GiveDlg::InitImageControl()
{
	for(int i = 0; i < EImageControlName::IC_END; ++i)
	{
		switch(i)
		{
		case CTRGuildWorkshop_GiveDlg::IC_BASE:
			m_arrayImageControl[i] = static_cast<CGUIImageCtrl*>(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::IC_BASE], GUI_SUB_CONTROL_IMAGE_CTRL));
			break;
		case CTRGuildWorkshop_GiveDlg::IC_SELECTITEM_IMAGE:
			m_arrayImageControl[i] = static_cast<CGUIImageCtrl*>(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::IC_SELECTITEM_IMAGE], GUI_SUB_CONTROL_IMAGE_CTRL));
			break;
		case CTRGuildWorkshop_GiveDlg::IC_SELECTITEM_BASE:
			m_arrayImageControl[i] = static_cast<CGUIImageCtrl*>(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::IC_SELECTITEM_BASE], GUI_SUB_CONTROL_IMAGE_CTRL));
			break;
		}
	}

	m_pSelectItemImageCtrl = static_cast<CGUIItemImageCtrl*>(m_arrayDlg[EDialog::DLG_SELECTITEMDLG]->findControl(m_arrayControlName[EControl::CONTROL_IMAGECONTROL][EImageControlName::IC_SELECTITEM_IMAGE], GUI_SUB_CONTROL_ITEM_IMAGE_CTRL));
}

void CTRGuildWorkshop_GiveDlg::InitListBox()
{
	for(int i = 0; i < EListBoxName::LB_END; ++i)
	{
		switch(i)
		{
		case CTRGuildWorkshop_GiveDlg::LB_POSSIBLEMEMBER:
			m_arrayListBox[i].pListBox = static_cast<CGUIListBox*>(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayControlName[EControl::CONTROL_LISTBOX][EListBoxName::LB_POSSIBLEMEMBER], GUI_SUB_CONTROL_LIST_BOX));
			break;

		case CTRGuildWorkshop_GiveDlg::LB_RECEIVEMEMBER:
			m_arrayListBox[i].pListBox = static_cast<CGUIListBox*>(m_arrayDlg[EDialog::DLG_GIVEPOPUP]->findControl(m_arrayControlName[EControl::CONTROL_LISTBOX][EListBoxName::LB_RECEIVEMEMBER], GUI_SUB_CONTROL_LIST_BOX));
			break;
		}
	}

	InitListBoxCondition();
}

void CTRGuildWorkshop_GiveDlg::InitListBoxCondition()
{
	for(int i = 0; i < EListBoxCondition::LBC_END; i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_GiveDlg::LBC_01:
			m_arrayListBoxCondition[i] = [](string _strName, bool _bCheck)
			{
				bool bCheck = !_bCheck ? false : true;
				return true;
			};
			break;

		case CTRGuildWorkshop_GiveDlg::LBC_02:
			m_arrayListBoxCondition[i] = [](string _strName, bool _bCheck)
			{
				bool bCheck = !_bCheck ? false : true;
				return true;
			};
			break;

		case CTRGuildWorkshop_GiveDlg::LBC_03:
			m_arrayListBoxCondition[i] = [](string _strName, bool _bCheck)
			{
				bool bCheck = !_bCheck ? false : true;
				return true;
			};
			break;

		case CTRGuildWorkshop_GiveDlg::LBC_04:
			m_arrayListBoxCondition[i] = [](string _strName, bool _bCheck)
			{
				bool bCheck = !_bCheck ? false : true;
				return true;
			};
			break;
		}
	}
}

void CTRGuildWorkshop_GiveDlg::onRecvGuildPlantGetGivePossibleUserListOK(std::vector<std::string> userList)
{
	if(!m_bStart)
	{
		return;
	}

	m_userList.clear();

	if(userList.size() > 0)
	{
		m_userList.assign(userList.begin(), userList.end());
	}

	UpdateListBox(m_arrayListBox[EListBoxName::LB_POSSIBLEMEMBER]);
}

void CTRGuildWorkshop_GiveDlg::showGiveYes()
{
	CNetClientManager::getInstance().requestGiftGuildPlantItem(m_sGuildPlantMakeInfo.m_iItemIndexNum, m_arrayListBox[EListBoxName::LB_RECEIVEMEMBER].vecName);
	CTRShortTimeMessage::getInstance().showMessage(_STR(GUILD_PLANT_GIFT_ITEM));

	CNetClientManager::getInstance().requestGetGuildPlantMakeStandbyItemList();
	CNetClientManager::getInstance().requestGetGuildPlantProgressItem();

	CTRRewardManager::getInstance().getReward(eRewardCondition_ITEM, m_sGuildPlantMakeInfo.m_iItemDescNum, 1, true);

	m_arrayListBox[EListBoxName::LB_RECEIVEMEMBER].vecName.clear();

	closeDialog();
}

void CTRGuildWorkshop_GiveDlg::UpdateListBox(SListBox & _sListBox)
{
	_sListBox.pListBox->removeAll();

	_sListBox.vecName.clear();
	_sListBox.vecName.assign(m_userList.begin(), m_userList.end());

	for each (auto var in _sListBox.vecName)
	{
		_sListBox.pListBox->addItem(var);
	}
}

void CTRGuildWorkshop_GiveDlg::ChangeListBox(SListBox & _sFromListBox, SListBox & _sToListBox)
{
	if(!_sFromListBox.pListBox || !_sToListBox.pListBox)
	{
		return;
	}

	int nSelectNum = _sFromListBox.pListBox->getSelectedIndex();
	if(nSelectNum == -1)
	{
		return;
	}

	string strName = _sFromListBox.vecName[nSelectNum];
	if(find(_sFromListBox.vecName.begin(), _sFromListBox.vecName.end(), strName) != _sFromListBox.vecName.end())
	{
		_sToListBox.vecName.emplace_back(strName);
		_sToListBox.pListBox->addItem(strName);

		auto iter = _sFromListBox.vecName.begin();
		while(iter != _sFromListBox.vecName.end())
		{
			if((*iter) == strName)
			{
				iter = _sFromListBox.vecName.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		_sFromListBox.pListBox->remove(_sFromListBox.pListBox->getSelectedIndex(), 1);
	}
}

void CTRGuildWorkshop_GiveDlg::ClearListBox(SListBox & _sListBox)
{
	_sListBox.pListBox->removeAll();

	_sListBox.vecName.clear();
	std::vector<std::string>().swap(_sListBox.vecName);
}

map<eGuildPlantGiveCondition, bool> CTRGuildWorkshop_GiveDlg::GetConditionCheck()
{
	map<eGuildPlantGiveCondition, bool> mapCheck;
	for(int i = EButtonName::BUTTON_OPTION1; i <= EButtonName::BUTTON_OPTION4; i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_GiveDlg::BUTTON_OPTION1:
			mapCheck.insert(make_pair<eGuildPlantGiveCondition, bool>(eGuildPlantGiveCondition_CONTRIBUTE, m_arrayButton[i]->isChecked()));
			break;
		case CTRGuildWorkshop_GiveDlg::BUTTON_OPTION2:
			mapCheck.insert(make_pair<eGuildPlantGiveCondition, bool>(eGuildPlantGiveCondition_CLASS, m_arrayButton[i]->isChecked()));
			break;
		case CTRGuildWorkshop_GiveDlg::BUTTON_OPTION3:
			mapCheck.insert(make_pair<eGuildPlantGiveCondition, bool>(eGuildPlantGiveCondition_JOIN, m_arrayButton[i]->isChecked()));
			break;
		case CTRGuildWorkshop_GiveDlg::BUTTON_OPTION4:
			mapCheck.insert(make_pair<eGuildPlantGiveCondition, bool>(eGuildPlantGiveCondition_INVEST, m_arrayButton[i]->isChecked()));
			break;
		}
	}

	return mapCheck;
}

void CTRGuildWorkshop_GiveDlg::InitSelectDlg()
{
	if(m_arrayDlg[EDialog::DLG_SELECTITEMDLG])
	{
		const CItemInfoNode* pItemInfo = CClientItemList::getInstance().getRealItemInfo(m_sGuildPlantMakeInfo.m_iItemDescNum);

		m_pSelectItemImageCtrl->setItemImage(m_sGuildPlantMakeInfo.m_iItemDescNum);

		m_arrayStaticText[EStaticTextName::ST_SELECTITEM_GOODSNAME]->setText(pItemInfo->m_name);
		m_arrayStaticText[EStaticTextName::ST_SELECTITEM_GOODSNAME]->setVisible(true);

		m_arrayStaticText[EStaticTextName::ST_SELECTITEM_DAY]->setText(GetSelectDay(m_iFinishDate));
		m_arrayStaticText[EStaticTextName::ST_SELECTITEM_DAY]->setVisible(true);
	}
}
