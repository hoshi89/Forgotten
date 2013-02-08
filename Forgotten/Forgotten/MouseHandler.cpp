#include "MouseHandler.h"

MouseHandler::MouseHandler()
	:m_m1pressed(false), m_m2pressed(false)
{
}

bool MouseHandler::mouse1WasPressed(){

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(m_m1pressed){
			return false;
		}else{
			m_m1pressed = true;
			return true;
		}

	}else{

		m_m1pressed = false;
		return false;

	}

}

bool MouseHandler::mouse2WasPressed(){

	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		if(m_m2pressed){
			return false;
		}else{
			m_m2pressed = true;
			return true;
		}

	}else{

		m_m2pressed = false;
		return false;

	}

}

bool MouseHandler::mouse1IsPressed(){

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;

	return false;

}

bool MouseHandler::mouse2IsPressed(){

	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		return true;

	return false;

}