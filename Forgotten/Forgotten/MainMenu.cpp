#include "MainMenu.h"

MainMenu::MainMenu()
{
	LoadImage();
	// Set the view size
	m_view.setSize(1024, 576);
	m_view.setCenter(800, 288);
}

void MainMenu::LoadImage()
{
	m_texture.loadFromFile("Data/DaMenyz.png");
	m_sprite.setTexture(m_texture);
}

sf::IntRect MainMenu::GetRect()
{
	
	m_shape.setFillColor(sf::Color::Blue);
	m_shape.setSize(sf::Vector2f(400, 50));
	sf::IntRect rect = sf::IntRect(m_shape.getPosition().x, m_shape.getPosition().y, m_shape.getSize().x, m_shape.getSize().y);
	m_shape.setTextureRect(rect);
	return m_shape.getTextureRect();
}

void MainMenu::Render(sf::RenderWindow& window)
{
	// Clear the screen 
	window.clear(sf::Color(0, 0, 0));

	// Set the game view
	window.setView(m_view);

	// Set the game view again
	window.setView(m_view);

	window.draw(m_sprite);

	window.draw(m_shape);

	// Display all rendered items
	window.display();
}

void MainMenu::Process()
{
	GetRect();
}
