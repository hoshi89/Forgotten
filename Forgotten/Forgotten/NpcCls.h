#pragma once
#include "DialogOwnerCls.h"
class NpcCls :
	public DialogOwnerCls
{
public:
	NpcCls(const char *aDeckName);
	/*
	- Ärver klickbarhet från dialogOwner
	- 
	*/
	virtual ~NpcCls(void);
};

