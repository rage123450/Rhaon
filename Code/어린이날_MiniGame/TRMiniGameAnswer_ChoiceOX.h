#pragma once
#include "TRMiniGameAnswer.h"
class CTRMiniGameAnswer_ChoiceOX :
	public CTRMiniGameAnswer
{
public:
	CTRMiniGameAnswer_ChoiceOX();
	virtual ~CTRMiniGameAnswer_ChoiceOX();

	// CTRMiniGameAnswer을(를) 통해 상속됨
	virtual void Init() override;
};

