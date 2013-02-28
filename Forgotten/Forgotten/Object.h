#ifndef INCLUDED_OBJECT
#define INCLUDED_OBJECT

#include "Entity.h"

class Object : public Entity{
public:
	Object();
	void SetPosition(int x, int y);
	void Update();
	const sf::Sprite& GetSprite() const;
	void Render(sf::RenderWindow &window);
	const int GetZ();
	void StopSound();
	void Interact();
	sf::Vector2f GetInteractionNode();
	void StartInteraction();
	bool MouseOver(MouseHandler &mouse);
	void GoTo(sf::Vector2f);
	void Inspect();
private:
	Animation m_idle;
	Animation *m_currentAnimation;
	sf::Vector2f m_position;
	sf::Vector2f m_interactionNode;
	std::string m_interactScript;
	std::string m_inspectScript;
};

#endif