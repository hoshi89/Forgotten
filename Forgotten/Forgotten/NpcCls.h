#pragma once
#include "entity.h"

#include <string>

using namespace std;

class NpcCls :
	public Entity
{
public:
	NpcCls(int aXpos, int aYpos, const string aSpriteName, int numFrames, int timePerFrame,
		sf::Vector2f aInteractionNode,
		GenericMap &aMap, string interactionScript, string inspectScript, string giveScript, string noCanDoScript, int wantsItem = -1);
	sf::Texture m_texture;
	void SetPosition(int x, int y) override;
	const sf::Sprite& GetSprite() const override;
	void Render(sf::RenderWindow &aWindow) override;
	void Update() override;
	int const GetZ();
	void StopSound() override;
	void Interact(int item=-1);
	void Inspect();
	sf::Vector2f GetInteractionNode() override;
	void StartInteraction() override;
	bool MouseOver(MouseHandler&) override;
	void GoTo(sf::Vector2f aInteractionNode) override;
	void SetDirection(Entity::Direction aDirection) override;
	virtual ~NpcCls(void);
private:
	string m_interactScript;
	string m_inspectScript;
	string m_giveScript;
	string m_noCanDoScript;
	int posX;
	int posY;
	int m_hasBeenGivenItem;
	int m_wantsItem;
	GenericMap &m_nodeMap;
	Animation m_currentAnimation;
	sf::Vector2f m_position;
	sf::Vector2f m_InteractionNode;
	Entity::Direction m_Direction;
};

