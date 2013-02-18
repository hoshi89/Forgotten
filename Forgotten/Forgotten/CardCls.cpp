#include "CardCls.h"

CardCls::CardCls(void)
{
}

CardCls* CardCls::ShowCard(sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos)
{
	m_EntityPos = aEntityPos;
	m_InteractionNode = aInteractionNode;
	int wNrOfAnswers = GetNrOfAnswers();
	if(wNrOfAnswers == 0)
	{
		ShowOnlyQuestion();
		return m_TargetCard;
	}
	else
		if(wNrOfAnswers == 1)
			ShowQuestionAndOneAnswer();
		else
			ShowQuestionAndAnswers();		

}

void CardCls::ShowOnlyQuestion()
{
	if(m_Clock==NULL)
		m_Clock = new sf::Clock();
	
	if(m_Clock->getElapsedTime() < QUESTION_ELAPSED_TIME)
	{
		ManageQuestion();
	}
	else
		EndDialog();
}

void CardCls::ShowQuestionAndOneAnswer()
{

}
void CardCls::ShowQuestionAndAnswers()
{
}
void CardCls::ManageQuestion()
{
	sf::Text wQuestion = sf::Text(m_Question);
	if(m_TextPlace.compare("NPC"))
		wQuestion.setPosition(m_EntityPos.x, m_EntityPos.y-20);
	else
	{
		//int wX = m_player->GetPosition().x;
		//int wY = m_player->GetPosition().y;	Snacka med robin
		int wX = 100;
		int wY = 300;
		wQuestion.setPosition(m_InteractionNode.x, m_InteractionNode.y-20);
	}
	wQuestion.setCharacterSize(TEXT_SIZE);
	wQuestion.setColor(sf::Color::White);
	
}

void CardCls::EndDialog()
{
}

int CardCls::GetNrOfAnswers()
{
	return m_Answers.size();
}

CardCls::~CardCls(void)
{
}
