#include "Portal.h"
#include <SFML/Graphics.hpp>

Portal::Portal(int level, sf::IntRect rect, sf::Vector2f nodePosition, Entity::Direction direction)
	:m_level(level), m_rect(rect), m_nodePosition(nodePosition), m_direction(direction), m_active(false)
{
}

void Portal::StandingOn(Player &player){

	// If the portal is active, go through portal
	// Fade to black
	// Load new level
	// Place and face player correctly



}

void Portal::Interact(Player *player){

	// For objects later...
	// Check if the player is in any of the adjacent nodes
	// if not, calculate the closest node to the player and send player.goto(node)

	// For portals, go to node position and activate portal

	player->GoTo(m_nodePosition);

}

void Portal::SetTargetPortal(Portal *portal){ m_targetPortal = portal; }

int Portal::GetID(){ return m_level; }

Portal* Portal::GetTargetPortal(){ return m_targetPortal; }

sf::IntRect Portal::GetPortalRect(){ return m_rect; }

sf::Vector2f Portal::GetNodePosition(){ return m_nodePosition; }

void Portal::ActivatePortal(){ m_active = true; }

void Portal::DeactivatePortal(){ m_active = false; }

bool Portal::IsActive(){ return m_active; }

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