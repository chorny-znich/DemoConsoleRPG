#include "game_object.h"

GameObject::GameObject(GameObjectType type) :
  mType{ type }
{
}

void GameObject::setType(GameObjectType type)
{
  mType = type;
}

GameObjectType GameObject::getType() const
{
    return mType;
}

void GameObject::setPosition(GameData::Position pos)
{
  mPosition = pos;
}

GameData::Position GameObject::getPosition() const
{
  return mPosition;
}

void GameObject::setSymbol(char symbol)
{
  mSymbol = symbol;
}

char GameObject::getSymbol() const
{
  return mSymbol;
}
