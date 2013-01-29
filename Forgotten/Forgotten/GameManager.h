#ifndef INCLUDED_GAMEMANAGER
#define INCLUDED_GAMEMANAGER

#include "Player.h"
#include "Level.h"
#include <sstream>

const bool FULLSCREEN = true;
const bool DEBUG = true;
const bool DEBUG_NODE = true;

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

	Level m_level1;
	Level *m_currentLevel;

	// Debug stuff
	sf::Font m_debugFont;
	sf::Text m_mousePosition;
	sf::Text m_mouseNodePosition;
	std::stringstream m_debugStream;
};

#endif