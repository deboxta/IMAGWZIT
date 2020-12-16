#pragma once
#include "Watcher.h"
#include "EnemyFactory.hpp"
#include <random>

namespace TP3Prog
{
	Texture Watcher::watcherTexture;

	const int Watcher::ANIM_SIZES[ANIM_COUNT] =
	{
		6,
		5,
	};

	Watcher::Watcher(): intRects(nullptr), currentIntRect(nullptr), 
	currentAnimationState(IDLE)	, Enemy(Green, WATCHER_SPEED, WATCHER_HEALTH)
	{

	}

	Watcher::~Watcher()
	{
		for (int i = 0; i < ANIM_COUNT; ++i)
		{
			delete[] intRects[i];
		}

		delete[] intRects;
	}

	void Watcher::visualAdjustments()
	{
		setTexture(watcherTexture);

		setOrigin(ORIGIN_X, ORIGIN_Y);

		//For each direction. We initialise an array of frames.
		intRects = new IntRect*[ANIM_COUNT];

		for (int i = 0; i < ANIM_COUNT; ++i)
		{
			intRects[i] = new IntRect[ANIM_SIZES[i]];
			for (int j = 0; j < ANIM_SIZES[i]; ++j)
			{
				intRects[i][j].left = ANIMRECT_SIZE_X * j;
				intRects[i][j].width = ANIMRECT_SIZE_X;

				intRects[i][j].top = ANIMRECT_SIZE_Y * i;
				intRects[i][j].height = ANIMRECT_SIZE_Y;
			}
		}

		currentAnimationState = IDLE;
	}

	bool Watcher::loadTexture(const std::string texturePath)
	{
		if (!watcherTexture.loadFromFile(texturePath))
		{
			return false;
		}

		return true;
	}

	void Watcher::update(Player* player, EnemyHandler* enemyHandler)
	{
		Enemy::update(player, enemyHandler);
		if (!isActive)
			return;

		Vector2f targetPosition = player->getPosition();
		Vector2f delta = targetPosition - getPosition();

		float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
		alignToDelta(delta);


		if(distance < ATTACK_RANGE)
		{
			if (currentAnimationState != ATTACKING)
			{
				currentAnimationState = ATTACKING;
				frameCount = 0;
			}

			if(attackFrameCount == ANIM_SIZES[ATTACKING] / 2 * attackAnimRefreshRate)
			{
				watcherWeapon.shoot(*this);
				attackFrameCount = 0;
			}
		}
		else
		{
			if (currentAnimationState != IDLE)
			{
				currentAnimationState = IDLE;
				frameCount = 0;
			}

			const Vector2f projectedPosition = getPosition() + Vector2f(std::cos(getRotation() * std::_Pi / 180) * speed,
				std::sin(getRotation() * std::_Pi / 180) * speed);

			CollisionCircle projectedCollider =
				CollisionCircle(WATCHER_RADIUS, projectedPosition.x, projectedPosition.y);

			bool canMove = true;

			for (Enemy& i : *enemyHandler->getEnemyList())
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

			for (Obstacle& i : *enemyHandler->getObstacleList())
			{
				if (getBoxCollider(projectedPosition).intersects(i.getGlobalBounds()))
				{
					canMove = false;
					break;
				}
			}

			if (canMove)
			{
				setPosition(projectedPosition);
			}
		}

		watcherWeapon.updateSelfAndProjectiles(enemyHandler);
		handleAnimation();
	}

	void Watcher::handleAnimation()
	{
		if (currentAnimationState == IDLE)
		{
			animLayer = 1;

			if (frameCount <= 0)
			{
				forward = true;
			}

			if (forward)
			{
				animFrameIndex = frameCount++ / ANIM_DEFAULT_REFRESH_RATE;
			}
			else
			{
				animFrameIndex = --frameCount / ANIM_DEFAULT_REFRESH_RATE;
			}

			if (frameCount <= 0 || frameCount / ANIM_DEFAULT_REFRESH_RATE >=
				ANIM_SIZES[animLayer])
			{
				forward = !forward;
			}
		}
		else
		{
			animLayer = 0;
			animFrameIndex = (frameCount++ / attackAnimRefreshRate) % ANIM_SIZES[animLayer];
			++attackFrameCount;
		}


		currentIntRect = &intRects[animLayer][animFrameIndex];
		setTextureRect(*currentIntRect);
	}

	CollisionCircle Watcher::getCollider() const
	{
		return CollisionCircle(WATCHER_RADIUS, getPosition().x, getPosition().y);
	}

	void Watcher::drawEnemy(RenderWindow* renderWindow)
	{
		Enemy::drawEnemy(renderWindow);

		watcherWeapon.drawProjectiles(renderWindow);
	}

	void Watcher::takeDamage(DamageableType damageableType, int damageTaken)
	{
		Enemy::takeDamage(damageableType, damageTaken);
		attackAnimRefreshRate = ANIM_BASE_REFRESH_RATE +
			static_cast<float>(health) / static_cast<float>(maxHealth) * static_cast<float>(ANIM_DEFAULT_REFRESH_RATE);
		attackFrameCount = 0;
	}

	void Watcher::heal(int amount)
	{
		Enemy::heal(amount);
		attackAnimRefreshRate = ANIM_BASE_REFRESH_RATE +
			static_cast<float>(health) / static_cast<float>(maxHealth) * static_cast<float>(ANIM_DEFAULT_REFRESH_RATE);
		//attackFrameCount = 0;
	}

	FloatRect Watcher::getBoxCollider()
	{
		return FloatRect(getPosition() - getOrigin(), { WATCHER_RADIUS * 2, WATCHER_RADIUS * 2 });
	}

	FloatRect Watcher::getBoxCollider(Vector2f fromPosition)
	{
		return FloatRect(fromPosition - getOrigin(), { WATCHER_RADIUS * 2, WATCHER_RADIUS * 2 });
	}
}
