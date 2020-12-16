#pragma once
#include "../TP3Algo/Queue.hpp"
#include "EnemyFactory.hpp"
#include "Swarmling.h"

namespace TP3Prog
{
	class EnemySquadronGenerator
	{
	public:
		EnemySquadronGenerator();
		~EnemySquadronGenerator();
		static TP3Algo::Queue<Enemy>* formSquadron(std::vector<EnemyType> enemyType);
		static TP3Algo::Queue<Enemy>* formSquadron(const unsigned int amount);
		static void init();

	private:

		static const std::string crawlerTexturePaths[Crawler::TEXTURE_AMOUNT];
		static const std::string swarmQueenTexturePath;
		static const std::string swarmlingTexturePath;
		static const std::string phaserTexturePath;
		static const std::string followerTexturePath;
		static const std::string watcherTexturePath;
		static const std::string guardianTexturePath;
	};
}

