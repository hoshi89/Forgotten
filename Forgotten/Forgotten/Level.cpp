#include "Level.h"

Level::Level(int id, std::string nodeData, int nodeWidth, int nodeHeight, std::string bgTexture, float entityScale, int scaleOffset)
	:m_id(id), m_nodeMap(nodeData, nodeWidth, nodeHeight, entityScale, scaleOffset)
{
	// Set background
	m_bgTexture.loadFromFile(bgTexture);
	m_bgSprite.setTexture(m_bgTexture);

	// Create player for this room
	m_player = new Player(m_nodeMap);

	// Push the player into the entity vector and map
	m_entitiesVector.push_back(m_player);
	m_entitiesMap["player"] = m_player;
}

GenericMap& Level::GetNodeMap()
{
	return m_nodeMap;
}

const sf::Sprite& Level::GetBackgroundImage() const
{
	return m_bgSprite;
}

void Level::AddObject(const std::string& id, Entity *entity)
{
	m_entitiesMap[id] = entity;
	m_entitiesVector.push_back(entity);
}

std::vector<Entity*>& Level::GetEntities()
{
	return m_entitiesVector;
}

Player* Level::GetPlayer()
{
	return m_player;
}

void Level::StopAllSounds()
{
	for(std::vector<Entity*>::iterator i = m_entitiesVector.begin(); i != m_entitiesVector.end(); i++)
	{
		(*i)->StopSound();
	}
}

//DialogStuff
void Level::LoadLevelDialogs(string aScriptName)
{
	m_Dialogs = new LevelDialogsCls(aScriptName, false);
}

LevelDialogsCls* Level::GetLevelDialogs()
{
	return m_Dialogs;
}

Entity* Level::GetEntity(const std::string& id)
{
	return m_entitiesMap.find(id)->second;
}