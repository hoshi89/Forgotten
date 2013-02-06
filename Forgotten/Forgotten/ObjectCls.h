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
	void Render(sf::RenderWindow &aWindow) override;
	virtual ~ObjectCls(void);
};

