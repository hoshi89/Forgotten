#ifndef INCLUDED_GUI
#define INCLUDED_GUI

#include "Inventory.h"
#include "MouseHandler.h"
#include <SFML/Graphics.hpp>

class Gui{
public:
	Gui(MouseHandler& mouse);
	void Render();
	void IsOverlap();
	void Update();
	sf::Vector2f GetPosition();
	void Draw(sf::RenderWindow &window);
private:
	//sf::IntRect GetRect();
	void Move(const float SPEED);
	int LoadImage();
	sf::Texture m_gui;
	sf::Sprite m_guiSprite;
	sf::Vector2f m_position;
	sf::IntRect m_textureRect;
	bool m_down;
	sf::IntRect GetRect();
	MouseHandler& m_mouseHandler;
};

#endif