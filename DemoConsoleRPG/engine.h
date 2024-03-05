#pragma once

#include "game_state.h"
#include "data.h"

class Engine
{ 
private:
  GameState mGameState;
  Data mData;
  
  bool mRunning{ true };/*

  /*Map mCurrentMap; 
  Player mPlayer; 
  Coin mCoin;
  PlayerInterface mInterface;
  
  void collisionDetection(Position pos, Movement move); */ 
  void init();
  void input();
  void update();
  void render();

 // void prepareInterface();
  
public:
  void run();
};