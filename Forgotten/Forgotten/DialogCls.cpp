#include "DialogCls.h"

DialogCls::DialogCls(const char *aDeckName)
{
	DialogEngine = d3_init();
	TheDeck = d3_load_deck_bin(aDeckName);
	d3_use_deck(DialogEngine, TheDeck, 0);
//	answer = d3_get_answer(DialogEngine, 1);
}



//bool DialogCls::PlayerOwnCard()
//{
//	return wBool;
//}

//std::vector<const char*> DialogCls::getCurrentText()
//{
//	if(myClock==NULL)
//	{
//		myClock = new sf::Clock();
//		TextsToRender.clear();
//		TextsToRender.push_back(d3_get_question(DialogEngine));
//	}
//	else
//	{
//		sf::Time t = myClock->getElapsedTime();
//		if(t>sf::microseconds(5000000))
//		{
//			int wNrOfAnswers = d3_get_answer_count(DialogEngine);
//			if(wNrOfAnswers == 0)
//			{
//				TextsToRender.clear();
//				myClock=NULL;
//			}
//			else
//				GetNextText();					
//					
//		}
//	}
//	return TextsToRender;	
//}

//void DialogCls::GetNextText(void)
//{
//	//if(wNrOfAnswers == 1)
//	//{
//	//	TextsToRender.push_back(GetNextText());
//	//	myClock->restart();
//	//}
//	//else
//	const char *wAnswer;
//	int wNrOfAnswers = d3_get_answer_count(DialogEngine);
//	for(int i = 0; i < wNrOfAnswers; i++)
//	{
//		wAnswer = d3_get_answer(DialogEngine, i);
//		TextsToRender.push_back(wAnswer);
//	}
//}

int DialogCls::GetNrOfAnswers()
{
	return d3_get_answer_count(DialogEngine);
}

const char* DialogCls::getQuestion()
{
	return d3_get_question(DialogEngine);
}

const char* DialogCls::getQuestionUserData()
{
	return d3_get_card_user_data(DialogEngine);
}

const char* DialogCls::getAnswer(int aAnswerIdx)
{
	return d3_get_answer(DialogEngine, aAnswerIdx);
}

const char* DialogCls::getAnswerUserData(int aAnswerIdx)
{
	return d3_get_answer_user_data(DialogEngine, aAnswerIdx);
}

bool DialogCls::ChooseAnswer(int aAnswerIndx)
{
	int wResult = d3_choose(DialogEngine, aAnswerIndx);
	return d3_choose(DialogEngine, aAnswerIndx)==0;
}

DialogCls::~DialogCls()
{
}
//string CharToString(const char *aChar)
//{
//	string wString = string(aChar);
//	return wString;
//}