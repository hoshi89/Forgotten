#pragma once
#include "DialogCls.h"
#include "Player.h"
#include <SFML\Graphics.hpp>

class DialogOwnerCls
{
public:
	DialogOwnerCls(const char *aDeckName, Player *aPlayer);
	void BeginDialog();
	virtual void AddToInventory();
	virtual ~DialogOwnerCls(void);
	virtual	void PlaceText(DialogCls aDialog);
	DialogCls mDialog;
	string m_currentString;

private:
	sf::IntRect getQuestionRect();
	sf::IntRect *aTextRect;
	Player *m_player;
};

