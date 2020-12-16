#pragma once
#include "Enemy.h"

namespace TP3Prog
{
	class Crawler : public Enemy
	{
	public:
		Crawler();
		Crawler(DamageableType type);
		~Crawler();

		void update(Player* player, EnemyHandler* enemyHandler);

		static int const TEXTURE_AMOUNT = 3;

		static bool loadTextures(const std::string texturePaths[3]);
		FloatRect getBoxCollider();
		FloatRect getBoxCollider(Vector2f fromPosition);
	private:
		static sf::Texture crawlerTextures[TEXTURE_AMOUNT];
		EnemyStates currentState;

		static const int CRAWLER_SIZE = 49;

		static const int CRAWLER_DAMAGE = 1;
		static const int CRAWLER_HEALTH = 5;
		static const int CRAWLER_SPEED = 3;
	};
}