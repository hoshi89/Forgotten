#include "Gui.h"

Gui::Gui(sf::Vector2f position) : m_position(position), down(false){
	LoadImage();
	m_inventorySprite.setPosition(m_position);
	m_inventorySprite.setScale(0.75f, 0.75f);
}

int Gui::LoadImage(){
	if(!m_inventory.loadFromFile("Data/Inventory/InventoryV03.png")){
		return EXIT_FAILURE;
	}
	m_inventorySprite.setTexture(m_inventory);
	return 0;
}

void Gui::Move(const float SPEED){
	m_inventorySprite.move(0, SPEED);
}

void Gui::Draw(sf::RenderWindow &window){
	sf::IntRect rect(m_inventorySprite.getPosition().x, m_inventorySprite.getPosition().y, m_inventory.getSize().x-150, m_inventory.getSize().y);
	m_textureRect = rect;
	window.draw(m_inventorySprite);
}

void Gui::Render(sf::RenderWindow &window){
	const float SPEED = 1.2f;
	if(m_inventorySprite.getPosition().y < 0 && down){
		Move(SPEED);
	}else if(m_inventorySprite.getPosition().y < -50){
		Move(0);
	}else if(!down){
		Move(-SPEED);
	}
	Draw(window);
}

sf::Vector2f Gui::GetPosition(){
	return m_inventorySprite.getPosition();
}

sf::IntRect Gui::GetRect(){
	return m_textureRect;
}

void Gui::IsOverlap(sf::IntRect rect){
	if(m_textureRect.intersects(rect)){
		down = true;
	}else{
		down = false;
	}
}