#pragma once
#include "../TP3Algo/CircularDoubleLinkedList.hpp"
#include "../TP3Algo/Queue.hpp"
#include "Enemy.h"
#include "Obstacle.h"
#include "Exit.h"


namespace TP3Prog
{
	class GameScreen;

	class EnemyHandler
	{
	public:
		EnemyHandler(Player* playerInstance, GameScreen* gameInstance, Exit* exit);
		~EnemyHandler();

		void update();
		void drawEnemies(sf::RenderWindow* renderWindow) const;
		void drawObstacles(RenderWindow* renderWindow) const;

		void removeEnemy(CircularDoubleLinkedList<Enemy>::iterator enemyToDelete) const;
		void addEnemySquadron(TP3Algo::Queue<Enemy>* newSquadron);
		void unloadCurrentSquadron() const;

		void spawnObstacles();
		void clearObstacles() const;

		CircularDoubleLinkedList<Enemy>* getEnemyList() const;
		CircularDoubleLinkedList<Obstacle>* getObstacleList() const;

		void manageEnemyDeath(const CircularDoubleLinkedList<Enemy>::iterator& enemyIterator, Vector2f enemyPosition) const;

		Player* getPlayer() const;

		static int const OBSTACLE_AMOUNT = 12;
	private:
		void handleSpawning();

		CircularDoubleLinkedList<Obstacle>* obstacles;

		CircularDoubleLinkedList<Enemy>* enemies;
		Enemy* enemyToSpawn = nullptr;

		/// <summary>
		/// When the Handler attempts to spawn an enemy,
		/// he might not be placed. This is why
		/// the instance is tracked in order to try again
		/// on the same instance.
		/// </summary>
		TP3Algo::Queue<Enemy>* currentSquadron = nullptr;

		Player* playerInstance;
		GameScreen* gameInstance;

		const int spawnInterval = 15;
		int spawnFrameCount = 0;

		Exit* exitInstance;

		static const int MAX_ENEMY_COUNT = 75;
	};
}