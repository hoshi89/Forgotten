#include "ScriptText.h"

//Constructor
ScriptText::ScriptText(std::string text, int time, sf::Vector2f position, int rowBreak, std::string style, sf::Color color, int fontsize) : m_text(text), m_time(time), m_position(position), m_expired(false){

	// Load font
	m_font.loadFromFile("Data/Fonts/BebasNeue.otf");

	// Text color
	m_text.setColor(color);

	// Position and size
	m_text.setPosition(m_position);
	m_text.setCharacterSize(fontsize);

	// Background text
	m_bgText.setPosition(m_position.x+2, m_position.y+2);
	m_bgText.setCharacterSize(fontsize);
	m_bgText.setColor(sf::Color::Black);

	// Text style
	for(int i = 0; i < style.size(); i++)
	{
		switch(style[i])
		{
		case 'I':
			// Italic
			m_text.setStyle(sf::Text::Italic);
			m_bgText.setStyle(sf::Text::Italic);
			break;
		case 'B':
			// Bold
			m_text.setStyle(sf::Text::Bold);
			m_bgText.setStyle(sf::Text::Bold);
			break;
		case 'N':
			// Normal
			m_text.setStyle(sf::Text::Regular);
			m_bgText.setStyle(sf::Text::Regular);
			break;
		case 'U':
			// Underline
			m_text.setStyle(sf::Text::Underlined);
			m_bgText.setStyle(sf::Text::Underlined);
			break;
		case 'C':
			// Center text horizontally
			m_text.setPosition((1024-m_text.getGlobalBounds().width)/2, m_position.y);
			m_bgText.setPosition(((1024-m_text.getGlobalBounds().width)/2)+2, m_position.y+2);
			break;
		default:
			// Normal
			m_text.setStyle(sf::Text::Regular);
			m_bgText.setStyle(sf::Text::Regular);
			break;
		}
	}

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

	// Set strings
	m_text.setString(tmpString);
	m_bgText.setString(tmpString);

	// Set fonts
	m_text.setFont(m_font);
	m_bgText.setFont(m_font);

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

