#pragma once

#include <SFML/Graphics.hpp>
//pour le mvc
//#include "IModele.h"

using namespace sf;

/// <summary>
/// Classe abstraite avec aucune m�thode concr�tis�e.  Un .h suffit donc.
/// </summary>
namespace TP3Prog
{
	class Scene
	{
	public:
		//Quand vos ajouterez des sc�nes, ajouter un enum ici
		enum scenes {TITLE, GAME, INSTRUCTIONS, CREDITS, END, EXIT};

		virtual ~Scene() {}  //Pour que le destructeur de l'objet en m�moire soit apell�
		virtual scenes run() = 0;
		
		//La boucle de jeu est maintenant g�r�e par la sc�ne
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
		/// � la fin de chaque sc�ne, on indique � Game quelle sra la nouvelle sc�ne qu'elle doit charger.
		/// </summary>
		Scene::scenes transitionToScene;
		Texture ScreenImageT;
		Sprite ScreenImage;
		Font font;
		//IModele* interfaceModele = nullptr;
		bool isRunning;

	};
}