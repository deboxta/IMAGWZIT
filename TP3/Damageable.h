#pragma once
#include "IObserver.h"
namespace TP3Prog 
{
	class Entity;

	class Damageable : public IObserver
	{
	public:
		/// <summary>
		/// The DamageableType is the type of the Damageable. (Strengths and Weaknesses).
		/// </summary>
		enum DamageableType
		{
			None = 0,
			Blue = 1,
			Red = 2,
			Green = 3
		};

		Damageable(int initialHealth, DamageableType damageableType);
		virtual ~Damageable();

		virtual void takeDamage(DamageableType damageableType, int damageTaken);
		virtual void heal(int amount);

		DamageableType getDamageElement() const;

		int getHealth() const;

	protected:
		DamageableType type;
		const int maxHealth;
		int health;
	};
}

