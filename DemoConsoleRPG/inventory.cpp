#include "inventory.h"
#include "game_object_type.h"
#include <format>

void Inventory::add(std::shared_ptr<GameObject> pObject)
{
  mInventory.push_back(std::move(pObject));
}

std::string Inventory::show()
{
  std::string result{};
  result.append("INVENTORY:\n");
  if (mInventory.size() == 0) {
    return result.append("Inventory is empty");
  }
  size_t counter{ 1 };
  for (auto pObject : mInventory) {
    std::string item{};
    if (pObject->getType() == GameObjectType::POTION && pObject->getSubType() == GameObjectSubType::HEALING_POTION) {
      item = "Healing potion";
    }
    result.append(std::format("{}. {}\n", counter++, item));
  }

  return result;
}

size_t Inventory::getSize() const
{
    return mInventory.size();
}
