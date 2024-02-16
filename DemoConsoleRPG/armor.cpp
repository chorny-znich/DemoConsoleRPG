#include "armor.h"

Armor::Armor(size_t armor) :
  GameObject(GameObjectType::ARMOR, GameObjectSubType::CHEST),
  mArmor{ armor }
{
  setSymbol(IMAGE);
}

size_t Armor::getArmor() const
{
  return mArmor;
}