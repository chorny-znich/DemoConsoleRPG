#include "object_manager.h"
/*#include "money.h"
#include "ladder.h"
#include "potion.h"*/
#include "map_symbols.h"
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <DisRealityGF.h>

void ObjectManager::createObjects(const std::string& filename)
{
  mObjects.clear(); /*
  std::unordered_map<std::string, size_t> objects;
  ini::Document doc = ini::Load(filename);
  ini::Section section = doc.GetSection("general");
  objects.insert({ "money", std::stoul(section.at("Money_amount")) });
  objects.insert({ "ladder", std::stoul(section.at("Ladder_amount")) });
  objects.insert({ "potion", std::stoul(section.at("Potion_amount")) });
  // Create money objects
  for (size_t i{1}; i <= objects.at("money"); i++) {
    std::shared_ptr<Money> pMoney = std::make_shared<Money>();
    std::string sectionName = "money_" + std::to_string(i);
    ini::Section section = doc.GetSection(sectionName);
    pMoney->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
    mObjects.push_back(std::move(pMoney));
  }
  // Create ladder objects
  for (size_t i{ 1 }; i <= objects.at("ladder"); i++) {
    std::shared_ptr<Ladder> pLadder = std::make_shared<Ladder>();
    std::string sectionName = "ladder_" + std::to_string(i);
    ini::Section section = doc.GetSection(sectionName);
    pLadder->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
    std::string ladderDirection = section.at("Direction_to");
    char symbol = ladderDirection == "UP" ? MapSymbols::LADDER_UP : MapSymbols::LADDER_DOWN;
    pLadder->setSymbol(symbol);
    pLadder->setMapIndexTo(std::stoi(section.at("Map_index_to")));
    pLadder->setPlayerSpawnTo({ std::stoi(section.at("Player_position_x")), std::stoi(section.at("Player_position_y")) });
    mObjects.push_back(std::move(pLadder));
  }
  // Create potion objects
  for (size_t i{ 1 }; i <= objects.at("potion"); i++) {
    std::shared_ptr<Potion> pPotion = std::make_shared<Potion>();
    std::string sectionName = "potion_" + std::to_string(i);
    ini::Section section = doc.GetSection(sectionName);
    if (section.at("Type") == "HEALING_POTION") {
      std::shared_ptr<HealingPotion> pPotion = std::dynamic_pointer_cast<HealingPotion>(pPotion);
    }
    pPotion->setPosition({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
    mObjects.push_back(std::move(pPotion));
  }*/
}
/*
std::vector<GameData::Position> ObjectManager::getObjectPositions() const
{
  std::vector<GameData::Position> objectPos;
  /*  for (const auto& object : mObjects) {
    objectPos.push_back(object.getPosition());
  } */ /*
  return objectPos;
}
*/
const std::vector<std::shared_ptr<GameObject>>& ObjectManager::getObjects() const
{
  return mObjects;
}

std::vector<std::shared_ptr<GameObject>>& ObjectManager::getObjects()
{
  return mObjects;
}

std::shared_ptr<GameObject>& ObjectManager::getObject(GameData::Position pos)
{
  for (auto& object : mObjects) {
    if (pos.first == object->getPosition().first && pos.second == object->getPosition().second) {
      return object;
    }
  }
  throw std::runtime_error("the objects doesn't exist at this position");
}

void ObjectManager::destroyObject(GameData::Position pos)
{
  auto iter = std::find_if(mObjects.begin(), mObjects.end(), [pos](const auto& obj) {
    return pos == obj->getPosition();
    });
  mObjects.erase(iter);
}