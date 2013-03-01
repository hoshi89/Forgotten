#ifndef INCLUDED_BACKGROUNDOBJECT
#define INCLUDED_BACKGROUNDOBJECT

#include "Entity.h"
#include "Animation.h"

class BackgroundObject : public Entity{
public:
	BackgroundObject(std::string animationSheet, int timePerFrame, int numFrames, int posX, int posY, int z, const std::string& soundFilename = "");
	virtual std::string GetID();
	virtual void SetID(std::string id);
	void SetPosition(int x, int y);
	void Update();
	const sf::Sprite& GetSprite() const;
	void Render(sf::RenderWindow &window);
	const int GetZ();
	void StopSound();
	void Interact(){};
	bool MouseOver(MouseHandler&){ return false; };
	void GoTo(sf::Vector2f){};
private:
	sf::Vector2f m_position;
	Animation m_animation;
	int m_z;
	std::string m_id;
};

#endif


