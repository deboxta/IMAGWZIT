#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace TP3Prog
{

	class Exit :
		public sf::Sprite
	{
	public:
		Exit(sf::Vector2f centralPosition);
		~Exit();
		static bool loadTexture(std::string texturePath);

		static const int OBSTACLE_SIZE = 64;
	private:
		static sf::Texture exitTexture;
	};

}

