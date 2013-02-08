#include "DialogCls.h"

DialogCls::DialogCls(const char *aDeckName)
{
	DialogEngine = d3_init();
	TheDeck = d3_load_deck_bin(aDeckName);
	d3_use_deck(DialogEngine, TheDeck, 0);
	question = d3_get_question(DialogEngine);
}



bool DialogCls::PlayerOwnCard()
{
	return strcmp(d3_get_card_user_data(DialogEngine), "P");
}

sf::Text DialogCls::getCurrentText()
{
	sf::Text wCurrentText = sf::Text(question);
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