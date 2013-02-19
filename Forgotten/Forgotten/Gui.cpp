#include "Gui.h"
#include "FlagManager.h"

Gui::Gui(MouseHandler& mouse) : 
	m_down(false),
	m_position(200, -50),
	m_mouseHandler(mouse)
{
	LoadImage();
	m_guiSprite.setPosition(m_position);

}

int Gui::LoadImage(){
	if(!m_gui.loadFromFile("Data/Inventory/InventoryV03.png")){
		return EXIT_FAILURE;
	}
	m_guiSprite.setTexture(m_gui);
	return 0;
}

void Gui::Move(const float SPEED){
	m_guiSprite.move(0, SPEED);
}

void Gui::Render(){
	const float SPEED = 1.2f;
	if(m_guiSprite.getPosition().y < 0 && m_down){
		Move(SPEED);
	}else if(m_guiSprite.getPosition().y < -50){
		Move(0);
	}else if(!m_down){
		Move(-SPEED);
	}
}

void Gui::Draw(sf::RenderWindow &window){
	Update();
	IsOverlap();
	window.draw(m_guiSprite);
	Inventory::GetInstance()->Draw(window);
}

void Gui::Update(){
	sf::IntRect rect(m_guiSprite.getPosition().x, m_guiSprite.getPosition().y, m_gui.getSize().x, m_gui.getSize().y);
	m_textureRect = rect;
	Render();
	Inventory::GetInstance()->Render(m_guiSprite.getPosition());
}

sf::Vector2f Gui::GetPosition(){
	return m_guiSprite.getPosition();
}

sf::IntRect Gui::GetRect(){
	return m_textureRect;
}

void Gui::IsOverlap(){
	sf::Vector2i mouse(m_mouseHandler.GetPosition().x, m_mouseHandler.GetPosition().y);
	if(m_textureRect.contains(mouse)){
		m_down = true;
	}else{
		m_down = false;
	}
}
