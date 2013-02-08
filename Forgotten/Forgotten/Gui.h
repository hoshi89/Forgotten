#ifndef INCLUDED_GUI
#define INCLUDED_GUI

#include <SFML/Graphics.hpp>

class Gui{
public:
	Gui(sf::Vector2f position);
	//sf::IntRect GetRect();
	void Render(sf::RenderWindow &window);
	sf::Vector2f GetPosition();
	bool down;
	void IsOverlap(sf::IntRect rect);
private:
	sf::IntRect GetRect();
	void Move(const float SPEED);
	void Draw(sf::RenderWindow & window);
	int LoadImage();
	sf::Texture m_inventory;
	sf::Sprite m_inventorySprite;
	sf::Vector2f m_position;
	sf::IntRect m_textureRect;
};

#endif