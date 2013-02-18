#include "LevelDialogsCls.h"


LevelDialogsCls::LevelDialogsCls(string aScriptName)
{
}

void LevelDialogsCls::ShowDialog(string aDeckId, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos)
{
	m_CurrentDeck = GetDeckById(aDeckId);
	m_CurrentDeck->ShowDialog(aInteractionNode, aEntityPos);
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

LevelDialogsCls::~LevelDialogsCls(void)
{
}

void LevelDialogsCls::LoadScript(string aScriptName)
{
	//pushback hårdkodade dialoger in i vector .. 
}