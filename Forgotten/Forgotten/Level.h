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
	void AddObject(Entity* entity);
	void AddSound(SFX* sfx);
	std::vector<Entity*>& GetEntities();
	std::vector<Portal*>& GetPortals();
	Player* GetPlayer();
	void StopAllSounds();
	void PlaySound(std::string& id);

	//Dialog
	LevelDialogsCls* GetLevelDialogs();
	void LoadLevelDialogs(string aScriptName);
private:
	Player *m_player;
	std::vector<Entity*> m_entities;
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