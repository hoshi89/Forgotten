#ifndef INCLUDED_ENTITY
#define INCLUDED_ENTITY

#include "GenericMap.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Entity{
public:
	Entity(){};
	virtual ~Entity(){};
	virtual void SetPosition(int x, int y) abstract;
	virtual void Update() abstract;
	virtual const sf::Sprite& GetSprite() const abstract;
	virtual void Render(sf::RenderWindow &aWindow) abstract;
	virtual const int GetZ() abstract;
	enum Direction {UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT};
};

#endif