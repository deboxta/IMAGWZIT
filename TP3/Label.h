#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;


namespace TP3Prog
{
	 //<summary>
	 //Contr�le de texte de base, pleine de flaws, mais qui fera la job pour ce TP
	 //Label sert comme texte d'information.  la sous-classe Textbox permet en plus 
	 //d'entrer de l'information.  Je r�p�te c'est un peu boboche, mais �a marche
	 //et c'est ce qui est important
	 //</summary>
	class Label : public RectangleShape
	{
	//DOC DES M�THODES DANS LE .CPP
	public:
		Label();
		void initializeTextControl(const Font& font, const Vector2f position, const bool central, const int width, 
			                 const String text, const int textLenghtLimit, Color frameColor, Color backgroundColor, Color textColor);

		void initializeStandardLabel(const Font& font, const Vector2f position, const bool central, const int width,
                     			     const String text, const int textLenghtLimit);

		void initializeFloatingTextLabel(const Font& font, const Vector2f position, const bool central, const int width,
			                             const String text, const int textLenghtLimit, Color textColor);


		void setText(String text);
		String getText() const;
		void draw(RenderWindow* const window);

	protected:
		void visualAdjustments();

		 //<summary>
		 //Limite de caract�res que notre textbox tol�re.  Mettez 1 de limite par 20 pixels de largeur de votre boite
		 //Ainsi si vous entrez que des caract�res larges (comme W par exemple), tout va entrer
		 //</summary>
		int textLenghtLimit;

		 //<summary>
		 //Le texte � afficher.
		 //</summary>
		Text text;

		//<summary>
		//Si vrai, on fonctionne en centr�.  Si faux, on fonctionne en appui gauche.
		//</summary>
		bool centralPositioning;

		//Couleur du cadre sauvegard� (pratique surtout pour les sous-classes)
		Color frameColor;

		// Ces �l�ments sont d�lib�r�ments hardcod�s: on ne veut pas une label hyper-flexible,
		// juste de quoi qui fera le travail pour ce TP.  Mais en gros, on garde la hauteur fixe.
		// Rendre flexible la hauteur du label et la taille du texte demanderait pas mal de tests
		static const int HEIGHT = 40;
		static const int CHARACTER_SIZE = 20;
		static const int CHARACTER_OFFSET = 20;
		static const int LETTER_OFFSET1 = 7;
		static const int LETTER_OFFSET2 = 2;
		static const int OUTILINE_THICKNESS = 2;
		static const Color orange;
		static const Color darkGrey;
		static const Color lightGrey;
	};
}


