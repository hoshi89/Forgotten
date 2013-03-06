#include "NpcCls.h"
#include "GameManager.h"
#include "FlagManager.h"


NpcCls::NpcCls(int aXpos, int aYpos, const string aSpriteName,
	sf::Vector2f aInteractionNode,
	GenericMap &aMap, string interactScript, string inspectScript, string giveScript, string noCanDoScript, int wantsItem)
	: Entity(), m_currentAnimation(aSpriteName, 1000, 1),
	m_position(sf::Vector2f(aXpos, aYpos)), m_nodeMap(aMap),
	m_interactScript(interactScript),
	m_inspectScript(inspectScript),
	m_giveScript(giveScript),
	m_noCanDoScript(noCanDoScript),
	m_wantsItem(wantsItem)
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

	if(item >= 0)
	{
		m_hasBeenGivenItem = item;
	}
}

sf::Vector2f NpcCls::GetInteractionNode()
{
	return m_InteractionNode;
}

void NpcCls::StartInteraction()
{
	// Has an object been dropped on the npc?
	if(m_hasBeenGivenItem >= 0)
	{
		if(m_hasBeenGivenItem == m_wantsItem)
		{
			GameManager::GetInstance()->LoadScript(m_giveScript);
		}
		else
		{
			GameManager::GetInstance()->LoadScript(m_noCanDoScript);
		}
	}
	else
	{
		GameManager::GetInstance()->LoadScript(m_interactScript);
	}
	m_hasBeenGivenItem = -1;
}

bool NpcCls::MouseOver(MouseHandler& mouse)
{
	if(m_currentAnimation.getSprite().getGlobalBounds().contains(mouse.GetPosition())){

		sf::Vector2f mousePixel(mouse.GetPosition().x-m_currentAnimation.getSprite().getPosition().x, mouse.GetPosition().y-m_currentAnimation.getSprite().getPosition().y);
		sf::Image npcImage = m_currentAnimation.getSprite().getTexture()->copyToImage();
		mousePixel.x += m_currentAnimation.getSprite().getTextureRect().left;
		mousePixel.y += m_currentAnimation.getSprite().getTextureRect().top;

		sf::Color cPoint = npcImage.getPixel(mousePixel.x, mousePixel.y);

		if(cPoint.a != 0)
		{
			// Set mouse animation
			mouse.SetCursor(7);
			return true;
		}
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

void NpcCls::Inspect()
{
	GameManager::GetInstance()->LoadScript(m_inspectScript);
}