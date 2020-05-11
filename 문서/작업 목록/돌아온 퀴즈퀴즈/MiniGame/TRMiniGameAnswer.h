#pragma once
class CTRMiniGameAnswer
{
public:
	enum EAnswerType
	{
		ANSWERTYPE_CHOICE,
		ANSWERTYPE_SHORT,
		ANSWERTYPE_END
	};

private:
	EAnswerType m_eAnswerType = EAnswerType::ANSWERTYPE_END;

public:
	CTRMiniGameAnswer() = default;
	virtual ~CTRMiniGameAnswer() = default;
};

