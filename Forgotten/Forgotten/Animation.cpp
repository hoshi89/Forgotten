#include "Animation.h"

Animation::Animation(const std::string& filename, int timePerFrame, int numFrames, const std::string& soundFilename, int pauseTime):m_timePerFrame(timePerFrame), m_numFrames(numFrames), m_currentFrame(0), m_sound(soundFilename, ""), m_pauseTime(pauseTime){
	m_texture.loadFromFile(filename);
	m_sprite.setTexture(m_texture);

	sf::IntRect textureRect(0, 0, m_texture.getSize().x/m_numFrames, m_texture.getSize().y);
	m_sprite.setTextureRect(textureRect);
}

Animation::~Animation(){
}

void Animation::update(){

	// Update sound position, Z = 0
	m_sound.SetSoundPosition(m_sprite.getGlobalBounds().left, m_sprite.getGlobalBounds().top, 0);

	if(m_animationPauseTimer.getElapsedTime().asSeconds() > m_pauseTime)
	{

		if(m_currentFrame == 0){
			m_sound.Play();
		}

		if(m_frameTimer.getElapsedTime().asMilliseconds() > m_timePerFrame){
			m_frameTimer.restart();
			m_currentFrame++;
			if(m_currentFrame >= m_numFrames){
				m_sound.Stop();
				m_currentFrame = 0;
				m_animationPauseTimer.restart();
			}

		}

	}

	sf::IntRect currentRect = m_sprite.getTextureRect();
	currentRect.left = currentRect.width * m_currentFrame;

	m_sprite.setTextureRect(currentRect);
}

void Animation::setPosition(const sf::Vector2f& position){
	m_sprite.setPosition(position);
}

const sf::Sprite& Animation::getSprite() const{ return m_sprite; }

void Animation::PauseSound(){ m_sound.Pause(); }

void Animation::PlaySound(){ m_sound.Play(); }

void Animation::StopSound(){ m_sound.Stop(); }

void Animation::SetScale(float scale)
{
	m_sprite.setScale(scale, scale);
}

void Animation::SetRelativeSound(bool relative)
{
	m_sound.SetRelativeSound(relative);
}

void Animation::SetSoundPosition(int x, int y, int z)
{
	m_sound.SetSoundPosition(x, y, z);
}