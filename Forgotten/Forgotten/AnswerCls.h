#pragma once

#include <SFML\Graphics.hpp>

#include <string>


using namespace std;

class AnswerCls
{
public:
	AnswerCls(string aAnswerId, string aTargetId);

	string ManageAnswer(sf::RenderWindow &aWindow);
	string GetTargetId();
	void LoadFromFile(string aAnswerText);
	virtual ~AnswerCls(void);
private:
	string m_AnswerId;
	string m_TextPlace;
	string m_AnswerText;
	string m_TargetCardId;
};

