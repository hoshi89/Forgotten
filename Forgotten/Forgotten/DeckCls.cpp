#include "DeckCls.h"


DeckCls::DeckCls(void)
{
	m_CurrentCardId = "";
}

string DeckCls::GetDeckId()
{
	return m_DeckId;
}

CardCls* DeckCls::GetCardById(string aCardId)
{
	string wCardId;
	for(int i = 0; i < m_Cards.size(); i++)
	{
		wCardId = m_Cards[i]->GetCardId();
		if(wCardId.compare(aCardId) == 0)
			return m_Cards[i];
	}
	return NULL;
}

bool DeckCls::ShowDialog(sf::RenderWindow &aWindow, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos)
{
	if(m_CurrentCardId == "")
		m_CurrentCardId = m_Cards[0]->GetCardId();
	
	m_CurrentCard = GetCardById(m_CurrentCardId);
	m_CurrentCardId = m_CurrentCard->ShowCard(aWindow, aInteractionNode, aEntityPos);
	return m_CurrentCardId != "";
	
}

void DeckCls::LoadFromFile()
{
	m_DeckId = "blabla";

	//här ska vi ladda alla Cards som ligger under DETTA deck i loop från scriptfilen
	CardCls* CardOne = new CardCls("bajs", "kol");
	m_Cards.push_back(CardOne);
	CardOne->LoadFromFile("Hello, bajs");

	CardCls* CardTwo = new CardCls("kol", "yes!");
	m_Cards.push_back(CardTwo);
	CardTwo->LoadFromFile("haha, kul");

	CardCls* CardThree = new CardCls("yes!", "");
	m_Cards.push_back(CardThree);
	CardThree->LoadFromFile("YAAAA");
	
	//
}

DeckCls::~DeckCls(void)
{
}
