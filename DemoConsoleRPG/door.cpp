#include "door.h"

Door::Door() :
  GameObject(GameObjectType::DOOR, GameObjectSubType::NONE)
{
}

void Door::setStatus(DoorStatus status)
{
  mStatus = status;
}

DoorStatus Door::getStatus() const
{
  return mStatus;
}
