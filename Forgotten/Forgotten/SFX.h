#ifndef INCLUDED_SFX
#define INCLUDED_SFX

#include <SFML\Audio.hpp>

class SFX{
public:
	SFX(const std::string& filename, const std::string& id = "");
	void Play();
	void Pause();
	void Stop();
	void SetRelativeSound(bool relative);
	void SetSoundPosition(int x, int y, int z);
	std::string GetID();
private:
	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;
	std::string m_id;
};

#endif