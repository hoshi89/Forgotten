#include "DialogOwnerCls.h"


DialogOwnerCls::DialogOwnerCls(const char *aDeckName) : mDialog(aDeckName)
{
}

void DialogOwnerCls::BeginDialog()
{
	//den h�r funktionen anropas n�r dialogen ska b�rja..
}

void DialogOwnerCls::AddToInventory()
{
	//default �r det ett objekt som l�gger till sig sj�lv till inventory
	//override f�r NPC l�gger till objekt som NPC:n ger dig
	//InventoryVector.pushback(objekt) ..
	//Den h�r funktionen skickar ALLTID det som inventory ska inneh�lla!
}
DialogOwnerCls::~DialogOwnerCls(void)
{
}
