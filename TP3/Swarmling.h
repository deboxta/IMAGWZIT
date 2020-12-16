#pragma once
#include "Enemy.h"
#include "SwarmQueen.h"

namespace TP3Prog
{
	class Swarmling : public Enemy
	{
	public:
		Swarmling();
		Swarmling(DamageableType type);
		~Swarmling();
		
		void update(Player* player, EnemyHandler* enemyHandler);
		static bool loadTexture(std::string texturePath);
		FloatRect getBoxCollider() override;
		FloatRect getBoxCollider(Vector2f fromPosition);
	private:
		static const int SWARMLING_SPEED = 6;
		static const int SWARMLING_HEALTH = 1;
		EnemyStates currentState;
		static Texture swarmlingTexture;

		static const int SWARLING_ATTACK_DAMAGE = 1;
	};
}

