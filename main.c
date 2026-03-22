#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct {
    char *commandWord;
    char *secondWord;
} Command;

Player *player;

Room *basement, *hallway, *garage, *office, *bathroom, *bedroom, *stairs, *upstairs, *attic, *exitDoor;

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

void PrintWelcome(void) {
    printf("\nWelcome to Escape It!\n");
    printf("You awaken in darkness. Your head throbs. You must escape.\n");
    printf("Type 'help' if you need help.\n\n"); //implementing this later
    PrintRoom(player->currentRoom);
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

void GoRoom(Command cmd) {
    if (cmd.secondWord == NULL) {
        printf("Go where?\n");
        return;
    }

    Room *next = NULL;

    if (strcmp(cmd.secondWord, "north") == 0) next = player->currentRoom->north;
    else if (strcmp(cmd.secondWord, "south") == 0) next = player->currentRoom->south;
    else if (strcmp(cmd.secondWord, "east") == 0) next = player->currentRoom->east;
    else if (strcmp(cmd.secondWord, "west") == 0) next = player->currentRoom->west;
    else if (strcmp(cmd.secondWord, "up") == 0) next = player->currentRoom->up;
    else if (strcmp(cmd.secondWord, "down") == 0) next = player->currentRoom->down;

    if (next == NULL) {
        printf("There is no door!\n");
    } else {
        player->currentRoom = next;
        PrintRoom(player->currentRoom);
    }
}

int ProcessCommand(Command cmd) {

    if (cmd.commandWord == NULL) {
        printf("I don't understand...\n");
        return 0;
    }

    if (strcmp(cmd.commandWord, "go") == 0) {
        GoRoom(cmd);
    } else if (strcmp(cmd.commandWord, "look") == 0) {
        PrintRoom(player->currentRoom);

    } else if (strcmp(cmd.commandWord, "help") == 0) {
        printf("Commands: go, look, help, quit\n");
    } else if (strcmp(cmd.commandWord, "quit") == 0) {
        return 1;
    } else {
        printf("Unknown command.\n");
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
    printf("Thank you for playing. Goodbye.\n");
}
int main(void) {
    CreateRooms();
    player = CreatePlayer("Player", basement);
    Play();
    return 0;
}