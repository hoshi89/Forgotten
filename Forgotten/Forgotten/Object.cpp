#include "Object.h"
#include "GameManager.h"

Object::Object(std::string id, int xPos, int yPos, int interactionX, int interactionY, sf::IntRect hitbox, std::string texture, int timeperframe, int numframes)
	:
	m_id(id),
	m_idle(texture, timeperframe, numframes),
	m_position(xPos, yPos),
	m_interactionNode(interactionX, interactionY),
	m_hasBeenGivenItem(-1),
	xOffset(0),
	yOffset(0),
	m_hitbox(hitbox)
{
	m_currentAnimation = &m_idle;
}

std::string Object::GetID()
{
	return m_id;
}

void Object::SetID(std::string id)
{
	m_id = id;
}

void Object::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

void Object::Update()
{
	// Fix sprite offset
	m_currentAnimation->setPosition(sf::Vector2f(m_position.x-xOffset, m_position.y-yOffset));

	// Update current animation
	m_currentAnimation->update();
}

const sf::Sprite& Object::GetSprite() const
{
	return m_currentAnimation->getSprite();
}

void Object::Render(sf::RenderWindow &window)
{
	window.draw(m_currentAnimation->getSprite());

	// Test rectangle
	sf::RectangleShape tmpShape;
	tmpShape.setSize(sf::Vector2f(m_hitbox.width, m_hitbox.height));
	tmpShape.setPosition(m_hitbox.left, m_hitbox.top);
	tmpShape.setFillColor(sf::Color(255, 0, 0, 100));
	
	window.draw(tmpShape);

}

const int Object::GetZ()
{
	return m_position.y;
}

void Object::StopSound()
{
	m_currentAnimation->StopSound();
}

void Object::Interact(int item)
{
	GameManager::GetInstance()->GetPlayer()->GoTo(m_interactionNode);
	GameManager::GetInstance()->GetPlayer()->SetFocus(this);

	if(item >= 0)
	{
		m_hasBeenGivenItem = item;
	}

}

sf::Vector2f Object::GetInteractionNode()
{
	return m_interactionNode;
}

void Object::StartInteraction()
{
	// Has an object been placed on the object
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

bool Object::MouseOver(MouseHandler &mouse)
{
	if(m_hitbox.contains(mouse.GetPosition().x, mouse.GetPosition().y))
	{
		// The mouse is within the sprite
		mouse.SetCursor(6);
		return true;
	}
	return false;
}

void Object::GoTo(sf::Vector2f)
{
	// Objects don't move...
}

void Object::Inspect()
{
	GameManager::GetInstance()->LoadScript(m_inspectScript);
}

void Object::SetInteractScript(std::string script)
{
	m_interactScript = script;
}

void Object::SetInspectScript(std::string script)
{
	m_inspectScript = script;
}

void Object::SetGiveScript(std::string script)
{
	m_giveScript = script;
}

void Object::SetNoCanDoScript(std::string script)
{
	m_noCanDoScript = script;
}

void Object::SetWantsItem(int id)
{
	m_wantsItem = id;
}

void Object::SetSpriteOffset(int x, int y)
{
	xOffset = x;
	yOffset = y;
}