#pragma once
#include "Enemy.h"
#include "WatcherWeapon.h"

namespace TP3Prog
{

	class Watcher : public Enemy
	{
	public:

		enum WatcherAnimationStates
		{
			ATTACKING = 0,
			IDLE = 1,
		};

		Watcher();
		~Watcher();

		void visualAdjustments();

		static bool loadTexture(const std::string texturePath);

		void update(Player* player, EnemyHandler* enemyHandler) override;
		void handleAnimation();

		CollisionCircle getCollider() const override;
		void drawEnemy(RenderWindow* renderWindow) override;
		void takeDamage(DamageableType damageableType, int damageTaken) override;
		void heal(int amount) override;
		FloatRect getBoxCollider() override;
		FloatRect getBoxCollider(Vector2f fromPosition);
	private:
		static sf::Texture watcherTexture;

		static const int ANIM_COUNT = 2;

		static const int ANIM_SIZES[ANIM_COUNT];

		static const int ANIMRECT_SIZE_X = 17 * 4;
		static const int ANIMRECT_SIZE_Y = 22 * 4;
		static const int ORIGIN_X = 13 * 4;
		static const int ORIGIN_Y = ANIMRECT_SIZE_Y / 2;

		static const int ANIM_BASE_REFRESH_RATE = 4;
		static const int ANIM_DEFAULT_REFRESH_RATE = ANIM_BASE_REFRESH_RATE + 20;
		int attackAnimRefreshRate = ANIM_DEFAULT_REFRESH_RATE;

		IntRect** intRects;
		IntRect* currentIntRect;

		int frameCount = 0;
		int attackFrameCount = 0;

		WatcherAnimationStates currentAnimationState;

		static const int WATCHER_RADIUS = 17 * 4 / 2;
		static const int ATTACK_RANGE = 500;
		static const int WATCHER_ATTACK_DAMAGE = 4;
		static const int WATCHER_SPEED = 2;
		static const int WATCHER_HEALTH = 20;

		int animFrameIndex = 0;
		int animLayer = 0;
		bool forward = true;

		WatcherWeapon watcherWeapon;
	};
}
