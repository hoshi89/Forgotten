#ifndef INCLUDED_LEVELMANAGER
#define INCLUDED_LEVELMANAGER

#include "Level.h"
#include <vector>
#include "BackgroundObject.h"
#include "NpcCls.h"
#include "LevelDialogsCls.h"

class LevelManager{
public:
	LevelManager();
	void update();
	void LoadChapter(int id);
	Level* GetCurrentLevel();
	void SetLevel(int id);
	void StopAllSounds();
	bool InitialScriptRun();
	std::string GetInitialScript();
	void AddSound(SFX* sfx);
	void PlaySound(std::string& id);
	void SetBackgroundMusicVolume(float volume);
private:
	std::vector<Level*> m_levels;
	std::vector<SFX*> m_sounds;
	Level *m_currentLevel;
	std::string m_initializingScript;
	bool m_initialScriptRun;
	sf::Music m_bgMusic;
	float m_bgVolume;
	float m_fadeSpeed;
};

#endif