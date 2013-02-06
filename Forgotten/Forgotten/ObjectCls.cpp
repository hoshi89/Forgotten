#include "ObjectCls.h"


ObjectCls::ObjectCls(const char *aDeckName, Player *aPlayer) : DialogOwnerCls(aDeckName, aPlayer)
{
	mDialog = DialogCls::DialogCls(aDeckName);
	
}

void ObjectCls::PlaceText(DialogCls aDialog)
{
}

ObjectCls::~ObjectCls(void)
{
}
