#pragma once
#include "Entity.h"
#include <SFML/Graphics/Texture.hpp>

namespace TP3Prog
{

	/// <summary>
	/// Superclass of the projectile thrown/shot by the player.
	/// </summary>
	/// <seealso cref="Entity" />
	class Projectile : public Entity
	{


	public:
		Projectile();
		Projectile(int defaultProjectileTimeout, float speed, bool isInvulnerable = false, 
			int projectileDamage = DEFAULT_PROJECTILE_DAMAGE);
		virtual ~Projectile();

		/// <summary>
		/// Sets the texture for all types of projectiles.
		/// Projectiles' texture will have to be set for each of them.
		/// </summary>
		/// <param name="textures"></param>
		static void setProjectileTextures(sf::Texture* textures);
		static void unloadProjectileTextures();

		/// <summary>
		/// Loads the single projectile's texture.
		/// </summary>
		virtual void loadTexture();

		virtual void initialise(sf::Vector2f position, float angle);
		virtual void update();

		bool getIsInvulnerable() const;

		CollisionCircle getCollider() const override;

		int getDamage() const;

		void notify(Subject* subject);

	protected:
		static sf::Texture* projectileTextures;

		int defaultProjectileTimeout;
		int projectileTimeout;

		float angle;

		bool isInvulnerable = false;
		const int projectileDamage;
		static const int DEFAULT_PROJECTILE_SPEED = 16;
		static const int DEFAULT_PROJECTILE_INTERVAL = 240;

		static const int DEFAULT_PROJECTILE_DAMAGE = 1;
	};

}
