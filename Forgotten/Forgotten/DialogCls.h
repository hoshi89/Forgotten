#pragma once
#include "d3.h"

class DialogCls
{
public:
	DialogCls(const char *aDeckName);
	struct d3 *DialogEngine;	//själva dialog motorn
	struct d3deck *TheDeck;		//innehåller dialogen
	int NrOfAnswers;
	const char *getCardID(void);
	const char *answer; //pekare till "aktuellt" svar
	const char *question; // -		||		-	 fråga
	virtual ~DialogCls(){};
};