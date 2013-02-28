#ifndef INCLUDED_SCRIPTTEXT
#define INCLUDED_SCRIPTTEXT

#include <SFML\Graphics.hpp>

class ScriptText{
public:
	ScriptText(std::string text, int time, sf::Vector2f position);
	void Draw(sf::RenderWindow& window);
	bool IsExpired();
private:
	sf::Text m_text;
	sf::Clock m_clock;
	int m_time;
	sf::Vector2f m_position;
	bool m_expired;
};

#endif