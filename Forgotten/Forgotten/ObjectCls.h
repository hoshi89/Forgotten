#pragma once
#include "dialogownercls.h"
class ObjectCls :
	public DialogOwnerCls
{
public:
	ObjectCls(const char *aDeckName, int aXpos, int aYpos);
	/*

	*/
	sf::Texture m_texture;
	Animation m_currentAnimation;
	void SetPosition(int x, int y) override;
	const sf::Sprite& GetSprite() const override;
//	void PlaceText(DialogCls aDialog) override;
	void Render(sf::RenderWindow &aWindow) override;
	void Update() override;
	sf::Vector2f m_position;
private:
//	sf::Text ManageText(sf::Text aText) override;
	virtual ~ObjectCls(void);
};

