#include "weapon.h"

Weapon::Weapon() :
  GameObject(GameObjectType::WEAPON, GameObjectSubType::SWORD)
{
  setSymbol(IMAGE);
}
