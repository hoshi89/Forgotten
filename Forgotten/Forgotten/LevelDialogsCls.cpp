#include "LevelDialogsCls.h"


LevelDialogsCls::LevelDialogsCls(string aScriptName)
{
	//här ska vi öppna och ladda alla Deck i loop från scriptfilen
	m_CurrentDeck = new DeckCls();
	m_CurrentDeck->LoadFromFile();
	m_Decks.push_back(m_CurrentDeck);
}

bool LevelDialogsCls::ShowDialog(sf::RenderWindow &aWindow, 
	string aDeckId, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos)
{
	m_CurrentDeck = GetDeckById(aDeckId);
	return m_CurrentDeck->ShowDialog(aWindow, aInteractionNode, aEntityPos);

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

void Choosed(int aMousePos)
{

}
void LevelDialogsCls::LoadScript(string aScriptName)
{
	//pushback hårdkodade dialoger in i vector .. 

}