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
	//deux enums et un pointeur de scene pour faire la manipulation de sc�ne
	Scene::scenes selecteurDeScene = Scene::scenes::TITLE;
	Scene::scenes sceneEnRetour;
	Scene* sceneActive = nullptr; //Pointeur de la super-classe, peut pointer sur n'imprte quelle sc�ne

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
			//Vous allez ajouter d'autre sc�nes, alors elles devront
			//�tre ajout�es ici
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
				//� la fin d'une sc�ne, s'il y a des sauvegardes � faire
				//C'est aussi possible de les faire l�.
				if (dynamic_cast<GameScreen*>(sceneActive))
				{
					score = (dynamic_cast<GameScreen*>(sceneActive))->getScore();
				}
			}
			else
			{
				//cleap-up � faire pour s'assurer  de ne pas avoir de leak
				//(malgr� l'�chec)
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
