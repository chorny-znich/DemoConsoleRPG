#include "current_npc.h"
#include <cassert>

CurrentNpc::CurrentNpc()
{
  assert(mpInstance == nullptr);
  mpInstance = this;
}

void CurrentNpc::setNpc(std::unique_ptr<Npc> pNpc)
{
  auto& npc = mpInstance->mpNpc;
  npc = std::move(pNpc);
}

std::unique_ptr<Npc>& CurrentNpc::getNpc()
{
  auto& npc = mpInstance->mpNpc;

  return npc;
}
