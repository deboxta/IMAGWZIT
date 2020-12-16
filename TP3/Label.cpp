#include "Label.h"

using namespace TP3Prog;

const Color Label::orange = Color(255, 165, 0);
const Color Label::darkGrey = Color(32, 32, 32);
const Color Label::lightGrey = Color(112, 112, 112);

Label::Label()
{
}

/// <summary>
/// Initiation d'un Label.  Le choix ne rien mettre dans le constructeur vient du fait
/// Qu'il est inutile d'initialiser quoi que ce soit tant qu'on a pas une font valide.
/// O� alors on serait oblig� de l'utiliser comme pointeur.
/// Les m�thode d'initialisation r�glent la question
///
/// </summary>
/// <param name="font">La font utilis�e</param>
/// <param name="position">Position � l'�cran.  Si centr�e, Le label est centr�e sur cette position.</param>
/// <param name="position">Si le texte est centr�e sur le controle. Si faux, est en appui gauche.</param>
/// <param name="width">Largeur en pixels du Label</param>
/// <param name="text">Le texte � afficher tout simplement</param>
/// <param name="textLenghtLimit">Limite de caract�res; devrait �tre 1 pour 20 pixels de longueur du label.</param>
/// <param name="frameColor">Couleur du cadre du label</param>
/// <param name="backgroundColor">Couleur du fond du label.</param>
/// <param name="textColor">Couleur du texte dans le label.</param>
void Label::initializeTextControl(const Font& font, const Vector2f position, const bool central, const int width,
	const String text, const int textLenghtLimit, Color frameColor, Color backgroundColor, Color textColor)
{
	this->setSize(Vector2f(width, HEIGHT));
	this->setPosition(position);
	this->centralPositioning = central;

	if (centralPositioning)
	{
		setOrigin(width / 2, HEIGHT / 2);
	}

	this->setOutlineThickness(OUTILINE_THICKNESS);
	this->setOutlineColor(frameColor);
	this->setFillColor(backgroundColor);
	this->textLenghtLimit = textLenghtLimit;
	this->frameColor = frameColor;

	this->text.setFont(font);
	this->text.setCharacterSize(CHARACTER_SIZE);
	this->text.setFillColor(textColor);
	this->textLenghtLimit = textLenghtLimit;
	this->setText(text);
}

//Comme au dessus, mais les couleurs sont hardcod�s.
void Label::initializeStandardLabel(const Font& font, const Vector2f position, const bool central, const int width,
	const String text, const int textLenghtLimit)
{
	initializeTextControl(font, position, central, width, text, textLenghtLimit, lightGrey, darkGrey, lightGrey);
}

//Comme au dessus, mais le cadre et le fond sont transparents.
void Label::initializeFloatingTextLabel(const Font& font, const Vector2f position, const bool central, const int width,
	const String text, const int textLenghtLimit, Color textColor)
{
	initializeTextControl(font, position, central, width, text, textLenghtLimit, Color::Transparent, Color::Transparent, textColor);
}


String Label::getText() const
{
	return text.getString();
}

/// <summary>
/// Le texte est ins�r� et remplace le pr�c�dent.
/// S'il est plus long que le maxuimum permis, on le coupe au maximum permis.
/// On ajuste le visuel pour bien positionner le texte dans le contrpole.
/// </summary>
/// <param name="leTexte">Le texte.</param>
void Label::setText(String text)
{
	//Si trop long on concat�ne
	if (text.getSize() > textLenghtLimit)
	{
		text = text.substring(0, textLenghtLimit);
	}

	this->text.setString(text);
	visualAdjustments();
}

/// <summary>
/// Ajustements visuels: le texte peut-�tre centr� sur la position de la boite.
/// </summary>
void Label::visualAdjustments()
{
	if (centralPositioning)
	{		
		text.setOrigin(Vector2f(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2 + LETTER_OFFSET1));
		text.setPosition(getPosition());
	}
	else
	{
		text.setPosition(getPosition().x + LETTER_OFFSET1, getPosition().y + LETTER_OFFSET2);
	}
}

void Label::draw(RenderWindow* const window)
{
	window->draw(*this);
	window->draw(text);
}
