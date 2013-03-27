#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL

#include "GenericMap.h"
#include "Player.h"
#include "Portal.h"
#include "SFX.h"

#include "LevelDialogsCls.h"

class Level{
public:
	Level(int id, std::string nodeData, int nodeWidth, int nodeHeight, std::string bgTexture, float entityScale, int scaleOffset);
	GenericMap& GetNodeMap();
	const sf::Sprite& GetBackgroundImage() const;
	void AddObject(const std::string& id, Entity* entity);
	std::vector<Entity*>& GetEntities();
	Player* GetPlayer();
	void StopAllSounds();
	void PlaySound(int id);
	Entity* GetEntity(const std::string& id);

	//Dialog
	LevelDialogsCls* GetLevelDialogs();
	void LoadLevelDialogs(string aScriptName);
private:
	std::map<std::string, Entity*> m_entitiesMap;
	std::vector<Entity*> m_entitiesVector;
	Player *m_player;
	std::vector<SFX*> m_soundEffects;
	int m_id;
	int m_scaleOffset;
	sf::Texture m_bgTexture;
	sf::Sprite m_bgSprite;
	GenericMap m_nodeMap;
	
	//DialogStuff
	LevelDialogsCls* m_Dialogs;
};

#endif