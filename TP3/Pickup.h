#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "WeaponType.h"


namespace TP3Prog
{

	/// <summary>
	/// Representation for a pickup used during
	/// the game when it is dropped by an enemy.
	/// Yields a special weapon to the player.
	/// </summary>
	/// <seealso cref="sf::Sprite" />
	class Pickup :
		public sf::Sprite
	{
	public:
		Pickup(sf::Vector2f position, WeaponType pickupType, sf::Texture& pickupTexture, int ammoYield);
		~Pickup();

		bool getIsActive() const;

		WeaponType getWeaponType() const;
		int getAmmoYield() const;

		void activate();
		void deactivate();

	private:
		bool isActive;
		WeaponType weaponType;

		/// <summary>
		/// The ammo yielded to the player.
		/// </summary>
		int ammoYield;
	};

}

