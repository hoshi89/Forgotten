#pragma once
#include "DialogOwnerCls.h"
class NpcCls :
	public DialogOwnerCls
{
public:
	NpcCls(const char *aDeckName);
	/*
	- �rver klickbarhet fr�n dialogOwner
	- 
	*/
	virtual ~NpcCls(void);
};

