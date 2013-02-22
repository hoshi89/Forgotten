#pragma once

#include <SFML\Graphics.hpp>
#include "AnswerCls.h"

#include <vector>

const sf::Time QUESTION_ELAPSED_TIME = sf::microseconds(5000000);
const sf::Time ANSWER_ELAPSED_TIME = sf::microseconds(2*5000000);
const int DISPLAY_HEIGHT = 576;
const int TEXT_SIZE = 25;


using namespace std;
class CardCls
{
public:
	CardCls(string aCardId, string aTargetCardId);
	string ShowCard(sf::RenderWindow &aWindow, sf::Vector2f aInteractionNode,
				sf::Vector2f aEntityPos);
	void LoadFromFile(string aText);
	string GetCardId();
	virtual ~CardCls(void);
private:
	string m_CardId;
	vector<AnswerCls*> m_Answers;
	sf::Clock *m_Clock;
	string m_Question;
	string m_TextPlace;
	sf::Vector2f m_EntityPos;
	sf::Vector2f m_InteractionNode;
	string m_TargetCardId;

	string ShowOnlyQuestion(sf::RenderWindow &aWindow);
	string ShowQuestionAndOneAnswer(sf::RenderWindow &aWindow);
	string ShowQuestionAndAnswers(sf::RenderWindow &aWindow);
	int GetNrOfAnswers();
	void ManageQuestion(sf::RenderWindow &aWindow);
	string EndDialog();
};

