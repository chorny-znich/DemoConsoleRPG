// The roleplay system
// version 1
#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <SFML/System.hpp>
#include "game_data.h"

class RPStats
{
protected:
	const std::map<size_t, size_t> LevelCap{
		{0, 0}, {1, 25}, {2, 100}, {3, 250}, {4, 500}, {5, 1000}
	};
	const std::map<size_t, std::unordered_map<std::string, size_t>> Adventurer{
		{1, {{"attack", 0}, {"defence", 0}, {"health", 5}}},
		{2, {{"attack", 0}, {"defence", 1}, {"health", 5}}},
		{3, {{"attack", 1}, {"defence", 0}, {"health", 5}}},
		{4, {{"attack", 0}, {"defence", 1}, {"health", 5}}},
		{5, {{"attack", 1}, {"defence", 0}, {"health", 5}}}
	};

	std::string mName{ "Vargar" };
	size_t mExperience{ 0 };
	size_t mExperienceForKill{ 25 };
	std::size_t mMoney{ 0 };
	size_t mAttack{ 0 };
	size_t mDefence{ 0 };
	sf::Vector2u mDamage{ 0, 0 };
	size_t mArmor{ 0 };
	size_t mMaxHealth{ 30 };
	size_t mHealth{ 30 };
	//GameData::RPClass mClass{ GameData::RPClass::Adventurer };
	size_t mLevel{ 0 };

public:
	void setName(const std::string& name);
	const std::string& getName() const;
	size_t getLevel() const;
	void setExperience(size_t exp);
	void increaseExperience(size_t exp);
	size_t getExperience() const;
	size_t& getExperience();
	void setExperienceForKill(size_t exp);
	size_t getExperienceForKill() const;
	void setMoney(size_t money);
	void increaseMoney(size_t money);
	void decreaseMoney(size_t money);
	size_t getMoney() const;
	size_t& getMoney();
	void setAttack(size_t atk);
	size_t getAttack() const;
	void setDefence(size_t def);
	size_t getDefence() const;
	void setDamage(sf::Vector2u dmg);
	sf::Vector2u getDamage() const;
	size_t getDamageValue() const;
	void setArmor(size_t armor);
	size_t getArmor() const;
	void setMaxHealth(size_t value);
	size_t getMaxHealth() const;
	void setHealth(size_t value);
	void increaseHealth(size_t value);
	void decreaseHealth(size_t value);
	size_t getHealth() const;
};