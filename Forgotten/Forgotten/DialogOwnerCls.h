#pragma once
#include "DialogCls.h"
#include "Player.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"

class DialogOwnerCls: public Entity
{
public:
	DialogOwnerCls(const char *aDeckName, int aXpos, int aYpos);
//	void BeginDialog();
//	virtual void AddToInventory();
	virtual ~DialogOwnerCls(void);
//	virtual	void PlaceText(DialogCls aDialog);
	virtual void Render(sf::RenderWindow &aWindow) abstract;
	virtual void Update() abstract;
	DialogCls mDialog;
//	string m_currentString;
//	sf::Text *m_currentText;
//	virtual sf::Text ManageText(sf::Text aText) abstract;
	int posX;
	int posY;

private:
//	sf::IntRect getQuestionRect();
	sf::IntRect *aTextRect;
	Player *m_player;
//	sf::Vector2f *m_playerPosition;
};

