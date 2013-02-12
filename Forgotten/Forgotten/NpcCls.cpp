#include "NpcCls.h"


NpcCls::NpcCls(const char *aDeckName, int aXpos, int aYpos, Player *aPlayer,
	const string aSpriteName) : DialogOwnerCls(aDeckName, aXpos, aYpos, aPlayer, aSpriteName)
{
	mDialog = DialogCls::DialogCls(aDeckName);
//	PlaceText(mDialog);
}

//void NpcCls::PlaceText(DialogCls aDialog)
//{
//}

//sf::Text NpcCls::ManageText(sf::Text aText)
//{
//	return sf::Text();
//}

NpcCls::~NpcCls(void)
{
}
