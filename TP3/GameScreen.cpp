#pragma once
#include "GameScreen.h"
#include "Flamethrower.h"
#include "Scattershot.h"
#include "RocketLauncher.h"
#include "Scatter.h"
#include "Handgun.h"
#include "EnemyHandler.h"
#include "Shield.h"
#include "EnemySquadronGenerator.h"
#include "LaserGun.h"
#include "Minigun.h"
#include "DronePickup.h"
#include "Drone.h"
#include "Obstacle.h"
#include "../TP3Algo/ContainerFactory.hpp"

namespace TP3Prog
{

	GameScreen::GameScreen()
	{
		view = View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
		view.setCenter(WORLD_WIDTH / 2, WORLD_HEIGHT / 2);
		
	}

	GameScreen::~GameScreen()
	{
		mainWin->setView( mainWin->getDefaultView());
	}

	Scene::scenes GameScreen::run()
	{
		while (isRunning)
		{
			initialiseNewLevel();
			while (!levelFinished && isRunning)
			{
				getInputs();
				update();
				draw();
			}
			unloadLevel();

			if(levelIndex >= LAST_LEVEL)
			{
				manageEndGame();
			}
		}

		unload();
		return transitionToScene;
	}

	bool GameScreen::init(RenderWindow * const window)
	{
		this->mainWin = window;
		mainWin->setKeyRepeatEnabled(false);

		if (!fieldT.loadFromFile("Sprites\\grass.png"))
		{
			return false;
		}

		if (!playerT.loadFromFile("Sprites\\Art\\player.png"))
		{
			return false;
		}

		if (!slowBombT[0].loadFromFile("Sprites\\Art\\BombBlue.png"))
		{
			return false;
		}

		if (!slowBombT[1].loadFromFile("Sprites\\Art\\BombRed.png"))
		{
			return false;
		}

		if (!slowBombT[2].loadFromFile("Sprites\\Art\\BombGreen.png"))
		{
			return false;
		}

		if (!healT.loadFromFile("Sprites\\Logos\\Heal.png"))
		{
			return false;
		}

		if (!droneT.loadFromFile("Sprites\\Logos\\droneLogo.png"))
		{
			return false;
		}

		if (!shieldIconT[0].loadFromFile("Sprites\\Logos\\ShieldLogoBlue.png"))
		{
			return false;
		}

		if (!shieldIconT[1].loadFromFile("Sprites\\Logos\\ShieldLogoRed.png"))
		{
			return false;
		}

		if (!shieldIconT[2].loadFromFile("Sprites\\Logos\\ShieldLogoGreen.png"))
		{
			return false;
		}

		if (!weaponIconT[ROCKETLAUNCHER].loadFromFile("Sprites\\Logos\\MissileLogo.png"))
		{
			return false;
		}

		if (!weaponIconT[FLAMETHROWER].loadFromFile("Sprites\\Logos\\FlameLogo.png"))
		{
			return false;
		}

		if (!weaponIconT[SCATTERSHOT].loadFromFile("Sprites\\Logos\\ScatterLogo.png"))
		{
			return false;
		}

		if (!weaponIconT[LASER_GUN].loadFromFile("Sprites\\Logos\\LaserLogo.png"))
		{
			return false;
		}

		if (!weaponIconT[MINIGUN].loadFromFile("Sprites\\Logos\\MinigunLogo.png"))
		{
			return false;
		}

		if (!weaponPickupSoundBuffers[0].loadFromFile("Sounds\\WeaponPickup\\imvegannow.wav"))
		{
			return false;
		}

		if (!weaponPickupSoundBuffers[1].loadFromFile("Sounds\\WeaponPickup\\deadrat.wav"))
		{
			return false;
		}

		if (!weaponPickupSoundBuffers[2].loadFromFile("Sounds\\WeaponPickup\\healthhapiness.wav"))
		{
			return false;
		}

		projectileTextures = new Texture[Weapon::PICKABLE_WEAPON_COUNT + 2];

		if (!projectileTextures[DEFAULT].loadFromFile("Sprites\\Projectiles\\Bullet.png"))
		{
			return false;
		}

		if (!projectileTextures[ROCKETLAUNCHER].loadFromFile("Sprites\\Projectiles\\Missile.png"))
		{
			return false;
		}

		if (!projectileTextures[FLAMETHROWER].loadFromFile("Sprites\\Projectiles\\taser1.png"))
		{
			return false;
		}

		if (!projectileTextures[SCATTERSHOT].loadFromFile("Sprites\\Projectiles\\Scatter.png"))
		{
			return false;
		}

		if (!projectileTextures[FOLLOWER_WEAPON].loadFromFile("Sprites\\Projectiles\\pokeball.png"))
		{
			return false;
		}

		if (!projectileTextures[WATCHER_WEAPON].loadFromFile("Sprites\\Projectiles\\WatcherProjectile3x.png"))
		{
			return false;
		}

		if (!projectileTextures[LASER_GUN].loadFromFile("Sprites\\Projectiles\\LaserSpritesheet20x.png"))
		{
			return false;
		}

		if (!projectileTextures[MINIGUN].loadFromFile("Sprites\\Projectiles\\MinigunBullet.png"))
		{
			return false;
		}

		if (!mainFont.loadFromFile("Fonts\\segoepr.ttf"))
		{
			return false;
		}

		if (!music.openFromFile("Sounds\\everydaybro.wav"))
		{
			return false;
		}

		//UI Initialization.

		scoreText.setFont(mainFont);
		scoreText.setCharacterSize(30);

		roomLabel.setFont(mainFont);
		roomLabel.setCharacterSize(30);

		waveLabel.setFont(mainFont);
		waveLabel.setCharacterSize(30);

		currentAmmoText.setFont(mainFont);
		currentAmmoText.setCharacterSize(20);

		livesText.setFont(mainFont);
		livesText.setCharacterSize(30);

		//Texture assignment.

		Projectile::setProjectileTextures(projectileTextures);

		//Sprite Initialization.

		field.setTexture(fieldT);

		//Instance initialization.
		weapons = new Weapon*[Weapon::PICKABLE_WEAPON_COUNT]
		{
			new Handgun(),
			new RocketLauncher(),
			new Flamethrower(),
			new Scattershot(),
			new LaserGun(),
			new Minigun()
		};

		for (int x = 0; x < FIELD_TILE_AMOUNT / 3; ++x)
		{
			for (int y = 0; y < FIELD_TILE_AMOUNT / 3; ++y)
			{
				fieldPositions[x * 3 + y] = Vector2f(x * FIELD_SIZE, y * FIELD_SIZE);
			}
		}

		score = 0;

		EnemySquadronGenerator::init();

		if(!Drone::loadTexture("Sprites\\Art\\Drone.png"))
		{
			return false;
		}

		if(!Obstacle::loadTexture("Sprites\\obstacle2.png"))
		{
			return false;
		}

		Exit::loadTexture("Sprites\\door.png");
		exit = new Exit(Vector2f(EXIT_LOCATION_X, EXIT_LOCATION_Y));

		player = new Player(weapons[DEFAULT], &healT);
		player->setTexture(playerT);
		player->setOrigin(playerT.getSize().x / 2 + 7, playerT.getSize().y / 2 + 7);

		enemyHandler = new EnemyHandler(player, this, exit);

		player->setEnemyHandlerInstance(enemyHandler);

		//Play the music!
		music.setVolume(30);
		//music.play();
		music.setLoop(true);

		return true;
	}

	void GameScreen::unload()
	{
		Projectile::unloadProjectileTextures();

		delete player;

		for (int i = 0; i < Weapon::PICKABLE_WEAPON_COUNT; ++i)
		{
			delete weapons[i];
		}

		delete[] weapons;

		if (!pickups.empty())
		{
			for (Pickup* pickup : pickups)
			{
				delete pickup;
			}
		}

		delete enemyHandler;

		delete exit;

		if (waves != nullptr)
		{
			while (!waves->isEmpty())
			{
				TP3Algo::Queue<Enemy>* queueToDelete = waves->dequeue();
				while (!queueToDelete->isEmpty())
				{
					delete queueToDelete->dequeue();
				}
				delete queueToDelete;
			}

			delete waves;
		}
	}

	void GameScreen::getInputs()
	{
		int mouseWheelDelta = 0;

		while (mainWin->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				transition(EXIT);	
			}
			else if (event.type == Event::MouseWheelScrolled)
			{
				mouseWheelDelta = event.mouseWheelScroll.delta;
			}
			else if(event.type == Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::P)
				{
					isPaused = !isPaused;
				}
			}
		}

		const Vector2i relativeMousePosition = Vector2i(Mouse::getPosition(*mainWin).x, Mouse::getPosition(*mainWin).y)
			- mainWin->mapCoordsToPixel(player->getPosition());

		player->getInputs(relativeMousePosition, mouseWheelDelta);

		(Keyboard::isKeyPressed(Keyboard::Escape)) ? esc = true : esc = false;
	}

	void GameScreen::transition(const Scene::scenes & scene1)
	{
		isRunning = false;
		transitionToScene = scene1;
	}

	void GameScreen::manageEnemyDeath(Vector2f position)
	{
		score += 100;

		if (rand() % 101 < 40)
		{
			int pickupProbability = rand() % 101;

			//Spawn a pickup!
			if (pickupProbability < 20)
			{
				ShieldPickup* newShield;
				switch (rand() % 3 + 1)
				{
				case 1:
					newShield = new ShieldPickup(position, shieldIconT[0], Entity::DamageableType::Blue);
					break;
				case 2:
					newShield = new ShieldPickup(position, shieldIconT[1], Entity::DamageableType::Red);
					break;
				case 3:
					newShield = new ShieldPickup(position, shieldIconT[2], Entity::DamageableType::Green);
					break;
				default:
					newShield = new ShieldPickup(position, shieldIconT[0], Entity::DamageableType::Blue);
					break;
				}
				pickups.push_back(newShield);
			}
			else if (pickupProbability < 40)
			{
				SlowBombPickup* newSlowBomb;
				switch (rand() % 3 + 1)
				{
				case 1:
					newSlowBomb = new SlowBombPickup(position, slowBombT[0], Entity::DamageableType::Blue, enemyHandler, player);
					break;
				case 2:
					 newSlowBomb = new SlowBombPickup(position, slowBombT[1], Entity::DamageableType::Red, enemyHandler, player);
					break;
				case 3:
					 newSlowBomb = new SlowBombPickup(position, slowBombT[2], Entity::DamageableType::Green, enemyHandler, player);
					break;
				default:
					 newSlowBomb = new SlowBombPickup(position, slowBombT[0], Entity::DamageableType::Blue, enemyHandler, player);
					break;
				}
				pickups.push_back(newSlowBomb);
			}
			else if (pickupProbability < 60)
			{
				HealPickup* newHealPickup = new HealPickup(position, healT);
				pickups.push_back(newHealPickup);
			}
			else if (pickupProbability < 63)
			{
				DronePickup* newDronePickup = new DronePickup(position, droneT);
				pickups.push_back(newDronePickup);
			}
			else
			{
				int weaponType = 1 + rand() % (Weapon::PICKABLE_WEAPON_COUNT - 1);
				int ammoYield;

				switch (weaponType)
				{
				case ROCKETLAUNCHER:
					ammoYield = 35 + rand() % 16;
					break;
				case FLAMETHROWER:
					ammoYield = 100 + rand() % 76;
					break;
				case SCATTERSHOT:
					ammoYield = 100 + rand() % 76;
					break;
				case LASER_GUN:
					ammoYield = 1;
					break;
				case MINIGUN:
					ammoYield = 200 + rand() % 76;
					break;
				default:
					ammoYield = 0;
					break;
				}
				Pickup* newPickup = new Pickup(position, (WeaponType)weaponType, weaponIconT[weaponType], ammoYield);
				pickups.push_back(newPickup);
			}
		}
	}

	void GameScreen::manageEndGame()
	{
		transition(END);
	}

	int GameScreen::getScore() const
	{
		return score;
	}

	TP3Algo::Queue<Enemy>* GameScreen::getNextSquadron()
	{
		if (!waves->isEmpty())
		{
			++waveIndex;

			waveLabel.setString("WAVE " + std::to_string(waveIndex));

			waveTextInterval = TEXT_DURATION;

			return waves->dequeue();
		}
		else return nullptr;
	}

	void GameScreen::initialiseNewLevel()
	{
		exitUnlocked = false;

		++levelIndex;

		waves = TP3Algo::ContainerFactory<TP3Algo::Queue<Enemy>>::getQueue();

		const int waveAmount = BASE_WAVE_AMOUNT + levelIndex;

		for (int i = 0; i < waveAmount; ++i)
		{
			waves->enqueue(EnemySquadronGenerator::formSquadron(BASE_ENEMY_PER_WAVE * (levelIndex * 1.5) + i));
		}

		player->setPosition(WORLD_CENTER_X, WORLD_CENTER_Y);

		enemyHandler->spawnObstacles();

		levelFinished = false;

		roomLabel.setString("ROOM " + std::to_string(levelIndex));

		roomTextInterval = TEXT_DURATION;
	}

	void GameScreen::unloadLevel()
	{
		while (!waves->isEmpty())
		{
			TP3Algo::Queue<Enemy>* queueToDelete = waves->dequeue();
			while(!queueToDelete->isEmpty())
			{
				delete queueToDelete->dequeue();
			}
			delete queueToDelete;
		}

		delete waves;
		waves = nullptr;

		enemyHandler->clearObstacles();


		for (Pickup* pickup : pickups)
		{
			delete pickup;
		}

		pickups.clear();
	}

	void GameScreen::unlockExit()
	{
		exitUnlocked = true;
	}

	void GameScreen::managePickupCollisions()
	{
		for (unsigned int i = 0; i < pickups.size(); i++)
		{
			if (pickups[i]->getIsActive() && pickups[i]->getGlobalBounds().intersects(player->getGlobalBounds()))
			{
				if (dynamic_cast<ShieldPickup*>(pickups[i]))
				{
					ShieldPickup* temp = dynamic_cast<ShieldPickup*>(pickups[i]);
					Shield* newShield = new Shield(temp->getShieldType());
					player->pickupShield(newShield);
					pickups[i]->deactivate();
				}
				else if (dynamic_cast<HealPickup*>(pickups[i]))
				{
					player->heal(2);
					pickups[i]->deactivate();
				}
				else if (dynamic_cast<SlowBombPickup*>(pickups[i]))
				{
					SlowBombPickup* tempBomb = dynamic_cast<SlowBombPickup*>(pickups[i]);
					tempBomb->notifyAllObservers();
					pickups[i]->deactivate();
				}
				else if (dynamic_cast<DronePickup*>(pickups[i]))
				{
					if (player->getDrone() == nullptr)
					{
						Drone* newDrone = new Drone(player, enemyHandler);

							newDrone->visualAdjustments();
							player->pickupDrone(newDrone);
							pickups[i]->deactivate();
					}
				}
				else
				{
					player->pickupWeapon(weapons[pickups[i]->getWeaponType()], pickups[i]->getAmmoYield());
					pickups[i]->deactivate();
				}
			}
		}
	}

	void GameScreen::update()
	{
		if (esc)
		{
			transition(TITLE);
		}

		if(isPaused)
		{
			return;
		}

		WeaponType lastWeaponType = player->getCurrentWeapon().getWeaponType();

		player->update();

		const WeaponType currentWeaponType = player->getCurrentWeapon().getWeaponType();

		if (currentWeaponType != DEFAULT)
		{
			weaponIcon.setTexture(weaponIconT[currentWeaponType]);
		}

		enemyHandler->update();

		managePickupCollisions();

		view.setCenter(player->getPosition());
		crossingViewLimitsAdjustment();
		
		if(player->getGlobalBounds().intersects(exit->getGlobalBounds()) && exitUnlocked)
		{
			levelFinished = true;
		}
		
		if (player->getLives() <= 0)
		{
			manageEndGame();
		}
	}

	void GameScreen::centerInterfaceToView()
	{
		int positionFactor = 50;
		for (int i = 0; i < player->getLives(); i++)
		{
			player->getLivesDash()->operator[](i).setPosition(view.getCenter() + view.getSize() * 0.5f - Vector2f(10 + positionFactor, 120));
			positionFactor += 50;
		}
		scoreText.setPosition(view.getCenter() - view.getSize() * 0.5f + Vector2f(5, 5));
		scoreText.setString("Score : " + std::to_string(score));

		weaponIcon.setPosition(view.getCenter() - view.getSize() * 0.5f + Vector2f(5, 40));

 		waveLabel.setPosition(view.getCenter() - Vector2f(-30, 120));
		roomLabel.setPosition(view.getCenter() - Vector2f(-30, 20));

		livesText.setPosition(view.getCenter() + view.getSize() * 0.5f - Vector2f(200, 45));
		livesText.setString("Health : " + std::to_string(player->getHealth()));

		currentAmmoText.setPosition(view.getCenter() - view.getSize() * 0.5f + Vector2f(60, 50));

		const std::string currentAmmoString = (player->getCurrentWeapon().getWeaponType() != DEFAULT ?
			"Ammo : " + std::to_string(player->getCurrentWeapon().getAmmo()) : "");
		currentAmmoText.setString(currentAmmoString);
	}

	void GameScreen::draw()
	{
		centerInterfaceToView();

		mainWin->clear();
		mainWin->setView(view);

		for (int i = 0; i < FIELD_TILE_AMOUNT; i++)
		{
			//On ajuste la position du sprite de tuile
			field.setPosition(fieldPositions[i]);

			//On "étampe" la tuile
			mainWin->draw(field);
		}

		if (player->getIsActive())
			player->draw(mainWin);

		enemyHandler->drawEnemies(mainWin);
		enemyHandler->drawObstacles(mainWin);

		for (int i = 0; i < Weapon::PICKABLE_WEAPON_COUNT; ++i)
		{
			weapons[i]->drawProjectiles(mainWin);
		}

		for (Pickup* pickup : pickups)
		{
			if (pickup->getIsActive())
			{
				mainWin->draw(*pickup);
			}
		}

		if (exitUnlocked)
		{
			mainWin->draw(*exit);
		}

		if (--roomTextInterval > 0)
		{
			mainWin->draw(roomLabel);
		}
		if (--waveTextInterval > 0)
		{
			mainWin->draw(waveLabel);
		}

		mainWin->draw(scoreText);
		mainWin->draw(currentAmmoText);
		mainWin->draw(livesText);
		for (int i = 0; i < player->getLives(); i++)
		{
			mainWin->draw(player->getLivesDash()->operator[](i));
		}

		if (player->getCurrentWeapon().getWeaponType() != DEFAULT)
			mainWin->draw(weaponIcon);

		mainWin->display();
	}

	//Ici si on dépasse la "surface de jeu" on est ramené à l'intérieur.
	void GameScreen::crossingViewLimitsAdjustment()
	{
		if (view.getCenter().x < VIEW_LIMIT_MIN_X)
		{
			view.setCenter(VIEW_LIMIT_MIN_X, view.getCenter().y);
		}
		else if (view.getCenter().x > VIEW_LIMIT_MAX_X)
		{
			view.setCenter(VIEW_LIMIT_MAX_X, view.getCenter().y);
		}

		if (view.getCenter().y < VIEW_LIMIT_MIN_Y)
		{
			view.setCenter(view.getCenter().x, VIEW_LIMIT_MIN_Y);
		}
		else if (view.getCenter().y > VIEW_LIMIT_MAX_Y)
		{
			view.setCenter(view.getCenter().x, VIEW_LIMIT_MAX_Y);
		}
	}
}
