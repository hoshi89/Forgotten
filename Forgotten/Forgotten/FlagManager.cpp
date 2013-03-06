#include "FlagManager.h"

FlagManager* FlagManager::m_instance = 0;

FlagManager* FlagManager::GetInstance()
{
	if(!m_instance)
		m_instance = new FlagManager;

	return m_instance;
}

void FlagManager::CreateFlag(std::string flagname)
{
	m_flags.push_back(flagname);
}

void FlagManager::DeleteFlag(std::string flagname)
{
	int flag_to_be_removed = -1;

	for(unsigned int i = 0; i < m_flags.size(); i++)
	{
		if(!m_flags[i].compare(flagname))
		{
			// Mark this flag
			flag_to_be_removed = i;
		}
	}

	// Was any flag found?
	if(flag_to_be_removed >= 0)
	{
		// Delete it
		m_flags.erase(m_flags.begin()+flag_to_be_removed);
	}
}

bool FlagManager::IsFlagSet(std::string flagname)
{
	for(unsigned int i = 0; i < m_flags.size(); i++)
	{
		if(!m_flags[i].compare(flagname))
		{
			return true;
		}
	}
	return false;
}

FlagManager::FlagManager()
{
}