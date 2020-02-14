#pragma once
#include "TRMiniGameAnswer.h"
class CTRMiniGameAnswer_ChoiceNum :
	public CTRMiniGameAnswer
{
public:
	CTRMiniGameAnswer_ChoiceNum();
	virtual ~CTRMiniGameAnswer_ChoiceNum();

	// CTRMiniGameAnswer을(를) 통해 상속됨
	virtual void Init() override;
};

