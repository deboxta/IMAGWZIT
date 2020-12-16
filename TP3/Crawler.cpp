#include "Crawler.h"
#include <complex>
#include <random>
#include <valarray>
#include "GameScreen.h"
#include "Player.h"

namespace TP3Prog
{

	Texture Crawler::crawlerTextures[TEXTURE_AMOUNT];


	Crawler::Crawler() : Crawler(None)
	{

	}

	Crawler::Crawler(DamageableType type) : Enemy(type, CRAWLER_SPEED, CRAWLER_HEALTH), currentState(UNDEFINED)
	{
		this->isActive = false;

		int textureID = rand() % TEXTURE_AMOUNT;

		setTexture(crawlerTextures[textureID]);

		setOrigin(crawlerTextures[textureID].getSize().x / 2, crawlerTextures[textureID].getSize().y / 2);

		sf::Color assignedColor;

		if (type != None)
		{
			switch (type)
			{
			case Blue:
				assignedColor = sf::Color::Blue;
				break;
			case Red:
				assignedColor = sf::Color::Red;
				break;
			case Green:
				assignedColor = sf::Color::Green;
				break;
			}

			setColor(assignedColor);
		}
	}

	Crawler::~Crawler()
	{
	}

	void Crawler::update(Player* player, EnemyHandler* enemyHandler)
	{
		Enemy::update(player, enemyHandler);
		if (!isActive)
			return;

		CircularDoubleLinkedList<Enemy>* enemies = enemyHandler->getEnemyList();
		CircularDoubleLinkedList<Obstacle>* obstacles = enemyHandler->getObstacleList();

		Vector2f targetPosition = player->getPosition();

		if (player->getIsActive())
		{
			alignToDelta(targetPosition - getPosition());

			if (player->getCollider().checkCollision(getCollider()))
			{
				player->takeDamage(getDamageElement(), CRAWLER_DAMAGE);
			}
		}
		else
		{
			alignToDelta(getPosition() - targetPosition);
		}

		const Vector2f projectedPosition = Vector2f(std::cos(getRotation() * std::_Pi / 180) * speed,
			std::sin(getRotation() * std::_Pi / 180) * speed);

		const CollisionCircle projectedCollider = CollisionCircle(radius, getPosition().x + projectedPosition.x,
			getPosition().y + projectedPosition.y);

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
			if (getBoxCollider(projectedPosition + getPosition()).intersects(i.getGlobalBounds()))
			{
				canMove = false;
				break;
			}
		}

		if (canMove)
			move(projectedPosition);
	}

	bool Crawler::loadTextures(const std::string texturePaths[3])
	{
		for (int i = 0; i < TEXTURE_AMOUNT; ++i)
		{
			if (!crawlerTextures[i].loadFromFile(texturePaths[i]))
			{
				return false;
			}
		}

		return true;
	}

	FloatRect Crawler::getBoxCollider()
	{
		return FloatRect(getPosition() - getOrigin(), Vector2f( CRAWLER_SIZE, CRAWLER_SIZE ));
	}

	FloatRect Crawler::getBoxCollider(Vector2f fromPosition)
	{
		return FloatRect(fromPosition - getOrigin(), Vector2f(CRAWLER_SIZE, CRAWLER_SIZE));
	}
}