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
	int GetId();
	bool HoldsItem();
	void DropItem();
	void SetCursor(int id);
	void SetInventoryCursor(Animation* animation);
	void SetHoldingItem(bool holdItem);
private:
	Animation m_default;
	Animation m_walkGreen;
	Animation m_walkRed;
	Animation m_walk;
	Animation m_portal;
	Animation m_grabItem;
	Animation* m_currentMouseAnimation;
	bool m_m1pressed;
	bool m_m2pressed;
	sf::Vector2f MousePosition;
	void SetPosition();
	sf::RenderWindow& m_window;
	int m_id;
	bool m_holdsItem;
	
};

#endif