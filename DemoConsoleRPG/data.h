#pragma once

#include <unordered_map>
#include "game_object.h"
#include "potion.h"
#include "weapon.h"
#include "armor.h"
#include <DisRealityGF.h>

class Data
{
private:
  Data* mpInstance{ nullptr };
  std::unordered_map<size_t, GameObject> mItemDatabase;
  std::unordered_map<size_t, Potion> mPotionDatabase;
  std::unordered_map<size_t, Weapon> mWeaponDatabase;
  std::unordered_map<size_t, Armor> mArmorDatabase;

public:
  Data();
  void init();
};

