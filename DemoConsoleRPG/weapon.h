#pragma once

#include "game_object.h"

class Weapon : public GameObject
{
private:
  const char IMAGE{ '?' };
  sf::Vector2u mDamage{};

public:
  Weapon();
  void setDamage(sf::Vector2u dmg);
  sf::Vector2u getDamage() const;
};