#include "AnswerCls.h"

AnswerCls::AnswerCls(string aAnswerId): m_AnswerId(aAnswerId)
{
	m_Members.push_back(new CaseValues(TARGETSTR, TARGET_ID));
	m_Members.push_back(new CaseValues(TEXT_PLACESTR, TEXT_PLACE));
	m_Members.push_back(new CaseValues(ANSWERTEXTSTR, ANSWER_TEXT));
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
				m_AnswerText = sf::Text(aTag->getValue());
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

void AnswerCls::ManageAnswer(sf::RenderWindow &aWindow)
{
	if(m_TextPlace == "NPC")
	{
		m_AnswerText.setPosition(400, 400);
		m_AnswerText.setColor(sf::Color::White);
	}
	else
	{
		m_AnswerText.setPosition(200, 200);
		m_AnswerText.setColor(sf::Color::Cyan);
	}

	m_AnswerText.setStyle(sf::Text::Bold);
	m_AnswerText.setCharacterSize(TEXT_SIZE);
	aWindow.draw(m_AnswerText);	
	string wStr = string(m_AnswerText.getString());
	wStr = wStr+"siodj";
}

string* AnswerCls::GetTargetId()
{
	return &m_TargetCardId;
}

void AnswerCls::ManageAnswerS(sf::RenderWindow &aWindow, int aYpos)
{
	m_AnswerText.setPosition(100, aYpos);
	m_AnswerText.setCharacterSize(25);
	m_AnswerText.setColor(sf::Color::Cyan);
	m_AnswerText.setStyle(sf::Text::Bold);
	aWindow.draw(m_AnswerText);	
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

AnswerCls::~AnswerCls(void)
{
}
