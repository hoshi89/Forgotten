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
	virtual void Render(sf::RenderWindow &aWindow);
	DialogCls mDialog;
	string m_currentString;
//	sf::Text m_theText;

private:
	sf::IntRect getQuestionRect();
	sf::IntRect *aTextRect;
	Player *m_player;
//	sf::Vector2f *m_playerPosition;
};

