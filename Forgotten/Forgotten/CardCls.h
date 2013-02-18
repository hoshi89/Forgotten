#pragma once

#include <SFML\Graphics.hpp>
#include "AnswerCls.h"
//#include "GameManager.h"

#include <vector>

const sf::Time QUESTION_ELAPSED_TIME = sf::microseconds(5000000);
const sf::Time ANSWER_ELAPSED_TIME = sf::microseconds(2*5000000);
const int DISPLAY_HEIGHT = 576;
const int TEXT_SIZE = 12;


using namespace std;
class CardCls
{
public:
	CardCls(void);
	CardCls* ShowCard(sf::Vector2f aInteractionNode,
				sf::Vector2f aEntityPos);
	virtual ~CardCls(void);
private:
	vector<AnswerCls*> m_Answers;
	sf::Clock *m_Clock;
	string m_Question;
	CardCls* m_TargetCard;
	string m_TextPlace;
	sf::Vector2f m_EntityPos;
	sf::Vector2f m_InteractionNode;

	void ShowOnlyQuestion();
	void ShowQuestionAndOneAnswer();
	void ShowQuestionAndAnswers();
	int GetNrOfAnswers();
	void ManageQuestion();
	void EndDialog();

	//tmpstuff
};

