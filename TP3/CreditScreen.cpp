#include "CreditScreen.h"
#include "Game.h"

using namespace TP3Prog;

CreditScreen::CreditScreen()
{

}

CreditScreen::~CreditScreen()
{
}

Scene::scenes CreditScreen::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionToScene;
}

bool CreditScreen::init(RenderWindow * const window)
{
	if (!ScreenImageT.loadFromFile("Sprites\\tp3_credit.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Fonts\\Lady Radical 2.ttf"))
	{
		return false;
	}

	ScreenImage.setTexture(ScreenImageT);

	returnMenuButton.initializeStandardCustomButton(font, Vector2f(1750, 900), true, 200, "return", 6);

	this->mainWin = window;
	isRunning = true;

	return true;
}

//Puisqu'il ne s'agit pas vraiment d'une scene de jeu et que la manipulation des label et textbox est tr�s fortement 
//li�e aux �v�nements claviers et souris, tout sera cod� dans le getInputs pour leur manipulations
void CreditScreen::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fen�tre ne mettrait pas n�cessairement 
			//fin corrctement � l'application
			transition(EXIT);
		}

		//Si on a un �v�nement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//Valider si on a appuy� ou non sur un bouton
				returnMenuButton.pressed(Mouse::getPosition(*mainWin));
			}
		}

		if (event.type == Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (returnMenuButton.released(Mouse::getPosition(*mainWin)))
				{
					transition(TITLE);
				}
			}
		}
	}
}

void CreditScreen::update()
{
}

void CreditScreen::draw()
{
	mainWin->clear();
	mainWin->draw(ScreenImage);
	returnMenuButton.draw(mainWin);
	mainWin->display();
}

void CreditScreen::transition(const Scene::scenes & scene)
{
	isRunning = false;
	transitionToScene = scene;
}
