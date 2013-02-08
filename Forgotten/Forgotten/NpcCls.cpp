#include "NpcCls.h"


NpcCls::NpcCls(const char *aDeckName, int aXpos, int aYpos) : DialogOwnerCls(aDeckName, aXpos, aYpos)
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
