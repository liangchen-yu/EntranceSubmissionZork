#include <stdio.h>
#include <stdlib.h>

typedef struct Room {
    char *description;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    struct Room *up;
    struct Room *down;

} Room;

typedef struct {
    char *name;
    Room *currentRoom;
} Player;

Player *player;

Room *basement, *hallway, *garage, *office, *bathroom, *bedroom, *stairs, *upstairs, *attic, *exitDoor;

Room *CreateRoom(char *description) {
    Room *room = (Room *)malloc(sizeof(Room));
    room->description = description;
    room->north = NULL;
    room->south = NULL;
    room->east = NULL;
    room->west = NULL;
    room->up = NULL;
    room->down = NULL;
    return room;
}

void PrintRoom(Room *room) {
    printf("Room description: %s\n", room->description);
    printf("Exits: ");
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
}

void CreateRooms(void) {
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
}

Player *CreatePlayer(char *name, Room *start) {
    Player *p = (Player *)malloc(sizeof(Player));
    p->name = name;
    p->currentRoom = start;
    return p;
}

int main(void) {
    printf("Zork Text Based Game\n");
    CreateRooms();
    player = CreatePlayer("Player", basement);
    PrintRoom(player->currentRoom);
    return 0;
}