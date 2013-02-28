#include "Object.h"
#include "GameManager.h"

Object::Object()
	:m_idle("Filnamn", 100, 1)
{
}

void Object::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

void Object::Update()
{
	// Update current animation
	m_currentAnimation->update();
	m_currentAnimation->setPosition(m_position);
}

const sf::Sprite& Object::GetSprite() const
{
	return m_currentAnimation->getSprite();
}

void Object::Render(sf::RenderWindow &window)
{
	window.draw(m_currentAnimation->getSprite());
}

const int Object::GetZ()
{
	return m_position.y;
}

void Object::StopSound()
{
	m_currentAnimation->StopSound();
}

void Object::Interact()
{
	GameManager::GetInstance()->GetPlayer()->GoTo(m_interactionNode);
	GameManager::GetInstance()->GetPlayer()->SetFocus(this);
}

sf::Vector2f Object::GetInteractionNode()
{
	return m_interactionNode;
}

void Object::StartInteraction()
{
	GameManager::GetInstance()->LoadScript(m_interactScript);
}

bool Object::MouseOver(MouseHandler &mouse)
{
	if(m_currentAnimation->getSprite().getGlobalBounds().contains(mouse.GetPosition()))
	{
		// The mouse is within the sprite, but is it over the actual object?
		if(m_currentAnimation->getSprite().getTexture()->copyToImage().getPixel(mouse.GetPosition().x, mouse.GetPosition().y) != sf::Color::Transparent)
		{
			// The color isn't transparent
			return true;
		}
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