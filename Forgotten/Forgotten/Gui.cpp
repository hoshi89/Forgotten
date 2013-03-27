//Gui Class
#include "Gui.h"
#include "FlagManager.h"
#include "GameManager.h"

static const float SPEED = 1.5f;

//Constructor for GUI
Gui::Gui(MouseHandler& mouse) : 
	m_script(false),
	m_down(false),
	m_showGui(true),
	m_showItems(false),
	m_position(256, -50),
	m_mouseHandler(mouse),
	m_itemInHand(-1),
	m_waitForText(false)
{
	LoadImage();
	m_guiSprite.setPosition(m_position);
	m_guiview.setSize(1024, 576);
	m_guiview.setCenter(512, 288);

	SetCursorVector();

	//m_DialogState = DialogStateEnum::ContinueDialog;
}
	 
int Gui::LoadImage()
{
	if(!m_gui.loadFromFile("Data/Inventory/InventoryV2.png")){
		return EXIT_FAILURE;
	}
	m_guiSprite.setTexture(m_gui);
	return 0;
}

//Move GUI in X coords
void Gui::Move(const float SPEED)
{
	m_guiSprite.move(0, SPEED);
}

//Drawing the gui and its items.
void Gui::Draw(sf::RenderWindow &window)
{
	window.setView(m_guiview);

	//Update GUI
	Update();

	bool mousepressed;
	sf::Vector2f mouseOverPos;

 	LevelDialogsCls* currentLevelDialogs = GameManager::GetInstance()->GetLevelManager()->GetCurrentLevel()->GetLevelDialogs();
 	switch (m_DialogState)
 	{
 	case DialogStateEnum::ContinueDialog:
		mousepressed = false;
		if(m_mouseHandler.mouse1WasPressed())
			mousepressed = true;
		m_DialogState = currentLevelDialogs->ShowDialog(window, m_DeckId, m_PlayerPos, m_EntityPos, mousepressed);
		mousepressed = false;
 		break;
 	case DialogStateEnum::WaitForAnswer:
		mousepressed = false;
		//if(m_mouseHandler.mouse1WasPressed())
		//	mousepressed = true;
		m_DialogState = currentLevelDialogs->ShowDialog(window, m_DeckId, m_PlayerPos, m_EntityPos, mousepressed); 
		mouseOverPos.y = window.convertCoords(sf::Mouse::getPosition(window), m_guiview).y;
		mouseOverPos.x = window.convertCoords(sf::Mouse::getPosition(window), m_guiview).x; 
		currentLevelDialogs->IsMouseOverAnswer(&mouseOverPos);
 		if(m_mouseHandler.mouse1WasPressed())
 		{
 			sf::Vector2f mousePos;
 			mousePos.y = window.convertCoords(sf::Mouse::getPosition(window), m_guiview).y;
			mousePos.x = window.convertCoords(sf::Mouse::getPosition(window), m_guiview).x; 
 			currentLevelDialogs->ChooseAnswer(&mousePos);
			mousepressed = false;
			m_DialogState = currentLevelDialogs->ShowDialog(window, m_DeckId, m_PlayerPos, m_EntityPos, mousepressed);
 		}
		mousepressed = false;
 		break;
	case DialogStateEnum::EndDialog:
		break;
	}

	if(m_showGui)
	{
		window.draw(m_guiSprite);
			
		if(m_showItems)
		{
			Inventory::GetInstance()->Draw(window);	
		}
	}

	//Draw text
	DrawText(window);

	//Delete text that have expired
	DeleteText();

	//Remove dead Items
	Inventory::GetInstance()->RemoveItem();

	for(int i = 0; i < Inventory::GetInstance()->Contains().size(); i++)
	{
		if(Inventory::GetInstance()->GetItemsRect(i).contains(window.convertCoords(sf::Mouse::getPosition(window), m_guiview).x, window.convertCoords(sf::Mouse::getPosition(window), m_guiview).y))
		{
			if(m_mouseHandler.mouse1WasPressed())
			{
				if(!m_mouseHandler.HoldsItem())
				{
					m_mouseHandler.SetInventoryCursor(GetIdCursor(Inventory::GetInstance()->GetId(i)));
					m_mouseHandler.SetHoldingItem(true);
					m_itemInHand = Inventory::GetInstance()->GetId(i);
				}
				else if(m_itemInHand == Inventory::GetInstance()->Contains()[i]->GetRequires())
				{
					GameManager::GetInstance()->LoadScript(Inventory::GetInstance()->GetWantScript(i));
					RemoveHand();
				}
			}
			else if(m_mouseHandler.mouse2WasPressed())
			{
				GameManager::GetInstance()->LoadScript(Inventory::GetInstance()->GetScript(i));
			}
		}
	}

	if(!m_script)
	{
		IsOverlap(window);
	}
}

//Update GUI Rect for collision and render(Get Guis' position) Items
void Gui::Update()
{
	//Set Rect into right coords
	if(m_showGui)
	{
		sf::IntRect rect(m_guiSprite.getPosition().x, m_guiSprite.getPosition().y, m_gui.getSize().x, m_gui.getSize().y);
		m_textureRect = rect;
	}

	//Move GUI
	if(m_guiSprite.getPosition().y < -1 && m_down)
	{
		Move(SPEED);
		m_showItems = true;
	}
	else if(m_guiSprite.getPosition().y < -50)
	{
		Move(0);
		m_showItems = false;
	}
	else if(!m_down)
	{
		Move(-SPEED);
		m_showItems = true;
	}
	else
	{
		Move(0);
	}

	//Get Position of Gui to items
	Inventory::GetInstance()->Render(m_guiSprite.getPosition());
}

sf::Vector2f Gui::GetPosition()
{
	return m_position = m_guiSprite.getPosition();
}

sf::IntRect Gui::GetRect()
{
	return m_textureRect;
}

//Check if mouse is over
void Gui::IsOverlap(sf::RenderWindow &window)
{
	if(m_textureRect.contains(window.convertCoords(sf::Mouse::getPosition(window), m_guiview).x, window.convertCoords(sf::Mouse::getPosition(window), m_guiview).y))
	{
		m_down = true;
		m_showItems = true;
		m_mouseHandler.SetCursor(5);
		if(m_mouseHandler.mouse1WasPressed() && !m_mouseHandler.HoldsItem())
		{
			RemoveHand();
		}
	}
	else
	{
		m_down = false;
		if(m_mouseHandler.mouse1WasPressed() && m_mouseHandler.HoldsItem())
		{
			RemoveHand();
		}
	}
}

//Handling text event
void Gui::PushText(std::string text, int time, sf::Vector2f position, int rowbreak, std::string style, sf::Color color, int fontsize)
{
	ScriptText* scriptText = new ScriptText(text, time, position, rowbreak, style, color, fontsize);
	m_texts.push_back(scriptText);
}

//Drawing text
void Gui::DrawText(sf::RenderWindow& window)
{
	m_waitForText = false;
	for(TextVector::iterator i = m_texts.begin(); i != m_texts.end(); i++)
	{
		(*i)->Draw(window, m_mouseHandler);

		if((*i)->WaitForText())
			m_waitForText = true;
	}
}

//Delete text vector
void Gui::DeleteText()
{
	//Local vector
	TextVector texts;
	for(TextVector::iterator i = m_texts.begin(); i != m_texts.end(); i++)
	{
		if((*i)->IsExpired())
		{
			delete (*i);
		}else{
			texts.push_back(*i);
		}
	}
	m_texts = texts;
}

//Load from file(items.txt) all objects and push them into a vector
void Gui::SetCursorVector()
{
	//Loads and opens a text file
	m_objectFile.open("Data/items.txt");

	while(m_objectFile.good())
	{
		//Create local temp holders
		int size;
		m_objectFile >> size;
		int id;
		std::string name;
		std::string directory;
		std::string script;
		int requires;
		std::string wantScript;

		for(int i = 0; i < size; i++)
		{
			m_objectFile >> id >> name >> directory >> script >> requires >> wantScript;
			m_objectCursor.push_back(new Animation(directory, 1000, 1));
		}
	}
	m_objectFile.close();
}

//Returns Animation of the objectsVector
Animation* Gui::GetIdCursor(int id)
{
	CursorVector::iterator i = m_objectCursor.begin() + id-1;
		
	return *i;
}

//Script events, show GUI/Draw GUI
void Gui::SetShowGui(bool showGui)
{
	m_showGui = showGui;
}

//Script events, pull down GUI
void Gui::SetIsDownGui(bool down)
{
	m_down = down;
}

void Gui::SetDeckId(string aDeckId, sf::Vector2f aPlayerpos, sf::Vector2f aEntitypos)
{
	m_DeckId = aDeckId;
	m_PlayerPos = aPlayerpos;
	m_EntityPos = aEntitypos;
	m_DialogState = DialogStateEnum::ContinueDialog;
}

DialogStateEnum Gui::getDialogState()
{
	return m_DialogState;
}

int Gui::ItemInHand()
{
	if(m_mouseHandler.HoldsItem())
	{
		return m_itemInHand;
	}
	return -1;
}

void Gui::IsInScript(bool script)
{
	m_script = script;
}

//Remove object at hand
void Gui::RemoveHand()
{
	m_mouseHandler.DropItem();
	m_itemInHand = -1;
}

bool Gui::WaitForText()
{
	return m_waitForText;
}