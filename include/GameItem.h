#ifndef GAMEITEM_H_
#define GAMEITEM_H_
#include "GameObject.h"

enum class ItemType{Player,Fruit,Wall,Empty,BadFruit};

struct GameItem
{
  ItemType type = ItemType::Empty;

  GameObject* obj = nullptr;
};


#endif