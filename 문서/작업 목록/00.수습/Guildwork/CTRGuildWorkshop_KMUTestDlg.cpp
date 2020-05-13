#include "stdafx.h"
#include "CTRGuildWorkshop_KMUTestDlg.h"

CTRGuildWorkshop_KMUTestDlg::CTRGuildWorkshop_KMUTestDlg()
{
}

CTRGuildWorkshop_KMUTestDlg::~CTRGuildWorkshop_KMUTestDlg()
{
}

bool CTRGuildWorkshop_KMUTestDlg::onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)
{
	string name;

	CGUIControl* pCtrl = ctrlID.findControl();
	if(pCtrl)
	{
		name = pCtrl->getName();
		for each (auto var in m_arrayButton)
		{
			if(var.strName == name)
			{
				var.funcEvent();
			}
		}
	}

	return __super::onButtonClick(ctrlID, cmdID);
}

void CTRGuildWorkshop_KMUTestDlg::showDialog()
{
	closeDialog();

	string errmsg;
	m_pDlg = CTRUserInterface::loadGUI("gui/Guild/Workshop_GivePopupTest.gui", errmsg);
	if(m_pDlg)
	{
		m_pDlg->setZOrder(-1.f);
		m_pDlg->centerPosition();
		m_pDlg->setModalDialog(true);
		m_pDlg->setDialogListener(getCommandTargetID());
		CGUIManager::getInstance().setFocus(m_pDlg->getControlID());
		CTRUserInterface::getInstance().setGUIAnimatorPopupShow(m_pDlg, true);
	}

	if(!Init())
	{
		DBG_OUTPUT("CTRGuildWorkshop_GiveDlg Init Error!");
	}
}

void CTRGuildWorkshop_KMUTestDlg::closeDialog()
{
	if(m_pDlg)
	{
		CTRUserInterface::getInstance().setGUIAnimatorPopupHide(m_pDlg);
		m_pDlg = nullptr;
	}
}

bool CTRGuildWorkshop_KMUTestDlg::Init()
{
	if(!InitButton())
	{
		DBG_OUTPUT("CTRGuildWorkshop_GiveDlg InitButton Error!");
		return false;
	}

	if(!InitListBox())
	{
		DBG_OUTPUT("CTRGuildWorkshop_GiveDlg InitListBox Error!");
		return false;
	}

	return true;
}

bool CTRGuildWorkshop_KMUTestDlg::InitButton()
{
	if(m_pDlg == nullptr)
	{
		return false;
	}

	for(int i = 0; i < EButton::BUTTON_END; i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_KMUTestDlg::BUTTON_CLOSE:
			m_arrayButton[i].strName = "CloseBtn";
			m_arrayButton[i].pGUI = static_cast<CGUIButton*>(m_pDlg->findControl(m_arrayButton[i].strName, GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				closeDialog();
			};
			break;

		case CTRGuildWorkshop_KMUTestDlg::BUTTON_OPTION1:
			m_arrayButton[i].strName = "Option1Btn";
			m_arrayButton[i].pGUI = static_cast<CGUIButton*>(m_pDlg->findControl(m_arrayButton[i].strName, GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				m_arrayButton[EButton::BUTTON_OPTION1].pGUI->setChecked(m_arrayButton[EButton::BUTTON_OPTION1].pGUI->isChecked() ? false : true);
				UpdateListBox(m_arrayButton[EButton::BUTTON_OPTION1], m_arrayListBox[EListBox::LB_LISTBOX1], EBitListBox::BLB_01, [](int nTemp) {return (nTemp % 2 == 0 && nTemp != 2); });
			};
			break;

		case CTRGuildWorkshop_KMUTestDlg::BUTTON_OPTION2:
			m_arrayButton[i].strName = "Option2Btn";
			m_arrayButton[i].pGUI = static_cast<CGUIButton*>(m_pDlg->findControl(m_arrayButton[i].strName, GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				m_arrayButton[EButton::BUTTON_OPTION2].pGUI->setChecked(m_arrayButton[EButton::BUTTON_OPTION2].pGUI->isChecked() ? false : true);
				UpdateListBox(m_arrayButton[EButton::BUTTON_OPTION2], m_arrayListBox[EListBox::LB_LISTBOX1], EBitListBox::BLB_02, [](int nTemp) {return (nTemp % 3 == 0 && nTemp != 3); });
			};
			break;

		case CTRGuildWorkshop_KMUTestDlg::BUTTON_OPTION3:
			m_arrayButton[i].strName = "Option3Btn";
			m_arrayButton[i].pGUI = static_cast<CGUIButton*>(m_pDlg->findControl(m_arrayButton[i].strName, GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				m_arrayButton[EButton::BUTTON_OPTION3].pGUI->setChecked(m_arrayButton[EButton::BUTTON_OPTION3].pGUI->isChecked() ? false : true);
				UpdateListBox(m_arrayButton[EButton::BUTTON_OPTION3], m_arrayListBox[EListBox::LB_LISTBOX1], EBitListBox::BLB_03, [](int nTemp) {return (nTemp % 5 == 0 && nTemp != 5); });
			};
			break;

		case CTRGuildWorkshop_KMUTestDlg::BUTTON_OPTION4:
			m_arrayButton[i].strName = "Option4Btn";
			m_arrayButton[i].pGUI = static_cast<CGUIButton*>(m_pDlg->findControl(m_arrayButton[i].strName, GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				m_arrayButton[EButton::BUTTON_OPTION4].pGUI->setChecked(m_arrayButton[EButton::BUTTON_OPTION4].pGUI->isChecked() ? false : true);
				UpdateListBox(m_arrayButton[EButton::BUTTON_OPTION4], m_arrayListBox[EListBox::LB_LISTBOX1], EBitListBox::BLB_04, [](int nTemp) {return (nTemp % 7 == 0 && nTemp != 7); });
			};
			break;

		case CTRGuildWorkshop_KMUTestDlg::BUTTON_OPTION5:
			m_arrayButton[i].strName = "Option5Btn";
			m_arrayButton[i].pGUI = static_cast<CGUIButton*>(m_pDlg->findControl(m_arrayButton[i].strName, GUI_SUB_CONTROL_IMAGE_BUTTON));
			m_arrayButton[i].funcEvent = [&]()
			{
				m_arrayButton[EButton::BUTTON_OPTION5].pGUI->setChecked(m_arrayButton[EButton::BUTTON_OPTION5].pGUI->isChecked() ? false : true);
				UpdateListBox(m_arrayButton[EButton::BUTTON_OPTION5], m_arrayListBox[EListBox::LB_LISTBOX1], EBitListBox::BLB_05, [](int nTemp) {return (nTemp % 11 == 0 && nTemp != 11); });
			};
			break;
		}
	}

	return true;
}

bool CTRGuildWorkshop_KMUTestDlg::InitListBox()
{
	if(m_pDlg == nullptr)
	{
		return false;
	}

	for(int i = 0; i < EListBox::LB_END; i++)
	{
		switch(i)
		{
		case CTRGuildWorkshop_KMUTestDlg::LB_LISTBOX1:
			m_arrayListBox[i].strName = "ListBox1";
			m_arrayListBox[i].pGUI = static_cast<CGUIListBox*>(m_pDlg->findControl(m_arrayListBox[i].strName, GUI_SUB_CONTROL_LIST_BOX));

			for(int j = 0; j < MAX_TEST_DATANUM; ++j)
			{
				m_arrayListBox[i].vecResult.push_back(make_pair(j, EBitListBox::BLB_00));
				m_arrayListBox[i].pGUI->addItem(to_string(j));
			}
			break;
		}
	}

	return true;
}

void CTRGuildWorkshop_KMUTestDlg::UpdateListBox(SButton& _sButton, SListBox& _sListBox, EBitListBox _eBit, function<bool(int)> _funcObj)
{
	if(_sButton.pGUI->isChecked())
	{
		for(int i = 0; i < _sListBox.vecResult.size(); i++)
		{
			int nTemp = _sListBox.vecResult[i].first;
			if(_funcObj(nTemp))
			{
				_sListBox.vecResult[i].second.set(static_cast<int>(_eBit), true);
				int a = 1;
			}
		}
	}
	else
	{
		for(int i = 0; i < _sListBox.vecResult.size(); i++)
		{
			_sListBox.vecResult[i].second.set(static_cast<int>(_eBit), false);
		}
	}

	_sListBox.pGUI->removeAll();
	for(auto var : _sListBox.vecResult)
	{
		if(!var.second.any())
		{
			_sListBox.pGUI->addItem(to_string(var.first));
		}
	}
}
