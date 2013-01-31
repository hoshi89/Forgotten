#include "Player.h"
#include <math.h>

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
	m_currentAnimation(&m_walkingRight),
	m_nodeMap(map),
	m_currentTarget(-1, -1)
{
}

void Player::GoTo(sf::Vector2f goal){
	m_pathFinder.SetPath(ConvertToNodeCoords(m_position), goal);
}

void Player::SetPosition(int x, int y){

	m_position.x = x;
	m_position.y = y;

}

sf::Vector2f Player::GetPosition(){ return m_position; }

void Player::Update(){

	// Is there a complete path to go?
	if(m_pathFinder.PathComplete()){
		if(m_currentTarget.x < 0 && m_currentTarget.y < 0){
			// No target is set so set next target
			m_currentTarget = ConvertToPixelCoords(m_pathFinder.GetNextMove());
		}else{
			// Make an area of which destination reached is detected
			sf::FloatRect destRect(m_currentTarget.x-2, m_currentTarget.y-2, 9, 9);

			// Target is set, check if we're there
			if(destRect.contains(m_position)){
				// We're there so get new target
				m_currentTarget = ConvertToPixelCoords(m_pathFinder.GetNextMove());
			}
		}
		asdf
		// Set velocity to make player reach destination
		float x_diff = m_currentTarget.x - m_position.x;
		float y_diff = m_currentTarget.y - m_position.y;

		if(x_diff > 0 || y_diff > 0){

			float hyp = sqrt((x_diff*x_diff) + (y_diff*y_diff));
			x_diff = x_diff / hyp;
			y_diff = y_diff / hyp;

			m_velocity = sf::Vector2f(x_diff*0.1, y_diff*0.1);

		}

	}else{
		// Stop the player
		m_velocity.x = 0;
		m_velocity.y = 0;
	}

	m_pathFinder.FindPath();
	m_position += m_velocity;
	m_currentAnimation->update();

	m_currentAnimation->setPosition(m_position);

}

const sf::Sprite& Player::GetSprite() const{ return m_currentAnimation->getSprite(); }

sf::Vector2f Player::ConvertToNodeCoords(sf::Vector2f coords){

	sf::Vector2f nodeCoords;

	nodeCoords.x = floor(coords.x / m_nodeMap.GetNodeSize().x);
	nodeCoords.y = floor(coords.y / m_nodeMap.GetNodeSize().y);

	return nodeCoords;

}

sf::Vector2f Player::ConvertToPixelCoords(sf::Vector2f nodeCoords){

	sf::Vector2f pixelCoords;

	pixelCoords.x = nodeCoords.x * m_nodeMap.GetNodeSize().x;
	pixelCoords.y = nodeCoords.y * m_nodeMap.GetNodeSize().y;

	return pixelCoords;

}