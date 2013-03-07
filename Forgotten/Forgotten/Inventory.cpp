#include "Inventory.h"

Inventory* Inventory::m_instance = NULL;

Inventory* Inventory::GetInstance(){
	if(!m_instance)
		m_instance = new Inventory;
		return m_instance;
}

Inventory::Inventory(){
}

Inventory::~Inventory(){
	//Clearing the vector
	while(!m_items.empty()){
		delete m_items.back();
		m_items.pop_back();
	}
}

void Inventory::AddItem(int aId){
	levelfile.open("Data/items.txt");
	//Put Item into vector
	int size;
	levelfile >> size;
	int id;
	std::string name;
	std::string directory;
	std::string scriptName;
	for(int i = 0; i < size; i++){
		//Local variables to hold values
		levelfile >> id >> name >> directory >> scriptName;
		//Pushes right(id) object into inventory vector
		if(id == aId)
		{
			m_items.push_back(new InventoryItem(id, name, directory, scriptName));
		}
	}
	levelfile.close();
}

sf::Vector2f Inventory::GetPosition(int id){
	return m_items[id]->GetPosition();
}

std::string Inventory::GetDirectory(int id){
	return m_items[id]->GetDirectory();
}

std::string Inventory::GetName(int id){
	return m_items[id]->GetName();
}

std::string Inventory::GetScript(int id)
{
	return m_items[id]->GetScript();
}

int Inventory::GetId(int i){
	return m_items[i]->GetId();
}

void Inventory::Read(int i){
	std::cout << m_items[i]->GetName();
}

void Inventory::Render(sf::Vector2f position){
	for(int i = 0; i < m_items.size(); i++){
		m_items[i]->SetPosition(position.x+55*i+40, position.y+10);
	}
}

void Inventory::Draw(sf::RenderWindow &window){
	for(InventoryVector::iterator i = m_items.begin(); i != m_items.end(); i++){
		(*i)->Draw(window);
	}
}

int Inventory::IsOverlap(sf::RenderWindow& window, sf::View& view){
	for(int i = 0; i < m_items.size(); i++){
		if(m_items[i]->GetRect().contains(window.convertCoords(sf::Mouse::getPosition(window), view).x, window.convertCoords(sf::Mouse::getPosition(window), view).y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
			return m_items[i]->GetId();
		}
	}
}

std::vector<InventoryItem*> Inventory::Contains(){
	return m_items;
}

void Inventory::RemoveItem(){
	InventoryVector items;
	for(InventoryVector::iterator i = m_items.begin(); i != m_items.end(); i++){
		if((*i)->IsAlive()){
			items.push_back((*i));
		}else{
			delete (*i);
		}
	}
	m_items = items;
}

sf::IntRect Inventory::GetItemsRect(int i){
	return m_items[i]->GetRect();
}

void Inventory::KillItem(int id){
	for(int i = 0; i < m_items.size(); i++)
	{
		if(m_items[i]->GetId() == id)
		{
			m_items[i]->SetDead();
		}
	}
}