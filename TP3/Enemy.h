#pragma once
#include "Entity.h"
#include "EnemyStates.h"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace TP3Prog
{
	class EnemyHandler;

	class Player;

	enum EnemyType
	{
		CRAWLER,
		SWARMER,
		PHASER,
		FOLLOWER,
		WATCHER,
		GUARDIAN
	};


	/// <summary>
	/// Class of an enemy that follows the player
	/// in the game.
	/// </summary>
	/// <seealso cref="Entity" />
	class Enemy :
		public Entity
	{
	public:

		Enemy();
		Enemy(DamageableType type, int speed, int initialHealth);
		~Enemy();

		virtual void update(Player* player, EnemyHandler* enemyHandler);
		virtual void drawEnemy(RenderWindow* renderWindow);

		static const int DEFAULT_HEALTH = 3;
		const int DEFAULT_SPEED = 3;
		static const int DEFAULT_ENEMY_DAMAGE = 2;

		CollisionCircle getCollider() const override;
		virtual FloatRect getBoxCollider() = 0;
		virtual FloatRect getBoxCollider(Vector2f fromPosition) = 0;
		void notify(Subject* subject) override;
	protected:
		int radius = 24;
	};
}

