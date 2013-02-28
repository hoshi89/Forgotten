#include "CardCls.h"

CardCls::CardCls(string aCardId, string aTargetCardId) : m_CardId(aCardId),
	m_TargetCardId(aTargetCardId)
{
	m_TextPlace = "NPC";
	m_Clock = NULL;

}

string* CardCls::ShowCard(sf::RenderWindow &aWindow, sf::Vector2f aInteractionNode,
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
			return ShowQuestionAndAnswers(aWindow);
}

string* CardCls::ShowOnlyQuestion(sf::RenderWindow &aWindow)
{
	if(m_Clock==NULL)
		m_Clock = new sf::Clock();
	
	if(m_Clock->getElapsedTime() < QUESTION_ELAPSED_TIME)
	{
		ManageQuestion(aWindow);
		m_State = DialogStateEnum::ContinueDialog;
		return &m_CardId;
	}

	if(m_TargetCardId == "")
		return EndDialog();
	else
	{
		ContinueDialog();
		return &m_TargetCardId;
	}
}

string* CardCls::ShowQuestionAndOneAnswer(sf::RenderWindow &aWindow)
{
	if(m_Clock==NULL)
		m_Clock = new sf::Clock();
	
	m_State = DialogStateEnum::ContinueDialog;
	if(m_Clock->getElapsedTime() < QUESTION_ELAPSED_TIME)
	{
		ManageQuestion(aWindow);
		return &m_CardId;
	}
	if(m_Clock->getElapsedTime() < ANSWER_ELAPSED_TIME)
	{
		m_Answers[0]->ManageAnswer(aWindow);
		return &m_CardId;
	}
	string* wTargetId = m_Answers[0]->GetTargetId();
	if(*wTargetId == "")
		return EndDialog();
	else
	{
		delete m_Clock;
		m_Clock = NULL;
		return wTargetId;
	}
}
string* CardCls::ShowQuestionAndAnswers(sf::RenderWindow &aWindow)
{
	ManageQuestion(aWindow);
	int wY = DISPLAY_HEIGHT-TEXT_SIZE-10;
	for(int i=GetNrOfAnswers()-1; i>=0; i--)
	{
		m_Answers[i]->ManageAnswerS(aWindow, wY);
		wY-=(TEXT_SIZE+3);
	}
	m_State = DialogStateEnum::WaitForAnswer;
	return &m_CardId;
}
void CardCls::ManageQuestion(sf::RenderWindow &aWindow)
{
	if(m_TextPlace == "NPC")
		m_QuestionText.setPosition(m_EntityPos.x, m_EntityPos.y-20);
	else
	{
		int wX = 100;
		int wY = 300;
		m_QuestionText.setPosition(m_InteractionNode.x, m_InteractionNode.y);
	}
	m_QuestionText.setCharacterSize(TEXT_SIZE);
	m_QuestionText.setColor(sf::Color::White);
	aWindow.draw(m_QuestionText);	
}

string* CardCls::GetCardId()
{
	return &m_CardId;
}
void CardCls::LoadFromFile(string aText)
{
	//här ska vi ladda Question och alla Answers som ligger under DETTA Card i loop från scriptfilen
	m_Question = aText;
	m_QuestionText = sf::Text(m_Question);
	if(m_CardId == "firstcard")
	{
		AnswerCls* wAnswer = new AnswerCls("firstcardfirsanswer", "secondcard");
		m_Answers.push_back(wAnswer);
		wAnswer->LoadFromFile("firstcardfirsanswer!");
	}
	else
		if(m_CardId == "secondcard")
		{
			AnswerCls* wAnswer = new AnswerCls("secondcardfirstanswer", "thirdcard");
			m_Answers.push_back(wAnswer);
			wAnswer->LoadFromFile("secondcardfirstanswer!");

			AnswerCls* wAnswer2 = new AnswerCls("secondcardsecondanswer", "fourthcard");
			m_Answers.push_back(wAnswer2);
			wAnswer2->LoadFromFile("secondcardsecondanswer!");
		}

}

string* CardCls::EndDialog()
{
	delete m_Clock;
	m_Clock = NULL;
	m_State = DialogStateEnum::EndDialog;
	return &m_TargetCardId;
}

void CardCls::ContinueDialog()
{
	m_State = DialogStateEnum::ContinueDialog;
}

int CardCls::GetNrOfAnswers()
{
	return m_Answers.size();
}

DialogStateEnum CardCls::GetDialogState()
{
	return m_State;
}

string* CardCls::ChooseAnswer(sf::Vector2f* aMousePos)
{
	for(int i = 0; i<m_Answers.size(); i++)
		if(m_Answers[i]->isAnswerChoosen(aMousePos))
		{
			m_State = DialogStateEnum::EndDialog;
			string* wTargetId = m_Answers[i]->GetTargetId();
			if(*wTargetId == "")
				return EndDialog();
			else
			{
				ContinueDialog();
				return m_Answers[i]->GetTargetId();
			}
		}
		return &m_CardId;
}
CardCls::~CardCls(void)
{
}
