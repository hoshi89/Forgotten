//Gui class

#include "Gui.h"
#include "FlagManager.h"
#include "GameManager.h"

//Constructor for GUI
Gui::Gui(MouseHandler& mouse) : 
	m_down(false),
	m_showGui(false),
	m_showItems(false),
	m_position(200, -50),
	m_mouseHandler(mouse)
{
	LoadImage();
	m_guiSprite.setPosition(m_position);
	m_guiview.setSize(1024, 576);
	m_guiview.setCenter(512, 288);

	//Temp for adding items to vector.
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

//Move GUI in-X coord
void Gui::Move(const float SPEED){
	m_guiSprite.move(0, SPEED);
}

//Move GUI depend on circumstances
void Gui::Render(){
	const float SPEED = 1.5f;
	if(m_guiSprite.getPosition().y < 0 && m_down){
		Move(SPEED);
	}else if(m_guiSprite.getPosition().y < -50){
		Move(0);
		m_showItems = false;
	}else if(!m_down){
		Move(-SPEED);
	}else{
		Move(0);
	}
}

//Drawing the gui and its items.
void Gui::Draw(sf::RenderWindow &window){

	window.setView(m_guiview);

	if(m_showGui){
		window.draw(m_guiSprite);
			
		if(m_showItems){
			Inventory::GetInstance()->Draw(window);
		}
	}

	//Om m_isWaitingForAnswer är true och mouseClicked anropa choose(mousPosition)
	if(m_isDialogState)
	{
		//Hämtar dialogerna för "rätt" level
		LevelDialogsCls* currentLevelDialogs = GameManager::GetInstance()->GetLevelManager()->GetCurrentLevel()->GetLevelDialogs();
		//if(m_isWaitingForAnswer && m_MouseHandler->mouse1WasPressed())
		//{
//			sf::Vector2f mousePos = m_MouseHandler->GetPosition();
			//currentLevelDialogs->Choosed(15);
//		}
		m_isDialogState = currentLevelDialogs->ShowDialog(window, "blabla", GameManager::GetInstance()->GetPlayer()->GetPosition(), sf::Vector2f(200, 200)); 
	}
	//Update GUI
	Update();

	IsOverlap(window);

	DrawText(window);

	DeleteText();

	Inventory::GetInstance()->RemoveItem();

	for(int i = 0; i < Inventory::GetInstance()->Contains().size(); i++){
		if(Inventory::GetInstance()->GetItemsRect(i).contains(window.convertCoords(sf::Mouse::getPosition(window), m_guiview).x, window.convertCoords(sf::Mouse::getPosition(window), m_guiview).y)){
			m_mouseHandler.SetCurrentMouseAnimation(Inventory::GetInstance()->GetDirectory(i), Inventory::GetInstance()->GetId(i));
		}
	}
}

void Gui::SetShowGui(bool showGui){
	m_showGui = showGui;
}

//Update GUI Rect for collision and render(Get Guis' position) Items
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

//Check if mouse is over
void Gui::IsOverlap(sf::RenderWindow &window){
	if(m_textureRect.contains(window.convertCoords(sf::Mouse::getPosition(window), m_guiview).x, window.convertCoords(sf::Mouse::getPosition(window), m_guiview).y)){
		m_down = true;
		m_showItems = true;
		}else{
		m_down = false;
	}
}

//Handling text event
void Gui::PushText(std::string text, int time, sf::Vector2f position){
	ScriptText* scriptText = new ScriptText(text, time, position);
	m_texts.push_back(scriptText);
}

//Drawing text
void Gui::DrawText(sf::RenderWindow& window){
	for(TextVector::iterator i = m_texts.begin(); i != m_texts.end(); i++){
		(*i)->Draw(window);
	}
}

//Delete text vector
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
	