#include "CardCls.h"

CardCls::CardCls(string aId)
{
	m_CardId = aId;
	m_Clock = NULL;
	m_Members.push_back(new CaseValues(TARGETSTR, TARGET_ID));
	m_Members.push_back(new CaseValues(TEXT_PLACESTR, TEXT_PLACE));
	m_Members.push_back(new CaseValues(ANSWERSTR, ANSWER));
	m_Members.push_back(new CaseValues(QUESTIONSTR, QUESTION));
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
			return ShowQuestionAndOneAnswer(aWindow, aEntityPos, aInteractionNode);
		else
			return ShowQuestionAndAnswers(aWindow, aEntityPos, aInteractionNode);
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
		m_Clock = NULL;
		return &m_TargetCardId;
	}
}

string* CardCls::ShowQuestionAndOneAnswer(sf::RenderWindow &aWindow, sf::Vector2f aEntityPos, sf::Vector2f aInteractionPos)
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
		m_Answers[0]->ManageAnswer(aWindow, aEntityPos, aInteractionPos);
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

string* CardCls::ShowQuestionAndAnswers(sf::RenderWindow &aWindow, sf::Vector2f aEntityPos, sf::Vector2f aInteractionPos)
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
	{
		m_QuestionText.setPosition(m_EntityPos);
		m_QuestionText.setColor(sf::Color::White);
	}
	else
	{
		m_QuestionText.setPosition(m_InteractionNode);
		m_QuestionText.setColor(sf::Color::Cyan);
	}
	m_QuestionText.setStyle(sf::Text::Bold);
	m_QuestionText.setCharacterSize(TEXT_SIZE);
	aWindow.draw(m_QuestionText);	
}

string* CardCls::GetCardId()
{
	return &m_CardId;
}

bool CardCls::LoadFromFile(DialogReaderWriter* aRw, TagCls* aTag)
{
	//här ska vi ladda Question och alla Answers som ligger under DETTA Card i loop från scriptfilen
	int wMemberId;
	AnswerCls* wAnswer;
	bool isComplete = false;
	
	aRw->getTag(aTag);
	wMemberId = aRw->MapMemberName(m_Members, aTag->getToken());
	while(!aRw->isEndOfFile() && !isComplete && 
		aTag->getToken() != CARD_ID && aTag->getToken() != DECK_ID)
	{
		switch(wMemberId)
		{
			case TARGET_ID:
				m_TargetCardId = aTag->getValue();
				break;
			case TEXT_PLACE:
				m_TextPlace = aTag->getValue();
				break;
			case QUESTION:
				m_QuestionText = sf::Text(aTag->getValue());
				break;
			case ANSWER:
				wAnswer = this->AddAnswer(aTag->getValue());
				wAnswer->LoadFromFile(aRw, aTag);
				isComplete = false;
				continue;
			default:
				return true;
		}
		aRw->getTag(aTag);
		wMemberId = aRw->MapMemberName(m_Members, aTag->getToken());
		if(aRw->isEndOfFile())
			return true;
	}
	return isComplete;
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

//Scriptfunc
AnswerCls* CardCls::AddAnswer(string aAnswerId)
{
	AnswerCls* wAnswer = new AnswerCls(aAnswerId);
	m_Answers.push_back(wAnswer);
	return wAnswer;
}

CardCls::~CardCls(void)
{
}
