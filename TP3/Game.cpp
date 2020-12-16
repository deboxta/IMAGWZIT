#include "Game.h"
#include "GameScreen.h"
#include "TitleScreen.h"	
#include "InstructionScreen.h"
#include "CreditScreen.h"
#include "EndScreen.h"
#include "Constants.h"

using namespace TP3Prog;

Game::Game()
{
	mainWin.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "TP3 - "); // , Style::Fullscreen);

	mainWin.setVerticalSyncEnabled(true);
}

int Game::run()
{
	//deux enums et un pointeur de scene pour faire la manipulation de scène
	Scene::scenes selecteurDeScene = Scene::scenes::TITLE;
	Scene::scenes sceneEnRetour;
	Scene* sceneActive = nullptr; //Pointeur de la super-classe, peut pointer sur n'imprte quelle scène

	while (true)
	{
		//Seule condition de EXIT de toute l'app
		if (selecteurDeScene == Scene::scenes::EXIT)
		{
			//Controleur::getInstance()->release();
			return EXIT_SUCCESS;
		}
		else
		{
			//Vous allez ajouter d'autre scènes, alors elles devront
			//être ajoutées ici
			switch (selecteurDeScene)
			{
			case Scene::scenes::TITLE:
				sceneActive = new TitleScreen();
				break;
			case Scene::scenes::GAME:
				sceneActive = new GameScreen();
				break;
			case Scene::scenes::INSTRUCTIONS:
				sceneActive = new InstructionScreen();
				break;
			case Scene::scenes::CREDITS:
				sceneActive = new CreditScreen();
				break;
			case Scene::scenes::END:
				sceneActive = new EndScreen(&score);
				break;
			}


			if (sceneActive->init(&mainWin))
			{
				sceneEnRetour = sceneActive->run();
				//À la fin d'une scène, s'il y a des sauvegardes à faire
				//C'est aussi possible de les faire là.
				if (dynamic_cast<GameScreen*>(sceneActive))
				{
					score = (dynamic_cast<GameScreen*>(sceneActive))->getScore();
				}
			}
			else
			{
				//cleap-up à faire pour s'assurer  de ne pas avoir de leak
				//(malgré l'échec)
				return EXIT_FAILURE;
			}
		}

		selecteurDeScene = sceneEnRetour;
		delete sceneActive;
		sceneActive = nullptr;
	}
}

int TP3Prog::Game::getscore() const
{
	return score;
}
