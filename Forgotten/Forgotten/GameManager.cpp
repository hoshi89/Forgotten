#include "GameManager.h"
#include <algorithm>
#include <iostream>
#include "FlagManager.h"

GameManager* GameManager::m_instance = NULL;
FlagManager *flags = FlagManager::GetInstance();

bool EntitySort(Entity *e1, Entity *e2){ return e1->GetZ() < e2->GetZ(); }

GameManager* GameManager::GetInstance()
{
	if(!m_instance)
		m_instance = new GameManager;

	return m_instance;
}

GameManager::GameManager(GameManager const&)
	:gui(m_mouseHandler),
	m_mouseHandler(m_window)
{
}

GameManager::GameManager()
	:gui(m_mouseHandler),
	m_fadingOut(true),
	m_fadeAlpha(255),
	m_wait(false),
	m_mouseHandler(m_window),
	m_suspend(false)
{

	// Set fadeShape
	m_fadeShape.setFillColor(sf::Color(0, 0, 0, 255));

	// Start new game
	m_levelManager.LoadChapter(0); // Load first chapter
	LoadScript("Data/Scripts/0004.txt");

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
		m_window.create(sf::VideoMode(1024, 576, 32), "Forgotten");
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

	// Hide the cursor
	m_window.setMouseCursorVisible(false);

	// Check the inital script for the chapter
	if(m_levelManager.InitialScriptRun()){
		LoadScript(m_levelManager.GetInitialScript());
	}

	// Get next script event in queue
	ProcessNextEvent();

	// Check fade status
	UpdateFade();

	// Check if the player has reached its focus
	PlayerFocus();

	// Mouse coords
	sf::Vector2f nodePos;
	sf::Vector2f mousePosition = m_window.convertCoords(sf::Mouse::getPosition(m_window));
	nodePos.x = floor(mousePosition.x / m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().x);
	nodePos.y = floor(mousePosition.y / m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().y);

	// Check if node is walkable
	if(m_levelManager.GetCurrentLevel()->GetNodeMap().isWalkable(nodePos.x, nodePos.y)){
		m_mouseHandler.SetCursor(1);
	}else{
		m_mouseHandler.SetCursor(2);
	}


	// Sort the vector by Z value
	std::sort(m_levelManager.GetCurrentLevel()->GetEntities().begin(), m_levelManager.GetCurrentLevel()->GetEntities().end(), EntitySort);

	// Update all entities
	for(int i = 0; i < m_levelManager.GetCurrentLevel()->GetEntities().size(); i++){

		// Update the entity
		m_levelManager.GetCurrentLevel()->GetEntities()[i]->Update();

		// Update mouse icon
		m_levelManager.GetCurrentLevel()->GetEntities()[i]->MouseOver(m_mouseHandler);

	}

	if(!m_suspend){
		// Check mouse click
		if(m_mouseHandler.mouse1WasPressed()){

			bool interactFound = false;

			// Check all entities for interaction
			for(int i = 0; i < m_levelManager.GetCurrentLevel()->GetEntities().size(); i++){

				if(m_levelManager.GetCurrentLevel()->GetEntities()[i]->MouseOver(m_mouseHandler)){
					m_levelManager.GetCurrentLevel()->GetEntities()[i]->Interact();
					interactFound = true;
				}

			}

			// Else go to node
			if(!interactFound)
				m_levelManager.GetCurrentLevel()->GetPlayer()->GoTo(nodePos);

		}
	}else{
		m_mouseHandler.SetCursor(0);
	}

}

void GameManager::Render(){

		// Clear the screen 
		m_window.clear(sf::Color(0, 0, 0));

		// Always draw the first layer of the level background first
		m_window.draw(m_levelManager.GetCurrentLevel()->GetBackgroundImage());

		// Draw entities
		for(int i = 0; i < m_levelManager.GetCurrentLevel()->GetEntities().size(); i++){
			m_levelManager.GetCurrentLevel()->GetEntities()[i]->Render(m_window);
		}

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

		// Set view
		m_view.setCenter(sf::Vector2f(m_levelManager.GetCurrentLevel()->GetPlayer()->GetPosition().x, 288));

		// Is the camera out of bounds?
		if(m_view.getCenter().x + (m_view.getSize().x/2) > m_levelManager.GetCurrentLevel()->GetBackgroundImage().getGlobalBounds().width){
			m_view.setCenter(sf::Vector2f(m_levelManager.GetCurrentLevel()->GetBackgroundImage().getGlobalBounds().width - (m_view.getSize().x/2), 288));
		}else if(m_view.getCenter().x - (m_view.getSize().x/2) < 0){
			m_view.setCenter(sf::Vector2f(m_view.getSize().x/2, 288));
		}

		// Set the game view
		m_window.setView(m_view);

		// Draw the overlay for all items. Fade sprite.
		m_window.draw(m_fadeShape);

		// Draw the GUI on top of fade
		gui.Draw(m_window);

		// Set the game view again
		m_window.setView(m_view);

		// Draw mouse pointer
		m_mouseHandler.Draw();

		// Display all rendered items
		m_window.display();

}

sf::RenderWindow& GameManager::GetWindow(){ return m_window; }

void GameManager::LoadScript(std::string filename){

	std::ifstream scriptFile(filename);
	std::string tmpString;

	if(scriptFile)
	{
		while(std::getline(scriptFile, tmpString))
		{
			m_events.push(tmpString);
		}
	}

}

Player* GameManager::GetPlayer(){
	return m_levelManager.GetCurrentLevel()->GetPlayer();
}

void GameManager::ProcessNextEvent(){

	if(m_wait){
		if(m_waitClock.getElapsedTime().asSeconds() < m_waitTime)
		{
			return;
		}else{
			m_wait = false;
		}
	}

	if(m_events.size() > 0 && !m_wait){

		// Get next event as string
		std::string tmpEvent = m_events.front();

		// Create temporary stuff
		std::stringstream tmpStream;
		std::string tmpString;
		std::string token;

		// Add the string to the stream
		tmpStream << tmpEvent;

		// Get the event type
		std::getline(tmpStream, token, ' ');

		// Wait
		if(token == "wait")
		{
			// Get wait time as string
			std::getline(tmpStream, token, ' ');
			m_waitTime = StringToInt(token);

			// Set GameManager variables
			m_wait = true;
			m_waitClock.restart();
		}
		// Fade out
		else if(token == "fadeout")
		{
			// Get fade time as string
			std::getline(tmpStream, token, ' ');
			int fadetime = StringToInt(token);

			m_fadeSpeed = 255/fadetime;
			m_fadingOut = true;
			m_fadeClock.restart();
		}
		// Fade in
		else if(token == "fadein")
		{
			// Get fade time as string
			std::getline(tmpStream, token, ' ');
			int fadetime = StringToInt(token);

			m_fadeSpeed = 255/fadetime;
			m_fadingOut = false;
			m_fadeClock.restart();
		}
		// Move entity
		else if(token == "move")
		{
			// Get coordinates as strings
			std::getline(tmpStream, token, ' ');
			int xcoord = StringToInt(token);
			
			std::getline(tmpStream, token, ' ');
			int ycoord = StringToInt(token);

			// Get entity id as string
			std::getline(tmpStream, token, ' ');
			int entityid = StringToInt(token);

			// Move the entity... if it exists
			if(m_levelManager.GetCurrentLevel()->GetEntities().size() >= entityid)
			{
				m_levelManager.GetCurrentLevel()->GetEntities()[entityid]->GoTo(sf::Vector2f(xcoord, ycoord));
			}
		}
		// Suspend controls
		else if(token == "suspend")
		{
			// Set state
			m_suspend = true;
		}
		else if(token == "resume")
		{
			// Set state
			m_suspend = false;
		}
		// Play sound
		else if(token == "playsound")
		{
			// Get the soundid as string
			std::getline(tmpStream, token, ' ');
			int soundid = StringToInt(token);
			
			// Play the sound
			m_levelManager.GetCurrentLevel()->PlaySound(soundid);
		}
		// Set level
		else if(token == "setlevel")
		{
			// Get the levelid as string
			std::getline(tmpStream, token, ' ');
			int levelid = StringToInt(token);

			// Change level
			m_levelManager.SetLevel(levelid);
		}
		// Set direction
		else if(token == "setdirection")
		{
			// Get the entity id as string
			std::getline(tmpStream, token, ' ');
			int entityid = StringToInt(token);

			// Get the direction as string
			std::getline(tmpStream, token, ' ');
			int direction = StringToInt(token);

			// What direction?
			Entity::Direction enumDirection;

			switch(direction)
			{
			case 0:
				enumDirection = Entity::UP;
				break;
			case 1:
				enumDirection = Entity::UP_RIGHT;
				break;
			case 2:
				enumDirection = Entity::RIGHT;
				break;
			case 3:
				enumDirection = Entity::DOWN_RIGHT;
				break;
			case 4:
				enumDirection = Entity::DOWN;
				break;
			case 5:
				enumDirection = Entity::DOWN_LEFT;
				break;
			case 6:
				enumDirection = Entity::LEFT;
				break;
			case 7:
				enumDirection = Entity::UP_LEFT;
				break;
			default:
				enumDirection = Entity::RIGHT;
				break;
			}

			// Set direction
			m_levelManager.GetCurrentLevel()->GetEntities()[entityid]->SetDirection(enumDirection);
		}
		// Set position
		else if(token == "setposition")
		{
			// Get coordinates as strings
			std::getline(tmpStream, token, ' ');
			int xcoord = StringToInt(token);
			
			std::getline(tmpStream, token, ' ');
			int ycoord = StringToInt(token);

			// Get entity id as string
			std::getline(tmpStream, token, ' ');
			int entityid = StringToInt(token);

			m_levelManager.GetCurrentLevel()->GetEntities()[entityid]->SetPosition(xcoord, ycoord);
		}
		// Set nodeposition
		else if(token == "setnodeposition")
		{
			// Get coordinates as strings
			std::getline(tmpStream, token, ' ');
			int xcoord = StringToInt(token);
			
			std::getline(tmpStream, token, ' ');
			int ycoord = StringToInt(token);

			// Get entity id as string
			std::getline(tmpStream, token, ' ');
			int entityid = StringToInt(token);

			// Calculate nodepos
			xcoord = xcoord * m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().x + (m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().x/2);
			ycoord = ycoord * m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().y + (m_levelManager.GetCurrentLevel()->GetNodeMap().GetNodeSize().y/2);

			m_levelManager.GetCurrentLevel()->GetEntities()[entityid]->SetPosition(xcoord, ycoord);
		}
		// Show text
		else if(token == "showtext")
		{
			// Get coordinates as strings
			std::getline(tmpStream, token, ' ');
			int xcoord = StringToInt(token);
			
			std::getline(tmpStream, token, ' ');
			int ycoord = StringToInt(token);

			// Get time as string
			std::getline(tmpStream, token, ' ');
			int time = StringToInt(token);

			// Get text
			std::getline(tmpStream, token);
			std::string text = token;

			gui.PushText(token, time, sf::Vector2f(xcoord, ycoord));
		}

		m_events.pop();
	}

}

int GameManager::StringToInt(const std::string &str)
{
	std::istringstream stream(str);
	int t;
	stream >> t;
	return t;
}

void GameManager::UpdateFade(){

	float fadeAddition = m_fadeSpeed*m_fadeClock.getElapsedTime().asSeconds();
	m_fadeClock.restart();

	if(m_fadingOut)
	{
		if(m_fadeAlpha < 255)
		{

			if((m_fadeAlpha + fadeAddition) > 255)
			{
				m_fadeAlpha = 255;
			}
			else
			{
				m_fadeAlpha += fadeAddition;
			}

			m_fadeShape.setFillColor(sf::Color(0, 0, 0, m_fadeAlpha));

		}
	}
	else
	{
		if(m_fadeAlpha > 0)
		{

			if((m_fadeAlpha - fadeAddition) < 0)
			{
				m_fadeAlpha = 0;
			}
			else
			{
				m_fadeAlpha -= fadeAddition;
			}

			m_fadeShape.setFillColor(sf::Color(0, 0, 0, m_fadeAlpha));

		}
	}
	m_fadeShape.setSize(m_view.getSize());
	m_fadeShape.setPosition(((m_view.getCenter().x)-(m_view.getSize().x/2)), ((m_view.getCenter().y)-(m_view.getSize().y/2)));
}

void GameManager::PlayerFocus(){

	Entity* currentFocus = m_levelManager.GetCurrentLevel()->GetPlayer()->GetFocus();

	if(currentFocus)
	{
		// Get nodes
		sf::Vector2f playerNode(m_levelManager.GetCurrentLevel()->GetPlayer()->GetNodePosition());
		sf::Vector2f interactionNode(currentFocus->GetInteractionNode());

		if(playerNode == interactionNode)
		{
			// Player is on the interaction node
			m_levelManager.GetCurrentLevel()->GetPlayer()->GetFocus()->StartInteraction();

			// Remove focus
			m_levelManager.GetCurrentLevel()->GetPlayer()->SetFocus(NULL);
		}
	}
}

LevelManager* GameManager::GetLevelManager()
{
	return &m_levelManager;
}