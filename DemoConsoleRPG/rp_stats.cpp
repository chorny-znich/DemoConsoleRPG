#include "rp_stats.h"
#include <DisRealityGF.h>

void RPStats::setName(const std::string& name)
{
	mName = name;
}
const std::string& RPStats::getName() const
{
	return mName;
}

size_t RPStats::getLevel() const
{
	return mLevel;
}

void RPStats::setExperience(size_t exp)
{
	mExperience = exp;
}

void RPStats::increaseExperience(size_t exp)
{
	mExperience += exp;
}

size_t RPStats::getExperience() const
{
	return mExperience;
}

size_t& RPStats::getExperience()
{
	return mExperience;
}

void RPStats::setExperienceForKill(size_t exp)
{
	mExperienceForKill = exp;
}

size_t RPStats::getExperienceForKill() const
{
	return mExperienceForKill;
}

void RPStats::increaseMoney(size_t money)
{
	mMoney += money;
}

void RPStats::decreaseMoney(size_t money)
{
	mMoney = (money > mMoney) ? 0 : mMoney - money;
}

size_t RPStats::getMoney() const
{
	return mMoney;
}

size_t& RPStats::getMoney()
{
	return mMoney;
}

void RPStats::setAttack(size_t atk)
{
	mAttack = atk;
}

size_t RPStats::getAttack() const
{
	return mAttack;
}

void RPStats::setDefence(size_t def)
{
	mDefence = def;
}

size_t RPStats::getDefence() const
{
	return mDefence;
}

void RPStats::setDamage(sf::Vector2u dmg)
{
	mDamage = dmg;
}

sf::Vector2u RPStats::getDamage() const
{
	return mDamage;
}

size_t RPStats::getDamageValue() const
{
	return dr::EngineUtility::getRandomInRange(mDamage.x, mDamage.y);
}

void RPStats::setMaxHealth(size_t value)
{
	mMaxHealth = value;
}

size_t RPStats::getMaxHealth() const
{
	return mMaxHealth;
}

void RPStats::setHealth(size_t value)
{
	mHealth = value;
}

void RPStats::increaseHealth(size_t value)
{
	if (mMaxHealth >= mHealth + value) {
		mHealth += value;
	}
	else {
		mHealth = mMaxHealth;
	}
}

void RPStats::decreaseHealth(size_t value)
{
	mHealth = (mHealth > value) ? mHealth - value : 0;	
}

size_t RPStats::getHealth() const
{
	return mHealth;
}