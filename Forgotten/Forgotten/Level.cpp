#include "Level.h"

Level::Level(int id, std::string nodeData, int nodeWidth, int nodeHeight, std::string bgTexture)
	:m_id(id), m_nodeMap(nodeData, nodeWidth, nodeHeight)
{
	m_bgTexture.loadFromFile(bgTexture);
	m_bgSprite.setTexture(m_bgTexture);
}

GenericMap& Level::GetNodeMap(){ return m_nodeMap; }

const sf::Sprite& Level::GetBackgroundImage() const { return m_bgSprite; }