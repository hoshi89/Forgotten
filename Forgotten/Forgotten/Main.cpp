#include "GameManager.h"

int main()
{
	// Create the manager
	GameManager manager;

	while (manager.GetWindow().isOpen())
	{
		sf::Event Event;
		while(manager.GetWindow().pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::Closed:
				manager.GetWindow().close();
				break;
			default:
				break;
			}

		}

		// Process data here
		manager.Process();

		// Render the screen
		manager.Render();
	}

	return 0;
}