#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(std::string animationSheet, int timePerFrame, int numFrames, int posX, int posY, int z, const std::string& soundFilename)
	:m_animation(animationSheet, timePerFrame, numFrames, soundFilename), m_position(posX, posY), m_z(z)
{
}

void BackgroundObject::SetPosition(int x, int y){}

void BackgroundObject::Update(){

	m_animation.setPosition(m_position);
	m_animation.update();

}

const sf::Sprite& BackgroundObject::GetSprite() const{ return sf::Sprite(); }

void BackgroundObject::Render(sf::RenderWindow &window){

	window.draw(m_animation.getSprite());

}

const int BackgroundObject::GetZ(){ return m_z; }

void BackgroundObject::StopSound(){ m_animation.StopSound(); }