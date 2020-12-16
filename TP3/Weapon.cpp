#include "Weapon.h"
#include "Game.h"
#include <xtgmath.h>
#include "EnemyHandler.h"

namespace TP3Prog
{
	Weapon::~Weapon()
	{
		delete[] projectiles;
	}

	/// <summary>
	/// Protected constructor used for a specific weapon.
	/// </summary>
	/// <param name="maxProjectileCount"></param>
	Weapon::Weapon(int maxProjectileCount, int shootInterval, WeaponType weaponType,
		int requiredAmmo, bool fromPlayer) :
		maxProjectileCount(maxProjectileCount), fromPlayer(fromPlayer),
		weaponType(weaponType), shootInterval(shootInterval), requiredAmmo(requiredAmmo)
	{
	}

	void Weapon::shoot(Entity& entity)
	{
		for (int i = 0; i < maxProjectileCount; ++i)
		{
			if (!projectiles[i].getIsActive())
			{
				projectiles[i].initialise(entity.getPosition(), entity.getRotation());
				break;
			}
		}

		currentShootInterval = shootInterval;

		--ammoCount;
	}

	int Weapon::getCurrentShootInterval() const
	{
		return currentShootInterval;
	}

	int Weapon::getRequiredAmmo() const
	{
		return requiredAmmo;
	}

	void Weapon::updateSelfAndProjectiles(EnemyHandler* enemyHandler)
	{
		std::vector<CircularDoubleLinkedList<Enemy>::iterator> enemiesToRemove;
		CircularDoubleLinkedList<Enemy>* enemies = enemyHandler->getEnemyList();

		if (currentShootInterval > 0)
		{
			--currentShootInterval;
		}

		for (int i = 0; i < maxProjectileCount; ++i)
		{
			if (projectiles[i].getIsActive())
			{
				projectiles[i].update();

				if (fromPlayer)
				{
					for (auto enemy = enemies->begin(); enemy != enemies->end(); ++enemy)
					{
						if ((*enemy).getIsActive() && projectiles[i].getGlobalBounds().intersects((*enemy).getGlobalBounds()))
						{
							(*enemy).takeDamage(projectiles[i].getDamageElement(), projectiles[i].getDamage());

							if((*enemy).getHealth() <= 0)
							{
								//We have to check if the enemy is already queued up for deletion.
								bool enemyToBeRemoved = false;
								for (auto enemyToRemove : enemiesToRemove)
								{
									if(&(*enemyToRemove) == &(*enemy))
									{
										enemyToBeRemoved = true;
										break;
									}
								}

								if (!enemyToBeRemoved)
								{
									enemiesToRemove.push_back(CircularDoubleLinkedList<Enemy>::iterator(enemy));
								}
							}							

							if (!projectiles[i].getIsInvulnerable())
							{
								projectiles[i].deactivate();
								break;
							}
						}
					}
				}
				else
				{
					if(enemyHandler->getPlayer()->getCollisionBox().intersects(projectiles[i].getGlobalBounds()))
					{
						enemyHandler->getPlayer()->takeDamage(projectiles[i].getDamageElement(),
							projectiles[i].getDamage());

						if (!projectiles[i].getIsInvulnerable())
						{
							projectiles[i].deactivate();
						}
					}

					
				}

				for (Obstacle obstacle : *enemyHandler->getObstacleList())
				{
					if (projectiles[i].getGlobalBounds().intersects(obstacle.getGlobalBounds()))
					{
						if (!projectiles[i].getIsInvulnerable())
						{
							projectiles[i].deactivate();
							break;
						}
					}
				}
			}
		}

		for(auto &i : enemiesToRemove)
		{
			enemyHandler->manageEnemyDeath(i, (*i).getPosition());
		}
	}

	Projectile& Weapon::operator[](int x) const
	{
		return projectiles[x];
	}

	void Weapon::drawProjectiles(sf::RenderWindow* renderWindow) const
	{
		for (int i = 0; i < maxProjectileCount; ++i)
		{
			if (projectiles[i].getIsActive())
			{
				renderWindow->draw(projectiles[i]);
			}
		}
	}

	void Weapon::addAmmo(int ammoAdded)
	{
		ammoCount += ammoAdded;
	}

	int Weapon::getAmmo() const
	{
		return ammoCount;
	}

	WeaponType Weapon::getWeaponType() const
	{
		return weaponType;
	}
}
