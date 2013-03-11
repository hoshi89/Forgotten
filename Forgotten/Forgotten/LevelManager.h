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
	void LoadChapter(int id);
	Level* GetCurrentLevel();
	void SetLevel(int id);
	void StopAllSounds();
	void SetBackgroundMusicVolume(float volume);
	bool InitialScriptRun();
	std::string GetInitialScript();
private:
	std::vector<Level*> m_levels;
	Level *m_currentLevel;
	std::string m_initializingScript;
	bool m_initialScriptRun;
	sf::Music m_bgMusic;
};

#endif