#pragma once

#include "location.h"
#include <vector>
#include <string>
//#include <utility>
#include <SFML/System.hpp>

namespace GameData { 
  using TextMap = std::vector<std::string>;
  using LocationMap = std::vector<Location>; 
  using Position = std::pair<size_t, size_t>;
  using Movement = std::pair<int, int>;

  const sf::Vector2u DICE{ 1, 10 };

  enum class Screens {
    MENU_SCREEN,
    EXPLORE_SCREEN,
    PLAYER_SCREEN,
    INVENTORY_SCREEN,
    SHOP_SCREEN
  };

  inline namespace path {
    const std::string PlayerInfo = R"(data/player.txt)";
    const std::string ItemsInfo = R"(data/items.txt)";
  } /*
  enum class RPClass {
    Adventurer
  };*/
}