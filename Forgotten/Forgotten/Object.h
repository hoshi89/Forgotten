#ifndef INCLUDED_OBJECT
#define INCLUDED_OBJECT

#include "Entity.h"

class Object : public Entity{
public:
	Object(std::string id, int xPos, int yPos, int interactionX, int interactionY, std::string texture, int timeperframe, int numframes);
	virtual std::string GetID();
	virtual void SetID(std::string id);
	void SetPosition(int x, int y);
	void Update();
	const sf::Sprite& GetSprite() const;
	void Render(sf::RenderWindow &window);
	const int GetZ();
	void StopSound();
	void Interact(int item=-1);
	sf::Vector2f GetInteractionNode();
	void StartInteraction();
	bool MouseOver(MouseHandler &mouse);
	void GoTo(sf::Vector2f);
	void Inspect();
	void SetInteractScript(std::string script);
	void SetInspectScript(std::string script);
	void SetGiveScript(std::string script);
	void SetNoCanDoScript(std::string script);
	void SetWantsItem(int id);
	void SetSpriteOffset(int x, int y);
private:
	Animation m_idle;
	Animation *m_currentAnimation;
	sf::Vector2f m_position;
	sf::Vector2f m_interactionNode;
	std::string m_interactScript;
	std::string m_giveScript;
	std::string m_inspectScript;
	std::string m_noCanDoScript;
	std::string m_id;
	int m_hasBeenGivenItem;
	int m_wantsItem;
	int xOffset;
	int yOffset;
};

#endif