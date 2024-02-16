#include "battle.h"
#include <format>
#include <DisRealityGF.h>

Battle::Battle(Player& player, Enemy& enemy) :
  mPlayer{player},
  mEnemy{enemy}
{
  mEnemy.setBattleStatus(true);
}

std::string Battle::playerAttack()
{
  std::string str{ std::format("You attack {}", mEnemy.getName()) };
  // check if the player hit the enemy
  size_t rollAttack = dr::EngineUtility::getRandomInRange(GameData::DICE.x, GameData::DICE.y);
  str += std::format(" [dice:{} + Atk:{} vs Enemy Def:{}]\n", rollAttack, mPlayer.getAttack(), mEnemy.getDefence());
  if (mPlayer.getAttack() + rollAttack >= mEnemy.getDefence()) {
    size_t damage = mPlayer.getDamageValue();
    mEnemy.decreaseHealth(damage);
    if (mEnemy.getHealth() == 0) {
      str += std::format("You deal {} points of damage. You kill {}", damage, mEnemy.getName());
      mEnemy.setBattleStatus(false);
      mEnemy.setActiveStatus(false);
      mEnemy.isDead();
      mPlayer.increaseExperience(mEnemy.getExperienceForKill());
      if (mPlayer.levelupCheck()) {
        str += std::format("\nYou gained new level!");
      }
    }
    else {
      str += std::format("You deal {} points of damage. {} has {} points of health",
        damage, mEnemy.getName(), mEnemy.getHealth());
    }
  }
  else {
    str += "You didn't the Enemy";
  }

  return str;
}

std::string Battle::enemyAttack()
{
  std::string str{ std::format("{} attacks you ", mEnemy.getName()) };
  // check if the enemy hit the player
  size_t rollAttack = dr::EngineUtility::getRandomInRange(GameData::DICE.x, GameData::DICE.y);
  str += std::format(" [dice:{} + {} Atk:{} vs your Def:{}]\n", rollAttack, mEnemy.getName(), mEnemy.getAttack(), mPlayer.getDefence());

  if (mEnemy.getAttack() + rollAttack >= mPlayer.getDefence()) {
    size_t damage = mEnemy.getDamageValue();
    size_t damageToPlayer = damage - mPlayer.getArmor();

    if (damageToPlayer > 0) {
      mPlayer.decreaseHealth(damageToPlayer);
    }
    else {
      damageToPlayer = 0;
    }

    if (mPlayer.getHealth() == 0) {
      str += std::format("You took {} points of damage. You killed by {}", damageToPlayer, mEnemy.getName());
      mEnemy.setBattleStatus(false);
    }
    else {
      str += std::format("You took {} points of damage ({} absorbed by armor)", damageToPlayer, damage - damageToPlayer);
    }
  }
  else {
    str += std::format("{} didn't hit you", mEnemy.getName());
  }

  return str;
}