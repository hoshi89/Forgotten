#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL

#include "GenericMap.h"
#include "Player.h"
#include "Portal.h"
#include "SFX.h"

class Level{
public:
	Level(int id, std::string nodeData, int nodeWidth, int nodeHeight, std::string bgTexture);
	GenericMap& GetNodeMap();
	const sf::Sprite& GetBackgroundImage() const;
	void AddObject(Entity* entity);
	void AddPortal(Portal* portal);
	void AddSound(SFX* sfx);
	std::vector<Entity*>& GetEntities();
	std::vector<Portal*>& GetPortals();
	Player* GetPlayer();
	void StopAllSounds();
	void PlaySound(int id);
private:
	Player *m_player;
	std::vector<Entity*> m_entities;
	std::vector<Portal*> m_portals;
	std::vector<SFX*> m_soundEffects;
	int m_id;
	sf::Texture m_bgTexture;
	sf::Sprite m_bgSprite;
	GenericMap m_nodeMap;
};

#endif