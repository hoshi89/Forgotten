//Inventory Item Class
/*
	Class for creating InventoryItems to the Inventory
*/
#include "InventoryItem.h"

//Constructor
InventoryItem::InventoryItem(int id, 
	std::string name,
	std::string directory,
	std::string aScriptName,
	int requires,
	std::string wantScript)
	: m_id(id), m_name(name), 
	m_directory(directory), 
	m_isAlive(true), 
	m_scriptName(aScriptName),
	m_requires(requires), 
	m_wantScript(wantScript)
{
	m_texture.loadFromFile(m_directory);
	m_sprite.setTexture(m_texture);
}

InventoryItem::~InventoryItem()
{
	//destructor
}

//Return if item is alive
bool InventoryItem::IsAlive()
{
	return m_isAlive;
}

//Set dead to item...
void InventoryItem::SetDead()
{
	m_isAlive = false;
}

//Return id of item
int InventoryItem::GetId()
{
	return m_id;
}

//Return Requires of item
int InventoryItem::GetRequires()
{
	return m_requires;
}

//Return directory of item
std::string InventoryItem::GetDirectory()
{
	return m_directory;
}

//Return name of item
std::string InventoryItem::GetName()
{
	return m_name;
}

//Return script of item
std::string InventoryItem::GetScript()
{

	return m_scriptName;
}

//Return what script items want
std::string InventoryItem::GetWantScript()
{
	return m_wantScript;
}

//Return position of item
sf::Vector2f InventoryItem::GetPosition()
{
	return m_position;
}

//Set texture to items from a directory on computer
void InventoryItem::SetTexture(std::string directory)
{
	m_texture.loadFromFile(directory);
	m_sprite.setTexture(m_texture);
}

//Draw every item sprite and set rect for items
void InventoryItem::Draw(sf::RenderWindow &window)
{
	sf::IntRect rect(m_sprite.getPosition().x, m_sprite.getPosition().y, m_texture.getSize().x, m_texture.getSize().y);
	m_textureRect = rect;
	window.draw(m_sprite);
}

//Set Position for a item
void InventoryItem::SetPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

//Return rect of item
sf::IntRect InventoryItem::GetRect()
{
	return m_textureRect;
}

//Return texture of item
sf::Texture InventoryItem::GetTexture()
{
	return m_texture;
}
	
