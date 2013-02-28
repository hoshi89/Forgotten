#include "AnswerCls.h"


AnswerCls::AnswerCls(string aAnswerId, string aTargetId) :m_AnswerId(aAnswerId),
	m_TargetCardId(aTargetId)
{
	m_TextPlace = "ickeNPC";
}

void AnswerCls::LoadFromFile(string aAnswerText)
{
	//här ska vi ladda Answer som ligger under DETTA Card i loop från scriptfilen
	m_Answer = aAnswerText;
	m_AnswerText = sf::Text(m_Answer);
}

void AnswerCls::ManageAnswer(sf::RenderWindow &aWindow)
{
	if(m_TextPlace == "NPC")
		m_AnswerText.setPosition(400, 400);
	else
	{
		m_AnswerText.setPosition(200, 200);
	}
	m_AnswerText.setCharacterSize(25);
	m_AnswerText.setColor(sf::Color::Cyan);
	aWindow.draw(m_AnswerText);	

	//return m_TargetCardId;
}

string* AnswerCls::GetTargetId()
{
	return &m_TargetCardId;
}

void AnswerCls::ManageAnswerS(sf::RenderWindow &aWindow, int aYpos)
{
	m_AnswerText.setPosition(20, aYpos);

	m_AnswerText.setCharacterSize(25);
	m_AnswerText.setColor(sf::Color::Cyan);
	aWindow.draw(m_AnswerText);	

}

bool AnswerCls::isAnswerChoosen(sf::Vector2f* aMousePos)
{
	sf::FloatRect* wRect = &m_AnswerText.getGlobalBounds();
	
	return wRect->contains(*aMousePos);
}
AnswerCls::~AnswerCls(void)
{
}
