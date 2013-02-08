#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL

#include "GenericMap.h"
#include "Player.h"

class Level{
public:
	Level(int id, std::string nodeData, int nodeWidth, int nodeHeight, std::string bgTexture);
	GenericMap& GetNodeMap();
	const sf::Sprite& GetBackgroundImage() const;
	void AddObject(Entity* entity);
	std::vector<Entity*> GetEntities();
	Player* GetPlayer();
private:
	Player *m_player;
	std::vector<Entity*> m_entities;
	int m_id;
	sf::Texture m_bgTexture;
	sf::Sprite m_bgSprite;
	GenericMap m_nodeMap;
};

#endif