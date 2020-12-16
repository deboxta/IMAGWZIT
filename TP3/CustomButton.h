#pragma once
#include <SFML/Graphics.hpp>
#include "Label.h"

using namespace sf;

namespace TP3Prog
{
	class CustomButton : public Label
	{
	public:
		CustomButton();

		void initializeStandardCustomButton(const Font& font, const Vector2f position, const bool central, const int width,
			const String text, const int textLenghtLimit);

		void pressed(const Vector2i& position);
		bool released(const Vector2i& position);

	private:
		static const int CLICKED_OUTILINE_THICKNESS = 6;
		int clickCount = 0;
	};
}

