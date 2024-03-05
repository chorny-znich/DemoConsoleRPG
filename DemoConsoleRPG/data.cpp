#include "data.h"
#include "game_data.h"
#include <cassert>

Data::Data()
{
  assert(mpInstance == nullptr);
  mpInstance = this;
}

void Data::init()
{
  std::unordered_map<std::string, size_t> items;
  ini::Document doc = ini::Load(GameData::path::ItemsInfo);
  ini::Section section = doc.GetSection("general");
  items.insert({ "potion", std::stoul(section.at("Potion_amount")) });
  items.insert({ "weapon", std::stoul(section.at("Weapon_amount")) });
  items.insert({ "armor", std::stoul(section.at("Armor_amount")) });
  
  // Create potion objects
  for (size_t i{ 1 }; i <= items.at("potion"); i++) {
    std::string sectionName = "potion_" + std::to_string(i);
    ini::Section section = doc.GetSection(sectionName);
    if (section.at("Type") == "HEALING_POTION") {
      HealingPotion pPotion;
      pPotion.setName(section.at("Name"));
      mPotionDatabase.insert({i, std::move(pPotion) });
    }
  }
  // Create weapon objects
  for (size_t i{ 1 }; i <= items.at("weapon"); i++) {
    std::string sectionName = "weapon_" + std::to_string(i);
    ini::Section section = doc.GetSection(sectionName);
    if (section.at("Type") == "WEAPON") {
      Weapon pWeapon;
      pWeapon.setName(section.at("Name"));
      pWeapon.setDamage({ std::stoul(section.at("Damage_min")), std::stoul(section.at("Damage_max")) });
      mWeaponDatabase.insert({ i, std::move(pWeapon) });
    }
  }
  // Create armor objects
  for (size_t i{ 1 }; i <= items.at("armor"); i++) {
    std::string sectionName = "armor_" + std::to_string(i);
    ini::Section section = doc.GetSection(sectionName);
    if (section.at("Type") == "ARMOR") {
      Armor pArmor(std::stoul(section.at("Armor")));
      pArmor.setName(section.at("Name"));
      mArmorDatabase.insert({ i, std::move(pArmor) });
    }
  }
}
