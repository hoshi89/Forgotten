#include "CardCls.h"
#include "FlagManager.h"
#include "GameManager.h"

CardCls::CardCls(string aId)
{
	m_CardId = aId;
	m_Clock = NULL;
	m_ShowWhat = ShowWhatEnum::ShowQuestion;
	m_Members.push_back(new CaseValues(TARGETSTR, TARGET_ID));
	m_Members.push_back(new CaseValues(TEXT_PLACESTR, TEXT_PLACE));
	m_Members.push_back(new CaseValues(ANSWERSTR, ANSWER));
	m_Members.push_back(new CaseValues(QUESTIONSTR, QUESTION));
	m_Members.push_back(new CaseValues(QUESTIONSETFLAG, QUESTION_SET_FLAG));
}

string* CardCls::ShowCard(sf::RenderWindow &aWindow, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos, bool aIsPressed)
{
	m_WasMousePressed = aIsPressed;
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
	ManageQuestion(aWindow);
	if(m_WasMousePressed)
		if(m_TargetCardId == "")
			return EndDialog();
		else
			return &m_TargetCardId;
	else
	{
		m_State = DialogStateEnum::ContinueDialog;
		return &m_CardId;
	}
//	if(m_Clock==NULL)
//		m_Clock = new sf::Clock();
//	
//	if(m_Clock->getElapsedTime() < QUESTION_ELAPSED_TIME)
//	{
//		ManageQuestion(aWindow);
//		m_State = DialogStateEnum::ContinueDialog;
//		return &m_CardId;
//	}
//
//	if(m_TargetCardId == "")
//		return EndDialog();
//	else
//	{
//		ContinueDialog();
//		m_Clock = NULL;
//		return &m_TargetCardId;
//	}
}

string* CardCls::ShowQuestionAndOneAnswer(sf::RenderWindow &aWindow, sf::Vector2f aEntityPos, sf::Vector2f aInteractionPos)
{
	switch(m_ShowWhat)
	{
	case ShowQuestion:
		ManageQuestion(aWindow);
		m_State = DialogStateEnum::ContinueDialog;
		if(m_WasMousePressed)
			m_ShowWhat = ShowAnswer;
		return &m_CardId;
	case ShowAnswer:
		m_Answers[0]->ManageAnswer(aWindow, aEntityPos, aInteractionPos);
		if(m_WasMousePressed)
		{
			string* wString = m_Answers[0]->GetTargetId();
			if(*wString == "")
				return EndDialog();
			else
			{
				m_ShowWhat = ShowWhatEnum::ShowQuestion;
				return wString;
			}
		}
		else
			return &m_CardId;
}

	
	//if(m_Clock==NULL)
	//	m_Clock = new sf::Clock();
	//
	//m_State = DialogStateEnum::ContinueDialog;
	//if(m_Clock->getElapsedTime() < QUESTION_ELAPSED_TIME)
	//{
	//	ManageQuestion(aWindow);
	//	return &m_CardId;
	//}

	//if(m_Clock->getElapsedTime() < ANSWER_ELAPSED_TIME)
	//{
	//	m_Answers[0]->ManageAnswer(aWindow, aEntityPos, aInteractionPos);
	//	return &m_CardId;
	//}

	//string* wTargetId = m_Answers[0]->GetTargetId();
	//if(*wTargetId == "")
	//	return EndDialog();
	//else
	//{
	//	delete m_Clock;
	//	m_Clock = NULL;
	//	return wTargetId;
	//}
}

string* CardCls::ShowQuestionAndAnswers(sf::RenderWindow &aWindow, sf::Vector2f aEntityPos, sf::Vector2f aInteractionPos)
{
	ManageQuestion(aWindow);
	int wY = DISPLAY_HEIGHT-TEXT_SIZE-10;
	for(int i=GetNrOfAnswers()-1; i>=0; i--)
	{
		string* wFlag = m_Answers[i]->GetNeedFlag();
		bool wBoolFlag = FlagManager::GetInstance()->IsFlagSet(*wFlag);
		if(wBoolFlag || *wFlag == "")
		{
			m_Answers[i]->ManageAnswerS(aWindow, wY);
			wY-=(TEXT_SIZE+3);
		}
		else
		{
		}

	}
	m_State = DialogStateEnum::WaitForAnswer;
	return &m_CardId;
}

void CardCls::ManageQuestion(sf::RenderWindow &aWindow)
{
	sf::Color NPCQuestionColor(226, 90, 75);
	if(m_TextPlace == "NPC")
	{
		string tmpString = m_QuestionText.getString();
		if(m_EntityPos.x < m_InteractionNode.x && tmpString.size() <= 10)
		{
			m_EntityPos.x = m_EntityPos.x + 100;
		}
		m_QuestionText.setPosition(m_EntityPos.x, m_EntityPos.y);
		m_QuestionText.setColor(NPCQuestionColor);
	}
	else
	{
		string tmpString = m_QuestionText.getString();
		if(m_EntityPos.x > m_InteractionNode.x && tmpString.size() <= 10)
		{
			m_InteractionNode.x = m_InteractionNode.x+100;
		}
		m_QuestionText.setPosition(m_InteractionNode);
		m_QuestionText.setColor(sf::Color::White);
	}
	m_QuestionText.setFont(GameManager::GetInstance()->GetFont());
	m_QuestionText.setCharacterSize(TEXT_SIZE);

	//outline1
	sf::Text outline1(m_QuestionText);
	outline1.setColor(sf::Color::Black);
	outline1.setCharacterSize(TEXT_SIZE);
	outline1.setFont(GameManager::GetInstance()->GetFont());
	outline1.setPosition(m_QuestionText.getPosition().x+1, m_QuestionText.getPosition().y+1); 
	//outline1
	sf::Text outline2(m_QuestionText);
	outline2.setColor(sf::Color::Black);
	outline2.setCharacterSize(TEXT_SIZE);
	outline2.setFont(GameManager::GetInstance()->GetFont());
	outline2.setPosition(m_QuestionText.getPosition().x+1, m_QuestionText.getPosition().y-1); 
	//outline1
	sf::Text outline3(m_QuestionText);
	outline3.setColor(sf::Color::Black);
	outline3.setCharacterSize(TEXT_SIZE);
	outline3.setFont(GameManager::GetInstance()->GetFont());
	outline3.setPosition(m_QuestionText.getPosition().x-1, m_QuestionText.getPosition().y+1); 
	//outline1
	sf::Text outline4(m_QuestionText);
	outline4.setColor(sf::Color::Black);
	outline4.setCharacterSize(TEXT_SIZE);
	outline4.setFont(GameManager::GetInstance()->GetFont());
	outline4.setPosition(m_QuestionText.getPosition().x-1, m_QuestionText.getPosition().y-1); 

	aWindow.draw(outline1);
	aWindow.draw(outline2);
	aWindow.draw(outline3);
	aWindow.draw(outline4);

	aWindow.draw(m_QuestionText);
	if(m_QuestionSetFlag != "")
	{
		FlagManager::GetInstance()->CreateFlag(m_QuestionSetFlag);
		m_QuestionSetFlag = "";
	}
}

void CardCls::IsMouseOverAnswer(sf::Vector2f* aMousePos)
{
	for(int i = 0; i < m_Answers.size(); i++)
	{
		m_Answers[i]->IsMouseOverAnswer(aMousePos);
	}
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
				{
				m_QuestionText = sf::Text(aTag->getValue());
				// Wrap text
				int chars_before_linebreak = 20;
				int charCounter = 0;

				sf::String tmpString = m_QuestionText.getString();

				// Iterate through the string
				for(int i = 0; i < tmpString.getSize(); i++)
				{
					if(charCounter >= chars_before_linebreak)
					{
						int rowBreak = tmpString.find(sf::String(" "), i);

						tmpString.insert(rowBreak+1, "\n");
						m_QuestionText.setString(tmpString);

						charCounter = 0;
					}
					charCounter++;
				}

				break;
				}
			case ANSWER:
				wAnswer = this->AddAnswer(aTag->getValue(), m_InteractionNode, m_EntityPos);
				wAnswer->LoadFromFile(aRw, aTag);
				isComplete = false;
				continue;
			case QUESTION_SET_FLAG:
				m_QuestionSetFlag = aTag->getValue();
				break;
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
	//delete m_Clock;
	//m_Clock = NULL;
	m_ShowWhat = ShowWhatEnum::ShowQuestion;
	m_State = DialogStateEnum::EndDialog;
	m_WasMousePressed = false;
	return &m_TargetCardId;
}

void CardCls::ContinueDialog()
{
	m_ShowWhat = ShowWhatEnum::ShowQuestion;
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
			m_Answers[i]->setChosen();
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
AnswerCls* CardCls::AddAnswer(string aAnswerId, sf::Vector2f aInteractionNode,
		sf::Vector2f aEntityPos)
{
	AnswerCls* wAnswer = new AnswerCls(aAnswerId, aInteractionNode, aEntityPos);
	m_Answers.push_back(wAnswer);
	return wAnswer;
}

CardCls::~CardCls(void)
{
}
