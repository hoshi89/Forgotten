#pragma once
#include "dialogownercls.h"
class ObjectCls :
	public DialogOwnerCls
{
public:
	ObjectCls(const char *aDeckName, int aXpos, int aYpos, Player *aPlayer);
	/*

	*/
	sf::Texture m_texture;
	Animation m_currentAnimation;
	void SetPosition(int x, int y) override;
	const sf::Sprite& GetSprite() const override;
//	sf::Vector2f PlaceText(DialogCls aDialog) override;
	void Render(sf::RenderWindow &aWindow) override;
	void Update() override;
	int const GetZ() override;
	sf::Vector2f m_position;
	sf::Text ManageText(sf::Text aText) override;
private:
	virtual ~ObjectCls(void);
};

