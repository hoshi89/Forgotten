#pragma once
#include "d3.h"
#include <string>
#include <SFML\Graphics.hpp>
using namespace std;

class DialogCls
{
public:
	DialogCls(const char *aDeckName);
	struct d3 *DialogEngine;	//sj�lva dialog motorn
	struct d3deck *TheDeck;		//inneh�ller dialogen
//	int NrOfAnswers;
	//const char *answer; //pekare till "aktuellt" svar
	//const char *question; // -		||		-	 fr�ga
//	bool PlayerOwnCard();
//	bool wBool;
//	std::vector<const char*> getCurrentText();
	int GetNrOfAnswers();
	const char* getQuestion();
	const char* getAnswer(int aAnswerIdx);
	const char* getQuestionUserData();
	const char* getAnswerUserData(int aAnswerIdx);
	bool ChooseAnswer(int aAnswerIndx);
	virtual ~DialogCls();
private:
//	void GetNextText(void);
	std::vector<const char*> TextsToRender;
	

};