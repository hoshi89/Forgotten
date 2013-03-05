#include "ScriptText.h"

//Constructor
ScriptText::ScriptText(std::string text, int time, sf::Vector2f position) : m_text(text), m_time(time), m_position(position), m_expired(false){

	m_text.setPosition(m_position);
	m_text.setCharacterSize(16);

	// Wrap text
	int chars_before_linebreak = 35;
	int charCounter = 0;

	sf::String tmpString = m_text.getString();

	// Iterate through the string
	for(int i = 0; i < tmpString.getSize(); i++)
	{
		if(charCounter >= chars_before_linebreak)
		{
			int rowBreak = tmpString.find(sf::String(" "), i);

			tmpString.insert(rowBreak+1, "\n");
			m_text.setString(tmpString);

			charCounter = 0;
		}
		charCounter++;
	}

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

