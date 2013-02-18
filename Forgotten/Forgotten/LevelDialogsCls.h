#pragma once

#include "DeckCls.h"

#include <vector>
#include <string>

using namespace std;

class LevelDialogsCls
{
public:
	LevelDialogsCls(string aScriptName);
	virtual ~LevelDialogsCls(void);
	void ShowDialog(string aDeckId, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos);

private:
	void LoadScript(string aScriptName);
	vector<DeckCls*> m_Decks;
	DeckCls* GetDeckById(string aDeckId);
	DeckCls *m_CurrentDeck;
	
};

