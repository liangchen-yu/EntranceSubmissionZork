#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char *name;
    char *description;
} Item;

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

NPC *rat;
Player *player;
Room *basement, *hallway, *garage, *office, *bathroom, *bedroom, *stairs, *upstairs, *attic, *exitDoor;

int secretCode;
int codeboxOpened = 0;
Furniture *codebox;
char input[500];
char word1[100];
char word2[100];

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

Item *CreateItem(char *name, char *description) {
    Item *item = (Item *)malloc(sizeof(Item));
    item->name = name;
    item->description = description;
    return item;
}

void AddItemToRoom(Room *room, Item *item) {
    int count = room->itemCount;
    room->items[count] = item;
    room->itemCount = room->itemCount + 1;
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

void PrintWelcome(void) {
    printf("\nWelcome to Escape It!\n");
    printf("You awaken in darkness. Your head throbs. You must escape.\n");
    printf("Type 'help' if you need help.\n\n"); //implementing this later
    PrintRoom(player->currentRoom);
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

Player *CreatePlayer(char *name, Room *start) {
    Player *p = (Player *)malloc(sizeof(Player));
    p->name = name;
    p->currentRoom = start;
    p->inventoryCount = 0;
    return p;
}

Command GetCommand(void) {
    Command cmd;
    cmd.commandWord = NULL;
    cmd.secondWord = NULL;

    printf("> ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = 0;

    word1[0] = '\0';
    word2[0] = '\0';

    sscanf(input, "%s %s", word1, word2);//fixed

    if (strlen(word1) > 0) cmd.commandWord = word1;
    if (strlen(word2) > 0) cmd.secondWord = word2;

    return cmd;
}

int HasItem(char *itemName) {
    for (int i = 0; i < player->inventoryCount; i++) {
        if (strcmp(player->inventory[i]->name, itemName) == 0) {
            return 1;
        }
    }
    return 0;
}

void GoRoom(Command cmd) {
    if (cmd.secondWord == NULL) {
        printf("Go where?\n");
        return;
    }
    Room *next = NULL;

    if (strcmp(cmd.secondWord, "north") == 0) {
        next = player->currentRoom->north;
    } else if (strcmp(cmd.secondWord, "south") == 0) {
        next = player->currentRoom->south;
    } else if (strcmp(cmd.secondWord, "east") == 0) {
        next = player->currentRoom->east;
    }else if (strcmp(cmd.secondWord, "west") == 0) {
        next = player->currentRoom->west;
    } else if (strcmp(cmd.secondWord, "up") == 0) {
        next = player->currentRoom->up;
    } else if (strcmp(cmd.secondWord, "down") == 0) {
        next = player->currentRoom->down;
    }

    if (next == NULL) {
        printf("There is no door!\n");
    } else if (next == attic && HasItem("rope") == 0) {
        printf("The attic trapdoor is locked. You need a rope to climb up.\n");
    } else if (next == exitDoor && HasItem("key") == 0) {
        printf("The exit door is locked. You need a key.\n");
    } else{
        player->currentRoom = next;
        PrintRoom(player->currentRoom);
        if (player->currentRoom == exitDoor) {
            printf("You've beaten the game!!, ");
            printf("You escaped the house!\n");
            exit(0); //Quit the game.
        }
    }
}

void TakeItem(Command cmd) {
    if (cmd.secondWord == NULL) {
        printf("Take what?\n");
        return;
    }
    Room *room = player->currentRoom;
    int foundIndex = -1;
    // Find item
    for (int i = 0; i < room->itemCount; i++) {
        if (strcmp(room->items[i]->name, cmd.secondWord) == 0) {
            foundIndex = i;
        }
    }
    // not foundd
    if (foundIndex == -1) {
        printf("There is no %s here.\n", cmd.secondWord);
        return;
    }
    // Get item
    Item *item = room->items[foundIndex];
    // Add to inventory
    player->inventory[player->inventoryCount] = item;
    player->inventoryCount = player->inventoryCount + 1;
    // Remove
    for (int i = foundIndex; i < room->itemCount - 1; i++) {
        room->items[i] = room->items[i + 1];
    }
    room->itemCount = room->itemCount - 1;
    printf("You picked up the %s.\n", item->name);
}

void ShowInventory(void) {
    if (player->inventoryCount == 0) {
        printf("Your inventory is empty.\n");
        return;
    }

    printf("You are carrying:\n");
    for (int i = 0; i < player->inventoryCount; i++) {
        printf("%s\n", player->inventory[i]->name);
    }
}

void DropItem(Command cmd) {
    if (cmd.secondWord == NULL) {
        printf("Drop what?\n");
        return;
    }

    int foundIndex = -1;
    // Find item in inventory
    for (int i = 0; i < player->inventoryCount; i++) {
        if (strcmp(player->inventory[i]->name, cmd.secondWord) == 0) {
            foundIndex = i;
        }
    }
    // Not found
    if (foundIndex == -1) {
        printf("You don't have a %s.\n", cmd.secondWord);
        return;
    }
    // Get
    Item *item = player->inventory[foundIndex];
    // Add
    Room *room = player->currentRoom;
    room->items[room->itemCount] = item;
    room->itemCount = room->itemCount + 1;
    for (int i = foundIndex; i < player->inventoryCount - 1; i++) {
        player->inventory[i] = player->inventory[i + 1];
    }
    player->inventoryCount = player->inventoryCount - 1;
    printf("You dropped the %s.\n", item->name);
}

void SearchFurniture(Command cmd) {
    if (cmd.secondWord == NULL) {
        printf("Search what?\n");
        return;
    }
    Room *room = player->currentRoom;
    for (int i = 0; i < room->furnitureCount; i++) {
        if (strcmp(room->furniture[i]->name, cmd.secondWord) == 0) {
            Furniture *furniture = room->furniture[i];
            printf("You search the %s. %s\n", furniture->name, furniture->description);

            // Check if already searched
            if (furniture->searched == 1) {
                printf("You already searched this\n");
                return;
            }
            // Check for hidden item
            if (furniture->hiddenItem != NULL) {
                printf("You found a %s!\n", furniture->hiddenItem->name);
                printf("Use 'take %s' to pick it up\n", furniture->hiddenItem->name);
                AddItemToRoom(room, furniture->hiddenItem);
                furniture->hiddenItem = NULL;
            } else if (strcmp(furniture->name, "closet") == 0 && codeboxOpened == 0) {
                printf("You found a codebox inside!\n");
                AddFurnitureToRoom(room, codebox);
            } else {
                printf("You found nothing useful\n");
            }
            furniture->searched = 1;
            return;
        }
    }
    printf("There is no %s here.\n", cmd.secondWord);
}

void InteractNPC(Command cmd) {
    if (cmd.secondWord == NULL) {
        printf("Interact with what?\n");
        return;
    }
    if (strcmp(cmd.secondWord, "rat") == 0 && rat->location == player->currentRoom) {
        printf("The rat says: %s\n", rat->dialogue);
    } else {
        printf("There is no %s here.\n", cmd.secondWord);
    }
}

char *GetRoomName(Room *room) {
    if (room == basement) {
        return "basement";
    } else if (room == hallway) {
        return "hallway";
    } else if (room == garage) {
        return "garage";
    } else if (room == office) {
        return "office";
    } else if (room == bathroom) {
        return "bathroom";
    } else if (room == bedroom) {
        return "bedroom";
    } else if (room == stairs) {
        return "stairs";
    } else if (room == upstairs) {
        return "upstairs";
    } else if (room == attic) {
        return "attic";
    } else if (room == exitDoor) {
        return "exit";
    } else {
        return "unknown";
    }
}

Room *GetRoomByName(char *name) {
    if (strcmp(name, "basement") == 0) {
        return basement;
    } else if (strcmp(name, "hallway") == 0) {
        return hallway;
    } else if (strcmp(name, "garage") == 0) {
        return garage;
    } else if (strcmp(name, "office") == 0) {
        return office;
    } else if (strcmp(name, "bathroom") == 0) {
        return bathroom;
    } else if (strcmp(name, "bedroom") == 0) {
        return bedroom;
    } else if (strcmp(name, "stairs") == 0) {
        return stairs;
    } else if (strcmp(name, "upstairs") == 0) {
        return upstairs;
    } else if (strcmp(name, "attic") == 0) {
        return attic;
    } else if (strcmp(name, "exit") == 0) {
        return exitDoor;
    } else {
        return basement;
    }
}

void SaveGame(void) {
    FILE *file = fopen("savegame.txt", "w");
    if (file == NULL) {
        printf("Could not save game\n");
        return;
    }// Save current room
    fprintf(file, "%s\n", GetRoomName(player->currentRoom));
    // Save inventory count
    fprintf(file, "%d\n", player->inventoryCount);
    // Sav each item
    for (int i = 0; i < player->inventoryCount; i++) {
        fprintf(file, "%s\n", player->inventory[i]->name);
    }
    fprintf(file, "%d\n", secretCode); // saves code aswell
    fclose(file);
    printf("Game saved!\n");
}

void LoadGame(void) {
    FILE *file = fopen("savegame.txt", "r");
    if (file == NULL) {
        printf("No save file found\n");
        return;
    }
    char roomName[100];
    int itemCount;
    // Load current room
    fscanf(file, "%s", roomName);
    player->currentRoom = GetRoomByName(roomName);
    // Load inventory count
    fscanf(file, "%d", &itemCount);
    // Load each item
    player->inventoryCount = 0;
    for (int i = 0; i < itemCount; i++) {
        char itemName[100];
        fscanf(file, "%s", itemName);
        player->inventory[player->inventoryCount] = CreateItem(itemName, "loaded item");
        player->inventoryCount = player->inventoryCount + 1;
    }
    fscanf(file, "%d", &secretCode);
    fclose(file);
    printf("Game loaded!\n");
    PrintRoom(player->currentRoom);
}

void OpenCodeBox(void) {
    Room *room = player->currentRoom;
    // Check if codebox is in room
    int found = 0;
    for (int i = 0; i < room->furnitureCount; i++) {
        if (strcmp(room->furniture[i]->name, "codebox") == 0) {
            found = 1;
        }
    }
    if (found == 0) {
        printf("There is no codebox here.\n");
        return;
    }
    if (codeboxOpened == 1) {
        printf("The codebox is already open.\n");
        return;
    }
    // Ask for code
    printf("Enter 3-digit code: ");
    int guess;
    scanf("%d", &guess);
    getchar();
    if (guess == secretCode) {
        printf("Click! The codebox opens!\n");
        printf("You found a key! Use 'take key' to pick it up.\n");
        AddItemToRoom(room, codebox->hiddenItem);
        codebox->hiddenItem = NULL;
        codeboxOpened = 1;
    } else {
        printf("Wrong code. The lock doesn't budge.\n");
    }
}

void ReadItem(Command cmd) {
    if (cmd.secondWord == NULL) {
        printf("Read what?\n");
        return;
    }

    // Check inventory for item
    for (int i = 0; i < player->inventoryCount; i++) {
        if (strcmp(player->inventory[i]->name, cmd.secondWord) == 0) {
            printf("%s\n", player->inventory[i]->description);
            return;
        }
    }

    printf("You don't have a %s.\n", cmd.secondWord);
}
void PrintMap(void) {
    printf("\n");
    printf("      GROUND FLOOR                              UPSTAIRS\n");
    printf("\n");
    printf("         [Exit Door]                             [Attic]        [Bathroom]\n");
    printf("              |                                    |              |\n");
    printf("        north(need key)                        up(need rope)     north\n");
    printf("              |                                    |               |\n");
    printf("[Garage]--[Hallway]---[Stairs]      [Office]---[Upstairs]------[Bedroom]\n");
    printf("  (rat)       |           |         (drawer)       |\n");
    printf("            south         |                      down\n");
    printf("              |           |                        |\n");
    printf("         [Basement]       | -----------------> (to Stairs)\n");
    printf("        *START HERE\n");
    printf("\n");
}

int ProcessCommand(Command cmd) {

    if (cmd.commandWord == NULL) {
        printf("I don't understand\n");
        return 0;
    }
    if (strcmp(cmd.commandWord, "go") == 0) {
        GoRoom(cmd);
    } else if (strcmp(cmd.commandWord, "look") == 0) {
        PrintRoom(player->currentRoom);
    } else if (strcmp(cmd.commandWord, "help") == 0) {
        printf("Commands: go, look, take, drop, inventory, search, read, interact, open, save, load, debug, teleport, map, help, quit\n");
    } else if (strcmp(cmd.commandWord, "take") == 0) {
        TakeItem(cmd);
    } else if (strcmp(cmd.commandWord, "drop") == 0) {
        DropItem(cmd);
    } else if (strcmp(cmd.commandWord, "inventory") == 0) {
        ShowInventory();
    } else if (strcmp(cmd.commandWord, "search") == 0) {
        SearchFurniture(cmd);
    } else if (strcmp(cmd.commandWord, "quit") == 0) {
        return 1;
    } else if (strcmp(cmd.commandWord, "debug") == 0) {
        // Give all items
        player->inventory[player->inventoryCount] = CreateItem("rope", "debug rope");
        player->inventoryCount = player->inventoryCount + 1;
        player->inventory[player->inventoryCount] = CreateItem("key", "debug key");
        player->inventoryCount = player->inventoryCount + 1;
        printf("DEBUG: Added rope and key to inventory.\n");
    } else if (strcmp(cmd.commandWord, "teleport") == 0) {
        if (cmd.secondWord == NULL) {
            printf("teleport where? (basement, hallway, garage, office, bathroom, bedroom, stairs, upstairs, attic, exit)\n");
        } else if (strcmp(cmd.secondWord, "basement") == 0) {
            player->currentRoom = basement;
            PrintRoom(player->currentRoom);
        } else if (strcmp(cmd.secondWord, "hallway") == 0) {
            player->currentRoom = hallway;
            PrintRoom(player->currentRoom);
        } else if (strcmp(cmd.secondWord, "garage") == 0) {
            player->currentRoom = garage;
            PrintRoom(player->currentRoom);
        } else if (strcmp(cmd.secondWord, "office") == 0) {
            player->currentRoom = office;
            PrintRoom(player->currentRoom);
        } else if (strcmp(cmd.secondWord, "bathroom") == 0) {
            player->currentRoom = bathroom;
            PrintRoom(player->currentRoom);
        } else if (strcmp(cmd.secondWord, "bedroom") == 0) {
            player->currentRoom = bedroom;
            PrintRoom(player->currentRoom);
        } else if (strcmp(cmd.secondWord, "stairs") == 0) {
            player->currentRoom = stairs;
            PrintRoom(player->currentRoom);
        } else if (strcmp(cmd.secondWord, "upstairs") == 0) {
            player->currentRoom = upstairs;
            PrintRoom(player->currentRoom);
        } else if (strcmp(cmd.secondWord, "attic") == 0) {
            player->currentRoom = attic;
            PrintRoom(player->currentRoom);
        } else if (strcmp(cmd.secondWord, "exit") == 0) {
            player->currentRoom = exitDoor;
            PrintRoom(player->currentRoom);
        } else {
            printf("Unkown room\n");
        }
    } else if (strcmp(cmd.commandWord, "interact") == 0) {
        InteractNPC(cmd);
    } else if (strcmp(cmd.commandWord, "save") == 0) {
        SaveGame();
    } else if (strcmp(cmd.commandWord, "load") == 0) {
        LoadGame();
    } else if (strcmp(cmd.commandWord, "open") == 0) {
        if (cmd.secondWord != NULL && strcmp(cmd.secondWord, "codebox") == 0) {
            OpenCodeBox();
        } else {
            printf("Open what? Invalid\n");
        }
    } else if (strcmp(cmd.commandWord, "read") == 0) {
        ReadItem(cmd);
    } else if (strcmp(cmd.commandWord, "map") == 0) {
        PrintMap();
    } else {
        printf("Unknown command\n");
    }
    return 0;
}

void Play(void) {
    PrintWelcome();
    int finished = 0;
    while (!finished) {
        Command cmd = GetCommand();
        finished = ProcessCommand(cmd);
    }
}

int main(void) {
    CreateRooms();
    player = CreatePlayer("Player", basement);
    Play();
    return 0;
}