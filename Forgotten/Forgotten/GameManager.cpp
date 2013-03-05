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

	// Update mousehandler
	m_mouseHandler.Update();

	// Hide the cursor
	m_window.setMouseCursorVisible(false);

	// Check the inital script for the chapter
	if(!m_levelManager.InitialScriptRun()){
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

				if(m_levelManager.GetCurrentLevel()->GetEntities()[i]->MouseOver(m_mouseHandler))
				{
					// Is holding something?
					m_levelManager.GetCurrentLevel()->GetEntities()[i]->Interact(gui.ItemInHand());
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

						int h = m_levelManager.GetCurrentLevel()->GetPlayer()->GetNodePosition().x;

						if(m_levelManager.GetCurrentLevel()->GetNodeMap().isWalkable(x, y)){
							nodeRect.setFillColor(sf::Color(0, 255, 0, 20));

							if(m_levelManager.GetCurrentLevel()->GetPlayer()->GetNodePosition().x == x && m_levelManager.GetCurrentLevel()->GetPlayer()->GetNodePosition().y == y){
								nodeRect.setFillColor(sf::Color(0, 0, 255, 255));
							}
							
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
			m_events.push_back(tmpString);
		}
	}

}

Player* GameManager::GetPlayer(){
	return m_levelManager.GetCurrentLevel()->GetPlayer();
}

void GameManager::ProcessNextEvent(){

	if(gui.getDialogState() == DialogStateEnum::ContinueDialog || gui.getDialogState() == DialogStateEnum::WaitForAnswer)
		return;

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
		std::string tmpEvent = m_events[0];

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
			std::string entity_id = token;

			// Move the entity
			for(unsigned int i = 0; i < m_levelManager.GetCurrentLevel()->GetEntities().size(); i++)
			{
				if(!m_levelManager.GetCurrentLevel()->GetEntities()[i]->GetID().compare(entity_id))
				{
					// Found the entity, move it
					m_levelManager.GetCurrentLevel()->GetEntities()[i]->GoTo(sf::Vector2f(xcoord, ycoord));
					break;
				}
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
			std::string entity_id = token;

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

			for(unsigned int i = 0; i < m_levelManager.GetCurrentLevel()->GetEntities().size(); i++)
			{
				if(!m_levelManager.GetCurrentLevel()->GetEntities()[i]->GetID().compare(entity_id))
				{
					// Found the entity, set direction
					m_levelManager.GetCurrentLevel()->GetEntities()[i]->SetDirection(enumDirection);
					break;
				}
			}

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
		// Play dialog
		else if(token == "playdialog")
		{
			// Get id as string
			std::getline(tmpStream, token, ' ');
			std::string id = token;

			std::getline(tmpStream, token, ' ');
			int wPlayerXPos = StringToInt(token);
			std::getline(tmpStream, token, ' ');
			int wPlayerYPos = StringToInt(token);

			sf::Vector2f wPlayerPos = sf::Vector2f(wPlayerXPos, wPlayerYPos);

			std::getline(tmpStream, token, ' ');
			int wEntityXPos = StringToInt(token);
			std::getline(tmpStream, token, ' ');
			int wEntityYPos = StringToInt(token);

			sf::Vector2f wEntityPos = sf::Vector2f(wEntityXPos, wEntityYPos);

			gui.SetDeckId(id, wPlayerPos, wEntityPos);
		}
		// Add item
		else if(token == "additem")
		{
			// Get entity id as string
			std::getline(tmpStream, token, ' ');
			int id = StringToInt(token);

			Inventory::GetInstance()->AddItem(id);
		}
		// Remove item
		else if(token == "removeentity")
		{
			// Get entity id as string
			std::getline(tmpStream, token, ' ');
			std::string entity_id = token;

			for(unsigned int i = 0; i < m_levelManager.GetCurrentLevel()->GetEntities().size(); i++)
			{
				std::string entityname = m_levelManager.GetCurrentLevel()->GetEntities()[i]->GetID();
				if(!m_levelManager.GetCurrentLevel()->GetEntities()[i]->GetID().compare(entity_id))
				{
					// Found the entity to be removed, so remove it
					m_levelManager.GetCurrentLevel()->GetEntities().erase(m_levelManager.GetCurrentLevel()->GetEntities().begin()+i);
					break;
				}
			}

		}
		// If statement
		else if(token == "if")
		{
			// Temporary variables
			int nestLevel = 0;
			int deleteLevel = 0;
			bool active_delete = false;

			// If flag
			std::getline(tmpStream, token, ' ');
			if(token == "flag")
			{
				// Get flag name
				std::getline(tmpStream, token, ' ');

				// Check if raised
				if(FlagManager::GetInstance()->IsFlagSet(token))
				{
					// Set deleteLevel
					deleteLevel = nestLevel;

					// Flag is raised, search for elseif, else and endif and delete
					for(unsigned int i = 1; i < m_events.size(); i++)
					{
						// Get tokens and strings
						std::stringstream delStream;
						std::string delString;
						std::string delToken;

						// Add the string to the stream
						delStream << m_events[i];

						// Get the event type
						std::getline(delStream, delToken, ' ');

						// Check and set nestLevel
						if(!delToken.compare("if"))
						{
							// Increase the nestlevel
							nestLevel++;
						}

						// Look for elseif and else to initialize delete
						if(nestLevel == deleteLevel)
						{
							// Initialize delete?
							if(!delToken.compare("elseif") || !delToken.compare("else"))
							{
								active_delete = true;
							}

							// Deactivate delete?
							if(!delToken.compare("endif"))
							{
								m_events.erase(m_events.begin()+i);
								active_delete = false;
								break;
							}
						}
						else
						{
							if(!delToken.compare("endif"))
							{
								nestLevel--;
							}
						}

						// Delete
						if(active_delete)
						{
							m_events.erase(m_events.begin()+i);
							i--;
						}

					}
				}
				else
				{
					// Activate delete
					active_delete = true;

					// If statement was not true
					for(unsigned int i = 1; i < m_events.size(); i++)
					{
						// Get tokens and strings
						std::stringstream delStream;
						std::string delString;
						std::string delToken;

						// Add the string to the stream
						delStream << m_events[i];

						// Get the event type
						std::getline(delStream, delToken, ' ');

						// Check and set nestLevel
						if(!delToken.compare("if"))
						{
							// Increase the nestlevel
							nestLevel++;
						}

						if(deleteLevel == nestLevel)
						{
							// If "else" then delete line, stop delete until endif is found

							if(!delToken.compare("else"))
							{
								m_events.erase(m_events.begin()+i);
								active_delete = false;
							}
							else if(!delToken.compare("endif"))
							{
								m_events.erase(m_events.begin()+i);
								break;
							}
						}else{
							if(!delToken.compare("endif"))
							{
								// Increase the nestlevel
								nestLevel--;
							}
						}

						if(active_delete)
						{
							m_events.erase(m_events.begin()+i);
							i--;
						}
					}
				}
			}
		}
		// Raise flag
		else if(token == "raiseflag")
		{
			// Get flag as string
			std::getline(tmpStream, token, ' ');
			std::string flag = token;

			FlagManager::GetInstance()->CreateFlag(flag);
		}

		m_events.erase(m_events.begin());
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

	sf::Vector2f bgSize(m_levelManager.GetCurrentLevel()->GetBackgroundImage().getTexture()->getSize());

	m_fadeShape.setSize(bgSize);
	m_fadeShape.setPosition(0, 0);
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

MouseHandler& GameManager::GetMouseHandler()
{
	return m_mouseHandler;
}