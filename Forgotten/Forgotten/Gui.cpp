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
	window.setView(m_guiview);

	window.draw(m_guiSprite);
	
	Update();
	
	Inventory::GetInstance()->Draw(window);

	IsOverlap(window);

	DrawText(window);

	DeleteText();

	Inventory::GetInstance()->RemoveItem();

	for(int i = 0; i < Inventory::GetInstance()->Contains().size(); i++){
		if(Inventory::GetInstance()->GetItemsRect(i).contains(window.convertCoords(sf::Mouse::getPosition(window), m_guiview).x, window.convertCoords(sf::Mouse::getPosition(window), m_guiview).y)){
			m_mouseHandler.SetCurrentMouseAnimation(Inventory::GetInstance()->GetDirectory(i), Inventory::GetInstance()->GetId(i));
		}else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
			m_mouseHandler.SetDefaultMouseAnimation();
			if(m_mouseHandler.mouse1IsPressed()){
				std::string text = "I suddenly wanted to walk again";
				PushText(text, 2, sf::Vector2f(200, 200));
			}
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

void Gui::PushText(std::string text, int time, sf::Vector2f position){
	ScriptText* scriptText = new ScriptText(text, time, position);
	m_texts.push_back(scriptText);
}

void Gui::DrawText(sf::RenderWindow& window){
	for(TextVector::iterator i = m_texts.begin(); i != m_texts.end(); i++){
		(*i)->Draw(window);
	}
}

void Gui::DeleteText(){
	TextVector texts;
	for(TextVector::iterator i = m_texts.begin(); i != m_texts.end(); i++){
		if((*i)->IsExpired()){
			delete (*i);
		}else{
			texts.push_back((*i));
		}
	}
	m_texts = texts;
}
	