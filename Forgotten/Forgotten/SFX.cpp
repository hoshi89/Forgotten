#include "SFX.h"

SFX::SFX(const std::string& filename)
{
	if(filename.length() > 0){
		m_buffer.loadFromFile(filename);
	}
	m_sound.setBuffer(m_buffer);
}

void SFX::Play(){ m_sound.play(); }

void SFX::Pause(){ m_sound.pause(); }

void SFX::Stop(){ m_sound.stop(); }