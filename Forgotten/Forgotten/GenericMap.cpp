#include "GenericMap.h"

GenericMap::GenericMap(std::string mapdata, int nodeWidth, int nodeHeight)
	:m_nodeWidth(nodeWidth), m_nodeHeight(nodeHeight)
{
	m_mapImage.loadFromFile(mapdata);
	m_xSize = m_mapImage.getSize().x;
	m_ySize = m_mapImage.getSize().y;
}

sf::Vector2f GenericMap::GetMapSize(){

	sf::Vector2f mapSize;

	mapSize.x = m_xSize;
	mapSize.y = m_ySize;

	return mapSize;

}

sf::Vector2f GenericMap::GetNodeSize(){

	sf::Vector2f nodeSize;

	nodeSize.x = m_nodeWidth;
	nodeSize.y = m_nodeHeight;

	return nodeSize;

}

bool GenericMap::isWalkable(int x, int y){

	if(x >= 0 && y >= 0 && x <= m_mapImage.getSize().x && y <= m_mapImage.getSize().y){
		if(m_mapImage.getPixel(x, y) != sf::Color::Black){
			return true;
		}
	}

	return false;

}