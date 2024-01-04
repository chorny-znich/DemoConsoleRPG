#include "engine.h"
#include "screen_manager.h"

#include <iostream> 
#include <format>
#include <string>
#include <Windows.h>

void Engine::init()
{
  HWND hWindowConsole = GetConsoleWindow();
  COORD bufferSize{ 800, 600 };
  SetConsoleScreenBufferSize(hWindowConsole, bufferSize);
  MoveWindow(hWindowConsole, 600, 200, bufferSize.X, bufferSize.Y, TRUE);
}

void Engine::input()
{ 
  if (!mGameState.isEmpty()) {
    mGameState.getCurrent()->inputHandler();
  }
}

void Engine::update()
{ 
  if (!mGameState.isEmpty()) {
    mGameState.getCurrent()->update();
  } 
}

/**
* @brief Render the console graphic from the current active screen
*/ 
void Engine::render()
{ 
  if (!mGameState.isEmpty()) {
    system("cls");
    mGameState.getCurrent()->render();
  } 
}
/*
void Engine::update() {
  collisionDetection(mPlayer.getPosition(), mPlayer.getMovement());
  mPlayer.update(mCurrentMap.getMap());
  prepareInterface();
}
*/ 
void Engine::run() 
{
  init();
  ScreenManager::createScreen(GameData::Screens::MENU_SCREEN);

  while (mRunning && !mGameState.isEmpty()) {
    render();
    input();
    update();
  }
  system("cls");
  std::cout << std::format("The game is over\n");
}
/*
void Engine::collisionDetection(Position pos, Movement move) {
  GameMap& map = mCurrentMap.getMap();
  Position newPosition{ pos.first + move.first, pos.second + move.second };
  if (map[newPosition.second][newPosition.first] == '#') {
    mPlayer.moving(false);
  }
  else {
    mPlayer.moving(true);
  }

  if (map[newPosition.second][newPosition.first] == GOLD_ITEM) {
    mPlayer.moving(true);
    map[newPosition.second][newPosition.first] = mCoin.getTerrain();
    std::string message{ "You pick coins" };
    PlayerInterface::setMessage(message, 0);
  }
}

void Engine::prepareInterface() {
  std::string playerPosition{ "Player position: (" + std::to_string(mPlayer.getPosition().first) + ", " +
    std::to_string(mPlayer.getPosition().second) + ")" };
  PlayerInterface::setMessage(playerPosition, 1);
}
*/