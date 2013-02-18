#pragma once
#include "DialogOwnerCls.h"

class NpcCls :
	public DialogOwnerCls
{
public:
	NpcCls(int aXpos, int aYpos,
		Player *aPlayer, const string aSpriteName);
	/*
	- Ärver klickbarhet från dialogOwner
	- 
	*/
//	void PlaceText(DialogCls aDialog) override;
	virtual ~NpcCls(void);
};

