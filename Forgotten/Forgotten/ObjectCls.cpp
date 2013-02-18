#include "ObjectCls.h"


ObjectCls::ObjectCls(int aXpos, int aYpos,
	Player *aPlayer, const string aSpriteName) 
	: DialogOwnerCls(aXpos, aYpos, aPlayer, aSpriteName) 
{
//	m_currentText = ManageText(m_currentText);
}


//sf::Vector2f ObjectCls::PlaceText(DialogCls aDialog)
//{
//	if(mDialog.PlayerOwnCard())
//		return sf::Vector2f(m_player->GetPosition().x, m_player->GetPosition().y);
//	else
//		return sf::Vector2f(posX, posY);
//}

//void ObjectCls::Render(sf::RenderWindow &aWindow)
//{
////	sf::Text wCurrentText = sf::Text(TextsToRender, sf::Font::getDefaultFont(), 15);
//	//sf::Text currentText = ManageText();
//	//aWindow.draw(currentText);
//	//aWindow.draw(m_currentAnimation.getSprite());
//}

//void ObjectCls::SetPosition(int x, int y)
//{
//	m_position.x = x;
//	m_position.y = y;
//}

const sf::Sprite& ObjectCls::GetSprite() const
{
	sf::Sprite wSprite = m_currentAnimation.getSprite();
	return m_currentAnimation.getSprite();
}

//sf::Text ObjectCls::ManageText()
//{
//	sf::Text wCurrentText = mDialog.getCurrentText();
//	wCurrentText.setPosition(posX, posY);
//	wCurrentText.setColor(sf::Color::White);
//	return wCurrentText;
//}

//void ObjectCls::Update()
//{
//
//	m_currentAnimation.setPosition(sf::Vector2f(posX, posY));
//	m_currentAnimation.update();
//}

int const ObjectCls::GetZ()
{
	return 1;
}



ObjectCls::~ObjectCls(void)
{
}
