#include "stats.h"
#include <assert.h>

Stats::Stats(Player& player, Inventory& inventory) :
  mPlayer{player},
  mInventory{inventory}
{
  assert(mpInstance == nullptr);
  mpInstance = this;
}

Player& Stats::getPlayer()
{
  auto& player = mpInstance->mPlayer;
  return player;
}

Inventory& Stats::getInventory()
{
  auto& inventory = mpInstance->mInventory;
  return inventory;
}