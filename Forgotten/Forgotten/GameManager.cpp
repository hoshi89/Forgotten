#include "GameManager.h"
#include <algorithm>

bool EntitySort(Entity *e1, Entity *e2){ return e1->GetZ() < e2->GetZ(); }

GameManager::GameManager()
	:gui(sf::Vector2f(300, -50))
{
	// Start new game
	m_levelManager.LoadChapter(); // Load first chapter

	// Create the player
	m_player = new Player(m_levelManager.GetCurrentLevel()->GetNodeMap());

	//m_inventory = new Inventory("Data/Levels/Level1_items.txt");
	//m_inventory->Read();

	// Set the view size
	m_view.setSize(1024, 576);
	m_view.setCenter(512, 288);

	// Save default view
	m_defaultView = m_window.getDefaultView();

	// Set the window size and other properties
	if(FULLSCREEN){
		m_window.create(sf::VideoMode(1680, 1050, 32), "Forgotten", sf::Style::Fullscreen);
	}else{
		m_window.create(sf::VideoMode(1680, 1050, 32), "Forgotten");
	}

	// Set frame limit
	m_window.setFramerateLimit(60);

	// Load debug font
	const unsigned int fontSize = 8;
	m_debugFont.loadFromFile("Data/Fonts/Minecraftia.ttf");
	m_mousePosition.setFont(m_debugFont);
	m_mousePosition.setScale(0.3, 0.4);
	m_mouseNodePosition.setFont(m_debugFont);
	m_mouseNodePosition.setScale(0.3, 0.4);
	m_fps.setFont(m_debugFont);
	m_fps.setScale(0.3, 0.4);
	m_playerNodePos.setFont(m_debugFont);
	m_playerNodePos.setScale(0.3, 0.4);
}

void GameManager::Process(){
	
	// Mouse coords
	sf::Vector2f nodePos;
	sf::Vector2f mousePosition = m_window.convertCoords(sf::Mouse::getPosition(m_window));
	nodePos.x = floor(mousePosition.x / m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().x);
	nodePos.y = floor(mousePosition.y / m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().y);

	if(m_mouseHandler.mouse1WasPressed()){

		m_levelManager.GetCurrentLevel()->GetPlayer()->GoTo(nodePos);

	}

	// Update all entities
	for(int i = 0; i < m_levelManager.GetCurrentLevel()->GetEntities().size(); i++){
		m_levelManager.GetCurrentLevel()->GetEntities()[i]->Update();
	}

	// Sort the vector for drawing
	std::sort(m_levelManager.GetCurrentLevel()->GetEntities().begin(), m_levelManager.GetCurrentLevel()->GetEntities().end(), EntitySort);

}

void GameManager::Render(){

		// Clear the screen 
		m_window.clear(sf::Color(0, 0, 0));

		// Always draw the first layer of the level background first
		m_window.draw(m_levelManager.GetCurrentLevel()->GetBackgroundImage());

		// Draw players and NPCs
		for(int i = 0; i < m_levelManager.GetCurrentLevel()->GetEntities().size(); i++){
			m_levelManager.GetCurrentLevel()->GetEntities()[i]->Render(m_window);
		}

		// Draw next layer of the background


		// Set camera and draw layer three

		// Camera and four...

		// Draw all debug stuff on top layer
		if(DEBUG){

			// Set the default view for reference of mouse pointer and node drawing
			sf::Vector2f mousePosition = m_window.convertCoords(sf::Mouse::getPosition(m_window));

			// Draw the nodeMap
			if(DEBUG_NODE){

				sf::RectangleShape nodeRect;
				
				for(int x = 0; x < m_levelManager.GetCurrentLevel()->GetNodeMap().GetMapSize().x; x++){
					for(int y = 0; y < m_levelManager.GetCurrentLevel()->GetNodeMap().GetMapSize().y; y++){
						// Draw a rectangle for each node/tile 
						nodeRect.setPosition(x * m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().x, y * m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().y);
						nodeRect.setSize(sf::Vector2f(m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize()));
						nodeRect.setOutlineColor(sf::Color::Black);
						nodeRect.setOutlineThickness(1);
						if(m_levelManager.GetCurrentLevel()->GetNodeMap().isWalkable(x, y)){
							nodeRect.setFillColor(sf::Color(0, 255, 0, 20));
						}else{
							nodeRect.setFillColor(sf::Color(255, 0, 0, 20));
						}
						m_window.draw(nodeRect);
					}
				}
				
			}

			// Mouse position
			m_debugStream.str("");
			m_debugStream << "Mouse position:\n";
			m_debugStream << "X: " << mousePosition.x << " Y: " << mousePosition.y;
			m_mousePosition.setString(m_debugStream.str());
			m_mousePosition.setPosition(10, 10);

			// Mouse node position
			m_debugStream.str("");
			m_debugStream << "Mouse node position:\n";
			m_debugStream << "X: " << floor(mousePosition.x / m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().x) << " Y: " << floor(mousePosition.y / m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().y);
			m_mouseNodePosition.setString(m_debugStream.str());
			m_mouseNodePosition.setPosition(10, 50);

			// Frames per second
			float fps = floor(1.0f/m_debugClock.getElapsedTime().asSeconds());
			m_debugClock.restart();
			m_debugStream.str("");
			m_debugStream << "FPS: " << fps;
			m_fps.setString(m_debugStream.str());
			m_fps.setPosition(10, 90);

			// Player node position
			m_debugStream.str("");
			m_debugStream << "Player node position:\n";
			m_debugStream << "X: " << m_levelManager.GetCurrentLevel()->GetPlayer()->GetNodePosition().x << " Y: " << m_levelManager.GetCurrentLevel()->GetPlayer()->GetNodePosition().y;
			m_playerNodePos.setString(m_debugStream.str());
			m_playerNodePos.setPosition(10, 130);

			// Set the default view to draw text in right place
			m_window.setView(m_defaultView);

			// Debug text
			m_window.draw(m_mousePosition);
			m_window.draw(m_mouseNodePosition);
			m_window.draw(m_fps);
			m_window.draw(m_playerNodePos);

		}

		// Draw the GUI
		gui.Render(m_window);

		// Set view
		m_view.setCenter(sf::Vector2f(m_levelManager.GetCurrentLevel()->GetPlayer()->GetPosition().x, 288));

		// Is the camera out of bounds?
		if(m_view.getCenter().x + (m_view.getSize().x/2) > m_levelManager.GetCurrentLevel()->GetBackgroundImage().getGlobalBounds().width){
			m_view.setCenter(sf::Vector2f(m_levelManager.GetCurrentLevel()->GetBackgroundImage().getGlobalBounds().width - (m_view.getSize().x/2), 288));
		}else if(m_view.getCenter().x - (m_view.getSize().x/2) < 0){
			m_view.setCenter(sf::Vector2f(m_view.getSize().x/2, 288));
		}

		m_window.setView(m_view);

		// Draw entities
		//for(std::vector<Entity*>::iterator i = m_levelManager.GetCurrentLevel()->GetEntities().begin(); i != m_levelManager.GetCurrentLevel()->GetEntities().end(); i++){
		//	(*i)->Render(m_window);
		//}

		// Display all rendered items
		m_window.display();

}

sf::RenderWindow& GameManager::GetWindow(){ return m_window; }

void GameManager::SortDrawOrder(std::vector<Entity*> &vector){

	for(int i = 0; i < vector.size(); i++){
	}

}