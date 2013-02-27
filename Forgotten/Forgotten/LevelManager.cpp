#include "LevelManager.h"
#include "Portal.h"
#include "GameManager.h"

LevelManager::LevelManager()
	:m_initialScriptRun(false)
{

}

void LevelManager::LoadChapter(int id){

	switch(id){
	case 0:

		// Set initalizing script
		m_initializingScript = "Data/Scripts/0004.txt";

		// Create rooms for this level
		m_levels.push_back(new Level(0, "Data/Levels/Level1/kapitel_1_test_hall_node.png", 52, 975, "Data/Levels/Level1/TEST_hall_fardig.png"));
		m_levels.push_back(new Level(1, "Data/Levels/Level1/kapitel_1_test_reception_node.png", 20, 20, "Data/Levels/Level1/kapitel_1_test_exterior.png"));
		m_levels.push_back(new Level(2, "Data/Levels/Level1/kapitel_1_test_reception_node.png", 50, 10, "Data/Levels/Level1/test_reception_inget_ljus.png"));
		m_levels.push_back(new Level(3, "Data/Levels/Level1/chapter_1_hotel_room_node.png", 50, 10, "Data/Levels/Level1/chapter_1_level_art_hotel_room.png"));

		// Set player position
		m_levels[0]->GetPlayer()->SetNodePosition(7, 0);
		m_levels[1]->GetPlayer()->SetNodePosition(30, 21);
		m_levels[2]->GetPlayer()->SetNodePosition(10, 50);
		m_levels[3]->GetPlayer()->SetNodePosition(4, 49);

		// Add sounds
		m_levels[0]->AddSound(new SFX("Data/Sounds/Hiss dörr öppna.wav"));
		m_levels[2]->AddSound(new SFX("Data/Sounds/Hiss dörr öppna.wav"));

		// Add background animations
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_animation_lampa.png", 100, 16, 1150, 70, 0, "Data/Sounds/Trasig lampa.wav"));
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_hiss.png", 1000, 1, 2191, 190, 32));
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_skuggning.png", 1000, 1, 0, 0, 33));
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_animation_fonster.png", 100, 22, 60, 136, 34));
		m_levels[2]->AddObject(new BackgroundObject("Data/Levels/Level1/test_ljus_overlay.png", 100, 1, 430, 70, 35));
		m_levels[3]->AddObject(new BackgroundObject("Data/Levels/Level1/chapter_1_bed.png", 100, 1, 370, 384, 470));
		m_levels[3]->AddObject(new BackgroundObject("Data/Levels/Level1/chapter_1_books.png", 100, 1, 765, 480, 870));

		// Create portals
		Portal *hall2reception = new Portal(0, sf::IntRect(2236, 260, 50, 230), sf::Vector2f(43, 0), Entity::Direction::LEFT);
		Portal *reception2hall = new Portal(2, sf::IntRect(0, 425, 150, 150), sf::Vector2f(1, 50), Entity::Direction::RIGHT);
		Portal *hotelroom2hall = new Portal(3, sf::IntRect(1050, 180, 150, 270), sf::Vector2f(21, 49), Entity::Direction::LEFT);

		// Set scripts for portals
		hall2reception->SetScript("Data/Scripts/0001.txt");
		reception2hall->SetScript("Data/Scripts/0002.txt");
		hotelroom2hall->SetScript("Data/Scripts/0003.txt");

		// Add them to the entity vector
		m_levels[0]->AddObject(hall2reception);
		m_levels[2]->AddObject(reception2hall);
		m_levels[3]->AddObject(hotelroom2hall);

		// Set first room
		m_currentLevel = m_levels[3];
		m_currentLevel->GetPlayer()->SetDirection(Entity::Direction::DOWN);

		//Add Dialogs
		m_levels[0]->LoadLevelDialogs("blabla");
		m_levels[1]->LoadLevelDialogs("blabla");
		m_levels[2]->LoadLevelDialogs("blabla");
		m_levels[3]->LoadLevelDialogs("blabla");
		break;
	}
}

Level* LevelManager::GetCurrentLevel(){ return m_currentLevel; }

void LevelManager::SetLevel(int id){

	m_currentLevel = m_levels[id];

	// Stop sounds
	StopAllSounds();
}

void LevelManager::StopAllSounds(){

	for(std::vector<Level*>::iterator i = m_levels.begin(); i != m_levels.end(); i++){
		(*i)->StopAllSounds();
	}

}

bool LevelManager::InitialScriptRun(){ return m_initialScriptRun; }

std::string LevelManager::GetInitialScript(){

	m_initialScriptRun = true;

	return m_initializingScript;

}