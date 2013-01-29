#include "Player.h"

Player::Player(GenericMap &map)
	:m_pathFinder(map),
	m_walkingRight("Data/Animations/Player/player_walking_right.png", 100, 9),
	m_walkingDownRight("Data/Animations/Player/player_walking_down_right.png", 100, 9),
	m_walkingDown("Data/Animations/Player/player_walking_down.png", 100, 9),
	m_walkingDownLeft("Data/Animations/Player/player_walking_down_left.png", 100, 9),
	m_walkingLeft("Data/Animations/Player/player_walking_left.png", 100, 9),
	m_walkingUpLeft("Data/Animations/Player/player_walking_up_left.png", 100, 9),
	m_walkingUp("Data/Animations/Player/player_walking_up.png", 100, 9),
	m_walkingUpRight("Data/Animations/Player/player_walking_up_right.png", 100, 9),
	m_currentAnimation(&m_walkingRight)
{
}

void Player::GoTo(sf::Vector2f goal){
	m_pathFinder.SetPath(m_position, goal);
}

void Player::SetPosition(int x, int y){
	m_position.x = x;
	m_position.y = y;
}

sf::Vector2f Player::GetPosition(){ return m_position; }

void Player::Update(){

	m_position += m_velocity;
	m_currentAnimation->update();

	m_currentAnimation->setPosition(m_position);

}

const sf::Sprite& Player::GetSprite() const{ return m_currentAnimation->getSprite(); }