#include "InventoryItem.h"

InventoryItem::InventoryItem(int id, std::string name, std::string directory) : m_id(id), m_name(name), m_directory(directory), m_isAlive(true){
	m_texture.loadFromFile(m_directory);
	m_sprite.setTexture(m_texture);
}

InventoryItem::~InventoryItem(){
	//destructor
}

bool InventoryItem::IsAlive(){
	return m_isAlive;
}

void InventoryItem::SetDead(){
	m_isAlive = false;
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

sf::Vector2f InventoryItem::GetPosition(){
	return m_position;
}

void InventoryItem::SetTexture(std::string directory){
	m_texture.loadFromFile(directory);
	m_sprite.setTexture(m_texture);
}

void InventoryItem::Draw(sf::RenderWindow &window){
	sf::IntRect rect(m_sprite.getPosition().x, m_sprite.getPosition().y, m_texture.getSize().x, m_texture.getSize().y);
	m_textureRect = rect;
	window.draw(m_sprite);
}

void InventoryItem::SetPosition(float x, float y){
	m_sprite.setPosition(x, y);
}

sf::IntRect InventoryItem::GetRect(){
	return m_textureRect;
}

sf::Texture InventoryItem::GetTexture(){
	return m_texture;
}
	
