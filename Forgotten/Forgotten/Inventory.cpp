#include "Inventory.h"

Inventory::Inventory(std::string filename) : m_filename(filename){
	//LoadItems();
}

Inventory::~Inventory(){
	//Clearing the vector
	while(!m_items.empty()){
		delete m_items.back();
		m_items.pop_back();
	}
}

void Inventory::AddItem(int aId){
	levelfile.open(m_filename);
	//Puts Items into vector
	int size;
	levelfile >> size;
	int id;
	std::string name;
	std::string directory;
	for(int i = 0; i < size; i++){
		//Local variables to hold values
		levelfile >> id >> name >> directory;
		//Pushes right(id) object into inventory vector
		if(id == aId){
			m_items.push_back(new InventoryItem(id, name, directory));
		}
	}
	levelfile.close();
}

sf::Vector2f Inventory::GetPosition(int id){
	return m_items[id]->GetPosition();
}

std::string Inventory::GetDirectory(int id){
	return m_items[id-1]->GetDirectory();
}

void Inventory::LoadItems(){
	levelfile.open(m_filename);
	//Puts Items into vector
	int size;
	levelfile >> size;
	int id;
	std::string name;
	sf::Vector2f position;
	std::string directory;
	for(int i = 0; i < size; i++){
		//Local variables to hold values
		levelfile >> id >> name >> position.x >> position.y >> directory;
		//Pushes right(id) object into inventory vector
		m_items.push_back(new InventoryItem(id, name, directory));
	}
	levelfile.close();
}

void Inventory::Read(){
	for(int i = 0; i < m_items.size(); i++){
		std::cout << m_items[i]->GetId() << ' ';
		std::cout << m_items[i]->GetName() << ' ';
		std::cout << m_items[i]->GetDirectory() << std::endl;
	}
}

void Inventory::Render(sf::Vector2f position){
	for(int i = 0; i < m_items.size(); i++){
		m_items[i]->SetPosition(position.x+45*i+20, position.y);
	}
}

void Inventory::Draw(sf::RenderWindow &window){
	window.draw(mouseSprite);
	for(InventoryVector::iterator i = m_items.begin(); i != m_items.end(); i++){
		(*i)->Draw(window);
	}
}

void Inventory::IsOverlap(sf::IntRect rect, sf::RenderWindow &window){
	sf::Vector2f mousePosition = window.convertCoords(sf::Mouse::getPosition(window));
	mouseSprite.setPosition(mousePosition.x-rect.width, mousePosition.y-rect.height);

	for(int i = 0; i < m_items.size(); i++){
		if(rect.intersects(m_items[i]->GetRect()) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
			mouseTexture.loadFromFile(m_items[i]->GetDirectory());
			mouseSprite.setTexture(mouseTexture);
			std::cout << m_items[i]->GetDirectory();
		}
	}
	Draw(window);
}
