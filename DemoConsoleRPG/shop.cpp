#include "shop.h"
#include <format>

Shop::Shop(std::unique_ptr<Npc> pNpc) :
  mpNpc{std::move(pNpc)},
  mStaff{mpNpc->getStaff()},
  mPlayer{Stats::getPlayer()},
  mInventory{Stats::getInventory()}
{
}

void Shop::add(std::shared_ptr<GameObject> pObject)
{
}

std::string Shop::show()
{
  std::string result;
  result.append("\t\tSHOP\n");
  result.append(mpNpc->getName() + '\n');
  result.append(std::format("{} has ${}\n", mPlayer.getName(), mPlayer.getMoney()));
  result.append(mpNpc->showStaff() + '\n');

  return result;
}

size_t Shop::getSize() const
{
  return mStaff.size();
}

std::shared_ptr<GameObject>& Shop::getItem(size_t index)
{
  return mStaff.at(index);
}

void Shop::destroyItem(size_t index)
{
}
