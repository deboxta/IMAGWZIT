#pragma once
#include "Entity.h"
#include "Handgun.h"

namespace TP3Prog
{
	class Player;

	class EnemyHandler;

	class Drone :
		public Entity
	{
	public:
		Drone(Player* player, EnemyHandler* enemyHandler);
		~Drone();
		void update();
		void notify(Subject* subject) override;

		static bool loadTexture(std::string texturePath);

		void drawDrone(RenderWindow* renderWindow);
		void visualAdjustments();
		
		CollisionCircle getCollider() const override;

	private:
		static const int DRONE_ACTIVATION_DURATION = 7200;
		int activationInterval = 0;

		int PLAYER_COMMAND_DELAY = 7;
		static const int DRONE_RADIUS = 35;
		static const int DRONE_RANGE = 800;
		static Texture droneTexture;


		IntRect* intRects;
		int frameCount;
		static const int ANIM_SIZE = 2;
		static const int ANIM_RECT_SIZE = 64;
		static const int ANIM_REFRESH_RATE = 4;

		Handgun droneWeapon;

		Player* playerInstance = nullptr;
		EnemyHandler* enemyHandlerInstance;
	};
}

