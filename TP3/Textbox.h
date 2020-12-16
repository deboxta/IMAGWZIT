#pragma once
#include <SFML/Graphics.hpp>
#include "Label.h"

using namespace sf;


namespace TP3Prog
{
	class Textbox : public Label
	{
	//DOC DES MÉTHODES DANS LE .CPP
	public:
		Textbox();
		void initializeStandardTextbox(const Font& font, const Vector2f position, const bool central, const int width,
			const String text, const int textLenghtLimit);
		void select();
		void unSelect();
		bool touch(const Vector2i& position);
		void addCharacter(const char character);
		void removeCharacter();
		void setSelectionColor(const Color selectionColor);

	private:		
		/// <summary>
		/// Couleur par défaut du cadre quand il est séelctionné.
		/// </summary>
		Color selectionColor = Color::Yellow;
	};
}

