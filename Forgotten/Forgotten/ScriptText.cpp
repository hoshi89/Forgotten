#include "ScriptText.h"

//Constructor
ScriptText::ScriptText(std::string text, int time, sf::Vector2f position, int rowBreak, std::string style, sf::Color color, int fontsize) : m_text(text), m_time(time), m_position(position), m_expired(false){

	const int OUTLINE_THICKNESS = 1;

	// Load font
	m_font.loadFromFile("Data/Fonts/BebasNeue.otf");

	// Text color
	m_text.setColor(color);

	// Position and size
	m_text.setPosition(m_position);
	m_text.setCharacterSize(fontsize);

	// Background text
	m_bgText0.setPosition(m_position.x-OUTLINE_THICKNESS, m_position.y-OUTLINE_THICKNESS);
	m_bgText0.setCharacterSize(fontsize);
	m_bgText0.setColor(sf::Color::Black);

	m_bgText1.setPosition(m_position.x+OUTLINE_THICKNESS, m_position.y-OUTLINE_THICKNESS);
	m_bgText1.setCharacterSize(fontsize);
	m_bgText1.setColor(sf::Color::Black);

	m_bgText2.setPosition(m_position.x+OUTLINE_THICKNESS, m_position.y+OUTLINE_THICKNESS);
	m_bgText2.setCharacterSize(fontsize);
	m_bgText2.setColor(sf::Color::Black);

	m_bgText3.setPosition(m_position.x-OUTLINE_THICKNESS, m_position.y+OUTLINE_THICKNESS);
	m_bgText3.setCharacterSize(fontsize);
	m_bgText3.setColor(sf::Color::Black);

	// Set fonts
	m_text.setFont(m_font);
	m_bgText0.setFont(m_font);
	m_bgText1.setFont(m_font);
	m_bgText2.setFont(m_font);
	m_bgText3.setFont(m_font);

	// Wrap text
	sf::String tmpString = m_text.getString();
	int chars_before_linebreak = rowBreak;
	int charCounter = 0;

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
	m_bgText0.setString(tmpString);
	m_bgText1.setString(tmpString);
	m_bgText2.setString(tmpString);
	m_bgText3.setString(tmpString);

	// Text style
	for(int i = 0; i < style.size(); i++)
	{
		switch(style[i])
		{
		case 'I':
			// Italic
			m_text.setStyle(sf::Text::Italic);
			m_bgText0.setStyle(sf::Text::Italic);
			m_bgText1.setStyle(sf::Text::Italic);
			m_bgText2.setStyle(sf::Text::Italic);
			m_bgText3.setStyle(sf::Text::Italic);
			break;
		case 'B':
			// Bold
			m_text.setStyle(sf::Text::Bold);
			m_bgText0.setStyle(sf::Text::Bold);
			m_bgText1.setStyle(sf::Text::Bold);
			m_bgText2.setStyle(sf::Text::Bold);
			m_bgText3.setStyle(sf::Text::Bold);
			break;
		case 'N':
			// Normal
			m_text.setStyle(sf::Text::Regular);
			m_bgText0.setStyle(sf::Text::Regular);
			m_bgText1.setStyle(sf::Text::Regular);
			m_bgText2.setStyle(sf::Text::Regular);
			m_bgText3.setStyle(sf::Text::Regular);
			break;
		case 'U':
			// Underline
			m_text.setStyle(sf::Text::Underlined);
			m_bgText0.setStyle(sf::Text::Underlined);
			m_bgText1.setStyle(sf::Text::Underlined);
			m_bgText2.setStyle(sf::Text::Underlined);
			m_bgText3.setStyle(sf::Text::Underlined);
			break;
		case 'C':
			// Center text horizontally
			m_text.setPosition(512 - (m_text.getGlobalBounds().width/2), m_position.y);
			m_bgText0.setPosition(((1024-m_text.getGlobalBounds().width)/2)+OUTLINE_THICKNESS, m_position.y+OUTLINE_THICKNESS);
			m_bgText1.setPosition(((1024-m_text.getGlobalBounds().width)/2)-OUTLINE_THICKNESS, m_position.y+OUTLINE_THICKNESS);
			m_bgText2.setPosition(((1024-m_text.getGlobalBounds().width)/2)+OUTLINE_THICKNESS, m_position.y-OUTLINE_THICKNESS);
			m_bgText3.setPosition(((1024-m_text.getGlobalBounds().width)/2)-OUTLINE_THICKNESS, m_position.y-OUTLINE_THICKNESS);
			break;
		default:
			// Normal
			m_text.setStyle(sf::Text::Regular);
			m_bgText0.setStyle(sf::Text::Regular);
			m_bgText1.setStyle(sf::Text::Regular);
			m_bgText2.setStyle(sf::Text::Regular);
			m_bgText3.setStyle(sf::Text::Regular);
			break;
		}
	}
}

void ScriptText::Draw(sf::RenderWindow& window){
	if(m_clock.getElapsedTime().asSeconds() < m_time){
		window.draw(m_bgText0);
		window.draw(m_bgText1);
		window.draw(m_bgText2);
		window.draw(m_bgText3);
		window.draw(m_text);
	}else{
		m_expired = true;
	}
}

bool ScriptText::IsExpired(){
	return m_expired;
}

