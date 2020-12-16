#include "EnemyHandler.h"
#include "../TP3Algo/ContainerFactory.hpp"
#include "GameScreen.h"
#include "Exit.h"


namespace TP3Prog
{
	EnemyHandler::EnemyHandler(Player* playerInstance, GameScreen* gameInstance, Exit* exit) : 
	enemies(TP3Algo::ContainerFactory<Enemy>::getCircularDoubleLinkedList()),
	obstacles(TP3Algo::ContainerFactory<Obstacle>::getCircularDoubleLinkedList()),
	playerInstance(playerInstance), gameInstance(gameInstance), exitInstance(exit)
	{
	}


	EnemyHandler::~EnemyHandler()
	{
		for (Enemy& enemy : *enemies)
		{
			delete &enemy;
		}
		delete enemies;

		delete enemyToSpawn;

		if (currentSquadron != nullptr)
		{
			unloadCurrentSquadron();
		}

		for (Obstacle& obstacle : *obstacles)
		{
			delete &obstacle;
		}

		delete obstacles;
	}

	void EnemyHandler::update()
	{
		if (currentSquadron != nullptr)
		{
			if (!currentSquadron->isEmpty())
			{
				handleSpawning();
			}
			else
			{
				delete currentSquadron;
				currentSquadron = nullptr;
			}
		}
		else if (enemies->isEmpty())
		{
			currentSquadron = gameInstance->getNextSquadron();
			if(currentSquadron == nullptr)
			{
				gameInstance->unlockExit();
			}
		}

		std::vector<CircularDoubleLinkedList<Enemy>::iterator> enemiesToRemove;
		for (auto enemy = enemies->begin(); enemy != enemies->end(); ++enemy)
		{
			if ((*enemy).getHealth() == 0)
			{
				enemiesToRemove.push_back(CircularDoubleLinkedList<Enemy>::iterator(enemy));
			}
			else
			{
				(*enemy).update(playerInstance, this);
			}
		}
		for (auto i : enemiesToRemove)
		{
			manageEnemyDeath(i, (*i).getPosition());
		}
	}

	void EnemyHandler::drawEnemies(sf::RenderWindow* renderWindow) const
	{
		for (Enemy& enemy : *enemies)
		{
			enemy.drawEnemy(renderWindow);
		}
	}

	void EnemyHandler::drawObstacles(RenderWindow* renderWindow) const
	{
		for (Obstacle obstacle : *obstacles)
		{
			renderWindow->draw(obstacle);
		}
	}

	void EnemyHandler::removeEnemy(CircularDoubleLinkedList<Enemy>::iterator enemyToDelete) const
	{
		Enemy* cellHolder = &*enemyToDelete;
		enemies->remove(enemyToDelete);
		delete cellHolder;
	}

	void EnemyHandler::addEnemySquadron(TP3Algo::Queue<Enemy>* newSquadron)
	{
		currentSquadron = newSquadron;
	}

	void EnemyHandler::unloadCurrentSquadron() const
	{
		Enemy* enemyToDelete = nullptr;
		while(!currentSquadron->isEmpty())
		{
			enemyToDelete = currentSquadron->dequeue();
			delete enemyToDelete;
		}

		delete currentSquadron;
	}

	void EnemyHandler::spawnObstacles()
	{
		static int MAX_SPAWNING_ATTEMPTS = 30;

		for (int i = 0; i < OBSTACLE_AMOUNT; ++i)
		{
			Vector2f spawnPosition;
			Vector2f randomSize;
			int nbAttempts = 0;
			bool canSpawn;
			Obstacle* obstacleAttempt = nullptr;

			do
			{
				canSpawn = true;
				spawnPosition = Vector2f(rand() % GameScreen::WORLD_WIDTH, 
					rand() % GameScreen::WORLD_HEIGHT);

				randomSize = Vector2f(Obstacle::OBSTACLE_SIZE / 1.5f + rand() % Obstacle::OBSTACLE_SIZE * 2,
					Obstacle::OBSTACLE_SIZE / 1.5f + rand() % Obstacle::OBSTACLE_SIZE * 2);
				
				obstacleAttempt = new Obstacle(spawnPosition, randomSize);

				for (Obstacle obstacle : *obstacles)
				{
					if(obstacle.getGlobalBounds().intersects(obstacleAttempt->getGlobalBounds()))
					{
						canSpawn = false;
						delete obstacleAttempt;
						break;
					}
				}

				if(obstacleAttempt->getGlobalBounds().intersects(exitInstance->getGlobalBounds()))
				{
					canSpawn = false;
					delete obstacleAttempt;
					continue;
				}

				if(obstacleAttempt->getGlobalBounds().intersects(playerInstance->getGlobalBounds()))
				{
					canSpawn = false;
					delete obstacleAttempt;
				}

			} while (!canSpawn && ++nbAttempts <= MAX_SPAWNING_ATTEMPTS);

			if(nbAttempts > MAX_SPAWNING_ATTEMPTS)
			{
				continue;
			}
			else
			{
				obstacles->addEnd(obstacleAttempt);
			}
		}
	}

	void EnemyHandler::clearObstacles() const
	{
		while (!obstacles->isEmpty())
		{
			auto i = obstacles->begin();
			delete &*i;
			obstacles->removeStart();
		}
	}

	CircularDoubleLinkedList<Enemy>* EnemyHandler::getEnemyList() const
	{
		return enemies;
	}

	CircularDoubleLinkedList<Obstacle>* EnemyHandler::getObstacleList() const
	{
		return obstacles;
	}

	void EnemyHandler::manageEnemyDeath(const CircularDoubleLinkedList<Enemy>::iterator& enemyIterator, Vector2f enemyPosition) const
	{
		removeEnemy(enemyIterator);
		gameInstance->manageEnemyDeath(enemyPosition);
	}

	Player* EnemyHandler::getPlayer() const
	{
		return playerInstance;
	}

	void EnemyHandler::handleSpawning()
	{
		static const int MAX_SPAWNING_ATTEMPTS = 30;


		if (spawnFrameCount <= 0)
		{
			spawnFrameCount = spawnInterval;

			//Assigns a random color to the enemy, for the moment.

			if (enemyToSpawn == nullptr)
			{
				enemyToSpawn = currentSquadron->dequeue();
			}

			sf::Vector2f spawnPosition;
			int nbAttempts = 0;
			bool canSpawn;

			do
			{
				canSpawn = true;
				spawnPosition = sf::Vector2f(rand() % GameScreen::WORLD_WIDTH, rand() % GameScreen::WORLD_HEIGHT);
				enemyToSpawn->setPosition(spawnPosition);

				CollisionCircle collider = enemyToSpawn->getCollider();
				FloatRect boxCollider = enemyToSpawn->getBoxCollider();

				if (abs(spawnPosition.x - playerInstance->getPosition().x) + abs(spawnPosition.y - playerInstance->getPosition().y) < 750)
				{
					canSpawn = false;
					continue;
				}

				for (Enemy& enemy : *enemies)
				{
					if (collider.checkCollision(enemy.getCollider()))
					{
						canSpawn = false;
						break;
					}
				}

				for (Obstacle& i : *obstacles)
				{
					if (boxCollider.intersects(i.getGlobalBounds()))
					{
						canSpawn = false;
						break;
					}
				}

			} while (!canSpawn && ++nbAttempts <= MAX_SPAWNING_ATTEMPTS);

			if (nbAttempts > MAX_SPAWNING_ATTEMPTS)
			{
				return;
			}
			else
			{
				enemyToSpawn->activate();
				
				enemies->addEnd(enemyToSpawn);

				//Enemy has been placed, we can now create another one.
				enemyToSpawn = nullptr;
			}
		}
		spawnFrameCount--;
	}
}
