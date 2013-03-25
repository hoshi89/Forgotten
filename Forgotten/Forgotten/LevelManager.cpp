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
	// Background music
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
		m_bgMusic.setLoop(true);

		// Create rooms for this level
		m_levels.push_back(new Level(0, "Data/Levels/Level1/kapitel_1_test_hall_node.png", 25, 10, "Data/Levels/Level1/TEST_hall_fardig.png", 0.9, 0));
		m_levels.push_back(new Level(1, "Data/Levels/Level1/chapter_1_exterior_node.png", 50, 20, "Data/Levels/Level1/hotelexterior.png", 0.6, 0));
		m_levels.push_back(new Level(2, "Data/Levels/Level1/kapitel_1_test_reception_node.png", 50, 10, "Data/Levels/Level1/test_reception_inget_ljus.png", 1.2, 0));
		m_levels.push_back(new Level(3, "Data/Levels/Level1/chapter_1_hotel_room_node.png", 50, 10, "Data/Levels/Level1/hotel_room.png", 1.2, 0));
		m_levels.push_back(new Level(4, "Data/Levels/Level1/chapter_1_bar_node.png", 50, 20, "Data/Levels/Level1/chapter1_bar.png", 2.5, 12));

		// Set player position
		m_levels[0]->GetPlayer()->SetNodePosition(15, 48);
		m_levels[1]->GetPlayer()->SetNodePosition(13, 24);
		m_levels[2]->GetPlayer()->SetNodePosition(10, 50);
		m_levels[3]->GetPlayer()->SetNodePosition(7, 47);
		m_levels[4]->GetPlayer()->SetNodePosition(18, 20);

		// Add sounds
		AddSound(new SFX("Data/Sounds/elevator_open.wav", "elevator_open"));
		AddSound(new SFX("Data/Sounds/elevator_open.wav", "elevator_close"));
		AddSound(new SFX("Data/Sounds/Cello Complete Em.wav", "cello_complete_em"));
		AddSound(new SFX("Data/Sounds/matchbox.wav", "matchbox"));
		AddSound(new SFX("Data/Sounds/necklace.wav", "necklace"));
		AddSound(new SFX("Data/Sounds/letter.wav", "letter"));
		AddSound(new SFX("Data/Sounds/cash.wav", "cash"));
		AddSound(new SFX("Data/Sounds/door_1.wav", "door_1"));
		AddSound(new SFX("Data/Sounds/door_2.wav", "door_2"));

		// Add background animations
		m_levels[0]->AddObject("Broken_lamp", new BackgroundObject("Broken lamp", "Data/Levels/Level1/TEST_hall_animation_lampa.png", 100, 16, true, 1150, 70, 0, Behaviour::STATIC, "Data/Sounds/broken_lamp.wav", 3));
		m_levels[0]->AddObject("Elevator wall", new BackgroundObject("Elevator wall", "Data/Levels/Level1/TEST_hall_hiss.png", 1000, 1, true, 2191, 190, 510, Behaviour::STATIC));
		m_levels[0]->AddObject("Hall shadow", new BackgroundObject("Hall shadow", "Data/Levels/Level1/TEST_hall_skuggning.png", 1000, 1, true, 0, 0, 33, Behaviour::STATIC));
		m_levels[2]->AddObject("Overlay light", new BackgroundObject("Overlay light", "Data/Levels/Level1/test_ljus_overlay.png", 100, 1, true, 430, 70, 1000, Behaviour::STATIC));
		m_levels[2]->AddObject("Reception booth", new BackgroundObject("Reception booth", "Data/Levels/Level1/reception_booth.png", 1000, 1, true, 580, 90, 200, Behaviour::STATIC));
		m_levels[0]->AddObject("Cart", new BackgroundObject("Cart", "Data/Levels/Level1/chapter_1_cart.png", 1000, 1, true, 1045, 413, 510, Behaviour::STATIC));
		m_levels[1]->AddObject("Smoke", new BackgroundObject("Smoke", "Data/Levels/Level1/smoke.png", 100, 20, true, 400, 400, 1000, Behaviour::STATIC));
		m_levels[1]->AddObject("Camera", new BackgroundObject("Camera", "Data/Levels/Level1/camera.png", 1000, 1, true, 62, 0, 1001, Behaviour::STATIC));
		m_levels[1]->AddObject("Blinking light", new BackgroundObject("Blinking light", "Data/Levels/Level1/blink.png", 1000, 2, true, 300, 70, 1002, Behaviour::STATIC));
		m_levels[1]->AddObject("Car", new BackgroundObject("Car", "Data/Levels/Level1/car_1.png", 5000, 1, true, -300, 420, 999, Behaviour::MOVING_CAR, "Data/Sounds/car_1.wav"));
		m_levels[2]->AddObject("Keyboard", new BackgroundObject("Keyboard", "Data/Levels/Level1/null.png", 1000, 21, true, 0, 0, 0, Behaviour::STATIC, "Data/Sounds/keyboard.wav", 10));
		m_levels[4]->AddObject("Ambient bar sounds", new BackgroundObject("Ambient bar sounds", "Data/Levels/Level1/null.png", 1000, 47, true, 0, 0, 0, Behaviour::STATIC, "Data/Sounds/ambient_bar.wav"));

		// Add multiple animations background objects
		BackgroundObject *elevator_door = new BackgroundObject("door_close", "Data/Levels/Level1/level_room_door_close_sheet.png", 50, 9, false, 1057, 179, 100, Behaviour::STATIC);
		elevator_door->AddAnimation("door_open", "Data/Levels/Level1/level_room_door_open_sheet.png", 50, 9, false);

		m_levels[3]->AddObject("hotel_room_interior_door", elevator_door);

		///////////////////// PORTALS BEGIN ///////////////////////////

		// Create portals
		Portal *hotelroom2hall = new Portal("hotelroom_to_hall", sf::IntRect(1050, 180, 150, 270), sf::Vector2f(21, 45));
		Portal *hall2reception = new Portal("hall_to_reception", sf::IntRect(2136, 260, 150, 230), sf::Vector2f(91, 48));
		Portal *hall2hotelroom = new Portal("hall_to_hotelroom", sf::IntRect(310, 260, 135, 215), sf::Vector2f(15, 48));
		Portal *reception2hall = new Portal("reception_to_hall", sf::IntRect(0, 425, 150, 150), sf::Vector2f(1, 50));
		Portal *reception2bar = new Portal("reception_to_bar", sf::IntRect(920, 140, 120, 250), sf::Vector2f(19, 38));
		Portal *reception2streets = new Portal("reception_to_streets", sf::IntRect(1265, 150, 215, 260), sf::Vector2f(27, 41));
		Portal *bar2reception = new Portal("bar_to_reception", sf::IntRect(870, 210, 110, 180), sf::Vector2f(18, 19));
		Portal *streets2reception = new Portal("streets_to_reception", sf::IntRect(570, 355, 170, 120), sf::Vector2f(13, 24));

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
		m_levels[0]->AddObject("Hall2Reception", hall2reception);
		m_levels[0]->AddObject("Hall2hotelroom", hall2hotelroom);
		m_levels[1]->AddObject("Streets2Reception", streets2reception);
		m_levels[2]->AddObject("reception2hall", reception2hall);
		m_levels[2]->AddObject("reception2bar", reception2bar);
		m_levels[2]->AddObject("reception2streets", reception2streets);
		m_levels[3]->AddObject("Hotelroom2hall", hotelroom2hall);
		m_levels[4]->AddObject("bar2Reception", bar2reception);

		///////////////////// PORTALS END ///////////////////////////

		// Add objects
		Object *matches = new Object("matches", 210, 475, 5, 49, sf::IntRect(200, 395, 45, 20), "Data/Levels/Level1/chapter1_matchbox.png", 1000, 1);
		Object *necklace = new Object("necklace", 1100, 520, 44, 54, sf::IntRect(1100, 445, 33, 50), "Data/Animations/Objects/necklace.png", 1000, 1);
		Object *bed = new Object("bed", 172, 471, 10, 54, sf::IntRect(320, 360, 430, 90), "Data/Levels/Level1/hotel_room_bed.png", 1000, 1);
		Object *room_poster = new Object("poster", 0, 0, 17, 46, sf::IntRect(810, 180, 115, 220), "Data/Levels/Level1/null.png", 1000, 1);
		Object *room_items = new Object("room_items", 765, 680, 20, 54, sf::IntRect(1040, 425, 260, 135), "Data/Levels/Level1/chapter_1_books.png", 1000, 1);
		Object *silhouettes = new Object("silhouettes", 60, 136, 12, 51, sf::IntRect(100, 290, 200, 185), "Data/Levels/Level1/TEST_hall_animation_fonster.png", 100, 22);
		Object *broken_light = new Object("broken_light", 0, 0, 53, 53, sf::IntRect(1275, 205, 130, 35), "Data/Levels/Level1/null.png", 1000, 1);
		Object *payphones = new Object("payphones", 0, 0, 6, 44, sf::IntRect(100, 200, 370, 120), "Data/Levels/Level1/null.png", 1000, 1);
		Object *belmont_fees = new Object("belmont_fees", 0, 0, 12, 43, sf::IntRect(525, 120, 90, 200), "Data/Levels/Level1/null.png", 1000, 1);
		Object *posters = new Object("posters", 0, 0, 23, 44, sf::IntRect(1050, 170, 210, 170), "Data/Levels/Level1/null.png", 1000, 1);
		Object *neon_sign = new Object("neon_sign", 0, 0, 15, 21, sf::IntRect(710, 180, 120, 210), "Data/Levels/Level1/null.png", 1000, 1);
		Object *empty_bar = new Object("empty_bar", 0, 0, 21, 25, sf::IntRect(1100, 290, 400, 200), "Data/Levels/Level1/null.png", 1000, 1);
		Object *hotel_sign = new Object("hotel_sign", 0, 0, 13, 25, sf::IntRect(530, 190, 230, 100), "Data/Levels/Level1/null.png", 1000, 1);
		Object *security_camera = new Object("security_camera", 0, 0, 11, 25, sf::IntRect(180, 90, 280, 180), "Data/Levels/Level1/null.png", 1000, 1);
		Object *streets = new Object("streets", 0, 0, 12, 25, sf::IntRect(270, 520, 750, 50), "Data/Levels/Level1/null.png", 1000, 1);

		// Set object scripts
		// Matches
		matches->SetInteractScript("Data/Scripts/ch1_matches_interact.script");
		matches->SetGiveScript("Data/Scripts/ch1_matches_give.script");
		matches->SetInspectScript("Data/Scripts/ch1_matches_inspect.script");
		matches->SetNoCanDoScript("Data/Scripts/ch1_matches_nocando.script");

		// Necklace
		necklace->SetInteractScript("Data/Scripts/ch1_necklace_interact.script");
		necklace->SetGiveScript("Data/Scripts/ch1_necklace_give.script");
		necklace->SetInspectScript("Data/Scripts/ch1_necklace_inspect.script");
		necklace->SetNoCanDoScript("Data/Scripts/ch1_necklace_nocando.script");

		// Bed
		bed->SetInteractScript("Data/Scripts/ch1_bed_interact.script");
		bed->SetGiveScript("Data/Scripts/ch1_bed_give.script");
		bed->SetInspectScript("Data/Scripts/ch1_bed_inspect.script");
		bed->SetNoCanDoScript("Data/Scripts/ch1_bed_nocando.script");

		// Room poster
		room_poster->SetInteractScript("Data/Scripts/ch1_room_poster_interact.script");
		room_poster->SetGiveScript("Data/Scripts/ch1_room_poster_give.script");
		room_poster->SetInspectScript("Data/Scripts/ch1_room_poster_inspect.script");
		room_poster->SetNoCanDoScript("Data/Scripts/ch1_room_poster_nocando.script");

		// Room items
		room_items->SetInteractScript("Data/Scripts/ch1_room_items_interact.script");
		room_items->SetGiveScript("Data/Scripts/ch1_room_items_give.script");
		room_items->SetInspectScript("Data/Scripts/ch1_room_items_inspect.script");
		room_items->SetNoCanDoScript("Data/Scripts/ch1_room_items_nocando.script");

		// Silhouettes
		silhouettes->SetInteractScript("Data/Scripts/ch1_silhouettes_interact.script");
		silhouettes->SetGiveScript("Data/Scripts/ch1_silhouettes_give.script");
		silhouettes->SetInspectScript("Data/Scripts/ch1_silhouettes_inspect.script");
		silhouettes->SetNoCanDoScript("Data/Scripts/ch1_silhouettes_nocando.script");

		// Broken light
		broken_light->SetInteractScript("Data/Scripts/ch1_broken_light_interact.script");
		broken_light->SetGiveScript("Data/Scripts/ch1_broken_light_give.script");
		broken_light->SetInspectScript("Data/Scripts/ch1_broken_light_inspect.script");
		broken_light->SetNoCanDoScript("Data/Scripts/ch1_broken_light_nocando.script");

		// Payphones
		payphones->SetInteractScript("Data/Scripts/ch1_payphones_interact.script");
		payphones->SetGiveScript("Data/Scripts/ch1_payphones_give.script");
		payphones->SetInspectScript("Data/Scripts/ch1_payphones_inspect.script");
		payphones->SetNoCanDoScript("Data/Scripts/ch1_payphones_nocando.script");

		// Belmont fees
		belmont_fees->SetInteractScript("Data/Scripts/ch1_belmont_fees_interact.script");
		belmont_fees->SetGiveScript("Data/Scripts/ch1_belmont_fees_give.script");
		belmont_fees->SetInspectScript("Data/Scripts/ch1_belmont_fees_inspect.script");
		belmont_fees->SetNoCanDoScript("Data/Scripts/ch1_belmont_fees_nocando.script");

		// Posters
		posters->SetInteractScript("Data/Scripts/ch1_posters_interact.script");
		posters->SetGiveScript("Data/Scripts/ch1_posters_give.script");
		posters->SetInspectScript("Data/Scripts/ch1_posters_inspect.script");
		posters->SetNoCanDoScript("Data/Scripts/ch1_posters_nocando.script");

		// Neon sign
		neon_sign->SetInteractScript("Data/Scripts/ch1_neon_sign_interact.script");
		neon_sign->SetGiveScript("Data/Scripts/ch1_neon_sign_give.script");
		neon_sign->SetInspectScript("Data/Scripts/ch1_neon_sign_inspect.script");
		neon_sign->SetNoCanDoScript("Data/Scripts/ch1_neon_sign_nocando.script");

		// Empty bar
		empty_bar->SetInteractScript("Data/Scripts/ch1_empty_bar_interact.script");
		empty_bar->SetGiveScript("Data/Scripts/ch1_empty_bar_give.script");
		empty_bar->SetInspectScript("Data/Scripts/ch1_empty_bar_inspect.script");
		empty_bar->SetNoCanDoScript("Data/Scripts/ch1_empty_bar_nocando.script");

		// Hotel sign
		hotel_sign->SetInteractScript("Data/Scripts/ch1_hotel_sign_interact.script");
		hotel_sign->SetGiveScript("Data/Scripts/ch1_hotel_sign_give.script");
		hotel_sign->SetInspectScript("Data/Scripts/ch1_hotel_sign_inspect.script");
		hotel_sign->SetNoCanDoScript("Data/Scripts/ch1_hotel_sign_nocando.script");

		// Security camera
		security_camera->SetInteractScript("Data/Scripts/ch1_security_camera_interact.script");
		security_camera->SetGiveScript("Data/Scripts/ch1_security_camera_give.script");
		security_camera->SetInspectScript("Data/Scripts/ch1_security_camera_inspect.script");
		security_camera->SetNoCanDoScript("Data/Scripts/ch1_security_camera_nocando.script");

		// Streets
		streets->SetInteractScript("Data/Scripts/ch1_streets_interact.script");
		streets->SetGiveScript("Data/Scripts/ch1_streets_give.script");
		streets->SetInspectScript("Data/Scripts/ch1_streets_inspect.script");
		streets->SetNoCanDoScript("Data/Scripts/ch1_streets_nocando.script");

		// Set sprite offsets
		matches->SetSpriteOffset(0, 75);
		necklace->SetSpriteOffset(0, 70);
		bed->SetSpriteOffset(0, 123);
		room_items->SetSpriteOffset(0, 200);

		// Add objects to the entity vector
		m_levels[0]->AddObject("Neclace", necklace);
		m_levels[0]->AddObject("Silhouettes", silhouettes);
		m_levels[0]->AddObject("Broken Light", broken_light);
		m_levels[1]->AddObject("Hotel Sign", hotel_sign);
		m_levels[1]->AddObject("Security Camera", security_camera);
		m_levels[1]->AddObject("Streets", streets);
		m_levels[2]->AddObject("Payphones", payphones);
		m_levels[2]->AddObject("Belmont fees", belmont_fees);
		m_levels[2]->AddObject("Posters", posters);
		m_levels[3]->AddObject("Matches", matches);
		m_levels[3]->AddObject("Bed", bed);
		m_levels[3]->AddObject("Room poster", room_poster);
		m_levels[3]->AddObject("Room items", room_items);
		m_levels[4]->AddObject("Neon sign", neon_sign);
		m_levels[4]->AddObject("Empty bar", empty_bar);

		// Set first room
		m_currentLevel = m_levels[3];
		m_currentLevel->GetPlayer()->SetDirection(Entity::Direction::DOWN);

		// Add NPCS
		NpcCls *angry_woman = new NpcCls(800, 210, "Data/Animations/NPC/TEST_kapitel_1_lady.png", 1, 1000, sf::Vector2f(15, 43), m_levels[0]->GetNodeMap(), "Data/Scripts/ch1_angry_woman_interact.script", "Data/Scripts/ch1_angry_woman_inspect.script", "Data/Scripts/ch1_angry_woman_give.script", "Data/Scripts/ch1_angry_woman_nocando.script", sf::IntRect(830, 220, 60, 220 ), "angry_woman");   
		NpcCls *dendi = new NpcCls(100, 200, "Data/Animations/NPC/dendi.png", 1, 1000, sf::Vector2f(7, 26), m_levels[4]->GetNodeMap(), "Data/Scripts/ch1_dendi_interact.script", "Data/Scripts/ch1_dendi_inspect.script", "Data/Scripts/ch1_dendi_give.script", "Data/Scripts/ch1_dendi_nocando.script", sf::IntRect(120, 210, 160, 310), "dendi");
		NpcCls *valet = new NpcCls(1255, 500, "Data/Animations/NPC/chapter_1_valet.png", 1, 1000, sf::Vector2f(45, 54), m_levels[0]->GetNodeMap(), "Data/Scripts/ch1_valet_interact.script", "Data/Scripts/ch1_valet_inspect.script", "Data/Scripts/ch1_valet_give.script", "Data/Scripts/ch1_valet_nocando.script", sf::IntRect(1150, 380, 100, 140), "valet");
		NpcCls *receptionist = new NpcCls(680, 190, "Data/Animations/NPC/receptionist.png", 34, 100, sf::Vector2f(15, 43), m_levels[2]->GetNodeMap(), "Data/Scripts/ch1_receptionist_interact.script", "Data/Scripts/ch1_receptionist_inspect.script", "Data/Scripts/ch1_receptionist_give.script", "Data/Scripts/ch1_receptionist_nocando.script", sf::IntRect(650, 170, 120, 130), "receptionist");
		NpcCls *taxi = new NpcCls(1100, 540, "Data/Animations/NPC/taxi.png", 1, 100, sf::Vector2f(23, 25), m_levels[1]->GetNodeMap(), "Data/Scripts/ch1_taxi_interact.script", "Data/Scripts/ch1_taxi_inspect.script", "Data/Scripts/ch1_taxi_give.script", "Data/Scripts/ch1_taxi_nocando.script", sf::IntRect(1020, 450, 290, 80), "taxi");

		// Set sprite offset
		valet->SetSpriteOffset(100, 130);
		taxi->SetSpriteOffset(100, 200);

		// Set wants item
		dendi->SetWantsItem(1);
		angry_woman->SetWantsItem(4);
		receptionist->SetWantsItem(3);
		taxi->SetWantsItem(2);

		m_levels[2]->AddObject("Angry_woman", angry_woman);
		m_levels[4]->AddObject("Dendi", dendi);
		m_levels[0]->AddObject("Valet", valet);
		m_levels[2]->AddObject("Receptionist", receptionist);
		m_levels[1]->AddObject("Taxi", taxi);

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

std::vector<Level*> LevelManager::GetLevel()
{
	return m_levels;
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

void LevelManager::BackgroundMusicPlay(bool play)
{
	if(play)
	{
		m_bgMusic.play();
	}
	else
	{
		m_bgMusic.stop();
	}
}