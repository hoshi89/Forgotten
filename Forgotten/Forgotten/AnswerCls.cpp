#include "AnswerCls.h"
#include "FlagManager.h"

AnswerCls::AnswerCls(string aAnswerId, sf::Vector2f aInteractionNode,
		sf::Vector2f aEntityPos): m_AnswerId(aAnswerId), m_EntityPos(aEntityPos),
		m_InteractionPos(aInteractionNode)
{
	m_Members.push_back(new CaseValues(TARGETSTR, TARGET_ID));
	m_Members.push_back(new CaseValues(TEXT_PLACESTR, TEXT_PLACE));
	m_Members.push_back(new CaseValues(ANSWERTEXTSTR, ANSWER_TEXT));
	m_Members.push_back(new CaseValues(ANSWERSETFLAG, ANSWER_SET_FLAG));
	m_Members.push_back(new CaseValues(ANSWERNEEDFLAG, ANSWER_NEED_FLAG));
}

bool AnswerCls::LoadFromFile(DialogReaderWriter* aRw, TagCls* aTag)
{
	//här ska vi ladda Answer som ligger under DETTA Card i loop från scriptfilen
	int wMemberId;
	bool isComplete = false;

	aRw->getTag(aTag);
	wMemberId = aRw->MapMemberName(m_Members, aTag->getToken());
 	while(!aRw->isEndOfFile() && !isComplete)
	{
		switch(wMemberId)
		{
			case TARGET_ID:
				m_TargetCardId = aTag->getValue();
				break;
			case TEXT_PLACE:
				m_TextPlace = aTag->getValue();
				break;
			case ANSWER_TEXT:
				{
				m_AnswerText = sf::Text(aTag->getValue());
				// Wrap text
				int chars_before_linebreak = 20;
				int charCounter = 0;

				sf::String tmpString = m_AnswerText.getString();

				// Iterate through the string
				for(int i = 0; i < tmpString.getSize(); i++)
				{
					if(charCounter >= chars_before_linebreak)
					{
						int rowBreak = tmpString.find(sf::String(" "), i);

						tmpString.insert(rowBreak+1, "\n");
						m_AnswerText.setString(tmpString);

						charCounter = 0;
					}
					charCounter++;
				}
				break;
				}
			case ANSWER_SET_FLAG:
				m_AnswerSetFlag = aTag->getValue();
				break;
			case ANSWER_NEED_FLAG:
				m_AnswerNeedFlag = aTag->getValue();
				break;
			default:
				return true;
		}
		aRw->getTag(aTag);
		wMemberId = aRw->MapMemberName(m_Members, aTag->getToken());
		if(aRw->isEndOfFile())
			return true;
	}
	return true;
}

void AnswerCls::ManageAnswer(sf::RenderWindow &aWindow, sf::Vector2f aEntityPos, sf::Vector2f aInteractionPos)
{
	if(m_TextPlace == "NPC")
	{
		string tmpString = m_AnswerText.getString();
		if(m_EntityPos.x < m_InteractionPos.x && tmpString.size() <= 10)
			aEntityPos.x = aEntityPos.x+100;
		m_AnswerText.setPosition(aEntityPos);
		m_AnswerText.setColor(sf::Color::White);
	}
	else
	{
		string tmpString = m_AnswerText.getString();
		if(m_EntityPos.x > m_InteractionPos.x && tmpString.size() <= 20)
			aInteractionPos.x = aInteractionPos.x+100;
		m_AnswerText.setPosition(aInteractionPos);
		m_AnswerText.setColor(sf::Color::Cyan);
	}

	sf::Text outline1(m_AnswerText);
	outline1.setColor(sf::Color::Black);
	outline1.setCharacterSize(TEXT_SIZE);
	outline1.setPosition(m_AnswerText.getPosition().x+1, m_AnswerText.getPosition().y+1); 
	//outline1
	sf::Text outline2(m_AnswerText);
	outline2.setColor(sf::Color::Black);
	outline2.setCharacterSize(TEXT_SIZE);
	outline2.setPosition(m_AnswerText.getPosition().x+1, m_AnswerText.getPosition().y-1); 
	//outline1
	sf::Text outline3(m_AnswerText);
	outline3.setColor(sf::Color::Black);
	outline3.setCharacterSize(TEXT_SIZE);
	outline3.setPosition(m_AnswerText.getPosition().x-1, m_AnswerText.getPosition().y+1); 
	//outline1
	sf::Text outline4(m_AnswerText);
	outline4.setColor(sf::Color::Black);
	outline4.setCharacterSize(TEXT_SIZE);
	outline4.setPosition(m_AnswerText.getPosition().x-1, m_AnswerText.getPosition().y-1); 

	aWindow.draw(outline1);
	aWindow.draw(outline2);
	aWindow.draw(outline3);
	aWindow.draw(outline4);

	m_AnswerText.setCharacterSize(TEXT_SIZE);
	aWindow.draw(m_AnswerText);	
	//string wStr = string(m_AnswerText.getString());
	//wStr = wStr+"siodj";
}

string* AnswerCls::GetTargetId()
{
	return &m_TargetCardId;
}

void AnswerCls::ManageAnswerS(sf::RenderWindow &aWindow, int aYpos)
{
	m_AnswerText.setPosition(10, aYpos);
	m_AnswerText.setCharacterSize(25);
	m_AnswerText.setColor(sf::Color::Cyan);
	//sf::RectangleShape* wRectShape = new sf::RectangleShape();
	//wRectShape->getGlobalBounds() = m_AnswerText.getGlobalBounds();
	//wRectShape->setPosition(30, 400);
	//wRectShape->setFillColor(sf::Color::Red);
	//aWindow.draw(*wRectShape);
	//sf::Text outline1(m_AnswerText);
	//outline1.setColor(sf::Color::Black);
	//outline1.setCharacterSize(TEXT_SIZE);
	//outline1.setPosition(m_AnswerText.getPosition().x+1, m_AnswerText.getPosition().y+1); 
	////outline1
	//sf::Text outline2(m_AnswerText);
	//outline2.setColor(sf::Color::Black);
	//outline2.setCharacterSize(TEXT_SIZE);
	//outline2.setPosition(m_AnswerText.getPosition().x+1, m_AnswerText.getPosition().y-1); 
	////outline1
	//sf::Text outline3(m_AnswerText);
	//outline3.setColor(sf::Color::Black);
	//outline3.setCharacterSize(TEXT_SIZE);
	//outline3.setPosition(m_AnswerText.getPosition().x-1, m_AnswerText.getPosition().y+1); 
	////outline1
	//sf::Text outline4(m_AnswerText);
	//outline4.setColor(sf::Color::Black);
	//outline4.setCharacterSize(TEXT_SIZE);
	//outline4.setPosition(m_AnswerText.getPosition().x-1, m_AnswerText.getPosition().y-1); 

	//aWindow.draw(outline1);
	//aWindow.draw(outline2);
	//aWindow.draw(outline3);
	//aWindow.draw(outline4);

	aWindow.draw(m_AnswerText);
	if(m_AnswerSetFlag != "")
	{
		FlagManager::GetInstance()->CreateFlag(m_AnswerSetFlag);
		m_AnswerSetFlag = "";
	}

}

bool AnswerCls::isAnswerChoosen(sf::Vector2f* aMousePos)
{
	sf::FloatRect* wRect = &m_AnswerText.getGlobalBounds();
	return wRect->contains(*aMousePos);
}

string* AnswerCls::GetAnswerId()
{
	return &m_AnswerId;
}

string* AnswerCls::GetNeedFlag()
{
	return &m_AnswerNeedFlag;
}

AnswerCls::~AnswerCls(void)
{
}
