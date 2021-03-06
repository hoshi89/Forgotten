#ifndef INCLUDED_PLAYER
#define INCLUDED_PLAYER

#include "AStar.h"
#include "Entity.h"

const float WALKSPEED = 3.5;
const float X_FEETOFFSET = 80;
const float Y_FEETOFFSET = 275;

class Player : public Entity{
public:
	Player(GenericMap &map);
	void GoTo(sf::Vector2f goal);
	std::string GetID();
	void SetID(std::string id);
	void SetPosition(int x, int y);
	void SetNodePosition(int x, int y);
	void SetDirection(Entity::Direction direction);
	sf::Vector2f GetPosition();
	sf::Vector2f GetNodePosition();
	void Update();
	void Render(sf::RenderWindow &window);
	const sf::Sprite& GetSprite() const;
	sf::Vector2f ConvertToNodeCoords(sf::Vector2f coords);
	sf::Vector2f ConvertToPixelCoords(sf::Vector2f nodeCoords);
	const int GetZ();
	void StopSound();
	void SetFocus(Entity *entity);
	Entity* GetFocus();
	void Interact(int item=-1){};
	bool MouseOver(MouseHandler&){ return false; }
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

	Animation m_idleRight;
	Animation m_idleDownRight;
	Animation m_idleDown;
	Animation m_idleDownLeft;
	Animation m_idleLeft;
	Animation m_idleUpLeft;
	Animation m_idleUp;
	Animation m_idleUpRight;

	Animation *m_currentAnimation;

	AStar m_pathFinder;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_currentTarget;
	GenericMap &m_nodeMap;
	Entity *m_currentFocus;
	bool m_isWalking;
	float m_scale;
};

#endif