#pragma once
#include "entity.h"

#include <string>

using namespace std;

class NpcCls :
	public Entity
{
public:
	NpcCls(int aXpos, int aYpos, const string aSpriteName);
	/*
	- �rver klickbarhet fr�n dialogOwner
	- 
	*/
//	void PlaceText(DialogCls aDialog) override;
	virtual ~NpcCls(void);
};

