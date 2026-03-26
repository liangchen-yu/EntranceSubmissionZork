//
// Created by yumerxcy on 3/26/26.
//

#ifndef ENTRANCESUBMISSIONZORK_DECLARATION_H
#define ENTRANCESUBMISSIONZORK_DECLARATION_H
#include "Item.h"

typedef struct {
    char *name;
    char *description;
    int searched;
    Item *hiddenItem;
} Furniture;

typedef struct Room {
    char *description;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    struct Room *up;
    struct Room *down;
    Item *items[10];
    int itemCount;
    Furniture *furniture[10];
    int furnitureCount;
} Room;

typedef struct {
    char *name;
    char *description;
    char *dialogue;
    Room *location;
} NPC;

typedef struct {
    char *name;
    Room *currentRoom;
    Item *inventory[10];
    int inventoryCount;
} Player;

typedef struct {
    char *commandWord;
    char *secondWord;
} Command;
// Globals
extern NPC *rat;
extern Player *player;
extern Room *basement, *hallway, *garage, *office, *bathroom, *bedroom, *stairs, *upstairs, *attic, *exitDoor;

extern int secretCode;
extern int codeboxOpened;
extern Furniture *codebox;

extern char input[500];
extern char word1[100];
extern char word2[100];
// Room functions
Room *CreateRoom(char *description);

void AddItemToRoom(Room *room, Item *item);
void PrintRoom(Room *room);
void CreateRooms(void);
void PlaceItemsRandomly(void);

Furniture *CreateFurniture(char *name, char *description);
void AddFurnitureToRoom(Room *room, Furniture *furniture);

NPC *CreateNPC(char *name, char *description, char *dialogue);
// Player functions
Player *CreatePlayer(char *name, Room *start);
int HasItem(char *itemName);

// Parser
Command GetCommand(void);
// Game functions
void GoRoom(Command cmd);
void TakeItem(Command cmd);
void ShowInventory(void);
void DropItem(Command cmd);
void SearchFurniture(Command cmd);
void InteractNPC(Command cmd);

void SaveGame(void);
void LoadGame(void);
void OpenCodeBox(void);
void ReadItem(Command cmd);
void PrintMap(void);
int ProcessCommand(Command cmd);
void PrintWelcome(void);

void Play(void);
char *GetRoomName(Room *room);
Room *GetRoomByName(char *name);

#endif //ENTRANCESUBMISSIONZORK_DECLARATION_H