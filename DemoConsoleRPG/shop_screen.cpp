#include "shop_screen.h"
#include <iostream>
#include <format>

void ShopScreen::showStaff()
{
  std::cout << std::format("\t\tSHOP");
}

ShopScreen::ShopScreen() :
  mRenderScreen{true}
{
}

void ShopScreen::init()
{
}

void ShopScreen::inputHandler()
{
}

void ShopScreen::update()
{
}

void ShopScreen::render()
{
  if (mRenderScreen) {
    showStaff();
    mRenderScreen = false;
  }
}
