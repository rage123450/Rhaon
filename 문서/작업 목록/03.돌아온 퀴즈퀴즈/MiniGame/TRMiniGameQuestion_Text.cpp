#include "stdafx.h"
#include "TRMiniGameQuestion_Text.h"
#include "language/UnicodeTextFile.h"

bool CTRMiniGameQuestion_Text::LoadText(ELoadTextType _eType)
{
	m_vecText.clear();
	std::vector<QUIZ_TABLE>().swap(m_vecText);
	m_vecText.reserve(MAX_QUIZ);

	switch(_eType)
	{
	case CTRMiniGameQuestion_Text::LOADTEXTTYPE_QUIZQUIZ:
		return LoadText_QuizQuiz();
	}

	return false;
}

void CTRMiniGameQuestion_Text::InitText(CGUIDialog * _pDlg, const std::string & _strName, ETextType _eTextType)
{
	m_eTextType = _eTextType;

	switch(m_eTextType)
	{
	case CTRMiniGameQuestion_Text::TEXTTYPE_STATIC:
		InitStaticText(_pDlg, _strName);
		break;

	case CTRMiniGameQuestion_Text::TEXTTYPE_FORMATED:
		InitFormatedText(_pDlg, _strName);
		break;
	}
}

void CTRMiniGameQuestion_Text::UpdateText(const int& _fdNum)
{
	if(m_vecText.empty())
	{
		return;
	}

	switch(m_eTextType)
	{
	case CTRMiniGameQuestion_Text::TEXTTYPE_STATIC:
		UpdateStaticText(GetQuizTable(_fdNum).strQuestion);
		break;

	case CTRMiniGameQuestion_Text::TEXTTYPE_FORMATED:
		UpdateFormatedText(GetQuizTable(_fdNum).strQuestion);
		break;
	}
}

void CTRMiniGameQuestion_Text::UpdateText(const int & _fdNum, float _fTimeLen)
{
	if(m_vecText.empty())
	{
		return;
	}

	switch(m_eTextType)
	{
	case CTRMiniGameQuestion_Text::TEXTTYPE_STATIC:
		UpdateStaticTextTypingEffect(GetQuizTable(_fdNum).strQuestion, _fTimeLen);
		break;

	case CTRMiniGameQuestion_Text::TEXTTYPE_FORMATED:
		break;
	}
}

int CTRMiniGameQuestion_Text::GetTextLengthUTF8(int _fdNum)
{
	if(m_vecText.empty())
	{
		return -1;
	}

	LPCTSTR pStr = GetQuizTable(_fdNum).strQuestion.c_str();
	wstring strUTF8 = CA2W(pStr);

	return strUTF8.length();
}

std::vector<int> CTRMiniGameQuestion_Text::GetTextNewLine(int _fdNum)
{
	if(m_vecText.empty())
	{
		return std::vector<int>();
	}

	vector<string> vec;
	stringstream ss(GetQuizTable(_fdNum).strQuestion);
	string token;
	while (getline(ss,token,'\n'))
	{
		vec.push_back(token);
	}

	std::vector<int> vecNewLine;
	for(auto& i : vec)
	{
		LPCTSTR pStr = i.c_str();
		wstring strUTF8 = CA2W(pStr);
		vecNewLine.push_back(strUTF8.length());
	}

	return vecNewLine;
}

std::vector<int> CTRMiniGameQuestion_Text::GetTextSentence(int _fdNum)
{
	if(m_vecText.empty())
	{
		return std::vector<int>();
	}

	m_vecChar.clear();
	m_vecChar.reserve(128);

	for(size_t i = 0; i < GetQuizTable(_fdNum).strQuestion.length(); i++)
	{
		if(isalnum(GetQuizTable(_fdNum).strQuestion[i]))
		{
			m_vecChar.push_back(0);
		}
		else if(GetQuizTable(_fdNum).strQuestion[i] < 0)
		{
			i++;
			m_vecChar.push_back(0);
		}
		else if(GetQuizTable(_fdNum).strQuestion[i]==' ')
		{
			m_vecChar.push_back(1);
		}
		else if(GetQuizTable(_fdNum).strQuestion[i]=='\n')
		{
			m_vecChar.push_back(2);
		}
		else
		{
			m_vecChar.push_back(0);
		}
	}

	return m_vecChar;
}

int CTRMiniGameQuestion_Text::GetQuizType(int _fdNum) const
{
	if(m_vecText.empty() || _fdNum < 1)
	{
		return -1;
	}

	for(auto& i : m_vecText)
	{
		if(i.nNum == _fdNum)
		{
			return i.nType;
		}
	}

	return -1;
}

const CTRMiniGameQuestion_Text::QUIZ_TABLE& CTRMiniGameQuestion_Text::GetQuizTable(int _fdNum) const
{
	if(m_vecText.empty() || _fdNum < 1)
	{
		return QUIZ_TABLE();
	}

	for(auto& i : m_vecText)
	{
		if(i.nNum == _fdNum)
		{
			return i;
		}
	}

	return QUIZ_TABLE();
}

void CTRMiniGameQuestion_Text::InitStaticText(CGUIDialog * _pDlg, const std::string & _strName)
{
	if(_pDlg)
	{
		m_pStaticText = (CGUIStaticText*)_pDlg->findControl(_strName, GUI_SUB_CONTROL_STATIC_TEXT);
		if(m_pStaticText)
		{
			m_pStaticText->setText("");
		}
	}
}

void CTRMiniGameQuestion_Text::InitFormatedText(CGUIDialog * _pDlg, const std::string & _strName)
{
	if(_pDlg)
	{
		m_pFormatedText = (CFormatedStaticText*)_pDlg->findControl(_strName, GUI_SUB_CONTROL_FORMATED_STATIC_TEXT);
		if(m_pFormatedText)
		{
			m_pFormatedText->setText("");
		}
	}
}

void CTRMiniGameQuestion_Text::UpdateStaticText(const string & _strText)
{
	if(m_pStaticText)
	{
		m_pStaticText->setVisible(true);
		m_pStaticText->setText(_strText);
	}
}

void CTRMiniGameQuestion_Text::UpdateStaticTextTypingEffect(const string & _strText, float _fTimeLen)
{
	if(m_pStaticText)
	{
		LPCTSTR pStr = _strText.c_str();
		wstring strUTF8 = CA2W(pStr);

		m_pStaticText->setVisible(true);
		m_pStaticText->setTypingEffect(_strText);
		m_pStaticText->setMessageSpeed(1.0f / (_fTimeLen*10.0f) * static_cast<float>(strUTF8.length()));
	}
}

void CTRMiniGameQuestion_Text::UpdateFormatedText(const string & _strText)
{
	if(m_pFormatedText)
	{
		m_pFormatedText->setVisible(true);
		m_pFormatedText->setText(_strText);
	}
}

bool CTRMiniGameQuestion_Text::LoadText_QuizQuiz()
{
	CTextFileToPackage filereader(true);
	if(!filereader.open("script\\Content\\EssenQuizQuiz_QuizBank.txt"))
	{
		return false;
	}

	try
	{
		boost::regex re_info(
			"(.+?),"
			"(.+?),"
			"(.+?),"
			"\"(.+?)\","
			"\"(.+?)\","
			"\"(.+?)\","
			"\"(.+?)\","
			"\"(.+?)\""
		);

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

			if(results.size() < 9)
			{
				throw exception(("[results Err]" + buf).c_str());
			}

			QUIZ_TABLE temp;
			temp.nNum = atoi(results[1].str().c_str());
			temp.nType = atoi(results[2].str().c_str());
			temp.nSubject = atoi(results[3].str().c_str());
			temp.strQuestion = results[4].str();
			temp.strFirst = results[5].str();
			temp.strSecond = results[6].str();
			temp.strThird = results[7].str();
			temp.strFourth = results[8].str();
			stringutil::replaceString(temp.strQuestion, "\\n", "\n");
			stringutil::replaceString(temp.strQuestion, "<br>", "\n");

			m_vecText.push_back(temp);
		}
	}
	catch(const std::exception& e)
	{
		TRDBG_OUTPUT_ERROR("%s - %s", __FUNCTION__, e.what());
		_ASSERTE(FALSE);
		return false;
	}

	return true;
}