#pragma once
#include <SFML/Graphics.hpp>
#include "GameScreen.h"
#include "Scene.h"
#include "Label.h"
#include "CustomButton.h"


using namespace sf;
using namespace std;

namespace TP3Prog
{
	class EndScreen : public Scene
	{
	public:
		EndScreen(int* score);
		~EndScreen();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();
		void transition(const Scene::scenes& scene);

	private:
		Label scoreLebel;
		int score;
		CustomButton newGameButton;
		CustomButton titleButton;
		CustomButton quitButton;
	};
}