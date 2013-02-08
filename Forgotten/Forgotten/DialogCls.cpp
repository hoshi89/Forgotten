#include "DialogCls.h"

DialogCls::DialogCls(const char *aDeckName)
{
	DialogEngine = d3_init();
	TheDeck = d3_load_deck_bin(aDeckName);
	d3_use_deck(DialogEngine, TheDeck, 0);
	question = d3_get_question(DialogEngine);
}



//bool DialogCls::PlayerOwnCard()
//{
//	return wBool;
//}

sf::Text DialogCls::getCurrentText()
{
	sf::Text wCurrentText = sf::Text(question, sf::Font::getDefaultFont(), 15);
	return wCurrentText;
	
}

DialogCls::~DialogCls()
{
}
//string CharToString(const char *aChar)
//{
//	string wString = string(aChar);
//	return wString;
//}