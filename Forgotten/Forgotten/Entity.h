#ifndef INCLUDED_ENTITY
#define INCLUDED_ENTITY

#include "GenericMap.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include "MouseHandler.h"

class Entity{
public:
	enum Direction {UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT};
	Entity(){};
	virtual ~Entity(){};
	virtual std::string GetID(){ return ""; };
	virtual void SetID(std::string id){};
	virtual void SetPosition(int x, int y) abstract;
	virtual void Update() abstract;
	virtual const sf::Sprite& GetSprite() const abstract;
	virtual void Render(sf::RenderWindow &window) abstract;
	virtual const int GetZ() abstract;
	virtual void StopSound() abstract;
	virtual void Interact() abstract;
	virtual sf::Vector2f GetInteractionNode(){ return sf::Vector2f(); };
	virtual void StartInteraction(){};
	virtual bool MouseOver(MouseHandler&) abstract;
	virtual void GoTo(sf::Vector2f)=0;
	virtual void SetDirection(Entity::Direction direction){};
	virtual void Inspect(){};
};

#endif