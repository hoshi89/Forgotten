#ifndef INCLUDED_INVENTORY
#define INCLUDED_INVENTORY

#include "InventoryItem.h"

class Inventory{
public:
	Inventory(std::string filename);
	~Inventory();
	void AddItem(int aId);
	void SetName(std::string name);
	void Read();
	void LoadItems();
	std::string GetDirectory(int id);
	void Render();
	void Draw(sf::RenderWindow &window);
private:
	sf::Vector2f m_position;
	std::string m_name;
	std::ifstream levelfile;
	typedef std::vector<InventoryItem*> InventoryVector;
	InventoryVector m_items;
	std::string m_filename;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif