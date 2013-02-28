#include "MouseHandler.h"

MouseHandler::MouseHandler(sf::RenderWindow& window)
	:m_m1pressed(false), m_m2pressed(false),
	m_holdsItem(false),
	m_default("Data/Animations/MouseIcons/default.png", 1000, 1),
	m_walkGreen("Data/Animations/MouseIcons/MousepointerWalkGreen.png", 1000, 1), 
	m_walkRed("Data/Animations/MouseIcons/MousepointerWalkRed.png", 1000, 1),
	m_walk("Data/Animations/MouseIcons/MousepointerWalk.png", 1000, 1),
	m_portal("Data/Animations/MouseIcons/portal.png", 50, 14),
	m_grabItem("Data/Animations/MouseIcons/OverGui.png", 1000, 1),
	m_currentMouseAnimation(&m_default),
	m_window(window)
{
	m_window.setMouseCursorVisible(false);
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

//void MouseHandler::SetCurrentMouseAnimation(std::string& directory, int id){
//	if(m_currentMouseAnimation == m_item){
//		delete m_item;
//		m_item = new Animation(directory, 1000, 1);
//		m_currentMouseAnimation = m_item;
//		m_id = id;
//	}else{
//		m_item = new Animation(directory, 1000, 1);
//		m_currentMouseAnimation = m_item;
//		m_id = id;
//	}
//}

void MouseHandler::Draw(){

	// Update animation
	m_currentMouseAnimation->update();

	SetPosition();
	m_window.draw(m_currentMouseAnimation->getSprite());
}

int MouseHandler::GetId(){
	return m_id;
}

void MouseHandler::SetCursor(int id){
	if(!m_holdsItem){
		switch(id){
		case 0:
			m_currentMouseAnimation = &m_default;
			break;
		case 1:
			m_currentMouseAnimation = &m_walkGreen;
			break;
		case 2:
			m_currentMouseAnimation = &m_walkRed;
			break;
		case 3:
			m_currentMouseAnimation = &m_walk;
			break;
		case 4:
			m_currentMouseAnimation = &m_portal;
			break;
		case 5:
			m_currentMouseAnimation = &m_grabItem;
			break;
		default:
			m_currentMouseAnimation = &m_default;
			break;
		}
	}
}

void MouseHandler::SetInventoryCursor(Animation* animation){
	m_currentMouseAnimation = animation;
}

bool MouseHandler::HoldsItem(){
	if(m_holdsItem){
		return true;
	}else{
		return false;
	}
}

void MouseHandler::SetHoldingItem(bool holdItem){
	m_holdsItem = holdItem;
}

void MouseHandler::DropItem(){
	m_holdsItem = false;
}