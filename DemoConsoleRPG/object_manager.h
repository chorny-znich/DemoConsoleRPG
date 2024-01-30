#pragma once

#include "game_object.h"
#include <memory>
#include <vector>
#include <string>

class ObjectManager
{
private:
  std::vector<std::shared_ptr<GameObject>> mObjects;

public:
  void createObjects(const std::string& filename);
  const std::vector<std::shared_ptr<GameObject>>& getObjects() const;
  std::vector<std::shared_ptr<GameObject>>& getObjects();
  std::shared_ptr<GameObject>& getObject(GameData::Position pos);
  void destroyObject(GameData::Position pos);
};