#pragma once

#include "screen.h"
#include "map.h"
#include "player.h" /*
#include "inventory.h"
#include "enemy_manager.h"
#include "object_manager.h" */
#include "console_hud.h"
#include "level.h"
//#include "stats.h"

class ExploreScreen : public Screen
{	
private:
	enum class GameplayState 
	{
		START,
		PLAYER_INPUT,
		PLAYER_TURN,
		PLAYER_TURN_SHOW,
		ENEMY_TURN,
		ENEMY_TURN_SHOW
	};
	GameplayState mState{ GameplayState::START };
	
	Player mPlayer; /*
	Inventory mInventory;
	EnemyManager mEnemyManager;
	ObjectManager mObjectManager; */
	ConsoleHUD mConsoleHUD;
	Level mLevel;
	Map mCurrentMap;
//	Stats mStats;
	 
	bool collisionDetection(GameData::Position pos, GameData::Movement move); /*
	bool battleDetection(GameData::Position pos, GameData::Movement move);
	bool checkPlayerNearby(GameData::Position pos);
	void pickItem();
	void useLadder();
	void showStats(Player& player);
	void showInventory(); */
	std::string showLocationInfo();
	void changeMap();

public:
	ExploreScreen();

	void init() override;
	void inputHandler() override;
	void update() override;
	void render() override;
	//Player& getCurrentPlayer();
};