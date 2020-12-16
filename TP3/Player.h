#pragma once
#include "Entity.h"
#include "WeaponType.h"
#include "../TP3Algo/CircularDoubleLinkedList.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../TP3Algo/Stack.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "../TP3Algo/Queue.hpp"
#include "PlayerCommand.hpp"
#include "EnemyHandler.h"


namespace TP3Prog
{
	class Weapon;
	class Shield;
	class Drone;

	/// <summary>
	/// Class of the player in the game.
	/// </summary>
	/// <seealso cref="Entity" />
	class Player : public Entity
	{
	public:
		Player(Weapon* defaultWeapon, sf::Texture* livesT);
		~Player();
		bool hasAmmoLeft() const;

		bool canShoot() const;

		void setEnemyHandlerInstance(EnemyHandler* enemyHandler);

		void getInputs(const sf::Vector2i aimVector, int scrollWheelDelta);
		void moveWithinWorldBoundaries(const sf::Vector2f projectedPosition, const CollisionCircle playerBounds,
		                               const sf::IntRect worldBounds);
		
		CollisionCircle getCollider() const override;

		/// <summary>
		/// Slightly more costly collider.
		/// This is an alternative for those that don't have a CollisionCircle.
		/// </summary>
		/// <returns>the collision box of the player.</returns>
		sf::FloatRect getCollisionBox() const;
		sf::FloatRect getCollisionBox(Vector2f positionFrom) const;

		/// <summary>
		/// Updates the player : manages movement and shooting.
		/// </summary>
		void update();

		void pickupWeapon(Weapon* newWeapon, int ammoYield) const;

		void pickupShield(Shield* newShield) const;

		Weapon& getCurrentWeapon() const;

		void draw(sf::RenderWindow* renderWindow) const;

		void removeLife();

		int getLives() const;
		TP3Algo::Queue<Sprite>* getLivesDash() const;

		void takeDamage(DamageableType damageElement, int damageTaken) override;
		bool isInvulnerable() const;

		void notify(Subject* subject) override;

		bool getIsMoving() const;
		TP3Algo::Queue<PlayerCommand>* getPlayerCommands() const;
		void pickupDrone(Drone* drone);
		Drone* getDrone() const;

		static const int PLAYER_SPEED = 10;
	private:

		//Directional Inputs
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;

		//Weapon Interaction.
		bool shootButtonPressed = false;
		bool prevWeapon;
		bool nextWeapon;
		
		//Aim Vector.
		sf::Vector2i aimVector;
		
		int livesCount;

		int currentRespawnInterval = 0;
		int currentInvulnerabilityInterval = 0;
		int laserShotInterval = 0;

		static const int INVULNERABILITY_DURATION = 240;
		static const int PLAYER_RADIUS = 40;

		static const int DEFAULT_PLAYER_HEALTH = 10;
		static const int RESPAWN_INTERVAL = 120;
		
		static const sf::Color DAMAGED_COLOR;

		TP3Algo::Stack<Shield>* shields;

		bool isMoving;
		TP3Algo::Queue<PlayerCommand>* commands;
		static const int MAX_PLAYER_COMMANDS_AT_ONCE = 20;

		Drone* drone = nullptr;

		CircularDoubleLinkedList<Weapon>* weapons;
		CircularDoubleLinkedList<Weapon>::iterator* currentWeapon;

		TP3Algo::Queue<Sprite>* livesDash;
		EnemyHandler* enemyHandlerInstance;
		
	};
}

