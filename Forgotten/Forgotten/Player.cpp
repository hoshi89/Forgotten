#include "Player.h"
#include <math.h>

Player::Player(GenericMap &map)
	:m_pathFinder(map),

	m_walkingRight("Data/Animations/Player/player_walking_right.png", 100, 9, "Data/Sounds/GympadojorSten 1.wav"),
	m_walkingDownRight("Data/Animations/Player/player_walking_down_right.png", 100, 9, "Data/Sounds/GympadojorSten 1.wav"),
	m_walkingDown("Data/Animations/Player/player_walking_down.png", 100, 9, "Data/Sounds/GympadojorSten 1.wav"),
	m_walkingDownLeft("Data/Animations/Player/player_walking_down_left.png", 100, 9, "Data/Sounds/GympadojorSten 1.wav"),
	m_walkingLeft("Data/Animations/Player/player_walking_left.png", 100, 9, "Data/Sounds/GympadojorSten 1.wav"),
	m_walkingUpLeft("Data/Animations/Player/player_walking_up_left.png", 100, 9, "Data/Sounds/GympadojorSten 1.wav"),
	m_walkingUp("Data/Animations/Player/player_walking_up.png", 100, 9, "Data/Sounds/GympadojorSten 1.wav"),
	m_walkingUpRight("Data/Animations/Player/player_walking_up_right.png", 100, 9, "Data/Sounds/GympadojorSten 1.wav"),

	m_idleRight("Data/Animations/Player/player_idle_right.png", 1000, 1),
	m_idleDownRight("Data/Animations/Player/player_idle_down_right.png", 1000, 1),
	m_idleDown("Data/Animations/Player/player_idle_down.png", 1000, 1),
	m_idleDownLeft("Data/Animations/Player/player_idle_down_left.png", 1000, 1),
	m_idleLeft("Data/Animations/Player/player_idle_left.png", 1000, 1),
	m_idleUpLeft("Data/Animations/Player/player_idle_up_left.png", 1000, 1),
	m_idleUp("Data/Animations/Player/player_idle_up.png", 1000, 1),
	m_idleUpRight("Data/Animations/Player/player_idle_up_right.png", 1000, 1),

	m_currentAnimation(&m_walkingRight),
	m_nodeMap(map),
	m_currentTarget(-1, -1),
	m_currentFocus(NULL),
	m_isWalking(false)
{
}

void Player::GoTo(sf::Vector2f goal){
	m_pathFinder.SetPath(ConvertToNodeCoords(m_position), goal);
}

std::string Player::GetID()
{
	return "player";
}

void Player::SetID(std::string id)
{
}

void Player::SetFocus(Entity *entity){
	m_currentFocus = entity;
}

Entity* Player::GetFocus(){

	if(m_currentFocus)
		return m_currentFocus;

	return NULL;
}

void Player::SetPosition(int x, int y){

	m_position.x = x;
	m_position.y = y;

}

void Player::SetNodePosition(int x, int y){

	sf::Vector2f nodePos(x, y);

	m_position = ConvertToPixelCoords(nodePos);

}

void Player::SetDirection(Direction direction){ m_direction = direction; }

sf::Vector2f Player::GetPosition(){
	
	sf::Vector2f offsetPos;
	offsetPos.x = m_position.x - X_FEETOFFSET;
	offsetPos.y = m_position.y - Y_FEETOFFSET;

	return offsetPos;

}

sf::Vector2f Player::GetNodePosition(){

	sf::Vector2f nodePos;
	nodePos.x = ((m_position.x + (m_nodeMap.GetNodeSize().x/2)) / m_nodeMap.GetNodeSize().x)-1;
	nodePos.y = ((m_position.y + (m_nodeMap.GetNodeSize().y/2)) / m_nodeMap.GetNodeSize().y)-1;

	return nodePos;

}

void Player::Update(){

	if(m_position == m_currentTarget)
	{
		m_isWalking = false;
		m_velocity.x = 0;
		m_velocity.y = 0;
	}

	if(m_isWalking)
	{
		// Move the player towards its target
		// Calculate distance
		sf::Vector2f distance = m_currentTarget - m_position;

		// Hypotenuse of distance
		float hypothenuse = sqrt((distance.x * distance.x) + (distance.y * distance.y));

		// Normalize distance
		sf::Vector2f normal;
		normal.x = distance.x / hypothenuse;
		normal.y = distance.y / hypothenuse;

		// Fix speed
		if(normal.x > 0 || normal.x < 0)
		{
			if(normal.y > 0 || normal.y < 0)
			{
				normal *= (WALKSPEED * (m_nodeMap.GetNodeSize().y/m_nodeMap.GetNodeSize().x)/1.2f);
			}
		}
		else
		{
			if(normal.y > 0 || normal.y < 0)
			{
				normal *= (WALKSPEED * (m_nodeMap.GetNodeSize().y/m_nodeMap.GetNodeSize().x)/2.5f);
			}
			else
			{
				normal *= WALKSPEED;
			}
		}


		// Set the walk speed
		normal *= (WALKSPEED*m_scale);

		// Check the normal distance
		float normal_hypothenuse = sqrt((normal.x * normal.x) + (normal.y * normal.y));

		if(normal_hypothenuse < hypothenuse){

			// Move player the normal distance
			m_velocity = normal;

		}else{

			// Move player the remaining distance
			m_velocity = distance;

		}
	}
	else
	{

		// The player is idle, check if any new path has been calculated
		if(m_pathFinder.PathComplete()){

			m_currentTarget = ConvertToPixelCoords(m_pathFinder.GetNextMove());
			m_isWalking = true;

			// Start walking
			// Move the player towards its target
			// Calculate distance
			sf::Vector2f distance = m_currentTarget - m_position;

			// Hypotenuse of distance
			float hypothenuse = sqrt((distance.x * distance.x) + (distance.y * distance.y));

			// Normalize distance
			sf::Vector2f normal;
			normal.x = distance.x / hypothenuse;
			normal.y = distance.y / hypothenuse;

			// Set the walk speed
			normal *= WALKSPEED;

			// Check the normal distance
			float normal_hypothenuse = sqrt((normal.x * normal.x) + (normal.y * normal.y));

			if(normal_hypothenuse < hypothenuse){

				// Move player the normal distance
				m_velocity = normal;

			}else{

				// Move player the remaining distance
				m_velocity = distance;

			}
		}
	}

	// Set player direction
	if(m_velocity.x < 0){
		// Left side
		if(m_velocity.y < 0){
			// Left up side
			m_direction = 7;
		}else if(m_velocity.y > 0){
			// Left down side
			m_direction = 5;
		}else{
			// Straight left
			m_direction = 6;
		}
	}else if(m_velocity.x > 0){
		// Right side
		if(m_velocity.y < 0){
			// Right up side
			m_direction = 1;
		}else if(m_velocity.y > 0){
			// Right down side
			m_direction = 3;
		}else{
			// Straight right
			m_direction = 2;
		}
	}else{
		// No side
		if(m_velocity.y < 0){
			// Walking up
			m_direction = 0;
		}else if(m_velocity.y > 0){
			// Walking down
			m_direction = 4;
		}else{
			// Standing still
			m_isWalking = false;
		}
	}

	// Set correct animation
	switch (m_direction){
	case 0:
		if(m_isWalking){
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_walkingUp;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}else{
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_idleUp;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}
		break;
	case 1:
		if(m_isWalking){
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_walkingUpRight;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}else{
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_idleUpRight;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}
		break;
	case 2:
		if(m_isWalking){
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_walkingRight;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}else{
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_idleRight;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}
		break;
	case 3:
		if(m_isWalking){
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_walkingDownRight;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}else{
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_idleDownRight;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}
		break;
	case 4:
		if(m_isWalking){
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_walkingDown;
		}else{
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_idleDown;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}
		break;
	case 5:
		if(m_isWalking){
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_walkingDownLeft;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}else{
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_idleDownLeft;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}
		break;
	case 6:
		if(m_isWalking){
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_walkingLeft;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}else{
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_idleLeft;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}
		break;
	case 7:
		if(m_isWalking){
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_walkingUpLeft;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}else{
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_idleUpLeft;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}
		break;
	default:
		if(m_isWalking){
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_walkingUp;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}else{
			// Pause sound of current animation
			m_currentAnimation->PauseSound();
			// Set new animation
			m_currentAnimation = &m_idleUp;
			// Play sound of new animation
			m_currentAnimation->PlaySound();
		}
		break;
	}

	m_pathFinder.FindPath();
	m_position += m_velocity;

	// Update animation
	m_currentAnimation->update();

	// Update scale and sprite position
	sf::Vector2f offsetPos;
	float scale = m_nodeMap.GetEntityScale();
	int scaleOffset = m_nodeMap.GetScaleOffset();
	float yPos = GetNodePosition().y;

	if(yPos == 0)
		yPos = 1;

	float yNodes = m_nodeMap.GetMapSize().y;
	float scalePerNode = scale/yNodes;

	if(yPos >= scaleOffset)
	{
		yPos = yPos-scaleOffset;
		m_scale = scalePerNode * yPos;
	}
	else
	{
		m_scale = 1.0;
	}

	offsetPos.x = m_position.x - (X_FEETOFFSET)*m_scale;
	offsetPos.y = m_position.y - (Y_FEETOFFSET)*m_scale;

	m_currentAnimation->setPosition(offsetPos);

}

void Player::Render(sf::RenderWindow &window){

	sf::Sprite currentSprite = m_currentAnimation->getSprite();
	currentSprite.setScale(m_scale, m_scale);

	window.draw(currentSprite);

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

	pixelCoords.x = (nodeCoords.x * m_nodeMap.GetNodeSize().x) + (m_nodeMap.GetNodeSize().x/2);
	pixelCoords.y = (nodeCoords.y * m_nodeMap.GetNodeSize().y) + (m_nodeMap.GetNodeSize().y/2);

	return pixelCoords;

}

const int Player::GetZ(){

	return m_position.y;

}

void Player::StopSound(){ m_currentAnimation->PauseSound(); }