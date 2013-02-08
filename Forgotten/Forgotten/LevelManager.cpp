#include "LevelManager.h"

void LevelManager::LoadChapter(){

	// Create rooms for this level
	m_levels.push_back(new Level(0, "Data/Levels/Level1/kapitel_1_test_hall_node.png", 52, 975, "Data/Levels/Level1/TEST_hall_fardig.png"));
	m_levels.push_back(new Level(1, "Data/Levels/Level1/kapitel_1_test_reception_node.png", 20, 20, "Data/Levels/Level1/kapitel_1_test_exterior.png"));
	m_levels.push_back(new Level(2, "Data/Levels/Level1/kapitel_1_test_reception_node.png", 50, 10, "Data/Levels/Level1/kapitel_1_test_reception.png"));

	// Set player position
	m_levels[0]->GetPlayer()->SetNodePosition(7, 0);
	m_levels[1]->GetPlayer()->SetNodePosition(30, 21);
	m_levels[2]->GetPlayer()->SetNodePosition(10, 50);

	// Add background animations
	m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_animation_lampa.png", 100, 16, 1150, 70, 0));
	m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_hiss.png", 1000, 1, 2191, 190, 32));
	m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_skuggning.png", 1000, 1, 0, 0, 33));

	// Set first room
	m_currentLevel = m_levels[0];
	m_currentLevel->GetPlayer()->SetDirection(Entity::Direction::DOWN);
}

Level* LevelManager::GetCurrentLevel(){ return m_currentLevel; }

void LevelManager::SetLevel(int id){ m_currentLevel = m_levels[id]; }