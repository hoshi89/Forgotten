#include "Gui.h"

Gui::Gui(sf::Vector2f position) : m_position(position){
	LoadImage();
	m_inventorySprite.setPosition(m_position);
	m_inventorySprite.scale(0.75f, 0.75f);
}

int Gui::LoadImage(){
	if(!m_inventory.loadFromFile("Data/Inventory/InventoryV03.png")){
		return -1;
	}
	m_inventorySprite.setTexture(m_inventory);
	return 1;
}

void Gui::Move(float y, float offset){
	if(m_inventorySprite.getPosition().y < 300){
	m_position.x += y*offset;
	}
}

void Gui::Draw(sf::RenderWindow &window){
	window.draw(m_inventorySprite);
}

void Gui::Render(sf::RenderWindow &window){
	Move(0.1f, 1.f);
	Draw(window);
}