#pragma once

#include "game_state.h"
/*
#include "map.h" 
#include "player.h" 
#include "coin.h"
#include "player_interface.h"
*/ 
class Engine
{ 
private:
  GameState mGameState;
  
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