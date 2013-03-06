#include "NpcCls.h"
#include "GameManager.h"
#include "FlagManager.h"


NpcCls::NpcCls(int aXpos, int aYpos, const string aSpriteName,
	sf::Vector2f aInteractionNode,
	GenericMap &aMap, string aScript)
	: Entity(), m_currentAnimation(aSpriteName, 1000, 1),
	m_position(sf::Vector2f(aXpos, aYpos)), m_nodeMap(aMap),
	m_CurrentScript(aScript)
{
	posX = aXpos;
	posY = aYpos;
	m_InteractionNode = aInteractionNode;
}

void NpcCls::Render(sf::RenderWindow &aWindow)
{
	aWindow.draw(m_currentAnimation.getSprite());
}

void NpcCls::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

const sf::Sprite& NpcCls::GetSprite() const
{
	sf::Sprite wSprite = m_currentAnimation.getSprite();
	return m_currentAnimation.getSprite();
}

void NpcCls::Update()
{

	m_currentAnimation.setPosition(sf::Vector2f(posX, posY));
	m_currentAnimation.update();
}

int const NpcCls::GetZ()
{
	return 1;
}

void NpcCls::StopSound()
{
}

void NpcCls::Interact(int item)
{
	GameManager::GetInstance()->GetPlayer()->GoTo(m_InteractionNode);
	GameManager::GetInstance()->GetPlayer()->SetFocus(this);
}

sf::Vector2f NpcCls::GetInteractionNode()
{
	return m_InteractionNode;
}

void NpcCls::StartInteraction()
{
	std::cout <<"Player has reached interactionNode";
	GameManager::GetInstance()->LoadScript(m_CurrentScript);
}

bool NpcCls::MouseOver(MouseHandler& mouse)
{
	if(m_currentAnimation.getSprite().getGlobalBounds().contains(mouse.GetPosition())){
		// Set mouse animation
		std::cout << "Mouse over NPC : x: " << mouse.GetPosition().x << " y: " << mouse.GetPosition().y << std::endl;
		return true;
	}

	return false;

}

void NpcCls::GoTo(sf::Vector2f aInteractionNode)
{

}

void NpcCls::SetDirection(Entity::Direction aDirection)
{
	m_Direction = aDirection;
}
NpcCls::~NpcCls(void)
{
}
