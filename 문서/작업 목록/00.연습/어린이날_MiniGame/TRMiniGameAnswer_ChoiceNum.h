#pragma once
#include "TRMiniGameAnswer.h"
class CTRMiniGameAnswer_ChoiceNum :
	public CTRMiniGameAnswer
{
public:
	CTRMiniGameAnswer_ChoiceNum();
	virtual ~CTRMiniGameAnswer_ChoiceNum();

	// CTRMiniGameAnswer��(��) ���� ��ӵ�
	virtual void Init() override;
};

