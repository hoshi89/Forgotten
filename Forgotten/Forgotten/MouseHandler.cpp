#include "MouseHandler.h"

MouseHandler::MouseHandler(sf::RenderWindow& window)
	:m_m1pressed(false), m_m2pressed(false), 
	m_walkGreen("Data/Animations/MouseIcons/MousepointerWalkGreen.png", 1000, 1), 
	m_walkRed("Data/Animations/MouseIcons/MousepointerWalkRed.png", 1000, 1),
	m_walk("Data/Animations/MouseIcons/MousepointerWalk.png", 1000, 1),
	m_currentMouseAnimation(&m_walkGreen),
	m_window(window)
{
	MousePosition = m_window.convertCoords(sf::Mouse::getPosition(m_window));
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

void MouseHandler::Render(){
	SetPosition();
	m_window.draw(m_currentMouseAnimation->getSprite());
}

bool MouseHandler::IsOver(sf::IntRect rect){
	if(rect.contains(MousePosition.x, MousePosition.y)){
		return true;
	}else{
		return false;
	}
}

void MouseHandler::SetPosition(){
	MousePosition = m_window.convertCoords(sf::Mouse::getPosition(m_window));
	m_currentMouseAnimation->setPosition(MousePosition);
}

sf::Vector2f MouseHandler::GetPosition(){
	return MousePosition;
}

void MouseHandler::Draw(){
	SetPosition();
	m_window.draw(m_currentMouseAnimation->getSprite());
}

