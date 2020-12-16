#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include "SlowBombPickup.h"
#include "HealPickup.h"
#include "ShieldPickup.h"
#include "Weapon.h"
#include "Scene.h"
#include "Label.h"
#include "../TP3Algo/Queue.hpp"


namespace TP3Prog
{

	class EnemyHandler;

	/// <summary>
	/// The Game behavior class. Manages the game flow and
	/// all elements within.
	/// </summary>
	class GameScreen : public Scene
	{
	public:
		GameScreen();
		~GameScreen();

		/// <summary>
		/// Gets the user's inputs.
		/// </summary>
		void getInputs();
		/// <summary>
		/// Initializes the game.
		/// </summary>
		/// <returns>true if the init has been a success. Otherwise, false</returns>
		bool init(RenderWindow * const window);
		void update();
		void draw();

		scenes run();

		void transition(const Scene::scenes & scene1) override;
		void manageEnemyDeath(Vector2f position);
		void manageEndGame();
		int getScore() const;

		TP3Algo::Queue<Enemy>* getNextSquadron();

		void initialiseNewLevel();
		void unloadLevel();

		void unlockExit();

		static const int SCREEN_WIDTH = 1920;
		static const int SCREEN_HEIGHT = 1080;

		static const int WORLD_WIDTH = 640 * 3;
		static const int WORLD_HEIGHT = 640 * 3;
	private:
		static int const FIELD_TILE_AMOUNT = 9;
		static int const TILE_POSITION_X = WORLD_WIDTH/2;
		static int const TILE_POSITION_Y = WORLD_WIDTH/2;

		const int WORLD_CENTER_X = WORLD_WIDTH / 2;
		const int WORLD_CENTER_Y = WORLD_HEIGHT / 2;

		//View limits
		const int VIEW_LIMIT_MIN_X = SCREEN_WIDTH / 2;
		const int VIEW_LIMIT_MIN_Y = SCREEN_HEIGHT / 2;
		const int VIEW_LIMIT_MAX_X = WORLD_WIDTH - VIEW_LIMIT_MIN_X;
		const int VIEW_LIMIT_MAX_Y = WORLD_HEIGHT - VIEW_LIMIT_MIN_Y;

		const int EXIT_LOCATION_X = WORLD_WIDTH - 200;
		const int EXIT_LOCATION_Y = WORLD_HEIGHT - 200;

		//Textures
		Texture fieldT;
		Texture playerT;
		Texture* projectileTextures;

		/// <summary>
		/// The weapon icon's texture.
		/// Used when a special weapon is picked up.
		/// </summary>
		Texture weaponIconT[Weapon::PICKABLE_WEAPON_COUNT];
		Texture shieldIconT[3];
		Texture slowBombT[3];
		Texture healT;
		Texture droneT;


		Text scoreText;
		Text currentAmmoText;
		Text livesText;
		Sprite weaponIcon;

		TP3Algo::Queue<char>* roomStatText;
		String roomStat = "Unknown";

		sf::Text roomLabel;
		sf::Text waveLabel;

		int roomTextInterval;
		int waveTextInterval;
		int waveIndex = 0;

		static const int TEXT_DURATION = 5 * 60;

		//Projectile buffers and their lengths
		const int PROJECTILE_BUFFER_LENGTHS[Weapon::PICKABLE_WEAPON_COUNT]
		{
			10,
			200,
			24
		};

		Weapon** weapons;

		//Other resources
		Font mainFont;
		Music music;

		/// <summary>
		/// The weapon pickup sound effect.
		/// </summary>
		Sound weaponPickupSound;

		SoundBuffer weaponPickupSoundBuffers[3];

		Sprite field;

		static const int FIELD_SIZE = 640;

		Vector2f fieldPositions[FIELD_TILE_AMOUNT];

		/// <summary>
		/// The player.
		/// </summary>
		Player* player;

		EnemyHandler* enemyHandler;
		
		/// <summary>
		/// If the game is paused.
		/// </summary>
		bool isPaused = false;

		/// <summary>
		/// This is the Room number or the level the player is currently at.
		/// </summary>
		int levelIndex = 0;
		static const int LAST_LEVEL = 3;

		static const int BASE_WAVE_AMOUNT = 2;
		TP3Algo::Queue<TP3Algo::Queue<Enemy>>* waves;

		static const int BASE_ENEMY_PER_WAVE = 2;

		bool exitUnlocked = false;
		bool levelFinished = false;

		static const int PICKUP_COUNT = 30;

		/// <summary>
		/// The pickups.
		/// </summary>
		std::vector<Pickup*> pickups;

		Exit* exit = nullptr;

		int score;

		void unload();

		void managePickupCollisions();

		/// <summary>
		/// Centers the UI to the view.
		/// </summary>
		void centerInterfaceToView();

		void crossingViewLimitsAdjustment();

		bool pause = false;

		bool esc = false;

		View view;
	};
}
