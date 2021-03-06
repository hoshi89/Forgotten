#ifndef INCLUDED_INVENTORYITEM
#define INCLUDED_INVENTORYITEM

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class InventoryItem{
public:
	InventoryItem(int nr, std::string name, std::string directory, std::string scriptName, int requires, std::string wantScript);
	~InventoryItem();
	int GetId();
	std::string GetDirectory();
	std::string GetName();
	sf::Vector2f GetPosition();
	void SetPosition(float x, float y);
	void SetTexture(std::string directory);
	void Draw(sf::RenderWindow &window);
	sf::IntRect GetRect();
	sf::Texture GetTexture();
	bool IsAlive();
	void SetDead();
	std::string GetScript();
	int GetRequires();
	std::string GetWantScript();
private:
	int m_id;
	std::string m_name;
	std::string m_directory;
	std::string m_wantScript;
	sf::Vector2f m_position;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::IntRect m_textureRect;
	bool m_isAlive;
	std::string m_scriptName;
	int m_requires;
};

#endif