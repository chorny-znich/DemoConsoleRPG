#include "console_hud.h"
#include <iostream>
#include <memory>

// Show a divider of the user interface elements
void ConsoleHUD::showDivider(char ch, size_t width)
{
  std::cout << std::string(width, ch) << "\n\n";
}

// Add the text to the appropriate container
void ConsoleHUD::addToHud(HUD_Type type, std::string str, size_t line)
{
  switch (type) {
  case HUD_Type::PLAYER_INFO:
    mPlayerInfo.at(line) = std::move(str);
    break;
  case HUD_Type::LOCATION_INFO:
    mLocationInfo.at(line) = std::move(str);
    break;
  case HUD_Type::GAME_LOG:
    mGameLog.at(line) = std::move(str);
    break;
  }
}

void ConsoleHUD::display(HUD_Type type)
{
  std::array<std::string, 3> arrayToPrint;
  switch (type) {
  case HUD_Type::PLAYER_INFO:
    arrayToPrint = mPlayerInfo;
    break;
  case HUD_Type::LOCATION_INFO:
    arrayToPrint = mLocationInfo;
    break;
  case HUD_Type::GAME_LOG:
    arrayToPrint = mGameLog;
    break;
  }

  for (const auto& str : arrayToPrint) {
    std::cout << str << '\n';
  }
  std::cout << '\n';
}

void ConsoleHUD::displayCommandString()
{
  std::cout << "\nYour action: ";
}

void ConsoleHUD::clear()
{
  mPlayerInfo.fill("");
  mLocationInfo.fill("");
  mGameLog.fill("");
}