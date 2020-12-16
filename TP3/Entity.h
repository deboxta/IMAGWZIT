#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "CollisionCircle.h"
#include "Damageable.h"
#include "IObserver.h"

namespace TP3Prog
{
	/// <summary>
	/// Class of a moving entity in the game.
	/// (Enemy and Player).
	/// </summary>
	/// <seealso cref="sf::Sprite" />
	class Entity : public sf::Sprite, public Damageable
	{
	public:
		Entity(int speed);

		Entity(int speed, DamageableType entityType, int health);

		/// <summary>
		/// Aligns to the specified position (coordinate).
		/// </summary>
		/// <param name="position">The position.</param>
		void alignTo(sf::Vector2f position);

		/// <summary>
		/// Aligns to the specified delta (Vector2).
		/// </summary>
		/// <param name="delta">The delta.</param>
		void alignToDelta(sf::Vector2f delta);

		int getSpeed() const;

		void activate();
		void deactivate();

		bool getIsActive() const;

		virtual CollisionCircle getCollider() const = 0;

	protected:
		/// <summary>
		/// The displacement speed of the Entity.
		/// </summary>
		int speed;
		bool isActive = false;
		bool slowed = false;

		int framecount = 0; 
		int slowInterval = 0;
	};
}
