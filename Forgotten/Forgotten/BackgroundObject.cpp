#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(std::string animationSheet, int timePerFrame, int numFrames, int posX, int posY, int z, Behaviour behaviour, const std::string& soundFilename, int pauseTime)
	:m_animation(animationSheet, timePerFrame, numFrames, soundFilename, pauseTime),
	m_behaviour(behaviour),
	m_position(posX, posY),
	m_z(z)
{
}

std::string BackgroundObject::GetID()
{
	return m_id;
}

void BackgroundObject::SetID(std::string id)
{
	m_id = id;
}

void BackgroundObject::SetPosition(int x, int y){}

void BackgroundObject::Update(){

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

	m_animation.setPosition(m_position);
	m_animation.update();

}

const sf::Sprite& BackgroundObject::GetSprite() const{ return sf::Sprite(); }

void BackgroundObject::Render(sf::RenderWindow &window){

	window.draw(m_animation.getSprite());

}

const int BackgroundObject::GetZ(){ return m_z; }

void BackgroundObject::StopSound(){ m_animation.StopSound(); }

void BackgroundObject::MovingCar()
{
	m_position.x = cos(m_clock.getElapsedTime().asSeconds())*100;
}