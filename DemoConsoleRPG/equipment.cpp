#include "equipment.h"
#include "game_object_type.h"
#include <format>

void Equipment::equip(std::shared_ptr<GameObject> pObject)
{
  if (pObject->getType() == GameObjectType::WEAPON) {
    mEquipment["Right hand"] = pObject;
  }
  if (pObject->getType() == GameObjectType::ARMOR && pObject->getSubType() == GameObjectSubType::CHEST) {
    mEquipment["Chest"] = pObject;
  }
}

std::string Equipment::show() const
{
  std::string result{};
  result.append("EQUIPMENT:\n");
  for (auto [first, second] : mEquipment) {
    if (second != nullptr) {
      result.append(std::format("{} - {}", first, second->getName()));
    }
    else {
      result.append(std::format("{} -", first));
    }
  }
  result.append("\n\n");
  return result;
}