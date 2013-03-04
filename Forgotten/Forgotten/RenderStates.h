#ifndef INCLUDED_RENDERSTATES
#define INCLUDED_RENDERSTATES

#include "GameManager.h"
#include "MainMenu.h"
#include <SFML\Graphics.hpp>

class RenderStates{
	enum RenderState{Menu, Game, Settings} m_state;
public:
	RenderStates();
	RenderState GetRenderStates();
	sf::RenderWindow& GetWindow();
	void RenderState();
	void ChangeState();
private:
	MainMenu m_menu;
};

#endif