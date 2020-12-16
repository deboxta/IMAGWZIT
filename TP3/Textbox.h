#pragma once
#include <SFML/Graphics.hpp>
#include "Label.h"

using namespace sf;


namespace TP3Prog
{
	class Textbox : public Label
	{
	//DOC DES M�THODES DANS LE .CPP
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
		/// Couleur par d�faut du cadre quand il est s�elctionn�.
		/// </summary>
		Color selectionColor = Color::Yellow;
	};
}

