#pragma once
#include "TRMiniGameAnswer.h"
class CTRMiniGameAnswer_StringAnswer :
	public CTRMiniGameAnswer
{
public:
	CTRMiniGameAnswer_StringAnswer();
	virtual ~CTRMiniGameAnswer_StringAnswer();

public:
	// CTRMiniGameAnswer��(��) ���� ��ӵ�
	virtual void Init() override;
};

