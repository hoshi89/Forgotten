#ifndef INCLUDED_INVENTORYITEM
#define INCLUDED_INVENTORYITEM

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class InventoryItem{
public:
	InventoryItem(int nr, std::string name, sf::Vector2f position, std::string directory);
	int GetId();
	std::string GetDirectory();
	std::string GetName();
	sf::Vector2f GetPosition();
	float GetXPosition();
	float GetYPosition();
private:
	int m_id;
	std::string m_name;
	std::string m_directory;
	sf::Vector2f m_position;
};

#endif