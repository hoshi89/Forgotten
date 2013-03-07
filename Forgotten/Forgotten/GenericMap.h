#ifndef INCLUDED_GENERICMAP
#define INCLUDED_GENERICMAP

#include <string>
#include <SFML/Graphics.hpp>

class GenericMap{
public:
	GenericMap(std::string mapdata, int nodeWidth, int nodeHeight, float entityScale, int scaleOffset);
	sf::Vector2f GetMapSize();
	sf::Vector2f GetNodeSize();
	bool isWalkable(int x, int y);
	const float GetEntityScale();
	const int GetScaleOffset();
private:
	sf::Image m_mapImage;
	int m_xSize, m_ySize;
	int m_nodeWidth, m_nodeHeight;
	float m_entityScale;
	int m_scaleOffset;
};

#endif