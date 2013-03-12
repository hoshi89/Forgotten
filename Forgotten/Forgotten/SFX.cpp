#include "SFX.h"

SFX::SFX(const std::string& filename, const std::string& id)
{
	if(filename.length() > 0){
		m_buffer.loadFromFile(filename);
	}
	m_sound.setBuffer(m_buffer);
}

void SFX::Play(){ m_sound.play(); }

void SFX::Pause(){ m_sound.pause(); }

void SFX::Stop(){ m_sound.stop(); }

void SFX::SetRelativeSound(bool relative)
{
	m_sound.setRelativeToListener(relative);
}

void SFX::SetSoundPosition(int x, int y, int z)
{
	m_sound.setPosition(x, y, z);
}

std::string SFX::GetID()
{
	return m_id;
}