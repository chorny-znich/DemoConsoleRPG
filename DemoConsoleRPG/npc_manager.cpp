#include "Npc_manager.h"
#include <DisRealityGF.h>

void NpcManager::createNpcs(const std::string& filename)
{
  mNpc.clear();
  size_t NpcAmount{ 0 };
  ini::Document doc = ini::Load(filename);
  ini::Section section = doc.GetSection("general");
  NpcAmount = std::stoul(section.at("Npc_amount"));

  for (size_t i{ 1 }; i <= NpcAmount; i++) {
    Npc Npc;
    std::string sectionName = "npc_" + std::to_string(i);
    ini::Section section = doc.GetSection(sectionName);
    Npc.spawn({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
    Npc.setSymbol(section.at("Symbol")[0]);
    Npc.setName(section.at("Name"));
    mNpc.push_back(std::move(Npc));
  }
}

const std::vector<Npc>& NpcManager::getNpcs() const
{
  return mNpc;
}

std::vector<Npc>& NpcManager::getNpcs()
{
  return mNpc;
}

Npc& NpcManager::getNpc(GameData::Position pos)
{
  for (auto& npc : mNpc) {
    if (pos.first == npc.getPosition().first && pos.second == npc.getPosition().second) {
      return npc;
    }
  }
  throw std::runtime_error("Enemy don't exist");
}
