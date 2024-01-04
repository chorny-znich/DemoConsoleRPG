#include "console_hud.h"
#include <iostream>

void ConsoleHUD::showTopDivider()
{
  std::cout << std::string(25, '=') << "\n\n";
}

void ConsoleHUD::showBottomDivider()
{
  std::cout << "\n\n" << std::string(25, '=') << "\n\n";
}

void ConsoleHUD::setTopHud(std::string str, size_t line)
{
  mTopHUD.at(line) = std::move(str);
}

void ConsoleHUD::displayTopHUD()
{
  for (const auto& str : mTopHUD) {
    std::cout << str << '\n';
  }
  std::cout << '\n';
}

void ConsoleHUD::setBottomHUD(std::string str, size_t line)
{
  mBottomHUD.at(line) = std::move(str);
}

void ConsoleHUD::displayBottomHUD()
{
  std::cout << '\n';
  for (const auto& str : mBottomHUD) {
    std::cout << str << '\n';
  }
}

void ConsoleHUD::displayCommandString()
{
  std::cout << "\nYour action: ";
}