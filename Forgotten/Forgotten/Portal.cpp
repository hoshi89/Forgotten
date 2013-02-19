#include "Portal.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"

GameManager* manager = GameManager::GetInstance();

Portal::Portal(int level, sf::IntRect rect, sf::Vector2f nodePosition, Entity::Direction direction)
	:m_level(level), m_rect(rect), m_direction(direction), m_active(false),
	m_currentScript("Data/Scripts/0001.txt")
{
}

void Portal::Interact(){

	manager->GetPlayer()->GoTo(m_nodePosition);
	manager->GetPlayer()->SetFocus(this);

}

void Portal::SetTargetPortal(Portal *portal){ m_targetPortal = portal; }

int Portal::GetID(){ return m_level; }

Portal* Portal::GetTargetPortal(){ return m_targetPortal; }

sf::IntRect Portal::GetPortalRect(){ return m_rect; }

sf::Vector2f Portal::GetNodePosition(){ return m_nodePosition; }

Entity::Direction Portal::GetDirection(){ return m_direction; }

void Portal::SetPosition(int x, int y){
}

void Portal::Update(){
}

const sf::Sprite& Portal::GetSprite() const{
	return m_sprite;
}

void Portal::Render(sf::RenderWindow &window){
}

const int Portal::GetZ(){
	return 0;
}

void Portal::StopSound(){
}

sf::Vector2f Portal::GetInteractionNode(){ return m_nodePosition; }

void Portal::StartInteraction(){

	manager->LoadScript(m_currentScript);

}

bool Portal::MouseOver(MouseHandler& mouse){

	if(m_rect.contains(mouse.GetPosition().x, mouse.GetPosition().y)){
		// Set mouse animation
		return true;
	}

	return false;
}