#include "DialogOwnerCls.h"


DialogOwnerCls::DialogOwnerCls(const char *aDeckName, int aXpos, int aYpos) : mDialog(aDeckName)
{
}

<<<<<<< HEAD
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

void DialogOwnerCls::PlaceText(DialogCls aDialog)
{
}


sf::IntRect DialogOwnerCls::getQuestionRect()
{
	if(mDialog.PlayerOwnCard())
	{
		m_player->GetPosition();
	}
	return sf::IntRect();

}
=======
//void DialogOwnerCls::BeginDialog()
//{
//	//den h�r funktionen anropas n�r dialogen ska b�rja..
//}

//void DialogOwnerCls::AddToInventory()
//{
//	//default �r det ett objekt som l�gger till sig sj�lv till inventory
//	//override f�r NPC l�gger till objekt som NPC:n ger dig
//	//InventoryVector.pushback(objekt) ..
//	//Den h�r funktionen skickar ALLTID det som inventory ska inneh�lla!
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
>>>>>>> 90f646568dcd44ab91c7c44b6a14f58e5f2d37f2
DialogOwnerCls::~DialogOwnerCls(void)
{
}
