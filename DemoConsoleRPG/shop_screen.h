#pragma once

#include "screen.h"
#include "shop.h"

class ShopScreen : public Screen
{
private:
	Shop mShop;
  bool mRenderScreen;
	void showStaff();

public:
	ShopScreen();
	void init() override;
	void inputHandler() override;
	void update() override;
	void render() override;
};