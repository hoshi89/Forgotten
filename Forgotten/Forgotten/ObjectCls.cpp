#include "ObjectCls.h"


ObjectCls::ObjectCls(const char *aDeckName, Player *aPlayer) : DialogOwnerCls(aDeckName, aPlayer)
{
	mDialog = DialogCls::DialogCls(aDeckName);
}

void ObjectCls::PlaceText(DialogCls aDialog)
{
}

void ObjectCls::Render(sf::RenderWindow &aWindow)
{
	m_currentString = mDialog.getCurrentString();
	sf::Text m_theText = sf::Text::Text(m_currentString);
	aWindow.draw(m_theText);

}


ObjectCls::~ObjectCls(void)
{
}
