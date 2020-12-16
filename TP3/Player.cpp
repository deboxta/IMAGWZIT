#include "Player.h"
#include "../TP3Algo/ContainerFactory.hpp"
#include "Weapon.h"
#include "Shield.h"
#include "GameScreen.h"
#include "LaserProjectile.h"
#include "PlayerCommand.hpp"
#include "Drone.h"

using namespace sf;

namespace TP3Prog
{

	const sf::Color Player::DAMAGED_COLOR = Color(255,100,100);

	Player::Player(Weapon* defaultWeapon, sf::Texture* livesT) : 
	Entity(PLAYER_SPEED, DamageableType::None, DEFAULT_PLAYER_HEALTH),
		weapons(TP3Algo::ContainerFactory<Weapon>::getCircularDoubleLinkedList()),
		shields(TP3Algo::ContainerFactory<Shield>::getStack()),
		commands(TP3Algo::ContainerFactory<PlayerCommand>::getQueue())
	{
		this->livesCount = 3;
		this->isActive = true;
		weapons->addStart(defaultWeapon);
		currentWeapon = new CircularDoubleLinkedList<Weapon>::iterator(weapons->begin(), true);
		livesDash = new TP3Algo::Queue<Sprite>;
		for (int i = 0; i < livesCount; i++)
		{
			livesDash->enqueue(new Sprite(*livesT));
		}
	}


	Player::~Player()
	{
		delete currentWeapon;
		delete weapons;

		Shield* shieldToDelete = nullptr;
		while(!shields->isEmpty())
		{
			shieldToDelete = &shields->top();
			shields->pop();
			delete shieldToDelete;
		}

		Sprite* spriteToDelete = nullptr;
		while (!livesDash->isEmpty())
		{
			spriteToDelete = &livesDash->top();
			livesDash->dequeue();
			delete spriteToDelete;
		}

		delete shields;

		while(!commands->isEmpty())
		{
			delete commands->dequeue();
		}
		delete commands;

		delete drone;
		delete livesDash;
	}

	/// <summary>
	/// Determines whether the character has ammo left.
	/// </summary>
	/// <returns>
	///   <c>true</c> if has ammo left; otherwise, <c>false</c>.
	/// </returns>
	bool Player::hasAmmoLeft() const
	{
		return (**currentWeapon).getWeaponType() == WeaponType::DEFAULT ? true :
			(**currentWeapon).getAmmo() >= (**currentWeapon).getRequiredAmmo();
	}

	bool Player::canShoot() const
	{
		return (**currentWeapon).getCurrentShootInterval() <= 0 &&
			hasAmmoLeft();
	}

	void Player::setEnemyHandlerInstance(EnemyHandler* enemyHandler)
	{
		enemyHandlerInstance = enemyHandler;
	}

	void Player::getInputs(const Vector2i aimVector, int scrollWheelDelta)
	{
		(Keyboard::isKeyPressed(Keyboard::W)) ? up = true : up = false;
		(Keyboard::isKeyPressed(Keyboard::S)) ? down = true : down = false;
		(Keyboard::isKeyPressed(Keyboard::A)) ? left = true : left = false;
		(Keyboard::isKeyPressed(Keyboard::D)) ? right = true : right = false;

		nextWeapon = false;
		prevWeapon = false;

		if (scrollWheelDelta > 0)
		{
			nextWeapon = true;
		}
		else if (scrollWheelDelta < 0)
		{
			prevWeapon = true;
		}

		(Mouse::isButtonPressed(Mouse::Button::Left)) ? shootButtonPressed = true : shootButtonPressed = false;

		this->aimVector = aimVector;

	}

	void Player::moveWithinWorldBoundaries(const sf::Vector2f projectedPosition, const CollisionCircle playerBounds,
		const IntRect worldBounds)
	{
		//If the worldBounds contains the projected player's bounds.
		if (worldBounds.contains(projectedPosition.x, projectedPosition.y))
		{
			Vector2f newPosition = projectedPosition;

			//Clamp the x position to the world's bounds
			if (projectedPosition.x - playerBounds.getRadius() < 0)
			{
				newPosition.x = playerBounds.getRadius();
			}
			else if (projectedPosition.x + playerBounds.getRadius() > worldBounds.width)
			{
				newPosition.x = worldBounds.width - playerBounds.getRadius();
			}

			//Clamp the y position to the world's bounds
			if (projectedPosition.y - playerBounds.getRadius() < 0)
			{
				newPosition.y = playerBounds.getRadius();
			}
			else if (projectedPosition.y + playerBounds.getRadius() > worldBounds.height)
			{
				newPosition.y = worldBounds.height - playerBounds.getRadius();
			}

			setPosition(newPosition);
		}
	}

	CollisionCircle Player::getCollider() const
	{
		return CollisionCircle(PLAYER_RADIUS, getPosition().x, getPosition().y);
	}

	sf::FloatRect Player::getCollisionBox() const
	{
		return FloatRect(getPosition() - getOrigin(), Vector2f(PLAYER_RADIUS, PLAYER_RADIUS));
	}

	sf::FloatRect Player::getCollisionBox(Vector2f positionFrom) const
	{
		return FloatRect(positionFrom - getOrigin(), Vector2f(PLAYER_RADIUS, PLAYER_RADIUS));
	}

	void Player::update()
	{
		float moveX = 0.0f;
		float moveY = 0.0f;

		if (slowInterval > 0)
		{
			--slowInterval;
		}
		else
		{
			speed = PLAYER_SPEED;
		}

		isMoving = true;

		for (Weapon& weapon : *weapons)
		{
			weapon.updateSelfAndProjectiles(enemyHandlerInstance);
		}

		if(laserShotInterval > 0)
		{
			--laserShotInterval;
			return;
		}

		if (prevWeapon)
		{
			--*currentWeapon;
		}
		else if (nextWeapon)
		{
			++*currentWeapon;
		}

		//todo : since the world will become "rooms", change world bounds accordingly.
		const IntRect worldBounds = IntRect(0, 0, GameScreen::WORLD_WIDTH, GameScreen::WORLD_HEIGHT);

		if (left) moveX -= 1.0f;
		if (right) moveX += 1.0f;
		if (up) moveY -= 1.0f;
		if (down) moveY += 1.0f;

		if(commands->size() > MAX_PLAYER_COMMANDS_AT_ONCE)
		{
			delete commands->dequeue();
		}

		if (isActive)
		{
			alignToDelta(Vector2f(aimVector));

			const sf::Vector2f projectedPosition = getPosition() +
				Vector2f(moveX, moveY) * static_cast<float>(speed);

			bool canMove = true;

			for (auto obstacle : *enemyHandlerInstance->getObstacleList())
			{
				if(obstacle.getGlobalBounds().intersects(getCollisionBox(projectedPosition)))
				{
					canMove = false;
					isMoving = false;
					break;
				}
			}

			if (canMove)
			{
				moveWithinWorldBoundaries(projectedPosition, getCollider(), worldBounds);
			}
			
			if (isMoving && (abs(moveX) > 0 || abs(moveY) > 0))
			{
				commands->enqueue(new PlayerCommand(Vector2f(moveX, moveY)));
			}
			else
			{
				isMoving = false;
			}
			
			if (drone != nullptr)
			{
				drone->update();
				if (!drone->getIsActive())
				{
					delete drone;
					drone = nullptr;
				}
			}

			if (shootButtonPressed && canShoot())
			{
				(**currentWeapon).shoot(*this);
				
				if ((**currentWeapon).getWeaponType() == LASER_GUN)
				{
					laserShotInterval = LaserProjectile::LASER_PROJECTILE_TIMEOUT;
				}
			}

			if(currentInvulnerabilityInterval > 0)
			{
				--currentInvulnerabilityInterval;
				if(currentInvulnerabilityInterval <= 0)
				{
					setColor(Color::White);
				}
			}
		}
		else if (--currentRespawnInterval <= 0)
		{
			
			activate();
			health = DEFAULT_PLAYER_HEALTH;
		}
		if (livesCount == 0)
		{
			isActive = false;
		}


	}

	void Player::pickupWeapon(Weapon* newWeapon, int ammoYield) const
	{
		newWeapon->addAmmo(ammoYield);

		for (Weapon& weapon : *weapons)
		{
			//Since weapons aren't dynamic for the moment, we can check if both weapon are simply the same.
			if (newWeapon == &weapon)
			{
				//If it exists, the ammo has already been added, so everything is fine already.
				return;
			}
		}

		//If the weapon isn't in the weapon list, we add it.
		weapons->addEnd(newWeapon);
	}

	void Player::pickupShield(Shield* newShield) const
	{
		shields->push(newShield);
	}

	Weapon& Player::getCurrentWeapon() const
	{
		return **currentWeapon;
	}

	void Player::draw(sf::RenderWindow* renderWindow) const
	{
		renderWindow->draw(*this);

		if(!shields->isEmpty())
		{
			renderWindow->draw(shields->top().getShape(getPosition()));
		}

		if (drone != nullptr)
		{
			drone->drawDrone(renderWindow);
		}
	}

	void Player::removeLife()
	{
		livesCount--;
		deactivate();
		currentRespawnInterval = RESPAWN_INTERVAL;
	}

	int Player::getLives() const
	{
		return livesCount;
	}

	TP3Algo::Queue<Sprite>* Player::getLivesDash() const
	{
		return livesDash;
	}

	void Player::takeDamage(DamageableType damageElement, int damageTaken)
	{
		//The player doesn't take damage is he has already taken some time before.
		if(isInvulnerable())
		{
			return;
		}

		int damageCount = damageTaken;

		Shield* lastShield = nullptr;

		//Damage for shields.
		while (damageCount > 0 && !shields->isEmpty())
		{		
				lastShield = &shields->top();
				int shieldHealth = lastShield->getHealth();

				if (lastShield->getDamageElement() == damageElement)
				{
					//todo: return damage taken if shield coincides with entity type??
					//entity.takeDamage(*this, damageTaken);
					return;
				}
				else
				{
					lastShield->takeDamage(damageElement, damageCount <= shieldHealth ? damageCount : shieldHealth);
					damageCount -= shieldHealth;

					if(lastShield->getHealth() <= 0)
					{
						shields->pop();
						delete lastShield;
					}
				}		
		}

		//Damage for entity if damageCount is still positive		
		if(damageCount > 0)
		{
			health -= damageCount;
		}

		currentInvulnerabilityInterval = INVULNERABILITY_DURATION;
		setColor(DAMAGED_COLOR);

		if(health <= 0)
		{
			removeLife();
		}
	}

	bool Player::isInvulnerable() const
	{
		return currentInvulnerabilityInterval > 0;
	}
	void Player::notify(Subject * subject)
	{
		if (typeid(*subject) == typeid(SlowBombPickup))
		{
			SlowBombPickup *slowBomb = static_cast<SlowBombPickup*>(subject);
			if (!shields->isEmpty())
			{
				if (slowBomb->getBombType() != shields->top().getDamageElement())
				{
					slowInterval = 500;
					speed = 2;
				}
			}
			else
			{
				slowInterval = 500;
				speed = 2;
			}
		}
	}

	bool Player::getIsMoving() const
	{
		return isMoving;
	}

	TP3Algo::Queue<PlayerCommand>* Player::getPlayerCommands() const
	{
		return commands;
	}

	void Player::pickupDrone(Drone* drone)
	{
		this->drone = drone;
	}

	Drone* Player::getDrone() const
	{
		return drone;
	}
}

