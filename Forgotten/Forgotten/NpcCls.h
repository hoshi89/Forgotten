#pragma once
#include "DialogOwnerCls.h"

class NpcCls :
	public DialogOwnerCls
{
public:
	NpcCls(const char *aDeckName, int aXpos, int aYpos);
	/*
	- �rver klickbarhet fr�n dialogOwner
	- 
	*/
//	void PlaceText(DialogCls aDialog) override;
	virtual ~NpcCls(void);
};

