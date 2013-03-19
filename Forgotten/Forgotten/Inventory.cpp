#include "Inventory.h"

Inventory* Inventory::m_instance = NULL;

Inventory* Inventory::GetInstance()
{
	if(!m_instance)
		m_instance = new Inventory;
		return m_instance;
}

Inventory::Inventory()
{
	//Puts items into a vector
	LoadItems();
}

//Destructor, removing every item in vector
Inventory::~Inventory()
{
	//Clearing the vector
	while(!m_items.empty())
	{
		delete m_items.back();
		m_items.pop_back();
	}
	//Clearing container vector of items
	while(!m_itemsContainer.empty())
	{
		delete m_itemsContainer.back();
		m_itemsContainer.pop_back();
	}
}

//Load all items from a file, putting them into computers memory
void Inventory::LoadItems()
{
	levelfile.open("Data/items.txt");
	//Put Item into vector
	int size;
	levelfile >> size;
	int id;
	std::string name;
	std::string directory;
	std::string scriptName;
	int requires;
	std::string wantScript;
	for(int i = 0; i < size; i++)
	{
		//Local variables to hold values
		levelfile >> id >> name >> directory >> scriptName >> requires >> wantScript;
		//Pushes right(id) object into inventory vector
		m_itemsContainer.push_back(new InventoryItem(id, name, directory, scriptName, requires, wantScript));
	}

	levelfile.close();
}

//Adds required item of an id to a vector to draw items.
void Inventory::AddItem(int aId)
{
	for(InventoryVector::iterator i = m_itemsContainer.begin(); i != m_itemsContainer.end(); i++)
	{
		if(aId == (*i)->GetId())
		{
			m_items.push_back((*i));
		}
	}
}

//Get position from specific item in a position in vector
sf::Vector2f Inventory::GetPosition(int id)
{
	return m_items[id]->GetPosition();
}

//Get a items directory
std::string Inventory::GetDirectory(int id)
{
	return m_items[id]->GetDirectory();
}

//Get name from a item
std::string Inventory::GetName(int id)
{
	return m_items[id]->GetName();
}

//Get a script from a item in vector
std::string Inventory::GetScript(int id)
{
	return m_items[id]->GetScript();
}

//Get a script that a item wants.
std::string Inventory::GetWantScript(int id)
{
	return m_items[id]->GetWantScript();
}

//Get a id from a item in vector
int Inventory::GetId(int i)
{
	return m_items[i]->GetId();
}

//Read a name from items a vector
void Inventory::Read(int i)
{
	std::cout << m_items[i]->GetName();
}

//Set all position for items in vector
void Inventory::Render(sf::Vector2f position)
{
	for(int i = 0; i < m_items.size(); i++)
	{
		m_items[i]->SetPosition(position.x+58*i+39, position.y+10);
	}
}

//Draw every item in vector
void Inventory::Draw(sf::RenderWindow &window)
{
	for(InventoryVector::iterator i = m_items.begin(); i != m_items.end(); i++)
	{
		(*i)->Draw(window);
	}
}

//Get if mouse overlaps a item in vector
int Inventory::IsOverlap(sf::RenderWindow& window, sf::View& view)
{
	for(int i = 0; i < m_items.size(); i++)
	{
		if(m_items[i]->GetRect().contains(window.convertCoords(sf::Mouse::getPosition(window), view).x, window.convertCoords(sf::Mouse::getPosition(window), view).y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			return m_items[i]->GetId();
		}
	}
}

//Return items vector
std::vector<InventoryItem*> Inventory::Contains()
{
	return m_items;
}

//Clear dead items from memory
void Inventory::RemoveItem()
{
	InventoryVector items;

	for(InventoryVector::iterator i = m_items.begin(); i != m_items.end(); i++)
	{
		if((*i)->IsAlive())
		{
			items.push_back((*i));
		}
		else
		{
			delete (*i);
		}
	}
	m_items = items;
}

//Return every items rect
sf::IntRect Inventory::GetItemsRect(int i)
{
	return m_items[i]->GetRect();
}

//Remove a item in vector
void Inventory::KillItem(int id)
{
	for(int i = 0; i < m_items.size(); i++)
	{
		if(m_items[i]->GetId() == id)
		{
			m_items[i]->SetDead();
		}
	}
}

//Combine two items into a specific, it requires...
void Inventory::Combine(int requires, int itemInHand)
{
	//Combines two objects
	//If itemInHand gets it's required number it combines to a new item...
	switch(requires)
	{
	case 1:
		Inventory::GetInstance()->AddItem(8);
		Inventory::GetInstance()->Contains()[itemInHand]->SetDead();
		break;
	case 3:
		Inventory::GetInstance()->AddItem(8);
		Inventory::GetInstance()->Contains()[itemInHand]->SetDead();
		break;
	default:
		//Don't add
		break;
	}
}