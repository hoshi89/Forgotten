#include "CardCls.h"
#include "FlagManager.h"
#include "GameManager.h"

CardCls::CardCls(string aId)
{
	m_cardId = aId;
	m_showWhat = ShowWhatEnum::ShowQuestion;
	//adding the members to the map
	m_members.push_back(new CaseValues(TARGETSTR, TARGET_ID));
	m_members.push_back(new CaseValues(TEXT_PLACESTR, TEXT_PLACE));
	m_members.push_back(new CaseValues(ANSWERSTR, ANSWER));
	m_members.push_back(new CaseValues(QUESTIONSTR, QUESTION));
	m_members.push_back(new CaseValues(QUESTIONSETFLAG, QUESTION_SET_FLAG));
}

string* CardCls::ShowCard(sf::RenderWindow &aWindow, sf::Vector2f aInteractionNode,
					sf::Vector2f aEntityPos, bool aIsPressed)
{
	m_wasMousePressed = aIsPressed;
	m_entityPos = aEntityPos;
	m_interactionNode = aInteractionNode;
	int wNrOfAnswers = GetNrOfAnswers();
	//Checking the number of answers on each card
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
	//Shows cards with one question only
	ManageQuestion(aWindow);
	if(m_wasMousePressed)
		if(m_targetCardId == "")
			return EndDialog();
		else
			return &m_targetCardId;
	else
	{
		m_state = DialogStateEnum::ContinueDialog;
		return &m_cardId;
	}

}

string* CardCls::ShowQuestionAndOneAnswer(sf::RenderWindow &aWindow, sf::Vector2f aEntityPos, sf::Vector2f aInteractionPos)
{
	//Shows card with one answer
	switch(m_showWhat)
	{
	case ShowQuestion:
		ManageQuestion(aWindow);
		m_state = DialogStateEnum::ContinueDialog;
		if(m_wasMousePressed)
			m_showWhat = ShowAnswer;
		return &m_cardId;
	case ShowAnswer:
		m_answers[0]->ManageAnswer(aWindow, aEntityPos, aInteractionPos);
		if(m_wasMousePressed)
		{
			string* wString = m_answers[0]->GetTargetId();
			if(*wString == "")
				return EndDialog();
			else
			{
				m_showWhat = ShowWhatEnum::ShowQuestion;
				return wString;
			}
		}
		else
			return &m_cardId;
}
}

string* CardCls::ShowQuestionAndAnswers(sf::RenderWindow &aWindow, sf::Vector2f aEntityPos, sf::Vector2f aInteractionPos)
{
	//Show cards with several answers
	ManageQuestion(aWindow);
	int wY = DISPLAY_HEIGHT-TEXT_SIZE-10;
	for(int i=GetNrOfAnswers()-1; i>=0; i--)
	{
		string* wFlag = m_answers[i]->GetNeedFlag();
		bool wBoolFlag = FlagManager::GetInstance()->IsFlagSet(*wFlag);
		if(wBoolFlag || *wFlag == "")
		{
			m_answers[i]->ManageAnswerS(aWindow, wY);
			wY-=(TEXT_SIZE+3);
		}
		else
		{
		}

	}
	m_state = DialogStateEnum::WaitForAnswer;
	return &m_cardId;
}

void CardCls::ManageQuestion(sf::RenderWindow &aWindow)
{
	sf::Color NPCQuestionColor(226, 90, 75);
	if(m_textPlace == "NPC")
	{
		//manage the text when NPC "says" something
		string tmpString = m_questionText.getString();
		if(m_entityPos.x < m_interactionNode.x && tmpString.size() <= 10)
		{
			m_entityPos.x = m_entityPos.x + 100;
		}
		m_questionText.setPosition(m_entityPos.x, m_entityPos.y);
		m_questionText.setColor(NPCQuestionColor);
	}
	else
	{
		//manage the text when Player "says" something
		string tmpString = m_questionText.getString();
		if(m_entityPos.x > m_interactionNode.x && tmpString.size() <= 10)
		{
			m_interactionNode.x = m_interactionNode.x+100;
		}
		m_questionText.setPosition(m_interactionNode);
		m_questionText.setColor(sf::Color::White);
	}
	m_questionText.setFont(GameManager::GetInstance()->GetFont());
	m_questionText.setCharacterSize(TEXT_SIZE);

	//outline1
	sf::Text outline1(m_questionText);
	outline1.setColor(sf::Color::Black);
	outline1.setCharacterSize(TEXT_SIZE);
	outline1.setFont(GameManager::GetInstance()->GetFont());
	outline1.setPosition(m_questionText.getPosition().x+1, m_questionText.getPosition().y+1); 
	//outline1
	sf::Text outline2(m_questionText);
	outline2.setColor(sf::Color::Black);
	outline2.setCharacterSize(TEXT_SIZE);
	outline2.setFont(GameManager::GetInstance()->GetFont());
	outline2.setPosition(m_questionText.getPosition().x+1, m_questionText.getPosition().y-1); 
	//outline1
	sf::Text outline3(m_questionText);
	outline3.setColor(sf::Color::Black);
	outline3.setCharacterSize(TEXT_SIZE);
	outline3.setFont(GameManager::GetInstance()->GetFont());
	outline3.setPosition(m_questionText.getPosition().x-1, m_questionText.getPosition().y+1); 
	//outline1
	sf::Text outline4(m_questionText);
	outline4.setColor(sf::Color::Black);
	outline4.setCharacterSize(TEXT_SIZE);
	outline4.setFont(GameManager::GetInstance()->GetFont());
	outline4.setPosition(m_questionText.getPosition().x-1, m_questionText.getPosition().y-1); 

	aWindow.draw(outline1);
	aWindow.draw(outline2);
	aWindow.draw(outline3);
	aWindow.draw(outline4);

	aWindow.draw(m_questionText);
	if(m_questionSetFlag != "")
	{
		FlagManager::GetInstance()->CreateFlag(m_questionSetFlag);
		m_questionSetFlag = "";
	}
}

void CardCls::IsMouseOverAnswer(sf::Vector2f* aMousePos)
{
	for(int i = 0; i < m_answers.size(); i++)
	{
		m_answers[i]->IsMouseOverAnswer(aMousePos);
	}
}

string* CardCls::GetCardId()
{
	return &m_cardId;
}

bool CardCls::LoadFromFile(DialogReaderWriter* aRw, TagCls* aTag)
{
	//Load the question and all the answers on this card
	int wMemberId;
	AnswerCls* wAnswer;
	bool isComplete = false;
	
	aRw->getTag(aTag);
	wMemberId = aRw->MapMemberName(m_members, aTag->getToken());
	while(!aRw->isEndOfFile() && !isComplete && 
		aTag->getToken() != CARD_ID && aTag->getToken() != DECK_ID)
	{
		switch(wMemberId)
		{
			case TARGET_ID:
				m_targetCardId = aTag->getValue();
				break;
			case TEXT_PLACE:
				m_textPlace = aTag->getValue();
				break;
			case QUESTION:
				{
				m_questionText = sf::Text(aTag->getValue());
				// Wrap text
				int chars_before_linebreak = 20;
				int charCounter = 0;

				sf::String tmpString = m_questionText.getString();

				// Iterate through the string
				for(int i = 0; i < tmpString.getSize(); i++)
				{
					if(charCounter >= chars_before_linebreak)
					{
						int rowBreak = tmpString.find(sf::String(" "), i);

						tmpString.insert(rowBreak+1, "\n");
						m_questionText.setString(tmpString);

						charCounter = 0;
					}
					charCounter++;
				}

				break;
				}
			case ANSWER:
				wAnswer = this->AddAnswer(aTag->getValue(), m_interactionNode, m_entityPos);
				wAnswer->LoadFromFile(aRw, aTag, &m_answers);
				isComplete = false;
				continue;
			case QUESTION_SET_FLAG:
				m_questionSetFlag = aTag->getValue();
				break;
			default:
				return true;
		}
		aRw->getTag(aTag);
		wMemberId = aRw->MapMemberName(m_members, aTag->getToken());
		if(aRw->isEndOfFile())
			return true;
	}
	return isComplete;
}

string* CardCls::EndDialog()
{
	m_showWhat = ShowWhatEnum::ShowQuestion;
	m_state = DialogStateEnum::EndDialog;
	m_wasMousePressed = false;
	return &m_targetCardId;
}

void CardCls::ContinueDialog()
{
	m_showWhat = ShowWhatEnum::ShowQuestion;
	m_state = DialogStateEnum::ContinueDialog;
}

int CardCls::GetNrOfAnswers()
{
	return m_answers.size();
}

DialogStateEnum CardCls::GetDialogState()
{
	return m_state;
}

string* CardCls::ChooseAnswer(sf::Vector2f* aMousePos)
{
	for(int i = 0; i<m_answers.size(); i++)
		if(m_answers[i]->isAnswerChoosen(aMousePos))
		{
			m_answers[i]->setChosen();
			m_state = DialogStateEnum::EndDialog;
			string* wTargetId = m_answers[i]->GetTargetId();
			if(*wTargetId == "")
				return EndDialog();
			else
			{
				ContinueDialog();
				return m_answers[i]->GetTargetId();
			}
		}
		return &m_cardId;
}

//Scriptfunc
AnswerCls* CardCls::AddAnswer(string aAnswerId, sf::Vector2f aInteractionNode,
		sf::Vector2f aEntityPos)
{
	AnswerCls* wAnswer = new AnswerCls(aAnswerId, aInteractionNode, aEntityPos);
	m_answers.push_back(wAnswer);
	return wAnswer;
}

CardCls::~CardCls(void)
{
}
