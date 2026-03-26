//
// Created by yumerxcy on 3/26/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Declaration.h"

Room *CreateRoom(char *description) {
    Room *room = (Room *)malloc(sizeof(Room));
    room->description = description;
    room->north = NULL;
    room->south = NULL;
    room->east = NULL;
    room->west = NULL;
    room->up = NULL;
    room->down = NULL;
    room->itemCount = 0;
    room->furnitureCount = 0;
    return room;
}
void AddItemToRoom(Room *room, Item *item) {
    int count = room->itemCount;
    room->items[count] = item;
    room->itemCount = room->itemCount + 1;
}

Furniture *CreateFurniture(char *name, char *description) {
    Furniture *furniture = (Furniture *)malloc(sizeof(Furniture));
    furniture->name = name;
    furniture->description = description;
    furniture->searched = 0;
    furniture->hiddenItem = NULL;
    return furniture;
}

void AddFurnitureToRoom(Room *room, Furniture *furniture) {
    int count = room->furnitureCount;
    room->furniture[count] = furniture;
    room->furnitureCount = room->furnitureCount + 1;
}

NPC *CreateNPC(char *name, char *description, char *dialogue) {
    NPC *npc = (NPC *)malloc(sizeof(NPC));
    npc->name = name;
    npc->description = description;
    npc->dialogue = dialogue;
    npc->location = NULL;
    return npc;
}
void PrintRoom(Room *room) {
    printf("Room description: %s\n", room->description);

    if (room->itemCount > 0) {
        printf("Items: \n");
        for (int i = 0; i < room->itemCount; i++) {
            printf("%s \n", room->items[i]->name);
        }
        printf("\n");
    }

    if (room->furnitureCount > 0) {
        printf("You see: ");
        for (int i = 0; i < room->furnitureCount; i++) {
            printf("%s ", room->furniture[i]->name);
        }
        printf("\n");
    }

    printf("Exits: \n");
    if (room->north) {
        printf("north\n");
    }
    if (room->south) {
        printf("south\n");
    }
    if (room->east) {
        printf("east\n");
    }
    if (room->west) {
        printf("west\n");
    }
    if (room->up) {
        printf("up\n");
    }
    if (room->down) {
        printf("down\n");
    }
    if (rat->location == room) {
        printf("You see a %s here\n", rat->name);
    }
}
void PlaceItemsRandomly(void) {
    int random1 = rand() % 7;
    int random2 = rand() % 7;
    int random3 = rand() % 7;

    // put rope somewhere
    if (random1 == 0) {
        AddItemToRoom(basement, CreateItem("rope", "a long, frayed rope"));
    } else if (random1 == 1) {
        AddItemToRoom(hallway, CreateItem("rope", "a long, frayed rope"));
    } else if (random1 == 2) {
        AddItemToRoom(garage, CreateItem("rope", "a long, frayed rope"));
    } else if (random1 == 3) {
        AddItemToRoom(bathroom, CreateItem("rope", "a long, frayed rope"));
    } else if (random1 == 4) {
        AddItemToRoom(bedroom, CreateItem("rope", "a long, frayed rope"));
    } else if (random1 == 5) {
        AddItemToRoom(stairs, CreateItem("rope", "a long, frayed rope"));
    } else {
        AddItemToRoom(upstairs, CreateItem("rope", "a long, frayed rope"));
    }

    // put wrench somewhere
    if (random2 == 0) {
        AddItemToRoom(basement, CreateItem("wrench", "a heavy steel wrench"));
    } else if (random2 == 1) {
        AddItemToRoom(hallway, CreateItem("wrench", "a heavy steel wrench"));
    } else if (random2 == 2) {
        AddItemToRoom(garage, CreateItem("wrench", "a heavy steel wrench"));
    } else if (random2 == 3) {
        AddItemToRoom(bathroom, CreateItem("wrench", "a heavy steel wrench"));
    } else if (random2 == 4) {
        AddItemToRoom(bedroom, CreateItem("wrench", "a heavy steel wrench"));
    } else if (random2 == 5) {
        AddItemToRoom(stairs, CreateItem("wrench", "a heavy steel wrench"));
    } else {
        AddItemToRoom(upstairs, CreateItem("wrench", "a heavy steel wrench"));
    }

    // put note somewhere
    if (random3 == 0) {
        AddItemToRoom(basement, CreateItem("note", "a torn piece of paper"));
    } else if (random3 == 1) {
        AddItemToRoom(hallway, CreateItem("note", "a torn piece of paper"));
    } else if (random3 == 2) {
        AddItemToRoom(garage, CreateItem("note", "a torn piece of paper"));
    } else if (random3 == 3) {
        AddItemToRoom(bathroom, CreateItem("note", "a torn piece of paper"));
    } else if (random3 == 4) {
        AddItemToRoom(bedroom, CreateItem("note", "a torn piece of paper"));
    } else if (random3 == 5) {
        AddItemToRoom(stairs, CreateItem("note", "a torn piece of paper"));
    } else {
        AddItemToRoom(upstairs, CreateItem("note", "a torn piece of paper"));
    }
}
void CreateRooms(void) {
    srand(time(NULL));
    secretCode = (rand() % 900) + 100;
    // Create all rooms
    basement = CreateRoom("In the cold, damp basement. Water drips from the rusty pipes overhead");
    hallway = CreateRoom("In the narrow, dark hallway");
    garage = CreateRoom("In the dusty, old garage");
    office = CreateRoom("In the messy, cluttered office");
    bathroom = CreateRoom("in the grimy bathroom. The mirror is cracked and the faucet drips steadily");
    bedroom = CreateRoom("In the bedroom. The bed sheets are stained and moth-eaten");
    stairs = CreateRoom("on the creaky wooden stairs. Each step groans under your weight");
    upstairs = CreateRoom("upstairs in the dim corridor. Moonlight filters through a broken window");
    attic = CreateRoom("in the dark, suffocating attic. Cobwebs hang from every corner");
    exitDoor = CreateRoom("at the exit");

    // Link rooms
    basement->north = hallway;
    hallway->south = basement;
    hallway->east = stairs;
    hallway->west = garage;
    hallway->north = exitDoor;
    garage->east = hallway;
    stairs->west = hallway;
    stairs->up = upstairs;
    upstairs->down = stairs;
    upstairs->east = bedroom;
    bedroom->west = upstairs;
    bedroom->north = bathroom;
    bathroom->south = bedroom;
    upstairs->up = attic;
    attic->down = upstairs;
    upstairs->west = office;
    office->east = upstairs;

    // Drawer with notebook and has code
    Furniture *drawer = CreateFurniture("drawer", "a rusted drawer attached to the desk");
    char *notebookDesc = malloc(100);
    sprintf(notebookDesc, "a weathered notebook. Inside it says: The code is %d", secretCode);
    drawer->hiddenItem = CreateItem("notebook", notebookDesc);
    AddFurnitureToRoom(office, drawer);
    // Closet up inattic
    Furniture *closet = CreateFurniture("closet", "a tall, dusty wooden closet");
    AddFurnitureToRoom(attic, closet);
    // Codebox inside closet
    codebox = CreateFurniture("codebox", "a small metal box with a 3-digit lock");
    codebox->hiddenItem = CreateItem("key", "a rusty old key");
    rat = CreateNPC("rat", "a grey rat with beady eyes", "The closet upstairs.. squeak...something shiny, and the notebook has werid number in it!");
    rat->location = garage;
    PlaceItemsRandomly();
}