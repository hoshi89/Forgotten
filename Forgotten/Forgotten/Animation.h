#ifndef INCLUDED_ANIMATION
#define INCLUDED_ANIMATION

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include "SFX.h"

class Animation{
public:
	Animation(const std::string& filename, int timePerFrame, int numFrames, const std::string& soundFilename = "");
	~Animation();
	void update();
	void setPosition(const sf::Vector2f& position);
	const sf::Sprite& getSprite() const;
	void PauseSound();
	void PlaySound();
	void StopSound();
	void SetScale(float scale);
private:
	sf::Clock m_frameTimer;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	int m_timePerFrame;
	int m_numFrames;
	int m_currentFrame;
	SFX m_sound;
};

#endif