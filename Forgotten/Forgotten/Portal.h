#ifndef INCLUDED_PORTAL
#define INCLUDED_PORTAL

#include "Entity.h"
#include "Player.h"
#include "MouseHandler.h"

class Portal : public Entity{
public:
	Portal(int level, sf::IntRect rect, sf::Vector2f nodePosition, Entity::Direction direction);
	void MouseOver(MouseHandler &mouse);
	void Interact();
	void SetTargetPortal(Portal *portal);


	int GetID();
	Portal* GetTargetPortal();

	sf::IntRect GetPortalRect();
	sf::Vector2f GetNodePosition();

	Entity::Direction GetDirection();
	
	void SetPosition(int x, int y);
	void Update();
	const sf::Sprite& GetSprite() const;
	void Render(sf::RenderWindow &aWindow);
	const int GetZ();
	void StopSound();
	sf::Vector2f GetInteractionNode();
	void StartInteraction();
	bool MouseOver();
	void GoTo(sf::Vector2f){};
private:
	sf::Vector2f m_nodePosition;
	std::string m_currentScript;
	sf::Sprite m_sprite;
	int m_level;
	sf::IntRect m_rect;
	Entity::Direction m_direction;
	Portal *m_targetPortal;
	bool m_active;
};

#endif