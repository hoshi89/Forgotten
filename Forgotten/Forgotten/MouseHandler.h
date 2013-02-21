#ifndef INCLUDED_MOUSEHANDLER
#define INCLUDED_MOUSEHANDLER

#include "Animation.h"

class MouseHandler{
public:
	MouseHandler(sf::RenderWindow& window);
	bool mouse1WasPressed();
	bool mouse2WasPressed();
	bool mouse1IsPressed();
	bool mouse2IsPressed();
	void Render();
	bool IsOver(sf::IntRect rect);
	sf::Vector2f GetPosition();
	void Draw();
	void SetCurrentMouseAnimation(std::string& directory, int id);
	void SetDefaultMouseAnimation();
	int GetId();
	bool IfHoldsItem();
private:
	Animation m_walkGreen;
	Animation m_walkRed;
	Animation m_walk;
	Animation* m_item;
	Animation* m_currentMouseAnimation;
	bool m_m1pressed;
	bool m_m2pressed;
	sf::Vector2f MousePosition;
	void SetPosition();
	sf::RenderWindow& m_window;
	int m_id;
};

#endif