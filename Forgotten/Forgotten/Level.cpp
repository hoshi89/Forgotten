#include "Level.h"

Level::Level(std::string nodeData, int nodeWidth, int nodeHeight, std::string bgTexture)
	:m_nodeMap(nodeData, nodeWidth, nodeHeight), m_player(m_nodeMap)
{
	m_bgTexture.loadFromFile(bgTexture);
	m_bgSprite.setTexture(m_bgTexture);
}

GenericMap& Level::GetNodeMap(){ return m_nodeMap; }

Player& Level::GetPlayer(){ return m_player; }

sf::Sprite Level::GetBackgroundImage(){ return m_bgSprite; }