#pragma once

#include "screen.h"
#include "player.h"

class PlayerScreen : public Screen
{
private:
	Player& mPlayer;
	bool mRenderScreen;
	void showStats();

public:
	PlayerScreen();
	void init() override;
	void inputHandler() override;
	void update() override;
	void render() override;
};