#pragma once
#include "Projectile.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include "Player.h"


namespace TP3Prog
{

	class GameScreen;

	class EnemyHandler;

	class Weapon
	{
	public:
		virtual ~Weapon();

		WeaponType getWeaponType() const;
		Projectile& operator[](int x) const;

		void updateSelfAndProjectiles(EnemyHandler* enemyHandler);
		void drawProjectiles(sf::RenderWindow* renderWindow) const;
		
		void addAmmo(int ammoAdded);
		int getAmmo() const;		

		virtual void shoot(Entity& entity);

		int getCurrentShootInterval() const;
		int getRequiredAmmo() const;

		static const int PICKABLE_WEAPON_COUNT = 6;

	protected:
		static const int DEFAULT_SHOOT_INTERVAL = 6;

		Weapon(int maxProjectileCount, int shootInterval, WeaponType weaponType = DEFAULT, 
			int requiredAmmo = 1, bool fromPlayer = true);

		Projectile* projectiles;
		
		/// <summary>
		/// The shoot interval (in frames)
		/// for the selected weapon.
		/// </summary>
		const int shootInterval;

		/// <summary>
		/// The current shoot interval (in frames)
		/// Once it hits 0, it gets reset in update()
		/// by the shootInterval integer.
		/// </summary>
		int currentShootInterval = 0;

		const WeaponType weaponType;

		const int requiredAmmo = 0;
		int ammoCount = 0;
	
		const int maxProjectileCount = 0;

		const bool fromPlayer;
	};

}
