#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

namespace TP3Prog
{

	/// <summary>
	/// The Game behavior class. Manages the game flow and
	/// all elements within.
	/// </summary>
	class Game
	{
	public:
		Game();
		int run();
		int getscore() const;
		
	private:
		static const int SCREEN_WIDTH = 1920;
		static const int SCREEN_HEIGHT = 1080;
		RenderWindow mainWin;
		Event event;
		int score = 0;
	};
}