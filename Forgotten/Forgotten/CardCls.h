#pragma once

#include <SFML\Graphics.hpp>
#include "AnswerCls.h"
#include <vector>

const sf::Time QUESTION_ELAPSED_TIME = sf::microseconds(5000000);
const sf::Time ANSWER_ELAPSED_TIME = sf::microseconds(2*5000000);
const int DISPLAY_HEIGHT = 576;

enum DialogStateEnum {EndDialog, ContinueDialog, WaitForAnswer};

using namespace std;
class CardCls
{
public:
	CardCls(string aId);
	string* ShowCard(sf::RenderWindow &aWindow, sf::Vector2f aInteractionNode,
				sf::Vector2f aEntityPos);
	bool LoadFromFile(DialogReaderWriter* aRw, TagCls* aTag);
	string* GetCardId();
	DialogStateEnum GetDialogState();
	string* ChooseAnswer(sf::Vector2f* aMousePos);

	//Scriptfunc
	AnswerCls* AddAnswer(string aAnswerId);
	virtual ~CardCls(void);
private:
	static const int TARGET_ID = 1;
	static const int TEXT_PLACE = 2;
	static const int ANSWER = 3;
	static const int QUESTION = 4;

	string m_CardId;
	vector<AnswerCls*> m_Answers;
	sf::Clock *m_Clock;
	string m_TextPlace;
	sf::Vector2f m_EntityPos;
	sf::Vector2f m_InteractionNode;
	string m_TargetCardId;
	DialogStateEnum m_State;
	sf::Text m_QuestionText;
	MapVector m_Members;

	string* ShowOnlyQuestion(sf::RenderWindow &aWindow);
	string* ShowQuestionAndOneAnswer(sf::RenderWindow &aWindow,  sf::Vector2f aEntityPos, sf::Vector2f aInteractionPos);
	string* ShowQuestionAndAnswers(sf::RenderWindow &aWindow, sf::Vector2f aEntityPos, sf::Vector2f aInteractionPos);
	int GetNrOfAnswers();
	void ManageQuestion(sf::RenderWindow &aWindow);
	string* EndDialog();
	void ContinueDialog();
};