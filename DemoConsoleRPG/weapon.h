#pragma once

#include "game_object.h"

class Weapon : public GameObject
{
private:
  const char IMAGE{ '?' };

public:
  Weapon();
};