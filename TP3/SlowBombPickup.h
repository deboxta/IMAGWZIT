#pragma once
#include "Pickup.h"
#include "Entity.h"
#include "Subject.h"
#include "Player.h"
#include "EnemyHandler.h"

using namespace sf;

namespace TP3Prog
{
	class SlowBombPickup : public Subject, public Pickup
	{
	public:
		SlowBombPickup(sf::Vector2f position, sf::Texture& pickupTexture, Entity::DamageableType type, EnemyHandler* enemyHandler, Player* player);
		~SlowBombPickup();

		Entity::DamageableType getBombType() const;

		static const int BOMB_RADIUS_EXPOSITION = 400;
	private:
		Entity::DamageableType type;

		Player* player;
		CircularDoubleLinkedList<Enemy>* enemies;

	};
}