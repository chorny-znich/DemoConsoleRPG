#pragma once

#include "game_object.h"
#include <unordered_map>
#include <memory>
#include <string>

class Equipment
{
private:
  enum class EquipmentSlot {
    WEAPON_RIGHT_HAND,
    CHEST
  };
  std::unordered_map<EquipmentSlot, std::string> mSlots{
    {EquipmentSlot::WEAPON_RIGHT_HAND, "Right hand"},
    {EquipmentSlot::CHEST, "Chest"}
  };
  std::unordered_map<std::string, std::shared_ptr<GameObject>> mEquipment{
    {"Right hand", nullptr},
    {"Chest", nullptr}
  };

public:
  void equip(std::shared_ptr<GameObject>);
  std::string show() const;
};

