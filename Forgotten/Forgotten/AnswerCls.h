#pragma once

#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>
#include <string>
#include <map>
#include "DialogReaderWriter.h"

using namespace std;

const int TEXT_SIZE = 24;

class AnswerCls
{
public:
	AnswerCls(string aAnswerId,  sf::Vector2f aInteractionNode,
		sf::Vector2f aEntityPos);
	void ManageAnswer(sf::RenderWindow &aWindow,
		sf::Vector2f aEntityPos, sf::Vector2f aInteractionPos);
	void ManageAnswerS(sf::RenderWindow &aWindow, int aYpos);
	string* GetTargetId();
	bool LoadFromFile(DialogReaderWriter* aRw, TagCls* aTag, vector<AnswerCls*>* aNrOfAnswers);
	virtual ~AnswerCls(void);
	bool isAnswerChoosen(sf::Vector2f* aMousePos);
	void IsMouseOverAnswer(sf::Vector2f* aMousePos);
	string* GetAnswerId();
	string* GetNeedFlag();
	void setChosen();
	bool getChosen();
private:
	static const int TARGET_ID = 1;
	static const int TEXT_PLACE = 2;
	static const int ANSWER_TEXT = 3;
	static const int ANSWER_SET_FLAG = 4;
	static const int ANSWER_NEED_FLAG = 5;

	bool m_mouseOverAnswer;
	string m_answerId;
	string m_textPlace;
	string m_targetCardId;
	string m_answerSetFlag;
	string m_answerNeedFlag;
	sf::Text m_answerText;
	MapVector m_members;
	sf::Vector2f m_entityPos;
	sf::Vector2f m_interactionPos;
	bool m_hasAnswerBeenChosen;
};