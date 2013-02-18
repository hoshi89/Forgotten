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
	void ShowDialog(sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos);

	virtual ~DeckCls(void);
private:
	string m_DeckId;
	vector<CardCls*> m_Cards;
	CardCls *m_CurrentCard;

};

