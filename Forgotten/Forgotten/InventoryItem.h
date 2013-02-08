#ifndef INCLUDED_INVENTORYITEM
#define INCLUDED_INVENTORYITEM

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class InventoryItem{
public:
	InventoryItem(int nr, std::string name, std::string directory);
	~InventoryItem();
	int GetId();
	std::string GetDirectory();
	std::string GetName();
	sf::Vector2f GetPosition();
	float GetXPosition();
	float GetYPosition();
	void SetDirectory(std::string directory);
	void SetName(std::string name);
	void SetPosition(float x, float y);
	void SetId(int id);
	void SetTexture(std::string directory);
	void Draw(sf::RenderWindow &window);
	sf::IntRect GetRect();
private:
	int m_id;
	std::string m_name;
	std::string m_directory;
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::IntRect m_textureRect;
};

#endif