#include "ObjectCls.h"


ObjectCls::ObjectCls(const char *aDeckName, int aXpos, int aYpos) 
	: DialogOwnerCls(aDeckName, aXpos, aYpos), 
	m_currentAnimation("Data/Animations/Objects/necklace.png", 10000, 1)
{
	mDialog = DialogCls::DialogCls(aDeckName);
	posX = aXpos;
	posY = aYpos;
}


//void ObjectCls::PlaceText(DialogCls aDialog)
//{
//}

void ObjectCls::Render(sf::RenderWindow &aWindow)
{
	//m_currentString = mDialog.getCurrentString();
	//sf::Text m_theText = sf::Text::Text(m_currentString);
	//aWindow.draw(m_theText);
	sf::Text m_currentText = mDialog.getCurrentText();
	sf::Font myFont;
	myFont.loadFromFile("C:/windows/fonts/Arial.ttf");
	m_currentText.setFont(myFont);
	m_currentText.setColor(sf::Color::White);
	m_currentText.setCharacterSize(15);
	m_currentText.setPosition(posX-10, posY-25);

	sf::Sprite mySprite = GetSprite();
	mySprite.setPosition(posX, posY);
	const sf::Texture *mytexture = mySprite.getTexture();
	aWindow.draw(mySprite);
	aWindow.draw(m_currentText);

}
void ObjectCls::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

const sf::Sprite& ObjectCls::GetSprite() const
{
//	sf::Sprite wSprite = m_currentAnimation.getSprite();
//	wSprite.scale(1, 1);
	return m_currentAnimation.getSprite();
}

void ObjectCls::Update()
{
}



ObjectCls::~ObjectCls(void)
{
}
