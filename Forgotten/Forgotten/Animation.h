#ifndef INCLUDED_ANIMATION
#define INCLUDED_ANIMATION

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include "SFX.h"

class Animation{
public:
	Animation(const std::string& filename, int timePerFrame, int numFrames, const std::string& soundFilename = "", int pauseTime=0);
	~Animation();
	void update();
	void setPosition(const sf::Vector2f& position);
	const sf::Sprite& getSprite() const;
	void PauseSound();
	void PlaySound();
	void StopSound();
	void SetScale(float scale);
	void SetRelativeSound(bool relative);
	void SetSoundPosition(int x, int y, int z);
private:
	sf::Clock m_frameTimer;
	sf::Clock m_animationPauseTimer;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	int m_timePerFrame;
	int m_numFrames;
	int m_currentFrame;
	int m_pauseTime;
	SFX m_sound;
};

#endif