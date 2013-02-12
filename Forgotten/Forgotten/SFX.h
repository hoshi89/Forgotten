#ifndef INCLUDED_SFX
#define INCLUDED_SFX

#include <SFML\Audio.hpp>

class SFX{
public:
	SFX(const std::string& filename);
	void Play();
	void Pause();
	void Stop();
private:
	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;
};

#endif