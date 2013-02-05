#ifndef INCLUDED_GUI
#define INCLUDED_GUI

#include <SFML/Graphics.hpp>

class Gui{
public:
	Gui(sf::Vector2f position);
	void Render(sf::RenderWindow &window);	
private:
	void Move(float y, float offset);
	void Draw(sf::RenderWindow & window);
	int LoadImage();
	sf::Texture m_inventory;
	sf::Sprite m_inventorySprite;
	sf::Vector2f m_position;
};

#endif