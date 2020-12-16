#include "TitleScreen.h"

using namespace TP3Prog;

TitleScreen::TitleScreen()
{

}

TitleScreen::~TitleScreen()
{
}

Scene::scenes TitleScreen::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionToScene;
}

bool TitleScreen::init(RenderWindow * const window)
{
	if (!ScreenImageT.loadFromFile("Sprites\\tp3_title.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Fonts\\Lady Radical 2.ttf"))
	{
		return false;
	}

	ScreenImage.setTexture(ScreenImageT);

	creatorsNames.initializeFloatingTextLabel(font, Vector2f(1920/2, 500), true, 0, "", 50, Color::Red);
	enterGameButton.initializeStandardCustomButton(font, Vector2f(1920 / 2, 600), true, 200, "game", 4);
	instrucButton.initializeStandardCustomButton(font, Vector2f(1920 / 2, 700), true, 200, "instructions", 12);
	creditsButton.initializeStandardCustomButton(font, Vector2f(1920 / 2, 800), true, 200, "credits", 7);
	quitButton.initializeStandardCustomButton(font, Vector2f(1920 / 2, 900), true, 200, "quit", 4);

	this->mainWin = window;
	isRunning = true;

	return true;
}

//Puisqu'il ne s'agit pas vraiment d'une scene de jeu et que la manipulation des label et textbox est très fortement 
//liée aux événements claviers et souris, tout sera codé dans le getInputs pour leur manipulations
void TitleScreen::getInputs()
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
				enterGameButton.pressed(Mouse::getPosition(*mainWin));
				instrucButton.pressed(Mouse::getPosition(*mainWin));
				creditsButton.pressed(Mouse::getPosition(*mainWin));
				quitButton.pressed(Mouse::getPosition(*mainWin));
			}
		}

		if (event.type == Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (enterGameButton.released(Mouse::getPosition(*mainWin)))
				{
					transition(GAME);
				}
				if (instrucButton.released(Mouse::getPosition(*mainWin)))
				{
					transition(INSTRUCTIONS);
				}
				if (creditsButton.released(Mouse::getPosition(*mainWin)))
				{
					transition(CREDITS);
				}
				if (quitButton.released(Mouse::getPosition(*mainWin)))
				{
					transition(EXIT);
				}
			}
		}
	}
}

void TitleScreen::update()
{
}

void TitleScreen::draw()
{
	mainWin->clear();
	mainWin->draw(ScreenImage);
	creatorsNames.draw(mainWin);
	enterGameButton.draw(mainWin);
	instrucButton.draw(mainWin);
	creditsButton.draw(mainWin);
	quitButton.draw(mainWin);
	mainWin->display();
}

void TitleScreen::transition(const Scene::scenes & scene)
{
	isRunning = false;
	transitionToScene = scene;
}

