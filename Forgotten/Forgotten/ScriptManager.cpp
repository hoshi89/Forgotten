#include "ScriptManager.h"

ScriptManager* ScriptManager::m_instance = NULL;

ScriptManager* ScriptManager::GetInstance()
{
	if(!m_instance)
		m_instance = new ScriptManager;

	return m_instance;
}

void ScriptManager::LoadScript(std::string filename)
{

	std::ifstream scriptFile(filename);
	std::stringstream tmpStream;
	std::string tmpString;
	std::string token;

	if(scriptFile)
	{

		// Start looping through the rows
		while(std::getline(scriptFile, tmpString))
		{

			// Add the string to the stream
			tmpStream << tmpString;

			// Get the event type
			std::getline(tmpStream, token, ' ');
			
			// Wait
			if(token == "wait")
			{
				// Get wait time as string
				std::getline(tmpStream, token, ' ');
				int time = ConvertFromString(token);

				// Create a wait object and push it into the queue to run
				// EventHandler::GetInstance()->AddEvent(Wait(time));

			}else if(token == "fade"){

				// Get fade time as string
				std::getline(tmpStream, token, ' ');
				int fadetime = ConvertFromString(token);

				// Create a wait object and push it into the queue to run
				// EventHandler::GetInstance()->AddEvent(Fade(fadetime));

			}

			// Clear the stream
			tmpStream.clear();

		}

	}

}

int ScriptManager::ConvertFromString(const std::string &str)
{
	std::istringstream stream(str);
	int t;
	stream >> t;
	return t;

}