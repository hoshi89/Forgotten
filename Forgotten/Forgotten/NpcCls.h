#pragma once
#include "entity.h"

#include <string>

using namespace std;

class NpcCls :
	public Entity
{
public:
	NpcCls(int aXpos, int aYpos, const string aSpriteName,
		sf::Vector2f aInteractionNode,
		GenericMap &aMap, string aScript);
	sf::Texture m_texture;
	void SetPosition(int x, int y) override;
	const sf::Sprite& GetSprite() const override;
	void Render(sf::RenderWindow &aWindow) override;
	void Update() override;
	int const GetZ() override;
	void StopSound() override;
	void Interact(int item=-1);
	sf::Vector2f GetInteractionNode() override;
	void StartInteraction() override;
	bool MouseOver(MouseHandler&) override;
	void GoTo(sf::Vector2f aInteractionNode) override;
	void SetDirection(Entity::Direction aDirection) override;
	virtual ~NpcCls(void);
private:
	string m_CurrentScript;
	int posX;
	int posY;
	GenericMap &m_nodeMap;
	Animation m_currentAnimation;
	sf::Vector2f m_position;
	sf::Vector2f m_InteractionNode;
	Entity::Direction m_Direction;


};

