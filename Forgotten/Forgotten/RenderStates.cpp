#include "RenderStates.h"

RenderStates::RenderStates()
{
	GameManager* gameManager;
	GameManager::GetInstance()->GetWindow();
	m_state = RenderState::Menu;
}

void RenderStates::RenderState()
{
	switch(m_state){
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
}

sf::RenderWindow& RenderStates::GetWindow()
{
	return GameManager::GetInstance()->GetWindow();
}