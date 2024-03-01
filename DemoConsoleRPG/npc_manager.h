#pragma once

#include "npc.h"
#include <vector>

class NPCManager
{
private:
  std::vector<NPC> mNPC;

public:
  void createNPCs(const std::string& filename);
  const std::vector<NPC>& getNPCs() const;
  std::vector<NPC>& getNPCs();
  NPC& getNPC(GameData::Position pos);
};