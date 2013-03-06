#include "ScriptText.h"

//Constructor
ScriptText::ScriptText(std::string text, int time, sf::Vector2f position, int rowBreak) : m_text(text), m_time(time), m_position(position), m_expired(false){

	// White text
	m_text.setPosition(m_position);
	m_text.setCharacterSize(16);

	// Background text
	m_bgText.setPosition(m_position.x+1, m_position.y+1);
	m_bgText.setCharacterSize(16);
	m_bgText.setColor(sf::Color::Black);

	// Wrap text
	int chars_before_linebreak = rowBreak;
	int charCounter = 0;

	sf::String tmpString = m_text.getString();

	// Iterate through the string
	for(int i = 0; i < tmpString.getSize(); i++)
	{
		if(charCounter >= chars_before_linebreak)
		{
			int breakAt = tmpString.find(sf::String(" "), i);

			tmpString.insert(breakAt+1, "\n");

			charCounter = 0;
		}
		charCounter++;
	}

	m_text.setString(tmpString);
	m_bgText.setString(tmpString);

}

void ScriptText::Draw(sf::RenderWindow& window){
	if(m_clock.getElapsedTime().asSeconds() < m_time){
		window.draw(m_bgText);
		window.draw(m_text);
	}else{
		m_expired = true;
	}
}

bool ScriptText::IsExpired(){
	return m_expired;
}

