#include "menu_screen.h"
#include "game_state.h"
#include <iostream>
#include <format>
#include "game_data.h"
#include "screen_manager.h"

void MenuScreen::showMainMenu()
{
  std::cout << "Console RPG ver 0.3.0\n\n";
  std::cout << "1. Play\n" << "2. Exit\n\n";
  std::cout << "Your action: ";
}
 
void MenuScreen::init()
{
}

void MenuScreen::inputHandler()
{  
  if (!mRenderScreen) {
    size_t menuItem{ 0 };
    std::cin >> menuItem;
    switch (menuItem) {
    case 1:
      mRenderScreen = true;
      ScreenManager::createScreen(GameData::Screens::EXPLORE_SCREEN);
      break;
    case 2:
      exit(0);
      break;
    default:
      std::cout << "Choose valid menu item\n\n";
      mRenderScreen = true;
      break;
    }
  }
}

void MenuScreen::update()
{
}

void MenuScreen::render()
{
  if (mRenderScreen) {
    showMainMenu();
    mRenderScreen = false;
  }
}