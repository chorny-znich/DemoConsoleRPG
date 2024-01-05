#include "player_screen.h"
#include "player.h"
#include "game_state.h"
#include "stats.h"
#include <iostream>
#include <format>
/*

//#include "game_data.h"

*/

PlayerScreen::PlayerScreen() :
  mPlayer{Stats::getPlayer()},
  mRenderScreen{true}
{
}

void PlayerScreen::showStats()
{
  std::cout << std::format("\t\tName: {}\n", mPlayer.getName());
  std::cout << std::format("Exp:{}\t${}\n", mPlayer.getExperience(), mPlayer.getMoney());
  std::cout << std::format("HP:{}\n", mPlayer.getHealth());
  std::cout << std::format("Atk:{}\tDef:{}\n\n", mPlayer.getAttack(), mPlayer.getDefence());

  std::cout << "1. Exit\n";
  std::cout << "Your action: ";
}

void PlayerScreen::init()
{
}

void PlayerScreen::inputHandler()
{
  if (!mRenderScreen) {
    size_t menuItem{ 0 };
    std::cin >> menuItem;
    switch (menuItem) {
    case 1:
      mRenderScreen = true;
      GameState::destroyScreen();
      break;
    default:
      std::cout << "Choose valid menu item\n\n";
      mRenderScreen = true;
      break;
    }
  }
}

void PlayerScreen::update()
{
}

void PlayerScreen::render()
{
  if (mRenderScreen) {
    showStats();
    mRenderScreen = false;
  }
}