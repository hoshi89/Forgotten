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
#include <queue>

const float FADESPEED = 2.0f;
const bool FULLSCREEN = false;
const bool DEBUG = true;
const bool DEBUG_NODE = false;

// SINGLETON

class GameManager{
public:
	static GameManager* GetInstance();
	void RenderWindow();
	void Process();
	void Render();
	sf::RenderWindow& GetWindow();
	void SortDrawOrder(std::vector<Entity*> &vector);
	void LoadScript(std::string filename);
	Player* GetPlayer();
private:
	GameManager();
	GameManager(GameManager const&);
	GameManager& operator=(GameManager const&){};
	static GameManager *m_instance;

	void PlayerFocus();

	sf::RenderWindow m_window;
	sf::View m_defaultView;
	sf::View m_view;

	Inventory* m_inventory;
	Gui gui;

	LevelManager m_levelManager;
	MouseHandler m_mouseHandler;

	bool m_goingThroughPortal;
	//Portal* m_targetPortal;
	//sf::RectangleShape m_fade;

	// Script stuff
	typedef std::queue<std::string> EventQueue;
	EventQueue m_events;

	void ProcessNextEvent();
	int StringToInt(const std::string &str);

	
	//Script variables
	//Wait
	bool m_wait;
	int m_waitTime;
	sf::Clock m_waitClock;

	//Fading
	sf::Clock m_fadeClock;
	void UpdateFade();
	bool m_fadingOut;
	int m_fadeAlpha;
	sf::RectangleShape m_fadeShape;
	int m_fadeSpeed;


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