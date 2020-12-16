#include "Guardian.h"
#include "GameScreen.h"
#include "Player.h"
#include <random>

namespace  TP3Prog
{
	sf::Texture Guardian::swarmlingTexture;

	Guardian::Guardian() :Guardian(None)
	{
	}

	Guardian::Guardian(DamageableType type) : Enemy(type, GUARDIAN_SPEED, GUARDIAN_HEALTH), currentState(FOLLOWING)
	{
		this->isActive = true;	
	}

	Guardian::~Guardian()
	{
		for (int i = 0; i < NBR_OF_ANIMS; ++i)
		{
			delete[] intRectsAnims[i];
		}

		delete[] intRectsAnims;
	}

	void Guardian::update(Player* player, EnemyHandler* enemyHandler)
	{
		Enemy::update(player, enemyHandler);
		animate();
		if (!isActive)
			return;

		CircularDoubleLinkedList<Enemy>* enemies = enemyHandler->getEnemyList();
		CircularDoubleLinkedList<Obstacle>* obstacles = enemyHandler->getObstacleList();

		bool canMove = true;
		Vector2f targetPosition = player->getPosition();
		switch (currentState)
		{
		case ATTACK:
			canMove = true;
			if (player->getIsActive())
			{
				alignToDelta(targetPosition - getPosition());
				if (player->getCollider().checkCollision(getCollider()))
				{
					player->takeDamage(getDamageElement(), GUARDIAN_ATTACK_DAMAGE);
					attackDone = true;
				}
			}
			else
			{
				alignToDelta(getPosition() - targetPosition);
			}
			if (attackDone == true)
			{
				alignToDelta(getPosition() - targetPosition);
				if (frameCount % 300 == 10)
				{
					currentState = IDLE;
					attackDone = false;
				}
			}

			break;
		case FOLLOWING:
			canMove = true;
			radius = DistanceRadius;
			if (player->getCollider().checkCollision(getCollider()))
			{
				currentState = ATTACK;
				radius = normalRadius;
				break;
			}
			radius = normalRadius;

			if (player->getIsActive())
			{
				alignToDelta(targetPosition - getPosition());

				if (player->getCollider().checkCollision(getCollider()))
				{
					player->takeDamage(getDamageElement(), GUARDIAN_ATTACK_DAMAGE);
				}
			}
			else
			{
				alignToDelta(getPosition() - targetPosition);
			}
			break;
		case IDLE:
			canMove = false;
			if (frameCount% 500 == 10)
			{
				radius = DistanceRadius;
				if (player->getCollider().checkCollision(getCollider()))
				{
					currentState = ATTACK;
				}
				else
				{
					currentState = FOLLOWING;
				}
				radius = normalRadius;
			}
			break;
		}
		//Enemies collisions handling
		const Vector2f projectedPosition = Vector2f(std::cos(getRotation() * std::_Pi / 180) * (speed),
			std::sin(getRotation() * std::_Pi / 180) * (speed));

		const CollisionCircle projectedCollider = CollisionCircle(radius, getPosition().x + projectedPosition.x,
			getPosition().y + projectedPosition.y);

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
			if (getBoxCollider(projectedPosition + getPosition()).intersects(i.getGlobalBounds()))
			{
				canMove = false;
				break;
			}
		}

		if (canMove)
			move(projectedPosition);
;
		frameCount++;
	}

	bool Guardian::loadTexture(std::string texturePath)
	{
		if (!swarmlingTexture.loadFromFile(texturePath))
		{
			return false;
		}

		return true;
	}
	void Guardian::visualAdjustements()
	{
		setTexture(swarmlingTexture);
		setOrigin(RECTANGLE_SIZE / 2, RECTANGLE_SIZE / 2);

		intRectsAnims = new IntRect*[NBR_OF_LEVELS];
		for (int i = 0; i < NBR_OF_LEVELS; i++)
		{
			intRectsAnims[i] = new IntRect[NBR_OF_ANIMS];
			for (int j = 0; j < NBR_OF_ANIMS; ++j)
			{
				intRectsAnims[i][j].left = RECTANGLE_SIZE * j;
				intRectsAnims[i][j].width = RECTANGLE_SIZE;

				intRectsAnims[i][j].top = RECTANGLE_SIZE * i;
				intRectsAnims[i][j].height = RECTANGLE_SIZE;
			}
		}
	}

	void Guardian::animate()
	{
		//Animation de marche, elle est cyclique
		if (currentState == FOLLOWING || currentState == IDLE)
		{
			if (animator++ % animationSpeed == 0)
			{
				setTextureRect(intRectsAnims[currentState][(animator / animationSpeed) % NBR_OF_ANIMS]);
			}
		}

		//Les animations de saut et de célébration sont linéaires
		else
		{
			if (animator++ % animationSpeed == 0)
			{
				int frame = animator / animationSpeed;

				//Pour rester sur le dernier frame à la fin de l'animation
				if (frame > (NBR_OF_ANIMS - 1))
				{
					frame = NBR_OF_ANIMS - 1;
				}

				setTextureRect(intRectsAnims[currentState][(frame) % NBR_OF_ANIMS]);
			}
		}
	}

	FloatRect Guardian::getBoxCollider()
	{
		return FloatRect(getPosition() - getOrigin(), Vector2f(RECTANGLE_SIZE - 20, RECTANGLE_SIZE - 20));
	}

	FloatRect Guardian::getBoxCollider(Vector2f fromPosition)
	{
		return FloatRect(fromPosition - getOrigin(), Vector2f(RECTANGLE_SIZE - 20, RECTANGLE_SIZE - 20));
	}
}
