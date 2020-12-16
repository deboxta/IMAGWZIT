#include "EndScreen.h"

using namespace TP3Prog;

EndScreen::EndScreen(int* score) : score(*score)
{

}

EndScreen::~EndScreen()
{
}

Scene::scenes EndScreen::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionToScene;
}

bool EndScreen::init(RenderWindow * const window)
{
	if (!ScreenImageT.loadFromFile("Sprites\\tp3_end.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Fonts\\Lady Radical 2.ttf"))
	{
		return false;
	}
	ScreenImage.setTexture(ScreenImageT);

	scoreLebel.initializeFloatingTextLabel(font, Vector2f(1920 / 2, 500), true, 0, "", 60, Color::White);
	newGameButton.initializeStandardCustomButton(font, Vector2f(1920 / 2, 700), true, 200, "new game", 8);
	titleButton.initializeStandardCustomButton(font, Vector2f(1920 / 2, 800), true, 200, "return to menu", 14);;
	quitButton.initializeStandardCustomButton(font, Vector2f(1920 / 2, 900), true, 200, "quit", 4);

	scoreLebel.setText("Score : " +std::to_string(score));

	this->mainWin = window;
	isRunning = true;

	return true;
}

//Puisqu'il ne s'agit pas vraiment d'une scene de jeu et que la manipulation des label et textbox est très fortement 
//liée aux événements claviers et souris, tout sera codé dans le getInputs pour leur manipulations
void EndScreen::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin corrctement à l'application
			transition(EXIT);
		}

		//-------------------SELECTION DE TEXTBOX ACTIVE------------------------------------//
		//Si on a un événement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//Valider si on a appuyé ou non sur un bouton
				newGameButton.pressed(Mouse::getPosition(*mainWin));
				titleButton.pressed(Mouse::getPosition(*mainWin));
				quitButton.pressed(Mouse::getPosition(*mainWin));
			}
		}

		if (event.type == Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (newGameButton.released(Mouse::getPosition(*mainWin)))
				{
					transition(GAME);
				}
				if (titleButton.released(Mouse::getPosition(*mainWin)))
				{
					transition(TITLE);
				}
				if (quitButton.released(Mouse::getPosition(*mainWin)))
				{
					transition(EXIT);
				}
			}
		}
	}
}

void EndScreen::update()
{
}

void EndScreen::draw()
{
	mainWin->clear();
	mainWin->draw(ScreenImage);
	scoreLebel.draw(mainWin);
	newGameButton.draw(mainWin);
	titleButton.draw(mainWin);
	quitButton.draw(mainWin);
	mainWin->display();
}

void EndScreen::transition(const Scene::scenes & scene)
{
	isRunning = false;
	transitionToScene = scene;
}
