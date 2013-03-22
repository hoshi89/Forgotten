#ifndef INCLUDED_BACKGROUNDOBJECT
#define INCLUDED_BACKGROUNDOBJECT

#include "Entity.h"
#include "Animation.h"

enum Behaviour{STATIC, MOVING_CAR};

class BackgroundObject : public Entity{
public:
	BackgroundObject(const std::string& id, const std::string& animationSheet, int timePerFrame, int numFrames, bool loop, int posX, int posY, int z, Behaviour behaviour, const std::string& soundFilename = "", int pauseTime=0);
	virtual std::string GetID();
	virtual void SetID(std::string id);
	void SetPosition(int x, int y);
	void Update();
	const sf::Sprite& GetSprite() const;
	void Render(sf::RenderWindow &window);
	const int GetZ();
	void StopSound();
	void Interact(int item=-1){};
	bool MouseOver(MouseHandler&){ return false; };
	void GoTo(sf::Vector2f){};
	void AddAnimation(const std::string& id, const std::string& animationSheet, int timePerFrame, int numFrames, bool loop = true, const std::string& soundFilename = "", int pauseTime = 0);
	void SetAnimation(const std::string& id);
private:
	std::map<std::string, Animation*> m_animations;
	Behaviour m_behaviour;
	sf::Clock m_clock;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	Animation *m_currentAnimation;
	int m_z;
	std::string m_id;
	void MovingCar();
};

#endif


