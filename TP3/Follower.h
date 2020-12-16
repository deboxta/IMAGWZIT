#pragma once
#include "Enemy.h"
#include "Weapon.h"
#include "FollowerWeapon.h"
#include "EnemyHandler.h"
#include "Subject.h"

namespace TP3Prog
{
	class Follower : public Enemy, public Subject
	{
	public:

		Follower();
		~Follower();

		void visualAdjustments();

		static bool loadTexture(const std::string texturePath);

		void handleAnimation();
		void update(Player* player, EnemyHandler* enemyHandler) override;

		void drawEnemy(RenderWindow* renderWindow) override;

		CollisionCircle getCollider() const override;
		FloatRect getBoxCollider();
		FloatRect getBoxCollider(Vector2f fromPosition);
		static const int HEAL_AMOUNT = 2;
		static const int HEALING_AURA_RADIUS = 200;

	private:
		static sf::Texture followerTexture;
		static const Color AURA_COLOR;

		FollowerWeapon followerWeapon;

		CircleShape healingAura;
		static const int FOLLOWER_SHOOTING_RANGE = 700;

		static const int ANIMRECT_SIZE_X = 14 * 4;
		static const int ANIMRECT_SIZE_Y = 20 * 4;

		static const int ANIM_SIZE = 4;
		static const int ANIM_REFRESH_RATE = 4;

		IntRect* intRects = nullptr;
		IntRect* currentIntRect = nullptr;

		int frameCount = 0;
		int animFrameIndex = 0;
		bool forward = true;

		static const int ATTACK_RANGE = 80;
		static const int FOLLOWER_ATTACK_DAMAGE = 4;
		static const int FOLLOWER_SPEED = 2;
		static const int FOLLOWER_HEALTH = 10;
		static const int FOLLOWER_RADIUS = 16;
		static const int HEAL_COOLDOWN = 120;

		int healCooldown;
	};
}
