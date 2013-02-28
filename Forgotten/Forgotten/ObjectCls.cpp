#include "ObjectCls.h"
#include "GameManager.h"


ObjectCls::ObjectCls(int aXpos, int aYpos, 
	const string aSpriteName, sf::Vector2f aInteractionNode, sf::IntRect aIntRect,
	 Entity::Direction aDirection) : Entity(), m_currentAnimation(aSpriteName, 1000, 1)
{
	posX = aXpos;
	posY = aYpos;
	m_InteractionRect = aIntRect;
	m_InteractionNode = aInteractionNode;
	m_Direction = aDirection;

}


void ObjectCls::Render(sf::RenderWindow &aWindow)
{
	aWindow.draw(m_currentAnimation.getSprite());
}

void ObjectCls::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

const sf::Sprite& ObjectCls::GetSprite() const
{
	sf::Sprite wSprite = m_currentAnimation.getSprite();
	return m_currentAnimation.getSprite();
}

void ObjectCls::Update()
{

	m_currentAnimation.setPosition(sf::Vector2f(posX, posY));
	m_currentAnimation.update();
}

int const ObjectCls::GetZ()
{
	return 1;
}

void ObjectCls::StopSound()
{
}

void ObjectCls::Interact()
{
	GameManager::GetInstance()->GetPlayer()->GoTo(m_InteractionNode);
	GameManager::GetInstance()->GetPlayer()->SetFocus(this);
}

sf::Vector2f ObjectCls::GetInteractionNode()
{
	return m_InteractionNode;
}

void ObjectCls::StartInteraction()
{
	std::cout <<"Player has reached interactionNode";
	GameManager::GetInstance()->LoadScript("Data/Scripts/dialogtest.txt");
}

bool ObjectCls::MouseOver(MouseHandler& aMouse)
{
	if(m_InteractionRect.contains(aMouse.GetPosition().x, aMouse.GetPosition().y)){
		// Set mouse animation
		std::cout << "Mouse over Object : x: " << aMouse.GetPosition().x << " y: " << aMouse.GetPosition().y << std::endl;
		return true;
	}

	return false;

}

void ObjectCls::GoTo(sf::Vector2f aInteractionNode)
{

}

void ObjectCls::SetDirection(Entity::Direction aDirection)
{
	m_Direction = aDirection;
}



ObjectCls::~ObjectCls(void)
{
}
