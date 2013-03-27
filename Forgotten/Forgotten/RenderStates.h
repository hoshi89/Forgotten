#ifndef INCLUDED_RENDERSTATES
#define INCLUDED_RENDERSTATES

#include "GameManager.h"
#include "MainMenu.h"
#include <SFML\Graphics.hpp>

class RenderStates
{
public:
	typedef enum RenderState{Menu, Game, Settings, Exit} State;
	RenderStates(State state);
	RenderStates::RenderState GetRenderStates();
	sf::RenderWindow& GetWindow();
	void RenderState();
	void ChangeState();
	void SetRenderState(State state);
private:
	State m_state;
	MainMenu m_menu;
};

#endif