#include "RenderStates.h"

int main()
{
	//Create RenderState
	RenderStates* renderStates = new RenderStates;

	while (renderStates->GetWindow().isOpen())
	{
		sf::Event Event;
		while(renderStates->GetWindow().pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::Closed:
				renderStates->GetWindow().close();
				break;
			default:
				break;
			}

		}
		renderStates->RenderState();
	}
	return 0;
}