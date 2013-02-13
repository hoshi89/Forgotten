#ifndef INCLUDED_MOUSEHANDLER
#define INCLUDED_MOUSEHANDLER

#include "Animation.h"

class MouseHandler{
public:
	MouseHandler();
	bool mouse1WasPressed();
	bool mouse2WasPressed();
	bool mouse1IsPressed();
	bool mouse2IsPressed();
	void Render(sf::RenderWindow &window);
	bool IsOver(sf::IntRect rect);
	sf::Vector2f GetPosition();
private:
	Animation m_walkGreen;
	Animation m_walkRed;
	Animation m_walk;
	Animation* m_currentMouseAnimation;
	bool m_m1pressed;
	bool m_m2pressed;
	sf::Vector2f m_position;
	void SetPosition();
};

#endif