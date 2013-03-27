#include "DeckCls.h"

DeckCls::DeckCls(string aId)
{
	m_currentCardId = NULL;
	m_deckId = aId;
}

string DeckCls::GetDeckId()
{
	return m_deckId;
}

CardCls* DeckCls::GetCardById(string* aCardId)
{
	string* wCardId;
 	for(int i = 0; i < m_cards.size(); i++)
	{
		wCardId = m_cards[i]->GetCardId();
		if(*wCardId == *aCardId)
			return m_cards[i];
	}
	return NULL;
}

DialogStateEnum DeckCls::ShowDialog(sf::RenderWindow &aWindow, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos, bool aIsPressed)
{
	if(m_currentCardId == NULL || *m_currentCardId == "")
		m_currentCardId = m_cards[0]->GetCardId();

	m_currentCard = GetCardById(m_currentCardId);
	m_currentCardId = m_currentCard->ShowCard(aWindow, aInteractionNode, aEntityPos, aIsPressed);
	DialogStateEnum wDlgState = m_currentCard->GetDialogState();
	return wDlgState;
}

void DeckCls::IsMouseOverAnswer(sf::Vector2f* aMousePos)
{
	m_currentCard->IsMouseOverAnswer(aMousePos);
}

bool DeckCls::LoadFromFile(DialogReaderWriter* aRw, TagCls* aTag)
{
	bool isComplete = false;
	CardCls *wCard;
	aRw->getTag(aTag);
	while(!aRw->isEndOfFile() && aTag->getToken() == CARD_ID)
	{
		wCard = this->addCard(aTag->getValue());
		wCard->LoadFromFile(aRw, aTag);
	}
	return isComplete;
}

void DeckCls::ChooseAnswer(sf::Vector2f* aMousePos)
{
	m_currentCardId = m_currentCard->ChooseAnswer(aMousePos);
}

//ScriptFunc
CardCls* DeckCls::addCard(string aId)
{
	CardCls* wCard = new CardCls(aId);
	m_cards.push_back(wCard);
	return wCard;
}

DeckCls::~DeckCls(void)
{
}
