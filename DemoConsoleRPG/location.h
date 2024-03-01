#pragma once
/*
#include "game_object.h"
#include <memory>
#include <utility>
*/
class Location
{
private:
  char mSymbol;
  bool mBarrier{ false };
  bool mPlayer{ false };
  bool mEnemy{ false };
  bool mObject{ false };
  bool mNPC{ false };

public:
  void setSymbol(char ch);
  char getSymbol() const; 
  void setBarrier(bool value);
  bool isBarrier() const;
  void setPlayer(bool value);
  bool isPlayer() const;
  void setEnemy(bool value);
  bool isEnemy() const;
  void setObject(bool value);
  bool isObject() const;
  void setNPC(bool value);
};