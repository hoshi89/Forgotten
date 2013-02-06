#include "DialogCls.h"

DialogCls::DialogCls(const char *aDeckName)
{
	DialogEngine = d3_init();
	TheDeck = d3_load_deck_bin(aDeckName);
	d3_use_deck(DialogEngine, TheDeck, 0);
}



bool DialogCls::PlayerOwnCard()
{
	return strcmp(d3_get_card_user_data(DialogEngine), "P");
}

string CharToString(const char aChar)
{
	return "hi";
}

