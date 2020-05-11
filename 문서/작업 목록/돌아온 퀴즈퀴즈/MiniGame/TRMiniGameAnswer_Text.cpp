#include "stdafx.h"
#include "TRMiniGameAnswer_Text.h"

void CTRMiniGameAnswer_Text::InitStaticText(CGUIDialog* _pDlg, const string& _strName)
{
	if(_pDlg)
	{
		m_pStaticText = (CGUIStaticText*)_pDlg->findControl(_strName, GUI_SUB_CONTROL_STATIC_TEXT);
	}
}

void CTRMiniGameAnswer_Text::UpdateStaticText(CGUIStaticText* _pStaticText)
{
	if(_pStaticText)
	{
		_pStaticText->setText(GetText());
	}
	else if(m_pStaticText)
	{
		m_pStaticText->setText(GetText());
	}
}

void CTRMiniGameAnswer_Text::ChangeStaticText(const string& _strText)
{
	if(m_pStaticText)
	{
		m_pStaticText->setText(_strText);
	}
}
