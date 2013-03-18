#pragma once

#include <string>
#include <vector>

#include "CardCls.h"

using namespace std;

class DeckCls
{
public:
	DeckCls(string aId);
	string GetDeckId();
	DialogStateEnum ShowDialog(sf::RenderWindow &aWindow, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos, bool aIsPressed);
	bool LoadFromFile(DialogReaderWriter* aRw, TagCls* aTag);
	CardCls* GetCardById(string* aCardId);
	void ChooseAnswer(sf::Vector2f* aMousePos);
	void IsMouseOverAnswer(sf::Vector2f* aMousePos);

	//Scriptfunc
	CardCls* addCard(string aId);
	virtual ~DeckCls(void);
private:
	string m_DeckId;
	vector<CardCls*> m_Cards;
	CardCls *m_CurrentCard;
	string* m_CurrentCardId;
};

