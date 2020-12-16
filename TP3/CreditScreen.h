#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "CustomButton.h"


using namespace sf;
using namespace std;

namespace TP3Prog
{
	class CreditScreen : public Scene
	{
	public:
		CreditScreen();
		~CreditScreen();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();
		void transition(const Scene::scenes& scene);

	private:
		CustomButton returnMenuButton;
	};
}
