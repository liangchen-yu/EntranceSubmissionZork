//
// Created by yumerxcy on 3/26/26.
//
#include <stdlib.h>
#include <string.h>
#include "Declaration.h"

Player *CreatePlayer(char *name, Room *start) {
    Player *p = (Player *)malloc(sizeof(Player));
    p->name = name;
    p->currentRoom = start;
    p->inventoryCount = 0;
    return p;
}
int HasItem(char *itemName) {
    for (int i = 0; i < player->inventoryCount; i++) {
        if (strcmp(player->inventory[i]->name, itemName) == 0) {
            return 1;
        }
    }
    return 0;
}