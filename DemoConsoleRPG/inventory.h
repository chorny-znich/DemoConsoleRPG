#pragma once

#include "game_object.h"
#include <vector>
#include <memory>
#include <string>

class Inventory
{
private:
  std::vector<std::shared_ptr<GameObject>> mInventory;

public:
  void add(std::shared_ptr<GameObject> pObject);
  std::string show();
  size_t getSize() const;
};