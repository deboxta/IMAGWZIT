#include "Textbox.h"

using namespace TP3Prog;

Textbox::Textbox()
{
}

//Initialisation des des couleurs "standards d'un textbox"
void Textbox::initializeStandardTextbox(const Font& font, const Vector2f position, const bool central, const int width,
	const String text, const int textLenghtLimit)
{
	initializeTextControl(font, position, central, width, text, textLenghtLimit, orange, lightGrey, Color::White);
}

/// <summary>
/// Fait juste changer la couleur du cadre pour la couleur de s�lection
/// </summary>
void Textbox::select()
{
	setOutlineColor(selectionColor);
}

/// <summary>
/// Ram�ne la couleur r�guli�re du cadre de s�lection.
/// </summary>
void Textbox::unSelect()
{
	setOutlineColor(frameColor);
}

/// <summary>
/// V�rifie si une position touche au textbox
/// Utile pour un click de souris
/// </summary>
bool Textbox::touch(const Vector2i& position)
{
	if (position.x > getGlobalBounds().left && position.x < getGlobalBounds().left + getGlobalBounds().width &&
		position.y > getGlobalBounds().top && position.y < getGlobalBounds().top + getGlobalBounds().height)
	{
		return true;
	}

	return false;
}

/// <summary>
/// On ajoute un caract�re � la string, si on est pas � la longueur maximale
/// </summary>
void Textbox::addCharacter(const char character)
{
	if (text.getString().getSize() >= textLenghtLimit) return;

	text.setString(text.getString() + character);
	visualAdjustments();
}

/// <summary>
/// On retire un caract�re � la string, si on est pas � la longueur 0
/// </summary>
void Textbox::removeCharacter()
{
	if (text.getString().getSize() == 0) return;

	text.setString(text.getString().substring(0, text.getString().getSize() - 1));
	visualAdjustments();
}

void Textbox::setSelectionColor(const Color selectionColor)
{
	this->selectionColor = selectionColor;
}