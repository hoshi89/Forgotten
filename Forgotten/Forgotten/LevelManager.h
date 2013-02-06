#ifndef INCLUDED_LEVELMANAGER
#define INCLUDED_LEVELMANAGER

#include "Level.h"
#include <vector>

class LevelManager{
public:
	void LoadChapter(/* CHAPTER1.dat */);
	Level* GetCurrentLevel();
private:
	std::vector<Level*> m_levels;
	Level *m_currentLevel;
};

#endif