#ifndef INCLUDED_GAMEMANAGER
#define INCLUDED_GAMEMANAGER

#include "LevelManager.h"
#include "Player.h"
#include "Entity.h"
#include "Level.h"
#include "Inventory.h"
#include "Gui.h"
#include <sstream>

const bool FULLSCREEN = true;
const bool DEBUG = true;
const bool DEBUG_NODE = false;

// SINGLETON

class GameManager{
public:
	GameManager();
	void RenderWindow();
	void Process();
	void Render();
	sf::RenderWindow& GetWindow();
private:
	Player* m_player;
	std::vector<Entity*> m_entities;

	sf::RenderWindow m_window;
	sf::View m_defaultView;
	sf::View m_view;

	Inventory* m_inventory;
	Gui gui;

	LevelManager m_levelManager;

	// Debug stuff
	sf::Font m_debugFont;
	sf::Text m_mousePosition;
	sf::Text m_mouseNodePosition;
	sf::Text m_fps;
	std::stringstream m_debugStream;
	sf::Clock m_debugClock;
};

#endif