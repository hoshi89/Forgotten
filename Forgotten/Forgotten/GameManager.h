#ifndef INCLUDED_GAMEMANAGER
#define INCLUDED_GAMEMANAGER

#include "LevelManager.h"
#include "Player.h"
#include "Entity.h"
#include "Level.h"
#include "Inventory.h"
#include "Gui.h"
#include <sstream>
#include <SFML/Audio.hpp>
#include "MouseHandler.h"

const float FADESPEED = 2.0f;
const bool FULLSCREEN = false;
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
	void SortDrawOrder(std::vector<Entity*> &vector);
private:
	sf::RenderWindow m_window;
	sf::View m_defaultView;
	sf::View m_view;

	Inventory* m_inventory;
	Gui gui;

	LevelManager m_levelManager;
	MouseHandler m_mouseHandler;

	bool m_goingThroughPortal;
	bool m_fadingOut;
	Portal* m_targetPortal;
	sf::RectangleShape m_fade;
	float m_fadeAlpha;

	// Debug stuff
	sf::Font m_debugFont;
	sf::Text m_mousePosition;
	sf::Text m_mouseNodePosition;
	sf::Text m_fps;
	sf::Text m_playerNodePos;
	std::stringstream m_debugStream;
	sf::Clock m_debugClock;
};

#endif