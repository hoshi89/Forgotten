#include "RenderStates.h"

RenderStates::RenderStates(State aState) : m_state(aState), m_menu(GameManager::GetInstance()->GetMouseHandler())
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
		m_menu.Process();
		m_menu.Render(GameManager::GetInstance()->GetWindow());
		ChangeState();
		break;
	case RenderState::Settings:

		break;
	}
}

void RenderStates::ChangeState()
{
	if(m_menu.IsOver())
	{
		m_state = RenderState::Game;
	}

}

sf::RenderWindow& RenderStates::GetWindow()
{
	return GameManager::GetInstance()->GetWindow();
}

void RenderStates::SetRenderState(State aState)
{
	m_state = aState;
}