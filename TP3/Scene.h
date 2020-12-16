#pragma once

#include <SFML/Graphics.hpp>
//pour le mvc
//#include "IModele.h"

using namespace sf;

/// <summary>
/// Classe abstraite avec aucune méthode concrétisée.  Un .h suffit donc.
/// </summary>
namespace TP3Prog
{
	class Scene
	{
	public:
		//Quand vos ajouterez des scènes, ajouter un enum ici
		enum scenes {TITLE, GAME, INSTRUCTIONS, CREDITS, END, EXIT};

		virtual ~Scene() {}  //Pour que le destructeur de l'objet en mémoire soit apellé
		virtual scenes run() = 0;
		
		//La boucle de jeu est maintenant gérée par la scène
		virtual bool init(RenderWindow * const window) = 0;
		virtual void getInputs() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

		virtual void transition(const scenes& scene) = 0;
		virtual void errorMessage(const std::string &error) {};
		virtual void scoresDisplay() {};
	protected:
		RenderWindow *mainWin;
		Event event;
		
		/// <summary>
		/// À la fin de chaque scène, on indique à Game quelle sra la nouvelle scène qu'elle doit charger.
		/// </summary>
		Scene::scenes transitionToScene;
		Texture ScreenImageT;
		Sprite ScreenImage;
		Font font;
		//IModele* interfaceModele = nullptr;
		bool isRunning;

	};
}