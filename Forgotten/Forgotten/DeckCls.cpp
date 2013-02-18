#include "DeckCls.h"


DeckCls::DeckCls(void)
{
}

string DeckCls::GetDeckId()
{
	return m_DeckId;
}

void DeckCls::ShowDialog(sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos)
{
	m_CurrentCard = m_Cards[0];
	do
		m_CurrentCard = m_CurrentCard->ShowCard(aInteractionNode, aEntityPos);
	while(m_CurrentCard != 0);
	
}


DeckCls::~DeckCls(void)
{
}
