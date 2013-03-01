#include "MainMenu.h"

MainMenu::MainMenu()
{
	LoadImage();
}

void MainMenu::LoadImage()
{
	m_texture.loadFromFile("Data/Meny.png");
	m_sprite.setTexture(m_texture);
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void MainMenu::SetRect(){
	sf::IntRect rect = sf::IntRect(0, 200, 300, 200);
	m_continueRect = rect;
}

void MainMenu::PushMenu()
{
	//Another menu

}

void MainMenu::Update(sf::RenderWindow& window)
{
	Draw(window);
}