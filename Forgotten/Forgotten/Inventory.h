#ifndef INCLUDED_INVENTORY
#define INCLUDED_INVENTORY

#include "InventoryItem.h"

class Inventory{
public:
	Inventory(std::string filename);
	~Inventory();
	void AddItem(std::string filename);
	void SetName(std::string name);
	void Read();
	void LoadItems(std::string filename);
	std::string GetDirectory(int id);
private:
	sf::Vector2f m_position;
	std::string m_name;
	std::ifstream levelfile;
	typedef std::vector<InventoryItem*> InventoryVector;
	InventoryVector m_items;
};

#endif