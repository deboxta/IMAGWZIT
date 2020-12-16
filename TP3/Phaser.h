#pragma once
#include "Enemy.h"

namespace TP3Prog
{
	class Phaser : public Enemy
	{
	public:

		enum PhaserAnimationStates
		{
			IDLE = 0,
			TELEPORTING_IN = 1,
			TELEPORTING_OUT = 2,
			ATTACKING = 3,
		};

		Phaser();
		~Phaser();

		void visualAdjustments();

		static bool loadTexture(const std::string texturePath);

		bool findTeleportLocation(Player* player);
		void update(Player* player, EnemyHandler* enemyHandler) override;
		void handleAnimationAndAttackSprite();
		void transitionTo(PhaserAnimationStates newAnimationState);
		
		void drawEnemy(RenderWindow* renderWindow) override;
		FloatRect getBoxCollider();
		FloatRect getBoxCollider(Vector2f fromPosition);
	private:
		static sf::Texture phaserTexture;

		static const int ANIM_COUNT = 3;

		static const int ANIM_SIZES[ANIM_COUNT];
		static const int ANIM_REFRESH_RATES[ANIM_COUNT];

		static const int ANIMRECT_SIZE_X = 21 * 3;
		static const int ANIMRECT_SIZE_Y = 26 * 3;

		IntRect** intRects;
		IntRect* currentIntRect;

		int frameCount = 0;
		int attackFrameCount = 0;

		EnemyStates currentState;
		PhaserAnimationStates currentAnimationState;

		static const float TELEPORT_IN_DISTANCE;
		Vector2f teleportLocation;
		
		int currentTeleportCooldown;
		static const int DEFAULT_TELEPORT_COOLDOWN = 480;

		Sprite attackSprite;
		static const int ATTACK_RANGE = 80;
		static const int PHASER_ATTACK_DAMAGE = 4;
		static const int PHASER_SPEED = 2;
		static const int PHASER_HEALTH = 20;

		int animFrameIndex = 0;
		int animLayer = 0;
		bool forward = true;
	};
}