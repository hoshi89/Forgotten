#include "LevelManager.h"
#include "Portal.h"
#include "GameManager.h"
#include "Object.h"

LevelManager::LevelManager()
	:m_initialScriptRun(false), m_bgVolume(100.f), m_fadeSpeed(3.f)
{
}

void LevelManager::update()
{
	if(m_bgMusic.getVolume() < m_bgVolume)
	{
		float nextVolume = m_bgMusic.getVolume()+m_fadeSpeed;
		if(nextVolume > m_bgVolume)
		{
			m_bgMusic.setVolume(m_bgVolume);
		}
		else
		{
			m_bgMusic.setVolume(nextVolume);
		}
	}
	else if(m_bgMusic.getVolume() > m_bgVolume)
	{
		float nextVolume = m_bgMusic.getVolume()-m_fadeSpeed;
		if(nextVolume < m_bgVolume)
		{
			m_bgMusic.setVolume(m_bgVolume);
		}
		else
		{
			m_bgMusic.setVolume(nextVolume);
		}
	}
}

void LevelManager::LoadChapter(int id){

	switch(id){
	case 0:

		// Set initalizing script
		m_initializingScript = "Data/Scripts/initial_chapter_1.script";

		m_bgMusic.openFromFile("Data/Music/Hotel.ogg");
		m_bgMusic.play();
		m_bgMusic.setLoop(true);

		// Create rooms for this level
		m_levels.push_back(new Level(0, "Data/Levels/Level1/kapitel_1_test_hall_node.png", 52, 975, "Data/Levels/Level1/TEST_hall_fardig.png", 0.8, 0));
		m_levels.push_back(new Level(1, "Data/Levels/Level1/chapter_1_exterior_node.png", 50, 20, "Data/Levels/Level1/chapter_1_level_art_hotel_exterior.png", 0.7, 0));
		m_levels.push_back(new Level(2, "Data/Levels/Level1/kapitel_1_test_reception_node.png", 50, 10, "Data/Levels/Level1/test_reception_inget_ljus.png", 1.2, 0));
		m_levels.push_back(new Level(3, "Data/Levels/Level1/chapter_1_hotel_room_node.png", 50, 10, "Data/Levels/Level1/chapter_1_level_art_hotel_room.png", 1.2, 0));
		m_levels.push_back(new Level(4, "Data/Levels/Level1/chapter_1_bar_node.png", 50, 20, "Data/Levels/Level1/chapter1_bar.png", 2.5, 12));

		// Set player position
		m_levels[0]->GetPlayer()->SetNodePosition(7, 0);
		m_levels[1]->GetPlayer()->SetNodePosition(13, 21);
		m_levels[2]->GetPlayer()->SetNodePosition(10, 50);
		m_levels[3]->GetPlayer()->SetNodePosition(7, 47);
		m_levels[4]->GetPlayer()->SetNodePosition(18, 20);

		// Add sounds
		AddSound(new SFX("Data/Sounds/Hiss dörr öppna.wav", "elevator_open"));
		AddSound(new SFX("Data/Sounds/Cello Complete Em.wav", "cello_complete_em"));
		AddSound(new SFX("Data/Sounds/Tändstickask.wav", "matchbox"));

		// Add background animations
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_animation_lampa.png", 100, 16, 1150, 70, 0, "Data/Sounds/Trasig lampa.wav", 3));
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_hiss.png", 1000, 1, 2191, 190, 1000));
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_skuggning.png", 1000, 1, 0, 0, 33));
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/TEST_hall_animation_fonster.png", 100, 22, 60, 136, 34));
		m_levels[2]->AddObject(new BackgroundObject("Data/Levels/Level1/test_ljus_overlay.png", 100, 1, 430, 70, 1000));
		m_levels[2]->AddObject(new BackgroundObject("Data/Levels/Level1/reception_booth.png", 1000, 1, 580, 90, 200));
		m_levels[3]->AddObject(new BackgroundObject("Data/Levels/Level1/chapter_1_bed.png", 1000, 1, 271, 345, 470));
		m_levels[3]->AddObject(new BackgroundObject("Data/Levels/Level1/chapter_1_books.png", 100, 1, 765, 480, 870));
		m_levels[0]->AddObject(new BackgroundObject("Data/Levels/Level1/chapter_1_cart.png", 1000, 1, 1045, 413, 500));

		///////////////////// PORTALS BEGIN ///////////////////////////

		// Create portals
		Portal *hotelroom2hall = new Portal("hotelroom_to_hall", sf::IntRect(1050, 180, 150, 270), sf::Vector2f(21, 45));
		Portal *hall2reception = new Portal("hall_to_reception", sf::IntRect(2236, 260, 50, 230), sf::Vector2f(43, 0));
		Portal *hall2hotelroom = new Portal("hall_to_hotelroom", sf::IntRect(310, 260, 135, 215), sf::Vector2f(7, 0));
		Portal *reception2hall = new Portal("reception_to_hall", sf::IntRect(0, 425, 150, 150), sf::Vector2f(1, 50));
		Portal *reception2bar = new Portal("reception_to_bar", sf::IntRect(920, 140, 120, 250), sf::Vector2f(19, 38));
		Portal *reception2streets = new Portal("reception_to_streets", sf::IntRect(1265, 150, 215, 260), sf::Vector2f(27, 41));
		Portal *bar2reception = new Portal("bar_to_reception", sf::IntRect(870, 210, 110, 180), sf::Vector2f(18, 19));
		Portal *streets2reception = new Portal("streets_to_reception", sf::IntRect(615, 280, 130, 135), sf::Vector2f(13, 21));

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
		Object *matches = new Object("matches", 210, 400, 5, 49, "Data/Levels/Level1/chapter1_matchbox.png", 1000, 1);
		Object *necklace = new Object("necklace", 1100, 650, 21, 0, "Data/Animations/Objects/necklace.png", 1000, 1);

		// Set object scripts
		matches->SetInteractScript("Data/Scripts/ch1_matches_interact.script");
		matches->SetGiveScript("Data/Scripts/ch1_matches_give.script");
		matches->SetInspectScript("Data/Scripts/ch1_matches_inspect.script");
		matches->SetNoCanDoScript("Data/Scripts/ch1_matches_nocando.script");

		necklace->SetInteractScript("Data/Scripts/ch1_necklace_interact.script");
		necklace->SetGiveScript("Data/Scripts/ch1_necklace_give.script");
		necklace->SetInspectScript("Data/Scripts/ch1_necklace_inspect.script");
		necklace->SetNoCanDoScript("Data/Scripts/ch1_necklace_nocando.script");

		// Set sprite offsets
		necklace->SetSpriteOffset(0, 200);

		// Add objects to the entity vector
		m_levels[0]->AddObject(necklace);
		m_levels[3]->AddObject(matches);

		// Set first room
		m_currentLevel = m_levels[3];
		m_currentLevel->GetPlayer()->SetDirection(Entity::Direction::DOWN);

		// Add NPCS
		NpcCls *angry_woman = new NpcCls(800, 210, "Data/Animations/NPC/TEST_kapitel_1_lady.png", 1, 1000, sf::Vector2f(15, 43), m_levels[0]->GetNodeMap(), "Data/Scripts/ch1_angry_woman_interact.script", "Data/Scripts/ch1_angry_woman_inspect.script", "Data/Scripts/ch1_angry_woman_give.script", "Data/Scripts/ch1_angry_woman_nocando.script", sf::IntRect(830, 220, 60, 220 ), "angry_woman");   
		NpcCls *dendi = new NpcCls(100, 200, "Data/Animations/NPC/dendi.png", 1, 1000, sf::Vector2f(7, 26), m_levels[4]->GetNodeMap(), "Data/Scripts/ch1_dendi_interact.script", "Data/Scripts/ch1_dendi_inspect.script", "Data/Scripts/ch1_dendi_give.script", "Data/Scripts/ch1_dendi_nocando.script", sf::IntRect(120, 210, 160, 310), "dendi");
		NpcCls *valet = new NpcCls(1250, 580, "Data/Animations/NPC/chapter_1_valet.png", 1, 1000, sf::Vector2f(20, 0), m_levels[0]->GetNodeMap(), "Data/Scripts/ch1_valet_interact.script", "Data/Scripts/ch1_valet_inspect.script", "Data/Scripts/ch1_valet_give.script", "Data/Scripts/ch1_valet_nocando.script", sf::IntRect(1150, 380, 100, 140), "valet");
		NpcCls *receptionist = new NpcCls(680, 190, "Data/Animations/NPC/receptionist.png", 34, 100, sf::Vector2f(15, 43), m_levels[2]->GetNodeMap(), "Data/Scripts/ch1_receptionist_interact.script", "Data/Scripts/ch1_receptionist_inspect.script", "Data/Scripts/ch1_receptionist_give.script", "Data/Scripts/ch1_receptionist_nocando.script", sf::IntRect(650, 170, 120, 130), "receptionist");
		NpcCls *taxi = new NpcCls(1100, 480, "Data/Animations/NPC/taxi.png", 1, 100, sf::Vector2f(23, 21), m_levels[1]->GetNodeMap(), "Data/Scripts/ch1_taxi_interact.script", "Data/Scripts/ch1_taxi_inspect.script", "Data/Scripts/ch1_taxi_give.script", "Data/Scripts/ch1_taxi_nocando.script", sf::IntRect(1020, 380, 290, 80), "taxi");

		// Set sprite offset
		valet->SetSpriteOffset(100, 200);
		taxi->SetSpriteOffset(100, 200);

		// Set wants item
		dendi->SetWantsItem(1);
		angry_woman->SetWantsItem(4);
		receptionist->SetWantsItem(3);
		taxi->SetWantsItem(2);

		m_levels[2]->AddObject(angry_woman);
		m_levels[4]->AddObject(dendi);
		m_levels[0]->AddObject(valet);
		m_levels[2]->AddObject(receptionist);
		m_levels[1]->AddObject(taxi);

		//Add Dialogs
		m_levels[0]->LoadLevelDialogs("Data/Scripts/LevelNullDlg.txt");
		m_levels[2]->LoadLevelDialogs("Data/Scripts/LevelTwoDlg.txt");
		m_levels[4]->LoadLevelDialogs("Data/Scripts/LevelFourDlg.txt");
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

void LevelManager::SetBackgroundMusicVolume(float volume)
{
	m_bgVolume = volume;
}

bool LevelManager::InitialScriptRun(){ return m_initialScriptRun; }

std::string LevelManager::GetInitialScript(){

	m_initialScriptRun = true;

	return m_initializingScript;

}

void LevelManager::AddSound(SFX* sfx)
{
	m_sounds.push_back(sfx);
}

void LevelManager::PlaySound(std::string& id){
	if(!m_sounds.empty())
	{
		for(unsigned int i = 0; i < m_sounds.size(); i++)
		{
			if(!m_sounds[i]->GetID().compare(id))
			{
				// Found the entity, play the sound
				m_sounds[i]->Play();
				break;
			}
		}
	}
}