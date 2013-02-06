#include "LevelManager.h"

void LevelManager::LoadChapter(){

	// Create rooms for this level
	m_levels.push_back(new Level(0, "Data/Levels/Level1/hotelRoom_node.png", 100, 20, "Data/Levels/Level1/kapitel_1_test_hall.png"));
	m_levels.push_back(new Level(1, "Data/Levels/Level1/hotelRoom_node.png", 100, 20, "Data/Levels/Level1/kapitel_1_test_exterior.png"));
	m_levels.push_back(new Level(2, "Data/Levels/Level1/hotelRoom_node.png", 100, 20, "Data/Levels/Level1/kapitel_1_test_reception.png"));

	// Create list of objects


	// Set first room
	m_currentLevel = m_levels[0];
}

Level* LevelManager::GetCurrentLevel(){ return m_currentLevel; }