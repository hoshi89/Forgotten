#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(const std::string& id, const std::string& animationSheet, int timePerFrame, int numFrames, bool loop, int posX, int posY, int z, Behaviour behaviour, const std::string& soundFilename, int pauseTime)
	:m_behaviour(behaviour),
	m_position(posX, posY),
	m_z(z)
{
	m_animations[id] = new Animation(animationSheet, timePerFrame, numFrames, loop, soundFilename, pauseTime);
	SetAnimation(id);
}

std::string BackgroundObject::GetId()
{
	return m_id;
}

void BackgroundObject::SetId(std::string id)
{
	m_id = id;
}

void BackgroundObject::SetPosition(int x, int y){}

void BackgroundObject::Update()
{
	// Behaviours
	switch(m_behaviour)
	{
	case 1:
		MovingCar();
		break;
	default:
		break;
	}

	m_position += m_velocity;

	m_currentAnimation->SetPosition(m_position);
	m_currentAnimation->Update();
}

const sf::Sprite& BackgroundObject::GetSprite() const{ return sf::Sprite(); }

void BackgroundObject::Render(sf::RenderWindow &window)
{

	window.draw(m_currentAnimation->GetSprite());
}

const int BackgroundObject::GetZ()
{
	return m_z;
}

void BackgroundObject::StopSound()
{ 
	m_currentAnimation->StopSound(); 
}

void BackgroundObject::MovingCar()
{
	m_velocity.y = 0;
	m_velocity.x = 30;

	if(m_clock.getElapsedTime().asSeconds() > 5)
	{
		m_currentAnimation->PlaySound();
		m_position.x = -300;
		m_clock.restart();
	}
}

void BackgroundObject::AddAnimation(const std::string& id, const std::string& animationSheet, int timePerFrame, int numFrames, bool loop, const std::string& soundFilename, int pauseTime)
{
	Animation *newAnimation = new Animation(animationSheet, timePerFrame, numFrames, loop, soundFilename, pauseTime);
	m_animations[id] = newAnimation;
}

void BackgroundObject::SetAnimation(const std::string& id)
{
	m_currentAnimation = m_animations.find(id)->second;
	m_currentAnimation->Restart();
}