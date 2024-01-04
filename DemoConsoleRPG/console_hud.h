#pragma once

#include <array>
#include <string>

class ConsoleHUD
{
private:
  std::array<std::string, 3> mTopHUD;
  std::array<std::string, 3> mBottomHUD;
  std::string mCommandString;

public:
  void showTopDivider();
  void showBottomDivider();
  void setTopHud(std::string str, size_t line);
  void displayTopHUD();
  void setBottomHUD(std::string str, size_t line);
  void displayBottomHUD();
  void displayCommandString();
};