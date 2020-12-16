#include "EnemySquadronGenerator.h"
#include "../TP3Algo/ContainerFactory.hpp"


namespace TP3Prog
{
	const std::string EnemySquadronGenerator::crawlerTexturePaths[Crawler::TEXTURE_AMOUNT] = 
	{
			"Sprites\\Art\\Kid1.png",
			"Sprites\\Art\\Kid2.png",
			"Sprites\\Art\\Kid3.png"
	};

	const std::string EnemySquadronGenerator::swarmQueenTexturePath = "Sprites\\Art\\SwarmQueenSheet3.png";

	const std::string EnemySquadronGenerator::swarmlingTexturePath = "Sprites\\Art\\Swarmling.png";

	const std::string EnemySquadronGenerator::phaserTexturePath = "Sprites\\Art\\Phaser3x.png";

	const std::string EnemySquadronGenerator::followerTexturePath = "Sprites\\Art\\Follower4x.png";

	const std::string EnemySquadronGenerator::watcherTexturePath = "Sprites\\Art\\Watcher4x.png";

	const std::string EnemySquadronGenerator::guardianTexturePath = "Sprites\\Art\\GuardianSheet.png";

	EnemySquadronGenerator::EnemySquadronGenerator()
	{
	}


	EnemySquadronGenerator::~EnemySquadronGenerator()
	{
	}

	TP3Algo::Queue<Enemy>* EnemySquadronGenerator::formSquadron(std::vector<EnemyType> enemyTypes)
	{
		TP3Algo::Queue<Enemy>* squadron = TP3Algo::ContainerFactory<Enemy>::getQueue();

		for (EnemyType enemyType : enemyTypes)
		{
			switch (enemyType)
			{
			case CRAWLER:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::CRAWLER));
				break;
			case SWARMER:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::SWARMER));
				break;
			case PHASER:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::PHASER));
				break;
			case FOLLOWER:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::FOLLOWER));
				break;
			case WATCHER:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::WATCHER));
				break;
			case GUARDIAN:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::GUARDIAN));
				break;
			default: 
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::CRAWLER));
				break;
			}
		}

		return squadron;
	}

	TP3Algo::Queue<Enemy>* EnemySquadronGenerator::formSquadron(const unsigned int amount = 5)
	{
		TP3Algo::Queue<Enemy>* squadron = TP3Algo::ContainerFactory<Enemy>::getQueue();

		for (int i = 0; i < amount; ++i)
		{
			int enemyType = rand() % 6;

			switch (enemyType)
			{
			case CRAWLER:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::CRAWLER));
				break;
			case SWARMER:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::SWARMER));
				break;
			case PHASER:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::PHASER));
				break;
			case FOLLOWER:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::FOLLOWER));
				break;
			case WATCHER:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::WATCHER));
				break;
			case GUARDIAN:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::GUARDIAN));
				break;
			default:
				squadron->enqueue(EnemyFactory::createEnemy(EnemyFactory::CRAWLER));
				break;
			}
		}

		return squadron;
	}

	void EnemySquadronGenerator::init()
	{
		//load each textures.
		Crawler::loadTextures(crawlerTexturePaths);

		SwarmQueen::loadTexture(swarmQueenTexturePath);

		Swarmling::loadTexture(swarmlingTexturePath);

		Guardian::loadTexture(guardianTexturePath);

		Phaser::loadTexture(phaserTexturePath);

		Follower::loadTexture(followerTexturePath);

		Watcher::loadTexture(watcherTexturePath);

	}
}
