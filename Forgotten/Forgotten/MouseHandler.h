#ifndef INCLUDED_MOUSEHANDLER
#define INCLUDED_MOUSEHANDLER

#include <SFML\Window.hpp>

class MouseHandler{
public:
	MouseHandler();
	bool mouse1WasPressed();
	bool mouse2WasPressed();
	bool mouse1IsPressed();
	bool mouse2IsPressed();
private:
	bool m_m1pressed;
	bool m_m2pressed;
};

#endif