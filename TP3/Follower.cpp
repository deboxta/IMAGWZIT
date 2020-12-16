#include "Follower.h"
#include "FollowerWeapon.h"
#include <random>

namespace TP3Prog
{
	Texture Follower::followerTexture;

	const Color Follower::AURA_COLOR = Color(0, 255, 0, 70);

	Follower::Follower() : healingAura(HEALING_AURA_RADIUS), intRects(nullptr), currentIntRect(nullptr),
		Enemy(Red, FOLLOWER_SPEED, FOLLOWER_HEALTH)
	{
		healingAura.setFillColor(AURA_COLOR);
		healingAura.setOrigin(HEALING_AURA_RADIUS, HEALING_AURA_RADIUS);
		frameCount = 0;
		animFrameIndex = 0;
	}

	Follower::~Follower()
	{
		delete[] intRects;
	}

	void Follower::visualAdjustments()
	{
		setTexture(followerTexture);
		setOrigin(ANIMRECT_SIZE_X / 2, ANIMRECT_SIZE_Y / 2);

		intRects = new IntRect[ANIM_SIZE];

		for (int i = 0; i < ANIM_SIZE; ++i)
		{
			intRects[i].left = 0;
			intRects[i].width = ANIMRECT_SIZE_X;

			intRects[i].top = ANIMRECT_SIZE_Y * i;
			intRects[i].height = ANIMRECT_SIZE_Y;
		}
	}

	bool Follower::loadTexture(const std::string texturePath)
	{
		if (!followerTexture.loadFromFile(texturePath))
		{
			return false;
		}

		return true;
	}

	void Follower::handleAnimation()
	{
		if (frameCount <= 0)
		{
			forward = true;
		}

		if (forward)
		{
			animFrameIndex = frameCount++ / ANIM_REFRESH_RATE;
		}
		else
		{
			animFrameIndex = --frameCount / ANIM_REFRESH_RATE;
		}

		if (frameCount <= 0 || frameCount / ANIM_REFRESH_RATE >=
			ANIM_SIZE)
		{
			forward = !forward;
		}


		currentIntRect = &intRects[animFrameIndex]; //set to default for now.
		setTextureRect(*currentIntRect);
	}

	void Follower::update(Player* player, EnemyHandler* enemyHandler)
	{
		Enemy::update(player, enemyHandler);
		if (!isActive)
			return;

		CircularDoubleLinkedList<Enemy>* enemies = enemyHandler->getEnemyList();
		CircularDoubleLinkedList<Obstacle>* obstacles = enemyHandler->getObstacleList();
		
		Vector2f targetPosition = player->getPosition();
		Vector2f playerDelta = targetPosition - getPosition();

		float distance = sqrt(playerDelta.x * playerDelta.x + playerDelta.y * playerDelta.y);
		alignToDelta(playerDelta);

		Enemy* closestEnemy = nullptr;
		float closestDistance = std::numeric_limits<float>::max();
		Vector2f closestEnemyDelta = {0,0};

		for (Enemy& enemy : *enemies)
		{
			if(&enemy == this)
			{
				continue;
			}

			Vector2f enemyDelta = enemy.getPosition() - getPosition();
			float enemyDist = sqrt(enemyDelta.x * enemyDelta.x + enemyDelta.y * enemyDelta.y);
			
			if(enemyDist > HEALING_AURA_RADIUS && enemyDist < closestDistance)
			{
				closestEnemy = &enemy;
				closestEnemyDelta = enemyDelta;
				closestDistance = enemyDist;
			}
		}


		if(closestEnemy != nullptr && closestDistance > HEALING_AURA_RADIUS - 50)
		{
			float angle = atan2(closestEnemyDelta.y, closestEnemyDelta.x) * 180 / std::_Pi;

			Vector2f projectedPosition = getPosition() + Vector2f(std::cos(angle * std::_Pi / 180) * speed,
				std::sin(angle * std::_Pi / 180) * speed);

			CollisionCircle projectedCollider = 
				CollisionCircle(FOLLOWER_RADIUS, projectedPosition.x, projectedPosition.y);
		
			bool canMove = true;

			for (Enemy& i : *enemies)
			{
				if (&i == this)
				{
					continue;
				}

				if (projectedCollider.checkCollision(i.getCollider()))
				{
					canMove = false;
					break;
				}
			}

			for (Obstacle& i : *obstacles)
			{
				if (getBoxCollider(projectedPosition).intersects(i.getGlobalBounds()))
				{
					canMove = false;
					break;
				}
			}

			if(canMove)
			{
				setPosition(projectedPosition);
			}
		}

		if(followerWeapon.getCurrentShootInterval() <= 0 && distance <= FOLLOWER_SHOOTING_RANGE)
		{
			followerWeapon.shoot(*this);
		}

		if(healCooldown > 0)
		{
			--healCooldown;
		}
		else
		{
			notifyAllObservers();
			healCooldown = HEAL_COOLDOWN;
		}

		followerWeapon.updateSelfAndProjectiles(enemyHandler);

		healingAura.setPosition(getPosition());

		handleAnimation();
	}

	void Follower::drawEnemy(RenderWindow* renderWindow)
	{
		renderWindow->draw(healingAura);
		
		Enemy::drawEnemy(renderWindow);

		followerWeapon.drawProjectiles(renderWindow);
	}

	CollisionCircle Follower::getCollider() const
	{
		return CollisionCircle(FOLLOWER_RADIUS, getPosition().x, getPosition().y);
	}

	FloatRect Follower::getBoxCollider()
	{
		return FloatRect(getPosition() - getOrigin(), { FOLLOWER_RADIUS * 2, FOLLOWER_RADIUS * 2 });
	}

	FloatRect Follower::getBoxCollider(Vector2f fromPosition)
	{
		return FloatRect(fromPosition - getOrigin(), { FOLLOWER_RADIUS * 2, FOLLOWER_RADIUS * 2 });
	}
}
