#include "Level.h"

Level::Level(int id, std::string nodeData, int nodeWidth, int nodeHeight, std::string bgTexture)
	:m_id(id), m_nodeMap(nodeData, nodeWidth, nodeHeight)
{
	// Set background
	m_bgTexture.loadFromFile(bgTexture);
	m_bgSprite.setTexture(m_bgTexture);

	// Create player for this room
	m_player = new Player(m_nodeMap);

	// Push the player into the entity vector
	m_entities.push_back(m_player);
}

GenericMap& Level::GetNodeMap(){ return m_nodeMap; }

const sf::Sprite& Level::GetBackgroundImage() const { return m_bgSprite; }

void Level::AddObject(Entity* entity){ m_entities.push_back(entity); }

std::vector<Entity*> Level::GetEntities(){ return m_entities; }

Player* Level::GetPlayer(){ return m_player; }