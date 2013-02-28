#pragma once

#include <SFML\Graphics.hpp>

#include <string>


using namespace std;

class AnswerCls
{
public:
	AnswerCls(string aAnswerId, string aTargetId);

	void ManageAnswer(sf::RenderWindow &aWindow);
	void ManageAnswerS(sf::RenderWindow &aWindow, int aYpos);
	string* GetTargetId();
	void LoadFromFile(string aAnswerText);
	virtual ~AnswerCls(void);
	bool isAnswerChoosen(sf::Vector2f* aMousePos);
private:
	string m_AnswerId;
	string m_TextPlace;
	string m_Answer;
	string m_TargetCardId;
	sf::Text m_AnswerText;
};

