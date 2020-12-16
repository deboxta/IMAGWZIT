#include "Drone.h"
#include "EnemyHandler.h"


namespace TP3Prog
{
	Texture Drone::droneTexture;

	Drone::Drone(Player* player, EnemyHandler* enemyHandler) : Entity(Player::PLAYER_SPEED, Red, 30),
		playerInstance(player), enemyHandlerInstance(enemyHandler), frameCount(0)
	{
		setPosition(player->getPosition());
		activate();
		activationInterval = DRONE_ACTIVATION_DURATION;
	}


	Drone::~Drone()
	{
		delete intRects;
	}

	void Drone::update()
	{
		if(--activationInterval < 0)
		{
			deactivate();
		}

		if(playerInstance->getIsMoving())
		{
			TP3Algo::Queue<PlayerCommand>* commands = playerInstance->getPlayerCommands();

			if (commands->size() > PLAYER_COMMAND_DELAY)
			{
				move((*commands)[(commands->size() - 1) - PLAYER_COMMAND_DELAY].moveVector *
					static_cast<float>(playerInstance->getSpeed()));
			}
		}

		Enemy* closestEnemy = nullptr;
		float closestDistance = std::numeric_limits<float>::max();
		Vector2f closestEnemyDelta = { 0,0 };

		for (Enemy& enemy : *enemyHandlerInstance->getEnemyList())
		{
			Vector2f enemyDelta = enemy.getPosition() - getPosition();
			float enemyDist = sqrt(enemyDelta.x * enemyDelta.x + enemyDelta.y * enemyDelta.y);

			if (enemyDist < DRONE_RANGE && enemyDist < closestDistance)
			{
				closestEnemy = &enemy;
				closestEnemyDelta = enemyDelta;
				closestDistance = enemyDist;
			}
		}


		if (closestEnemy != nullptr)
		{
			alignToDelta(closestEnemyDelta);

			if(droneWeapon.getCurrentShootInterval() <= 0)
				droneWeapon.shoot(*this);
		}

		droneWeapon.updateSelfAndProjectiles(enemyHandlerInstance);
	}

	void Drone::notify(Subject* subject)
	{

	}

	bool Drone::loadTexture(std::string texturePath)
	{
		if (!droneTexture.loadFromFile(texturePath))
		{
			return false;
		}

		return true;
	}

	void Drone::drawDrone(RenderWindow* renderWindow)
	{
		setTextureRect(intRects[++frameCount / ANIM_REFRESH_RATE % 2]);
		renderWindow->draw(*this);
		droneWeapon.drawProjectiles(renderWindow);
	}

	void Drone::visualAdjustments()
	{
		setTexture(droneTexture);
		setOrigin(ANIM_RECT_SIZE / 2, ANIM_RECT_SIZE / 2);
		intRects = new IntRect[ANIM_SIZE];

		for (int i = 0; i < ANIM_SIZE; ++i)
		{
			intRects[i].left = ANIM_RECT_SIZE * i;
			intRects[i].width = ANIM_RECT_SIZE;

			intRects[i].top = 0;
			intRects[i].height = ANIM_RECT_SIZE;
		}
	}

	CollisionCircle Drone::getCollider() const
	{
		return CollisionCircle(DRONE_RADIUS, getPosition().x, getPosition().y);
	}
}
