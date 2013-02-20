#include "Gui.h"
#include "FlagManager.h"

Gui::Gui(MouseHandler& mouse) : 
	m_down(false),
	m_position(200, -50),
	m_mouseHandler(mouse)
{
	LoadImage();
	m_guiSprite.setPosition(m_position);
	m_guiview.setSize(1024, 576);
	m_guiview.setCenter(512, 288);
	Inventory::GetInstance()->AddItem(1);
	Inventory::GetInstance()->AddItem(2);
	Inventory::GetInstance()->AddItem(3);
	Inventory::GetInstance()->AddItem(4);
	Inventory::GetInstance()->AddItem(5);
	Inventory::GetInstance()->AddItem(6);
	Inventory::GetInstance()->AddItem(7);
}

int Gui::LoadImage(){
	if(!m_gui.loadFromFile("Data/Inventory/InventoryV2.png")){
		return EXIT_FAILURE;
	}
	m_guiSprite.setTexture(m_gui);
	return 0;
}

void Gui::Move(const float SPEED){
	m_guiSprite.move(0, SPEED);
}

void Gui::Render(){
	const float SPEED = 1.5f;
	if(m_guiSprite.getPosition().y < 0 && m_down){
		Move(SPEED);
	}else if(m_guiSprite.getPosition().y < -50){
		Move(0);
	}else if(!m_down){
		Move(-SPEED);
	}else{
		Move(0);
	}
}

void Gui::Draw(sf::RenderWindow &window){
	Update();
	window.setView(m_guiview);
	window.draw(m_guiSprite);
	Inventory::GetInstance()->Draw(window);
	IsOverlap(window);
	Inventory::GetInstance()->RemoveItem();
	for(int i = 0; i < Inventory::GetInstance()->Contains().size(); i++){
		if(Inventory::GetInstance()->GetItemsRect(i).contains(window.convertCoords(sf::Mouse::getPosition(window), m_guiview).x, window.convertCoords(sf::Mouse::getPosition(window), m_guiview).y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
			m_mouseHandler.SetCurrentMouseAnimation(Inventory::GetInstance()->GetDirectory(i));
			Inventory::GetInstance()->KillItem(i);	
		}
	}

}

void Gui::Update(){
	sf::IntRect rect(m_guiSprite.getPosition().x, m_guiSprite.getPosition().y, m_gui.getSize().x, m_gui.getSize().y);
	m_textureRect = rect;
	Render();
	Inventory::GetInstance()->Render(m_guiSprite.getPosition());
}

sf::Vector2f Gui::GetPosition(){
	return m_position = m_guiSprite.getPosition();
}

sf::IntRect Gui::GetRect(){
	return m_textureRect;
}

void Gui::IsOverlap(sf::RenderWindow &window){
	if(m_textureRect.contains(window.convertCoords(sf::Mouse::getPosition(window), m_guiview).x, window.convertCoords(sf::Mouse::getPosition(window), m_guiview).y)){
		m_down = true;
		}else{
		m_down = false;
	}
}