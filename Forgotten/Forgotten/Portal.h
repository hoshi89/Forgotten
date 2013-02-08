#ifndef INCLUDED_PORTAL
#define INCLUDED_PORTAL

#include "Entity.h"
#include "Player.h"
#include "MouseHandler.h"

class Portal : public Entity{
public:
	Portal();
	void MouseOver(MouseHandler &mouse);
	void Interact(Player &player);
private:
	sf::IntRect m_rect;
};

#endif