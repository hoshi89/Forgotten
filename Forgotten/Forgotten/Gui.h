#ifndef INCLUDED_GUI
#define INCLUDED_GUI

#include "Inventory.h"
#include "MouseHandler.h"
#include "ScriptText.h"

#include "LevelDialogsCls.h"
//#include <SFML/Graphics.hpp>

class Gui{
public:
	Gui(MouseHandler& mouse);
	void Render();
	void IsOverlap(sf::RenderWindow &window);
	void Update();
	sf::Vector2f GetPosition();
	void Draw(sf::RenderWindow &window);
	void PushText(std::string text, int time, sf::Vector2f position);
	void DeleteText();
	void SetShowGui(bool showGui);

	//Dialog
	void SetDeckId(string aDeckId);
	void WaitingForAnswer(bool aIsWait, MouseHandler* aMouse);

private:
	void Move(const float SPEED);
	int LoadImage();
	sf::Texture m_gui;
	sf::Sprite m_guiSprite;
	sf::Vector2f m_position;
	sf::IntRect m_textureRect;
	sf::View m_guiview;
	bool m_down;
	sf::IntRect GetRect();
	MouseHandler& m_mouseHandler;
	sf::Text m_text;
	sf::Text* p_text;
	typedef std::vector<ScriptText*> TextVector;
	TextVector m_texts;
	void DrawText(sf::RenderWindow& window);
	sf::Clock m_clock;
	bool m_showGui;
	bool m_showItems;

	//Dialog
	bool m_isWaitingForAnswer;
	string m_DeckId;
	bool m_isDialogState;
	MouseHandler* m_MouseHandler;
};

#endif