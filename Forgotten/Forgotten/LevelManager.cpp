#include "LevelManager.h"
#include "Portal.h"

void LevelManager::LoadChapter(){

	// Create rooms for this level
	m_levels.push_back(new Level(0, "Data/Levels/Level1/kapitel_1_test_hall_node.png", 52, 975, "Data/Levels/Level1/TEST_hall_fardig.png"));
	m_levels.push_back(new Level(1, "Data/Levels/Level1/kapitel_1_test_reception_node.png", 20, 20, "Data/Levels/Level1/kapitel_1_test_exterior.png"));
	m_levels.push_back(new Level(2, "Data/Levels/Level1/kapitel_1_test_reception_node.png", 50, 10, "Data/Levels/Level1/test_reception_inget_ljus.png"));

	// Set player position
	m_levels[0]->GetPlayer()->SetNodePosition(7, 0);
	m_levels[1]->GetPlayer()->SetNodePosition(30, 21);
	m_levels[2]->GetPlayer()->SetNodePosition(10, 50);

	// Add sounds
	m_levels[0]->AddSound(new SFX("Data/Sounds/Hiss dörr öppna.wav"));
	m_levels[2]->AddSound(new SFX("Data/Sounds/Hiss dörr öppna.wav"));

	// Add background animations
	m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_animation_lampa.png", 100, 16, 1150, 70, 0, "Data/Sounds/Trasig lampa.wav"));
	m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_hiss.png", 1000, 1, 2191, 190, 32));
	m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_skuggning.png", 1000, 1, 0, 0, 33));
	m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_animation_fonster.png", 100, 22, 60, 136, 34));

	m_levels[2]->AddObject(new BackgroundObject("Data/Levels/Level1/test_ljus_overlay.png", 100, 1, 430, 70, 35));

	// Create portals
	Portal *hall2reception = new Portal(0, sf::IntRect(2236, 260, 50, 230), sf::Vector2f(43, 0), Entity::Direction::LEFT);
	Portal *reception2hall = new Portal(2, sf::IntRect(0, 425, 150, 150), sf::Vector2f(1, 54), Entity::Direction::RIGHT);

	// Create portal links
	hall2reception->SetTargetPortal(reception2hall);
	reception2hall->SetTargetPortal(hall2reception);

	// Add the portals to the portal vector
	m_levels[0]->AddPortal(hall2reception);
	m_levels[2]->AddPortal(reception2hall);
	// NVM, add them to the entity vector
	m_levels[0]->AddObject(hall2reception);
	m_levels[2]->AddObject(reception2hall);

	// Set first room
	m_currentLevel = m_levels[0];
	m_currentLevel->GetPlayer()->SetDirection(Entity::Direction::DOWN);
}

Level* LevelManager::GetCurrentLevel(){ return m_currentLevel; }

void LevelManager::SetLevel(int id){ m_currentLevel = m_levels[id]; }

void LevelManager::StopAllSounds(){

	for(std::vector<Level*>::iterator i = m_levels.begin(); i != m_levels.end(); i++){
		(*i)->StopAllSounds();
	}

}