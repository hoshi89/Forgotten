#include "LevelDialogsCls.h"


LevelDialogsCls::LevelDialogsCls(string aScriptName, bool isSave)
{
	if(!isSave)
		LoadScript(aScriptName);
}

DialogStateEnum LevelDialogsCls::ShowDialog(sf::RenderWindow &aWindow, 
	string aDeckId, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos, bool aIsPressed)
{
	m_CurrentDeck = GetDeckById(aDeckId);
	return m_CurrentDeck->ShowDialog(aWindow, aInteractionNode, aEntityPos, aIsPressed);
}

void LevelDialogsCls::IsMouseOverAnswer(sf::Vector2f* aMousePos)
{
	m_CurrentDeck->IsMouseOverAnswer(aMousePos);
}

DeckCls* LevelDialogsCls::GetDeckById(string aDeckId)
{
	string wDeckId;
	for(int i = 0; i < m_Decks.size(); i++)
	{
		wDeckId = m_Decks[i]->GetDeckId();
		if(wDeckId.compare(aDeckId) == 0)
			return m_Decks[i];
	}
	return NULL;
}

void LevelDialogsCls::ChooseAnswer(sf::Vector2f* aMousePos)
{
	m_CurrentDeck->ChooseAnswer(aMousePos);
}

void LevelDialogsCls::LoadScript(string aScriptName)
{
	m_dlgrw = new DialogReaderWriter(aScriptName, false);
	bool wIsComplete = false;
	TagCls* tag = new TagCls();
	m_dlgrw->getTag(tag);
	DeckCls *wDeck;

	while(!m_dlgrw->isEndOfFile() && !wIsComplete)
	{
		wDeck = this->addDeck(tag->getValue());
		wIsComplete = wDeck->LoadFromFile(m_dlgrw, tag);
	}
}

DeckCls* LevelDialogsCls::addDeck(string aId)
{
	DeckCls* wDeck = new DeckCls(aId);
	m_Decks.push_back(wDeck);
	return wDeck;
}

LevelDialogsCls::~LevelDialogsCls(void)
{
}
