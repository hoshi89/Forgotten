#include "Inventory.h"

Inventory::Inventory(){
}

Inventory::~Inventory(){
	while(!m_items.empty()){
		delete m_items.back();
		m_items.pop_back();
	}
}

void Inventory::AddItem(std::string filename){
	//
}

std::string Inventory::GetDirectory(int id){
	return m_items[id-1]->GetDirectory();
}


void Inventory::LoadItems(std::string filename){
	levelfile.open(filename);
	int size;
	levelfile >> size;
	for(int i = 0; i < size; ++i){
	int id = 0;
	std::string name;
	sf::Vector2f position;
	std::string directory;
	levelfile >> id >> name >> position.x >> position.y >> directory;
	m_items.push_back(new InventoryItem(id, name, position, directory));
	}
}

void Inventory::Read(){
	for(int i = 0; i < m_items.size(); i++){
		std::cout << m_items[i]->GetId() << ' ';
		std::cout << m_items[i]->GetName() << ' ';
		std::cout << m_items[i]->GetXPosition() << ' ';
		std::cout << m_items[i]->GetYPosition() << ' ';
		std::cout << m_items[i]->GetDirectory() << std::endl;
	}
}