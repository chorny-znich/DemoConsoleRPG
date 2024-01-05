#pragma once

#include "game_object_type.h"
#include "game_data.h"

class GameObject
{
private:
  GameData::Position mPosition;
  char mSymbol;

protected:
  GameObjectType mType;
  GameObjectSubType mSubType;

public:
  GameObject(GameObjectType type, GameObjectSubType subType);
  void setType(GameObjectType type);
  GameObjectType getType() const;
  void setSubType(GameObjectSubType subType);
  GameObjectSubType getSubType() const;
  void setPosition(GameData::Position pos);
  GameData::Position getPosition() const;
  void setSymbol(char symbol);
  char getSymbol() const;
};