#include "DeckCls.h"

DeckCls::DeckCls(string aId)
{
	m_CurrentCardId = NULL;
	m_DeckId = aId;
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
					sf::Vector2f aEntityPos, bool aIsPressed)
{
	if(m_CurrentCardId == NULL || *m_CurrentCardId == "")
		m_CurrentCardId = m_Cards[0]->GetCardId();

	m_CurrentCard = GetCardById(m_CurrentCardId);
	m_CurrentCardId = m_CurrentCard->ShowCard(aWindow, aInteractionNode, aEntityPos, aIsPressed);
	DialogStateEnum wDlgState = m_CurrentCard->GetDialogState();
	return wDlgState;
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
	m_CurrentCardId = m_CurrentCard->ChooseAnswer(aMousePos);
}

//ScriptFunc
CardCls* DeckCls::addCard(string aId)
{
	CardCls* wCard = new CardCls(aId);
	m_Cards.push_back(wCard);
	return wCard;
}

DeckCls::~DeckCls(void)
{
}
