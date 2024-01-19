#pragma once
#include "screen.h"
#include "player.h"
#include "inventory.h"
#include "equipment.h"

class InventoryScreen : public Screen
{
private:
	Player& mPlayer;
	Inventory& mInventory;
	Equipment& mEquipment;
	bool mRenderScreen;
	const size_t mInventorySize;
	void showInventory();
	void showEquipment();

public:
	InventoryScreen();
	void init() override;
	void inputHandler() override;
	void update() override;
	void render() override;
};