#ifndef INCLUDED_GUI
#define INCLUDED_GUI

#include "Inventory.h"
#include "MouseHandler.h"
#include "ScriptText.h"
#include "LevelDialogsCls.h"
//#include <SFML/Graphics.hpp>

class Gui
{
public:
	Gui(MouseHandler& mouse);
	void Update();
	sf::Vector2f GetPosition();
	void Draw(sf::RenderWindow &window);
	void PushText(std::string text, int time, sf::Vector2f position, int rowbreak, std::string style, sf::Color color, int fontsize);
	void DeleteText();
	void SetShowGui(bool showGui);
	Animation* GetIdCursor(int id);
	sf::IntRect GetRect();
	void SetIsDownGui(bool down);
	int ItemInHand();
	void IsInScript(bool script);
	void RemoveHand();
	bool WaitForText();

	// Dialog
	void SetDeckId(string aDeckId, sf::Vector2f aPlayerpos, sf::Vector2f aEntitypos);
	void AddItem(int Id);
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

	typedef std::vector<ScriptText*> TextVector;
	TextVector m_texts;
	int m_itemInHand;
	bool m_waitForText;

	void DrawText(sf::RenderWindow& window);
	sf::Clock m_clock;
	bool m_showGui;
	bool m_showItems;
	bool m_script;
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
	sf::Vector2f m_PlayerPos;
	sf::Vector2f m_EntityPos;
	DialogStateEnum m_DialogState;
};

#endif