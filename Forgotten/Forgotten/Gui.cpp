#include "Gui.h"

Gui::Gui(sf::Vector2f position) : m_position(position), down(false){
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

void Gui::Move(const float SPEED){
	m_inventorySprite.move(0, SPEED);
}

void Gui::Draw(sf::RenderWindow &window){
	window.draw(m_inventorySprite);
}

void Gui::Render(sf::RenderWindow &window){
	const float SPEED = 1.2f;
	if(m_inventorySprite.getPosition().y < 0 && !down){
		Move(SPEED);
	}else if(m_inventorySprite.getPosition().y > -10 && !down){
		down = true;
	}
	Draw(window);
}