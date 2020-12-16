#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace TP3Prog
{
	class Obstacle :
		public sf::Sprite
	{
	public:
		Obstacle(sf::Vector2f centralPosition, sf::Vector2f size);
		~Obstacle();
		static bool loadTexture(std::string texturePath);

		static const int OBSTACLE_SIZE = 64;
	private:
		static sf::Texture obstacleTexture;
	};
}

