#include "InventoryItem.h"


InventoryItem::InventoryItem(int id, std::string name, sf::Vector2f position ,std::string directory) : m_id(id), m_name(name), m_position(position), m_directory(directory){
}

int InventoryItem::GetId(){
	return m_id;
}

std::string InventoryItem::GetDirectory(){
	return m_directory;
}

std::string InventoryItem::GetName(){
	return m_name;
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