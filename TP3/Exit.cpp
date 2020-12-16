#include "Exit.h"
#include <SFML/Graphics/Texture.hpp>

namespace TP3Prog
{
	sf::Texture Exit::exitTexture;

	Exit::Exit(sf::Vector2f centralPosition)
	{
		setTexture(exitTexture);
		setOrigin(0.5f * sf::Vector2f(exitTexture.getSize()));
		setPosition(centralPosition);
	}

	Exit::~Exit()
	{
	}

	bool Exit::loadTexture(std::string texturePath)
	{
		if (!exitTexture.loadFromFile(texturePath))
		{
			return false;
		}

		return true;
	}
}
