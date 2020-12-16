#include "CustomButton.h"

using namespace TP3Prog;

CustomButton::CustomButton()
{
}

//Label avec couleurs hardcodés
void CustomButton::initializeStandardCustomButton(const Font& font, const Vector2f position, const bool central, const int width,
	const String text, const int textLenghtLimit)
{
	initializeTextControl(font, position, central, width, text, textLenghtLimit, Color::Red, Color::White, Color::Red);
}

void CustomButton::pressed(const Vector2i& position)
{
	if (position.x > getGlobalBounds().left && position.x < getGlobalBounds().left + getGlobalBounds().width &&
		position.y > getGlobalBounds().top && position.y < getGlobalBounds().top + getGlobalBounds().height)
	{
		this->setOutlineThickness(CLICKED_OUTILINE_THICKNESS);
		++clickCount;
	}
}

bool CustomButton::released(const Vector2i& position)
{
	if (position.x > getGlobalBounds().left && position.x < getGlobalBounds().left + getGlobalBounds().width &&
		position.y > getGlobalBounds().top && position.y < getGlobalBounds().top + getGlobalBounds().height)
	{
		++clickCount;
	}

	this->setOutlineThickness(OUTILINE_THICKNESS);
	int tempclickCount = clickCount;
	clickCount = 0;

	if (tempclickCount == 2)
	{
		return true;
	}

	return false;
}
