#include "inventory_screen.h"
#include "stats.h"
#include "game_state.h"
#include <iostream>
#include <format>

void InventoryScreen::showInventory()
{
  std::cout << mInventory.show();
  std::cout << std::format("\n{}. Exit\n\n", mInventorySize + 1);
  std::cout << "Your action: ";
}

InventoryScreen::InventoryScreen() :
  mPlayer{ Stats::getPlayer() },
  mInventory{ Stats::getInventory() },
  mRenderScreen{ true },
  mInventorySize{ mInventory.getSize() }
{
}

void InventoryScreen::init()
{
}

void InventoryScreen::inputHandler()
{
  if (!mRenderScreen) {
    const size_t EXIT_NUMBER = mInventorySize + 1;
    size_t menuItem{ 0 };
    std::cin >> menuItem;
    switch (menuItem) {
    default:
      if (menuItem == EXIT_NUMBER) {
        GameState::destroyScreen();
      }
      else {
        std::cout << "Choose valid menu item\n\n";
        mRenderScreen = true;
        break;
      }
    }
  }
}

void InventoryScreen::update()
{
}

void InventoryScreen::render()
{
  if (mRenderScreen) {
    showInventory();
    mRenderScreen = false;
  }
}