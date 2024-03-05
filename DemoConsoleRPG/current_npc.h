#pragma once

#include "npc.h"
#include <memory>

class CurrentNpc
{
  std::unique_ptr<Npc> mpNpc{ nullptr };
  static inline CurrentNpc* mpInstance{ nullptr };

public:
  CurrentNpc();
  static void setNpc(std::unique_ptr<Npc> pNpc);
  static std::unique_ptr<Npc>& getNpc();
  
};

