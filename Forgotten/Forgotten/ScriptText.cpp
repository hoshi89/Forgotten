#include "ScriptText.h"

//Constructor
ScriptText::ScriptText(std::string text, int time, sf::Vector2f position) : m_text(text), m_time(time), m_position(position), m_expired(false){
	m_text.setPosition(m_position);
}

void ScriptText::Draw(sf::RenderWindow& window){
	if(m_clock.getElapsedTime().asSeconds() < m_time){
		window.draw(m_text);
	}else{
		m_expired = true;
	}
}

bool ScriptText::IsExpired(){
	return m_expired;
}

