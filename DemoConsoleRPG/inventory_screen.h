#pragma once
#include "screen.h"
#include "player.h"
#include "inventory.h"

class InventoryScreen : public Screen
{
private:
	Player& mPlayer;
	Inventory& mInventory;
	bool mRenderScreen;
	const size_t mInventorySize;
	void showInventory();

public:
	InventoryScreen();
	void init() override;
	void inputHandler() override;
	void update() override;
	void render() override;
};