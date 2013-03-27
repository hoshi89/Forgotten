#include "LevelDialogsCls.h"


LevelDialogsCls::LevelDialogsCls(string aScriptName, bool isSave)
{
	//Asking if its time to load or write
	if(!isSave)
		LoadScript(aScriptName);
}

DialogStateEnum LevelDialogsCls::ShowDialog(sf::RenderWindow &aWindow, 
	string aDeckId, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos, bool aIsPressed)
{
	m_currentDeck = GetDeckById(aDeckId);
	return m_currentDeck->ShowDialog(aWindow, aInteractionNode, aEntityPos, aIsPressed);
}

void LevelDialogsCls::IsMouseOverAnswer(sf::Vector2f* aMousePos)
{
	m_currentDeck->IsMouseOverAnswer(aMousePos);
}

DeckCls* LevelDialogsCls::GetDeckById(string aDeckId)
{
	string wDeckId;
	//iterate through the decknames to find the right one
	for(int i = 0; i < m_decks.size(); i++)
	{
		wDeckId = m_decks[i]->GetDeckId();
		if(wDeckId.compare(aDeckId) == 0)
			return m_decks[i];
	}
	return NULL;
}

void LevelDialogsCls::ChooseAnswer(sf::Vector2f* aMousePos)
{
	m_currentDeck->ChooseAnswer(aMousePos);
}

void LevelDialogsCls::LoadScript(string aScriptName)
{
	//loading from the txt filed written by dialogreaderwriter
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
	m_decks.push_back(wDeck);
	return wDeck;
}

LevelDialogsCls::~LevelDialogsCls(void)
{
}
