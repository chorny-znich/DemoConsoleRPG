#pragma once

#include "player.h"
#include "enemy.h"
#include <string>

class Battle
{ 
private:
  Player& mPlayer;
  Enemy& mEnemy;

public:
  Battle(Player& player, Enemy& enemy);
  std::string playerAttack();
  std::string enemyAttack(); 
};