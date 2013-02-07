#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(std::string animationSheet, int timePerFrame, int numFrames, int posX, int posY)
	:m_animation(animationSheet, timePerFrame, numFrames), m_position(posX, posY)
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

int BackgroundObject::GetZ(){ return m_z; }