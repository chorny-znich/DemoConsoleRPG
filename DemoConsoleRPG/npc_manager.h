#pragma once

#include "npc.h"
#include <vector>

class NpcManager
{
private:
  std::vector<Npc> mNpc;

public:
  void createNpcs(const std::string& filename);
  const std::vector<Npc>& getNpcs() const;
  std::vector<Npc>& getNpcs();
  Npc& getNpc(GameData::Position pos);
};