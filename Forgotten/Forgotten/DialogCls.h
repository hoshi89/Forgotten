#pragma once
#include "d3.h"
#include <string>
using namespace std;

class DialogCls
{
public:
	DialogCls(const char *aDeckName);
	struct d3 *DialogEngine;	//sj�lva dialog motorn
	struct d3deck *TheDeck;		//inneh�ller dialogen
	int NrOfAnswers;
	string CharToString(const char aChar);
	const char *answer; //pekare till "aktuellt" svar
	const char *question; // -		||		-	 fr�ga
	bool PlayerOwnCard();
	virtual ~DialogCls(){};
};