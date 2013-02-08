#include "ObjectCls.h"


ObjectCls::ObjectCls(const char *aDeckName, int aXpos, int aYpos, Player *aPlayer) 
	: DialogOwnerCls(aDeckName, aXpos, aYpos, aPlayer), 
	m_currentAnimation("Data/Animations/Objects/necklace.png", 10000, 1)
{
	mDialog = DialogCls::DialogCls(aDeckName);
	m_currentText = mDialog.getCurrentText();
//	m_currentText = ManageText(m_currentText);
	posX = aXpos;
	posY = aYpos;
}


//sf::Vector2f ObjectCls::PlaceText(DialogCls aDialog)
//{
//	if(mDialog.PlayerOwnCard())
//		return sf::Vector2f(m_player->GetPosition().x, m_player->GetPosition().y);
//	else
//		return sf::Vector2f(posX, posY);
//}

void ObjectCls::Render(sf::RenderWindow &aWindow)
{
	//m_currentString = mDialog.getCurrentString();
	//sf::Text m_theText = sf::Text::Text(m_currentString);
	//aWindow.draw(m_theText);

	aWindow.draw(m_currentText);
	aWindow.draw(m_currentAnimation.getSprite());

}
void ObjectCls::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

const sf::Sprite& ObjectCls::GetSprite() const
{
	return m_currentAnimation.getSprite();
}

sf::Text ObjectCls::ManageText(sf::Text aText)
{
	m_currentText.setColor(sf::Color::White);
	return m_currentText;
}

void ObjectCls::Update()
{
	m_currentText.setPosition(900, 550);
	m_currentAnimation.setPosition(sf::Vector2f(posX, posY));
	m_currentAnimation.update();
}

int const ObjectCls::GetZ()
{
	return 1;
}



ObjectCls::~ObjectCls(void)
{
}
