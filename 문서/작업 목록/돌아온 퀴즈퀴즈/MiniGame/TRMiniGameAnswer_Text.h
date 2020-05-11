#pragma once
#include "TRMiniGameAnswer.h"
class CTRMiniGameAnswer_Text :
	public CTRMiniGameAnswer
{
private:
	CGUIEditCtrl* m_pEdit = nullptr;
	CGUIStaticText* m_pStaticText = nullptr;
	std::string m_strText = "";

public:
	CTRMiniGameAnswer_Text() = default;
	CTRMiniGameAnswer_Text(CGUIStaticText* _pStaticText) :m_pStaticText(_pStaticText) {};
	virtual ~CTRMiniGameAnswer_Text() = default;

public:
	void InitStaticText(CGUIDialog* _pDlg, const string& _strName);
	void UpdateStaticText(CGUIStaticText* _pStaticText = nullptr);
	void ChangeStaticText(const string& _strText);

public:
	CGUIEditCtrl* GetEdit()const { return m_pEdit; }
	void SetEdit(CGUIEditCtrl* _pEdit) { m_pEdit = _pEdit; }
	__declspec(property(get = GetEdit, put = SetEdit)) CGUIEditCtrl* __pEdit;

	CGUIStaticText* GetStaticText()const { return m_pStaticText; }
	void SetStaticText(CGUIStaticText* _pStaticText) { m_pStaticText = _pStaticText; }
	__declspec(property(get = GetStaticText, put = SetStaticText)) CGUIStaticText* __pStaticText;

	const std::string& GetText()
	{
		if(m_pEdit)
		{
			m_pEdit->getText(m_strText);
		}
		return m_strText;
	}
	__declspec(property(get = GetText)) const std::string& __strText;
};

