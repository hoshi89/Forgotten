#ifndef INCLUDED_MAINMENU
#define INCLUDED_MAINMENU

#include "Menu.h"
#include "MouseHandler.h"
#include <vector>
#include <SFML\Graphics.hpp>

class MainMenu{
public:
	MainMenu(MouseHandler& mouse);
	void Render(sf::RenderWindow& window);
	void Process();
	void IsOverSign(sf::RenderWindow& window);
	void IsOver(int i);
	bool GetButton();
	bool NewGame();
	bool Exit();
	bool Continue();
private:
	void SetRects();
	void LoadImage();
	void PushMenu();
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Text m_text;

	sf::IntRect m_continueRect;
	sf::IntRect m_newGameRect;
	sf::IntRect m_exitRect;

	bool m_newGame;
	bool m_exit;
	bool m_continue;

	sf::Sprite GetSprite();
	sf::View m_defaultView;
	sf::View m_view;
	sf::RectangleShape m_shape;

	MouseHandler& m_mouse;
};

#endif