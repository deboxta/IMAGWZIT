#pragma once
#include <SFML/System/Vector2.hpp>

struct PlayerCommand
{
	PlayerCommand(sf::Vector2f moveVector)
	{
		this->moveVector = moveVector;
	}
	sf::Vector2f moveVector;
};

