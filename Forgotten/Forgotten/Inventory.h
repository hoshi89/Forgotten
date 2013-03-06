#ifndef INCLUDED_INVENTORY
#define INCLUDED_INVENTORY

#include "InventoryItem.h"

class Inventory{
public:
	~Inventory();
	static Inventory* GetInstance();
	void AddItem(int aId);
	void SetName(std::string name);
	void Read(int i);
	void LoadItems();
	int GetId(int i);
	sf::Vector2f GetPosition(int id);
	std::string GetDirectory(int id);
	void Render(sf::Vector2f position);
	void Draw(sf::RenderWindow &window);
	int IsOverlap(sf::RenderWindow& window, sf::View& view);
	sf::IntRect GetItemsRect(int i);
	std::vector<InventoryItem*> Contains();
	void RemoveItem();
	void KillItem(int id);
private:
	Inventory();
	Inventory(Inventory const&){};
	Inventory& operator=(Inventory const&){};
	static Inventory *m_instance;
	sf::Vector2f m_position;
	std::string m_name;
	std::ifstream levelfile;
	typedef std::vector<InventoryItem*> InventoryVector;
	InventoryVector m_items;
	std::string m_filename;
	sf::Sprite mouseSprite;
	sf::Texture mouseTexture;

};

#endif