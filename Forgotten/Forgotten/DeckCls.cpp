#include "DeckCls.h"


DeckCls::DeckCls(void)
{
	m_CurrentCardId = NULL;
}

string DeckCls::GetDeckId()
{
	return m_DeckId;
}

CardCls* DeckCls::GetCardById(string* aCardId)
{
	string* wCardId;
 	for(int i = 0; i < m_Cards.size(); i++)
	{
		wCardId = m_Cards[i]->GetCardId();
		if(*wCardId == *aCardId)
			return m_Cards[i];
	}
	return NULL;
}

DialogStateEnum DeckCls::ShowDialog(sf::RenderWindow &aWindow, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos)
{
	if(m_CurrentCardId == NULL || *m_CurrentCardId == "")
		m_CurrentCardId = m_Cards[0]->GetCardId();

	m_CurrentCard = GetCardById(m_CurrentCardId);
	m_CurrentCardId = m_CurrentCard->ShowCard(aWindow, aInteractionNode, aEntityPos);
	DialogStateEnum wDlgState = m_CurrentCard->GetDialogState();

	return wDlgState;
	
}

void DeckCls::LoadFromFile()
{
	m_DeckId = "blabla";

	//här ska vi ladda alla Cards som ligger under DETTA deck i loop från scriptfilen
	CardCls* CardZero = new CardCls("zerocard", "firstcard");
	m_Cards.push_back(CardZero);
	CardZero->LoadFromFile("zerocard!");

	CardCls* CardOne = new CardCls("firstcard", "");
	m_Cards.push_back(CardOne);
	CardOne->LoadFromFile("firstcard!");

	CardCls* CardTwo = new CardCls("secondcard", "");
	m_Cards.push_back(CardTwo);
	CardTwo->LoadFromFile("secondcard!");

	CardCls* CardThree = new CardCls("thirdcard", "");
	m_Cards.push_back(CardThree);
	CardThree->LoadFromFile("thirdcard!");

	CardCls* CardFour = new CardCls("fourthcard", "");
	m_Cards.push_back(CardFour);
	CardFour->LoadFromFile("fourthcard!");
	
	//
}

void DeckCls::ChooseAnswer(sf::Vector2f* aMousePos)
{
	m_CurrentCardId = m_CurrentCard->ChooseAnswer(aMousePos);
}

DeckCls::~DeckCls(void)
{
}
