#include "RenderStates.h"

int main()
{
	//Create RenderState
	RenderStates* renderStates = new RenderStates(RenderStates::RenderState::Menu);

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
			case sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::Escape)
				{
					renderStates->SetRenderState(RenderStates::RenderState::Menu);
				}
			default:
				//Wrong I guess!!??!
				break;
			}

		}
		renderStates->RenderState();
	}
	return 0;
}