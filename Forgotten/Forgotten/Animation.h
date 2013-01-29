#ifndef INCLUDED_ANIMATION
#define INCLUDED_ANIMATION

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>

class Animation{
public:
	Animation(const std::string& filename, int timePerFrame, int numFrames);
	~Animation();
	void update();
	void setPosition(const sf::Vector2f& position);
	const sf::Sprite& getSprite() const;
private:
	sf::Clock m_frameTimer;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	int m_timePerFrame;
	int m_numFrames;
	int m_currentFrame;
};

#endif