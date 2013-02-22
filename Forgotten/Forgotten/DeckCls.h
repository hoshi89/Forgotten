#pragma once

#include <string>
#include <vector>

#include "CardCls.h"

using namespace std;

class DeckCls
{
public:
	DeckCls(void);
	string GetDeckId();
	bool ShowDialog(sf::RenderWindow &aWindow, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos);
	void LoadFromFile();
	CardCls* GetCardById(string aCardId);

	virtual ~DeckCls(void);
private:
	string m_DeckId;
	vector<CardCls*> m_Cards;
	CardCls *m_CurrentCard;
	string m_CurrentCardId;
};

