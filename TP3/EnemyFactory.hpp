#pragma once
#include "Crawler.h"
#include "SwarmQueen.h"
#include "Phaser.h"
#include "Follower.h"
#include "Watcher.h"
#include "Swarmling.h"
#include "Guardian.h"


namespace TP3Prog
{
	class EnemyFactory
	{
	public:
		enum EnemyType
		{
			CRAWLER,  //Crawler...
			SWARMER, //SwarmQueen
			SWARMLING, //Swarmling
			PHASER, //Ennemi qui se téléporte
			FOLLOWER, //Support
			WATCHER, //Ranged Berserker
			GUARDIAN //Tank
		};
		static Enemy* createEnemy(EnemyType enemy)
		{
			if (enemy == CRAWLER)
			{
				return new Crawler();
			}
			else if (enemy == SWARMER)
			{
				SwarmQueen* swarmQueen = new SwarmQueen(Damageable::DamageableType::None);
				swarmQueen->visualAdjustements();
				return swarmQueen;
			}
			else if (enemy == PHASER)
			{
				Phaser* phaser = new Phaser();
				phaser->visualAdjustments();
				return phaser;
			}
			else if(enemy == FOLLOWER)
			{
				Follower* follower = new Follower();
				follower->visualAdjustments();
				return follower;
			}
			else if(enemy == WATCHER)
			{
				Watcher* watcher = new Watcher();
				watcher->visualAdjustments();
				return watcher;
			}
			else if (enemy == SWARMLING)
			{
				Swarmling* swarmling = new Swarmling(Damageable::DamageableType::Red);
				return swarmling;
			}
			else if (enemy == GUARDIAN)
			{
				Guardian* guardian = new Guardian(Damageable::DamageableType::Blue);
				guardian->visualAdjustements();
				return guardian;
				
			}
		}
	private:
		EnemyFactory();
	};
}
