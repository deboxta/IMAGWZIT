#include "SwarmQueen.h"
#include "EnemyFactory.hpp"
#include <random>
#include "EnemyHandler.h"


namespace TP3Prog
{
	sf::Texture SwarmQueen::swarmQueenTexture;

	SwarmQueen::SwarmQueen() : SwarmQueen(None)
	{
	}
	SwarmQueen::SwarmQueen(DamageableType type) : Enemy(type, SWARMQUEEN_SPEED, SWARMQUEEN_HEALTH), currentState(FOLLOWING)
	{
		this->isActive = false;

		radius = normalRadius;
	}
	SwarmQueen::~SwarmQueen()
	{
		for (int i = 0; i < NBR_OF_ANIMS; ++i)
		{
			delete[] intRectsAnims[i];
		}

		delete[] intRectsAnims;
	}
	void SwarmQueen::update(Player* player, EnemyHandler* enemyHandler)
	{
		Enemy::update(player, enemyHandler);
		animate();
		if (!isActive)
			return;

		CircularDoubleLinkedList<Enemy>* enemies = enemyHandler->getEnemyList();

		bool canMove = true;
		Vector2f targetPosition = player->getPosition();
		switch (currentState)
		{
		case FOLLOWING:
			canMove = true;
			if (player->getIsActive())
			{
				if (swarlingCount < 5)
				{
					radius = DistanceRadius;
					if (player->getCollider().checkCollision(getCollider()))
					{
						currentState = IDLE;
						radius = normalRadius;
						break;
					}
					else
					{
						radius = normalRadius;
						alignToDelta(targetPosition - getPosition());
					}
				}
				else
				{
					alignToDelta(targetPosition - getPosition());
				}
				if (player->getCollider().checkCollision(getCollider()))
				{
					player->takeDamage(getDamageElement(), SWARMQUEEN_ATTACK_DAMAGE);
					attackDone = true;
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
			}
			else
			{
				alignToDelta(getPosition() - targetPosition);
			}
			break;
		case IDLE:
			canMove = false;
			if (frameCount % 60 == 0 && swarlingCount < MAX_SWARMLINGS)
			{
				enemies->addEnd(EnemyFactory::createEnemy(EnemyFactory::SWARMLING));
			}
			if (swarlingCount % 5 == 0 && swarlingCount >= 1)
			{
				currentState = FOLLOWING;
			}

			break;
		}

		//Enemies collisions handling
		const Vector2f projectedPosition = Vector2f(std::cos(getRotation() * std::_Pi / 180) * speed,
			std::sin(getRotation() * std::_Pi / 180) * speed);

		const CollisionCircle projectedCollider = CollisionCircle(radius, getPosition().x + projectedPosition.x,
			getPosition().y + projectedPosition.y);
		swarlingCount = 0;
		for (Enemy& i : *enemies)
		{
			if (dynamic_cast<Swarmling*>(&i))
			{
				swarlingCount++;
			}
			if (&i == this)
			{
				continue;
			}
			if (projectedCollider.checkCollision(i.getCollider()))
			{
				canMove = false;
			}
		}

		for (Obstacle& i : *enemyHandler->getObstacleList())
		{
			if (getBoxCollider(getPosition() + projectedPosition).intersects(i.getGlobalBounds()))
			{
				canMove = false;
				break;
			}
		}

		if (canMove)
			move(projectedPosition);
		frameCount++;
	}

	void SwarmQueen::visualAdjustements()
	{
		setOrigin(RECTANGLE_SIZE / 2, RECTANGLE_SIZE / 2);
		setTexture(swarmQueenTexture);

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

	void SwarmQueen::animate()
	{
		//Animation de marche, elle est cyclique
		if (currentState == FOLLOWING)
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

	bool SwarmQueen::loadTexture(const std::string& texturePath)
	{
		if (!swarmQueenTexture.loadFromFile(texturePath))
		{
			return false;
		}

		return true;
	}

	FloatRect SwarmQueen::getBoxCollider()
	{
		return FloatRect(getPosition() - getOrigin(), Vector2f(RECTANGLE_SIZE, RECTANGLE_SIZE));
	}

	FloatRect SwarmQueen::getBoxCollider(Vector2f fromPosition)
	{
		return FloatRect(fromPosition - getOrigin(), Vector2f(RECTANGLE_SIZE, RECTANGLE_SIZE));
	}
}

