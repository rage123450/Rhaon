#pragma once
class CTRMiniGameQuestion
{
public:
	enum EQuestionType
	{
		QUESTIONTYPE_QUIZ,
		QUESTIONTYPE_NPCVIEW,
		QUESTIONTYPE_END
	};

private:
	EQuestionType m_eQuestionType = EQuestionType::QUESTIONTYPE_END;

public:
	CTRMiniGameQuestion() = default;
	virtual ~CTRMiniGameQuestion() = default;
};

