#pragma once
#include "TRMiniGameQuestion.h"
class CTRMiniGameQuestion_Text :
	public CTRMiniGameQuestion
{
public:
	static constexpr int MAX_QUIZ = 10;

public:
	enum ETextType
	{
		TEXTTYPE_STATIC,
		TEXTTYPE_FORMATED,
		TEXTTYPE_END
	};

	enum ELoadTextType
	{
		LOADTEXTTYPE_QUIZQUIZ,
		LOADTEXTTYPE_END
	};

public:
	typedef struct tagQuizTable
	{
		int nNum;												// ��ȣ
		int nType;												// 1:������, 2:�ְ���, 3:ox
		int nSubject;											// 1:���, 2:��ȸ, 3:�ͼ���, 4:���� 5:�׷�
		std::string strQuestion;								// ����
		std::string strFirst, strSecond, strThird, strFourth;	// ����

		tagQuizTable() :nNum(0), nType(0), nSubject(0), strQuestion(""), strFirst(""), strSecond(""), strThird(""), strFourth("")
		{}
	}QUIZ_TABLE;

private:
	ETextType m_eTextType = ETextType::TEXTTYPE_END;
	CGUIStaticText* m_pStaticText = nullptr;
	CFormatedStaticText* m_pFormatedText = nullptr;

	std::vector<QUIZ_TABLE> m_vecText;
	std::vector<int> m_vecChar;		// 0:alpha or num or kor 1:' ' 2:\n

public:
	CTRMiniGameQuestion_Text() = default;
	virtual ~CTRMiniGameQuestion_Text() = default;

public:
	bool LoadText(ELoadTextType _eType);

	void InitText(CGUIDialog* _pDlg, const std::string& _strName, ETextType _eTextType);
	void UpdateText(const int& _fdNum);
	void UpdateText(const int& _fdNum, float _fTimeLen);

	int GetTextLengthUTF8(int _fdNum);
	std::vector<int> GetTextNewLine(int _nRound);
	std::vector<int> GetTextSentence(int _nRound);

	int GetQuizType(int _fdNum)const;
	const QUIZ_TABLE& GetQuizTable(int _fdNum)const;

private:
	void InitStaticText(CGUIDialog* _pDlg, const std::string& _strName);
	void InitFormatedText(CGUIDialog* _pDlg, const std::string& _strName);

	void UpdateStaticText(const string& _strText);
	void UpdateStaticTextTypingEffect(const string& _strText,float _fTimeLen);
	void UpdateFormatedText(const string& _strText);

	bool LoadText_QuizQuiz();

public:
	reference_wrapper<const ETextType> GetTextType()const { return cref(m_eTextType); }
	__declspec(property(get = GetTextType)) reference_wrapper<const ETextType> __eTextType;

	CGUIStaticText* GetStaticText()const { return m_pStaticText; }
	void SetStaticText(CGUIStaticText* _pStaticText) { m_eTextType = TEXTTYPE_STATIC; m_pStaticText = _pStaticText; }
	__declspec(property(get = GetStaticText, put = SetStaticText)) CGUIStaticText* __pStaticText;

	CFormatedStaticText* GetFormatedText()const { return m_pFormatedText; }
	void SetFormatedText(CFormatedStaticText* _pFormatedText) { m_eTextType = TEXTTYPE_FORMATED; m_pFormatedText = _pFormatedText; }
	__declspec(property(get = GetFormatedText, put = SetFormatedText)) CFormatedStaticText* __pFormatedText;

	std::reference_wrapper<const std::vector<QUIZ_TABLE>> GetText()const { return cref(m_vecText); }
	__declspec(property(get = GetText)) std::reference_wrapper<const std::vector<QUIZ_TABLE>> __vecText;
};

