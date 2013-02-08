#include "DialogOwnerCls.h"


DialogOwnerCls::DialogOwnerCls(const char *aDeckName, int aXpos, int aYpos, Player *aPlayer) : mDialog(aDeckName), m_player(aPlayer)
{
}

//void DialogOwnerCls::BeginDialog()
//{
//	//den här funktionen anropas när dialogen ska börja..
//}

//void DialogOwnerCls::AddToInventory()
//{
//	//default är det ett objekt som lägger till sig själv till inventory
//	//override för NPC lägger till objekt som NPC:n ger dig
//	//InventoryVector.pushback(objekt) ..
//	//Den här funktionen skickar ALLTID det som inventory ska innehålla!
//}

//void DialogOwnerCls::PlaceText(DialogCls aDialog)
//{
//}


//sf::IntRect DialogOwnerCls::getQuestionRect()
//{
//	if(mDialog.PlayerOwnCard())
//	{
//		m_player->GetPosition();
//	}
//
//}

DialogOwnerCls::~DialogOwnerCls(void)
{
}
