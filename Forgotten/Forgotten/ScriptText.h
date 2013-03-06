#ifndef INCLUDED_SCRIPTTEXT
#define INCLUDED_SCRIPTTEXT

#include <SFML\Graphics.hpp>

class ScriptText{
public:
	ScriptText(std::string text, int time, sf::Vector2f position, int rowBreak, char style, sf::Color color, int fontsize);
	void Draw(sf::RenderWindow& window);
	bool IsExpired();
private:
	sf::Text m_text;
	sf::Text m_bgText;
	sf::Clock m_clock;
	int m_time;
	sf::Vector2f m_position;
	bool m_expired;
};

#endif
