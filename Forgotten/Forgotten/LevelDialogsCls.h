#pragma once

//#include <SFML\Graphics.hpp>

#include "DeckCls.h"

#include <vector>
#include <string>

using namespace std;

class LevelDialogsCls
{
public:
	LevelDialogsCls(string aScriptName);
	virtual ~LevelDialogsCls(void);
	bool ShowDialog(sf::RenderWindow &aWindow, string aDeckId,
					sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos);
	void Choosed(int aMousePos);

private:
	void LoadScript(string aScriptName);
	vector<DeckCls*> m_Decks;
	DeckCls* GetDeckById(string aDeckId);
	DeckCls *m_CurrentDeck;
	
};

