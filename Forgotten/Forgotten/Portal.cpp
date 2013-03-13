#include "Portal.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"

Portal::Portal(std::string id, sf::IntRect rect, sf::Vector2f nodePosition)
	:
	m_id(id),
	m_rect(rect),
	m_nodePosition(nodePosition),
	m_currentScript("Data/Scripts/0001.txt")
{
}

std::string Portal::GetID()
{
	return m_id;
}

void Portal::SetID(std::string id)
{
	m_id = id;
}

void Portal::Interact(int item)
{
	GameManager::GetInstance()->GetPlayer()->GoTo(m_nodePosition);
	GameManager::GetInstance()->GetPlayer()->SetFocus(this);
}


sf::IntRect Portal::GetPortalRect(){ return m_rect; }

sf::Vector2f Portal::GetNodePosition(){ return m_nodePosition; }

void Portal::SetPosition(int x, int y){
}

void Portal::SetScript(std::string script){
	m_currentScript = script;
}

void Portal::Update(){
}

const sf::Sprite& Portal::GetSprite() const{
	return sf::Sprite();
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

	GameManager::GetInstance()->LoadScript(m_currentScript);

}

bool Portal::MouseOver(MouseHandler& mouse){

	if(m_rect.contains(mouse.GetPosition().x, mouse.GetPosition().y)){
		mouse.SetCursor(4);
		return true;
	}

	return false;
}