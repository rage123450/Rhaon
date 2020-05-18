#pragma once
#include "TRMiniGameAnswer.h"
class CTRMiniGameAnswer_StringAnswer :
	public CTRMiniGameAnswer
{
public:
	CTRMiniGameAnswer_StringAnswer();
	virtual ~CTRMiniGameAnswer_StringAnswer();

public:
	// CTRMiniGameAnswer을(를) 통해 상속됨
	virtual void Init() override;
};

