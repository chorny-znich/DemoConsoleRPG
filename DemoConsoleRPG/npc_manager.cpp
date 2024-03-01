#include "npc_manager.h"
#include <DisRealityGF.h>

void NPCManager::createNPCs(const std::string& filename)
{
  mNPC.clear();
  size_t NPCAmount{ 0 };
  ini::Document doc = ini::Load(filename);
  ini::Section section = doc.GetSection("general");
  NPCAmount = std::stoul(section.at("NPC_amount"));

  for (size_t i{ 1 }; i <= NPCAmount; i++) {
    NPC npc;
    std::string sectionName = "npc_" + std::to_string(i);
    ini::Section section = doc.GetSection(sectionName);
    npc.spawn({ std::stoi(section.at("Position_x")), std::stoi(section.at("Position_y")) });
    npc.setSymbol(section.at("Symbol")[0]);
    npc.setName(section.at("Name"));
    mNPC.push_back(std::move(npc));
  }
}

const std::vector<NPC>& NPCManager::getNPCs() const
{
  return mNPC;
}

std::vector<NPC>& NPCManager::getNPCs()
{
  return mNPC;
}
