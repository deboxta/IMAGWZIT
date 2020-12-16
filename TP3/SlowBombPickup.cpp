#include "SlowBombPickup.h"

namespace TP3Prog
{
	SlowBombPickup::SlowBombPickup(sf::Vector2f position, sf::Texture& pickupTexture, Entity::DamageableType type, EnemyHandler* enemyHandler, Player* player)
		: Pickup(position,WeaponType::None,pickupTexture,0) , player(player)
	{
		enemies = enemyHandler->getEnemyList();
		for (Enemy &i : *enemies)
		{
			addObserver(&i);
		}
		addObserver(player);
		this->type = type;
	}
	SlowBombPickup::~SlowBombPickup()
	{
		for (Enemy &i : *enemies)
		{
			removeObserver(&i);
		}
		removeObserver(player);
	}
	Entity::DamageableType SlowBombPickup::getBombType() const
	{
		return type;
	}
}