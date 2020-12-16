#pragma once
#include "Phaser.h"
#include <random>
#include "GameScreen.h"

namespace TP3Prog
{
	sf::Texture Phaser::phaserTexture;

	const float Phaser::TELEPORT_IN_DISTANCE = 375.0f;

	const int Phaser::ANIM_SIZES[ANIM_COUNT] =
	{
		5,
		4,
		6
	};

	const int Phaser::ANIM_REFRESH_RATES[ANIM_COUNT] = 
	{
		6,
		6,
		6,
	};

	Phaser::Phaser() : Enemy(Blue, PHASER_SPEED, PHASER_HEALTH), currentState(UNDEFINED), currentAnimationState(IDLE), currentTeleportCooldown(0)
	{
		this->isActive = false;
	}

	Phaser::~Phaser()
	{
		for (int i = 0; i < ANIM_COUNT; ++i)
		{
			delete[] intRects[i];
		}

		delete[] intRects;
	}

	void Phaser::visualAdjustments()
	{
		setTexture(phaserTexture);
		attackSprite.setTexture(phaserTexture);

		attackSprite.setOrigin(ANIMRECT_SIZE_X / 2, ANIMRECT_SIZE_Y / 2);
		setOrigin(ANIMRECT_SIZE_X / 2, ANIMRECT_SIZE_Y / 2);

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

	void Phaser::update(Player* player, EnemyHandler* enemyHandler)
	{
		Enemy::update(player, enemyHandler);
		if (!isActive)
			return;

		Vector2f targetPosition = player->getPosition();
		Vector2f delta = targetPosition - getPosition();

		float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
		alignToDelta(delta);

		switch (currentState)
		{
		case FOLLOWING:
			if (TELEPORT_IN_DISTANCE - distance > 0)
			{
				if (currentTeleportCooldown <= 0)
				{
					currentState = TELEPORT_IN;
					transitionTo(TELEPORTING_IN);
				}
				else if(TELEPORT_IN_DISTANCE - distance > 30)
				{
					move(std::cos((getRotation() + 180) * std::_Pi / 180) * speed,
					std::sin((getRotation() + 180) * std::_Pi / 180) * speed);
				}
			}
			else if(TELEPORT_IN_DISTANCE - distance <= 0)
			{
				move(std::cos(getRotation() * std::_Pi / 180) * speed,
					std::sin(getRotation() * std::_Pi / 180) * speed);
			}
			break;

		case ATTACK:
			if(attackSprite.getGlobalBounds().intersects(player->getCollisionBox()))
			{
				player->takeDamage(type, PHASER_ATTACK_DAMAGE);
			}

			if(attackFrameCount / ANIM_REFRESH_RATES[0] >= ANIM_SIZES[0])
			{
				transitionTo(IDLE);
				currentState = FOLLOWING;
			}
			break;

		case EnemyStates::IDLE:
			currentState = FOLLOWING;
			break;

		case TELEPORT_IN:
			if(currentAnimationState == TELEPORTING_IN && 
				frameCount / ANIM_REFRESH_RATES[2] >= ANIM_SIZES[2])
			{				
				if(findTeleportLocation(player))
				{
					transitionTo(TELEPORTING_OUT);
					setPosition(teleportLocation);
					currentTeleportCooldown = DEFAULT_TELEPORT_COOLDOWN;
				};
			}
			else if(currentAnimationState == TELEPORTING_OUT && frameCount <= 0)
			{
				currentState = ATTACK;
				transitionTo(ATTACKING);
			}
			break;

		case UNDEFINED:
			currentState = EnemyStates::IDLE;
			break;
		default:;
		}

		if(currentTeleportCooldown > 0)
		{
			--currentTeleportCooldown;
		}

		handleAnimationAndAttackSprite();
	}

	void Phaser::handleAnimationAndAttackSprite()
	{
		if(currentAnimationState == PhaserAnimationStates::IDLE || 
			currentAnimationState == PhaserAnimationStates::ATTACKING)
		{
			animLayer = 1;
			
			if(frameCount <= 0)
			{
				forward = true;
			}

			if (forward)
			{
				animFrameIndex = frameCount++ / ANIM_REFRESH_RATES[animLayer];
			}
			else
			{
				animFrameIndex = --frameCount / ANIM_REFRESH_RATES[animLayer];
			}
			
			if (frameCount <= 0 || frameCount / ANIM_REFRESH_RATES[animLayer] >=
				ANIM_SIZES[animLayer])
			{
				forward = !forward;
			}
		}
		else
		{
			bool forward = currentAnimationState == PhaserAnimationStates::TELEPORTING_IN;
			animLayer = 2;

			if (forward)
			{
				animFrameIndex = frameCount++ / ANIM_REFRESH_RATES[animLayer];
			}
			else
			{
				animFrameIndex = --frameCount / ANIM_REFRESH_RATES[animLayer];
			}
		}

		if(currentAnimationState == PhaserAnimationStates::ATTACKING)
		{
			IntRect* attackIntRect = &intRects[0][attackFrameCount++ / ANIM_REFRESH_RATES[0]];
			attackSprite.setTextureRect(*attackIntRect);

			Vector2f attackOffset = Vector2f(std::cos(getRotation() * std::_Pi / 180) * ATTACK_RANGE,
				std::sin(getRotation() * std::_Pi / 180) * ATTACK_RANGE);

			attackSprite.setPosition(getPosition() + attackOffset);
			attackSprite.setRotation(getRotation());
		}

		currentIntRect = &intRects[animLayer][animFrameIndex];

		setTextureRect(*currentIntRect);
	}

	void Phaser::transitionTo(PhaserAnimationStates newAnimationState)
	{
		currentAnimationState = newAnimationState;
		switch (newAnimationState) 
		{ 
		case IDLE:
			frameCount = 0;
			break;
		case TELEPORTING_IN:
			frameCount = 0;
			break;
		case TELEPORTING_OUT:
			break;
		case ATTACKING:
			frameCount = 0;
			attackFrameCount = 0;
			break;
		}
	}

	bool Phaser::loadTexture(const std::string texturePath)
	{
		if(!phaserTexture.loadFromFile(texturePath))
		{
			return false;
		}

		return true;
	}

	bool Phaser::findTeleportLocation(Player* player)
	{
		static const int MAX_TELEPORTING_ATTEMPTS = 30;

		Vector2f teleportLocationAttempt;
		int nbAttempts = 0;
		bool canTeleport;

		static const int TELEPORT_IN_SIZE = 125;

		do
		{
			canTeleport = true;

			teleportLocationAttempt = player->getPosition() - Vector2f(TELEPORT_IN_SIZE / 2, TELEPORT_IN_SIZE / 2)
				+ Vector2f(rand() % TELEPORT_IN_SIZE, rand() % TELEPORT_IN_SIZE);

			CollisionCircle collider = CollisionCircle(radius, teleportLocationAttempt.x, 
				teleportLocationAttempt.y);

			if (collider.checkCollision(player->getCollider()))
			{
				canTeleport = false;
				continue;
			}

		} while (!canTeleport && ++nbAttempts <= MAX_TELEPORTING_ATTEMPTS);

		if(nbAttempts > MAX_TELEPORTING_ATTEMPTS)
		{
			return false;
		}

		teleportLocation = teleportLocationAttempt;
		return true;
	}

	void Phaser::drawEnemy(RenderWindow* renderWindow)
	{
		Enemy::drawEnemy(renderWindow);

		if (currentState == ATTACK)
		{			
			renderWindow->draw(attackSprite);
		}
	}

	FloatRect Phaser::getBoxCollider()
	{
		return FloatRect(getPosition() - getOrigin(), Vector2f(0, 0));
	}

	FloatRect Phaser::getBoxCollider(Vector2f fromPosition)
	{
		return FloatRect(fromPosition - getOrigin(), Vector2f(0, 0));
	}
}
