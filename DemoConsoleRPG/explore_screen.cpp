#include "explore_screen.h"
#include <iostream> 
#include <string>
#include <format> /*
#include "game_data.h"
/*#include "map_symbols.h"*/ 
/*#include "money.h"
#include "ladder.h"
#include "potion.h"
#include "game_object.h"
#include "entity.h"
#include "battle.h" */
#include "screen_manager.h" 
#include "game_state.h"

ExploreScreen::ExploreScreen() :
  mCurrentMap{0}/*,
  mStats{mPlayer, mInventory}*/
{}

void ExploreScreen::init()
{
  mLevel.init();
  changeMap();   
}

void ExploreScreen::inputHandler()
{ 
  if (mState == GameplayState::PLAYER_INPUT) {  
    mConsoleHUD.displayCommandString();
    std::string cmd;
    std::cin >> cmd;
    
    if (cmd == "quit") {
      GameState::destroyScreen();
    } /*
    else if (cmd == "west") {
      mPlayer.moveWest();
      mPlayer.moving(true);
    }
    else if (cmd == "east") {
      mPlayer.moveEast();
      mPlayer.moving(true);
    }
    else if (cmd == "north") {
      mPlayer.moveNorth();
      mPlayer.moving(true);
    }
    else if (cmd == "south") {
      mPlayer.moveSouth();
      mPlayer.moving(true);
    }
    else if (cmd == "pick") {
      pickItem();
    }
    else if (cmd == "go") {
      useLadder();
    }
    else if (cmd == "hero") {
      showStats(mPlayer);
    }
    else if (cmd == "bag") {
      showInventory();
    } */
    mState = GameplayState::PLAYER_TURN;
  }
}

void ExploreScreen::update()
{
  if (mState == GameplayState::PLAYER_TURN) { /*
    if (mPlayer.isMoving()) {
      if (battleDetection(mPlayer.getPosition(), mPlayer.getMovement())) {
        Enemy& enemy{ mEnemyManager.getEnemy({ mPlayer.getPosition().first + mPlayer.getMovement().first,
          mPlayer.getPosition().second + mPlayer.getMovement().second }) };
        Battle battle(mPlayer, enemy);
        mConsoleHUD.setBottomHUD(battle.playerAttack(), 1);
        if (!enemy.isActive()) {
          mCurrentMap.clearEnemy(enemy.getPosition());
        }
      }
      else if (!collisionDetection(mPlayer.getPosition(), mPlayer.getMovement())) { 
        mCurrentMap.clearPlayer(mPlayer.getPosition()); 
        mPlayer.update();
        mConsoleHUD.setBottomHUD("", 1);
      } 
    } 
    mConsoleHUD.setBottomHUD(showLocationInfo(), 0); */
    mState = GameplayState::PLAYER_TURN_SHOW;
  } 
  if (mState == GameplayState::ENEMY_TURN) { /*
    std::vector<Enemy>& enemies = mEnemyManager.getEnemies();
    mConsoleHUD.setBottomHUD(std::string{ std::format("") }, 2);
    for (auto& enemy : enemies) {
      if (enemy.isActive()) {
        // the enemy is near the player
        if (checkPlayerNearby(enemy.getPosition())) {
          enemy.setBattleStatus(true);
        }
        // enemy attack player
        if (enemy.isInBattle()) {
          Battle battle(mPlayer, enemy);
          mConsoleHUD.setBottomHUD(battle.enemyAttack(), 2);
          if (mPlayer.getHealth() <= 0) {
            GameState::destroyAllScreens();
          }
        }
        else {
          // enemy move
          enemy.move();
          if (!collisionDetection(enemy.getPosition(), enemy.getMovement()) &&
            (!battleDetection(enemy.getPosition(), enemy.getMovement()))) {
            mCurrentMap.clearEnemy(enemy.getPosition());
            enemy.update();
          }
        }
      } 
    } */
    mState = GameplayState::ENEMY_TURN_SHOW;
  } 
  // prepare the current map and the interface to render
  if (mState == GameplayState::PLAYER_TURN_SHOW || mState == GameplayState::ENEMY_TURN_SHOW || 
    mState == GameplayState::START) {
    mCurrentMap.createRenderMap(); /*
    mCurrentMap.setObjects(mObjectManager.getObjects());
    mCurrentMap.setEnemies(mEnemyManager.getEnemies());
    mCurrentMap.setPlayer(mPlayer.getPosition());
    
    mConsoleHUD.setTopHud(std::string{ std::format("Name: {} exp:{} ${}", mPlayer.getName(), mPlayer.getExperience(),
      mPlayer.getMoney()) }, 0);
    mConsoleHUD.setTopHud(std::string{ std::format("HP:{}/{}", mPlayer.getHealth(), mPlayer.getMaxHealth()) }, 1);
    mConsoleHUD.setTopHud(std::string{ std::format("Atk:{} Def:{}", mPlayer.getAttack(), mPlayer.getDefence()) }, 2); */
  } 
}

void ExploreScreen::render()
{ 
  if (mState == GameplayState::PLAYER_TURN_SHOW || mState == GameplayState::ENEMY_TURN_SHOW || 
    mState == GameplayState::START) {
    mConsoleHUD.showTopDivider();
    mConsoleHUD.displayTopHUD(); 
    mCurrentMap.render();  
    mConsoleHUD.displayBottomHUD();
    mConsoleHUD.showBottomDivider();
    if (mState == GameplayState::ENEMY_TURN_SHOW || mState == GameplayState::START) {
      mState = GameplayState::PLAYER_INPUT;
    }
    else if (mState == GameplayState::PLAYER_TURN_SHOW) {
      mState = GameplayState::ENEMY_TURN;
    }
  }
}
/*
bool ExploreScreen::checkPlayerNearby(GameData::Position pos)
{
  GameData::LocationMap& map = mCurrentMap.getMap();
  const size_t RowSize = mCurrentMap.getMapSize().x;
  size_t index = pos.second * RowSize + pos.first;
  bool battleStatus{ false };
  // check if the player left of the enemy
  if ((index % (RowSize) != 0) && (map.at(index - 1).isPlayer())) {
    battleStatus = true;
  }
  // check if the player right of the enemy
  else if ((index % (RowSize + 1) != 0)  && (map.at(index + 1).isPlayer())) {
    battleStatus = true;
  }
  // check if the player above the enemy
  else if ((index >= RowSize) && (map.at(index - RowSize).isPlayer())) {
    battleStatus = true;
  }
  // check if the player below the enemy
  else if ((index < mCurrentMap.getMapSize().y * RowSize - RowSize) && (map.at(index + RowSize).isPlayer())) {
    battleStatus = true;
  }
  
  return battleStatus;
}

bool ExploreScreen::collisionDetection(GameData::Position pos, GameData::Movement move)
{
  GameData::LocationMap& map = mCurrentMap.getMap();
  GameData::Position newPosition{ pos.first + move.first, pos.second + move.second };
  if (map.at(newPosition.second * mCurrentMap.getMapSize().x + newPosition.first).isBarrier()) {
    mPlayer.moving(false);
    return true;
  }
  
  return false;
}

bool ExploreScreen::battleDetection(GameData::Position pos, GameData::Movement move)
{
  GameData::LocationMap& map = mCurrentMap.getMap();
  GameData::Position newPosition{ pos.first + move.first, pos.second + move.second };
  if (map.at(newPosition.second * mCurrentMap.getMapSize().x + newPosition.first).isEnemy()) {
    mPlayer.moving(false);
    return true;
  }
  if (map.at(newPosition.second * mCurrentMap.getMapSize().x + newPosition.first).isPlayer()) {
    try {
      Enemy& enemy = mEnemyManager.getEnemy(pos);
      enemy.setBattleStatus(true);
    }
    catch (std::runtime_error re) {
      std::cout << std::format("{} in battleDetection()\n", re.what());
    }
    return true;
  }

  return false;
}

void ExploreScreen::pickItem()
{
  GameData::Position currentPlayerLocation = mPlayer.getPosition();
  Location& location = mCurrentMap.getCurrentLocation(currentPlayerLocation);
  if (location.isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject(currentPlayerLocation);
    if (pObject->getType() == GameObjectType::MONEY) {
      auto pMoneyObject = std::static_pointer_cast<Money>(pObject);
      mPlayer.increaseMoney(pMoneyObject->getAmount());
      mConsoleHUD.setBottomHUD(std::format("You pick up ${}", pMoneyObject->getAmount()), 1);
      location.setObject(false);
      mObjectManager.destroyObject(currentPlayerLocation);
      location.setSymbol(' ');
    } else if (pObject->getType() == GameObjectType::HEALING_POTION) {
      auto pHelaingPotionObject = std::static_pointer_cast<HealingPotion>(pObject);
      //mPlayer.increaseMoney(pMoneyObject->getAmount());
      mConsoleHUD.setBottomHUD(std::format("You pick up a healing potion"), 1);
      location.setObject(false);
      mObjectManager.destroyObject(currentPlayerLocation);
      location.setSymbol(' ');
    }
  }
  else {
    mConsoleHUD.setBottomHUD(std::format("Nothing to pick up here"), 1);
  } 
}

void ExploreScreen::useLadder()
{
  GameData::Position currentPlayerLocation = mPlayer.getPosition();
  Location& location = mCurrentMap.getCurrentLocation(currentPlayerLocation);
  if (location.isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject(currentPlayerLocation);
    if (pObject->getType() == GameObjectType::LADDER) {
      auto pLadderObject = std::static_pointer_cast<Ladder>(pObject);
      mConsoleHUD.setBottomHUD(std::format("You use the ladder"), 1);
      mLevel.setCurrentMapIndex(pLadderObject->getMapIndexTo());
      mLevel.setPlayerSpawnPosition(pLadderObject->getPlayerSpawnTo());
      changeMap();
    }
  }
  else {
    mConsoleHUD.setBottomHUD(std::format("There is no ladder here"), 1);
  }
}
 
void ExploreScreen::showStats(Player& player)
{
  ScreenManager::createScreen(GameData::Screens::PLAYER_SCREEN);
}

void ExploreScreen::showInventory()
{
  ScreenManager::createScreen(GameData::Screens::INVENTORY_SCREEN);
}

std::string ExploreScreen::showLocationInfo()
{
  std::string result{};

  GameData::Position currentPlayerLocation = mPlayer.getPosition();
  Location& location = mCurrentMap.getCurrentLocation(currentPlayerLocation);
  if (location.isObject()) {
    try {
      std::shared_ptr<GameObject> pObject = mObjectManager.getObject(currentPlayerLocation);
      if (pObject->getType() == GameObjectType::MONEY) {
        auto pMoneyObject = std::static_pointer_cast<Money>(pObject);
        result = std::format("You see ${}", pMoneyObject->getAmount());
      }
      else if (pObject->getType() == GameObjectType::POTION) {
        result = std::format("You see a potion");
      }
    }
    catch (std::runtime_error re) {
      std::cout << std::format("{} in showLocationInfo()\n", re.what());
    }  
  }
  else {
    result = std::format("Nothing is interesting here");
  }
  
  return result;
}
*/
void ExploreScreen::changeMap()
{
  mCurrentMap = mLevel.getCurrentMap();
  /*mPlayer.spawn(mLevel.getPlayerSpawnPosition());
  mEnemyManager.createEnemies(mLevel.getCurrentEnemyListFilename());
  mObjectManager.createObjects(mLevel.getCurrentObjectListFilename());*/
  mState = GameplayState::START;
}
/*
Player& ExploreScreen::getCurrentPlayer()
{
  return mPlayer;
} */