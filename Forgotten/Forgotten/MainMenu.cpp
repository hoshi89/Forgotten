#include "MainMenu.h"

MainMenu::MainMenu(MouseHandler& mouse) : m_newGame(false), m_exit(false), m_continue(false), m_mouse(mouse)
{
	LoadImage();
	//// Set the view size
	m_view.setSize(1024, 576);
	m_view.setCenter(855, 288);
	SetRects();
}

bool MainMenu::NewGame()
{
	return m_newGame;
}

bool MainMenu::Exit()
{
	return m_exit;
}

bool MainMenu::Continue()
{
	return m_continue;
}

void MainMenu::IsOver(int i)
{

}

void MainMenu::LoadImage()
{
	m_texture.loadFromFile("Data/DaMenyz4.png");
	m_sprite.setTexture(m_texture);
}

void MainMenu::SetRects()
{
	m_newGameRect = sf::IntRect(950, 300, 270, 100);
	m_exitRect = sf::IntRect(1150, 440, 200, 80);
	m_continueRect = sf::IntRect(930, 180, 270, 100);
}

void MainMenu::Render(sf::RenderWindow& window)
{
	// Clear the screen 
	window.clear(sf::Color(0, 0, 0));


	window.setMouseCursorVisible(false);

	// Set the game view again
	window.setView(m_view);

	window.draw(m_sprite);

	m_mouse.Render();

	IsOverSign(window);

	// Display all rendered items
	window.display();
}

void MainMenu::Process()
{
	m_mouse.SetCursor(0);
	m_mouse.Update();
}

void MainMenu::IsOverSign(sf::RenderWindow& window)
{
	if(m_newGameRect.contains(window.convertCoords(sf::Mouse::getPosition(window), m_view).x, window.convertCoords(sf::Mouse::getPosition(window), m_view).y) && m_mouse.mouse1WasPressed()){
		m_newGame = true;
	}else{
		m_newGame = false;
	}
	if(m_exitRect.contains(window.convertCoords(sf::Mouse::getPosition(window), m_view).x, window.convertCoords(sf::Mouse::getPosition(window), m_view).y) && m_mouse.mouse1WasPressed()){
		m_exit = true;
	}else{
		m_exit = false;
	}
	//if(m_continueRect.contains(window.convertCoords(sf::Mouse::getPosition(window), m_view).x, window.convertCoords(sf::Mouse::getPosition(window), m_view).y)){
	//	m_continue = true;
	//}else{
	//	m_continue = false;
	//}
}
