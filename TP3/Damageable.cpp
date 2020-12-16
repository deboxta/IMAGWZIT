#include "Damageable.h"
#include <utility>

namespace TP3Prog
{
	Damageable::Damageable(int initialHealth, DamageableType damageableType = None) : type(damageableType), maxHealth(initialHealth), health(initialHealth)
	{
	}

	Damageable::~Damageable()
	{
	}

	void Damageable::takeDamage(DamageableType damageElement, int damageTaken)
	{
		health -= damageTaken;
	}

	void Damageable::heal(int amount)
	{
		health = std::_Min_value(health + amount, maxHealth);
	}

	Damageable::DamageableType Damageable::getDamageElement() const
	{
		return type;
	}

	int Damageable::getHealth() const
	{
		return health;
	}
}
