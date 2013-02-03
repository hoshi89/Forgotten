#include "DialogCls.h"

DialogCls::DialogCls(const char *aDeckName)
{
	DialogEngine = d3_init();
	TheDeck = d3_load_deck_bin(aDeckName);
	d3_use_deck(DialogEngine, TheDeck, 0);

}
const char *DialogCls::getCardID(void)
{
	return d3_get_card_id(DialogEngine);
}

