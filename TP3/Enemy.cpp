#include "Enemy.h"
#include "Follower.h"
#include "SlowBombPickup.h"
#include "Player.h"

namespace TP3Prog
{
	Enemy::Enemy() : Enemy(None, DEFAULT_SPEED, DEFAULT_HEALTH)
	{
	}

	Enemy::Enemy(DamageableType type, int speed, int initialHealth) : Entity(speed, type, initialHealth), DEFAULT_SPEED(speed)
	{
		this->isActive = false;
		Subject::addObserver(this);
	}

	Enemy::~Enemy()
	{
		Subject::removeObserver(this);
	}

	void Enemy::update(Player * player, EnemyHandler * enemyHandler)
	{
		if (slowInterval > 0)
		{
			--slowInterval;
		}
		else
		{
			speed = DEFAULT_SPEED;
		}
	}

	void Enemy::drawEnemy(RenderWindow* renderWindow)
	{
		renderWindow->draw(*this);
	}

	CollisionCircle Enemy::getCollider() const
	{
		return CollisionCircle(radius, getPosition().x, getPosition().y);
	}

	void Enemy::notify(Subject* subject)
	{
		if(typeid(*subject) == typeid(Follower))
		{
			Vector2f delta = ((Follower*)subject)->getPosition() - getPosition();
			float distance = sqrt(delta.x * delta.x + delta.y * delta.y);

			if (distance < Follower::HEALING_AURA_RADIUS)
			{
				heal(Follower::HEAL_AMOUNT);
			}
		}
		if (typeid(*subject) == typeid(SlowBombPickup))
		{
			Vector2f delta = ((SlowBombPickup*)subject)->getPosition() - getPosition();
			float distance = sqrt(delta.x * delta.x + delta.y * delta.y);

			if (distance < SlowBombPickup::BOMB_RADIUS_EXPOSITION && type != ((SlowBombPickup*)subject)->getBombType())
			{
				slowInterval = 500- distance;
				speed = 1;
			}
		}
	}
}

