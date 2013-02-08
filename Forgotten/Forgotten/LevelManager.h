#ifndef INCLUDED_LEVELMANAGER
#define INCLUDED_LEVELMANAGER

#include "Level.h"
#include <vector>
#include "BackgroundObject.h"

class LevelManager{
public:
	void LoadChapter(/* CHAPTER1.dat */);
	Level* GetCurrentLevel();
	void SetLevel(int id);
private:
	std::vector<Level*> m_levels;
	Level *m_currentLevel;
};

#endif