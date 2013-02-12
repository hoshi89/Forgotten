#pragma once
#include "DialogCls.h"
#include "Player.h"
#include <SFML\Graphics.hpp>
#include "Entity.h"

const sf::Time QUESTION_ELAPSED_TIME = sf::microseconds(5000000);
const sf::Time ANSWER_ELAPSED_TIME = sf::microseconds(2*5000000);
const int DISPLAY_HEIGHT = 576;
const int TEXT_SIZE = 12;

class DialogOwnerCls: public Entity
{
public:
	DialogOwnerCls(const char *aDeckName, int aXpos, int aYpos,
		Player *aPlayer, const string aSpriteName);
//	virtual void SetPosition(int x, int y) abstract;
	virtual void Render(sf::RenderWindow &aWindow) override;
	virtual void Update() override;
	virtual const int GetZ() abstract;
	virtual void ChoosedByMouse() override;

	//	string m_currentString;
//	sf::Text m_currentText;
//	void BeginDialog();
//	virtual void AddToInventory();
//	virtual	sf::Vector2f PlaceText(DialogCls aDialog) abstract;
	DialogCls mDialog;
	virtual ~DialogOwnerCls(void);
	Player *m_player;
	Animation m_currentAnimation;
private:
//	sf::IntRect getQuestionRect();
	bool isIntersect();
	sf::IntRect *aTextRect;
	bool m_Choosed;
	int posX;
	int posY;
	sf::Clock *myClock;
	void EndDialog();
	void BeginCard();
	void ShowOnlyQuestion(sf::RenderWindow &aWindow);
	void ShowQuestionAndOneAnswer(sf::RenderWindow &aWindow);
	void ShowQuestionAndAnswers(sf::RenderWindow &aWindow);
	void ManageText(const char* aText, const char* aUserData,
		sf::RenderWindow &aWindow);
	void ManageAnswers(const char* aText, sf::RenderWindow &aWindow,
		int aYpos);
//	sf::Vector2f *m_playerPosition;
};

