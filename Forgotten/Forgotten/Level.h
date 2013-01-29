#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL

#include "GenericMap.h"
#include "Player.h"

class Level{
public:
	Level(std::string nodeData, int nodeWidth, int nodeHeight, std::string bgTexture);
	GenericMap& GetNodeMap();
	Player& GetPlayer();
	sf::Sprite GetBackgroundImage();
private:
	sf::Texture m_bgTexture;
	sf::Sprite m_bgSprite;
	GenericMap m_nodeMap;
	Player m_player;
};

#endif