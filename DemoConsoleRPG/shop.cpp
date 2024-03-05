#include "shop.h"

void Shop::add(std::shared_ptr<GameObject> pObject)
{
}

std::string Shop::show()
{
  return std::string();
}

size_t Shop::getSize() const
{
  return mStaff.size();
}

std::shared_ptr<GameObject>& Shop::getItem(size_t index)
{
  return mStaff.at(index);
}

void Shop::destroyItem(size_t index)
{
}
