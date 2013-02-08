#pragma once
#include "DialogCls.h"
#include "Player.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"

class DialogOwnerCls: public Entity
{
public:
	DialogOwnerCls(const char *aDeckName, int aXpos, int aYpos, Player *aPlayer);
	virtual void SetPosition(int x, int y) abstract;
	virtual void Render(sf::RenderWindow &aWindow) abstract;
	virtual void Update() abstract;
	virtual int GetZ() abstract;

	//	string m_currentString;
	sf::Text m_currentText;
	virtual sf::Text ManageText(sf::Text aText) abstract;
//	void BeginDialog();
//	virtual void AddToInventory();
//	virtual	void PlaceText(DialogCls aDialog);
	int posX;
	int posY;
	DialogCls mDialog;
	virtual ~DialogOwnerCls(void);
	Player *m_player;

private:
//	sf::IntRect getQuestionRect();
	sf::IntRect *aTextRect;
//	sf::Vector2f *m_playerPosition;
};

