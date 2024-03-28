#include "explore_screen.h"
#include <iostream> 
#include <string>
#include <format> 
#include "money.h"
#include "ladder.h"
#include "door.h"
#include "potion.h"
#include "weapon.h"
#include "armor.h"
#include "battle.h"
#include "screen_manager.h" 
#include "game_state.h"

#include <DisRealityGF.h>

ExploreScreen::ExploreScreen() :
  mCurrentMap{0},
  mStats{ mPlayer, mInventory, mEquipment }
{}

void ExploreScreen::init()
{
  mLevel.init();
  changeMap();   
}

void ExploreScreen::inputHandler()
{ 
  if (mState == GameplayState::PLAYER_INPUT) { 
    mConsoleHUD.clear();
    mConsoleHUD.displayCommandString();
    std::string cmd;
    std::cin >> cmd;
    
    if (cmd == "quit") {
      GameState::destroyScreen();
    }
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
    }
    else if (cmd == "open") {
      checkDoors(mPlayer.getPosition());
    }
    else if (cmd == "trade") {
      if (checkNpcNearby(mPlayer.getPosition())) {
        showShop();
      }
    }
    mState = GameplayState::PLAYER_TURN;
  }
}

void ExploreScreen::update()
{
  if (mState == GameplayState::PLAYER_TURN) {
    if (mPlayer.isMoving()) {
      if (battleDetection(mPlayer.getPosition(), mPlayer.getMovement())) {
        mPlayer.setDangerStatus(true);
        Enemy& enemy{ mEnemyManager.getEnemy({ mPlayer.getPosition().first + mPlayer.getMovement().first,
          mPlayer.getPosition().second + mPlayer.getMovement().second }) };
        Battle battle(mPlayer, enemy);
        mConsoleHUD.AddToHud(HUD_Type::GAME_LOG, battle.playerAttack(), 1);
        if (!enemy.isActive()) {
          mCurrentMap.clearEnemy(enemy.getPosition());
        }
      }
      else if (!collisionDetection(mPlayer.getPosition(), mPlayer.getMovement())) {
        mCurrentMap.clearPlayer(mPlayer.getPosition()); 
        mPlayer.setDangerStatus(false);
        mPlayer.update();
        mConsoleHUD.AddToHud(HUD_Type::GAME_LOG, "", 1);
      } 
    } 
    mConsoleHUD.AddToHud(HUD_Type::LOCATION_INFO, showLocationInfo(), 0);
    mState = GameplayState::PLAYER_TURN_SHOW;
  } 
  if (mState == GameplayState::ENEMY_TURN) {
    std::vector<Enemy>& enemies = mEnemyManager.getEnemies();
    mConsoleHUD.AddToHud(HUD_Type::GAME_LOG, std::string{ std::format("") }, 2);
    for (auto& enemy : enemies) {
      if (enemy.isActive()) {
        // the enemy is near the player
        if (checkPlayerNearby(enemy.getPosition())) {
          enemy.setBattleStatus(true);
        }
        else {
          enemy.setBattleStatus(false);
        }
        // enemy attack player
        if (enemy.isInBattle()) {
          Battle battle(mPlayer, enemy);
          mConsoleHUD.AddToHud(HUD_Type::GAME_LOG, battle.enemyAttack(), 2);
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
    }
    mState = GameplayState::ENEMY_TURN_SHOW;
  } 
  // Check for the objects visibility
  if (mState == GameplayState::START || mState == GameplayState::PLAYER_TURN_SHOW) {
    if (!mPlayer.getDangerStatus()) {
      checkEnvironment(mPlayer.getPosition());
    }
  }

  // prepare the current map and the interface to render
  if (mState == GameplayState::PLAYER_TURN_SHOW || mState == GameplayState::ENEMY_TURN_SHOW || 
    mState == GameplayState::START) {
    mCurrentMap.createRenderMap();
    mCurrentMap.setObjects(mObjectManager.getObjects());
    mCurrentMap.setEnemies(mEnemyManager.getEnemies());
    mCurrentMap.setNpcs(mNpcManager.getNpcs());
    mCurrentMap.setPlayer(mPlayer.getPosition());
    
    mConsoleHUD.AddToHud(HUD_Type::PLAYER_INFO, std::string{ std::format("Name: {} exp:{} ${}", mPlayer.getName(), mPlayer.getExperience(),
      mPlayer.getMoney()) }, 0);
    mConsoleHUD.AddToHud(HUD_Type::PLAYER_INFO, std::string{ std::format("HP:{}/{}", mPlayer.getHealth(), mPlayer.getMaxHealth()) }, 1);
    mConsoleHUD.AddToHud(HUD_Type::PLAYER_INFO, std::string{ std::format("Atk:{} Def:{}", mPlayer.getAttack(), mPlayer.getDefence()) }, 2);
  }  
}

void ExploreScreen::render()
{ 
  if (mState == GameplayState::PLAYER_TURN_SHOW || mState == GameplayState::ENEMY_TURN_SHOW || 
    mState == GameplayState::START) {
    mConsoleHUD.showDivider(GameData::UI_DIVIDER_SYMBOL, GameData::UI_DIVIDER_WIDTH);
    mConsoleHUD.display(HUD_Type::PLAYER_INFO); 
    mCurrentMap.render();
    mConsoleHUD.showDivider(GameData::UI_DIVIDER_SYMBOL, GameData::UI_DIVIDER_WIDTH);
    mConsoleHUD.display(HUD_Type::LOCATION_INFO);
    mConsoleHUD.showDivider(GameData::UI_DIVIDER_SYMBOL, GameData::UI_DIVIDER_WIDTH);
    mConsoleHUD.display(HUD_Type::GAME_LOG);
    mConsoleHUD.showDivider(GameData::UI_DIVIDER_SYMBOL, GameData::UI_DIVIDER_WIDTH);
    if (mState == GameplayState::ENEMY_TURN_SHOW || mState == GameplayState::START) {
      mState = GameplayState::PLAYER_INPUT;
    }
    else if (mState == GameplayState::PLAYER_TURN_SHOW) {
      mState = GameplayState::ENEMY_TURN;
    }
  }
}

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
  if (map.at(newPosition.second * mCurrentMap.getMapSize().x + newPosition.first).isBarrier() || 
    map.at(newPosition.second * mCurrentMap.getMapSize().x + newPosition.first).isEnemy()) {
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
      mConsoleHUD.AddToHud(HUD_Type::LOCATION_INFO, std::format("You pick up ${}", pMoneyObject->getAmount()), 1);
      location.setObject(false);
      mObjectManager.destroyObject(currentPlayerLocation);
      location.setSymbol(' ');
    } 
    else if (pObject->getType() == GameObjectType::POTION) {
        if (pObject->getSubType() == GameObjectSubType::HEALING_POTION) {
          auto pHealingPotionObject = std::static_pointer_cast<HealingPotion>(pObject);
          mInventory.add(pHealingPotionObject);
          mConsoleHUD.AddToHud(HUD_Type::LOCATION_INFO, std::format("You pick up a healing potion"), 1);
          location.setObject(false);
          mObjectManager.destroyObject(currentPlayerLocation);
          location.setSymbol(' ');
        }
    }
    else if (pObject->getType() == GameObjectType::WEAPON) {
      auto pWeaponObject = std::static_pointer_cast<Weapon>(pObject);
      mInventory.add(pWeaponObject);
      mConsoleHUD.AddToHud(HUD_Type::LOCATION_INFO, std::format("You pick up a {}", pWeaponObject->getName()), 1);
      location.setObject(false);
      mObjectManager.destroyObject(currentPlayerLocation);
      location.setSymbol(' ');
    }
    else if (pObject->getType() == GameObjectType::ARMOR) {
      auto pArmorObject = std::static_pointer_cast<Armor>(pObject);
      mInventory.add(pArmorObject);
      mConsoleHUD.AddToHud(HUD_Type::LOCATION_INFO, std::format("You pick up a {}", pArmorObject->getName()), 1);
      location.setObject(false);
      mObjectManager.destroyObject(currentPlayerLocation);
      location.setSymbol(' ');
    }
  }
  else {
    mConsoleHUD.AddToHud(HUD_Type::LOCATION_INFO, std::format("Nothing to pick up here"), 1);
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
      mConsoleHUD.AddToHud(HUD_Type::LOCATION_INFO, std::format("You use the ladder"), 1);
      mLevel.setCurrentMapIndex(pLadderObject->getMapIndexTo());
      mLevel.setPlayerSpawnPosition(pLadderObject->getPlayerSpawnTo());
      changeMap();
    }
  }
  else {
    mConsoleHUD.AddToHud(HUD_Type::LOCATION_INFO, std::format("There is no ladder here"), 1);
  }
}

void ExploreScreen::checkDoors(GameData::Position pos)
{
  GameData::LocationMap& map = mCurrentMap.getMap();
  const size_t RowSize = mCurrentMap.getMapSize().x;
  size_t index = pos.second * RowSize + pos.first;

  // check if the door is on the left from the player
  if (map.at(index - 1).isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first - 1, pos.second });
    if (pObject->getType() == GameObjectType::DOOR) {
      useDoor(pObject);
    }
  }
  // check if the player right of the door
  if (map.at(index + 1).isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first + 1, pos.second });
    if (pObject->getType() == GameObjectType::DOOR) {
      useDoor(pObject);
    }
  }
  // check if the player above the door
  if (map.at(index - RowSize).isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first, pos.second - 1 });
    if (pObject->getType() == GameObjectType::DOOR) {
      useDoor(pObject);
    }
  }
  // check if the player below the door
  if (map.at(index + RowSize).isObject()) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first, pos.second + 1 });
    if (pObject->getType() == GameObjectType::DOOR) {
      useDoor(pObject);
    }
  }
}

void ExploreScreen::useDoor(std::shared_ptr<GameObject> pObject)
{
  auto pDoor = std::static_pointer_cast<Door>(pObject);
  Location& location = mCurrentMap.getCurrentLocation(pDoor->getPosition());
  if (pDoor->getStatus() == DoorStatus::LOCKED) {
    pDoor->setStatus(DoorStatus::UNLOCKED);
    location.setBarrier(false);
  }
  else {
    pDoor->setStatus(DoorStatus::LOCKED);
    location.setBarrier(true);
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

bool ExploreScreen::checkNpcNearby(GameData::Position pos)
{
  GameData::LocationMap& map = mCurrentMap.getMap();
  const size_t RowSize = mCurrentMap.getMapSize().x;
  size_t index = pos.second * RowSize + pos.first;
  bool result{ false };
  // check if the npc left of the player
  if ((index % (RowSize) != 0) && (map.at(index - 1).isNpc())) {
    result = true;
    CurrentNpc::setNpc(std::make_unique<Npc>(mNpcManager.getNpc({ pos.first - 1, pos.second })));
  }
  // check if the npc right of the player
  else if ((index % (RowSize + 1) != 0) && (map.at(index + 1).isNpc())) {
    CurrentNpc::setNpc(std::make_unique<Npc>(mNpcManager.getNpc({ pos.first + 1, pos.second })));
    result = true;
  }
  // check if the npc above the player
  else if ((index >= RowSize) && (map.at(index - RowSize).isNpc())) {
    CurrentNpc::setNpc(std::make_unique<Npc>(mNpcManager.getNpc({ pos.first, pos.second - 1 })));
    result = true;
  }
  // check if the npc below the player
  else if ((index < mCurrentMap.getMapSize().y * RowSize - RowSize) && (map.at(index + RowSize).isNpc())) {
    result = true;
    CurrentNpc::setNpc(std::make_unique<Npc>(mNpcManager.getNpc({ pos.first, pos.second + 1 })));
  }

  return result;
}

void ExploreScreen::showShop()
{
  ScreenManager::createScreen(GameData::Screens::SHOP_SCREEN);
}

std::string ExploreScreen::showLocationInfo()
{
  std::string result{"You see "};

  GameData::Position currentPlayerLocation = mPlayer.getPosition();
  Location& location = mCurrentMap.getCurrentLocation(currentPlayerLocation);
  if (location.isObject()) {
    try {
      std::shared_ptr<GameObject> pObject = mObjectManager.getObject(currentPlayerLocation);
      if (pObject->getType() == GameObjectType::MONEY) {
        auto pMoneyObject = std::static_pointer_cast<Money>(pObject);
        result += std::format("${}", pMoneyObject->getAmount());
      }
      else {
        result += std::format("a {}", pObject->getName());
      }
    }
    catch (std::runtime_error re) {
      std::cout << std::format("{} in showLocationInfo()\n", re.what());
    }  
  }
  else {
    result += std::format(" nothing interesting here");
  }
  
  return result;
}

void ExploreScreen::changeMap()
{
  mCurrentMap = mLevel.getCurrentMap();
  mPlayer.spawn(mLevel.getPlayerSpawnPosition());
  mEnemyManager.createEnemies(mLevel.getCurrentEnemyListFilename());
  mObjectManager.createObjects(mLevel.getCurrentObjectListFilename());
  mNpcManager.createNpcs(mLevel.getCurrentNPCListFilename());
  mState = GameplayState::START;
}

void ExploreScreen::checkEnvironment(GameData::Position pos)
{
  // check if the object is on the left from the player
  if (mObjectManager.isObject({pos.first - 1, pos.second})) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first - 1, pos.second });
    if (!pObject->isVisible() && checkVisibility(pObject->getVisibility())) {
      pObject->setVisibleStatus(true);
    }
  }
  // check if the player right of the door
  if (mObjectManager.isObject({ pos.first + 1, pos.second })) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first + 1, pos.second });
    if (!pObject->isVisible() && checkVisibility(pObject->getVisibility())) {
      pObject->setVisibleStatus(true);
    }
  }
  // check if the player above the door
  if (mObjectManager.isObject({ pos.first, pos.second - 1 })) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first, pos.second - 1 });
    if (!pObject->isVisible() && checkVisibility(pObject->getVisibility())) {
      pObject->setVisibleStatus(true);
    }
  }
  // check if the player below the door
  if (mObjectManager.isObject({ pos.first, pos.second + 1 })) {
    std::shared_ptr<GameObject> pObject = mObjectManager.getObject({ pos.first, pos.second + 1 });
    if (!pObject->isVisible() && checkVisibility(pObject->getVisibility())) {
      pObject->setVisibleStatus(true);
    }
  }
}

bool ExploreScreen::checkVisibility(size_t value)
{
  size_t randomValue = dr::EngineUtility::getRandomInRange(GameData::DICE.x, GameData::DICE.y);
  std::cout << std::format("??? Skill: {} Dice: {} Check: {} ???\n", mPlayer.getSkillValue("Search"), 
    randomValue, value);
  return (mPlayer.getSkillValue("Search") + randomValue >= value) ? true : false;
}
