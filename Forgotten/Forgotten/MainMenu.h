#ifndef INCLUDED_MAINMENU
#define INCLUDED_MAINMENU

#include "MouseHandler.h"
#include <SFML\Graphics.hpp>
#include <stack>

class MainMenu{
public:
	MainMenu();
	void Render(sf::RenderWindow& window);
	void Process();
	sf::IntRect GetRect();
private:
	void LoadImage();
	void PushMenu();
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Text m_text;
	sf::IntRect m_continueRect;
	sf::Sprite GetSprite();
	sf::View m_defaultView;
	sf::View m_view;
	sf::RectangleShape m_shape;
};

#endif