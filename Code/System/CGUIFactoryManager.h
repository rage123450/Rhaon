#pragma once
class CGUIFactoryManager
{
public:
	CGUIFactoryManager();
	virtual ~CGUIFactoryManager();

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
};

