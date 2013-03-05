#include "MainMenu.h"

MainMenu::MainMenu(MouseHandler& mouse) : m_over(false), m_mouse(mouse)
{
	LoadImage();
	//// Set the view size
	m_view.setSize(1024, 576);
	m_view.setCenter(855, 288);
}

bool MainMenu::IsOver(){
	return m_over;
}

void MainMenu::LoadImage()
{
	m_texture.loadFromFile("Data/DaMenyz4.png");
	m_sprite.setTexture(m_texture);
}

sf::IntRect MainMenu::GetRect()
{
	m_shape.setFillColor(sf::Color::Blue);
	m_shape.setSize(sf::Vector2f(200, 100));
	m_shape.setPosition(400.f, 200.f);
	sf::IntRect rect = sf::IntRect(m_shape.getPosition().x, m_shape.getPosition().y, m_shape.getSize().x, m_shape.getSize().y);
	m_shape.setTextureRect(rect);
	return m_shape.getTextureRect();
}

void MainMenu::Render(sf::RenderWindow& window)
{
	// Clear the screen 
	window.clear(sf::Color(0, 0, 0));

	IsOverSign(window);

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

void MainMenu::IsOverSign(sf::RenderWindow& window)
{
	if(m_shape.getTextureRect().contains(window.convertCoords(sf::Mouse::getPosition(window), m_view).x, window.convertCoords(sf::Mouse::getPosition(window), m_view).y)){
		m_over = true;
	}else{
		m_over = false;
	}
}
