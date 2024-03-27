#include "player.h"
#include "DisRealityGF.h"

Player::Player()
{
  create();
}

void Player::create()
{
  ini::Document doc = ini::Load(GameData::path::PlayerInfo);
  ini::Section section = doc.GetSection("player");
  setSymbol(section.at("Symbol")[0]);
  setName(section.at("Name"));
  setExperience(std::stoi(section.at("Experience")));
  setMaxHealth(std::stoi(section.at("Health")));
  setHealth(std::stoul(section.at("Health")));
  setAttack(std::stoul(section.at("Attack")));
  setDefence(std::stoul(section.at("Defence")));
  spawn({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
  setDamage({ std::stoul(section.at("Damage_min")), std::stoul(section.at("Damage_max")) });
  setMoney({std::stoul(section.at("Money"))});
}

void Player::update()
{
    mPosition.first += mMovement.first;
    mPosition.second += mMovement.second;
    moving(false);
}

void Player::moveWest() {
  mMovement = { -CHAR_STEP, 0 };
}

void Player::moveEast() {
  mMovement = { CHAR_STEP, 0 };
}

void Player::moveNorth() {
  mMovement = { 0 , -CHAR_STEP };
}

void Player::moveSouth() {
  mMovement = { 0 , CHAR_STEP };
}

void Player::moving(bool move) {
  mMoving = move;
}

bool Player::isMoving() const
{
  return mMoving;
}

void Player::setDangerStatus(bool status)
{
  mDangerStatus = status;
}

bool Player::getDangerStatus() const
{
  return mDangerStatus;
}

bool Player::levelupCheck()
{
  if (mExperience >= LevelCap.at(mLevel + 1)) {
    levelup();
    return true;
  }

  return false;
}

void Player::levelup()
{
  mLevel++;
  setAttack(getAttack() + Adventurer.at(mLevel).at("attack"));
  setDefence(getDefence() + Adventurer.at(mLevel).at("defence"));
  setMaxHealth(getMaxHealth() + Adventurer.at(mLevel).at("health"));
}