#include "AnswerCls.h"
#include "FlagManager.h"
#include "GameManager.h"

AnswerCls::AnswerCls(string aAnswerId, sf::Vector2f aInteractionNode,
		sf::Vector2f aEntityPos): m_answerId(aAnswerId), m_entityPos(aEntityPos),
		m_interactionPos(aInteractionNode)
{
	m_mouseOverAnswer = false;
	m_members.push_back(new CaseValues(TARGETSTR, TARGET_ID));
	m_members.push_back(new CaseValues(TEXT_PLACESTR, TEXT_PLACE));
	m_members.push_back(new CaseValues(ANSWERTEXTSTR, ANSWER_TEXT));
	m_members.push_back(new CaseValues(ANSWERSETFLAG, ANSWER_SET_FLAG));
	m_members.push_back(new CaseValues(ANSWERNEEDFLAG, ANSWER_NEED_FLAG));
}

bool AnswerCls::LoadFromFile(DialogReaderWriter* aRw, TagCls* aTag, vector<AnswerCls*>* aNrOfAnswers)
{
	//här ska vi ladda Answer som ligger under DETTA Card i loop från scriptfilen
	int wMemberId;
	bool isComplete = false;

	aRw->getTag(aTag);
	wMemberId = aRw->MapMemberName(m_members, aTag->getToken());
 	while(!aRw->isEndOfFile() && !isComplete)
	{
		switch(wMemberId)
		{
			case TARGET_ID:
				m_targetCardId = aTag->getValue();
				break;
			case TEXT_PLACE:
				m_textPlace = aTag->getValue();
				break;
			case ANSWER_TEXT:
				{
				m_answerText = sf::Text(aTag->getValue());

				// Wrap text
				int chars_before_linebreak = 20;
				int charCounter = 0;
				sf::String tmpString = m_answerText.getString();
				//om antalet svar är 1 eller mindre så ska vi göra radbrytning annars inte
				if(aNrOfAnswers->size() <= 1)
				{
				// Iterate through the string
					for(int i = 0; i < tmpString.getSize(); i++)
					{
						if(charCounter >= chars_before_linebreak && charCounter <= 40)
						{
							int rowBreak = tmpString.find(sf::String(" "), i);

							tmpString.insert(rowBreak+1, "\n");
							m_answerText.setString(tmpString);

							charCounter = 0;
						}
						charCounter++;
					}
				}
				break;
				}
			case ANSWER_SET_FLAG:
				m_answerSetFlag = aTag->getValue();
				break;
			case ANSWER_NEED_FLAG:
				m_answerNeedFlag = aTag->getValue();
				break;
			default:
				return true;
		}
		aRw->getTag(aTag);
		wMemberId = aRw->MapMemberName(m_members, aTag->getToken());
		if(aRw->isEndOfFile())
			return true;
	}
	return true;
}

void AnswerCls::ManageAnswer(sf::RenderWindow &aWindow, sf::Vector2f aEntityPos, sf::Vector2f aInteractionPos)
{
	sf::Color NPCAnswerColor(226, 90, 75);
	if(m_textPlace == "NPC")
	{
		string tmpString = m_answerText.getString();
		if(m_entityPos.x < m_interactionPos.x && tmpString.size() <= 10)
			aEntityPos.x = aEntityPos.x+100;
		m_answerText.setPosition(aEntityPos);
		m_answerText.setColor(NPCAnswerColor);
	}
	else
	{
		string tmpString = m_answerText.getString();
		if(m_entityPos.x > m_interactionPos.x && tmpString.size() <= 20)
			aInteractionPos.x = aInteractionPos.x+100;
		m_answerText.setPosition(aInteractionPos);
		m_answerText.setColor(sf::Color::White);
	}

	sf::Text outline1(m_answerText);
	outline1.setColor(sf::Color::Black);
	outline1.setCharacterSize(TEXT_SIZE);
	outline1.setFont(GameManager::GetInstance()->GetFont());
	outline1.setPosition(m_answerText.getPosition().x+1, m_answerText.getPosition().y+1); 
	//outline1
	sf::Text outline2(m_answerText);
	outline2.setColor(sf::Color::Black);
	outline2.setCharacterSize(TEXT_SIZE);
	outline2.setFont(GameManager::GetInstance()->GetFont());
	outline2.setPosition(m_answerText.getPosition().x+1, m_answerText.getPosition().y-1); 
	//outline1
	sf::Text outline3(m_answerText);
	outline3.setColor(sf::Color::Black);
	outline3.setCharacterSize(TEXT_SIZE);
	outline3.setFont(GameManager::GetInstance()->GetFont());
	outline3.setPosition(m_answerText.getPosition().x-1, m_answerText.getPosition().y+1); 
	//outline1
	sf::Text outline4(m_answerText);
	outline4.setColor(sf::Color::Black);
	outline4.setCharacterSize(TEXT_SIZE);
	outline4.setFont(GameManager::GetInstance()->GetFont());
	outline4.setPosition(m_answerText.getPosition().x-1, m_answerText.getPosition().y-1); 

	aWindow.draw(outline1);
	aWindow.draw(outline2);
	aWindow.draw(outline3);
	aWindow.draw(outline4);

	m_answerText.setCharacterSize(TEXT_SIZE);
	m_answerText.setFont(GameManager::GetInstance()->GetFont());
	aWindow.draw(m_answerText);	
	string wStr = string(m_answerText.getString());
	wStr = wStr+"siodj";
}

string* AnswerCls::GetTargetId()
{
	return &m_targetCardId;
}

void AnswerCls::ManageAnswerS(sf::RenderWindow &aWindow, int aYpos)
{
	sf::Color answerScolor(255, 209, 138);
	sf::Color answerHasBeenChosenColor(255, 157, 28);
	if(m_hasAnswerBeenChosen == true)
		m_answerText.setColor(answerHasBeenChosenColor);
	else
		m_answerText.setColor(answerScolor);

	m_answerText.setPosition(10, aYpos);
	m_answerText.setCharacterSize(TEXT_SIZE);
	if(m_mouseOverAnswer)
		m_answerText.setColor(sf::Color::Blue);

	sf::Text outline1(m_answerText);
	outline1.setColor(sf::Color::Black);
	outline1.setCharacterSize(TEXT_SIZE);
	outline1.setFont(GameManager::GetInstance()->GetFont());
	outline1.setPosition(m_answerText.getPosition().x+1, m_answerText.getPosition().y+1); 
	//outline1
	sf::Text outline2(m_answerText);
	outline2.setColor(sf::Color::Black);
	outline2.setCharacterSize(TEXT_SIZE);
	outline2.setFont(GameManager::GetInstance()->GetFont());
	outline2.setPosition(m_answerText.getPosition().x+1, m_answerText.getPosition().y-1); 
	//outline1
	sf::Text outline3(m_answerText);
	outline3.setColor(sf::Color::Black);
	outline3.setCharacterSize(TEXT_SIZE);
	outline3.setFont(GameManager::GetInstance()->GetFont());
	outline3.setPosition(m_answerText.getPosition().x-1, m_answerText.getPosition().y+1); 
	//outline1
	sf::Text outline4(m_answerText);
	outline4.setColor(sf::Color::Black);
	outline4.setCharacterSize(TEXT_SIZE);
	outline4.setFont(GameManager::GetInstance()->GetFont());
	outline4.setPosition(m_answerText.getPosition().x-1, m_answerText.getPosition().y-1); 

	aWindow.draw(outline1);
	aWindow.draw(outline2);
	aWindow.draw(outline3);
	aWindow.draw(outline4);

	m_answerText.setFont(GameManager::GetInstance()->GetFont());
	aWindow.draw(m_answerText);
	if(m_answerSetFlag != "")
	{
		FlagManager::GetInstance()->CreateFlag(m_answerSetFlag);
		m_answerSetFlag = "";
	}

}

bool AnswerCls::isAnswerChoosen(sf::Vector2f* aMousePos)
{
	sf::FloatRect* wRect = &m_answerText.getGlobalBounds();
	return wRect->contains(*aMousePos);
}

void AnswerCls::IsMouseOverAnswer(sf::Vector2f* aMousePos)
{
	m_mouseOverAnswer = m_answerText.getGlobalBounds().contains(*aMousePos);
}	

string* AnswerCls::GetAnswerId()
{
	return &m_answerId;
}

string* AnswerCls::GetNeedFlag()
{
	return &m_answerNeedFlag;
}

void AnswerCls::setChosen()
{
	m_hasAnswerBeenChosen = true;
}

bool AnswerCls::getChosen()
{
	return m_hasAnswerBeenChosen;
}

AnswerCls::~AnswerCls(void)
{
}
