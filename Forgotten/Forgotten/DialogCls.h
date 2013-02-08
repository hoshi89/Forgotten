#pragma once
#include "d3.h"
#include <string>
#include <SFML\Graphics.hpp>
using namespace std;

class DialogCls
{
public:
	DialogCls(const char *aDeckName);
	struct d3 *DialogEngine;	//själva dialog motorn
	struct d3deck *TheDeck;		//innehåller dialogen
	int NrOfAnswers;
//	string CharToString(const char *aChar);
	const char *answer; //pekare till "aktuellt" svar
	const char *question; // -		||		-	 fråga
//	bool PlayerOwnCard();
//	bool wBool;
	sf::Text getCurrentText();
	virtual ~DialogCls();
};