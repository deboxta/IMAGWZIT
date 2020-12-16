#pragma once
#include "Enemy.h"

namespace TP3Prog
{
	class Guardian : public Enemy
	{
	public:
		Guardian();
		Guardian(DamageableType type);
		~Guardian();

		void update(Player* player, EnemyHandler* enemyHandler);
		static bool loadTexture(std::string texturePath);
		void visualAdjustements();
	private:
		static const int RECTANGLE_SIZE = 128;
		static const int GUARDIAN_SPEED = 4;
		static const int GUARDIAN_HEALTH = 20;

		EnemyStates currentState;
		static Texture swarmlingTexture;

		int frameCount = 0;
		int DistanceRadius = radius + 150;
		int normalRadius = RECTANGLE_SIZE / 2;
		int speedAdjustement = 0;

		bool attackDone = false;

		IntRect** intRectsAnims;

		const int NBR_OF_LEVELS = 3;
		const int NBR_OF_ANIMS = 3;

		int animator = 0;
		const int animationSpeed = 8;

		void animate();
		FloatRect getBoxCollider();
		FloatRect getBoxCollider(Vector2f fromPosition);

		static const int GUARDIAN_ATTACK_DAMAGE = 3;
	};
}