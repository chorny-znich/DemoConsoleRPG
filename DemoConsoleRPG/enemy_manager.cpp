#include "enemy_manager.h"
//#include <algorithm>
#include <DisRealityGF.h>

void EnemyManager::createEnemies(const std::string& filename)
{
  mEnemies.clear();
  size_t enemiesAmount{ 0 };
  ini::Document doc = ini::Load(filename);
  ini::Section section = doc.GetSection("general");
  enemiesAmount = std::stoul(section.at("Enemies_amount"));
  
  for (size_t i{ 1 }; i <= enemiesAmount; i++) {
    Enemy enemy;
    std::string sectionName = "enemy_" + std::to_string(i);
    ini::Section section = doc.GetSection(sectionName);
    enemy.spawn({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y"))});
    enemy.setSymbol(section.at("Symbol")[0]);
    enemy.setName(section.at("Name"));
    enemy.setExperienceForKill(std::stoi(section.at("Experience_for_kill")));
    enemy.setMaxHealth(std::stoi(section.at("Health")));
    enemy.setAttack(std::stoul(section.at("Attack")));
    enemy.setDefence(std::stoul(section.at("Defence")));
    enemy.setHealth(std::stoul(section.at("Health")));
    enemy.setDamage({std::stoul(section.at("Damage_min")), std::stoul(section.at("Damage_max"))});
    mEnemies.push_back(std::move(enemy));
  }
}
/*
std::vector<GameData::Position> EnemyManager::getEnemyPositions() const
{
  std::vector<GameData::Position> enemyPos;
  for (const auto& enemy : mEnemies) {
    enemyPos.push_back(enemy.getPosition());
  }
  return enemyPos;
}
*/
const std::vector<Enemy>& EnemyManager::getEnemies() const
{
    return mEnemies;
}

std::vector<Enemy>& EnemyManager::getEnemies()
{
  return mEnemies;
}

Enemy& EnemyManager::getEnemy(GameData::Position pos)
{
  for (auto& enemy : mEnemies) {
    if (pos.first == enemy.getPosition().first && pos.second == enemy.getPosition().second) {
      return enemy;
    }
  }
  throw std::runtime_error("Enemy don't exist");    
}