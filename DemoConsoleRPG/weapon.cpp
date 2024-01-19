#include "weapon.h"

Weapon::Weapon() :
  GameObject(GameObjectType::WEAPON, GameObjectSubType::SWORD)
{
  setSymbol(IMAGE);
}

void Weapon::setDamage(sf::Vector2u dmg)
{
  mDamage = dmg;
}

sf::Vector2u Weapon::getDamage() const
{
  return mDamage;
}
