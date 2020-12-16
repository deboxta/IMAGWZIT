#include "Swarmling.h"
#include "GameScreen.h"
#include "Player.h"
#include <random>

namespace  TP3Prog
{
	sf::Texture Swarmling::swarmlingTexture;

	Swarmling::Swarmling() :Swarmling(None)
	{
	}

	Swarmling::Swarmling(DamageableType type) : Enemy(type, SWARMLING_SPEED, SWARMLING_HEALTH), currentState(SPAWNING)
	{
		radius = 32;
		this->isActive = true;

		setTexture(swarmlingTexture);
		setOrigin(swarmlingTexture.getSize().x / 2, swarmlingTexture.getSize().y / 2);
	}

	Swarmling::~Swarmling()
	{
	}

	void Swarmling::update(Player* player, EnemyHandler* enemyHandler)
	{
		Enemy::update(player, enemyHandler);
		if (!isActive)
			return;

		CircularDoubleLinkedList<Enemy>* enemies = enemyHandler->getEnemyList();

		bool canMove = true;
		Vector2f targetPosition = player->getPosition();
		switch (currentState)
		{
		case FOLLOWING:
			if (player->getIsActive())
			{
				alignToDelta(targetPosition - getPosition());

				if (player->getCollider().checkCollision(getCollider()))
				{
					health = 0;
					player->takeDamage(getDamageElement(), SWARLING_ATTACK_DAMAGE);
				}
			}
			else
			{
				alignToDelta(getPosition() - targetPosition);
			}
			break;
		case SPAWNING:
			CollisionCircle projectedCollider;
			Vector2f projectedPosition;
			for (Enemy& enemy : *enemies)
			{
				if (dynamic_cast<SwarmQueen*>(&enemy))
				{
					projectedPosition = Vector2f(enemy.getPosition().x+ 60, enemy.getPosition().y+60);
					projectedCollider = CollisionCircle(radius, projectedPosition.x,
						projectedPosition.y);
				}
				if ((projectedCollider.checkCollision(enemy.getCollider()))==false)
				{
					setPosition(projectedPosition);
					currentState = FOLLOWING;
				}
			}

			break;
		}
		//Enemies collisions handling
		const Vector2f projectedPosition = Vector2f(std::cos(getRotation() * std::_Pi / 180) * speed,
			std::sin(getRotation() * std::_Pi / 180) * speed);

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

		for (Obstacle& i : *enemyHandler->getObstacleList())
		{
			if (getBoxCollider(projectedPosition + getPosition()).intersects(i.getGlobalBounds()))
			{
				canMove = false;
				break;
			}
		}

		if (canMove)
			move(projectedPosition);
	}

	bool Swarmling::loadTexture(std::string texturePath)
	{
		if (!swarmlingTexture.loadFromFile(texturePath))
		{
			return false;
		}

		return true;
	}

	FloatRect Swarmling::getBoxCollider()
	{
		return FloatRect(getPosition() - getOrigin(),
			Vector2f(swarmlingTexture.getSize().x, swarmlingTexture.getSize().y));
	}

	FloatRect Swarmling::getBoxCollider(Vector2f fromPosition)
	{
		return FloatRect(fromPosition - getOrigin(),
			Vector2f(swarmlingTexture.getSize().x, swarmlingTexture.getSize().y));
	}
}
