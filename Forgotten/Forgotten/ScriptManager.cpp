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

			}
			// Fade out
			else if(token == "fadeout")
			{

				// Get fade time as string
				std::getline(tmpStream, token, ' ');
				int fadetime = ConvertFromString(token);

				// Create a wait object and push it into the queue to run
				// EventHandler::GetInstance()->AddEvent(FadeOut(fadetime));

			}
			// Fade in
			else if(token == "fadein")
			{

				// Get fade time as string
				std::getline(tmpStream, token, ' ');
				int fadetime = ConvertFromString(token);

				// Create a wait object and push it into the queue to run
				// EventHandler::GetInstance()->AddEvent(FadeIn(fadetime));

			}
			// Set level
			else if(token == "setlevel")
			{

				// Get level id as string
				std::getline(tmpStream, token, ' ');
				int level = ConvertFromString(token);

				// Create setlevel object and push it into the queue to run
				// EventHandler::GetInstance()->AddEvent(SetLevel(id));

			}
			// Move entity
			else if(token == "move")
			{

				// Get entity id as string
				std::getline(tmpStream, token, ' ');
				int entityid = ConvertFromString(token);

				// Get X coordinate
				std::getline(tmpStream, token, ' ');
				int x = ConvertFromString(token);

				// Get Y coordinate
				std::getline(tmpStream, token, ' ');
				int y = ConvertFromString(token);

				// Create setlevel object and push it into the queue to run
				// EventHandler::GetInstance()->AddEvent(SetLevel(id));

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