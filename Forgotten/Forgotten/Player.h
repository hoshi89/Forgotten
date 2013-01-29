#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

#include "AStar.h"
#include "Animation.h"
#include "Entity.h"

// SINGLETON

class Player : public Entity{
public:
	Player(GenericMap &map);
	void GoTo(sf::Vector2f goal);
	void SetPosition(int x, int y);
	sf::Vector2f GetPosition();
	void Update();
	const sf::Sprite& GetSprite() const;
private:
	int m_direction;
	Animation m_walkingRight;
	Animation m_walkingDownRight;
	Animation m_walkingDown;
	Animation m_walkingDownLeft;
	Animation m_walkingLeft;
	Animation m_walkingUpLeft;
	Animation m_walkingUp;
	Animation m_walkingUpRight;
	Animation *m_currentAnimation;
	AStar m_pathFinder;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
};

#endif