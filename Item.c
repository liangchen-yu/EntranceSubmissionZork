//
// Created by yumerxcy on 3/26/26.
//
#include <stdlib.h>
#include "Item.h"
// Creates a new item with a name and description
Item *CreateItem(char *name, char *description) {
    Item *item = (Item *)malloc(sizeof(Item));
    item->name = name;
    item->description = description;
    return item;
}