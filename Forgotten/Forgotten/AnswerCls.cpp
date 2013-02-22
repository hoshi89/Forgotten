#include "AnswerCls.h"


AnswerCls::AnswerCls(string aAnswerId, string aTargetId) :m_AnswerId(aAnswerId),
	m_TargetCardId(aTargetId)
{
	m_TextPlace = "ickeNPC";
}

void AnswerCls::LoadFromFile(string aAnswerText)
{
	//här ska vi ladda Answer som ligger under DETTA Card i loop från scriptfilen
	m_AnswerText = aAnswerText;
}

string AnswerCls::ManageAnswer(sf::RenderWindow &aWindow)
{
	sf::Text wAnswer = sf::Text(m_AnswerText);
	if(m_TextPlace.compare("NPC"))
		wAnswer.setPosition(400, 400);
	else
	{
		wAnswer.setPosition(200, 200);
	}
	wAnswer.setCharacterSize(25);
	wAnswer.setColor(sf::Color::Cyan);
	aWindow.draw(wAnswer);	

	return m_TargetCardId;
}

string AnswerCls::GetTargetId()
{
	return m_TargetCardId;
}
AnswerCls::~AnswerCls(void)
{
}
