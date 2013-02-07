#ifndef INCLUDED_ENTITY
#define INCLUDED_ENTITY

class Entity{
public:
	Entity(){};
	virtual ~Entity(){};
	virtual void SetPosition(int x, int y)=0;
	virtual void Update()=0;
	virtual const sf::Sprite& GetSprite() const=0;
	virtual void Render(sf::RenderWindow &aWindow)=0;
	enum Direction {UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT, UP_LEFT};
};

#endif