#pragma once

#include "DeckCls.h"
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>

using namespace std;

class LevelDialogsCls
{
public:
	LevelDialogsCls(string aScriptName, bool isSave);
	virtual ~LevelDialogsCls(void);
	DialogStateEnum ShowDialog(sf::RenderWindow &aWindow, string aDeckId,
					sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos, bool aIsPressed);
	void ChooseAnswer(sf::Vector2f* aMousePos);

	//Scriptfunc
	DeckCls* addDeck(string aId);
private:
	void LoadScript(string aScriptName);
	vector<DeckCls*> m_Decks;
	DeckCls* GetDeckById(string aDeckId);
	DeckCls *m_CurrentDeck;
	DialogReaderWriter* m_dlgrw;
};

