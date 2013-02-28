#ifndef INCLUDED_GUI
#define INCLUDED_GUI

#include "Inventory.h"
#include "MouseHandler.h"
#include "ScriptText.h"

#include "LevelDialogsCls.h"
//#include <SFML/Graphics.hpp>

using namespace std;

class Gui{
public:
	Gui(MouseHandler& mouse);
	void Render();
	void Update();
	sf::Vector2f GetPosition();
	void Draw(sf::RenderWindow &window);
	void PushText(std::string text, int time, sf::Vector2f position);
	void DeleteText();
	void SetShowGui(bool showGui);
	Animation* GetIdCursor(int id);
	sf::IntRect GetRect();
	void SetIsDownGui(bool down);

	// Dialog
	void SetDeckId(string aDeckId);
	void AddItem(int aId);
	DialogStateEnum getDialogState();

private:
	void Move(const float SPEED);
	int LoadImage();
	sf::Texture m_gui;
	sf::Sprite m_guiSprite;
	sf::Vector2f m_position;
	sf::IntRect m_textureRect;
	sf::View m_guiview;
	bool m_down;
	MouseHandler& m_mouseHandler;
	sf::Text m_text;
	sf::Text* p_text;
	typedef std::vector<ScriptText*> TextVector;
	TextVector m_texts;

	void DrawText(sf::RenderWindow& window);
	sf::Clock m_clock;
	bool m_showGui;
	bool m_showItems;
	std::ifstream m_objectFile;
	void IsOverlap(sf::RenderWindow &window);
	void IsOverItem();

	//Objects for MouseCursor
	typedef std::vector<Animation*>CursorVector;
	CursorVector m_objectCursor;
	void SetCursorVector();
	void LoadCursorImages();

	//Dialog
	string m_DeckId;
	DialogStateEnum m_DialogState;
};

#endif