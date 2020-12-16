#include "Shield.h"

namespace TP3Prog
{
	Shield::Shield(DamageableType shieldType) : Damageable(DEFAULT_SHIELD_HEALTH, shieldType)
	{
		shieldCircle.setRadius(60);

		sf::Color shieldColor;

		switch (shieldType)
		{
		case Blue: 
			shieldColor = sf::Color::Blue;
			break;
		case Red:
			shieldColor = sf::Color::Red;
			break;
		case Green: 
			shieldColor = sf::Color::Green;
			break;
		default: ;
		}

		shieldCircle.setOutlineColor(shieldColor);
		shieldCircle.setFillColor(sf::Color(shieldColor.r, shieldColor.g, shieldColor.b, 255 * 0.3f));
		shieldCircle.setOrigin(shieldCircle.getRadius(), shieldCircle.getRadius());
	}

	Shield::~Shield() 
	{
	}

	void Shield::takeDamage(DamageableType damageElement, int damageTaken)
	{
		health -= damageTaken;
	}

	sf::CircleShape Shield::getShape(const sf::Vector2f position)
	{
		shieldCircle.setPosition(position);
		return shieldCircle;
	}
	void Shield::notify(Subject * subject)
	{
	}
}
