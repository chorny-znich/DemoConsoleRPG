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
  mData.init();
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