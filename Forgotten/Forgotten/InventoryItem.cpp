#include "InventoryItem.h"


InventoryItem::InventoryItem(int id, std::string name, std::string directory) : m_id(id), m_name(name), m_directory(directory){
	m_texture.loadFromFile(m_directory);
	m_sprite.setTexture(m_texture);
	m_sprite.scale(0.50f, 0.50f);
}

int InventoryItem::GetId(){
	return m_id;
}

void InventoryItem::SetId(int id){
	m_id = id;
}

std::string InventoryItem::GetDirectory(){
	return m_directory;
}

void InventoryItem::SetDirectory(std::string directory){
	m_directory = directory;
}

std::string InventoryItem::GetName(){
	return m_name;
}

void InventoryItem::SetName(std::string name){
	m_name = name;
}

float InventoryItem::GetXPosition(){
	return m_position.x;
}

float InventoryItem::GetYPosition(){
	return m_position.y;
}

void InventoryItem::SetPosition(float x, float y){
	m_position.x = x;
	m_position.y = y;
}

sf::Vector2f InventoryItem::GetPosition(){
	return m_position;
}

sf::Sprite& InventoryItem::GetSprite(){
	return m_sprite;
}

void InventoryItem::SetSprite(sf::Sprite &sprite){
	m_sprite = sprite;
}

void InventoryItem::SetTexture(std::string directory){
	m_texture.loadFromFile(directory);
	m_sprite.setTexture(m_texture);
}

void InventoryItem::Draw(sf::RenderWindow &window){
	m_sprite.setPosition(GetPosition());
	window.draw(m_sprite);
}
