#include "Obstacle.h"
#include <SFML/Graphics/Texture.hpp>


namespace TP3Prog
{
	sf::Texture Obstacle::obstacleTexture;

	Obstacle::Obstacle(sf::Vector2f centralPosition, sf::Vector2f size)
	{
		setTexture(obstacleTexture);
		setScale(size * (1.0f / OBSTACLE_SIZE));
		setOrigin(size * 0.5f);
		setPosition(centralPosition);
	}

	Obstacle::~Obstacle()
	{
	}

	bool Obstacle::loadTexture(std::string texturePath)
	{
		if (!obstacleTexture.loadFromFile(texturePath))
		{
			return false;
		}

		return true;
	}
}
