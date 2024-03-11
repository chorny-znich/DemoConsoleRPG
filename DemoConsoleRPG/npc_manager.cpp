#include "Npc_manager.h"
#include "data.h"
#include "potion.h"
#include "weapon.h"
#include "armor.h"
#include <DisRealityGF.h>

void NpcManager::createNpcs(const std::string& filename)
{
  mNpc.clear();
  size_t NpcAmount{ 0 };
  ini::Document doc = ini::Load(filename);
  ini::Section section = doc.GetSection("general");
  NpcAmount = std::stoul(section.at("Npc_amount"));

  for (size_t i{ 1 }; i <= NpcAmount; i++) {
    Npc npc;
    std::string sectionName = "npc_" + std::to_string(i);
    ini::Section section = doc.GetSection(sectionName);
    size_t numberOfItems = std::stoul(section.at("NumberOfItems"));
    npc.spawn({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
    npc.setSymbol(section.at("Symbol")[0]);
    npc.setName(section.at("Name"));
    for (size_t j{ 1 }; j <= numberOfItems; j++) {
      std::string keyName = "Item_" + std::to_string(j);
      size_t itemId = std::stoul(section.at(keyName));
      auto object = Data::getItem(itemId);

      if (object->getType() == GameObjectType::POTION) {
        if (object->getSubType() == GameObjectSubType::HEALING_POTION) {
          auto potion = std::static_pointer_cast<Potion>(object);

          std::shared_ptr<HealingPotion> pHealingPotion{ std::make_shared<HealingPotion>() };
          pHealingPotion->setName(potion->getName());
          npc.addStaff(pHealingPotion);
        }
      }
      else if (object->getType() == GameObjectType::WEAPON) {
        auto weapon = std::static_pointer_cast<Weapon>(object);

        std::shared_ptr<Weapon> pWeapon = std::make_shared<Weapon>();
        pWeapon->setName(weapon->getName());
        pWeapon->setDamage({ weapon->getDamage() });
        npc.addStaff(pWeapon);
      }
      else if (object->getType() == GameObjectType::ARMOR) {
        auto armor = std::static_pointer_cast<Armor>(object);

        std::shared_ptr<Armor> pArmor = std::make_shared<Armor>(std::stoul(section.at("Armor")));
        pArmor->setName(section.at("Name"));
        npc.addStaff(pArmor);
      }
    }

    mNpc.push_back(std::move(npc));
  }
}

const std::vector<Npc>& NpcManager::getNpcs() const
{
  return mNpc;
}

std::vector<Npc>& NpcManager::getNpcs()
{
  return mNpc;
}

Npc& NpcManager::getNpc(GameData::Position pos)
{
  for (auto& npc : mNpc) {
    if (pos.first == npc.getPosition().first && pos.second == npc.getPosition().second) {
      return npc;
    }
  }
  throw std::runtime_error("Enemy don't exist");
}
