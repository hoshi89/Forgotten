#include "CardCls.h"
#include "GameManager.h"

CardCls::CardCls(string aCardId, string aTargetCardId) : m_CardId(aCardId),
	m_TargetCardId(aTargetCardId)
{
	m_TextPlace = "NPC";
	m_Clock = NULL;
}

string CardCls::ShowCard(sf::RenderWindow &aWindow, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos)
{
	m_EntityPos = aEntityPos;
	m_InteractionNode = aInteractionNode;
	int wNrOfAnswers = GetNrOfAnswers();
	if(wNrOfAnswers == 0)
		return ShowOnlyQuestion(aWindow);
	else
		if(wNrOfAnswers == 1)
			return ShowQuestionAndOneAnswer(aWindow);
		else
//			ShowQuestionAndAnswers(aWindow);
	return "";

}

string CardCls::ShowOnlyQuestion(sf::RenderWindow &aWindow)
{
	if(m_Clock==NULL)
		m_Clock = new sf::Clock();
	
	if(m_Clock->getElapsedTime() < QUESTION_ELAPSED_TIME)
	{
		ManageQuestion(aWindow);
		return m_CardId;
	}
	return EndDialog();
}

string CardCls::ShowQuestionAndOneAnswer(sf::RenderWindow &aWindow)
{
	if(m_Clock==NULL)
		m_Clock = new sf::Clock();
	if(m_Clock->getElapsedTime() < QUESTION_ELAPSED_TIME)
	{
		ManageQuestion(aWindow);
		return m_CardId;
	}
	if(m_Clock->getElapsedTime() < ANSWER_ELAPSED_TIME)
	{
		m_Answers[0]->ManageAnswer(aWindow);
		return m_CardId;
	}
	return m_Answers[0]->GetTargetId();
}
//string CardCls::ShowQuestionAndAnswers(sf::RenderWindow &aWindow)
//{
//	DlgMng->WatingForAnswer(true);
//	return "";
//}
void CardCls::ManageQuestion(sf::RenderWindow &aWindow)
{
	sf::Text wQuestion = sf::Text(m_Question);
	if(m_TextPlace.compare("NPC"))
		wQuestion.setPosition(m_EntityPos.x, m_EntityPos.y-20);
	else
	{
		int wX = 100;
		int wY = 300;
		wQuestion.setPosition(m_InteractionNode.x, m_InteractionNode.y);
	}
	wQuestion.setCharacterSize(TEXT_SIZE);
	wQuestion.setColor(sf::Color::White);
	aWindow.draw(wQuestion);	
}

string CardCls::GetCardId()
{
	return m_CardId;
}
void CardCls::LoadFromFile(string aText)
{
	//här ska vi ladda Question och alla Answers som ligger under DETTA Card i loop från scriptfilen
	m_Question = aText;
	if(m_CardId.compare("bajs") == 0)
	{
		AnswerCls* wAnswer = new AnswerCls("bajs1svar", "kol");
		m_Answers.push_back(wAnswer);
		wAnswer->LoadFromFile("smells good");
	}
	else
		if(m_CardId.compare("kol") == 0)
		{
			AnswerCls* wAnswer = new AnswerCls("kol1svar", "yes!");
			m_Answers.push_back(wAnswer);
			wAnswer->LoadFromFile("hihihihih");
		}

}

string CardCls::EndDialog()
{
	m_Clock = NULL;
	return m_TargetCardId;
}

int CardCls::GetNrOfAnswers()
{
	return m_Answers.size();
}

CardCls::~CardCls(void)
{
}
