#ifndef INCLUDED_MAINMENU
#define INCLUDED_MAINMENU

#include "MouseHandler.h"
#include <stack>

class MainMenu{
public:
	MainMenu();
	void Update(sf::RenderWindow& window);
private:
	void Draw(sf::RenderWindow& window);
	void LoadImage();
	void SetRect();
	void PushMenu();
	MouseHandler* m_mouseHandler;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Text m_text;
	/*typedef std::stack<MainMenu>MenuStack;
	MenuStack m_menuStack;*/
	sf::IntRect m_continueRect;
	sf::IntRect m_newGameRect;
	sf::IntRect m_quitRect;
};

#endif