#ifndef INCLUDED_PORTAL
#define INCLUDED_PORTAL

#include "Entity.h"
#include "Player.h"
#include "MouseHandler.h"

class Portal : public Entity{
public:
	Portal(std::string id, sf::IntRect rect, sf::Vector2f nodePosition);
	virtual std::string GetID();
	virtual void SetID(std::string id);
	bool MouseOver(MouseHandler &mouse);
	void Interact(int item=-1);
	sf::IntRect GetPortalRect();
	sf::Vector2f GetNodePosition();
	Entity::Direction GetDirection();
	void SetPosition(int x, int y);
	void SetScript(std::string script);
	void Update();
	const sf::Sprite& GetSprite() const;
	void Render(sf::RenderWindow &aWindow);
	const int GetZ();
	void StopSound();
	sf::Vector2f GetInteractionNode();
	void StartInteraction();
	void GoTo(sf::Vector2f){};
private:
	sf::Vector2f m_nodePosition;
	std::string m_currentScript;
	sf::IntRect m_rect;
	std::string m_id;
};

#endif