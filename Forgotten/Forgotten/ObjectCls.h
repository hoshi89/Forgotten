#pragma once
#include "dialogownercls.h"
class ObjectCls :
	public DialogOwnerCls
{
public:
	ObjectCls(const char *aDeckName, Player *aPlayer);
	/*

	*/
	void PlaceText(DialogCls aDialog) override;
	virtual ~ObjectCls(void);
};

