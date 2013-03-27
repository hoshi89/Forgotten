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
	virtual void SetPosition(int x, int y)=0;
	virtual void Update()=0;
	virtual const sf::Sprite& GetSprite() const=0;
	virtual void Render(sf::RenderWindow &window)=0;
	virtual const int GetZ()=0;
	virtual void StopSound()=0;
	virtual void Interact(int item = -1)=0;
	virtual sf::Vector2f GetInteractionNode(){ return sf::Vector2f(); };
	virtual void StartInteraction(){};
	virtual bool MouseOver(MouseHandler&)=0;
	virtual void GoTo(sf::Vector2f)=0;
	virtual void SetDirection(Entity::Direction direction){};
	virtual void Inspect(){};
	virtual void Move(){};
	virtual void SetAnimation(const std::string&){};
};

#endif