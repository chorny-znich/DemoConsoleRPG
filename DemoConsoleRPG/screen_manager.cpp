#include "screen_manager.h"
#include "menu_screen.h"
#include "explore_screen.h"
#include "player_screen.h"
//#include "inventory_screen.h"
#include "game_state.h"

void ScreenManager::createScreen(GameData::Screens screenID)
{ 
	if (screenID == GameData::Screens::MENU_SCREEN)
	{
		std::unique_ptr<MenuScreen> pMenuScreen = std::make_unique<MenuScreen>();
		pMenuScreen->init();
		GameState::addScreen(std::move(pMenuScreen));
	}
	
	if (screenID == GameData::Screens::EXPLORE_SCREEN)
	{
		std::unique_ptr<ExploreScreen> pExploreScreen = std::make_unique<ExploreScreen>();
		pExploreScreen->init();
		GameState::addScreen(std::move(pExploreScreen));
	}
	if (screenID == GameData::Screens::PLAYER_SCREEN)
	{
		std::unique_ptr<PlayerScreen> pPlayerScreen = std::make_unique<PlayerScreen>();
		pPlayerScreen->init();
		GameState::addScreen(std::move(pPlayerScreen));
	}/*
	if (screenID == GameData::Screens::INVENTORY_SCREEN)
	{
		std::unique_ptr<InventoryScreen> pInventoryScreen = std::make_unique<InventoryScreen>();
		pInventoryScreen->init();
		GameState::addScreen(std::move(pInventoryScreen));
	}*/
}