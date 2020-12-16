#pragma once
#include "Enemy.h"

namespace TP3Prog
{
	class EnemyFactory;
	class SwarmQueen : public Enemy
	{
	public:
		SwarmQueen();
		SwarmQueen(DamageableType type);
		~SwarmQueen();

		void update(Player* player, EnemyHandler* enemyHandler);

		void visualAdjustements();
		void animate();
		static bool loadTexture(const std::string& texturePath);
		FloatRect getBoxCollider() override;
		FloatRect getBoxCollider(Vector2f fromPosition) override;
	private:

		static const int RECTANGLE_SIZE = 64;
		static const int MAX_SWARMLINGS = 10;
		static const int SWARMQUEEN_SPEED = 4;
		static const int SWARMQUEEN_HEALTH = 6;

		EnemyStates currentState;

		static Texture swarmQueenTexture;

		int DistanceRadius = radius + 400;
		int normalRadius = RECTANGLE_SIZE / 2;
		int frameCount = 0;
		int swarlingCount = 0;

		IntRect** intRectsAnims;

		const int NBR_OF_LEVELS = 3; 
		const int NBR_OF_ANIMS = 3; 

		int animator = 0;
		const int animationSpeed = 8;

		static const int SWARMQUEEN_ATTACK_DAMAGE = 3;

		bool attackDone = false;
	};
}