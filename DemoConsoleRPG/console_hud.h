#pragma once

#include <array>
#include <string>

enum class HUD_Type {
  PLAYER_INFO,
  LOCATION_INFO,
  GAME_LOG
};

class ConsoleHUD
{
private:
  std::array<std::string, 3> mPlayerInfo;
  std::array<std::string, 3> mLocationInfo;
  std::array<std::string, 3> mGameLog;
  std::string mCommandString;

public:  
  void showDivider(char ch, size_t width);
  void AddToHud(HUD_Type type, std::string str, size_t line);
  void display(HUD_Type type);
  void displayCommandString();
  void clear();
};