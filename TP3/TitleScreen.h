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
	class TitleScreen : public Scene
	{
	public:
		TitleScreen();
		~TitleScreen();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();
		void transition(const Scene::scenes& scene);

	private:
		Label creatorsNames;
		CustomButton enterGameButton;
		CustomButton instrucButton;
		CustomButton creditsButton;
		CustomButton quitButton;
	};
}
