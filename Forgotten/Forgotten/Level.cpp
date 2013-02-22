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

void Level::AddSound(SFX* sfx){ m_soundEffects.push_back(sfx); }

std::vector<Entity*>& Level::GetEntities(){ return m_entities; }

Player* Level::GetPlayer(){ return m_player; }

void Level::StopAllSounds(){

	for(std::vector<Entity*>::iterator i = m_entities.begin(); i != m_entities.end(); i++){
		(*i)->StopSound();
	}

}

void Level::PlaySound(int id){

	if(!m_soundEffects.empty() && m_soundEffects.size() >= id){

		m_soundEffects[id]->Play();

	}

}

//DialogStuff
void Level::LoadLevelDialogs(string aScriptName)
{
	m_Dialogs = new LevelDialogsCls(aScriptName);
}

LevelDialogsCls* Level::GetLevelDialogs()
{
	return m_Dialogs;
}

