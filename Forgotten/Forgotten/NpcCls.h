#pragma once
#include "DialogOwnerCls.h"

class NpcCls :
	public DialogOwnerCls
{
public:
	NpcCls(int aXpos, int aYpos,
		Player *aPlayer, const string aSpriteName);
	/*
	- �rver klickbarhet fr�n dialogOwner
	- 
	*/
//	void PlaceText(DialogCls aDialog) override;
	virtual ~NpcCls(void);
};

