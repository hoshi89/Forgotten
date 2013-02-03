#pragma once
#include "d3.h"

class DialogCls
{
public:
	DialogCls(const char *aDeckName);
	struct d3 *DialogEngine;	//sj�lva dialog motorn
	struct d3deck *TheDeck;		//inneh�ller dialogen
	int NrOfAnswers;
	const char *getCardID(void);
	const char *answer; //pekare till "aktuellt" svar
	const char *question; // -		||		-	 fr�ga
	virtual ~DialogCls(){};
};