#include "LevelManager.h"
#include "Portal.h"
#include "GameManager.h"
#include "Object.h"

LevelManager::LevelManager()
	:m_initialScriptRun(false)
{
}

void LevelManager::LoadChapter(int id){

	switch(id){
	case 0:

		// Set initalizing script
		m_initializingScript = "Data/Scripts/initial_chapter_1.script";

		m_bgMusic.openFromFile("Data/Music/Hotel.ogg");
		//m_bgMusic.play();
		m_bgMusic.setLoop(true);

		// Create rooms for this level
		m_levels.push_back(new Level(0, "Data/Levels/Level1/kapitel_1_test_hall_node.png", 52, 975, "Data/Levels/Level1/TEST_hall_fardig.png", 0.0008));
		m_levels.push_back(new Level(1, "Data/Levels/Level1/chapter_1_exterior_node.png", 50, 20, "Data/Levels/Level1/chapter_1_level_art_hotel_exterior.png", 0.12));
		m_levels.push_back(new Level(2, "Data/Levels/Level1/kapitel_1_test_reception_node.png", 50, 10, "Data/Levels/Level1/test_reception_inget_ljus.png", 0.12));
		m_levels.push_back(new Level(3, "Data/Levels/Level1/chapter_1_hotel_room_node.png", 50, 10, "Data/Levels/Level1/chapter_1_level_art_hotel_room.png", 0.12));
		m_levels.push_back(new Level(4, "Data/Levels/Level1/chapter_1_bar_node.png", 50, 25, "Data/Levels/Level1/Chapter_1_level_art_hotel_bar.png", 0.12));

		// Set player position
		m_levels[0]->GetPlayer()->SetNodePosition(7, 0);
		m_levels[1]->GetPlayer()->SetNodePosition(13, 21);
		m_levels[2]->GetPlayer()->SetNodePosition(10, 50);
		m_levels[3]->GetPlayer()->SetNodePosition(4, 49);
		m_levels[4]->GetPlayer()->SetNodePosition(18, 15);

		// Add sounds
		m_levels[0]->AddSound(new SFX("Data/Sounds/Hiss dörr öppna.wav"));
		m_levels[2]->AddSound(new SFX("Data/Sounds/Hiss dörr öppna.wav"));

		// Add background animations
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_animation_lampa.png", 100, 16, 1150, 70, 0, "Data/Sounds/Trasig lampa.wav", 3));
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_hiss.png", 1000, 1, 2191, 190, 32));
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_skuggning.png", 1000, 1, 0, 0, 33));
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_animation_fonster.png", 100, 22, 60, 136, 34));
		m_levels[2]->AddObject(new BackgroundObject("Data/Levels/Level1/test_ljus_overlay.png", 100, 1, 430, 70, 1000));
		m_levels[3]->AddObject(new BackgroundObject("Data/Levels/Level1/chapter_1_bed.png", 100, 1, 370, 384, 470));
		m_levels[3]->AddObject(new BackgroundObject("Data/Levels/Level1/chapter_1_books.png", 100, 1, 765, 480, 870));

		///////////////////// PORTALS BEGIN ///////////////////////////

		// Create portals
		Portal *hotelroom2hall = new Portal("hotelroom_to_hall", sf::IntRect(1050, 180, 150, 270), sf::Vector2f(21, 49));
		Portal *hall2reception = new Portal("hall_to_reception", sf::IntRect(2236, 260, 50, 230), sf::Vector2f(43, 0));
		Portal *hall2hotelroom = new Portal("hall_to_hotelroom", sf::IntRect(310, 260, 135, 215), sf::Vector2f(7, 0));
		Portal *reception2hall = new Portal("reception_to_hall", sf::IntRect(0, 425, 150, 150), sf::Vector2f(1, 50));
		Portal *reception2bar = new Portal("reception_to_bar", sf::IntRect(920, 140, 120, 250), sf::Vector2f(19, 38));
		Portal *reception2streets = new Portal("reception_to_streets", sf::IntRect(1265, 150, 215, 260), sf::Vector2f(27, 41));
		Portal *bar2reception = new Portal("bar_to_reception", sf::IntRect(870, 210, 110, 180), sf::Vector2f(18, 15));
		Portal *streets2reception = new Portal("streets_to_reception", sf::IntRect(615, 280, 130, 135), sf::Vector2f(13, 20));

		// Set scripts for portals
		hall2reception->SetScript("Data/Scripts/portal_hall_to_reception.script");
		hall2hotelroom->SetScript("Data/Scripts/portal_hall_to_hotelroom.script");
		reception2hall->SetScript("Data/Scripts/portal_reception_to_hall.script");
		reception2bar->SetScript("Data/Scripts/portal_reception_to_bar.script");
		hotelroom2hall->SetScript("Data/Scripts/portal_hotelroom_to_hall.script");
		bar2reception->SetScript("Data/Scripts/portal_bar_to_reception.script");
		reception2streets->SetScript("Data/Scripts/portal_reception_to_streets.script");
		streets2reception->SetScript("Data/Scripts/portal_streets_to_reception.script");

		// Add them to the entity vector
		m_levels[0]->AddObject(hall2reception);
		m_levels[0]->AddObject(hall2hotelroom);
		m_levels[1]->AddObject(streets2reception);
		m_levels[2]->AddObject(reception2hall);
		m_levels[2]->AddObject(reception2bar);
		m_levels[2]->AddObject(reception2streets);
		m_levels[3]->AddObject(hotelroom2hall);
		m_levels[4]->AddObject(bar2reception);

		///////////////////// PORTALS END ///////////////////////////

		// Add objects
		Object *matches = new Object("matches", 200, 450, 4, 50, "Data/Animations/Objects/matches2.png", 1000, 1);

		// Set object scripts
		matches->SetInteractScript("Data/Scripts/ch1_matches_1.script");

		// Add objects to the entity vector
		m_levels[3]->AddObject(matches);

		// Set first room
		m_currentLevel = m_levels[3];
		m_currentLevel->GetPlayer()->SetDirection(Entity::Direction::DOWN);

		//Add NPCS
		m_levels[2]->AddObject(new NpcCls(800, 210, "Data/Animations/NPC/TEST_kapitel_1_lady.png",
		sf::Vector2f(15, 43), Entity::Direction::RIGHT, m_levels[0]->GetNodeMap(), "Data/Scripts/AngryWomanScriptStandard.txt"));   
		//Add Dialogs
		m_levels[0]->LoadLevelDialogs("Data/Scripts/LevelNullDlg.txt");
		m_levels[0]->LoadLevelDialogs("Data/Scripts/LevelTwoDlg.txt");
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