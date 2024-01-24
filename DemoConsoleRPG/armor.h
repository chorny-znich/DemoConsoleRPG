#pragma once

#include "game_object.h"

class Armor : public GameObject
{
private:
  const char IMAGE{ '?' };
  size_t mArmor;

public:
  Armor(size_t armor);
  size_t getArmor() const;
};