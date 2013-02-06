#ifndef INCLUDED_LEVELMANAGER
#define INCLUDED_LEVELMANAGER

#include "Level.h"
#include <vector>

class LevelManager{
public:
	void LoadLevel(/* LEVEL1.dat */);
private:
	std::vector<Level*> m_levelRooms;
};

#endif