#ifndef INCLUDED_GENERICMAP
#define INCLUDED_GENERICMAP

#include <string>
#include <SFML/Graphics.hpp>

class GenericMap{
public:
	GenericMap(std::string mapdata, int nodeWidth, int nodeHeight);
	sf::Vector2f GetMapSize();
	sf::Vector2f GetNodeSize();
	bool isWalkable(int x, int y);
private:
	sf::Image m_mapImage;
	int m_xSize, m_ySize;
	int m_nodeWidth, m_nodeHeight;
};

#endif