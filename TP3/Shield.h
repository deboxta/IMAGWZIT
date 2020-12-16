#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

namespace TP3Prog
{
	class Shield : public Damageable
	{
	public:
		Shield(DamageableType shieldType);
		~Shield();

		void takeDamage(DamageableType damageElement, int damageTaken) override;
		sf::CircleShape getShape(const sf::Vector2f position);

		static const int DEFAULT_SHIELD_HEALTH = 3;
		void notify(Subject* subject);
	private:
		sf::CircleShape shieldCircle;
		sf::Color shieldColor;
	};
}

