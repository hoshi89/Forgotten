#pragma once

#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>
#include <string>
#include <map>
#include "DialogReaderWriter.h"

using namespace std;

const int TEXT_SIZE = 17;

class AnswerCls
{
public:
	AnswerCls(string aAnswerId);
	void ManageAnswer(sf::RenderWindow &aWindow);
	void ManageAnswerS(sf::RenderWindow &aWindow, int aYpos);
	string* GetTargetId();
	bool LoadFromFile(DialogReaderWriter* aRw, TagCls* aTag);
	virtual ~AnswerCls(void);
	bool isAnswerChoosen(sf::Vector2f* aMousePos);
	string* GetAnswerId();
private:
	static const int TARGET_ID = 1;
	static const int TEXT_PLACE = 2;
	static const int ANSWER_TEXT = 3;

	string m_AnswerId;
	string m_TextPlace;
	string m_TargetCardId;
	sf::Text m_AnswerText;
	MapVector m_Members;
};