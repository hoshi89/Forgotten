#include "DialogOwnerCls.h"


DialogOwnerCls::DialogOwnerCls(const char *aDeckName, int aXpos, int aYpos,
	Player *aPlayer, const string aSpriteName)
	: mDialog(aDeckName), m_player(aPlayer), m_currentAnimation(aSpriteName, 10000, 1)

{
	mDialog = DialogCls::DialogCls(aDeckName);
	posX = aXpos;
	posY = aYpos;
	myClock = NULL;
}

void DialogOwnerCls::ChoosedByMouse()
{
	m_Choosed = true;
}

void DialogOwnerCls::Render(sf::RenderWindow &aWindow)
{
	aWindow.draw(m_currentAnimation.getSprite());


	if(!m_Choosed)
		return;
	if(!isIntersect())
		return;
	
	if(mDialog.GetNrOfAnswers() == 0)
		ShowOnlyQuestion(aWindow);
	else
		if(mDialog.GetNrOfAnswers() == 1)
			ShowQuestionAndOneAnswer(aWindow);
		else
			ShowQuestionAndAnswers(aWindow);	
	//här ska alla svar skrivas ut nere i hörn och frågan över ngn..
//			std::vector<const char*> currentText = ManageText();
//	aWindow.draw(currentText);
	
	
}

void DialogOwnerCls::Update()
{
	m_currentAnimation.setPosition(sf::Vector2f(posX, posY));
	m_currentAnimation.update();
}

void DialogOwnerCls::ManageText(const char* aText, const char* aUserData,
	sf::RenderWindow &aWindow)
{
	//std::vector<const char*> wCurrentText = mDialog.getCurrentText();
	//return wCurrentText;
	sf::Text wText = sf::Text(aText);
	if(aUserData[0] == 'D')
		wText.setPosition(posX, posY-20);
	else
	{
		//int wX = m_player->GetPosition().x;
		//int wY = m_player->GetPosition().y;	Snacka med robin
		int wX = 100;
		int wY = 300;
		wText.setPosition(wX, wY);
	}
	wText.setCharacterSize(TEXT_SIZE);
	wText.setColor(sf::Color::White);
	aWindow.draw(wText);
	

}

bool DialogOwnerCls::isIntersect()
{
	return true;
}

void DialogOwnerCls::ShowOnlyQuestion(sf::RenderWindow &aWindow)
{
	if(myClock==NULL)
		myClock = new sf::Clock();
	
	if(myClock->getElapsedTime() < QUESTION_ELAPSED_TIME)
	{
		const char* wQuestion = mDialog.getQuestion();
		const char* wCardUserData = mDialog.getQuestionUserData();
		ManageText(wQuestion, wCardUserData, aWindow);
	}
	else
		EndDialog();
}

void DialogOwnerCls::ShowQuestionAndOneAnswer(sf::RenderWindow &aWindow)
{
	if(myClock==NULL)
		myClock = new sf::Clock();
	int wIsAnswerChosen;
	if(myClock->getElapsedTime() < QUESTION_ELAPSED_TIME)
	{
		const char* wQuestion = mDialog.getQuestion();
		const char* wCardUserData = mDialog.getQuestionUserData();
		ManageText(wQuestion, wCardUserData, aWindow);
	}
	else 
		if(myClock->getElapsedTime() < ANSWER_ELAPSED_TIME)
		{
			const char* wAnswer = mDialog.getAnswer(0);
			const char* wCardUserData = mDialog.getAnswerUserData(0);
			ManageText(wAnswer, wCardUserData, aWindow);
		}
		else
		{
			wIsAnswerChosen = mDialog.ChooseAnswer(0);
			if(wIsAnswerChosen == 0)
				myClock->restart();
			else
				EndDialog();
		}

}

void DialogOwnerCls::ShowQuestionAndAnswers(sf::RenderWindow &aWindow)
{
	const char* wQuestion = mDialog.getQuestion();
	const char* wCardUserData = mDialog.getQuestionUserData();
	ManageText(wQuestion, wCardUserData, aWindow);

	const char* wAnswer;
	int wY = DISPLAY_HEIGHT-TEXT_SIZE-10;
	for(int i=mDialog.GetNrOfAnswers(); i>=0; i--)
	{
		wAnswer = mDialog.getAnswer(i);
		ManageAnswers(wAnswer, aWindow, wY);
		wY-=(TEXT_SIZE+3);
	}

}

void DialogOwnerCls::ManageAnswers(const char* aText, sf::RenderWindow &aWindow,
		int aYpos)
{
	sf::Text wText = sf::Text(aText);

	wText.setCharacterSize(TEXT_SIZE);
	wText.setColor(sf::Color::White);
	wText.setPosition(10, aYpos);
	aWindow.draw(wText);

}

void BeginCard()
{

}
void DialogOwnerCls::EndDialog()
{
	myClock = NULL;
	m_Choosed = false;
	//avsluta "paus-läge"
}
//void DialogOwnerCls::BeginDialog()
//{
//	//den här funktionen anropas när dialogen ska börja..
//}

//void DialogOwnerCls::AddToInventory()
//{
//	//default är det ett objekt som lägger till sig själv till inventory
//	//override för NPC lägger till objekt som NPC:n ger dig
//	//InventoryVector.pushback(objekt) ..
//	//Den här funktionen skickar ALLTID det som inventory ska innehålla!
//}

//void DialogOwnerCls::PlaceText(DialogCls aDialog)
//{
//}


//sf::IntRect DialogOwnerCls::getQuestionRect()
//{
//	if(mDialog.PlayerOwnCard())
//	{
//		m_player->GetPosition();
//	}
//
//}

DialogOwnerCls::~DialogOwnerCls(void)
{
}
