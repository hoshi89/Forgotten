#include "RenderStates.h"

RenderStates::RenderStates(State state) : 
	m_state(state), 
	m_menu(GameManager::GetInstance()->GetMouseHandler())
{
	GameManager* gameManager;
	GameManager::GetInstance()->GetWindow();
}

void RenderStates::RenderState()
{
	switch(m_state)
	{
	case RenderState::Game:
		GameManager::GetInstance()->Process();
		GameManager::GetInstance()->Render();
		break;
	case RenderState::Menu:
		GameManager::GetInstance()->GetMouseHandler().DropItem();
		m_menu.Process();
		m_menu.Render(GameManager::GetInstance()->GetWindow());
		ChangeState();
		break;
	case RenderState::Settings:

		break;

	case RenderState::Exit:
		GetWindow().close();
		break;
	}
}

void RenderStates::ChangeState()
{
	if(m_menu.NewGame())
	{
		m_state = RenderState::Game;
	}
	if(m_menu.Exit())
	{
		m_state = RenderState::Exit;
	}
	if(m_menu.Continue())
	{
		m_state = RenderState::Game;
	}
}

sf::RenderWindow& RenderStates::GetWindow()
{
	return GameManager::GetInstance()->GetWindow();
}

void RenderStates::SetRenderState(State state)
{
	m_state = state;
}