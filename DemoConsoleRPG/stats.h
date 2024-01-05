#pragma once

#include "player.h"
//#include "inventory.h"
#include <memory>

class Stats
{
private:
  Player& mPlayer;
//  Inventory& mInventory;
  static inline Stats* mpInstance{ nullptr };

public:
  Stats(Player& player/*, Inventory& inventory*/);
  static Player& getPlayer();
//  static Inventory& getInventory();
};