#include "NpcCls.h"


NpcCls::NpcCls(const char *aDeckName, Player *aPlayer) : DialogOwnerCls(aDeckName, aPlayer)
{
	mDialog = DialogCls::DialogCls(aDeckName);
	PlaceText(mDialog);
}

void NpcCls::PlaceText(DialogCls aDialog)
{
}


NpcCls::~NpcCls(void)
{
}
