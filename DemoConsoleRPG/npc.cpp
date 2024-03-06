#include "npc.h"

void Npc::addStaff(std::shared_ptr<GameObject> object)
{
  mStaff.push_back(std::move(object));
}
