#pragma once

#include "screen.h"

class ShopScreen : public Screen
{
private:
  bool mRenderScreen;
	void showStaff();

public:
	ShopScreen();
	void init() override;
	void inputHandler() override;
	void update() override;
	void render() override;
};