#pragma once
#include "TRMiniGameAnswer.h"
class CTRMiniGameAnswer_ChoiceOX :
	public CTRMiniGameAnswer
{
public:
	CTRMiniGameAnswer_ChoiceOX();
	virtual ~CTRMiniGameAnswer_ChoiceOX();

	// CTRMiniGameAnswer��(��) ���� ��ӵ�
	virtual void Init() override;
};

