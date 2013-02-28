#pragma once
#include "entity.h"

#include "Player.h"
#include "MouseHandler.h"

#include <string>
#include <iostream>

using namespace std;
class ObjectCls:
	public Entity
{
public:
	ObjectCls(int aXpos, int aYpos, const string aSpriteName,
		sf::Vector2f aInteractionNode, sf::IntRect aIntRect,
		Entity::Direction aDirection);

	sf::Texture m_texture;
	void SetPosition(int x, int y) override;
	const sf::Sprite& GetSprite() const override;
	void Render(sf::RenderWindow &aWindow) override;
	void Update() override;
	int const GetZ() override;
	void StopSound() override;
	void Interact() override;
	sf::Vector2f GetInteractionNode() override;
	void StartInteraction() override;
	bool MouseOver(MouseHandler&) override;
	void GoTo(sf::Vector2f aInteractionNode) override;
	void SetDirection(Entity::Direction aDirection) override;

private:
	Animation m_currentAnimation;
	int posX;
	int posY;
	virtual ~ObjectCls(void);
	sf::Vector2f m_position;
	sf::Vector2f m_InteractionNode;
	sf::IntRect m_InteractionRect;
	Entity::Direction m_Direction;
};

