#include "NpcCls.h"
#include "GameManager.h"
#include "FlagManager.h"


NpcCls::NpcCls(int aXpos, int aYpos, const string aSpriteName, int numFrames, int timePerFrame,
	sf::Vector2f aInteractionNode,
	GenericMap &aMap, string interactScript, string inspectScript, string giveScript, string noCanDoScript, sf::IntRect hitbox, std::string id, int wantsItem)
	: Entity(), m_currentAnimation(aSpriteName, timePerFrame, numFrames),
	m_position(sf::Vector2f(aXpos, aYpos)), m_nodeMap(aMap),
	m_interactScript(interactScript),
	m_inspectScript(inspectScript),
	m_giveScript(giveScript),
	m_noCanDoScript(noCanDoScript),
	m_id(id),
	m_wantsItem(wantsItem),
	xOffset(0),
	yOffset(0),
	m_hitbox(hitbox)
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

	// Fix sprite offset
	m_currentAnimation.setPosition(sf::Vector2f(posX-xOffset, posY-yOffset));

	m_currentAnimation.update();
}

int const NpcCls::GetZ()
{
	return m_position.y;
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
	if(m_hitbox.contains(mouse.GetPosition().x, mouse.GetPosition().y))
	{
		mouse.SetCursor(7);
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

void NpcCls::Inspect()
{
	GameManager::GetInstance()->LoadScript(m_inspectScript);
}

void NpcCls::SetWantsItem(int id)
{
	m_wantsItem = id;
}

void NpcCls::SetSpriteOffset(int x, int y)
{
	xOffset = x;
	yOffset = y;
}

std::string NpcCls::GetID()
{
	return m_id;
}