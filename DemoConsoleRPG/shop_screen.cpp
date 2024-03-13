#include "shop_screen.h"
#include "game_state.h"
#include "current_npc.h"
#include <iostream>
#include <format>
#include <string>

ShopScreen::ShopScreen() :
  mShop{ CurrentNpc::getNpc() },
  mRenderScreen{ true }
{
}

void ShopScreen::showStaff()
{
  std::cout << mShop.show();
  std::cout << std::format("\n{}. Exit\n\n", mShop.getSize() + 1);
  std::cout << "Your action: ";
}

void ShopScreen::init()
{
}

void ShopScreen::inputHandler()
{ 
  if (!mRenderScreen) { 
    const size_t EXIT_NUMBER = mShop.getSize() + 1;
    size_t menuItem{ 0 };
    std::string cmd{};
    std::cin >> menuItem;

    if (menuItem == EXIT_NUMBER) {
      GameState::destroyScreen();
    }
    else if (menuItem > EXIT_NUMBER || menuItem < 1) {
      std::cout << "Choose valid menu item\n\n";
      mRenderScreen = true;
    }
    else { 
      std::cin >> cmd;
      //auto pCurrentItem = mInventory.getItem(menuItem - 1);
      if (cmd == "buy") {
        mShop.buy(menuItem - 1);
      }
        mRenderScreen = true;
    } /*
      else if (cmd == "equip" && pCurrentItem->getType() == GameObjectType::WEAPON) {
        mEquipment.equip(pCurrentItem);
        auto pWeapon = std::static_pointer_cast<Weapon>(pCurrentItem);
        mPlayer.setDamage({ pWeapon->getDamage().x, pWeapon->getDamage().y });
        mRenderScreen = true;
      }
      else if (cmd == "equip" && pCurrentItem->getType() == GameObjectType::ARMOR) {
        mEquipment.equip(pCurrentItem);
        auto pArmor = std::static_pointer_cast<Armor>(pCurrentItem);
        mPlayer.setArmor({ pArmor->getArmor() });
        mRenderScreen = true;
      }
      else {
        std::cout << "Enter the proper action\n\n";
        mRenderScreen = true;
      }*/
  }
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
